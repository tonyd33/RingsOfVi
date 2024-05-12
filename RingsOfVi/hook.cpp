#include "pch.h"
#include <cstdlib>
#include "hook.h"
#include "lend.h"
#include <vector>
#include <iostream>

#define MIN_OVERWRITE_SIZE 5 // jmp [relative address] is at least 5 bytes

namespace Memory {
    /* helper class for adding assembly instructions easily. allows for a file-like interface for pushing bytes
       into the stream. */
    class ByteStream {
    public:
        std::vector<BYTE> bytes;

        ByteStream& operator<<(uint8_t byte) {
            bytes.push_back(byte);
            return *this;
        }

        ByteStream& operator<<(const char* str) {
            size_t len = strlen(str);
            for (size_t i = 0; i < len; ++i) {
                bytes.push_back(static_cast<BYTE>(str[i]));
            }
            return *this;
        }

        ByteStream& operator<<(const std::vector<BYTE>& data) {
            bytes.insert(bytes.end(), data.begin(), data.end());
            return *this;
        }
        /* pushes a 4 byte value into the stream. since we have an overload that takes in 1 byte value, we
           can't mistakenly cast a 1 byte value into 4 bytes before pushing. */
        ByteStream& operator<<(uint32_t value) {
            bytes.push_back(static_cast<BYTE>(value & 0xFF));
            bytes.push_back(static_cast<BYTE>((value >> 8) & 0xFF));
            bytes.push_back(static_cast<BYTE>((value >> 16) & 0xFF));
            bytes.push_back(static_cast<BYTE>((value >> 24) & 0xFF));
            return *this;
        }

        size_t size() const {
            return bytes.size();
        }
    };

    Hook::~Hook() { }

    BOOL Hook::SetTarget(uintptr_t target) {
        if (hooked) return false;
        this->target = target;
        initialized = false;
    }

    BOOL Hook::SetHook(uintptr_t hook) {
        if (hooked) return false;
        this->hook = hook;
        initialized = false;
    }

    void Hook::SetExtraIn(
        void* extraIn,
        void* extraInStorage,
        BOOL extraInIsPtr
    ) {
        this->hasExtraIn = true;
        this->extraIn = extraIn;
        this->extraInStorage = extraInStorage;
        this->extraInIsPtr = extraInIsPtr;
    }

    BOOL Hook::Initialize(uintptr_t* out) {
        if (target == NULL || hook == NULL) return false;
        if (initialized) return true;
        // TODO: handle error codes and better way of not mangling instruction
 
        /* figure out how many bytes to patch. we must make sure the
           overwritten bytes are instruction-aligned. problem right now is that
           if the entire function body is less than 5 bytes (e.g. just a ret),
           then we could be mangling instructions for the next function. */
        uintptr_t curr = target;
        BYTE instrFirstByte = *(BYTE*)curr;
        while (
            // need at least 5 bytes
            curr - target < MIN_OVERWRITE_SIZE &&
            // stop on ret instructions
            instrFirstByte != 0xc3 &&
            instrFirstByte != 0xcb &&
            instrFirstByte != 0xc2 &&
            instrFirstByte != 0xca
         ) {
            // read length of instruction; go to next
            curr += length_disasm((void*)curr);
            instrFirstByte = *(BYTE*)curr;
        }

        /* we are now at an instruction-aligned address. but is there enough 
           room? */
        patchLen = curr - target;
        if (patchLen < MIN_OVERWRITE_SIZE) return false;

        returnAddr = target + patchLen;

        // copy the original instructions into the buffer
        orig.resize(patchLen);
        memcpy(&orig[0], (void*)target, patchLen);

        // this is where we'll jump to 
        ByteStream strm;

        // set some value before executing the rest of the function
        if (hasExtraIn) {
            // push ecx
            strm << "\x51";
            // mov ecx, extraInStorage
            strm << "\xb9" << (uintptr_t)extraInStorage;
            // TODO: fix if it's a pointer. we're not actually dynamically
            // getting the value at the ptr lmao
            // mov [ecx], extraIn
            strm << "\xc7\x01" << (extraInIsPtr ? *(uint32_t*)extraIn : (uint32_t)extraIn);
            // pop ecx
            strm << "\x59";
        }

        // jmp hook
        strm << "\xff\x25" << (uint32_t)&hook;

        /* the contents of the start of the original function are gonna be
           placed at this offset from the trampoline */
        unsigned trueFuncTrampOffset = strm.size();
        // original function
        strm << orig;
        // jmp returnAddr
        strm << "\xff\x25" << (uint32_t)&returnAddr;

        trampoline = strm.bytes;

        trueFuncAddr = (uintptr_t)(&trampoline[0] + trueFuncTrampOffset);
        *out = trueFuncAddr;

        initialized = true;
        return true;
    }

    BOOL Hook::Enable() {
        if (!initialized) return false;
        if (this->hooked) return true;

        // TODO: return false on errors
        VirtualProtect(&trampoline[0], trampoline.size(), PAGE_EXECUTE_READWRITE, &trampolineProtect);

        DWORD currProtect;
        VirtualProtect((LPVOID)target, patchLen, PAGE_EXECUTE_READWRITE, &currProtect);

        // fill with nops
        memset((void*)target, 0x90, patchLen);

        // jmp instruction placed is 5 bytes
        DWORD relAddr = ((DWORD)&trampoline[0] - (DWORD)target) - 5;

        // jmp relAddr
        *(BYTE*)target = 0xe9;
        *(DWORD*)((DWORD)target + 1) = relAddr;

        DWORD temp;
        VirtualProtect((LPVOID)target, patchLen, currProtect, &temp);

        this->hooked = true;

        return true;
    }

    BOOL Hook::Disable(){
        if (this->hooked == false) return false;

        // TODO: return false on errors
        DWORD currProtect;

        VirtualProtect((LPVOID)target, patchLen, PAGE_EXECUTE_READWRITE, &currProtect);
        memcpy((void*)target, &orig[0], patchLen);
        VirtualProtect((LPVOID)target, patchLen, currProtect, &currProtect);

        /* restore old protections */
        /* actually, don't do this. it's very possible that the IP is within
           the trampoline as we try to do set back to non-executable memory.
           if we want to restore the protections, we'd have to flush the
           current calls out of here and then restore it. or check how MS
           detours does it. */
        // VirtualProtect(&trampoline[0], patchLen, trampolineProtect, &trampolineProtect);

        this->hooked = false;

        return true;
    }
}
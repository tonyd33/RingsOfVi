#pragma once
#include <Windows.h>
#include <vector>

namespace Memory {
    class Hook {
    public:
        uintptr_t target = NULL;
        uintptr_t hook = NULL;
        void* extraIn = NULL;
        void* extraInStorage = NULL;
        BOOL extraInIsPtr;
        BOOL hasExtraIn;

        BOOL hooked = false;
        BOOL initialized = false;

        ~Hook();

        BOOL SetTarget(uintptr_t target);
        BOOL SetHook(uintptr_t hook);
        /* if set, will store the value of extraIn or value pointed by extraIn
           into the pointer pointed by extraInStorage before executing the
           function. */
        void SetExtraIn(
            void* extraIn,
            void* extraInStorage,
            BOOL extraInIsPtr
        );

        /* returns whether initialization successful. stores the original
           function ptr into out */
        BOOL Initialize(uintptr_t* out);

        /* returns whether hook was successful. Initialize must be called
           before this. */
        BOOL Enable();

        /* returns whether undoing hook was successful */
        BOOL Disable();

    private:
        /* how many bytes did we overwrite */
        unsigned patchLen;
        /* the bytes that have been/will be overwritten. */
        std::vector<BYTE> orig;
        /* set up the hook */
        std::vector<BYTE> trampoline;
        /* the way we set this up, we'll still have a way to call the original
           function. */
        uintptr_t trueFuncAddr;
        uintptr_t returnAddr;

        DWORD trampolineProtect;
    };
}
#pragma once
#include <string>
#include <vector>
#include <map>
#include "wrapped_types.h"
#include "hookgroup.h"
#include "hook.h"

typedef std::string GeneralTarget;

class GeneralHooks : public HookGroup<void*, GeneralTarget, void*> {
protected:
    struct TargInfo;

    std::vector<GeneralTarget> targets;
    std::vector<TargInfo> targetInfos;
    std::map<GeneralTarget, HookGroup::TargHookInfo> targToHookInfo;
    std::map<uint32_t, void*> targHookInfoToHandler;

    /* we need extra info */
    void AddTarget(GeneralTarget target, uintptr_t addr, TargInfo targInfo);
    void* GetGateway() override;
    void* GetGateway(TargInfo);
    void LoadHookAddrs() override;
    void* GetParamStorage() override;

    TargInfo GWGetTargInfo();

public:
    enum CallingConvention : unsigned char {
        CC_FASTCALL,
        CC_CDECL,
        CC_STDCALL,
     };

    struct TargInfo {
        CallingConvention cc;
        unsigned char nargs;
        unsigned char hasReturn;
        unsigned char free;
        TargInfo(
            CallingConvention cc,
            unsigned nargs,
            bool hasReturn
        );
    };
    static_assert(sizeof(TargInfo) == 4, "TargInfo should be small");

    static GeneralHooks& Instance();
    void PrepareHooks();

    static void  __fastcall HandleFastcallHook0_0();
    static void  __fastcall HandleFastcallHook1_0(void*);
    static void  __fastcall HandleFastcallHook2_0(void*, void*);
    static void* __fastcall HandleFastcallHook0_1();
    static void* __fastcall HandleFastcallHook1_1(void*);
    static void* __fastcall HandleFastcallHook2_1(void*, void*);
};

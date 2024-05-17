#include "pch.h"
#include <iostream>
#include "general_hooks.h"
#include "game.h"

typedef GeneralHooks::TargInfo TargInfo;
typedef GeneralHooks::CallingConvention CallingConvention;

static int currIndex = 0;

TargInfo::TargInfo(
    CallingConvention cc,
    unsigned nargs,
    bool hasReturn
) {
    this->cc = cc;
    this->nargs = nargs;
    this->hasReturn = hasReturn;
}

TargInfo GeneralHooks::GWGetTargInfo() {
    void* storage = GetParamStorage();
    int index = *(int*)storage;

    return targetInfos[index];
}

GeneralHooks& GeneralHooks::Instance() {
    static GeneralHooks instance;
    return instance;
}

void GeneralHooks::LoadHookAddrs() {
    // set targ info map
    TargInfo ti = TargInfo(CC_FASTCALL, 0, 0);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook0_0;

    ti = TargInfo(CC_FASTCALL, 1, 0);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook1_0;

    ti = TargInfo(CC_FASTCALL, 2, 0);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook2_0;

    ti = TargInfo(CC_FASTCALL, 0, 1);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook0_1;

    ti = TargInfo(CC_FASTCALL, 1, 1);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook1_1;

    ti = TargInfo(CC_FASTCALL, 2, 1);
    targHookInfoToHandler[*(uint32_t*)&ti] = HandleFastcallHook2_1;

    uintptr_t base = Game::modBaseAddr;
    AddTarget(
        "computeEventList",
        base + 0x59b90,
        TargInfo(GeneralHooks::CC_FASTCALL, 2, false)
    );
}

void GeneralHooks::AddTarget(GeneralTarget target, uintptr_t addr, TargInfo targInfo) {
    targets.push_back(target);
    targetAddrs.push_back(addr);
    targetInfos.push_back(targInfo);
}

void* GeneralHooks::GetGateway() {
    return NULL;
}

void* GeneralHooks::GetGateway(TargInfo targInfo) {
    return targHookInfoToHandler[*(uint32_t*)&targInfo];
}

void* GeneralHooks::GetParamStorage() {
    return (void*)&currIndex;
}

void GeneralHooks::PrepareHooks() {
    LoadHookAddrs();
    void* storage = GetParamStorage();

    for (int i = 0; i < targets.size(); i++) {
        GeneralTarget name = targets[i];
        uintptr_t addr = targetAddrs[i];
        TargInfo targInfo = targetInfos[i];
        void* gateway = GetGateway(targInfo);

        TargHookInfo* targetHookInfo = new TargHookInfo();
        targetHookInfo->hook->SetHook((uintptr_t)gateway);
        targetHookInfo->hook->SetTarget(addr);
        targetHookInfo->hook->SetExtraIn((void*)i, storage, false);
        targetHookInfo->hook->Initialize((uintptr_t*)&targetHookInfo->trueFunc);
        targetToInfo[name] = targetHookInfo;
    }
}

void  __fastcall GeneralHooks::HandleFastcallHook0_0() {
    std::cout << "shiiiet\n";
    GeneralHooks& ghs = GeneralHooks::Instance();
    auto targetInfo = ghs.GWGetTargHookInfo();
    auto thi = ghs.GWGetTargHookInfo();
    ((void(__fastcall*)())thi->trueFunc)();
}

void  __fastcall GeneralHooks::HandleFastcallHook1_0(void*) {
    GeneralHooks& ghs = GeneralHooks::Instance();
    auto targetInfo = ghs.GWGetTargHookInfo();
}
void  __fastcall GeneralHooks::HandleFastcallHook2_0(void*, void*) {
    std::cout << "shiiiet\n";
}
void* __fastcall GeneralHooks::HandleFastcallHook0_1() {
    return 0;
}
void* __fastcall GeneralHooks::HandleFastcallHook1_1(void*) {
    return 0;
}
void* __fastcall GeneralHooks::HandleFastcallHook2_1(void*, void*) {
    return 0; 
}

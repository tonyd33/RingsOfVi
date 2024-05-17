#include "pch.h"
#include "game.h"
#include "general_hooks.h"
#include <iostream>

static int currIndex = 0;

ComputeEventListHook& ComputeEventListHook::Instance() {
    static ComputeEventListHook instance;
    return instance;
}

void* ComputeEventListHook::GetParamStorage() {
    return (void*)&currIndex;
}

void __fastcall ComputeEventListHook::HandleComputeEventListHook(void* oiList, void* param_2) {
    ComputeEventListHook& celh = ComputeEventListHook::Instance();
    auto targetInfo = celh.GWGetTargHookInfo();

    targetInfo->trueFunc(oiList, param_2);
}

OrigComputeEventListFunc ComputeEventListHook::GetGateway() {
    return HandleComputeEventListHook;
}

void ComputeEventListHook::LoadHookAddrs() {
    AddTarget(Game::modBaseAddr + 0x59b90);
}

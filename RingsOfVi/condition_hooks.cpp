#include "pch.h"
#include "condition_hooks.h"
#include <iostream>

static int currIndex = 0;

ConditionHooks& ConditionHooks::Instance() {
    static ConditionHooks instance;
    return instance;
}

void* ConditionHooks::GetParamStorage() {
    return (void*)&currIndex;
}

bool __cdecl ConditionHooks::HandleConditionHook(Condition* condition, RunObject* ro) {
    ConditionHooks& ahs = ConditionHooks::Instance();
    HookGroup::TargHookInfo* targetInfo = ahs.GWGetTargHookInfo();

    CCondition cCondition = CCondition(condition);
    CRunObject cRo = CRunObject(ro);

    int i;
    bool shouldContinue;
    HookGroup::CbInfo cbInfo;

    for (i = 0; i < targetInfo->callbacks.size(); i++) {
        cbInfo = targetInfo->callbacks[i];
        if (cbInfo.when == FUNC_PRE) {
            shouldContinue = cbInfo.callback(&cCondition, &cRo);
            if (!shouldContinue) return shouldContinue;
        }
    }

    shouldContinue = targetInfo->trueFunc(condition, ro);
    if (!shouldContinue) return shouldContinue;

    for (i = 0; i < targetInfo->callbacks.size(); i++) {
        cbInfo = targetInfo->callbacks[i];
        if (cbInfo.when == FUNC_POST) {
            shouldContinue = cbInfo.callback(&cCondition, &cRo);
            if (!shouldContinue) return shouldContinue;
        }
    }

    return shouldContinue;
}

OrigConditionFunc ConditionHooks::GetGateway() {
    return HandleConditionHook;
}

void ConditionHooks::LoadHookAddrs() {
    // TODO: Implement
}


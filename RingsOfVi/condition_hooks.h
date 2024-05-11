#pragma once
#include <string>
#include <vector>
#include "wrapped_types.h"
#include "hookgroup.h"

typedef std::string ConditionTarget;
typedef bool(__cdecl* ConditionCallback)(CCondition*, CRunObject*);
typedef bool(__cdecl* OrigConditionFunc)(Condition*, RunObject*);

class ConditionHooks : public HookGroup<ConditionCallback, ConditionTarget, OrigConditionFunc> {
protected:
    OrigConditionFunc GetGateway() override;
    void LoadHookAddrs() override;
    void* GetParamStorage() override;

public:
    static ConditionHooks& Instance();
    static bool __cdecl HandleConditionHook(Condition* condition, RunObject* ro);
};

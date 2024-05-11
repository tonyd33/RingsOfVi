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
	 void InitHookAddrs() override;

public:

	static ConditionHooks& Instance();
};

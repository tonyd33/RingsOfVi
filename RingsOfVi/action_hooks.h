#pragma once
#include <string>
#include <vector>
#include "wrapped_types.h"
#include "hookgroup.h"

typedef std::string ActionTarget;
typedef bool(__cdecl* ActionCallback)(CAction*);
typedef bool(__cdecl* OrigActionFunc)(Action*);

typedef TargHookInfo<ActionCallback, ActionTarget, OrigActionFunc> ActionTargetInfo;
typedef CbInfo<ActionCallback, ActionTarget> ActionCallbackInfo;

class ActionHooks : public HookGroup<ActionCallback, ActionTarget, OrigActionFunc> {
private:
	void LoadExtsTable();
protected:
	static int currIndex;
	 void InitHookAddrs() override;
public:
	static ActionHooks& Instance();
	static void __cdecl HandleActionHook(Action* action);
};

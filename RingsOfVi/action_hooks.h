#pragma once
#include <string>
#include <vector>
#include "wrapped_types.h"
#include "hookgroup.h"

typedef std::string ActionTarget;
typedef bool(__cdecl* ActionCallback)(CAction*);
typedef void(__cdecl* OrigActionFunc)(Action*);

class ActionHooks : public HookGroup<ActionCallback, ActionTarget, OrigActionFunc> {
private:
    void LoadExtsTable();
protected:
    OrigActionFunc GetGateway() override;
    void LoadHookAddrs() override;
    void* GetParamStorage() override;
public:
    static ActionHooks& Instance();
    static void __cdecl HandleActionHook(Action* action);
};

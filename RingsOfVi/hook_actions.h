#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <vector>
//#include "action.h"
//#include "hook.h"
//#include "hook_basehook.h"
//#include "string"
//
//namespace Hook {
//
//    namespace Actions {
//		/* return true to continue, false otherwise */
//		typedef bool(*ActionCallbackFunc)(CAction* action);
//        typedef void(__cdecl* OrigActionFunc)(Action* action);
//
//        struct ActionCallback {
//            ActionCallbackFunc hookFunc;
//            CallbackWhen when;
//            CallbackID id;
//        };
//		struct ActionHookInfo {
//			std::vector<ActionCallback*> callbacks;
//			BaseHook* hook;
//            OrigActionFunc realFunc;
//            ActionHookInfo();
//            ~ActionHookInfo();
//		};
//        /* human-friendly identifier for function targets to hook to. */
//        typedef std::string ActionTarget;
//
//        /* expose this */
//		extern std::vector<ActionTarget> targets;
//
//        HStatus Initialize();
//        HStatus Deinitialize();
//        HStatus Register(ActionCallback* hook, ActionTarget target);
//
//        HStatus Deregister(CallbackID id);
//
//        HStatus DoHooks();
//        HStatus UndoHooks();
//        HStatus ToggleHooks();
//    };
//
//
//}
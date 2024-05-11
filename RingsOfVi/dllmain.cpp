// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "hook.h"
#include "hook_basehook.h"
#include "wrapped_types.h"
#include "action_hooks.h"

bool DoSomething(CAction* action) {
    std::cout << "hooked\n";
    return true;
    //bool isViInObj = 21 <= action->action->objectInfoList && action->action->objectInfoList <= 106;

    //std::vector<Parameter*> params;
    //action->GetParams(&params);

   // for (int i = 0; i < params.size(); i++) {
   //     Parameter* param = params[i];
   //     if (param->evpCode == 22) {
			//// short size
			//// short code
			//// short comparison
			//// short objectType
			//// short num
			//Expression* expr = (Expression*)((uintptr_t)param + 6);
   //         while (expr->type != 0 || expr->num != 0) {
   //             // system
   //             //std::cout << " type " << expr->type << " num " << expr->num;
   //             //std::cout << std::endl;
   //             if (expr->type == -1) return true;
   //             if (expr->type == 2 || expr->type == -7) {
   //                 unsigned short oi = *(unsigned short*)((uintptr_t)expr + 4);
			//		unsigned short oiList = *(unsigned short*)((uintptr_t)expr + 6);
			//		unsigned short value = *(unsigned short*)((uintptr_t)expr + 8);
			//		unsigned short otherValue = *(unsigned short*)((uintptr_t)expr + 0xa);
   //                 if (expr->type == 2 && expr->num == 16) {
   //                     //std::cout << " value " << value << std::endl;
   //                     if (21 <= value && value <= 106) return true;
   //                 }
   //             }
   //             expr = (Expression*)((uintptr_t)expr + expr->size);
   //         }
   //     }
   // }
    //std::cout << std::endl;
    //return isViInObj;
}

void ModThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Attached\n";

    uintptr_t modBaseAddr = (uintptr_t)GetModuleHandle(L"Wings Of Vi.exe");
    ActionCallbackInfo cb;
    cb.callback = DoSomething;
    cb.when = FUNC_PRE;

    Hook::Initialize(modBaseAddr);
    ActionHooks actHooks = ActionHooks::Instance();
    actHooks.Initialize();
    //Hook::Actions::Initialize();



    CbID tmp;
    actHooks.Register("SetX", DoSomething, FUNC_PRE, &tmp);
    //Hook::Actions::Register(&cb, "SetX");
    //Hook::Actions::Register(&cb, "SetY");
    //Hook::Actions::Register(&cb, "SetSpeed");
    //Hook::Actions::Register(&cb, "SetMaximumSpeed");
    //Hook::Actions::Register(&cb, "SetAlterableValue");
    //Hook::Actions::Register(&cb, "AddToAlterable");
    //Hook::Actions::Register(&cb, "SubtractFromAlterable");
    //Hook::Actions::Register(&cb, "SetAcceleration");
    //Hook::Actions::Register(&cb, "SetDeceleration");
    //for (int i = 0; i < Hook::Actions::targets.size(); i++) {
    //    Hook::Actions::Register(&cb, Hook::Actions::targets[i]);
    //}

    while (1) {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        if (GetAsyncKeyState(VK_END) & 1) {
            actHooks.ToggleHook("SetX");
        }
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            std::cout << "curr index addr: 0x" << std::hex << &actHooks;
        }

        Sleep(10);
    }

    //Hook::Actions::Deinitialize();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ModThread, hModule, 0, 0);
        if (thread) CloseHandle(thread);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


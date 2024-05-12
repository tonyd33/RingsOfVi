// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "game.h"
#include "hook.h"
#include "wrapped_types.h"
#include "action_hooks.h"

bool DoSomething(CAction* action) {
    std::vector<CParameter> params = action->GetParams();

    short objectInfo = action->action->objectInfo;

    if (objectInfo == 378 || // converter
        objectInfo == 470 || // demon jumper hitbox
        objectInfo == 471 || // demon jumper sprite
        objectInfo == 501 || // eye of the wary - eye
        objectInfo == 502 || // watching eye
        false // make syntax uniform lmao
     ) return false;

    return true;

    for (int i = 0; i < params.size(); i++) {
        CParameter param = params[i];
        // expression param
        if (param.param->evpCode != 22) continue;

        CExpressionParameter exprParam = CExpressionParameter((ExpressionParameter*)&param.param->startOfBody);

        std::vector<CExpression> exprs = exprParam.GetExpressions();

        if (exprs.size() < 3) continue;
        // PLAYXLEFT
        if (exprs[0].expr->type == -1 && exprs[0].expr->num == 2) continue;
        std::cout << "oiList: " << action->action->objectInfoList;

        std::cout << " comparison " << exprParam.exprParam->comparison << " Num exprs " << exprs.size() << std::endl;
        for (int i = 0; i < exprs.size(); i++) {
            CExpression expr = exprs[i];
            std::cout << expr.PrettyName() << " ";
            // std::cout << "type " << expr.expr->type << " num " << expr.expr->num << " size " << expr.expr->size;

        }

        std::cout << std::endl;

    }
    return true;
}

void ModThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Attached\n";

    uintptr_t modBaseAddr = (uintptr_t)GetModuleHandle(L"Wings Of Vi.exe");
    //ActionCallbackInfo cb;
    //cb.callback = DoSomething;
    //cb.when = FUNC_PRE;

    Game::Initialize(modBaseAddr);
    ActionHooks& actHooks = ActionHooks::Instance();
    actHooks.PrepareHooks();
    //Hook::Actions::Initialize();



    CbID tmp;
    actHooks.Subscribe("SetX", DoSomething, FUNC_PRE, &tmp);
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
            std::cout << "Toggled\n";
        }
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            // std::cout << ActionHooks::Instance().targets.size() << std::endl;
        }

        Sleep(10);
    }

    // TODO: Deinit
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


#include "pch.h"
#include "game.h"
#include "action_hooks.h"
#include <iostream>

static int currIndex = 0;

ActionHooks& ActionHooks::Instance() {
    static ActionHooks instance;
    return instance;
}

void* ActionHooks::GetParamStorage() {
    return (void*)&currIndex;
}

void __cdecl ActionHooks::HandleActionHook(Action* action) {
    ActionHooks& ahs = ActionHooks::Instance();
    HookGroup::TargHookInfo* targetInfo = ahs.GWGetTargHookInfo();

    CAction cAction = CAction(action);

    int i;
    bool shouldContinue;
    HookGroup::CbInfo cbInfo;

    for (i = 0; i < targetInfo->callbacks.size(); i++) {
        cbInfo = targetInfo->callbacks[i];
        if (cbInfo.when == FUNC_PRE) {
            shouldContinue = cbInfo.callback(&cAction);
            if (!shouldContinue) return;
        }
    }

    targetInfo->trueFunc(action);

    for (i = 0; i < targetInfo->callbacks.size(); i++) {
        cbInfo = targetInfo->callbacks[i];
        if (cbInfo.when == FUNC_POST) {
            shouldContinue = cbInfo.callback(&cAction);
            if (!shouldContinue) return;
        }
    }
}

OrigActionFunc ActionHooks::GetGateway() {
    return HandleActionHook;
}

//ActionHooks& ActionHooks::Instance() {
//	static ActionHooks instance;
//	return instance;
//}

void ActionHooks::LoadHookAddrs() {
    LoadExtsTable();

    //for (int i = 0; i < targets.size(); i++) {
    //	ActionTarget name = targets[i];
    //	uintptr_t addr = targetAddrs[i];

    //	ActionTargetInfo* targetInfo = new ActionTargetInfo();
    //	targetInfo->hook->SetHook((uintptr_t)HandleActionHook);
    //	targetInfo->hook->SetTarget(addr);
    //	targetInfo->hook->SetExtraIn((void*)i, (void*)&ActionHooks::currIndex, false);
    //	targetInfo->hook->Initialize((uintptr_t*)&targetInfo->trueFunc);
    //	targetToInfo[name] = targetInfo;
    //}

    //std::cout << std::hex << targetToInfo["SetX"]->trueFunc << std::dec << std::endl;
    //return;
}

void ActionHooks::LoadExtsTable() {
    uintptr_t* table = (uintptr_t*)(Game::modBaseAddr + 0xb0008);
    AddTarget("SetPosition", table[1]);
    AddTarget("SetX", table[2]);
    AddTarget("SetY", table[3]);
    AddTarget("Stop", table[4]);
    AddTarget("Start", table[5]);
    AddTarget("SetSpeed", table[6]);
    AddTarget("SetMaximumSpeed", table[7]);
    AddTarget("Wrap", table[8]);
    AddTarget("Bounce", table[9]);
    AddTarget("Reverse", table[10]);
    AddTarget("NextMovement", table[11]);
    AddTarget("PreviousMovement", table[12]);
    AddTarget("SelectMovement", table[13]);
    AddTarget("LookAt", table[14]);
    AddTarget("StopAnimation", table[15]);
    AddTarget("StartAnimation", table[16]);
    AddTarget("ForceAnimation", table[17]);
    AddTarget("ForceDirection", table[18]);
    AddTarget("ForceSpeed", table[19]);
    AddTarget("RestoreAnimation", table[20]);
    AddTarget("RestoreDirection", table[21]);
    AddTarget("RestoreSpeed", table[22]);
    AddTarget("SetDirection", table[23]);
    AddTarget("Destroy", table[24]);
    AddTarget("SwapPosition", table[25]);
    AddTarget("Hide", table[26]);
    AddTarget("Show", table[27]);
    AddTarget("FlashDuring", table[28]);
    AddTarget("Shoot", table[29]);
    AddTarget("ShootToward", table[30]);
    AddTarget("SetAlterableValue", table[31]);
    AddTarget("AddToAlterable", table[32]);
    AddTarget("SubtractFromAlterable", table[33]);
    AddTarget("SpreadValue", table[34]);
    AddTarget("EnableFlag", table[35]);
    AddTarget("DisableFlag", table[36]);
    AddTarget("ToggleFlag", table[37]);
    AddTarget("SetInkEffect", table[38]);
    AddTarget("SetSemiTransparency", table[39]);
    AddTarget("ForceFrame", table[40]);
    AddTarget("RestoreFrame", table[41]);
    AddTarget("SetAcceleration", table[42]);
    AddTarget("SetDeceleration", table[43]);
    AddTarget("SetRotatingSpeed", table[44]);
    AddTarget("SetDirections", table[45]);
    AddTarget("BranchNode", table[46]);
    AddTarget("SetGravity", table[47]);
    AddTarget("GoToNode", table[48]);
    AddTarget("SetAlterableString", table[49]);
    AddTarget("SetFontName", table[50]);
    AddTarget("SetFontSize", table[51]);
    AddTarget("SetBold", table[52]);
    AddTarget("SetItalic", table[53]);
    AddTarget("SetUnderline", table[54]);
    AddTarget("SetStrikeOut", table[55]);
    AddTarget("SetTextColor", table[56]);
    AddTarget("BringToFront", table[57]);
    AddTarget("BringToBack", table[58]);
    AddTarget("MoveBehind", table[59]);
    AddTarget("MoveInFront", table[60]);
    AddTarget("MoveToLayer", table[61]);
    AddTarget("AddToDebugger", table[62]);
    AddTarget("SetEffect", table[63]);
    AddTarget("SetEffectParameter", table[64]);
    AddTarget("SetAlphaCoefficient", table[65]);
    AddTarget("SetRGBCoefficient", table[66]);
    AddTarget("SetEffectImage", table[67]);
    AddTarget("SetFriction", table[68]);
    AddTarget("SetElasticity", table[69]);
    AddTarget("ApplyImpulse", table[70]);
    AddTarget("ApplyAngularImpulse", table[71]);
    AddTarget("ApplyForce", table[72]);
    AddTarget("ApplyTorque", table[73]);
    AddTarget("SetLinearVelocity", table[74]);
    AddTarget("SetAngularVelocity", table[75]);
    AddTarget("Foreach", table[76]);
    AddTarget("ForeachTwoObjects", table[77]);
    AddTarget("StopForce", table[78]);
    AddTarget("StopTorque", table[79]);
    AddTarget("SetDensity", table[80]);
    AddTarget("SetGravityScale", table[81]);
}

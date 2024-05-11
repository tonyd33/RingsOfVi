#include "pch.h"
#include "hook.h"
#include "action_hooks.h"
#include <iostream>

int ActionHooks::currIndex = 0;

/* this is what first intercepts a hooked function. it then wraps the
   action with our CAction and then uses currTarget, which is set from
   the hook mechanism to execute the list of callbacks. it has to be */
void __cdecl ActionHooks::HandleActionHook(Action* action) {
	ActionHooks ahs = ActionHooks::Instance();

	std::cout << "0x" << std::hex << action << " ahs addr " << &ahs << std::endl;

	//ActionHooks ahs = ActionHooks::Instance();

	//ActionTarget target = ahs.targets[ahs.currIndex];
	//ActionTargetInfo* targetInfo = ahs.targetToInfo[target];

	//CAction cAction = CAction(action);

	//int i;
	//bool shouldContinue;

	//ActionCallbackInfo cbInfo;

	//for (i = 0; i < targetInfo->callbacks.size(); i++) {
	//	cbInfo = targetInfo->callbacks[i];
	//	if (cbInfo.when == HOOK_PRE) {
	//		shouldContinue = cbInfo.callback(&cAction);
	//		if (!shouldContinue) return;
	//	}
	//}

	//targetInfo->trueFunc(action);

	//for (i = 0; i < targetInfo->callbacks.size(); i++) {
	//	cbInfo = targetInfo->callbacks[i];
	//	if (cbInfo.when == HOOK_POST) {
	//		shouldContinue = cbInfo.callback(&cAction);
	//		if (!shouldContinue) return;
	//	}
	//}
}

//ActionHooks& ActionHooks::Instance() {
//	static ActionHooks instance;
//	return instance;
//}

void ActionHooks::InitHookAddrs() {
	//LoadPlayersTable();
	//LoadActivesTable();
	LoadExtsTable();

	for (int i = 0; i < targets.size(); i++) {
		ActionTarget name = targets[i];
		uintptr_t addr = targetAddrs[i];

		ActionTargetInfo* targetInfo = new ActionTargetInfo();
		targetInfo->hook->SetHook((uintptr_t)HandleActionHook);
		targetInfo->hook->SetTarget(addr);
		targetInfo->hook->SetExtraIn((void*)i, (void*)&ActionHooks::currIndex, false);
		targetInfo->hook->Initialize((uintptr_t*)&targetInfo->trueFunc);
		targetToInfo[name] = targetInfo;
	}

	std::cout << std::hex << targetToInfo["SetX"]->trueFunc << std::dec << std::endl;
	return;
}

void ActionHooks::LoadExtsTable() {
	uintptr_t* table = (uintptr_t*)(Hook::modBaseAddr + 0xb0008);
	targets.push_back("SetPosition"); targetAddrs.push_back(table[1]);
	targets.push_back("SetX"); targetAddrs.push_back(table[2]);
	targets.push_back("SetY"); targetAddrs.push_back(table[3]);
	targets.push_back("Stop"); targetAddrs.push_back(table[4]);
	targets.push_back("Start"); targetAddrs.push_back(table[5]);
	targets.push_back("SetSpeed"); targetAddrs.push_back(table[6]);
	targets.push_back("SetMaximumSpeed"); targetAddrs.push_back(table[7]);
	targets.push_back("Wrap"); targetAddrs.push_back(table[8]);
	targets.push_back("Bounce"); targetAddrs.push_back(table[9]);
	targets.push_back("Reverse"); targetAddrs.push_back(table[10]);
	targets.push_back("NextMovement"); targetAddrs.push_back(table[11]);
	targets.push_back("PreviousMovement"); targetAddrs.push_back(table[12]);
	targets.push_back("SelectMovement"); targetAddrs.push_back(table[13]);
	targets.push_back("LookAt"); targetAddrs.push_back(table[14]);
	targets.push_back("StopAnimation"); targetAddrs.push_back(table[15]);
	targets.push_back("StartAnimation"); targetAddrs.push_back(table[16]);
	targets.push_back("ForceAnimation"); targetAddrs.push_back(table[17]);
	targets.push_back("ForceDirection"); targetAddrs.push_back(table[18]);
	targets.push_back("ForceSpeed"); targetAddrs.push_back(table[19]);
	targets.push_back("RestoreAnimation"); targetAddrs.push_back(table[20]);
	targets.push_back("RestoreDirection"); targetAddrs.push_back(table[21]);
	targets.push_back("RestoreSpeed"); targetAddrs.push_back(table[22]);
	targets.push_back("SetDirection"); targetAddrs.push_back(table[23]);
	targets.push_back("Destroy"); targetAddrs.push_back(table[24]);
	targets.push_back("SwapPosition"); targetAddrs.push_back(table[25]);
	targets.push_back("Hide"); targetAddrs.push_back(table[26]);
	targets.push_back("Show"); targetAddrs.push_back(table[27]);
	targets.push_back("FlashDuring"); targetAddrs.push_back(table[28]);
	targets.push_back("Shoot"); targetAddrs.push_back(table[29]);
	targets.push_back("ShootToward"); targetAddrs.push_back(table[30]);
	targets.push_back("SetAlterableValue"); targetAddrs.push_back(table[31]);
	targets.push_back("AddToAlterable"); targetAddrs.push_back(table[32]);
	targets.push_back("SubtractFromAlterable"); targetAddrs.push_back(table[33]);
	targets.push_back("SpreadValue"); targetAddrs.push_back(table[34]);
	targets.push_back("EnableFlag"); targetAddrs.push_back(table[35]);
	targets.push_back("DisableFlag"); targetAddrs.push_back(table[36]);
	targets.push_back("ToggleFlag"); targetAddrs.push_back(table[37]);
	targets.push_back("SetInkEffect"); targetAddrs.push_back(table[38]);
	targets.push_back("SetSemiTransparency"); targetAddrs.push_back(table[39]);
	targets.push_back("ForceFrame"); targetAddrs.push_back(table[40]);
	targets.push_back("RestoreFrame"); targetAddrs.push_back(table[41]);
	targets.push_back("SetAcceleration"); targetAddrs.push_back(table[42]);
	targets.push_back("SetDeceleration"); targetAddrs.push_back(table[43]);
	targets.push_back("SetRotatingSpeed"); targetAddrs.push_back(table[44]);
	targets.push_back("SetDirections"); targetAddrs.push_back(table[45]);
	targets.push_back("BranchNode"); targetAddrs.push_back(table[46]);
	targets.push_back("SetGravity"); targetAddrs.push_back(table[47]);
	targets.push_back("GoToNode"); targetAddrs.push_back(table[48]);
	targets.push_back("SetAlterableString"); targetAddrs.push_back(table[49]);
	targets.push_back("SetFontName"); targetAddrs.push_back(table[50]);
	targets.push_back("SetFontSize"); targetAddrs.push_back(table[51]);
	targets.push_back("SetBold"); targetAddrs.push_back(table[52]);
	targets.push_back("SetItalic"); targetAddrs.push_back(table[53]);
	targets.push_back("SetUnderline"); targetAddrs.push_back(table[54]);
	targets.push_back("SetStrikeOut"); targetAddrs.push_back(table[55]);
	targets.push_back("SetTextColor"); targetAddrs.push_back(table[56]);
	targets.push_back("BringToFront"); targetAddrs.push_back(table[57]);
	targets.push_back("BringToBack"); targetAddrs.push_back(table[58]);
	targets.push_back("MoveBehind"); targetAddrs.push_back(table[59]);
	targets.push_back("MoveInFront"); targetAddrs.push_back(table[60]);
	targets.push_back("MoveToLayer"); targetAddrs.push_back(table[61]);
	targets.push_back("AddToDebugger"); targetAddrs.push_back(table[62]);
	targets.push_back("SetEffect"); targetAddrs.push_back(table[63]);
	targets.push_back("SetEffectParameter"); targetAddrs.push_back(table[64]);
	targets.push_back("SetAlphaCoefficient"); targetAddrs.push_back(table[65]);
	targets.push_back("SetRGBCoefficient"); targetAddrs.push_back(table[66]);
	targets.push_back("SetEffectImage"); targetAddrs.push_back(table[67]);
	targets.push_back("SetFriction"); targetAddrs.push_back(table[68]);
	targets.push_back("SetElasticity"); targetAddrs.push_back(table[69]);
	targets.push_back("ApplyImpulse"); targetAddrs.push_back(table[70]);
	targets.push_back("ApplyAngularImpulse"); targetAddrs.push_back(table[71]);
	targets.push_back("ApplyForce"); targetAddrs.push_back(table[72]);
	targets.push_back("ApplyTorque"); targetAddrs.push_back(table[73]);
	targets.push_back("SetLinearVelocity"); targetAddrs.push_back(table[74]);
	targets.push_back("SetAngularVelocity"); targetAddrs.push_back(table[75]);
	targets.push_back("Foreach"); targetAddrs.push_back(table[76]);
	targets.push_back("ForeachTwoObjects"); targetAddrs.push_back(table[77]);
	targets.push_back("StopForce"); targetAddrs.push_back(table[78]);
	targets.push_back("StopTorque"); targetAddrs.push_back(table[79]);
	targets.push_back("SetDensity"); targetAddrs.push_back(table[80]);
	targets.push_back("SetGravityScale"); targetAddrs.push_back(table[81]);
}

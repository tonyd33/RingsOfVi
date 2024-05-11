#include "pch.h"
#include <iostream>
//#include "hook_actions.h"
//
//namespace Hook {
//	namespace Actions {
//		/* begin ActionHookInfo */
//		ActionHookInfo::ActionHookInfo() {
//			this->hook = new BaseHook();
//			this->realFunc = NULL;
//		}
//		ActionHookInfo::~ActionHookInfo() {
//			delete this->hook;
//		}
//		/* end ActionHookInfo */
//
//		/* begin regular Action hook stuff */
//        std::map<ActionTarget, ActionHookInfo*> targetToInfo;
//
//        /* translate human-friendly identifiers to actual addresses. */
//		std::vector<ActionTarget> targets;
//		std::vector<uintptr_t> targetAddrs;
//
//		CallbackID currID;
//
//        /* when we hook onto functions, the target will be stored in here so
//           that HandleActionHook knows which list of callbacks to run. */
//		int currIndex;
//
//		bool areAllHooked = false;
//
//		void InitHookAddrs();
//		void LoadPlayersTable();
//		void LoadActivesTable();
//		void LoadExtsTable();
//
//		/* this is what first intercepts a hooked function. it then wraps the
//		   action with our CAction and then uses currTarget, which is set from
//		   the hook mechanism to execute the list of callbacks. it has to be */
//		void __cdecl HandleActionHook(Action* action) {
//			ActionTarget target = targets[currIndex];
//			ActionHookInfo* actInfo = targetToInfo[target];
//
//			CAction cAction = CAction(action);
//
//			int i;
//			bool shouldContinue;
//
//			for (i = 0; i < actInfo->callbacks.size(); i++) {
//				ActionCallback* callback = actInfo->callbacks[i];
//				if (callback->when == HOOK_PRE) {
//					shouldContinue = callback->hookFunc(&cAction);
//					if (!shouldContinue) return;
//				}
//			}
//
//			actInfo->realFunc(action);
//
//			for (i = 0; i < actInfo->callbacks.size(); i++) {
//				ActionCallback* callback = actInfo->callbacks[i];
//				if (callback->when == HOOK_POST) {
//					shouldContinue = callback->hookFunc(&cAction);
//					if (!shouldContinue) return;
//				}
//			}
//		}
//
//		HStatus Initialize() {
//			InitHookAddrs();
//			return H_OK;
//		}
//
//		HStatus Deinitialize() {
//			HStatus ret;
//			ret = UndoHooks();
//			if (ret != H_OK) return ret;
//
//			// TODO: also need to free all the callbacks i think
//			for (const auto& ptr : targetToInfo) {
//				delete ptr.second;
//			}
//
//			return H_OK;
//		}
//
//		HStatus Register(ActionCallback* hook, ActionTarget target) {
//			// TODO: check index lol
//			targetToInfo[target]->callbacks.push_back(hook);
//			hook->id = currID++;
//			return H_OK;
//		}
//
//		HStatus Deregister(CallbackID id) {
//			for (const auto& ptr : targetToInfo) {
//				std::vector<ActionCallback*> callbacks = ptr.second->callbacks;
//				for (int i = 0; i < callbacks.size(); i++) {
//					if (callbacks[i]->id == id) {
//						callbacks.erase(callbacks.begin() + i);
//						return H_OK;
//					}
//				}
//			}
//			return H_ERR_NOTFOUND;
//		}
//
//		HStatus DoHooks() {
//			for (const auto& ptr : targetToInfo) {
//				// TODO: Error
//				ptr.second->hook->DoHook();
//			}
//			areAllHooked = true;
//			return H_OK;
//		}
//
//		HStatus UndoHooks() {
//			for (const auto& ptr : targetToInfo) {
//				// TODO: error
//				ptr.second->hook->UndoHook();
//			}
//			areAllHooked = false;
//			return H_OK;
//		}
//
//		HStatus ToggleHooks() {
//			HStatus ret;
//			if (areAllHooked) {
//				std::cout << "Undoing hooks\n";
//				ret = UndoHooks();
//				areAllHooked = false;
//			}
//			else {
//				std::cout << "Doing hooks\n";
//				ret = DoHooks();
//				areAllHooked = true;
//			}
//
//			return ret;
//		}
//
//
//		void InitHookAddrs() {
//			LoadPlayersTable();
//			LoadActivesTable();
//			LoadExtsTable();
//
//			for (int i = 0; i < targets.size(); i++) {
//				ActionTarget name = targets[i];
//				uintptr_t addr = targetAddrs[i];
//				ActionHookInfo* act = new ActionHookInfo();
//				act->hook->SetHook((uintptr_t)HandleActionHook);
//				act->hook->SetTarget(addr);
//				act->hook->SetExtraIn((uintptr_t*)i, (uintptr_t*)&currIndex, false);
//				act->hook->Initialize((uintptr_t*)(void*)&act->realFunc);
//				targetToInfo[name] = act;
//			}
//		}
//
//		void LoadPlayersTable() {
//			//uintptr_t* table = (uintptr_t*)(modBaseAddr + 0xaf994);
//			//targetToAddr["SetScore"] = table[0];
//			//targetToAddr["SetLives"] = table[1];
//			//targetToAddr["IgnoreControls"] = table[2];
//			//targetToAddr["RestoreControls"] = table[3];
//			//targetToAddr["AddScore"] = table[4];
//			//targetToAddr["AddLives"] = table[5];
//			//targetToAddr["SubtractScore"] = table[6];
//			//targetToAddr["SubtractLives"] = table[7];
//			//targetToAddr["ChangeControlType"] = table[8];
//			//targetToAddr["ChangeInputKey"] = table[9];
//			//targetToAddr["SetPlayerName"] = table[10];
//		}
//
//		void LoadActivesTable() {
//			//uintptr_t* table = (uintptr_t*)(modBaseAddr + 0xaf784);
//			//targetToAddr["PasteActive"] = table[80];
//			//targetToAddr["BringToFront"] = table[81];
//			//targetToAddr["BringToBack"] = table[82];
//			//targetToAddr["AddBackdrop"] = table[83];
//			//targetToAddr["ReplaceColor"] = table[84];
//			//targetToAddr["SetScale"] = table[85];
//			//targetToAddr["SetXScale"] = table[86];
//			//targetToAddr["SetYScale"] = table[87];
//			//targetToAddr["SetAngle"] = table[88];
//			//targetToAddr["LoadActiveFrame"] = table[89];
//		}
//
//		void LoadExtsTable() {
//			uintptr_t* table = (uintptr_t*)(modBaseAddr + 0xb0008);
//			targets.push_back("SetPosition"); targetAddrs.push_back(table[1]);
//			targets.push_back("SetX"); targetAddrs.push_back(table[2]);
//			targets.push_back("SetY"); targetAddrs.push_back(table[3]);
//			targets.push_back("Stop"); targetAddrs.push_back(table[4]);
//			targets.push_back("Start"); targetAddrs.push_back(table[5]);
//			targets.push_back("SetSpeed"); targetAddrs.push_back(table[6]);
//			targets.push_back("SetMaximumSpeed"); targetAddrs.push_back(table[7]);
//			targets.push_back("Wrap"); targetAddrs.push_back(table[8]);
//			targets.push_back("Bounce"); targetAddrs.push_back(table[9]);
//			targets.push_back("Reverse"); targetAddrs.push_back(table[10]);
//			targets.push_back("NextMovement"); targetAddrs.push_back(table[11]);
//			targets.push_back("PreviousMovement"); targetAddrs.push_back(table[12]);
//			targets.push_back("SelectMovement"); targetAddrs.push_back(table[13]);
//			targets.push_back("LookAt"); targetAddrs.push_back(table[14]);
//			targets.push_back("StopAnimation"); targetAddrs.push_back(table[15]);
//			targets.push_back("StartAnimation"); targetAddrs.push_back(table[16]);
//			targets.push_back("ForceAnimation"); targetAddrs.push_back(table[17]);
//			targets.push_back("ForceDirection"); targetAddrs.push_back(table[18]);
//			targets.push_back("ForceSpeed"); targetAddrs.push_back(table[19]);
//			targets.push_back("RestoreAnimation"); targetAddrs.push_back(table[20]);
//			targets.push_back("RestoreDirection"); targetAddrs.push_back(table[21]);
//			targets.push_back("RestoreSpeed"); targetAddrs.push_back(table[22]);
//			targets.push_back("SetDirection"); targetAddrs.push_back(table[23]);
//			targets.push_back("Destroy"); targetAddrs.push_back(table[24]);
//			targets.push_back("SwapPosition"); targetAddrs.push_back(table[25]);
//			targets.push_back("Hide"); targetAddrs.push_back(table[26]);
//			targets.push_back("Show"); targetAddrs.push_back(table[27]);
//			targets.push_back("FlashDuring"); targetAddrs.push_back(table[28]);
//			targets.push_back("Shoot"); targetAddrs.push_back(table[29]);
//			targets.push_back("ShootToward"); targetAddrs.push_back(table[30]);
//			targets.push_back("SetAlterableValue"); targetAddrs.push_back(table[31]);
//			targets.push_back("AddToAlterable"); targetAddrs.push_back(table[32]);
//			targets.push_back("SubtractFromAlterable"); targetAddrs.push_back(table[33]);
//			targets.push_back("SpreadValue"); targetAddrs.push_back(table[34]);
//			targets.push_back("EnableFlag"); targetAddrs.push_back(table[35]);
//			targets.push_back("DisableFlag"); targetAddrs.push_back(table[36]);
//			targets.push_back("ToggleFlag"); targetAddrs.push_back(table[37]);
//			targets.push_back("SetInkEffect"); targetAddrs.push_back(table[38]);
//			targets.push_back("SetSemiTransparency"); targetAddrs.push_back(table[39]);
//			targets.push_back("ForceFrame"); targetAddrs.push_back(table[40]);
//			targets.push_back("RestoreFrame"); targetAddrs.push_back(table[41]);
//			targets.push_back("SetAcceleration"); targetAddrs.push_back(table[42]);
//			targets.push_back("SetDeceleration"); targetAddrs.push_back(table[43]);
//			targets.push_back("SetRotatingSpeed"); targetAddrs.push_back(table[44]);
//			targets.push_back("SetDirections"); targetAddrs.push_back(table[45]);
//			targets.push_back("BranchNode"); targetAddrs.push_back(table[46]);
//			targets.push_back("SetGravity"); targetAddrs.push_back(table[47]);
//			targets.push_back("GoToNode"); targetAddrs.push_back(table[48]);
//			targets.push_back("SetAlterableString"); targetAddrs.push_back(table[49]);
//			targets.push_back("SetFontName"); targetAddrs.push_back(table[50]);
//			targets.push_back("SetFontSize"); targetAddrs.push_back(table[51]);
//			targets.push_back("SetBold"); targetAddrs.push_back(table[52]);
//			targets.push_back("SetItalic"); targetAddrs.push_back(table[53]);
//			targets.push_back("SetUnderline"); targetAddrs.push_back(table[54]);
//			targets.push_back("SetStrikeOut"); targetAddrs.push_back(table[55]);
//			targets.push_back("SetTextColor"); targetAddrs.push_back(table[56]);
//			targets.push_back("BringToFront"); targetAddrs.push_back(table[57]);
//			targets.push_back("BringToBack"); targetAddrs.push_back(table[58]);
//			targets.push_back("MoveBehind"); targetAddrs.push_back(table[59]);
//			targets.push_back("MoveInFront"); targetAddrs.push_back(table[60]);
//			targets.push_back("MoveToLayer"); targetAddrs.push_back(table[61]);
//			targets.push_back("AddToDebugger"); targetAddrs.push_back(table[62]);
//			targets.push_back("SetEffect"); targetAddrs.push_back(table[63]);
//			targets.push_back("SetEffectParameter"); targetAddrs.push_back(table[64]);
//			targets.push_back("SetAlphaCoefficient"); targetAddrs.push_back(table[65]);
//			targets.push_back("SetRGBCoefficient"); targetAddrs.push_back(table[66]);
//			targets.push_back("SetEffectImage"); targetAddrs.push_back(table[67]);
//			targets.push_back("SetFriction"); targetAddrs.push_back(table[68]);
//			targets.push_back("SetElasticity"); targetAddrs.push_back(table[69]);
//			targets.push_back("ApplyImpulse"); targetAddrs.push_back(table[70]);
//			targets.push_back("ApplyAngularImpulse"); targetAddrs.push_back(table[71]);
//			targets.push_back("ApplyForce"); targetAddrs.push_back(table[72]);
//			targets.push_back("ApplyTorque"); targetAddrs.push_back(table[73]);
//			targets.push_back("SetLinearVelocity"); targetAddrs.push_back(table[74]);
//			targets.push_back("SetAngularVelocity"); targetAddrs.push_back(table[75]);
//			targets.push_back("Foreach"); targetAddrs.push_back(table[76]);
//			targets.push_back("ForeachTwoObjects"); targetAddrs.push_back(table[77]);
//			targets.push_back("StopForce"); targetAddrs.push_back(table[78]);
//			targets.push_back("StopTorque"); targetAddrs.push_back(table[79]);
//			targets.push_back("SetDensity"); targetAddrs.push_back(table[80]);
//			targets.push_back("SetGravityScale"); targetAddrs.push_back(table[81]);
//		}
//		/* end regular Action stuff */
//
//	}
//}
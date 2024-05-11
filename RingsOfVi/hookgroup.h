#pragma once
#include <string>
#include <vector>
#include <map>
#include "hook.h"
#include "hook_basehook.h"

enum HStatus {
	H_OK,
	H_ERR_UNKNOWN,
	H_ERR_NOTFOUND,
};

/* should the callback be executed before or after the original function
   executes? */
enum CbWhen {
	FUNC_PRE,
	FUNC_POST
};
typedef unsigned int CbID;

template <typename CbT, typename TargIDT>
struct CbInfo {
	CbT callback;
	CbWhen when;
	TargIDT target;
	CbID id;
};

template <typename CbT, typename TargIDT, typename TargFuncT>
struct TargHookInfo {
	/* the list of callbacks that should be executed on a target */
	std::vector<CbInfo<CbT, TargIDT>> callbacks;
	/* ptr to what we used to create the hook. */
	Hook::BaseHook* hook;
	TargFuncT trueFunc;

	TargHookInfo() : hook(new Hook::BaseHook()) {}
	~TargHookInfo() { delete hook; }
};


template <typename CbT, typename TargIDT, typename TargFuncT>
class HookGroup {
protected:
	CbID nextID;
	/* map target ids to  */
	std::map<TargIDT, TargHookInfo<CbT, TargIDT, TargFuncT>*> targetToInfo;

	std::vector<TargIDT> targets;
	std::vector<uintptr_t> targetAddrs;

	bool areAllHooked;

	virtual void InitHookAddrs() = 0;

public:
	HStatus Initialize() {
		InitHookAddrs();
		return H_OK;
	}
	HStatus Register(
		TargIDT target,
		CbT callback,
		CbWhen when,
		CbID* out
	) {
		CbInfo<CbT, TargIDT> callbackInfo;
		callbackInfo.callback = callback;
		callbackInfo.when = when;
		callbackInfo.id = nextID++;
		*out = callbackInfo.id;
		callbackInfo.target = target;
		targetToInfo[target]->callbacks.push_back(callbackInfo);
		return H_OK;
	}

	HStatus Deregister(CbID id) {
		for (auto& ptr : targetToInfo) {
			std::vector<CbInfo<CbT, TargIDT>> callbacks = ptr.second->callbacks;
			for (int i = 0; i < callbacks.size(); i++) {
				if (callbacks[i]->id == id) {
					callbacks.erase(callbacks.begin() + i);
					return H_OK;
				}
			}
		}
		return H_ERR_NOTFOUND;
	}
	void Deinitialize() {
		UndoAllHooks();

		for (const auto& ptr : targetToInfo) {
			delete ptr.second;
		}
	}

	std::vector<TargIDT> ListTargets() {
		return targets;
	}

	HStatus DoAllHooks() {
		for (const auto& ptr : targetToInfo) {
			// TODO: Error
			ptr.second.hook->DoHook();
		}
		areAllHooked = true;
		return H_OK;
	}
	HStatus UndoAllHooks() {
		for (const auto& ptr : targetToInfo) {
			// TODO: error
			ptr.second.hook->UndoHook();
		}
		areAllHooked = false;
		return H_OK;
	}
	HStatus DoHook(TargIDT target) {
		// TODO: Error
		targetToInfo[target]->hook->DoHook();
		return H_OK;
	}
	HStatus UndoHook(TargIDT target) {
		// TODO: Error
		targetToInfo[target]->hook->DoHook();
		return H_OK;
	}

	HStatus ToggleHook(TargIDT target) {
		if (targetToInfo[target]->hook->hooked) {
			targetToInfo[target]->hook->UndoHook();
		} else {
			targetToInfo[target]->hook->DoHook();
		}
		// TODO: Error
		return H_OK;
	}
};


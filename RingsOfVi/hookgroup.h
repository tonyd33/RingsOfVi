#pragma once
#include <string>
#include <vector>
#include <map>
#include "hook.h"

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


/* 
    an abstract class for a collection of hooks with a fixed target function
    signature. we intend to use this by deriving a class for each group and
    having a singleton class.

    when we hook onto each of the targets in a group, each will jump to the
    _same_ "gateway" function that's implemented in a derived class. to identify
    from which function it jumped from, we set set a variable that allows for
    the gateway to index into the targets array.
    we don't inject a parameter into the function call because it's _really_
    hard to do this generally and reliably.

    to implement this interface, derived classes must:
    1. implement a gateway function
    2. implement the virtual functions
      a. LoadHookAddrs should find all the addresses it needs to hook onto and
         call AddTarget
      b. GetGateway should just return your gateway function.
      c. GetParamStorage just needs to return a pointer that's accessible
         globally


     to use this interface:
     1. call PrepareHooks()
     2. call Subscribe() on your callbacks
     3. call EnableHook()
 */
template <typename CbT, typename TargIDT, typename TargFuncT>
class HookGroup {
    /* begin declarations */
protected:
    struct TargHookInfo;
    struct CbInfo;

    /* child class implements this and calls AddTarget for each of its 
       targets */
    virtual void LoadHookAddrs() = 0;
    virtual TargFuncT GetGateway() = 0;
    virtual void* GetParamStorage() = 0;


private:
    CbID nextID;
    std::map<TargIDT, TargHookInfo*> targetToInfo;

    std::vector<TargIDT> targets;
    std::vector<uintptr_t> targetAddrs;
    /* end declarations */

    /* begin implementations */
protected:
    struct CbInfo {
        CbT callback;
        CbWhen when;
        TargIDT target;
        CbID id;
    };

    struct TargHookInfo {
        /* the list of callbacks that should be executed on a target */
        std::vector<CbInfo> callbacks;
        /* ptr to what we used to create the hook. */
        Memory::Hook* hook;
        TargFuncT trueFunc;

        TargHookInfo() : hook(new Memory::Hook()) {}
        ~TargHookInfo() { delete hook; }
    };

    TargIDT GWGetTarget() {
        void* storage = GetParamStorage();
        int index = *(int*)storage;

        return targets[index];
    }

    TargHookInfo* GWGetTargHookInfo() {
        TargIDT target = GWGetTarget();
        return targetToInfo[target];
    }

    /* child classes will use this to add a target. should be used in the
       */
    void AddTarget(TargIDT target, uintptr_t addr) {
        targets.push_back(target);
        targetAddrs.push_back(addr);
    }

public:
    void PrepareHooks() {
        LoadHookAddrs();

        TargFuncT gateway = GetGateway();
        void* storage = GetParamStorage();

        for (int i = 0; i < targets.size(); i++) {
            TargIDT name = targets[i];
            uintptr_t addr = targetAddrs[i];

            TargHookInfo* targetInfo = new TargHookInfo();
            targetInfo->hook->SetHook((uintptr_t)gateway);
            targetInfo->hook->SetTarget(addr);
            targetInfo->hook->SetExtraIn((void*)i, storage, false);
            targetInfo->hook->Initialize((uintptr_t*)&targetInfo->trueFunc);
            targetToInfo[name] = targetInfo;
        }
        return;
    }

    HStatus Subscribe(
        TargIDT target,
        CbT callback,
        CbWhen when,
        CbID* out
    ) {
        CbInfo callbackInfo;
        callbackInfo.callback = callback;
        callbackInfo.when = when;
        callbackInfo.id = nextID++;
        *out = callbackInfo.id;
        callbackInfo.target = target;
        targetToInfo[target]->callbacks.push_back(callbackInfo);
        return H_OK;
    }

    HStatus Unsubscribe(CbID id) {
        for (auto& ptr : targetToInfo) {
            std::vector<CbInfo> callbacks = ptr.second->callbacks;
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
        for (const auto& ptr : targetToInfo) {
            DisableHook(ptr.first);
            delete ptr.second;
        }
    }

    std::vector<TargIDT> ListTargets() {
        return targets;
    }
    HStatus EnableHook(TargIDT target) {
        // TODO: Error
        targetToInfo[target]->hook->Enable();
        return H_OK;
    }

    HStatus DisableHook(TargIDT target) {
        // TODO: Error
        targetToInfo[target]->hook->Disable();
        return H_OK;
    }

    HStatus ToggleHook(TargIDT target) {
        if (targetToInfo[target]->hook->hooked) {
            targetToInfo[target]->hook->Disable();
        } else {
            targetToInfo[target]->hook->Enable();
        }
        // TODO: Error
        return H_OK;
    }
    /* end implementations */
};


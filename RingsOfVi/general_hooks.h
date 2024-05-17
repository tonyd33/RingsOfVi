#pragma once
#include <string>
#include <vector>
#include "wrapped_types.h"
#include "hookgroup.h"

typedef void(*ComputeEventListCallback)(void*, void*);
typedef void(__fastcall* OrigComputeEventListFunc)(void*, void*);

class ComputeEventListHook : public SingleHook<ComputeEventListCallback, OrigComputeEventListFunc> {
protected:
    OrigComputeEventListFunc GetGateway() override;
    void LoadHookAddrs() override;
    void* GetParamStorage() override;
public:
    static ComputeEventListHook& Instance();
    static void __fastcall HandleComputeEventListHook(void*, void*);
};

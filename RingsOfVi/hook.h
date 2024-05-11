#pragma once
#include <Windows.h>

namespace Hook {
    typedef uintptr_t GenericHookFunc;
    typedef unsigned int CallbackID;
    enum HStatus {
        H_OK,
        H_ERR_UNKNOWN,
        H_ERR_NOTFOUND,
    };

    enum CallbackWhen {
        HOOK_PRE,
        HOOK_POST
    };

    extern uintptr_t modBaseAddr;

    /* this function must be called before anything in the Hook namespace can be used. */
    void Initialize(uintptr_t modBaseAddr);
}
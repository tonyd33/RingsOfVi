#pragma once
#include <Windows.h>

namespace Game {
    extern uintptr_t modBaseAddr;

    /* this function must be called before anything in the Hook namespace can be used. */
    void Initialize(uintptr_t modBaseAddr);
}

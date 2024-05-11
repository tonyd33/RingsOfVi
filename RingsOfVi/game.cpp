#include "pch.h"
#include "game.h"

namespace Game {
    uintptr_t Game::modBaseAddr = NULL;

    void Initialize(uintptr_t modBaseAddr) {
        Game::modBaseAddr = modBaseAddr;
    }
}
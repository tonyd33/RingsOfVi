#include "pch.h"
#include "hook.h"

namespace Hook {
	uintptr_t Hook::modBaseAddr = NULL;

	void Initialize(uintptr_t modBaseAddr) {
		Hook::modBaseAddr = modBaseAddr;
		// TODO: check struct sizes
	}
};
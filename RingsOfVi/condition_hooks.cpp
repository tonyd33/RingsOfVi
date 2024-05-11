#include "pch.h"
#include "condition_hooks.h"

void ConditionHooks::InitHookAddrs() {
	return;
}

ConditionHooks& ConditionHooks::Instance() {
	static ConditionHooks instance;
	return instance;
}


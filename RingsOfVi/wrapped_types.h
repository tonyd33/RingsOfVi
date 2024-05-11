#pragma once
#include <string>
#include <vector>
#include "types.h"

class CAction;
class CCondition;
class CParameter;
class CRunObject;

class CAction {
public:
	Action* action;

	CAction(Action* action);
	std::vector<CParameter> GetParams();
};

class CCondition {
public:
	Condition* condition;

	CCondition(Condition* condition);
	std::vector<CParameter> GetParams();
};

class CParameter {
public:
	Parameter* param;

	CParameter(Parameter* param);
	CParameter Next();
	std::string Name();
};


class CRunObject {
public:
	RunObject* ro;

	CRunObject(RunObject* ro);
};

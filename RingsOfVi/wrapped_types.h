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

	CAction(Action*);
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

	CParameter(Parameter*);
	CParameter Next();
	std::string Name();
};


class CRunObject {
public:
	RunObject* ro;

	CRunObject(RunObject* ro);
};

class CExpression {
public:
	Expression* expr;
	CExpression(Expression*);

	CExpression Next();
	bool IsEnd();
	std::string Name();
	std::string PrettyName();
};

class CExpressionParameter {
public:
	ExpressionParameter* exprParam;
	CExpressionParameter(ExpressionParameter*);

	std::vector<CExpression> GetExpressions();
};


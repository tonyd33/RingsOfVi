#include "pch.h"
#include <iostream>
#include "wrapped_types.h"

CAction::CAction(Action* action) {
    this->action = action;
}

std::vector<CParameter> CAction::GetParams() {
    std::vector<CParameter> params;
    Parameter* curr = (Parameter*)((uintptr_t)action + sizeof(Action));

    for (int i = 0; i < action->numParams; i++) {
        CParameter cCurr = CParameter(curr);
        params.push_back(cCurr);
        curr = cCurr.Next().param;
    }

    return params;
}

CCondition::CCondition(Condition* condition) {
    this->condition = condition;
}

std::vector<CParameter> CCondition::GetParams() {
    std::vector<CParameter> params;
    Parameter* curr = (Parameter*)((uintptr_t)condition + sizeof(Condition));

    for (int i = 0; i < condition->numParams; i++) {
        CParameter cCurr = CParameter(curr);
        params.push_back(cCurr);
        curr = cCurr.Next().param;
    }

    return params;
}

CParameter::CParameter(Parameter* param) {
    this->param = param;
}

CParameter CParameter::Next() {
    Parameter* nextParam = (Parameter*)((uintptr_t)param + param->evpSize);
    return CParameter(nextParam);
}

std::string CParameter::Name() {
    return "Not implemented";
}

CRunObject::CRunObject(RunObject* ro) {
    this->ro = ro;
}


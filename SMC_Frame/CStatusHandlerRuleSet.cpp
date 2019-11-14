// Copyright (C) 2011 SMS Siemag AG
#include <string>
#include "CStatusHandlerRuleSet.h"


CStatusHandlerRuleSet::CStatusHandlerRuleSet( const std::string & Key, long State, long Transition )
: m_Key(Key)
, m_State(State)
, m_Transition(Transition)
{
}

CStatusHandlerRuleSet::~CStatusHandlerRuleSet()
{
}

long CStatusHandlerRuleSet::getTransition()
{
	return m_Transition;
}

long CStatusHandlerRuleSet::getState()
{
	return m_State;
}


std::string& CStatusHandlerRuleSet::getKey()
{
	return m_Key;
}


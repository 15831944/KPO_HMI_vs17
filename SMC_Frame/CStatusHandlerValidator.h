// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CStatusHandlerValidator_47384A8F01B9_INCLUDED
#define _INC_CStatusHandlerValidator_47384A8F01B9_INCLUDED

#include <string>
#include <map>

#include "CStatusHandlerRuleSet.h"

class CStatusHandlerValidator 
{
private:

  std::multimap<std::string,CStatusHandlerRuleSet*> m_RuleSetList;

  void insertRuleSet(const std::string& Key,  CStatusHandlerRuleSet* pStatusHandlerRuleSet   );

  void log(const std::string& Message, long Level);


public:
	virtual ~CStatusHandlerValidator();

	CStatusHandlerValidator();

  void loadRule(const std::string& Key, long State, long Transition);

  bool validateTransition(const std::string& Key, long ActState, long NewState);

};

#endif /* _INC_CStatusHandlerValidator_47384A8F01B9_INCLUDED */

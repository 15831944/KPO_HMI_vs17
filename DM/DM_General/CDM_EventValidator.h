// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EVENTVALIDATOR_429D8B6D00EF_INCLUDED
#define _INC_CDM_EVENTVALIDATOR_429D8B6D00EF_INCLUDED

#include <set>
#include <map>

//class reading "rulesets", e.g. EventMessage Name and 
//respective expected Data names, from file as defined at ini 
//file [PATH] / EventRuleSet. Rules will be managed in the 
//RulSetList.
class CDM_EventValidator 
{
public:

	virtual ~CDM_EventValidator();

	CDM_EventValidator();

	void loadRules();

	std::set<std::string> getRuleSetNames(const std::string& EventMessage);

private:
	std::multimap<std::string,std::string> m_RuleSetList;

};

#endif /* _INC_CDM_EVENTVALIDATOR_429D8B6D00EF_INCLUDED */

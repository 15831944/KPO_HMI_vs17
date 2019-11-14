// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_EVENTVALIDATOR_429D8B6D00EF_INCLUDED
#define _INC_CSMC_EVENTVALIDATOR_429D8B6D00EF_INCLUDED

#include <set>
#include <map>

//class reading "rulesets", e.g. EventMessage Name and 
//respective expected Data names, from file as defined at ini 
//file [PATH] / EventRuleSet. Rules will be managed in the 
//RulSetList.
//##ModelId=471C7256003A
class CSMC_EventValidator 
{
public:

	//##ModelId=471C7256004E
	virtual ~CSMC_EventValidator();

	//##ModelId=471C72560050
	CSMC_EventValidator();

	//##ModelId=471C72560051
	void loadRules();

	//##ModelId=471C72560058
	std::set<std::string> getRuleSetNames(const std::string& EventMessage,const std::string& Enty = "Names" );

private:
	//##ModelId=471C7256005C
	std::multimap< std::string, std::map<std::string,std::string> > m_RuleSetList;

};

#endif /* _INC_CSMC_EVENTVALIDATOR_429D8B6D00EF_INCLUDED */

// Copyright (C) 2004 SMS Demag AG

#include <sstream>
#include <iostream>
#include <fstream>
#include "cCBS_StdInitBase.h"
#include "CDM_EventValidator.h"


CDM_EventValidator::~CDM_EventValidator()
{
  m_RuleSetList.erase(m_RuleSetList.begin(),m_RuleSetList.end());
}

CDM_EventValidator::CDM_EventValidator()
{
	loadRules();
}

void CDM_EventValidator::loadRules()
{
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
  
  std::string EventRuleSet;

  pInitBase->replaceWithEntry("PATH", "EventRuleSet", EventRuleSet);

  if (!EventRuleSet.empty())
  {
    EventRuleSet =  pInitBase->getXPACT_SMC() + EventRuleSet;

    std::ifstream in(EventRuleSet.c_str());
    std::string lineBuffer;
    std::string Block;

    while (getline(in, lineBuffer))
	  {
      std::string Name;

      std::istringstream istr(lineBuffer);

      // processing empty and comment lines
      if(lineBuffer.empty() || lineBuffer.substr(0,2) == "//")
      {
        continue;
      }
      
      if(lineBuffer.substr(0,1) == "[")
      {
        // Block is value inbetween "[" and "]"
        if( istr >> Block )
        {
          Block = Block.substr(1,Block.length()-2);
        }
        else
        {
          Block.erase();
        }
      }

      if( istr >> Name )
      {
        m_RuleSetList.insert(std::pair<std::string,std::string>(Block,Name));
      }
    }

    in.close();
  }
  
}

std::set<std::string> CDM_EventValidator::getRuleSetNames(const std::string& EventMessage)
{
  std::multimap<std::string,std::string>::iterator it;
  std::set<std::string> RuleSetNames;

  for( it = m_RuleSetList.begin() ; it != m_RuleSetList.end() ; ++it)
  {
    if ( it->first == EventMessage )
    {
      RuleSetNames.insert(it->second);
    }
  }

	return RuleSetNames;
}

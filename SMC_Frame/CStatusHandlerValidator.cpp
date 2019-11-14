// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdLog_Task.h"

#include "CStatusHandlerRuleSet.h"
#include "CStatusHandlerValidator.h"



CStatusHandlerValidator::~CStatusHandlerValidator()
{
}

CStatusHandlerValidator::CStatusHandlerValidator()
{
}

void CStatusHandlerValidator::loadRule(const std::string& Key, long State, long Transition)
{
  CStatusHandlerRuleSet *pRuleSet = new CStatusHandlerRuleSet(Key,State,Transition);

  insertRuleSet(Key,pRuleSet);
}

void CStatusHandlerValidator::insertRuleSet(const std::string& Key,  CStatusHandlerRuleSet* pStatusHandlerRuleSet   )
{
  std::multimap<std::string,CStatusHandlerRuleSet*>::iterator it;

  if (pStatusHandlerRuleSet)
  {
    it = m_RuleSetList.find(Key);
    m_RuleSetList.insert(it,std::pair<std::string,CStatusHandlerRuleSet*>(Key,pStatusHandlerRuleSet));
  }
  else
  {
    log("CStatusHandlerValidator::insertRuleSet() : pStatusHandlerRuleSet invalid!",1);
  }
}

void CStatusHandlerValidator::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->writeLog(Message,Level);
}

bool CStatusHandlerValidator::validateTransition(const std::string& Key, long ActState, long NewState)
{
  bool RetValue = true;

  if ( m_RuleSetList.size() > 0 )
  {
    std::multimap<std::string,CStatusHandlerRuleSet*>::iterator it ;

    for ( it = m_RuleSetList.find(Key); it != m_RuleSetList.end(); ++it )
    {
      if ( it->first != Key )
      {
        break;
      }

      if ( it->second->getState() == ActState )
      {
        RetValue = false;

        if ( it->second->getTransition() == NewState )
        {
          RetValue = true;
          break;
        }
      }
    }
  }

  return RetValue;
}


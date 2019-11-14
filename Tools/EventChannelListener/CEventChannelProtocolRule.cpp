// Copyright (C) 2011 SMS Siemag AG

#include <sstream>

#include "CEventMessage.h"
#include "CEventChannelProtocolRule.h"


CEventChannelProtocolRule::CEventChannelProtocolRule(const std::string& Block,std::multimap<std::string,std::string> RuleList)
{
  m_Block    = Block;
  m_RuleList = RuleList;
}

CEventChannelProtocolRule::~CEventChannelProtocolRule()
{
}


bool CEventChannelProtocolRule::doOnEvent(const CEventMessage& EventMessage)
{
  // increase counter
  // calculate time difference

	return true;
}

std::string CEventChannelProtocolRule::getBlock()
{
  return m_Block;
}
std::multimap<std::string,std::string> CEventChannelProtocolRule::getRuleList()
{
  return m_RuleList;
}

std::string CEventChannelProtocolRule::getContent()
{
  std::stringstream Content;

  Content << m_Block;

  std::multimap<std::string,std::string>::iterator it;

  for ( it = m_RuleList.begin() ; it != m_RuleList.end() ; ++it)
  {
    Content << " -> ";
    Content << it->first;
    Content << " -> ";
    Content << it->second;
  }

  return Content.str();
}

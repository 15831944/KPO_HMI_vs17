// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEventChannelProtocolRule_41344FE603C7_INCLUDED
#define _INC_CEventChannelProtocolRule_41344FE603C7_INCLUDED

#include "CDateTime.h"
#include "CEventHandler.h"

//##ModelId=41344FE603C7
class CEventChannelProtocolRule 
{
public:
	bool doOnEvent(const CEventMessage& EventMessage);

  CEventChannelProtocolRule(const std::string& Block, std::multimap<std::string,std::string> RuleList);
  virtual ~CEventChannelProtocolRule();
  std::string getContent();

  std::string getBlock();
  std::multimap<std::string,std::string> getRuleList();

private:

  std::string m_Block;
  std::multimap<std::string,std::string> m_RuleList;

  double m_CallInterval;
  double m_NoOfCalls;

  CDateTime m_LastCallTime;
};

#endif /* _INC_CEventChannelProtocolRule_41344FE603C7_INCLUDED */

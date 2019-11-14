// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEventChannelProtocol_41344FE603C7_INCLUDED
#define _INC_CEventChannelProtocol_41344FE603C7_INCLUDED

#include "CDateTime.h"
#include "CEventHandler.h"

//##ModelId=41344FE603C7
class CEventChannelProtocol 
{
public:
	bool doOnEvent(const CEventMessage& EventMessage);

  CEventChannelProtocol(const CEventMessage& EventMessage);
  virtual ~CEventChannelProtocol();
  std::string getContent();

  std::string getMessage();
  std::string getSender();
  std::string getReceiver();


private:

  std::string m_Message;
  std::string m_Sender;
  std::string m_Receiver;

  double m_CallInterval;
  double m_NoOfCalls;

  CDateTime m_LastCallTime;
};

#endif /* _INC_CEventChannelProtocol_41344FE603C7_INCLUDED */

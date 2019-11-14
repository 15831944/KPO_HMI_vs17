// Copyright (C) 2011 SMS Siemag AG

#include <sstream>


#include "CEventMessage.h"
#include "CEventChannelProtocol.h"


CEventChannelProtocol::CEventChannelProtocol(const CEventMessage& EventMessage)
: m_NoOfCalls(0)
, m_CallInterval(0)
{
  m_Message    = EventMessage.getMessage();
  m_Sender     = EventMessage.getSender();
  m_Receiver   = EventMessage.getReceiver();
}

CEventChannelProtocol::~CEventChannelProtocol()
{
}


bool CEventChannelProtocol::doOnEvent(const CEventMessage& EventMessage)
{
  // increase counter
  m_NoOfCalls ++ ;

  // calculate time difference
  CDateTime Now;
  CDeltaTime DeltaTime = CDateTime::subTimes(Now,m_LastCallTime);

  m_CallInterval = DeltaTime.asSeconds();
  
  m_LastCallTime = Now;

	return true;
}

std::string CEventChannelProtocol::getMessage()
{
  return m_Message;
}
std::string CEventChannelProtocol::getSender()
{
  return m_Sender;
}

std::string CEventChannelProtocol::getReceiver()
{
  return m_Receiver;
}

std::string CEventChannelProtocol::getContent()
{
  std::stringstream Content;

  Content << m_Message;
  Content << " : ";
  Content << m_Sender;
  Content << " -> ";
  Content << m_Receiver;
  Content << " : ";
  Content << m_NoOfCalls;
  Content << " : ";
  Content << m_CallInterval;
  Content << " : ";
  Content << m_LastCallTime.asString();

  return Content.str();
}

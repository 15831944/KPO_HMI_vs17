// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTCHANNELLISTENEREVENTHANDLER_41344FE603C7_INCLUDED
#define _INC_CEVENTCHANNELLISTENEREVENTHANDLER_41344FE603C7_INCLUDED


#include "CEventHandler.h"

class CEventMessage;
class CEventChannelProtocol;
class CEventChannelProtocolRule;


//##ModelId=41344FE603C7
class CEventChannelListenerEventHandler 
: public CEventHandler
{
private:
  
  std::multimap<std::string,CEventChannelProtocolRule*> m_EventProtocolRuleList;
  std::multimap<std::string,CEventChannelProtocol*> m_EventProtocolList;

  CEventChannelProtocol* findEventChannelProtocol(const std::string& Message,const std::string& Sender,const std::string& Receiver);
  bool doOnEventMessage(const CEventMessage& EventMessage);
  void loadRules();
  void addRule(const std::string& Block,std::multimap<std::string,std::string> RuleList);

  void clearProtocol();

  bool checkRules();


public:
	//##ModelId=42C298BB00F0
	virtual bool doOnEventHandlingError(const FRIESEvent& Event);

	//##ModelId=42BBC9C40272
	virtual bool checkEventAcceptance(const FRIESEvent& Event);

	//##ModelId=41405DEE01F6
	virtual bool handleEvent(const FRIESEvent& Event);

  CEventChannelListenerEventHandler();
  ~CEventChannelListenerEventHandler();

};

#endif /* _INC_CEVENTCHANNELLISTENEREVENTHANDLER_41344FE603C7_INCLUDED */

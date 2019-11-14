// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTHANDLER_410E06FA0066_INCLUDED
#define _INC_CEVENTHANDLER_410E06FA0066_INCLUDED

class CEventMessage;


#include "CEventMessage.h"

#include "cCBS_StdEventHandler.h"

class CEventMessage;

//##ModelId=410E06FA0066
class CEventHandler 
: public cCBS_StdEventHandler
{
protected:
	//##ModelId=410E076500D8
	CEventHandler();

  //##ModelId=434CD60C0145
	void initCommunication(const std::string& Group);

	//##ModelId=433BDA3402C6
	std::vector<std::string> m_TransmitterList;

  std::vector<std::string> m_MessageList;

	//##ModelId=433BB14B0297
	std::vector<std::string> m_DestinationList;

	//##ModelId=433BAF560341
	std::string m_SenderName;

	//##ModelId=44FE9C2F025F
	std::vector<std::string> m_PlantIdList;

	//##ModelId=42395C000298
	static CEventMessage m_ActEvent;

	//##ModelId=412E17780197
  std::string m_ReceiverName;

public:
	//##ModelId=433BAE830372
	virtual void setpTask(cCBS_StdFrame_Task* value);

	//##ModelId=42C291EC0266
	virtual bool doOnEventHandlingError(const FRIESEvent& Event);

	//##ModelId=42B812960221
	virtual bool checkEventAcceptance(const FRIESEvent& Event);

  virtual bool checkReplaceEvent(const FRIESEvent& FirstEvent, const FRIESEvent& NewEvent);

	//##ModelId=42397ADA017E
	virtual bool checkDataIntegrity(CEventMessage& Event);

	//##ModelId=416CF0F5026E
	virtual bool checkReceiver(CEventMessage& Event);

	//##ModelId=44FE9C2F0271
	virtual bool checkPlantId(CEventMessage& Event);

	//##ModelId=44FE9C2F028F
	virtual bool checkTransmitter(CEventMessage& Event);

  virtual bool checkMessage(CEventMessage& Event);

	//##ModelId=41405A4C00C1
	void log(CEventMessage& Event, long Level);

	//##ModelId=471C725E0254
  virtual bool dispatchEvent(const std::string& SenderName, std::vector<std::string> & DestinationList, CEventMessage &Event);

	//##ModelId=471C725F0039
  virtual bool dispatchEvent(const std::string& SenderName, std::vector<std::string> & DestinationList, CEventMessage &Event, bool External);

  // to be backward compatible !
	//##ModelId=413EC4A30084
  virtual bool dispatchEvent(const std::string& SenderName, const std::string& Destination, CEventMessage &Event);


	//##ModelId=412F247502D3
	const std::string& getReceiverName() const;

	//##ModelId=412E18350387
	void log(const std::string& Message, long Level);

	//##ModelId=410E3DC9024D
  virtual bool handleEvent(const FRIESEvent& Event);

	virtual bool afterHandleEvent(const FRIESEvent& Event);

	virtual bool beforeHandleEvent(const FRIESEvent& Event);

	//##ModelId=410E076B0287
	virtual ~CEventHandler();
};

#endif /* _INC_CEVENTHANDLER_410E06FA0066_INCLUDED */

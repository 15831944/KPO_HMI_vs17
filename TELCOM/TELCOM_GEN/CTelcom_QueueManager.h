// Copyright (C) 2007 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_QUEUEMANAGER_45AB73A602D8_INCLUDED
#define _INC_CTELCOM_QUEUEMANAGER_45AB73A602D8_INCLUDED

#include "CTelcom_MsgQueue.h"
#include "IQueue.h"
#include "cCBS_LocalSyncEvent.h"
#include "cCBS_CriticalSection.h"


class CTelcom_Msg;
class Protocol;
class Prot;
class CTelcom_MsgConverter;

class CTelcom_MsgTypeTranslator;

///////////////////////////////////////////////
//
//Synchronization of the queue access with CBS utilities.
//Queue size control if no connection to remote peer.
//
///////////////////////////////////////////////
class CTelcom_QueueManager : public IQueue
{
private:
	CTelcom_MsgTypeTranslator* m_pMsgTypeTranslator;

	Prot* m_pProtocol;

	//Maximum queue size.
	//* 0 = no limit
	long m_MaxQueueSize;

  unsigned long m_sendPause;

  cCBS_CriticalSection m_Section;

  cCBS_LocalSyncEvent  m_Event;

	CTelcom_MsgQueue m_Queue;

  enum ReturnValues
  { 
    OK = 0,
    TIMEOUT = -1
  };

  //counter for lost messages since start up of application
	long m_LostMessages;

public:
	void setMsgTypeTranslator(CTelcom_MsgTypeTranslator* value);

	void setProtocol(Prot* value);

	CTelcom_QueueManager();

	virtual ~CTelcom_QueueManager();

	virtual void open(const std::string& name);

	virtual void close();

	//  Enqueue a message. More...
	virtual void enqueue(TCMessage &msg );

	//Will be called by SProt to send the message.
	virtual int dequeue(TCMessage& msg, int seconds);

	virtual void enqueueTelcomMsg(CTelcom_Msg* Msg);

protected:
	CTelcom_MsgConverter* m_MsgConverter;

};

#endif /* _INC_CTELCOM_QUEUEMANAGER_45AB73A602D8_INCLUDED */

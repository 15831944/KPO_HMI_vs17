// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTSENDER_40C03A0F03D1_INCLUDED
#define _INC_CEVENTSENDER_40C03A0F03D1_INCLUDED

#include "cCBS_StdEventSenderTask.h"

class CEventMessage;

//Class realizing an CBS EventChannelSender
//##ModelId=40EAA093023C
class cCBS_StdEventSender_Task : public cCBS_StdEventSenderTask
  
{
private:
  cCBS_StdEvent_Task* m_pEventTask;

  std::string m_TaskName;
  std::string m_ChannelName;
  std::string m_ServiceName;
  std::string m_ChannelName2;
  std::string m_ServiceName2;

public:

	//##ModelId=40EBCAAE0025
  void log( const std::string  & Message, long Level);

  //Sends given event to receiver.
  //##ModelId=40EAA093023E
  virtual bool sendEvent(const FRIESEvent& Event);

  //##ModelId=40EAA0930246
  virtual ~cCBS_StdEventSender_Task();

  cCBS_StdEventSender_Task( cCBS_StdEvent_Task* pEventTask,const std::string& TaskName, const std::string& ChannelName, const std::string& ServiceName, const std::string& ChannelName2, const std::string& ServiceName2);

  virtual void ownStartUp();
  virtual void ownRunDown();
};

#endif /* _INC_CEVENTSENDER_40C03A0F03D1_INCLUDED */

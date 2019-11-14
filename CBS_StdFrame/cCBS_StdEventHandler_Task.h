// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTCONSUMER_40C03A1E0347_INCLUDED
#define _INC_CEVENTCONSUMER_40C03A1E0347_INCLUDED

#include "cCBS_StdEventHdlTask.h"

class cCBS_StdEventMessage;
class cCBS_StdEvent_Task;
class cCBS_StdEventHandlerAdapter;
class cCBS_StdEventHandler;


//Class providing EventChannel functionalities.
//##ModelId=40EAA093024C
class cCBS_StdEventHandler_Task 
: public cCBS_StdEventHdlTask
{
private:
  //##ModelId=40EBCAAE010D
  cCBS_StdEvent_Task* m_pEventTask;

  cCBS_StdEventHandlerAdapter* m_pEventHandlerAdapter;

  std::string m_TaskName;
  std::string m_ChannelName;
  std::string m_ServiceName;
  std::string m_ChannelName2;
  std::string m_ServiceName2;

public:

	//##ModelId=40EBCAAE0116
  void log( const std::string & Message, long Level);

  cCBS_StdEventHandler_Task( cCBS_StdEvent_Task* pEventTask,const std::string& TaskName, const std::string& ChannelName, const std::string& ServiceName, const std::string& ChannelName2, const std::string& ServiceName2);

  //event handling method
  //
  //abstract method, must be implemented to ensure the 
  //event being handled in an application specific way
  //
  //parameters:
  //- const FRIESEvent &
  //
  //simplyfied speaking, a consumer is nothing but a CORBA 
  //object which offers methods to be accessed from 
  //clients. this method can be considered as one of these
  //##ModelId=40EAA0930251
  virtual void handleEvent(const FRIESEvent& Event);

  //##ModelId=40EAA0930256
  virtual ~cCBS_StdEventHandler_Task();

  std::string getStateDetails();

  bool registerEventHandler(cCBS_StdEventHandler* pEventHandler);

  virtual void ownStartUp();
  virtual void ownRunDown();


};

#endif /* _INC_CEVENTCONSUMER_40C03A1E0347_INCLUDED */

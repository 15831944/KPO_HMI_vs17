// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"

//##ModelId=40EAA093023E
#include "cCBS_StdEventSender_Task.h"


cCBS_StdEventSender_Task::cCBS_StdEventSender_Task( cCBS_StdEvent_Task* pEventTask,const std::string& TaskName, const std::string& ChannelName, const std::string& ServiceName, const std::string& ChannelName2, const std::string& ServiceName2)
: cCBS_StdEventSenderTask(ChannelName.c_str(), ServiceName.c_str(), ChannelName2.c_str(), ServiceName2.c_str())
, m_pEventTask(pEventTask)
, m_TaskName(TaskName)
, m_ChannelName(ChannelName)
, m_ServiceName(ServiceName)
, m_ChannelName2(ChannelName2)
, m_ServiceName2(ServiceName2)
{

}

//##ModelId=40EAA0930246
cCBS_StdEventSender_Task::~cCBS_StdEventSender_Task()
{
}




//##ModelId=40EAA093023E
bool cCBS_StdEventSender_Task::sendEvent(const FRIESEvent& Event)
{
  bool RetValue = false;
  try
  {
    // Send FRIES event via event channel
    RetValue = cCBS_StdEventSenderTask::send(Event);

    // reconnect if neccessary
    if ( !RetValue )
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorConnectingEventChannel(Message);
    }
  }
  catch(CORBA::SystemException& Exc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,Exc._name(),"cCBS_StdEventSender_Task::sendEvent()","Sending Event");
  }
  catch(CORBA::Exception& Exc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,Exc._name(),"cCBS_StdEventSender_Task::sendEvent()","Sending Event");
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught("","cCBS_StdEventSender_Task::sendEvent()","Sending Event");
  }

  return RetValue;

}


//##ModelId=40EBCAAE0025
void cCBS_StdEventSender_Task::log(const std::string& Message, long Level)
{
  if ( m_pEventTask )
  {
    m_pEventTask->log(Message, Level);
  }
}

void cCBS_StdEventSender_Task::ownStartUp()
{
  cCBS_StdEventSenderTask::ownStartUp();
  setWorking(true);
}

//##ModelId=40EAA0930182
void cCBS_StdEventSender_Task::ownRunDown()
{
  cCBS_StdEventSenderTask::ownRunDown();
  setWorking(false);
}

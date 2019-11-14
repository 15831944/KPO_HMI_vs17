// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>

#include "cCBS_AccessSync.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdEventHandlerAdapter.h"

#include "cCBS_StdEventHandler_Task.h"


cCBS_StdEventHandler_Task::cCBS_StdEventHandler_Task( cCBS_StdEvent_Task* pEventTask
                                             ,const std::string& TaskName
                                             ,const std::string& ChannelName
                                             ,const std::string& ServiceName
                                             ,const std::string& ChannelName2
                                             ,const std::string& ServiceName2)
: cCBS_StdEventHdlTask(ChannelName.c_str(), ServiceName.c_str(), ChannelName2.c_str(), ServiceName2.c_str())
, m_pEventTask(pEventTask)
, m_pEventHandlerAdapter(0)
, m_TaskName(TaskName)
, m_ChannelName(ChannelName)
, m_ServiceName(ServiceName)
, m_ChannelName2(ChannelName2)
, m_ServiceName2(ServiceName2)
{

  m_pEventHandlerAdapter = new cCBS_StdEventHandlerAdapter(pEventTask,TaskName);

}


//##ModelId=40EAA0930256
cCBS_StdEventHandler_Task::~cCBS_StdEventHandler_Task()
{
  if (m_pEventHandlerAdapter)
  {
    delete m_pEventHandlerAdapter;
  }
}


//##ModelId=40EAA0930251
void cCBS_StdEventHandler_Task::handleEvent(const FRIESEvent& Event)
{
  // synchronization necessary, if method will be called internally and from EventHandlerTask !
  cCBS_AccessSync AccessSync;

  try
  {
    if (m_pEventHandlerAdapter)
    {
      m_pEventHandlerAdapter->handleEvent(Event);
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorUsingFrameTask(Message,"EventTask");
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,sExc._name(),"cCBS_StdEventHandler_Task::handleEvent","Handling Event");
  }

  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,cExc._name(),"cCBS_StdEventHandler_Task::handleEvent","Handling Event");
  }

  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"","cCBS_StdEventHandler_Task::handleEvent","Handling Event");
  }
}


//##ModelId=40EBCAAE0116
void cCBS_StdEventHandler_Task::log( const std::string & Message, long Level)
{
  if ( m_pEventTask )
  {
    m_pEventTask->log(Message, Level);
  }
}

std::string cCBS_StdEventHandler_Task::getStateDetails()
{
  std::string StateDetails;

  if ( m_pEventHandlerAdapter )
  {
    StateDetails = m_pEventHandlerAdapter->getStateDetails();
  }

  return StateDetails;
}

bool cCBS_StdEventHandler_Task::registerEventHandler(cCBS_StdEventHandler* pEventHandler)
{ 
  bool RetValue = false;

  if ( m_pEventHandlerAdapter )
  {
    RetValue = m_pEventHandlerAdapter->registerEventHandler(pEventHandler);
  }

  return RetValue;
}

void cCBS_StdEventHandler_Task::ownStartUp()
{
  cCBS_StdEventHdlTask::ownStartUp();
  setWorking(true);
}

//##ModelId=40EAA0930182
void cCBS_StdEventHandler_Task::ownRunDown()
{
  cCBS_StdEventHdlTask::ownRunDown();
	setWorking(false);
}

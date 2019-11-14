// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdEventLogCyclicReminder.h"

//##ModelId=48A53D540303
cCBS_StdEventLogCyclicReminder::cCBS_StdEventLogCyclicReminder()
{
}

//##ModelId=48A53D5402E4
cCBS_StdEventLogCyclicReminder::~cCBS_StdEventLogCyclicReminder()
{
  cCBS_StdMutex CBS_StdMutex("m_EventLogList");

  try
  {
    std::map<long,cCBS_StdEventLogCyclicReminder::CCyclicTrig*>::iterator it;

    for ( it = m_EventLogList.begin(); it != m_EventLogList.end();++it)
    {
      // terminates trigger
      it->second->setTerminateThread();
      it->second->join();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::~cCBS_StdEventLogCyclicReminder()","Terminating trigger");
  }

}

//##ModelId=48A53D540399
void cCBS_StdEventLogCyclicReminder::sendMessage(sEventLogMessage& EventLog, long msec /* = 20000 */ )
{
  log("cCBS_StdEventLogCyclicReminder::sendMessage(sEventLogMessage& EventLog, long msec /* = 20000 */ )",4);

  cCBS_StdEventLogCyclicReminder::CCyclicTrig* pCyclicTrig = findTrigger(EventLog);

  if (pCyclicTrig)
  {
    pCyclicTrig->recall();
  }
  else
  {
    addEventLog(EventLog, msec);
  }
}

void cCBS_StdEventLogCyclicReminder::log(const std::string & Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}


//##ModelId=48A53D550006
cCBS_StdEventLogCyclicReminder::CCyclicTrig* cCBS_StdEventLogCyclicReminder::findTrigger(sEventLogMessage& EventLog)
{
  cCBS_StdMutex CBS_StdMutex("m_EventLogList");

  cCBS_StdEventLogCyclicReminder::CCyclicTrig* pCyclicTrig = 0;

  std::map<long,cCBS_StdEventLogCyclicReminder::CCyclicTrig*>::iterator it;

  it = m_EventLogList.find(EventLog.eventId);

  if ( it != m_EventLogList.end() )
  {
    // for operator achnowledge enetid could be identical inbetween control time, but we have to check message content also to decide if this is a real re-call
    if ( std::string(it->second->getEventLog().messageText) == std::string(EventLog.messageText) )
    {
      pCyclicTrig = it->second;
    }
  }

  return pCyclicTrig;
  
}

//##ModelId=48A53D54030D
void cCBS_StdEventLogCyclicReminder::addEventLog(sEventLogMessage& EventLog, long msec)
{
  cCBS_StdMutex CBS_StdMutex("m_EventLogList");

  log("cCBS_StdEventLogCyclicReminder::addEventLog(sEventLogMessage& EventLog, long msec)",4);

  // create new cyclic trigger
  cCBS_StdEventLogCyclicReminder::CCyclicTrig *pTrig = new cCBS_StdEventLogCyclicReminder::CCyclicTrig(this, EventLog, msec);

  // fill m_EventLogList, first entry is event id 
  m_EventLogList.insert( std::pair<long,cCBS_StdEventLogCyclicReminder::CCyclicTrig*> (EventLog.eventId, pTrig ));

  // start trigger
  pTrig->setFreeOnTerminate(true);  
  pTrig->run();

}

//##ModelId=48A53D540367
void cCBS_StdEventLogCyclicReminder::removeEventLog(sEventLogMessage& EventLog)
{
  cCBS_StdMutex CBS_StdMutex("m_EventLogList");

  log("cCBS_StdEventLogCyclicReminder::removeEventLog(sEventLogMessage& EventLog)",4);

  std::map<long,cCBS_StdEventLogCyclicReminder::CCyclicTrig*>::iterator it;

  it = m_EventLogList.find(EventLog.eventId);

  if ( it != m_EventLogList.end() )
  {
    // do not delete object due to beeing thread that will be called with setTerminateThread() by caller of removeEventLog()
    m_EventLogList.erase(it);  
  }
}


//##ModelId=48A53D550034
void cCBS_StdEventLogCyclicReminder::recall(sEventLogMessage& EventLog)
{
  log("cCBS_StdEventLogCyclicReminder::recall(sEventLogMessage& EventLog)",4);

  cCBS_StdEventLogCyclicReminder::CCyclicTrig* pCyclicTrig = findTrigger(EventLog);

  if ( pCyclicTrig )
  {
    pCyclicTrig->recall();
  }
}


//##ModelId=48A53D5500DF
cCBS_StdEventLogCyclicReminder::CCyclicTrig::~CCyclicTrig()
{
}

//##ModelId=48A53D5500E1
cCBS_StdEventLogCyclicReminder::CCyclicTrig::CCyclicTrig(cCBS_StdEventLogCyclicReminder* parent, sEventLogMessage& EventLog, long RemindTime)
: m_EventLog(EventLog)
, m_RemindTime(RemindTime)
, m_Parent(parent)
, m_isRecalled(false)
{
}

void cCBS_StdEventLogCyclicReminder::CCyclicTrig::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdEventLogCyclicReminder::CCyclicTrig::work()","performing Working Step");
  }
}


//##ModelId=48A53D5500EB
void cCBS_StdEventLogCyclicReminder::CCyclicTrig::performWorkingStep()
{
  try
  {
    m_isRecalled = false;

    // send the eventlog directly
    if ( !getTerminateThread() )
    {
      log("cCBS_StdEventLogCyclicReminder::CCyclicTrig::performWorkingStep() - calling cCBS_EventLog::sendMessage(EventLogMessage);", 4);

      cCBS_StdEventLogFrameController::getInstance()->getpEventLog()->cCBS_EventLog::sendMessage(m_EventLog);
    }

    sleep(m_RemindTime);

    // if eventlog is recalled within m_RemindTime, we have to send it again
    // m_isRecalled is set at void cCBS_StdEventLogCyclicReminder::CCyclicTrig::recall()
    if ( !m_isRecalled )
    {
      terminate();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }
}


//##ModelId=48A53D5500D4
void cCBS_StdEventLogCyclicReminder::CCyclicTrig::recall()
{
  try
  {
    m_isRecalled = true;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::recall()","recalling");
  }
}

//##ModelId=48A53D5500E9
std::string cCBS_StdEventLogCyclicReminder::CCyclicTrig::getCurrentThreadId()
{
  std::stringstream Message;
  Message << GetCurrentThreadId() ;

  return Message.str();
}

//##ModelId=48A53D5500EA
void cCBS_StdEventLogCyclicReminder::CCyclicTrig::terminate()
{
  // clear List with eventlogs
  m_Parent->removeEventLog(m_EventLog);

  // indicate thread itself as terminated
  // flag will be checked at performWorkingStep
  setTerminateThread();
}

sEventLogMessage cCBS_StdEventLogCyclicReminder::CCyclicTrig::getEventLog()
{
  return m_EventLog;
}

void cCBS_StdEventLogCyclicReminder::CCyclicTrig::log(const std::string & Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}


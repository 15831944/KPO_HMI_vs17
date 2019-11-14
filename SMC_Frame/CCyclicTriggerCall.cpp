// Copyright (C) 2004 SMS Demag AG

#include <sstream>
#include "wrapthread.h"

#include "CSMC_Mutex.h"
#include "CEventMessage.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"

#include "CCyclicTriggerCall.h"



//##ModelId=4266118F017A
CCyclicTriggerCall::~CCyclicTriggerCall()
{
  try
  {
  	if ( m_pTrig )
    {
      // terminates trigger
      m_pTrig->setTerminateThread();
      m_pTrig->join();
    }

  	if ( m_pTrig )
    {
      delete m_pTrig;
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::~CCyclicTriggerCall()","Terminate trigger");
  }

}

//##ModelId=4266118F0331
CCyclicTriggerCall::CCyclicTriggerCall(CEventMessage& arg, long msec)
: m_pTrig(0), m_Terminated(false)
{
  std::stringstream Message;
  Message << " CCyclicTriggerCall::CCyclicTrig::CCyclicTrig starting with " 
          << arg.getMessage() << " " 
          << arg.getProductID() << " " 
          << msec;

  cCBS_StdLog_Task::getInstance()->log(Message.str(),3);

	m_pTrig = new CCyclicTriggerCall::CCyclicTrig(this, arg, msec);
}

//##ModelId=4266138A03C6
void CCyclicTriggerCall::send()
{
  try
  {
	  if (m_pTrig)
    {
      m_pTrig->resetAndSend();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicTriggerCall::send()","Sending trigger");
  }
}

//##ModelId=42BAA975022C
void CCyclicTriggerCall::update(CEventMessage& Event)
{
  try
  {
	  if (m_pTrig)
    {
      m_pTrig->update(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicTriggerCall::update()","Update trigger");
  }
}

void CCyclicTriggerCall::reset()
{
  try
  {
	  if (m_pTrig)
    {
      m_pTrig->resetAndWait();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicTriggerCall::update()","Update trigger");
  }
}





//##ModelId=4266115103E6
CCyclicTriggerCall::CCyclicTrig::~CCyclicTrig()
{
}

//##ModelId=42661152028B
CCyclicTriggerCall::CCyclicTrig::CCyclicTrig(CCyclicTriggerCall* parent, CEventMessage& ev, long cycle)
: m_eventMessage(ev)
, m_cycleTime(cycle)
, m_Parent(parent)
, m_LifeTime(-1)    // trigger will not terminate automatically !
, m_elapsedTime(0)

{
  setFreeOnTerminate(false);
  run();
}

//##ModelId=42661F0902F8
void CCyclicTriggerCall::CCyclicTrig::resetAndSend()
{
  try
  {
    logThreadInformation("resetting thread to send immediate");

    if ( !getTerminateThread() )
    {
      m_elapsedTime = 0;
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::reset()","resetting trigger");
  }
}

void CCyclicTriggerCall::CCyclicTrig::resetAndWait()
{
  try
  {
    logThreadInformation("resetting thread to wait until elapsed time");

    if ( !getTerminateThread() )
    {
      m_elapsedTime = 1; // set to value > 0 because m_elapsedTime == 0 is checked in performWorkingStep
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::reset()","resetting trigger");
  }
}


void CCyclicTriggerCall::CCyclicTrig::work()
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
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicTriggerCall::CCyclicTrig::work()","performing Working Step");
  }
}

//##ModelId=426664040345
void CCyclicTriggerCall::CCyclicTrig::performWorkingStep()
{
  try
  {
    // check sender time every xxx msecs
    long checkTime   = 50;

    if ( !getTerminateThread() )
    {
      // perform step in interval given by m_cycleTime
      if ( m_elapsedTime >= m_cycleTime || m_elapsedTime == 0 )
      {
        // terminate if life time has elapsed
        // send event if not

        CDeltaTime  DurTime;
        CDateTime   now;

        DurTime = CDateTime::subTimes(now, m_LastActionTime);

        if ( ((DurTime.asSeconds()*1000) < m_LifeTime) || m_LifeTime < 0 )
        {
          std::vector<std::string> DestinationList;

          // check if destinationName is containing several entries !
          std::string ActValue = m_eventMessage.getReceiver();

          while (!ActValue.empty())
          {
            std::string ActSubstr = ActValue;

            std::basic_string <char>::size_type pos = ActValue.find(",");

            if ( std::string::npos != pos )
            {
              ActSubstr = ActValue.substr(0,pos );
              ActValue = ActValue.substr(pos+1,ActValue.length());
            }
            else
            {
              ActValue.erase();
            }

            DestinationList.push_back(ActSubstr);        
          }

          // make a copy here because CEventMessage class will overwrite Destination !
          CEventMessage MessageToSend(m_eventMessage);
          MessageToSend.dispatch(MessageToSend.getSender(),DestinationList);

        }
        else
        {
          std::stringstream Message;
          Message << "Duration from last action: " << DurTime.asSeconds() << " exceeds the LifeTime:" << m_LifeTime;
          cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_TerminatingCyclicTrigger(sMessage,m_eventMessage.getMessage().c_str(),m_eventMessage.getHeatID().c_str(),m_eventMessage.getTreatID().c_str());

          // inform parent class and set terminate flag of thread
          terminate();
        }

        m_elapsedTime = 0 ;
      }

      if ( !getTerminateThread() )
      {
        sleep(checkTime);
        m_elapsedTime += checkTime;
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }

}


//##ModelId=42BAA990020F
void CCyclicTriggerCall::CCyclicTrig::update(CEventMessage& Event)
{
  logThreadInformation("updating thread");

  // updating stored event information with actual data !
  m_eventMessage.setDataKey(Event.getDataKey());
}


//##ModelId=44E34307020C
std::string CCyclicTriggerCall::CCyclicTrig::getCurrentThreadId()
{
  std::stringstream Message;
  Message << GetCurrentThreadId() ;

  return Message.str();
}

//##ModelId=44E343070235
void CCyclicTriggerCall::CCyclicTrig::terminate()
{
  // indicate CCyclicTriggerCall(parent) as terminated
  m_Parent->setTerminated(true);

  // indicate thread itself as terminated
  // flag will be checked at performWorkingStep
  setTerminateThread();
}

//##ModelId=44E343070217
void CCyclicTriggerCall::CCyclicTrig::logThreadInformation(const std::string& Message)
{
  std::stringstream LogMessage;
  LogMessage << Message << " thread " << getCurrentThreadId() ;
  cCBS_StdLog_Task::getInstance()->log(LogMessage.str(),2);
}


//##ModelId=44E3444C01B8
void CCyclicTriggerCall::setLifeTime(long value)
{
	m_pTrig->m_LifeTime = value;

  std::stringstream Message;
  Message << "Set lifetime: " << m_pTrig->m_LifeTime;
  cCBS_StdLog_Task::getInstance()->log(Message.str(),2);
}


//##ModelId=44E3444B02CD
long CCyclicTriggerCall::getLifeTime()
{
	return m_pTrig->m_LifeTime;
}


//##ModelId=44E3417600B1
void CCyclicTriggerCall::updateActionTime(CDateTime& value)
{
	m_pTrig->m_LastActionTime = value;
}

//##ModelId=44E3418702C3
CDateTime& CCyclicTriggerCall::getLastActionTime()
{
	return m_pTrig->m_LastActionTime;
}

//##ModelId=44E5C8B5031C
bool CCyclicTriggerCall::isTerminated()
{
  return m_Terminated;
}

//##ModelId=44E5C8B50330
void CCyclicTriggerCall::setTerminated(bool _t)
{
  m_Terminated = _t;
}

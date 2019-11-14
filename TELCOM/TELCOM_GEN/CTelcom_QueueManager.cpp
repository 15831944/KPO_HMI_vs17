// Copyright (C) 2007 SMS Siemag AG

#include "CTelcom_Msg.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "CTelcom_QueueMonitoringTask.h"
#include "CTelcom_MsgConverter.h"
#include "CTelcom_MsgTypeTranslator.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDateTime.h"
#include "cCBS_ThreadSleep.h"

#include "CTelcom_QueueManager.h"

void CTelcom_QueueManager::open(const std::string& name)
{
  m_Queue.clear();
  m_MsgConverter->setMsgTypeTranslator(m_pMsgTypeTranslator);
}

void CTelcom_QueueManager::close()
{
  // delete objects
  int s = m_Queue.size();
  for (int i=0; i<s; i++)
    delete m_Queue.at(i);
  // remove all stuff from our queue
  m_Queue.clear();
}

void CTelcom_QueueManager::enqueue(TCMessage &msg)
{
  std::stringstream Message;
  Message << "Unexpected call to CTELCOM_QTransport::enqueue(TCMessage&)";
  cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
}

int CTelcom_QueueManager::dequeue(TCMessage& msg, int seconds)
{
  cCBS_StdLog_Task::getInstance()->log(" ++++ CTelcom_QueueManager::dequeue",5);

  int status = 0;
  int retVal = OK;
  if (m_Queue.empty())
  {
    // wait as long as not woken up or after seconds time
    status = m_Event.wait(seconds * 1000);
  }

  if (2 == status) // time out
  {
    retVal = TIMEOUT;
  }
  else if (0 == status) // waiked up after raise in enqueue a message
  {
    //to get a pause between two telegrams, that are not a watchdog, add a pause here
    cCBS_ThreadSleep().sleep(m_sendPause);

    m_Section.lock();// have queue own access

    try
    {
      m_Event.reset(); //make redy to go to sleep (m_Event.wait(seco)

      //------------------------------------------------
      // do something on the queue

      if ( m_MsgConverter->fillTCMessage(m_Queue.back(), msg) )
      {
        std::string SendTlgName = m_Queue.back()->getTlg()->getId();

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TelegramHandled(sMessage,SendTlgName.c_str(),"");
      }
      else
      {
        std::string SendTlgName = m_Queue.back()->getTlg()->getId();
        
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingTelegram(sMessage,SendTlgName.c_str(),"");
      }


      delete m_Queue.back();
      m_Queue.pop_back();

      CTelcom_QueueMonitoringTask::getInstance()->m_QueueSize = m_Queue.size();
    }
    catch(...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"Unknown", "CTelcom_QueueManager::dequeue()","");
    }

    //------------------------------------------------
    // give free
    m_Section.unlock();
  }
  return retVal;
}

void CTelcom_QueueManager::enqueueTelcomMsg(CTelcom_Msg* Msg)
{
  try
  {
    m_Section.lock(); // block the queue

    //------------------------------------------------
    // delete one if maximum size achieved
    if (m_MaxQueueSize != 0 && (long)m_Queue.size() >= m_MaxQueueSize)
    {
      std::string LostTlgName;
      LostTlgName = m_Queue.back()->getType();
      delete m_Queue.back();
      m_Queue.pop_back();

      m_LostMessages ++;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_LostTelegramInQueue(sMessage,
                                        CTelcom_QueueMonitoringTask::getInstance()->getReciver().c_str(),
                                        cCBS_StdInitBase::getInstance()->m_ServerName.c_str(),
                                        LostTlgName.c_str());

      // to see monitoring data in task viewer
      CDateTime Now;
      CTelcom_QueueMonitoringTask::getInstance()->m_LostMessages = m_LostMessages;
      CTelcom_QueueMonitoringTask::getInstance()->m_LostMessageTimestamp = Now.asString();
    }

    // put message into queue
    m_Queue.push_front(Msg);

    // to see monitoring data in task viewer
    CTelcom_QueueMonitoringTask::getInstance()->m_QueueSize = m_Queue.size();
    CTelcom_QueueMonitoringTask::getInstance()->m_LastMessage = Msg->getType();

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown", "CTelcom_QueueManager::enqueueTelcomMsg()","");
  }

  //------------------------------------------------
  m_Event.raise();    // wake up waiting thread
  m_Section.unlock(); // allow access to queue
}

CTelcom_QueueManager::CTelcom_QueueManager() 
: m_LostMessages(0)
, m_MaxQueueSize(0)
, m_sendPause(0)
{
  m_MsgConverter = new CTelcom_MsgConverter();

  std::string localFormat  = "CSV";
  std::string remoteFormat = "FEL";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("sprot","localFormat",localFormat);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("sprot","remoteFormat",remoteFormat);
  m_MsgConverter->setLocalFormat(localFormat);
  m_MsgConverter->setRemoteFormat(remoteFormat);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("queuetransport","max_queue_size",m_MaxQueueSize);
  long sendPause = m_sendPause;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("queuetransport","sendPause",sendPause);
  m_sendPause = sendPause;
}

CTelcom_QueueManager::~CTelcom_QueueManager()
{
  close();
}

void CTelcom_QueueManager::setProtocol(Prot* value)
{
	m_pProtocol = value;
}

void CTelcom_QueueManager::setMsgTypeTranslator(CTelcom_MsgTypeTranslator* value)
{
	m_pMsgTypeTranslator = value;
}


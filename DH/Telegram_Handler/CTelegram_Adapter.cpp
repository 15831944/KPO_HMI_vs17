// Copyright (C) 2011 SMS Siemag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "CSMC_EventLogFrameController.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "CTelegram_Handler.h"
#include "CTelegram_Adapter.h"


bool CTelegram_Adapter::doOnComplete(const std::string& Key, const std::string& TlgName)
{
  vector<CTelegram_Handler*>::iterator it;
  bool TlgHandled = false;

  if ( checkTelegramFrequence(TlgName) )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_HandlingTelegramData(sMessage,TlgName.c_str());

    for ( it = m_Telegram_Handler_List.begin(); it != m_Telegram_Handler_List.end(); it++)
    {
      if (true == (*it)->doOnComplete(Key, TlgName))
      {
        TlgHandled = true;
        break;
      }
    }
  }
  return TlgHandled;
}

bool CTelegram_Adapter::registerHandler(CTelegram_Handler* NewHandler)
{
  NewHandler->assignTelegramAdapter(this);
  m_Telegram_Handler_List.push_back(NewHandler);
  return true;
}

CTelegram_Adapter::CTelegram_Adapter(CSMC_DataProvider_Impl *pIntf_IN, CSMC_DataProvider_Impl *pIntf_OUT, cCBS_StdFrame_Task *pTask)
: m_pEvent_Task(0)
, m_pIntf_IN(pIntf_IN)
, m_pIntf_OUT(pIntf_OUT)
, m_pTask(pTask)
{
  m_pEvent_Task = cCBS_StdEvent_Task::getInstance();

  m_SenderName  = cCBS_StdInitBase::getInstance()->m_ServerName;
  m_DestinationName  = "DM";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "SenderName", m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationName", m_DestinationName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage", "DestinationList", m_DestinationList);

  std::string TaskName = m_pTask->getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName",m_DestinationName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationList",m_DestinationList);
}

CTelegram_Adapter::~CTelegram_Adapter()
{
}


void CTelegram_Adapter::log(const std::string& message, long Level)
{
  if (m_pEvent_Task)
  {
    m_pEvent_Task->log(message, Level);
  }
}

void CTelegram_Adapter::addTelegram_DataProfile(const std::string& TelegramID)
{
  CTelegram_DataProfile *pTelegram_DataProfile = new CTelegram_DataProfile(TelegramID);
  m_Telegram_DataProfile_List.insert( std::pair<std::string,CTelegram_DataProfile*>(TelegramID,pTelegram_DataProfile));
}


bool CTelegram_Adapter::checkTelegramFrequence(const std::string& TelegramID)
{
  bool RetValue = true;

  map<std::string,CTelegram_DataProfile*>::iterator it;

  it = m_Telegram_DataProfile_List.find(TelegramID);
  if ( it == m_Telegram_DataProfile_List.end() ) 
  {
    addTelegram_DataProfile(TelegramID);
  }
  else
  {
    RetValue = it->second->check();
  }

  return RetValue;


}

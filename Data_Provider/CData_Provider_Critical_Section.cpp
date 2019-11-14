// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CData_Provider_Critical_Section.h"

CData_Provider_Critical_Section::~CData_Provider_Critical_Section()
{
  m_Section.unlock();
}

CData_Provider_Critical_Section::CData_Provider_Critical_Section()
: m_Locked(false)
{
}

CData_Provider_Critical_Section::CData_Provider_Critical_Section(const std::string& scope, bool lock /*= true*/)
: m_Locked(false)
{
  if (lock)
  {
    if (0 == m_Section.lock())
      m_Locked = true;
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_MutexAccessError(Message, m_ProviderName.c_str(), GetCurrentThreadId(),scope.c_str());

      m_Locked = false;
    }
  }
}

bool CData_Provider_Critical_Section::isLocked()
{
  return m_Locked;
}

bool CData_Provider_Critical_Section::tryLock(const std::string& scope)
{
  if (m_Section.tryLock())
    return true;
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_MutexAccessError(Message, m_ProviderName.c_str(), GetCurrentThreadId(),scope.c_str());

    return false;
  }
}

bool CData_Provider_Critical_Section::unlock(const std::string& scope)
{
  if (0 == m_Section.unlock())
    return true;
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_MutexFreeError(Message, GetCurrentThreadId(),scope.c_str());
  }
  return false;
}

bool CData_Provider_Critical_Section::lock(const std::string& scope)
{
  if (0 == m_Section.lock())
    return true;
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_MutexAccessError(Message, m_ProviderName.c_str(), GetCurrentThreadId(),scope.c_str());

    return false;
  }
}

void CData_Provider_Critical_Section::setProviderName(const std::string& providerName)
{
  m_ProviderName = providerName;
}


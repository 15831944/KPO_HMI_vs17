// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLogHandler.h"
#include "cCBS_StdLogHandlerAdapter.h"

//##ModelId=411A42B101BF
void cCBS_StdLogHandlerAdapter::registerLogHandler(cCBS_StdLogHandler* MessageHandler)
{
  m_LogMessageHandlerList.push_back(MessageHandler);
}

void cCBS_StdLogHandlerAdapter::log(const std::string& Message, long Level)
{
  try
  {
    std::vector<cCBS_StdLogHandler*>::iterator it;

    if (!m_LogMessageHandlerList.empty())
    {
      for ( it = m_LogMessageHandlerList.begin() ; it != m_LogMessageHandlerList.end() ; ++it)
      {
        (*it)->log(Message, Level);
      }
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message,"","cCBS_StdLogHandlerAdapter::log()","Log Message");
  }

}

std::vector<cCBS_StdLogHandler*> cCBS_StdLogHandlerAdapter::getLogHandler() const
{
  return m_LogMessageHandlerList;
}


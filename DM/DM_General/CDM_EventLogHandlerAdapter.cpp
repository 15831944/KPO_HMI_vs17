// Copyright (C) 2004 SMS Demag AG

#include "CDM_EventLogHandler.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_EventLogHandlerAdapter.h"
#include "cCBS_StdEventLogFrameController.h"



void CDM_EventLogHandlerAdapter::registerEventLogHandler(CDM_EventLogHandler* EventLogHandler)
{
	m_EventLogHandlerlist.push_back(EventLogHandler);
}

bool CDM_EventLogHandlerAdapter::EventLog(CEventMessage& Event)
{
  bool RetValue = false;

  try
  {
    std::vector<CDM_EventLogHandler*>::iterator it;

    if (!m_EventLogHandlerlist.empty())
    {
      for ( it = m_EventLogHandlerlist.begin() ; it != m_EventLogHandlerlist.end() ; ++it)
      {
        RetValue = (*it)->EventLog(Event);
        if ( RetValue )
        {
          break;
        }
      }
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventLogHandlerAdapter::EventLog()",
                                         "");
  }

  return RetValue;

}


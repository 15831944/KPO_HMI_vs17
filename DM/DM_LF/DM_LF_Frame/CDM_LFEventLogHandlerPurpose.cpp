// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_LFTask.h"
#include "CSMC_EventLogLFController.h"
#include "CDM_LFEventLogHandlerPurpose.h"

bool CDM_LFEventLogHandlerPurpose::EventLog(CEventMessage& Event)
{
  std::string Message = Event.getMessage();
  std::string ProductID = Event.getProductID();
  bool retValue  = false;

  if (m_pDataInterface)
  {

    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();

    if ( Message == LF_EvMsg::evLFHandleUpdatePurpose )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HandleUpdatePurpose(sMessage);

      retValue = true;
    }
  }
  return retValue;
}

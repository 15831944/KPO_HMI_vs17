// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_LFTask.h"
#include "CSMC_EventLogLFController.h"
#include "CDM_LFEventLogHandlerModelResults.h"

bool CDM_LFEventLogHandlerModelResults::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {
    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();

    if( Message == LF_EvMsg::evLFModelResultCode )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultCode(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFModelResultActualSetpoints )

    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultActualSetPoints(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFModelResultRecipeSetpoints )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultRecipeSetPoints(sMessage);
    }
    else
    {
      RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
    }
  }
  return RetValue;
}

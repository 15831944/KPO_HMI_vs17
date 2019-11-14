// Copyright (C) 2005 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_EAFTask.h"
#include "CSMC_EventLogEAFController.h"
#include "CDM_EAFEventLogHandlerModelResults.h"


bool CDM_EAFEventLogHandlerModelResults::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {

    CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();

    if( Message == EAF_EvMsg::evEAFModelResultCode )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultCode(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFModelResultActualSetpoints )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultActualSetPoints(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFModelResultRecipeSetpoints )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultRecipeSetPoints(sMessage);
    }
    else
      RetValue = false;
  }
  return RetValue;
}


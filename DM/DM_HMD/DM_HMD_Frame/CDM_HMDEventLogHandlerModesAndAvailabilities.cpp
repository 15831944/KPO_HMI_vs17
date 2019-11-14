// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerModesAndAvailabilities.h"

//##ModelId=45139A720114
bool CDM_HMDEventLogHandlerModesAndAvailabilities::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {
    CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
  
    if( Event.getMessage() == HMD_EvMsg::evHMDSetComputerModeOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ComputerModeOn(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDSetComputerModeOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ComputerModeOff(sMessage);
    }
    else
      RetValue = false;
  }
  else
    RetValue = false;

  return RetValue;
}

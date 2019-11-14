// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerMaterial.h"
#include "CIntfData.h"


//##ModelId=45139A720128
bool CDM_HMDEventLogHandlerMaterial::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {
    CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();

    if ( Event.getMessage() == HMD_EvMsg::evHMDChangePhysicalMatAvailibility ||
         Event.getMessage() == HMD_EvMsg::evHMDMaterialAvailability )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangePhysicalMatAvailibility(sMessage,
        m_pDataInterface->getString(DataKey,DATA::MatCode).c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHandleUpdatePurpose )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HandleUpdatePurpose(sMessage);
    }
  
    else
      RetValue = false;
  }
  else
    RetValue = false;

  return RetValue;
}


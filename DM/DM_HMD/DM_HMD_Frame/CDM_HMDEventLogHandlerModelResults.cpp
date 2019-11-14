// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerModelResults.h"

//##ModelId=45139A72011E
bool CDM_HMDEventLogHandlerModelResults::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = getExternalHeatID(ProductID);
  std::string TreatID   = getExternalTreatID(ProductID);


  if (m_pDataInterface)
  {
    CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();

    if( Event.getMessage() == HMD_EvMsg::evHMDModelResultCode )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResultCode(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDModelResult )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ModelResult(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatAnnounceStatus )
    {
      std::string HeatAnnounceStatus = m_pDataInterface->getString(Event.getDataKey(),DATA::HeatAnnounceStatus);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnounceStatus(sMessage, HeatAnnounceStatus.c_str(), HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatAnnounceStatusOffline )
    {
      std::string HeatAnnounceStatusOffline = m_pDataInterface->getString(Event.getDataKey(),DATA::HeatAnnounceStatus);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnounceStatus(sMessage, HeatAnnounceStatusOffline.c_str(), HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else
      RetValue = false;
  }
  else
    RetValue = false;


  return RetValue;
}

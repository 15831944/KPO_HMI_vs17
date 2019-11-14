// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerSignalsAndMeasurements.h"

//##ModelId=45139A7200FF
bool CDM_HMDEventLogHandlerSignalsAndMeasurements::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = getExternalHeatID(ProductID);
  std::string TreatID   = getExternalTreatID(ProductID);

  if (m_pDataInterface)
  {
    CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
  
    if ( Event.getMessage() == HMD_EvMsg::evHMDDeslaggingStart )
    {
      CDateTime DeslagStartTime;
      DeslagStartTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DeslagStartTime);
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeslaggingStart(sMessage,
        DeslagStartTime.asString().c_str(),
        m_pDataInterface->getString(DataKey,DATA::DeslaggingStatus).c_str()  );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDDeslaggingEnd )
    {
      CDateTime DeslagEndTime;
      DeslagEndTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DeslagEndTime);
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeslaggingEnd(sMessage, DeslagEndTime.asString().c_str() );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDTempMeasurement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TempMeasurement(sMessage,
        m_pDataInterface->getDouble(DataKey,DATA::MeasTemp));
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPowderBlowingStart)
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_InjectionLanceBlowingStart(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPowderBlowingEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_InjectionLanceBlowingStop(sMessage );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDApplicationSystemRestart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ApplicationSystemRestart(sMessage );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDChangeAimData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeAimData(sMessage );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDUpdateAimDepartureTime )
    {
      CDateTime TreatEndAimTime;
      TreatEndAimTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::TreatEndAim);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeAimDepartureTime(sMessage, TreatEndAimTime.asString().c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDCreateTreatmentID )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CreateTreatmentID(sMessage );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDDelayStatus )
    {
      CDateTime DelayStartTime, DelayEndTime;
      DelayStartTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DelayStartDate);
      DelayEndTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DelayEndDate);
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DelayStatus(sMessage,
        m_pDataInterface->getString(DataKey,DATA::DelayPlant).c_str(),
        m_pDataInterface->getString(DataKey,DATA::DelayCode).c_str(),
        DelayStartTime.asString().c_str(),
        DelayEndTime.asString().c_str(),
        m_pDataInterface->getString(DataKey,DATA::DelayDescription).c_str()  );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatAnnouncement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncement(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
		  m_pDataInterface->getString(DataKey,DATA::LadleNo).c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatAnnouncementOffline )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncementOffline(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str(), 
		  m_pDataInterface->getString(DataKey,DATA::LadleNo).c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatCancellation )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatCancellation(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str() );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatDeparture )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatDeparture(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str() );
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatStart(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseMonoInjectionCarbideEnd(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseMonoInjectionCarbideStart(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseMonoInjectionContinued )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseMonoInjectionContinued(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseMonoInjectionLimeEnd(sMessage);
    }
		else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseCoInjectionMagnesiumStart(sMessage);
    }
		else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseCoInjectionMagnesiumEnd(sMessage);
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PhaseMonoInjectionLimeStart(sMessage);
    }
    else
      RetValue = false;
  }
  else
    RetValue = false;

  return RetValue;
}

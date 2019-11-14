// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CDataConversion.h"
#include "CDateTime.h"
#include "CSMC_EventLogEAFController.h"
#include "CIntfData.h"
#include "CDM_EAFEventLogHandlerTreatmentManagement.h"

bool CDM_EAFEventLogHandlerTreatmentManagement::EventLog(CEventMessage& Event)
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

    CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();

    if ( Message == EAF_EvMsg::evEAFHeatAnnouncement )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncement(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHeatAnnouncementOffline )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncementOffline(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHeatCancellation )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatCancellation(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFHeatDeparture )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatDeparture(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFHeatStart )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatStart(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFDelayStatus )
    {
      CDateTime dStartTime,dEndTime;

      dStartTime.SetTime(m_pDataInterface->getDate(DataKey.c_str(), DATA::DelayStartDate));
      dEndTime.SetTime  (m_pDataInterface->getDate(DataKey.c_str(), DATA::DelayEndDate));

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DelayStatus(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::DelayPlant),      "-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::DelayCode),       "-").c_str(),
        CDataConversion::SetInvalidToDefault(dStartTime,                                                 "-").c_str(),
        CDataConversion::SetInvalidToDefault(dEndTime,                                                   "-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::DelayDescription),"-").c_str() );
    }
    else if ( Message == EAF_EvMsg::evEAFHeatScheduleUpdate )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatScheduleUpdate(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeAimData )
    { 
      CDateTime TreatEndAimTime;
      TreatEndAimTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::TreatEndAim);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeAimData(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SteelGradeCode),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::TempAim),"-").c_str(),
        CDataConversion::SetInvalidToDefault(TreatEndAimTime,"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::AimWeight),"-").c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeHotHeelData )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeHotHeelData(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeTapLadleData )
    {
      std::string statusVal;      
      long nLadleNO;
      statusVal = CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleStatus),"-");
      nLadleNO = m_pDataInterface->getLong(DataKey,DATA::LadleNo);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeTapLadleData(sMessage,
        CDataConversion::LongToString(nLadleNO).c_str(),
        statusVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFSteelGradeChanged )
    {
      std::string SteelGrade  = m_pDataInterface->getString(Event.getDataKey(), DATA::SteelGradeCode);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SteelGradeChanged(sMessage,SteelGrade.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerElec )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerElec(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerInjection )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerInjection(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerOxygen )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerOxygen(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracDataBurner )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracDataBurnerOxygen(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerParameter )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerParameter(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerRestriction )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerRestriction(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFCreateTreatmentID )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CreateTreatmentID(sMessage);
    } 
    else if(Message == EAF_EvMsg::evEAFHeatEnd)
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatEnd(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if(Message == EAF_EvMsg::evEAFChangeThermalStatus)
    {
      std::string FurnaceStatus = CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::FurnaceStatus),"-");

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeEquipmentThermalStatus(sMessage,PlantID.c_str(),FurnaceStatus.c_str());
    }

    else
      RetValue = false;
  }
  return RetValue;
}


// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CSMC_EventLogLFController.h"
#include "CIntfData.h"
#include "CDM_LFEventLogHandlerTreatmentManagement.h"
#include "CDataConversion.h"

bool CDM_LFEventLogHandlerTreatmentManagement::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  std::string PlantID   = Event.getPlantID();
  std::string HeatID    = getExternalHeatID(ProductID);
  std::string TreatID   = getExternalTreatID(ProductID);

  if (m_pDataInterface && 
      m_pPlantManagementInterface && 
      m_pProductManagementInterface)
  {
    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();

    if ( Message == LF_EvMsg::evLFHeatAnnouncement )
    {  
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncement(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
                                     m_pProductManagementInterface->getString(ProductID,DATA::LadleTransferCarId).c_str(),
                                    (m_pDataInterface->getString(DataKey,DATA::LadleType) + 
                                    CDataConversion::IntToString(m_pDataInterface->getLong(DataKey,DATA::LadleNo))     ).c_str() );
    }

    else if ( Message == LF_EvMsg::evLFHeatAnnouncementOffline )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnouncementOffline(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
                                     m_pProductManagementInterface->getString(ProductID,DATA::LadleTransferCarId).c_str(),
                                    (m_pDataInterface->getString(DataKey,DATA::LadleType) + 
                                     CDataConversion::IntToString(m_pDataInterface->getLong(DataKey,DATA::LadleNo))     ).c_str() );
    }

    else if ( Message == LF_EvMsg::evLFHeatCancellation )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatCancellation(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatDeparture )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatDeparture(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatStart(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatEnd )
    {
      // Just for fuxin, jspl,beause L1 sen heat end when car leave treamnetposition 
      //sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      //pEventLog->EL_HeatEnd(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }

    else if ( Message == LF_EvMsg::evLFDelayStatus )
    {
      CDateTime StartTime;//, EndTime;
      StartTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DelayStartDate);
      //EndTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DelayEndDate);

      //sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      //pEventLog->EL_DelayStatus(sMessage,
      //  m_pDataInterface->getString(DataKey,DATA::DelayPlant).c_str(),
      //  m_pDataInterface->getString(DataKey,DATA::DelayCode).c_str(),
      //  StartTime.asString().c_str(),
      //  EndTime.asString().c_str(),
      //  m_pDataInterface->getString(DataKey,DATA::DelayDescription).c_str()      );

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DelayStatus(sMessage,
        Event.getPlantID().c_str(),
        m_pDataInterface->getString(DataKey,DATA::DelayCode).c_str(),
        StartTime.asString().c_str(),"","");
    }
    else if ( Message == LF_EvMsg::evLFChangeAimData )
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
    else if ( Message == LF_EvMsg::evLFSteelGradeChanged )
    {
      std::string SteelGrade  = m_pDataInterface->getString(Event.getDataKey(), DATA::SteelGradeCode);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SteelGradeChanged(sMessage,SteelGrade.c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerElec )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerElec(sMessage,
        m_pDataInterface->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerParameter )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerParameter(sMessage,
        m_pDataInterface->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerRestriction )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerRestriction(sMessage,
        m_pDataInterface->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFChangeProdPracPointerStirring )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeProdPracPointerStirring(sMessage,
        m_pDataInterface->getString(DataKey,DATA::ProdPracPointer).c_str());
    }
    else if ( Message == LF_EvMsg::evLFFinalHeating )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_FinalHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFInitialHeating )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_InitialHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFMainHeating )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MainHeating(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFCreateTreatmentID )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CreateTreatmentID(sMessage );
    }
    else
    {
      RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
    }
  }
  return RetValue;
}

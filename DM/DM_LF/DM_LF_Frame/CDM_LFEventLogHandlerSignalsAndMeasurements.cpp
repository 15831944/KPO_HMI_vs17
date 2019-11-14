// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_LFTask.h"
#include "CSMC_EventLogLFController.h"
#include "CDM_LFEventLogHandlerSignalsAndMeasurements.h"
#include "CIntfData.h"
#include "DEF_GC_COOLWATER.h"
#include "CDataConversion.h"

bool CDM_LFEventLogHandlerSignalsAndMeasurements::EventLog(CEventMessage& Event)
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

    if ( Message == LF_EvMsg::evLFElectrodesInOperatingPosition )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ElectrodesInOperatingPosition(sMessage );
    }
    else if ( Message == LF_EvMsg::evLFFurnaceBreakerOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_FurnaceBreakerOn(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFFurnaceBreakerOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_FurnaceBreakerOff(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFPowerOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PowerOn(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFPowerOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PowerOff(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFTapChangeStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TapChangeStart(sMessage,
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::VoltTapNo),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ElectrodRegCurve),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFTapChangeFinished )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TapChangeFinished(sMessage,
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::VoltTapNo),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ElectrodRegCurve),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFImpCurveChanged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TapChangeFinished(sMessage,
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::VoltTapNo),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ElectrodRegCurve),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFCeloxMeasurement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CeloxMeasurement(sMessage,
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasCarbonConc),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasAlConc),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleId),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasTemp),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasO2Conc),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFSlagCeloxMeasurement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SlagCeloxMeasurement(sMessage,
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasFeOConc),"-").c_str(),
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasMnOConc),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFTempMeasurement )
    {
      std::string strVal;      
      long LadleCarPosition  = CDataConversion::SetInvalidToDefault(m_pDataInterface->getLong(DataKey,DATA::LadleCarPosition),DEF_CARPOSITION::OutOfOperatingPosition);
      long SampleNo          = CDataConversion::SetInvalidToDefault(m_pDataInterface->getLong(DataKey,DATA::SampleNo),-1);

      if(LadleCarPosition == DEF_CARPOSITION::OperationPositon)
        strVal="In Operating Position";
      else if(LadleCarPosition == DEF_CARPOSITION::DeslagPosition)
        strVal="In Deslaging Position";
      else if(LadleCarPosition == DEF_CARPOSITION::OutOfOperatingPosition)
        strVal="Out of Operating Position and Deslagging Position";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TempMeasurement(sMessage, 
      CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasTemp),"-").c_str(),
      SampleNo,
      strVal.c_str() );
    }
    else if ( Message == LF_EvMsg::evLFDeslaggingData )
    {
      std::string strVal;      
      long LadleCarPosition = CDataConversion::SetInvalidToDefault(m_pDataInterface->getLong(DataKey,DATA::LadleCarPosition),DEF_CARPOSITION::OutOfOperatingPosition);

      if(LadleCarPosition == DEF_CARPOSITION::OperationPositon)
        strVal="In Operating Position";
      else if(LadleCarPosition == DEF_CARPOSITION::DeslagPosition)
        strVal="In Deslaging Position";
      else if(LadleCarPosition == DEF_CARPOSITION::OutOfOperatingPosition)
        strVal="Out of Operating Position and Deslagging Position";

      CDateTime DesaggingStartTime, DesaggingEndTime;
      DesaggingStartTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DeslagStartTime);
      DesaggingEndTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::DeslagEndTime);
      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeslaggingData(sMessage,
        DesaggingStartTime.asString().c_str(),
        DesaggingEndTime.asString().c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId),"-").c_str(),
        strVal.c_str(),
        (CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleType),"-") + 
         CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleNo),"-")     ).c_str() );
    }
    else if ( Message == LF_EvMsg::evLFBottomStirringByPassOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BottomStirringByPassOn(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadlePlugNo),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFBottomStirringByPassOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BottomStirringByPassOff(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadlePlugNo),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFBottomStirringStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BottomStirringStart(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId),"-").c_str(),
         CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::StirringGasType),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadlePlugNo),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFBottomStirringEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BottomStirringEnd(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::StirringGasType),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::LadlePlugNo),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFHeatAnnounceStatus )
    {
      std::string strVal;      
      long statusVal = CDataConversion::SetInvalidToDefault(m_pDataInterface->getLong(DataKey.c_str(),DATA::HeatAnnounceStatus),-1);

      if (statusVal == 0)
        strVal="Announcement not successful";
      else 
        strVal="Announcement successfull";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HeatAnnounceStatus(sMessage,strVal.c_str(),HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }

    else if ( Message == HMI_EvMsg::evHMISetUpOfHeat )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HMISetUpOfHeat(sMessage );
    }
    else if ( Message == HMI_EvMsg::evHMIResetOfHeat )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HMIResetOfHeat(sMessage );
    }
    else if ( Message == LF_EvMsg::evLFParameterUpdate )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ParameterUpdate(sMessage,
        m_pDataInterface->getString(DataKey,DATA::ParamName).c_str(),
        m_pDataInterface->getString(DataKey,DATA::ParamValue).c_str());
    }
    else if ( Message == GEN_EvMsg::evGenParameterUpdate )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ParameterUpdate(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ParaArea),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == LF_EvMsg::evLFCooling )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CoolingStirring(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFCleanlinessStirring )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CleanlinessStirring(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFSoftStirring )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SoftStirring(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFTrimmingMaterialDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TrimmingMaterialDischarged(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFAlloyingMaterialDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_AlloyingMaterialDischarged(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFGantrySwungOut )
    {
      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_GantryOutTreatmentPosition(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFMaintenance )
    {
      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_GantryInMaintenancePosition(sMessage);
    }
    // is handled in plant manager
    //
    //else if ( Message == LF_EvMsg::evLFGantrySwungIn )
    //{
    //  std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);
    //  long GantryPosIn                = m_pDataInterface->getLong(Event.getDataKey()  , DATA::GantryPosIn);

    //  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    //  pEventLog->EL_GantryInTreatmentPosition(sMessage,GantryPosIn,LadleTransferCarId.c_str());
    //}
    // is handled in plant manager
    //
    else if ( Message == LF_EvMsg::evLFTransferCarPositionChanged )
    {
      std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);
      long LadleCarPosition           = m_pDataInterface->getLong(Event.getDataKey()  , DATA::LadleCarPosition);
     
      // switch LadleTransferCarInOperatingPosition to new CarID
      // reset if TransferCar leaves operatin position 
      if ( LadleCarPosition == DEF_CARPOSITION::OperationPositon )
      {
        CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TransferCarInOperationPos(sMessage,LadleTransferCarId.c_str());
      }
      else
      {
        CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TransferCarOutOfOperationPos(sMessage,LadleTransferCarId.c_str());
      }
    }
    //else if ( Message == LF_EvMsg::evLFRoofArrivesInUpPosition )
    //{
    //  std::string LadleTransferCarId = m_pDataInterface->getString(DataKey, DATA::LadleTransferCarId);

    //  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
    //                                  CDM_LFTask::getInstance()->getProcessState(ProductID)
    //                                  ,ProductID,CDM_LFTask::getInstance()->getExternalHeatID(ProductID));
    //  pEventLog->EL_RoofArrivesInUpPosition(sMessage, LadleTransferCarId.c_str());
    //}
    //else if ( Message == LF_EvMsg::evLFRoofArrivesInDownPosition )
    //{
    //  std::string LadleTransferCarId = m_pDataInterface->getString(DataKey, DATA::LadleTransferCarId);

    //  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,
    //                                  CDM_LFTask::getInstance()->getProcessState(ProductID)
    //                                  ,ProductID,CDM_LFTask::getInstance()->getExternalHeatID(ProductID));
    //  pEventLog->EL_RoofArrivesInDownPosition(sMessage, LadleTransferCarId.c_str());
    //}

    else
    {
      RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
    }
  }
  return RetValue;
}


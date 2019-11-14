// Copyright (C) 2005 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"

#include "CDateTime.h"
#include "CDM_EAFTask.h"
#include "CIntfData.h"
#include "CDataConversion.h"

#include "CSMC_EventLogEAFController.h"

#include "CDM_EAFEventLogHandlerSignalsAndMeasurements.h"


bool CDM_EAFEventLogHandlerSignalsAndMeasurements::EventLog(CEventMessage& Event)
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

    if ( Message == EAF_EvMsg::evEAFLadleStirringStart )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LadleStirringStart(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFLadleStirringStop )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LadleStirringStop(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFBurnerStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BurnerStart(sMessage);
    }

    else if ( Message == EAF_EvMsg::evEAFBurnerStop )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BurnerStop(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFElectrodesInOperatingPosition )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ElectrodesInOperatingPosition(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFElectrodesOutOperatingPosition )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ElectrodesOutOfOperatingPosition(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFFurnaceBreakerOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_FurnaceBreakerOn(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFFurnaceBreakerOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_FurnaceBreakerOff(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFPowerOn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PowerOn(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFPowerOff )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_PowerOff(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFTapChangeStart )
    {
      std::string statusVal, strVal;      
      statusVal = CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::FurnTapChangOn),"-");
      long nReactTapNo = m_pDataInterface->getLong(DataKey,DATA::ReactTapNo);
      long nTapNo      = m_pDataInterface->getLong(DataKey,DATA::VoltTapNo);
      long nCurveNo    = m_pDataInterface->getLong(DataKey,DATA::ElectrodRegCurve);

      if (statusVal=="1")
        strVal="Tap Change On";
      else 
        strVal="Tap Change Off";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TapChangeStart(sMessage,
        (CDataConversion::LongToString(nReactTapNo)).c_str(),
        (CDataConversion::LongToString(nTapNo)).c_str(),
        (CDataConversion::LongToString(nCurveNo)).c_str(),
        strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFTapChangeFinished )
    {
      std::string statusVal, strVal;      
      statusVal = CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::FurnTapChangOn),"-");
      long nReactTapNo = m_pDataInterface->getLong(DataKey,DATA::ReactTapNo);
      long nTapNo = m_pDataInterface->getLong(DataKey,DATA::VoltTapNo);
      long nCurveNo = m_pDataInterface->getLong(DataKey,DATA::ElectrodRegCurve);

      if (statusVal=="1")
        strVal="Tap Change On";
      else 
        strVal="Tap Change Off";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TapChangeFinished(sMessage,
        (CDataConversion::LongToString(nReactTapNo)).c_str(),
        (CDataConversion::LongToString(nTapNo)).c_str(),
        (CDataConversion::LongToString(nCurveNo)).c_str(),
        strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFElectrodeRegCurveNum )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ElectrodeRegCurveNum(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFManipGasLanceStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ManipGasLanceStart(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::GasLanceNo),"-").c_str() );
    }
    else if ( Message == EAF_EvMsg::evEAFManipGasLanceStop )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ManipGasLanceStop(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::GasLanceNo),"-").c_str() );

      seqGasLanceData GasLanceData = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(),DATA::GasLanceAmount));
      long seqLength = CIntfData::getLength(GasLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sGasLanceData sElement;
        CIntfData::getAt(sElement, GasLanceData,i);
      
        seqGasData GasData = sElement.LanceData;
        long seqLength2 = CIntfData::getLength(sElement.LanceData);
        
        for(int i=0;i<seqLength2;i++)
        {
          sGasData sElement2;
          CIntfData::getAt(sElement2, GasData,i);
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
          pEventLog->EL_ManipGasLanceStop(sMessage,
               sElement.Device, 
               sElement2.GasType,
               sElement2.GasValue);
        }
      }
    }
    else if ( Message == EAF_EvMsg::evEAFManipInjectLanceStart )
    {
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
        pEventLog->EL_ManipInjectLanceStart(sMessage, 
            sElement.Device,
            sElement.MatCode);
      }
    }
    else if ( Message == EAF_EvMsg::evEAFManipInjectLanceStop )
    {
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
        pEventLog->EL_ManipInjectLanceStop(sMessage, 
            sElement.Device,
            sElement.MatCode,
            sElement.Value);
      }
    }
    else if ( Message == EAF_EvMsg::evEAFBurnerStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BurnerStart(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFBurnerStop )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_BurnerStop(sMessage);
    }

    else if ( Message == EAF_EvMsg::evEAFTempMeasurement )
    {
      long SampleNo     = CDataConversion::SetInvalidToDefault(m_pDataInterface->getLong(DataKey,DATA::SampleNo),0);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TempMeasurement(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::MeasTemp),"-").c_str(),
        SampleNo );
    }
    else if ( Message == EAF_EvMsg::evEAFCeloxMeasurement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_CeloxMeasurement(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFOxygenMeasurement )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_OxygenMeasurement(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFDeslaggingStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeslaggingStart(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFDeslaggingEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeslaggingEnd(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFDoorOpened )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DoorOpened(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFDoorClosed )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DoorClosed(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFRoofArrivesInUpPosition )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RoofArrivesInUpPosition(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFRoofArrivesInDownPosition )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RoofArrivesInDownPosition(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFGantrySwungIn )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_GantrySwungIn(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFGantrySwungOut )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_GantrySwungOut(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFSetTappingMasses )
    {     
      std::string strVal = CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::TappingMass),"Filled with NetWeight");

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SetTappingMasses(sMessage,strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFTappingStart )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TappingStart(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFTappingEnd )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_TappingEnd(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFApplicationSystemRestart )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ApplicationSystemRestart(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFParameterUpdate )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ParameterUpdate(sMessage, 
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ParamName).c_str(),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::ParamValue).c_str(),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFCarbonInjectStart )
    {      
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
        pEventLog->EL_InjectionStart(sMessage, 
            sElement.Device,
            sElement.MatCode);
      }
    }
    else if ( Message == EAF_EvMsg::evEAFCarbonInjectStop )
    {      
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
        pEventLog->EL_InjectionStop(sMessage, 
            sElement.Device,
            sElement.MatCode,
            sElement.Value);
      }
    }
    else
      RetValue = false;
  }

	return RetValue;
}
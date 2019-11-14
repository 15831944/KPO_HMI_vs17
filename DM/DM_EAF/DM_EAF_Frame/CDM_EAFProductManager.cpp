// Copyright (C) 2004 SMS Demag AG

#include <iomanip>
#include <algorithm>

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "CEventMessage.h"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CSMC_EventLogFrameController.h"
#include "CProductID.h"
#include "CDataConversion.h"

#include "CGasLanceDataHandler.h"
#include "CInjectLanceDataHandler.h"

#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_TREATMENTPHASE_DEF.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GCE_INJECTION.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_CHARGE_DEST.h"

#include "CDM_StatusHandler.h"
#include "CStirringDataHandler.h"
#include "CDM_ProductManagementInterface_Impl.h"

#include "CDM_EAFTask.h"
#include "CDM_EAFProductManager.h"




CDM_EAFProductManager::~CDM_EAFProductManager()
{
}

CDM_EAFProductManager::CDM_EAFProductManager() 
: CDM_ProductManager("E")
{
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Electric);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::ElectricModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::GasLance);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::GasLanceModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Injection);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::InjectionModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Level2Error);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandleL1Error);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandleModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::RejectHeatL1);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Stirring);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::StirringModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Burner);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::BurnerModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::DynamicFeed);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::DynamicFeedModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::PatternFeed);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::PatternFeedModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::TappingBatch);

  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_1);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_2);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_3);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_4);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::DoorBurner);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::EBTBurner);

  m_GasLanceDeviceList.push_back(DEF_GCE_INJECTION::Oxygen_Injector_1);
  m_GasLanceDeviceList.push_back(DEF_GCE_INJECTION::Oxygen_Injector_2);

  m_GasTypeList.push_back(DEF_GCE_BURNER_GASTYPE::O2);
  m_GasTypeList.push_back(DEF_GCE_BURNER_GASTYPE::BG);
}

bool CDM_EAFProductManager::changeProductInformation(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pProductManagementInterface)
      {
        if ( Message == EAF_EvMsg::evEAFHeatAnnouncement )
        {
          CDateTime DateTime;
          CDateTime invDate (CDateTime::InvalidDateTime());

          resetProductManager(Event);

          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatAnnounceTime,DateTime.assDate());
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,invDate.assDate());
          m_pProductManagementInterface->setString(ProductID,DATA::ActPlantLocation,DEF_PLANT::Furnace);

          setTreatmentPosition(ProductID, DEF_GC_TRETMENTPOSITION::Furnace);

					std::vector<std::string> NameList;
					NameList.push_back(DATA::CustHeatID);
					NameList.push_back(DATA::CustTreatID);

					CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
																								m_pProductManagementInterface,
																								Event.getDataKey(),
																								ProductID,
																								NameList);

          m_pProductManagementInterface->showContent(ProductID,2);
          RetValue = true;
        }
        else if ( Message == EAF_EvMsg::evEAFHeatCancellation ||
                  Message == EAF_EvMsg::evEAFHeatDeparture )
        {
          m_pProductManagementInterface->setString(ProductID, DATA::ActPlantLocation, DEF_PLANT::TappingLadle);

          m_pProductManagementInterface->showContent(ProductID,2);

          RetValue = true;
        }
        else if ( Message == EAF_EvMsg::evEAFHeatStart )
        {
          CDateTime DateTime;
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());

          setTreatmentPosition(ProductID, DEF_GC_TRETMENTPOSITION::Furnace);

          RetValue = true;
        }
        else if ( Message == EAF_EvMsg::evEAFTappingStart )
        {
          setTreatmentPosition(ProductID, DEF_GC_TRETMENTPOSITION::TappingArea);

          RetValue = true;
        }
        else if ( Message == EAF_EvMsg::evEAFHeatEnd )
        {
          m_pProductManagementInterface->setString(ProductID, DATA::ActPlantLocation, DEF_PLANT::TappingArea);

          m_pProductManagementInterface->showContent(ProductID,2);

          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeSampleInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();

  std::string Plant = m_pDMTask->getPlantFromEventMessage(Event);

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface )
      {
        if ( Message == EAF_EvMsg::evEAFSteelSampleTaken )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Steel);
        }
        else if ( Message == EAF_EvMsg::evEAFSlagSampleTaken )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Slag);
        }
        else if ( Message == EAF_EvMsg::evEAFTempMeasurement )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Temp);
        }
        else if( Message == EAF_EvMsg::evEAFCeloxMeasurement )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Celox);
        }

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeAnalysisInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface )
      {
        if ( Message == EAF_EvMsg::evEAFSteelAnalysisReceived)
        {
          setAnalysisData(Event, DATA::SteelMeasAnalysis);
          RetValue = true;
        }
        else if ( Message == EAF_EvMsg::evEAFSlagAnalysisReceived)
        {
          setAnalysisData(Event, DATA::SlagMeasAnalysis);
          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeTappingData(CEventMessage& Event)
{
  bool RetValue = false;

  // store tapping times for Product 

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;
  try
  {
    if (m_pProductManagementInterface )
    {
      CDateTime Now;

      if ( Message == EAF_EvMsg::evEAFTappingStart )
      {
        m_pProductManagementInterface->setDate(ProductID.c_str(), DATA::TappingStartTime, Now.assDate() );

        m_pProductManagementInterface->setString(ProductID, DATA::ActPlantLocation, DEF_PLANT::TappingArea);

        m_pProductManagementInterface->showContent(ProductID,2);

        RetValue = true;
      }
      else if ( Message == EAF_EvMsg::evEAFSetTappingMasses )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::TappingMass);

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pProductManagementInterface,
                                             Event.getDataKey(),
                                             ProductID,
                                             NameList);
        RetValue = true;
      }
      else if ( Message == EAF_EvMsg::evEAFTappingEnd )
      {
        m_pProductManagementInterface->setDate(ProductID.c_str(), DATA::TappingEndTime, Now.assDate() );

        m_pProductManagementInterface->setString(ProductID, DATA::ActPlantLocation, DEF_PLANT::TappingArea);

        m_pProductManagementInterface->showContent(ProductID,2);

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeBurningData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID << ", " << DataKey;
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface)
    {

      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
      {
        seqGasLanceData ActBurnerFlow      = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerFlow));
        seqGasLanceData ActBurnerAmount    = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));

        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::BurnerFlow));
        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::BurnerAmount));

        // update product related data with actual values
        CGasLanceDataHandler BurnerFlowHandler      (BurnerFlow);
        CGasLanceDataHandler BurnerAmountHandler    (BurnerAmount);

        BurnerFlowHandler.update(ActBurnerFlow);
        BurnerAmountHandler.update(ActBurnerAmount);

        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::BurnerFlow          , BurnerFlowHandler.getGasLanceData());
        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::BurnerAmount        , BurnerAmountHandler.getGasLanceData());

        m_pProductManagementInterface->showContent(ProductID,4);

      }
      else if ( Message == EAF_EvMsg::evEAFBurnerStart || 
                Message == EAF_EvMsg::evEAFBurnerStop)
      {
        seqGasLanceData ActBurnerFlow      = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerFlow));
        seqGasLanceData ActBurnerAmount       = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));
        seqStatus       ActBurnerStatus       = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::BurnerStatus));

        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::BurnerFlow));
        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::BurnerAmount));
        seqStatus       BurnerStatus       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::BurnerStatus));

        CGasLanceDataHandler BurnerFlowHandler(BurnerFlow);
        BurnerFlowHandler.update(ActBurnerFlow);

        CGasLanceDataHandler BurnerAmountHandler(BurnerAmount);
        BurnerAmountHandler.update(ActBurnerAmount);

        CStatusHandler BurnerStatusHandler(BurnerStatus);
        BurnerStatusHandler.update(ActBurnerStatus);

        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::BurnerFlow          , BurnerFlowHandler.getGasLanceData());
        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::BurnerAmount        , BurnerAmountHandler.getGasLanceData());
        m_pProductManagementInterface->setStatus      (ProductID.c_str(), DATA::BurnerStatus        , BurnerStatusHandler.getStatusData());

        m_pProductManagementInterface->showContent(ProductID,4);

      }

      RetValue = true;

    } // if (m_pDataInterface && m_pProductManagementInterface)
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFProductManager::changeBurningData()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFProductManager::changeBurningData()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFProductManager::changeBurningData()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeStirringData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface)
      {
        // update dur since heat start and announce
        changeEventDataInformation(Event);

        if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
        {
          seqStirringData ActStirringFlow      = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringFlow));
          seqStirringData ActStirringAmount    = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringAmount));
          seqStirringData ActStirringPressure  = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringPressure));

          seqStirringData StirringFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringFlow));
          seqStirringData StirringAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
          seqStirringData StirringPressure     = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringPressure));

          // update product related data with actual values
          CStirringDataHandler StirringFlowHandler      (StirringFlow);
          CStirringDataHandler StirringAmountHandler    (StirringAmount);
          CStirringDataHandler StirringPressureHandler  (StirringPressure);

          StirringFlowHandler.update(ActStirringFlow);
          StirringAmountHandler.update(ActStirringAmount);
          StirringPressureHandler.update(ActStirringPressure);

          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringFlow          , StirringFlowHandler.getStirringData());
          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringAmount        , StirringAmountHandler.getStirringData());
          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringPressure      , StirringPressureHandler.getStirringData());

          m_pProductManagementInterface->showContent(ProductID,4);

        }
        else if ( Message == EAF_EvMsg::evEAFBottomStirringStart || 
                  Message == EAF_EvMsg::evEAFBottomStirringEnd)
        {
          seqStirringData ActStirringAmount       = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringAmount));
          seqStatus       ActStirringStatus       = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::StirringStatus));

          seqStirringData StirringAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
          seqStatus       StirringStatus       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::StirringStatus));

          seqStirringData StirringFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringFlow));

          CStatusHandler StirrStatusHandlerDevice(ActStirringStatus);

          CStirringDataHandler StirringAmountHandler(StirringAmount);
          StirringAmountHandler.update(ActStirringAmount);

          CStatusHandler StirrStatusHandler(StirringStatus);
          StirrStatusHandler.update(ActStirringStatus);

          CStirringDataHandler  StirringFlowHandler     (StirringFlow);

          // reset flows on stirring end !
          if ( Message == EAF_EvMsg::evEAFBottomStirringEnd )
          {
            // looking for devices of DEF_STATUS_NAME::Stirring with state DEF_GEN_STATES::Off
            std::vector<std::string> DeviceList = StirrStatusHandlerDevice.getIDList(DEF_STATUS_NAME::Stirring,DEF_GEN_STATES::Off);

            // set flows to 0.0 for all devices detected
            StirringFlowHandler.setGasDataValue(DeviceList,0.0);
          }

          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringAmount        , StirringAmountHandler.getStirringData());
          m_pProductManagementInterface->setStatus      (ProductID.c_str(), DATA::StirringStatus        , StirrStatusHandler.getStatusData());
          
					m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringFlow          , StirringFlowHandler.getStirringData());

          m_pProductManagementInterface->showContent(ProductID,4);

        }

        RetValue = true;

      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetProductManager(CEventMessage& Event)
{

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    resetComputerModeAvailabilities(Event);
    resetInjectionData(Event);
    resetElectricalData(Event);
    resetBurnerData(Event);
    resetMatFeedData(Event);
    resetGasLanceData(Event);
    resetMasses(Event);
    resetMaterialData(Event);

    if (m_pProductManagementInterface)
    {
      m_pProductManagementInterface->setString(ProductID, DATA::PhaseAct        ,DEF_GC_PHASE::Preparation);
      m_pProductManagementInterface->setString(ProductID, DATA::PhaseProcess    ,"");
      m_pProductManagementInterface->setString(ProductID, DATA::PhaseModel      ,"");
      m_pProductManagementInterface->setString(ProductID, DATA::PhaseTracker    ,"");

      m_pProductManagementInterface->setLong  (ProductID, DATA::PhaseNoAct      ,0);
      m_pProductManagementInterface->setLong  (ProductID, DATA::PhaseNoProcess  ,0);
      m_pProductManagementInterface->setLong  (ProductID, DATA::PhaseNoModel    ,0);
      m_pProductManagementInterface->setLong  (ProductID, DATA::PhaseNoTracker  ,0);

      m_pProductManagementInterface->setDouble(ProductID.c_str(),DATA::SteelMassAct ,0.);
      m_pProductManagementInterface->setDouble(ProductID.c_str(),DATA::SlagMassAct  ,0.);

      m_pProductManagementInterface->setString(ProductID, DATA::ActPlantLocation, "");
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                        "CDM_EAFProductManager::resetProductManager()",
                                        ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                        "CDM_EAFProductManager::resetProductManager()",
                                        ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CDM_EAFProductManager::resetProductManager()",
                                        ExceptionMsg.str().c_str());
  }
  
  //HF ---

  return true;
}

bool CDM_EAFProductManager::resetComputerModeAvailabilities(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      CDM_StatusHandler StatusHandler;
      seqComputerModes StatusSeq; 

      if ( Event.getMessage() == EAF_EvMsg::evEAFHeatCancellation )
      {
        // fill status handler with "off" data
        fillStatusHandler(StatusHandler,m_ComputerModeAvailabilityList,DEF_GEN_STATES::NotAvailable);
      }
      else
      {
        // fill status handler with "default" data
        fillStatusHandler(StatusHandler,m_ComputerModeAvailabilityList,DEF_GEN_STATES::Available);
      }

      // write updated statushandler data into sequecne
      fillComputerModesSequence(StatusHandler,StatusSeq);

      // write updated data into CORBA interface
      m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeComputerModeAvailabilities(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  CDM_StatusHandler StatusHandler;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      // fill status handler with "default" data
      fillStatusHandler(StatusHandler,m_ComputerModeAvailabilityList,DEF_GEN_STATES::NotAvailable);

      // read actual values from CORBA interface and update above list
      seqComputerModes StatusSeq; 

      seqComputerModes SourceSeq ; 
      sComputerMode SourceStruct ; 

      seqComputerModes AimSeq ; 
      sComputerMode AimStruct ; 

      // react on special event
      if ( Message == EAF_EvMsg::evEAFModelResultActualSetpoints  || 
           Message == EAF_EvMsg::evEAFModelResultCode             ||
           Message == EAF_EvMsg::evEAFModelResultRecipeSetpoints )
      {
        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // read actual Availabilities from Model Results
        // this data will become part of the product related values
        SourceSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModeAvail));

        // update AimSeq with Model Result Data
        UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,Device,std::string);

        // work with the updated data from Product interface
        fillStatusHandler(StatusHandler,AimSeq);

        // upadate statushandler entries
        // decide follwing status for Electric
        if ( StatusHandler.getStatus(DEF_COMP_MODES::ElectricModel) == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error)  == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1) == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::Electric, DEF_GEN_STATES::Available );
        }

        // decide follwing status for Stirring
        if ( StatusHandler.getStatus(DEF_COMP_MODES::StirringModel) == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error)  == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1) == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::Stirring, DEF_GEN_STATES::Available );
        }

        // decide follwing status for Injection
        if ( StatusHandler.getStatus(DEF_COMP_MODES::InjectionModel) == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error)  == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1) == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::Injection, DEF_GEN_STATES::Available );
        }

        // decide follwing status for GasLance
        if ( StatusHandler.getStatus(DEF_COMP_MODES::GasLanceModel) == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error)  == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1) == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::GasLance, DEF_GEN_STATES::Available );
        }


        // decide follwing status for Material Handling
        if ( StatusHandler.getStatus(DEF_COMP_MODES::MatHandleModel)   == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error   )   == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1  )   == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::MatHandleL1Error) == DEF_GEN_STATES::NotAvailable)
        {
          StatusHandler.setStatus(DEF_COMP_MODES::MatHandle, DEF_GEN_STATES::Available );
        }

        //Burner
        if ( StatusHandler.getStatus(DEF_COMP_MODES::BurnerModel)   == DEF_GEN_STATES::Available &&
          StatusHandler.getStatus(DEF_COMP_MODES::Level2Error   )   == DEF_GEN_STATES::NotAvailable &&
          StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1  )   == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::Burner, DEF_GEN_STATES::Available );
        }

        // MatFeed
        if ( StatusHandler.getStatus(DEF_COMP_MODES::PatternFeedModel)   == DEF_GEN_STATES::Available &&
             StatusHandler.getStatus(DEF_COMP_MODES::Level2Error   )   == DEF_GEN_STATES::NotAvailable &&
             StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1  )   == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::PatternFeed, DEF_GEN_STATES::Available );
        }

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;

      } //  if ( Message == EAF_EvMsg::evEAFModelResultActualSetpoints  || ...

      else if ( Message == EAF_EvMsg::evEAFMaterialHandlingReport )
      {
        // check RecipeStatus 
        long RecipeStatus = m_pDataInterface->getLong(DataKey,DATA::RecipeStatus);

        // set MatHanldeL1Error = 1       
        if ( RecipeStatus == DEF_GC_RECIPE_STATUS::UnKnown ) 
        {
          // read actual Availabilities from Product interface
          AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

          // work with the data from Product interface
          fillStatusHandler(StatusHandler,AimSeq);

          // upadate statushandler entries
          StatusHandler.setStatus(DEF_COMP_MODES::MatHandleL1Error, DEF_GEN_STATES::Error );

          // write updated statushandler data into sequecne
          fillComputerModesSequence(StatusHandler,StatusSeq);

          // write updated data into CORBA interface
          m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);
        }

        RetValue = true;
      } // else if ( Message == EAF_EvMsg::evEAFMaterialHandlingReport )

      else if ( Message == EAF_EvMsg::evEAFSteelSampleTaken )
      {
        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // work with the data from Product interface
        fillStatusHandler(StatusHandler,AimSeq);

        // upadate statushandler entries
        StatusHandler.setStatus(DEF_COMP_MODES::MatHandleL1Error, DEF_GEN_STATES::Warning );

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;
      } // else if ( Message == EAF_EvMsg::evEAFSteelSampleTaken )

      else if ( Message == EAF_EvMsg::evEAFSteelAnalysisReceived )
      {
        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // work with the data from Product interface
        fillStatusHandler(StatusHandler,AimSeq);

        // upadate statushandler entries
        StatusHandler.setStatus(DEF_COMP_MODES::MatHandleL1Error, DEF_GEN_STATES::NotAvailable );

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;
      } // else if ( Message == EAF_EvMsg::evEAFSteelAnalysisReceived)
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_EAFProductManager::changeElectricalData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface )
      {
        // measured value
        double ElecCons           = m_pDataInterface->getDouble(DataKey,DATA::ElecCons);

        // check if real data are available, if not make them usable
        ElecCons = CDataConversion::SetInvalidToDefault(ElecCons,0.0);

        std::vector<std::string> NameList;
        NameList.push_back(DATA::VoltTapNo);                      
        NameList.push_back(DATA::ElectrodRegCurve);
        NameList.push_back(DATA::ElecPower);

        if ( ElecCons > 0.0) // to prevent setting ElecCons to 0 for Product during treatment!
        {
          NameList.push_back(DATA::ElecCons);
        }

        NameList.push_back(DATA::MomentO2);                       

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
          m_pProductManagementInterface,
          DataKey,
          ProductID,
          NameList);

        if ( ElecCons > 0.0) // to prevent setting ElecCons to 0 for Product during treatment!
        {
          double ElecConsPhaseStart = m_pProductManagementInterface->getDouble(ProductID,DATA::ElecConsPhaseStart);
          double ElecConsPhase      = ElecCons;

          if ( ElecConsPhaseStart != DEF::Inv_Double )
          {
            ElecConsPhase = ElecCons - ElecConsPhaseStart;
            m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhase,ElecConsPhase);
          }
        }

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;
      } // if (m_pDataInterface && m_pProductManagementInterface )
    } // if ( findProduct(ProductID,HeatID,TreatID) )
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeGasData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      // react on special event
      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement  )
      {
        seqGasLanceData ActBurnerFlow      = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::GasLanceFlow));
        seqGasLanceData ActBurnerAmount    = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::GasLanceAmount));

        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::GasLanceFlow));
        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::GasLanceAmount));

        // update product related data with actual values
        CGasLanceDataHandler BurnerFlowHandler      (BurnerFlow);
        CGasLanceDataHandler BurnerAmountHandler    (BurnerAmount);

        BurnerFlowHandler.update(ActBurnerFlow);
        BurnerAmountHandler.update(ActBurnerAmount);

        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::GasLanceFlow          , BurnerFlowHandler.getGasLanceData());
        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::GasLanceAmount        , BurnerAmountHandler.getGasLanceData());

        m_pProductManagementInterface->showContent(ProductID,4);

      }
      else if ( Message == EAF_EvMsg::evEAFManipGasLanceStart ||  Message == EAF_EvMsg::evEAFManipGasLanceStop )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::GasLanceNo);
        NameList.push_back(DATA::GasLanceStatus);

			  CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pProductManagementInterface,
                                             DataKey,
                                             ProductID,
                                             NameList);
  
        seqGasLanceData ActBurnerFlow      = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::GasLanceFlow));
        seqGasLanceData ActBurnerAmount    = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::GasLanceAmount));
        seqStatus       ActBurnereStatus   = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::GasLanceStatus));

        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::GasLanceFlow));
        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasLanceData(ProductID.c_str(), DATA::GasLanceAmount));
        seqStatus       BurnerAmountStatus = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::GasLanceStatus));

        // update product related data with actual values
        CGasLanceDataHandler BurnerFlowHandler      (BurnerFlow);
        CGasLanceDataHandler BurnerAmountHandler    (BurnerAmount);
        CStatusHandler       BurnerStatusHandler    (BurnerAmountStatus);
        
        BurnerFlowHandler.update(ActBurnerFlow);
        BurnerAmountHandler.update(ActBurnerAmount);
        BurnerStatusHandler.update(ActBurnereStatus);

        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::GasLanceFlow        , BurnerFlowHandler.getGasLanceData());
        m_pProductManagementInterface->setGasLanceData(ProductID.c_str(), DATA::GasLanceAmount      , BurnerAmountHandler.getGasLanceData());
        m_pProductManagementInterface->setStatus      (ProductID.c_str(), DATA::GasLanceStatus      , BurnerStatusHandler.getStatusData());

        m_pProductManagementInterface->showContent(ProductID,4);
        
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}



bool CDM_EAFProductManager::resetInjectionData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      seqInjectLanceData InjectLanceDataSeq;
      sInjectLanceData InjectLanceDataStruct;

      seqStatus StatusSeq;
      sStatus StatusStruct;

      // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    = DEF_GCE_INJECTION::Carbon_Injector.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::CarbonInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

       // init Status sequence
      StatusStruct.Device = InjectLanceDataStruct.Device;
      StatusStruct.Status = DEF_GEN_STATES::Off;
      CIntfData::insert(StatusSeq, StatusStruct);

      // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    =  DEF_GCE_INJECTION::Silicon_Injector.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::SiliconInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

       // init Status sequence
      StatusStruct.Device = InjectLanceDataStruct.Device;
      StatusStruct.Status = DEF_GEN_STATES::Off;
      CIntfData::insert(StatusSeq, StatusStruct);      

      m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(),
                                                        DATA::InjectLanceFlow,
                                                        InjectLanceDataSeq);
      m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(),
                                                        DATA::InjectLanceAmount,
                                                        InjectLanceDataSeq);
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetElectricalData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      m_pProductManagementInterface->setDouble(ProductID,DATA::ElecCons,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhase,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhaseStart,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::ElecPower,0.);

      m_pProductManagementInterface->setLong(ProductID,DATA::VoltTapNoAim,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::VoltTapNo,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElectrodRegCurveAim,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElectrodRegCurve,0);

      m_pProductManagementInterface->setLong(ProductID,DATA::ElecPullReq,DEF_GEN_STATES::No);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElecInhibitReq,DEF_GEN_STATES::Yes);
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetBurnerData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      vector<std::string>::iterator itBurnerDeviceList;
      vector<std::string>::iterator itGasTypeList;

      seqGasData GasDataSeq; 
      sGasData GasDataStruct; 

      seqGasLanceData BurnerDataSeq; 
      sGasLanceData BurnerDataStruct;

      seqStatus BurnerStatusSeq;
      sStatus Status;
      Status.Status = DEF_GEN_STATES::Off;

      GasDataStruct.GasValue = 0.0;

      // for ech member of m_GasTypeList
      for ( itGasTypeList = m_GasTypeList.begin() ; itGasTypeList != m_GasTypeList.end() ; ++itGasTypeList)
      {
        GasDataStruct.GasType = (*itGasTypeList).c_str();
        CIntfData::insert(GasDataSeq,GasDataStruct);
      }

      // for ech member of m_BurnerDeviceList
      for ( itBurnerDeviceList = m_BurnerDeviceList.begin() ; itBurnerDeviceList != m_BurnerDeviceList.end() ; ++itBurnerDeviceList)
      {
        Status.Device = (*itBurnerDeviceList).c_str();
        Status.StatusName = DEF_STATUS_NAME::Burner;
        CIntfData::insert(BurnerStatusSeq,Status);

        // init BurnerData for Burner 1 ... n
        BurnerDataStruct.LanceData = GasDataSeq;
        BurnerDataStruct.Device = (*itBurnerDeviceList).c_str();
        CIntfData::insert(BurnerDataSeq,BurnerDataStruct);
      }

      // write updated data into CORBA interface
      m_pProductManagementInterface->setStatus      (ProductID.c_str(),DATA::BurnerStatus ,BurnerStatusSeq);

      m_pProductManagementInterface->setGasLanceData(ProductID.c_str(),DATA::BurnerAmount ,BurnerDataSeq);
      m_pProductManagementInterface->setGasLanceData(ProductID.c_str(),DATA::BurnerFlow   ,BurnerDataSeq);


      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetBurnerData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetBurnerData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetBurnerData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetMatFeedData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      seqBatch sqMatFeedingBatch;
      seqStatus MatFeedingBatchStatus;

      for ( long i = 0 ; i <= 8 ; ++i)
      {
        std::string MatCode = DEF::Inv_String;
        long MatWeight   = 0;
        long FeederNo    = i+1;
        long FeedingRate = 0;

        sBatch sBatchMatFeedingData;

        //InjectType don't necessary to use in EAF
        sBatchMatFeedingData.MatCode      = MatCode.c_str();
        sBatchMatFeedingData.Mass         = MatWeight;
        sBatchMatFeedingData.MatFeedSpeed = FeedingRate;
        sBatchMatFeedingData.Source       = FeederNo;

        sStatus Status;
        Status.Status     = DEF_GEN_STATES::Off;
        Status.Device     = CDataConversion::LongToString(FeederNo).c_str();
        Status.StatusName = CDataConversion::LongToString(FeederNo).c_str();

        CIntfData::insert(sqMatFeedingBatch    , sBatchMatFeedingData);
        CIntfData::insert(MatFeedingBatchStatus, Status);
      }

      // write updated data into CORBA interface
      m_pProductManagementInterface->setBatch (ProductID.c_str(),DATA::MatFeedingData           , sqMatFeedingBatch);
      m_pProductManagementInterface->setStatus(ProductID.c_str(),DATA::MatFeedingDataStatus     , MatFeedingBatchStatus);
      
      RetValue = true;
    }
}
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetMatFeedData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetMatFeedData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetMatFeedData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetGasLanceData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      vector<std::string>::iterator itGasLanceDeviceList;
      vector<std::string>::iterator itGasTypeList;

      seqGasData GasDataSeq; 
      sGasData GasDataStruct; 

      seqGasLanceData GasLanceDataSeq; 
      sGasLanceData GasLanceDataStruct;

      seqStatus GasLanceStatusSeq;
      sStatus Status;
      Status.Status = DEF_GEN_STATES::Off;

      GasDataStruct.GasValue = 0.0;

      // for ech member of m_GasTypeList
      for ( itGasTypeList = m_GasTypeList.begin() ; itGasTypeList != m_GasTypeList.end() ; ++itGasTypeList)
      {
        GasDataStruct.GasType = (*itGasTypeList).c_str();
        CIntfData::insert(GasDataSeq,GasDataStruct);
      }

      // for ech member of m_GasLanceDeviceList
      for ( itGasLanceDeviceList = m_GasLanceDeviceList.begin() ; itGasLanceDeviceList != m_GasLanceDeviceList.end() ; ++itGasLanceDeviceList)
      {
        Status.Device = (*itGasLanceDeviceList).c_str();
        Status.StatusName = DEF_STATUS_NAME::Burner;
        CIntfData::insert(GasLanceStatusSeq,Status);

        // init GasLanceData for GasLance 1 ... n
        GasLanceDataStruct.LanceData = GasDataSeq;
        GasLanceDataStruct.Device = (*itGasLanceDeviceList).c_str();
        CIntfData::insert(GasLanceDataSeq,GasLanceDataStruct);
      }

      // write updated data into CORBA interface
      m_pProductManagementInterface->setStatus      (ProductID.c_str(),DATA::GasLanceStatus ,GasLanceStatusSeq);

      m_pProductManagementInterface->setGasLanceData(ProductID.c_str(),DATA::GasLanceAmount ,GasLanceDataSeq);
      m_pProductManagementInterface->setGasLanceData(ProductID.c_str(),DATA::GasLanceFlow   ,GasLanceDataSeq);


      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetGasLanceData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetGasLanceData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetGasLanceData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_EAFProductManager::resetMasses(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      m_pProductManagementInterface->setDouble(ProductID,DATA::SteelMassAct,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::SlagMassAct,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::TappingMass,0.0);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetMasses()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetMasses()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetMasses()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::resetMaterialData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::resetMaterialData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::resetMaterialData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::resetMaterialData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeInjectionData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;
  try
  {
    // copy incoming data to m_pProductManagementInterface
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement  )
      {
        seqInjectLanceData ActInjectLanceAmount = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount));
        seqInjectLanceData ActInjectLanceFlow   = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow));

        seqInjectLanceData InjectLanceAmount    = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount));
        seqInjectLanceData InjectLanceFlow      = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow));

        // update product related data with actual values
        CInjectLanceDataHandler InjectLanceDataHandlerAmount  (InjectLanceAmount);
        CInjectLanceDataHandler InjectLanceDataHandlerFlow    (InjectLanceFlow);

        InjectLanceDataHandlerAmount.update(ActInjectLanceAmount);
        InjectLanceDataHandlerFlow.update(ActInjectLanceFlow);

        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(),DATA::InjectLanceAmount,InjectLanceDataHandlerAmount.getInjectLanceData());
        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(),DATA::InjectLanceFlow,InjectLanceDataHandlerFlow.getInjectLanceData());

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;
      }
       // react on special event
      else if (  Message == EAF_EvMsg::evEAFManipInjectLanceStart || Message == EAF_EvMsg::evEAFManipInjectLanceStop )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::LanceId);

			  CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pProductManagementInterface,
                                             DataKey,
                                             ProductID,
                                             NameList);


        seqInjectLanceData ActInjectLancerFlow     = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData ActInjectLanceAmount    = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount));
        seqStatus          ActInjectLanceStatus    = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::InjectorStatus));
     
        seqInjectLanceData InjectLanceFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData InjectLanceAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount));
        seqStatus          InjectLanceStatus       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::InjectorStatus));

        // update product related data with actual values

        CInjectLanceDataHandler InjectLanceAmountHandler;
        InjectLanceAmountHandler.fill(InjectLanceAmount);

        CInjectLanceDataHandler InjectLanceFlowHandler;
        InjectLanceFlowHandler.fill(InjectLanceFlow);

        CStatusHandler InjectLanceStatusHandler(InjectLanceStatus);


        InjectLanceAmountHandler.update(ActInjectLanceAmount);
        InjectLanceFlowHandler.update(ActInjectLancerFlow);      
        InjectLanceStatusHandler.update(ActInjectLanceStatus);


        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount     , InjectLanceAmountHandler.getInjectLanceData());
        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow       , InjectLanceFlowHandler.getInjectLanceData());    
        m_pProductManagementInterface->setStatus         (ProductID.c_str(), DATA::InjectorStatus        , InjectLanceStatusHandler.getStatusData());

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;
      }
      // react on special event
      else if ( Message == EAF_EvMsg::evEAFCarbonInjectStart || Message == EAF_EvMsg::evEAFCarbonInjectStop )
      {
        seqInjectLanceData ActInjectLancerFlow     = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData ActInjectLanceAmount    = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount));
        seqStatus          ActInjectLanceStatus    = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::InjectorStatus));
     
        seqInjectLanceData InjectLanceFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData InjectLanceAmount      = CIntfData::ToCORBAType(m_pProductManagementInterface->getInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount));
        seqStatus          InjectLanceStatus      = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::InjectorStatus));

        // update product related data with actual values
        CInjectLanceDataHandler InjectLanceFlowHandler;
        InjectLanceFlowHandler.fill(InjectLanceFlow);

        CInjectLanceDataHandler InjectLanceAmountHandler;
        InjectLanceAmountHandler.fill(InjectLanceAmount);

        InjectLanceFlowHandler.update(ActInjectLancerFlow);
        InjectLanceAmountHandler.update(ActInjectLanceAmount);

        CStatusHandler InjectLanceStatusHandler(InjectLanceStatus);
        InjectLanceStatusHandler.update(ActInjectLanceStatus);

        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(), DATA::InjectLanceFlow          , InjectLanceFlowHandler.getInjectLanceData());
        m_pProductManagementInterface->setInjectLanceData(ProductID.c_str(), DATA::InjectLanceAmount        , InjectLanceAmountHandler.getInjectLanceData());
        m_pProductManagementInterface->setStatus         (ProductID.c_str(), DATA::InjectorStatus           , InjectLanceStatusHandler.getStatusData());

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;
      }   
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeCoolingWaterData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID << ", " << DataKey;
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface)
      {
        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
          m_pProductManagementInterface,
          DataKey,
          ProductID);
        m_pProductManagementInterface->showContent(ProductID,4);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFProductManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFProductManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFProductManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}

void CDM_EAFProductManager::init(CDM_Task* pDMTask)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Init Product Manager: " ;

  try
  {

    // first of all call base class method to set
    // members
	  CDM_ProductManager::init(pDMTask);


    if ( m_pDataInterface )
    {
      m_pDataInterface->setPersistence(DEF_DATAKEY::CYCLIC_FURNACE,true);
    }

    m_pProductManagementInterface->showContent("",4);
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }

}

bool CDM_EAFProductManager::changeSetpoints(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID << ", " << DataKey;

  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface)
      {
        if ( Message == EAF_EvMsg::evEAFModelResultActualSetpoints        || 
             Message == EAF_EvMsg::evEAFModelResultRecipeSetpoints        ||
             Message == EAF_EvMsg::evEAFModelResultActualSetpointsOffline || 
             Message == EAF_EvMsg::evEAFModelResultRecipeSetpointsOffline)
        {
          // store ladle, car and gas data
          std::vector<std::string> DataList;

          DataList.push_back(DATA::VoltTapNoAim);
          DataList.push_back(DATA::ElectrodRegCurveAim);
          DataList.push_back(DATA::ReactTapNoAim);
          DataList.push_back(DATA::ElecPullReq);
          DataList.push_back(DATA::ElecInhibitReq);
          DataList.push_back(DATA::TotalRemElecEgy);
          DataList.push_back(DATA::TempMeasReq);
          DataList.push_back(DATA::SteelSampleReq);
          DataList.push_back(DATA::EAFMatRecipe);
          DataList.push_back(DATA::StirringIntensity);

          DataList.push_back(DATA::RemTreatDur);
          DataList.push_back(DATA::PhaseModel);
          DataList.push_back(DATA::PhaseNoModel);


          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
            DataKey,ProductID,DataList);

          m_pProductManagementInterface->showContent(ProductID,4);

          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFProductManager::changeSetpoints()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFProductManager::changeSetpoints()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFProductManager::changeSetpoints()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::changeMaterialFeedingData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID << ", " << DataKey;
  try
  {
    if ( findProduct(ProductID, HeatID, TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface)
      {
        std::string PhaseProcess    = m_pProductManagementInterface->getString(Event.getProductID(),DATA::PhaseProcess);
        long PhaseNoProcess         = m_pProductManagementInterface->getLong(Event.getProductID(), DATA::PhaseNoProcess);

        if ( Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStart || Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStop )
        {
          seqStatus       ActMatFeedingBatchStatus = CIntfData::ToCORBAType(m_pDataInterface->getStatus(Event.getDataKey().c_str(), DATA::MatFeedingDataStatus));
          seqStatus       MatFeedingBatchStatus    = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus(ProductID.c_str(), DATA::MatFeedingDataStatus));

          seqBatch sqMatFeedingBatch;

          bool isReset = false;

          seqBatch sqMatFeedingBatchCur   = CIntfData::ToCORBAType(m_pDataInterface->getBatch(Event.getDataKey().c_str(), DATA::MatFeedingData));

          seqBatch sqMatFeedingBatchAct ;
          if ( PhaseProcess == DEF_GC_PHASE::Refining )
          {
            sqMatFeedingBatchAct   = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingData));
          }
          else
          {
            sqMatFeedingBatchAct   = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingAmountActPhase));
          }

          seqBatch sqMatFeedingBatchPrev  = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingAmountPrevPhase));

          CStatusHandler MatFeedingBatchStatusHandler(MatFeedingBatchStatus);
          MatFeedingBatchStatusHandler.update(ActMatFeedingBatchStatus);

          if (CIntfData::getLength(sqMatFeedingBatchCur) != 0)
          {
            for (long i = 0 ; i < CIntfData::getLength(sqMatFeedingBatchAct) ; ++i)
            {
              sBatch Batch;

              if (CIntfData::getAt(Batch,sqMatFeedingBatchAct,i))
              {
                if ( std::string(Batch.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) || 
                    (std::string(Batch.MatCode) == std::string(DEF::Inv_String) && Batch.Source == sqMatFeedingBatchCur[0].Source) )
                {
                  Batch.MatCode      = sqMatFeedingBatchCur[0].MatCode;
                  Batch.Mass         = sqMatFeedingBatchCur[0].Mass;
                  Batch.MatFeedSpeed = sqMatFeedingBatchCur[0].MatFeedSpeed;

                  for (long ii = 0 ; ii < CIntfData::getLength(sqMatFeedingBatchPrev) ; ++ii)
                  {
                    sBatch BatchPrev;
                    if (CIntfData::getAt(BatchPrev,sqMatFeedingBatchPrev,ii))
                    {
                      if ( PhaseProcess == DEF_GC_PHASE::Refining )
                      {
                        if  ( std::string(BatchPrev.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) && sqMatFeedingBatchCur[0].Mass >= BatchPrev.Mass )
                        {
                          Batch.Mass = sqMatFeedingBatchCur[0].Mass - BatchPrev.Mass;
                          break;
                        }
                        else if  ( std::string(BatchPrev.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) && sqMatFeedingBatchCur[0].Mass == 0 )
                        {
                          isReset = true;
                          CIntfData::setAt(sqMatFeedingBatchPrev,sqMatFeedingBatchCur[0],ii);
                          break;
                        }
                      }// if ( PhaseProcess == DEF_GC_PHASE::Refining )
                      else
                      {
                        if  ( std::string(BatchPrev.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) && sqMatFeedingBatchCur[0].Mass >= BatchPrev.Mass )
                        {
                          Batch.Mass = sqMatFeedingBatchCur[0].Mass - BatchPrev.Mass;
                          if ( sqMatFeedingBatchCur[0].Mass > BatchPrev.Mass )
                          {
                            isReset = true;
                            CIntfData::setAt(sqMatFeedingBatchPrev,sqMatFeedingBatchCur[0],ii);
                          }
                          break;
                        }
                        // when mass is reseted also prev value should be reseted
                        else if  ( std::string(BatchPrev.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) && sqMatFeedingBatchCur[0].Mass >= 0 )
                        {
                          isReset = true;
                          CIntfData::setAt(sqMatFeedingBatchPrev,sqMatFeedingBatchCur[0],ii);
                          break;
                        }
                      }
                    }
                  }// for (long ii = 0 ; ii < CIntfData::getLength(sqMatFeedingBatchPrev) ; ++ii)
                }// if (  std::string(Batch.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode )

                CIntfData::insert(sqMatFeedingBatch, Batch);
              }// if (CIntfData::getAt(Batch,sqMatFeedingBatchAct,i))
            }// for (long i = 0 ; i < CIntfData::getLength(sqMatFeedingBatchAct) ; ++i)
          }// if (CIntfData::getLength(sqMatFeedingBatchCur) != 0)
          else
          {
            sqMatFeedingBatch = sqMatFeedingBatchAct;
          }

          // accept only as continuous feeding when L1 is in Refining Phase. Otherwise it must be handled as a batch.
          if ( PhaseProcess == DEF_GC_PHASE::Refining )
          {
            if ( CIntfData::getLength(sqMatFeedingBatch) )
            {
              m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingData, sqMatFeedingBatch);
            }

            if (isReset)
            {
              m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingAmountPrevPhase, sqMatFeedingBatchPrev);
            }

            RetValue = true;
          }
          else
          {
            if ( Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStop )
            {
              std::string RecipeName    = "MeltdownSlagFormNo" + CDataConversion::LongToString(PhaseNoProcess, "1");
              seqBatch RecipeBatch      = sqMatFeedingBatch;       
              std::string RecipeSource  = DEF_GC_RECIPE_SOURCE::Bin;
              long RecipeNo             = 1;

              seqStatus StatusFeedingDataOn = MatFeedingBatchStatusHandler.getStatusData(DEF_GEN_STATES::On);         
              if (  CIntfData::getLength(StatusFeedingDataOn) == 0 )
              {
                std::vector<std::string> DestinationList;
                std::string SenderName;
                std::string TaskName =  m_pDMTask->getTaskName();
                std::vector<std::string> PlantList;
                std::vector<std::string>::iterator it;

                cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"ReceiverName",SenderName);

                cCBS_StdInitBase::getInstance()->getEntryList("PLANT","PlantId",PlantList);
                cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"PlantId",PlantList);

                CEventMessage Message(Event);

                // set interface only when all started feeder stopped then make a batch (this mean status should not be "on")
                m_pDataInterface->setString(Event.getDataKey()        ,DATA::RecipeName    ,RecipeName);            
                m_pDataInterface->setBatch (Event.getDataKey().c_str(),DATA::RecipeContent ,RecipeBatch);
                m_pDataInterface->setString(Event.getDataKey()        ,DATA::RecipeSource  ,RecipeSource);
                m_pDataInterface->setLong  (Event.getDataKey()        ,DATA::RecipeNo      ,RecipeNo);
                m_pDataInterface->setString(Event.getDataKey()        ,DATA::RecipeTarget  ,DEF_GC_CHARGE_DEST::Furnace);

                m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingAmountPrevPhase, sqMatFeedingBatch);

                for ( it = PlantList.begin() ; it != PlantList.end(); it ++)
                {
                  Message.setMessage(EAF_EvMsg::evEAFHMIMaterialDischarged);
                  Message.setPlantEvent(false);
                  Message.dispatch(SenderName,SenderName);
                }
              }// if (  CIntfData::getLength(StatusFeedingDataOn) == 0 )
            }// if ( Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStop )
            else  if ( Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStart )
            {
              if (isReset)
              {
                m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingAmountPrevPhase, sqMatFeedingBatchPrev);
              }
            }
          }

          m_pProductManagementInterface->setStatus(ProductID.c_str(), DATA::MatFeedingDataStatus, MatFeedingBatchStatusHandler.getStatusData());

          m_pProductManagementInterface->showContent(ProductID,4);
        }//if ( Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStart || Event.getMessage() == EAF_EvMsg::evEAFMatFeedingStop )
        else if ( Event.getMessage() == EAF_EvMsg::evEAFCyclicMeasurement )
        {
          seqBatch sqMatFeedingBatch;
                   
          seqBatch sqMatFeedingBatchCur   = CIntfData::ToCORBAType(m_pDataInterface->getBatch(Event.getDataKey().c_str(), DATA::MatFeedingData));
          
          seqBatch sqMatFeedingBatchAct ;
          if ( PhaseProcess == DEF_GC_PHASE::Refining )
          {
            sqMatFeedingBatchAct   = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingData));
          }
          else
          {
            sqMatFeedingBatchAct   = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingAmountActPhase));
          }

          seqBatch sqMatFeedingBatchPrev  = CIntfData::ToCORBAType(m_pProductManagementInterface->getBatch(ProductID.c_str(), DATA::MatFeedingAmountPrevPhase));

          if (CIntfData::getLength(sqMatFeedingBatchCur) != 0)
          {
            for (long i = 0 ; i < CIntfData::getLength(sqMatFeedingBatchAct) ; ++i)
            {
              sBatch Batch;

              if (CIntfData::getAt(Batch,sqMatFeedingBatchAct,i))
              {
                for (long k = 0 ; k < CIntfData::getLength(sqMatFeedingBatchCur) ; ++k)
                {
                  sBatch BatchCur;
                  CIntfData::getAt(BatchCur,sqMatFeedingBatchCur,k);

                  if ( std::string(Batch.MatCode) == std::string(BatchCur.MatCode) || 
                      (std::string(Batch.MatCode) == std::string(DEF::Inv_String) && Batch.Source == BatchCur.Source) )
                  {
                    Batch.MatCode      = BatchCur.MatCode;
                    Batch.Mass         = BatchCur.Mass;
                    Batch.MatFeedSpeed = BatchCur.MatFeedSpeed;

                    for (long ii = 0 ; ii < CIntfData::getLength(sqMatFeedingBatchPrev) ; ++ii)
                    {
                      sBatch BatchPrev;
                      if (CIntfData::getAt(BatchPrev,sqMatFeedingBatchPrev,ii))
                      {
                        if  ( std::string(BatchPrev.MatCode) == std::string(BatchCur.MatCode) && BatchCur.Mass > BatchPrev.Mass )
                        {
                          Batch.Mass = BatchCur.Mass - BatchPrev.Mass;
                          break;
                        }                      
                      }
                    }// for (long ii = 0 ; ii < CIntfData::getLength(sqMatFeedingBatchPrev) ; ++ii)
                    break;
                  }// if ( std::string(Batch.MatCode) == std::string(sqMatFeedingBatchCur[0].MatCode) || 
                }// for (long k = 0 ; k < CIntfData::getLength(sqMatFeedingBatchCur) ; ++k)

                CIntfData::insert(sqMatFeedingBatch, Batch);
              }// if (CIntfData::getAt(Batch,sqMatFeedingBatchAct,i))
            }// for (long i = 0 ; i < CIntfData::getLength(sqMatFeedingBatchAct) ; ++i)

						  //SARS: if new material is added in sqMatFeedingBatchCur which is not in sqMatFeedingBatchAct
						  for (long k = 0 ; k < CIntfData::getLength(sqMatFeedingBatchCur) ; ++k)
              {
                sBatch BatchCur;
								bool matExist = false;
                CIntfData::getAt(BatchCur,sqMatFeedingBatchCur,k);
								for (long i = 0 ; i < CIntfData::getLength(sqMatFeedingBatchAct) ; ++i)
								{
									sBatch Batch;
									CIntfData::getAt(Batch,sqMatFeedingBatchAct,i);
									if ( std::string(Batch.MatCode) == std::string(BatchCur.MatCode))
									{
										matExist = true;
									}
								}
								if(!matExist)
								{
									CIntfData::insert(sqMatFeedingBatch, BatchCur);
								}
							} //SARS end 



          }
          else
          {
            sqMatFeedingBatch = sqMatFeedingBatchAct;
          }

          // accept only as continuous feeding when L1 is in Refining Phase. Otherwise it must be handled as a batch.
          if ( PhaseProcess == DEF_GC_PHASE::Refining )
          {
            // MatFeedingAmountActPhase is used as batch handling and MatFeedingData as continuous feeding
            m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingData, sqMatFeedingBatch);
          }// if ( PhaseProcess == DEF_GC_PHASE::Refining )
          else
          {
            // MatFeedingAmountActPhase is used as batch handling and MatFeedingData as continuous feeding
            m_pProductManagementInterface->setBatch(ProductID.c_str(), DATA::MatFeedingAmountActPhase, sqMatFeedingBatch);       
          }

          std::vector<std::string> DataList;

          DataList.push_back(DATA::ElecCons);
          DataList.push_back(DATA::MomentO2);

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
            m_pProductManagementInterface,
            DataKey,
            ProductID, 
            DataList);

          m_pProductManagementInterface->showContent(ProductID,4);  

          RetValue = true;
        }// else if ( Event.getMessage() == EAF_EvMsg::evEAFCyclicMeasurement )
      }// if (m_pDataInterface && m_pProductManagementInterface)
    }// if ( findProduct(ProductID, HeatID, TreatID) )
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFProductManager::changeMaterialFeedingData()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFProductManager::changeMaterialFeedingData()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown",
      "CDM_EAFProductManager::changeMaterialFeedingData()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFProductManager::doOnPhaseStateChange(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID << ", " << DataKey;
  try
  {
    if ( findProduct(ProductID, HeatID, TreatID) )
    {
      //      if (m_pProductManagementInterface)
      //      {
      //        double ElecCons           = m_pProductManagementInterface->getDouble(ProductID,DATA::ElecCons);
      //
      //
      //        m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhaseStart ,ElecCons);
      //        m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhase      ,0.0);

      // use method only when there is just Level 1 phasetracking!!
      // Message.setMessage(EAF_EvMsg::evEAFPhaseChange);

      addEventMessageToSend(EAF_EvMsg::evEAFEstimatedEnergyReached);

      RetValue = true;
      //      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown",
      "CDM_EAFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}

//bool CDM_EAFProductManager::doEstimatedEnergyReached(CEventMessage& Event)
//{
//  bool RetValue = false;
//
//  std::string ProductID = Event.getProductID();
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID();
//  std::string DataKey   = Event.getDataKey();
//  std::string Message   = Event.getMessage();
//
//  std::stringstream ExceptionMsg;
//  ExceptionMsg << "Handling event: " << Event.getSender()
//    << ", " << ProductID << ", " << HeatID
//    << ", " << TreatID << ", " << DataKey;
//  try
//  {
//    if (m_pProductManagementInterface)
//    {
//      seqEAFProcessPredRes  SeqEAFProcessPredRes   = CIntfData::ToCORBAType(m_pProductManagementInterface->getEAFProcessPredRes ( ProductID.c_str(), DATA::EAFProcessPredRes));
//
//      std::string PhaseTracker   = m_pProductManagementInterface->getString(ProductID.c_str(), DATA::PhaseTracker);
//      long PhaseNoTracker        = m_pProductManagementInterface->getLong(ProductID.c_str()  , DATA::PhaseNoTracker);
//
//      double ElecConsPhase       = m_pProductManagementInterface->getDouble(ProductID,DATA::ElecConsPhase);
//
//      double TotalEnergyConsPhase = 0.;
//
//      for (int i = 0 ; i < CIntfData::getLength(SeqEAFProcessPredRes) ; ++i)
//      {
//        sEAFProcessPredRes EAFProcessPredRes;
//        CIntfData::getAt(EAFProcessPredRes,SeqEAFProcessPredRes,i);
//
//        if ( (std::string)EAFProcessPredRes.Phase == PhaseTracker && EAFProcessPredRes.PhaseNo == PhaseNoTracker )
//        {
//          TotalEnergyConsPhase += EAFProcessPredRes.ElecEgyStep;
//          RetValue= true;
//        }
//      }
//
//      if ( RetValue && ElecConsPhase >= TotalEnergyConsPhase )
//      {
//        addEventMessageToSend(EAF_EvMsg::evEAFEstimatedEnergyReached);
//      }
//    }
//  }
//  catch(CORBA::SystemException& sExc) 
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
//    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
//      "CDM_EAFProductManager::doEstimatedEnergyReached()",
//      ExceptionMsg.str().c_str());
//  }
//  catch(CORBA::Exception& cExc) 
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
//    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
//      "CDM_EAFProductManager::doEstimatedEnergyReached()",
//      ExceptionMsg.str().c_str());
//  }
//  catch(...) 
//  {
//    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
//    pEventLog->EL_ExceptionCaught(sMessage,"Unknown",
//      "CDM_EAFProductManager::doEstimatedEnergyReached()",
//      ExceptionMsg.str().c_str());
//  }
//  return RetValue;
//}
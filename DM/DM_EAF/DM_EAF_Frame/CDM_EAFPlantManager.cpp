// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"

#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "CDM_EAFTask.h"
#include "CSMC_EventLogFrameController.h"
#include "DEF_GC_THERM_STAT.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_INJECTION.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GC_COMP_STATUS.h"

#include "CGasLanceDataHandler.h"
#include "CInjectLanceDataHandler.h"
#include "CStatusHandler.h"
#include "CCoolWaterHandler.h"

#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_EAFPlantManager.h"


CDM_EAFPlantManager::~CDM_EAFPlantManager()
{
}

CDM_EAFPlantManager::CDM_EAFPlantManager()
{
  // fill GasNames into respective container
  m_GasTypeList.push_back(DEF_GC_STIRR_GAS_TYPE::Ar);
  m_GasTypeList.push_back(DEF_GC_STIRR_GAS_TYPE::N2);
  m_GasTypeList.push_back(DEF_GCE_BURNER_GASTYPE::O2);

  // fill GasDevices into respective container
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_1);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_2);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_3);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::Burner_4);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::DoorBurner);
  m_BurnerDeviceList.push_back(DEF_GCE_BURNER::EBTBurner);

  m_GasLanceDeviceList.push_back(DEF_GCE_INJECTION::Oxygen_Injector_1);
  m_GasLanceDeviceList.push_back(DEF_GCE_INJECTION::Oxygen_Injector_2);

  m_ComputerModeList.push_back(DEF_COMP_MODES::Electric);
  m_ComputerModeList.push_back(DEF_COMP_MODES::GasLance);
  m_ComputerModeList.push_back(DEF_COMP_MODES::Injection);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandleL1Error);
  m_ComputerModeList.push_back(DEF_COMP_MODES::RejectHeatL1);
  m_ComputerModeList.push_back(DEF_COMP_MODES::Stirring);
  m_ComputerModeList.push_back(DEF_COMP_MODES::Burner);
  m_ComputerModeList.push_back(DEF_COMP_MODES::DynamicFeed);
  m_ComputerModeList.push_back(DEF_COMP_MODES::PatternFeed);
  m_ComputerModeList.push_back(DEF_COMP_MODES::TappingBatch);
}

bool CDM_EAFPlantManager::changePlantInformation(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Message   = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();


  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if ( Message == EAF_EvMsg::evEAFModelResultActualSetpoints || 
         Message == EAF_EvMsg::evEAFModelResultRecipeSetpoints )
    {
      if ( m_pPlantManagementInterface && m_pDataInterface )
      {
        // check status for pulling electrodes
        long ElecPullReq = m_pDataInterface->getLong(DataKey.c_str(), DATA::ElecPullReq);
        
        if (m_StatusHandler.isStatusChanged(PlantID.c_str(), DATA::ElecPullReq, ElecPullReq))
        {
          if (ElecPullReq == DEF_GEN_STATES::Yes)
          {
            addEventMessageToSend(EAF_EvMsg::evEAFPullElectrodeRequest);
          }
        }
        m_pPlantManagementInterface->setLong(PlantID.c_str(), DATA::ElecPullReq, ElecPullReq);

        // check status for releasing/inhibiting electrodes
        long ElecInhibitReq = m_pDataInterface->getLong(DataKey.c_str(), DATA::ElecInhibitReq);
        if (m_StatusHandler.isStatusChanged(PlantID.c_str(), DATA::ElecInhibitReq, ElecInhibitReq))
        {
          if (ElecInhibitReq == DEF_GEN_STATES::Yes)
          {
            addEventMessageToSend(EAF_EvMsg::evEAFElectrodeHydraulicSystemInhibitRequest);
          }
          else
          {
            addEventMessageToSend(EAF_EvMsg::evEAFElectrodeHydraulicSystemReleaseRequest);
          }
        }

        m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::ElecInhibitReq, ElecInhibitReq);
      }
    }
    else if ( Message == EAF_EvMsg::evEAFHeatAnnouncement )
    {
      resetPlantManager(Event);

      m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,ProductID.c_str());
      m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::HeatID,HeatID.c_str());
      m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::TreatID,TreatID.c_str());

      RetValue = true;
    }
    else if ( Message == EAF_EvMsg::evEAFHeatAnnounceStatus )
    {
      // check model status, if necessarry deassign heat from plantmanager
      if (m_pDataInterface)
      {
        long HeatAnnounceStatus = m_pDataInterface->getLong(Event.getDataKey().c_str(),DATA::HeatAnnounceStatus);
        
        // HeatAnnounceStatus == 0 means prediction not successful !
        if ( 0 == HeatAnnounceStatus )
        {
          //deassignHeat(Event.getHeatID());
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_HeatAnnouncementModelError(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
        }

        RetValue = true;
      }
    }
    else if ( Message == EAF_EvMsg::evEAFHeatStart )
    {
      // write ProductID as ActualID to PlantManagementInterface
      if ( m_pPlantManagementInterface ) 
      {
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,ProductID.c_str());
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::HeatID,HeatID.c_str());
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::TreatID,TreatID.c_str());
        RetValue = true;
      }
    }
    else if ( Message == EAF_EvMsg::evEAFHeatCancellation  )
    {
      deassignProduct(Event);

      if ( m_pPlantManagementInterface )
      {
        log("Reset ProductID at Furnace!",2);
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,"");
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::HeatID,"");
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::TreatID,"");
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::OrderId,"");
      }

      resetPlantManager(Event);

      RetValue = true;
    }
    else if ( Message == EAF_EvMsg::evEAFHeatDeparture )
    {
      deassignProduct(Event);

      initElectricalData();

      if ( m_pPlantManagementInterface )
      {
        std::string ActProductFurnace = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::Furnace),DATA::ProductID);
        std::string ActProductTapping = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::TappingArea),DATA::ProductID);

        if (ActProductFurnace != DEF::Inv_String && !ActProductFurnace.empty())
        {
          if (ActProductTapping != DEF::Inv_String && !ActProductTapping.empty())
          {
            // when heat in furnace is the same heat in tapping area
            // means no new heat is announced. Delete heat in furnace as well
            if (ActProductTapping == ActProductFurnace)
            {
              log("Remove ProductID from Furnace!",3);
              m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,"");
            }
          }
          else
          {
            log("INFO: No Product at Tapping Area",3);
          }
        }
        else
        {
          log("INFO: No Product at Furnace",3);
        }

        //remove heat from tapping area 
        std::string Message = "Remove Product, Heat, Treat, Order from TappingArea! ";
        Message += ActProductTapping + ", " + HeatID + ", " + TreatID + ", " + OrderID;
        log(Message, 3);

        m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::ProductID, "");
        m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::HeatID,  "");
        m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::TreatID, "");
        m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::OrderId, "");

        m_pPlantManagementInterface->showContent(DEF_PLANT::TappingArea,4);

        RetValue = true;
      }//if ( m_pPlantManagementInterface )
    }
    else if ( Message == EAF_EvMsg::evEAFChangeThermalStatus )
    {
      std::string FurnaceStatus = m_pDataInterface->getString(DataKey, DATA::FurnaceStatus);
      if (FurnaceStatus != DEF::Inv_String && 
         (FurnaceStatus == DEF_GC_THERM_STAT::H ||
          FurnaceStatus == DEF_GC_THERM_STAT::C ||
          FurnaceStatus == DEF_GC_THERM_STAT::M))
      {
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::FurnaceStatus, FurnaceStatus.c_str());
        RetValue = true;
      }
    }
    else if ( Message == EAF_EvMsg::evEAFTappingEnd )
    {
      //deassignProduct(Event);

      //initElectricalData();
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFPlantManager::changeComputerModes(CEventMessage& Event)
{
  bool RetValue = false;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      std::string DataKey    = Event.getDataKey();
      // Computer Modes will be stored under "Furnace"

      /* set initial values for sequence and struct */ 
      seqComputerModes AimSeq; 
      sComputerMode AimStruct ; 
      AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes));
  
      seqComputerModes SourceSeq ; 
      sComputerMode SourceStruct ; 
      SourceSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModes));

      // update data at m_pPlantManagementInterface with data m_pDataInterface
      UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,Device,std::string);

      m_pPlantManagementInterface->setComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes,AimSeq);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFPlantManager::changeAvailabilities(CEventMessage& Event)
{
  return CDM_PlantManager::changeAvailabilities(Event);
}

bool CDM_EAFPlantManager::changeBurningData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {

      //// copy incoming data to m_pPlantManagementInterface
      //CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
      //                                     m_pPlantManagementInterface,
      //                                     DataKey,
      //                                     DEF_PLANT::Furnace);

      //m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
      {
        seqGasLanceData ActBurnerFlow      = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerFlow));
        seqGasLanceData ActBurnerAmount    = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));

        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(DEF_PLANT::Furnace, DATA::BurnerFlow));
        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(DEF_PLANT::Furnace, DATA::BurnerAmount));

        // update product related data with actual values
        CGasLanceDataHandler BurnerFlowHandler      (BurnerFlow);
        CGasLanceDataHandler BurnerAmountHandler    (BurnerAmount);

        BurnerFlowHandler.update(ActBurnerFlow);
        BurnerAmountHandler.update(ActBurnerAmount);

        m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace, DATA::BurnerFlow          , BurnerFlowHandler.getGasLanceData());
        m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace, DATA::BurnerAmount        , BurnerAmountHandler.getGasLanceData());

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

         RetValue = true;

      }
      else if ( Message == EAF_EvMsg::evEAFBurnerStart || 
                Message == EAF_EvMsg::evEAFBurnerStop)
      {
        seqGasLanceData ActBurnerAmount       = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerAmount));
        seqGasLanceData ActBurnerFlow         = CIntfData::ToCORBAType(m_pDataInterface->getGasLanceData(DataKey.c_str(), DATA::BurnerFlow));
        seqStatus       ActBurnerStatus       = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::BurnerStatus));

        seqGasLanceData BurnerAmount       = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(DEF_PLANT::Furnace, DATA::BurnerAmount));
        seqGasLanceData BurnerFlow         = CIntfData::ToCORBAType(m_pPlantManagementInterface->getGasLanceData(DEF_PLANT::Furnace, DATA::BurnerFlow));
        seqStatus       BurnerStatus       = CIntfData::ToCORBAType(m_pPlantManagementInterface->getStatus      (DEF_PLANT::Furnace, DATA::BurnerStatus));

        CGasLanceDataHandler BurnerAmountHandler(BurnerAmount);
        BurnerAmountHandler.update(ActBurnerAmount);

        CGasLanceDataHandler BurnerFlowHandler  (BurnerFlow);
        BurnerFlowHandler.update(ActBurnerFlow);

        CStatusHandler StirrStatusHandler(BurnerStatus);
        StirrStatusHandler.update(ActBurnerStatus);

        m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace, DATA::BurnerAmount        , BurnerAmountHandler.getGasLanceData());
        m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace, DATA::BurnerFlow          , BurnerFlowHandler.getGasLanceData());
        m_pPlantManagementInterface->setStatus      (DEF_PLANT::Furnace, DATA::BurnerStatus        , StirrStatusHandler.getStatusData());

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }
      else if ( Message == EAF_EvMsg::evEAFBurnerGasAvail)
      {
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeBurningData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeBurningData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeBurningData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_EAFPlantManager::changeCoolingWaterData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey    = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << Event.getProductID() << ", " << Event.getHeatID()
    << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      // using CCoolWaterHandler due to cool water data might be transferred seperately for each colling water device
      seqCoolWaterData AimSeqCoolWaterData    = CIntfData::ToCORBAType(m_pPlantManagementInterface->getCoolWaterData(DEF_PLANT::Furnace, DATA::CoolingWaterData));
      seqCoolWaterData SourceSeqCoolWaterData = CIntfData::ToCORBAType(m_pDataInterface->getCoolWaterData(DataKey.c_str(), DATA::CoolingWaterData));

      CCoolWaterHandler CoolWaterHandler(AimSeqCoolWaterData);
      CoolWaterHandler.update(SourceSeqCoolWaterData);

      // save data
      m_pPlantManagementInterface->setCoolWaterData(DEF_PLANT::Furnace,DATA::CoolingWaterData, CoolWaterHandler.getCoolWaterData());

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      "CDM_EAFPlantManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_EAFPlantManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EAFPlantManager::changeCoolingWaterData()",
      ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_EAFPlantManager::changeLadleData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      if (Message == EAF_EvMsg::evEAFTapLadleData)
      {
        std::vector<std::string> NameList;
        // this value is set in DH_IN
        std::string EventSource = m_pDataInterface->getString(DataKey, DATA::MeasurementType);
        if (EventSource == DEF_CYCLIC_MEASUREMENT_TYPES::TapLadleStirring)
        {
          // copy Plant relevant data from Event interface
          NameList.push_back(DATA::LadleNo);
          NameList.push_back(DATA::LadleType);
          //NameList.push_back(DATA::TapLadleStirrFlow);
          //NameList.push_back(DATA::TapLadleStirrAmount);
          NameList.push_back(DATA::StirringGasType);
        }

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::TappingLadle,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::TappingLadle,4);

        RetValue = true;

      }
      //else if ( Message == EAF_EvMsg::evEAFLadleStirringStart || Message == EAF_EvMsg::evEAFLadleStirringStop  )
      //{
      //  m_pPlantManagementInterface->setLong(DEF_PLANT::TappingLadle,
      //                                       DATA::PlugNo,
      //                                       m_pDataInterface->getLong(DataKey, DATA::PlugNo));

      //  m_pPlantManagementInterface->setString(DEF_PLANT::TappingLadle,
      //                                         DATA::StirringGasType,
      //                                         m_pDataInterface->getString(DataKey,DATA::StirringGasType));

      //m_pPlantManagementInterface->setGasData(DEF_PLANT::TappingLadle,
      //                                        DATA::StirringAmount,
      //                                        CIntfData::ToCORBAType(m_pDataInterface->getGasData(DataKey.c_str(),DATA::StirringAmount)));
      //  RetValue = true;

      //}
      else if (Message == EAF_EvMsg::evEAFChangeTapLadleData)
      {
        // set tapping ladle of current heat 

        long LadleNo = m_pDataInterface->getLong(DataKey, DATA::LadleNo);
        std::string LadleType   = m_pDataInterface->getString(DataKey, DATA::LadleType);
        std::string LadleStatus = m_pDataInterface->getString(DataKey, DATA::LadleStatus);

        if (LadleNo != DEF::Inv_Long && LadleType != DEF::Inv_String)
        {
          m_pPlantManagementInterface->setLong(DEF_PLANT::TappingLadle,   DATA::LadleNo, LadleNo);
          m_pPlantManagementInterface->setString(DEF_PLANT::TappingLadle, DATA::LadleType, LadleType);
          m_pPlantManagementInterface->setString(DEF_PLANT::TappingLadle, DATA::LadleStatus, LadleStatus);
        }
        else
          log("EAFChangeTapLadleData: Invalid ladle received",1);

        m_pPlantManagementInterface->showContent(DEF_PLANT::TappingLadle,4);

        RetValue = true;

      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeLadleData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeLadleData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeLadleData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFPlantManager::changeStirringData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_EAFPlantManager::changeTappingData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string OrderID = Event.getOrderID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      if ( Message == EAF_EvMsg::evEAFTappingStart )
      {
        std::string ActProductFurnace = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::Furnace),DATA::ProductID);
        std::string ActProductTapping = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::TappingArea),DATA::ProductID);

        if (ActProductFurnace != DEF::Inv_String && !ActProductFurnace.empty())
        {
          // when heat in furnace is not equal to the heat in tapping area
          // move heat to tapping area
          if ( ActProductTapping.empty() || 
               ActProductTapping == DEF::Inv_String || 
               ActProductTapping != ActProductFurnace )
          {
            std::stringstream Message;
            Message << "Update heat data in tapping area. ProductID:" << ProductID;
            Message << " HeatID:"  << HeatID;
            Message << " TreatID:" << TreatID;
            Message << " OrderID:" << OrderID;

            log(Message.str(), 3);

            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::ProductID, ProductID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::HeatID,  HeatID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::TreatID, TreatID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::OrderId, OrderID);
          }
  
          m_pPlantManagementInterface->showContent(DEF_PLANT::TappingArea,4);
        }
        else
        {
          log("Invalid product in furnace :" + ActProductFurnace,1);
        }

      }
      else if ( Message == EAF_EvMsg::evEAFTappingEnd )
      {
        // if tapping start does not come

        std::string ActProductFurnace = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::Furnace),DATA::ProductID);
        std::string ActProductTapping = m_pPlantManagementInterface->getString(std::string(DEF_PLANT::TappingArea),DATA::ProductID);

        if (ActProductFurnace != DEF::Inv_String && !ActProductFurnace.empty())
        {
          // when heat in furnace is not equal to the heat in tapping area
          // move heat to tapping area
          if ( (ActProductTapping.empty() || 
                ActProductTapping == DEF::Inv_String) && 
                ActProductTapping != ActProductFurnace )
          {
            std::stringstream Message;
            Message << "Update heat data in tapping area. ProductID:" << ProductID;
            Message << " HeatID:"  << HeatID;
            Message << " TreatID:" << TreatID;
            Message << " OrderID:" << OrderID;

            log(Message.str(), 3);

            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::ProductID, ProductID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::HeatID,  HeatID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::TreatID, TreatID);
            m_pPlantManagementInterface->setString(DEF_PLANT::TappingArea, DATA::OrderId, OrderID);
          }
  
          m_pPlantManagementInterface->showContent(DEF_PLANT::TappingArea,4);
        }
        else
        {
          log("Invalid product in furnace :" + ActProductFurnace,1);
        }
      }

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeTappingData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_EAFPlantManager::changeBurningStatus(CEventMessage& Event, const std::string &BurningDevice,  long BurningStatus   )
{
  CDM_EAFTask::getInstance()->log("!!!!! CDM_EAFPlantManager::changeBurningStatus.. not implemented !", 9);
	return false;
}


bool CDM_EAFPlantManager::changeElectricalData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {

      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::ReactTapNo);
        NameList.push_back(DATA::VoltTapNo);
        NameList.push_back(DATA::ElectrodRegCurve);
        NameList.push_back(DATA::ElecCons);
        NameList.push_back(DATA::ElecPower);
        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::Furnace,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }
    }
    else if ( Message == EAF_EvMsg::evEAFPowerOn || EAF_EvMsg::evEAFPowerOff  )
    {
      std::vector<std::string> NameList;
      NameList.push_back(DATA::ReactTapNo);
      NameList.push_back(DATA::VoltTapNo);
      NameList.push_back(DATA::ElectrodRegCurve);
      NameList.push_back(DATA::ElecCons);
      
      CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                           m_pPlantManagementInterface,
                                           DataKey,
                                           DEF_PLANT::Furnace,
                                           NameList);

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

      RetValue = true;
    }
    else if ( Message == EAF_EvMsg::evEAFUpdatePlantStatus )
    {
      std::vector<std::string> NameList;
      NameList.push_back(DATA::FurnBreakOn);
      NameList.push_back(DATA::PowerOn);
      NameList.push_back(DATA::FurnTapChangOn);
      NameList.push_back(DATA::ElecPosUp);
      NameList.push_back(DATA::ReactTapNo); 
      NameList.push_back(DATA::VoltTapNo); 
      NameList.push_back(DATA::ElectrodRegCurve); 
      NameList.push_back(DATA::ElecCons);

      
      CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                           m_pPlantManagementInterface,
                                           DataKey,
                                           DEF_PLANT::Furnace,
                                           NameList);

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_EAFPlantManager::changeWasteGasData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {

      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::WasteGasConc);
        NameList.push_back(DATA::WasteGasFlow);
        NameList.push_back(DATA::WasteGasTemp);

        NameList.push_back(DATA::MomentO2);

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::Furnace,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeWasteGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeWasteGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeWasteGasData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_EAFPlantManager::changeGasData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey = Event.getDataKey();
  std::string Message = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {

      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
      {
        std::vector<std::string> NameList;
        NameList.push_back(DATA::GasLanceAmount);
        NameList.push_back(DATA::GasLanceFlow);
        //NameList.push_back(DATA::InjectLanceFlow);
        //NameList.push_back(DATA::StirringFlow);
        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::Furnace,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeGasData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

void CDM_EAFPlantManager::init(CDM_Task* pDMTask)
{

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Init Plant Manager: " ;

  try
  {
    // first of all call base class method to set
    // members
	  CDM_PlantManager::init(pDMTask);

    if ( m_pPlantManagementInterface )
    {
      m_pPlantManagementInterface->setPersistence(DEF_PLANT::Furnace,true);
      m_pPlantManagementInterface->setPersistence(DEF_PLANT::TappingLadle,true);

      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::RoofPosUp,   1); // up
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::GantryPosIn, 0); // out
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::SlagDoorOpen,1); // open

      // computer modes
      initComputerModes();

      // init electrical data
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::ReactTapNo,0);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::VoltTapNo,0);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::ElectrodRegCurve,0);
      m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::FurnaceStatus,DEF_GC_THERM_STAT::M);

      initElectricalData();

      // injection and gas data
      initInjectionData();
      initBurnerData();
      initGasLanceData();
      initWasteGasData(DEF_PLANT::Furnace);

      // cooling water
      initCoolingWaterData();

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }

}



void CDM_EAFPlantManager::initComputerModes()
{
  if ( m_pPlantManagementInterface )
  {
    // iterate over all mode entries
    seqComputerModes AimSeq ; 
    sComputerMode AimStruct ; 

    // prepare computer mode entries at m_pPlantManagementInterface with "empty" values
    std::vector<std::string>::iterator it;
    for ( it = m_ComputerModeList.begin(); it != m_ComputerModeList.end(); ++it)
    {
      AimStruct.Device = (*it).c_str();
      AimStruct.Status = DEF_GEN_STATES::Off;
      CIntfData::insert(AimSeq,AimStruct);
    }

    m_pPlantManagementInterface->setComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes,AimSeq);
  }
}



// for 
// DATA::InjectLanceAmount
// DATA::InjectLanceFlow
// DATA::EAFGasLanceAmount
// DATA::EAFGasLanceFlow
// ...
// for each member of m_BurnerDeviceList
// see contructor
//  m_BurnerDeviceList.push_back(DEF_BLOW_DEVICES::GasLance1);
//  m_BurnerDeviceList.push_back(DEF_BLOW_DEVICES::GasLance2);
// ..
// for each members of m_GasTypeList
// see contructor
//  m_GasTypeList.push_back(DEF_GC_STIRR_GAS_TYPE::Ar);
//  m_GasTypeList.push_back(DEF_GC_STIRR_GAS_TYPE::N2);
// ...

void CDM_EAFPlantManager::initBurnerData()
{
  if (m_pPlantManagementInterface)
  {
    // iterate over all device entries and
    // set amounts for each Gas entry to 0
    vector<std::string>::iterator itGasDataList;
    vector<std::string>::iterator itBurnerDeviceList;
    vector<std::string>::iterator itGasTypeList;

    // defining sequences
    seqGasLanceData     GasLanceDataSeq;
    seqGasLanceGasAvail GasLanceGasAvailSeq;
    seqStatus           StatusSeq;

    // for ech member of m_BurnerDeviceList
    for ( itBurnerDeviceList = m_BurnerDeviceList.begin() ; 
          itBurnerDeviceList != m_BurnerDeviceList.end() ; 
          ++itBurnerDeviceList)
    {
      std::string GasDevice = *itBurnerDeviceList; // should be GasLance1 ....

      // defining structures
      sStatus           StatusStruct;
      sGasLanceData     GasLanceDataStruct;
      sGasLanceGasAvail GasLanceGasAvailStruct;

      seqGasData  GasDataSeq;
      seqGasAvail GasAvailSeq;

      // search for all Gas types in actual member of m_GasTypeList
      for ( itGasTypeList = m_GasTypeList.begin() ; 
            itGasTypeList != m_GasTypeList.end() ; 
            ++itGasTypeList)
      {
        sGasData GasDataStruct;
        GasDataStruct.GasValue = 0.0;
        GasDataStruct.GasType = (*itGasTypeList).c_str(); // should be O2...

        CIntfData::insert(GasDataSeq,GasDataStruct);

        sGasAvail GasAvailStruct;
        GasAvailStruct.GasAvail = 0; // not available
        GasAvailStruct.GasType = (*itGasTypeList).c_str(); // should be O2...

        CIntfData::insert(GasAvailSeq,GasAvailStruct);

      } // for ( itGasTypeList = m_GasTypeList.begin() ; itGasTypeList != m_GasTypeList.end() ; ++itGasTypeList)

      GasLanceDataStruct.LanceData    = GasDataSeq;
      GasLanceDataStruct.Device       = GasDevice.c_str();
      CIntfData::insert(GasLanceDataSeq,GasLanceDataStruct);

      GasLanceGasAvailStruct.GasAvail = GasAvailSeq;
      GasLanceGasAvailStruct.Device   = GasDevice.c_str();
      CIntfData::insert(GasLanceGasAvailSeq,GasLanceGasAvailStruct);

      StatusStruct.Status = DEF_GEN_STATES::Off;
      StatusStruct.Device = GasDevice.c_str();
      CIntfData::insert(StatusSeq,StatusStruct);

    } // for ( itBurnerDeviceList = m_BurnerDeviceList.begin() ; 

    // write initialized data to m_pPlantManagementInterface
    m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace,DATA::BurnerFlow,GasLanceDataSeq);
    m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace,DATA::BurnerAmount,GasLanceDataSeq);

    m_pPlantManagementInterface->setGasLanceGasAvail(DEF_PLANT::Furnace,DATA::BurnerGasAvail,GasLanceGasAvailSeq);
    
    m_pPlantManagementInterface->setStatus(DEF_PLANT::Furnace,DATA::BurnerGasAvail,StatusSeq);
    m_pPlantManagementInterface->setStatus(DEF_PLANT::Furnace,DATA::BurnerStatus  ,StatusSeq);

  } // if (m_pPlantManagementInterface)
}

void CDM_EAFPlantManager::initGasLanceData()
{
  if (m_pPlantManagementInterface)
  {
    // iterate over all device entries and
    // set amounts for each Gas entry to 0
    vector<std::string>::iterator itGasDataList;
    vector<std::string>::iterator itLanceDeviceList;
    vector<std::string>::iterator itGasTypeList;

    // defining sequences
    seqGasLanceData     GasLanceDataSeq;
    seqGasLanceGasAvail GasLanceGasAvailSeq;
    seqStatus           StatusSeq;

    // for ech member of m_GasLanceDeviceList
    for ( itLanceDeviceList = m_GasLanceDeviceList.begin() ; 
          itLanceDeviceList != m_GasLanceDeviceList.end() ; 
          ++itLanceDeviceList)
    {
      std::string GasDevice = *itLanceDeviceList; // should be GasLance1 ....

      // defining structures
      sStatus           StatusStruct;
      sGasLanceData     GasLanceDataStruct;
      sGasLanceGasAvail GasLanceGasAvailStruct;

      seqGasData  GasDataSeq;
      seqGasAvail GasAvailSeq;

      // search for all Gas types in actual member of m_GasTypeList
      for ( itGasTypeList = m_GasTypeList.begin() ; 
            itGasTypeList != m_GasTypeList.end() ; 
            ++itGasTypeList)
      {
        sGasData GasDataStruct;
        GasDataStruct.GasValue = 0.0;
        GasDataStruct.GasType = (*itGasTypeList).c_str(); // should be O2...

        CIntfData::insert(GasDataSeq,GasDataStruct);

        sGasAvail GasAvailStruct;
        GasAvailStruct.GasAvail = 0; // not available
        GasAvailStruct.GasType = (*itGasTypeList).c_str(); // should be O2...

        CIntfData::insert(GasAvailSeq,GasAvailStruct);

      } // for ( itGasTypeList = m_GasTypeList.begin() ; itGasTypeList != m_GasTypeList.end() ; ++itGasTypeList)

      GasLanceDataStruct.LanceData    = GasDataSeq;
      GasLanceDataStruct.Device       = GasDevice.c_str();
      CIntfData::insert(GasLanceDataSeq,GasLanceDataStruct);

      GasLanceGasAvailStruct.GasAvail = GasAvailSeq;
      GasLanceGasAvailStruct.Device   = GasDevice.c_str();
      CIntfData::insert(GasLanceGasAvailSeq,GasLanceGasAvailStruct);

      StatusStruct.Status = DEF_GEN_STATES::Off;
      StatusStruct.Device = GasDevice.c_str();
      CIntfData::insert(StatusSeq,StatusStruct);

    } // for ( itLanceDeviceList = m_GasLanceDeviceList.begin() ; 

    // write initialized data to m_pPlantManagementInterface
    m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace,DATA::GasLanceFlow,GasLanceDataSeq);
    m_pPlantManagementInterface->setGasLanceData(DEF_PLANT::Furnace,DATA::GasLanceAmount,GasLanceDataSeq);

    m_pPlantManagementInterface->setGasLanceGasAvail(DEF_PLANT::Furnace,DATA::GasLanceGasAvail,GasLanceGasAvailSeq);
    
    m_pPlantManagementInterface->setStatus(DEF_PLANT::Furnace,DATA::GasLanceGasAvail,StatusSeq);
    m_pPlantManagementInterface->setStatus(DEF_PLANT::Furnace,DATA::GasLanceStatus  ,StatusSeq);

  } // if (m_pPlantManagementInterface)
}


void CDM_EAFPlantManager::initElectricalData()
{
  if (m_pPlantManagementInterface)
  {
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::ElecPosUp,1);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::FurnBreakOn,0);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::PowerOn,0);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::FurnTapChangOn,0);

    m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace,DATA::ElecCons,0.0);
    m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace,DATA::MomentO2,0.0);
  }
}

void CDM_EAFPlantManager::initInjectionData()
{
  bool RetValue = false;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: initInjectionData";

  try
  {
    if (m_pDataInterface && m_pPlantManagementInterface )
    {
      seqInjectLanceData InjectLanceDataSeq;
      sInjectLanceData InjectLanceDataStruct;

      // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    = DEF_GCE_INJECTION::Carbon_Injector.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::CarbonInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

       // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    = DEF_GCE_INJECTION::Oxygen_Injector_1.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::OxygenInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

      // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    = DEF_GCE_INJECTION::Oxygen_Injector_2.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::OxygenInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

      // init Injection Lance Data sequence
      InjectLanceDataStruct.Device    = DEF_GCE_INJECTION::Silicon_Injector.c_str();
      InjectLanceDataStruct.Value     = 0.0;
      InjectLanceDataStruct.MatCode   = "";
      InjectLanceDataStruct.InjectionType = DEF_GCE_INJECTION_TYPE::SiliconInjection.c_str();
      CIntfData::insert(InjectLanceDataSeq,InjectLanceDataStruct);

      m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace,
                                                      DATA::InjectLanceFlow,
                                                      InjectLanceDataSeq);
      m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace,
                                                      DATA::InjectLanceAmount,
                                                      InjectLanceDataSeq);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"");
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::initElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"");
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::initElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"");
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::initElectricalData()",
                                         ExceptionMsg.str().c_str());
  } 
}

void CDM_EAFPlantManager::initCoolingWaterData()
{
  if (m_pPlantManagementInterface)
  {
    // Cooling water
    seqCoolWaterData CoolWaterData;
    sCoolWaterDevice CoolWaterDevice;

    // init flow data
    sCoolWater CoolWater;
	  CoolWater.OutletTemp  = 0.0;
	  CoolWater.InletTemp   = 0.0;
    CoolWater.WaterFlow   = 0.0;

    CoolWaterDevice.CoolWaterDeviceNo = 0;
    CoolWaterDevice.CoolWaterData = CoolWater;

    // init data per cool water device
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::BottomLoop.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::CoverBay.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::Dedusting.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::DoorPanel.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::DoorTunelPanel.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::Elbow.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::LowerWall.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::Roof.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::UpperWall.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::Wall.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::WallLowPanelLoop.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::WallUpPanelLoop.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);

    m_pPlantManagementInterface->setCoolWaterData(DEF_PLANT::Furnace,DATA::CoolingWaterData,CoolWaterData);
  } // if (m_pPlantManagementInterface)
}



bool CDM_EAFPlantManager::changeInjectionData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey    = Event.getDataKey();
  std::string Message    = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      if ( Message == EAF_EvMsg::evEAFCyclicMeasurement  )
      {
        seqInjectLanceData ActInjectLancerFlow     = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData ActInjectLanceAmount    = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount));
          
        seqInjectLanceData InjectLanceFlow         = CIntfData::ToCORBAType(m_pPlantManagementInterface->getInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceFlow));
        seqInjectLanceData InjectLanceAmount       = CIntfData::ToCORBAType(m_pPlantManagementInterface->getInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceAmount));

        // update product related data with actual values
        CInjectLanceDataHandler InjectLanceFlowHandler;
        InjectLanceFlowHandler.fill(InjectLanceFlow);

        CInjectLanceDataHandler InjectLanceAmountHandler;
        InjectLanceAmountHandler.fill(InjectLanceAmount);

        InjectLanceFlowHandler.update(ActInjectLancerFlow);
        InjectLanceAmountHandler.update(ActInjectLanceAmount);

        m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceFlow          , InjectLanceFlowHandler.getInjectLanceData());
        m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceAmount        , InjectLanceAmountHandler.getInjectLanceData());

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }
       // react on special event
      else if ( Message == EAF_EvMsg::evEAFCarbonInjectStart || Message == EAF_EvMsg::evEAFCarbonInjectStop )
      {
        seqInjectLanceData ActInjectLancerFlow     = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow));
        seqInjectLanceData ActInjectLanceAmount    = CIntfData::ToCORBAType(m_pDataInterface->getInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount));
        seqStatus          ActInjectLanceStatus    = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::InjectorStatus));
     
        seqInjectLanceData InjectLanceFlow         = CIntfData::ToCORBAType(m_pPlantManagementInterface->getInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceFlow));
        seqInjectLanceData InjectLanceAmount      = CIntfData::ToCORBAType(m_pPlantManagementInterface->getInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceAmount));
        seqStatus          InjectLanceStatus      = CIntfData::ToCORBAType(m_pPlantManagementInterface->getStatus         (DEF_PLANT::Furnace, DATA::InjectorStatus));

        // update product related data with actual values
        CInjectLanceDataHandler InjectLanceFlowHandler;
        InjectLanceFlowHandler.fill(InjectLanceFlow);

        CInjectLanceDataHandler InjectLanceAmountHandler;
        InjectLanceAmountHandler.fill(InjectLanceAmount);

        InjectLanceFlowHandler.update(ActInjectLancerFlow);
        InjectLanceAmountHandler.update(ActInjectLanceAmount);

        CStatusHandler InjectLanceStatusHandler(InjectLanceStatus);
        InjectLanceStatusHandler.update(ActInjectLanceStatus);

        m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceFlow          , InjectLanceFlowHandler.getInjectLanceData());
        m_pPlantManagementInterface->setInjectLanceData(DEF_PLANT::Furnace, DATA::InjectLanceAmount     , InjectLanceAmountHandler.getInjectLanceData());
        m_pPlantManagementInterface->setStatus         (DEF_PLANT::Furnace, DATA::InjectorStatus        , InjectLanceStatusHandler.getStatusData());

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

void CDM_EAFPlantManager::resetPlantManager(CEventMessage &Event)
{
  if ( m_pPlantManagementInterface )
  {
    m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace,DATA::ElecCons,0.0);
    m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace,DATA::MomentO2,0.0);
  }

  resetComputerModes(Event);

  initInjectionData();
  initBurnerData();
  initGasLanceData();
  initWasteGasData(DEF_PLANT::Furnace);
}

void CDM_EAFPlantManager::resetComputerModes(CEventMessage& Event)
{
  std::string DataKey    = Event.getDataKey();
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
              << ", " << Event.getProductID() << ", " << Event.getHeatID()
              << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if ( m_pPlantManagementInterface )
    {
      seqComputerModes AimSeq ; 
      sComputerMode AimStruct ; 

      AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModeAvail));

      // set computer modes to normal state 
      for ( long i = 0 ; i < CIntfData::getLength(AimSeq); ++i )
      {
        CIntfData::getAt(AimStruct,AimSeq,i);
        std::string ActDevice = AimStruct.Device;

        if ( ActDevice == DEF_COMP_MODES::Electric    || 
             ActDevice == DEF_COMP_MODES::GasLance    || 
             ActDevice == DEF_COMP_MODES::Injection   || 
             ActDevice == DEF_COMP_MODES::MatHandle   || 
             ActDevice == DEF_COMP_MODES::Stirring    ||
             ActDevice == DEF_COMP_MODES::Burner      || 
             ActDevice == DEF_COMP_MODES::DynamicFeed || 
             ActDevice == DEF_COMP_MODES::PatternFeed ||
             ActDevice == DEF_COMP_MODES::TappingBatch ) 
        {
          AimStruct.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
        }
        else
        {
          AimStruct.Status = DEF_GC_COMP_STATUS::ManualMode;
        }

        CIntfData::setAt(AimSeq,AimStruct,i);

      }

      m_pPlantManagementInterface->setComputerModes(DEF_PLANT::Furnace,DATA::ComputerModeAvail,AimSeq);

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
}

// Copyright (C) 2005 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "CDM_LFTask.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogLFController.h"

#include "CStatusHandler.h"
#include "CCoolWaterHandler.h"

#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_STIRR_DEVICE.h"
#include "DEF_GC_COMP_STATUS.h"

#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_LFPlantManager.h"

CDM_LFPlantManager::~CDM_LFPlantManager()
{
}

CDM_LFPlantManager::CDM_LFPlantManager()
{
  // fill GasNames into respective container
  m_GasTypeList.push_back(DEF_GAS::Ar);
  m_GasTypeList.push_back(DEF_GAS::N2);
  m_GasTypeList.push_back(DEF_GAS::O2);

  m_ComputerModeList.push_back(DEF_COMP_MODES::Electric);
  m_ComputerModeList.push_back(DEF_COMP_MODES::ElectricModel);
  m_ComputerModeList.push_back(DEF_COMP_MODES::Level2Error);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandleL1Error);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandleModel);
  m_ComputerModeList.push_back(DEF_COMP_MODES::RejectHeatL1);
  m_ComputerModeList.push_back(DEF_COMP_MODES::Stirring);
  m_ComputerModeList.push_back(DEF_COMP_MODES::StirringModel);

  m_TransferCarPlantIdList.insert(std::pair<std::string,std::string>("1",DEF_PLANT::TransferCar1));
  m_TransferCarPlantIdList.insert(std::pair<std::string,std::string>("2",DEF_PLANT::TransferCar2));
}

bool CDM_LFPlantManager::changePlantInformation(CEventMessage& Event)
{
  std::string ProductID = Event.getProductID();
  std::string HeatID = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string OrderID = Event.getOrderID();
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();


  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();

  try
  {
    if ( Message == LF_EvMsg::evLFModelResultActualSetpoints || 
         Message == LF_EvMsg::evLFModelResultRecipeSetpoints )
    {
      if ( m_pPlantManagementInterface && m_pDataInterface )
      {
        // ****************************************************************
        // moved to product Manager due to request could appear per product
        // ****************************************************************

        //// check status for pulling electrodes
        //long ElecPullReq = m_pDataInterface->getLong(DataKey.c_str(), DATA::ElecPullReq);
        //
        //if (StatusHandler.isStatusChanged(PlantID.c_str(), DATA::ElecPullReq, ElecPullReq))
        //{
        //  if (ElecPullReq == DEF_GEN_STATES::Yes)
        //  {
        //    addEventMessageToSend(LF_EvMsg::evLFPullElectrodeRequest);
        //  }
        //}
        //m_pPlantManagementInterface->setLong(PlantID.c_str(), DATA::ElecPullReq, ElecPullReq);

        //// check status for releasing/inhibiting electrodes
        //long ElecInhibitReq = m_pDataInterface->getLong(DataKey.c_str(), DATA::ElecInhibitReq);
        //if (StatusHandler.isStatusChanged(PlantID.c_str(), DATA::ElecInhibitReq, ElecInhibitReq))
        //{
        //  if (ElecInhibitReq == DEF_GEN_STATES::Yes)
        //  {
        //    addEventMessageToSend(LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest);
        //  }
        //  else
        //  {
        //    addEventMessageToSend(LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest);
        //  }
        //}
        //
        //m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::ElecInhibitReq, ElecInhibitReq);
      }
    }

    else if ( Message == LF_EvMsg::evLFHeatAnnouncement )
    {
      resetPlantManager(Event);

      // assign data to respective tranfercar
      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        std::string LadleType   = m_pDataInterface->getString(DataKey,DATA::LadleType);
        long LadleNo            = m_pDataInterface->getLong(DataKey,DATA::LadleNo);

        std::string LadleTransferCarId = m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId);
        
        // covert from number to DEF_PLANT::TransferCarXY
        std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::LadleTransferCarId,LadleTransferCarId);
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::LadleType,LadleType);
        m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleNo,LadleNo);

        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::ProductID,ProductID);
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::HeatID,HeatID);
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::TreatID,TreatID);
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::OrderId,OrderID);
      }
    }
    else if ( Message == LF_EvMsg::evLFHeatAnnounceStatus || 
              Message == LF_EvMsg::evLFHeatAnnounceStatusOffline  )
    {
      // check model status, if necessarry deassign heat from plantmanager
      if (m_pDataInterface)
      {
        long HeatAnnounceStatus = m_pDataInterface->getLong(Event.getDataKey(),DATA::HeatAnnounceStatus);
        
        // HeatAnnounceStatus == 0 means prediction not successful !
        if ( 0 == HeatAnnounceStatus )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
          pEventLog->EL_PredictionCalculationError(sMessage,m_pDMTask->getExternalHeatID(ProductID).c_str(),m_pDMTask->getExternalTreatID(ProductID).c_str(),PlantID.c_str());
        }
      }
    }
    else if ( Message == LF_EvMsg::evLFHeatDeparture || 
              Message == LF_EvMsg::evLFHeatCancellation )
    {
      // deassign product from model
      deassignProduct(Event);

      // delete actual transfercar at operating position
      if (m_pPlantManagementInterface)
      {
        std::string LadleTransferCarId = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);

        if ( LadleTransferCarId.empty() || LadleTransferCarId == DEF::Inv_String )
        {
          log("INFO: get transfer car number from product",3);
          LadleTransferCarId = getPlantEquipmentOfProduct(ProductID);
        }

        // covert from number to DEF_PLANT::TransferCarXY
        std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::ProductID,"");
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::HeatID,"");
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::TreatID,"");
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::OrderId,"");

        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::LadleTransferCarId,"");
        m_pPlantManagementInterface->setString(TransferCarPlantId,DATA::LadleType,"");
        m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleNo,0);

      }
      
      // reset e.g. computer modes and stirring data for respective TransferCar
      resetPlantManager(Event);

    }
    else if ( Message == LF_EvMsg::evLFGantrySwungOut )
    {
      // the (only) car in operatind position (electrical ernergy input) is characterized by 
      // DATA::LadleTransferCarInOperatingPosition with entries DATA::LadleTransferCarId ( "1" or "2" )

      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition,"");
      }

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);
    }

    // depending on LF contruction, gantry is turning form Position1 to Position2 
    // or roof moves only up and down
    // in both cases the transfercar in this situation is the one in operating postition !
    else if ( Message == LF_EvMsg::evLFGantrySwungIn || 
              Message == LF_EvMsg::evLFRoofArrivesInDownPosition )
    {
      // the (only) car in operating position (electrical ernergy input) is characterized by 
      // DATA::LadleTransferCarInOperatingPosition with entries DATA::LadleTransferCarId ( "1" or "2" )

      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);
        long GantryPosIn                = m_pDataInterface->getLong(Event.getDataKey()  , DATA::GantryPosIn);

        // covert from number to DEF_PLANT::TransferCarXY
        std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

        if ( !TransferCarPlantId.empty() )
        {

          m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition,LadleTransferCarId);
          m_pPlantManagementInterface->setLong  (DEF_PLANT::Furnace, DATA::GantryPosIn,GantryPosIn);
          

          // now the car itself is located under the roof 
          // the car itself is now in DEF_CARPOSITION::OperationPositon
          m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleCarPosition,DEF_CARPOSITION::OperationPositon);
        }

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);
        m_pPlantManagementInterface->showContent(TransferCarPlantId,4);
      }
    }
    else if ( Message == LF_EvMsg::evLFMaintenance )
    {
      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        long GantryPosIn                = m_pDataInterface->getLong(Event.getDataKey()  , DATA::GantryPosIn);

        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition,"");
        m_pPlantManagementInterface->setLong  (DEF_PLANT::Furnace, DATA::GantryPosIn,GantryPosIn);

      }

      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

    }
    else if ( Message == LF_EvMsg::evLFTransferCarPositionChanged )
    {
      // depending on LF construction, two transfercars may be in operating position at the same time
      // chracterized by DATA::LadleCarPosition with following states 
      // DEF_CARPOSITION::
      // - OperationPositon = 1;
      // - DeslagPosition = 2;
      // - OutOfOperatingPosition = 0;


      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);
        long LadleCarPosition           = m_pDataInterface->getLong(Event.getDataKey()  , DATA::LadleCarPosition);

        // for now both positions must be reseted !!!! should be furnace I think !!
        if ( LadleTransferCarId == "0")
        {
          LadleTransferCarId = "1";

          std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

          // update tranfer car data for the respecive TransferCar
          m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleCarPosition,LadleCarPosition);

          LadleTransferCarId = "2";

          // covert from number to DEF_PLANT::TransferCarXY
          TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

          // update tranfer car data for the respecive TransferCar
          m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleCarPosition,LadleCarPosition);

          m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition,"");
        }
        else
        {
          std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

          if ( !TransferCarPlantId.empty() )
          {
            m_pPlantManagementInterface->setString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition,LadleTransferCarId);
          }

          // update tranfer car data for the respecive TransferCar
          m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleCarPosition,LadleCarPosition);
        }
      }
      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);
    }
    else if ( Message == LF_EvMsg::evLFRoofArrivesInUpPosition )
    {
      std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);
      // convert from number to DEF_PLANT::TransferCarXY
      std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

      if ( !TransferCarPlantId.empty() )
      {
        m_pPlantManagementInterface->setLong(TransferCarPlantId, DATA::RoofPosUp, DEF_GEN_STATES::On);

        // now the car itself is located under the roof but it is lifted
        // the car itself is now in DEF_CARPOSITION::OutOfOperatingPosition
        if ( !TransferCarPlantId.empty() )
        {
          m_pPlantManagementInterface->setLong(TransferCarPlantId,DATA::LadleCarPosition,DEF_CARPOSITION::OutOfOperatingPosition);
        }
      }
      m_pPlantManagementInterface->showContent(TransferCarPlantId,4);

    }
    else if ( Message == LF_EvMsg::evLFRoofArrivesInDownPosition )
    {
      std::string LadleTransferCarId  = m_pDataInterface->getString(Event.getDataKey(), DATA::LadleTransferCarId);

      // convert from number to DEF_PLANT::TransferCarXY
      std::string TransferCarPlantId = getPlantEquipmentData(LadleTransferCarId);

      m_pPlantManagementInterface->setLong(TransferCarPlantId, DATA::RoofPosUp, DEF_GEN_STATES::Off);

      m_pPlantManagementInterface->showContent(TransferCarPlantId,4);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_LFPlantManager::changeComputerModes(CEventMessage& Event)
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

      // data must be stored per transfercar
      std::string TransferCarPlantId = getRelevantTransferCar(Event);

      if ( TransferCarPlantId != DEF::Inv_String )
      {
        /* set initial values for sequence and struct */ 
        seqComputerModes AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(TransferCarPlantId.c_str(),DATA::ComputerModes)); 
        sComputerMode AimStruct ; 
    
        seqComputerModes SourceSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModes)); 
        sComputerMode SourceStruct ; 

        // update data at m_pPlantManagementInterface with data m_pDataInterface
        UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,Device,std::string);

        m_pPlantManagementInterface->setComputerModes(TransferCarPlantId.c_str(),DATA::ComputerModes,AimSeq);

        Event.setDataKey(TransferCarPlantId);
      }

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFPlantManager::changeAvailabilities(CEventMessage& Event)
{
  return CDM_PlantManager::changeAvailabilities(Event);
}

bool CDM_LFPlantManager::changeLadleData(CEventMessage& Event)
{
  return CDM_PlantManager::changeLadleData(Event);
}

bool CDM_LFPlantManager::changeStirringData(CEventMessage& Event)
{
  // read data from ProductManagement INterface related with "productID" and write
  // data for LadleTransferCar to PlantManagementInterface

  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    // search existing data at m_pPlantManagementInterface 
    if ( m_pDataInterface && m_pPlantManagementInterface )
    {

      if ( Message == LF_EvMsg::evLFCyclicMeasurement         || 
           Message == LF_EvMsg::evLFBottomStirringEnd         ||
           Message == LF_EvMsg::evLFBottomStirringByPassOff   ||
           Message == LF_EvMsg::evLFBottomStirringStart       ||
           Message == LF_EvMsg::evLFBottomStirringByPassOn )
      {
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());

  }
  return RetValue;
}
 
bool CDM_LFPlantManager::changeTappingData(CEventMessage& Event)
{
	return CDM_PlantManager::changeTappingData(Event);
}

bool CDM_LFPlantManager::changeTransferCarData(CEventMessage& Event)
{
  return false;
}

void CDM_LFPlantManager::resetPlantManager(CEventMessage& Event)
{
  // reset data for actual ztransfercar only !
  std::string TransferCarPlantId = getRelevantTransferCar(Event);

  if ( TransferCarPlantId != DEF::Inv_String )
  {
    if ( m_pPlantManagementInterface )
    {
      m_pPlantManagementInterface->setLong(TransferCarPlantId, DATA::VoltTapNo,0);
      m_pPlantManagementInterface->setLong(TransferCarPlantId, DATA::ElectrodRegCurve,0);
      m_pPlantManagementInterface->setDouble(TransferCarPlantId, DATA::ElecCons,0.0);

      // in case of two roofs we have to track each related to transfer car
      m_pPlantManagementInterface->setLong(TransferCarPlantId, DATA::RoofPosUp,DEF_GEN_STATES::On);
    }
    // resets data for actual transfercar only !

    // calls initTransferCarComputerModeData for respective transfercar
    resetComputerModes(Event);
    // calls initTransferCarStirringData for respective transfercar
    resetStirringData(Event);
  }

  m_pPlantManagementInterface->showContent("",4);
}

void CDM_LFPlantManager::resetComputerModes(CEventMessage& Event)
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
      // reset all data for respective transfer car
      std::string TransferCarPlantId = getRelevantTransferCar(Event);

      if ( TransferCarPlantId != DEF::Inv_String )
      {
        initTransferCarComputerModeData(TransferCarPlantId);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
}


bool CDM_LFPlantManager::changeWasteGasData(CEventMessage& Event)
{
  // changing Waste gas
  // WasteGasConc
  // WastGasFlow
  // WastGasTemp

	return CDM_PlantManager::changeWasteGasData(Event);
}



bool CDM_LFPlantManager::changeCoolingWaterData(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Message   = Event.getMessage();
  std::string PlantID   = Event.getPlantID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;

  try
  {
    if (m_pDataInterface && m_pPlantManagementInterface)
    {
      if ( Message == LF_EvMsg::evLFCyclicMeasurement ) // data are not heat / product related !!!
      {
        // read car of heat 
        std::string LadleTransferCarId = getRelevantTransferCar(Event);

        // using CCoolWaterHandler due to cool water data might be transferred seperately for each colling water device
        seqCoolWaterData AimSeqCoolWaterData    = CIntfData::ToCORBAType(m_pPlantManagementInterface->getCoolWaterData(LadleTransferCarId.c_str(), DATA::CoolingWaterData));
        seqCoolWaterData SourceSeqCoolWaterData = CIntfData::ToCORBAType(m_pDataInterface->getCoolWaterData(DataKey.c_str(), DATA::CoolingWaterData));

        CCoolWaterHandler CoolWaterHandler(AimSeqCoolWaterData);
        CoolWaterHandler.update(SourceSeqCoolWaterData);

        // save data
        m_pPlantManagementInterface->setCoolWaterData(LadleTransferCarId.c_str(),DATA::CoolingWaterData, CoolWaterHandler.getCoolWaterData());

        m_pPlantManagementInterface->showContent(LadleTransferCarId,4);

      }

      RetValue = true;

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::changeCoolingWaterData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::changeCoolingWaterData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::changeCoolingWaterData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFPlantManager::changeElectricalData(CEventMessage& Event)
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
    if (m_pDataInterface && m_pPlantManagementInterface)
    {
      if ( Message == LF_EvMsg::evLFCyclicMeasurement )
      {

        std::string TransferCarPlantId = getRelevantTransferCar(Event);

        if ( TransferCarPlantId != DEF::Inv_String )
        {
          // copy data from Event interface for TransferCar
          std::vector<std::string> NameList;
          NameList.push_back(DATA::VoltTapNo);                       // long
          NameList.push_back(DATA::ElectrodRegCurve);                   // long
          NameList.push_back(DATA::ElecCons);                        // double

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                               m_pPlantManagementInterface,
                                               DataKey,
                                               TransferCarPlantId,
                                               NameList);

          m_pPlantManagementInterface->showContent(TransferCarPlantId,4);
        }

        RetValue = true;
      }
      else if ( Message == LF_EvMsg::evLFTapChangeStart ||  
                Message == LF_EvMsg::evLFTapChangeFinished ||
                Message == LF_EvMsg::evLFImpCurveChanged )
      {

        // copy data from Event interface for Plant
        std::vector<std::string> NameList;
        NameList.push_back(DATA::FurnBreakOn);
        NameList.push_back(DATA::PowerOn);
        NameList.push_back(DATA::FurnTapChangOn);
        NameList.push_back(DATA::ElecPosUp);
        NameList.push_back(DATA::GantryPosIn);
        NameList.push_back(DATA::ElecInhibit);
        NameList.push_back(DATA::VoltTapNo);
        NameList.push_back(DATA::ElectrodRegCurve);
        NameList.push_back(DATA::ElecCons);                        // double

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::Furnace,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,4);

        RetValue = true;
      }
      else if ( Message == LF_EvMsg::evLFUpdatePlantStatus )
      {
        std::vector<std::string> NameList;

        NameList.push_back(DATA::FurnBreakOn     );
        NameList.push_back(DATA::PowerOn         );
        NameList.push_back(DATA::FurnTapChangOn  );
        NameList.push_back(DATA::ElecPosUp       );
        NameList.push_back(DATA::GantryPosIn     );
        NameList.push_back(DATA::ElecInhibit     );
        NameList.push_back(DATA::VoltTapNo       );
        NameList.push_back(DATA::ElectrodRegCurve   );
        NameList.push_back(DATA::ElecCons        );

      
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
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}



std::string CDM_LFPlantManager::getProductAtPlantEquipment(const std::string& Equipment)
{
  std::string ProductID = DEF::Inv_String;

  // convert from number to DEF_PLANT::TransferCarXY
  std::string TransferCarPlantId = getPlantEquipmentData(Equipment);

  if (m_pPlantManagementInterface)
  {
    ProductID = m_pPlantManagementInterface->getString(TransferCarPlantId,DATA::ProductID);
  }

  return ProductID;
}

std::string CDM_LFPlantManager::getPlantEquipmentOfProduct(const std::string& ProductID)
{
  std::string RetValue;
  std::map<std::string,std::string>::iterator it;

  for( it = m_TransferCarPlantIdList.begin() ; it != m_TransferCarPlantIdList.end(); ++ it )
  {
    std::string DataKey = it->second;

    std::string ActProductID = m_pPlantManagementInterface->getString(DataKey,DATA::ProductID);

    if ( ActProductID == ProductID && ActProductID != DEF::Inv_String )
    {
      RetValue = it->first;
    }
  }

  if ( RetValue.empty() )
  {
	  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_EquipmentIdentification(sMessage);
  }


  return RetValue;
}


std::string CDM_LFPlantManager::getPlantEquipmentData(const std::string& Equipment)
{
  // convert from number to DEF_PLANT::TransferCarXY

  std::string RetValue;
  std::map<std::string,std::string>::iterator it;

  it = m_TransferCarPlantIdList.find(Equipment);

  if ( it != m_TransferCarPlantIdList.end() )
  {
    RetValue = it->second;
  }
  else
  {
	  CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorTransferCarIdentification(sMessage,Equipment.c_str());
  }

  return RetValue;
}



void CDM_LFPlantManager::resetStirringData(CEventMessage& Event)
{
  // read data from ProductManagement INterface related with "productID" and write
  // data for LadleTransferCar to PlantManagementInterface
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    // search existing data at m_pPlantManagementInterface 
    if ( m_pDataInterface && m_pPlantManagementInterface )
    {
      // reset all data for respective transfer car
      std::string TransferCarPlantId = getRelevantTransferCar(Event);

      if ( TransferCarPlantId != DEF::Inv_String )
      {
        initTransferCarData(TransferCarPlantId);
        initTransferCarStirringData(TransferCarPlantId);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
}



std::string CDM_LFPlantManager::getRelevantTransferCar(CEventMessage& Event)
{
  std::string RetValue;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    // search existing data at m_pPlantManagementInterface 
    if ( m_pDataInterface  )
    {
      // reset all data for respective transfer car
      std::string LadleTransferCarId  = m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId);

      // if no transfer car avaiable at data interface
      // use product information of heat announcement
      if ( LadleTransferCarId == DEF::Inv_String || LadleTransferCarId.empty())
      {
        if ( CDM_LFTask::getInstance()->getpProductManagementInterface() )
        {
          LadleTransferCarId = CDM_LFTask::getInstance()->getpProductManagementInterface()->
            getString(ProductID,DATA::LadleTransferCarId);
        }
      }

      // if heat announcement does not provide LadleTransferCarId 
      // usa actual transfercar in operating position
      if ( LadleTransferCarId == DEF::Inv_String || LadleTransferCarId.empty())
      {
        LadleTransferCarId = m_pPlantManagementInterface->getString(DEF_PLANT::Furnace,
                                                                    DATA::LadleTransferCarInOperatingPosition);
      }

      if ( LadleTransferCarId == DEF::Inv_String || LadleTransferCarId.empty())
      {
	      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
        pEventLog->EL_NoTransferCarInOperatingPosition(sMessage);
      }
      else  // some valid data found
      {
        // convert from number to DEF_PLANT::TransferCarXY
        RetValue = getPlantEquipmentData(LadleTransferCarId);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::searchForTransferCar()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::searchForTransferCar()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::searchForTransferCar()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}



void CDM_LFPlantManager::init(CDM_Task* pDMTask)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Init Plant Manager: " ;

  try
  {

    // first of all call base class method to set
    // members
	  CDM_PlantManager::init(pDMTask);

    // set plant to initial state
    if ( m_pPlantManagementInterface )
    {
      m_pPlantManagementInterface->setPersistence(DEF_PLANT::Furnace,true);
      m_pPlantManagementInterface->setPersistence(DEF_PLANT::TransferCar1,true);
      m_pPlantManagementInterface->setPersistence(DEF_PLANT::TransferCar2,true);
    }


    // init transfercar data for each transfercar
    std::map<std::string,std::string>::iterator it;
    
    for( it = m_TransferCarPlantIdList.begin() ; it != m_TransferCarPlantIdList.end(); ++ it )
    {
      initTransferCarData(it->second);
      initTransferCarStirringData(it->second);
      initTransferCarComputerModeData(it->second);

      // voltTap and eltrdRegCurve should be initial for furnace data
      m_pPlantManagementInterface->setLong(it->second, DATA::VoltTapNo,0);
      m_pPlantManagementInterface->setLong(it->second, DATA::ElectrodRegCurve,0);

      m_pPlantManagementInterface->setDouble(it->second, DATA::ElecCons,0.0);
      // in case of two roofs we have to track each related to transfer car
      m_pPlantManagementInterface->setLong(it->second, DATA::RoofPosUp,DEF_GEN_STATES::On);

      initCoolingWaterData(it->second);
    }

    // ElecCons should be initial for TransferCarPlantId data
    m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::ElecCons,0.0);
    
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::VoltTapNo,0);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::ElectrodRegCurve,0);

    // Plant
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::ElecPosUp,DEF_GEN_STATES::On);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::FurnBreakOn,DEF_GEN_STATES::Off);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::FurnTapChangOn,DEF_GEN_STATES::Off);
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::PowerOn,DEF_GEN_STATES::Off);
    
    m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::GantryPosIn,DEF_GANTRY_POS::Maintenance);

    initWasteGasData(DEF_PLANT::Furnace);

    m_pPlantManagementInterface->showContent("",4);

  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }

}

void CDM_LFPlantManager::initTransferCarStirringData(const std::string& DataKey)
{
  // string
  m_pPlantManagementInterface->setString(DataKey,DATA::StirringGasType,"");  
  // long
  m_pPlantManagementInterface->setLong(DataKey,DATA::LadlePlugNo,0);

  m_pPlantManagementInterface->setLong(DataKey,DATA::StirringBypassStatus,DEF_GEN_STATES::Off);                
}

void CDM_LFPlantManager::initTransferCarComputerModeData(const std::string& DataKey)
{
  if (m_pPlantManagementInterface)
  {
    seqComputerModes AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModeAvail)); 
    sComputerMode AimStruct ; 

    // prepare computer mode entries at m_pPlantManagementInterface with "empty" values
    if ( CIntfData::getLength(AimSeq) == 0 )
    {
      std::vector<std::string>::iterator it;
      for ( it = m_ComputerModeList.begin(); it != m_ComputerModeList.end(); ++it)
      {
        AimStruct.Device = (*it).c_str();
        AimStruct.Status = DEF_GEN_STATES::NotAvailable;
        CIntfData::insert(AimSeq,AimStruct);
      }
    }

    // set computer modes to normal state 
    for ( long i = 0 ; i < CIntfData::getLength(AimSeq); ++i )
    {
      CIntfData::getAt(AimStruct,AimSeq,i);
      std::string ActDevice = AimStruct.Device;

      if ( ActDevice == DEF_COMP_MODES::Electric   || 
           ActDevice == DEF_COMP_MODES::MatHandle  ||
           ActDevice == DEF_COMP_MODES::Stirring )
      {
        AimStruct.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }
      else
      {
        AimStruct.Status = DEF_GC_COMP_STATUS::ManualMode;
      }
    }

    m_pPlantManagementInterface->setComputerModes(DataKey.c_str(),DATA::ComputerModeAvail,AimSeq);
  }
}

void CDM_LFPlantManager::initCoolingWaterData(const std::string& DataKey)
{
  if (m_pPlantManagementInterface)
  {
    // cooling water
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
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::Roof.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);
    CoolWaterDevice.CoolWaterDevice = DEF_GC_COOLWATER::WasteGas.c_str();
    CIntfData::insert(CoolWaterData,CoolWaterDevice);

    m_pPlantManagementInterface->setCoolWaterData(DataKey.c_str(),DATA::CoolingWaterData,CoolWaterData);
  }
}

void CDM_LFPlantManager::initTransferCarData(const std::string& DataKey)
{
  m_pPlantManagementInterface->setString(DataKey,DATA::LadleType,"");       
  m_pPlantManagementInterface->setLong  (DataKey,DATA::LadleNo,DEF::Inv_Long);       
}


void CDM_LFPlantManager::resetPlantData(CEventMessage &Event)
{
}

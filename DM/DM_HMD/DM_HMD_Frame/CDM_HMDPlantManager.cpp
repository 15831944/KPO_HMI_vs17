// Copyright (C) 2008 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"

#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "CDM_HMDTask.h"
#include "CDateTime.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogHMDController.h"
//#include "cCBS_StdEventLogFrameController.h"
#include "CDM_HMDPlantManager.h"


CDM_HMDPlantManager::~CDM_HMDPlantManager()
{
}

CDM_HMDPlantManager::CDM_HMDPlantManager()
{
  m_GasInitializationList.push_back(DATA::TotalAmount);

  // fill GasNames into respective container
  m_GasTypeList.push_back(DEF_GAS::Ar);
  m_GasTypeList.push_back(DEF_GAS::N2);

  m_ComputerModeList.push_back(DEF_COMP_MODES::Level2Error);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeList.push_back(DEF_COMP_MODES::MatHandleL1Error);
  m_ComputerModeList.push_back(DEF_COMP_MODES::RejectHeatL1);
}

bool CDM_HMDPlantManager::changePlantInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string Message   = Event.getMessage();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( Message == HMD_EvMsg::evHMDHeatAnnouncement )
    {
      resetPlantManager(Event);

      // assign data to respective tranfercar
      if (m_pDataInterface && m_pPlantManagementInterface)
      {
		  std::string LadleId = m_pDataInterface->getString(DataKey,DATA::LadleNo);
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::LadleNo,LadleId);
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,ProductID);

        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HeatAnnouncement(sMessage, HeatID.c_str(), TreatID.c_str(), PlantID.c_str(), LadleId.c_str());
      }
      RetValue = true;
    }
    else if ( Message == HMD_EvMsg::evHMDHeatAnnounceStatus || 
              Message == HMD_EvMsg::evHMDHeatAnnounceStatusOffline  )
    {
      // check model status, if necessarry deassign heat from plantmanager
      if (m_pDataInterface)
      {
        long HeatAnnounceStatus = m_pDataInterface->getLong(Event.getDataKey(),DATA::HeatAnnounceStatus);
        
        // HeatAnnounceStatus == 0 means prediction not successful !
        if ( 0 == HeatAnnounceStatus )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_HeatAnnouncementError(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
        }
      }
      RetValue = true;
    }
    else if ( Message == HMD_EvMsg::evHMDHeatStart )
    {
      // write ProductID as ActualID to PlantManagementInterface
      if ( m_pPlantManagementInterface )
      {
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,ProductID);
        RetValue = true;

        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HeatStart(sMessage, HeatID.c_str(), TreatID.c_str(), PlantID.c_str());
      }
    }
    else if (Message == HMD_EvMsg::evHMDHeatDeparture || 
             Message == HMD_EvMsg::evHMDHeatCancellation )
    {
      deassignProduct(Event);// release model from product

      if ( m_pPlantManagementInterface )
      {
        log("Reset ProductID at Furnace!",2);
        m_pPlantManagementInterface->setString(DEF_PLANT::Furnace,DATA::ProductID,"");

        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage  = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        if(Message == HMD_EvMsg::evHMDHeatCancellation)
          pEventLog->EL_HeatCancellation(sMessage, HeatID.c_str(), TreatID.c_str(), PlantID.c_str());
        else if(Message == HMD_EvMsg::evHMDHeatDeparture)
          pEventLog->EL_HeatDeparture(sMessage, HeatID.c_str(), TreatID.c_str(), PlantID.c_str());
      }
      RetValue = true;
    }
    else if ( Message == HMD_EvMsg::evHMDPlantStatus )
    {
      if (m_pDataInterface && m_pPlantManagementInterface)
      {
        std::string StatusInfo = "INFO: changePlantInformation: State change of. ";
        std::string LanceInUse = "INFO: changePlantInformation: LanceId in use. ";

        // LanceID
        long LanceId = m_pDataInterface->getLong(Event.getDataKey(), DATA::LanceId);
        if (LanceId != DEF::Inv_Long)
        {
          log(LanceInUse + DATA::LanceId,2);
          m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::LanceId,LanceId);
        }

        // Lance position control
        long LancePos = m_pDataInterface->getLong(Event.getDataKey(), DATA::LancePos);
        if (LancePos != DEF::Inv_Long && m_StatusHandler.isStatusChanged(DEF_PLANT::Furnace,DATA::LancePos,LancePos))
        {
          log(StatusInfo + DATA::LancePos,2);

          //additional event
          addEventMessageToSend(HMD_EvMsg::evHMDLancePositionChanged);
          m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::LancePos,LancePos);

          CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          if (LancePos == DEF_GEN_STATES::OperationPosition)
          {
            pEventLog->EL_LanceInOperationPos(sMessage,m_pDataInterface->getLong(Event.getDataKey(), DATA::LanceId));
          }
          else if (LancePos == DEF_GEN_STATES::OutOfOperationPosition)
          {
            pEventLog->EL_LanceOutOfOperationPos(sMessage,m_pDataInterface->getLong(Event.getDataKey(), DATA::LanceId));
          }
        }

        // Hood position control
        long HoodPos = m_pDataInterface->getLong(Event.getDataKey(), DATA::HoodPos);
        if (HoodPos != DEF::Inv_Long && m_StatusHandler.isStatusChanged(DEF_PLANT::Furnace,DATA::HoodPos,HoodPos))
        {
          log(StatusInfo + DATA::HoodPos,2);

          //additional event
          addEventMessageToSend(HMD_EvMsg::evHMDHoodPositionChanged);
          m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::HoodPos,HoodPos);

          CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          if (HoodPos == DEF_GEN_STATES::OperationPosition)
          {
            pEventLog->EL_HoodInOperationPos(sMessage);
          }
          else if (HoodPos == DEF_GEN_STATES::OutOfOperationPosition)
          {
            pEventLog->EL_HoodOutOfOperationPos(sMessage);
          }
        }
      }
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::changePlantInformation()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_HMDPlantManager::changeComputerModes(CEventMessage& Event)
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
      string DataKey    = Event.getDataKey();
      // Computer Modes will be stored under "Furnace"

      /* set initial values for sequence and struct */ 
      seqComputerModes AimSeq;
      sComputerMode AimStruct;
      AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes));
  
      seqComputerModes SourceSeq;
      sComputerMode SourceStruct;
      SourceSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModes));

      // update data at m_pPlantManagementInterface with data m_pDataInterface
      UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,Device,std::string);

      m_pPlantManagementInterface->setComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes,AimSeq);
      m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,2);
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::changeComputerModes()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_HMDPlantManager::changeInjectionData(CEventMessage& Event)
{
  bool RetValue = false;
  string DataKey      = Event.getDataKey();
  std::string Message = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if (m_pPlantManagementInterface && m_pDataInterface )
    {
      if ( Message == HMD_EvMsg::evHMDCyclicMeasurement )
      {
        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_CyclicMeasurement(sMessage);

        std::vector<std::string> NameList;
        NameList.push_back(DATA::TopLanceHeight);
        NameList.push_back(DATA::HMDBlowType);
        NameList.push_back(DATA::HMDBlowingRateMg);
        NameList.push_back(DATA::HMDBlowingRateLime);
        NameList.push_back(DATA::HMDBlowingRateCarbide);

        CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                             m_pPlantManagementInterface,
                                             DataKey,
                                             DEF_PLANT::Furnace,
                                             NameList);

        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,2);
        RetValue = true;
      }
      else if ( Message == HMD_EvMsg::evHMDPowderBlowingStart )
      {
        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InjectionLanceBlowingStart(sMessage);
        // set new BlowingStatus
        m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::TopLanceStat,DEF_GEN_STATES::Start);
        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,2);
        RetValue = true;
      }
      else if ( Message == HMD_EvMsg::evHMDPowderBlowingEnd )
      {
        CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InjectionLanceBlowingStop(sMessage);

        m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace,DATA::TopLanceStat,DEF_GEN_STATES::Stop);
        m_pPlantManagementInterface->showContent(DEF_PLANT::Furnace,2);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;

}

void CDM_HMDPlantManager::resetPlantManager(CEventMessage &Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( m_pPlantManagementInterface )
    {
      resetBlowingData(Event);
      resetComputerModes(Event);
      resetCyclicData(Event);

      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::LancePos, DEF_GEN_STATES::OutOfOperationPosition);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::LanceId, 0);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::HoodPos, DEF_GEN_STATES::OutOfOperationPosition);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::TiltingFramePos, 0);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::resetPlantManager()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::resetPlantManager()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::resetPlantManager()",
                                         ExceptionMsg.str().c_str());
  }
}

void CDM_HMDPlantManager::resetBlowingData(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( m_pPlantManagementInterface )
    {
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::TopLanceStat, DEF_GEN_STATES::Stop);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::LancePos, DEF_GEN_STATES::OutOfOperationPosition);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::resetBlowingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::resetBlowingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::resetBlowingData()",
                                         ExceptionMsg.str().c_str());
  }
}

void CDM_HMDPlantManager::resetCyclicData(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( m_pPlantManagementInterface )
    {
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::TopLanceHeight, 100);
      m_pPlantManagementInterface->setLong(DEF_PLANT::Furnace, DATA::BlowType, DEF_GEN_STATES::Off);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateMg, 0.0);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateLime, 0.0);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::HMDBlowingRateCarbide, 0.0);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::MagnAmount, 0.0);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::LimeAmount, 0.0);
      m_pPlantManagementInterface->setDouble(DEF_PLANT::Furnace, DATA::CarbAmount, 0.0);
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::resetCyclicData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::resetCyclicData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::resetCyclicData()",
                                         ExceptionMsg.str().c_str());
  }
}

void CDM_HMDPlantManager::resetComputerModes(CEventMessage& Event)
{
  string DataKey    = Event.getDataKey();
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( m_pPlantManagementInterface )
    {
      initComputerModes();

      // iterate over all mode entries
      seqComputerModes AimSeq ; 
      sComputerMode AimStruct ; 
      AimSeq = CIntfData::ToCORBAType(m_pPlantManagementInterface->getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes));

      // set computer modes to normal state 
      for ( long i = 0 ; i < CIntfData::getLength(AimSeq); ++i )
      {
        CIntfData::getAt(AimStruct,AimSeq,i);
        std::string ActDevice = AimStruct.Device;

        if ( ActDevice == DEF_COMP_MODES::MatHandle || 
             ActDevice == DEF_COMP_MODES::Blowing )
        {
          AimStruct.Status = DEF_GEN_STATES::On;
        }
        else
        {
          AimStruct.Status = 0;
        }

      }

      m_pPlantManagementInterface->setComputerModes(DataKey.c_str(),DATA::ComputerModes,AimSeq);

    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::resetComputerModes()",
                                         ExceptionMsg.str().c_str());
  }
}



void CDM_HMDPlantManager::init(CDM_Task* pDMTask)
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
    }

    // computer modes
    initComputerModes();

    m_pPlantManagementInterface->showContent("",2);
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDPlantManager::init()",
                                         ExceptionMsg.str().c_str());
  }
}

void CDM_HMDPlantManager::initComputerModes()
{
  
  if ( m_pPlantManagementInterface )
  {
    // iterate over all mode entries
    seqComputerModes AimSeq; 
    sComputerMode AimStruct ; 

    // prepare computer mode entries at m_pPlantManagementInterface with "empty" values
    std::vector<std::string>::iterator it;
    for ( it = m_ComputerModeList.begin(); it != m_ComputerModeList.end(); ++it)
    {
      AimStruct.Device = (*it).c_str();
      AimStruct.Status = 0;                   // 0 == not available !
      CIntfData::insert(AimSeq,AimStruct);
    }

    m_pPlantManagementInterface->setComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes,AimSeq);
    
  }
}

// Copyright (C) 2005 SMS Demag AG

#include <iomanip>
#include <algorithm>

#include "iSMC_DataDefinitions_s.hh"
#include "CEventMessage.h"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDataConversion.h"
#include "CDM_LFTask.h"
#include "iEventMessages_s.hh"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogLFController.h"
#include "CDM_StatusHandler.h"
#include "CGasDataHandler.h"
#include "CStirringDataHandler.h"
#include "CStatusHandler.h"
#include "CProductID.h"
#include "CTreatID.h"
#include "CSMC_DBData.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GCL_ACTIVITY.h"
#include "DEF_GC_STIRR_DEVICE.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_PHASE.h"

#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_LFProductManager.h"


CDM_LFProductManager::~CDM_LFProductManager()
{
}

CDM_LFProductManager::CDM_LFProductManager() 
: CDM_ProductManager("L")
{
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Electric);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::ElectricModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Level2Error);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandleL1Error);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandleModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::RejectHeatL1);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Stirring);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::StirringModel);

  m_GasTypeList.push_back(DEF_GAS::Ar);
  m_GasTypeList.push_back(DEF_GAS::N2);

}

bool CDM_LFProductManager::changeProductInformation(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pProductManagementInterface && m_pDataInterface)
      {
        if ( Message == LF_EvMsg::evLFHeatAnnouncement )
        {
          log("INFO: CDM_LFProductManager::changeProductInformation: LFHeatAnnouncement",2);
          CDateTime DateTime;

          // preset tracking information
          resetProductManager(Event);

          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatAnnounceTime,DateTime.assDate());
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());

          // two heats can be announced in the same time
          //m_pProductManagementInterface->setString(ProductID,DATA::ActPlantLocation,DEF_PLANT::Furnace);
          m_pProductManagementInterface->setString(ProductID,DATA::ActPlantLocation,PlantID);
          m_pProductManagementInterface->setString(ProductID,DATA::OrderId,Event.getOrderID());


          // copy additional information to ProductManagementInterface
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LadleType);                        // string
          DataList.push_back(DATA::LadleNo);                          // long
          DataList.push_back(DATA::LadleTransferCarId);               // string
          DataList.push_back(DATA::CustHeatID);                       // string
          DataList.push_back(DATA::CustTreatID);                      // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);

          std::string LadleTransferCarId = m_pProductManagementInterface->getString(ProductID,DATA::LadleTransferCarId);

          // preset model assugnment relevant data
          std::string EquipmentId = m_pDMTask->getpPlantManager()->getPlantEquipmentData(LadleTransferCarId);

          m_pProductManagementInterface->setString(ProductID,DATA::EquipmentId,EquipmentId); 

          if (LadleTransferCarId.empty() || LadleTransferCarId == DEF::Inv_String)
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
            pEventLog->EL_InconsistentDataReceived(sMessage,
                                                  "CDM_LFProductManager::changeProductInformation()",
                                                  "Empty LadleTransferCarId received! Using Car 1 as default!");
            LadleTransferCarId = "1";
            m_pProductManagementInterface->setString(ProductID,DATA::LadleTransferCarId,LadleTransferCarId);
          }

          setTreatmentPosition(ProductID, CDataConversion::StringToLong(LadleTransferCarId,1) );

          m_pProductManagementInterface->showContent(ProductID,4);

          RetValue = true;
        }
        else if ( Message == LF_EvMsg::evLFHeatAnnouncementOffline )
        {
          CDateTime DateTime;

          // preset tracking information
          resetProductManager(Event); // resetting data for product data only

          // preset with "now" for further use of e.g. model or archiver for correct time calculations
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatAnnounceTime,DateTime.assDate());
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());

          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatAnnounceTimeOffline,DateTime.assDate());

          // copy additional information to ProductManagementInterface
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LadleTransferCarId);               // string
          DataList.push_back(DATA::CustHeatID);                       // string
          DataList.push_back(DATA::CustTreatID);                      // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);

          std::string LadleTransferCarId = m_pProductManagementInterface->getString(ProductID,DATA::LadleTransferCarId);

          setTreatmentPosition(ProductID, CDataConversion::StringToLong(LadleTransferCarId,1) );

          m_pProductManagementInterface->showContent(ProductID,4);
          RetValue = true;
        }

        else if ( Message == LF_EvMsg::evLFHeatCancellation )
        {
          log("INFO: CDM_LFProductManager::changeProductInformation: LFHeatCancellation",3);
          CDateTime DateTime;

          resetProductManager(Event);

          // if cust heatid is not available in product interface (in case of treacking restar)
          // it could come with event. 
          if (m_pProductManagementInterface->getString(ProductID,DATA::CustHeatID) == DEF::Inv_String)
          {
            //set external heat data for event log info in Task
            std::string CustHeatID = m_pDataInterface->getString(Event.getDataKey(), DATA::CustHeatID);
            std::string CustTreatID = m_pDataInterface->getString(Event.getDataKey(), DATA::CustTreatID);

            m_pProductManagementInterface->setString(ProductID,DATA::CustHeatID,CustHeatID);
            m_pProductManagementInterface->setString(ProductID,DATA::CustTreatID,CustTreatID);
          }

          m_pProductManagementInterface->showContent(ProductID,4);

          RetValue = true;
        }
        else if ( Message == LF_EvMsg::evLFHeatDeparture )
        {
          CDateTime DateTime;
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatDepartureTime,DateTime.assDate());

          // if cust heatid is not available in product interface (in case of treacking restar)
          // it could come with event. 
          if (m_pProductManagementInterface->getString(ProductID, DATA::CustHeatID) == DEF::Inv_String)
          {
            //set cast heat data for event log info in Task
            std::string CustHeatID = m_pDataInterface->getString(Event.getDataKey(), DATA::CustHeatID);
            std::string CustTreatID = m_pDataInterface->getString(Event.getDataKey(), DATA::CustTreatID);

            m_pProductManagementInterface->setString(ProductID, DATA::CustHeatID, CustHeatID);
            m_pProductManagementInterface->setString(ProductID, DATA::CustTreatID, CustTreatID);
          }

          m_pProductManagementInterface->setString(ProductID,DATA::ActPlantLocation, "");

          m_pProductManagementInterface->showContent(ProductID,4);

        }
        else if ( Message == LF_EvMsg::evLFHeatStart )
        {
          log("INFO: CDM_LFProductManager::changeProductInformation: LFHeatStart",3);
          CDateTime DateTime;

          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());

          // copy additional information to ProductManagementInterface
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LadleType);                        // string
          DataList.push_back(DATA::LadleNo);                          // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);

          m_pProductManagementInterface->showContent(ProductID,4);

          RetValue = true;

        }
        else if ( Message == LF_EvMsg::evLFCreateTreatmentID )
        {
          // read HeatID and TreatID from event data !
          std::string TreatID = m_pDataInterface->getString(Event.getDataKey(),DATA::TreatID);
          std::string HeatID  = m_pDataInterface->getString(Event.getDataKey(),DATA::HeatID);

          // error if HeatID / TreatID empty !!!
          if ( TreatID.empty() || 
               HeatID.empty()  || 
               TreatID == DEF::Inv_String ||
               HeatID  == DEF::Inv_String )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
            pEventLog->EL_InconsistentDataReceived(sMessage,
                                                  "CDM_LFProductManager::changeProductInformation()",
                                                  "Empty HeatID or TreatID received !");
          }

          // generate values for "next" TreatID 
          CProductID PID;
          CTreatID TID;

          std::string GenTreatID    = TID.getTreatID(TID.getPrefix(TreatID),TID.getCounter(TreatID)+1);
          std::string GenProductID  = PID.getProductID(HeatID,GenTreatID);
          std::string GenHeatID     = HeatID; //doesn't change !

          // update Event Message (will be sent by Event manager)
          Event.setProductID(GenProductID);
          Event.setHeatID(GenHeatID);
          Event.setTreatID(GenTreatID);

          RetValue = true;
        }
        else if ( Message == LF_EvMsg::evLFLadleDataChanged )
        {
          log("INFO: CDM_LFProductManager::changeProductInformation: LFHeatStart",3);

          // copy additional information to ProductManagementInterface
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LadleType);                        // string
          DataList.push_back(DATA::LadleNo);                          // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);

          RetValue = true;
        }
        else if ( Message == LF_EvMsg::evLFModelResultActualSetpoints ||
                  Message == LF_EvMsg::evLFModelResultRecipeSetpoints   )
        {
          log("INFO: CDM_LFProductManager::changeProductInformation: ModelResults",3);

          // copy additional information to ProductManagementInterface
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LadleType);                        // string
          DataList.push_back(DATA::LadleNo);                          // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);


          bool TempMeasReq     = m_pDataInterface->getBoolean(Event.getDataKey(),DATA::TempMeasReq);
          bool SteelSampleReq  = m_pDataInterface->getBoolean(Event.getDataKey(),DATA::SteelSampleReq);

          seqStatus TempSampleReqStatus = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus(ProductID.c_str(), "TempSampleReqStatus") );

          CStatusHandler StatusHandlerTempSample(TempSampleReqStatus);

          if ( StatusHandlerTempSample.isStatusChanged("Sampling", "Temp"  , TempMeasReq ) || 
               StatusHandlerTempSample.isStatusChanged("Sampling", "Sample", SteelSampleReq) )
          {
            if ( TempMeasReq || SteelSampleReq )
            {
              addEventMessageToSend(LF_EvMsg::evLFTemperatureSampleRequest);
            }
          }

          m_pProductManagementInterface->setStatus(ProductID.c_str(), "TempSampleReqStatus", StatusHandlerTempSample.getStatusData() );

          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFProductManager::changeSampleInformation(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string Message   = Event.getMessage();
  std::string PlantID   = Event.getPlantID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Message << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << Event.getDataKey();
  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface )
      {
        if ( Message == LF_EvMsg::evLFSteelSampleTaken )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Steel);
        }
        else if ( Message == LF_EvMsg::evLFSlagSampleTaken )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Slag);
        }
        else if ( Message == LF_EvMsg::evLFTempMeasurement )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Temp);
        }
        else if ( Message == LF_EvMsg::evLFSlagCeloxMeasurement )
        {
          setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Celox_Slag);
        }
        else if ( Message == LF_EvMsg::evLFCeloxMeasurement )
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
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());

  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());

  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeSampleInformation()",
                                         ExceptionMsg.str().c_str());

  }
  return RetValue;
}

bool CDM_LFProductManager::changeAnalysisInformation(CEventMessage& Event)
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
        if ( Message == LF_EvMsg::evLFSteelAnalysisReceived)
        {
          setAnalysisData(Event, DATA::SteelMeasAnalysis);
          RetValue = true;
        }
        else if ( Message == LF_EvMsg::evLFSlagAnalysisReceived)
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
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFProductManager::changeTappingData(CEventMessage& Event)
{
  return CDM_ProductManager::changeTappingData(Event);
}

bool CDM_LFProductManager::changeStirringData(CEventMessage& Event)
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

        // read actual time from ProductManagementInterface
        double ActTime    = m_pProductManagementInterface->getDouble(ProductID,DATA::DurSinceHeatAnnounce);

        if ( Message == LF_EvMsg::evLFCleanlinessStirring )
        {
        }
        else if ( Message == LF_EvMsg::evLFSoftStirring )
        {
        }
        else if ( Message == LF_EvMsg::evLFCooling )
        {
        }

        else if ( Message == LF_EvMsg::evLFCyclicMeasurement )
        {
          seqStirringData ActStirringIntensity = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringIntensity));
          seqStirringData ActStirringFlow      = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringFlow));
          seqStirringData ActStirringAmount    = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringAmount));
          seqStirringData ActStirringPressure  = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringPressure));


          seqStirringData StirringIntensity    = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringIntensity));
          seqStirringData StirringFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringFlow));
          seqStirringData StirringAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
          seqStirringData StirringPressure     = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringPressure));

          // update product related data with actual values
          CStirringDataHandler StirringIntensityHandler (StirringIntensity);
          CStirringDataHandler StirringFlowHandler      (StirringFlow);
          CStirringDataHandler StirringAmountHandler    (StirringAmount);
          CStirringDataHandler StirringPressureHandler  (StirringPressure);

          StirringIntensityHandler.update(ActStirringIntensity);
          StirringFlowHandler.update(ActStirringFlow);
          StirringAmountHandler.update(ActStirringAmount);
          StirringPressureHandler.update(ActStirringPressure);

          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringIntensity     , StirringIntensityHandler.getStirringData());
          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringFlow          , StirringFlowHandler.getStirringData());
          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringAmount        , StirringAmountHandler.getStirringData());
          m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringPressure      , StirringPressureHandler.getStirringData());

          m_pProductManagementInterface->showContent(ProductID,4);

        }
        else if ( Message == LF_EvMsg::evLFBottomStirringStart || 
                  Message == LF_EvMsg::evLFBottomStirringEnd)
        {
          seqStirringData ActStirringAmount       = CIntfData::ToCORBAType(m_pDataInterface->getStirringData(DataKey.c_str(), DATA::StirringAmount));
          seqStatus       ActStirringStatus       = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::StirringStatus));
          seqStatus       ActStirringBypassStatus = CIntfData::ToCORBAType(m_pDataInterface->getStatus      (DataKey.c_str(), DATA::StirringBypassStatus));

          seqStirringData StirringAmount       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
          seqStatus       StirringStatus       = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus      (ProductID.c_str(), DATA::StirringStatus));

          seqStirringData StirringFlow         = CIntfData::ToCORBAType(m_pProductManagementInterface->getStirringData(ProductID.c_str(), DATA::StirringFlow));

          CStatusHandler StirrStatusHandlerDevice(ActStirringStatus);

          CStirringDataHandler StirringAmountHandler(StirringAmount);
          StirringAmountHandler.update(ActStirringAmount);

          CStatusHandler StirrStatusHandler(StirringStatus);
          StirrStatusHandler.update(ActStirringStatus);
          StirrStatusHandler.update(ActStirringBypassStatus);

          CStirringDataHandler  StirringFlowHandler     (StirringFlow);

          // reset flows on stirring end !
          if ( Message == LF_EvMsg::evLFBottomStirringEnd )
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
        else if ( Message == LF_EvMsg::evLFEmergencyLanceStirringStart || 
                  Message == LF_EvMsg::evLFEmergencyLanceStirringEnd      )
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
          if ( Message == LF_EvMsg::evLFEmergencyLanceStirringEnd )
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
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}



bool CDM_LFProductManager::writeDiffStirringData(CEventMessage& Event, const std::string& ActData, const std::string  & NewData, double Value, std::string& StirringGasType)
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
    if (m_pProductManagementInterface)
    {
      CGasDataHandler GasDataHandler;
      CGasDataHandler DestGasDataHandler;

      seqGasData CalcGasData;
      seqGasData pActGasData  = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ProductID.c_str(),ActData.c_str())); 
      seqGasData pDestGasData = CIntfData::ToCORBAType(m_pProductManagementInterface->getGasData(ProductID.c_str(),NewData.c_str())); 

      std::vector<std::string> vStirrGasType;
      vStirrGasType.push_back(StirringGasType);

      // init gas handler with start data
      GasDataHandler.setGasData(pActGasData);

      // make difference for stirring gas
      GasDataHandler.diffGasData(StirringGasType,Value);

      // now add to existing data new difference
      DestGasDataHandler.setGasData(pDestGasData);
      DestGasDataHandler.addGasData(StirringGasType, GasDataHandler.getGasData(StirringGasType));

      // write new data to ProductManagementInterface
      DestGasDataHandler.fillSequence(CalcGasData);

      m_pProductManagementInterface->setGasData(ProductID.c_str(),NewData.c_str(),CalcGasData);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::writeDiffStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::writeDiffStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::writeDiffStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;

}



bool CDM_LFProductManager::resetComputerModeAvailabilities(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      CDM_StatusHandler StatusHandler;
      seqComputerModes StatusSeq; 

      if ( Message == LF_EvMsg::evLFHeatCancellation )
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
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFProductManager::resetProductManager(CEventMessage& Event)
{
  std::string ProductID = Event.getProductID();

  resetStirringData(Event);
  resetComputerModeAvailabilities(Event);
  resetElectricalData(Event);

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

    seqStatus TempSampleReqStatus;

    CStatusHandler::setDeviceStatus(TempSampleReqStatus, "Sampling" , "Temp"  , false);
    CStatusHandler::setDeviceStatus(TempSampleReqStatus, "Sampling" , "Sample", false);

    m_pProductManagementInterface->setStatus(Event.getProductID().c_str(), "TempSampleReqStatus", TempSampleReqStatus);

    seqStatus TempElectrodeReqStatus;

    CStatusHandler::setDeviceStatus(TempElectrodeReqStatus, "Electrodes", "ElecPullReq"   , DEF_GEN_STATES::No);
    CStatusHandler::setDeviceStatus(TempElectrodeReqStatus, "Electrodes", "ElecInhibitReq", DEF_GEN_STATES::No);

    m_pProductManagementInterface->setStatus(Event.getProductID().c_str(), "TempElectrodeReqStatus", TempElectrodeReqStatus);


  }

  return true;
}

bool CDM_LFProductManager::changeComputerModeAvailabilities(CEventMessage& Event)
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

      seqComputerModes SourceSeq; 
      sComputerMode SourceStruct ; 

      seqComputerModes AimSeq; 
      sComputerMode AimStruct ; 

      // react on special event
      if ( Message == LF_EvMsg::evLFModelResultActualSetpoints  || 
           Message == LF_EvMsg::evLFModelResultCode             ||
           Message == LF_EvMsg::evLFModelResultRecipeSetpoints )
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

        // decide follwing status for Material Handling
        if ( StatusHandler.getStatus(DEF_COMP_MODES::MatHandleModel)   == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error   )   == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1  )   == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::MatHandleL1Error) == DEF_GEN_STATES::NotAvailable)
        {
          StatusHandler.setStatus(DEF_COMP_MODES::MatHandle, DEF_GEN_STATES::Available );
        }

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;

      } //  if ( Message == LF_EvMsg::evLFModelResultActualSetpoints  || ...

      else if ( Message == LF_EvMsg::evLFMaterialHandlingReport )
      {
        // check RecipeStatus 
        long RecipeStatus = m_pDataInterface->getLong(Event.getDataKey(),DATA::RecipeStatus);

        // set MatHanldeL1Error = 1       
        if ( RecipeStatus == DEF_GC_RECIPE_STATUS::UnKnown ) 
        {
          // read actual Availabilities from Product interface
          AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

          // work with the data from Product interface
          fillStatusHandler(StatusHandler,AimSeq);

          // upadate statushandler entries
          StatusHandler.setStatus(DEF_COMP_MODES::MatHandleL1Error, DEF_GEN_STATES::NotOk );

          // write updated statushandler data into sequecne
          fillComputerModesSequence(StatusHandler,StatusSeq);

          // write updated data into CORBA interface
          m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);
        }

        RetValue = true;
      } // else if ( Message == LF_EvMsg::evLFMaterialHandlingReport )

      else if ( Message == LF_EvMsg::evLFSteelSampleTaken )
      {
        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // work with the data from Product interface
        fillStatusHandler(StatusHandler,AimSeq);

        // upadate statushandler entries
        StatusHandler.setStatus(DEF_COMP_MODES::MatHandleL1Error, DEF_GEN_STATES::NotOk );

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;
      } // else if ( Message == LF_EvMsg::evLFSteelSampleTaken )

      else if ( Message == LF_EvMsg::evLFSteelAnalysisReceived )
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
      } // else if ( Message == LF_EvMsg::evLFSteelAnalysisReceived)
      else if ( Message == LF_EvMsg::evLFResetComputerModeAvailability)
      {
        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // work with the data from Product interface
        fillStatusHandler(StatusHandler,AimSeq);

        // upadate statushandler entries
        StatusHandler.setStatus(DEF_COMP_MODES::MatHandle, DEF_GEN_STATES::Off);
        StatusHandler.setStatus(DEF_COMP_MODES::MatHandleModel, DEF_GEN_STATES::Off);

        StatusHandler.setStatus(DEF_COMP_MODES::Electric, DEF_GEN_STATES::Off);
        StatusHandler.setStatus(DEF_COMP_MODES::ElectricModel, DEF_GEN_STATES::Off);

        StatusHandler.setStatus(DEF_COMP_MODES::Stirring, DEF_GEN_STATES::Off);
        StatusHandler.setStatus(DEF_COMP_MODES::StirringModel, DEF_GEN_STATES::Off);

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;
      } // else if ( Message == LF_EvMsg::evLFSteelAnalysisReceived)
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_LFProductManager::resetStirringData(CEventMessage& Event)
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
    if (m_pDataInterface && m_pProductManagementInterface)
    {
      seqStatus StirringStatus;

      CStatusHandler::setDeviceStatus(StirringStatus, DEF_GC_STIRR_DEVICE::Plug1         , DEF_STATUS_NAME::Stirring, DEF_GEN_STATES::Off);
      CStatusHandler::setDeviceStatus(StirringStatus, DEF_GC_STIRR_DEVICE::Plug2         , DEF_STATUS_NAME::Stirring, DEF_GEN_STATES::Off);
      CStatusHandler::setDeviceStatus(StirringStatus, DEF_GC_STIRR_DEVICE::EmergencyLance, DEF_STATUS_NAME::Stirring, DEF_GEN_STATES::Off);

      m_pProductManagementInterface->setStatus(ProductID.c_str(), DATA::StirringStatus, StirringStatus);

      // reset plug states
      seqStirringData SeqStirrGasData;
      CStirringDataHandler NullStirringDataHandler;
      NullStirringDataHandler.fill(SeqStirrGasData);
      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::Plug1, DEF_GAS::Ar, 0);
      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::Plug2, DEF_GAS::Ar, 0);
      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::EmergencyLance, DEF_GAS::Ar, 0);

      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::Plug1, DEF_GAS::N2, 0);
      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::Plug2, DEF_GAS::N2, 0);
      NullStirringDataHandler.updateGasDataValue(DEF_GC_STIRR_DEVICE::EmergencyLance, DEF_GAS::N2, 0);

      m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringAmount             ,NullStirringDataHandler.getStirringData());
      m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringFlow               ,NullStirringDataHandler.getStirringData());
      m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringPressure           ,NullStirringDataHandler.getStirringData());
      m_pProductManagementInterface->setStirringData(ProductID.c_str(), DATA::StirringIntensity          ,NullStirringDataHandler.getStirringData());
      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::resetStirringData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


//##ModelId=42A6FCA90218
bool CDM_LFProductManager::changeElectricalData(CEventMessage& Event)
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
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;

  try
  {
    if ( findProduct(ProductID,HeatID,TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface)
      {
        // measured value
        double ElecCons           = m_pDataInterface->getDouble(DataKey,DATA::ElecCons);

        // if data are not available at DM interface, preset
        if ( ElecCons      == DEF::Inv_Double )        ElecCons     = 0.0;

        if (ElecCons > 0.0) // to prevent setting ElecCons to 0 for Product during treatment!
        {
          // copy additional data
          std::vector<std::string> NameList;
          NameList.push_back(DATA::VoltTapNo);                      // long
          NameList.push_back(DATA::ElectrodRegCurve);                  // long
          NameList.push_back(DATA::ElecCons);                       // double

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,
                                                m_pProductManagementInterface,
                                                DataKey,
                                                ProductID,
                                                NameList);
        }

        m_pProductManagementInterface->showContent(ProductID,4);

        RetValue = true;
      } // if (m_pDataInterface && m_pProductManagementInterface)
    } // if ( findProduct(ProductID,HeatID,TreatID) )
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_LFProductManager::resetElectricalData(CEventMessage& Event)
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

      m_pProductManagementInterface->setLong(ProductID,DATA::ElecPullReq,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElecInhibitReq,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::VoltTapNoAim,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::VoltTapNo,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElectrodRegCurveAim,0);
      m_pProductManagementInterface->setLong(ProductID,DATA::ElectrodRegCurve,0);

      m_pProductManagementInterface->setDouble(ProductID,DATA::PowerOnDur,0.0);
      m_pProductManagementInterface->setDouble(ProductID,DATA::PowerOffDur,0.0);

      // new handling of Electrical Phase information
      m_pProductManagementInterface->setLong(ProductID,DATA::ElecPhaseNo,0);

      CDateTime Now;
      seqElecPhaseData SourceSeq ;          
      sElecPhaseData SourceStruct;

      SourceStruct.Duration       = 0.0;
      SourceStruct.ElecCons       = 0.0;
      SourceStruct.ElecConsStart  = 0.0;
      SourceStruct.PhaseNo        = 0;   
      SourceStruct.PhaseType      = 0;   // POWER_OFF  
      SourceStruct.StartTime      = Now.assDate();
      SourceStruct.EndTime        = CSMC_DBData::unspecDate.assDate();
      SourceStruct.PhaseName      = DEF::Undefined;

      CIntfData::insert(SourceSeq,SourceStruct);
      m_pProductManagementInterface->setElecPhaseData(ProductID.c_str(),DATA::ElecPhaseData,SourceSeq);          

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::resetElectricalData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFProductManager::changeSetpoints(CEventMessage& Event)
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

        // read actual time from ProductManagementInterface
        double ActTime = m_pProductManagementInterface->getDouble(ProductID,DATA::DurSinceHeatAnnounce);

        if ( Message == LF_EvMsg::evLFModelResultActualSetpoints || 
             Message == LF_EvMsg::evLFModelResultRecipeSetpoints ||
             Message == LF_EvMsg::evLFModelResultActualSetpointsOffline || 
             Message == LF_EvMsg::evLFModelResultRecipeSetpointsOffline)
        {
          // store ladle, car and gas data
          std::vector<std::string> DataList;
          DataList.push_back(DATA::LFActSetPointStirrIntensity);   
          DataList.push_back(DATA::LFActSetPointStirrFlow);        
          DataList.push_back(DATA::LFActSetPointStirrGasType);     
          DataList.push_back(DATA::LFActStirrActivity);            

          DataList.push_back(DATA::RemTreatDur);
          DataList.push_back(DATA::PhaseModel);
          DataList.push_back(DATA::PhaseNoModel);

          DataList.push_back(DATA::VoltTapNoAim);
          DataList.push_back(DATA::ElectrodRegCurveAim);
          // see below
          //DataList.push_back(DATA::ElecPullReq);
          //DataList.push_back(DATA::ElecInhibitReq);
          DataList.push_back(DATA::TotalRemElecEgy);
          DataList.push_back(DATA::TempMeasReq);
          DataList.push_back(DATA::SteelSampleReq);
          DataList.push_back(DATA::LFElecPredRes);
          DataList.push_back(DATA::LFStirrPredRes);
          DataList.push_back(DATA::LFMatRecipe);
          DataList.push_back(DATA::StirringIntensity);

  				CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);

          // check if model sends request and detect changes to previous state
          // send respective events in case of status change
          long ElecPullReq     = m_pDataInterface->getLong(Event.getDataKey(),DATA::ElecPullReq);
          long ElecInhibitReq  = m_pDataInterface->getLong(Event.getDataKey(),DATA::ElecInhibitReq);

          seqStatus TempElectrodeReqStatus = CIntfData::ToCORBAType(m_pProductManagementInterface->getStatus(ProductID.c_str(), "TempElectrodeReqStatus") );

          CStatusHandler StatusHandlerElectrodeReq(TempElectrodeReqStatus);

          if ( StatusHandlerElectrodeReq.isStatusChanged("Electrodes", "ElecPullReq"  , ElecPullReq ) )
          {
            if (ElecPullReq == DEF_GEN_STATES::Yes)
            {
              addEventMessageToSend(LF_EvMsg::evLFPullElectrodeRequest);
            }
          }
          if ( StatusHandlerElectrodeReq.isStatusChanged("Electrodes", "ElecInhibitReq"  , ElecInhibitReq ) )
          {
            if (ElecInhibitReq == DEF_GEN_STATES::Yes)
            {
              addEventMessageToSend(LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest);
            }
            else
            {
              addEventMessageToSend(LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest);
            }
          }

          m_pProductManagementInterface->setLong(ProductID.c_str(), DATA::ElecPullReq, ElecPullReq);
          m_pProductManagementInterface->setLong(ProductID.c_str(), DATA::ElecInhibitReq, ElecInhibitReq);
          m_pProductManagementInterface->setStatus(ProductID.c_str(), "TempElectrodeReqStatus", StatusHandlerElectrodeReq.getStatusData() );


          m_pProductManagementInterface->showContent(ProductID,4);

          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeSetpoints()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeSetpoints()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeSetpoints()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_LFProductManager::changeHeatingData(CEventMessage& Event)
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
      std::vector<std::string> DataList;
      DataList.push_back(DATA::PhaseProcess);   

      CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                           DataKey,ProductID,DataList);

      // DATA::PhaseProcess is set in 
      // bool CLF_TelegramHandler::DoProcessLFL281TreamentSteps(const std::string& Key, const std::string& TlgName)

      if ( Message == LF_EvMsg::evLFMainHeating )
      {
        //m_pProductManagementInterface->setString(ProductID, DATA::PhaseProcess, DEF_LF_PHASES::HeatingMain);
      }
      else if ( Message == LF_EvMsg::evLFInitialHeating )
      {
        //m_pProductManagementInterface->setString(ProductID, DATA::PhaseProcess, DEF_LF_PHASES::HeatingInitial);
      }
      else if ( Message == LF_EvMsg::evLFFinalHeating  ) 
      {
        //m_pProductManagementInterface->setString(ProductID, DATA::PhaseProcess, DEF_LF_PHASES::HeatingFinal);
      }
      else if ( Message == LF_EvMsg::evLFTemperatureHold  ) 
      {
        //m_pProductManagementInterface->setString(ProductID, DATA::PhaseProcess, DEF_LF_PHASES::HeatingTempHold);
      }

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::changeHeatingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::changeHeatingData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::changeHeatingData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


std::string CDM_LFProductManager::getProductAtTransferCar(const std::string& TransferCarID)
{
  // call must be by car no (1,2)
  std::string ProductAtPlantEquipment = m_pDMTask->getpPlantManager()->getProductAtPlantEquipment(TransferCarID);
  
  if ( ProductAtPlantEquipment.empty() || ProductAtPlantEquipment == DEF::Inv_String )
  {
    ProductAtPlantEquipment = DEF::Inv_String;

    std::stringstream Message;
    Message << "No Product found at TransferCar! CarNo : " << TransferCarID;

    log(Message.str(), 1);
  }

  return ProductAtPlantEquipment;
}



void CDM_LFProductManager::init(CDM_Task* pDMTask)
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
                                         "CDM_LFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }

}

bool CDM_LFProductManager::findProductByEquipment(CEventMessage& Event, std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderID)
{
  bool RetValue = false;
  std::string PlantID = Event.getPlantID();

  log("CDM_LFProductManager::findProductByEquipment(...)",3);

  if (m_pProductManagementInterface && m_pDMTask->getpPlantManagementInterface())
  {
    // we will only use this strategy if HeatID and ProductID are empty to identify events only by transfercar
    if ( HeatID.empty() || ProductID.empty() )
    {
      log("INFO: find product by transfer car assigned to plant " + PlantID,3);

      // LadleTransferCarId = X
      std::string LadleTransferCarId = m_pDMTask->getpDataInterface()->getString(Event.getDataKey(),DATA::LadleTransferCarId);

      if ( LadleTransferCarId == DEF::Inv_String || LadleTransferCarId.empty())
      {
        // search LadleTransferCarInOperatingPosition at PlantManager
        LadleTransferCarId  = m_pDMTask->getpPlantManagementInterface()->getString(DEF_PLANT::Furnace, DATA::LadleTransferCarInOperatingPosition);
        std::stringstream Message;
        Message << "INFO: LadleTransferCarInOperatingPosition at PlantManagementInterface is " << LadleTransferCarId << "'";
        m_pDMTask->log(Message.str(),3);
      }

      if ( LadleTransferCarId == DEF::Inv_String || LadleTransferCarId.empty())
      {
	      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = m_pDMTask->initEventLogMessage(__FILE__,__LINE__,ProductID);
        pEventLog->EL_NoTransferCarInOperatingPosition(sMessage);

        std::stringstream Message;
        Message << "Product by Transfercar not found " << LadleTransferCarId ;
        m_pDMTask->log(Message.str(),2);
      }
      else
      {
        // search in Product is jnown at transfer car
        std::string ProductAtTransferCar  = getProductAtTransferCar(LadleTransferCarId);

        if (ProductAtTransferCar != DEF::Inv_String)
        {
          std::stringstream Message;
          Message << "INFO: Product '" << ProductAtTransferCar << "' found at Transfercar '" << LadleTransferCarId << "'";
          m_pDMTask->log(Message.str(),3);

          ProductID = ProductAtTransferCar;
          HeatID    = m_pProductManagementInterface->getString(ProductAtTransferCar,DATA::HeatID);
          TreatID   = m_pProductManagementInterface->getString(ProductAtTransferCar,DATA::TreatID);
          OrderID   = m_pProductManagementInterface->getString(ProductAtTransferCar,DATA::OrderId);

          RetValue = true;
        }
      }
    }
  }

	return RetValue;
}

bool CDM_LFProductManager::setProductData(const std::string& ProductID, long TreatmentPosition)
{
  bool RetValue = false;


  std::stringstream ExceptionMsg;

  try
  {
    if (m_pProductManagementInterface)
    {
      if ( findProduct(std::string(ProductID)) )
      {
        m_pProductManagementInterface->setString(ProductID, DATA::LadleTransferCarId, CDataConversion::LongToString(TreatmentPosition));

        setTreatmentPosition(ProductID, TreatmentPosition ); 

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFProductManager::setProductData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_LFProductManager::doOnPhaseStateChange(CEventMessage& Event)
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
      if (m_pProductManagementInterface)
      {
        double ElecCons           = m_pProductManagementInterface->getDouble(ProductID,DATA::ElecCons);

        m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhaseStart ,ElecCons);
        m_pProductManagementInterface->setDouble(ProductID,DATA::ElecConsPhase      ,0.0);

        CEventMessage Message(Event);

        std::vector<std::string> DestinationList;
        std::string SenderName;
        std::string TaskName =  m_pDMTask->getTaskName();
        std::vector<std::string> PlantList;
        std::vector<std::string>::iterator it;
        
        cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",SenderName);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName", DestinationList);

        cCBS_StdInitBase::getInstance()->getEntryList("PLANT","PlantId",PlantList);
        cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"PlantId",PlantList);

        for ( it = PlantList.begin() ; it != PlantList.end(); it ++)
        { 
          Message.setMessage(LF_EvMsg::evLFPhaseChange);
          Message.setPlantEvent(false);
          Message.dispatch(SenderName,DestinationList);
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
      "CDM_LFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      "CDM_LFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown",
      "CDM_LFProductManager::doOnPhaseStateChange()",
      ExceptionMsg.str().c_str());
  }
  return RetValue;
}
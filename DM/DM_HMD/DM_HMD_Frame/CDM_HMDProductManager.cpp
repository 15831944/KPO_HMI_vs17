// Copyright (C) 2008 SMS Demag AG

#include <iomanip>
#include <algorithm>

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CSMC_EventLogHMDController.h"
#include "CEventMessage.h"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDM_HMDTask.h"

#include "CDM_StatusHandler.h"
#include "CProductID.h"
#include "CDM_ProductManagementInterface_Impl.h"

//#include "DEF_GC_PROBETYPE.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"

#include "CDM_HMDProductManager.h"



CDM_HMDProductManager::~CDM_HMDProductManager()
{
}

CDM_HMDProductManager::CDM_HMDProductManager(std::string& _prefix) 
: CDM_ProductManager(_prefix)
{
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandle);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::Level2Error);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::MatHandleModel);
  m_ComputerModeAvailabilityList.push_back(DEF_COMP_MODES::RejectHeatL1);

  // fill GasNames into respective container
  m_GasTypeList.push_back(DEF_GAS::Ar);
  m_GasTypeList.push_back(DEF_GAS::N2);

  m_pSampleManager = new CDM_HMDSampleManager();
}

bool CDM_HMDProductManager::changeProductInformation(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  //std::string TreatID   = Event.getTreatID(); monoj dutta
	std::string TreatID   = "01";
  std::string OrderID   = Event.getOrderID();
  std::string Message   = Event.getMessage();
  std::string DataKey   = Event.getDataKey();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();


  try
  {
    if ( findProduct(ProductID, HeatID, TreatID) )
    {
      if (m_pProductManagementInterface)
      {
        if ( Event.getMessage() == HMD_EvMsg::evHMDHeatAnnouncement )
        {
          CDateTime DateTime;

          resetProductManager(Event);
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatAnnounceTime,DateTime.assDate());
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());
          m_pProductManagementInterface->setString(ProductID.c_str(),DATA::ActPlantLocation,DEF_PLANT::Furnace);
          m_pProductManagementInterface->setString(ProductID.c_str(),DATA::HeatID,HeatID);
          m_pProductManagementInterface->setString(ProductID.c_str(),DATA::TreatID,TreatID);
          m_pProductManagementInterface->setString(ProductID.c_str(),DATA::OrderId,OrderID);

          std::vector<std::string> DataList;
		  DataList.push_back(DATA::LadleNo);                          // string
          DataList.push_back(DATA::LadleType);                        // string
          DataList.push_back(DATA::CustHeatID);                       // string
          DataList.push_back(DATA::CustTreatID);                      // string

          CSMC_DataProvider_Impl::copyIntfData(m_pDataInterface,m_pProductManagementInterface,
                                               DataKey,ProductID,DataList);
          RetValue = true;
          m_pProductManagementInterface->showContent(ProductID,2);
        }
        else if ( Event.getMessage() == HMD_EvMsg::evHMDHeatStart )
        {
          CDateTime DateTime;
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatStartTime,DateTime.assDate());
          RetValue = true;
          m_pProductManagementInterface->showContent(ProductID,2);
        }
        else if ( Message == HMD_EvMsg::evHMDCreateTreatmentID )
        {
          // read HeatID and TreatID from event data !
          std::string TreatID = m_pDataInterface->getString(Event.getDataKey().c_str(),DATA::TreatID);
          std::string HeatID  = m_pDataInterface->getString(Event.getDataKey().c_str(),DATA::HeatID);

          // error if HeatID / TreatID empty !!!
          if ( TreatID.empty() || 
               HeatID.empty()  || 
               TreatID == DEF::Inv_String ||
               HeatID  == DEF::Inv_String )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_InconsistentDataReceived(sMessage,
                                                  "CDM_HMDProductManager::changeProductInformation()",
                                                  "Empty HeatID or TreatID received !");
          }

          // prepare ProductID with "old" TreatID
     //     //CProductID ID(m_TreatIDPrefix);   DUTM for conversion 14.03.2013
     //     //ID.getValidProductID("",HeatID,TreatID,1);



     ////     long NewTreatNo = ID.getTreatNo()+1;   
					//////long NewTreatNo=1;
     ////     
     ////     // generate values for "next" TreatID 
     ////     CProductID GenID(m_TreatIDPrefix); 
     ////     std::string GenProductID = GenID.getValidProductID("", HeatID, "", NewTreatNo);
     ////     std::string GenHeatID    = GenID.getHeatID();
     ////     std::string GenTreatID   = GenID.getTreatID(); 
					/*std::string GenTreatID   = "01"; */

          // update Event Message (will be sent by Event manager)
          ////Event.setProductID(GenProductID);
          ////Event.setHeatID(GenHeatID);
          ////Event.setTreatID(GenTreatID);
          RetValue = true;
        }
        else if ( Message == HMD_EvMsg::evHMDHeatDeparture )
        {
          CDateTime DateTime;
          m_pProductManagementInterface->setDate(ProductID.c_str(),DATA::HeatDepartureTime,DateTime.assDate());

          m_pProductManagementInterface->showContent(ProductID,3);
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::changeProductInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_HMDProductManager::changeSampleData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();
  std::string HeatID     = Event.getHeatID();
  std::string TreatID    = Event.getTreatID();
  std::string Message    = Event.getMessage();
  std::string PlantID   = Event.getPlantID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;


  try
  {
    if ( findProduct(ProductID, HeatID, TreatID) )
    {
      if (m_pDataInterface && m_pProductManagementInterface )
      {
        std::string NewSampleCode;
        if ( Message == HMD_EvMsg::evHMDHeatAnnouncement )
        {
          // for each prob type in m_ProductSampleInformationList
          // set default ProcessStage, reset SampleCounter
          m_pSampleManager->initProductSampleInformation(ProductID,PlantID);
          //TESTEN m_pSampleManager->changeSampleType(Event);
        }
        else if ( Message == HMD_EvMsg::evHMDHeatDeparture ||
                  Message == HMD_EvMsg::evHMDHeatCancellation )
        {
          // remove all probe types for a product
          m_pSampleManager->removeProcessStages(ProductID);
        }
        else if ( Message == HMD_EvMsg::evHMDSlagSampleTaken )
        {
          NewSampleCode = setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Slag);
          CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_SlagSampleTaken(sMessage,NewSampleCode.c_str(),1,"");
        }
        else if ( Message == HMD_EvMsg::evHMDHotMetalSampleTaken )
        {
          NewSampleCode = setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::HM);
          CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_HotMetalSampleTaken(sMessage,NewSampleCode.c_str(),1,"");
        }
        else if ( Message == HMD_EvMsg::evHMDTempMeasurement )
        {
			NewSampleCode = setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::Temp);
          CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_TempMeasurement(sMessage, m_pDataInterface->getDouble(DataKey,DATA::MeasTemp));
        }
        //else if ( Message == HMD_EvMsg::evHMDCeloxMeasurement)
        //{
        //  NewSampleCode = setSampleData(Event,DEF_GC_MEASUREMENT_TYPE::TempCarbonOxygen);
        //  CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
        //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        //  pEventLog->EL_TempMeasurement(sMessage, m_pDataInterface->getDouble(DataKey,DATA::MeasTemp));
        //}

        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::changeSampleData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::changeSampleData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::changeSampleData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}


bool CDM_HMDProductManager::changeAnalysisInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();
  std::string HeatID     = Event.getHeatID();
  std::string TreatID    = Event.getTreatID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;


  try
  {
    if ( findProduct(ProductID, HeatID, TreatID) )
    {
      if (m_pDataInterface && 
          m_pProductManagementInterface)
      {
        if ( Event.getMessage() == HMD_EvMsg::evHMDSlagAnalysisReceived)
        {
          setAnalysisData(Event, DATA::SlagMeasAnalysis);
          RetValue = true;
        }
        else if ( Event.getMessage() == HMD_EvMsg::evHMDHotMetalAnalysisReceived)
        {
          setAnalysisData(Event, DATA::HMMeasAnalysis);
          RetValue = true;
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::changeAnalysisInformation()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}

bool CDM_HMDProductManager::changeInjectionData(CEventMessage& Event)
{
  bool RetValue = false;
  std::string DataKey   = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string Message   = Event.getMessage();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << DataKey;

  try
  {
    if (m_pProductManagementInterface && m_pDataInterface )
    {
      if ( Message == HMD_EvMsg::evHMDCyclicMeasurement )
      {
        // get actual received amounts
        double MagnAmount = m_pDataInterface->getDouble(DataKey,DATA::MagnAmount);
        double LimeAmount = m_pDataInterface->getDouble(DataKey,DATA::LimeAmount);
        double CarbAmount = m_pDataInterface->getDouble(DataKey,DATA::CarbAmount);

        // set actual received 
        m_pProductManagementInterface->setDouble(ProductID,DATA::MagnAmount,MagnAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::LimeAmount,LimeAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::CarbAmount,CarbAmount);

        m_pProductManagementInterface->showContent(ProductID,2);
        RetValue = true;
      }
      else if (Message == HMD_EvMsg::evHMDPhasePreparation ||
		       Message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart ||
               Message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart ||
               Message == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumStart ||
               Message == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumEnd ||
               Message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd ||
               Message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd ||
               Message == HMD_EvMsg::evHMDPhaseDeslagging)
      {
        double ActTime = m_pProductManagementInterface->getDouble(ProductID,DATA::DurSinceHeatAnnounce);

        // copy the phase name from the EVENT interface to PRODUCT interface
        std::string ActPhase = m_pDataInterface->getString(DataKey.c_str(),DATA::PhaseAct);
        m_pProductManagementInterface->setString(ProductID.c_str(),DATA::PhaseAct,ActPhase);

        // get the amounts from the start of heat
        //double ActLimeCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::LimeAmount);
        //double ActMagnCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::MagnAmount);
        //double ActCarbCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::CarbAmount);

        //// get the amounts on the start of the phase
        //double PhaseStartLimeCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::PhaseStartLimeAmount);
        //double PhaseStartMagnCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::PhaseStartMagnAmount);
        //double PhaseStartCarbCons = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::PhaseStartCarbAmount);
        //
        //// calc the difference for the phase
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseLimeAmount, ActLimeCons - PhaseStartLimeCons);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseMagnAmount, ActMagnCons - PhaseStartMagnCons);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseCarbAmount, ActCarbCons - PhaseStartCarbCons);

        //// set the amount on the start of the phase to an actual amount values
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartLimeAmount, ActLimeCons);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartMagnAmount, ActMagnCons);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartCarbAmount, ActCarbCons);

        double StartDur = m_pProductManagementInterface->getDouble(ProductID.c_str(), DATA::BlowingActStartDur);
        m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::BlowDur, ActTime - StartDur);
        m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::BlowingActStartDur, ActTime);
      }
      else if ( Message == HMD_EvMsg::evHMDPowderBlowingStart )
      {
        // Needed as FirstBlowStart and after InjectionAbort nextBlowStart will have 0.0 values.
        // get actual received amounts
        double MagnAmount = m_pDataInterface->getDouble(DataKey,DATA::MagnAmount);
        double LimeAmount = m_pDataInterface->getDouble(DataKey,DATA::LimeAmount);
        double CarbAmount = m_pDataInterface->getDouble(DataKey,DATA::CarbAmount);

				//sankar
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseMagnAmount,MagnAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseLimeAmount,LimeAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseCarbAmount,CarbAmount);

        // set actual received 
        //m_pProductManagementInterface->setDouble(ProductID,DATA::MagnAmount,MagnAmount);
        //m_pProductManagementInterface->setDouble(ProductID,DATA::LimeAmount,LimeAmount);
        //m_pProductManagementInterface->setDouble(ProductID,DATA::CarbAmount,CarbAmount);
        //
        //// Important!!! set the amount on the start of the phase to current amount values.
        //// Normal Blow Start not effected by this but needed for BlowStart after Injection Abort Case.
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartLimeAmount, LimeAmount);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartMagnAmount, MagnAmount);
        //m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartCarbAmount, CarbAmount);


      }
      else if ( Message == HMD_EvMsg::evHMDPowderBlowingEnd )
      {

        double MagnAmount = m_pDataInterface->getDouble(DataKey,DATA::MagnAmount);
        double LimeAmount = m_pDataInterface->getDouble(DataKey,DATA::LimeAmount);
        double CarbAmount = m_pDataInterface->getDouble(DataKey,DATA::CarbAmount);

				//sankar
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseMagnAmount,MagnAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseLimeAmount,LimeAmount);
        m_pProductManagementInterface->setDouble(ProductID,DATA::PhaseCarbAmount,CarbAmount);

        //// get actual received amounts
        //double MagnAmount = m_pDataInterface->getDouble(DataKey,DATA::MagnAmount);
        //double LimeAmount = m_pDataInterface->getDouble(DataKey,DATA::LimeAmount);
        //double CarbAmount = m_pDataInterface->getDouble(DataKey,DATA::CarbAmount);

				//// set actual received 
        //m_pProductManagementInterface->setDouble(ProductID,DATA::MagnAmount,pMagnAmount);
        //m_pProductManagementInterface->setDouble(ProductID,DATA::LimeAmount,pLimeAmount);
        //m_pProductManagementInterface->setDouble(ProductID,DATA::CarbAmount,pCarbAmount);


				// get actual received amounts during Blowing End
				//double pMagnAmount = m_pDataInterface->getDouble(DataKey,DATA::PhaseMagnAmount);
				//double pLimeAmount = m_pDataInterface->getDouble(DataKey,DATA::PhaseLimeAmount);
				//double pCarbAmount = m_pDataInterface->getDouble(DataKey,DATA::PhaseCarbAmount);

    //    // set actual received 
    //    m_pProductManagementInterface->setDouble(ProductID,DATA::MagnAmount,pMagnAmount);
    //    m_pProductManagementInterface->setDouble(ProductID,DATA::LimeAmount,pLimeAmount);
    //    m_pProductManagementInterface->setDouble(ProductID,DATA::CarbAmount,pCarbAmount);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::changeInjectionData()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;
}

bool CDM_HMDProductManager::changeComputerModeAvailabilities(CEventMessage& Event)
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

  CDM_StatusHandler StatusHandler;

  try
  {
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      // react on special event
      if ( Message == HMD_EvMsg::evHMDModelResult || 
          Message == HMD_EvMsg::evHMDModelResultCode )
      {
        // fill status handler with "default" data
        fillStatusHandler(StatusHandler,m_ComputerModeAvailabilityList,DEF_GEN_STATES::NotAvailable);

        // read actual values from CORBA interface and update above list
        seqComputerModes StatusSeq; 

        seqComputerModes SourceSeq; 
        sComputerMode SourceStruct ; 

        seqComputerModes AimSeq ; 
        sComputerMode AimStruct ; 

        // read actual Availabilities from Product interface
        AimSeq = CIntfData::ToCORBAType(m_pProductManagementInterface->getComputerModes(ProductID.c_str(),DATA::ComputerModeAvail));

        // read actual Availabilities from Model Results
        // this data will become part of the product related values
        SourceSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModeAvail));

        // update AimSeq with Model Result Data
        UPDATE_SEQ(&SourceSeq,SourceStruct,&AimSeq,AimStruct,Device,std::string);

        // work with the updated data from Product interface
        fillStatusHandler(StatusHandler,&AimSeq);

        // upadate statushandler entries
        if ( StatusHandler.getStatus(DEF_COMP_MODES::MatHandleModel) == DEF_GEN_STATES::Available &&
            StatusHandler.getStatus(DEF_COMP_MODES::Level2Error)  == DEF_GEN_STATES::NotAvailable &&
            StatusHandler.getStatus(DEF_COMP_MODES::RejectHeatL1) == DEF_GEN_STATES::NotAvailable )
        {
          StatusHandler.setStatus(DEF_COMP_MODES::Blowing, DEF_GEN_STATES::Available );
        }

        // write updated statushandler data into sequecne
        fillComputerModesSequence(StatusHandler,StatusSeq);

        // write updated data into CORBA interface
        m_pProductManagementInterface->setComputerModes(ProductID.c_str(),DATA::ComputerModeAvail,StatusSeq);

        RetValue = true;

      } //  if ( Message == HMD_EvMsg::evHMDModelResul || ...
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::changeComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;

}

bool CDM_HMDProductManager::resetProductManager(CEventMessage& Event)
{
  std::string ProductID = Event.getProductID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();
  try
  {

    if ( m_pProductManagementInterface )
    {
      m_pProductManagementInterface->setString(ProductID.c_str(),DATA::PhaseAct,"Preparation");
    }

    resetComputerModeAvailabilities(Event);
    resetInjectionData(Event);
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_AODProductManager::resetProductManager()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_AODProductManager::resetProductManager()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_AODProductManager::resetProductManager()",
                                         ExceptionMsg.str().c_str());
  }


  return true;
}

bool CDM_HMDProductManager::resetComputerModeAvailabilities(CEventMessage& Event)
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
    if (m_pDataInterface && m_pProductManagementInterface )
    {
      CDM_StatusHandler StatusHandler;
      seqComputerModes StatusSeq; 

      // fill status handler with "default" data
      fillStatusHandler(StatusHandler,m_ComputerModeAvailabilityList,DEF_GEN_STATES::NotAvailable);

      // JAST L1 will be informed with "Unavailable first"
      // after succssful calculations at model, respective availabilities will be set 
      // StatusHandler.setStatus(DEF_HMD_COMP_MODES::Blowing, DEF_MAT_HANDLE_STATUS::Available );
      // StatusHandler.setStatus(DEF_HMD_COMP_MODES::MatHandle, DEF_MAT_HANDLE_STATUS::Available );

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
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::resetComputerModeAvailabilities()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}



bool CDM_HMDProductManager::resetInjectionData(CEventMessage& Event)
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
    if (m_pProductManagementInterface )
    {
      m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::BlowDur, 0.0);
      m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::BlowingActStartDur, 0.0);
      m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartLimeAmount, 0.0);
      m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartMagnAmount, 0.0);
      m_pProductManagementInterface->setDouble(ProductID.c_str(), DATA::PhaseStartCarbAmount, 0.0);

      RetValue = true;
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::resetInjectionData()",
                                         ExceptionMsg.str().c_str());
  }
  return RetValue;
}
bool CDM_HMDProductManager::findActualProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderID)
{
  bool RetValue = false;

  if (m_pDataInterface && m_pProductManagementInterface && m_pDMTask->getpPlantManagementInterface())
  {
    // we will only use this strategy if HeatID and ProductID are empty to identify events only by transfercar
    if ( HeatID.empty() || ProductID.empty() )
    {
      std::string ProductFromInterface = CDM_HMDTask::getInstance()->getpPlantManagementInterface()->getString((std::string)DEF_PLANT::Furnace, DATA::ProductID);

      if (ProductFromInterface != DEF::Inv_String)
      {
        std::stringstream Message;
        Message << "Product " << ProductFromInterface << " found at Furnance";
        m_pDMTask->log(Message.str(),2);

        ProductID = ProductFromInterface;
        HeatID    = m_pProductManagementInterface->getString(ProductFromInterface,DATA::HeatID);
        TreatID   = m_pProductManagementInterface->getString(ProductFromInterface,DATA::TreatID);
        OrderID   = m_pProductManagementInterface->getString(ProductFromInterface,DATA::OrderId);
        RetValue = true;
      }
      else
      {
        std::stringstream Message;
        Message << "Product NOT found af Furnance";
        m_pDMTask->log(Message.str(),2);
      }
    }
  }

	return RetValue;
}

void CDM_HMDProductManager::init(CDM_Task* pDMTask)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Init Product Manager: " ;

  try
  {

    // first of all call base class method to set
    // members
	  CDM_ProductManager::init(pDMTask);

    m_pProductManagementInterface->showContent("",2);
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDProductManager::init()",
                                         ExceptionMsg.str().c_str());
  }

}

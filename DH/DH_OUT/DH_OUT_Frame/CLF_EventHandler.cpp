// Copyright (C) 2012 SMS Siemag AG Germany

//DH_OUT_LF PATTERN IMPLEMENTATION 
//bool CLF_EventHandler::provideData_TlgName(CEventMessage& Event)
//{
//  //=========================    Example   ===================================
//  bool RetValue = true;
//
//  //------------ read the data from Event ------------------
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID(); 
//  std::string ProductID = Event.getProductID();
//  std::string OrderID   = Event.getOrderID();
//  std::string DataKey   = Event.getDataKey();
//  std::string PlantID   = Event.getPlantID();
//  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
//  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
//  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);
//
//  //------------ This variables are used as buffer ------------------
//  std::string DataKeyL1;
//
//  std::string CustHeatID;
//  std::string CustTreatID;
//
//  std::string LadleType; /;
//  std::string LadleId;
//  long LadleNo   = 0;
//
//  CDateTime Now;
//  DEF::seqLong seqSpare;
//
//  std::string Action    = "Reading DM interface data from ";
//  Action +=  Event.getSender();
//  Action +=  "ProductID:";
//  Action +=  Event.getProductID();
//  Action +=  " - ";
//  Action +=  "Key:";
//  Action +=  Event.getDataKey(); 
//
//  std::string TlgName   = "TlgName";
//  std::string Function = "CLF_EventHandler::provideData_" + TlgName;
//
//  log (TlgName + ": Started", 3);
//
//  try
//  {
//    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);
//
//    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
//
//    if ( pDM_Interface && pTelcom_Interface )
//    {
//      //********    preset data  **************************************************************************************
//
//      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
//      {
//        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);
//
//        //********    Read event related data  ************************************************************************
//
//        //********    Convert and check event data  *******************************************************************
//
//        //********    Log event data **********************************************************************************
//
//        //********    Write telegram data  ****************************************************************************
//
//        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF03::UnitNo,        UnitNo);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::HeatId,        CustHeatID);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::TreatId,       CustTreatID);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::OrderID,       OrderID);
//        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF03::CreateTime,    Now.asCORBAAny()); 
//
//        pTelcom_Interface->showContent(DataKeyL1, 4);
//
//        //********    send internal event  ***************************************************************************
//
//        SendEventMessage(DataKey,TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);
//
//        //********    End processing data  ***************************************************************************
//      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
//      else
//      {
//        RetValue = false;
//      }
//
//    }// if ( pDM_Interface && m_pTelcom_Interface )
//    else
//    {
//      RetValue = false;
//    }
//
//  }// try
//  catch (cCBS_DBExc &e)
//  {
//    RetValue = false;
//
//    
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
//      Function.c_str(), TlgName.c_str()); 
//  }
//  catch(CORBA::SystemException& sExc) 
//  {
//    RetValue = false;
//
//    
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
//      Function.c_str(), TlgName.c_str());    
//  }
//  catch(CORBA::Exception& cExc) 
//  {
//    RetValue = false;
//
//    
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
//      Function.c_str(), TlgName.c_str()); 
//  }
//  catch(...)
//  {
//    RetValue = false;
//
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
//  }
//
//  if ( !RetValue )
//  {
//    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
//    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
//    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
//  }
//
//  log (TlgName + ": Finished", 3);
//
//  return RetValue;
//}// bool CLF_EventHandler::provideData_TlgName(const std::string& Key, const std::string& TlgName
//DH OUT LF PATTERN IMPLEMENTATION 

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iDH_Telcom_s.hh"
#include "iDM_Interface_s.hh"
#include "Telcom_Out_s.hh"

//utilities
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDH_OUT_Task.h"
#include "CSMC_DataProvider_Impl.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrame.h"
#include "cCBS_StdCORBA_Task.h"
#include "CLadleID.h"

#include "CLF_EventHandler.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_SOURCE.h"
#include "DEF_GT_PURP.h"
#include "DEF_GCL_STIRR_PHASE.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"

CLF_EventHandler::CLF_EventHandler()
:m_pPP_HEAT_PLANT (0)
{
  try
  {
    cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();

    if (pConnection)
    {
      long PlantNo  = 1;
      std::string Plant = DEF_GC_PLANT_DEF::LF;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);
  
			//sankar
			long OracleTransfer = 1;
      cCBS_StdInitBase::getInstance()->replaceWithEntry("UseOracleTransfer", "OracleTransfer"  , OracleTransfer);
			if(OracleTransfer == 1)
				UseOracleTransfer = true;
			else
				UseOracleTransfer = false;

			// GENERAL
      // create PlantID converter between L1<-->L2
      m_pGC_Plant_Container       = new CGC_Plant_Container    (pConnection, Plant);
      // create converter for customer heat and treat ids
      m_pHeatDataConverter      = new CHeatDataConverter     (pConnection);

      m_pGC_Recipe_L1Container  = new CGC_Recipe_L1Container (pConnection,Plant);       
      m_pGC_SourceContainer     = new CGC_SourceContainer    (pConnection,Plant,PlantNo);

      // SPECIFIC
      m_pGT_MAT_PURP            = new CGT_MAT_PURP           (pConnection);
      m_pGT_MAT                 = new CGT_MAT                (pConnection);
      m_pGT_GRADE_PRODPRAC      = new CGT_GRADE_PRODPRAC     (pConnection);
      m_pGCL_STIRR_PHASE        = new CGCL_STIRR_PHASE       (pConnection);
     
      m_pPD_LADLE               = new CPD_LADLE              (pConnection);
      m_pPD_HEAT_DATA           = new CPD_HEAT_DATA          (pConnection);   

      m_pPD_RECIPE              = new CPD_RECIPE             (pConnection); 
      m_pPDL_HEAT_DATA          = new CPDL_HEAT_DATA         (pConnection);
      
      m_pPP_HEAT_PLANT          = new CPP_HEAT_PLANT         (pConnection);
      m_pPP_HEAT                = new CPP_HEAT               (pConnection);

	  ElPatternChanged = true;
	  AimVoltTapPrev   = 0;
	  AimCurveNoPrev   = 0;
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CLF_EventHandler","No database connection");

      // to guaranty EL_ExceptionCaught to be sent to CBS service
      Sleep(3000);

      // terminate programm in case of starting up without getting connection to database
      exit(EXIT_FAILURE);
    }
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame EventLog;
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    EventLog.EL_ExceptionCaught(sMessage,"", "CLF_EventHandler::CLF_EventHandler","");
    throw;
  }
}

CLF_EventHandler::~CLF_EventHandler()
{
  if( m_pGC_Plant_Container )       delete m_pGC_Plant_Container;
  if( m_pHeatDataConverter)       delete m_pHeatDataConverter;
  if( m_pGC_Recipe_L1Container )  delete m_pGC_Recipe_L1Container; 
  if( m_pPD_RECIPE )              delete m_pPD_RECIPE; 
  if( m_pGC_SourceContainer )     delete m_pGC_SourceContainer; 
  if( m_pPD_HEAT_DATA   )         delete m_pPD_HEAT_DATA;
  if( m_pPDL_HEAT_DATA   )        delete m_pPDL_HEAT_DATA;
  if( m_pPP_HEAT )                delete m_pPP_HEAT;
  if( m_pGT_GRADE_PRODPRAC )      delete m_pGT_GRADE_PRODPRAC;
  if( m_pPP_HEAT_PLANT )          delete m_pPP_HEAT_PLANT;
  if( m_pGCL_STIRR_PHASE )        delete m_pGCL_STIRR_PHASE;
  if( m_pPD_LADLE )               delete m_pPD_LADLE; 
  if (m_pGT_MAT_PURP)             delete m_pGT_MAT_PURP; 
  if (m_pGT_MAT)                  delete m_pGT_MAT;
}

bool CLF_EventHandler::afterHandleEvent(const FRIESEvent& Event)
{
  return true;
}

bool CLF_EventHandler::beforeHandleEvent(const FRIESEvent& Event)
{
  //CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

  //if ( pTelcom_Interface )
  //{
  //  std::vector<std::string> IntfKeyList = pTelcom_Interface->getIntfKeyList();
  //  std::vector<std::string>::iterator it; 

  //  for ( it = IntfKeyList.begin(); it != IntfKeyList.end(); ++it)
  //  {
  //    std::string Key = (*it);
  //    CORBA::Any seqAny = pTelcom_Interface->getAny(Key,"EventMessage");

  //    // check if data are usable for construction
  //    if ( CEventMessage::isAsCORBAAny(seqAny) )
  //    {

  //      Sleep(1000);
  //      CEventMessage MstToL1Sender(seqAny);
  //      dispatchEvent(m_SenderName,"",MstToL1Sender);   
  //    }
  //  }
  //}

  return true;
}


bool CLF_EventHandler::handleEvent(CEventMessage& evMessage)
{
  log("Class.CLF_EventHandler Version.1.0.0", 4);

  log(evMessage,3);

  bool RetValue = true;

  

  if ( evMessage.getMessage() == LF_EvMsg::evLFHeatAnnouncement )   
  {
    RetValue = provideData_L2LF72StatusRequest    (evMessage);      
    RetValue = provideData_L2LF03HeatAnnouncement (evMessage);     
    RetValue = provideData_L2LF23ReleaseElectrodes(evMessage);      
    RetValue = provideData_L2LF07CompMode         (evMessage);      

    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2LF70_MAT_HANDL(evMessage);      
    }
    else
    {
      RetValue = provideData_L2LF70MatHandling(evMessage);      
    }
  }
  if ( evMessage.getMessage() == LF_EvMsg::evLFHeatStart )   
  {
    RetValue = provideData_L2LF72StatusRequest(evMessage);      
  }
  else if ( evMessage.getMessage()  == LF_EvMsg::evLFHeatCancellation )
  {
    RetValue = provideData_L2LF06HeatCancel       (evMessage);  
    RetValue = provideData_L2LF03HeatAnnouncement (evMessage, 1); // update    
  }
  else if ( evMessage.getMessage()  == LF_EvMsg::evLFHeatDeparture )
  {
    RetValue = provideData_L2LF03HeatAnnouncement (evMessage, 1); // update    
  }
  else if ( evMessage.getMessage()  == LF_EvMsg::evLFPullElectrodeRequest)
  { 
    RetValue = provideData_L2LF22PullElectrodes(evMessage);  
  }
  else if ( evMessage.getMessage() == LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest || 
	        evMessage.getMessage() == LF_EvMsg::evLFElectrodeHydraulicSystemReleaseRequest)
  {   	
    provideData_L2LF23ReleaseElectrodes(evMessage);      
  }
  else if ( evMessage.getMessage()  == LF_EvMsg::evLFModelResultActualSetpoints )
  { 
    RetValue = provideData_L2LF07CompMode   (evMessage);      

    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2LF20VoltageTap (evMessage);      //// u153 - Request for L1 to send it always
      RetValue = provideData_L2LF20_VOLTAGE_TAP (evMessage);  
      RetValue = provideData_L2LF30_ELEC_PATT (evMessage); 
      RetValue = provideData_L2LF31ProcessPatternStirr(evMessage);  
	  RetValue = provideData_L2LF31_STIRR_PATT      (evMessage);  //Sankar 
    }
    else
    {
      RetValue = provideData_L2LF20VoltageTap (evMessage);      //// u153 - Request for L1 to send it always
      RetValue = provideData_L2LF30ProcessPatternElec (evMessage);    //// agreed with L1 to send updated pattern always, when dynamic setpoints changed
      RetValue = provideData_L2LF31ProcessPatternStirr(evMessage);  
    }
  }
  else if ( evMessage.getMessage()  == LF_EvMsg::evLFModelResultRecipeSetpoints )
  {     
    if ( UseOracleTransfer )
    {
      RetValue = provideData_L2LF03HeatAnnouncement (evMessage, 1); // update    
      RetValue = provideData_L2LF07CompMode         (evMessage);      
      RetValue = provideData_L2LF30_ELEC_PATT       (evMessage); 
      RetValue = provideData_L2LF31ProcessPatternStirr(evMessage);  
      RetValue = provideData_L2LF31_STIRR_PATT      (evMessage);  //Sankar 
      RetValue = provideData_L2LF70_MAT_HANDL       (evMessage);
    }
    else
    {
      RetValue = provideData_L2LF03HeatAnnouncement   (evMessage, 1); // update    
      RetValue = provideData_L2LF07CompMode           (evMessage);      
      RetValue = provideData_L2LF30ProcessPatternElec (evMessage); 
      RetValue = provideData_L2LF31ProcessPatternStirr(evMessage);  
      RetValue = provideData_L2LF70MatHandling        (evMessage);      
    }
  }
  else if (evMessage.getMessage() == LF_EvMsg::evLFModelResultCode )
  { 
    RetValue = provideData_L2LF07CompMode      (evMessage);

    if ( UseOracleTransfer )
    {  
      RetValue = provideData_L2LF20VoltageTap (evMessage);      //// u153 - Request for L1 to send it always
      RetValue = provideData_L2LF20_VOLTAGE_TAP (evMessage);  
    }
    else
    {    
      RetValue = provideData_L2LF20VoltageTap    (evMessage);   
    }
  }
  else if (evMessage.getMessage() == LF_EvMsg::evLFRequestMatAvail )
  { 
    RetValue = provideData_L2LF71MatAvailRequest(evMessage);  
  }
  else if (evMessage.getMessage() == LF_EvMsg::evLFPlantStatusRequest )
  { 
    RetValue = provideData_L2LF72StatusRequest  (evMessage);      
  }
  else if(evMessage.getMessage() == GEN_EvMsg::evGenSystemStatusReport)
  {
    RetValue = provideData_L2LF07CompMode       (evMessage);
  }
  else if (evMessage.getMessage() == LF_EvMsg::evLFLadleDataChanged )
  {
    RetValue = provideData_L2LF03HeatAnnouncement (evMessage, 1); // update
  }
  else if(evMessage.getMessage() == "ORACLE_TRANSFER") // for testing purpose only
  {
    RetValue = provideData_L2LF20_VOLTAGE_TAP (evMessage);
    RetValue = provideData_L2LF30_ELEC_PATT   (evMessage);
    RetValue = provideData_L2LF31_STIRR_PATT  (evMessage);
    RetValue = provideData_L2LF70_MAT_HANDL   (evMessage);
  }  
  else 
  {
    log("LF_EventHandler::handleEvent: Unknown EventMessage = " + evMessage.getMessage(),4); // can be event like .RDY, should not logged with trace no 1
    RetValue = false;
  }

  if ( RetValue )
  {
    std::string Item = CDataConversion::FillRight(evMessage.getMessage(),50);
    CDH_OUT_Task::getInstance()->setStateDetails(Item ," was handled at " + CDateTime().asString() , 0);
  }

  return RetValue;
}

void CLF_EventHandler::SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID)
{
  try
  {
    //********    Dispatch event ***********************************************************************

    CEventMessage MstToL1Sender;
    MstToL1Sender.setMessage(std::string("TELEGRAM_") + TlgName);
    MstToL1Sender.setHeatID(HeatID);
    MstToL1Sender.setTreatID(TreatID);
    MstToL1Sender.setPlantID(PlantID);
    MstToL1Sender.setDataKey(DataKey);
    MstToL1Sender.setOrderID(OrderID);
    dispatchEvent(m_SenderName,"",MstToL1Sender);  
  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), "", ""); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), "", "");
  }
  catch(CORBA::Exception& cExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), "", "");
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "", ""); 
  }
}

bool CLF_EventHandler::provideData_L2LF03HeatAnnouncement(CEventMessage& Event, long UpdateFlag /* = 0 */)
{
  //==============       H E A T   A N N O N C E M E N T      ==========================
  bool RetValue = true; // assume success
  //read the data from Event
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action    = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF03";
  std::string Function = "CLF_EventHandler::provideData_L2LF03HeatAnnouncement";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************
      

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CIntfData::preset(seqSpare,0,5);

        //********    Read event related data  ************************************************************************

        std::string STEELGRADECODE;
        std::string SHIFT_ID;
        std::string CREW_ID;
        std::string USERCODE;
        std::string LADLETYPE;
        std::string LadleId;
        std::string ROUTECODEPLAN  = " " ;
        CDateTime ProdDate;
        CDateTime DepTime;
        long LADLENO        = 0;
        long HeatPlantRow   = 0;
        long CARNO          = 0;
        double STEELMASS        = 0.;  
        double SLAGMASS         = 0.;
        double LadleTareWeight  = 0.;
        double LadleGrossWeight = 0.;
        double AimTemp          = 0.;


        if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
        {          
          ProdDate        = m_pPD_HEAT_DATA->getTREATSTART_MOD(1);
          DepTime         = m_pPD_HEAT_DATA->getTREATEND_MOD(1);
          CDateTime dd    = m_pPD_HEAT_DATA->getTREATEND_PLAN(1);
          CDateTime d2    = m_pPD_HEAT_DATA->getTREATEND_ACT(1);


          STEELGRADECODE  = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
          SHIFT_ID        = m_pPD_HEAT_DATA->getSHIFT_ID (1);
          CREW_ID         = m_pPD_HEAT_DATA->getCREW_ID (1);
          USERCODE        = m_pPD_HEAT_DATA->getUSERCODE (1);
          LADLENO         = m_pPD_HEAT_DATA->getLADLENO(1);
          LADLETYPE       = m_pPD_HEAT_DATA->getLADLETYPE(1);
          STEELMASS       = m_pPD_HEAT_DATA->getSTEELMASS(1);
          SLAGMASS        = m_pPD_HEAT_DATA->getSLAGMASS(1);

          AimTemp         = m_pPD_HEAT_DATA->getAIMTEMP_MOD(1);


          ProdDate        = CDataConversion::SetInvalidToDefault(ProdDate,  m_pPD_HEAT_DATA->getTREATSTART_PLAN(1));
          DepTime         = CDataConversion::SetInvalidToDefault(DepTime,   m_pPD_HEAT_DATA->getTREATEND_PLAN(1));
          AimTemp         = CDataConversion::SetInvalidToDefault(AimTemp,   m_pPD_HEAT_DATA->getAIMTEMP_PLAN(1));


          if ( LADLENO    != CSMC_DBData::unspecLong && 
               LADLETYPE  != CSMC_DBData::unspecString && 
               m_pPD_LADLE->select(LADLENO,LADLETYPE) )
          {
            LadleTareWeight = m_pPD_LADLE->getTAREWEIGHT(1);
          }
          else
          {
            std::string Msg = Function + " wrong or invalid Ladle Data";
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());
          }

          if ( m_pPDL_HEAT_DATA->select (HeatID, TreatID, m_pGC_Plant_Container->getPlant(PlantID)) )
          {
            CARNO = m_pPDL_HEAT_DATA->getCARNO(1);
          }
          else
          {
            std::string Msg = Function + " wrong or invalid LF-Heat Data";
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());
          }
        }
        else
        {
          std::string Msg = Function + " wrong or invalid Heat Data";
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());
        }

        if ( m_pPP_HEAT->select(HeatID) )
        {
          ROUTECODEPLAN = m_pPP_HEAT->getROUTECODE_PLAN(1);
        }
        else
        {
            log (" L2LF03 : Routecode not defined",3);       // EL_
        }

        //********    Log event data ***********************************************************************

        //********    Convert and check event data  ***********************************************************

        // ***************************************************
        // reset all data in case of cancellation or departure
        // L1 will reset HMI data
        // ***************************************************
        if ( Event.getMessage() == LF_EvMsg::evLFHeatCancellation ||
             Event.getMessage() == LF_EvMsg::evLFHeatDeparture )
        {
          CustHeatID  = "";
          CustTreatID = "";
        }


        // setting defaults if invalid data have been detected
        SHIFT_ID        = CDataConversion::SetInvalidToDefault(SHIFT_ID   ,"" ,CSMC_DBData::unspecString);
        CREW_ID         = CDataConversion::SetInvalidToDefault(CREW_ID    ,"" ,CSMC_DBData::unspecString);
        USERCODE        = CDataConversion::SetInvalidToDefault(USERCODE   ,"" ,CSMC_DBData::unspecString);
        STEELMASS       = CDataConversion::SetInvalidToDefault(STEELMASS  ,0. ,CSMC_DBData::unspecDouble);
        SLAGMASS        = CDataConversion::SetInvalidToDefault(SLAGMASS   ,0. ,CSMC_DBData::unspecDouble);
    		ROUTECODEPLAN   = CDataConversion::SetInvalidToDefault(ROUTECODEPLAN   ,"" ,CSMC_DBData::unspecString);

        LadleTareWeight  = CDataConversion::SetInvalidToDefault(LadleTareWeight    ,0.   ,CSMC_DBData::unspecDouble);
        LadleGrossWeight = CDataConversion::SetInvalidToDefault(LadleGrossWeight   ,0.   ,CSMC_DBData::unspecDouble);

        CLadleID LadleID;

        LadleId = CDataConversion::SetInvalidToDefault(LadleID.generateLadleID(LADLETYPE, LADLENO), "" );

        // truncate string data to fit telegram length
        HeatID          = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID         = CDataConversion::CheckLengthAndTruncate(TreatID,2);
        CustHeatID      = CDataConversion::CheckLengthAndTruncate(CustHeatID,10);
        CustTreatID     = CDataConversion::CheckLengthAndTruncate(CustTreatID,2);
        OrderID         = CDataConversion::CheckLengthAndTruncate(OrderID,10);
        STEELGRADECODE  = CDataConversion::CheckLengthAndTruncate(STEELGRADECODE,12);
        CREW_ID         = CDataConversion::CheckLengthAndTruncate(CREW_ID,2);
        USERCODE        = CDataConversion::CheckLengthAndTruncate(USERCODE,6);
        LadleId         = CDataConversion::CheckLengthAndTruncate(LadleId,4);
        ROUTECODEPLAN   = CDataConversion::CheckLengthAndTruncate(ROUTECODEPLAN,20);
        SHIFT_ID        = CDataConversion::CheckLengthAndTruncate(SHIFT_ID,2);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF03::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::TreatId,       TreatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::HeatIdCust,    CustHeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::TreatIdCust,   CustTreatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::LadleId,       LadleId);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::ProdOrderId,   OrderID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF03::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF03::CarNo,         CARNO);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::SteelGradeCode,STEELGRADECODE);

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF03::ProdDate,      ProdDate.asCORBAAny());
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF03::DepTime,       DepTime.asCORBAAny()); 

        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::ShiftCode,       SHIFT_ID );
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::CrewCode,      CREW_ID );
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::OperCode,      USERCODE );
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF03::RouteCode,     ROUTECODEPLAN);

        pTelcom_Interface->setDouble  (DataKeyL1, Telegram_L2LF03::LadleTareWeight,  LadleTareWeight);
        pTelcom_Interface->setDouble  (DataKeyL1, Telegram_L2LF03::LadleGrossWeight, LadleGrossWeight);
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF03::AimTemp,          CDataConversion::RoundToLong(AimTemp));

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF03::UpdateFlag,      UpdateFlag);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF03::Spare,           CIntfData::ToAny(seqSpare));

        pTelcom_Interface->setDouble  (DataKeyL1, Telegram_L2LF03::SteelWeight,  STEELMASS);
        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        pTelcom_Interface->showContent(DataKeyL1, 4);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);
    }// if ( pDM_Interface && pTelcom_Interface )
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//  Heat Announcement

bool CLF_EventHandler::provideData_L2LF06HeatCancel(CEventMessage& Event)
{
  //============       H E A T   C A N C E L E D       =============================
  bool RetValue=true;       // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF06";
  std::string Function = "CLF_EventHandler::provideData_L2LF06HeatCancel";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface && pDM_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************

      //********    Convert and check event data  ***********************************************************

      // in case of cancellation CustHeatID and CustTreatID may be invalid at DB
      CustHeatID  = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustHeatID));
      CustTreatID = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustTreatID));

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF06::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF06::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF06::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF06::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF06::Spare,         CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }// if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);
    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CLF_EventHandler::provideData_L2LF06HeatCancel",Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CLF_EventHandler::provideData_L2LF06HeatCancel",Action);
  }
  catch(...)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CLF_EventHandler::provideData_L2LF06HeatCancel",
      Action,__FILE__,__LINE__);
    RetValue = false;
  }
  return RetValue;
}//end of L2LF Heat Cancelled


bool CLF_EventHandler::provideData_L2LF07CompMode(CEventMessage& Event)
{
  //=================    C O M P U T E R   M O D E S     ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF07";
  std::string Function = "CLF_EventHandler::provideData_L2LF07CompMode";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long ModeStirr  = 0;
      long ModeMat    = 0;
      long ModeElec   = 0;

      //read the Computer Mode Availabilitys from L2
      seqComputerModes scm = CIntfData::ToCORBAType(pDM_Interface->getComputerModes (ProductID.c_str(), DATA::ComputerModeAvail));

      log(CIntfData::getContent(CIntfData::ToAny(scm)),4);

      //********    Log event data ***********************************************************************

      // in case of cancellation CustHeatID and CustTreatID may be invalid at DB
      CustHeatID  = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustHeatID));
      CustTreatID = CIntfData::ToStdString(pDM_Interface->getString(ProductID.c_str(), DATA::CustTreatID));
      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        for (long ii=0; ii < CIntfData::getLength(scm); ii++)
        {
          sComputerMode cm;

          if (CIntfData::getAt(cm, scm, ii) && cm.Status > 0)
          {
            //set the status for bottom stirring mode
            if (std::string(cm.Device) == std::string (DEF_COMP_MODES::Stirring))
              ModeStirr = 1;
            else if (std::string(cm.Device) == std::string(DEF_COMP_MODES::MatHandle))
              ModeMat = 1;
            else if (std::string(cm.Device) == std::string(DEF_COMP_MODES::Electric))
              ModeElec = 1;
          }// if (cm.Status > 0)
        } // end of Looping the Sequence

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF07::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF07::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF07::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF07::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF07::ModeMat,       ModeMat);
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF07::ModeStirr,     ModeStirr);
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF07::ModeElec,      ModeElec);

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF07::Spare,         CIntfData::ToAny(seqSpare));

        //********    Dispatch event ***********************************************************************
  
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}// end of L2LF07 Computer Modes

bool CLF_EventHandler::provideData_L2LF20VoltageTap(CEventMessage& Event)
{
  //============   V O L T A G E   T A P   /   R E G    C U R V E      ============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF20";
  std::string Function = "CLF_EventHandler::provideData_L2LF20VoltageTap";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();


    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long AimVoltTap = pDM_Interface->getLong(ProductID.c_str(), DATA::VoltTapNoAim);
      long AimCurveNo = pDM_Interface->getLong(ProductID.c_str(), DATA::ElectrodRegCurveAim);

      if (AimVoltTap != AimVoltTapPrev || AimCurveNo != AimCurveNoPrev)
      {
        ElPatternChanged = true;
        AimVoltTapPrev = AimVoltTap;
        AimCurveNoPrev = AimCurveNo;
      }
      else
        ElPatternChanged = false;

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        std::stringstream tmp_elec;
          tmp_elec << "******* Process data *********" << std::endl;

        //********    Write telegram data  ***********************************************************************

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20::HeatId,        HeatID);
        tmp_elec << "HeatID : "   << HeatID << std::endl;
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF20::CreateTime,    Now.asCORBAAny());
        tmp_elec << "CreateTime : "   << Now.asString() << std::endl;

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::AimCurveNo,    AimCurveNo);
        tmp_elec << "AimCurveNo : "   << AimCurveNo << std::endl;
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20::AimVoltTap,    AimVoltTap);
        tmp_elec << "AimVoltTap : "   << AimVoltTap << std::endl;

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF20::Spare,         CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        CDH_OUT_Task::getInstance()->setStateDetails(TlgName, tmp_elec.str(),4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2LF20 VoltageTap/RegCurve 

bool CLF_EventHandler::provideData_L2LF22PullElectrodes(CEventMessage& Event)
{
  //=======================    P U L L    E L E C T R O D E S     ===================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF22";
  std::string Function = "CLF_EventHandler::provideData_L2LF22PullElectrodes";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long ElecPullReq = pDM_Interface->getLong(ProductID.c_str(),DATA::ElecPullReq);      

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //********    Write telegram data  ***********************************************************************

        if ( ElecPullReq == 1 )
        {
          pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF22::UnitNo,        UnitNo);
          pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF22::HeatId,        HeatID);
          pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF22::TreatId,       TreatID);
          pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF22::CreateTime,    Now.asCORBAAny());   

          pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF22::Spare,         CIntfData::ToAny(seqSpare));

          pTelcom_Interface->showContent(DataKeyL1, 4);

          //********    Dispatch event ***********************************************************************

          SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        }
        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2LF22 Pull Electrodes

bool CLF_EventHandler::provideData_L2LF23ReleaseElectrodes(CEventMessage& Event)
{
  //==============    R E L E A S E   I N H I B I T   E L E C T R O D E S    =================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF23";
  std::string Function = "CLF_EventHandler::provideData_L2LF23ReleaseElectrodes";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      long ElecInhibitReq = pDM_Interface->getLong(ProductID.c_str(),DATA::ElecInhibitReq);      

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        long ActionFlag = 1;

        //Read the event message and set ReleaseFlag according to this message
        // ReleaseFlag: Release = True , Inhibit = false
        if   (ElecInhibitReq == 1 || Event.getMessage() == LF_EvMsg::evLFElectrodeHydraulicSystemInhibitRequest)
        {
          ActionFlag = 0;
        }

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF23::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF23::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF23::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF23::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF23::ActionFlag,    ActionFlag);

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF23::Spare,         CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2LF23 Release/Inhibit Electrodes

//bool CLF_EventHandler::provideData_L2LF25SampleRequest(CEventMessage& Event)
//{
//  //===========     T / S A M P L E   M E S S U R E M E N T  R E Q U E S T   ===================
//  bool RetValue = true; // assume success
//
//  std::string HeatID    = Event.getHeatID();
//  std::string TreatID   = Event.getTreatID();
//  std::string ProductID = Event.getProductID();
//  std::string OrderID   = Event.getOrderID();
//  std::string DataKey   = Event.getDataKey();
//  std::string PlantID   = Event.getPlantID();
//  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
//  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
//  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);
//
//  // truncate string data to fit telegram length
//  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);
//
//  std::string CustHeatID;
//  std::string CustTreatID;
//  std::string TlgName;
//  std::string DataKeyL1;
//  CDateTime Now;
//  DEF::seqLong seqSpare;
//
//  std::string Action = "Reading DM interface data from ";
//  Action +=  Event.getSender();
//  Action +=  "ProductID:";
//  Action +=  Event.getProductID();
//  Action +=  " - ";
//  Action +=  "Key:";
//  Action +=  Event.getDataKey();
//
//  try
//  {
//    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);
//
//    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
//
//    if ( pDM_Interface && pTelcom_Interface )
//    {
//      //********    preset data  ************************************************************************
//
//      TlgName   = "L2LF25";
//
//      
//      log("****************************************************************************************", 3);
//      log( TlgName + ": Start", 3);
//      log("****************************************************************************************", 3);
//
//
//      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);
//
//      CIntfData::preset(seqSpare,0,5);
//
//      //********    Read event related data  ************************************************************************
//      //Type: get and set
//      long Type         = 0;
//      bool TempReq      = pDM_Interface->getBoolean(ProductID.c_str(), DATA::TempMeasReq);
//      bool StSampleReq  = pDM_Interface->getBoolean(ProductID.c_str(), DATA::SteelSampleReq);
//
//      //********    Log event data ***********************************************************************
//
//      //********    Convert and check event data  ***********************************************************
//
//      checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID);
//
//      // truncate string data to fit telegram length
//      CustHeatID  = CDataConversion::CheckLengthAndTruncate(CustHeatID,10);
//      CustTreatID = CDataConversion::CheckLengthAndTruncate(CustTreatID,2);
//
//      // set right number for L1
//      //Type
//      //1 = Steel Sample
//      //2 = Slag Sample
//      //3 = Temperature 
//      //4 = CELOX
//      //5 = Slag CELOX
//
//      if (TempReq && StSampleReq) // CELOX
//        Type = 4;
//      else if (TempReq)           // TEMP
//        Type = 3;
//      else if (StSampleReq)       // STEEL
//        Type = 1;
//
//      //********    Write telegram data  ***********************************************************************
//      if ( Type != 0 )
//      {
//        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF25::UnitNo,        UnitNo);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF25::HeatId,        CustHeatID);
//        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF25::TreatId,       CustTreatID);
//        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF25::CreateTime,    Now.asCORBAAny());   
//
//        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF25::Type,          Type);
//
//        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF25::Spare,         CIntfData::ToAny(seqSpare));
//
//        pTelcom_Interface->showContent(DataKeyL1, 4);
//
//        //********    Dispatch event ***********************************************************************
//        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);
//      }
//      //********    End processing data  ***********************************************************************
//
//      log( TlgName + ": End", 3);
//
//    }
//    else
//    {
//      // EL_
//      RetValue=false;
//    }
//  }
//  catch(CORBA::SystemException& sExc) 
//  {
//    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
//      "CLF_EventHandler::provideData_L2LF25SampleRequest",
//      Action,__FILE__,__LINE__);
//  }
//  catch(CORBA::Exception& cExc) 
//  {
//    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
//      "CLF_EventHandler::provideData_L2LF25SampleRequest",
//      Action,__FILE__,__LINE__);
//  }
//  catch(...) 
//  {
//    cCBS_StdCORBA_Task::getInstance()->doOnException("CLF_EventHandler::provideData_L2LF25SampleRequest",
//      Action,__FILE__,__LINE__);
//    RetValue = false;
//  }
//  return RetValue;
//}//end of L2LF25 T/Sample measurement Request 


//##ModelId=4587CE040231
bool CLF_EventHandler::provideData_L2LF30ProcessPatternElec(CEventMessage& Event)
{
  //===========    E L E C T R I C   P R O C E S S   P A T T E R N     =====================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF30";
  std::string Function = "CLF_EventHandler::provideData_L2LF30ProcessPatternElec";

  long longEnergy   = 0;

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CIntfData::preset(seqSpare,0,5);

        //********    Read event related data  ************************************************************************
        seqLFElecPredRes SeqLFElecPredRes = CIntfData::ToCORBAType(pDM_Interface->getLFElecPredRes(ProductID.c_str(),DATA::LFElecPredRes));

        DEF::seqDouble SeqRemDurStep;  
        DEF::seqLong SeqElecEnergyStep;
        DEF::seqLong SeqTempEndStep; 
        DEF::seqLong SeqAimVoltTap;  
        DEF::seqLong SeqAimCurveNo; 
        DEF::seqLong SeqEnabled;     

        long NoOfSteps = 7;

        CIntfData::preset(SeqEnabled,       0  ,NoOfSteps);      
        CIntfData::preset(SeqRemDurStep,    0. ,NoOfSteps);  
        CIntfData::preset(SeqElecEnergyStep,0  ,NoOfSteps);
        CIntfData::preset(SeqTempEndStep,   0  ,NoOfSteps); 
        CIntfData::preset(SeqAimVoltTap,    0  ,NoOfSteps);  
        CIntfData::preset(SeqAimCurveNo,    0  ,NoOfSteps); 

        //// posible phases
        //DEF::seqString SeqElectricPhases;

        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingInitial);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingMain);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingFinal);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingTempHold);

        //********    Log event data ***********************************************************************

        log ( CIntfData::getContent(CIntfData::ToAny(SeqLFElecPredRes)),2);

        //********    Log event data ***********************************************************************

        //********    Convert and check event data  ***********************************************************

        // initial heating (0 + 1) main heating (2 + 3) final heating (4 + 5) and temp hold (6)
        for ( long j = 0 ; j < CIntfData::getLength(SeqLFElecPredRes); ++j )
        {
          sLFElecPredRes LFElecPredRes;
          CIntfData::getAt(LFElecPredRes, SeqLFElecPredRes, j);

          std::string ElecPhase            = LFElecPredRes.ElecPhase;
          long SeqNo                  = 0;
          long TempEndStep            = 0;
          long Step                   = LFElecPredRes.Step;
          long VoltTap                = LFElecPredRes.VoltTap;
          long ImpCurve               = LFElecPredRes.ImpCurve;
          long Enable                 = LFElecPredRes.Enable;
          long ElecEgyStep            = CDataConversion::RoundToLong(LFElecPredRes.ElecEgyStep);
          double DurStep              = LFElecPredRes.DurStep;

          // setting defaults if invalid data have been detected
          Step        = CDataConversion::SetInvalidToDefault(Step        ,0);
          VoltTap     = CDataConversion::SetInvalidToDefault(VoltTap     ,0);
          ImpCurve    = CDataConversion::SetInvalidToDefault(ImpCurve    ,0);
          Enable      = CDataConversion::SetInvalidToDefault(Enable      ,0);
          ElecEgyStep = CDataConversion::SetInvalidToDefault(ElecEgyStep ,0);
          DurStep     = CDataConversion::SetInvalidToDefault(DurStep     ,0.);

          bool EnableElecPattern = false;
          cCBS_StdInitBase::getInstance()->replaceWithEntry("TELEGRAM","EnableElecPattern",EnableElecPattern);

          if ( EnableElecPattern )
          {
            Enable = 1;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorMessage(sMessage, "CLF_EventHandler::provideData_L2LF30ProcessPatternElec() - Enabled set to 1 by ini file ");
          }


          if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingInitial )
          {
            SeqNo = 0;    
            if ( Step == 2 )
            {
              SeqNo = 1;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingMain )
          {
            SeqNo = 2;    
            if ( Step == 2 )
            {
              SeqNo = 3;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingFinal )
          {
            SeqNo = 4;    
            if ( Step == 2 )
            {
              SeqNo = 5;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingTempHold )
          {
            SeqNo = 6;    
          }

          CIntfData::setAt(SeqRemDurStep     ,DurStep       ,SeqNo);  
          CIntfData::setAt(SeqElecEnergyStep ,ElecEgyStep   ,SeqNo);
          CIntfData::setAt(SeqTempEndStep    ,TempEndStep   ,SeqNo); 
          CIntfData::setAt(SeqAimVoltTap     ,VoltTap       ,SeqNo);  
          CIntfData::setAt(SeqAimCurveNo     ,ImpCurve      ,SeqNo); 
          CIntfData::setAt(SeqEnabled        ,Enable        ,SeqNo);      


        } // for ( long j = 0 ; j < CIntfData::getLength(SeqLFElecPredRes); ++j )

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF30::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF30::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF30::TreatId,       TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::CreateTime,    Now.asCORBAAny());   

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::Enabled,       CIntfData::ToAny(SeqEnabled));
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::RemDurStep,    CIntfData::ToAny(SeqRemDurStep));
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::ElecEnergyStep,CIntfData::ToAny(SeqElecEnergyStep));
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::TempEndStep,   CIntfData::ToAny(SeqTempEndStep));
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::AimVoltTap,    CIntfData::ToAny(SeqAimVoltTap));
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::AimCurveNo,    CIntfData::ToAny(SeqAimCurveNo));

        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF30::Spare,         CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2LF30 Electric Process Pattern

bool CLF_EventHandler::provideData_L2LF31ProcessPatternStirr(CEventMessage& Event)
{
  //===================    S T I R R I N G   P A T T E R N       =======================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF31";
  std::string Function = "CLF_EventHandler::provideData_L2LF31ProcessPatternStirr";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();


    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      DEF::seqLong    SeqPhaseNo;
      DEF::seqLong    SeqEnabled;
      DEF::seqDouble  SeqDuration;
      DEF::seqLong    SeqStirrInt;
      DEF::seqDouble  SeqGasFlow;
      DEF::seqLong    SeqStirrGasType;
      DEF::seqLong    SeqStepPrior;

      long NoOfSteps = 20;
      long StepNo    = 0;

      CIntfData::preset(SeqPhaseNo,        0  ,NoOfSteps);  
      CIntfData::preset(SeqEnabled,        0  ,NoOfSteps);  
      CIntfData::preset(SeqDuration,       0. ,NoOfSteps);  
      CIntfData::preset(SeqStirrInt,       0  ,NoOfSteps);  
      CIntfData::preset(SeqGasFlow,        0. ,NoOfSteps);  
      CIntfData::preset(SeqStirrGasType,   0  ,NoOfSteps);  
      CIntfData::preset(SeqStepPrior,      0  ,NoOfSteps);  

      seqLFStirrPredRes SeqLFStirrPredRes = CIntfData::ToCORBAType(pDM_Interface->getLFStirrPredRes(ProductID.c_str(), DATA::LFStirrPredRes));

      std::string sLFActStirrActivity     = pDM_Interface->getString(ProductID.c_str(), DATA::LFActStirrActivity);

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        std::stringstream off;
        off << "******* " << HeatID <<" *********" << std::endl;

        std::stringstream on;
        on << "******** " << HeatID <<" *********" << std::endl;

        for (long i=0; i < CIntfData::getLength(SeqLFStirrPredRes); i++)
        {
          sLFStirrPredRes LFStirrPredRes;

          CIntfData::getAt(LFStirrPredRes,SeqLFStirrPredRes,i);

          std::string StirrPhase      = LFStirrPredRes.StirrPhase;
          std::string GasType         = LFStirrPredRes.GasType;
          double StirrFlow            = LFStirrPredRes.StirrFlow*1000;  //// m³/min -> l/min 
          double DurStep              = LFStirrPredRes.DurStep;
          long Priority               = LFStirrPredRes.Priority;
          long StirrIntensity         = LFStirrPredRes.StirrIntensity;
          long Enable                 = LFStirrPredRes.Enable;
          long Order                  = LFStirrPredRes.Order;
          long isPatternOrActivity    = LFStirrPredRes.isPatternOrActivity;
          long VoltTap                = LFStirrPredRes.VoltTap;
          long ImpCurve               = LFStirrPredRes.ImpCurve;
          long GasTypeNo              = 0;

          long PRACPHASEORDERNO       = 0;

          if (isPatternOrActivity == 1)    //check if this phase is used
          {
            continue;
          }

          //Get the rows from database table by StirrPhase
          if ( StirrPhase != DEF::Inv_String && m_pGCL_STIRR_PHASE->selectByPracPhaseModel(StirrPhase))
          {
            PRACPHASEORDERNO = m_pGCL_STIRR_PHASE->getPRACPHASEORDERNO(1);
            StirrPhase       = m_pGCL_STIRR_PHASE->getPRACPHASE(1); 
          }
          else
          {
            std::string Msg = Function + " wrong or invalid StirrPhase" + StirrPhase;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());

            continue;          
          }        

          // setting defaults if invaliud data have been detected
          StirrFlow             = CDataConversion::SetInvalidToDefault(StirrFlow            ,0.);
          DurStep               = CDataConversion::SetInvalidToDefault(DurStep              ,0.);
          Priority              = CDataConversion::SetInvalidToDefault(Priority             ,0);
          StirrIntensity        = CDataConversion::SetInvalidToDefault(StirrIntensity       ,0);
          Enable                = CDataConversion::SetInvalidToDefault(Enable               ,0);
          Order                 = CDataConversion::SetInvalidToDefault(Order                ,0);
          isPatternOrActivity   = CDataConversion::SetInvalidToDefault(isPatternOrActivity  ,0);
          VoltTap               = CDataConversion::SetInvalidToDefault(VoltTap              ,0);
          ImpCurve              = CDataConversion::SetInvalidToDefault(ImpCurve             ,0);


          if (GasType == DEF_GC_STIRR_GAS_TYPE::Ar) 
          {
            GasTypeNo = 1;
          }
          else if (GasType == DEF_GC_STIRR_GAS_TYPE::N2) 
          {
            GasTypeNo = 2;
          }
          else
          {
            std::string Msg = Function + " wrong or invalid GasType";
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());

            continue; 
          }


          if ( StirrPhase == DEF_GCL_STIRR_PHASE::SlagBreaking )
          {
            StepNo = 0;   // pos 1 in telegram  
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Deoxidation )
          {
            StepNo = 1;    // pos 2 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::InitialHeating )
          {
            StepNo = 2;    // pos 3 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::MainHeating )
          {
            StepNo = 3;    // pos 4 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::FinalHeating )
          {
            StepNo = 4;    // pos 5 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CoolingStirring )
          {
            StepNo = 5;    // pos 7 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SlagForming )
          {
            StepNo = 6;    // pos 8 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::FirstAlloying )
          {
            StepNo = 7;    // pos 8 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SecondAlloying )
          {
            StepNo = 8;    // pos 9 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CoolingMaterial )
          {
            StepNo = 9;    // pos 10 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Trimming )
          {
            StepNo = 10;    // pos 11 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SoftStirring )
          {
            StepNo = 11;    // pos 12 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CaTreatment )
          {
            StepNo = 12;    // pos 13 in telegram  
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CleanStirring )
          {
            StepNo = 13;    // pos 14 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::TempHold )
          {
            StepNo = 14;    // pos 15 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Sampling )
          {
            StepNo = 15;    // pos 16 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Desulphurization )
          {
            StepNo = 16;    // pos 17 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Intermediate )
          {
            StepNo = 17;    // pos 18 in telegram 
          }

          if ( sLFActStirrActivity == StirrPhase )
          {
            Enable = 1;
          }

          // u153 - do not set values for steps with Duration = 0
          if (DurStep == 0.)
          {
            CIntfData::setAt(SeqPhaseNo       ,0  ,StepNo);
            CIntfData::setAt(SeqEnabled       ,0  ,StepNo);
            CIntfData::setAt(SeqDuration      ,0. ,StepNo);  
            CIntfData::setAt(SeqStirrInt      ,0  ,StepNo); 
            CIntfData::setAt(SeqGasFlow       ,0. ,StepNo);
            CIntfData::setAt(SeqStirrGasType  ,0  ,StepNo);
            CIntfData::setAt(SeqStepPrior     ,0  ,StepNo);
          }
          else
          {
            CIntfData::setAt(SeqPhaseNo       ,PRACPHASEORDERNO ,StepNo);
            CIntfData::setAt(SeqEnabled       ,Enable           ,StepNo);
            CIntfData::setAt(SeqDuration      ,DurStep          ,StepNo);  
            CIntfData::setAt(SeqStirrInt      ,StirrIntensity   ,StepNo); 
            CIntfData::setAt(SeqGasFlow       ,StirrFlow        ,StepNo);
            CIntfData::setAt(SeqStirrGasType  ,GasTypeNo        ,StepNo);
            CIntfData::setAt(SeqStepPrior     ,Priority         ,StepNo);
          }

          if (Enable == 0)
          {
            off << StirrPhase << std::endl;
          }
          else
          {
            on << StirrPhase << std::endl;
          }

          //StepNo ++ ;

          if ( i > 17 )
          {
            break;
          }
        } // for (long i=0; i < CIntfData::getLength(SeqLFStirrPredRes); i++)

        CDH_OUT_Task::getInstance()->setStateDetails("Enable", on.str(),4);
        CDH_OUT_Task::getInstance()->setStateDetails("Disable", off.str(),4);
        CDH_OUT_Task::getInstance()->setStateDetails("SuggestedFromModel", sLFActStirrActivity,1);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF31::UnitNo,      UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF31::HeatId,      HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF31::TreatId,     TreatID);
        pTelcom_Interface->setAny     (DataKeyL1, Telegram_L2LF31::CreateTime,  Now.asCORBAAny());   

        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::PhaseNo,      CIntfData::ToAny(SeqPhaseNo) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::Enabled,      CIntfData::ToAny(SeqEnabled) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::Duration,     CIntfData::ToAny(SeqDuration) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::StirrInt,     CIntfData::ToAny(SeqStirrInt) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::StirrGasFlow, CIntfData::ToAny(SeqGasFlow) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::StirrGasType, CIntfData::ToAny(SeqStirrGasType) );
        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::StepPriority, CIntfData::ToAny(SeqStepPrior) );

        pTelcom_Interface->setAny     (DataKeyL1,Telegram_L2LF31::Spare,        CIntfData::ToAny(seqSpare));

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}//end of L2LF31 Stirring Pattern

bool CLF_EventHandler::provideData_L2LF70MatHandling(CEventMessage& Event)
{
  //======    M A T E R I A L  H A N D L I N G   M O D E L   R E S U L T    =================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF70";
  std::string Function = "CLF_EventHandler::provideData_L2LF70MatHandling";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start:", 3);
      log("****************************************************************************************", 3);

      CIntfData::preset(seqSpare,0,5);

      //********    Convert and check event data  ***********************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //*******************************************************************************
        // sending reset event !
        // L1 has to reset all recipes that are not yet in use !
        //*******************************************************************************

        //********    Write telegram data  ***********************************************************************
        {
          long SeqLenght = 10;
          DEF::seqString  SeqMatCode;
          DEF::seqLong    SeqMatWeight;
          DEF::seqLong    SeqMatSequence;
          DEF::seqLong  SeqFeedSpeed;

          // preset sequences with empty values
          CIntfData::preset(SeqMatCode    ,"" ,SeqLenght);
          CIntfData::preset(SeqMatWeight  ,0  ,SeqLenght);
          CIntfData::preset(SeqMatSequence,0  ,SeqLenght);
          CIntfData::preset(SeqFeedSpeed  ,0 ,SeqLenght);

          DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName+"reset");

          //set the data to telcom interface
          pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::UnitNo,      UnitNo);
          pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::HeatId,      HeatID);
          pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::TreatId,     TreatID);
          pTelcom_Interface->setAny    (DataKeyL1,Telegram_L2LF70::CreateTime,  Now.asCORBAAny());   

          pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::Source,    0);
          pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::RecipeNo,  0);

          pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatCode     ,CIntfData::ToAny(SeqMatCode));
          pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
          pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

          pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::FeedRate    ,CIntfData::ToAny(SeqFeedSpeed));

          pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::Spare,CIntfData::ToAny(seqSpare));

          pTelcom_Interface->showContent(DataKeyL1, 4);

          //CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          //sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          //pEventLog->EL_RejectingRecipe(sMessage,"",CustHeatID.c_str(),CustTreatID.c_str(),DEF_GC_PLANT_DEF::LF );

          //********    Dispatch event ***********************************************************************
          //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 


          SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

        }

        // request by L1 one, send only reset telegram at evLFHeatDeparture but not model set points
        if ( Event.getMessage() == LF_EvMsg::evLFModelResultRecipeSetpoints )
        {
          DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

          if ( pDM_Interface )
          {
            DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

            //********    Read event related data  ************************************************************************
            seqRecipeList RecipeList = CIntfData::ToCORBAType(pDM_Interface->getRecipeList(ProductID.c_str(),DATA::LFMatRecipe));

            //********    Log event data ***********************************************************************

            //********    Write telegram data  ***********************************************************************
            // loop entire list and create one L1 Telegram per entry
            for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
            {
              // get current Recipe from RecipeList
              sRecipe Recipe;
              CIntfData::getAt(Recipe,RecipeList,ii);

              long l1RecipeNo = 0;
              long l1BatchNo  = 0;
              long l1Source   = 0;

              //Get the recipe name from the table by recipe number and recipe name
              l1RecipeNo = m_pGC_Recipe_L1Container->getL1RecipeNoByL2Name ( Recipe.RecipeNo,std::string(Recipe.RecipeName));

              if ( l1RecipeNo != 0 )
              {
                // get source from the table by string from L2
                l1Source = m_pGC_SourceContainer->getSourceL1InfoNoByName( std::string(Recipe.RecipeSource) );

                // no of materials per telegram is limited
                long SeqLenght = 10;

                //get the content of current recipe
                seqBatchPrio SeqBatchPrio = Recipe.RecipeContent;

                DEF::seqString  SeqMatCode;
                DEF::seqLong    SeqMatWeight;
                DEF::seqLong    SeqMatSequence;
                DEF::seqDouble  SeqFeedSpeed;

                // preset sequences with empty values
                CIntfData::preset(SeqMatCode      ,"" ,SeqLenght);
                CIntfData::preset(SeqMatWeight    ,0  ,SeqLenght);
                CIntfData::preset(SeqMatSequence  ,0  ,SeqLenght);
                CIntfData::preset(SeqFeedSpeed    ,0. ,SeqLenght);

                long ActSeqLenght = SeqLenght;

                long MatCounter = 0;
                long TelCounter = 1;

                if ( CIntfData::getLength(SeqBatchPrio) != 0 )
                {
                  // max no of Materials limited by SeqLenght
                  // send more than one telegram per Recipe if required
                  for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
                  {
                    // read batch data from Recipe
                    sBatchPrio BatchPrio;
                    CIntfData::getAt(BatchPrio,SeqBatchPrio,jj);

                    long ChargPrio        = BatchPrio.ChargPrio;
                    std::string MatCode   = BatchPrio.BatchData.MatCode;
                    double Mass           = BatchPrio.BatchData.Mass;
                    
                    double FeedSpeed       = 0.;

                    if ( m_pGT_MAT && m_pGT_MAT->select(MatCode) )
                    {
                      FeedSpeed   = m_pGT_MAT->getFEED_SPEED(1);

                      FeedSpeed   = CDataConversion::SetInvalidToDefault(FeedSpeed,0.);
                    }

                    MatCode   = CDataConversion::CheckLengthAndTruncate(MatCode,4);

                    CIntfData::setAt(SeqMatCode     ,MatCode.c_str() ,MatCounter);
                    CIntfData::setAt(SeqMatWeight   ,CDataConversion::RoundToLong(Mass),MatCounter);
                    CIntfData::setAt(SeqMatSequence ,ChargPrio       ,MatCounter);
                    CIntfData::setAt(SeqFeedSpeed   ,FeedSpeed       ,MatCounter);

                    // check if no of materials (CIntfData::getLength(SeqBatchPrio)) fits to
                    // length of telegram sequence (SeqLenght)
                    if ( CIntfData::getLength(SeqBatchPrio) >= TelCounter * SeqLenght - 1 || 
                         CIntfData::getLength(SeqBatchPrio) == jj + 1                     )
                    {
                      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

                      //set the data to telcom interface
                      pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::UnitNo,      UnitNo);
                      pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::HeatId,      HeatID);
                      pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::TreatId,     TreatID);
                      pTelcom_Interface->setAny    (DataKeyL1,Telegram_L2LF70::CreateTime,  Now.asCORBAAny());   

                      pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::Source,    l1Source);
                      pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::RecipeNo,  l1RecipeNo);                    

                      pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatCode     ,CIntfData::ToAny(SeqMatCode));
                      pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
                      pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

                      pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::FeedRate    ,CIntfData::ToAny(SeqFeedSpeed));

                      pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::Spare,CIntfData::ToAny(seqSpare));

                      pTelcom_Interface->showContent(DataKeyL1, 4);

                      //********    Dispatch event ***********************************************************************
                      //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 

                      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

                      CIntfData::preset(SeqMatCode    ,"",SeqLenght);
                      CIntfData::preset(SeqMatWeight  ,0,SeqLenght);
                      CIntfData::preset(SeqMatSequence,0,SeqLenght);

                      RetValue = true;

                      TelCounter++;
                      MatCounter = 0;
                    }

                    MatCounter++;

                  } // for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
                } // if ( CIntfData::getLength(SeqBatchPrio) != 0 )
                else
                {
                  //// send an empty telegram for this recipe to reset L1 Batches!
                  //// readrding only recipes that ar not yet in use (not yet enabled)
                  //if ( !m_pPD_RECIPE->isRecipeIniUse(HeatID,TreatID,DEF_GC_PLANT_DEF::LF,std::string(Recipe.RecipeName),Recipe.RecipeNo,std::string(Recipe.RecipeSource) ) )
                  //{
                  //  DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

                  //  //set the data to telcom interface
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::UnitNo,      UnitNo);
                  //  pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::HeatId,      HeatID);
                  //  pTelcom_Interface->setString (DataKeyL1,Telegram_L2LF70::TreatId,     TreatID);
                  //  pTelcom_Interface->setAny    (DataKeyL1,Telegram_L2LF70::CreateTime,  Now.asCORBAAny());   

                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::RecipeNo,  l1RecipeNo);
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::BatchNo,   l1BatchNo);
                  //  pTelcom_Interface->setLong   (DataKeyL1,Telegram_L2LF70::Source,    l1Source);

                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::Spare,CIntfData::ToAny(seqSpare));

                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatCode     ,CIntfData::ToAny(SeqMatCode));
                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatWeight   ,CIntfData::ToAny(SeqMatWeight));
                  //  pTelcom_Interface->setAny    (DataKeyL1, Telegram_L2LF70::MatSequence ,CIntfData::ToAny(SeqMatSequence));

                  //  pTelcom_Interface->showContent(DataKeyL1, 4);

                  //  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                  //  pEventLog->EL_RejectingRecipe(sMessage,Recipe.RecipeName,CustHeatID.c_str(),CustTreatID.c_str(),DEF_GC_PLANT_DEF::LF );

                  //  //********    Dispatch event ***********************************************************************
                  //  //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 

                  //      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

                  //}
                } // // if ( CIntfData::getLength(SeqBatchPrio) == 0 )
              }  // if ( l1RecipeNo != 0 )
            }  // for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
          }//  if ( pDM_Interface )
          else
          {
            // EL_
            RetValue=false;
          }      
        }

        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }      

      log( TlgName + ": End", 3);
    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}// end of L2LF70 Model Parameter

bool CLF_EventHandler::provideData_L2LF71MatAvailRequest(CEventMessage& Event)
{
  //==========    M A T E R I A L   A V A I L A B I L I T Y   R E Q U E S T    =======
  bool RetValue=true;       // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF71";
  std::string Function = "CLF_EventHandler::provideData_L2LF71MatAvailRequest";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  *************************************************************

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ********************************************************

      //********    Write telegram data  ******************************************************************
      pTelcom_Interface->setLong  (DataKeyL1, Telegram_L2LF71::UnitNo,      UnitNo);
      pTelcom_Interface->setAny   (DataKeyL1, Telegram_L2LF71::CreateTime,  Now.asCORBAAny());   
      pTelcom_Interface->setAny   (DataKeyL1, Telegram_L2LF71::Spare,       CIntfData::ToAny(seqSpare));

      pTelcom_Interface->showContent(DataKeyL1, 4);

      //********    Dispatch event ***********************************************************************
      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

      //********    End processing data  ****************************************************************
      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }
  }
  catch(CORBA::SystemException& sExc)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CLF_EventHandler::provideData_L2LF71MatAvailRequest",Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CLF_EventHandler::provideData_L2LF71MatAvailRequest",Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CLF_EventHandler::provideData_L2LF71MatAvailRequest",
      Action);
    RetValue = false;
  }
  return RetValue;
}//end of L2LF Material Availability Request

bool CLF_EventHandler::provideData_L2LF72StatusRequest(CEventMessage& Event)
{
  //==========    P L A N T   S T A T U S   R E Q U E S T    =======
  bool RetValue=true;       // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF72";
  std::string Function = "CLF_EventHandler::provideData_L2LF72StatusRequest";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pTelcom_Interface )
    {
      //********    preset data  ************************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Write telegram data  ***********************************************************************
      pTelcom_Interface->setAny (DataKeyL1, Telegram_L2LF72::CreateTime, Now.asCORBAAny());   
      pTelcom_Interface->setAny (DataKeyL1, Telegram_L2LF72::Spare,CIntfData::ToAny(seqSpare)); 

      pTelcom_Interface->showContent(DataKeyL1, 4);

      //********    Dispatch event ***********************************************************************

      SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

    }
    else
    {
      RetValue=false;
    }
  }
  catch(CORBA::SystemException& sExc)
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
      "CLF_EventHandler::provideData_L2LF72StatusRequest",Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
      "CLF_EventHandler::provideData_L2LF72StatusRequest",Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CLF_EventHandler::provideData_L2LF72StatusRequest",
      Action);
    RetValue = false;
  }
  return RetValue;
}//end of L2LF Material Availability Request

bool CLF_EventHandler::provideData_L2LF20_VOLTAGE_TAP(CEventMessage& Event)
{
  //============   V O L T A G E   T A P   /   R E G    C U R V E      ============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF20_VOLTAGE_TAP";
  std::string Function = "CLF_EventHandler::provideData_L2LF20_VOLTAGE_TAP";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();


    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************
      
      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      //********    Read event related data  ************************************************************************
      long AimVoltTap = pDM_Interface->getLong(ProductID.c_str(), DATA::VoltTapNoAim);
      long AimCurveNo = pDM_Interface->getLong(ProductID.c_str(), DATA::ElectrodRegCurveAim);

      if (AimVoltTap != AimVoltTapPrev || AimCurveNo != AimCurveNoPrev)
      {
        ElPatternChanged = true;
        AimVoltTapPrev = AimVoltTap;
        AimCurveNoPrev = AimCurveNo;
      }
      else
        ElPatternChanged = false;

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        //********    Write telegram data  ***********************************************************************
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::UnitNo,        UnitNo);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::CreateTime,    Now.toDBString());   
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::HeatId,        HeatID);
        pTelcom_Interface->setString  (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::TreatId,       TreatID);

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::AimCurveNo,    AimCurveNo);
        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::AimVoltTap,    AimVoltTap);

        pTelcom_Interface->setLong    (DataKeyL1, Telegram_L2LF20_VOLTAGE_TAP::Spare,         0);

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}

bool CLF_EventHandler::provideData_L2LF30_ELEC_PATT(CEventMessage& Event)
{
  //===========    E L E C T R I C   P R O C E S S   P A T T E R N     =====================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF30_ELEC_PATT";
  std::string Function = "CLF_EventHandler::provideData_L2LF30_ELEC_PATT";

  long longEnergy   = 0;

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CIntfData::preset(seqSpare,0,5);

        //********    Read event related data  ************************************************************************
        seqLFElecPredRes SeqLFElecPredRes = CIntfData::ToCORBAType(pDM_Interface->getLFElecPredRes(ProductID.c_str(),DATA::LFElecPredRes));

        DEF::seqDouble SeqRemDurStep;  
        DEF::seqLong SeqElecEnergyStep;
        DEF::seqLong SeqTempEndStep; 
        DEF::seqLong SeqAimVoltTap;  
        DEF::seqLong SeqAimCurveNo; 
        DEF::seqLong SeqEnabled;     
        DEF::seqLong SeqActive;     // for internal use

        long NoOfSteps = 7;

        CIntfData::preset(SeqEnabled,       0  ,NoOfSteps);      
        CIntfData::preset(SeqRemDurStep,    0. ,NoOfSteps);  
        CIntfData::preset(SeqElecEnergyStep,0  ,NoOfSteps);
        CIntfData::preset(SeqTempEndStep,   0  ,NoOfSteps); 
        CIntfData::preset(SeqAimVoltTap,    0  ,NoOfSteps);  
        CIntfData::preset(SeqAimCurveNo,    0  ,NoOfSteps); 
        CIntfData::preset(SeqActive,        0  ,NoOfSteps); // for internal use

        //// posible phases
        //DEF::seqString SeqElectricPhases;

        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingInitial);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingMain);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingFinal);
        //CIntfData::insert(SeqElectricPhases,DEF_LF_PHASES::HeatingTempHold);

        //********    Log event data ***********************************************************************

        log ( CIntfData::getContent(CIntfData::ToAny(SeqLFElecPredRes)),2);

        //********    Log event data ***********************************************************************

        //********    Convert and check event data  ***********************************************************

        // initial heating (0 + 1) main heating (2 + 3) final heating (4 + 5) and temp hold (6)
        for ( long j = 0 ; j < CIntfData::getLength(SeqLFElecPredRes); ++j )
        {
          sLFElecPredRes LFElecPredRes;
          CIntfData::getAt(LFElecPredRes, SeqLFElecPredRes, j);

          std::string ElecPhase            = LFElecPredRes.ElecPhase;
          long SeqNo                  = 0;
          long TempEndStep            = 0;
          long Step                   = LFElecPredRes.Step;
          long VoltTap                = LFElecPredRes.VoltTap;
          long ImpCurve               = LFElecPredRes.ImpCurve;
          long Enable                 = LFElecPredRes.Enable;
          long ElecEgyStep            = CDataConversion::RoundToLong(LFElecPredRes.ElecEgyStep);
          double DurStep              = LFElecPredRes.DurStep;
          long Active                 = 1;

          // setting defaults if invalid data have been detected
          Step        = CDataConversion::SetInvalidToDefault(Step        ,0);
          VoltTap     = CDataConversion::SetInvalidToDefault(VoltTap     ,0);
          ImpCurve    = CDataConversion::SetInvalidToDefault(ImpCurve    ,0);
          Enable      = CDataConversion::SetInvalidToDefault(Enable      ,0);
          ElecEgyStep = CDataConversion::SetInvalidToDefault(ElecEgyStep ,0);
          DurStep     = CDataConversion::SetInvalidToDefault(DurStep     ,0.);

          if ( ElecEgyStep == 0 )
          {
            Active                 = 0;
          }

          bool EnableElecPattern = false;
          cCBS_StdInitBase::getInstance()->replaceWithEntry("TELEGRAM","EnableElecPattern",EnableElecPattern);

          if ( EnableElecPattern )
          {
            Enable = 1;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorMessage(sMessage, "CLF_EventHandler::provideData_L2LF30ProcessPatternElec() - Enabled set to 1 by ini file ");
          }


          if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingInitial )
          {
            SeqNo = 0;    
            if ( Step == 2 )
            {
              SeqNo = 1;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingMain )
          {
            SeqNo = 2;    
            if ( Step == 2 )
            {
              SeqNo = 3;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingFinal )
          {
            SeqNo = 4;    
            if ( Step == 2 )
            {
              SeqNo = 5;    
            }
          }
          else if ( std::string(LFElecPredRes.ElecPhase) == DEF_LF_PHASES::HeatingTempHold )
          {
            SeqNo = 6;    
          }

          CIntfData::setAt(SeqRemDurStep     ,DurStep       ,SeqNo);  
          CIntfData::setAt(SeqElecEnergyStep ,ElecEgyStep   ,SeqNo);
          CIntfData::setAt(SeqTempEndStep    ,TempEndStep   ,SeqNo); 
          CIntfData::setAt(SeqAimVoltTap     ,VoltTap       ,SeqNo);  
          CIntfData::setAt(SeqAimCurveNo     ,ImpCurve      ,SeqNo); 
          CIntfData::setAt(SeqEnabled        ,Enable        ,SeqNo);      
          CIntfData::setAt(SeqActive         ,Active        ,SeqNo);      

        } // for ( long j = 0 ; j < CIntfData::getLength(SeqLFElecPredRes); ++j )

        //********    Write telegram data  ***********************************************************************

        Telegram_L2LF30_ELEC_PATT::t_ENTRY seqENTRY;

        for(long j = 0; j < NoOfSteps ; j++)
        {
          Telegram_L2LF30_ELEC_PATT::sENTRY ENTRY;
          
          ENTRY.MessageIndex            = j;
          ENTRY.HeatId                  = HeatID.c_str()         ;
          ENTRY.TreatId                 = TreatID.c_str()        ;

          long Active                   = 0;

          CIntfData::getAt(Active          , SeqActive        , j);

					//Sankar as per L1 request irresepective of Active 0/1 ActivityType must be send and now it is disabled
          /*if ( j == 0 || j == 1 )
          {
            ENTRY.ActivityType = 3;
          }
          else if ( j == 2 || j == 3 )
          {
            ENTRY.ActivityType = 4;
          }
          else if ( j == 4 || j == 5 )
          {
            ENTRY.ActivityType = 5;
          }
          else if ( j == 6 )
          {
            ENTRY.ActivityType = 15;
          }

          if ( j == 0 || j == 2 ||  j == 4 || j == 6 )
          {
            ENTRY.StepNo = 1;
          }
          else if ( j == 1 || j == 3 ||  j == 5 )
          {
            ENTRY.StepNo = 2;
          }

          CIntfData::getAt(ENTRY.Enabled          , SeqEnabled        , j);
          CIntfData::getAt(ENTRY.RemDurStep       , SeqRemDurStep     , j);
          CIntfData::getAt(ENTRY.ElecEnergyStep   , SeqElecEnergyStep , j);
          CIntfData::getAt(ENTRY.TempEndStep      , SeqTempEndStep    , j);
          CIntfData::getAt(ENTRY.AimVoltTap       , SeqAimVoltTap     , j);
          CIntfData::getAt(ENTRY.AimCurveNo       , SeqAimCurveNo     , j);
					*/
					
          if ( Active == 1 )
          {
            if ( j == 0 || j == 1 )
            {
              ENTRY.ActivityType = 3;
            }
            else if ( j == 2 || j == 3 )
            {
              ENTRY.ActivityType = 4;
            }
            else if ( j == 4 || j == 5 )
            {
              ENTRY.ActivityType = 5;
            }
            else if ( j == 6 )
            {
              ENTRY.ActivityType = 15;
            }

            if ( j == 0 || j == 2 ||  j == 4 || j == 6 )
            {
              ENTRY.StepNo = 1;
            }
            else if ( j == 1 || j == 3 ||  j == 5 )
            {
              ENTRY.StepNo = 2;
            }

            CIntfData::getAt(ENTRY.Enabled          , SeqEnabled        , j);
            CIntfData::getAt(ENTRY.RemDurStep       , SeqRemDurStep     , j);
            CIntfData::getAt(ENTRY.ElecEnergyStep   , SeqElecEnergyStep , j);
            CIntfData::getAt(ENTRY.TempEndStep      , SeqTempEndStep    , j);
            CIntfData::getAt(ENTRY.AimVoltTap       , SeqAimVoltTap     , j);
            CIntfData::getAt(ENTRY.AimCurveNo       , SeqAimCurveNo     , j);
          }
          else
          {
            ENTRY.ActivityType    = 0;
            ENTRY.StepNo          = 0;
            ENTRY.Enabled         = 0;
            ENTRY.RemDurStep      = 0.;
            ENTRY.ElecEnergyStep  = 0;
            ENTRY.TempEndStep     = 0;
            ENTRY.AimVoltTap      = 0;
            ENTRY.AimCurveNo      = 0;
          }
					

          ENTRY.Spare_1 = 0;
          ENTRY.Spare_2 = 0;

          CIntfData::insert(seqENTRY,ENTRY);
          //********    Dispatch event ****** *****************************************************************
        }

        CORBA::Any seqAny;
        seqAny = CIntfData::ToAny(seqENTRY);

        //set the data to telcom interface
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF30_ELEC_PATT::HeatId,          HeatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF30_ELEC_PATT::TreatId,         TreatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF30_ELEC_PATT::CreateTime,      Now.toDBString());   

        pTelcom_Interface->setAny      ( DataKeyL1, Telegram_L2LF30_ELEC_PATT::ENTRY,           seqAny);

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}

bool CLF_EventHandler::provideData_L2LF31_STIRR_PATT(CEventMessage& Event)
{
  //===================    S T I R R I N G   P A T T E R N       =======================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));
  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID); 
  long UnitNo           = m_pGC_Plant_Container->getPlantNo(PlantID);

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  std::string CustHeatID;
  std::string CustTreatID;
  std::string DataKeyL1;
  CDateTime Now;
  DEF::seqLong seqSpare;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF31_STIRR_PATT";
  std::string Function = "CLF_EventHandler::provideData_L2LF31_STIRR_PATT";

  try
  {
    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();


    if ( pDM_Interface && pTelcom_Interface )
    {
      //********    preset data  ***********************************************************************

      log("****************************************************************************************", 3);
      log( TlgName + ": Start", 3);
      log("****************************************************************************************", 3);


      DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

      CIntfData::preset(seqSpare,0,5);

      //********    Read event related data  ************************************************************************
      DEF::seqLong    SeqPhaseNo;
      DEF::seqLong    SeqEnabled;
      DEF::seqDouble  SeqDuration;
      DEF::seqLong    SeqStirrInt;
      DEF::seqDouble  SeqGasFlow;
      DEF::seqLong    SeqStirrGasType;
      DEF::seqLong    SeqStepPrior;

      long NoOfSteps = 20;
      long StepNo    = 0;

      CIntfData::preset(SeqPhaseNo,        0  ,NoOfSteps);  
      CIntfData::preset(SeqEnabled,        0  ,NoOfSteps);  
      CIntfData::preset(SeqDuration,       0. ,NoOfSteps);  
      CIntfData::preset(SeqStirrInt,       0  ,NoOfSteps);  
      CIntfData::preset(SeqGasFlow,        0. ,NoOfSteps);  
      CIntfData::preset(SeqStirrGasType,   0  ,NoOfSteps);  
      CIntfData::preset(SeqStepPrior,      0  ,NoOfSteps);  

      seqLFStirrPredRes SeqLFStirrPredRes = CIntfData::ToCORBAType(pDM_Interface->getLFStirrPredRes(ProductID.c_str(), DATA::LFStirrPredRes));

      //********    Log event data ***********************************************************************

      //********    Convert and check event data  ***********************************************************

      if ( checkInternalData(TlgName, HeatID, TreatID, Plant, CustHeatID, CustTreatID) )
      {
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        for (long i=0; i < CIntfData::getLength(SeqLFStirrPredRes); i++)
        {
          sLFStirrPredRes LFStirrPredRes;

          CIntfData::getAt(LFStirrPredRes,SeqLFStirrPredRes,i);

          std::string StirrPhase      = LFStirrPredRes.StirrPhase;
          std::string GasType         = LFStirrPredRes.GasType;
          double StirrFlow            = LFStirrPredRes.StirrFlow;
          double DurStep              = LFStirrPredRes.DurStep;
          long Priority               = LFStirrPredRes.Priority;
          long StirrIntensity         = LFStirrPredRes.StirrIntensity;
          long Enable                 = LFStirrPredRes.Enable;
          long Order                  = LFStirrPredRes.Order;
          long isPatternOrActivity    = LFStirrPredRes.isPatternOrActivity;
          long VoltTap                = LFStirrPredRes.VoltTap;
          long ImpCurve               = LFStirrPredRes.ImpCurve;
          long GasTypeNo              = 0;

          long PRACPHASEORDERNO       = 0;

          if (isPatternOrActivity == 1)    //check if this phase is used
          {
            continue;
          }

          //Get the rows from database table by StirrPhase
          if ( StirrPhase != DEF::Inv_String && m_pGCL_STIRR_PHASE->selectByPracPhaseModel(StirrPhase))
          {
            PRACPHASEORDERNO = m_pGCL_STIRR_PHASE->getPRACPHASEORDERNO(1);
            StirrPhase       = m_pGCL_STIRR_PHASE->getPRACPHASE(1); 
          }
          else
          {
            std::string Msg = Function + " wrong or invalid StirrPhase";
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());

            continue;          
          }        

          // setting defaults if invaliud data have been detected
          StirrFlow             = CDataConversion::SetInvalidToDefault(StirrFlow            ,0.);
          DurStep               = CDataConversion::SetInvalidToDefault(DurStep              ,0.);
          Priority              = CDataConversion::SetInvalidToDefault(Priority             ,0);
          StirrIntensity        = CDataConversion::SetInvalidToDefault(StirrIntensity       ,0);
          Enable                = CDataConversion::SetInvalidToDefault(Enable               ,0);
          Order                 = CDataConversion::SetInvalidToDefault(Order                ,0);
          isPatternOrActivity   = CDataConversion::SetInvalidToDefault(isPatternOrActivity  ,0);
          VoltTap               = CDataConversion::SetInvalidToDefault(VoltTap              ,0);
          ImpCurve              = CDataConversion::SetInvalidToDefault(ImpCurve             ,0);


          if (GasType == DEF_GC_STIRR_GAS_TYPE::Ar) 
          {
            GasTypeNo = 1;
          }
          else if (GasType == DEF_GC_STIRR_GAS_TYPE::N2) 
          {
            GasTypeNo = 2;
          }
          else
          {
            std::string Msg = Function + " wrong or invalid GasType";
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Msg.c_str());

            continue; 
          }


          if ( StirrPhase == DEF_GCL_STIRR_PHASE::SlagBreaking )
          {
            StepNo = 0;   // pos 1 in telegram  
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Deoxidation )
          {
            StepNo = 1;    // pos 2 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::InitialHeating )
          {
            StepNo = 2;    // pos 3 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::MainHeating )
          {
            StepNo = 3;    // pos 4 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::FinalHeating )
          {
            StepNo = 4;    // pos 5 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CoolingStirring )
          {
            StepNo = 5;    // pos 7 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SlagForming )
          {
            StepNo = 6;    // pos 8 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::FirstAlloying )
          {
            StepNo = 7;    // pos 8 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SecondAlloying )
          {
            StepNo = 8;    // pos 9 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CoolingMaterial )
          {
            StepNo = 9;    // pos 10 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Trimming )
          {
            StepNo = 10;    // pos 11 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::SoftStirring )
          {
            StepNo = 11;    // pos 12 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CaTreatment )
          {
            StepNo = 12;    // pos 13 in telegram  
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::CleanStirring )
          {
            StepNo = 13;    // pos 14 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::TempHold )
          {
            StepNo = 14;    // pos 15 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Sampling )
          {
            StepNo = 15;    // pos 16 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Desulphurization )
          {
            StepNo = 16;    // pos 17 in telegram 
          }
          else if ( StirrPhase == DEF_GCL_STIRR_PHASE::Intermediate )
          {
            StepNo = 17;    // pos 18 in telegram 
          }

          CIntfData::setAt(SeqPhaseNo       ,PRACPHASEORDERNO ,StepNo);
          CIntfData::setAt(SeqEnabled       ,Enable           ,StepNo);
          CIntfData::setAt(SeqDuration      ,DurStep          ,StepNo);  
          CIntfData::setAt(SeqStirrInt      ,StirrIntensity   ,StepNo); 
          CIntfData::setAt(SeqGasFlow       ,StirrFlow        ,StepNo);
          CIntfData::setAt(SeqStirrGasType  ,GasTypeNo        ,StepNo);
          CIntfData::setAt(SeqStepPrior     ,Priority         ,StepNo);

          //StepNo ++ ;

          if ( i > 17 )
          {
            break;
          }
        } // for (long i=0; i < CIntfData::getLength(SeqLFStirrPredRes); i++)


        //********    Write telegram data  ***********************************************************************
        DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF31_STIRR_PATT::CreateTime,   Now.toDBString());   
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF31_STIRR_PATT::HeatId,       HeatID);   
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF31_STIRR_PATT::TreatId,      TreatID);   

        Telegram_L2LF31_STIRR_PATT::t_ENTRY seqENTRY;

        for(long j = 0; j < NoOfSteps ; j++)
        {
          Telegram_L2LF31_STIRR_PATT::sENTRY ENTRY;
          
          ENTRY.MessageIndex            = j;
          ENTRY.HeatId                  = HeatID.c_str()         ;
          ENTRY.TreatId                 = TreatID.c_str()        ;

          CIntfData::getAt(ENTRY.PhaseNo              ,SeqPhaseNo                 ,j);
          CIntfData::getAt(ENTRY.Enabled              ,SeqEnabled                 ,j);
          CIntfData::getAt(ENTRY.Duration             ,SeqDuration                ,j);
          CIntfData::getAt(ENTRY.StirrInt             ,SeqStirrInt                ,j);
          CIntfData::getAt(ENTRY.StirrGasFlow         ,SeqGasFlow                 ,j);
          CIntfData::getAt(ENTRY.StirrGasType         ,SeqStirrGasType            ,j);
          CIntfData::getAt(ENTRY.StepPriority         ,SeqStepPrior               ,j);
          ENTRY.Spare_1 = 0;
          ENTRY.Spare_2 = 0;

          CIntfData::insert(seqENTRY,ENTRY);
          //********    Dispatch event ****** *****************************************************************
        }

        CORBA::Any seqAny;
        seqAny = CIntfData::ToAny(seqENTRY);

        pTelcom_Interface->setAny   ( DataKeyL1, Telegram_L2LF31_STIRR_PATT::ENTRY       ,     seqAny);

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************

        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);


        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log( TlgName + ": End", 3);

    }
    else
    {
      // EL_
      RetValue=false;
    }

    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}

bool CLF_EventHandler::provideData_L2LF70_MAT_HANDL(CEventMessage& Event)
{
  //=================    M A T E R I A L   H A N D L I N G   ===============================
  bool RetValue = true; // assume success

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string OrderID   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();

  std::string Plant     = m_pGC_Plant_Container->getPlant(PlantID);
  long 				PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string L1PlantID = CDataConversion::LongToString(m_pGC_Plant_Container->getL1PlantID(PlantID));

  // truncate string data to fit telegram length
  OrderID   = CDataConversion::CheckLengthAndTruncate(OrderID,10);

  CDateTime Now;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  "ProductID:";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  "Key:";
  Action +=  Event.getDataKey();

  std::string TlgName  = "L2LF70_MAT_HANDL";
  std::string Function = "CLF_EventHandler::provideData_L2LF70_MAT_HANDL";

  try
  {
    CSMC_DataProvider_Impl* pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

    DM::iDM_Interface_var pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

    if ( pTelcom_Interface && pDM_Interface)
    {
      //********    preset data  ************************************************************************

      TlgName   = "L2LF70_MAT_HANDL";

      log("****************************************************************************************", 3);
      log( TlgName + ": Start: " + HeatID, 3);
      log("****************************************************************************************", 3);

      //********    Read event related data  ************************************************************************

      seqRecipeList RecipeList = CIntfData::ToCORBAType(pDM_Interface->getRecipeList(ProductID.c_str(),DATA::LFMatRecipe));

      log(CIntfData::getContent(CIntfData::ToAny(RecipeList)),4); 

      DEF::seqLong    Seql1Source;
      DEF::seqLong    Seql1RecipeNo;
      DEF::seqString  SeqMatCode;
      DEF::seqLong    SeqMatWeight;
      DEF::seqLong    SeqMatSequence;
      DEF::seqLong    SeqFeedSpeed;

      if ( !HeatID.empty() && HeatID != DEF::Inv_String )
      {
        //********    Convert and check event data  ***********************************************************
        // truncate string data to fit telegram length
        HeatID  = CDataConversion::CheckLengthAndTruncate(HeatID,10);
        TreatID = CDataConversion::CheckLengthAndTruncate(TreatID,2);

        long Spare_1       = 0;
        long Spare_2       = 0;      

        std::string DataKeyL1 = pTelcom_Interface->generateDataKey(TlgName);

        CORBA::Any seqAny;
        long MatCounter       = 0;
        long MatSeqLenght     = 300;

        // preset sequences with empty values
        CIntfData::preset(Seql1Source       ,0              ,MatSeqLenght);
        CIntfData::preset(Seql1RecipeNo     ,0              ,MatSeqLenght);
        CIntfData::preset(SeqMatCode        ,""             ,MatSeqLenght);
        CIntfData::preset(SeqMatWeight      ,0              ,MatSeqLenght);
        CIntfData::preset(SeqMatSequence    ,0              ,MatSeqLenght);
        CIntfData::preset(SeqFeedSpeed      ,0              ,MatSeqLenght);


        for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    
        {
          long l1RecipeNo   = 0;
          long l1BatchNo    = 0;
          long l1Source     = 0;

          // get current Recipe from RecipeList
          sRecipe Recipe;
          CIntfData::getAt(Recipe,RecipeList,ii);

          //Get the recipe name from the table by recipe number and recipe name
          l1RecipeNo = m_pGC_Recipe_L1Container->getL1RecipeNoByL2Name ( Recipe.RecipeNo,std::string(Recipe.RecipeName));

          if ( l1RecipeNo != 0 && l1RecipeNo > 0 )
          {
            // get source from the table by string from L2
            l1Source = m_pGC_SourceContainer->getSourceL1InfoNoByName( std::string(Recipe.RecipeSource) );

            //get the content of current recipe
            seqBatchPrio SeqBatchPrio = Recipe.RecipeContent;
 
            if ( CIntfData::getLength(SeqBatchPrio) != 0 )
            {
              // max no of Materials limited by MatSeqLenght
              for (long jj=0; jj < MatSeqLenght ; jj++)    
              {
                // read batch data from Recipe
                sBatchPrio BatchPrio;

                if ( CIntfData::getAt(BatchPrio,SeqBatchPrio,jj) )
                {
                  long ChargPrio        = BatchPrio.ChargPrio;
                  std::string MatCode   = BatchPrio.BatchData.MatCode;
                  double Mass           = BatchPrio.BatchData.Mass;
                  long MatFeedSpeed     = (long)BatchPrio.BatchData.MatFeedSpeed;

                  MatCode   = CDataConversion::CheckLengthAndTruncate(MatCode,10);

                  CIntfData::setAt(Seql1Source     ,l1Source                          ,MatCounter);
                  CIntfData::setAt(Seql1RecipeNo   ,l1RecipeNo                        ,MatCounter);
                  CIntfData::setAt(SeqMatCode      ,MatCode.c_str()                   ,MatCounter);
                  CIntfData::setAt(SeqMatWeight    ,CDataConversion::RoundToLong(Mass),MatCounter);
                  CIntfData::setAt(SeqMatSequence  ,ChargPrio                         ,MatCounter);
                  CIntfData::setAt(SeqFeedSpeed    ,MatFeedSpeed                      ,MatCounter);

                  MatCounter++;
                }
              } // for (long jj=0; jj < CIntfData::getLength(SeqBatchPrio) ; jj++)    
            } // if ( CIntfData::getLength(SeqBatchPrio) != 0 )
          }  // if ( l1RecipeNo != 0 )

          //********    Write telegram data  ***********************************************************************

          Telegram_L2LF70_MAT_HANDL::t_ENTRY seqENTRY;

          for(long j = 0; j < MatSeqLenght ; j++)
          {
            Telegram_L2LF70_MAT_HANDL::sENTRY ENTRY;
          
            ENTRY.MessageIndex            = j;
            ENTRY.HeatId                  = HeatID.c_str()         ;
            ENTRY.TreatId                 = TreatID.c_str()        ;

            CIntfData::getAt(ENTRY.Source               ,Seql1Source           ,j);
            CIntfData::getAt(ENTRY.RecipeNo             ,Seql1RecipeNo         ,j);
            CIntfData::getAt(ENTRY.MatCode              ,SeqMatCode            ,j);
            CIntfData::getAt(ENTRY.MatWeight            ,SeqMatWeight          ,j);
            CIntfData::getAt(ENTRY.MatSequence          ,SeqMatSequence        ,j);
            CIntfData::getAt(ENTRY.FeedRate             ,SeqFeedSpeed          ,j);
            ENTRY.Spare_1                                 = Spare_1            ;
            ENTRY.Spare_2                                 = Spare_2            ;

            CIntfData::insert(seqENTRY,ENTRY);
            //********    Dispatch event ****** *****************************************************************
          }

          seqAny = CIntfData::ToAny(seqENTRY);

        } // for (long ii=0; ii < CIntfData::getLength(RecipeList); ii++)    

        // *************************************************************************
        // fill one entry to set data in datail table that L1 could reset batch list
        // *************************************************************************
        if ( CIntfData::getLength(RecipeList) == 0 )
        {
          //********    Write telegram data  ***********************************************************************

          Telegram_L2LF70_MAT_HANDL::t_ENTRY seqENTRY;

          for(long j = 0; j < MatSeqLenght ; j++)
          {
            Telegram_L2LF70_MAT_HANDL::sENTRY ENTRY;
          
            ENTRY.MessageIndex            = j;
            ENTRY.HeatId                  = HeatID.c_str();
            ENTRY.TreatId                 = TreatID.c_str();

            ENTRY.Source                  = 0;
            ENTRY.RecipeNo                = 0;
            ENTRY.MatCode                 = "";
            ENTRY.MatWeight               = 0;
            ENTRY.MatSequence             = 0;
            ENTRY.FeedRate                = 0;
            ENTRY.Spare_1                 = Spare_1;
            ENTRY.Spare_2                 = Spare_2;

            CIntfData::insert(seqENTRY,ENTRY);
          }

          seqAny = CIntfData::ToAny(seqENTRY);

        }

        //set the data to telcom interface
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF70_MAT_HANDL::HeatId,          HeatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF70_MAT_HANDL::TreatId,         TreatID);
        pTelcom_Interface->setString   ( DataKeyL1, Telegram_L2LF70_MAT_HANDL::CreateTime,      Now.toDBString());   
        pTelcom_Interface->setAny      ( DataKeyL1, Telegram_L2LF70_MAT_HANDL::ENTRY,           seqAny);

        pTelcom_Interface->showContent(DataKeyL1, 4);

        //********    Dispatch event ***********************************************************************
        //            multiple telegrams send if model results contains more materials than defined in telegram sequence! 
        SendEventMessage(TlgName,DataKeyL1,L1PlantID,HeatID,TreatID,OrderID);

      } // if ( !HeatID.empty() && HeatID != DEF::Inv_String && (CIntfData::getLength(RecipeList) > 0 ) )

      //********    End processing data  ***********************************************************************

      log( TlgName + ": End", 3);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorPointerHandling(sMessage,Function.c_str()," pDM_Interface or pTelcom_Interface invalid ");
      RetValue=false;
    }
    
    if ( !RetValue )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Function.c_str());
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc, Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException(Function, Action, __FILE__, __LINE__);
    RetValue = false;
  }

  return RetValue;
}


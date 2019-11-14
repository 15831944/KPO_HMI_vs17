// Copyright (C) 2006 SMS Demag AG

#include "CHMD_TelegramHandler.h"

#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogHMDController.h"
#include "DEF_GC_SAMPLELOC.h"


CHMD_TelegramHandler::CHMD_TelegramHandler()
{
  try
  {
		cCBS_StdConnection *pConnection = CDH_IN_Task::getInstance()->getStdConnection();
    if(pConnection)
    {
      long PlantNo  = 1;
      std::string plant           = DEF_GC_PLANT_DEF::HMD;
      std::string m_PlantPrefix               = "H";
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , plant);

      m_pGC_Plant_Container         = new CGC_Plant_Container(pConnection,plant);
      // create converter for customer heat and treat ids
      m_pHeatDataConverter        = new CHeatDataConverter(pConnection);
      m_pGC_Plantgroup_Container  = new CGC_Plantgroup_Container(pConnection);
      m_pPP_Heat                  = new CPP_HEAT(pConnection);
      pGT_MAT_PURP                = new CGT_MAT_PURP(pConnection);
      pGC_Source                  = new CGC_SourceContainer(pConnection,plant,PlantNo);
      m_pGC_Recipe_L1             = new CGC_Recipe_L1Container(pConnection,plant);
      m_pGC_Charge_Dest           = new CGC_Charge_Dest_Container (pConnection,plant);
      m_pGC_SampleLoc             = new CGC_SAMPLELOC(pConnection);
			m_pREPORT_MOTOR_ENTRY       = new CREPORT_MOTOR_ENTRY(pConnection);

			m_pPP_HM                    = new CPP_HM(pConnection);
			m_pPD_HOT_METAL             = new CPD_HOT_METAL(pConnection);
			m_pPD_SAMPLE_REF            = new CPD_SAMPLE_REF(pConnection);

    }
    else
      log("ERROR: CHMD_TelegramHandler: No connection from CDH_Task!",3);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CHMD_TelegramHandler","");
    throw;
  }
}

CHMD_TelegramHandler::~CHMD_TelegramHandler()
{
  if (m_pGC_Plant_Container)  {delete m_pGC_Plant_Container;m_pGC_Plant_Container=0;}
  if (m_pHeatDataConverter) {delete m_pHeatDataConverter; m_pHeatDataConverter=0;}
  if (m_pGC_Plantgroup_Container) {delete m_pGC_Plantgroup_Container; m_pGC_Plantgroup_Container=0;}
  if (pGT_MAT_PURP) {delete pGT_MAT_PURP; pGT_MAT_PURP=0;}
  if (m_pPP_Heat) {delete m_pPP_Heat; m_pPP_Heat=0;}
  if (m_pGC_Charge_Dest) {delete m_pGC_Charge_Dest; m_pGC_Charge_Dest=0;}
  if (m_pGC_Recipe_L1) {delete m_pGC_Recipe_L1; m_pGC_Recipe_L1=0;}
  if (m_pGC_SampleLoc) {delete m_pGC_SampleLoc; m_pGC_SampleLoc=0;}

  if (m_pREPORT_MOTOR_ENTRY) {delete m_pREPORT_MOTOR_ENTRY; m_pREPORT_MOTOR_ENTRY=0;}

  if (m_pPP_HM) {delete m_pPP_HM; m_pPP_HM=0;}
  if (m_pPD_HOT_METAL) {delete m_pPD_HOT_METAL; m_pPD_HOT_METAL=0;}
  if (m_pPD_SAMPLE_REF) {delete m_pPD_SAMPLE_REF; m_pPD_SAMPLE_REF=0;}
	
	
}

bool CHMD_TelegramHandler::doOnComplete(const string& Key, const string& TlgName)
{

  bool retval = false;

  if(m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT && 
    m_pTelegram_Adapter->m_pEvent_Task )
  {
    EventMessageVector.clear();
    m_Heat.clear();
    m_Treat.clear();
    m_PlantID.clear();
    OrderID.clear();
    handleTelegram(Key, TlgName);

		std::vector <std::string>::iterator EventMsgToSend;

    for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
    {

      std::string LogMessageString = TlgName + " BSSL HMD handled!";
      log(LogMessageString,3);

      CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
        m_pTelegram_Adapter->m_DestinationName,
        *EventMsgToSend,
        m_PlantID,
        "",
        "",
        false,
        m_Heat,
        "01",//m_Treat sankar always one treatment
        m_DataKey);

      Message.setOrderID(OrderID);
      
      retval = m_EventHandler.dispatchEvent("","",Message);

			//sankar as per JSW requirement
			handleEventLog(*EventMsgToSend,m_Heat,"01",m_PlantID,m_DataKey);
    }
  }
  return retval;
}



void CHMD_TelegramHandler::handleTelegram(const string& Key, const string& TlgName)
{
  std::string CustHeatID;
  std::string CustTreatID;
  long lPlant;              // Plant id from L1

  //Announcement of Heat
  if   (TlgName == "HDL203") // m_Heat Announcement, for testing only !!!!
  {
    log("HDL203: Started",3);
    EventMessageVector.clear();
    EventMessageVector.push_back(HMD_EvMsg::evHMDHeatAnnouncement);

    m_DataKey   = generateDataKey("");
    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL203::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

      //********    reset statushandler for plant *******************************************************************************
      m_StatusHandler.removeID( m_PlantID ); //sankar

		CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL203::HeatNo);
    //CustTreatID  = m_PlantPrefix + m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL203::TreatId);        
		CustTreatID="01";
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat,  m_pGC_Plant_Container->getPlant(m_PlantID));
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;
    if(m_pPP_Heat->select(CustHeatID))
    {
      OrderID = m_pPP_Heat->getPRODORDERID(1);
    }

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL203::CreateTime);

    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());
    //Ladle ID: Get and put
    std::string LadleTransferCarId = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL203::TransferCar);
    m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::LadleTransferCarId, LadleTransferCarId.c_str());
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL203::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
		m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey.c_str(),1);
  }
  //Start of Heat
  else if(TlgName=="HDL204")
  {
    log("HDL204: Started",3);

    EventMessageVector.push_back(HMD_EvMsg::evHMDHeatStart);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL204::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL204::HeatNo);
    //CustTreatID  = m_PlantPrefix + m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL204::TreatId);        
    // get internal representation of heat and treat ids

	long custLength = CustHeatID.length();
    int ii;
    for (ii = 1; ii <= custLength; ii++)
    {
      char heatNoWrod = CustHeatID[ii-1];
      if (heatNoWrod == ' ')
        break;
    }
	CustHeatID   = CustHeatID.substr (0, ii-1);


    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat,   m_pGC_Plant_Container->getPlant(m_PlantID));
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL204::CreateTime);

    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    //Ladle ID: Get and put
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL204::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey.c_str(),1);

		DoAutoHeatScheduleCreation(CustHeatID); //SARS
  }
  //End of Heat/LDL Departure
  else if(TlgName=="HDL205")
  {
    log ("HDL205: Started",3);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL205::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL205::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL205::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat, m_pGC_Plant_Container->getPlant(m_PlantID));
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL205::CreateTime);

    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    //Ladle ID: Get and put
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL205::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

    long    actionFlag  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL205::ActionFlag);
    if (actionFlag == 1)
      EventMessageVector.push_back(HMD_EvMsg::evHMDHeatEnd);
    else if (actionFlag == 2)
    {
      EventMessageVector.push_back(HMD_EvMsg::evHMDHeatDeparture);
      // delete all status
     m_StatusHandler.removeID( m_PlantID ); //sankar
    }
    else
      log ("WARNING: HMD205: Invalid Action neither 1 nor 2",3);

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);

  }
  //Heat Cancelled
  else if(TlgName=="HDL206")
  {
    log ("HDL206: Started",3);

    EventMessageVector.push_back(HMD_EvMsg::evHMDHeatCancellation);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL206::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL206::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL206::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat, m_pGC_Plant_Container->getPlant(m_PlantID)); 

		m_Heat = CustHeatID;
		m_Treat=CustTreatID;
    //m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(),DATA::PlantID,m_PlantID.c_str());
    //Masked by Liu Yang because the PlantID should not appear on the interface


    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL206::CreateTime);
    
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //Sample Taken
  else if(TlgName=="HDL209")
  {
    log ("HDL209: Started",3);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL209::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL209::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL209::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat, m_pGC_Plant_Container->getPlant(m_PlantID));
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;

    if (m_pGC_SampleLoc->selectSampleLoc(m_pGC_Plant_Container->getPlant(m_PlantID)))
    {
      m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::SampleLocation, m_pGC_SampleLoc->getSAMPLELOC(1));
    }

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL209::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    //Ladle ID: Get and put
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL209::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;

    std::string sSampleCode = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL209::SampleCode);
    m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(),DATA::SampleCode,sSampleCode);

    long    lsampleNo  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL209::SampleNo);
    m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::SampleNo,lsampleNo);

    long actionFlag  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL209::ActionFlag);
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());
		std::string SampleLocation = DEF_GC_SAMPLELOC::HMD;
		m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::SampleLocation,SampleLocation.c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setLong (m_DataKey.c_str(), DATA::LadleNo, ldlId);

    if (actionFlag == 1)
    {
      EventMessageVector.push_back(HMD_EvMsg::evHMDHotMetalSampleTaken);
			m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::SampleType, DEF_GC_MEASUREMENT_TYPE::HM);
      m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::HMSampleTime,temptemp.assDate());
    }
    else if   (actionFlag == 2)
    {
      EventMessageVector.push_back(HMD_EvMsg::evHMDSlagSampleTaken);
      m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::SampleType, DEF_GC_MEASUREMENT_TYPE::Slag);
      m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::SlagSampleTime, temptemp.assDate());
    }
    else  
    {
      log("WARNING:Event : Unrecognizable probe type received!",3);
    }

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //Temp is taken
  else if(TlgName=="HDL211")
  {
    log ("HDL211: Started",3);

    EventMessageVector.push_back(HMD_EvMsg::evHMDTempMeasurement);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL211::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL211::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL211::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat,m_pGC_Plant_Container->getPlant(m_PlantID));
		
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL211::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::TempMeasTime,temptemp.assDate());

    //Set SampleLocation...
    if (m_pGC_SampleLoc->selectSampleLoc(m_pGC_Plant_Container->getPlant(m_PlantID)))
    {
      m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::SampleLocation, m_pGC_SampleLoc->getSAMPLELOC(1));
    }
    //Ladle ID: Get and put
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL211::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

    double Temp   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL211::TempVal);  
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(),DATA::MeasTemp,Temp);
		m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(),DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Temp);

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //Update Aim Departure Time
  else if(TlgName=="HDL213")
  {
  //  log ("HDL213: Started",3);

  //  EventMessageVector.push_back(HMD_EvMsg::evHMDUpdateAimDepartureTime);
  //  m_DataKey   = generateDataKey("");

  //  lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL213::UnitNo);
  //  m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

  //  CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL213::HeatNo);
  //  CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL213::TreatId);        
  //  // get internal representation of heat and treat ids
  //  m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat, 
  //    m_pGC_Plant_Container->getPlant(m_PlantID));
		//
		//m_Heat = CustHeatID;
		//m_Treat=CustTreatID;

  //  m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(),DATA::PlantID,m_PlantID.c_str());

  //  CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL213::CreateTime);
  //  CDateTime temptemp(DateTime);
  //  m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

  //  CORBA::Any depAimtime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL213::DepAimDate);
  //  CDateTime DepAimtime(depAimtime);

  //  long ActionFlag = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL213::ActionFlag);
  //  // AimSulphur should be in percentage(double) in L2.
  //  // Level 1 sends in ppm(long)
  //  double AimSulphur = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL213::AimSulphurCont);
  //  AimSulphur = AimSulphur / 10000.0; // convert from ppm to percent

  //  if (ActionFlag == 2)
  //  {
  //    EventMessageVector.push_back(HMD_EvMsg::evHMDChangeAimData);      
  //    //m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::RecipeContent, AimSulphur);
  //    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::RecipeContent, AimSulphur);
  //  }
  //  else if (ActionFlag == 3)
  //  {
  //    EventMessageVector.push_back(HMD_EvMsg::evHMDUpdateAimDepartureTime);
  //    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(), DATA::TreatEndAim, DepAimtime.assDate());
  //  }

  //  m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //HMD Operation Modes
  else if(TlgName=="HDL220")
  {
    log ("HDL220: Started",3);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL220::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL220::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL220::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat,  m_pGC_Plant_Container->getPlant(m_PlantID));

    m_Heat = CustHeatID;
		m_Treat= CustTreatID; 

	
    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL220::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    long lL1Mode;             //temporary variable for comp. modes
    seqComputerModes seqCompModes; // the Sequence, stores data for MatHandle mode
    sComputerMode SComputerMode; // the Structure

    //material handle only
    SComputerMode.Device = DEF_COMP_MODES::MatHandle;
    lL1Mode = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key.c_str(), Telegram_HDL220::Mode);

    if (lL1Mode == 1)
    {
		//sankar
      //if (m_StatusHandler.isStatusChanged(m_PlantID, std::string(DEF_COMP_MODES::MatHandle), DEF_GEN_STATES::On))
      //{
        SComputerMode.Status = DEF_GEN_STATES::On;
        CIntfData::insert(seqCompModes, SComputerMode);
        EventMessageVector.push_back(HMD_EvMsg::evHMDSetComputerModeOn);
      //}
      m_pTelegram_Adapter->m_pIntf_OUT->setComputerModes(m_DataKey.c_str(), DATA::ComputerModes, seqCompModes);
    }
    else if (lL1Mode == 2)
    {
		//sankar
      //if (m_StatusHandler.isStatusChanged(m_PlantID, std::string(DEF_COMP_MODES::MatHandle), DEF_GEN_STATES::Off))
      //{
        SComputerMode.Status = DEF_GEN_STATES::Off;
        CIntfData::insert(seqCompModes, SComputerMode);
        EventMessageVector.push_back(HMD_EvMsg::evHMDSetComputerModeOff);
      //}
      m_pTelegram_Adapter->m_pIntf_OUT->setComputerModes(m_DataKey.c_str(), DATA::ComputerModes, seqCompModes);
    }
    else
      log("ERROR: Telegram_HDL220: Unrecognized Mode received!",1);

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //Plant Status
  else if(TlgName=="HDL221")
  {
    log ("HDL221: Started",3);
    EventMessageVector.push_back( HMD_EvMsg::evHMDPlantStatus);
    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL221::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL211::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    long  HoodPos = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL221::HoodPos);
    if(HoodPos==2)//Park position=2
      m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::HoodPos,DEF_GEN_STATES::OutOfOperationPosition );
    else  //Treatment position=1
      m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::HoodPos,DEF_GEN_STATES::OperationPosition );

    long  TiltingFramePos = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL221::TiltingFramePos);
    m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::TiltingFramePos,TiltingFramePos );

    long  InjLancePos = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL221::InjLancePos);
    if(InjLancePos==1)//Park position=1
      m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::LancePos,DEF_GEN_STATES::OutOfOperationPosition );
    else  //Treatment position=2
      m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::LancePos,DEF_GEN_STATES::OperationPosition );

    long  InjLanceNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL221::InjLanceNo);
    m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::LanceId,InjLanceNo );


    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //HMD Actual Values
  else if(TlgName=="HDL223")
  {
    log ("HDL223: Started",3);

    EventMessageVector.push_back(HMD_EvMsg::evHMDCyclicMeasurement);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL223::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CORBA::Any DateTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL223::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    long  lancePos = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::LancePos);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::LancePos, lancePos ); //sankar

    long blowingMode     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlowingMode);
	blowingMode -= 1;
    m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::HMDBlowType, blowingMode);

    long blowRateMg     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlowRateMg);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::HMDBlowingRateMg, blowRateMg);

    long blowRateLime     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlowRateLime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::HMDBlowingRateLime, blowRateLime);

    long blowRateCarbide     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlowRateCarbide);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::HMDBlowingRateCarbide, blowRateCarbide);

    long blowMg     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlownMg);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::MagnAmount, blowMg);

    long blowLime     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlownLime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::LimeAmount, blowLime);

    long blowCarbide     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::BlownCarbide);
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::CarbAmount, blowCarbide);

	long deslaggingStat     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::DeslaggingStat);
	m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::DeslaggingStatus, deslaggingStat);

	long PowderInjGasFlowRate_N2     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::PowderInjGasFlowRate_N2);
	m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::PowderFlow, PowderInjGasFlowRate_N2);

	long PowderInjGasPressure_N2     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::PowderInjGasPressure_N2);
	m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::N2Press, PowderInjGasPressure_N2);

	long TotalCoolingWaterConsumed     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::TotalCoolingWaterConsumed);
	m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::CoolingWaterData, TotalCoolingWaterConsumed);//sankar

	//sankar
	long TotalNconsumed     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL223::TotalNConsumed);
  m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::PowderConsumption, TotalNconsumed);

	m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);
  }
  //Blowing Report
  else if(TlgName=="HDL260")
  {
    log("\nHDL260: Started",3);

    m_DataKey = generateDataKey("HDL260");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL260::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL260::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL260::TreatId);        
    // get internal representation of heat and treat ids
    //m_pHeatDataConverter->getInternalHeatData(CustHeatID, CustTreatID, m_Heat, m_Treat,m_pGC_Plant_Container->getPlant(m_PlantID));
		
		m_Heat = CustHeatID;
		m_Treat=CustTreatID;
    CORBA::Any DateTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL260::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    //get the UNITGROUPNUMBER from GC_PLANTGROUP to get the MATCODE
    long UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(m_pGC_Plant_Container->getPlant(m_PlantID));
    std::string LimeCode = pGT_MAT_PURP->getRelatedMatCode( UnitGroupNo,DEF_GT_PURP::Lime);
    if (LimeCode == CSMC_DBData::unspecString)
    {
      log ("ERROR no MAT_CODE for Lime was found!",1);
    }
    std::string MgCode =  pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP::Magnesium );
    if (MgCode == CSMC_DBData::unspecString)
    {
      log ("ERROR no MAT_CODE for Magnesium was found!",1);
    }
    std::string CarbCode =  pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP::Carbide);
    if (CarbCode == CSMC_DBData::unspecString)
    {
      log ("ERROR no MAT_CODE for Carbide was found!",1);
    }
    
    // get L2 RecipeName from DB depends on L1 number
    long l1RecNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL260::ReceipeName);
    std::string L2RecipeName = m_pGC_Recipe_L1->getL2RecipeNameByL1No(l1RecNo);
    if (!L2RecipeName.empty())
      m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::RecipeName, L2RecipeName.c_str());
    else
    {
      std::stringstream mes("WARNING:Event HDL260: Cannot get L2 RecipeName. L1RecipeNo '");
      mes << l1RecNo << "' not found in data base";
      log(mes.str(),3);
    }

    long L2RecipeNo = m_pGC_Recipe_L1->getL2RecipeNoByL1No(l1RecNo);
    if( L2RecipeNo > -1)
      m_pTelegram_Adapter->m_pIntf_OUT->setLong (m_DataKey.c_str(), DATA::RecipeNo, L2RecipeNo);
    else
    {
      std::stringstream mes("WARNING:Event HDL260: Cannot get L2 RecipeNo. L1RecipeNo '");
      mes << l1RecNo << "' not found in data base";
      log(mes.str(),3);
    }

    // get L2 RecipeSource from DB depends on L1 source number.
    long L1RecipeSource = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key.c_str(), Telegram_HDL260::Source);
    std::string L2RecipeSource = pGC_Source->getL2SourceNameByL1No(L1RecipeSource);
    if (!L2RecipeSource.empty())
      m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::RecipeSource, L2RecipeSource.c_str());
    else
    {
      std::stringstream mes("WARNING:Event HDL260: Cannot get L2 RecipeSource. L1SourceNo '");
      mes << L1RecipeSource << "' not found in data base";
      log(mes.str(),3);
    }

    // get L2 RecipeTarget from DB depends on L1 target number.
    long L1RecipeTarget = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL260::Target);
    std::string L2RecipeTarget = m_pGC_Charge_Dest->getDestNameByNo(L1RecipeTarget);
    if (!L2RecipeTarget.empty())
      m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::RecipeTarget, L2RecipeTarget.c_str());
    else
    {
      std::stringstream mes("WARNING:Event HDL260: Cannot get L2 RecipeTarget. L1TargetNo '");
      mes << L1RecipeTarget << "' not found in data base";
      log(mes.str(),3);
    }
    
    long MatFeedRate = 0;
    MatFeedRate = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key.c_str(),Telegram_HDL260::FeedingRate);

    //get Materials  sankar
    CORBA::Any MaterialsAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL260::MatCode);
    DEF::seqString *longMaterialsSeq;

		CORBA::Any MaterialsWgtAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL260::MatWeight);
    DEF::seqLong *longMaterialsWgtSeq;
		

    if (((MaterialsAny) >>= longMaterialsSeq) && ((MaterialsWgtAny) >>= longMaterialsWgtSeq) )
    {
      long MatLength = longMaterialsSeq->length();

      // construct the recipe from the received Sequences and stuff it to OUT
      for (long idx=0; idx < MatLength; idx ++ ) 
      {
        //std::stringstream tempStr;
        //std::string strMatCode;
        ////0,2,4... MatCode
        ////1,3,5... MatWgt
        //tempStr << (*longMaterialsSeq)[idx];
        //tempStr >> strMatCode;
        //double lMatWgt  = (*longMaterialsSeq)[idx+1];

        std::stringstream tempStr;
        std::string strMatCode;
				long lMatWgt;
				tempStr << (*longMaterialsSeq)[idx];
        tempStr >> strMatCode;
				tempStr.clear();
        tempStr << (*longMaterialsWgtSeq)[idx];
				tempStr >> lMatWgt;

        if(strMatCode == MgCode)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::MagnAmount, lMatWgt);
        }
        else if(strMatCode == LimeCode)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::LimeAmount, lMatWgt);
        }
        else if(strMatCode == CarbCode)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDouble(m_DataKey.c_str(), DATA::CarbAmount, lMatWgt);
        }
      }
    }

    long    blowStat  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL260::BlowStat);
    if ( 2 == blowStat )
    {
      EventMessageVector.push_back(HMD_EvMsg::evHMDPowderBlowingStart);  
			
    }
    else if ( 3 == blowStat )
    {
      EventMessageVector.push_back(HMD_EvMsg::evHMDPowderBlowingEnd);
    }
    else
      log("WARNING:Event HDL260: Unrecognizable BlowStat received!",3);

      m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,2);
  }
	  
  //Material Availbilities for Powder
  else if(TlgName=="HDL261")
  {
    log ("HDL261: Started",3);

    EventMessageVector.push_back(HMD_EvMsg::evHMDMaterialAvailability);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL261::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CORBA::Any  DateTime       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL261::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    long ActionFlag     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL261::ActionFlag);
    if(0==ActionFlag)
      m_pTelegram_Adapter->m_pIntf_OUT->setBoolean(m_DataKey.c_str(),DATA::AllMaterials,true);
    if(1==ActionFlag)
      m_pTelegram_Adapter->m_pIntf_OUT->setBoolean(m_DataKey.c_str(),DATA::AllMaterials,false);

    DEF::seqLong *sMat ;
    CORBA::Any  anyAvailMat    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL261::MatCode);

    anyAvailMat >>= sMat;

    seqMaterials seqMat;
    sMaterial theMaterial;
    for(int i=0;i<20;i++)
    {
      long ltemp = (*sMat)[i*2];
      if(ltemp == 0)
      {
        continue;
      }
      theMaterial.MatCode = CDataConversion::LongToString(ltemp).c_str();
      theMaterial.MatWeight = (*sMat)[i*2+1];
      CIntfData::insert(seqMat,theMaterial); 
    }

    m_pTelegram_Adapter->m_pIntf_OUT->setMaterials(m_DataKey.c_str(),DATA::MatAvailable,seqMat);

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,1);

  }
  //Liquid Material Handling Report
  else if(TlgName=="HDL270")
  {
    EventMessageVector.push_back(HMD_EvMsg::evHMDLiqMatHandlReport);

    m_DataKey   = generateDataKey("");

    lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL270::UnitNo);
    m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

    CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL270::HeatNo);
    CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL270::TreatId);    

		m_Heat = CustHeatID;
		m_Treat=CustTreatID;

    m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(),DATA::PlantID,m_PlantID.c_str());

    CORBA::Any  DateTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL270::CreateTime);
    CDateTime temptemp(DateTime);
    m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

    //Ladle ID: Get and put
    long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL270::LdlId);
    std::stringstream ladleNo;
    ladleNo << ldlId;
    std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
		m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
    m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

    //01-10:Spare
    //  11:LadleGrossWgtBeforeHMD
    //  12:LadleGrossWgtAfterHMD
    //  13:Gross weight update at HMD
    //  14:LadleGrossWeighBeforeCharging (ConArc)
    //  15:LadleGrossWeighAfterCharging(ConArc)
    //  16:Spare
    //  17:Spare
    //  18:Spare
    //  19::Spare
    //  20:Spare
    long WgtStat = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL270::WgtStat);
    long WgtType = CSMC_DBData::unspecLong; //sankar
    // Can not find exact items of DEF_LIQ_MAT_REPORT in iSMC_DataDefinitions.idl.
    // Following should be changed when find exact definitions.
    switch(WgtStat)
    {
    case 11:
      WgtType = DEF_LIQ_MAT_REPORT::HMLadleGrossWeightBeforeDesul;
      break ;
    case 12:
      WgtType = DEF_LIQ_MAT_REPORT::HMLadleGrossWeightAfterDesul;
      break ;
    case 13:
      WgtType = DEF_LIQ_MAT_REPORT::LadleGrossWeightUpdateAtDesul;
      break ;
    case 14:
      WgtType = DEF_LIQ_MAT_REPORT::HMLadleGrossWeightBeforeConArcCharge;
      break ;
    case 15:
      WgtType = DEF_LIQ_MAT_REPORT::HMLadleGrossWeightAfterConArcCharge;
      break ;
    default:
      log("ERROR: Undefined weighing type received in HDL270!",1);
    } 
    m_pTelegram_Adapter->m_pIntf_OUT->setLong(m_DataKey.c_str(), DATA::WeighingType,WgtType);


    long SteelWgt = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL270::SteelWgt);
    SteelWgt = SteelWgt*1000; // make kg
    m_pTelegram_Adapter->m_pIntf_OUT->setDouble (m_DataKey.c_str(), DATA::MeasWeight, (double)SteelWgt);

    m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,2);

  }
  //Treatment Steps
  else if(TlgName=="HDL281")
  {
	  m_DataKey   = generateDataKey("");

	  lPlant = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL281::UnitNo);
	  m_PlantID = m_pGC_Plant_Container->getL2PlantID(lPlant);

	  CustHeatID   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL281::HeatNo);
	  CustTreatID  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key.c_str(),Telegram_HDL281::TreatId);        

	  m_Heat  = CustHeatID;
	  m_Treat = CustTreatID;
	  m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(),DATA::PlantID,m_PlantID.c_str());

	  CORBA::Any  DateTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL281::CreateTime);
	  CDateTime temptemp(DateTime);
	  m_pTelegram_Adapter->m_pIntf_OUT->setDate(m_DataKey.c_str(),DATA::DateTime,temptemp.assDate());

	  //Ladle ID: Get and put
	  long    ldlId  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL281::LdlId);
	  std::stringstream ladleNo;
	  ladleNo << ldlId;
	  std::string ladleType = DEF_GC_LADLE_TYPE::HotMetalLadle;
	  m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleNo, ladleNo.str().c_str());
	  m_pTelegram_Adapter->m_pIntf_OUT->setString (m_DataKey.c_str(), DATA::LadleType, ladleType.c_str());

	  //TrStep
	  //Read the information about the actual Step of treatment
	  long TrStep = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL281::TrStep);
	  std::string ActPhase;

	  //evHMDPhasePreparation in case of TrStep = 1 or
	  //  evHMDPhaseMonoInjectionLimeStart in case of TrStep = 2 or
	  //  evHMDPhaseMonoInjectionCarbideStart in case of TrStep = 3 or
	  //  evHMDPhaseMonoInjectionContinued in case of TrStep = 4 or
	  //  evHMDPhaseMonoInjectionCarbideEnd in case of TrStep = 5 or
	  //  evHMDPhaseMonoInjectionLimeEnd in case of TrStep = 6 or
	  //  evHMDPhaseDeslagging in case of TrStep = 7
	  /* Need according message and variables */


	  switch( TrStep )    //Add the according message
	  {
	  case 1:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhasePreparation);
		  ActPhase = DEF_HMD_PHASES::Preparation;
		  break;
	  case 2:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart);
		  ActPhase = DEF_HMD_PHASES::StartMonoLime;
		  break;
	  case 3:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart);
		  ActPhase = DEF_HMD_PHASES::StartMonoCarb;
		  break;
	  case 4:
		  EventMessageVector.push_back( HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumStart);
		  ActPhase = DEF_HMD_PHASES::StartCoMg;
		  break;
	  case 5:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd);
		  ActPhase = DEF_HMD_PHASES::EndCarbide;
		  break;
	  case 6:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd);
		  ActPhase = DEF_HMD_PHASES::EndLime;
		  break;
	  case 7:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseDeslagging);
		  ActPhase = DEF_HMD_PHASES::Deslagging;
		  break;

	  /*case 5:
		  EventMessageVector.push_back( HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumEnd);
		  ActPhase = DEF_HMD_PHASES::EndCoMg;
		  break;
	  case 6:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd);
		  ActPhase = DEF_HMD_PHASES::EndCarbide;
		  break;
	  case 7:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd);
		  ActPhase = DEF_HMD_PHASES::EndLime;
		  break;
	  case 8:
		  EventMessageVector.push_back(HMD_EvMsg::evHMDPhaseDeslagging);
		  ActPhase = DEF_HMD_PHASES::Deslagging;
		  break;*/

	  default:
		  log("ERROR: HDL281: Unrecognized treatment step recived!",1);
	  }

	  m_pTelegram_Adapter->m_pIntf_OUT->setString(m_DataKey.c_str(), DATA::PhaseAct, ActPhase);
	  m_pTelegram_Adapter->m_pIntf_OUT->showContent(m_DataKey,2);
  }
	//motor maintenance as per JSW requirement
	else if(TlgName == "HDL290")
	{
		const long BoosterFan_ID   = 1;
		const long InjectionLance_ID   = 2;
		const long SampleLance_ID   = 3;
		const long SlagBreaker_ID   = 4;
		const long HydTiltPresPump_ID   = 5;
		const long HydTiltEmrPump_ID   = 6;
		const long HydTiltAirBlast_ID   = 7;
		const long LTC_ID_1   = 8;
		const long LTC_ID_2   = 9;
		const long MGSiloFilter_ID   = 10;

	  long UnitNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_HDL290::UnitNo);
	  m_PlantID = m_pGC_Plant_Container->getL2PlantID(UnitNo);
    long PlantNo = m_pGC_Plant_Container->getPlantNo(m_PlantID);

		long    BoosterFan  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::BoosterFan);
		long    InjectionLance  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::InjectionLance);
		long    SampleLance  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::SampleLance);
		long    SlagBreaker  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::SlagBreaker);
		long    HydTiltPresPump  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::HydTiltPresPump);
		long    HydTiltEmrPump  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::HydTiltEmrPump);

		long    HydTiltAirBlast  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::HydTiltAirBlast);
		CORBA::Any    LTC  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_HDL290::LTC);
		long    MGSiloFilter  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_HDL290::MGSiloFilter);

		bool RetValue = true;

		RetValue = RetValue && updateMotorData(BoosterFan_ID,PlantNo, BoosterFan);
		RetValue = RetValue && updateMotorData(InjectionLance_ID,PlantNo, InjectionLance);
		RetValue = RetValue && updateMotorData(SampleLance_ID,PlantNo, SampleLance);
		RetValue = RetValue && updateMotorData(SlagBreaker_ID,PlantNo, SlagBreaker);
		RetValue = RetValue && updateMotorData(HydTiltPresPump_ID,PlantNo, HydTiltPresPump);
		RetValue = RetValue && updateMotorData(HydTiltEmrPump_ID,PlantNo, HydTiltEmrPump);
		RetValue = RetValue && updateMotorData(HydTiltAirBlast_ID,PlantNo, HydTiltAirBlast);
		
		RetValue = RetValue && updateMotorData(MGSiloFilter_ID,PlantNo, MGSiloFilter);

		DEF::seqLong *longLTCSeq;
		if( LTC >>= longLTCSeq)
		{
			long Length = longLTCSeq->length();
			 for (long idx=0; idx < Length; idx ++ ) 
			 {
				 std::stringstream tempStr;
				 long condition;
				 tempStr << (*longLTCSeq)[idx];
				 tempStr >> condition;

				 if(idx == 0)
					RetValue = RetValue && updateMotorData(LTC_ID_1,PlantNo, condition);
				 if(idx == 1)
					RetValue = RetValue && updateMotorData(LTC_ID_2,PlantNo, condition);
			 }
		}

		if (RetValue)
			CDH_IN_Task::getInstance()->getStdConnection()->commit();
		else
			CDH_IN_Task::getInstance()->getStdConnection()->rollback();
		
	}

}

bool CHMD_TelegramHandler::updateMotorData(long MotorID,long PlantNo, long MotorStrart)
{
	  std::string Function = "CHMD_TelegramHandler::updateMotorData";
		std::string TlgName = "HDL290";
		cCBS_ODBC_DBError lastError;

		CDateTime Now;
		bool RetValue = true;
		try
		{
			if(m_pREPORT_MOTOR_ENTRY->selectByMOTORID(MotorID,PlantNo))
			{
				CDateTime startTime = m_pREPORT_MOTOR_ENTRY->getSTART_TIME(1);
				CDateTime stopTime = m_pREPORT_MOTOR_ENTRY->getSTOP_TIME(1);

				if(MotorStrart == 1 && stopTime != CSMC_DBData::unspecDate)
				{
					m_pREPORT_MOTOR_ENTRY->setMOTORID(MotorID);
					m_pREPORT_MOTOR_ENTRY->setSTART_TIME(Now);
					m_pREPORT_MOTOR_ENTRY->setPLANT_NO(PlantNo);

					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->insert();
				}
				else if(MotorStrart == 0 && stopTime == CSMC_DBData::unspecDate)
				{
					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->updateOrInsert(MotorID,startTime,PlantNo,Now,false,lastError);
				}
			}
			else
			{
				if(MotorStrart == 1)
				{
					m_pREPORT_MOTOR_ENTRY->setMOTORID(MotorID);
					m_pREPORT_MOTOR_ENTRY->setSTART_TIME(Now);
					m_pREPORT_MOTOR_ENTRY->setPLANT_NO(PlantNo);

					RetValue = RetValue && m_pREPORT_MOTOR_ENTRY->insert();
				}
			}
		}
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
			RetValue = false;
    }
    catch(CORBA::SystemException& sExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str());
      RetValue = false;
    }

	return RetValue;
}

void CHMD_TelegramHandler::handleEventLog(const string& message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey)
{
  CDateTime now;

  CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  
  if ( message == HMD_EvMsg::evHMDDeslaggingStart )
  {
    pEventLog->EL_DeslaggingStart(sMessage,now.asString().c_str(),"");
  }
  else if ( message == HMD_EvMsg::evHMDDeslaggingEnd )
  {
    pEventLog->EL_DeslaggingEnd(sMessage, now.asString().c_str() );
  }
  else if ( message == HMD_EvMsg::evHMDTempMeasurement )
  {
    pEventLog->EL_TempMeasurement(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasTemp));
  }
  else if ( message == HMD_EvMsg::evHMDPowderBlowingStart)
  {
    pEventLog->EL_InjectionLanceBlowingStart(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDPowderBlowingEnd )
  {
    pEventLog->EL_InjectionLanceBlowingStop(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDSetComputerModeOn )
  {
    pEventLog->EL_ComputerModeOn(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDSetComputerModeOff )
  {
    pEventLog->EL_ComputerModeOff(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDApplicationSystemRestart )
  {
    pEventLog->EL_ApplicationSystemRestart(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDChangeAimData )
  {
    pEventLog->EL_ChangeAimData(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDHotMetalSampleTaken )
  {
    pEventLog->EL_HotMetalSampleTaken(sMessage,"",-1,"HMD" );
  }
  else if ( message == HMD_EvMsg::evHMDSlagSampleTaken )
  {
    pEventLog->EL_SlagSampleTaken(sMessage,"",-1,"HMD" );
  }
  else if ( message == HMD_EvMsg::evHMDUpdateAimDepartureTime )
  {
    pEventLog->EL_ChangeAimDepartureTime(sMessage, now.asString().c_str());
  }
  else if ( message == HMD_EvMsg::evHMDCreateTreatmentID )
  {
    pEventLog->EL_CreateTreatmentID(sMessage );
  }
  else if ( message == HMD_EvMsg::evHMDDelayStatus )
  {
    CDateTime DelayStartTime, DelayEndTime;
    DelayStartTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::DelayStartDate);
    DelayEndTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::DelayEndDate);
    pEventLog->EL_DelayStatus(sMessage,
    m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayPlant).c_str(),
    m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayCode).c_str(),
    DelayStartTime.asString().c_str(),
    DelayEndTime.asString().c_str(),
    m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayDescription).c_str()  );
  }
  else if ( message == HMD_EvMsg::evHMDHeatAnnouncement )
  {
    pEventLog->EL_HeatAnnouncement(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str(),
		m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleNo).c_str());
  }
  else if ( message == HMD_EvMsg::evHMDHeatAnnouncementOffline )
  {
    pEventLog->EL_HeatAnnouncementOffline(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str(), 
		m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleNo).c_str());
  }
  else if ( message == HMD_EvMsg::evHMDHeatCancellation )
  {
    pEventLog->EL_HeatCancellation(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str() );
  }
  else if ( message == HMD_EvMsg::evHMDHeatEnd )
  {
    pEventLog->EL_HeatEnd(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str() );
  }
  else if ( message == HMD_EvMsg::evHMDHeatDeparture )
  {
    pEventLog->EL_HeatDeparture(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str() );
  }
  else if ( message == HMD_EvMsg::evHMDHeatStart )
  {
    pEventLog->EL_HeatStart(sMessage, HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
  }
  else if ( message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd )
  {
    pEventLog->EL_PhaseMonoInjectionCarbideEnd(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart )
  {
    pEventLog->EL_PhaseMonoInjectionCarbideStart(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDPhaseMonoInjectionContinued )
  {
    pEventLog->EL_PhaseMonoInjectionContinued(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd )
  {
    pEventLog->EL_PhaseMonoInjectionLimeEnd(sMessage);
  }
	else if ( message == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumStart )
  {
    pEventLog->EL_PhaseCoInjectionMagnesiumStart(sMessage);
  }
	else if ( message == HMD_EvMsg::evHMDPhaseCoInjectionMagnesiumEnd )
  {
    pEventLog->EL_PhaseCoInjectionMagnesiumEnd(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart )
  {
    pEventLog->EL_PhaseMonoInjectionLimeStart(sMessage);
  }
  else if ( message == HMD_EvMsg::evHMDCyclicMeasurement ) 
  {
    //pEventLog->EL_CyclicMeasurement(sMessage); //sankar cyclic message should not be logged
  }	
  else if ( message == HMD_EvMsg::evHMDPhaseDeslagging ) 
  {
    pEventLog->EL_DeslaggingStart(sMessage,now.asString().c_str(),""); 
  }	
  else if ( message == HMD_EvMsg::evHMDMaterialAvailability || message == HMD_EvMsg::evHMDPlantStatus || message == HMD_EvMsg::evHMDLiqMatHandlReport || message == HMD_EvMsg::evHMDPhasePreparation )
  {
    // no log function is there
  }		
	else
	{
		//
	}


}

bool CHMD_TelegramHandler::DoAutoHeatScheduleCreation( const std::string& HM_ID)
{
		 //SARS: only JSW specific
	  std::string Function = "CHMD_TelegramHandler::DoAutoHeatScheduleCreation";
		std::string TlgName = "AutoHeatSchedule";
		cCBS_ODBC_DBError lastError;
		string HeatID = CSMC_DBData::unspecString;
		string TreatID = "01";
		std::string MAX_HM_ID = ""; 
		std::string NEXT_HM_ID = ""; 
		long nextSampleRef,nextHMCounter,HMCounter,PlantNo;
		std::string NewOrderID = CSMC_DBData::unspecString;

		CDateTime Now;
		bool RetValue = true;
		try
		{
			CDateTime Now;
			CDateTime StartTime;
			CDateTime EndTime;
			if(m_pPP_HM->select(HM_ID))
			{
				HMCounter = m_pPP_HM ->getHOTMETAL_COUNTER(1);
				PlantNo   = m_pPP_HM ->getPLANTNO(1);
			}
			if(m_pPP_HM->getMaxHMID(MAX_HM_ID,lastError))
			{
				if(m_pPP_HM->select(MAX_HM_ID))
				{
					std::string OrderID = m_pPP_HM->getPRODORDERID(1);
					long temp_convert = CDataConversion::StringToLong(OrderID);

					if(temp_convert != DEF::Inv_Long)
					{
						temp_convert = temp_convert + 1;
						NewOrderID = CDataConversion::LongToString(temp_convert);
					}
					NEXT_HM_ID = CDataConversion::LongToString(m_pPP_HM->getNextHMID());
					nextSampleRef = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF(true,lastError);
					if(m_pPD_HOT_METAL->getNextHOTMETAL_COUNTER(nextHMCounter,lastError))
					{
						m_pPD_HOT_METAL->setHOTMETAL_COUNTER(nextHMCounter);
						m_pPD_HOT_METAL->setREVTIME(Now);
						RetValue = RetValue & m_pPD_HOT_METAL->insert();
					}
					
					if(m_pPD_HOT_METAL->select(HMCounter))
					{
						m_pPD_HOT_METAL->setLADLENO(m_pPD_HOT_METAL->getLADLENO(1));
						m_pPD_HOT_METAL->setLADLETYPE(m_pPD_HOT_METAL->getLADLETYPE(1));
						m_pPD_HOT_METAL->setWEIGHT(m_pPD_HOT_METAL->getWEIGHT(1));
						m_pPD_HOT_METAL->setSAMPLE_REF(nextSampleRef);

						if(m_pPD_HOT_METAL->select(nextHMCounter))
						{
							RetValue = RetValue & m_pPD_HOT_METAL->update();
						}
					}

					RetValue = RetValue & m_pPP_HM->updateInsertPP(NEXT_HM_ID,PlantNo,nextHMCounter,false,lastError);
					StartTime.addTime(20*60*1.0);
					EndTime.addTime(40*60*1.0);

					if(m_pPP_HM->select(HM_ID))
					{
						m_pPP_HM->setPRODORDERID(NewOrderID);

						if(NewOrderID == CSMC_DBData::unspecString)
						{
							m_pPP_HM->setHM_ID_CUST_PLAN(NEXT_HM_ID);
						}
						else
						{
							m_pPP_HM->setHM_ID_CUST_PLAN(NewOrderID);
						}
						m_pPP_HM->setTREATSTART_PLAN(StartTime);
						m_pPP_HM->setTREATEND_PLAN(EndTime);
						m_pPP_HM->setPLANNED(1);
						m_pPP_HM->setON_REQUEST(1);
						m_pPP_HM->setLADLEFREEBOARD(m_pPP_HM->getLADLEFREEBOARD(1));
						m_pPP_HM->setAIM_S(m_pPP_HM->getAIM_S(1));

						if(m_pPP_HM->select(NEXT_HM_ID))
						{
							RetValue = RetValue & m_pPP_HM->update();
						}

					}

				}

				if (RetValue)
					CDH_IN_Task::getInstance()->getStdConnection()->commit();
				else
				{
					CDH_IN_Task::getInstance()->getStdConnection()->rollback();
				}

			}

		}
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
			RetValue = false;
    }
    catch(CORBA::SystemException& sExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str());
      RetValue = false;
    }

	return RetValue;
}

// Copyright (C) 2010 SMS Demag AG Germany
#include "Telcom_Out_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdInitBase.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include "CEventHandler.h"
#include "CEventMessage.h"
#include "CSMC_DataProvider_Impl.h"
#include "CDH_OUT_Task.h"


// Access to DB
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_ORDER_SINGLE_AIMS.h"

#include "CPD_HEAT_REF.h"
#include "CPD_HEAT_DATA.h"
#include "CPDL_HEAT_DATA.h"
#include "CPDE_HEAT_DATA.h"

#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CPD_SAMPLE_REF.h"

#include "CPD_LADLE_LIFE_DATA.h"
#include "CPD_LADLE.h"
#include "CPD_RECIPE.h"

#include "CGT_PARAM.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_LADLE_PARTS.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_PARAM_TYPE.h"
#include "DEF_GC_HEAT_STATUS.h"

#include "CGC_HEAT_STATUS.h"
#include "CPD_ACTION.h"

#include "CPD_HEAT_PLANT_REF.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"

#include "CCCS_EventHandler.h"



//##ModelId=4582C08F0093
CCCS_EventHandler::CCCS_EventHandler( )
{

  m_pGC_Plant_Container = 0;
  m_pHeatDataConverter  = 0;

  m_pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();
  
  m_SenderName = cCBS_StdInitBase::getInstance()->m_ServerName;
  m_DestinationName = "TELCOM_CCS_OUT";

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","DestinationName",m_DestinationName);

  std::string TaskName = CDH_OUT_Task::getInstance()->getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName",m_DestinationName);

  // use existing DB conenction from Task
  cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();

  if (pConnection)
  {
    // create plantId converter between L1<-->L2
    m_pGC_Plant_Container     = new CGC_Plant_Container   (pConnection);
    // create converter for customer heat and treat ids
    m_pHeatDataConverter      = new CHeatDataConverter    (pConnection);

    m_pPP_HEAT                = new CPP_HEAT              (pConnection);
    m_pPP_HEAT_PLANT          = new CPP_HEAT_PLANT        (pConnection);
    m_pPP_ORDER_SINGLE_AIMS   = new CPP_ORDER_SINGLE_AIMS (pConnection);

    m_pPD_HEAT_REF            = new CPD_HEAT_REF          (pConnection);
    m_pPD_HEAT_DATA           = new CPD_HEAT_DATA         (pConnection);
    m_pPDL_HEAT_DATA          = new CPDL_HEAT_DATA        (pConnection);
    m_pPDE_HEAT_DATA          = new CPDE_HEAT_DATA        (pConnection);

    m_pPD_SAMPLE              = new CPD_SAMPLE            (pConnection);
    m_pPD_SAMPLE_ENTRY        = new CPD_SAMPLE_ENTRY      (pConnection);
    m_pPD_SAMPLE_REF          = new CPD_SAMPLE_REF        (pConnection);

    m_pPD_LADLE               = new CPD_LADLE             (pConnection);
    m_pPD_LADLE_LIFE_DATA     = new CPD_LADLE_LIFE_DATA   (pConnection);
    m_pPD_RECIPE              = new CPD_RECIPE            (pConnection);

    m_pGT_PARAM               = new CGT_PARAM            (pConnection);

    m_pGC_HEAT_STATUS         = new CGC_HEAT_STATUS      (pConnection);
		m_pPD_HEAT_PLANT_REF      = new CPD_HEAT_PLANT_REF   (pConnection);
		m_pPD_ACTION              = new CPD_ACTION           (pConnection);
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CCCS_EventHandler","No database connection");

    // to guaranty EL_ExceptionCaught to be sent to CBS service
    Sleep(3000);

    // terminate programm in case of starting up without getting connection to database
    exit(EXIT_FAILURE);
  }

}

//##ModelId=4582C08F024B
CCCS_EventHandler::~CCCS_EventHandler()
{
  if( m_pGC_Plant_Container ) {delete m_pGC_Plant_Container;    m_pGC_Plant_Container   = 0;}
  if( m_pHeatDataConverter )  {delete m_pHeatDataConverter;     m_pHeatDataConverter    = 0;}

  if( m_pPP_HEAT )            {delete m_pPP_HEAT;               m_pPP_HEAT              = 0;}
  if( m_pPP_HEAT_PLANT )      {delete m_pPP_HEAT_PLANT;         m_pPP_HEAT_PLANT        = 0;}
  if( m_pPP_ORDER_SINGLE_AIMS){delete m_pPP_ORDER_SINGLE_AIMS;  m_pPP_ORDER_SINGLE_AIMS = 0;}

  if( m_pPD_HEAT_REF )        {delete m_pPD_HEAT_REF;           m_pPD_HEAT_REF         = 0;}
  if( m_pPD_HEAT_DATA )       {delete m_pPD_HEAT_DATA;          m_pPD_HEAT_DATA         = 0;}
  if( m_pPDL_HEAT_DATA )      {delete m_pPDL_HEAT_DATA;         m_pPDL_HEAT_DATA        = 0;}
  if( m_pPDE_HEAT_DATA )      {delete m_pPDE_HEAT_DATA;         m_pPDE_HEAT_DATA        = 0;}

  if( m_pPD_SAMPLE )          {delete m_pPD_SAMPLE;             m_pPD_SAMPLE            = 0;}
  if( m_pPD_SAMPLE_ENTRY )    {delete m_pPD_SAMPLE_ENTRY;       m_pPD_SAMPLE_ENTRY      = 0;}
  if( m_pPD_SAMPLE_REF )      {delete m_pPD_SAMPLE_REF;         m_pPD_SAMPLE_REF        = 0;}

  if( m_pPD_LADLE )           {delete m_pPD_LADLE;              m_pPD_LADLE             = 0;}
  if( m_pPD_LADLE_LIFE_DATA ) {delete m_pPD_LADLE_LIFE_DATA;    m_pPD_LADLE_LIFE_DATA   = 0;}
  if( m_pPD_RECIPE )          {delete m_pPD_RECIPE;             m_pPD_RECIPE            = 0;}

  if( m_pGT_PARAM )           {delete m_pGT_PARAM;              m_pGT_PARAM            = 0;}

  if( m_pGC_HEAT_STATUS )     {delete m_pGC_HEAT_STATUS;        m_pGC_HEAT_STATUS      = 0;}

  if( m_pPD_HEAT_PLANT_REF )  {delete m_pPD_HEAT_PLANT_REF;     m_pPD_HEAT_PLANT_REF   = 0;}
	
  if( m_pPD_ACTION )          {delete m_pPD_ACTION;             m_pPD_ACTION   = 0;}
	

}



//##ModelId=4587AAA80238
bool CCCS_EventHandler::handleEvent(CEventMessage& evMessage)
{
  log("Class.CCCS_EventHandler Version.1.0.0", 3);

  bool RetValue = false;

  std::string actMessage = evMessage.getMessage();

  if (actMessage == EAF_EvMsg::evEAFCyclicMeasurement || actMessage == LF_EvMsg::evLFCyclicMeasurement )
  {
    log(evMessage, 3);
    RetValue = provideData_EstimatedLadleArrivalTime(evMessage);
		RetValue = provideData_HeatData(evMessage); 
  }
  else if ( actMessage == EAF_EvMsg::evEAFHeatAnnouncement   ||
            actMessage == EAF_EvMsg::evEAFHeatStart          ||
            actMessage == EAF_EvMsg::evEAFTappingStart       ||
            actMessage == EAF_EvMsg::evEAFHeatEnd            ||
            actMessage == EAF_EvMsg::evEAFHeatDeparture      ||
            actMessage == LF_EvMsg::evLFHeatAnnouncement     ||
            actMessage == LF_EvMsg::evLFHeatStart            ||
            actMessage == LF_EvMsg::evLFHeatEnd              ||
            actMessage == LF_EvMsg::evLFHeatDeparture        )
	{
		RetValue = provideData_HeatData(evMessage); 
	}
  else if(actMessage == LF_EvMsg::evLFSteelAnalysisReceived   ||
          actMessage == EAF_EvMsg::evEAFSteelAnalysisReceived )
  {
    RetValue = provideData_SteelAnalysisData(evMessage);
  }
  else if(actMessage == LF_EvMsg::evLFSlagAnalysisReceived    ||
          actMessage == EAF_EvMsg::evEAFSlagAnalysisReceived  )
  {
    RetValue = provideData_SlagAnalysisData(evMessage);
  }

	return RetValue;
}


bool CCCS_EventHandler::provideData_SteelAnalysisData(CEventMessage& Event) 
{
	string exceMsg = "CCCS_EventHandler::provideData_SteelAnalysisData";
  bool RetValue = true; 

  std::string CustHeatID, CustTreatID;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();     
  std::string OrderId   = Event.getOrderID();
	std::string L2PlantID   = Event.getPlantID();
	std::string L3PlantID   = "1";
	std::string Plant  = m_pGC_Plant_Container->getPlant(L2PlantID);
	long PlantNo       = m_pGC_Plant_Container->getPlantNo(L2PlantID); 

  try
  {
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID, Plant);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
			std::string tlgName  = "L2_ANALYSIS_STEEL";

			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::MsgStatus,1);

			long SampleRef = 0;
			long sampleCounter = 0;
      if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				SampleRef = m_pPD_HEAT_DATA->getSAMPLE_REF(1);
				if(m_pPD_HEAT_DATA->getLADLENO(1) != CSMC_DBData::unspecLong)
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::LadleNo,m_pPD_HEAT_DATA->getLADLENO(1));
			}

      if(m_pPD_SAMPLE_REF->select(SampleRef) && m_pPD_SAMPLE_REF->getLastRow() > 0)
      {
         sampleCounter = m_pPD_SAMPLE_REF->getSTEEL(1); 
      }

      if(m_pPD_SAMPLE->select(sampleCounter) && m_pPD_SAMPLE->getLastRow() > 0)
      {        
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::OrderId,m_pPD_SAMPLE->getPRODORDERID(1));
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::SmplTime,m_pPD_SAMPLE->getSAMPLETIME(1).assDate() );
				m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::SmplCounter,m_pPD_SAMPLE->getSAMPLENO(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::SmplCode, m_pPD_SAMPLE->getSAMPLEID_CUST(1));

				m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::SmplUseable,m_pPD_SAMPLE->getSAMPLEUSABLE(1));
			}

			if(m_pPD_SAMPLE_ENTRY->select(sampleCounter,CSMC_DBData::unspecString) && m_pPD_SAMPLE_ENTRY->getLastRow() > 0)
      {
        for(int i = 1; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); i++)
        {
          string element = m_pPD_SAMPLE_ENTRY->getMEASNAME(i); 
          double elementVal = m_pPD_SAMPLE_ENTRY->getMEASVALUE(i); 

					if(DEF_GC_MEASUREMENT_NAME::C == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_C,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Si == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Si,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Mn == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Mn,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::P == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_P,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::S == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_S,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Al == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Al,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Al_S == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Al_S,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Cu == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_CU,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Cr == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Cr,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Mo == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Mo,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Ni == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Ni,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::V == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_V,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Ti == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Ti,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Nb == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Nb,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Ca == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Ca,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Co == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Co,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Pb == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Pb,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::W == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_W,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Mg == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Mg,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Ce == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Ce,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::B == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_B,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::As == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_As,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Sn == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Sn,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Bi == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Bi,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::Sb == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Sb,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Zr == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Zr,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::O2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_O,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::N2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_N,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::H2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_H,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Zn == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_STEEL::AnlVal_Zn,elementVal);

				}
			}

      m_pTelcom_Interface->showContent(DataKeyOut, 4);

      CEventMessage message(m_SenderName, 
                            m_DestinationName, 
                            "TELEGRAM_" + tlgName,
                            L3PlantID,
                            "",
                            std::string ("UNUSED"),
                            false, 
                            HeatID,
                            TreatID, 
                            DataKeyOut);
        message.setOrderID(OrderId);
        RetValue = CDH_EventHandler::dispatchEvent("", "", message);

      }

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),exceMsg.c_str(), ""); 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",exceMsg.c_str(), ""  );    
  } 

  return RetValue;
  
}//end function

bool CCCS_EventHandler::provideData_SlagAnalysisData(CEventMessage& Event) 
{
	string exceMsg = "CCCS_EventHandler::provideData_SlagAnalysisData";
  bool RetValue = true; 

  std::string CustHeatID, CustTreatID;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();     
  std::string OrderId   = Event.getOrderID();
	std::string L2PlantID   = Event.getPlantID();
	std::string L3PlantID   = "1";
	std::string Plant  = m_pGC_Plant_Container->getPlant(L2PlantID);
	long PlantNo       = m_pGC_Plant_Container->getPlantNo(L2PlantID); 

  try
  {
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID, Plant);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
			std::string tlgName  = "L2_ANALYSIS_SLAG";

			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::MsgStatus,1);

			long SampleRef = 0;
			long sampleCounter = 0;
			
      if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				SampleRef = m_pPD_HEAT_DATA->getSAMPLE_REF(1);
				if(m_pPD_HEAT_DATA->getLADLENO(1) != CSMC_DBData::unspecLong)
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::LadleNo,m_pPD_HEAT_DATA->getLADLENO(1));
			}

      if(m_pPD_SAMPLE_REF->select(SampleRef) && m_pPD_SAMPLE_REF->getLastRow() > 0)
      {
         sampleCounter = m_pPD_SAMPLE_REF->getSLAG(1); 
      }

      if(m_pPD_SAMPLE->select(sampleCounter) && m_pPD_SAMPLE->getLastRow() > 0)
      {        
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::OrderId,m_pPD_SAMPLE->getPRODORDERID(1));
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::SmplTime,m_pPD_SAMPLE->getSAMPLETIME(1).assDate() );
				m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::SmplCounter,m_pPD_SAMPLE->getSAMPLENO(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::SmplCode, m_pPD_SAMPLE->getSAMPLEID_CUST(1));
				m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::SmplUseable,m_pPD_SAMPLE->getSAMPLEUSABLE(1));
			}

			if(m_pPD_SAMPLE_ENTRY->select(sampleCounter,CSMC_DBData::unspecString) && m_pPD_SAMPLE_ENTRY->getLastRow() > 0)
      {
        for(int i = 1; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); i++)
        {
          string element = m_pPD_SAMPLE_ENTRY->getMEASNAME(i); 
          double elementVal = m_pPD_SAMPLE_ENTRY->getMEASVALUE(i); 

					if(DEF_GC_MEASUREMENT_NAME::CaO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_CaO,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::SiO2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_SiO2,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::P2O5 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_P2O5,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::FeO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_FeO,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Fe2O3 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_Fe2O3,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Fe3O4 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_Fe3O4,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::S_X == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_S,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Al2O3 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_Al2O3,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::MgO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_MgO,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::MnO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_MnO,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Cr2O3 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_Cr2O3,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::MoO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_MoO,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::NiO == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_NiO,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::V2O5 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_V2O5,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::TiO2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_TiO2,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::TiFe == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_TiFe,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::CaC2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_CaC2,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::CaF2 == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_CaF2,elementVal);

					if(DEF_GC_MEASUREMENT_NAME::CaS == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_CaS,elementVal);
					if(DEF_GC_MEASUREMENT_NAME::Fe_X == element)
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ANALYSIS_SLAG::AnlVal_Fe_X,elementVal);

				}
			}

      m_pTelcom_Interface->showContent(DataKeyOut, 4);

      CEventMessage message(m_SenderName, 
                            m_DestinationName, 
                            "TELEGRAM_" + tlgName,
                            L3PlantID,
                            "",
                            std::string ("UNUSED"),
                            false, 
                            HeatID,
                            TreatID, 
                            DataKeyOut);
        message.setOrderID(OrderId);
        RetValue = CDH_EventHandler::dispatchEvent("", "", message);

      }

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),exceMsg.c_str(), ""); 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",exceMsg.c_str(), ""  );    
  } 

  return RetValue;
  
}//end function


bool CCCS_EventHandler::provideData_EstimatedLadleArrivalTime(CEventMessage& Event) 
{
	string exceMsg = "CCCS_EventHandler::provideData_EstimatedLadleArrivalTime";
  bool RetValue = true; 


  std::string CustHeatID, CustTreatID;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();     
  std::string OrderId   = Event.getOrderID();
	std::string L2PlantID   = Event.getPlantID();
	std::string L3PlantID   = "1";
	std::string Plant  = m_pGC_Plant_Container->getPlant(L2PlantID);
	long PlantNo       = m_pGC_Plant_Container->getPlantNo(L2PlantID); 
	
  try
  {
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID, Plant);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
			std::string tlgName  = "L2_ESTMT_LADLE_ARRIVAL";

			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;
			CDateTime ExpectedTreatmentEnd;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::MsgStatus,1);

			if(m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
			{
				if(m_pPD_HEAT_DATA->getLADLENO(1) != CSMC_DBData::unspecLong)
						m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::LadleNo,m_pPD_HEAT_DATA->getLADLENO(1));

				if(m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1) != CSMC_DBData::unspecString)
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::SteelGrade,m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1));

				if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMTEMP_MOD, 1) )
				{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::EstimatedArrivalTemp,m_pPD_HEAT_DATA->getAIMTEMP_MOD(1));
				}
				else if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMTEMP_PLAN, 1) )
				{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::EstimatedArrivalTemp,m_pPD_HEAT_DATA->getAIMTEMP_PLAN(1));
				}

				if(m_pPD_HEAT_DATA->isNull("TREATEND_ACT",1))
					ExpectedTreatmentEnd = m_pPD_HEAT_DATA->getTREATEND_MOD(1).assDate();
				else
					ExpectedTreatmentEnd = m_pPD_HEAT_DATA->getTREATEND_ACT(1).assDate();

				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_ESTMT_LADLE_ARRIVAL::ExpTreatmentEnd,ExpectedTreatmentEnd.assDate());
			}
			



      m_pTelcom_Interface->showContent(DataKeyOut, 4);

      CEventMessage message(m_SenderName, 
                            m_DestinationName, 
                            "TELEGRAM_" + tlgName,
                            L3PlantID,
                            "",
                            std::string ("UNUSED"),
                            false, 
                            HeatID,
                            TreatID, 
                            DataKeyOut);
        message.setOrderID(OrderId);
        RetValue = CDH_EventHandler::dispatchEvent("", "", message);

      }

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),exceMsg.c_str(), ""); 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",exceMsg.c_str(), ""  );    
  } 

  return RetValue;
  
}//end function


bool CCCS_EventHandler::provideData_HeatData(CEventMessage &Event)
{
  string exceMsg = "CCCS_EventHandler::provideData_HeatData()";

  bool retval = true; 

  std::string CustHeatID, CustTreatID;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();     
  std::string OrderId   = Event.getOrderID();
	std::string L2PlantID   = Event.getPlantID();
	std::string L3PlantID   = "1";
	std::string Plant  = m_pGC_Plant_Container->getPlant(L2PlantID);
	long PlantNo       = m_pGC_Plant_Container->getPlantNo(L2PlantID); 

  try
  {
    m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::EVENT);
		
		m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID,Plant);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_HEAT_DATA";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;
      string SteelGrade,ProdOrder;
      long LadleNo;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::MsgStatus,1 );


			if(m_pPD_HEAT_DATA->select(HeatID,TreatID,Plant) && m_pPD_HEAT_DATA->getLastRow() > 0)
			{
				ProdOrder = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
				SteelGrade = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
				LadleNo = m_pPD_HEAT_DATA->getLADLENO(1);

				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::OrderId,ProdOrder );

				if(LadleNo != CSMC_DBData::unspecLong)
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::LadleNo,LadleNo );

				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SteelGrade,SteelGrade) ;

				if(Plant == DEF_GC_PLANT_DEF::EAF )
				{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SteelWeight,m_pPD_HEAT_DATA->getSTEELMASS(1)) ;
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SlagWeight,m_pPD_HEAT_DATA->getSLAGMASS(1)) ;
				}
				else if(Plant == DEF_GC_PLANT_DEF::LF )
				{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SteelWeight,m_pPD_HEAT_DATA->getSTEELMASS_START(1)) ;
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SlagWeight,m_pPD_HEAT_DATA->getSLAGMASS_START(1)) ;
				}
			}

      if ( m_pPDE_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				if((m_pPDE_HEAT_DATA->getTAPMASS(1) != CSMC_DBData::unspecDouble) && (m_pPDE_HEAT_DATA->getTAPMASS(1) > 0.0))
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::SteelWeight,m_pPDE_HEAT_DATA->getTAPMASS(1));
			}

			if( m_pPD_HEAT_PLANT_REF->select(HeatID, TreatID, Plant) )
			{
				if(m_pGC_HEAT_STATUS->select(m_pPD_HEAT_PLANT_REF->getSTATUSNO(1)))
				{
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::UnitStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_CCS(1) );
				}
			}
			
			//last measure temp
			if(m_pPD_SAMPLE->selectLastHeatTemp(HeatID,TreatID,Plant))
			{
				for(int i = 1; i <= m_pPD_SAMPLE->getLastRow(); i++)
				{
					if(m_pPD_SAMPLE->getSAMPLENO(i) != CSMC_DBData::unspecLong  && m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE->getSAMPLE_COUNTER(i),DEF_GC_MEASUREMENT_NAME::Temp) )
					{
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::TempMeas,m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));	
						m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_DATA::TempMeasTime,m_pPD_SAMPLE->getSAMPLETIME(i).assDate());							
						break;
					}
				}
			}

			     
      m_pTelcom_Interface->showContent(DataKeyOut, 4);

      CEventMessage message(m_SenderName, 
                            m_DestinationName, 
                            "TELEGRAM_" + tlgName,
                            L3PlantID,
                            "",
                            std::string ("UNUSED"),
                            false, 
                            HeatID,
                            TreatID, 
                            DataKeyOut);
        message.setOrderID(OrderId);
        retval = CDH_EventHandler::dispatchEvent("", "", message);
    }

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),exceMsg.c_str(), ""); 
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",exceMsg.c_str(), ""  );    
  } 

  return retval;
}


#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "Telcom_Out_s.hh"
#include "iDH_Interface_s.hh"      // to access DH_L3_IN 

#include "cCBS_StdInitBase.h"

#include "CEventMessage.h"
#include "CDateTime.h"
#include "CIntfData.h"
#include "CDataConversion.h"
#include "CTreatIDCust.h"
#include "CHeatIDCust.h"


#include "CDH_OUT_Task.h"


#include "DEF_GC_MEMBER_ROLE_CAT.h"
#include "DEF_GC_ACTION_DEF.h"
#include "DEF_GC_COUNTER_TYPE.h"
#include "DEF_GC_STATUS.h"
#include "DEF_GC_HEAT_STATUS.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_LADLE_PARTS.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GD_EQUIP_TYPE.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "CL3_EventHandler.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GCE_BURNER.h"
#include "DEF_GC_DELAY_GROUP.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_RECIPE.h"


//##ModelId=4582C0AF01AE
CL3_EventHandler::CL3_EventHandler()
: m_pDM_Interface(0)
{
  m_pTelcom_Interface = CDH_OUT_Task::getInstance()->getpInterface_OUT();

  m_SenderName = cCBS_StdInitBase::getInstance()->m_ServerName;


  cCBS_StdConnection* pConnection = CDH_OUT_Task::getInstance()->getStdConnection();

  if (pConnection)
  {
    m_pGC_Plant_Container = new CGC_Plant_Container(pConnection);
    m_pHeatDataConverter  = new CHeatDataConverter(pConnection);
    m_pEquipmentData      = new CEquipmentData(pConnection);

    m_pPD_HEAT_DATA       = new CPD_HEAT_DATA(pConnection);
    m_pPD_HEAT_DATA_STIRR = new CPD_HEAT_DATA_STIRR(pConnection);

    m_pPD_RECIPE          = new CPD_RECIPE(pConnection);
    m_pPD_RECIPE_ENTRY    = new CPD_RECIPE_ENTRY(pConnection);


    m_pPD_LADLE_LIFE_DATA = new CPD_LADLE_LIFE_DATA(pConnection);
    m_pHD_RECIPE          = new CHD_RECIPE(pConnection);
    m_pHD_RECIPE_ENTRY    = new CHD_RECIPE_ENTRY(pConnection);
    m_pHD_SAMPLE          = new CHD_SAMPLE( pConnection );
    m_pHD_SAMPLE_ENTRY    = new CHD_SAMPLE_ENTRY(pConnection);
    m_pHD_SAMPLE_REF      = new CHD_SAMPLE_REF(pConnection);
    m_pGC_STATUS          = new CGC_STATUS(pConnection);
    m_pGC_HEAT_STATUS     = new CGC_HEAT_STATUS(pConnection);
    m_pPD_HEAT_PLANT_REF  = new CPD_HEAT_PLANT_REF(pConnection);
    m_pPD_HEAT_REF        = new CPD_HEAT_REF(pConnection);
    m_pPD_DELAYS          = new CPD_DELAYS(pConnection);
    m_pGT_DELAY_CODE      = new CGT_DELAY_CODE(pConnection);
    m_pPP_HEAT            = new CPP_HEAT(pConnection);
    m_pPP_HEAT_PLANT      = new CPP_HEAT_PLANT(pConnection);
    m_pPD_ACTION          = new CPD_ACTION(pConnection);
    m_pPD_SAMPLE          = new CPD_SAMPLE(pConnection);
    m_pPD_SAMPLE_ENTRY    = new CPD_SAMPLE_ENTRY(pConnection);
    m_pPD_SAMPLE_REF      = new CPD_SAMPLE_REF(pConnection);
    m_pGC_SAMPLELOC       = new CGC_SAMPLELOC(pConnection);

    m_pPDE_HEAT_DATA      = new CPDE_HEAT_DATA(pConnection);
    m_pPDL_HEAT_DATA      = new CPDL_HEAT_DATA(pConnection);

    m_pPDL_ACTIVITY_RES   = new CPDL_ACTIVITY_RES(pConnection);
		m_pPDH_HM_DATA        = new CPDH_HM_DATA(pConnection);
		m_pPD_HOT_METAL       = new CPD_HOT_METAL(pConnection);

		m_pGC_CREW_CAT                = new CGC_CREW_CAT(pConnection);
		m_pGC_MEMBER_CAT							= new CGC_MEMBER_CAT(pConnection);
		m_pPP_MEMBER_CREW_ASSIGNMENT  = new CPP_MEMBER_CREW_ASSIGNMENT(pConnection);

		m_pPD_HEAT_DATA_LIQADD  = new CPD_HEAT_DATA_LIQADD(pConnection);

		m_pPDE_HEAT_DATA_BURN  = new CPDE_HEAT_DATA_BURN(pConnection);
		m_pGC_Plantgroup_Container  = new CGC_Plantgroup_Container(pConnection);
		m_pGT_MAT_PURP = new CGT_MAT_PURP(pConnection);

		m_pPP_HM = new CPP_HM(pConnection);
		m_pPDH_ACTION = new CPDH_ACTION(pConnection);
		m_pHDH_EQUIP_COUNTER = new CHDH_EQUIP_COUNTER(pConnection);

  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CL3_EventHandler","No database connection");

    // to guaranty EL_ExceptionCaught to be sent to CBS service
    Sleep(3000);

    // terminate programm in case of starting up without getting connection to database
    exit(EXIT_FAILURE);
  }

}

//##ModelId=4582C0AF0322
CL3_EventHandler::~CL3_EventHandler()
{
	if(m_pGC_Plant_Container)   {delete m_pGC_Plant_Container;  m_pGC_Plant_Container = 0; }

	if(m_pPD_HEAT_DATA)         {delete m_pPD_HEAT_DATA;        m_pPD_HEAT_DATA = 0;}
	if(m_pPD_HEAT_DATA_STIRR)   {delete m_pPD_HEAT_DATA_STIRR;  m_pPD_HEAT_DATA_STIRR = 0;}

	if(m_pPD_LADLE_LIFE_DATA)   {delete m_pPD_LADLE_LIFE_DATA;  m_pPD_LADLE_LIFE_DATA = 0;}
	if(m_pHD_RECIPE)            {delete m_pHD_RECIPE;           m_pHD_RECIPE = 0;}
	if(m_pHD_RECIPE_ENTRY)      {delete m_pHD_RECIPE_ENTRY;     m_pHD_RECIPE_ENTRY = 0;}
	if(m_pHD_SAMPLE_ENTRY)      {delete m_pHD_SAMPLE_ENTRY;     m_pHD_SAMPLE_ENTRY = 0;}
	if(m_pHD_SAMPLE_REF)        {delete m_pHD_SAMPLE_REF;       m_pHD_SAMPLE_REF = 0;}
	if(m_pHD_SAMPLE)            {delete m_pHD_SAMPLE;           m_pHD_SAMPLE = 0;}
	if(m_pGC_STATUS)            {delete m_pGC_STATUS;           m_pGC_STATUS = 0;}
	if(m_pGC_HEAT_STATUS)       {delete m_pGC_HEAT_STATUS;      m_pGC_HEAT_STATUS = 0;}
	if(m_pPD_HEAT_PLANT_REF)    {delete m_pPD_HEAT_PLANT_REF;   m_pPD_HEAT_PLANT_REF = 0;}
	if(m_pPD_HEAT_REF)          {delete m_pPD_HEAT_REF;         m_pPD_HEAT_REF = 0;}
	if(m_pPD_DELAYS )           {delete m_pPD_DELAYS;           m_pPD_DELAYS = 0;}
	if(m_pGT_DELAY_CODE )       {delete m_pGT_DELAY_CODE;       m_pGT_DELAY_CODE = 0;}
	if(m_pPP_HEAT )             {delete m_pPP_HEAT;             m_pPP_HEAT = 0;}
  if(m_pPP_HEAT_PLANT)        {delete m_pPP_HEAT_PLANT;       m_pPP_HEAT_PLANT = 0;}
	if(m_pPD_ACTION)            {delete m_pPD_ACTION;           m_pPD_ACTION = 0;}
	if(m_pPD_SAMPLE)            {delete m_pPD_SAMPLE;           m_pPD_SAMPLE = 0;}
	if(m_pPD_SAMPLE_ENTRY)      {delete m_pPD_SAMPLE_ENTRY;     m_pPD_SAMPLE_ENTRY = 0;}
	if(m_pPD_SAMPLE_REF)        {delete m_pPD_SAMPLE_REF;       m_pPD_SAMPLE_REF = 0;}
	if(m_pGC_SAMPLELOC)         {delete m_pGC_SAMPLELOC;        m_pGC_SAMPLELOC = 0;}
	if(m_pPDE_HEAT_DATA)        {delete m_pPDE_HEAT_DATA;       m_pPDE_HEAT_DATA = 0;}
	if(m_pPDL_HEAT_DATA)        {delete m_pPDL_HEAT_DATA;       m_pPDL_HEAT_DATA = 0;}
	if(m_pPDL_ACTIVITY_RES)     {delete m_pPDL_ACTIVITY_RES;    m_pPDL_ACTIVITY_RES = 0;}

	if(m_pPDH_HM_DATA)          {delete m_pPDH_HM_DATA;    m_pPDH_HM_DATA = 0;}
	if(m_pPD_HOT_METAL)         {delete m_pPD_HOT_METAL;    m_pPD_HOT_METAL = 0;}
	
	if(m_pGC_CREW_CAT)								{delete m_pGC_CREW_CAT;    m_pGC_CREW_CAT = 0;}
	if(m_pGC_MEMBER_CAT)							{delete m_pGC_MEMBER_CAT;    m_pGC_MEMBER_CAT = 0;}
	if(m_pPP_MEMBER_CREW_ASSIGNMENT)  {delete m_pPP_MEMBER_CREW_ASSIGNMENT;    m_pPP_MEMBER_CREW_ASSIGNMENT = 0;}

	if(m_pPD_HEAT_DATA_LIQADD)  {delete m_pPD_HEAT_DATA_LIQADD;    m_pPD_HEAT_DATA_LIQADD = 0;}
	
	if(m_pPDE_HEAT_DATA_BURN)  {delete m_pPDE_HEAT_DATA_BURN;    m_pPDE_HEAT_DATA_BURN = 0;}
	
	if(m_pGC_Plantgroup_Container)  {delete m_pGC_Plantgroup_Container;    m_pGC_Plantgroup_Container = 0;}
	if(m_pGT_MAT_PURP)  {delete m_pGT_MAT_PURP;    m_pGT_MAT_PURP = 0;}
	
	if(m_pPP_HM)  {delete m_pPP_HM;    m_pPP_HM = 0;}
	if(m_pPDH_ACTION)  {delete m_pPDH_ACTION;    m_pPDH_ACTION = 0;}
	
	if(m_pHDH_EQUIP_COUNTER)  {delete m_pHDH_EQUIP_COUNTER;    m_pHDH_EQUIP_COUNTER = 0;}
	if(m_pPD_RECIPE_ENTRY)  {delete m_pPD_RECIPE_ENTRY;    m_pPD_RECIPE_ENTRY = 0;}
	if(m_pHeatDataConverter)  {delete m_pHeatDataConverter;    m_pHeatDataConverter = 0;}
	
	if(m_pEquipmentData)  {delete m_pEquipmentData;    m_pEquipmentData = 0;}
	if(m_pPD_RECIPE)  {delete m_pPD_RECIPE;    m_pPD_RECIPE = 0;}
	
		
		

}

void CL3_EventHandler::getSlagAnalysisStream(DEF::seqString& SlagAnalysisDB)
{  
  CIntfData::insert(SlagAnalysisDB, "CaO");
  CIntfData::insert(SlagAnalysisDB, "SiO2");
  CIntfData::insert(SlagAnalysisDB, "P2O5");
  CIntfData::insert(SlagAnalysisDB, "FeO");
  CIntfData::insert(SlagAnalysisDB, "Fe2O3");
  CIntfData::insert(SlagAnalysisDB, "Fe3O4");
  CIntfData::insert(SlagAnalysisDB, "S");
  CIntfData::insert(SlagAnalysisDB, "Al2O3");
  CIntfData::insert(SlagAnalysisDB, "MgO");
  CIntfData::insert(SlagAnalysisDB, "MnO");
  CIntfData::insert(SlagAnalysisDB, "Cr2O3");
  CIntfData::insert(SlagAnalysisDB, "MoO");
  CIntfData::insert(SlagAnalysisDB, "NiO");
  CIntfData::insert(SlagAnalysisDB, "V2O5");
  CIntfData::insert(SlagAnalysisDB, "TiO2");
  CIntfData::insert(SlagAnalysisDB, "TiFe");
  CIntfData::insert(SlagAnalysisDB, "CaC2");
  CIntfData::insert(SlagAnalysisDB, "CaF2");
  CIntfData::insert(SlagAnalysisDB, "CaS");
  CIntfData::insert(SlagAnalysisDB, "Fe_X");  
  CIntfData::insert(SlagAnalysisDB, "Spare1");  
  CIntfData::insert(SlagAnalysisDB, "Spare2");  
  CIntfData::insert(SlagAnalysisDB, "Spare3");  
  CIntfData::insert(SlagAnalysisDB, "Spare4");  
  CIntfData::insert(SlagAnalysisDB, "Spare5");  
  CIntfData::insert(SlagAnalysisDB, "Spare6");  
  CIntfData::insert(SlagAnalysisDB, "Spare7");  
  CIntfData::insert(SlagAnalysisDB, "Spare8");  
  CIntfData::insert(SlagAnalysisDB, "Spare9");  
  CIntfData::insert(SlagAnalysisDB, "Spare10");  
  CIntfData::insert(SlagAnalysisDB, "Spare11");  
  CIntfData::insert(SlagAnalysisDB, "Spare12");  
  CIntfData::insert(SlagAnalysisDB, "Spare13");  
  CIntfData::insert(SlagAnalysisDB, "Spare14");  
  CIntfData::insert(SlagAnalysisDB, "Spare15");  
  CIntfData::insert(SlagAnalysisDB, "Spare16");  
  CIntfData::insert(SlagAnalysisDB, "Spare17");  
  CIntfData::insert(SlagAnalysisDB, "Spare18");  
  CIntfData::insert(SlagAnalysisDB, "Spare19");  
  CIntfData::insert(SlagAnalysisDB, "Spare20"); 
}

void CL3_EventHandler::getSteelAnalysisStream(DEF::seqString& SteelAnalysisDB)
{
  CIntfData::insert(SteelAnalysisDB, "C");
  CIntfData::insert(SteelAnalysisDB, "Si");
  CIntfData::insert(SteelAnalysisDB, "Mn");
  CIntfData::insert(SteelAnalysisDB, "P");
  CIntfData::insert(SteelAnalysisDB, "S");
  CIntfData::insert(SteelAnalysisDB, "Al");
  CIntfData::insert(SteelAnalysisDB, "Al_S");  
  CIntfData::insert(SteelAnalysisDB, "Cu");
  CIntfData::insert(SteelAnalysisDB, "Cr");
  CIntfData::insert(SteelAnalysisDB, "Mo");
  CIntfData::insert(SteelAnalysisDB, "Ni");
  CIntfData::insert(SteelAnalysisDB, "V");
  CIntfData::insert(SteelAnalysisDB, "Ti");
  CIntfData::insert(SteelAnalysisDB, "Nb");
  CIntfData::insert(SteelAnalysisDB, "Ca");
  CIntfData::insert(SteelAnalysisDB, "Co");
  CIntfData::insert(SteelAnalysisDB, "Pb");
  CIntfData::insert(SteelAnalysisDB, "W");
  CIntfData::insert(SteelAnalysisDB, "Mg");
  CIntfData::insert(SteelAnalysisDB, "Ce");
  CIntfData::insert(SteelAnalysisDB, "B");
  CIntfData::insert(SteelAnalysisDB, "As");
  CIntfData::insert(SteelAnalysisDB, "Sn"); 
  CIntfData::insert(SteelAnalysisDB, "Bi");
  CIntfData::insert(SteelAnalysisDB, "Sb");
  CIntfData::insert(SteelAnalysisDB, "Zr");
  CIntfData::insert(SteelAnalysisDB, "O2");
  CIntfData::insert(SteelAnalysisDB, "N2");
  CIntfData::insert(SteelAnalysisDB, "H2");
  CIntfData::insert(SteelAnalysisDB, "Al_I");
  CIntfData::insert(SteelAnalysisDB, "Zn");
  CIntfData::insert(SteelAnalysisDB, "Fe");
  CIntfData::insert(SteelAnalysisDB, "Spare1");
  CIntfData::insert(SteelAnalysisDB, "Spare2");
  CIntfData::insert(SteelAnalysisDB, "Spare3");
  CIntfData::insert(SteelAnalysisDB, "Spare4");
  CIntfData::insert(SteelAnalysisDB, "Spare5");
  CIntfData::insert(SteelAnalysisDB, "Spare6");
  CIntfData::insert(SteelAnalysisDB, "Spare7");
  CIntfData::insert(SteelAnalysisDB, "Spare8");
  //CIntfData::insert(SteelAnalysisDB, "Spare9");
}

//##ModelId=4587AB5503E4
bool CL3_EventHandler::handleEvent(CEventMessage& evMessage)
{
  bool RetValue = false;
  std::string ActMessage = evMessage.getMessage();

  if ( ActMessage == L3_EvMsg::evL3HeatScheduleUpdate )
  {
    RetValue = provideData_ScheduleResponse(evMessage);
  }
  else if (ActMessage == HMD_EvMsg::evHMDProductionReport)
  {
    RetValue = provideData_ProductionDataHMD(evMessage); 
  }
  else if (ActMessage == LF_EvMsg::evLFProductionReport)
  {
    RetValue = provideData_ProductionDataLF(evMessage); 
  }
  else if (ActMessage == EAF_EvMsg::evEAFProductionReport)
  {
    RetValue = provideData_ProductionDataEAF(evMessage); 
  }
  else if(ActMessage == EAF_EvMsg::evEAFDelayStatus  || ActMessage == LF_EvMsg::evLFDelayStatus || ActMessage == HMD_EvMsg::evHMDDelayStatus ) 
  {
    RetValue = provideData_DelayReport (evMessage);
  }
  else if (ActMessage == EAF_EvMsg::evEAFCyclicMeasurement)
  {
    RetValue = provideData_HeatStatus(evMessage);
    RetValue = provideData_HeatReportMaterial (evMessage);
  }
  else if (  
            ActMessage == LF_EvMsg::evLFCyclicMeasurement    ||
            ActMessage == EAF_EvMsg::evEAFHeatAnnouncement   ||
            ActMessage == EAF_EvMsg::evEAFHeatStart          ||
            ActMessage == EAF_EvMsg::evEAFTappingStart       ||
            ActMessage == EAF_EvMsg::evEAFHeatEnd            ||
            ActMessage == EAF_EvMsg::evEAFHeatDeparture      ||
            ActMessage == LF_EvMsg::evLFHeatAnnouncement     ||
            ActMessage == LF_EvMsg::evLFHeatStart            ||
            ActMessage == LF_EvMsg::evLFHeatEnd              ||
            ActMessage == LF_EvMsg::evLFHeatDeparture    )
  {
    RetValue = provideData_HeatStatus(evMessage);
  }
  else if(ActMessage == EAF_EvMsg::evEAFHandleBasketDischarged || ActMessage == EAF_EvMsg::evEAFChargedHotMetal || ActMessage == EAF_EvMsg::evEAFMaterialHandlingReport || ActMessage == LF_EvMsg::evLFMaterialHandlingReport) 
  {
    RetValue = provideData_HeatReportMaterial (evMessage);
  }
  else if(ActMessage == HMD_EvMsg::evHMDCyclicMeasurement) 
  {
    RetValue = provideData_HeatReportMaterial (evMessage);
		RetValue = provideData_HeatStatus(evMessage);
  }
  else if(ActMessage == HMD_EvMsg::evHMDHeatAnnouncement || ActMessage == HMD_EvMsg::evHMDHeatStart || ActMessage == HMD_EvMsg::evHMDHeatEnd || ActMessage == HMD_EvMsg::evHMDHeatDeparture) 
  {
		RetValue = provideData_HeatStatus(evMessage);
  }
  else if(ActMessage == EAF_EvMsg::evEAFSteelSampleTaken || ActMessage == EAF_EvMsg::evEAFSlagSampleTaken || ActMessage == LF_EvMsg::evLFSteelSampleTaken || ActMessage == LF_EvMsg::evLFSlagSampleTaken || ActMessage == HMD_EvMsg::evHMDHotMetalSampleTaken  || ActMessage == HMD_EvMsg::evHMDSlagSampleTaken ) 
  {
    RetValue = provideData_sampleTaken(evMessage);
  }
  else if(ActMessage == EAF_EvMsg::evEAFTempMeasurement || ActMessage == EAF_EvMsg::evEAFCeloxMeasurement || ActMessage == LF_EvMsg::evLFTempMeasurement || ActMessage == LF_EvMsg::evLFCeloxMeasurement || ActMessage == HMD_EvMsg::evHMDTempMeasurement  || ActMessage == HMD_EvMsg::evHMDCeloxMeasurement ) 
  {
    RetValue = provideData_temperatureTaken(evMessage);
  }

  if ( RetValue )
  {
    log(ActMessage, 3);
  }


  return RetValue;
}


bool CL3_EventHandler::provideData_ProductionDataEAF(CEventMessage& Event) 
{
	string exceMsg = "CL3_EventHandler::provideData_ProductionDataEAF";
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
			std::string tlgName  = "L2_EAF_HEAT_REPORT";
			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::MsgStatus,1);

			std::string CrewCode = CSMC_DBData::unspecString;
			std::string CrewName = CSMC_DBData::unspecString;
			std::string SuperVisorName = CSMC_DBData::unspecString;
			std::string OptrName = CSMC_DBData::unspecString;

      if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ProdOrderNo,m_pPD_HEAT_DATA->getPRODORDERID_ACT(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::SteelGrade,m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::RouteCode,m_pPD_HEAT_DATA->getROUTECODE_ACT(1));

				if(m_pPD_HEAT_DATA->getLADLENO(1) != CSMC_DBData::unspecLong)
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::LadleNo,m_pPD_HEAT_DATA->getLADLENO(1));

				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ShiftCode,m_pPD_HEAT_DATA->getSHIFT_ID(1));

				CrewCode = m_pPD_HEAT_DATA->getCREW_ID(1);

				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::DepartureTime,m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1).assDate() );
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::TapSteelWeight,m_pPD_HEAT_DATA->getSTEELMASS(1));

				CDateTime ScrapChargeStartTime  = m_pPD_ACTION->GetFirstEventRevTime(HeatID, TreatID, Plant, DEF_GC_ACTION_DEF::ScrapAddition);
        CDateTime TapStartTime          = m_pPD_ACTION->GetFirstEventRevTime(HeatID, TreatID, Plant, DEF_GC_ACTION_DEF::TappingStart);
        CDateTime TapEndTime            = m_pPD_ACTION->GetFirstEventRevTime(HeatID, TreatID, Plant, DEF_GC_ACTION_DEF::TappingEnd);

				if(ScrapChargeStartTime != CSMC_DBData::unspecDate)
					m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ScrapChargeStartTime,ScrapChargeStartTime.assDate() );

				if(TapStartTime != CSMC_DBData::unspecDate)
					m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::TapStartTime,TapStartTime.assDate() );

				if(TapEndTime != CSMC_DBData::unspecDate)
					m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::TapEndTime,TapEndTime.assDate() );

				if(m_pPD_HEAT_DATA->getCOMMENTS(1) != CSMC_DBData::unspecString)
					m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Remarks,m_pPD_HEAT_DATA->getCOMMENTS(1));

				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::HeatStart,m_pPD_HEAT_DATA->getTREATSTART_ACT(1).assDate() );
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::HeatEnd,m_pPD_HEAT_DATA->getTREATEND_ACT(1).assDate() );
			}

			getCrewInformation(CrewCode,CrewName,SuperVisorName,OptrName);

      if ( m_pPDE_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::PowerOnDur,m_pPDE_HEAT_DATA->getPOWER_ON_DUR(1));	
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::OxygenCons,m_pPDE_HEAT_DATA->getBURNER_TOTALOXY(1) );						
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::BurnerGasCons,m_pPDE_HEAT_DATA->getBURNER_TOTALGAS(1));						
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ArgonCons,m_pPDE_HEAT_DATA->getTOTAL_AR_MOMENT(1));						
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::NitrogenCons,m_pPDE_HEAT_DATA->getTOTAL_N2_MOMENT(1));						
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::CarbonCons,m_pPDE_HEAT_DATA->getINJ_CARBON(1));		
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ElecEgyCons,m_pPDE_HEAT_DATA->getTOTAL_ELEC_EGY(1));

				if((m_pPDE_HEAT_DATA->getTAPMASS(1) != CSMC_DBData::unspecDouble) && (m_pPDE_HEAT_DATA->getTAPMASS(1) > 0.0))
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::TapSteelWeight,m_pPDE_HEAT_DATA->getTAPMASS(1));
      }

	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Shift_Mgr,CrewName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Shift_Inc,SuperVisorName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Eaf_Optr,OptrName);

			double ReturnSteelWeight = 0;
			if(m_pPD_HEAT_DATA_LIQADD->selectByOrderLiqAdd(HeatID, TreatID, Plant))
			{
				for(int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); i++)
				{
					if(m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(i) == DEF_GC_LADLE_TYPE::TeemingLadle) // steelWgt stored with 'TeemingLadle' during steel ladle charge at EAF, ladleNo is not important here
					{
						ReturnSteelWeight = ReturnSteelWeight + m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(i);
					}
				}
			}

			if(ReturnSteelWeight > 0.)
			{
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Used_ret_heat,"Y");
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::ReturnSteelWeight,ReturnSteelWeight);	
			}
			else
			{
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::Used_ret_heat,"N");
			}


			//B1
			double O2Cons = 0.;
			double O2Flow = 0.;
			if(m_pPDE_HEAT_DATA_BURN->select(HeatID, TreatID, Plant,DEF_GCE_BURNER::Burner_1,CSMC_DBData::unspecDate))
			{
				for(int i = 1; i <= m_pPDE_HEAT_DATA_BURN->getLastRow(); i++)
				{
					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Cons = O2Cons + m_pPDE_HEAT_DATA_BURN->getO2_CONS(i);

					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Flow = O2Flow + m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i);
				}
				O2Flow = O2Flow/m_pPDE_HEAT_DATA_BURN->getLastRow();

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B1_Oxygen_cons,O2Cons);
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B1_Oxygen_Flow,O2Flow);
			}
      
			//B2
			O2Cons = 0.;
			O2Flow = 0.;
			if(m_pPDE_HEAT_DATA_BURN->select(HeatID, TreatID, Plant,DEF_GCE_BURNER::Burner_2,CSMC_DBData::unspecDate))
			{
				for(int i = 1; i <= m_pPDE_HEAT_DATA_BURN->getLastRow(); i++)
				{
					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Cons = O2Cons + m_pPDE_HEAT_DATA_BURN->getO2_CONS(i);

					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Flow = O2Flow + m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i);
				}
				O2Flow = O2Flow/m_pPDE_HEAT_DATA_BURN->getLastRow();

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B2_Oxygen_cons,O2Cons);
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B2_Oxygen_Flow,O2Flow);
			}

			//B3
			O2Cons = 0.;
			O2Flow = 0.;
			if(m_pPDE_HEAT_DATA_BURN->select(HeatID, TreatID, Plant,DEF_GCE_BURNER::Burner_3,CSMC_DBData::unspecDate))
			{
				for(int i = 1; i <= m_pPDE_HEAT_DATA_BURN->getLastRow(); i++)
				{
					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Cons = O2Cons + m_pPDE_HEAT_DATA_BURN->getO2_CONS(i);

					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Flow = O2Flow + m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i);
				}
				O2Flow = O2Flow/m_pPDE_HEAT_DATA_BURN->getLastRow();

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B3_Oxygen_cons,O2Cons);
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B3_Oxygen_Flow,O2Flow);
			}

			//B4
			O2Cons = 0.;
			O2Flow = 0.;
			if(m_pPDE_HEAT_DATA_BURN->select(HeatID, TreatID, Plant,DEF_GCE_BURNER::Burner_4,CSMC_DBData::unspecDate))
			{
				for(int i = 1; i <= m_pPDE_HEAT_DATA_BURN->getLastRow(); i++)
				{
					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Cons = O2Cons + m_pPDE_HEAT_DATA_BURN->getO2_CONS(i);

					if(m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i) != CSMC_DBData::unspecDouble)
						O2Flow = O2Flow + m_pPDE_HEAT_DATA_BURN->getO2_FLOW(i);
				}
				O2Flow = O2Flow/m_pPDE_HEAT_DATA_BURN->getLastRow();

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B4_Oxygen_cons,O2Cons);
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_EAF_HEAT_REPORT::B4_Oxygen_Flow,O2Flow);
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





bool CL3_EventHandler::provideData_ProductionDataLF(CEventMessage& Event) 
{
	string exceMsg = "CL3_EventHandler::provideData_ProductionDataLF";
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
			std::string tlgName  = "L2_LF_HEAT_REPORT";
			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::MsgStatus,1);

			std::string CrewCode = CSMC_DBData::unspecString;
			std::string CrewName = CSMC_DBData::unspecString;
			std::string SuperVisorName = CSMC_DBData::unspecString;
			std::string OptrName = CSMC_DBData::unspecString;

      if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::ProdOrderNo,m_pPD_HEAT_DATA->getPRODORDERID_ACT(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::SteelGrade,m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1));
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::RouteCode,m_pPD_HEAT_DATA->getROUTECODE_ACT(1));

				if(m_pPD_HEAT_DATA->getLADLENO(1) != CSMC_DBData::unspecLong)
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::LadleNo,m_pPD_HEAT_DATA->getLADLENO(1));

				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::ShiftCode,m_pPD_HEAT_DATA->getSHIFT_ID(1));
				CrewCode = m_pPD_HEAT_DATA->getCREW_ID(1);

				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::TreatStart,m_pPD_HEAT_DATA->getTREATSTART_ACT(1).assDate() );
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::TreatEnd,m_pPD_HEAT_DATA->getTREATEND_ACT(1).assDate() );
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::LadleDepartTime,m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1).assDate() );
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::SteelWeight,m_pPD_HEAT_DATA->getSTEELMASS_START(1));
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::SlagWeight,m_pPD_HEAT_DATA->getSLAGMASS_START(1));

				if(m_pPD_HEAT_DATA->getCOMMENTS(1) != CSMC_DBData::unspecString)
					m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Remarks,m_pPD_HEAT_DATA->getCOMMENTS(1));
			}

			getCrewInformation(CrewCode,CrewName,SuperVisorName,OptrName);

      if ( m_pPDL_HEAT_DATA->select(HeatID, TreatID, Plant) )
      { 
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::LadleArrivalTime,m_pPDL_HEAT_DATA->getLADLE_ARRTIME(1).assDate() );

				if(m_pPDL_HEAT_DATA->getELEC_CONS(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::ElecEgyCons,m_pPDL_HEAT_DATA->getELEC_CONS(1));

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::N_Cons,m_pPDL_HEAT_DATA->getSTIRR_N2_CONS(1));
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::AR_Cons,m_pPDL_HEAT_DATA->getSTIRR_AR_CONS(1));

				if(m_pPDL_HEAT_DATA->getSTIRR_AR_DUR(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::StirrDur_Ar,m_pPDL_HEAT_DATA->getSTIRR_AR_DUR(1));

				if(m_pPDL_HEAT_DATA->getSTIRR_N2_DUR(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::StirrDur_N,m_pPDL_HEAT_DATA->getSTIRR_N2_DUR(1));

				if(m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::ARC_Dur,m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1));						
      }

			//last temp
			if(m_pPD_SAMPLE->selectLastHeatTemp(HeatID,TreatID,Plant))
			{
				for(int i = 1; i <= m_pPD_SAMPLE->getLastRow(); i++)
				{
					if(m_pPD_SAMPLE->getSAMPLENO(i) != CSMC_DBData::unspecLong  && m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE->getSAMPLE_COUNTER(i),DEF_GC_MEASUREMENT_NAME::Temp) )
					{
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::TempLast,m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));	
						break;
					}
				}
			}

	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Shift_Mgr,CrewName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Shift_Inc,SuperVisorName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Optr,OptrName);

			//DEF_GC_ACTION_DEF::PowerOn
			CDateTime revTime;
			long recCount = 0;
			if(m_pPD_ACTION->selectByActionNo(HeatID, TreatID, Plant, CSMC_DBData::unspecLong))
			{
				for(int i = 1; i <= m_pPD_ACTION->getLastRow(); i++)
				{
					revTime = m_pPD_ACTION->getREVTIME(i);
					if(m_pPD_ACTION->getACTIONNO(i) == DEF_GC_ACTION_DEF::PowerOff)
					{
						if(recCount == 0)
						{
							continue;
						}

						if(recCount == 1)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt1,revTime.assDate() );

						if(recCount == 2)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt2,revTime.assDate() );

						if(recCount == 3)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt3,revTime.assDate() );

						if(recCount == 4)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt4,revTime.assDate() );

						if(recCount == 5)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt5,revTime.assDate() );

						if(recCount == 6)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt6,revTime.assDate() );

						if(recCount == 7)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt7,revTime.assDate() );

						if(recCount == 8)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt8,revTime.assDate() );

						if(recCount == 9)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt9,revTime.assDate() );

						if(recCount == 10)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_End_Dt10,revTime.assDate() );
					}
					else if (m_pPD_ACTION->getACTIONNO(i) == DEF_GC_ACTION_DEF::PowerOn)
					{
						recCount = recCount + 1;

						if(recCount == 1)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt1,revTime.assDate() );

						if(recCount == 2)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt2,revTime.assDate() );

						if(recCount == 3)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt3,revTime.assDate() );

						if(recCount == 4)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt4,revTime.assDate() );

						if(recCount == 5)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt5,revTime.assDate() );

						if(recCount == 6)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt6,revTime.assDate() );

						if(recCount == 7)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt7,revTime.assDate() );

						if(recCount == 8)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt8,revTime.assDate() );

						if(recCount == 9)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt9,revTime.assDate() );

						if(recCount == 10)
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Lhf_Arc_St_Dt10,revTime.assDate() );
					}
					else
					{
						continue;
					}



				}
			}
    


			double ReturnSteelWeight = 0;
			if(m_pPD_HEAT_DATA_LIQADD->selectByOrderLiqAdd(HeatID, TreatID, Plant))
			{
				for(int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); i++)
				{
					if(m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i) != 1) //LiqAdd=1 means steelWgt stored during LF heatAnnouncement
					{
						ReturnSteelWeight = ReturnSteelWeight + m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(i);
					}
				}
			}

			if(ReturnSteelWeight > 0.)
			{
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Used_ret_heat,"Y");
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::ReturnSteelWeight,ReturnSteelWeight);	
			}
			else
			{
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Used_ret_heat,"N");
			}

			//1st temp
			if(m_pPD_SAMPLE->selectLastHeatTemp(HeatID,TreatID,Plant))
			{
				for(int i = m_pPD_SAMPLE->getLastRow(); i >= 1; i--)
				{
					if(m_pPD_SAMPLE->getSAMPLENO(i) != CSMC_DBData::unspecLong  && m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE->getSAMPLE_COUNTER(i),DEF_GC_MEASUREMENT_NAME::Temp) )
					{
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_LF_HEAT_REPORT::Initial_Temp,m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));	
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


bool CL3_EventHandler::provideData_ScheduleResponse(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_ScheduleResponse()";

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
      string tlgName = "L2_SCHEDULE_RESPONSE";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;

      string L3HeatId = m_pDM_Interface->getString(DataKey.c_str(), DATA::L3HeatId);
      string L3OrderId = m_pDM_Interface->getString(DataKey.c_str(), DATA::L3OrderId);
      long AckCode = m_pDM_Interface->getLong(DataKey.c_str(), DATA::AckCode);

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::L3_HeatId,L3HeatId ); 
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::L3_ProdOrder,L3OrderId ); 
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::AcceptCode,AckCode );
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::MsgStatus,1 );
    	  
      /*m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::Spare1,0 );
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::Spare2,0 );
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::Spare3,0 );
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::Spare4,0 );
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SCHEDULE_RESPONSE::Spare5,0 );*/

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

bool CL3_EventHandler::provideData_DelayReport(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_DelayReport()";

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
    //m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID, Plant);

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_DELAY_REPORT";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;
      long ActionFlag,DelayGroup;
      string DelayCode,DelayPlant,DelayDescr ;
      sDate DelayStart,DelayEnd;
      std::string OperatorComment;

      ActionFlag = m_pDM_Interface->getLong(DataKey.c_str(), DATA::Status); 

      DelayCode = m_pDM_Interface->getString(DataKey.c_str(), DATA::DelayCode);
      OperatorComment = m_pDM_Interface->getString(DataKey.c_str(), DATA::Comment);
      DelayStart = m_pDM_Interface->getDate(DataKey.c_str(), DATA::DelayStartDate );
      DelayEnd = m_pDM_Interface->getDate(DataKey.c_str(), DATA::DelayEndDate );
     
      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));

			if(ActionFlag == CSMC_DBData::unspecLong)
				ActionFlag = 1; //if delay comes from L1 

			m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::ActionFlag,ActionFlag);

			//assign L3 delay code from L1 delay code

      if(m_pGT_DELAY_CODE->select(Plant,DelayCode) && m_pGT_DELAY_CODE->getLastRow() > 0)
      {
        DelayGroup = m_pGT_DELAY_CODE->getGROUPNO(1); 

				if(DelayGroup == DEF_GC_DELAY_GROUP::Production)
					DelayGroup = 1;

				if(DelayGroup == DEF_GC_DELAY_GROUP::Maintenance)
					DelayGroup = 2;

				if(DelayGroup == DEF_GC_DELAY_GROUP::Mechanic)
					DelayGroup = 3;

				if(DelayGroup == DEF_GC_DELAY_GROUP::Electric)
					DelayGroup = 4;

				if(DelayGroup == DEF_GC_DELAY_GROUP::RED)
					DelayGroup = 5;

				if(DelayGroup == DEF_GC_DELAY_GROUP::CMD)
					DelayGroup = 6;

				if(DelayGroup == DEF_GC_DELAY_GROUP::Other)
					DelayGroup = 7;


        m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::DelayGroup,DelayGroup);
      }

			if(DelayCode != CSMC_DBData::unspecString)
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::DelayCode,DelayCode);

			if(OperatorComment != CSMC_DBData::unspecString)
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::DelayComments,OperatorComment);

			m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::StartTime,DelayStart);
			m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::EndTime,DelayEnd);
			m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_DELAY_REPORT::MsgStatus,1 );
	  
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

bool CL3_EventHandler::provideData_HeatStatus(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_HeatStatus()";

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

		if(Plant == DEF_GC_PLANT_DEF::HMD) 
		{
			if(m_pPP_HM->select(HeatID))
			{
				CustHeatID = m_pPP_HM->getHM_ID_CUST_PLAN(1);
				CustTreatID = "01";
				TreatID = "01";
			}
		}
		else
		{
	    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID,Plant);
		}
		
    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_HEAT_STATUS";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;
      string SteelGrade,ProdOrder;
      long LadleNo;
      sDate ExpectedTreatmentEnd;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::MsgStatus,1 );

			if(Plant == DEF_GC_PLANT_DEF::HMD )
			{
				long hmCounter = 0;
				if(m_pPP_HM->select(HeatID))
				{
					if(m_pPP_HM->getPRODORDERID(1) != CSMC_DBData::unspecString)
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::ProdOrderNo,m_pPP_HM->getPRODORDERID(1) );

					m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::ExpectedEndTime,m_pPP_HM->getTREATEND_PLAN(1).assDate() );  
				}

				if (m_pPDH_HM_DATA->select(HeatID, TreatID, Plant) )
				{ 
					hmCounter = m_pPDH_HM_DATA->getHOTMETAL_COUNTER(1);
				}
				if (m_pPD_HOT_METAL->select(hmCounter) )
				{ 
					m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::LadleNo,m_pPD_HOT_METAL->getLADLENO(1) ); 
				}


				if(m_pPDH_ACTION->select(HeatID, TreatID, Plant, CSMC_DBData::unspecLong))
				{
					if(DEF_GC_ACTION_DEF::HeatAnnounce == m_pPDH_ACTION->getACTIONNO(1))
					{
						if(m_pGC_HEAT_STATUS->select(DEF_GC_PLANT_DEF::HMD,DEF_GC_HEAT_STATUS::HeatAnnounced))
						{
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_L3(1) );	
						}						
					}

					if(DEF_GC_ACTION_DEF::HeatStart == m_pPDH_ACTION->getACTIONNO(1))
					{
						if(m_pGC_HEAT_STATUS->select(DEF_GC_PLANT_DEF::HMD,DEF_GC_HEAT_STATUS::TreatmentStart))
						{
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_L3(1) );	
						}						
					}
					if(DEF_GC_ACTION_DEF::HeatEnd == m_pPDH_ACTION->getACTIONNO(1))
					{
						if(m_pGC_HEAT_STATUS->select(DEF_GC_PLANT_DEF::HMD,DEF_GC_HEAT_STATUS::TreatmentEnd))
						{
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_L3(1) );	
						}						
					}
					if(DEF_GC_ACTION_DEF::Departure == m_pPDH_ACTION->getACTIONNO(1))
					{
						if(m_pGC_HEAT_STATUS->select(DEF_GC_PLANT_DEF::HMD,DEF_GC_HEAT_STATUS::LadleDeparture))
						{
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_L3(1) );	
						}						
					}
				}

			}
			else 
			{
				if(m_pPD_HEAT_DATA->select(HeatID,TreatID,Plant) && m_pPD_HEAT_DATA->getLastRow() > 0)
				{
					ProdOrder = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
					SteelGrade = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);
					LadleNo = m_pPD_HEAT_DATA->getLADLENO(1);

					if(m_pPD_HEAT_DATA->isNull("TREATEND_ACT",1))
						ExpectedTreatmentEnd = m_pPD_HEAT_DATA->getTREATEND_MOD(1).assDate();
					else
						ExpectedTreatmentEnd = m_pPD_HEAT_DATA->getTREATEND_ACT(1).assDate();

					m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::ProdOrderNo,ProdOrder );
					m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::SteelGrade,SteelGrade) ;

					if(LadleNo != CSMC_DBData::unspecLong)
						m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::LadleNo,LadleNo );

					m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::ExpectedEndTime,ExpectedTreatmentEnd );       
				}

				if( m_pPD_HEAT_PLANT_REF->select(HeatID, TreatID, Plant) )
				{
					if(m_pGC_HEAT_STATUS->select(m_pPD_HEAT_PLANT_REF->getSTATUSNO(1)))
					{
						m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_STATUS::HeatStatus,m_pGC_HEAT_STATUS->getHEATSTATNO_L3(1) );
					}
				}

			} //else
      

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

bool CL3_EventHandler::provideData_HeatReportMaterial(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_HeatReportMaterial()";

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

		if(Plant == DEF_GC_PLANT_DEF::HMD && m_pPP_HM->select(HeatID))
		{
			CustHeatID = m_pPP_HM->getHM_ID_CUST_PLAN(1);
			CustTreatID = "01";
			TreatID = "01";
		}
		else
		{
	    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID,Plant);
		}

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_HEAT_REPORT_MATERIAL";
      std::string DataKeyOut = "";
      CDateTime now;

			
			if(Plant == DEF_GC_PLANT_DEF::HMD)
			{
				  long UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(m_pGC_Plant_Container->getPlant(L2PlantID));
					std::string LimeCode = m_pGT_MAT_PURP->getRelatedMatCode( UnitGroupNo,DEF_GT_PURP::Lime);
					std::string MgCode =  m_pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP:: Magnesium );
					std::string CarbCode =  m_pGT_MAT_PURP->getRelatedMatCode(UnitGroupNo,DEF_GT_PURP::Carbide);

					double BlownMg              = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::MagnAmount);
					double BlownLime            = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::LimeAmount);
					double Blowncarbide         = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::CarbAmount);

					for(int i=1;i <= 3;i++)
					{
						string MatCode = "";
						double MatMass = 0.;

						if(i == 1) 
						{
							MatCode = CarbCode; //CaC2
							MatMass = Blowncarbide;
						}
						if(i == 2)
						{
								MatCode = LimeCode; //Lime
								MatMass = BlownLime;
						}
						if(i == 3)
						{
								MatCode = MgCode; //Mg
								MatMass = BlownMg;
						}

						if(MatMass == 0.) continue;

						DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

						m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::CreateTime,now.assDate() );
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::HeatId,CustHeatID);
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::TreatId,CustTreatID);
						m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MsgStatus,1 );

						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatCode,MatCode);
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatWeight,MatMass);
						m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatTime,now.assDate()); 
						m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatOrgin,"Powder");

						m_pTelcom_Interface->showContent(DataKeyOut,4);

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


					} //for..

			} //if(Plant == DEF_GC_PLANT_DEF::HMD)
			else 
			{
					string RecipeSource = m_pDM_Interface->getString(DataKey.c_str(), DATA::RecipeSource);	  
					long BatchStatus = m_pDM_Interface->getLong(DataKey.c_str(), DATA::RecipeStatus);	  
					seqBatch RecipeBatch = CIntfData::ToCORBAType(m_pDM_Interface->getBatch(DataKey.c_str(), DATA::RecipeContent));
					

					if(Event.getMessage() == EAF_EvMsg::evEAFCyclicMeasurement) //material for DynamicFeeding
					{
            log (" material for DynamicFeeding: ", 3);
						m_pDM_Interface = CDH_OUT_Task::getInstance()->getpDM_Interface(Event.getSender(),DM::PRODUCT);

						RecipeSource = "Bin";
						BatchStatus = DEF_GC_RECIPE_STATUS::Discharged;
						RecipeBatch = CIntfData::ToCORBAType(m_pDM_Interface->getBatch(ProductID.c_str(), DATA::MatFeedingData));
						if(CIntfData::getLength(RecipeBatch) == 0)
						{
							log (" length of material for DynamicFeeding is ZERO: ", 3);
						}
					}

					if(Event.getMessage() == EAF_EvMsg::evEAFHandleBasketDischarged)
					{
							//consider there are maximum 3 basket; only materials of last recipe will go to L3.
							for(int i = 3; i > 0 ;i--)
							{
								std::string ReceipeName = "";
								if( i == 3) ReceipeName = DEF_GC_RECIPE::Basket3;
								if( i == 2) ReceipeName = DEF_GC_RECIPE::Basket2;
								if( i == 1) ReceipeName = DEF_GC_RECIPE::Basket1;

								if(m_pPD_RECIPE_ENTRY->select(HeatID,TreatID,Plant,ReceipeName,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,DEF_GC_RECIPE_STATUS::Discharged,CSMC_DBData::unspecString))
								{
									for(int k = 1; k <= m_pPD_RECIPE_ENTRY->getLastRow(); k++)
									{
										  DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

										  std::string MatCode = m_pPD_RECIPE_ENTRY->getMAT_CODE(k);
										  double MatMass = m_pPD_RECIPE_ENTRY->getMATWEIGHT(k);
										  std::string MatOrgin = m_pPD_RECIPE_ENTRY->getSOURCE(k);

											m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::CreateTime,now.assDate() );
											m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
											m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::HeatId,CustHeatID);
											m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::TreatId,CustTreatID);
											m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MsgStatus,1 );

											m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatCode,MatCode);
											m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatWeight,MatMass);
											m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatTime,now.assDate()); 

											m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatOrgin,MatOrgin);
    		
											m_pTelcom_Interface->showContent(DataKeyOut,4);

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
									} //for..									

									break;
								} //if(m_pPD_RECIPE_ENTRY
							} //for..    

							return retval;
					} //if(Event.getMessage() == EAF_EvMsg::evEAFHandleBasketDischarged)

					if(Event.getMessage() == EAF_EvMsg::evEAFChargedHotMetal)
					{
							DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

							long UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant);
							std::string MatCode = m_pGT_MAT_PURP->getRelatedMatCode( UnitGroupNo,DEF_GT_PURP::HotMetal);
							double MatMass = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::SteelMassAct);//if hotmetal is not assigned then it takes HMWeight from L1 telegram 215

							if(m_pPD_HEAT_DATA_LIQADD->selectByOrderLiqAdd(HeatID, TreatID, Plant)) //if hotmetal is assigned then it ignore HMWeight from L1 telegram 215
							{
								MatMass = m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(1); //only last weight
							}

							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::CreateTime,now.assDate() );
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::HeatId,CustHeatID);
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::TreatId,CustTreatID);
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MsgStatus,1 );

							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatCode,MatCode);
							m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatWeight,MatMass);
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatTime,now.assDate()); 

							//m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatOrgin,"Liq");
    		
							m_pTelcom_Interface->showContent(DataKeyOut,4);

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

							return retval;
					} //if(Event.getMessage() == EAF_EvMsg::evEAFChargedHotMetal)

					if(DEF_GC_RECIPE_STATUS::Discharged == BatchStatus) //discharged
					{
						long seqLength = CIntfData::getLength(RecipeBatch);
						if (seqLength <= 0 ) return retval;

						for(int i=0;i< seqLength;i++)
						{
							sBatch sRecipeElement;
							CIntfData::getAt(sRecipeElement, RecipeBatch,i);
							string MatCode = sRecipeElement.MatCode;
							double MatMass = sRecipeElement.Mass;
							if(MatMass  <= 0. )
							{
								continue;
							}


							DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::CreateTime,now.assDate() );
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::HeatId,CustHeatID);
							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::TreatId,CustTreatID);
							m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MsgStatus,1 );

							m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatCode,MatCode);
							m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatWeight,MatMass);
							m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatTime,now.assDate()); 

							if(RecipeSource != CSMC_DBData::unspecString)
								m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::MatOrgin,RecipeSource);
    		
							if(Plant == DEF_GC_PLANT_DEF::LF)
							{
								if(m_pPD_ACTION->selectByActionNo(HeatID, TreatID, Plant, DEF_GC_ACTION_DEF::PowerOn))
								{
									m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HEAT_REPORT_MATERIAL::Arc_Ctr,m_pPD_ACTION->getLastRow() );
								}
							}

							m_pTelcom_Interface->showContent(DataKeyOut,4);

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
						} //for...
				} //if(DEF_GC_RECIPE_STATUS::Discharged == BatchStatus) //discharged

			} //else


    }//if (m_pTelcom_Interface && m_pDM_Interface)

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


bool CL3_EventHandler::provideData_ProductionDataHMD(CEventMessage& Event) 
{
	string exceMsg = "CL3_EventHandler::provideData_ProductionDataHMD";
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
		TreatID = "01";
		CustTreatID = "01";

		if(m_pPP_HM->select(HeatID))
		{
			CustHeatID = m_pPP_HM->getHM_ID_CUST_PLAN(1);
			OrderId = m_pPP_HM->getPRODORDERID(1);
		}

    if (m_pTelcom_Interface && m_pDM_Interface)
    {
			std::string tlgName  = "L2_HMD_HEAT_REPORT";
			std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);
			CDateTime now;

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::MsgStatus,1);

			if(OrderId != CSMC_DBData::unspecString)
				m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::ProdOrderNo,OrderId);
			
			long hmCounter = 0;

			std::string CrewCode = CSMC_DBData::unspecString;
			std::string CrewName = CSMC_DBData::unspecString;
			std::string SuperVisorName = CSMC_DBData::unspecString;
			std::string OptrName = CSMC_DBData::unspecString;

      if (m_pPDH_HM_DATA->select(HeatID, TreatID, Plant) )
      { 
				hmCounter = m_pPDH_HM_DATA->getHOTMETAL_COUNTER(1);
	      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::ShiftCode,m_pPDH_HM_DATA->getSHIFT_CODE(1));
				CrewCode = m_pPDH_HM_DATA->getCREW_CODE(1);

				if((m_pPDH_HM_DATA->isNull("HM_WEIGHT_END",1)) || (m_pPDH_HM_DATA->getHM_WEIGHT_END(1) == 0))
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::HMWeight,m_pPDH_HM_DATA->getHM_WEIGHTSTART_MOD(1));
				else
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::HMWeight,m_pPDH_HM_DATA->getHM_WEIGHT_END(1));

				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Initial_S,m_pPDH_HM_DATA->getAIM_S_GRADE(1));
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Aim_S,m_pPDH_HM_DATA->getAIM_S_OPER(1));

				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::StartTime,m_pPDH_HM_DATA->getTREATSTART_ACT(1).assDate());
				m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::EndTime,m_pPDH_HM_DATA->getTREATEND_ACT(1).assDate());

				if(m_pPDH_HM_DATA->getTEMP_INITIAL(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::TempInitial,m_pPDH_HM_DATA->getTEMP_INITIAL(1));

				if(m_pPDH_HM_DATA->getHM_TEMP_END(1) != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::TempLast,m_pPDH_HM_DATA->getHM_TEMP_END(1));

				if(m_pPDH_HM_DATA->getCOMMENTS(1) != CSMC_DBData::unspecString)
		      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Remarks,m_pPDH_HM_DATA->getCOMMENTS(1));
			}

			getCrewInformation(CrewCode,CrewName,SuperVisorName,OptrName);

      if (m_pPD_HOT_METAL->select(hmCounter) )
			{
	      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::LadleNo,m_pPD_HOT_METAL->getLADLENO(1));
			}
			
			if(m_pPD_SAMPLE->selectByType_HMD(HeatID,TreatID,Plant,PlantNo,DEF_GC_MEASUREMENT_TYPE::HM) && m_pPD_SAMPLE->getLastRow() > 0)
			{
				for(int i = 1; i <= m_pPD_SAMPLE->getLastRow(); i++)
				{
					if(m_pPD_SAMPLE_ENTRY->select(m_pPD_SAMPLE->getSAMPLE_COUNTER(i),DEF_GC_MEASUREMENT_NAME::S) && m_pPD_SAMPLE_ENTRY->getLastRow() > 0)
					{
						m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Final_S,m_pPD_SAMPLE_ENTRY->getMEASVALUE(1));
						break;
					}
				}
			}

			
      if (m_pHDH_EQUIP_COUNTER->select(HeatID, TreatID, Plant,CSMC_DBData::unspecLong,"INJ_LANCE","HEATS") && m_pHDH_EQUIP_COUNTER->getLastRow() > 0)
			{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::InjectionLanceLife,m_pHDH_EQUIP_COUNTER->getCOUNTER_VALUE(1));
			}

			if (m_pHDH_EQUIP_COUNTER->select(HeatID, TreatID, Plant,CSMC_DBData::unspecLong,"SRM_BLADE","HEATS") && m_pHDH_EQUIP_COUNTER->getLastRow() > 0)
			{
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::SrmPlateLife,m_pHDH_EQUIP_COUNTER->getCOUNTER_VALUE(1));
			}

	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Shift_Mgr,CrewName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Shift_Inc,SuperVisorName);
	    m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_HMD_HEAT_REPORT::Hmds_Optr,OptrName);

                                                                                                                                            
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



bool CL3_EventHandler::provideData_sampleTaken(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_sampleTaken()";

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

		long smplNo;

		if(Plant == DEF_GC_PLANT_DEF::HMD && m_pPP_HM->select(HeatID))
		{
			CustHeatID = m_pPP_HM->getHM_ID_CUST_PLAN(1);
			CustTreatID = "01";
			TreatID = "01";

			//in future get sampleNo from DATA::SampleNo like other plants
			if ( Event.getMessage() == HMD_EvMsg::evHMDHotMetalSampleTaken )
			{
				if(m_pPD_SAMPLE->selectByType_HMD(HeatID,TreatID,Plant,PlantNo,DEF_GC_MEASUREMENT_TYPE::HM))
				{
					smplNo = m_pPD_SAMPLE->getSAMPLENO(1);
				}
			}
			else
			{
				if(m_pPD_SAMPLE->selectByType_HMD(HeatID,TreatID,Plant,PlantNo,DEF_GC_MEASUREMENT_TYPE::Slag))
				{
					smplNo = m_pPD_SAMPLE->getSAMPLENO(1);
				}
			}

		}
		else
		{
	    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID,Plant);
		}
		
    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_SAMPLE_TAKEN";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;
			long smplType;

			if ( (  Event.getMessage() == EAF_EvMsg::evEAFSteelSampleTaken ) || (Event.getMessage() == LF_EvMsg::evLFSteelSampleTaken) || (Event.getMessage() == HMD_EvMsg::evHMDHotMetalSampleTaken) )
				smplType = 1;
			else
				smplType = 2;
   			
			if(Plant != DEF_GC_PLANT_DEF::HMD)
			{
				smplNo = m_pDM_Interface->getLong(DataKey.c_str(), DATA::SampleNo);
			}

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::MsgStatus,1 );

      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::SampleNo,smplNo );
      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::SampleTakenTime,now.assDate() );

      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::SampleCode,getCustSampleCode(CustHeatID,Plant,PlantNo,smplNo));
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_SAMPLE_TAKEN::SampleType,smplType );
      
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


bool CL3_EventHandler::provideData_temperatureTaken(CEventMessage &Event)
{
  string exceMsg = "CL3_EventHandler::provideData_temperatureTaken()";

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

		if(Plant == DEF_GC_PLANT_DEF::HMD && m_pPP_HM->select(HeatID))
		{
			CustHeatID = m_pPP_HM->getHM_ID_CUST_PLAN(1);
			CustTreatID = "01";
			TreatID = "01";
		}
		else
		{
	    m_pHeatDataConverter->getCustHeatData( HeatID, TreatID, CustHeatID, CustTreatID,Plant);
		}
		
    if (m_pTelcom_Interface && m_pDM_Interface)
    {
      string tlgName = "L2_TEMPERATURE_TAKEN";
      std::string DataKeyOut = m_pTelcom_Interface->generateDataKey(tlgName);

      CDateTime now;

			long smplType = m_pDM_Interface->getLong(DataKey.c_str(), DATA::SampleType);
			double measTemp = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasTemp);
			double measAlConc = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasAlConc) ; 
			double measO2Conc = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasO2Conc); 
			double measCarbonConc = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasCarbonConc);

      m_pTelcom_Interface->setDate(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::CreateTime,now.assDate() );
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::PlantUnit,Plant.substr(0,1) + CDataConversion::LongToString(PlantNo));
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::HeatId,CustHeatID);
      m_pTelcom_Interface->setString(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::TreatId,CustTreatID);
      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::MsgStatus,1 );
      
			if(measTemp != CSMC_DBData::unspecDouble)
				m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::Temp,measTemp );

			if(smplType == DEF_GC_MEASUREMENT_TYPE::Temp)
			{
	      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::MeasType,1 );
			}
			else //SARS: if temp or celox entered from HMI then it will be always celox because there is no provision in HMI like MeasType in telegram. Also note that HMDS has no celox measurement as per telegram. So . in HMDS only temp will be stored
			{
	      m_pTelcom_Interface->setLong(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::MeasType,2 );
				if(measAlConc != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::ConcAl,measAlConc * 10000. ); //%->ppm

				if(measO2Conc != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::ConcO2,measO2Conc * 10000.); //%->ppm

				if(measCarbonConc != CSMC_DBData::unspecDouble)
					m_pTelcom_Interface->setDouble(DataKeyOut.c_str(),Telegram_L2_TEMPERATURE_TAKEN::ConcC,measCarbonConc * 10000.); //%->ppm
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

string CL3_EventHandler::getCustSampleCode(const std::string& CustHeatID, const std::string& Plant, long PlantNo,long SampleNo)
{
	  std::stringstream smplCode ;
		smplCode.fill('0');
		CDateTime now;
		std::string smplNo;

		if(SampleNo == 1) smplNo = 'A';
		if(SampleNo == 2) smplNo = 'B';
		if(SampleNo == 3) smplNo = 'C';
		if(SampleNo == 4) smplNo = 'D';
		if(SampleNo == 5) smplNo = 'E';
		if(SampleNo == 6) smplNo = 'F';
		if(SampleNo == 7) smplNo = 'G';
		if(SampleNo == 8) smplNo = 'H';
		if(SampleNo == 9) smplNo = 'I';
		if(SampleNo == 10) smplNo = 'J';
		if(SampleNo == 11) smplNo = 'K';
		if(SampleNo == 12) smplNo = 'L';
		if(SampleNo == 13) smplNo = 'M';
		if(SampleNo == 14) smplNo = 'N';
		if(SampleNo == 15) smplNo = 'O';
		if(SampleNo == 16) smplNo = 'P';
		if(SampleNo == 17) smplNo = 'Q';
		if(SampleNo == 18) smplNo = 'R';
		if(SampleNo == 19) smplNo = 'S';
		if(SampleNo == 20) smplNo = 'T';
		if(SampleNo == 21) smplNo = 'U';
		if(SampleNo == 22) smplNo = 'V';
		if(SampleNo == 23) smplNo = 'W';
		if(SampleNo == 24) smplNo = 'X';
		if(SampleNo == 25) smplNo = 'Y';
		if(SampleNo == 26) smplNo = 'Z';

		if(Plant == DEF_GC_PLANT_DEF::HMD )
		{				 
			smplCode << "HH" << PlantNo << std::setw(2) << CDataConversion::IntToString(now.getYear()).substr(2) << std::setw(5) << CustHeatID << smplNo; 
		}
		else if(Plant == DEF_GC_PLANT_DEF::EAF )
		{
			smplCode << "TA" << PlantNo << std::setw(5) << CustHeatID << smplNo; 
		}
		else if(Plant == DEF_GC_PLANT_DEF::LF )
		{
			smplCode << "TL" << PlantNo << std::setw(5) << CustHeatID << smplNo; 
		}

	  return smplCode.str();
}

	void CL3_EventHandler::getCrewInformation(const std::string& CrewCode, std::string& CrewName, std::string& SuperVisorName,std::string& OptrName)
	{
			if(CrewCode != CSMC_DBData::unspecString && m_pPP_MEMBER_CREW_ASSIGNMENT->select(CrewCode,CSMC_DBData::unspecString))
			{
				 if(m_pGC_CREW_CAT->select(CrewCode))
				 {
					 CrewName = m_pGC_CREW_CAT->getCREW_DESC(1);
				 }

					for(int i = 1; i <= m_pPP_MEMBER_CREW_ASSIGNMENT->getLastRow(); i++)
					{
						std::string MemberID = m_pPP_MEMBER_CREW_ASSIGNMENT->getMEMBER_ID(i);
						if(MemberID != CSMC_DBData::unspecString && m_pGC_MEMBER_CAT->select(MemberID))
						{
							if(m_pGC_MEMBER_CAT->getMEMBER_ROLE(1) == DEF_GC_MEMBER_ROLE_CAT::Supervisor)
								SuperVisorName = m_pGC_MEMBER_CAT->getMEMBER_NAME(1);

							if(m_pGC_MEMBER_CAT->getMEMBER_ROLE(1) == DEF_GC_MEMBER_ROLE_CAT::Operator)
								OptrName = m_pGC_MEMBER_CAT->getMEMBER_NAME(1);
						}
					}
			}

	}



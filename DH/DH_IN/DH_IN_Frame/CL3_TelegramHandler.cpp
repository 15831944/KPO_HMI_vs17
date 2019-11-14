// Copyright (C) 2006 SMS Demag AG

#include "Telcom_in_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CDataConversion.h"
#include "CIntfData.h"
#include "CTreatID.h"


#include "CDH_IN_Task.h"

#include "CPP_ORDER.h" 
#include "CPP_ORDER_SINGLE_AIMS.h" 
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPD_RECIPE.h"
#include "CPDE_HEAT_DATA.h"
#include "CPD_HEAT_DATA.h"
#include "CGT_DELAY_CODE.h"

#include "CGT_GRADE.h"
#include "CGT_GRADE_ANL.h"
#include "CGT_GRADE_SINGLE_AIMS.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CGT_MAT.h"
#include "CGT_MAT_CHEM.h"
#include "CGT_PURP.h"
#include "CGT_MAT_PURP.h"
#include "CGC_Plant_Container.h"
#include "CGC_Plantgroup_Container.h"
#include "CPD_HEAT_PLANT_REF.h"

#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_HEAT_STATUS.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_GRADE_ANL.h"
#include "DEF_GC_PRODPRAC_DEF.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_DELAY_GROUP.h"
#include "CHeatStatusContainer.h"
#include "CL3_TelegramHandler.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "CPP_HM.h"
#include "DEF_GC_SAMPLELOC.h"
#include "DEF_GC_THERM_STAT.h"
#include "DEF_GC_LADLE_PARTS.h"

#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CHD_SAMPLE.h"
#include "CHD_SAMPLE_ENTRY.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_HOT_METAL.h"
#include "CPDH_HM_DATA.h"
#include "CGC_LADLE_DEF.h"
#include "CPD_LADLE.h"
#include "CPD_LADLE_LIFE_DATA.h"


//##ModelId=4582CFD50355
CL3_TelegramHandler::CL3_TelegramHandler()
{
  try
  {
    cCBS_StdConnection* pConnection = CDH_IN_Task::getInstance()->getStdConnection();

    if (pConnection)
    {
      long PlantNo  = 1;
      std::string Plant = DEF_GC_PLANT_DEF::L3;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);

      m_pGT_MAT               = new CGT_MAT(pConnection);
      m_pGT_MAT_CHEM          = new CGT_MAT_CHEM(pConnection);
      m_pGC_Plant_Container   = new CGC_Plant_Container(pConnection, Plant);
      m_pHeatDataConverter    = new CHeatDataConverter(pConnection);
      m_pPP_ORDER             = new CPP_ORDER(pConnection);
      m_pPP_ORDER_SINGLE_AIMS = new CPP_ORDER_SINGLE_AIMS(pConnection);
      m_pPP_HEAT              = new CPP_HEAT(pConnection);
      m_pPP_HEAT_PLANT        = new CPP_HEAT_PLANT(pConnection);
      m_pPD_RECIPE            = new CPD_RECIPE(pConnection);
      m_pPD_HEAT_DATA         = new CPD_HEAT_DATA(pConnection);
      m_pPDE_HEAT_DATA        = new CPDE_HEAT_DATA(pConnection);
      m_pGT_DELAY_CODE        = new CGT_DELAY_CODE(pConnection);
      m_pGT_GRADE             = new CGT_GRADE(pConnection);
      m_pGT_GRADE_ANL         = new CGT_GRADE_ANL(pConnection);
      m_pGT_GRADE_SINGLE_AIMS = new CGT_GRADE_SINGLE_AIMS(pConnection);
      m_pGT_GRADE_PRODPRAC    = new CGT_GRADE_PRODPRAC(pConnection);
      m_pGT_PURP              = new CGT_PURP(pConnection);
      m_pGT_MAT_PURP          = new CGT_MAT_PURP(pConnection);
      m_pPD_HEAT_PLANT_REF    = new CPD_HEAT_PLANT_REF(pConnection);
      m_pGT_GRADE_SAMPLE_FLAG = new CGT_GRADE_SAMPLE_FLAG(pConnection);
      m_pPD_HEAT_REF          = new CPD_HEAT_REF(pConnection);
			m_pPP_HM                = new CPP_HM(pConnection);

			m_pGC_LADLE_DEF         = new CGC_LADLE_DEF(pConnection);
			m_pPD_LADLE							= new CPD_LADLE(pConnection);
			m_pPD_LADLE_LIFE_DATA   = new CPD_LADLE_LIFE_DATA(pConnection);

			m_pPDH_HM_DATA          = new CPDH_HM_DATA(pConnection);

      m_pHeatStatusContainer  = new CHeatStatusContainer(pConnection);
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CL3_TelegramHandler","No database connection");
    }


    // fill map for steel elements
    m_SteelElementMap.clear();
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(1,std::pair<std::string,double>("C",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(2,std::pair<std::string,double>("Si",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(3,std::pair<std::string,double>("Mn",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(4,std::pair<std::string,double>("P",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(5,std::pair<std::string,double>("S",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(6,std::pair<std::string,double>("Al",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(7,std::pair<std::string,double>("Al_S",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(8,std::pair<std::string,double>("Cu",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(9,std::pair<std::string,double>("Cr",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(10,std::pair<std::string,double>("Mo",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(11,std::pair<std::string,double>("Ni",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(12,std::pair<std::string,double>("V",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(13,std::pair<std::string,double>("Ti",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(14,std::pair<std::string,double>("Nb",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(15,std::pair<std::string,double>("Ca",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(16,std::pair<std::string,double>("Co",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(17,std::pair<std::string,double>("Pb",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(18,std::pair<std::string,double>("W",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(19,std::pair<std::string,double>("Mg",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(20,std::pair<std::string,double>("Ce",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(21,std::pair<std::string,double>("B",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(22,std::pair<std::string,double>("As",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(23,std::pair<std::string,double>("Sn",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(24,std::pair<std::string,double>("Bi",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(25,std::pair<std::string,double>("Sb",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(26,std::pair<std::string,double>("Zr",1)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(27,std::pair<std::string,double>("O2",0.0001)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(28,std::pair<std::string,double>("N2",0.0001)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(29,std::pair<std::string,double>("H2",0.0001)));
    m_SteelElementMap.insert(std::pair<long,std::pair<std::string,double> >(30,std::pair<std::string,double>("Zn",1)));
    

    // fill map for slag components
    m_SlagElementMap.clear();
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(1,std::pair<std::string,double>("CaO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(2,std::pair<std::string,double>("SiO2",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(3,std::pair<std::string,double>("P2O5",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(4,std::pair<std::string,double>("FeO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(5,std::pair<std::string,double>("Fe2O3",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(6,std::pair<std::string,double>("Fe3O4",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(7,std::pair<std::string,double>("S_X",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(8,std::pair<std::string,double>("Al2O3",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(9,std::pair<std::string,double>("MgO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(10,std::pair<std::string,double>("MnO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(11,std::pair<std::string,double>("Cr2O3",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(12,std::pair<std::string,double>("MoO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(13,std::pair<std::string,double>("NiO",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(14,std::pair<std::string,double>("V2O5",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(15,std::pair<std::string,double>("TiO2",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(16,std::pair<std::string,double>("TiFe",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(17,std::pair<std::string,double>("CaC2",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(18,std::pair<std::string,double>("CaF2",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(19,std::pair<std::string,double>("CaS",1)));
    m_SlagElementMap.insert(std::pair<long,std::pair<std::string,double> >(20,std::pair<std::string,double>("Fe_X",1)));

  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CL3_TelegramHandler","");
    throw;
  }
}

//##ModelId=4582CFDC00F1
CL3_TelegramHandler::~CL3_TelegramHandler()
{
  if (m_pGT_MAT)                { delete m_pGT_MAT; m_pGT_MAT = 0;}
  if (m_pGT_MAT_CHEM)           { delete m_pGT_MAT_CHEM; m_pGT_MAT_CHEM = 0;}
  if (m_pGC_Plant_Container)    { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0;}
  if (m_pHeatDataConverter)     { delete m_pHeatDataConverter; m_pHeatDataConverter = 0;}
  if (m_pPP_ORDER)              { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPP_ORDER_SINGLE_AIMS)  { delete m_pPP_ORDER_SINGLE_AIMS; m_pPP_ORDER_SINGLE_AIMS = 0;}
  if (m_pPP_HEAT)               { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT)         { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0; }
  if (m_pPD_RECIPE)             { delete m_pPD_RECIPE; m_pPD_RECIPE = 0;}
  if (m_pPD_HEAT_DATA)          { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
  if (m_pPDE_HEAT_DATA)         { delete m_pPDE_HEAT_DATA; m_pPDE_HEAT_DATA = 0;}
  if (m_pGT_DELAY_CODE)         { delete m_pGT_DELAY_CODE; m_pGT_DELAY_CODE = 0;}
  if (m_pGT_GRADE)              { delete m_pGT_GRADE; m_pGT_GRADE = 0;  }
  if (m_pGT_GRADE_ANL)          { delete m_pGT_GRADE_ANL; m_pGT_GRADE_ANL = 0;  }
  if (m_pGT_GRADE_SINGLE_AIMS)  { delete m_pGT_GRADE_SINGLE_AIMS; m_pGT_GRADE_SINGLE_AIMS = 0;  }
  if (m_pGT_GRADE_PRODPRAC)     { delete m_pGT_GRADE_PRODPRAC; m_pGT_GRADE_PRODPRAC = 0;  }
  if (m_pGT_PURP)               { delete m_pGT_PURP; m_pGT_PURP = 0;  }
  if (m_pGT_MAT_PURP)           { delete m_pGT_MAT_PURP; m_pGT_MAT_PURP = 0;  }
  if (m_pPD_HEAT_PLANT_REF)     { delete m_pPD_HEAT_PLANT_REF; m_pPD_HEAT_PLANT_REF = 0;}
  if (m_pGT_GRADE_SAMPLE_FLAG)  { delete m_pGT_GRADE_SAMPLE_FLAG; m_pGT_GRADE_SAMPLE_FLAG = 0;}
  if (m_pPD_HEAT_REF)           { delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0;}
  if (m_pPP_HM)									{ delete m_pPP_HM; m_pPP_HM = 0;}

  if (m_pGC_LADLE_DEF)          { delete m_pGC_LADLE_DEF; m_pGC_LADLE_DEF = 0;}
  if (m_pPD_LADLE)							{ delete m_pPD_LADLE; m_pPD_LADLE = 0;}
  if (m_pPD_LADLE_LIFE_DATA)		{ delete m_pPD_LADLE_LIFE_DATA; m_pPD_LADLE_LIFE_DATA = 0;}
  if (m_pPDH_HM_DATA)		        { delete m_pPDH_HM_DATA; m_pPDH_HM_DATA = 0;}
	

  if (m_pHeatStatusContainer)   { delete m_pHeatStatusContainer;m_pHeatStatusContainer = 0;}
}


CDateTime CL3_TelegramHandler::FromTelegramFormat14(std::string strDateTime)
{
  CDateTime DateTime = CSMC_DBData::unspecDate;

  if ( !strDateTime.empty() && strDateTime.length() >= 13 )
  {
    long year     = CDataConversion::StringToLong(strDateTime.substr(0  ,4));
    long month    = CDataConversion::StringToLong(strDateTime.substr(4  ,2));
    long day      = CDataConversion::StringToLong(strDateTime.substr(6  ,2));
    long hour     = CDataConversion::StringToLong(strDateTime.substr(8  ,2));
    long minute   = CDataConversion::StringToLong(strDateTime.substr(10 ,2));
    long second   = CDataConversion::StringToLong(strDateTime.substr(12 ,2));
    long millisec = 0; // not transferred

    CDateTime NewDateTime(year,month,day,hour,minute,second,millisec);

    DateTime= NewDateTime;
  }

  return DateTime;
}



bool CL3_TelegramHandler::doOnComplete(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  std::stringstream strFunction;
  std::stringstream strAction;

  try
  {
    strFunction << "CL3_TelegramHandler::doOnComplete;";
    strFunction <<" TlgName:"<<TlgName;

    EventMessageVector.clear()  ;

    if(TlgName == "L3_STEELGRADES")
      RetValue =  DoProcessSteelGradeCodeDefinition(Key,TlgName); 
    else if(TlgName == "L3_HEAT_SCHEDULE")
      RetValue =  DoProcessHeatSchedule(Key,TlgName); 
    else if(TlgName == "L3_HM_LADLE")
      RetValue =  DoProcessHMLadle(Key,TlgName); 
    else if(TlgName == "L3_MATERIAL_CODES")
      RetValue =  DoProcessMaterialCodeDefinition(Key,TlgName); 
    else if(TlgName == "L3_DELAY_CODES")
      RetValue =  DoProcessDelayCodeDefinition(Key,TlgName); 
    else if(TlgName == "L3_ANALYSIS_STEEL")
      RetValue =  DoProcessSteelAnalysis(Key,TlgName); 
    else if(TlgName == "L3_ANALYSIS_SLAG")
      RetValue =  DoProcessSlagAnalysis(Key,TlgName);     
    else if(TlgName == "L3_TEEMING_LADLE")
      RetValue =  DoProcessTeemingLadle(Key,TlgName);     		
    else if(TlgName == "L3_STEELGRADE_CHANGE")
      RetValue =  DoProcessSteelGradeChange(Key,TlgName);     		
    else if(TlgName == "L3_LADLE_CHANGE")
      RetValue =  DoProcessLadleChange(Key,TlgName);     		
    else if(TlgName == "L3_ALIVE")
      return RetValue;     		
    else 
    {
      strFunction << " is unknown";

      RetValue = false;
    }

    if( RetValue == false )
    {
      log( "ERROR: Can not handle telegram " + TlgName ,1 );
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
    }
    strAction << "Invoke telegram handler for telegram :";
    strAction<< TlgName;
  }
  catch(...)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", strFunction.str().c_str(),strAction.str().c_str()); 
    RetValue = false;
  }

  if( RetValue == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),strFunction.str().c_str());
  }

  return RetValue;
}






bool CL3_TelegramHandler::DoProcessSteelGradeCodeDefinition(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::<DoProcessSteelGradeCodeDefinition";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      

  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);


      long ActionFlag	                = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_STEELGRADES::ActionFlag);
      std::string SteelGradeCode      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADES::SteelGradeCode);
      std::string SteelGradeDesc   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADES::SteelGradeDesc);

      long LiquidusTemp               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_STEELGRADES::LiquidusTemp);
			double EAF_Aim_Temp            = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_STEELGRADES::EAF_Aim_Temp);
			double LF_Aim_Temp            = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_STEELGRADES::LF_Aim_Temp);
			double CCM_Aim_Temp            = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_STEELGRADES::CCM_Aim_Temp);

		  seqAnalysis SeqAnalysisEAFAim = handleGradeAnalysis(Key,"EAF_Aim_","Steel");
      seqAnalysis SeqAnalysisEAFMin  = handleGradeAnalysis(Key,"EAF_Min_","Steel");
      seqAnalysis SeqAnalysisEAFMax  = handleGradeAnalysis(Key,"EAF_Max_","Steel");

		  seqAnalysis SeqAnalysisLFAim  = handleGradeAnalysis(Key,"LF_Aim_","Steel");
      seqAnalysis SeqAnalysisLFMin  = handleGradeAnalysis(Key,"LF_Min_","Steel");
      seqAnalysis SeqAnalysisLFMax =  handleGradeAnalysis(Key,"LF_Max_","Steel");

			seqAnalysis SeqAnalysisCCMAim  = handleGradeAnalysis(Key,"CCM_Aim_","Steel");
      seqAnalysis SeqAnalysisCCMMin = handleGradeAnalysis(Key,"CCM_Min_","Steel");
      seqAnalysis SeqAnalysisCCMMax = handleGradeAnalysis(Key,"CCM_Max_","Steel");


      //********    Convert and check telegram data  ***********************************************************       
      RetValue = RetValue && setErrorOnValidation(Key,10202,TlgName,Telegram_L3_STEELGRADES::ActionFlag,               ActionFlag,               1,3);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10207,TlgName,Telegram_L3_STEELGRADES::SteelGradeCode,           SteelGradeCode);
      //RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10208,TlgName,Telegram_L3_STEELGRADES::SteelGradeDesc,        SteelGradeDesc);
			if ( SteelGradeDesc == DEF::Inv_String || SteelGradeDesc.empty() )
			{
				SteelGradeDesc = SteelGradeCode;
			}

      if ( RetValue )
      {
        long State = DEF::Inv_Long;

        if ( ActionFlag == 1 )
        {
          State = DEF_GEN_STATES::New;
        }
        else if ( ActionFlag == 2 )
        {
          State = DEF_GEN_STATES::Update;
        }
        else if ( ActionFlag == 3 )
        {
          State = DEF_GEN_STATES::Delete;
        }
      
          //********    Define Event *******************************************************************************
          EventMessageVector.push_back(L3_EvMsg::evL3SteelGradeCodeDefinitionUpdate);

          //********    Write data base data  ***********************************************************************
          if ( State == DEF_GEN_STATES::Delete )
          {
            RetValue = RetValue && m_pGT_GRADE->deleteGrade(SteelGradeCode);

            if ( RetValue )
            {
              m_pGT_GRADE->commit();
            }
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DBWriteError(sMessage, "", "GT_GRADE","cannot delete grade");

              m_pGT_GRADE->rollback();

              handleErrorCode(Key, 10220);
            }
          }
          else if ( State == DEF_GEN_STATES::Update || 
                    State == DEF_GEN_STATES::New      )
          {
            RetValue = RetValue && m_pGT_GRADE->writeGrade(SteelGradeCode, SteelGradeDesc, SteelGradeDesc, LiquidusTemp,"L3",CSMC_DBData::unspecLong, Now, false);

            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::EAF, SteelGradeCode, DEF_GC_GRADE_ANL::Aim, SeqAnalysisEAFAim, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::EAF, SteelGradeCode, DEF_GC_GRADE_ANL::Min, SeqAnalysisEAFMin, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::EAF, SteelGradeCode, DEF_GC_GRADE_ANL::Max, SeqAnalysisEAFMax, false);

            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::LF, SteelGradeCode, DEF_GC_GRADE_ANL::Aim, SeqAnalysisLFAim, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::LF, SteelGradeCode, DEF_GC_GRADE_ANL::Min, SeqAnalysisLFMin, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::LF, SteelGradeCode, DEF_GC_GRADE_ANL::Max, SeqAnalysisLFMax, false);

            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::CCS, SteelGradeCode, DEF_GC_GRADE_ANL::Aim, SeqAnalysisCCMAim, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::CCS, SteelGradeCode, DEF_GC_GRADE_ANL::Min, SeqAnalysisCCMMin, false);
            RetValue = RetValue && m_pGT_GRADE_ANL->writeAnalysis(DEF_GC_PLANT_DEF::CCS, SteelGradeCode, DEF_GC_GRADE_ANL::Max, SeqAnalysisCCMMax, false);

            RetValue = RetValue && m_pGT_GRADE_SINGLE_AIMS->writeAims(DEF_GC_PLANT_DEF::EAF, SteelGradeCode, EAF_Aim_Temp, 0, false);
            RetValue = RetValue && m_pGT_GRADE_SINGLE_AIMS->writeAims(DEF_GC_PLANT_DEF::LF, SteelGradeCode, LF_Aim_Temp, 0, false);
            RetValue = RetValue && m_pGT_GRADE_SINGLE_AIMS->writeAims(DEF_GC_PLANT_DEF::CCS, SteelGradeCode, CCM_Aim_Temp, 0, false);
           
						if ( RetValue )
            {
              m_pGT_GRADE->commit();
            }
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DBWriteError(sMessage, "", "GT_GRADE","cannot update/insert grade");

              m_pGT_GRADE->rollback();

              handleErrorCode(Key, 10221);
            }
        } // if ( RetValue )
        //********    Convert and check telegram data  ***********************************************************

        if ( RetValue )
        {
          DataKey       = generateDataKey(TlgName);

          //********    Write telegram data  ***********************************************************************
          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);

          //********    End processing data  ***********************************************************************

          log (TlgName + ": Finished", 3);
        }
      }
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}









bool CL3_TelegramHandler::DoProcessHeatSchedule(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessHeatSchedule";
  std::string HeatId = CSMC_DBData::unspecString;
  std::string TreatId = CSMC_DBData::unspecString;
  std::string DataKey = CSMC_DBData::unspecString;
  std::string PlantId = CSMC_DBData::unspecString;      
  std::string Plant = CSMC_DBData::unspecString;      
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  const long ResponseCode_Accepted   = 0;
  const long ResponseCode_HeatAlreadyDone   = 1;
  const long ResponseCode_SteelGradeNotDefined   = 2;
  const long ResponseCode_ProductionOrderNotDefined   = 3;
  const long ResponseCode_PlantStarttimeNotUnique   = 4;
  const long ResponseCode_WrongActionFlag   = 5;

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      long ActionFlag             = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_HEAT_SCHEDULE::ActionFlag);
      string L3HeatID             = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::HeatId);
      string L3ProdOrder          = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::ProdOrderNo);
      string L3SteelGrade         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::SteelGrade);
      long PlanLadle              = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_HEAT_SCHEDULE::PlanLadle);
      string L3RouteCode          = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::RouteCode);
      double L3AimSteelEAF        = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimSteel_EAF_Wt);
      double L3AimSteelLF         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimSteel_LF_Wt);
      double L3AimSteelCCS        = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimSteel_CCS_Wt);
      double L3AimHMEAF           = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimHM_Wt);

      long TreatmentMode          = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentMode);
      double L3AimTempEAF        = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimTemp_EAF);
      double L3AimTempLF         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_L3_HEAT_SCHEDULE::AimTemp_LF);
      long CasterSeqNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_HEAT_SCHEDULE::CasterSeqNo);
      long HeatSeqNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_HEAT_SCHEDULE::HeatSeqNo);

      string L3PlantUnit_1         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_1);
      string L3PlantUnit_2         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_2);
      string L3PlantUnit_3         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_3);
      string L3PlantUnit_4         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_4);
      string L3PlantUnit_5         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_5);
      string L3PlantUnit_6         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_6);
      string L3PlantUnit_7         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_7);
      string L3PlantUnit_8         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_8);
      string L3PlantUnit_9         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_9);
      string L3PlantUnit_10        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::PlantUnit_10);

      string L3TreatID_1           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_1);
      string L3TreatID_2           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_2);
      string L3TreatID_3           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_3);
      string L3TreatID_4           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_4);
      string L3TreatID_5           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_5);
      string L3TreatID_6           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_6);
      string L3TreatID_7           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_7);
      string L3TreatID_8           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_8);
      string L3TreatID_9           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_9);
      string L3TreatID_10          = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HEAT_SCHEDULE::TreatmentId_10);

      CDateTime dtStartTime_1,dtStartTime_2,dtStartTime_3,dtStartTime_4,dtStartTime_5,dtStartTime_6,dtStartTime_7,dtStartTime_8,dtStartTime_9,dtStartTime_10;
      CDateTime dtEndTime_1,dtEndTime_2,dtEndTime_3,dtEndTime_4,dtEndTime_5,dtEndTime_6,dtEndTime_7,dtEndTime_8,dtEndTime_9,dtEndTime_10;

      sDate sdStartTime_1,sdStartTime_2,sdStartTime_3,sdStartTime_4,sdStartTime_5,sdStartTime_6,sdStartTime_7,sdStartTime_8,sdStartTime_9,sdStartTime_10;
      sDate sdEndTime_1,sdEndTime_2,sdEndTime_3,sdEndTime_4,sdEndTime_5,sdEndTime_6,sdEndTime_7,sdEndTime_8,sdEndTime_9,sdEndTime_10;

      sdStartTime_1   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_1);
      dtStartTime_1 << sdStartTime_1;

      sdStartTime_2   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_2);
      dtStartTime_2 << sdStartTime_2;

      sdStartTime_3   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_3);
      dtStartTime_3 << sdStartTime_3;

      sdStartTime_4   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_4);
      dtStartTime_4 << sdStartTime_4;

      sdStartTime_5   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_5);
      dtStartTime_5 << sdStartTime_5;

      sdStartTime_6   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_6);
      dtStartTime_6 << sdStartTime_6;

      sdStartTime_7   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_7);
      dtStartTime_7 << sdStartTime_7;

      sdStartTime_8   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_8);
      dtStartTime_8 << sdStartTime_8;

      sdStartTime_9   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_9);
      dtStartTime_9 << sdStartTime_9;

      sdStartTime_10   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::StartTime_10);
      dtStartTime_10 << sdStartTime_10;


      sdEndTime_1   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_1);
      dtEndTime_1 << sdEndTime_1;

      sdEndTime_2   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_2);
      dtEndTime_2 << sdEndTime_2;

      sdEndTime_3   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_3);
      dtEndTime_3 << sdEndTime_3;

      sdEndTime_4   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_4);
      dtEndTime_4 << sdEndTime_4;

      sdEndTime_5   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_5);
      dtEndTime_5 << sdEndTime_5;

      sdEndTime_6   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_6);
      dtEndTime_6 << sdEndTime_6;

      sdEndTime_7   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_7);
      dtEndTime_7 << sdEndTime_7;

      sdEndTime_8   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_8);
      dtEndTime_8 << sdEndTime_8;

      sdEndTime_9   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_9);
      dtEndTime_9 << sdEndTime_9;

      sdEndTime_10   = m_pTelegram_Adapter->m_pIntf_IN->getDate(Key.c_str(), Telegram_L3_HEAT_SCHEDULE::EndTime_10);
      dtEndTime_10 << sdEndTime_10;

			//default setting
			if(L3AimSteelEAF == DEF::Inv_Double || L3AimSteelEAF == 0)
			{
				L3AimSteelEAF = 160000.0;
			}

			if(L3AimSteelLF == DEF::Inv_Double || L3AimSteelLF == 0)
			{
				L3AimSteelLF = 160000.0;
			}

			if(L3AimHMEAF == DEF::Inv_Double || L3AimHMEAF == 0)
			{
				L3AimHMEAF = 65000.0;
			}

			if(m_pPP_HEAT->selectOrderBy(CSMC_DBData::unspecString,false))
			{
				std::string OrderID = m_pPP_HEAT->getPRODORDERID(1);				
				if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::EAF,1,DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE))
				{
					string modeValue = m_pPP_ORDER_SINGLE_AIMS->getVALUE(1);
					TreatmentMode = CDataConversion::StringToLong(modeValue);					
				}
      }
			
			if(L3AimTempEAF == DEF::Inv_Double || L3AimTempEAF == 0)
			{
				L3AimTempEAF = 1630.0;
			}

			if(L3AimTempLF == DEF::Inv_Double || L3AimTempLF == 0)
			{
				L3AimTempLF = 1550.0;
			}

			L3ProdOrder = L3HeatID; //as per JSW is's the same

			//********    Convert and check telegram data  ***********************************************************   
      EventMessageVector.push_back(L3_EvMsg::evL3HeatScheduleUpdate);
			DataKey       = generateDataKey(TlgName);

			RetValue = RetValue && setErrorOnValidation(Key,10802,TlgName,Telegram_L3_HEAT_SCHEDULE::ActionFlag,     ActionFlag,     1 , 3);
			m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::L3OrderId, L3ProdOrder);
			m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::L3HeatId, L3HeatID);

      //********    Convert and check telegram data  ***********************************************************
      if ( !RetValue )
      {
				m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_WrongActionFlag);  
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
        log (TlgName + ": Wrong Action Flag", 3);
				return true;
      }

			RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_HEAT_SCHEDULE::SteelGrade,    L3SteelGrade);
      if ( !RetValue )
      {
				m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_SteelGradeNotDefined);  
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
        log (TlgName + ": Steel grade not defined", 3);
				return true;
      }

			//RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_HEAT_SCHEDULE::ProdOrderNo,    L3ProdOrder);


      if ( !RetValue )
      {
				m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_ProductionOrderNotDefined);  
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
        log (TlgName + ": Production order not defined", 3);
				return true;
      }

			long State = DEF::Inv_Long;
			if ( ActionFlag == 1 )
			{
				State = DEF_GEN_STATES::New;
			}
			else if ( ActionFlag == 2 )
			{
				State = DEF_GEN_STATES::Update;
			}
			else if ( ActionFlag == 3 )
			{
				State = DEF_GEN_STATES::Delete;
			}

      bool hasRecord = false;
			string HeatID = CSMC_DBData::unspecString;
			string TreatID ="01";//we will always consider here only 1st treatment because re-treatment in EAF by HMI is not possible and re-treatment in LF is possible by HMI without re-scheduling heat
			string L3TreatID = CSMC_DBData::unspecString;
			string PlantName = CSMC_DBData::unspecString;

      if(State == DEF_GEN_STATES::Delete)
      {
        if(m_pPP_HEAT->selectOrder(L3ProdOrder))
        {
          HeatID = m_pPP_HEAT->getHEATID(1);
          hasRecord = m_pPD_HEAT_REF->isPlanned(HeatID);
        }

        if(hasRecord)
        {  
          RetValue = RetValue && m_pPP_HEAT->deleteRow(HeatID,false,m_lastError);
          RetValue = RetValue && m_pPP_ORDER->deletePP(L3ProdOrder,false,m_lastError);
          RetValue = RetValue && m_pPD_HEAT_REF->deleteRow(HeatID,false,m_lastError);

					if (RetValue)
						CDH_IN_Task::getInstance()->getStdConnection()->commit();
					else
					{
						CDH_IN_Task::getInstance()->getStdConnection()->rollback();
					}
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_Accepted);    
					m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
	        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
          return true;
        }
        else
        {
          log("Heat data Can NOT delete because it is already produced or producing..",3);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_HeatAlreadyDone);  
					m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
	        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
          return true;
        }                
      }


      //check starttime and it must be unique all over the plants under one production orders
      CDateTime checkStartTime = CSMC_DBData::unspecDate;
			CDateTime StartTime = CSMC_DBData::unspecDate;
			CDateTime EndTime = CSMC_DBData::unspecDate;
      for (int i = 1; i <= 10; i++)
      {
        if( i == 1)
        {
          PlantName = L3PlantUnit_1;
          StartTime = dtStartTime_1;
        }
        if( i == 2) 
        {
          PlantName = L3PlantUnit_2;
          StartTime = dtStartTime_2;
        }
        if( i == 3)
        {
          PlantName = L3PlantUnit_3;
          StartTime = dtStartTime_3;
        }
        if( i == 4)
        {
          PlantName = L3PlantUnit_4;
          StartTime = dtStartTime_4;
        }
        if( i == 5)
        {
          PlantName = L3PlantUnit_5;
          StartTime = dtStartTime_5;
        }
        if( i == 6)
        {
          PlantName = L3PlantUnit_6;
          StartTime = dtStartTime_6;
        }
        if( i == 7)
        {
          PlantName = L3PlantUnit_7;
          StartTime = dtStartTime_7;
        }
        if( i == 8)
        {
          PlantName = L3PlantUnit_8;
          StartTime = dtStartTime_8;
        }
        if( i == 9)
        {
          PlantName = L3PlantUnit_9;
          StartTime = dtStartTime_9;
        }
        if( i == 10) 
        {
          PlantName = L3PlantUnit_10;
          StartTime = dtStartTime_10;
        }

        
        if(PlantName.substr(0,1) == "E")
          PlantName = DEF_GC_PLANT_DEF::EAF;
        else if(PlantName.substr(0,1) == "L") 
          PlantName = DEF_GC_PLANT_DEF::LF;
        else 
          PlantName = "UNDEFINED";

        if (PlantName == "UNDEFINED") continue;

        if(checkStartTime < StartTime)
        {
          checkStartTime = StartTime;
        }
        else
        {
          log("Plant starttime must be unique all over the plants as well as all over the production order....or no start time is there...",3);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_PlantStarttimeNotUnique);  
					m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
	        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
          return true;
        }

      } //for (int i = 1; i <= 10; i++)

			if(State == DEF_GEN_STATES::Update || State == DEF_GEN_STATES::Insert) 
			{
				if(m_pPP_HEAT->selectOrder(L3ProdOrder))
				{
					HeatID = m_pPP_HEAT->getHEATID(1);      
					if(!m_pPD_HEAT_REF->isPlanned(HeatID))
					{
							log("Heat data Can NOT be updated for rest of telegram data because it is already anounced or produced or producing..",3);
							m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_HeatAlreadyDone);  
							m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
			        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
							return true;
					}
				}
					
				if(!m_pGT_GRADE->select(L3SteelGrade))
				{
					m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_SteelGradeNotDefined);  
					m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
					SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
          log("Steel grade does not exist in GT_GRADE. Please send Steel Grade first",3);
					return true;
				}

				//handel PP_ORDER && PP_ORDER_SINGLE_AIMS
				RetValue = RetValue && m_pPP_ORDER->updateInsertPP(L3ProdOrder,L3SteelGrade,"L3",false,m_lastError);
				hasRecord = m_pPP_ORDER->select(L3ProdOrder) ; 
				m_pPP_ORDER->setORDERSEQNO(CasterSeqNo);
				RetValue = RetValue && m_pPP_ORDER->update();

				PlanLadle = 1; //default
				//if(!m_pGC_LADLE_DEF->select(PlanLadle,DEF_GC_LADLE_TYPE::TeemingLadle))
				//{
				//	PlanLadle = CSMC_DBData::unspecLong;
				//}

				//handle PP_HEAT
				if(!m_pPP_HEAT->selectOrder(L3ProdOrder))
				{
					m_pPP_HEAT->getNextHeatId( HeatID, m_lastError );
					RetValue = RetValue && m_pPP_HEAT->updateInsertPP(HeatID,L3ProdOrder,L3RouteCode,CasterSeqNo,HeatSeqNo,"L3",1,1,0,DEF_GC_LADLE_TYPE::TeemingLadle,PlanLadle,false,m_lastError);
				}
				else
				{
					RetValue = RetValue && m_pPP_HEAT->updateInsertPP(HeatID,L3ProdOrder,L3RouteCode,CasterSeqNo,HeatSeqNo,"L3",1,1,0,DEF_GC_LADLE_TYPE::TeemingLadle,PlanLadle,false,m_lastError);
				}

				if ( CSMC_DBData::unspecString == L3HeatID 	|| L3HeatID.empty())
				{
					L3HeatID = HeatID;
				}					

				for (int i = 1; i <= 10; i++)
				{
					if( i == 1)
					{
						PlantName = L3PlantUnit_1;
						StartTime = dtStartTime_1;
						EndTime = dtEndTime_1;
						L3TreatID = L3TreatID_1;
					}
					if( i == 2) 
					{
						PlantName = L3PlantUnit_2;
						StartTime = dtStartTime_2;
						EndTime = dtEndTime_2;
						L3TreatID = L3TreatID_2;
					}
					if( i == 3)
					{
						PlantName = L3PlantUnit_3;
						StartTime = dtStartTime_3;
						EndTime = dtEndTime_3;
						L3TreatID = L3TreatID_3;
					}
					if( i == 4)
					{
						PlantName = L3PlantUnit_4;
						StartTime = dtStartTime_4;
						EndTime = dtEndTime_4;
						L3TreatID = L3TreatID_4;
					}
					if( i == 5)
					{
						PlantName = L3PlantUnit_5;
						StartTime = dtStartTime_5;
						EndTime = dtEndTime_5;
						L3TreatID = L3TreatID_5;
					}
					if( i == 6)
					{
						PlantName = L3PlantUnit_6;
						StartTime = dtStartTime_6;
						EndTime = dtEndTime_6;
						L3TreatID = L3TreatID_6;
					}
					if( i == 7)
					{
						PlantName = L3PlantUnit_7;
						StartTime = dtStartTime_7;
						EndTime = dtEndTime_7;
						L3TreatID = L3TreatID_7;
					}
					if( i == 8)
					{
						PlantName = L3PlantUnit_8;
						StartTime = dtStartTime_8;
						EndTime = dtEndTime_8;
						L3TreatID = L3TreatID_8;
					}
					if( i == 9)
					{
						PlantName = L3PlantUnit_9;
						StartTime = dtStartTime_9;
						EndTime = dtEndTime_9;
						L3TreatID = L3TreatID_9;
					}
					if( i == 10) 
					{
						PlantName = L3PlantUnit_10;
						StartTime = dtStartTime_10;
						EndTime = dtEndTime_10;
						L3TreatID = L3TreatID_10;
					}

					long PlantNo = 0;
					if(PlantName != CSMC_DBData::unspecString && !PlantName.empty())
					  PlantNo = CDataConversion::StringToLong(PlantName.substr(1,1));

					if(PlantName.substr(0,1) == "E")
						PlantName = DEF_GC_PLANT_DEF::EAF;
					else if(PlantName.substr(0,1) == "L") 
						PlantName = DEF_GC_PLANT_DEF::LF;
					else 
						PlantName = "UNDEFINED";

					
					if (PlantName == "UNDEFINED")
							continue;
					
					

					if (PlantName == DEF_GC_PLANT_DEF::EAF && TreatmentMode != DEF::Inv_Long )
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE,CDataConversion::LongToString(TreatmentMode,0),false,m_lastError);

					if (PlantName == DEF_GC_PLANT_DEF::EAF && L3AimSteelEAF != DEF::Inv_Double )
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL,CDataConversion::DoubleToString(L3AimSteelEAF,0),false,m_lastError);

					if (PlantName == DEF_GC_PLANT_DEF::EAF && L3AimTempEAF != DEF::Inv_Double )
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMTEMP,CDataConversion::DoubleToString(L3AimTempEAF,0),false,m_lastError);

					if (PlantName == DEF_GC_PLANT_DEF::EAF && L3AimHMEAF != DEF::Inv_Double )
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::LIQADD,CDataConversion::DoubleToString(L3AimHMEAF,0),false,m_lastError);
				
					if (PlantName == DEF_GC_PLANT_DEF::EAF && L3AimSteelCCS != DEF::Inv_Double)
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,DEF_GC_PLANT_DEF::CCS,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL,CDataConversion::DoubleToString(L3AimSteelCCS,0),false,m_lastError);

					if (PlantName == DEF_GC_PLANT_DEF::LF && L3AimSteelLF != DEF::Inv_Double)
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL,CDataConversion::DoubleToString(L3AimSteelLF,0),false,m_lastError);

					if (PlantName == DEF_GC_PLANT_DEF::LF && L3AimTempLF != DEF::Inv_Double)
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(L3ProdOrder,PlantName,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMTEMP,CDataConversion::DoubleToString(L3AimTempLF,0),false,m_lastError);


					//handle PP_HEAT_PLANT - we consider TreatID & CustomerTreatID are same
					RetValue = RetValue &&  m_pPP_HEAT_PLANT->updateInsertPP(HeatID,TreatID,PlantName,PlantNo,L3HeatID,TreatID,StartTime.assDate(),EndTime.assDate(),false,m_lastError);
					hasRecord = m_pPP_HEAT_PLANT->select(HeatID,TreatID,PlantName); 
					if(hasRecord)
					{
						m_pPP_HEAT_PLANT->setTREATSTART_PLAN(StartTime);
						m_pPP_HEAT_PLANT->setTREATEND_PLAN(EndTime);
						RetValue = RetValue && m_pPP_HEAT_PLANT->update();
					}       
				} //for..

				
				long HEATSTATUSNO_PLANNED      = m_pHeatStatusContainer->getHeatStatus(DEF_GC_PLANT_DEF::L3, DEF_GC_HEAT_STATUS::Planned );
				if(m_pPD_HEAT_REF->select(HeatID))
				{
					m_pPD_HEAT_REF->setHEATID(HeatID);
					m_pPD_HEAT_REF->setHEATSTATUSNO(HEATSTATUSNO_PLANNED);
					m_pPD_HEAT_REF->setUSERCODE("L3");
					m_pPD_HEAT_REF->setREVTIME(Now);
					RetValue = RetValue && m_pPD_HEAT_REF->update();
				}
				else
				{
					m_pPD_HEAT_REF->setHEATID(HeatID);
					m_pPD_HEAT_REF->setHEATSTATUSNO(HEATSTATUSNO_PLANNED);
					m_pPD_HEAT_REF->setUSERCODE("L3");
					m_pPD_HEAT_REF->setREVTIME(Now);
					RetValue = RetValue && m_pPD_HEAT_REF->insert();
				}


				if (RetValue)
					CDH_IN_Task::getInstance()->getStdConnection()->commit();
				else
				{
					CDH_IN_Task::getInstance()->getStdConnection()->rollback();
				}
        m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::AckCode, ResponseCode_Accepted);    
				m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
        return true;
		}


    //********    reset statushandler for plant *******************************************************************************
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}



bool CL3_TelegramHandler::DoProcessHMLadle(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessHMLadle";
  std::string HeatId = CSMC_DBData::unspecString;
  std::string TreatId = CSMC_DBData::unspecString;
  std::string DataKey = CSMC_DBData::unspecString;
  std::string PlantId = CSMC_DBData::unspecString;      
  std::string Plant = CSMC_DBData::unspecString;      
  std::string ProdOrderNo = CSMC_DBData::unspecString;      
  
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      PlantId                 = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HM_LADLE::PlantUnit);
      HeatId                  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HM_LADLE::HeatId);
      TreatId                 = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HM_LADLE::TreatId);
      ProdOrderNo             = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_HM_LADLE::ProdOrderNo);
			
      long   LadleNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_HM_LADLE::LadleNo);  
      double HMWeight            = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_HM_LADLE::HMWeight);  
      double SlagWeight          = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_HM_LADLE::SlagWeight);  
      long HMTemp                = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_HM_LADLE::HMTemp);  
      CDateTime HMTempTime;
			HMTempTime <<  m_pTelegram_Adapter->m_pIntf_IN->getDate  (Key.c_str(), Telegram_L3_HM_LADLE::HMTempTime);  

      long LadleFreeboard        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_HM_LADLE::LadleFreeboard);  

      CDateTime StartTime;
			StartTime <<  m_pTelegram_Adapter->m_pIntf_IN->getDate  (Key.c_str(), Telegram_L3_HM_LADLE::StartTime);  

      CDateTime EndTime;
			EndTime <<  m_pTelegram_Adapter->m_pIntf_IN->getDate  (Key.c_str(), Telegram_L3_HM_LADLE::EndTime);  
			
      double Aim_S                = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_HM_LADLE::Aim_S);  


			//for L3 HeatID and ProdOrderNo are same
			ProdOrderNo = HeatId;

			if(LadleFreeboard == DEF::Inv_Long || LadleFreeboard == 0)
			{
				LadleFreeboard = 300;
			}

      if ( !PlantId.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(PlantId);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

			seqAnalysis SeqAnalysisSteel = handleGradeAnalysis(Key,"AnlVal_","Steel");

      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_HM_LADLE::PlantUnit,    PlantId);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10804,TlgName,Telegram_L3_HM_LADLE::HeatId, HeatId);
      RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_HM_LADLE::LadleNo,        LadleNo,        1,  99);
      //********    Define Event *******************************************************************************

			bool hasRecord = false;
			long HMCoumter = 0;
			TreatId = "01"; //default value because there is no re-treatmet at HMDS

			CPD_SAMPLE PD_SAMPLE(CDH_IN_Task::getInstance()->getStdConnection());
			CPD_SAMPLE_ENTRY PD_SAMPLE_ENTRY(CDH_IN_Task::getInstance()->getStdConnection());
			CHD_SAMPLE HD_SAMPLE(CDH_IN_Task::getInstance()->getStdConnection());
			CHD_SAMPLE_ENTRY HD_SAMPLE_ENTRY(CDH_IN_Task::getInstance()->getStdConnection());
			CPD_SAMPLE_REF PD_SAMPLE_REF(CDH_IN_Task::getInstance()->getStdConnection());
			CPD_HOT_METAL PD_HOT_METAL(CDH_IN_Task::getInstance()->getStdConnection());

      string strIntenalNxtHeatID = CSMC_DBData::unspecString;
      hasRecord = m_pPP_HM->selectInternalID(HeatId) ; 
      if(!hasRecord)
      {
				strIntenalNxtHeatID = CDataConversion::LongToString(m_pPP_HM->getNextHMID());
				
				PD_HOT_METAL.getNextHOTMETAL_COUNTER(HMCoumter,m_lastError);
				RetValue = RetValue && PD_HOT_METAL.insertLadle(HMCoumter,DEF_GC_LADLE_TYPE::HotMetalLadle,LadleNo,HMWeight,false,m_lastError);
        RetValue = RetValue && m_pPP_HM->updateInsertPP(strIntenalNxtHeatID,PlantNo,HMCoumter,false,m_lastError);
      }
			else
			{
				strIntenalNxtHeatID = m_pPP_HM->getHM_ID(1);	
				HMCoumter =  m_pPP_HM->getHOTMETAL_COUNTER(1);

				if(m_pPDH_HM_DATA->select(strIntenalNxtHeatID,CSMC_DBData::unspecString,DEF_GC_PLANT_DEF::HMD))
				{
	        log (TlgName + ": Heat is already announced or produced", 3);
					return true;
				}
			}

      if( m_pPP_HM->select(strIntenalNxtHeatID))
      {
        m_pPP_HM->setPRODORDERID(ProdOrderNo);
        m_pPP_HM->setHM_ID_CUST_PLAN(HeatId);
        m_pPP_HM->setTREATSTART_PLAN(StartTime);
        m_pPP_HM->setTREATEND_PLAN(EndTime);
        m_pPP_HM->setAIM_S(Aim_S);
        m_pPP_HM->setPLANTNO(PlantNo);
				
        m_pPP_HM->setLADLEFREEBOARD(LadleFreeboard);
					
        RetValue = RetValue && m_pPP_HM->update();
			}

			if(PD_HOT_METAL.select(HMCoumter))
			{
				PD_HOT_METAL.setLADLENO(LadleNo);
				PD_HOT_METAL.setWEIGHT(HMWeight);
				PD_HOT_METAL.setWEIGHT_SLAG(SlagWeight);
				PD_HOT_METAL.setREVTIME(Now);
				RetValue = RetValue && PD_HOT_METAL.update();
			}

			long sampleRefNo = CSMC_DBData::unspecLong;
			if(PD_SAMPLE.selectByType_HMD(strIntenalNxtHeatID,TreatId,Plant,PlantNo,DEF_GC_MEASUREMENT_TYPE::HM))
			{
				long SampleCounter = PD_SAMPLE.getSAMPLE_COUNTER(1);
				if(SampleCounter != CSMC_DBData::unspecLong)
				{
					RetValue = RetValue &&  PD_SAMPLE_ENTRY.deleteSample(SampleCounter);
					RetValue = RetValue && PD_SAMPLE_ENTRY.insertAnalysis(SampleCounter,SeqAnalysisSteel,false,m_lastError);
					RetValue = RetValue && HD_SAMPLE.OnTempMeasurement(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter,false,m_lastError);
					RetValue = RetValue &&  HD_SAMPLE_ENTRY.copy(SampleCounter,false,m_lastError);
				}
			}
			else
			{
				sampleRefNo = PD_SAMPLE_REF.getNextSAMPLE_REF();
				RetValue = RetValue &&  PD_SAMPLE_REF.writeSAMPLE_REF(sampleRefNo,CSMC_DBData::unspecLong,CSMC_DBData::unspecLong,false,m_lastError); 
				if(PD_HOT_METAL.select(HMCoumter))
				{
					PD_HOT_METAL.setSAMPLE_REF(sampleRefNo);
					PD_HOT_METAL.setREVTIME(Now);
					RetValue = RetValue && PD_HOT_METAL.update();
				}

				long SampleCounter = PD_SAMPLE.getNextSAMPLE_COUNTER();
				RetValue = RetValue && PD_SAMPLE.insertByPrevSample_HMD(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter, SampleCounter, Now.assDate(), 1, DEF_GC_PLANT_DEF::L3,DEF_GC_LADLE_TYPE::HotMetalLadle,LadleNo,DEF_GC_MEASUREMENT_TYPE::HM, false, m_lastError);
				RetValue = RetValue && PD_SAMPLE_ENTRY.insertAnalysis(SampleCounter, SeqAnalysisSteel, false, m_lastError);
				RetValue = RetValue && PD_SAMPLE.updateSampleDetails(SampleCounter,ProdOrderNo,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,1,DEF_GC_PLANT_DEF::L3,CSMC_DBData::unspecString,CSMC_DBData::unspecLong);
				RetValue = RetValue && HD_SAMPLE.OnTempMeasurement(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter,false,m_lastError);
				RetValue = RetValue && HD_SAMPLE_ENTRY.copy(SampleCounter,false,m_lastError);			
				RetValue = RetValue &&  PD_SAMPLE_REF.writeSAMPLE_REF(sampleRefNo,SampleCounter,DEF_GC_MEASUREMENT_TYPE::HM,false,m_lastError); 
			}

			if(PD_SAMPLE.selectByType_HMD(strIntenalNxtHeatID,TreatId,Plant,PlantNo,DEF_GC_MEASUREMENT_TYPE::Temp))
			{
				long SampleCounter = PD_SAMPLE.getSAMPLE_COUNTER(1);
				if(SampleCounter != CSMC_DBData::unspecLong)
				{
					RetValue = RetValue &&  PD_SAMPLE_ENTRY.deleteSample(SampleCounter);
					RetValue = RetValue &&  PD_SAMPLE_ENTRY.insertSample(SampleCounter,DEF_GC_MEASUREMENT_NAME::Temp,HMTemp);
					RetValue = RetValue &&  HD_SAMPLE.OnTempMeasurement(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter,false,m_lastError);
					RetValue = RetValue &&  HD_SAMPLE_ENTRY.copy(SampleCounter,false,m_lastError);
				}
			}
			else
			{
				long SampleCounter = PD_SAMPLE.getNextSAMPLE_COUNTER();
				RetValue = RetValue && PD_SAMPLE.insertByPrevSample_HMD(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter, SampleCounter, Now.assDate(), 1, DEF_GC_PLANT_DEF::L3,DEF_GC_LADLE_TYPE::HotMetalLadle,LadleNo,DEF_GC_MEASUREMENT_TYPE::Temp, false, m_lastError);
				RetValue = RetValue &&  PD_SAMPLE_ENTRY.insertSample(SampleCounter,DEF_GC_MEASUREMENT_NAME::Temp,HMTemp);
				RetValue = RetValue && PD_SAMPLE.updateSampleDetails(SampleCounter,ProdOrderNo,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,1,DEF_GC_PLANT_DEF::L3,CSMC_DBData::unspecString,CSMC_DBData::unspecLong);
				RetValue = RetValue && HD_SAMPLE.OnTempMeasurement(strIntenalNxtHeatID,TreatId,Plant,PlantNo,SampleCounter,false,m_lastError);
				RetValue = RetValue && HD_SAMPLE_ENTRY.copy(SampleCounter,false,m_lastError);
				RetValue = RetValue &&  PD_SAMPLE_REF.writeSAMPLE_REF(sampleRefNo,SampleCounter,DEF_GC_MEASUREMENT_TYPE::Temp,false,m_lastError); 
			}

			if (RetValue)
				CDH_IN_Task::getInstance()->getStdConnection()->commit();
			else
			{
				CDH_IN_Task::getInstance()->getStdConnection()->rollback();
			}

      if ( RetValue )
      {
        DataKey       = generateDataKey(TlgName);
	      EventMessageVector.push_back(L3_EvMsg::evL3AssignLadle); //Note: do not use evL3HeatScheduleUpdate becuse wrong message will go to L3 via Schedule Response
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);   
        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);     
        log (TlgName + ": Finished", 3);
      }
			else
			{
        log (TlgName + ": error occours please check log....", 3);
			}
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}


bool CL3_TelegramHandler::DoProcessMaterialCodeDefinition(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessMaterialCodeDefinition";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------
  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      long ActionFlag                 = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_MATERIAL_CODES::ActionFlag);
      std::string MatCode             = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_MATERIAL_CODES::MatCode);
      std::string MatDesc          = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_MATERIAL_CODES::MatCodeDecs);

      long   Density                  = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_MATERIAL_CODES::Density);  
      long   BulkDensity              = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_MATERIAL_CODES::BulkDensity);  
      
      double FeedSpeed                = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_MATERIAL_CODES::FeedSpeed);  
      long   HomogenFactor            = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_MATERIAL_CODES::HomogenFactor);  
      double Enthalpy                 = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_MATERIAL_CODES::Enthalpy);  //(Key, Telegram_L3_MATERIAL_CODES::Enthalpy) / 100.; // 0.01 kWh/Kg -> kWh/kg
      double Price                    = m_pTelegram_Adapter->m_pIntf_IN->getDouble  (Key, Telegram_L3_MATERIAL_CODES::MatPrice);  

			//default value
			if ( MatDesc == DEF::Inv_String || MatDesc.empty() )
			{
				MatDesc = MatCode;
			}
			if ( Price == DEF::Inv_Double )
			{
				Price = 0;
			}


			seqAnalysis SeqAnalysisSteel = handleGradeAnalysis(Key,"Steel_","Steel");
      seqAnalysis SeqAnalysisSlag  = handleGradeAnalysis(Key,"Slag_","Slag");

      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidation(Key,10802,TlgName,Telegram_L3_MATERIAL_CODES::ActionFlag,     ActionFlag,     1 , 3);

      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_MATERIAL_CODES::MatCode,    MatCode);
      //RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10804,TlgName,Telegram_L3_MATERIAL_CODES::MatCodeDecs, MatDesc);

			//Note :all material may not have all valuses
      //RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_MATERIAL_CODES::Density,        Density,        0,  100000);
      //RetValue = RetValue && setErrorOnValidation(Key,10807,TlgName,Telegram_L3_MATERIAL_CODES::BulkDensity,    BulkDensity,    0,  100000);
      //RetValue = RetValue && setErrorOnValidation(Key,10809,TlgName,Telegram_L3_MATERIAL_CODES::FeedSpeed,      FeedSpeed,      0., 200.);
      //RetValue = RetValue && setErrorOnValidation(Key,10810,TlgName,Telegram_L3_MATERIAL_CODES::HomogenFactor,  HomogenFactor,  0,  100000);
      //RetValue = RetValue && setErrorOnValidation(Key,10811,TlgName,Telegram_L3_MATERIAL_CODES::Enthalpy,       Enthalpy,       0., 10000.);
      //RetValue = RetValue && setErrorOnValidation(Key,10812,TlgName,Telegram_L3_MATERIAL_CODES::MatPrice,          Price,          0., 10000.);

      //********    reset statushandler for plant *******************************************************************************


      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(L3_EvMsg::evL3MaterialCodeUpdate);
      
      //********    Convert and check telegram data  ***********************************************************

      if ( RetValue )
      {
        DataKey       = generateDataKey(TlgName);

        long State = DEF::Inv_Long;

        if ( ActionFlag == 1 )
        {
          State = DEF_GEN_STATES::New;
        }
        else if ( ActionFlag == 2 )
        {
          State = DEF_GEN_STATES::Update;
        }
        else if ( ActionFlag == 3 )
        {
          State = DEF_GEN_STATES::Delete;
        }

     
        if ( State == DEF_GEN_STATES::Delete )
        {
          if ( m_pGT_MAT->deleteRow(MatCode) )
          {
            m_pGT_MAT->commit();
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage, "", "GT_MAT","cannot delete material");

            m_pGT_MAT->rollback();

            handleErrorCode(Key, 10820);
          }
        }
        else if ( State == DEF_GEN_STATES::Update || 
                  State == DEF_GEN_STATES::New      )
        {
          long ChargePriority     = 1;
          double SpecHeat         = CSMC_DBData::unspecDouble;
          double DistribSteelSlag = CSMC_DBData::unspecDouble;
          double FeedTempFact     = CSMC_DBData::unspecDouble;
          long MG_Equivalent      = CSMC_DBData::unspecLong;
          long MultipleAdditions  = CSMC_DBData::unspecLong;
          long Avail              = 1;
          double MinWeight        = CSMC_DBData::unspecDouble;

          RetValue = RetValue && m_pGT_MAT->updateInsertMat(MatCode,MatDesc,ChargePriority,Price,Density,BulkDensity,CSMC_DBData::unspecDouble, 
                                                            Enthalpy,SpecHeat,HomogenFactor,DistribSteelSlag,FeedSpeed,
                                                            FeedTempFact,MatDesc,MG_Equivalent,MultipleAdditions,
                                                            Avail,MinWeight,false,m_lastError);
          RetValue = RetValue && m_pGT_MAT_CHEM->updateInsertChem(MatCode,SeqAnalysisSteel,false,false,m_lastError);
          RetValue = RetValue && m_pGT_MAT_CHEM->updateInsertChem(MatCode,SeqAnalysisSlag,false,false,m_lastError);

          // define type specific purpose and assign given material to GT_MAT_PURP with repective UNITPROUPNO
          //std::string PurposeCode = CSMC_DBData::unspecString;

          if ( RetValue )
          {
            m_pGT_MAT->commit();
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage, "", "GT_MAT","cannot update/insert material");

            m_pGT_MAT->rollback();

            handleErrorCode(Key, 10821);
          }
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

        //********    send internal event  ***********************************************************************

        if ( RetValue )
        {
          SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);
        }

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}

bool CL3_TelegramHandler::DoProcessSteelAnalysis(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessSteelAnalysis";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************     
      std::string CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_STEEL::HeatId );
      std::string CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_STEEL::TreatId);
      std::string PlantUnit  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_STEEL::PlantUnit);
      std::string OrderId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_STEEL::OrderId);
      long LadleNo               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_STEEL::LadleNo);
			long SmplCounter               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_STEEL::SmplCounter);
      std::string SmplCode  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_STEEL::SmplCode);

      CDateTime SampleTime;
			SampleTime << m_pTelegram_Adapter->m_pIntf_IN->getDate   (Key.c_str(),Telegram_L3_ANALYSIS_STEEL::SmplTime);
			long SmplUseable           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_STEEL::SmplUseable);
			std::string SampleLocation = CSMC_DBData::unspecString;
        
			seqAnalysis SeqAnalysis = handleGradeAnalysis(Key,"AnlVal_","Steel");
      
      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_ANALYSIS_STEEL::PlantUnit,    PlantUnit);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_ANALYSIS_STEEL::SmplCode,    SmplCode);
      RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_ANALYSIS_STEEL::SmplCounter,        SmplCounter,        1,  99);
      //RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_ANALYSIS_STEEL::SmplUseable,        SmplUseable,        0,  1);


      if ( !PlantUnit.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(PlantUnit);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

      //********    Define Event *******************************************************************************
      if ( Plant == DEF_GC_PLANT_DEF::EAF )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFSteelAnalysisReceived);
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatId, HeatId,TreatId, Plant);
				SampleLocation = DEF_GC_SAMPLELOC::EAF;
      }
      else if ( Plant == DEF_GC_PLANT_DEF::LF )
      {
        EventMessageVector.push_back(LF_EvMsg::evLFSteelAnalysisReceived);
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatId, HeatId,TreatId, Plant);
				SampleLocation = DEF_GC_SAMPLELOC::LF;
      }
			else //for HMD
			{
				EventMessageVector.push_back(HMD_EvMsg::evHMDHotMetalAnalysisReceived);
				SampleLocation = DEF_GC_SAMPLELOC::HMD;
				if(m_pPP_HM->selectInternalID(CustHeatId))
				{
					HeatId = m_pPP_HM->getHM_ID(1);
				}
				if( HeatId != CSMC_DBData::unspecString && m_pPDH_HM_DATA->select(HeatId,CSMC_DBData::unspecString,DEF_GC_PLANT_DEF::HMD))
				{
					TreatId = m_pPDH_HM_DATA->getTREATID(1);
				}
			 
			}
      
      
      //********    Convert and check telegram data  ***********************************************************
      if ( RetValue )
      {		
        DataKey       = generateDataKey(TlgName);

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::DateTime         ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustHeatID   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustTreatID  ,CustTreatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::PlantID          ,PlantId);

				if ( Plant == DEF_GC_PLANT_DEF::HMD )
				{
					m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::HMSampleTime  ,CDateTime(SampleTime).assDate() );
 					m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(),DATA::HMMeasAnalysis  ,SeqAnalysis);
					m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::LadleType       ,DEF_GC_LADLE_TYPE::HotMetalLadle);
				}
				else
				{
					m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(),DATA::SteelMeasAnalysis  ,SeqAnalysis);
					m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::SteelSampleTime  ,CDateTime(SampleTime).assDate() );
					m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::LadleType       ,DEF_GC_LADLE_TYPE::TeemingLadle);
				}

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::SampleLocation   ,SampleLocation);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleNo         ,SmplCounter);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleOrigin     ,DEF_GC_MEASUREMENT_ORIGIN::Measured);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleMode       ,DEF_GC_SAMPLEMODE::automatic);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleType       ,DEF_GC_MEASUREMENT_TYPE::Steel);
        m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::SampleId       ,SmplCode);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::LadleNo       ,LadleNo);
		
		


        if(1 == SmplUseable)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::Yes);
        }
        else
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::No);
        }

       
        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,OrderId,false);
     

        //********    End processing data  ***********************************************************************
        log (TlgName + ": Finished", 3);
      }
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}

bool CL3_TelegramHandler::DoProcessSlagAnalysis(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessSlagAnalysis";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************     
      std::string CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_SLAG::HeatId );
      std::string CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_SLAG::TreatId);
      std::string PlantUnit  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_SLAG::PlantUnit);
      std::string OrderId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_SLAG::OrderId);
      long LadleNo               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_SLAG::LadleNo);
			long SmplCounter               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_SLAG::SmplCounter);
      std::string SmplCode  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_L3_ANALYSIS_SLAG::SmplCode);

      CDateTime SampleTime;
			SampleTime << m_pTelegram_Adapter->m_pIntf_IN->getDate   (Key.c_str(),Telegram_L3_ANALYSIS_SLAG::SmplTime);
			long SmplUseable           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_L3_ANALYSIS_SLAG::SmplUseable);

      std::string SampleLocation = CSMC_DBData::unspecString;

			seqAnalysis SeqAnalysis = handleGradeAnalysis(Key,"AnlVal_","Slag");
      
      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_ANALYSIS_SLAG::PlantUnit,    PlantUnit);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10803,TlgName,Telegram_L3_ANALYSIS_SLAG::SmplCode,    SmplCode);
      RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_ANALYSIS_SLAG::SmplCounter,        SmplCounter,        1,  99);
      //RetValue = RetValue && setErrorOnValidation(Key,10806,TlgName,Telegram_L3_ANALYSIS_SLAG::SmplUseable,        SmplUseable,        0,  1);


      if ( !PlantUnit.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(PlantUnit);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

      //********    Define Event *******************************************************************************
      if ( Plant == DEF_GC_PLANT_DEF::EAF )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFSlagAnalysisReceived);
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatId, HeatId,TreatId, Plant);

				SampleLocation = DEF_GC_SAMPLELOC::EAF;
      }
      else if ( Plant ==DEF_GC_PLANT_DEF::LF )
      {
        EventMessageVector.push_back(LF_EvMsg::evLFSlagAnalysisReceived);
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatId, HeatId,TreatId, Plant);

				SampleLocation = DEF_GC_SAMPLELOC::LF;
      }
			else //for HMD
			{
				EventMessageVector.push_back(HMD_EvMsg::evHMDSlagAnalysisReceived);
				SampleLocation = DEF_GC_SAMPLELOC::HMD;
				if(m_pPP_HM->selectInternalID(CustHeatId))
				{
					HeatId = m_pPP_HM->getHM_ID(1);
				}			
				if( HeatId != CSMC_DBData::unspecString && m_pPDH_HM_DATA->select(HeatId,CSMC_DBData::unspecString,DEF_GC_PLANT_DEF::HMD))
				{
					TreatId = m_pPDH_HM_DATA->getTREATID(1);
				}

			}
      
      
      //********    Convert and check telegram data  ***********************************************************
      if ( RetValue )
      {		
		
        DataKey       = generateDataKey(TlgName);

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::DateTime         ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustHeatID   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::CustTreatID  ,CustTreatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::PlantID          ,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(), DATA::SlagSampleTime  ,CDateTime(SampleTime).assDate() );
        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,         DATA::SampleLocation   ,SampleLocation);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleNo         ,SmplCounter);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleOrigin     ,DEF_GC_MEASUREMENT_ORIGIN::Measured);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleMode       ,DEF_GC_SAMPLEMODE::automatic);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::SampleType       ,DEF_GC_MEASUREMENT_TYPE::Slag);
        m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::SampleId       ,SmplCode);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,         DATA::LadleNo       ,LadleNo);

				if ( Plant == DEF_GC_PLANT_DEF::HMD )
				{
					m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::LadleType       ,DEF_GC_LADLE_TYPE::HotMetalLadle);
				}
				else
				{
					m_pTelegram_Adapter->m_pIntf_OUT->setString   (DataKey,         DATA::LadleType       ,DEF_GC_LADLE_TYPE::TeemingLadle);
				}


        if(1 == SmplUseable)
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::Yes);
        }
        else
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,         DATA::SampleUsable, DEF_GEN_STATES::No);
        }

				m_pTelegram_Adapter->m_pIntf_OUT->setAnalysis(DataKey.c_str(),DATA::SlagMeasAnalysis  ,SeqAnalysis);
        
    
        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,OrderId,false);

        //********    End processing data  ***********************************************************************
        log (TlgName + ": Finished", 3);
      }
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}

bool CL3_TelegramHandler::DoProcessDelayCodeDefinition(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessDelayCodeDefinition";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      long ActionFlag                 = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_DELAY_CODES::ActionFlag);
      std::string L3PlantID           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_DELAY_CODES::PlantUnit);
      long L3DelayGroup               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_DELAY_CODES::DelayGroup);
      std::string DelayCode           = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_DELAY_CODES::DelayCode);
      std::string DelayDesc        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_DELAY_CODES::DelayDesc);
      long DelayDefaultDur          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_DELAY_CODES::DelayDefaultDur);

			//default value
			if ( DelayDesc == DEF::Inv_String || DelayDesc.empty() )
			{
				DelayDesc = DelayCode;
			}

      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidation(Key,10902,TlgName,Telegram_L3_DELAY_CODES::ActionFlag,                ActionFlag,               1 , 3);
      RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_L3_DELAY_CODES::DelayGroup,                L3DelayGroup,             1 , 7);

      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_DELAY_CODES::PlantUnit,              L3PlantID);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_DELAY_CODES::DelayCode,          DelayCode);
      //RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_L3_DELAY_CODES::DelayDesc,              DelayDesc);


      // convert L3 plant id
      // Plant specifier e.g. E1 = EAF 1, L1 = LF 1
      if ( !L3PlantID.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(L3PlantID);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

      if ( RetValue )
      {
        DataKey       = generateDataKey(TlgName);

        long State = DEF::Inv_Long;

        if ( ActionFlag == 1 )
        {
          State = DEF_GEN_STATES::New;
        }
        else if ( ActionFlag == 2 )
        {
          State = DEF_GEN_STATES::Update;
        }
        else if ( ActionFlag == 3 )
        {
          State = DEF_GEN_STATES::Delete;
        }

        long DelayGroup = 0;
        
        if (  L3DelayGroup == 1 )
        {
          DelayGroup = DEF_GC_DELAY_GROUP::Production;
        }
        else if (  L3DelayGroup == 2 ) 
        {
          DelayGroup = DEF_GC_DELAY_GROUP::Maintenance;
        }
        else if (  L3DelayGroup == 3 )
        {
          DelayGroup = DEF_GC_DELAY_GROUP::Mechanic;
        }
        else if (  L3DelayGroup == 4 ) 
        {
          DelayGroup = DEF_GC_DELAY_GROUP::Electric;
        }
        else if (  L3DelayGroup == 5 ) 
        {
          DelayGroup = DEF_GC_DELAY_GROUP::RED;
        }
        else if (  L3DelayGroup == 6 ) 
        {
          DelayGroup = DEF_GC_DELAY_GROUP::CMD;
        }
        else if (  L3DelayGroup == 7 ) 
        {
          DelayGroup = DEF_GC_DELAY_GROUP::Other;
        }

        if ( State == DEF_GEN_STATES::Delete )
        {
          if ( m_pGT_DELAY_CODE->deleteRow(Plant,DelayCode) )
          {
            m_pGT_DELAY_CODE->commit();
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage, "", "GT_DELAY_CODE","cannot delete delay");

            m_pGT_DELAY_CODE->rollback();

            handleErrorCode(Key, 10920);
          }
        }
        else if ( State == DEF_GEN_STATES::Update || 
                  State == DEF_GEN_STATES::New      )
        {
          std::string Usercode = "L3";

          RetValue = RetValue && m_pGT_DELAY_CODE->updateInsertDelay(Plant, DelayCode, DelayGroup, DelayDesc, DelayDesc, Usercode, DelayDefaultDur, false,m_lastError);

          if ( RetValue )
          {
            m_pGT_DELAY_CODE->commit();
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage, "", "GT_DELAY_CODE","cannot update/insert delay");

            m_pGT_DELAY_CODE->rollback();

            handleErrorCode(Key, 10921);
          }
        }
      }

      //********    reset statushandler for plant *******************************************************************************


      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(L3_EvMsg::evL3DelayCodeUpdate);

      //********    Convert and check telegram data  ***********************************************************

      if ( RetValue )
      {
        DataKey       = generateDataKey(TlgName);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,CSMC_DBData::unspecString,true);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }
    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}

seqAnalysis CL3_TelegramHandler::handleGradeAnalysis(const std::string& Key, const std::string& AnalysisPrefix,const std::string& Type)
{
  string exceMsg = "CL3_TelegramHandler::handleGradeAnalysis()";
  seqAnalysis SeqAnal;
  try
  {
    std::map<long,std::pair<std::string,double> >::const_iterator it;
    std::map<long,std::pair<std::string,double> >::const_iterator end;

    if(Type == "Steel")
	{
		it = m_SteelElementMap.begin();
		end = m_SteelElementMap.end();
	}
	else
	{
		it = m_SlagElementMap.begin();
		end = m_SlagElementMap.end();
	}
    double Value;

	while (it != end)
	{	
		if(it->second.first == "O2")
		{
		   Value = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,  AnalysisPrefix + "O");
		}
		else if(it->second.first == "N2")
		{
		   Value = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,  AnalysisPrefix + "N");
		}
		else if(it->second.first == "H2")
		{
		   Value = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,  AnalysisPrefix + "H");
		}
		else if(it->second.first == "S_X")
		{
		   Value = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,  AnalysisPrefix + "S");
		}
		else
		{
		   Value = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,  AnalysisPrefix + (it->second.first).c_str());
		}

		sAnalysis Analysis;
        Analysis.Element        = (it->second.first).c_str();
		Analysis.Concentration  = Value;
		if(Value != 0.0) //as per model guys on 22.04.2015
		{
        CIntfData::insert(SeqAnal,Analysis);
		}
		it++;
	}//while (it != end)
	return SeqAnal;

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),exceMsg.c_str(), ""); 
	return SeqAnal;
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",exceMsg.c_str(), ""  );    
	return SeqAnal;
  } 

}

void CL3_TelegramHandler::SendEventMessage(const std::string& Key, 
                                            const std::string& TlgName,
                                            const std::string& DataKey,
                                            const std::string& PlantId,
                                            const std::string& HeatId,
                                            const std::string& TreatId,
                                            const std::string& OrderID,
                                            bool isPlantEvent)
{
  //Send all event messages, that are present in EventMessageVector
  std::stringstream strFunction;
  std::stringstream strAction;

  std::vector <std::string>::iterator EventMsgToSend;

  try
  {
    strFunction << "CL3_TelegramHandler::SendEventMessage";
    for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
    {
      string LogMessage = TlgName + " Data handled!";
      log(LogMessage,3);
      // sending event to event channel 
      CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
        m_pTelegram_Adapter->m_DestinationName,
        *EventMsgToSend,
        PlantId,
        "",
        "",
        isPlantEvent,
        HeatId,
        TreatId,
        DataKey);

      if ( OrderID != CSMC_DBData::unspecString )
      {
        Message.setOrderID(OrderID);
      }

      strAction << "sending event:" << TlgName;

      if( !m_EventHandler.dispatchEvent("","",Message) )
      {
        log(" Send Message" + Message.getDataKey() + "failed",2);
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", strFunction.str().c_str(),strAction.str().c_str()); 
  }
}


bool CL3_TelegramHandler::DoProcessTeemingLadle(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessTeemingLadle";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
	std::string OrderId = CSMC_DBData::unspecString;
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      std::string L3PlantID      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_TEEMING_LADLE::PlantUnit);
      std::string CustHeatID         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_TEEMING_LADLE::HeatId);
      std::string CustTreatID        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_TEEMING_LADLE::TreatId);
      long LadleNo               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::LadleNo);
      long LadleLife             = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::LadleLife);
      std::string LadleCondition    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_TEEMING_LADLE::LadleCondition);

      long SlideGateLife            = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::SlideGateLife);
      long PlateLife                = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::PlateLife);
      long NozzleLife               = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::NozzleLife);
      long TBarLife                 = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::TBarLife);
      long WellBlockLife            = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::WellBlockLife);

      long PP1Life                 = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::PP1Life);
      long PP2Life                 = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_L3_TEEMING_LADLE::PP2Life);


      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_TEEMING_LADLE::HeatId,              CustHeatID);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_TEEMING_LADLE::PlantUnit,              L3PlantID);
      RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_L3_TEEMING_LADLE::LadleNo,           LadleNo, 1, 99);
      RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_L3_TEEMING_LADLE::PlantUnit,           L3PlantID, "E1");

			m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatID, HeatId,TreatId, DEF_GC_PLANT_DEF::EAF);

      // convert L3 plant id
      // Plant specifier e.g. E1 = EAF 1, L1 = LF 1
      if ( !L3PlantID.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(L3PlantID);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

      if(!m_pGC_LADLE_DEF->select(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle))
			{
				m_pGC_LADLE_DEF->setLADLENO(LadleNo);
				m_pGC_LADLE_DEF->setLADLETYPE(DEF_GC_LADLE_TYPE::TeemingLadle);
				RetValue = RetValue && m_pGC_LADLE_DEF->insert();
			}

			if(m_pPD_LADLE->select(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle))
			{
				if(DEF_GC_THERM_STAT::C == LadleCondition || DEF_GC_THERM_STAT::H == LadleCondition || DEF_GC_THERM_STAT::M == LadleCondition)
				{
					m_pPD_LADLE->setTHERMALSTATUS(LadleCondition);
					RetValue = RetValue && m_pPD_LADLE->update();
				}
			}
			else
			{
				m_pPD_LADLE->setLADLENO(LadleNo);
				m_pPD_LADLE->setLADLETYPE(DEF_GC_LADLE_TYPE::TeemingLadle);
				if(DEF_GC_THERM_STAT::C == LadleCondition || DEF_GC_THERM_STAT::H == LadleCondition || DEF_GC_THERM_STAT::M == LadleCondition)
				{
					m_pPD_LADLE->setTHERMALSTATUS(LadleCondition);
				}
				RetValue = RetValue && m_pPD_LADLE->insert();
			}

			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::LadleLife,LadleLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::SlideGate,SlideGateLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::PlateLining,PlateLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::UpperNozzle,NozzleLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::TBarLife,TBarLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::Wellblock1,WellBlockLife,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::PorousPlug1,PP1Life,false);
			RetValue = RetValue && m_pPD_LADLE_LIFE_DATA->setLifeData(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle,DEF_GC_LADLE_PARTS::PorousPlug2,PP2Life,false);

			if(m_pPD_HEAT_DATA->select(HeatId,TreatId, DEF_GC_PLANT_DEF::EAF))
			{
				OrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
			}

			if (RetValue)
			{
				CDH_IN_Task::getInstance()->getStdConnection()->commit();

        DataKey       = generateDataKey(TlgName);

				m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,                DATA::LadleNo      , LadleNo);
				m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,              DATA::LadleType      , DEF_GC_LADLE_TYPE::TeemingLadle);

				EventMessageVector.push_back(EAF_EvMsg::evEAFChangeTapLadleData);        
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);

        SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,OrderId,true);

        log (TlgName + ": Finished", 3);
			}
			else
			{
				CDH_IN_Task::getInstance()->getStdConnection()->rollback();
			}

    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}


bool CL3_TelegramHandler::DoProcessSteelGradeChange(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessSteelGradeChange";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
	std::string OrderId = CSMC_DBData::unspecString;
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      std::string L3PlantID      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADE_CHANGE::PlantUnit);
      std::string CustHeatID     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADE_CHANGE::HeatId);
      std::string CustTreatID    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADE_CHANGE::TreatId);
      std::string OldGrade       = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADE_CHANGE::Old_Grade);
      std::string NewGrade       = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_STEELGRADE_CHANGE::New_Grade);


      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_STEELGRADE_CHANGE::HeatId,              CustHeatID);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_STEELGRADE_CHANGE::PlantUnit,           L3PlantID);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_STEELGRADE_CHANGE::New_Grade,           NewGrade);

      // convert L3 plant id
      // Plant specifier e.g. E1 = EAF 1, L1 = LF 1
      if ( !L3PlantID.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(L3PlantID);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

			if(Plant == DEF_GC_PLANT_DEF::EAF)
			{
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatID, HeatId,TreatId, DEF_GC_PLANT_DEF::EAF);
				EventMessageVector.push_back(EAF_EvMsg::evEAFSteelGradeChanged);   
			}
			else if(Plant == DEF_GC_PLANT_DEF::LF)
			{
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatID, HeatId,TreatId, DEF_GC_PLANT_DEF::LF);
				EventMessageVector.push_back(LF_EvMsg::evLFSteelGradeChanged);   
		  }
			else
			{
				 return RetValue;
			}
			
			if(m_pPD_HEAT_DATA->select(HeatId,TreatId, Plant))
			{
				OrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
			}

			if(RetValue)
			{
				DataKey       = generateDataKey(TlgName);
				m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,                DATA::SteelGradeCode      , NewGrade);

				m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
				SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,OrderId,true);

				log (TlgName + ": Finished", 3);
			}

    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}

bool CL3_TelegramHandler::DoProcessLadleChange(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CL3_TelegramHandler::DoProcessLadleChange";
  std::string HeatId;
  std::string TreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
	std::string OrderId = CSMC_DBData::unspecString;
  long PlantNo = CSMC_DBData::unspecLong;
  CDateTime Now;
  //--------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);
		

      //********    Read telegram data  ************************************************************************
      std::string L3PlantID      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_LADLE_CHANGE::PlantUnit);
      std::string CustHeatID     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_LADLE_CHANGE::HeatId);
      std::string CustTreatID    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_L3_LADLE_CHANGE::TreatId);
      long OldLadle              = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_LADLE_CHANGE::Old_LadleNo);
      long NewLadle              = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_L3_LADLE_CHANGE::New_LadleNo);


      //********    Convert and check telegram data  ***********************************************************   
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_LADLE_CHANGE::HeatId,              CustHeatID);
      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_L3_LADLE_CHANGE::PlantUnit,           L3PlantID);
      RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_L3_LADLE_CHANGE::New_LadleNo,         NewLadle,1,99);

      // convert L3 plant id
      // Plant specifier e.g. E1 = EAF 1, L1 = LF 1
      if ( !L3PlantID.empty() )
      {
        PlantId = m_pGC_Plant_Container->getL2PlantID(L3PlantID);

        if ( !PlantId.empty() )
        {
          Plant   = m_pGC_Plant_Container->getPlant(PlantId);
          PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId); 
        }
      }

			if(Plant == DEF_GC_PLANT_DEF::EAF)
			{
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatID, HeatId,TreatId, DEF_GC_PLANT_DEF::EAF);
				EventMessageVector.push_back(EAF_EvMsg::evEAFChangeTapLadleData);   
			}
			else if(Plant == DEF_GC_PLANT_DEF::LF)
			{				
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID( CustHeatID, HeatId,TreatId, DEF_GC_PLANT_DEF::LF);
				EventMessageVector.push_back(LF_EvMsg::evLFLadleDataChanged);   
			}
			else
			{
				return RetValue;
			}

			if(m_pPD_HEAT_DATA->select(HeatId,TreatId, Plant))
			{
				OrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
			}
			
			if(RetValue)
			{
				DataKey       = generateDataKey(TlgName);
				m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,                DATA::LadleNo      , NewLadle);
				m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,              DATA::LadleType      , DEF_GC_LADLE_TYPE::TeemingLadle);
			
				m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,2);
				SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,OrderId,true);

				log (TlgName + ": Finished", 3);
			}

    }
    catch (cCBS_DBExc &e)
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::SystemException& sExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), Function.c_str(), TlgName.c_str());
      RetValue = false;
    }
    catch(CORBA::Exception& cExc) 
    {
      m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
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
  }

  return RetValue;
}


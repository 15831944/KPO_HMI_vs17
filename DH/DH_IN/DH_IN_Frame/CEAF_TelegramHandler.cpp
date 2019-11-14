// Copyright (C) 2012 SMS Simag AG
#include <assert.h>

#include "Telcom_In_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CDataConversion.h"
#include "CDH_IN_Task.h"

#include "CGC_Recipe_L1Container.h"
#include "CGC_Plantgroup_Container.h"
#include "CGC_SourceContainer.h" 
#include "CGC_Charge_Dest_Container.h"
#include "CGC_PHASE.h"
#include "CGC_COOLWATER.h"
#include "CGCE_BURNER.h"
#include "CGCE_InjectionContainer.h"
#include "CLadleID.h"

#include "CSMC_EventLogEAFController.h"

#include "DEF_GC_COMP_STATUS.h"
#include "DEF_GC_HEAT_STATUS.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GT_PURP.h"
#include "DEF_GC_LADLE_POS.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GC_SAMPLELOC.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GCE_BURNER.h"
#include "DEF_GCE_BURNER_GASTYPE.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_SOURCE.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GC_PARAM_TYPE.h"
#include "DEF_GC_ACTION_DEF.h"
#include "DEF_GC_PLANTSTATUS.h"

#include "DEF_GC_SCRAP_CONT_ORDER_STATUS.h"

#include "CGT_MAT.h"
#include "CGT_MAT_PURP.h"
#include "CGT_PARAM.h"
#include "CGTE_PP_FLAME_PROFILE.h"

#include "CPP_ORDER.h" 
#include "CPP_ORDER_SINGLE_AIMS.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPD_PLANTSTATUS_PLANT.h"

#include "CPDE_CYCL_MEAS_DATA.h"
#include "CPDE_HEAT_DATA.h"
#include "CPD_HEAT_DATA_STIRR.h"

#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_SCRAP_CONTAINER_ORDER.h"



#include "CPD_ACTION.h"
#include "CPD_LADLE.h"

#include "CPD_COOLWATER.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_MAT_AVAIL.h"
#include "CPD_HEAT_REF.h"
#include "CHeatStatusContainer.h"

#include "DEF_GC_SCRAP_CONTAINER_TYPE.h"
#include "DEF_GC_SCRAP_CONTAINER_LOC.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PHASE.h"
#include "DEF_GC_STIRR_DEVICE.h"
#include "DEF_GC_CHARGE_DEST.h"
#include "DEF_GCE_INJECTION.h"
#include "DEF_GCE_INJECTION_TYPE.h"
#include "DEF_GC_PLANTGROUP_DESC.h"
#include "CREPORT_MOTOR_ENTRY.h"

#include "CPDH_HM_DATA.h"
#include "CPD_HOT_METAL.h"

#include "CPDE_HEAT_DATA_MELT.h"

#include "CSMC_RecipeHandler.h"

#include "CEAF_TelegramHandler.h"

CEAF_TelegramHandler::CEAF_TelegramHandler()
{
  std::stringstream strFunction;
  std::stringstream strAction;
  try
  {
    strFunction << "CEAF_TelegramHandler::CEAF_TelegramHandler()";

    cCBS_StdConnection* pConnection = CDH_IN_Task::getInstance()->getStdConnection();

    strAction << "CDH_IN_Task::getInstance()->getConnection() ";

    if(pConnection)
    {
      strAction << "Success get database connection ";

			std::string TempHeatId = "UNDEFINED";

      long PlantNo  = 1;
      std::string Plant = DEF_GC_PLANT_DEF::EAF;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);

      strAction << "Create DB classed instance ";
      m_pGC_COOLWATER               = new CGC_COOLWATER(pConnection);
      m_pGC_Plant_Container         = new CGC_Plant_Container(pConnection, Plant);
      m_pGC_Plantgroup_Container    = new CGC_Plantgroup_Container(pConnection);
      m_pHeatDataConverter          = new CHeatDataConverter(pConnection);
      m_pGC_Recipe_L1Container      = new CGC_Recipe_L1Container(pConnection,Plant); 
      m_pGC_SourceContainer         = new CGC_SourceContainer(pConnection,Plant,PlantNo);
      m_pGC_Charge_Dest_Container   = new CGC_Charge_Dest_Container(pConnection,Plant);
      m_pGC_PHASE					          = new CGC_PHASE(pConnection);
      m_pGCE_BURNER                 = new CGCE_BURNER(pConnection);
      m_pGCE_InjectionContainer     = new CGCE_InjectionContainer(pConnection,Plant,PlantNo);
      m_pGT_MAT                     = new CGT_MAT(pConnection);
      m_pGT_MAT_PURP                = new CGT_MAT_PURP(pConnection);
      m_pGT_PARAM                   = new CGT_PARAM(pConnection);
      m_pGTE_PP_FLAME_PROFILE       = new CGTE_PP_FLAME_PROFILE(pConnection);      

      m_pPP_HEAT                    = new CPP_HEAT(pConnection);
      m_pPP_HEAT_PLANT              = new CPP_HEAT_PLANT(pConnection);
      m_pPP_ORDER                   = new CPP_ORDER(pConnection);
      m_pPP_ORDER_SINGLE_AIMS       = new CPP_ORDER_SINGLE_AIMS(pConnection);      

      m_pPDE_CYCL_MEAS_DATA         = new CPDE_CYCL_MEAS_DATA(pConnection);
      m_pPDE_HEAT_DATA              = new CPDE_HEAT_DATA(pConnection);  

      m_pPD_ACTION                  = new CPD_ACTION(pConnection);
      m_pPD_COOLWATER               = new CPD_COOLWATER(pConnection);
      m_pPD_HEAT_DATA               = new CPD_HEAT_DATA(pConnection);
      m_pPD_RECIPE                  = new CPD_RECIPE(pConnection);
      m_pPD_RECIPE_ENTRY            = new CPD_RECIPE_ENTRY(pConnection);

      m_pPD_MAT_AVAIL               = new CPD_MAT_AVAIL(pConnection);

      m_pPD_LADLE                   = new CPD_LADLE(pConnection);
			m_pPD_PLANTSTATUS_PLANT       = new CPD_PLANTSTATUS_PLANT(pConnection);

			m_pREPORT_MOTOR_ENTRY         = new CREPORT_MOTOR_ENTRY(pConnection);

			m_pPD_HEAT_REF                = new CPD_HEAT_REF(pConnection);
			m_pHeatStatusContainer        = new CHeatStatusContainer(pConnection);

			m_pPD_SCRAP_CONTAINER_ORDER   = new CPD_SCRAP_CONTAINER_ORDER(pConnection);
			m_pPD_HEAT_DATA_LIQADD        = new CPD_HEAT_DATA_LIQADD(pConnection);

			m_pPDH_HM_DATA                = new CPDH_HM_DATA(pConnection);
			m_pPD_HOT_METAL               = new CPD_HOT_METAL(pConnection);

			m_pPDE_HEAT_DATA_MELT         = new CPDE_HEAT_DATA_MELT(pConnection);

			strAction << "create DB classes instance successful ";

    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CEAF_TelegramHandler","No database connection");

      // to guaranty EL_ExceptionCaught to be sent to CBS service
      Sleep(3000);

      // terminate programm in case of starting up without getting connection to database
      exit(EXIT_FAILURE);
    }

    log(strFunction.str() + " " + strAction.str(), 1);

  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      strFunction.str().c_str(), strAction.str().c_str()); 

  }
  catch(CORBA::SystemException& sExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown Exception", "CEAFTelegramHandler","");
    throw;
  }
}

CEAF_TelegramHandler::~CEAF_TelegramHandler()
{ 
  std::stringstream strFunction;
  std::stringstream strAction;

  try
  {
    strFunction << "CEAF_TelegramHandler::~CEAF_TelegramHandler()";

    if (m_pGC_Plant_Container)        {delete m_pGC_Plant_Container;        m_pGC_Plant_Container = 0;}
    if (m_pGC_Plantgroup_Container)   {delete m_pGC_Plantgroup_Container;   m_pGC_Plantgroup_Container = 0;}
    if (m_pHeatDataConverter)         {delete m_pHeatDataConverter;         m_pHeatDataConverter = 0;}
    if (m_pGC_Recipe_L1Container)     {delete m_pGC_Recipe_L1Container;     m_pGC_Recipe_L1Container = 0;  }
    if (m_pGC_SourceContainer)        {delete m_pGC_SourceContainer;        m_pGC_SourceContainer = 0;}
    if (m_pGC_Charge_Dest_Container)  {delete m_pGC_Charge_Dest_Container;  m_pGC_Charge_Dest_Container = 0;}
    if (m_pGC_PHASE)				          {delete m_pGC_PHASE;                  m_pGC_PHASE = 0;}
    if (m_pGC_COOLWATER)			        {delete m_pGC_COOLWATER;              m_pGC_COOLWATER = 0;}
    if (m_pGCE_BURNER)				        {delete m_pGCE_BURNER;                m_pGCE_BURNER = 0;}
    if (m_pGCE_InjectionContainer)		{delete m_pGCE_InjectionContainer;    m_pGCE_InjectionContainer = 0;}
    if (m_pGT_MAT)                    {delete m_pGT_MAT;                    m_pGT_MAT = 0;}
    if (m_pGT_MAT_PURP)               {delete m_pGT_MAT_PURP;               m_pGT_MAT_PURP = 0;}
    if (m_pGT_PARAM)                  {delete m_pGT_PARAM;                  m_pGT_PARAM = 0;  }
    if (m_pGTE_PP_FLAME_PROFILE)      {delete m_pGTE_PP_FLAME_PROFILE;      m_pGTE_PP_FLAME_PROFILE = 0;} 
  
    if (m_pPP_ORDER)                  {delete m_pPP_ORDER;                  m_pPP_ORDER = 0;}
    if (m_pPP_HEAT_PLANT)             {delete m_pPP_HEAT_PLANT;             m_pPP_HEAT_PLANT = 0;  }
    if (m_pPP_ORDER_SINGLE_AIMS)      {delete m_pPP_ORDER_SINGLE_AIMS;      m_pPP_ORDER_SINGLE_AIMS =0;}
    if (m_pPP_HEAT)                   {delete m_pPP_HEAT;                   m_pPP_HEAT = 0;}

    if (m_pPDE_CYCL_MEAS_DATA)        {delete m_pPDE_CYCL_MEAS_DATA;        m_pPDE_CYCL_MEAS_DATA = 0;  }
    if (m_pPDE_HEAT_DATA)             {delete m_pPDE_HEAT_DATA;             m_pPDE_HEAT_DATA = 0;}

    if (m_pPD_ACTION)                 {delete m_pPD_ACTION;                 m_pPD_ACTION = 0;  }
    if (m_pPD_COOLWATER)              {delete m_pPD_COOLWATER;              m_pPD_COOLWATER = 0; }
    if (m_pPD_HEAT_DATA)              {delete m_pPD_HEAT_DATA;              m_pPD_HEAT_DATA = 0;}
    if (m_pPD_RECIPE)                 {delete m_pPD_RECIPE;                 m_pPD_RECIPE = 0;}
    if (m_pPD_RECIPE_ENTRY)           {delete m_pPD_RECIPE_ENTRY;           m_pPD_RECIPE_ENTRY = 0;}

    if (m_pPD_MAT_AVAIL)              {delete m_pPD_MAT_AVAIL;              m_pPD_MAT_AVAIL = 0;}

    if (m_pREPORT_MOTOR_ENTRY)        {delete m_pREPORT_MOTOR_ENTRY;        m_pREPORT_MOTOR_ENTRY = 0;}
		
    if (m_pPD_LADLE)                  {delete m_pPD_LADLE;                  m_pPD_LADLE = 0;}
    if (m_pPD_PLANTSTATUS_PLANT)      {delete m_pPD_PLANTSTATUS_PLANT;      m_pPD_PLANTSTATUS_PLANT = 0;}
		
    if (m_pPD_HEAT_REF)               {delete m_pPD_HEAT_REF;               m_pPD_HEAT_REF = 0;}
		if (m_pHeatStatusContainer)       { delete m_pHeatStatusContainer;      m_pHeatStatusContainer = 0;}

		
		if (m_pPD_SCRAP_CONTAINER_ORDER)  { delete m_pPD_SCRAP_CONTAINER_ORDER;      m_pPD_SCRAP_CONTAINER_ORDER = 0;}
		if (m_pPD_HEAT_DATA_LIQADD)       { delete m_pPD_HEAT_DATA_LIQADD;           m_pPD_HEAT_DATA_LIQADD = 0;}

		if (m_pPDH_HM_DATA)               { delete m_pPDH_HM_DATA;                 m_pPDH_HM_DATA = 0;}
		if (m_pPD_HOT_METAL)              { delete m_pPD_HOT_METAL;                m_pPD_HOT_METAL = 0;}

		if (m_pPDE_HEAT_DATA_MELT)        { delete m_pPDE_HEAT_DATA_MELT;          m_pPDE_HEAT_DATA_MELT = 0;}
		

    strAction << "Delete DBClasses instances ";
  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(), strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", strFunction.str().c_str(),strAction.str().c_str()); 
  }
}
bool CEAF_TelegramHandler::doOnComplete(const std::string& Key, const std::string& TlgName)
{
  //message list used to store the dispatch message
  bool RetValue = true;
  std::stringstream strFunction;
  std::stringstream strAction;
  try
  {
    strFunction << "CEAF_TelegramHandler::doOnComplete;";
    strFunction <<" TlgName:"<<TlgName;

    EventMessageVector.clear();

    if (TlgName == "EAL200")
      RetValue =  DoProcessEAL200ACK(Key,TlgName); 
    else if(TlgName == "EAL201")
      RetValue =  DoProcessEAL201WatchDog(Key,TlgName); 
    else if(TlgName == "EAL203")
      RetValue =  DoProcessEAL203HeatAnnouncement(Key,TlgName); 
    else if(TlgName == "EAL204")
      RetValue =  DoProcessEAL204HeatStart(Key,TlgName); 
    else if(TlgName == "EAL205")
      RetValue =  DoProcessEAL205HeatEnd(Key,TlgName); 
    else if(TlgName == "EAL206")
      RetValue =  DoProcessEAL206HeatCancel(Key,TlgName); 
    else if(TlgName == "EAL207")
      RetValue =  DoProcessEAL207Tapping(Key,TlgName); 
    else if(TlgName == "EAL209")
      RetValue =  DoProcessEAL209SampTaken(Key,TlgName); 
    else if(TlgName == "EAL211")
      RetValue =  DoProcessEAL211TempTaken(Key,TlgName); 
    else if(TlgName == "EAL214")
      RetValue =  DoProcessEAL214TapLadleData(Key,TlgName); 
    else if(TlgName == "EAL215")
      RetValue =  DoProcessEAL215BasketHMDischarged(Key,TlgName);
    else if(TlgName == "EAL216")
      RetValue =  DoProcessEAL216DeslagStatus(Key,TlgName); 

	 //else if(TlgName == "EAL217")
   //   RetValue =  DoProcessEAFL217DelayStatus(Key,TlgName); //SARS because all possible delays are handled by tracking on discussion with Mr. J.P. Singh

    else if(TlgName == "EAL220")
      RetValue =  DoProcessEAL220CompMode(Key,TlgName); 
    else if(TlgName == "EAL221")
      RetValue =  DoProcessEAL221FurnStatus(Key,TlgName); 
    else if(TlgName == "EAL222")
      RetValue =  DoProcessEAL222ElecStatus(Key,TlgName); 
    else if(TlgName == "EAL223")
      RetValue =  DoProcessEAL223ElecActVal(Key,TlgName); 
    else if(TlgName == "EAL224")
      RetValue =  DoProcessEAL224InjectionMatAvail(Key,TlgName); 
    else if(TlgName == "EAL225")
      RetValue =  DoProcessEAL225InjectionMatStatus(Key,TlgName); 
    else if(TlgName == "EAL226")
      RetValue =  DoProcessEAL226InjectionMatActVal(Key,TlgName); 
    else if(TlgName == "EAL227")
      RetValue =  DoProcessEAL227BurnerGasAvail(Key,TlgName); 
    else if(TlgName == "EAL228")
      RetValue =  DoProcessEAL228BurnerStatus(Key,TlgName); 
    else if(TlgName == "EAL229")
      RetValue =  DoProcessEAL229BurnerActVal(Key,TlgName); 
    else if(TlgName == "EAL233")
      RetValue =  DoProcessEAL233CoolingWater(Key,TlgName); 

    else if(TlgName == "EAL234") //SARS
      RetValue =  DoProcessEAL234VesselStirrStatus(Key,TlgName); 
    else if(TlgName == "EAL235") //SARS
      RetValue =  DoProcessEAL235VesselStirrCons(Key,TlgName); 
				
		else if(TlgName == "EAL236")
      RetValue =  DoProcessEAL236LadleStirrStatus(Key,TlgName); 
    else if(TlgName == "EAL237")
      RetValue =  DoProcessEAL237LadleStirrCons(Key,TlgName); 
    else if(TlgName == "EAL240")
      RetValue =  DoProcessEAL240EAFFlameProfile(Key,TlgName); 
    else if(TlgName == "EAL241")
      RetValue =  DoProcessEAL241Level1Param(Key,TlgName); 
    else if(TlgName == "EAL250")
      RetValue =  DoProcessEAL250WasteGas(Key,TlgName); 
    else if(TlgName == "EAL260")
      RetValue =  DoProcessEAL260MatHandReport(Key,TlgName); 
    else if(TlgName == "EAL261")
      RetValue =  DoProcessEAL261MatAvailibilty(Key,TlgName);
    else if(TlgName == "EAL262")
      RetValue =  DoProcessEAL262MaterialFeedingSystem(Key,TlgName); 
    else if(TlgName == "EAL263")
      RetValue =  DoProcessEAL263MaterialFeedingStatus(Key,TlgName); 
    else if(TlgName == "EAL270")
      RetValue =  DoProcessEAL270LiqMatReport(Key,TlgName); 
    else if(TlgName == "EAL280")
      RetValue =  DoProcessEAL280PhaseReport(Key,TlgName);
    else if(TlgName == "SYL292")
      RetValue =  DoProcessSYL292ScrapLoadingResults(Key,TlgName); 
    else if(TlgName == "SYL293")
      RetValue =  DoProcessSYL293ScrapLoadingInstructionRequest(Key,TlgName); 
    else if(TlgName == "SYL295")
      RetValue =  DoProcessSYL295ScrapMaterialRequest(Key,TlgName); 
    else if(TlgName == "EAL290") //motor maintenance as per JSW requirement
      RetValue =  DoProcessMotorMaintenance(Key,TlgName); 		
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
void CEAF_TelegramHandler::SendEventMessage(const std::string& Key, 
                                            const std::string& TlgName,
                                            const std::string& DataKey,
                                            const std::string& PlantId,
                                            const std::string& PlantLocation,
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
    strFunction << "CEAF_TelegramHandler::SendEventMessage";
    for ( EventMsgToSend = EventMessageVector.begin(); EventMsgToSend != EventMessageVector.end();++EventMsgToSend)
    {
      string LogMessage = TlgName + " Data handled!";
      log(LogMessage,3);
      // sending event to event channel 
      CEventMessage Message(m_pTelegram_Adapter->m_SenderName,
        m_pTelegram_Adapter->m_DestinationName,
        *EventMsgToSend,
        PlantId,
        PlantLocation,
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

			//sankar as per JSW requirement
			handleEventLog(*EventMsgToSend,HeatId,TreatId,PlantId,DataKey);

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

bool CEAF_TelegramHandler::DoProcessEAL200ACK(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL201WatchDog(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL201WatchDog";

  try
  {
    log (TlgName + ": Started", 3);

    //********    Read telegram data  ************************************************************************

    long UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL201::UnitNo);

    //********    reset statushandler  ***********************************************************************

    //********    Convert and check telegram data  ***********************************************************

    //********    Define Event *******************************************************************************

    //********    Write telegram data  ***********************************************************************

    //********    End processing data  ***********************************************************************

    log (TlgName + ": Finished", 3);
  }
  catch (cCBS_DBExc &e)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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

bool CEAF_TelegramHandler::DoProcessEAL203HeatAnnouncement(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL203HeatAnnouncement";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      

  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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

      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL203::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::TreatId);

      std::string OrderId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::ProdOrderId);
      std::string SteelGradeCode  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::SteelGradeCode);
      //long AimTemp                = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL203::AimTemp);
      //long AimWeight              = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL203::AimWeight);
      double AimTemp              = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL203::AimTemp);
      double AimWeight            = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL203::AimWeight);

      std::string HeatIdCust      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::HeatIdCust);
      std::string TreatIdCust     = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL203::TreatIdCust);

      CORBA::Any SpareAny         = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL203::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      DEF::seqString SeqAnySpare;
      CIntfData::FromAny(SeqAnySpare,SpareAny);

      OrderId         = CDataConversion::Trim(OrderId);
      SteelGradeCode  = CDataConversion::Trim(SteelGradeCode);

      //********    reset statushandler for plant *******************************************************************************

      m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFHeatAnnouncement);

      //********    Convert and check telegram data  ***********************************************************

      if ( !checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId) )
      {
        CustHeatId      = CDataConversion::Trim(HeatIdCust);
        CustTreatId     = CDataConversion::Trim(TreatIdCust);
      }

      checkValidity(TlgName,"UnitNo",UnitNo,1,2);

      std::string Message = TlgName;

      if ( RetValue && m_pPP_HEAT_PLANT->selectByCustData(CustHeatId,CustTreatId,Plant,false) )
      {
        HeatId  = m_pPP_HEAT_PLANT->getHEATID(1);
        TreatId = m_pPP_HEAT_PLANT->getTREATID(1);

        if ( OrderId == DEF::Inv_String || OrderId.empty() )
        {
          if ( m_pPP_HEAT->select(HeatId) )
          {
            OrderId = m_pPP_HEAT->getPRODORDERID(1);

            if ( OrderId != CSMC_DBData::unspecString && m_pPP_ORDER->select(OrderId) )
            {
              SteelGradeCode = m_pPP_ORDER->getSTEELGRADECODE(1);
            }
          }
        }

        Message += ": get planning data";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadInfo(sMessage, "HEATID - TREATID","PP_HEAT_PLANT",Message.c_str());
      }
      else
      {
        Message += ": Heat is not planned";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadWarning(sMessage, "HeatID - TreatID","PP_HEAT_PLANT",Message.c_str());
      }

      if ( RetValue )
      {
        DataKey       = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustHeatID       ,CustHeatId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustTreatIdUser  ,CustTreatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::CustTreatID      ,CustTreatId);

        // tracker insert or update pp data
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::OrderIdUser    ,OrderId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::OrderId        ,OrderId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SteelGradeCode ,SteelGradeCode);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::TempAim        ,AimTemp);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::AimWeight      ,AimWeight);

        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::TreatmentMode  ,2);


        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::UserCode,      "L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatId empty or unknown",CustHeatId.c_str());
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL204HeatStart(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL204HeatStart";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
  CDateTime Now;
  
  //-------------------------------------------------

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL204::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL204::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL204::TreatId);

      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL204::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFHeatStart);

      //********    Convert and check telegram data  ***********************************************************

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1  ,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL205HeatEnd(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL205HeatEnd";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;  

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = DEF::Inv_Long;

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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL205::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL205::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL205::TreatId);
      LadleId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL205::LadleId);

      long  ActionFlag    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL205::ActionFlag);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL205::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      if( ActionFlag == 1 )        //1: heat end 
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFHeatEnd);

				EventMessageVector.push_back(EAF_EvMsg::evEAFHeatDeparture); //SARS
      }
      else if( ActionFlag == 2 )    //2: heat departure
      {
				//SARS
				if ( m_pPD_HEAT_DATA->select(HeatId,TreatId,DEF_GC_PLANT_DEF::EAF) )
				{
					if( m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1) != CSMC_DBData::unspecDate)
						return true;
				}

				EventMessageVector.push_back(EAF_EvMsg::evEAFHeatEnd); //SARS

        EventMessageVector.push_back(EAF_EvMsg::evEAFHeatDeparture);
      }

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo     ,DEF::Inv_Long,LONG_MIN);
      CDataConversion::SetInvalidToDefault(ActionFlag ,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1  ,2);
      checkValidity(TlgName,"ActionFlag",ActionFlag ,1  ,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
            
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        LadleId            = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) ) //SARS
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo,LadleNo);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL206HeatCancel(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL206HeatCancel";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL206::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL206::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL206::TreatId);

      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL206::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFHeatCancellation);

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1  ,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::PlantID,PlantId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::CustHeatIdUser   ,CustHeatId);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::CustTreatIdUser  ,CustTreatId);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL207Tapping(const std::string& Key, const std::string& TlgName)
{

  bool RetValue = true;
  //------------ general variables ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant;

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = DEF::Inv_Long;
  CDateTime Now;
  //------------ general variables ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  log (TlgName + ": Started", 3);

  if (m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      //********    Read telegram data  ************************************************************************
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL207::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL207::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL207::TreatId);
      LadleId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL207::LadleId);
      
      long ActionFlag     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL207::ActionFlag);

      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL207::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

			//SARS: JSW specific if tapEnd times comes more than one time
			if( ActionFlag == 2 && m_pPD_ACTION->select(HeatId,TreatId,Plant,DEF_GC_ACTION_DEF::TappingEnd,CSMC_DBData::unspecDate))
			{
				return RetValue;
			}

      //********    Define Event *******************************************************************************
      if ( ActionFlag == 1 )//1 = Tapping start
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFTappingStart);
      }
      else if ( ActionFlag == 2 )//2 = Tapping end
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFTappingEnd);
      }

      //********    Convert and check telegram data  ***********************************************************

      LadleId            = CDataConversion::Trim(LadleId);

      CLadleID LadleID;

      if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) ) //SARS
      {
        LadleType          = LadleID.getLadleType(LadleId);
        LadleNo            = LadleID.getLadleNo(LadleId);
      }

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1  ,2);
      checkValidity(TlgName,"LadleNo"   ,LadleNo,    1  ,99);
      checkValidity(TlgName,"ActionFlag",ActionFlag, 1  ,2);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());
        
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey.c_str(),DATA::LadleNo,    LadleNo );
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::LadleType,  LadleType );
        
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
				//SARS: JSW specific
				if ( ActionFlag == 1 )//1 = Tapping start
				{
					DoAutoHeatScheduleCreation();
				}

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL209SampTaken(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL209SampTaken";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL209::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL209::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL209::TreatId);

      long SampleType     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL209::SampleType);
      long SampleCounter  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL209::SampleCounter);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL209::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    Define Event *******************************************************************************

      if ( SampleType == 2 )        //Steel
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFSteelSampleTaken);
      }
      else if ( SampleType == 3 )   //Slag
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFSlagSampleTaken);
      }

      //********    Convert and check telegram data  ***********************************************************
           
      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo",         UnitNo,         1 ,2);
      checkValidity(TlgName,"SampleType",     SampleType,     2 ,3);
      checkValidity(TlgName,"SampleCounter",  SampleCounter,  0 ,99);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
    
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        if ( SampleType == 2 )        //Steel
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::SteelSampleTime,Now.assDate ());
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,        DATA::SampleType,DEF_GC_MEASUREMENT_TYPE::Steel);
        }
        else if ( SampleType == 3 )   //Slag
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::SlagSampleTime,Now.assDate ());
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType,DEF_GC_MEASUREMENT_TYPE::Slag);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::SampleUsable,    1);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::SampleMode,      DEF_GC_SAMPLEMODE::automatic);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::ProcessStage,    DEF_PROCESS_STAGE::InProcess);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SampleLocation,  DEF_GC_SAMPLELOC::EAF);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::SampleNo,        SampleCounter);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SampleId,        CDataConversion::LongToString(SampleCounter));

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,DATA::UserCode,         "L1");

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,   Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL211TempTaken(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL211TempTaken";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL211::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL211::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL211::TreatId);

      long MeasType       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL211::MeasType); 
      long MeasNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL211::MeasNo);
      double Temp         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::Temp); 
      double ConcO2       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::ConcO2); 
      double ConcAl       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::ConcAl);
      double ConcC        = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::ConcC);
      double ConcFeO      = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::ConcFeO);
      double ConcMnO      = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL211::ConcMnO);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL211::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    Convert and check telegram data  ***********************************************************

      checkValidity(TlgName,"UnitNo"  ,UnitNo   ,1  ,2);
      checkValidity(TlgName,"MeasType",MeasType ,4  ,6);   // futere check 4..6 if CeloxSlag is available
      checkValidity(TlgName,"MeasNo"  ,MeasNo   ,1  ,99);

      checkValidityToDefault(TlgName,"Temp"    ,Temp    ,1000.,2000.    , 0.);
      checkValidityToDefault(TlgName,"ConcO2"  ,ConcO2  ,0.   ,1000000. , 0.);
      checkValidityToDefault(TlgName,"ConcAl"  ,ConcAl  ,0.   ,1000000. , 0.);
      checkValidityToDefault(TlgName,"ConcC"   ,ConcC   ,0.   ,1000000. , 0.);
      checkValidityToDefault(TlgName,"ConcFeO" ,ConcFeO ,0.   ,1000000. , 0.);
      checkValidityToDefault(TlgName,"ConcMnO" ,ConcMnO ,0.   ,1000000. , 0.);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        std::string SampleId = DEF::Inv_String;

        if ( MeasNo > 0 && MeasNo != DEF::Inv_Long )
        {
          SampleId = CDataConversion::LongToString(MeasNo);
        }

        //********    Define Event *******************************************************************************

        if( MeasType == 4 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFTempMeasurement);
        }
        else if( MeasType == 5 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFCeloxMeasurement);
        }
        else if( MeasType == 6 ) // event not yet implemented
        {
          //EventMessageVector.push_back(EAF_EvMsg::evEAFCeloxSlagMeasurement);
        }

        //********    Write telegram data  ***********************************************************************

        std::string Message;
        std::string ProductID = HeatId + "_" + TreatId;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",ProductID,CustHeatId);

        if ( MeasType == 4 )        //Temp
        {
          if ( Temp > 0. )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Temp);
            m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasTemp    ,Temp);
          }
          else
          {
            Message += "TEMP - for HeatID " + CustHeatId; 

            Message += " Temp ";
            pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), Temp);

            RetValue = false;
          }
        }// if ( MeasType == 4 )        //Temp
        else if ( MeasType == 5 )   //Celox
        {
          if ( (Temp > 0. && ( ConcAl > 0. || ConcO2 > 0. || ConcC  > 0.)) )                                                                 
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Celox);

            if ( Temp > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasTemp      ,Temp);
            }
            if ( ConcAl > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasAlConc    ,double(ConcAl/10000.));  // ppm -> %
            }
            if ( ConcO2 > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasO2Conc    ,double(ConcO2/10000.));  // ppm -> %
            }
            if ( ConcC > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasCarbonConc,double(ConcC/10000.));   // ppm -> %
            }
          }
          else
          {
            Message += "CELOX - for HeatID " + CustHeatId; 

            if ( !(Temp > 0.) )
            {
              Message += " Temp ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), Temp);
            }
            if ( !(ConcAl > 0.) )
            {
              Message += " ConcAl ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcAl);
            }
            if ( !(ConcO2 > 0.) )
            {
              Message += " ConcO2 ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcO2);
            }
            if ( !(ConcC > 0.) )
            {
              Message += " ConcC ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcC);
            }

            RetValue = false;
          }
        }//if ( MeasType == 5 )   //Celox
        else if ( MeasType == 6 )   //CeloxSlag
        {
          if ( ConcFeO > 0. || ConcMnO > 0. )
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey,DATA::SampleType    ,DEF_GC_MEASUREMENT_TYPE::Celox_Slag);

            if ( ConcFeO > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasFeOConc   ,double(ConcFeO/10000.)); // ppm -> %
            }

            if ( ConcMnO > 0. )
            {
              m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MeasMnOConc   ,double(ConcMnO/10000.)); // ppm -> %
            }
          }// if ( (ConcFeO != DEF::Inv_Double && ConcFeO > 0.) || (ConcMnO != DEF::Inv_Double && ConcMnO > 0.) )
          else
          {
            Message += "CELOX/SLAG - for HeatID " + CustHeatId;

            if ( !(ConcFeO > 0.) )
            {
              Message += " ConcFeO ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcFeO);
            }

            if ( !(ConcMnO > 0.) )
            {
              Message += " ConcMnO ";
              pEventLog->EL_MeasurementRejected(sMessage, Message.c_str(), ConcMnO);
            }

            RetValue = false;
          }
        }// if ( MeasType == 6 )   //CeloxSlag

        if ( RetValue )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(), DATA::DateTime     ,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::PlantID            ,PlantId);

          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleUsable         ,1);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::SampleNo             ,MeasNo);    
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SampleId           ,SampleId);   

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::SampleLocation     ,DEF_GC_SAMPLELOC::EAF);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::ProcessStage       ,DEF_PROCESS_STAGE::InProcess);

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

          //********    End processing data  ***********************************************************************
        }

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL214TapLadleData(const std::string& Key, const std::string& TlgName)
{
  //=========================    Update Aim Departure Time   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL214::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL214::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL214::TreatId);

      LadleId      = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL214::LadleId);

      long LadleStatus      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL214::LadleStatus);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      LadleId   = CDataConversion::Trim(LadleId);

      CLadleID LadleID;

      if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) )
      {
        LadleType          = LadleID.getLadleType(LadleId);
        LadleNo            = LadleID.getLadleNo(LadleId);
      }

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);   

        checkValidity(TlgName,Telegram_EAL214::UnitNo       ,UnitNo       ,1,2);
        checkValidity(TlgName,Telegram_EAL214::LadleStatus  ,LadleStatus  ,1,3);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(EAF_EvMsg::evEAFTapLadleData);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType          ,LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo            ,LadleNo);

        if( LadleStatus == 1 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::TapLadleStatus, DEF_THERMAL_STATUS::Low);
        }
        else if( LadleStatus == 2 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::TapLadleStatus, DEF_THERMAL_STATUS::Medium);
        }
        else if( LadleStatus == 3 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::TapLadleStatus, DEF_THERMAL_STATUS::High);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CEAF_TelegramHandler::DoProcessEAL214TapLadleData(const std::string& Key, const std::string& TlgName)


bool CEAF_TelegramHandler::DoProcessEAL215BasketHMDischarged(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL215BasketHMDischarged";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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

      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL215::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL215::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL215::TreatId);

      long  ChargeSeq         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL215::ChargeSeq);
      long  BasketNo          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL215::BasketNo);
      double BasketWeight     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL215::BasketWeight);
      long  LastBasket        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL215::LastBasket);
      std::string  HMLadleId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL215::HMLadleId);
      double  HMWeight        = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL215::HMWeight);
      long  LastHMLadle       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL215::LastHMLadle);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

			//for test bacause L1 data not coming and later remove it*********************
			ChargeSeq = 1;
			//if(TempHeatId != HeatId)
			//{
			//	TempCount = 1;

			//	HMWeight = 0.0;
			//	if( BasketWeight == 0.0) 
			//		BasketWeight = 15000.0;

			//	TempHeatId = HeatId;
			//}
			//else
			//{
			//	if(TempCount == 2) return RetValue;

			//	BasketWeight = 0.0;
			//	if( HMWeight == 0.0) 
			//		HMWeight = 89000.0;

			//	TempCount = 2;
			//}

      //********    Define Event *******************************************************************************
      if ( BasketWeight > 0.01 )
      {
				ChargeSeq = getNextChargeNo(HeatId,TreatId,"BASKET"); //SARS
				BasketNo = ChargeSeq; //SARS

        EventMessageVector.push_back(EAF_EvMsg::evEAFHandleBasketDischarged);
      }
      if ( HMWeight > 0.01 )
      {
				ChargeSeq = getNextChargeNo(HeatId,TreatId,"HM"); //SARS
				//HMLadleId = "H" + CDataConversion::LongToString(ChargeSeq); //SARS
				HMLadleId = "H" + CDataConversion::LongToString(getNextLadleNo()); //SARS

				//SARS
				if (m_StatusHandler.getStatus(PlantId, DEF_DEVICES::Roof) == 0 ) //roof down
				{
					EventMessageVector.push_back(EAF_EvMsg::evEAFChargedHotMetalLaunder);
				}
				else
				{
					EventMessageVector.push_back(EAF_EvMsg::evEAFChargedHotMetalRoof);
				}
				
        EventMessageVector.push_back(EAF_EvMsg::evEAFChargedHotMetal);
      }

      //********    Convert and check telegram data  ***********************************************************
           
      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      HMLadleId = CDataConversion::Trim(HMLadleId);

      CLadleID LadleID;

	  //SRKO-20AUG2013
      //if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::HotMetalLadle, LadleId) )
			//HMLadleId = "H1";
			//if ( HMLadleId == DEF::Inv_String || HMLadleId.empty() || HMLadleId == "H" || HMLadleId == "-1") //SARS default Ladleno
			//{
			//	HMLadleId = "H1";
			//}

      if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::HotMetalLadle, HMLadleId) )
      {
        LadleType          = LadleID.getLadleType(HMLadleId);
        LadleNo            = LadleID.getLadleNo(HMLadleId);
      }

      checkValidity(TlgName,"UnitNo"    ,UnitNo     ,1  ,2);

      if ( BasketWeight > 0.01 )
      {
        checkValidity(TlgName, "BasketNo",     BasketNo,     1, 99);
        checkValidity(TlgName, "ChargeSeq",    ChargeSeq,    1, 3);
        checkValidity(TlgName, "BasketWeight", BasketWeight, 0., 120000.);//kg
        checkValidity(TlgName, "LastBasket",   LastBasket,   0, 1);
      }
      if ( HMWeight > 0.01 )
      {
        checkValidity(TlgName, "HMLadleId",    LadleNo,     1, 99);
        checkValidity(TlgName, "HMWeight",     HMWeight,    0., 120000.);//kg
        checkValidity(TlgName, "LastHMLadle",  LastHMLadle, 0, 1);
      }

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        if ( BasketWeight > 0.01 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::BasketInSeq, ChargeSeq);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::BasketId, BasketNo);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LastBasket, LastBasket);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::BasketLocation, DEF_GC_SCRAP_CONTAINER_LOC::EAF);
					m_pTelegram_Adapter->m_pIntf_OUT->setDouble  (DataKey, DATA::BasketWeight, BasketWeight ); //SARS
        }
        if ( HMWeight > 0.01 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::LadleType, LadleType);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LadleNo, LadleNo);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::LastLadle, LastHMLadle);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::ChargeSeq, ChargeSeq);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::SteelMassAct, HMWeight ); //SARS					
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL216DeslagStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL216DeslagStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL216::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL216::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL216::TreatId);

      long DeslaggingStat = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL216::DeslaggingStat);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL216::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      // m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      if( DeslaggingStat == 1 )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFDeslaggingStart);
      }
      else if( DeslaggingStat == 0 )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFDeslaggingEnd);
      }

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"          ,UnitNo         ,1 ,2);
      checkValidity(TlgName,"DeslaggingStat"  ,DeslaggingStat ,0 ,1);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::DateTime,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL220CompMode(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL220CompMode";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL220::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL220::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL220::TreatId);

      long ModeElec         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeElec);
      long ModeInj          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeInj);
      long ModeMat          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeMat);
      long ModeBurner       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeBurner);
      long ModeStirring     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeStirring);
      long ModeContFeeding  = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeContFeeding);
      long ModeTappingBatch = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL220::ModeTappingBatch);
      CORBA::Any SpareAny   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL220::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFSetComputerMode);

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"          ,UnitNo           ,1  ,2);
      checkValidity(TlgName,"ModeElec"        ,ModeElec         ,0  ,2);        
      checkValidity(TlgName,"ModeInj"         ,ModeInj          ,0  ,2);        
      checkValidity(TlgName,"ModeMat"         ,ModeMat          ,0  ,2);        
      checkValidity(TlgName,"ModeBurner"      ,ModeBurner       ,0  ,2);     
      checkValidity(TlgName,"ModeStirring"    ,ModeStirring     ,0  ,2); 
      checkValidity(TlgName,"ModeContFeeding" ,ModeContFeeding  ,0  ,3);    
      checkValidity(TlgName,"ModeTappingBatch",ModeTappingBatch  ,0  ,3);    

      sComputerMode    ComputerMode;      
      seqComputerModes SeqComputerModes;  

      //============================= Electric =======================================================
      ComputerMode.Device = DEF_COMP_MODES::Electric;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeElec == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeElec > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= Injection =======================================================
      ComputerMode.Device = DEF_COMP_MODES::Injection;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeInj == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeInj > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= MatHandle =======================================================
      ComputerMode.Device = DEF_COMP_MODES::MatHandle;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;

      if(ModeMat == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeMat > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      // *******************************************************************************************
      // FUXIN specific, ComputerMode Burner from/for L1 is represented by ComputerMode GasLance in L2
      //============================= Burner =======================================================
      ComputerMode.Device = DEF_COMP_MODES::Burner;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeBurner == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeBurner > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);
      //============================= Gas Lance =======================================================
      ComputerMode.Device = DEF_COMP_MODES::GasLance;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeBurner == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeBurner > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= Stirring =======================================================
      ComputerMode.Device = DEF_COMP_MODES::Stirring;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeStirring == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeStirring > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= Pattern Feeding =======================================================
      ComputerMode.Device = DEF_COMP_MODES::PatternFeed;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeContFeeding == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeContFeeding > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= Dynamic Feeding =======================================================
      ComputerMode.Device = DEF_COMP_MODES::DynamicFeed;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeContFeeding == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeContFeeding > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);

      //============================= Tapping Batch =======================================================
      ComputerMode.Device = DEF_COMP_MODES::TappingBatch;
      ComputerMode.Status = DEF_GC_COMP_STATUS::ManualMode;
      
      if(ModeTappingBatch == 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::AutoMode;
      }
      else if(ModeTappingBatch > 1) 
      {
        ComputerMode.Status = DEF_GC_COMP_STATUS::ComputerDynamicMode;
      }

      CIntfData::insert(SeqComputerModes,ComputerMode);



      //====================================================================================      

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setComputerModes(DataKey.c_str(), DATA::ComputerModes,SeqComputerModes);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL221FurnStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL221FurnStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL221::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL221::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL221::TreatId);

      long RoofPos        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL221::RoofPos);
      long GantryPos      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL221::GantryPos);
      long SlagDoorPos    = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL221::SlagDoorPos);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key, Telegram_EAL221::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Roof, RoofPos) )
      {
        if ( RoofPos == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFRoofArrivesInDownPosition);
        }
        else if ( RoofPos == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFRoofArrivesInUpPosition);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DATA::GantryPosIn, GantryPos) )
      {
        if ( GantryPos == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFGantrySwungOut);
        }
        else if ( GantryPos == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFGantrySwungIn);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::SlagDoor, SlagDoorPos) )
      {
        if ( SlagDoorPos == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFDoorClosed);
        }
        else if ( SlagDoorPos == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFDoorOpened);
        }
      }

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1  ,2);
      checkValidity(TlgName,"RoofPos"     ,RoofPos      ,0  ,1);  
      checkValidity(TlgName,"GantryPos"   ,GantryPos    ,0  ,1);  
      checkValidity(TlgName,"SlagDoorPos" ,SlagDoorPos  ,0  ,1);  

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
     
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::RoofPosUp,RoofPos);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::GantryPosIn,GantryPos);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::SlagDoorOpen,SlagDoorPos);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);


        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL222ElecStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL222ElecStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL222::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL222::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL222::TreatId);

      long FurnBreakOn    = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::FurnBreakOn);
      long FurnPowerOn    = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::FurnPowerOn);
      long TapChanger     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::TapChanger);
      long ElecPos        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::ElecPos);
      long ReactorTap     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::ReactorTap);
      long ElecVoltTap    = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::ElecVoltTap);
      long ElecCurvNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL222::ElecCurvNo);
      double ElecCons     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_EAL222::ElecCons);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key, Telegram_EAL222::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      // in case of plant status was requested, reset status handler to forward all data to tracker
      DEF::seqLong Spare; 
      long ResetStatusHandlerFlag = 0;

      CIntfData::getAt(ResetStatusHandlerFlag, Spare, 0 );

      if ( ResetStatusHandlerFlag == 1 )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFUpdatePlantStatus);            
      }

      //********    Define Event *******************************************************************************

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnaceBreaker, FurnBreakOn) )
      {
        if ( FurnBreakOn == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFFurnaceBreakerOff);            
        }
        else if ( FurnBreakOn == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFFurnaceBreakerOn);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::FurnacePowerOn, FurnPowerOn) )
      {
        if ( FurnPowerOn == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFPowerOff);     
        }
        else if ( FurnPowerOn == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFPowerOn);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::TapChanger, TapChanger) )
      {
        if ( TapChanger == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFTapChangeStart);        
        }
        else if ( TapChanger == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFTapChangeFinished);
        }
      }

      if ( m_StatusHandler.isStatusChanged(PlantId, DEF_DEVICES::Electrodes, ElecPos) )
      {
        if ( ElecPos == 0 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFElectrodesOutOperatingPosition);
        }
        else if ( ElecPos == 1 )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFElectrodesInOperatingPosition);
        }
      }
      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"          ,UnitNo          ,1 ,2);
      checkValidity(TlgName,"FurnBreakOn"     ,FurnBreakOn     ,0 ,1);
      checkValidity(TlgName,"FurnPowerOn"     ,FurnPowerOn     ,0 ,1);
      checkValidity(TlgName,"TapChanger"      ,TapChanger      ,0 ,1);
      checkValidity(TlgName,"ElecPos"         ,ElecPos         ,0 ,1);
      checkValidity(TlgName,"ElecVoltTap"     ,ElecVoltTap     ,0 ,20);
      checkValidity(TlgName,"ElecCurvNo"      ,ElecCurvNo      ,0 ,20);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::FurnBreakOn,   FurnBreakOn);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::PowerOn,       FurnPowerOn);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::FurnTapChangOn,TapChanger);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::ElecPosUp,     ElecPos);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::ReactTapNo,    ReactorTap); 
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::VoltTapNo,     ElecVoltTap); 
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::ElectrodRegCurve, ElecCurvNo); 
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::ElecCons,      ElecCons);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}


bool CEAF_TelegramHandler::DoProcessEAL223ElecActVal(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL223ElecActVal";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL223::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL223::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL223::TreatId);

      double ElecCons     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL223::ElecCons);
      long ReactorTap     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL223::ReactorTap);
      long ElecVoltTap    = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL223::ElecVoltTap);
      long ElecCurvNo     = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL223::ElecCurvNo);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL223::Spare);
      double Elecpower     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL223::Power);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1 ,2);
      checkValidity(TlgName,"ElecCons"       ,ElecCons       ,0.,9999999.);
      checkValidity(TlgName,"ReactorTap"     ,ReactorTap     ,1 ,20);
      checkValidity(TlgName,"ElecVoltTap"    ,ElecVoltTap    ,1 ,20);
      checkValidity(TlgName,"ElecCurvNo"     ,ElecCurvNo     ,1 ,20);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);
      
      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::Electric);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::ElecCons,ElecCons);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::ReactTapNo,ReactorTap);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::VoltTapNo,ElecVoltTap);   
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,DATA::ElectrodRegCurve,ElecCurvNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::ElecPower,Elecpower);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL224InjectionMatAvail(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL224InjectionMatAvail";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL224::UnitNo);
      //HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL224::HeatId);
      //TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL224::TreatId);

      long CarbonInjAvail       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL224::CarbonInjAvail);
      long DustInjAvail         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL224::DustInjAvail);
      long LimeInjAvail         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL224::LimeInjAvail);

      std::string MatCodeCarbon = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL224::MatCodeCarbon);      
      std::string MatCodeDust   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL224::MatCodeDust);
      std::string MatCodeLime   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL224::MatCodeLime);
      CORBA::Any SpareAny       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL224::Spare);

      PlantId           = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant             = m_pGC_Plant_Container->getPlant(PlantId);
      long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Convert and check telegram data  ***********************************************************

      checkValidity(TlgName,"UnitNo"        ,UnitNo             ,1  ,2);
      checkValidity(TlgName,"CarbonInjAvail",CarbonInjAvail     ,0  ,1);
      checkValidity(TlgName,"DustInjAvail"  ,DustInjAvail       ,0  ,1);
      checkValidity(TlgName,"LimeInjAvail"  ,LimeInjAvail       ,0  ,1);

      MatCodeCarbon = CDataConversion::Trim(MatCodeCarbon);      
      MatCodeDust   = CDataConversion::Trim(MatCodeDust);
      MatCodeLime   = CDataConversion::Trim(MatCodeLime);
      

      if ( RetValue )
      {
        //DataKey           = generateDataKey(HeatId);
        DataKey   = generateDataKey(TlgName);  

        long UnitGroupNo  = m_pGC_Plantgroup_Container->getUnitGroupNo( Plant,PlantNo );

        m_pGT_MAT_PURP->deleteRow(UnitGroupNo,CSMC_DBData::unspecString,DEF_GT_PURP::Inj_Avail);

        //fill Mat info to pGT_MAT_PURP
        if( ! MatCodeCarbon.empty()  && MatCodeCarbon != "0")
        {
          if ( m_pGT_MAT_PURP->insertRow(UnitGroupNo,MatCodeCarbon, DEF_GT_PURP::Inj_Avail) )
          {
            m_pGT_MAT_PURP->commit();
          }
          else
          {
            m_pGT_MAT_PURP->rollback();
            RetValue = false;
          }
        }
        if( !MatCodeLime.empty()  &&  MatCodeLime != "0" )
        {
          if ( m_pGT_MAT_PURP->insertRow(UnitGroupNo,MatCodeLime, DEF_GT_PURP::Inj_Avail) )
          {
            m_pGT_MAT_PURP->commit();
          }
          else
          {
            m_pGT_MAT_PURP->rollback();
            RetValue = false;
          }
        }
        if( !MatCodeDust.empty()  &&  MatCodeDust != "0" )
        {
          if ( m_pGT_MAT_PURP->insertRow(UnitGroupNo,MatCodeDust, DEF_GT_PURP::Inj_Avail) )
          {
            m_pGT_MAT_PURP->commit();
          }
          else
          {
            m_pGT_MAT_PURP->rollback();
          }
        }

        if ( RetValue )
        {
          //********    Define Event *******************************************************************************

          EventMessageVector.push_back(EAF_EvMsg::evEAFHandleUpdatePurpose);

          //********    Write telegram data  ***********************************************************************

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

          //********    End processing data  ***********************************************************************
        }

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL225InjectionMatStatus(const std::string& Key, const std::string& TlgName)
{

  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL225InjectionMatStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL225::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL225::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL225::TreatId);

      long InjectorStatus       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL225::InjectorStatus);
      long InjectorNo           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL225::InjectorNo);
      std::string MatCodeCarbon = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL225::MatCodeCarbon);
      std::string MatCodeDust   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL225::MatCodeDust);
      std::string MatCodeLime   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL225::MatCodeLime);
      double AmountCarbon       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL225::AmountCarbon);
      double AmountDust         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL225::AmountDust);
      double AmountLime         = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL225::AmountLime);
      CORBA::Any SpareAny       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL225::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      if ( InjectorStatus == 0 )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFManipInjectLanceStop);           
      }
      else if ( InjectorStatus == 1 )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFManipInjectLanceStart);
      }
      else
      {
        // undefined Lance Status
        //log("ERROR:CEAF_TelegramHandler::DoProcessEAL225InjectionMatStatus.Can not handle EAL225: Undefined Lance Status, not 0 nor 1.. InjectionStatus:"+status ,2);
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), Telegram_EAL225::InjectorStatus, InjectorStatus);
        RetValue = false;
      }

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1 ,2);
      checkValidity(TlgName,"InjectorStatus" ,InjectorStatus ,0 ,1);
      checkValidity(TlgName,"InjectorNo"     ,InjectorNo     ,0 ,4);
      checkValidity(TlgName,"AmountCarbon"   ,AmountCarbon   ,0.,9999999.);
      checkValidity(TlgName,"AmountDust"     ,AmountDust     ,0.,9999999.);
      checkValidity(TlgName,"AmountLime"     ,AmountLime     ,0.,9999999.);


      MatCodeCarbon = CDataConversion::Trim(MatCodeCarbon);      
      MatCodeDust   = CDataConversion::Trim(MatCodeDust);
      MatCodeLime   = CDataConversion::Trim(MatCodeLime);

      //std::string DeviceName    = m_pGCE_InjectionContainer->getDeviceNameByL1DeviceNo(InjectorNo);
      //std::string InjectorType  = m_pGCE_InjectionContainer->getInjectionTypeByL1DeviceNo(InjectorNo, DeviceName);

      std::string DeviceName;
      std::string InjectorType;

      if(InjectorNo == 1)
      {
        DeviceName      = DEF_GCE_INJECTION::Carbon_Injector;
        InjectorType    = DEF_GCE_INJECTION_TYPE::CarbonInjection;
      }
      else if(InjectorNo == 2)
      {
        DeviceName      = DEF_GCE_INJECTION::Silicon_Injector;
        InjectorType    = DEF_GCE_INJECTION_TYPE::SiliconInjection;
      }

      if ( DeviceName == CSMC_DBData::unspecString )
      { 
        std::string Msg = "no device for InjectorNo " + CDataConversion::LongToString(InjectorNo) + " found";
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage, "DEVICENAME", "GCE_INJECTION", Msg.c_str() );

        InjectorNo  = 0;
        DeviceName  = "";
      }

      seqStatus SeqInjectorStatus;
      sStatus Status;

      Status.Device                = DeviceName.c_str();
      Status.StatusName            = DEF_STATUS_NAME::Injection;

      if ( InjectorStatus == 0 )
      {
        Status.Status              = DEF_GEN_STATES::Off;
        Status.StartTime           = CDateTime().assDate();
      }
      else if ( InjectorStatus == 1 )
      {
        Status.Status               = DEF_GEN_STATES::On;
        Status.EndTime              = CDateTime().assDate();
      }

      CIntfData::insert(SeqInjectorStatus,Status);

      seqInjectLanceData SeqInjectLanceDataAmount;
      seqInjectLanceData SeqInjectLanceDataFlow;
      sInjectLanceData InjectLanceData;

      if ( MatCodeCarbon == DEF::Inv_String || MatCodeCarbon.empty() )
      {
        if(  m_pGT_MAT_PURP && m_pGT_MAT_PURP->select(DEF_GC_PLANTGROUP_DESC::All_EAF,CSMC_DBData::unspecString,DEF_GT_PURP::CarbonInjection) )
        {
          MatCodeCarbon = m_pGT_MAT_PURP->getMAT_CODE(1);
        }
      }

      if ( MatCodeCarbon != DEF::Inv_String && !MatCodeCarbon.empty() )
      {
        InjectLanceData.Device        = DeviceName.c_str();
        InjectLanceData.MatCode       = MatCodeCarbon.c_str();
        InjectLanceData.InjectionType = InjectorType.c_str();
        InjectLanceData.Value         = AmountCarbon;
        CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);

        InjectLanceData.Value          = 0.0;
        CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
      }

      if ( MatCodeDust != DEF::Inv_String && !MatCodeDust.empty() )
      {
        InjectLanceData.Device        = DeviceName.c_str();
        InjectLanceData.MatCode       = MatCodeDust.c_str();
        InjectLanceData.InjectionType = InjectorType.c_str();
        InjectLanceData.Value         = AmountDust;
        CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);

        InjectLanceData.Value          = 0.0;
        CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
      }

      if ( MatCodeLime != DEF::Inv_String && !MatCodeLime.empty() )
      {
        InjectLanceData.Device        = DeviceName.c_str();
        InjectLanceData.MatCode       = MatCodeLime.c_str();
        InjectLanceData.InjectionType = InjectorType.c_str();
        InjectLanceData.Value         = AmountLime;
        CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);

        InjectLanceData.Value          = 0.0;
        CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
      }

      if ( CIntfData::getLength(SeqInjectLanceDataAmount)  == 0)
      {
        std::string Message = TlgName + "SeqInjectLanceDataAmount is empty";
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());

        RetValue= false;
      }

      if ( CIntfData::getLength(SeqInjectorStatus)  == 0)
      {
        std::string Message = TlgName + "SeqInjectorStatus is empty";
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());

        RetValue= false;
      }

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString         (DataKey,         DATA::LanceId,DeviceName);

        m_pTelegram_Adapter->m_pIntf_OUT->setInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount,  SeqInjectLanceDataAmount);
        m_pTelegram_Adapter->m_pIntf_OUT->setInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow  ,  SeqInjectLanceDataFlow);
        m_pTelegram_Adapter->m_pIntf_OUT->setStatus         (DataKey.c_str(), DATA::InjectorStatus   ,  SeqInjectorStatus);

        // show interface content
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL226InjectionMatActVal(const std::string& Key, const std::string& TlgName)
{

  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL226InjectionMatActVal";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL226::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL226::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL226::TreatId);

      //long InjectorNo           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL226::InjectorNo);
      CORBA::Any AnyMatCodeCarbon = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::MatCodeCarbon);
      CORBA::Any AnyMatCodeDust   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::MatCodeDust);
      CORBA::Any AnyMatCodeLime   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::MatCodeLime);
      CORBA::Any AnyFlowCarbon    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::FlowCarbon);
      CORBA::Any AnyFlowDust      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::FlowDust);
      CORBA::Any AnyFlowLime      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::FlowLime);
      CORBA::Any AnyAmountCarbon  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::AmountCarbon);
      CORBA::Any AnyAmountDust    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::AmountDust);
      CORBA::Any AnyAmountLime    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL226::AmountLime);

      CORBA::Any SpareAny       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL226::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);


      ////********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      ////********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

      ////********    Convert and check telegram data  ***********************************************************
      //     

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1 ,2);

      DEF::seqString MatCodeCarbonSeq;  CIntfData::FromAny(MatCodeCarbonSeq,AnyMatCodeCarbon);
      DEF::seqString MatCodeDustSeq;    CIntfData::FromAny(MatCodeDustSeq,AnyMatCodeDust);
      DEF::seqString MatCodeLimeSeq;    CIntfData::FromAny(MatCodeLimeSeq,AnyMatCodeLime);

      DEF::seqDouble FlowCarbonSeq;     CIntfData::FromAny(FlowCarbonSeq,AnyFlowCarbon);
      DEF::seqDouble FlowDustSeq;       CIntfData::FromAny(FlowDustSeq,AnyFlowDust);
      DEF::seqDouble FlowLimeSeq;       CIntfData::FromAny(FlowLimeSeq,AnyFlowLime);

      DEF::seqDouble AmountCarbonSeq;   CIntfData::FromAny(AmountCarbonSeq,AnyAmountCarbon);
      DEF::seqDouble AmountDustSeq;     CIntfData::FromAny(AmountDustSeq,  AnyAmountDust);
      DEF::seqDouble AmountLimeSeq;     CIntfData::FromAny(AmountLimeSeq,  AnyAmountLime);

      std::string MatCodeCarbon;  std::string MatCodeDust;  std::string MatCodeLime;
      double FlowCarbon   = 0.0 ;     
      double AmountCarbon = 0.0 ;	 
      double FlowDust     = 0.0 ;     
      double AmountDust   = 0.0 ;	 
      double FlowLime     = 0.0 ;     
      double AmountLime   = 0.0 ;	 
      
      seqInjectLanceData  SeqInjectLanceDataFlow;
      seqInjectLanceData  SeqInjectLanceDataAmount;
      sInjectLanceData    InjectLanceData;

      for ( long ii = 0 ; ii < (CIntfData::getLength(MatCodeCarbonSeq)) ; ++ii)
      {
         std::string DeviceName     ; //= m_pGCE_InjectionContainer->getDeviceNameByL1DeviceNo(ii+1);
         std::string InjectionType  ;//= m_pGCE_InjectionContainer->getInjectionTypeByL1DeviceNo(ii+1, DeviceName);
        
        if(ii == 0)
        {
          DeviceName      = DEF_GCE_INJECTION::Carbon_Injector;
          InjectionType   = "CI1";
        }
        else if(ii == 1)
        {
          DeviceName      = DEF_GCE_INJECTION::Silicon_Injector;
          InjectionType   = "SI1";
        }

         if ( DeviceName == CSMC_DBData::unspecString )
         {    
           log ("EAL226 : Device for Carbon injection not defined",3); 
         }
         else            
         {
            CIntfData::getAt(MatCodeCarbon,MatCodeCarbonSeq,ii);
            CIntfData::getAt(FlowCarbon,FlowCarbonSeq,ii);
            CIntfData::getAt(AmountCarbon,AmountCarbonSeq,ii);

            MatCodeCarbon = CDataConversion::Trim(MatCodeCarbon);

            if ( MatCodeCarbon != DEF::Inv_String && !MatCodeCarbon.empty() )
            {
              checkValidity(TlgName,"FlowCarbon"     ,FlowCarbon     ,0.,9999999.);
              checkValidity(TlgName,"AmountCarbon"   ,AmountCarbon   ,0.,9999999.);

              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeCarbon.c_str(); 
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = FlowCarbon;
              CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
            
              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeCarbon.c_str(); 
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = AmountCarbon;
              CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);
            }
         }
      }

      // Next declared as spare for future use, can be commented out !!   
      for ( long ii = 0 ; ii < (CIntfData::getLength(MatCodeDustSeq)) ; ++ii)
      {
         std::string DeviceName     = m_pGCE_InjectionContainer->getDeviceNameByL1DeviceNo(ii+1);
         std::string InjectionType  = m_pGCE_InjectionContainer->getInjectionTypeByL1DeviceNo(ii+1, DeviceName);

         if ( DeviceName == CSMC_DBData::unspecString )
         { 
            log ("EAL226 : Device for Dust Injection not defined",3);               
         }
         else            
         {
            CIntfData::getAt(MatCodeDust,MatCodeDustSeq,ii);
            CIntfData::getAt(FlowDust,FlowDustSeq,ii);
            CIntfData::getAt(AmountDust,AmountDustSeq,ii);

            MatCodeDust = CDataConversion::Trim(MatCodeDust);

            if ( MatCodeDust != DEF::Inv_String && !MatCodeCarbon.empty() )
            {
              checkValidity(TlgName,"FlowDust"     ,FlowDust     ,0.,9999999.);
              checkValidity(TlgName,"AmountDust"   ,AmountDust   ,0.,9999999.);

              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeDust.c_str();
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = FlowDust;
              CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
            
              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeDust.c_str();
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = AmountDust;
              CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);
            }
         }
      }
      // Next declared as spare for future use, can be commented out !!   
      for ( long ii = 0 ; ii < (CIntfData::getLength(MatCodeLimeSeq)) ; ++ii)
      {
         std::string DeviceName     = m_pGCE_InjectionContainer->getDeviceNameByL1DeviceNo(ii+1);
         std::string InjectionType  = m_pGCE_InjectionContainer->getInjectionTypeByL1DeviceNo(ii+1, DeviceName);

         if ( DeviceName == CSMC_DBData::unspecString )
         {
            log ("EAL226 : Device for Lime Injection not defined",3);               
         }
         else            
         {
            CIntfData::getAt(MatCodeLime,MatCodeLimeSeq,ii);
            CIntfData::getAt(FlowLime,FlowLimeSeq,ii);
            CIntfData::getAt(AmountLime,AmountLimeSeq,ii);

            MatCodeLime = CDataConversion::Trim(MatCodeLime);

            if ( MatCodeLime != DEF::Inv_String && !MatCodeCarbon.empty() )
            {
              checkValidity(TlgName,"FlowLime"     ,FlowLime     ,0.,9999999.);
              checkValidity(TlgName,"AmountLime"   ,AmountLime   ,0.,9999999.);

              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeLime.c_str();
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = FlowLime;
              CIntfData::insert(SeqInjectLanceDataFlow,InjectLanceData);
            
              InjectLanceData.Device        = DeviceName.c_str();
              InjectLanceData.MatCode       = MatCodeLime.c_str();
              InjectLanceData.InjectionType = InjectionType.c_str();
              InjectLanceData.Value         = AmountLime;
              CIntfData::insert(SeqInjectLanceDataAmount,InjectLanceData);
            }
         }
      }

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
         DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::Injection);
        m_pTelegram_Adapter->m_pIntf_OUT->setInjectLanceData(DataKey.c_str(), DATA::InjectLanceFlow,  SeqInjectLanceDataFlow);
        m_pTelegram_Adapter->m_pIntf_OUT->setInjectLanceData(DataKey.c_str(), DATA::InjectLanceAmount,SeqInjectLanceDataAmount);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// if ( CheckCustomerData(TlgName, sCustHeatID, sCustTreatID, HeatID, TreatID, Plant) )
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL227BurnerGasAvail(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL227BurnerGasAvail";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL227::UnitNo);
      //CustHeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL227::HeatId);
      //CustTreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL227::TreatId);

      long BurnerOxygenAvail  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL227::BurnerOxygenAvail);  
      long BurnerGasAvail     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL227::BurnerGasAvail);
      long BurnerAirAvail     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL227::BurnerAirAvail);
      CORBA::Any SpareAny     = m_pTelegram_Adapter->m_pIntf_IN->getAny (Key,Telegram_EAL227::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFBurnerGasAvail);

      //********    Convert and check telegram data  ***********************************************************
           

      //HeatId    = CDataConversion::Trim(HeatId);
      //TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"            ,UnitNo             ,1  ,2);
      checkValidity(TlgName,"BurnerOxygenAvail" ,BurnerOxygenAvail  ,0  ,1);
      checkValidity(TlgName,"BurnerGasAvail"    ,BurnerGasAvail     ,0  ,1);
      checkValidity(TlgName,"BurnerAirAvail"    ,BurnerAirAvail     ,0  ,1);

      seqGasAvail SeqGasAvail;
      sGasAvail   GasAvail;

      GasAvail.GasType  = DEF_GCE_BURNER_GASTYPE::O2.c_str();
      GasAvail.GasAvail = BurnerOxygenAvail;
      CIntfData::insert(SeqGasAvail,GasAvail);

      GasAvail.GasType  = DEF_GCE_BURNER_GASTYPE::BG.c_str();
      GasAvail.GasAvail = BurnerGasAvail;
      CIntfData::insert(SeqGasAvail,GasAvail);

      //GasAvail.GasType  = DEF_GCE_BURNER_GASTYPE::Air.c_str();
      //GasAvail.GasAvail = BurnerAirAvail;
      //CIntfData::insert(SeqGasAvail,GasAvail);

      seqGasLanceGasAvail SeqGasLanceGasAvail;
      sGasLanceGasAvail   GasLanceGasAvail;

      GasLanceGasAvail.GasAvail = SeqGasAvail;
      GasLanceGasAvail.Device   = DEF_DEVICES::Burner;
      CIntfData::insert(SeqGasLanceGasAvail,GasLanceGasAvail);


      if ( RetValue )
      {
        DataKey            = generateDataKey(TlgName);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setGasLanceGasAvail(DataKey.c_str(), DATA::BurnerGasAvail, SeqGasLanceGasAvail);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL228BurnerStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL228BurnerStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL228::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL228::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL228::TreatId);

      long BurnerStatus         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL228::BurnerStatus);
      long BurnerNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL228::BurnerNo);
      double AmountBurnerOxygen = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_EAL228::AmountBurnerOxygen);
      double AmountBurnerGas    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_EAL228::AmountBurnerGas);
      CORBA::Any SpareAny       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key, Telegram_EAL228::Spare);

      PlantId       = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant         = m_pGC_Plant_Container->getPlant(PlantId);
      long PlantNo  = m_pGC_Plant_Container->getPlantNo(PlantId);

      std::string BurnerName;

      if( BurnerNo == 1 )
      {
        BurnerName  = DEF_GCE_BURNER::Burner_1;
      }
      else if( BurnerNo == 2 )
      {
        BurnerName  = DEF_GCE_BURNER::Burner_2;
      }
      else if( BurnerNo == 3 )
      {
        BurnerName  = DEF_GCE_BURNER::Burner_3;
      }
      else if( BurnerNo == 4 )
      {
        BurnerName  = DEF_GCE_BURNER::Burner_4;
      }
      else 
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), Telegram_EAL228::BurnerNo, BurnerNo);
        RetValue = false;
      }
			

     if ( RetValue)
     {
       //********    Define Event *******************************************************************************

       if (BurnerStatus == 1) //Active
       {
         EventMessageVector.push_back(EAF_EvMsg::evEAFManipGasLanceStart); // FUXIN - using burner telegrams for oxygen injection data
       }
       else if(BurnerStatus == 0) //Not Active
       {
         EventMessageVector.push_back(EAF_EvMsg::evEAFManipGasLanceStop);  // FUXIN - using burner telegrams for oxygen injection data
       }

       //********    Convert and check telegram data  ***********************************************************

       HeatId    = CDataConversion::Trim(HeatId);
       TreatId   = CDataConversion::Trim(TreatId);

       checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1 ,2);
       checkValidity(TlgName,"BurnerStatus"   ,BurnerStatus   ,0 ,1);
       checkValidity(TlgName,"BurnerNo"       ,BurnerNo       ,0 ,6);    //GEPA 201200918 2-> 5 );
       checkValidity(TlgName,"AmountBurnerOxygen" ,AmountBurnerOxygen ,0.,9999999.);
       checkValidity(TlgName,"AmountBurnerGas" ,AmountBurnerGas ,0.,9999999.);

       seqStatus SeqStatus;
       sStatus Status;
       Status.Device     = BurnerName.c_str();
       Status.StatusName = DEF_STATUS_NAME::Burner;
       Status.Status     = BurnerStatus;
       CIntfData::insert(SeqStatus,Status);

       //If there are valid data, then set into sequence 
       seqGasLanceData SeqGasLanceDataFlow;
       seqGasLanceData SeqGasLanceDataAmount;
       seqGasData      SeqGasDataAmount;
       seqGasData      SeqGasDataFlow;

       //----

       sGasLanceData GasLanceData;
       sGasData      GasData;

       GasData.GasType   = DEF_GCE_BURNER_GASTYPE::O2.c_str();
       GasData.GasValue  = AmountBurnerOxygen;
       CIntfData::insert(SeqGasDataAmount,GasData);

       GasData.GasType   = DEF_GCE_BURNER_GASTYPE::BG.c_str();
       GasData.GasValue  = AmountBurnerGas;
       CIntfData::insert(SeqGasDataAmount,GasData);

       //----

       GasData.GasType   = DEF_GCE_BURNER_GASTYPE::O2.c_str();
       GasData.GasValue  = 0.;
       CIntfData::insert(SeqGasDataFlow,GasData);

       GasData.GasType   = DEF_GCE_BURNER_GASTYPE::BG.c_str();
       GasData.GasValue  = 0.;
       CIntfData::insert(SeqGasDataFlow,GasData);

       //----

       GasLanceData.Device     = BurnerName.c_str();
       GasLanceData.LanceData  = SeqGasDataAmount;

       CIntfData::insert(SeqGasLanceDataAmount,GasLanceData);

       GasLanceData.Device     = BurnerName.c_str();
       GasLanceData.LanceData  = SeqGasDataFlow;

       CIntfData::insert(SeqGasLanceDataFlow,GasLanceData);

       //----

       checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

       if ( RetValue )
       {
         DataKey            = generateDataKey(TlgName);

         //********    Write telegram data  ***********************************************************************

         m_pTelegram_Adapter->m_pIntf_OUT->setStatus      (DataKey.c_str(), DATA::GasLanceStatus,   SeqStatus);    
         m_pTelegram_Adapter->m_pIntf_OUT->setGasLanceData(DataKey.c_str(), DATA::GasLanceAmount,   SeqGasLanceDataAmount);
         m_pTelegram_Adapter->m_pIntf_OUT->setGasLanceData(DataKey.c_str(), DATA::GasLanceFlow,     SeqGasLanceDataFlow);
         m_pTelegram_Adapter->m_pIntf_OUT->setLong        (DataKey,         DATA::GasLanceNo,       BurnerNo);

         m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

         //********    send internal event  ***********************************************************************

         SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

         //********    End processing data  ***********************************************************************

         log (TlgName + ": Finished", 3);
       }// 
       else
       {
         RetValue = false;
       }
     }// if ( RetValue)
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL229BurnerActVal(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL229BurnerActVal";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL229::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL229::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL229::TreatId);

      // JAST ARRAYS NOW
      //long BurnerNo           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key, Telegram_EAL229::BurnerNo);
      CORBA::Any AnyFlowBurnerO2       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL229::FlowBurnerOxygen);   // Nm³/h
      CORBA::Any AnyFlowBurnerGas      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL229::FlowBurnerGas);      // Nm³/h
      CORBA::Any AnyAmountBurnerO2     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL229::AmountBurnerOxygen); // Nm³ 
      CORBA::Any AnyAmountBurnerGas    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL229::AmountBurnerGas);    // Nm³
      CORBA::Any SpareAny              = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL229::Spare);

      PlantId       = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant         = m_pGC_Plant_Container->getPlant(PlantId);
      long PlantNo  = m_pGC_Plant_Container->getPlantNo(PlantId);

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

      //********    Convert and check telegram data  ***********************************************************
      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);    

      if ( RetValue )
      {
        DEF::seqDouble FlowBurnerO2Seq;     
        DEF::seqDouble FlowBurnerGasSeq;    
        DEF::seqDouble AmountBurnerO2Seq;   
        DEF::seqDouble AmountBurnerGasSeq;  
        
        CIntfData::FromAny(FlowBurnerO2Seq,AnyFlowBurnerO2);
        CIntfData::FromAny(FlowBurnerGasSeq,AnyFlowBurnerGas);
        CIntfData::FromAny(AmountBurnerO2Seq,AnyAmountBurnerO2);
        CIntfData::FromAny(AmountBurnerGasSeq,  AnyAmountBurnerGas);

        double AmountBurnerOxygen = 0.0 ;     
        double AmountBurnerGas    = 0.0 ;
        double FlowBurnerO2       = 0.0 ;           
        double FlowBurnerGas      = 0.0 ;

				seqGasLanceData SeqGasLanceDataFlow;    
        seqGasLanceData SeqGasLanceDataAmount;  
      
        for ( long ii = 0 ; ii < (CIntfData::getLength(FlowBurnerO2Seq)) ; ++ii)
        {
          std::string BurnerName = CSMC_DBData::unspecString;

					if( ii == 0 )
					{
						BurnerName  = DEF_GCE_BURNER::Burner_1;
					}
					else if( ii == 1 )
					{
						BurnerName  = DEF_GCE_BURNER::Burner_2;
					}
					else if( ii == 2 )
					{
						BurnerName  = DEF_GCE_BURNER::Burner_3;
					}
					else if( ii == 3 )
					{
						BurnerName  = DEF_GCE_BURNER::Burner_4;
					}

               
          if ( BurnerName == CSMC_DBData::unspecString )
          {
            std::stringstream Message;

            Message << "EAL229 : BurnerName for Burner " << ii+1 << " not defined" ;
            log (Message.str() ,4);
          }
          else            
          {
            log (" EAL229 : BurnerName : "+  BurnerName ,3);  

            seqGasData      SeqBurnerFlows;
            seqGasData      SeqBurnerAmounts;

            sGasLanceData   GasLanceData;           
            sGasData        GasData;

            CIntfData::getAt(FlowBurnerO2, FlowBurnerO2Seq,ii);
            CIntfData::getAt(FlowBurnerGas,FlowBurnerGasSeq,ii);
            CIntfData::getAt(AmountBurnerOxygen,AmountBurnerO2Seq,ii);
            CIntfData::getAt(AmountBurnerGas,AmountBurnerGasSeq,ii);

            // Nm³/h -> Nm³/min
            FlowBurnerO2   = FlowBurnerO2  / 60. ;
            FlowBurnerGas  = FlowBurnerGas / 60. ;


            checkValidity(TlgName,"FlowBurnerO2"        ,FlowBurnerO2      ,0.,100.);
            checkValidity(TlgName,"FlowBurnerGas"       ,FlowBurnerGas     ,0.,100.);
            checkValidity(TlgName,"AmountBurnerOxygen"  ,AmountBurnerOxygen,0.,9999999.);
            checkValidity(TlgName,"AmountBurnerGas"     ,AmountBurnerGas   ,0.,9999999.);


            // For Burner
            GasData.GasType  = DEF_GCE_BURNER_GASTYPE::O2.c_str();
            GasData.GasValue = AmountBurnerOxygen;
            CIntfData::insert(SeqBurnerAmounts,  GasData);
            GasData.GasType  = DEF_GCE_BURNER_GASTYPE::BG.c_str();
            GasData.GasValue = AmountBurnerGas;
            CIntfData::insert(SeqBurnerAmounts,  GasData);

            GasData.GasType    = DEF_GCE_BURNER_GASTYPE::O2.c_str();
            GasData.GasValue   = FlowBurnerO2;
            CIntfData::insert(SeqBurnerFlows,    GasData);
            GasData.GasType    = DEF_GCE_BURNER_GASTYPE::BG.c_str();
            GasData.GasValue   = FlowBurnerGas;
            CIntfData::insert(SeqBurnerFlows,    GasData);
            // For Lance
            GasLanceData.Device     = BurnerName.c_str();
            GasLanceData.LanceData  = SeqBurnerFlows;
            CIntfData::insert(SeqGasLanceDataFlow,GasLanceData);
            GasLanceData.Device     = BurnerName.c_str();
            GasLanceData.LanceData  = SeqBurnerAmounts;
            CIntfData::insert(SeqGasLanceDataAmount,GasLanceData);

          }

        } //for ( long ii = 0 ; ii < (CIntfData::getLength(FlowBurnerO2Seq)) ; ++ii)

        if ( CIntfData::getLength(SeqGasLanceDataAmount) > 0 )
        {
          RetValue = true;
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"Burner sequence is empty", "");
        }

        if ( RetValue )
        {
          DataKey            = generateDataKey(HeatId);
          //********    Write telegram data  ***********************************************************************
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::Burning);
          m_pTelegram_Adapter->m_pIntf_OUT->setGasLanceData(DataKey.c_str(), DATA::GasLanceFlow,  SeqGasLanceDataFlow);
          m_pTelegram_Adapter->m_pIntf_OUT->setGasLanceData(DataKey.c_str(), DATA::GasLanceAmount,SeqGasLanceDataAmount);
          //  m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);
          //********    send internal event  ***********************************************************************
          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

          log (TlgName + ": Finished succesfully", 3);
        }

      //********    End processing data  ***********************************************************************
      }// if ( CheckCustomerData(TlgName, sCustHeatID, sCustTreatID, HeatID, TreatID, Plant) )
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL233CoolingWater(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL233CoolingWater";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL233::UnitNo);
      HeatId        = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL233::HeatId);
      TreatId       = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL233::TreatId);

      double InletRoofTemp  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::RoofWaterInlet);    
      double OutletRoofTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::RoofWaterOutlet);    
      double RoofTotFlow    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::RoofWaterFlow);

      double InletElbowTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::ElbowWaterInlet);    
      double OutletElbowTemp= m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::ElbowWaterOutlet);
      double ElbowTotFlow   = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::ElbowWaterFlow);

      double InletWallTemp  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::WallWaterInlet);    
      double OutletWallTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::WallWaterOutlet);    
      double WallTotFlow    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::WallWaterFlow);

      double UppWallTemp    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::UppWallOutlet);
      double LowWallTemp    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::LowWallOutlet);

      double DoorPanTemp    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::DoorPanelOutlet);    
      double DoorTunTemp    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::DoorTunelOutlet);

      CORBA::Any AnyCoverBayTemp = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL233::CoverBayOutlet);

      double InletDustTemp  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::DustWaterInlet);
      double OutletDustTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::DustWaterOutlet);    
      double DustTotFlow	  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::DustWaterFlow);

      CORBA::Any AnyUppWallPanelTemp = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL233::UppWallPanelTemp);
      CORBA::Any AnyLowWallPanelTemp = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL233::LowWallPanelTemp);
      CORBA::Any AnyBottomTemp       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL233::BottomTemp);

      double MomentO2     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::MomentO2);
      double MomentElec   = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL233::MomentElec);
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL233::Spare);


      DEF::seqDouble UppWallPanelTemp; 
      DEF::seqDouble LowWallPanelTemp; 
      DEF::seqDouble BottomTemp;       

      CIntfData::FromAny(UppWallPanelTemp,AnyUppWallPanelTemp);
      CIntfData::FromAny(LowWallPanelTemp,AnyLowWallPanelTemp);
      CIntfData::FromAny(BottomTemp,AnyBottomTemp);

      seqCoolWaterData SeqCoolWaterData;
      sCoolWaterDevice CoolWaterDevice;

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

      HeatId        = CDataConversion::Trim(HeatId);
      TreatId       = CDataConversion::Trim(TreatId);
      // right now the definition is 2 bit, but should be 3 in the future;
      // TreatId       = CDataConversion::FillLeft(TreatId, 3, "0");

      //********    Convert and check telegram data  ***********************************************************

      checkValidity(TlgName,"UnitNo"          ,UnitNo           ,1 ,2);
      checkValidity(TlgName,"InletRoofTemp"   ,InletRoofTemp    ,0.,100.);
      checkValidity(TlgName,"OutletRoofTemp"  ,OutletRoofTemp   ,0.,100.);
      checkValidity(TlgName,"InletElbowTemp"  ,InletElbowTemp   ,0.,100.);
      checkValidity(TlgName,"OutletElbowTemp" ,OutletElbowTemp  ,0.,100.);
      checkValidity(TlgName,"InletWallTemp"   ,InletWallTemp    ,0.,100.);
      checkValidity(TlgName,"OutletWallTemp"  ,OutletWallTemp   ,0.,100.);

      checkValidity(TlgName,"UppWallTemp"     ,UppWallTemp      ,0.,100.);
      checkValidity(TlgName,"LowWallTemp"     ,LowWallTemp      ,0.,100.);
      checkValidity(TlgName,"DoorPanTemp"     ,DoorPanTemp      ,0.,100.);
      checkValidity(TlgName,"DoorTunTemp"     ,DoorTunTemp      ,0.,100.);
      //checkValidity(TlgName,"CoverBayTemp"    ,CoverBayTemp     ,0.,100.);
      checkValidity(TlgName,"InletDustTemp"   ,InletDustTemp    ,0.,100.);
      checkValidity(TlgName,"OutletDustTemp"  ,OutletDustTemp   ,0.,100.);

      checkValidity(TlgName,"UppWallPanelTemp",UppWallPanelTemp ,0.,100.);
      checkValidity(TlgName,"LowWallPanelTemp",LowWallPanelTemp ,0.,100.);
      checkValidity(TlgName,"BottomTemp"      ,BottomTemp       ,0.,600.);
      checkValidity(TlgName,"MomentO2"        ,MomentO2         ,0.,9999999.);
      checkValidity(TlgName,"MomentElec"      ,MomentElec       ,0.,9999999.);

      // Nm³/h -> Nm³/min
      //RoofTotFlow    = RoofTotFlow  / 60. ;
      //ElbowTotFlow   = ElbowTotFlow / 60. ;
      //WallTotFlow    = WallTotFlow  / 60. ;
      //DustTotFlow	   = DustTotFlow  / 60. ;
  
      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);
      
        //** model values

        CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::Roof).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = InletRoofTemp;
        CoolWaterDevice.CoolWaterData.OutletTemp  = OutletRoofTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = RoofTotFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::Elbow).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = InletElbowTemp;
        CoolWaterDevice.CoolWaterData.OutletTemp  = OutletElbowTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = ElbowTotFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

         CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::Dedusting).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = InletDustTemp;
        CoolWaterDevice.CoolWaterData.OutletTemp  = OutletDustTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = DustTotFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::Wall).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = InletWallTemp;
        CoolWaterDevice.CoolWaterData.OutletTemp  = OutletWallTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = WallTotFlow;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        //CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::UpperWall).c_str();
        //CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        //CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        //CoolWaterDevice.CoolWaterData.OutletTemp  = UppWallTemp;
        //CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        //CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        //CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::LowerWall).c_str();
        //CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        //CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        //CoolWaterDevice.CoolWaterData.OutletTemp  = LowWallTemp;
        //CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        //CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::DoorPanel).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        CoolWaterDevice.CoolWaterData.OutletTemp  = DoorPanTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

 
        CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::DoorTunelPanel).c_str();
        CoolWaterDevice.CoolWaterDeviceNo         = 1; // default
        CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        CoolWaterDevice.CoolWaterData.OutletTemp  = DoorTunTemp;
        CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);

        //CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::CoverBay).c_str();
        //for ( long i = 0 ; i < CIntfData::getLength(CoverBayTemp); ++i )
        //{
        //  double Temp = 0.0;
        //  CIntfData::getAt(Temp,CoverBayTemp,i);

        //  CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::CoverBay).c_str();
        //  CoolWaterDevice.CoolWaterDeviceNo         = i + 1; // default
        //  CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        //  CoolWaterDevice.CoolWaterData.OutletTemp  = Temp;
        //  CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        //  CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);
        //}

        if ( m_pGC_COOLWATER->selectOrdered(Plant, DEF_GC_COOLWATER::WallUpPanelLoop, CSMC_DBData::unspecLong) )
        {
          long LastRow = m_pGC_COOLWATER->getCOOL_LOOP_NO(m_pGC_COOLWATER->getLastRow());

          CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::WallUpPanelLoop).c_str();
          for ( long i = 0 ; i < CIntfData::getLength(UppWallPanelTemp); ++i )
          {
            double Temp = 0.0;
            CIntfData::getAt(Temp,UppWallPanelTemp,i);
            CoolWaterDevice.CoolWaterDeviceNo         = i + 1;
            CoolWaterDevice.CoolWaterData.InletTemp   = InletWallTemp;
            CoolWaterDevice.CoolWaterData.OutletTemp  = Temp;
            CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;

            if  ( LastRow >= CoolWaterDevice.CoolWaterDeviceNo )
            {
              CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);
            }
          }
        }

        if ( m_pGC_COOLWATER->selectOrdered(Plant, DEF_GC_COOLWATER::WallLowPanelLoop, CSMC_DBData::unspecLong) )
        {
          long LastRow = m_pGC_COOLWATER->getCOOL_LOOP_NO(m_pGC_COOLWATER->getLastRow());

          CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::WallLowPanelLoop).c_str();
          for ( long i = 0 ; i < CIntfData::getLength(LowWallPanelTemp); ++i )
          {
            double Temp = 0.0;
            CIntfData::getAt(Temp,LowWallPanelTemp,i);
            CoolWaterDevice.CoolWaterDeviceNo         = i + 1;
            CoolWaterDevice.CoolWaterData.InletTemp   = InletWallTemp;
            CoolWaterDevice.CoolWaterData.OutletTemp  = Temp;
            CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;

            if  ( LastRow >= CoolWaterDevice.CoolWaterDeviceNo )
            {
              CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);
            }
          }
        }

        //CoolWaterDevice.CoolWaterDevice           = std::string(DEF_GC_COOLWATER::BottomLoop).c_str();
        //for ( long i = 0 ; i < CIntfData::getLength(BottomTemp); ++i )
        //{
        //  double Temp = 0.0;
        //  CIntfData::getAt(Temp,BottomTemp,i);
        //  CoolWaterDevice.CoolWaterDeviceNo         = i + 1;
        //  CoolWaterDevice.CoolWaterData.InletTemp   = 0.;
        //  CoolWaterDevice.CoolWaterData.OutletTemp  = Temp;
        //  CoolWaterDevice.CoolWaterData.WaterFlow   = 0.;
        //  CIntfData::insert(SeqCoolWaterData,CoolWaterDevice);
        //}

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::CoolingWater);
        m_pTelegram_Adapter->m_pIntf_OUT->setCoolWaterData(DataKey.c_str(),DATA::CoolingWaterData, SeqCoolWaterData);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::MomentO2,MomentO2); 
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,DATA::ElecCons,MomentElec); 

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished",3);
      }// if ( checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId) )
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL234VesselStirrStatus(const string& Key, const string& TlgName)
{
  //GEPA : Note : This telegram is obsolete for Fuxin according to L1 and contract
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL234VesselStirrStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
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

      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL234::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL234::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL234::TreatId);

      long StirrStat      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL234::StirrStat);
      long StirrGasType   = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL234::StirrGasType  );
      long PlugNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL234::PlugNo        );
      double StirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL234::StirrGasCons   );

      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL234::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

			//SARS
      //if(StirrStat == 1)//active
      //{
      //  EventMessageVector.push_back(EAF_EvMsg::evEAFBottomStirringStart);
      //}
      //else if(StirrStat == 0)//Not active
      //{
      //  EventMessageVector.push_back(EAF_EvMsg::evEAFBottomStirringEnd);
      //}

      //********    Convert and check telegram data  ***********************************************************


      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"          ,UnitNo         ,1  ,2);
      checkValidity(TlgName,"StirrStat"       ,StirrStat      ,0  ,1);
      checkValidity(TlgName,"StirrGasType"    ,StirrGasType   ,1  ,2);
      checkValidity(TlgName,"StirrGasCons"    ,StirrGasCons   ,0. ,999999.);
      checkValidity(TlgName,"PlugNo"          ,PlugNo         ,0  ,3);

      seqStirringData   SeqStirringData;
      sStirringData     StirringData;

      seqGasData        SeqGasData;      
      sGasData          GasData;

      seqStatus         SeqStatus;
      sStatus           Status;

      std::string       GasType;
      CDateTime         Now;

      if (StirrGasType == 1)
      {
        GasData.GasValue  = StirrGasCons;
        GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
        GasType           = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
      }
      else if (StirrGasType == 2)
      {
        GasData.GasValue  = StirrGasCons;
        GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
        GasType           = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
      }

      CIntfData::insert(SeqGasData,GasData);

      if ( PlugNo == 1 )
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug1, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringEnd);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId,DEF_GC_STIRR_DEVICE::Plug1,StirrStat ) )
      }
      else if ( PlugNo == 2 )
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringEnd);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug2.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug2.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )
      }
      else if ( PlugNo == 3 )
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug3.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug3, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringEnd);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug3.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug3.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug3, StirrStat ) )
      }
      else if ( PlugNo == 4 ) //SARS
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug4.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug4, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringEnd);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug4.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFBottomStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug4.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug4, StirrStat ) )
			}

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->setStatus(DataKey.c_str(),        DATA::StirringStatus       , SeqStatus);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,                DATA::StirringGasType      , GasType);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(),  DATA::StirringAmount       , SeqStirringData);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}
bool CEAF_TelegramHandler::DoProcessEAL235VesselStirrCons(const string& Key, const string& TlgName)
{
  //GEPA : Note : This telegram is obsolete for Fuxin according to L1 and contract
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL235VesselStirrCons";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
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

      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL235::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL235::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL235::TreatId);

      // JAST ARRAYS NOW
      CORBA::Any AnyStirrGasType = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL235::StirrGasType); 
      CORBA::Any AnyFlowPressOK  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL235::FlowPressOK);
      CORBA::Any AnyFlowAct      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL235::FlowAct);         // l/min
      CORBA::Any AnyStirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL235::StirrGasCons);    // l

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      checkValidity(TlgName,"UnitNo"          ,UnitNo         ,1  ,2);

			checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);    //SARS
      ////********    reset statushandler for plant *******************************************************************************
      if ( RetValue ) //&& CheckCustomerData(TlgName, CustHeatId, CustTreatId, HeatId, TreatId, Plant) SARS
      {

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

        //********    Convert and check telegram data  ***********************************************************

        HeatId    = CDataConversion::Trim(HeatId);
        TreatId   = CDataConversion::Trim(TreatId);

        DEF::seqLong   StirrGasTypeSeq; 
        DEF::seqLong   FlowPressOKSeq;  
        DEF::seqDouble FlowActSeq;      
        DEF::seqDouble StirrGasConsSeq; 

        CIntfData::FromAny(StirrGasTypeSeq,AnyStirrGasType);
        CIntfData::FromAny(FlowPressOKSeq,AnyFlowPressOK);
        CIntfData::FromAny(FlowActSeq,AnyFlowAct);
        CIntfData::FromAny(StirrGasConsSeq,AnyStirrGasCons);

        long   MyPlug         = 0 ;
        long   MyGastype      = 0 ;
        long   MyFlowPress    = 0 ;
        double MyFlowAct      = 0. ;
        double MyGasCons      = 0. ;

        //********    main telegram data   ***********************************************************************
        for ( long ii = 0 ; ii < (CIntfData::getLength(StirrGasTypeSeq)) ; ++ii)
        { 
         seqGasData SeqGasData;  // work always with fresh sequences
         sGasData   GasData;     // and structures
         seqStirringData   StirringPressData; 
         seqStirringData   StirringConsData;
         seqStirringData   StirringFlowData;
         sStirringData     StirringData;

         MyPlug  = ii+1;
         CIntfData::getAt(MyGastype,  StirrGasTypeSeq,ii);
         CIntfData::getAt(MyFlowPress,FlowPressOKSeq,ii);
         CIntfData::getAt(MyFlowAct,  FlowActSeq,ii);
         CIntfData::getAt(MyGasCons,  StirrGasConsSeq,ii);

         // l/min -> Nm³/min
         //MyFlowAct = MyFlowAct / 1000. ;
         // l -> Nm³
         //MyGasCons = MyGasCons / 1000. ;


          // Nm³/h -> Nm³/min SARS
          MyFlowAct   = MyFlowAct  / 60. ;


         checkValidity(TlgName,"Gastype"    ,MyGastype    ,1  ,2);
         checkValidity(TlgName,"FlowPress"  ,MyFlowPress  ,1  ,2);
         checkValidity(TlgName,"FlowAct"    ,MyFlowAct    ,0. ,9999999.);
         checkValidity(TlgName,"GasCons"    ,MyGasCons    ,0. ,9999999.);

         if(MyPlug == 1)
         {
           StirringData.Device = DEF_GC_STIRR_DEVICE::Plug1.c_str();
         }
         else if(MyPlug == 2)
         {
           StirringData.Device = DEF_GC_STIRR_DEVICE::Plug2.c_str();
         }
         else if(MyPlug == 3)
         {
           StirringData.Device = DEF_GC_STIRR_DEVICE::Plug3.c_str();
         }
         else if(MyPlug == 4)
         {
           StirringData.Device = "";//DEF_GC_STIRR_DEVICE::Plug4.c_str();  // not yet implemented
         }
         if(MyGastype == 1)//Ar
         {
            GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
         }
         else if(MyGastype == 2)//N2
         {
           GasData.GasType = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
         }
         // *************************************************************
         // pressure
         // *************************************************************
         GasData.GasValue = MyFlowPress;
         CIntfData::insert(SeqGasData,GasData);
         StirringData.GasData = SeqGasData;
         CIntfData::insert(StirringPressData,StirringData);
       
         // *************************************************************
         // flow
         // *************************************************************
         GasData.GasValue = MyFlowAct;
         CIntfData::setAt(SeqGasData,GasData,0);
         StirringData.GasData = SeqGasData;
         CIntfData::insert(StirringFlowData,StirringData);
       
         // *************************************************************
         // consumption
         // *************************************************************
         GasData.GasValue = MyGasCons;
         CIntfData::setAt(SeqGasData,GasData,0);
         StirringData.GasData = SeqGasData;
         CIntfData::insert(StirringConsData,StirringData);

         DataKey            = generateDataKey(HeatId);

         //********    Write telegram data  ***********************************************************************
         m_pTelegram_Adapter->m_pIntf_OUT->setString       (DataKey,         DATA::MeasurementType,  DEF_CYCLIC_MEASUREMENT_TYPES::Stirring);
         m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringFlow,     StirringFlowData);
         m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringAmount,   StirringConsData);
         m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringPressure, StirringPressData);

      				 

         m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

         m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

         SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }//for ( long ii = 0; ii < (CIntfData::getLength(StirrGasTypeSeq)) ; ++ii)

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// if ( CheckCustomerData(TlgName, sCustHeatID, sCustTreatID, HeatID, TreatID, Plant) )
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL236LadleStirrStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL236LadleStirrStatus";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL236::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL236::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL236::TreatId);

      std::string LadleId = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL236::LadleId);
      long PlugNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL236::PlugNo        );
      long StirrGasType   = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL236::StirrGasType  );
      long StirrStat      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL236::StirrStat);
      double StirrGasCons = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL236::StirrGasCons   );
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL236::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      if(StirrStat == 1)//active
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFLadleStirringStart);
      }
      else if(StirrStat == 0)//Not active
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFLadleStirringStop);
      }

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      LadleId   = CDataConversion::Trim(LadleId);

      CLadleID LadleID;

      if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::PreMetalLadle, LadleId) )
      {
        LadleType          = LadleID.getLadleType(LadleId);
        LadleNo            = LadleID.getLadleNo(LadleId);
      }

      checkValidity(TlgName,"UnitNo"          ,UnitNo         ,1  ,2);
      checkValidity(TlgName,"StirrStat"       ,StirrStat      ,0  ,1);
      checkValidity(TlgName,"StirrGasType"    ,StirrGasType   ,1  ,2);
      checkValidity(TlgName,"StirrGasCons"    ,StirrGasCons   ,0. ,999999.);
      checkValidity(TlgName,"PlugNo"          ,PlugNo         ,1  ,2);
      checkValidity(TlgName,"LadleId"         ,LadleNo        ,1  ,99);

      seqStirringData   SeqStirringData;
      sStirringData     StirringData;

      seqGasData        SeqGasData;      
      sGasData          GasData;

      seqStatus         SeqStatus;
      sStatus           Status;

      std::string       GasType;
      CDateTime         Now;

      if (StirrGasType == 1)
      {
        GasData.GasValue  = StirrGasCons;
        GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
        GasType           = DEF_GC_STIRR_GAS_TYPE::Ar.c_str();
      }
      else if (StirrGasType == 2)
      {
        GasData.GasValue  = StirrGasCons;
        GasData.GasType   = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
        GasType           = DEF_GC_STIRR_GAS_TYPE::N2.c_str();
      }

      CIntfData::insert(SeqGasData,GasData);

      if ( PlugNo == 1 )
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug1, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFLadleStirringStop);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFLadleStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug1.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug1, StirrStat ) )
      }
      else if ( PlugNo == 2 )
      {
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
        StirringData.GasData  = SeqGasData;

        CIntfData::insert(SeqStirringData,StirringData);

        if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )
        {
          if ( StirrStat == 0 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFLadleStirringStop);
            Status.Status     = DEF_GEN_STATES::Off;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.EndTime    = Now.assDate();
            Status.Device   =  DEF_GC_STIRR_DEVICE::Plug2.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
          else if ( StirrStat == 1 ) 
          {
            EventMessageVector.push_back( EAF_EvMsg::evEAFLadleStirringStart);
            Status.Status     = DEF_GEN_STATES::On;
            Status.StatusName = DEF_STATUS_NAME::Stirring;
            Status.StartTime  = Now.assDate();
            Status.Device     = DEF_GC_STIRR_DEVICE::Plug2.c_str();
            CIntfData::insert(SeqStatus,Status);
          }
        } // if ( m_StatusHandler.isStatusChanged(PlantId, DEF_GC_STIRR_DEVICE::Plug2, StirrStat ) )
      }

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

// JAST STIRRING        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,                DATA::StirringGasType      , GasType);
// JAST STIRRING        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,                DATA::PlugNo               , PlugNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,                DATA::LadleNo              , LadleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,                DATA::LadleType            , LadleType);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,                DATA::StirringGasType      , GasType);
        m_pTelegram_Adapter->m_pIntf_OUT->setStatus(DataKey.c_str(),        DATA::StirringStatus       , SeqStatus);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData(DataKey.c_str(),  DATA::StirringAmount       , SeqStirringData);

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}
bool CEAF_TelegramHandler::DoProcessEAL237LadleStirrCons(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL237LadleStirrCons";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL237::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL237::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL237::TreatId);

      std::string LadleId         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL237::LadleId);
      long StirrGasType           = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL237::StirrGasType); 
      CORBA::Any AnyStirrInt      = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL237::StirrInt);
      CORBA::Any AnyFlowAct       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL237::FlowAct);       // l/min
      CORBA::Any AnyPressure      = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL237::Pressure);
      CORBA::Any AnyConsGas       = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL237::StirrGasCons);  // l
      CORBA::Any SpareAny         = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL237::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      DEF::seqLong   SeqStirrInt;
      DEF::seqDouble SeqFlowAct;
      DEF::seqDouble SeqPressure;
      DEF::seqDouble SeqConsGas;

      CIntfData::FromAny(SeqStirrInt,AnyStirrInt);
      CIntfData::FromAny(SeqFlowAct,AnyFlowAct);
      CIntfData::FromAny(SeqPressure,AnyPressure);
      CIntfData::FromAny(SeqConsGas,AnyConsGas);

      checkValidity(TlgName,"UnitNo"          ,UnitNo        ,1  ,2);
      checkValidity(TlgName,"StirrGasType"    ,StirrGasType  ,1  ,2);
      checkValidity(TlgName,"StirrInt"        ,SeqStirrInt   ,1  ,6);
      checkValidity(TlgName,"FlowAct"         ,SeqFlowAct    ,0. ,100000.);
      checkValidity(TlgName,"Pressure"        ,SeqPressure   ,0. ,1000.);
      checkValidity(TlgName,"ConsGas"         ,SeqConsGas    ,0. ,100000.);


      //********    reset statushandler for plant *******************************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurementTapLadle);

        //********    Convert and check telegram data  ***********************************************************

        HeatId    = CDataConversion::Trim(HeatId);
        TreatId   = CDataConversion::Trim(TreatId);

        LadleId   = CDataConversion::Trim(LadleId);

        CLadleID LadleID;

        if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::PreMetalLadle, LadleId) )
        {
          LadleType          = LadleID.getLadleType(LadleId);
          LadleNo            = LadleID.getLadleNo(LadleId);
        }


        //********    main telegram data   ***********************************************************************

        DataKey            = generateDataKey(HeatId);

        seqStirringData   StirringPressData; 
        seqStirringData   StirringConsData;
        seqStirringData   StirringFlowData;
        sStirringData     StirringData;

        seqGasData SeqGasData;
        sGasData   GasData; 

        std::string       GasType;

        if (StirrGasType == 1)
        {
          GasType = DEF_GAS::Ar;
        }
        else
        {
          GasType = DEF_GAS::N2;
        }

        // *************************************************************
        // preset seqGasData
        // *************************************************************
        GasData.GasValue  = -1.;
        GasData.GasType   = GasType.c_str();
        CIntfData::insert(SeqGasData,GasData);

        // *************************************************************
        // pressure
        // *************************************************************
        double Pressure1 = -1;
        double Pressure2 = -1;
        CIntfData::getAt(Pressure1,SeqPressure,0);
        CIntfData::getAt(Pressure2,SeqPressure,1);
        
        GasData.GasValue = Pressure1;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringPressData,StirringData);

        GasData.GasValue = Pressure2;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringPressData,StirringData);

        // *************************************************************
        // flow
        // *************************************************************
        double Flow1 = -1;
        double Flow2 = -1;
        CIntfData::getAt(Flow1,SeqFlowAct,0);
        CIntfData::getAt(Flow2,SeqFlowAct,1);

        // l/min -> Nm³/min
        Flow1 = Flow1 / 1000. ;
        Flow2 = Flow2 / 1000. ;
        
        GasData.GasValue = Flow1;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringFlowData,StirringData);

        GasData.GasValue = Flow2;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringFlowData,StirringData);

        // *************************************************************
        // consumption
        // *************************************************************
        double Cons1 = -1;
        double Cons2 = -1;
        CIntfData::getAt(Cons1,SeqConsGas,0);
        CIntfData::getAt(Cons2,SeqConsGas,1);

        // l -> Nm³
        Cons1 = Cons1 / 1000. ;
        Cons2 = Cons2 / 1000. ;
        
        GasData.GasValue = Cons1;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug1.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringConsData,StirringData);

        GasData.GasValue = Cons2;
        CIntfData::setAt(SeqGasData,GasData,0);
        StirringData.Device   = DEF_GC_STIRR_DEVICE::Plug2.c_str();
        StirringData.GasData  = SeqGasData;
        CIntfData::insert(StirringConsData,StirringData);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setLong         (DataKey.c_str(), DATA::LadleNo,          LadleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setString       (DataKey.c_str(), DATA::LadleType,        LadleType);

        m_pTelegram_Adapter->m_pIntf_OUT->setString       (DataKey,         DATA::MeasurementType,  DEF_CYCLIC_MEASUREMENT_TYPES::TapLadleStirring);
        m_pTelegram_Adapter->m_pIntf_OUT->setString       (DataKey,         DATA::StirringGasType,  GasType);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringFlow,     StirringFlowData);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringAmount,   StirringConsData);
        m_pTelegram_Adapter->m_pIntf_OUT->setStirringData (DataKey.c_str(), DATA::StirringPressure, StirringPressData);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL240EAFFlameProfile(const std::string& Key, const std::string& TlgName)
{ // ########## Telegram not used for Fuxin #############
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL240EAFFlameProfile";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long PlantNo = DEF::Inv_Long;
  long LadleNo  = -1;
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
      
      UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL240::UnitNo);

      CORBA::Any FlameProfileNoAny    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::FlameProfileNo);
      CORBA::Any BurnerOxygenFlowAny  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::BurnerOxygenFlow);   // Nm³/h
      CORBA::Any BurnerGasFlowAny     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::BurnerGasFlow);      // Nm³/h
      CORBA::Any BurnerAirFlowAny     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::BurnerAirFlow);      // Nm³/h
      CORBA::Any BurnerPowerCalcAny   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::BurnerPowerCalc);
      CORBA::Any SpareAny             = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key,Telegram_EAL240::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);
      PlantNo   = m_pGC_Plant_Container->getPlantNo(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      //EventMessageVector.push_back(EAF_EvMsg::evEAFXX);

      //********    Convert and check telegram data  ***********************************************************
           

      DEF::seqLong   FlameProfileNoSeq;
      DEF::seqDouble BurnerOxygenFlowSeq;
      DEF::seqDouble BurnerGasFlowSeq;
      DEF::seqDouble BurnerAirFlowSeq;
      DEF::seqDouble BurnerPowerCalcSeq;

      CIntfData::FromAny(FlameProfileNoSeq,   FlameProfileNoAny);
      CIntfData::FromAny(BurnerOxygenFlowSeq, BurnerOxygenFlowAny);
      CIntfData::FromAny(BurnerGasFlowSeq,    BurnerGasFlowAny);
      CIntfData::FromAny(BurnerAirFlowSeq,    BurnerAirFlowAny);
      CIntfData::FromAny(BurnerPowerCalcSeq,  BurnerPowerCalcAny);

      checkValidity(TlgName,"UnitNo"               ,UnitNo              ,1  ,2);
      checkValidity(TlgName,"BurnerOxygenFlowSeq"  ,BurnerOxygenFlowSeq ,0. ,999999.);
      checkValidity(TlgName,"BurnerGasFlowSeq"     ,BurnerGasFlowSeq    ,0. ,999999.);
      checkValidity(TlgName,"BurnerAirFlowSeq"     ,BurnerAirFlowSeq    ,0. ,999999.);
      checkValidity(TlgName,"BurnerPowerCalcSeq"   ,BurnerPowerCalcSeq  ,0. ,999999.);

      DataKey            = generateDataKey(TlgName);

      if ( RetValue )
      {
        //********    Write telegram data  ***********************************************************************

        bool UseFlameProfile = true;

        cCBS_StdInitBase::getInstance()->replaceWithEntry("FLAMEPROFILEHANDLING","UseFlameProfile",UseFlameProfile);

        if ( UseFlameProfile )
        {
          long SequenceLength = 10;

          for (int i = 0; i < SequenceLength; i++)
          {
            long FlameProfileNo     = 0;
            double BurnerOxygenFlow = 0;
            double BurnerGasFlow    = 0;
            double BurnerAirFlow    = 0;
            double BurnerPowerCalc  = 0;

            CIntfData::getAt(FlameProfileNo,  FlameProfileNoSeq,    i);
            CIntfData::getAt(BurnerOxygenFlow,BurnerOxygenFlowSeq,  i);
            CIntfData::getAt(BurnerGasFlow,   BurnerGasFlowSeq,     i);
            CIntfData::getAt(BurnerAirFlow,   BurnerAirFlowSeq,     i);
            CIntfData::getAt(BurnerPowerCalc, BurnerPowerCalcSeq,   i);

            FlameProfileNo  = CDataConversion::SetInvalidToDefault(FlameProfileNo ,0, -1);
            FlameProfileNo  = CDataConversion::SetInvalidToDefault(FlameProfileNo ,0);

            // Nm³/h -> Nm³/min
            BurnerOxygenFlow  = BurnerOxygenFlow  / 60. ;
            BurnerGasFlow     = BurnerGasFlow     / 60. ;
            BurnerAirFlow     = BurnerAirFlow     / 60. ;

            m_pGTE_PP_FLAME_PROFILE->setPLANT           (Plant);
            m_pGTE_PP_FLAME_PROFILE->setPLANTNO         (PlantNo);

            m_pGTE_PP_FLAME_PROFILE->setFLAMEPROFILENO  (FlameProfileNo);
            m_pGTE_PP_FLAME_PROFILE->setFLAMEPROFILENO  (FlameProfileNo);

            m_pGTE_PP_FLAME_PROFILE->setFLAMEPROFILENO  (FlameProfileNo);
            m_pGTE_PP_FLAME_PROFILE->setOXYGENFLOW      (BurnerOxygenFlow);
            m_pGTE_PP_FLAME_PROFILE->setGASFLOW         (BurnerGasFlow);
            m_pGTE_PP_FLAME_PROFILE->setAIRFLOW         (BurnerAirFlow);
            m_pGTE_PP_FLAME_PROFILE->setCORRECTIONPOWER ((long)BurnerPowerCalc); // Iinterface is double

            // JAST BurnerName must be sent by L1 !!!!!!!!!!!!!!!!!!!!!!!!!!
            // this will force constraint violation !!!!!!!!!!!!!!
            std::string BurnerName = DEF::Undefined; 

            bool doCommit = false;

            if ( m_pGTE_PP_FLAME_PROFILE->select(Plant, PlantNo, BurnerName, FlameProfileNo) )
            {
              doCommit =  m_pGTE_PP_FLAME_PROFILE->update();
            }// if ( m_pGTE_PP_FLAME_PROFILE->select(FlameProfileNo) )
            else
            {
              doCommit =  m_pGTE_PP_FLAME_PROFILE->insert();
            }

            if (doCommit)
            {
              m_pGTE_PP_FLAME_PROFILE->commit();
            }
            else
            {
              m_pGTE_PP_FLAME_PROFILE->rollback();
            }
          } // for (int i = 0; i < SequenceLength; i++)
        }
        else
        {
          CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_FlameProfileUnused(sMessage);
        }

      } // if ( RetValue )

      //m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

      //********    send internal event  ***********************************************************************

      //SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL241Level1Param(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL241Level1Param";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo        = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL241::UnitNo);

      std::string ParamName = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL241::ParamName);
      double ParamValue     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL241::ParamValue);
      CORBA::Any SpareAny   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL241::Spare);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      long PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,"UnitNo",UnitNo,1,2);

      //********    main telegram data   ***********************************************************************

      DataKey   = generateDataKey(TlgName);  

      ParamName = CDataConversion::Trim(ParamName);
      log("Trimmed Value for ParamName -" + ParamName + "-",3);

      std::map<std::string,double> ParameterList;
      std::map<std::string,double>::iterator itParam;

      // ****************
      // general handling
      // ****************
      if ( !ParamName.empty() )
      {
        ParameterList.insert ( std::pair<std::string,double> (ParamName, ParamValue) );
      }

      if ( ParameterList.size() > 0 )
      {
        for ( itParam = ParameterList.begin(); itParam != ParameterList.end(); ++itParam)
        {
          std::string Name  = itParam->first;
          double Value      = itParam->second;
          // L1-Double sent parameter may be not a DParam type on L2
          if ( m_pGT_PARAM->isParam(Plant, PlantNo, Name, 0, CSMC_DBData::unspecLong) )
          {
            // This parameter is really in the GT_PARAM
            long ActParamType = m_pGT_PARAM->getTYPE(1);
            
            if ( m_pGT_PARAM->checkMinMaxRange(Plant, PlantNo, Name, 0, ActParamType,CDataConversion::DoubleToString(Value))  )
            {
              RetValue = RetValue && m_pGT_PARAM->updateValue(Plant, PlantNo, Name, 0, ActParamType,CDataConversion::DoubleToString(Value));
              if ( RetValue )
              {
                 CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();
                 sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                 pEventLog->EL_ParameterUpdate(sMessage, Name.c_str(), CDataConversion::DoubleToString(Value).c_str());
                 m_pGT_PARAM->commit();
              }
              else
              {
                std::string Message = "CEAF_TelegramHandler: Update failed on parameter " + Name;

                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());

                m_pGT_PARAM->rollback();

                RetValue = false;

                break;
              }
            } // if ( m_pGT_PARAM->checkMinMaxRange(Plant, PlantNo, Name, 0, DEF_GC_PARAM_TYPE::DParam, Value) )
          } // if ( m_pGT_PARAM->isParam(Plant, PlantNo, Name, 0, DEF_GC_PARAM_TYPE::DParam) )
          else
          {
            RetValue = false;

            std::string Message = "CEAF_TelegramHandler: Invalid parameter name:" + Name;

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),Message.c_str());

          }
        } // for ( itParam = ParameterList.begin(); itParam != ParameterList.end(); ++itParam)
      }
      else
      {
        RetValue = false;
      }

      //********    Define Event *******************************************************************************

      if ( RetValue ) 
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFParameterUpdate);
        //isPlantEvent = true;

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),   DATA::DateTime        ,Now.assDate());

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParaArea        , "EAF");
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ProdPracPointer , "unkown");

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParamName       , ParamName);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::ParamValue      , CDataConversion::DoubleToString(ParamValue).c_str());


        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);
      }
      
      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);

    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL250WasteGas(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL250WasteGas";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL250::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL250::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL250::TreatId);

      double ConcCO       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::ConcCO);
      double ConcCO2      = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::ConcCO2);
      double ConcO2       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::ConcO2);
      double ConcHe       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::ConcHe);
      double ConcAr       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::ConcAr);
      double WasteGasTemp = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::WasteGasTemp);
      double WasteGasFlow = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::WasteGasFlow);    
      double MomentO2     = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL250::AmountOxygen);

      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL250::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"      ,UnitNo       ,1  ,2);
      checkValidity(TlgName,"ConcAr"      ,ConcAr       ,0. ,100.);
      checkValidity(TlgName,"ConcCO"      ,ConcCO       ,0. ,100.);
      checkValidity(TlgName,"ConcCO2"     ,ConcCO2      ,0. ,100.);
      checkValidity(TlgName,"ConcHe"      ,ConcHe       ,0. ,100.);
      checkValidity(TlgName,"ConcO2"      ,ConcO2       ,0. ,100.);
      checkValidity(TlgName,"WasteGasTemp",WasteGasTemp ,0. ,2000.);
      checkValidity(TlgName,"MomentO2"    ,MomentO2     ,0. ,9999999.);

      CDataConversion::SetInvalidToDefault(ConcAr ,0.,-1.);
      CDataConversion::SetInvalidToDefault(ConcCO ,0.,-1.);
      CDataConversion::SetInvalidToDefault(ConcCO2,0.,-1.);
      CDataConversion::SetInvalidToDefault(ConcHe ,0.,-1.);
      CDataConversion::SetInvalidToDefault(ConcO2 ,0.,-1.);

      seqWasteGas SeqWasteGas;
      sWasteGas   WasteGas;

      WasteGas.WasteGasType = DEF_GAS::Ar;
      WasteGas.WasteGasConc = ConcAr;
      CIntfData::insert(SeqWasteGas,WasteGas);
      WasteGas.WasteGasType = DEF_GAS::CO;
      WasteGas.WasteGasConc = ConcCO;
      CIntfData::insert(SeqWasteGas,WasteGas);
      WasteGas.WasteGasType = DEF_GAS::CO2;
      WasteGas.WasteGasConc = ConcCO2;
      CIntfData::insert(SeqWasteGas,WasteGas);
      WasteGas.WasteGasType = DEF_GAS::He;
      WasteGas.WasteGasConc = ConcHe;
      CIntfData::insert(SeqWasteGas,WasteGas);
      WasteGas.WasteGasType = DEF_GAS::O2;
      WasteGas.WasteGasConc = ConcO2;
      CIntfData::insert(SeqWasteGas,WasteGas);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setWasteGas(DataKey.c_str(), DATA::WasteGasConc, SeqWasteGas);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::WasteGas);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::WasteGasTemp,    WasteGasTemp );
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::WasteGasFlow,    WasteGasFlow );
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::MomentO2,        MomentO2); 

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;

}

bool CEAF_TelegramHandler::DoProcessEAL260MatHandReport(const std::string& Key, const std::string& TlgName)
{
  //=================     M A T E R I A L   H A N D L I N G   R E P O R T         ============================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL260::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL260::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL260::TreatId);

      long Target     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_EAL260::Target);
      long Source     = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_EAL260::Source);
      long RecipeNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_EAL260::RecipeNo);
      long BatchStat  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_EAL260::BatchStat);

      CORBA::Any AnyMatCode     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL260::MatCode);
      CORBA::Any AnyMatWeight   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL260::MatWeight);
      CORBA::Any AnySourceNo    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL260::SourceNo);
      CORBA::Any AnyFeedingRate = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL260::FeedingRate);
      CORBA::Any AnySpare       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL260::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant = m_pGC_Plant_Container->getPlant(PlantId);

      DEF::seqString SeqMatCode;
      DEF::seqDouble SeqMatWeight;
      DEF::seqLong SeqSourceNo;
      DEF::seqDouble SeqFeedingRate;

      CIntfData::FromAny(SeqMatCode,AnyMatCode);
      CIntfData::FromAny(SeqMatWeight,AnyMatWeight);
      CIntfData::FromAny(SeqSourceNo,AnySourceNo);
      CIntfData::FromAny(SeqFeedingRate,AnyFeedingRate);


      //********    Convert and check telegram data  *********************************************************   
      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1 ,2);
      checkValidity(TlgName,"Target"         ,Target         ,1 ,9);
      checkValidity(TlgName,"Source"         ,Source         ,1 ,4);

      checkValidity(TlgName,"RecipeNo"       ,RecipeNo       ,1 ,100000); // referenced by GC_RECIPE_L1 
      checkValidity(TlgName,"BatchStat"      ,BatchStat      ,0 ,9);

      checkValidity(TlgName,"SeqMatWeight"   ,SeqMatWeight   ,0 ,999999.); 
      checkValidity(TlgName,"SeqSourceNo"    ,SeqSourceNo    ,0 ,10); 
      checkValidity(TlgName,"SeqFeedingRate" ,SeqFeedingRate ,0 ,999999.); 



      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);
   
        std::string L2RecipeName   = m_pGC_Recipe_L1Container->getL2RecipeNameByL1No( RecipeNo );
        std::string L2RecipeSource = m_pGC_SourceContainer->getL2SourceNameByL1No( Source );
        std::string L2RecipeTarget = m_pGC_Charge_Dest_Container->getDestNameByNo( Target );
        long L2RecipeNo            = m_pGC_Recipe_L1Container->getL2RecipeNoByL1No ( RecipeNo );

        // convert L2RecipeNo in case of receiving L1 data for already finished recipes
        CSMC_RecipeHandler RecipeHandler;
        RecipeHandler.checkMatHandlingRecipeData(Plant, HeatId, TreatId, L2RecipeSource, L2RecipeName, L2RecipeNo);

        // check RecipeStatus change
        m_StatusHandler.isStatusChanged(PlantId, L2RecipeName, BatchStat);

        seqBatch SeqBatch;

        // iteration over all sequences, SeqMatCode gives counter for iterator
        for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
        {
          sBatch   Batch;

          std::string MatCode;
          double MatWeight    = -1.;
          long SourceNo     = -1;
          double FeedingRate  = -1.;

          CIntfData::getAt(MatCode,SeqMatCode,i);
          CIntfData::getAt(MatWeight,SeqMatWeight,i);
          CIntfData::getAt(SourceNo,SeqSourceNo,i);
          CIntfData::getAt(FeedingRate,SeqFeedingRate,i);        

          MatCode = CDataConversion::Trim(MatCode);
          log("Trimmed Value for MatCode -" + MatCode + "-",3);

          if ( !MatCode.empty() )
          {
            Batch.MatCode       = MatCode.c_str();
            Batch.Mass          = MatWeight;
            Batch.MatFeedSpeed  = FeedingRate;
            Batch.Source        = SourceNo;

            if ( MatCode.empty() || MatWeight < 0.01 )
            { 
              if ( BatchStat != 6 && 
                   BatchStat != 9 )    // // DischargeStart && Discharged     
              {
                std::string Message = TlgName +"::MatCode " + MatCode + " - MatWeight invalid " + CDataConversion::DoubleToString(MatWeight);
                CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
              }
            }
            else
            {
              CIntfData::insert(SeqBatch,Batch);
            }
          } // if ( !MatCode.empty() )
        } // for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)

        //********    Define Event *******************************************************************************

        if ( L2RecipeName == DEF::Undefined ||
             L2RecipeName.empty()           || 
             L2RecipeSource.empty()         || 
             L2RecipeTarget.empty()         ||
             L2RecipeNo < 0 )
        {
          std::string Message = TlgName +"::RecipeName = " + L2RecipeName + "; RecipeSource = " + L2RecipeSource + "; RecipeNo = " + CDataConversion::LongToString(L2RecipeNo) + "; RecipeTarget = " + L2RecipeTarget;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
        }
        else
        {
          if ( CIntfData::getLength(SeqBatch) == 0 )
          {
            if ( BatchStat != 6 && 
                 BatchStat != 9 )    // // DischargeStart && Discharged     
            {
              std::string Message = TlgName +"::MatWeight not available - RecipeName = " + L2RecipeName + "; RecipeNo = " + CDataConversion::LongToString(L2RecipeNo) + ";";
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
            }
          }

          EventMessageVector.push_back( EAF_EvMsg::evEAFMaterialHandlingReport);

          //********    Write telegram data  ***********************************************************************
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeName     , L2RecipeName);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeSource   , L2RecipeSource);
          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::RecipeTarget   , L2RecipeTarget);
          m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::RecipeNo       , L2RecipeNo);

          if ( 0 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Disabled);
          else if ( 1 == BatchStat )
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Enabled);
          else if ( 2 == BatchStat )
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::ProcessingStart);
          else if ( 3 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Weighed);
          else if ( 4 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::WeighingComplete);
          else if ( 5 == BatchStat )
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::FirstMaterialInChargingHopper);
          else if ( 6 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::DischargeStart);
          else if ( 7 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::WeighingCompleteUpdate);
          else if ( 8 == BatchStat )
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::LastMaterialInChargingHopper);
          else if ( 9 == BatchStat ) 
            m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::RecipeStatus, DEF_GC_RECIPE_STATUS::Discharged);
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),"EAL260 :: BatchStat");
          }

          m_pTelegram_Adapter->m_pIntf_OUT->setBatch(DataKey.c_str(), DATA::RecipeContent, SeqBatch);

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL261MatAvailibilty(const std::string& Key, const std::string& TlgName)
{	
  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL261MatAvailibilty";
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
	long PlantNo	 = -1;
	bool updateEAFBin=false;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo           = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL261::UnitNo);
      long ActionFlag  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, Telegram_EAL261::ActionFlag);

      CORBA::Any AnyMatCode     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL261::MatCode);
      CORBA::Any AnyMinWeight   = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL261::MinWeight);
      CORBA::Any AnySourceNo    = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL261::SourceNo);
      CORBA::Any AnySource      = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL261::Source);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      DEF::seqString SeqMatCode;
      DEF::seqDouble SeqMinWeight;
      DEF::seqLong SeqSource;
      DEF::seqLong SeqSourceNo;

      CIntfData::FromAny(SeqMatCode,AnyMatCode);
      CIntfData::FromAny(SeqMinWeight,AnyMinWeight);
      CIntfData::FromAny(SeqSource,AnySource);
      CIntfData::FromAny(SeqSourceNo,AnySourceNo); 

      //********    Convert and check telegram data  *********************************************************   

      CDataConversion::SetInvalidToDefault(ActionFlag,DEF::Inv_Long,-1);

      checkValidity(TlgName, Telegram_EAL261::UnitNo,     UnitNo,     1 ,2);
      checkValidity(TlgName, Telegram_EAL261::ActionFlag, ActionFlag, 0 ,1);
      checkValidity(TlgName, Telegram_EAL261::Source,     SeqSource,  1 ,2    ,0);
      checkValidity(TlgName, Telegram_EAL261::SourceNo,   SeqSourceNo,1 ,100  ,0);

      //********    main telegram data   ***********************************************************************

      if ( RetValue )
      {
        DataKey   = generateDataKey(TlgName);  

  
        std::set<std::string> PurposeList;
        std::multimap<std::string,std::string> SourcePurposeList;

        long UnitGroupNo = -1;

        // check if availabilities should be set for EAF or EAF_1
        // use entries in ini file
        // [MATERIALHANDLING]
        // PlantIDNames = EAF_1,EAF_2
        // ...
        bool UseMaterialAvailibilities = true;
        bool UseSourceAvailibilities = false;
        std::vector<std::string> PlantIDNames;
        std::vector<std::string> StaticAvailibilityMaterials;
        std::vector<std::string>::iterator itPlantIDNames;
        std::vector<std::string> Sources;
        std::vector<std::string>::iterator itSources;
        cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","PlantIDNames",PlantIDNames);
        // excluded materials which will not changed by L1
        cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","StaticAvailibilityMaterials",StaticAvailibilityMaterials);
        cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","UseMaterialAvailibilities",UseMaterialAvailibilities);
        cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","UseSourceAvailibilities",UseSourceAvailibilities);

        if ( UseMaterialAvailibilities )
        {
          UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant,m_pGC_Plant_Container->getPlantNo(PlantId));
         
          if ( UseSourceAvailibilities )
          {
            cCBS_StdInitBase::getInstance()->getEntryList("MATERIALHANDLING","Sources",Sources);
          }
          // message contains ALL possible materials
          // all existing entreis in GT_MAT_PURP for given source / purpose must be removed !
          if (ActionFlag == 0)								
          { 
            for ( long i = 0 ; i < CIntfData::getLength(SeqSource) ; ++i)
            {
              long Source    = -1;
              CIntfData::getAt(Source,SeqSource,i);

              if ( SourcePurposeList.find(CDataConversion::LongToString(Source)) == SourcePurposeList.end() )
              {
                if ( Source == 1 )
                {
									//SRKO: For handling Bin material availability considering EAFBin and EAFTappingBin(handled by Bin of LF).
                  //SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Bin_Avail));
									SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::EAFBin_Avail));

                  // add purposes of Bin System to list that purposes will be deleted for all metarials
                  std::set<std::string>::iterator it;
                  std::set<std::string> PurposeBinSystemList;

                  m_pGT_PARAM->getKeyedValueList(Plant, m_pGC_Plant_Container->getPlantNo(PlantId), "BinSystemPurpose", 0, DEF_GC_PARAM_TYPE::SSParam, CSMC_DBData::unspecString, CSMC_DBData::unspecString, PurposeBinSystemList);

                  for ( it = PurposeBinSystemList.begin(); it != PurposeBinSystemList.end() ; ++ it )
                  {
                    SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),(*it)));
                  }

                }
                else if ( Source == 2 )
                {
                  SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Hand_Avail));
                }
                else if ( Source == 3 || Source == 4 )
                {
                  SourcePurposeList.insert( std::pair<std::string,std::string> (CDataConversion::LongToString(Source),DEF_GT_PURP::Wire_Avail));
                }
              } // if ( SourcePurposeList.find(CDataConversion::LongToString(Source)) == SourcePurposeList.end() )
            }

            std::multimap<std::string,std::string>::iterator its;
            for ( its = SourcePurposeList.begin() ; its != SourcePurposeList.end(); ++its )
            {
              for ( itSources = Sources.begin() ; itSources != Sources.end() ; ++itSources )
              {
                if ( *itSources == its->first )
                {
                  cCBS_StdInitBase::getInstance()->replaceWithEntry(*itSources,"UnitGroupNo",UnitGroupNo);
                }
              }

              if ( !StaticAvailibilityMaterials.empty() )
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRows(UnitGroupNo, StaticAvailibilityMaterials, its->second);
              }
              else
              {
                // functions does not commit SQL here!
                m_pGT_MAT_PURP->deleteRow(UnitGroupNo, CSMC_DBData::unspecString, its->second);
              }

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_MaterialAvailabilityChanged(sMessage, 0, "All", its->second.c_str());
            }
          }

          bool doCommit = true;

          // iteration over all sequences, SeqMatCode gives counter for iterator
          for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
          {
            std::string Purpose;
            std::string Source;
            std::string MatCode;
            double MinWeight    = -1.;
            double AvailWeight  = -1.;
            long lSource   = -1;
            long SourceNo  = -1;

            CIntfData::getAt(MatCode,SeqMatCode,i);
            CIntfData::getAt(MinWeight,SeqMinWeight,i);
            CIntfData::getAt(AvailWeight,SeqMinWeight,i); // we assume AvailWeight == MinWeight, L1 sends MinWeight == 0 if material is not available
            CIntfData::getAt(lSource,SeqSource,i);
            CIntfData::getAt(SourceNo,SeqSourceNo,i);

            std::string PurposeBinSystem  = CSMC_DBData::unspecString;
            std::string SourceBinSystem   = CDataConversion::LongToString(SourceNo);

            // read PurposeBinSystem from gt_param / gt_param_matrix
            m_pGT_PARAM->getKeyedValue(Plant, m_pGC_Plant_Container->getPlantNo(PlantId), "BinSystemPurpose", 0, DEF_GC_PARAM_TYPE::SSParam, SourceBinSystem, CSMC_DBData::unspecString, PurposeBinSystem);

            MinWeight = CDataConversion::SetInvalidToDefault(MinWeight,0.);

            if ( lSource == 1 )
            {
							//Purpose = DEF_GT_PURP::Bin_Avail; //SRKO: For handling Bin material availability considering EAFBin and EAFTappingBin(handled by Bin of LF).
							Purpose = DEF_GT_PURP::EAFBin_Avail;
              Source  = DEF_GC_SOURCE::Bin;
							updateEAFBin=true; //SRKO: Update Bin material availabilities for EAF
            }
            else if ( lSource == 2 )
            {
              Purpose = DEF_GT_PURP::Hand_Avail;
              Source  = DEF_GC_SOURCE::Hand;

              // set MinWeight for Hand Additions to a valid value 
              if ( MinWeight <= 0.01 )
              {
                cCBS_StdInitBase::getInstance()->replaceWithEntry("MATERIALHANDLING","MinWeightHand",MinWeight);
              }
            }
            else if ( lSource == 3 )
            {
              Purpose = DEF_GT_PURP::Yard_Avail;
              Source  = DEF_GC_SOURCE::Yard;
            }

            if ( !Purpose.empty() && PurposeList.find(Purpose) == PurposeList.end() )
            {
              PurposeList.insert(Purpose);
            }

            // sequence might contain empty entries
            // sequence is related to physical bin number
            if ( !MatCode.empty() && !Purpose.empty() )
            {
              log("### EAL261 Update PD_MAT_AVAIL", 3);	

              MatCode = CDataConversion::Trim(MatCode);
              log("Trimmed Value for MatCode -" + MatCode + "-",3);

              // m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight does not perform commit !
              if ( m_pPD_MAT_AVAIL->updateOrInsertRowForMinWeight(Plant, m_pGC_Plant_Container->getPlantNo(PlantId),
                                                                  Source ,SourceNo, MatCode, AvailWeight, MinWeight) )
              {
                if (ActionFlag == 1)                  // updating existing Materials only
                {
                  if ( MinWeight < 0. )                 // Material set, Weight incorrect
                  {
                    std::string Message = "EAL261 :: MatCode " + MatCode + " - MinWeight < 0";
                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
                  }
                  else if ( MinWeight > 0. )                 // Material set, Weight > 0 means material available
                  {
                    // we need to INSERT this Material if not already set.
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, Purpose);
                    
                    if ( PurposeBinSystem != CSMC_DBData::unspecString )
                    {
                      m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, PurposeBinSystem);

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), PurposeBinSystem.c_str());
                    }

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), Purpose.c_str());
                  }
                  else                                     // Material set, Weight == 0 means material not available 
                  {
                    // we need to DELETE this material if it exists.
                    if (m_pGT_MAT_PURP->deleteOnExist(UnitGroupNo, MatCode, Purpose))
                    {
                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 0, MatCode.c_str(), Purpose.c_str());
                    }
                  }
                }  
                else if (ActionFlag == 0)                       // complete update 
                {
                  // complete update : delete for all materials has been done before.
                  // we need to INSERT those materials with MatWgt>0 only.
                  if ( MinWeight > 0. )
                  {
                    // m_pGT_MAT_PURP->insertRow does not perform commit !
                    doCommit = m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, Purpose);

                    if ( PurposeBinSystem != CSMC_DBData::unspecString )
                    {
                      m_pGT_MAT_PURP->insertOrReplace(UnitGroupNo, MatCode, PurposeBinSystem);

                      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                      pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), PurposeBinSystem.c_str());
                    }

                    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
                    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                    pEventLog->EL_MaterialAvailabilityChanged(sMessage, 1, MatCode.c_str(), Purpose.c_str());
                  }
                }
              }
              else
              {
                cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
                sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
                pEventLog->EL_DBWriteError(sMessage,"", "PD_MAT_AVAIL", "" );
              }

              if (!doCommit) break;
            } // if (!MatCode.empty()) // update/insert PD_BIN now
          }// for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
          //20120810: GEPA commit/rollback moved to here: When L1 is sending an empty material list (is bad, but possible) the deletion of materials
          //          which were available before, transaction is neither finished by commit or rollback !!!

					if(updateEAFBin)//SRKO: Update Bin material availabilities for EAF
					{
						std::string From_Purp_Code_1=DEF_GT_PURP::EAFBin_Avail;
						std::string From_Purp_Code_2=DEF_GT_PURP::EAFTappingBin_Avail;
						std::string To_Purp_Code=DEF_GT_PURP::Bin_Avail;
						Plant=DEF_GC_PLANT_DEF::EAF;
						PlantNo=1;
						UnitGroupNo = m_pGC_Plantgroup_Container->getUnitGroupNo(Plant,PlantNo);
						doCommit=m_pGT_MAT_PURP->mergePurposeCodes(Plant, PlantNo, From_Purp_Code_1, From_Purp_Code_2, To_Purp_Code);
					} 

          if (doCommit)
          {
                m_pGT_MAT_PURP->commit(); // commits all
          }
          else
          {
              m_pGT_MAT_PURP->rollback(); // rolls back all SQL statements

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),"EAL261 :: DB Error");
          }
          //20120810: end

          seqStringList SeqStringList;
          std::set<std::string>::iterator it;
          for ( it = PurposeList.begin(); it != PurposeList.end(); ++it)
          {
            CIntfData::insert(SeqStringList,(*it).c_str() );
          }

          //********    Define Event *******************************************************************************

          if (doCommit)
          {
            // test item isPlantEvent = true;
            EventMessageVector.push_back( EAF_EvMsg::evEAFHandleUpdatePurpose);
          }

          //********    Write telegram data  ***********************************************************************

          if (doCommit)
          {
            m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DateTime,Now.assDate());

            m_pTelegram_Adapter->m_pIntf_OUT->setStringList(DataKey.c_str(),DATA::UpdatedPurpose,SeqStringList);

            m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

            m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

            //********    send internal event  ***********************************************************************

            SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);
          }

          //********    End processing data  ***********************************************************************
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_MaterialAvailabilityUnused(sMessage);
        }
      }//  if ( checkValidity(TlgName,"ActionFlag",ActionFlag,0,1) )
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}//bool CEAF_TelegramHandler::DoProcessEAL261MatAvailibilty(const std::string& Key, const std::string& TlgName)

bool CEAF_TelegramHandler::DoProcessEAL262MaterialFeedingSystem(const std::string& Key, const std::string& TlgName)
{
  //=========================    Material Feeding System   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL262::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL262::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL262::TreatId);

      CORBA::Any AnyFeederNo       = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL262::FeederNo);
      CORBA::Any AnyMatCode        = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL262::MatCode);
      CORBA::Any AnyMatCodeWgt     = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL262::MatWeight);
      CORBA::Any AnyMatFeedingRate = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key, Telegram_EAL262::FeedingRate);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      checkValidity(TlgName,"UnitNo"     ,UnitNo     ,1  ,2);


      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);   

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);

        DEF::seqLong SeqFeederNo;
        DEF::seqString SeqMatCode;
        DEF::seqDouble SeqMatWeight;
        DEF::seqDouble SeqFeedingRate;

        CIntfData::FromAny(SeqFeederNo,AnyFeederNo);
        CIntfData::FromAny(SeqMatCode,AnyMatCode);
        CIntfData::FromAny(SeqMatWeight,AnyMatCodeWgt);
        CIntfData::FromAny(SeqFeedingRate,AnyMatFeedingRate);

        seqBatch sqMatFeedingBatch;
        sBatch sBatchMatFeedingData;

        // iteration over all sequences, SeqMatCode gives counter for iterator
        for ( long i = 0 ; i <= CIntfData::getLength(SeqMatCode) ; ++i)
        {
          std::string MatCode;
          double MatWeight   = -1.;
          long FeederNo    = -1;
          double FeedingRate = -1.;

          CIntfData::getAt(FeederNo,SeqFeederNo,i);
          CIntfData::getAt(MatCode,SeqMatCode,i);
          CIntfData::getAt(MatWeight,SeqMatWeight,i);
          CIntfData::getAt(FeedingRate,SeqFeedingRate,i);

          MatCode = CDataConversion::Trim(MatCode);
          log("Trimmed Value for MatCode -" + MatCode + "-",3);

          if( !MatCode.empty() && MatWeight > 0. ) //valid values only
          {
            //InjectType don't necessary to use in EAF
            sBatchMatFeedingData.MatCode      = MatCode.c_str();
            sBatchMatFeedingData.Mass         = MatWeight;
            sBatchMatFeedingData.MatFeedSpeed = FeedingRate;
            sBatchMatFeedingData.Source       = FeederNo;

            CIntfData::insert(sqMatFeedingBatch, sBatchMatFeedingData); 
          }
        }

        if ( CIntfData::getLength(sqMatFeedingBatch) == 0 )
        {
          std::string Message = "EAL262 :: Feeding Data not available";
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
        }
        else
        {

					if(isRefiningPhaseStart(HeatId, TreatId) == false) //SARS JSW specific
					{
						std::string L2PhaseName = DEF_GC_PHASE::Refining;
						long L2PhaseNo   = 0;
						CDateTime StartTime;
    	  
						seqPhaseDataReport SeqPhaseDataReport ;
						sPhaseDataReport PhaseDataReport;
						PhaseDataReport.PhaseNo   = L2PhaseNo ; 
						PhaseDataReport.PhaseName = L2PhaseName.c_str() ; 
						PhaseDataReport.ElecCons  = 0.;
						PhaseDataReport.Duration  = 0.;
						PhaseDataReport.StartTime = StartTime.assDate();
						//PhaseDataReport.EndTime   = EndTime.assDate();
						CIntfData::insert(SeqPhaseDataReport,PhaseDataReport);
	  
						m_pTelegram_Adapter->m_pIntf_OUT->setPhaseDataReport(DataKey.c_str(),DATA::PhaseDataReport,SeqPhaseDataReport);
						m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::PhaseProcess       ,L2PhaseName);
						m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::PhaseNoProcess     ,L2PhaseNo);

						EventMessageVector.push_back(EAF_EvMsg::evEAFPhaseReport);
						log ("automatic set refining phase", 3);
					}

          //********    Define Event *******************************************************************************
          EventMessageVector.push_back(EAF_EvMsg::evEAFCyclicMeasurement);

          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,        DATA::MeasurementType, DEF_CYCLIC_MEASUREMENT_TYPES::MatFeeding);
          m_pTelegram_Adapter->m_pIntf_OUT->setBatch(DataKey.c_str(), DATA::MatFeedingData,  sqMatFeedingBatch); 

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

          // show interface content
          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }
        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }// if ( m_pTelegram_Adapter && 
    else
    {
      RetValue = false;
    }

  }// try
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), TlgName.c_str());    
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
  }

  return RetValue;
}// bool CEAF_TelegramHandler::DoProcessEAL262MaterialFeedingSystem(const std::string& Key, const std::string& TlgName)

bool CEAF_TelegramHandler::DoProcessEAL263MaterialFeedingStatus(const std::string& Key, const std::string& TlgName)
{
  //=========================    Material Feeding Status   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL263::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL263::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL263::TreatId);

      std::string MatCode = m_pTelegram_Adapter->m_pIntf_IN->getString(Key, Telegram_EAL263::MatCode);
      long FeedStat       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL263::FeedStat);
      long FeederNo       = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL263::FeederNo);
      double MatWeight    = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_EAL263::MatWeight);
      double FeedingRate  = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key, Telegram_EAL263::FeedingRate);  

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    Convert and check telegram data  *********************************************************   
      checkValidity(TlgName,"UnitNo"     ,UnitNo     ,1  ,2);  
      checkValidity(TlgName,"FeedStat"   ,FeedStat   ,1  ,2);
      checkValidity(TlgName,"FeederNo"   ,FeederNo   ,1  ,99);
      checkValidity(TlgName,"MatWeight"  ,MatWeight  ,0  ,999999.);
      checkValidity(TlgName,"FeedingRate",FeedingRate,0  ,999999.);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(HeatId);    

        seqBatch sqMatFeedingBatch;
        sBatch sBatchMatFeedingData;

        MatCode = CDataConversion::Trim(MatCode);
        log("Trimmed Value for MatCode -" + MatCode + "-",3);

        if( !MatCode.empty() ) //MatCode is a valid value
        {
          //InjectType don't necessary to use in EAF
          sBatchMatFeedingData.MatCode      = MatCode.c_str();
          sBatchMatFeedingData.Mass         = MatWeight;
          sBatchMatFeedingData.MatFeedSpeed = FeedingRate;
          sBatchMatFeedingData.Source       = FeederNo;

          CIntfData::insert(sqMatFeedingBatch, sBatchMatFeedingData); 

          //********    Define Event *******************************************************************************

          if( FeedStat == 1)
          {
            EventMessageVector.push_back(EAF_EvMsg::evEAFMatFeedingStart);
          }
          else if( FeedStat == 2)
          {
            EventMessageVector.push_back(EAF_EvMsg::evEAFMatFeedingStop);
          }
          else
            log("WARNING: Event EAL263: Unrecognizable FeedStat received!",3); 

          //********    Write telegram data  ***********************************************************************

          m_pTelegram_Adapter->m_pIntf_OUT->setBatch(DataKey.c_str(), DATA::MatFeedingData , sqMatFeedingBatch); 

          m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

          // show interface content
          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }// if ( m_pTelegram_Adapter && 
    else
    {
      RetValue = false;
    }

  }// try
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), TlgName.c_str());    
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
  }

  return RetValue;
}// bool CEAF_TelegramHandler::DoProcessEAL263MaterialFeedingStatus(const std::string& Key, const std::string& TlgName)

bool CEAF_TelegramHandler::DoProcessEAL270LiqMatReport(const std::string& Key, const std::string& TlgName)
{

  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL270LiqMatReport";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL270::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL270::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL270::TreatId);

      std::string LadleId = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL270::LadleId);
      long WeighingStat   = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL270::WeighingStat);    
      double Weight       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL270::Weight);  
      CORBA::Any SpareAny = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL270::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFLiqMatHandlReport);

      if( WeighingStat == DEF_LIQ_MAT_REPORT::LadleWeightAfterEAFTapping )
      {
        EventMessageVector.push_back(EAF_EvMsg::evEAFSetTappingMasses);
      }

      //********    Convert and check telegram data  ***********************************************************

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      LadleId   = CDataConversion::Trim(LadleId);

      CLadleID LadleID;

      if ( LadleID.checkLadleIDWithDefaultType(DEF_GC_LADLE_TYPE::TeemingLadle, LadleId) ) //SARS
      {
        LadleType          = LadleID.getLadleType(LadleId);
        LadleNo            = LadleID.getLadleNo(LadleId);
      }

      long LadlePos = DEF_GC_LADLE_POS::TT;

      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1   ,2);
      checkValidity(TlgName,"LadleNo"        ,LadleNo        ,1   ,99);
      checkValidity(TlgName,"WeighingStat"   ,WeighingStat   ,11  ,14);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

			//SARS : as per JSW as ladle no not coming from L1
			if(m_pPD_HEAT_DATA->select(HeatId, TreatId, Plant))
			{
					LadleNo = m_pPD_HEAT_DATA->getLADLENO(1);
					LadleType = m_pPD_HEAT_DATA->getLADLETYPE(1);
			}

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        // Ladle Deslagged: According to Rose only for WgtStat == (14 | 23)
        if ( WeighingStat == DEF_LIQ_MAT_REPORT::LadleSteelWeightAfterEAFDeslagging )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::LadleDeslagged, 1 );
        }
        else
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey, DATA::LadleDeslagged, 0 );
        }

        if( WeighingStat == DEF_LIQ_MAT_REPORT::LadleWeightAfterEAFTapping )
        {
          // special not req for JSW
					/*if(m_pPD_LADLE->select(LadleNo,DEF_GC_LADLE_TYPE::TeemingLadle))
					{
						double TareWeight = m_pPD_LADLE->getTAREWEIGHT(1);
						TareWeight     = CDataConversion::SetInvalidToDefault(TareWeight, 0);
						Weight = Weight - TareWeight;						
					}*/


          WeighingStat = DEF_LIQ_MAT_REPORT::LadleNettWeightAfterEAFTapping;
          m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey, DATA::TappingMass,Weight);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,  DATA::LadleNo,        LadleNo);
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey,  DATA::LadleType,      LadleType);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,  DATA::LadleLocation,  LadlePos);
        m_pTelegram_Adapter->m_pIntf_OUT->setDouble(DataKey,  DATA::MeasWeight,     Weight);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey,  DATA::WeighingType,   WeighingStat);   

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessEAL280PhaseReport(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;
  //------------ general variables ------------------
  std::string Function = "CEAF_TelegramHandler::DoProcessEAL280PhaseReport";
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId;
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;      
  std::string Plant;      
  std::string LadleType;
  std::string LadleId;
  long LadleNo  = -1;
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
      
      UnitNo    = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL280::UnitNo);
      HeatId    = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL280::HeatId);
      TreatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL280::TreatId);

      long PhaseNo          = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL280::PhaseNo);
      long PhaseType        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_EAL280::PhaseType);
      double ElecCons       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL280::ElecCons);
      double PhaseDur       = m_pTelegram_Adapter->m_pIntf_IN->getDouble(Key,Telegram_EAL280::PhaseDur);
      CORBA::Any PhaseStart = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL280::PhaseStart );
      CORBA::Any PhaseEnd   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL280::PhaseEnd);
      CORBA::Any SpareAny   = m_pTelegram_Adapter->m_pIntf_IN->getAny   (Key,Telegram_EAL280::Spare);

      PlantId   = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant     = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler for plant *******************************************************************************

      //m_StatusHandler.removeID( PlantId );

      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFPhaseReport);

      //********    Convert and check telegram data  ***********************************************************
           

      HeatId    = CDataConversion::Trim(HeatId);
      TreatId   = CDataConversion::Trim(TreatId);

      checkValidity(TlgName,"UnitNo"         ,UnitNo         ,1   ,2);
      checkValidity(TlgName,"PhaseNo"        ,PhaseNo        ,1   ,10);
      checkValidity(TlgName,"PhaseType"      ,PhaseType      ,1   ,10);
      checkValidity(TlgName,"ElecCons"       ,ElecCons       ,0.  ,9999999.);
      checkValidity(TlgName,"PhaseDur"       ,PhaseDur       ,0.  ,999.);

      std::string L2PhaseName;
      long L2PhaseNo = PhaseNo;

      if( PhaseType == 1)
      {
        L2PhaseName = DEF_GC_PHASE::Preparation;
        L2PhaseNo   = 0;
      }
      else if(PhaseType == 2)
      {
        L2PhaseName = DEF_GC_PHASE::MeltBskNo;
      }
      else if(PhaseType == 3)
      {
        L2PhaseName = DEF_GC_PHASE::HeatLiqChgNo;
      }
      else if(PhaseType == 4)
      {
        L2PhaseName = DEF_GC_PHASE::BskAndLiqChgNo;
      }
      else if(PhaseType == 10)
      {
        L2PhaseName = DEF_GC_PHASE::Refining;
        L2PhaseNo   = 0;
      }

      CDateTime StartTime(PhaseStart);
      CDateTime EndTime(PhaseEnd);

      seqPhaseDataReport SeqPhaseDataReport ;
      sPhaseDataReport PhaseDataReport;
      PhaseDataReport.PhaseNo   = L2PhaseNo ; 
      PhaseDataReport.PhaseName = L2PhaseName.c_str() ; 
      PhaseDataReport.ElecCons  = ElecCons;
      PhaseDataReport.Duration  = PhaseDur;
      PhaseDataReport.StartTime = StartTime.assDate();
      PhaseDataReport.EndTime   = EndTime.assDate();
      CIntfData::insert(SeqPhaseDataReport,PhaseDataReport);

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        DataKey            = generateDataKey(HeatId);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setPhaseDataReport(DataKey.c_str(),DATA::PhaseDataReport,SeqPhaseDataReport);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::PhaseProcess       ,L2PhaseName);
        m_pTelegram_Adapter->m_pIntf_OUT->setLong  (DataKey, DATA::PhaseNoProcess     ,L2PhaseNo);
      
        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

        //********    End processing data  ***********************************************************************

        log (TlgName + ": Finished", 3);
      }// 
      else
      {
        RetValue = false;
      }
    }
    catch (cCBS_DBExc &e)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function.c_str(), TlgName.c_str()); 
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
  }

  return RetValue;
}

bool CEAF_TelegramHandler::DoProcessSYL293ScrapLoadingInstructionRequest(const std::string& Key, const std::string& TlgName)
{
  //=========================  Scrap Loading Instruction Request   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_SYL293::UnitNo);

      long ContainerType = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_SYL293::ContainerType);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);
      CDataConversion::SetInvalidToDefault(ContainerType,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,Telegram_SYL293::UnitNo,UnitNo,1,2);

      //********    main telegram data   ***********************************************************************

      DataKey   = generateDataKey(TlgName);

      // = DEF_GC_SCRAP_CONTAINER_TYPE::Chute; // not used

      if ( ContainerType == 1 )
      {
        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(EAF_EvMsg::evEAFOrderScrap);

        //********    Write telegram data  ***********************************************************************
        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(),DATA::ContainerType,DEF_GC_SCRAP_CONTAINER_TYPE::Basket);

        m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);
      }
      else
      {
        RetValue = false;
      }

      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }// if ( m_pTelegram_Adapter && 
    else
    {
      RetValue = false;
    }

  }// try
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), TlgName.c_str());    
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
     Function.c_str(), TlgName.c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
  }

  return RetValue;
}// bool CEAF_TelegramHandler::DoProcessSYL293ScrapLoadingInstructionRequest(const std::string& Key, const std::string& TlgName)

bool CEAF_TelegramHandler::DoProcessSYL292ScrapLoadingResults(const std::string& Key, const std::string& TlgName)
{
  //=========================  Scrap Loading Results   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_SYL292::UnitNo);
      //GEPA :: Note : From L1 we are getting the customer heatId/TreatId !!!
      CustHeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_SYL292::HeatId );
      CustTreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_SYL292::TreatId);

      std::string ProdOrderId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_SYL292::ProdOrderId );

      long ContainerType       = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key,Telegram_SYL292::ContainerType);
      long ContainerNo         = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key,Telegram_SYL292::ContainerNo);
      long ContainerSeqNo      = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key,Telegram_SYL292::ContainerSeqNo );
      long TotalNoOfContainers = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key,Telegram_SYL292::TotalNoOfContainers);
      long LoadingStat         = m_pTelegram_Adapter->m_pIntf_IN->getLong (Key,Telegram_SYL292::LoadingStat);
      CORBA::Any AnyMatCode    = m_pTelegram_Adapter->m_pIntf_IN->getAny  (Key,Telegram_SYL292::MatCode );
      CORBA::Any AnyMatWeight  = m_pTelegram_Adapter->m_pIntf_IN->getAny  (Key,Telegram_SYL292::MatWeight);
      CORBA::Any AnyMatLoadSeq = m_pTelegram_Adapter->m_pIntf_IN->getAny  (Key,Telegram_SYL292::MatLoadSeq);
      CORBA::Any SpareAny      = m_pTelegram_Adapter->m_pIntf_IN->getAny  (Key,Telegram_SYL292::Spare);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      // heatid or treatid is not always kown -- notice order can also be different
      // CheckCustomerData(TlgName, CustHeatId, CustTreatId, HeatId, TreatId, Plant);

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      ProdOrderId    = CDataConversion::Trim(ProdOrderId);

      // we have two principle states for scrap loading results
      // 1) heat is planned   -> only ProdOrderId is available
      // 2) heat is announced -> in addition CustHeatId, CustTreatId are avialable
      // we need to check for CustomerData in state 2 only !

      if ( ProdOrderId == DEF::Inv_String && ProdOrderId.empty() )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), Telegram_SYL292::ProdOrderId, "is empty");
      }
      else if ( !m_pPP_HEAT->selectOrder(ProdOrderId) )
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), Telegram_SYL292::ProdOrderId, std::string(ProdOrderId + " not exist").c_str());   
      }
      else
      {
        CustHeatId    = CDataConversion::Trim(CustHeatId);
        CustTreatId   = CDataConversion::Trim(CustTreatId);

        if ( CustHeatId != DEF::Inv_String && !CustTreatId.empty() )
        {
          //GEPA :: Note : From L1 we are getting the customer heatId/TreatId !!!
          //if ( RetValue && m_pPP_HEAT_PLANT->select(HeatId,TreatId,Plant) )
          if ( RetValue && m_pPP_HEAT_PLANT->selectByCustData(CustHeatId,CustTreatId,Plant,true) )
          {
            HeatId  = m_pPP_HEAT_PLANT->getHEATID(1);
            TreatId = m_pPP_HEAT_PLANT->getTREATID(1);
          }
        }
      }

      checkValidity(TlgName,"UnitNo"             ,UnitNo               ,1 ,2);
      checkValidity(TlgName,"ContainerType"      ,ContainerType        ,1 ,1);

      checkValidity(TlgName,"ContainerSeqNo"     ,ContainerSeqNo       ,0 ,20);
      checkValidity(TlgName,"TotalNoOfContainers",TotalNoOfContainers  ,0 ,20);
      checkValidity(TlgName,"LoadingStat"        ,LoadingStat          ,1 ,4);
      
      if ( RetValue )
      {
        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(TlgName);

        DEF::seqString SeqMatCode;
        DEF::seqLong SeqMatWeight;
        DEF::seqLong SeqMatLoadSeq;

        CIntfData::FromAny(SeqMatCode,AnyMatCode);
        CIntfData::FromAny(SeqMatWeight,AnyMatWeight);
        CIntfData::FromAny(SeqMatLoadSeq,AnyMatLoadSeq);

        seqBatch SeqBatch;

        // iteration over all sequences, SeqMatCode gives counter for iterator
        for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)
        {
          sBatch   Batch;

          std::string MatCode;
          long MatWeight    = -1;
          long SourceNo     = -1;
          long MatLoadSeq   = -1;

          CIntfData::getAt(MatCode,SeqMatCode,i);
          CIntfData::getAt(MatWeight,SeqMatWeight,i);
          CIntfData::getAt(MatLoadSeq,SeqMatLoadSeq,i);      

          MatCode = CDataConversion::Trim(MatCode);
          log("Trimmed Value for MatCode -" + MatCode + "-",3);

          if ( !MatCode.empty() )
          {
            Batch.MatCode             = MatCode.c_str();
            Batch.Mass                = MatWeight;
            Batch.MatLoadingSequence  = MatLoadSeq;

            if ( MatCode.empty() || MatWeight < 0.01 )
            { 
              std::string Message = TlgName +"::MatCode " + MatCode + " - MatWeight invalid " + CDataConversion::DoubleToString(MatWeight);
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorProcessingData(sMessage, Function.c_str(),Message.c_str());
            }
            else
            {
              CIntfData::insert(SeqBatch,Batch);
            }
          } // if ( !MatCode.empty() )
        } // for ( long i = 0 ; i < CIntfData::getLength(SeqMatCode) ; ++i)


        long BasketLocation = DEF::Inv_Long;
        long BatchStat      = DEF::Inv_Long;

        if ( LoadingStat == 1)
        {
          BasketLocation  = DEF_GC_SCRAP_CONTAINER_LOC::UNKNOWN;
          BatchStat       = DEF_GC_RECIPE_STATUS::Enabled;
        }
        else if ( LoadingStat == 2)
        {
          checkValidity(TlgName,"ContainerNo"        ,ContainerNo          ,1,20);
          BasketLocation  = DEF_GC_SCRAP_CONTAINER_LOC::YARD;
          BatchStat       = DEF_GC_RECIPE_STATUS::ProcessingStart;
        }
        else if ( LoadingStat == 3)
        {
          checkValidity(TlgName,"ContainerNo"        ,ContainerNo          ,1,20);

          BasketLocation  = DEF_GC_SCRAP_CONTAINER_LOC::YARD;
          BatchStat       = DEF_GC_RECIPE_STATUS::WeighingComplete;
        }
        else if ( LoadingStat == 4)
        {
          checkValidity(TlgName,"ContainerNo"        ,ContainerNo          ,1,20);

          BasketLocation  = DEF_GC_SCRAP_CONTAINER_LOC::YARD;
          BatchStat       = DEF_GC_RECIPE_STATUS::Disabled;
        }

        // BasketLocation =  DEF_GC_SCRAP_CONTAINER_LOC::EAF;
        // see DoProcessEAL215BasketHMDischarged

        //********    Define Event *******************************************************************************

        EventMessageVector.push_back(EAF_EvMsg::evEAFHandleSetBasketData);

        //********    Write telegram data  ***********************************************************************

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey.c_str(), DATA::ContainerType, DEF_GC_SCRAP_CONTAINER_TYPE::Basket); // ContainerType = 1
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey.c_str(), DATA::BasketId,      ContainerNo);                         //Physical Container ID
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey.c_str(), DATA::BasketInSeq,   ContainerSeqNo);                      //Basket No. in Sequence

        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey.c_str(), DATA::BasketLocation, BasketLocation);

        // m_pTelegram_Adapter->m_pIntf_OUT->setLong(DataKey.c_str(),   DATA::TotalNoOfContainers); // we get back from L1 what we send
        
        m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey.c_str(), DATA::RecipeStatus,  BatchStat);

        if ( LoadingStat == 1 ||
             LoadingStat == 2 ||
             LoadingStat == 3 )
        {
          m_pTelegram_Adapter->m_pIntf_OUT->setBatch  (DataKey.c_str(), DATA::RecipeContent, SeqBatch);
        }

        m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey.c_str(), DATA::UserCode,      "L1");

        m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

        //********    send internal event  ***********************************************************************

        SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,ProdOrderId,false);

        //********    End processing data  ***********************************************************************
      }
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }// if ( m_pTelegram_Adapter && 
    else
    {
      RetValue = false;
    }

  }// try
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), TlgName.c_str());    
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
  }

  return RetValue;
}// bool CEAF_TelegramHandler::DoProcessSYL292ScrapLoadingResults(const std::string& Key, const std::string& TlgName)
bool CEAF_TelegramHandler::DoProcessSYL295ScrapMaterialRequest(const std::string& Key, const std::string& TlgName)
{
  //=========================  Scrap Material Request   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  try
  {
    if ( m_pTelegram_Adapter && 
      m_pTelegram_Adapter->m_pIntf_IN && 
      m_pTelegram_Adapter->m_pIntf_OUT )
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_SYL295::UnitNo);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      //********    Convert and check telegram data  *********************************************************   

      // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
      CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

      checkValidity(TlgName,Telegram_SYL293::UnitNo,UnitNo,1,2);

      //********    main telegram data   ***********************************************************************

      DataKey   = generateDataKey(TlgName);
      //********    Define Event *******************************************************************************

      EventMessageVector.push_back(EAF_EvMsg::evEAFScrapMaterialAvail);

      //********    Write telegram data  ***********************************************************************

      m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey, DATA::UserCode           ,"L1");

      m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

      //********    send internal event  ***********************************************************************

//      SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,false);

            SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);
      //********    End processing data  ***********************************************************************

      log (TlgName + ": Finished", 3);
    }// if ( m_pTelegram_Adapter && 
    else
    {
      RetValue = false;
    }

  }// try
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), TlgName.c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), TlgName.c_str());    
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
     Function.c_str(), TlgName.c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(), TlgName.c_str()); 
  }

  return RetValue;
}// bool CEAF_TelegramHandler:DoProcessSYL295ScrapMaterialRequestt(const std::string& Key, const std::string& TlgName)

bool CEAF_TelegramHandler::DoProcessMotorMaintenance(const std::string& Key, const std::string& TlgName)
{
	const long 	IDFan1_ID = 11;
	const long 	IDFan2_ID = 12;
	const long 	IDFan3_ID = 13;

	const long 	BFAN_EAFLF_ID = 14;
	const long 	BFAN_DRI_ID = 15;
	const long 	BFAN_EAFMHS_ID = 16;

	const long 	IncBeltBelDaybin_ID = 17;

	const long 	HydPresPump1_ID = 18;
	const long 	HydPresPump2_ID = 19;
	const long 	HydCircuPump1_ID = 20;
	const long 	HydCircuPump2_ID = 21;
	const long 	FDC1_ID = 22;
	const long 	FDC2_ID = 23;
	const long 	FDC3_ID = 24;
	const long 	FDC4_ID = 25;
	const long 	FDC5_ID = 26;
	const long 	FDC6_ID = 27;
	const long 	FDC7_ID = 28;
	const long 	FDC8_ID = 29;
	const long 	FDC9_ID = 30;
	const long 	FDC10_ID = 31;
	const long 	FDC11_ID = 32;
	const long 	FDC12_ID = 33;
	const long 	EafDischBeltCon_ID = 34;
	const long 	ShuttleTrvDrive_ID = 35;
	const long 	FluxDRIBeltCon_ID = 36;
	const long 	BC2Conveyor_ID = 37;
	const long 	BC1Conveyor_ID = 38;
	const long 	BC3Conveyor_ID = 39;
	const long 	BRUBeltMotor_ID = 40;
	const long 	FurnBrker_ID = 41;


	long UnitNo = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(),Telegram_EAL290::UnitNo);
	std::string PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
  long PlantNo = m_pGC_Plant_Container->getPlantNo(PlantId);

	CORBA::Any    IDFan  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_EAL290::IDFan);

	long    BFAN_EAFLF  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BFAN_EAFLF);
	long    BFAN_DRI  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BFAN_DRI);
	long    BFAN_EAFMHS  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BFAN_EAFMHS);


	CORBA::Any    HydPresPump  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_EAL290::HydPresPump);
	CORBA::Any    HydCircuPump  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_EAL290::HydCircuPump);

	CORBA::Any    FDC  = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(), Telegram_EAL290::FDC);

	
	long    IncBeltBelDaybin  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::IncBeltBelDaybin);	
	long    EafDischBeltCon  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::EafDischBeltCon);
	long    ShuttleTrvDrive  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::ShuttleTrvDrive);
	long    FluxDRIBeltCon  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::FluxDRIBeltCon);
	long    BC2Conveyor  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BC2Conveyor);
	long    BC1Conveyor  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BC1Conveyor);
	long    BC3Conveyor  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BC3Conveyor);
	long    BRUBeltMotor  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::BRUBeltMotor);
	long    FurnBrker  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key.c_str(), Telegram_EAL290::FurnBrker);

	bool RetValue = true;

	//IDFan
	DEF::seqLong *longIDFanSeq;
	if( IDFan >>= longIDFanSeq)
	{
		long Length = longIDFanSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longIDFanSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(IDFan1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(IDFan2_ID,PlantNo, condition);
				if(idx == 2)
				RetValue = RetValue && updateMotorData(IDFan3_ID,PlantNo, condition);
			}
	}

	//BoosterFan
	RetValue = RetValue && updateMotorData(BFAN_EAFLF_ID,PlantNo, BFAN_EAFLF);		
	RetValue = RetValue && updateMotorData(BFAN_DRI_ID,PlantNo, BFAN_DRI);		
	RetValue = RetValue && updateMotorData(BFAN_EAFMHS_ID,PlantNo, BFAN_EAFMHS);		

	//HydPresPump
	DEF::seqLong *longHydPresPumpSeq;
	if( HydPresPump >>= longHydPresPumpSeq)
	{
		long Length = longHydPresPumpSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longHydPresPumpSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(HydPresPump1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(HydPresPump2_ID,PlantNo, condition);
			}
	}

	//HydCircuPump
	DEF::seqLong *longHydCircuPumpSeq;
	if( HydCircuPump >>= longHydCircuPumpSeq)
	{
		long Length = longHydCircuPumpSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longHydCircuPumpSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(HydCircuPump1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(HydCircuPump2_ID,PlantNo, condition);
			}
	}

	//FDC
	DEF::seqLong *longFDCSeq;
	if( FDC >>= longFDCSeq)
	{
		long Length = longFDCSeq->length();
			for (long idx=0; idx < Length; idx ++ ) 
			{
				std::stringstream tempStr;
				long condition;
				tempStr << (*longFDCSeq)[idx];
				tempStr >> condition;

				if(idx == 0)
				RetValue = RetValue && updateMotorData(FDC1_ID,PlantNo, condition);
				if(idx == 1)
				RetValue = RetValue && updateMotorData(FDC2_ID,PlantNo, condition);
				if(idx == 2)
				RetValue = RetValue && updateMotorData(FDC3_ID,PlantNo, condition);
				if(idx == 3)
				RetValue = RetValue && updateMotorData(FDC4_ID,PlantNo, condition);
				if(idx == 4)
				RetValue = RetValue && updateMotorData(FDC5_ID,PlantNo, condition);
				if(idx == 5)
				RetValue = RetValue && updateMotorData(FDC6_ID,PlantNo, condition);
				if(idx == 6)
				RetValue = RetValue && updateMotorData(FDC7_ID,PlantNo, condition);
				if(idx == 7)
				RetValue = RetValue && updateMotorData(FDC8_ID,PlantNo, condition);
				if(idx == 8)
				RetValue = RetValue && updateMotorData(FDC9_ID,PlantNo, condition);
				if(idx == 9)
				RetValue = RetValue && updateMotorData(FDC10_ID,PlantNo, condition);
				if(idx == 10)
				RetValue = RetValue && updateMotorData(FDC11_ID,PlantNo, condition);
				if(idx == 11)
				RetValue = RetValue && updateMotorData(FDC12_ID,PlantNo, condition);
			}
	}

	RetValue = RetValue && updateMotorData(IncBeltBelDaybin_ID,PlantNo, IncBeltBelDaybin);			
	RetValue = RetValue && updateMotorData(EafDischBeltCon_ID,PlantNo, EafDischBeltCon);	
	RetValue = RetValue && updateMotorData(ShuttleTrvDrive_ID,PlantNo, ShuttleTrvDrive);	
	RetValue = RetValue && updateMotorData(FluxDRIBeltCon_ID,PlantNo, FluxDRIBeltCon);		
	RetValue = RetValue && updateMotorData(BC2Conveyor_ID,PlantNo, BC2Conveyor);	
	RetValue = RetValue && updateMotorData(BC1Conveyor_ID,PlantNo, BC1Conveyor);	
	RetValue = RetValue && updateMotorData(BC3Conveyor_ID,PlantNo, BC3Conveyor);	
	RetValue = RetValue && updateMotorData(BRUBeltMotor_ID,PlantNo, BRUBeltMotor);		
	RetValue = RetValue && updateMotorData(FurnBrker_ID,PlantNo, FurnBrker);		

	if (RetValue)
		CDH_IN_Task::getInstance()->getStdConnection()->commit();
	else
		CDH_IN_Task::getInstance()->getStdConnection()->rollback();

	return true;
}


bool CEAF_TelegramHandler::updateMotorData(long MotorID,long PlantNo, long MotorStrart)
{
	  std::string Function = "CEAF_TelegramHandler::updateMotorData";
		std::string TlgName = "EAL290";
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

bool CEAF_TelegramHandler::DoProcessEAFL217DelayStatus(const std::string& Key, const std::string& TlgName)
{
	 //=========================    Delay Status   ===================================

  bool RetValue = true;

  //------------ This variables are used as buffer ------------------
  long UnitNo   = -1;              
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; 

  std::string LadleType;
  std::string LadleId;
  long LadleNo   = -1;
  CDateTime Now;
  //------------ This variables are used as buffer ------------------

  std::string Function = "CEAF_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started", 3);

      //********    Read telegram data  ************************************************************************

      UnitNo   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_EAL217::UnitNo);
      HeatId   = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL217::HeatId );
      TreatId  = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL217::TreatId);

	  string DelayCode = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_EAL217::DelayCode);
	  CORBA::Any AnyDelayStartTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(),Telegram_EAL217::DelayStartTime);
	  CORBA::Any AnyDelayEndTime = m_pTelegram_Adapter->m_pIntf_IN->getAny(Key.c_str(),Telegram_EAL217::DelayEndTime);

      PlantId = m_pGC_Plant_Container->getL2PlantID(UnitNo);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

      //********    reset statushandler  ***********************************************************************

      //********    preparation telegram data   ****************************************************************

      checkInternalData(TlgName, HeatId, TreatId, Plant, CustHeatId, CustTreatId);

      if ( RetValue )
      {
        //********    Convert and check telegram data  *********************************************************   

        // Level 1 may send LONG_MIN , we use DEF::Inv_Long internally !
        UnitNo  = CDataConversion::SetInvalidToDefault(UnitNo,DEF::Inv_Long,LONG_MIN);

        checkValidity(TlgName,"UnitNo",UnitNo,1,2);

        //********    main telegram data   ***********************************************************************

        DataKey   = generateDataKey(TlgName);

        CDateTime DelayStartTime(AnyDelayStartTime); 
		CDateTime DelayEndTime(AnyDelayEndTime); 

        //********    Define Event *******************************************************************************

        if ( DelayStartTime != CSMC_DBData::unspecDate || DelayEndTime != CSMC_DBData::unspecDate )
        {
          EventMessageVector.push_back(EAF_EvMsg::evEAFDelayStatus);

          //********    Write telegram data  ***********************************************************************

		  m_pTelegram_Adapter->m_pIntf_OUT->setString(DataKey.c_str(), DATA::DelayCode, DelayCode);
          m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DelayStartDate,DelayStartTime.assDate());
		  m_pTelegram_Adapter->m_pIntf_OUT->setDate(DataKey.c_str(),DATA::DelayEndDate,DelayEndTime.assDate());

          m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

          //********    send internal event  ***********************************************************************

          SendEventMessage(Key,TlgName,DataKey,PlantId,"",HeatId,TreatId,CSMC_DBData::unspecString,true);//SARS
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

          pEventLog->EL_InvalidTlgData(sMessage, TlgName.c_str(), "Delay Code", DelayCode.c_str());

          RetValue = false;
        }

        //********    End processing data  ***********************************************************************
      }// 
      else
      {
        RetValue = false;
      }

      log (TlgName + ": Finished", 3);
    }
    catch (cCBS_DBExc &e)
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), TlgName.c_str()); 
    }
    catch(CORBA::Exception& cExc) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
        Function.c_str(), TlgName.c_str());
    }
    catch(...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", Function.c_str(),TlgName.c_str());
      RetValue = false;
    }
  }// if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
} //bool CEAF_TelegramHandler::DoProcessEAFL217DelayStatus(const std::string& Key, const std::string& TlgName)


void CEAF_TelegramHandler::handleEventLog(const string& Message,const std::string& HeatID,const std::string& TreatID,const std::string& PlantID,const std::string& DataKey)
{
  CDateTime now;

  CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  
    if ( Message == EAF_EvMsg::evEAFHeatAnnouncement )
    {      
      pEventLog->EL_HeatAnnouncement(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHeatAnnouncementOffline )
    {
      pEventLog->EL_HeatAnnouncementOffline(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHeatCancellation )
    {      
      pEventLog->EL_HeatCancellation(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFHeatDeparture )
    {      
      pEventLog->EL_HeatDeparture(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFHeatStart )
    {      
      pEventLog->EL_HeatStart(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFDelayStatus )
    {
      CDateTime dStartTime,dEndTime;

      dStartTime.SetTime(m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(), DATA::DelayStartDate));
      dEndTime.SetTime  (m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(), DATA::DelayEndDate));

      pEventLog->EL_DelayStatus(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayPlant),      "-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayCode),       "-").c_str(),
        CDataConversion::SetInvalidToDefault(dStartTime,                                                 "-").c_str(),
        CDataConversion::SetInvalidToDefault(dEndTime,                                                   "-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::DelayDescription),"-").c_str() );
    }
    else if ( Message == EAF_EvMsg::evEAFHeatScheduleUpdate )
    {      
      pEventLog->EL_HeatScheduleUpdate(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeAimData )
    { 
      CDateTime TreatEndAimTime;
      TreatEndAimTime << m_pTelegram_Adapter->m_pIntf_OUT->getDate(DataKey.c_str(),DATA::TreatEndAim);

      pEventLog->EL_ChangeAimData(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::SteelGradeCode),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::TempAim),"-").c_str(),
        CDataConversion::SetInvalidToDefault(TreatEndAimTime,"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::AimWeight),"-").c_str());
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeHotHeelData )
    {      
      pEventLog->EL_ChangeHotHeelData(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFChangeTapLadleData )
    {
      std::string statusVal;      
      long nLadleNO;
      statusVal = CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleStatus),"-");
      nLadleNO = m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::LadleNo);

      pEventLog->EL_ChangeTapLadleData(sMessage,
        CDataConversion::LongToString(nLadleNO).c_str(),
        statusVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFSteelGradeChanged )
    {
      std::string SteelGrade  = m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey, DATA::SteelGradeCode);

      pEventLog->EL_SteelGradeChanged(sMessage,SteelGrade.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerElec )
    {
      pEventLog->EL_ChangeProdPracPointerElec(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerInjection )
    {
      pEventLog->EL_ChangeProdPracPointerInjection(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerOxygen )
    {
      pEventLog->EL_ChangeProdPracPointerOxygen(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracDataBurner )
    {
      pEventLog->EL_ChangeProdPracDataBurnerOxygen(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerParameter )
    {
      pEventLog->EL_ChangeProdPracPointerParameter(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFChangeProdPracPointerRestriction )
    {
      pEventLog->EL_ChangeProdPracPointerRestriction(sMessage,
        CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ProdPracPointer),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFCreateTreatmentID )
    {      
      pEventLog->EL_CreateTreatmentID(sMessage);
    } 
    else if(Message == EAF_EvMsg::evEAFHeatEnd)
    {
      pEventLog->EL_HeatEnd(sMessage,HeatID.c_str(),TreatID.c_str(),PlantID.c_str());
    }
    else if(Message == EAF_EvMsg::evEAFChangeThermalStatus)
    {
      std::string FurnaceStatus = CDataConversion::SetInvalidToDefault(m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::FurnaceStatus),"-");

      pEventLog->EL_ChangeEquipmentThermalStatus(sMessage,PlantID.c_str(),FurnaceStatus.c_str());
    }
    else if(Message == EAF_EvMsg::evEAFTappingStart)
    {
      pEventLog->EL_TappingStart(sMessage);
    }
    else if(Message == EAF_EvMsg::evEAFTappingEnd)
    {
      pEventLog->EL_TappingEnd(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFSteelSampleTaken )
    {
      pEventLog->EL_SteelSampleTaken(sMessage,"","","EAF" );
    }
    else if ( Message == EAF_EvMsg::evEAFSlagSampleTaken )
    {
      pEventLog->EL_SlagSampleTaken(sMessage,"","","EAF" );
    }
    else if ( Message == EAF_EvMsg::evEAFTempMeasurement )
    {
      pEventLog->EL_TempMeasurement(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getDouble(DataKey,DATA::MeasTemp)).c_str(),-1 );
    }		
    else if ( Message == EAF_EvMsg::evEAFCeloxMeasurement )
    {
      pEventLog->EL_CeloxMeasurement(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFTapLadleData || Message == EAF_EvMsg::evEAFHandleBasketDischarged || Message == EAF_EvMsg::evEAFChargedHotMetal)
    {
      // no log function is there
    }		
    else if ( Message == EAF_EvMsg::evEAFDeslaggingStart )
    {
      pEventLog->EL_DeslaggingStart(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFDeslaggingEnd)
    {
      pEventLog->EL_DeslaggingEnd(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFSetComputerMode)
    {		
			seqComputerModes ActSeq         =  CIntfData::ToCORBAType(m_pTelegram_Adapter->m_pIntf_OUT->getComputerModes(DataKey.c_str(),DATA::ComputerModes)); 
      sComputerMode ActStruct ; 
      long seqLength = CIntfData::getLength(ActSeq);

      for(int i=0;i<seqLength;i++)
      {
        CIntfData::getAt(ActStruct, ActSeq,i);

        if ( ActStruct.Status == DEF_GC_COMP_STATUS::AutoMode )
        {
          pEventLog->EL_SetComputerModeAutomatic(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode )
        {
          pEventLog->EL_SetComputerModeDynamic(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerPatternMode )
        {
          pEventLog->EL_SetComputerModePattern(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ManualMode )
        {
          pEventLog->EL_SetComputerModeManual(sMessage,ActStruct.Device);
        }
			}
		}
    else if ( Message == EAF_EvMsg::evEAFRoofArrivesInDownPosition)
    {
      pEventLog->EL_RoofArrivesInDownPosition(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFRoofArrivesInUpPosition)
    {
      pEventLog->EL_RoofArrivesInUpPosition(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFGantrySwungOut)
    {
      pEventLog->EL_GantrySwungOut(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFGantrySwungIn)
    {
      pEventLog->EL_GantrySwungIn(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFDoorClosed)
    {
      pEventLog->EL_DoorClosed(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFDoorOpened)
    {
      pEventLog->EL_DoorOpened(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFUpdatePlantStatus || Message == EAF_EvMsg::evEAFElectrodesOutOperatingPosition || Message == EAF_EvMsg::evEAFElectrodesInOperatingPosition)
    {
      // no log function is there
    }		
    else if ( Message == EAF_EvMsg::evEAFFurnaceBreakerOff)
    {
      pEventLog->EL_FurnaceBreakerOff(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFFurnaceBreakerOn)
    {
      pEventLog->EL_FurnaceBreakerOn(sMessage);
    }				
    else if ( Message == EAF_EvMsg::evEAFPowerOff)
    {
      pEventLog->EL_PowerOff(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFPowerOn)
    {
      pEventLog->EL_PowerOn(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFTapChangeStart)
    {
      pEventLog->EL_TapChangeStart(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::VoltTapNo)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::ElectrodRegCurve)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::FurnTapChangOn)).c_str());
    }		
    else if ( Message == EAF_EvMsg::evEAFTapChangeFinished)
    {
      pEventLog->EL_TapChangeFinished(sMessage,CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::VoltTapNo)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::ElectrodRegCurve)).c_str(),CDataConversion::DoubleToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::FurnTapChangOn)).c_str());
    }		
    else if ( Message == EAF_EvMsg::evEAFCyclicMeasurement )
    {
			//nothing is recorded for cyclic measurement
    }		
    else if ( Message == EAF_EvMsg::evEAFHandleUpdatePurpose)
    {
      pEventLog->EL_HandleUpdatePurpose(sMessage);
    }		
    else if ( Message == EAF_EvMsg::evEAFManipInjectLanceStop)
    {
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pTelegram_Adapter->m_pIntf_OUT->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        pEventLog->EL_ManipInjectLanceStop(sMessage, 
            sElement.Device,
            sElement.MatCode,
            sElement.Value);
      }
    }		
    else if ( Message == EAF_EvMsg::evEAFManipInjectLanceStart)
    {
      seqInjectLanceData InjectLanceData = CIntfData::ToCORBAType(m_pTelegram_Adapter->m_pIntf_OUT->getInjectLanceData(DataKey.c_str(),DATA::InjectLanceAmount));
      long seqLength = CIntfData::getLength(InjectLanceData);

      for(int i=0;i<seqLength;i++)
      {
        sInjectLanceData sElement;
        CIntfData::getAt(sElement, InjectLanceData,i);
        pEventLog->EL_ManipInjectLanceStart(sMessage, 
            sElement.Device,
            sElement.MatCode);
      }
    }		
    else if ( Message == EAF_EvMsg::evEAFBurnerGasAvail)
    {
     // no log function is there
    }		
    else if ( Message == EAF_EvMsg::evEAFManipGasLanceStart)
    {
      pEventLog->EL_ManipGasLanceStart(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::GasLanceNo).c_str());
    }		
    else if ( Message == EAF_EvMsg::evEAFManipGasLanceStop)
    {
      pEventLog->EL_ManipGasLanceStop(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::GasLanceNo).c_str());
    }		
    else if ( Message == EAF_EvMsg::evEAFBottomStirringStart)
    {
      // no log function is there
    }		
    else if ( Message == EAF_EvMsg::evEAFBottomStirringEnd)
    {
      // no log function is there
    }				
    else if ( Message == EAF_EvMsg::evEAFLadleStirringStart)
    {
      pEventLog->EL_LadleStirringStart(sMessage);
    }				
    else if ( Message == EAF_EvMsg::evEAFLadleStirringStop)
    {
      pEventLog->EL_LadleStirringStop(sMessage);
    }				
    else if ( Message == EAF_EvMsg::evEAFCyclicMeasurementTapLadle)
    {
      // no log function is there
    }		
    else if ( Message == EAF_EvMsg::evEAFParameterUpdate)
    {
      pEventLog->EL_ParameterUpdate(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ParamName).c_str(),m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::ParamValue).c_str());
    }				
    else if ( Message == EAF_EvMsg::evEAFMaterialHandlingReport)
    {
      pEventLog->EL_MaterialHandlingReport(sMessage,        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeName).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeStatus).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeNo).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::RecipeTarget).c_str());
    }				
    else if ( Message == EAF_EvMsg::evEAFMatFeedingStart)
    {
      pEventLog->EL_MatFeedingStart(sMessage);
    }				
    else if ( Message == EAF_EvMsg::evEAFMatFeedingStop)
    {
      pEventLog->EL_MatFeedingStop(sMessage);
    }				
    else if ( Message == EAF_EvMsg::evEAFLiqMatHandlReport)
    {
        pEventLog->EL_LiqMatHandlReport(sMessage, m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::MeasWeight).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::WeighingType).c_str(),
        CDataConversion::LongToString(m_pTelegram_Adapter->m_pIntf_OUT->getLong(DataKey,DATA::LadleNo)).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LadleDeslagged).c_str());
    }				
    else if ( Message == EAF_EvMsg::evEAFSetTappingMasses)
    {
      pEventLog->EL_SetTappingMasses(sMessage,m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::TappingMass).c_str());
    }				
    else if ( Message == EAF_EvMsg::evEAFPhaseReport)
    {
      // no log function is there
    }				
    else if ( Message == EAF_EvMsg::evEAFOrderScrap)
    {
      // no log function is there
    }				
    else if ( Message == EAF_EvMsg::evEAFHandleSetBasketData)
    {
      std::string statusVal, strVal;      
      statusVal = m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::LastBasket);

      if(statusVal=="1")
        strVal="Last Basket";
      else if(statusVal=="0")
        strVal="Not last basket";

      pEventLog->EL_HandleSetScrapContainerData(sMessage,
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::BasketId).c_str(),
        m_pTelegram_Adapter->m_pIntf_OUT->getString(DataKey,DATA::BasketInSeq).c_str(),
        strVal.c_str());   
		}				
    else if ( Message == EAF_EvMsg::evEAFScrapMaterialAvail)
    {
      // no log function is there
    }								
		else
		{
			//
		}
}


bool CEAF_TelegramHandler::DoAutoHeatScheduleCreation()
{
	 //SARS: only JSW specific
	  std::string Function = "CEAF_TelegramHandler::DoAutoHeatScheduleCreation";
		std::string TlgName = "AutoHeatSchedule";
		cCBS_ODBC_DBError lastError;
		string HeatID = CSMC_DBData::unspecString;
		string TreatID = "01";
		std::string SteelGrade = "C45"; //default
		std::string OrderID = CSMC_DBData::unspecString;
		std::string NewOrderID = CSMC_DBData::unspecString;

		CDateTime Now;
		bool RetValue = true;
		try
		{
			CDateTime Now;
			CDateTime StartTime;
			CDateTime EndTime;

			if(m_pPP_HEAT->selectOrderBy(CSMC_DBData::unspecString,false))
			{
				for(int i = 1; i <= m_pPP_HEAT->getLastRow(); i++)
				{
					OrderID = m_pPP_HEAT->getPRODORDERID(i);				
					if(m_pPP_ORDER->select(OrderID))
					{
						SteelGrade = m_pPP_ORDER->getSTEELGRADECODE(1);
					}
					long temp_convert = CDataConversion::StringToLong(OrderID);
					if(temp_convert != DEF::Inv_Long)
					{
						temp_convert = temp_convert + 1;
						NewOrderID = CDataConversion::LongToString(temp_convert);
						if(!m_pPP_ORDER->select(NewOrderID))
						{
							break;
						}
					}
				} //for..
			}


				if(NewOrderID != CSMC_DBData::unspecString)
				{
					RetValue = RetValue && m_pPP_ORDER->updateInsertPP(NewOrderID,SteelGrade,"HMI",false,lastError);

					m_pPP_HEAT->getNextHeatId( HeatID, lastError );
					RetValue = RetValue && m_pPP_HEAT->updateInsertPP(HeatID,NewOrderID,"E1L1", CSMC_DBData::unspecLong, CSMC_DBData::unspecLong ,"HMI",0,1,0,DEF_GC_LADLE_TYPE::TeemingLadle, 1,false,lastError);

					EndTime.addTime(45*60*1.0);
					RetValue = RetValue &&  m_pPP_HEAT_PLANT->updateInsertPP(HeatID,TreatID,DEF_GC_PLANT_DEF::EAF,1,NewOrderID,"01",StartTime.assDate(),EndTime.assDate(),false,lastError);

					
					StartTime.addTime(50*60*1.0);
					EndTime.addTime(35*60*1.0);
					RetValue = RetValue &&  m_pPP_HEAT_PLANT->updateInsertPP(HeatID,TreatID,DEF_GC_PLANT_DEF::LF,1,NewOrderID,"01",StartTime.assDate(),EndTime.assDate(),false,lastError);
					
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::EAF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::EAF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::EAF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMTEMP))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::EAF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::LIQADD))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::CCS,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::LF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMSTEEL))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}
					if(m_pPP_ORDER_SINGLE_AIMS->select(OrderID,DEF_GC_PLANT_DEF::LF,CSMC_DBData::unspecLong,DEF_GC_PP_ORDER_SINGLE_AIMS::AIMTEMP))
					{
						RetValue = RetValue && m_pPP_ORDER_SINGLE_AIMS->updateInsertPP(NewOrderID,m_pPP_ORDER_SINGLE_AIMS->getPLANT(1),m_pPP_ORDER_SINGLE_AIMS->getVARNAME(1),m_pPP_ORDER_SINGLE_AIMS->getVALUE(1),false,lastError);
					}

					long HEATSTATUSNO_PLANNED      = m_pHeatStatusContainer->getHeatStatus(DEF_GC_PLANT_DEF::L3, DEF_GC_HEAT_STATUS::Planned );
					if(!m_pPD_HEAT_REF->select(HeatID))
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


int CEAF_TelegramHandler::getNextChargeNo(const std::string& HeatID,const std::string& TreatID,const std::string& ChargeName)
{
	 //SARS: only JSW specific
	  std::string Function = "CEAF_TelegramHandler::getNextChargeNo";
		std::string TlgName = "NextChargeNo";
		cCBS_ODBC_DBError lastError;

		CDateTime Now;
		bool RetValue = true;
		long nextChargeNo = 1; //default
		string OrderId = CSMC_DBData::unspecString;
		try
		{
			if ( m_pPD_HEAT_DATA->select(HeatID,TreatID,DEF_GC_PLANT_DEF::EAF) )
      {
        OrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(1);
			}

			if( ChargeName == "HM" && m_pPD_HEAT_DATA_LIQADD->selectByOrderLiqAdd(HeatID,TreatID,DEF_GC_PLANT_DEF::EAF))
			{
				nextChargeNo = m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(1);
				nextChargeNo = nextChargeNo + 1;
			}
			else if( ChargeName == "BASKET" && m_pPD_SCRAP_CONTAINER_ORDER->selectByContainerState(DEF_GC_PLANT_DEF::EAF,OrderId,DEF_GC_SCRAP_CONT_ORDER_STATUS::Discharged,false))
			{
				nextChargeNo = m_pPD_SCRAP_CONTAINER_ORDER->getCONTAINERINSEQ(1);
				nextChargeNo = nextChargeNo + 1;
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

	return nextChargeNo;
}

int CEAF_TelegramHandler::getNextLadleNo()
{
	 //SARS: only JSW specific
	  std::string Function = "CEAF_TelegramHandler::getNextLadleNo";
		std::string TlgName = "getNextLadleNo";
		cCBS_ODBC_DBError lastError;

		CDateTime Now;
		bool RetValue = true;
		long hmCounter;
		long ladleNo = 99; //default
		try
		{

			long DefltSetUpDur = 30 * 60; // 30 minutes in seconds
			if(m_pGT_PARAM->select(DEF_GC_PLANTGROUP_DESC::All_EAF,"DefltHMLadleDeparture", 0, CSMC_DBData::unspecLong))
			{
				DefltSetUpDur = CDataConversion::StringToLong(m_pGT_PARAM->getVALUE(1)) * 60; //DB contains minutes, we need seconds
			}

			if ( m_pPDH_HM_DATA->selectFinishedHeat(false) )
      {
				CDateTime HMDepartureAct;
				CDateTime Now;

        hmCounter = m_pPDH_HM_DATA->getHOTMETAL_COUNTER(1);
				HMDepartureAct = m_pPDH_HM_DATA->getHM_DEPARTURE_ACT(1);
				CDeltaTime duration = CDateTime::subTimes(Now,HMDepartureAct);

				if( duration.asSeconds() > DefltSetUpDur)
				{
					return ladleNo;
				}

				if ( m_pPD_HOT_METAL->select(hmCounter) )
				{
					ladleNo = m_pPD_HOT_METAL->getLADLENO(1);
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

	return ladleNo;
}

bool CEAF_TelegramHandler::isRefiningPhaseStart(const std::string& HeatID,const std::string& TreatID)
{
	 //SARS: only JSW specific
	  std::string Function = "CEAF_TelegramHandler::isRefiningPhaseStart";
		std::string TlgName = "isRefiningPhaseStart";
		cCBS_ODBC_DBError lastError;

		CDateTime Now;
		bool RetValue = false;
		try
		{	
			if(HeatIdRefiningPhase != HeatID)
			{
				if(m_pPD_RECIPE->select(HeatID,TreatID,DEF_GC_PLANT_DEF::EAF,"DynamicFeeding",CSMC_DBData::unspecLong,CSMC_DBData::unspecString,9))
				{
					RetValue = true;
				}
				HeatIdRefiningPhase = HeatID;
			}
			else
			{
				RetValue = true;
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


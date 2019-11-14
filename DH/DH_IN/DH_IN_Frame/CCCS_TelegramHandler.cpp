// Copyright (C) 2006 SMS Demag AG

#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_LADLE_POS.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_LADLE_TYPE.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_SAMPLELOC.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GC_COOLWATER.h"
#include "DEF_GC_SOURCE.h"
#include "DEF_GT_PURP.h"

#include "CCCS_TelegramHandler.h"

//##ModelId=4582D1FF01C8
CCCS_TelegramHandler::CCCS_TelegramHandler()
{
  std::stringstream strFunction;
  std::stringstream strAction;

  strFunction << " In CCCS_TelegramHandler::CCCS_TelegramHandler()";

  try
  {  	  
    cCBS_StdConnection *pConnection = CDH_IN_Task::getInstance()->getStdConnection();

    strAction << "CDH_IN_Task::getInstance()->getConnection() ";

    if(pConnection)
    {
      strAction << "Success get database connection ";

      long PlantNo  = 1;
      std::string Plant = DEF_GC_PLANT_DEF::CCS;

      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "PlantNo", PlantNo);
      cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant"  , Plant);

      // GENERAL
      m_pGC_Plant_Container       = new CGC_Plant_Container       (pConnection, Plant);
      m_pHeatDataConverter        = new CHeatDataConverter        (pConnection);

      m_pGC_Recipe_L1Container    = new CGC_Recipe_L1Container(pConnection,Plant); 
      m_pGC_SourceContainer       = new CGC_SourceContainer(pConnection,Plant,PlantNo);
      m_pGC_Charge_Dest_Container = new CGC_Charge_Dest_Container(pConnection,Plant);
      m_pGC_Plantgroup_Container  = new CGC_Plantgroup_Container(pConnection);

      
      strAction << "init StatusHandler successful ";
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"", "CCCS_TelegramHandler","No database connection");

      // to guaranty EL_ExceptionCaught to be sent to CBS service
      Sleep(3000);

      // terminate programm in case of starting up without getting connection to database
      exit(EXIT_FAILURE);
    }

    log(strFunction.str() + " " + strAction.str(), 1);

  }
  catch(...) 
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Unknown Exception", "CEAFTelegramHandler","");
    throw;
  }
}

//##ModelId=4582D2030393
CCCS_TelegramHandler::~CCCS_TelegramHandler()
{
  if (m_pGC_Plant_Container)  {delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0;}
  if (m_pHeatDataConverter) {delete m_pHeatDataConverter; m_pHeatDataConverter = 0;}

  if (m_pGC_Charge_Dest_Container) {delete m_pGC_Charge_Dest_Container; m_pGC_Charge_Dest_Container = 0;}
  if (m_pGC_SourceContainer)       {delete m_pGC_SourceContainer; m_pGC_SourceContainer = 0;} 
  if (m_pGC_Recipe_L1Container)    {delete m_pGC_Recipe_L1Container; m_pGC_Recipe_L1Container = 0;}
}

//##ModelId=458692400375
bool CCCS_TelegramHandler::doOnComplete(const std::string& Key, const std::string& TlgName)
{
  //message list used to store the dispatch message
  bool RetValue = true;
  std::stringstream strFunction;
  std::stringstream strAction;
  try
  {
    //doOnCompleteDelete(Key,TlgName);

    strFunction << "CCCS_TelegramHandler::doOnComplete;";
    strFunction <<" TlgName: " << TlgName;

    EventMessageVector.clear();

    if(TlgName == "CCS_HEAT_STATUS")
      RetValue =  DoProcessCCSHeatStatus(Key,TlgName); 
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
    RetValue = false;

    m_pTelegram_Adapter->m_pIntf_IN->showContent(Key,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      strFunction.str().c_str(),strAction.str().c_str());   
  }

  if( RetValue == false )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingTelegram(sMessage,TlgName.c_str(),strFunction.str().c_str());
  }

  return RetValue;
}

void CCCS_TelegramHandler::SendEventMessage(const std::string& Key, 
                                           const std::string& TlgName,
                                           const std::string& DataKey,
                                           const std::string& PlantId,
                                           const std::string& HeatId,
                                           const std::string& TreatId,
                                           bool isPlantEvent)
{
  //Send all event messages, that are present in EventMessageVector
  std::stringstream strFunction;
  std::stringstream strAction;

  std::vector <std::string>::iterator EventMsgToSend;

  try
  {
    strFunction << "CCCS_TelegramHandler::SendEventMessage";
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
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::SystemException& sExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    m_pTelegram_Adapter->m_pIntf_IN->showContent(TlgName,1);
    m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,1);
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      strFunction.str().c_str(),strAction.str().c_str()); 
  }
}

bool CCCS_TelegramHandler::DoProcessCCSHeatStatus(const std::string& Key, const std::string& TlgName)
{
  bool RetValue = true;

  long UnitNo;
  std::string HeatId;
  std::string TreatId; 
  std::string CustHeatId;
  std::string CustTreatId;
  std::string DataKey;
  std::string PlantId;
  std::string Plant; // we are CCS
  std::string OrderId;
  long CCSId   = -1;
  CDateTime Now;

  std::string Function = "CCCS_TelegramHandler::DoProcess" + TlgName;

  if ( m_pTelegram_Adapter && 
    m_pTelegram_Adapter->m_pIntf_IN && 
    m_pTelegram_Adapter->m_pIntf_OUT )
  {
    try
    {
      log (TlgName + ": Started: Announcement of Heat", 3);

      //********    Read telegram data  ************************************************************************
      UnitNo             = m_pTelegram_Adapter->m_pIntf_IN->getLong   (Key,Telegram_CCS_HEAT_STATUS::UnitNo);
      CCSId              = m_pTelegram_Adapter->m_pIntf_IN->getLong   (Key,Telegram_CCS_HEAT_STATUS::CCSId );
      long CasterStatus  = m_pTelegram_Adapter->m_pIntf_IN->getLong   (Key,Telegram_CCS_HEAT_STATUS::CasterStatus );

      CustHeatId                          = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_CCS_HEAT_STATUS::HeatId );
      CustTreatId                         = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_CCS_HEAT_STATUS::TreatId );
      OrderId                             = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_CCS_HEAT_STATUS::OrderId );
      long LadleNo                        = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_CCS_HEAT_STATUS::LadleNo );

		  CDateTime dtTurretTime;
      sDate sdTurretTime        = m_pTelegram_Adapter->m_pIntf_IN->getDate  (Key.c_str(),Telegram_CCS_HEAT_STATUS::RequiredSetInTurretTime );
      dtTurretTime << sdTurretTime;
	  
      long RemainingLadleSteelWeight   = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_CCS_HEAT_STATUS::RemainingLadleSteelWeight );
      long RemainingTundishSteelWeight  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_CCS_HEAT_STATUS::RemainingTundishSteelWeight );

      std::string SteelGrade              = m_pTelegram_Adapter->m_pIntf_IN->getString(Key,Telegram_CCS_HEAT_STATUS::SteelGrade );
      long HeatInSeq                      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_CCS_HEAT_STATUS::HeatInSeq );
      long SuperHeat                      = m_pTelegram_Adapter->m_pIntf_IN->getLong  (Key,Telegram_CCS_HEAT_STATUS::Superheat );	 
			long TundishTemp                  = m_pTelegram_Adapter->m_pIntf_IN->getLong(Key,Telegram_CCS_HEAT_STATUS::TundishTemp );

      RetValue = RetValue && setErrorOnValidationOrEmpty(Key,10903,TlgName,Telegram_CCS_HEAT_STATUS::HeatId,              CustHeatId);
			RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_CCS_HEAT_STATUS::CCSId,           CCSId, 1,1);
			RetValue = RetValue && setErrorOnValidation(Key,10903,TlgName,Telegram_CCS_HEAT_STATUS::CasterStatus,           CasterStatus, 1,4);

      PlantId = m_pGC_Plant_Container->getL2PlantID(CCSId);
      Plant   = m_pGC_Plant_Container->getPlant(PlantId);

			if(m_pHeatDataConverter->getInternalHeatDataByCustHeatID(CustHeatId, HeatId, TreatId, DEF_GC_PLANT_DEF::LF) == false) //sometime heat directly goes from EAF to LF
			{
				m_pHeatDataConverter->getInternalHeatDataByCustHeatID(CustHeatId, HeatId, TreatId, DEF_GC_PLANT_DEF::EAF);
				m_pHeatDataConverter->getCustHeatData(HeatId, TreatId,CustHeatId,CustTreatId,DEF_GC_PLANT_DEF::EAF); //just fetching actual CustTreatId from table
			}
			else
			{
				m_pHeatDataConverter->getCustHeatData(HeatId, TreatId,CustHeatId,CustTreatId,DEF_GC_PLANT_DEF::LF); //just fetching actual CustTreatId from table
			}
		

			if (RetValue)
			{
				DataKey       = generateDataKey(TlgName);
				EventMessageVector.push_back(CCS_EvMsg::evCCSHeatStatus);

				m_pTelegram_Adapter->m_pIntf_OUT->setDate   (DataKey.c_str(),DATA::DateTime,Now.assDate());
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::PlantID,PlantId);
				m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::CasterNo,CCSId);

				m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::HeatStatus,CasterStatus);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::CustHeatID,CustHeatId);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::CustTreatID,CustTreatId);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::OrderId,OrderId);
				m_pTelegram_Adapter->m_pIntf_OUT->setLong   (DataKey,DATA::LadleNo,LadleNo);

				m_pTelegram_Adapter->m_pIntf_OUT->setDate  (DataKey.c_str(),DATA::ReqSetInTurretTime     ,dtTurretTime.assDate());
				m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,DATA::RemSteelWeightLadle    ,RemainingLadleSteelWeight);
				m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,DATA::RemSteelWeightTundish  ,RemainingTundishSteelWeight);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::SteelGradeCode,SteelGrade);

				m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,DATA::CasterHeatInSeq  ,HeatInSeq);
				m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,DATA::TundishSuperHeat  ,SuperHeat);	  	  
				m_pTelegram_Adapter->m_pIntf_OUT->setLong (DataKey,DATA::TundishTemp             ,TundishTemp);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::HeatID,HeatId);
				m_pTelegram_Adapter->m_pIntf_OUT->setString (DataKey,DATA::TreatID,TreatId);

				m_pTelegram_Adapter->m_pIntf_OUT->showContent(DataKey,4);

				SendEventMessage(Key,TlgName,DataKey,PlantId,HeatId,TreatId,false);

				log (TlgName + ": Finished", 3);
			}
			else
			{
				log (TlgName + ": error occours , see log files", 3);
			}

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
      pEventLog->EL_ExceptionCaught(sMessage, "unknown exception", "CCCS_TelegramHandler::doProcess()",TlgName.c_str());
      RetValue = false;
    }
  }// // if ( m_pTelegram_Adapter &&
  else
  {
    RetValue = false;
  }

  return RetValue;
}// bool CCCS_TelegramHandler::DoProcessCCSHeatStatus(const std::string& Key, const std::string& TlgName)




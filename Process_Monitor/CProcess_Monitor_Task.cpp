// Copyright (C) 2009 SMS Demag AG Germany

#include "iDH_Telcom_s.hh"
#include "Telcom_Out_s.hh"
#include "iProcess_Monitor_s.hh"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEvent_Task.h"
#include "CDateTime.h"

#include "CProcess_Monitor_EventHandler.h"
#include "CProcess_Monitor_TelcomIntf_Impl.h"
#include "CProcess_Monitor_Task.h"

CProcess_Monitor_Task* CProcess_Monitor_Task::m_pInstance = 0;

CProcess_Monitor_Task* CProcess_Monitor_Task::getInstance()
{
  if( m_pInstance == 0 )
    m_pInstance = new CProcess_Monitor_Task();

  return m_pInstance;
}

CProcess_Monitor_Task::CProcess_Monitor_Task()
: m_pDM_Interface(0)
, m_pDMProxyManager(0)
//, m_pDH_Interface(0)
{
	m_pDMProxyManager = new CProxyManager<DM::iDM_Interface>();

  // setDBConnections();
}

CProcess_Monitor_Task::~CProcess_Monitor_Task()
{
}

void CProcess_Monitor_Task::bindProxies()
{
  //Proxy names under "DataManager" in ini-file will be read 
  //and all object references to this proxies will be holed 
  //from nameservice.
  m_pDMProxyManager->registerProxies("DataManager");
}

DM::iDM_Interface_var& CProcess_Monitor_Task::getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
  if (!m_pDM_Interface)
  {
    m_pDMProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
    m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
  }

  return m_pDM_Interface;
}

void CProcess_Monitor_Task::log(const std::string& _message, long _level)
{
    cCBS_StdLog_Task::getInstance()->log(_message, _level);
}

void CProcess_Monitor_Task::setDBConnections()
{
  cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  if (pDB_Task)
  {
    try
    {
      std::string DBName;
      std::string DBUser;
      std::string DBPassword;
      
      bool result = false;
      if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName) &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser)  &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword) ))
      {
        std::cerr << "Can not read SMC database settings from ini-file" << std::endl;
        exit(EXIT_FAILURE);
      }
      m_pConnection = pDB_Task->getConnection(DBName,DBUser, DBPassword);
      if (m_pConnection)
      {
        m_pConnection->setAutoCommit(false);
      }
    }
    catch(...) 
    {
      std::cout << "exception caught at getConnection() in CProcess_Monitor_Task::setDBConnections()" << std::endl;
    }
  }
}


cCBS_Connection* CProcess_Monitor_Task::getConnection()
{
	return m_pConnection;
}


//CSMC_DataProvider_Impl CProcess_Monitor_Task::getpDH_Interface()
//{
//	return m_pDH_Interface;
//}
//void CProcess_Monitor_Task::setpDH_Interface(CSMC_DataProvider_Impl pDH_Interface)
//{
//	m_pDH_Interface = pDH_Interface;
//}

CProcess_Monitor_TelcomIntf_Impl* CProcess_Monitor_Task::getTelcom_Interface()
{
	return m_pTelcomIntf_Impl;
}

bool CProcess_Monitor_Task::initialize()
{
  // must be called first
  bool ret = cCBS_StdFrame_Task::initialize();

  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
  if (pCORBA_Task)
  {
    m_pTelcomIntf_Impl = new CProcess_Monitor_TelcomIntf_Impl();

    // register servant(s)
    std::string ServerName  = cCBS_StdInitBase::getInstance()->m_ServerName;

    std::string TelcomServantName    = ServerName + "Telcom";

    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "TelcomServantName", TelcomServantName);
    
    pCORBA_Task->registerServant(m_pTelcomIntf_Impl,TelcomServantName);

  }// end if (pCORBA_Task)

  bindProxies();

  std::vector<std::string> MonitorPlants;
  std::vector<std::string>::iterator it;

  cCBS_StdInitBase::getInstance()->getEntryList("Monitor", "PlantId", MonitorPlants);
  for (it = MonitorPlants.begin(); it != MonitorPlants.end(); it++)
  {
    std::string Dest; // destination (receiver) of event message
    std::string Sender; // sender of event
    std::string PlantUnit;
    std::string PlantNo;
    std::string TelegramName; // to L1
    long NotAvailValue = 0; // value for not available to L1
    long ErrorNumber = 1; // max error number before event sending
    std::string Tracking; // name of tracking process
    std::string EventTracking;

    //---
    m_pTelcomIntf_Impl->setPersistence(*it, true);

    //---
    pStdInitBase->getEntry(*it, "Destination", Dest);
    m_pTelcomIntf_Impl->setString(*it, PM::Destination, Dest);

    //---
    pStdInitBase->getEntry(*it, "Sender", Sender);
    m_pTelcomIntf_Impl->setString(*it, PM::Sender, Sender);

    //---
    pStdInitBase->getEntry(*it, "PlantUnit", PlantUnit);
    m_pTelcomIntf_Impl->setString(*it, PM::PlantUnit, PlantUnit);

    //---
    pStdInitBase->getEntry(*it, "PlantNo", PlantNo);
    m_pTelcomIntf_Impl->setString(*it, PM::PlantNo, PlantNo);

    //---
    pStdInitBase->getEntry(*it, "NotAvailValue", NotAvailValue);
    m_pTelcomIntf_Impl->setLong(*it, PM::NotValidValue, NotAvailValue);

    //---
    pStdInitBase->getEntry(*it, "TelegramName", TelegramName);
    m_pTelcomIntf_Impl->setString(*it, PM::TelegramName, TelegramName);

    //---
    pStdInitBase->replaceWithEntry(*it, "ErrorsMax", ErrorNumber);
    m_pTelcomIntf_Impl->setLong(*it, PM::ErrorsMax, ErrorNumber);

    //---
    m_pTelcomIntf_Impl->setLong(*it, PM::ErrorCount, 0);

    //---
    m_pTelcomIntf_Impl->setBoolean(*it, PM::Control, false);

    //---
    pStdInitBase->getEntry(*it, "Tracking", Tracking);
    m_pTelcomIntf_Impl->setString(*it, PM::Tracking, Tracking);

    //---
    pStdInitBase->getEntry(*it, "EventTracking", EventTracking);
    m_pTelcomIntf_Impl->setString(*it, PM::EventTracking, EventTracking);

    //---
    std::vector<std::string> Procs;
    pStdInitBase->getEntryList(*it, "Processes", Procs);
    std::vector<std::string>::iterator it_p;
    for (it_p = Procs.begin(); it_p != Procs.end(); it_p++)
    {
      m_pTelcomIntf_Impl->addDefaultProcess(*it, *it_p);
    }

    // insert plant id only
    m_pTelcomIntf_Impl->addProcess(*it, "");
  }

  m_pTelcomIntf_Impl->showContent("", 4);

  CProcess_Monitor_EventHandler *eh = new CProcess_Monitor_EventHandler(this);

  cCBS_StdEvent_Task::getInstance()->registerEventHandler(eh);

  setStateDetails("Process initialized.");
  return ret;
}

bool CProcess_Monitor_Task::sendEvent(std::string& PlantID, std::string& ProductID)
{
  std::string DataKey = m_pTelcomIntf_Impl->generateDataKey("");
  bool SendTlg = false;

  std::string CustHeatID  = m_pTelcomIntf_Impl->getString(PlantID, PM::CustHeatID);
  std::string CustTreatID = m_pTelcomIntf_Impl->getString(PlantID, PM::CustTreatID);
  std::string HeatID    = m_pTelcomIntf_Impl->getString(PlantID, PM::HeatID);
  std::string TreatID   = m_pTelcomIntf_Impl->getString(PlantID, PM::TreatID);
  std::string OrderID   = m_pTelcomIntf_Impl->getString(PlantID, PM::OrderId);
  std::string PlantUnit = m_pTelcomIntf_Impl->getString(PlantID, PM::PlantUnit);
  std::string PlantNo   = m_pTelcomIntf_Impl->getString(PlantID, PM::PlantNo);
  long NotAvailable     = m_pTelcomIntf_Impl->getLong  (PlantID, PM::NotValidValue);
  std::string Sender    = m_pTelcomIntf_Impl->getString(PlantID, PM::Sender);
  std::string Dest      = m_pTelcomIntf_Impl->getString(PlantID, PM::Destination);
  std::string TlgName   = m_pTelcomIntf_Impl->getString(PlantID, PM::TelegramName);
  std::string Tracking  = m_pTelcomIntf_Impl->getString(PlantID, PM::Tracking);
  std::string EventTracking = m_pTelcomIntf_Impl->getString(PlantID, PM::EventTracking);
  DEF::seqLong seqSpare;
  CIntfData::preset(seqSpare,0,5);
  CDateTime now;

    if (CustHeatID == DEF::Inv_String)
    CustHeatID.clear();

  if (CustTreatID == DEF::Inv_String)
    CustTreatID.clear();

  //if (PlantUnit == "BOF")
  //{
  //  if (getTraceLevel() >= PM::INFO_LEVEL)
  //    log("Set telegram data for L2BO07", PM::INFO_LEVEL);

  //  m_pTelcomIntf_Impl->setString(DataKey, Telegram_L2BO07::HeatNo, CustHeatID);
  //  m_pTelcomIntf_Impl->setString(DataKey, Telegram_L2BO07::TreatId, CustTreatID);
  //  m_pTelcomIntf_Impl->setAny(DataKey, Telegram_L2BO07::CreateTime, now.asCORBAAny());

  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2BO07::MatStat, NotAvailable);
  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2BO07::BlowStirrStat, NotAvailable);
  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2BO07::BlowDynStat, NotAvailable);

  //  m_pTelcomIntf_Impl->setLong (DataKey, Telegram_L2BO07::BlowEndStat,NotAvailable);
  //  m_pTelcomIntf_Impl->setLong (DataKey, Telegram_L2BO07::FreeSpare2,-1);
  //  m_pTelcomIntf_Impl->setLong (DataKey, Telegram_L2BO07::FreeSpare3,-1);
  //  m_pTelcomIntf_Impl->setLong (DataKey, Telegram_L2BO07::FreeSpare4,-1);
  //  m_pTelcomIntf_Impl->setLong (DataKey, Telegram_L2BO07::FreeSpare5,-1);

  //  SendTlg = true;
  //}
  
/*  if (PlantUnit == "AOD")
  {
    if (getTraceLevel() >= PM::INFO_LEVEL)
      log("Set telegram data for L2EA07", PM::INFO_LEVEL);

    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2AO07::MeltId, HeatID);
    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2AO07::TreatId, TreatID);
    m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2AO07::CreateTime, now.asCORBAAny());

    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2AO07::ModeMat, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2AO07::ModeBlow, NotAvailable);
    m_pTelcomIntf_Impl->setAny (DataKey,Telegram_L2AO07::Spare, CIntfData::ToAny(seqSpare));
    SendTlg = true;
  }
  else if (PlantUnit == "EAF")
  {
    if (getTraceLevel() >= PM::INFO_LEVEL)
      log("Set telegram data for L2EA07", PM::INFO_LEVEL);

    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2EA07::HeatId, HeatID);
    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2EA07::TreatId, TreatID);
    m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2EA07::CreateTime, now.asCORBAAny());

    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeElec, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeInj, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeMat, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeBurner,NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeStirring,NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModePatternFeed,NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2EA07::ModeTappingBatch,NotAvailable);
    m_pTelcomIntf_Impl->setAny (DataKey,Telegram_L2EA07::Spare, CIntfData::ToAny(seqSpare));

    SendTlg = true;
  }
  else */
	  
	  if (PlantUnit == "LF")
  {
    if (getTraceLevel() >= PM::INFO_LEVEL)
      log("Set telegram data for L2LF07", PM::INFO_LEVEL);

    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2LF07::HeatId, HeatID);
    m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2LF07::TreatId, TreatID);
    m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2LF07::CreateTime, now.asCORBAAny());

    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2LF07::ModeElec, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2LF07::ModeStirr, NotAvailable);
    m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2LF07::ModeMat, NotAvailable);
    m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2LF07::Spare, CIntfData::ToAny(seqSpare));

    SendTlg = true;
  }
  //else if (PlantUnit == "LTS")
  //{
  //  if (getTraceLevel() >= PM::INFO_LEVEL)
  //    log("Set telegram data for L2AR07", PM::INFO_LEVEL);

  //  m_pTelcomIntf_Impl->setString(DataKey, Telegram_L2AR07::HeatNo, CustHeatID);
  //  m_pTelcomIntf_Impl->setString(DataKey, Telegram_L2AR07::TreatId, CustTreatID);
  //  m_pTelcomIntf_Impl->setAny(DataKey, Telegram_L2AR07::CreateTime, now.asCORBAAny());

  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2AR07::MatMode, NotAvailable);
  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2AR07::StirMode, NotAvailable);

  //  m_pTelcomIntf_Impl->setLong(DataKey, Telegram_L2AR07::FreeSpare1,-1);
  //  m_pTelcomIntf_Impl->setLong(DataKey, Telegram_L2AR07::FreeSpare2,-1);
  //  m_pTelcomIntf_Impl->setLong(DataKey, Telegram_L2AR07::FreeSpare3,-1);
  //  m_pTelcomIntf_Impl->setLong(DataKey, Telegram_L2AR07::FreeSpare4,-1);
  //  m_pTelcomIntf_Impl->setLong(DataKey, Telegram_L2AR07::FreeSpare5,-1);

  //  SendTlg = true;
  //}
  //else if (PlantUnit == "RH")
  //{
  //  if (getTraceLevel() >= PM::INFO_LEVEL)
  //    log("Set telegram data for L2RH07", PM::INFO_LEVEL);

  //  m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2RH07::HeatId, HeatID);
  //  m_pTelcomIntf_Impl->setString(DataKey,Telegram_L2RH07::TreatId, TreatID);
  //  m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2RH07::CreateTime, now.asCORBAAny());

  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2RH07::ModeVacuum, NotAvailable);
  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2RH07::ModeLance, NotAvailable);
  //  m_pTelcomIntf_Impl->setLong(DataKey,Telegram_L2RH07::ModeMat, NotAvailable);
  //  m_pTelcomIntf_Impl->setAny(DataKey,Telegram_L2RH07::Spare, CIntfData::ToAny(seqSpare));

  //  SendTlg = true;
  //}

  if (SendTlg)
  {
    CEventMessage MstToL1Sender;
    MstToL1Sender.setMessage(std::string("TELEGRAM_") + TlgName);
    MstToL1Sender.setPlantID(PlantNo);
    MstToL1Sender.setDataKey(DataKey);
    MstToL1Sender.setOrderID(OrderID);
    MstToL1Sender.setHeatID(HeatID);
    MstToL1Sender.setTreatID(TreatID);
    // bye, bye event
    if ( MstToL1Sender.dispatch(Sender,Dest) )
    {
      m_pTelcomIntf_Impl->setBoolean(PlantID, PM::EventIsSent, true);
    }

    // send event to tracking process
    if (!Tracking.empty() && 
         Tracking != DEF::Inv_String &&
        !EventTracking.empty() &&
        EventTracking != DEF::Inv_String)
    {
      log("Send event " + EventTracking + " to tracking " + Tracking +" to reset computer modes",3);

      CEventMessage ToTracking;
      ToTracking.setHeatID(HeatID);
      ToTracking.setTreatID(TreatID);
      ToTracking.setPlantID(PlantID);
      ToTracking.setOrderID(OrderID);
      ToTracking.setProductID(ProductID);
      ToTracking.setMessage(EventTracking);
      ToTracking.setDataKey(m_pTelcomIntf_Impl->generateDataKey(""));
      ToTracking.dispatch(Sender,Tracking);
    }
    else
    {
      log("No event is sent to tracking for plant " + PlantID + " because:");
      if (  Tracking.empty() || Tracking != DEF::Inv_String )
      {
        log("Tracking name is not set in ini file " + Tracking, PM::ERROR_LEVEL);
      }
      if ( EventTracking.empty() || EventTracking == DEF::Inv_String )
      {
        log("Event message is not set in ini file " + EventTracking, PM::ERROR_LEVEL);
      }
    }

    // ErrorCount is increased in check task
    // stop control if max number is reached
    long ActErrorNo = m_pTelcomIntf_Impl->getLong(PlantID, PM::ErrorCount);
    if ( ActErrorNo >= m_pTelcomIntf_Impl->getLong(PlantID, PM::ErrorsMax))
    {
      m_pTelcomIntf_Impl->setBoolean(PlantID, PM::Control, false);
      if (getTraceLevel() >= PM::WARNING_LEVEL)
        log("Max allowed number of errors is reached. Stop monitoring for " + PlantID+"->"+ProductID, PM::WARNING_LEVEL);
    }
  }

  return SendTlg;
}

void CProcess_Monitor_Task::ownStartUp()
{
  setWorking(true);
  setStateDetails("No monitoring for any plant currently active. Waiting for next heat announcement.");
}

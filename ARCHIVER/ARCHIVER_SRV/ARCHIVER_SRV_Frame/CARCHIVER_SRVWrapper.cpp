#include "CEventMessage.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "CDataConversion.h"

#include "CARCHIVER_SRVTask.h"

#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_ORDER.h"

#include "CPD_PRETREATDATA.h"

#include "CPD_HEAT_DATA.h"
#include "CPDL_HEAT_DATA.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_PLANTSTATUS.h"
#include "CPD_SAMPLE.h"
#include "CPD_HOT_METAL.h"


#include "CHD_HEAT_DATA.h"
#include "CHD_SAMPLE_REF.h"
#include "CHD_SAMPLE.h"
#include "CHD_LADLE_LIFE_DATA.h"


#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_HEAT_REF.h"

#include "CARCHIVER_SRVWrapper.h"


CARCHIVER_SRVWrapper::CARCHIVER_SRVWrapper()
: m_pPP_HEAT(0)
, m_pPP_HEAT_PLANT(0)
, m_pPP_ORDER(0)
, m_pPD_PRETREATDATA(0)
, m_pPD_HEAT_DATA(0)
, m_pPDL_HEAT_DATA(0)
, m_pPD_SAMPLE_REF(0)
, m_pPD_PLANTSTATUS(0)
, m_pPD_SAMPLE(0)
, m_pHD_HEAT_DATA(0)
, m_pHD_SAMPLE_REF(0)
, m_pHD_SAMPLE(0)
, m_pHD_LADLE_LIFE_DATA(0)
, m_pPD_HEAT_PLANT_REF(0)
, m_pPD_HEAT_REF(0)
, m_pPD_HOT_METAL(0)
{
}

CARCHIVER_SRVWrapper::~CARCHIVER_SRVWrapper()
{
  deleteDBClasses();
}

void CARCHIVER_SRVWrapper::deleteDBClasses()
{ 
  if (m_pPP_HEAT)              {delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT)        {delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER)             {delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPD_PRETREATDATA)      {delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0;}
  if (m_pPD_HEAT_DATA)         {delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
  if (m_pPDL_HEAT_DATA)        {delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  if (m_pPD_SAMPLE_REF)        {delete m_pPD_SAMPLE_REF; m_pPD_SAMPLE_REF = 0;}
  if (m_pPD_PLANTSTATUS)       {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
  if (m_pPD_SAMPLE)            {delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0;}
  if (m_pHD_HEAT_DATA)         {delete m_pHD_HEAT_DATA; m_pHD_HEAT_DATA = 0;}
  if (m_pHD_SAMPLE_REF)        {delete m_pHD_SAMPLE_REF; m_pHD_SAMPLE_REF = 0;}
  if (m_pHD_SAMPLE)            {delete m_pHD_SAMPLE; m_pHD_SAMPLE = 0;}
  if (m_pHD_LADLE_LIFE_DATA)   {delete m_pHD_LADLE_LIFE_DATA; m_pHD_LADLE_LIFE_DATA = 0;}
  if (m_pPD_HEAT_PLANT_REF)    {delete m_pPD_HEAT_PLANT_REF; m_pPD_HEAT_PLANT_REF = 0;}
  if (m_pPD_HEAT_REF)          {delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0;}
  if (m_pPD_HOT_METAL)         {delete m_pPD_HOT_METAL; m_pPD_HOT_METAL = 0;}

	

}

void CARCHIVER_SRVWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPP_HEAT              = new CPP_HEAT(pConnection);
  m_pPP_HEAT_PLANT        = new CPP_HEAT_PLANT(pConnection);
  m_pPP_ORDER             = new CPP_ORDER(pConnection);
  m_pPD_PRETREATDATA      = new CPD_PRETREATDATA(pConnection);
  m_pPD_HEAT_DATA         = new CPD_HEAT_DATA(pConnection);
  m_pPDL_HEAT_DATA        = new CPDL_HEAT_DATA(pConnection);
  m_pPD_SAMPLE_REF        = new CPD_SAMPLE_REF(pConnection);
  m_pPD_PLANTSTATUS       = new CPD_PLANTSTATUS(pConnection);
  m_pPD_SAMPLE            = new CPD_SAMPLE(pConnection);
  m_pHD_HEAT_DATA         = new CHD_HEAT_DATA(pConnection);
  m_pHD_SAMPLE_REF        = new CHD_SAMPLE_REF(pConnection);
  m_pHD_SAMPLE            = new CHD_SAMPLE(pConnection);
  m_pHD_LADLE_LIFE_DATA   = new CHD_LADLE_LIFE_DATA(pConnection);
  m_pPD_HEAT_PLANT_REF    = new CPD_HEAT_PLANT_REF(pConnection);
  m_pPD_HEAT_REF          = new CPD_HEAT_REF(pConnection);
  m_pPD_HOT_METAL         = new CPD_HOT_METAL(pConnection);

}

bool CARCHIVER_SRVWrapper::doOnServiceEvent(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_SRVWrapper::doOnServiceEvent");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  { 
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    // find data that are older than the respective remaning days given by inifile
    // check REVTIME
    CDateTime DeletionDate;

    // **********************
    // handle PP tables
    // **********************

    DeletionDate = getDeletionDate("PP_HEAT");
    if ( m_pPP_HEAT->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPP_HEAT->getLastRow() << " datasets" ;

      m_pPP_HEAT->deleteRows();
      m_pPP_HEAT->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PP_HEAT",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("PP_ORDER");
    if ( m_pPP_ORDER->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPP_ORDER->getLastRow() << " datasets" ;

      m_pPP_ORDER->deleteRows();
      m_pPP_ORDER->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PP_ORDER",Message.str().c_str() ); 
    }


    // **********************
    // handle PD tables
    // **********************

    DeletionDate = getDeletionDate("PD_HEAT_DATA");
    if ( m_pPD_HEAT_DATA->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_HEAT_DATA->getLastRow() << " datasets" ;

      m_pPD_HEAT_DATA->deleteRows();
      m_pPD_HEAT_DATA->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_HEAT_DATA",Message.str().c_str() ); 
    }

		//sankar
    DeletionDate = getDeletionDate("PD_HOT_METAL");
    if ( m_pPD_HOT_METAL->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_HOT_METAL->getLastRow() << " datasets" ;

      m_pPD_HOT_METAL->deleteRows();
      m_pPD_HOT_METAL->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_HOT_METAL",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("PD_PRETREATDATA");
    if ( m_pPD_PRETREATDATA->selectByRevTime(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_PRETREATDATA->getLastRow() << " datasets" ;

      m_pPD_PRETREATDATA->deleteRows();
      m_pPD_PRETREATDATA->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_PRETREATDATA",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("PD_SAMPLE_REF");
    if ( m_pPD_SAMPLE_REF->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_SAMPLE_REF->getLastRow() << " datasets" ;

      m_pPD_SAMPLE_REF->deleteRows();
      m_pPD_SAMPLE_REF->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_SAMPLE_REF",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("PD_SAMPLE");
    if ( m_pPD_SAMPLE->deleteByRecTime(DeletionDate) )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_SAMPLE->getLastRow() << " datasets" ;

      m_pPD_SAMPLE->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_SAMPLE",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("PD_HEAT_REF");
    if ( m_pPD_HEAT_REF->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pPD_HEAT_REF->getLastRow() << " datasets" ;

      m_pPD_HEAT_REF->deleteRows();
      m_pPD_HEAT_REF->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"PD_HEAT_REF",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("HD_SAMPLE_REF");
    if ( m_pHD_SAMPLE_REF->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pHD_SAMPLE_REF->getLastRow() << " datasets" ;

      m_pHD_SAMPLE_REF->deleteRows();
      m_pHD_SAMPLE_REF->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"HD_SAMPLE_REF",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("HD_SAMPLE");
    if ( m_pHD_SAMPLE->deleteByRecTime(DeletionDate) )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pHD_SAMPLE->getLastRow() << " datasets" ;

      m_pHD_SAMPLE->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"HD_SAMPLE",Message.str().c_str() ); 
    }

    DeletionDate = getDeletionDate("HD_HEAT_DATA");
    if ( m_pHD_HEAT_DATA->selectByREVTIME(DeletionDate,"<=") )
    {
      std::stringstream Message;
      Message << "deleting "  << m_pHD_HEAT_DATA->getLastRow() << " datasets" ;

      m_pHD_HEAT_DATA->deleteRows();
      m_pHD_HEAT_DATA->commit();

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBDeleteInfo(sMessage,"HD_HEAT_DATA",Message.str().c_str() ); 
    }


    RetValue = true;


  } 
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

CDateTime CARCHIVER_SRVWrapper::getDeletionDate(const std::string& TableName)
{
  CDateTime DeletionDate;

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
  try
  {
    long RemDays = 365; // default

    // **************************
    // look for specific defaults
    // **************************
    if ( TableName.find("PP_") != std::string::npos )
    {
      pStdInitBase->replaceWithEntry("SERVICE", "PP_Tables", RemDays);
    }
    if ( TableName.find("PD_") != std::string::npos )
    {
      pStdInitBase->replaceWithEntry("SERVICE", "PD_Tables", RemDays);
    }
    if ( TableName.find("HD_") != std::string::npos )
    {
      pStdInitBase->replaceWithEntry("SERVICE", "HD_Tables", RemDays);
    }

    // **************************
    // look for specifics
    // **************************
    pStdInitBase->replaceWithEntry("SERVICE", TableName, RemDays);

    // ***********************************************
    // Calculate date in the past from "now" regarding
    // ***********************************************
    DeletionDate.addTime(-1*RemDays*24*60*60);

  }
  catch(...) 
  {    
    log("exception caught in CARCHIVER_SRVTask::getDeletionDate()", 1);    
  }
  return DeletionDate;
}
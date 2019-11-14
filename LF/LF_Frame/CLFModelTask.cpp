// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfLF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfLF.h"
#include "CCfgLF.h"

#include "CIntfParamMgr.h"
#include "CIntfPurposeMgr.h"
#include "CIntfMatMgr.h"

#include "CProcCtrl.h"
#include "CEventLogRedirectorCORBA.h"

#include "CIniFile.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogLFController.h"
#include "CSMC_EventLogFrameController.h"

#include "CLFAnalysisHandlingWrapper.h"
#include "CLFAnalysisEventHandler.h"
#include "CLFMaterialHandlingEventHandler.h"
#include "CLFModelStatusEventHandler.h"
#include "CLFModesAndAvailibilitiesEventHandler.h"
#include "CLFPurposeEventHandler.h"
#include "CLFSignalsAndMeasurementEventHandler.h"
#include "CLFTreatmentManagerEventHandler.h"
#include "CLFModelResultWrapper.h"
#include "CLFModelTestResultWrapper.h"

#include "CLFModelTask.h"

#if defined(PRO_C_ACCESS)
  #pragma message("ORACLE Pro*C/C++ database adapter for manager activated!")
  #include "CIntfDBAdaptMatMgr.h"
  #include "CIntfDBAdaptPurposeMgr.h"
  #include "CIntfDBAdaptParamMgr.h"
#elif defined(ODBC_ACCESS)
  #pragma message("ODBC database adapter for manager activated!")
  #include "CIntfODBCAdaptMatMgr.h"
  #include "CIntfODBCAdaptPurposeMgr.h"
  #include "CIntfODBCAdaptParamMgr.h"
#else
  #error("Database access for manager not specified!")
#endif


//##ModelId=41513C6C027C
CLFModelTask::~CLFModelTask()
{
  if (m_pCfgLF) delete m_pCfgLF;
  if (m_pIntfParamMgr) delete m_pIntfParamMgr;
  if (m_pIntfPurposeMgr) delete m_pIntfPurposeMgr;
  if (m_pIntfMatMgr) delete m_pIntfMatMgr;
  if (m_pIntfLF) delete m_pIntfLF;
  if (m_pIntfAdaptMatMgr) delete m_pIntfAdaptMatMgr;
  if (m_pIntfAdaptParamMgr) delete m_pIntfAdaptParamMgr;
  if (m_pIntfAdaptPurposeMgr) delete m_pIntfAdaptPurposeMgr;
}

//##ModelId=41513C6C02B8
CLFModelTask::CLFModelTask() 
: m_pIntfAdaptMatMgr(0)
, m_pIntfAdaptParamMgr(0)
, m_pIntfAdaptPurposeMgr(0)
, m_pIntfMatMgr(0)
, m_pIntfParamMgr(0)
, m_pIntfPurposeMgr(0)
, m_pIntfLF(0)
{
}


//##ModelId=4174D48B0224
CLFModelTask* CLFModelTask::getInstance()
{
  if ( 0 == Instance )
  {
    Instance = new CLFModelTask();
  }
	return Instance;
}

//##ModelId=41513C6D01B5
bool CLFModelTask::initialize()
{
  bool RetCode = true;

  CModelTask::initialize();

  setPlantEquipment(DEF_PLANT::TransferCar1,"1");
  setPlantEquipment(DEF_PLANT::TransferCar2,"2");

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  // Database entries are validated in setDBConnections, no error handling required here
  std::string DBName, DBUser, DBPassword;
  pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName);
  pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser);
  pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword);
  std::stringstream tmp;
  tmp << DBUser << '/' << DBPassword << '@' << DBName;
  std::string ConnectString = tmp.str();

  // setting IniFileName to -config ... argument from command line
  std::string IniFileName = pStdInitBase->getConfigName();

  // searching valid value in inifile
  pStdInitBase->replaceWithEntry("PATH","ModelIniFileName",IniFileName);

  pStdInitBase->replaceWithEntry(getTaskName(),"ModelIniFileName",IniFileName);

  // combination with environment variable
  IniFileName = pStdInitBase->getXPACT_SMC() + IniFileName;
 
  // getting pointer to frame task
  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

  // redirect Model event logs to SMC frame
  CEventLogRedirectorCORBA* pEventLogRedirectorCORBA = new CEventLogRedirectorCORBA(this);
  CProcCtrl::Instance()->setpEventLogRedirector(pEventLogRedirectorCORBA);

  // read InifileName from programm command line arguments 
  m_pCfgLF = new CCfgLF(IniFileName);  
  // parameter manager
  m_pIntfParamMgr = new CIntfParamMgr(*m_pCfgLF);
  // purpose manager
  m_pIntfPurposeMgr = new CIntfPurposeMgr(*m_pCfgLF);
  // material manager
  m_pIntfMatMgr = new CIntfMatMgr(*m_pCfgLF);

#if defined(PRO_C_ACCESS)
  m_pIntfAdaptMatMgr     = new CIntfDBAdaptMatMgr(*m_pCfgLF, *m_pIntfMatMgr);
  m_pIntfAdaptPurposeMgr = new CIntfDBAdaptPurposeMgr(*m_pCfgLF, *m_pIntfPurposeMgr);
  m_pIntfAdaptParamMgr   = new CIntfDBAdaptParamMgr(*m_pCfgLF, *m_pIntfParamMgr);
#elif defined(ODBC_ACCESS)
  m_pIntfAdaptMatMgr     = new CIntfODBCAdaptMatMgr(*m_pCfgLF, *m_pIntfMatMgr);
  m_pIntfAdaptPurposeMgr = new CIntfODBCAdaptPurposeMgr(*m_pCfgLF, *m_pIntfPurposeMgr);
  m_pIntfAdaptParamMgr   = new CIntfODBCAdaptParamMgr(*m_pCfgLF, *m_pIntfParamMgr);
#endif

  std::ostringstream Message;
  long Count = 0;
  
  //**********************************************************
  Count = m_pIntfAdaptMatMgr->readFrom(ConnectString.c_str());
  if ( Count <= 0 )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GT_MAT","NO DATA AVAILABLE");
  }
  else
  {
    Message << "Found " << Count << " materials in data base";
    log(Message.str(), 1);
    Message.str("");
  }

  //**********************************************************
  Count = m_pIntfAdaptPurposeMgr->readFrom(ConnectString.c_str());
  if ( Count <= 0 )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GT_MAT_PURP","NO DATA AVAILABLE");
  }
  else
  {
    Message << "Found " << Count << " purposes in data base";
    log(Message.str(), 1);
    Message.str("");
  }

  //**********************************************************
  Count = m_pIntfAdaptParamMgr->readFrom(ConnectString.c_str());
  if ( Count <= 0 )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GT_PARAM","NO DATA AVAILABLE");
  }
  else
  {
    Message << "Found " << Count << " parameters in data base";
    log(Message.str(), 1);
  }

  // input/output interface for LF model
  m_pIntfLF = new CIntfLF(*m_pCfgLF,*m_pIntfMatMgr,*m_pIntfParamMgr,*m_pIntfPurposeMgr);

  // instantiation and registration of all EventHandler classes
  // register in order of increasing frequency of handled events.
  // this may reduce average effort in resolving the proper handler for 
  // an event.
  //
  CLFEventHandler *pEventHandler = 0;
  
  pEventHandler = new CLFPurposeEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFAnalysisEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFMaterialHandlingEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFModelStatusEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFModesAndAvailibilitiesEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFTreatmentManagerEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CLFSignalsAndMeasurementEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  // create new model result wrapper (to call special doModelResult method in LF heating mode)
  m_pLFModelResultWrapper = new CLFModelResultWrapper();
  m_pLFModelResultWrapper->setpModelTask(this);

  // create new model result wrapper (to call special doModelResult method in LF test mode)
  m_pLFModelTestResultWrapper = new CLFModelTestResultWrapper();
  m_pLFModelTestResultWrapper->setpModelTask(this);

  return RetCode;

}

//##ModelId=4174D10D02DD
CLFModelTask* CLFModelTask::Instance = 0;


//##ModelId=462767AD03E5
CIntf* CLFModelTask::getpModelInterface(const std::string& Type)
{
  return m_pIntfLF;
}

//##ModelId=462767AD03B3
bool CLFModelTask::callModelResultWrapper(const std::string& Type ,CEventMessage& Event)
{
  bool RetValue = false;

  bool TestMode = false;

  std::string ModelEntry  = "Model";
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(),"Model", ModelEntry);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(ModelEntry,"TestMode",TestMode);

  if ( TestMode )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ModelNotAvailable(sMessage,m_ProcessID.c_str(),"running in TEST MODE !");

    if ( m_pLFModelTestResultWrapper )
    {
      RetValue = m_pLFModelTestResultWrapper->doModelResult(Event);
    }
  }
  else
  {
    if ( m_pLFModelResultWrapper )
    {
      RetValue = m_pLFModelResultWrapper->doModelResult(Event);
    }
  }

  return RetValue;
}

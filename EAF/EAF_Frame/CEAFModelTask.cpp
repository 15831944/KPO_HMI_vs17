// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CCfgEAF.h"

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
#include "CSMC_EventLogFrameController.h"

#include "CEAFModelWrapper.h"

#include "CEAFAnalysisEventHandler.h"
#include "CEAFTreatmentManagerEventHandler.h"
#include "CEAFPurposeEventHandler.h"
#include "CEAFSignalAndMeasurementEventHandler.h"
#include "CEAFMaterialHandlingEventHandler.h"
#include "CEAFModelResultWrapper.h"

#include "CEAFModelTask.h"

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

//##ModelId=4178AB4E03DE
CEAFModelTask* CEAFModelTask::Instance = 0;

//##ModelId=4146BA480183
CEAFModelTask::CEAFModelTask() 
: m_pIntfEAF(0)
, m_pCfgEAF(0)
, m_pIntfParamMgr(0)
, m_pIntfPurposeMgr(0)
, m_pIntfMatMgr(0)
, m_pIntfAdaptMatMgr(0)
, m_pIntfAdaptParamMgr(0)
, m_pIntfAdaptPurposeMgr(0)
, m_pEAFModelResultWrapper(0)
{
}

//##ModelId=4146BA480179
CEAFModelTask::~CEAFModelTask()
{
  if (m_pCfgEAF) delete m_pCfgEAF;
  if (m_pIntfParamMgr) delete m_pIntfParamMgr;
  if (m_pIntfPurposeMgr) delete m_pIntfPurposeMgr;
  if (m_pIntfMatMgr) delete m_pIntfMatMgr;

  if (m_pIntfEAF) delete m_pIntfEAF;
  if (m_pIntfAdaptMatMgr) delete m_pIntfAdaptMatMgr;
  if (m_pIntfAdaptParamMgr) delete m_pIntfAdaptParamMgr;
  if (m_pIntfAdaptPurposeMgr) delete m_pIntfAdaptPurposeMgr;

  if (m_pEAFModelResultWrapper) delete m_pEAFModelResultWrapper;
}


//##ModelId=4146BA4802B0
bool CEAFModelTask::initialize()
{
	bool RetCode = true;
  
  CModelTask::initialize();

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
  std::string IniFileName = cCBS_StdInitBase::getInstance()->getConfigName();

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
	m_pCfgEAF = new CCfgEAF(IniFileName);  
  // parameter manager
  m_pIntfParamMgr = new CIntfParamMgr(*m_pCfgEAF);
  // purpose manager
  m_pIntfPurposeMgr = new CIntfPurposeMgr(*m_pCfgEAF);
  // material manager
  m_pIntfMatMgr = new CIntfMatMgr(*m_pCfgEAF);

  #if defined(PRO_C_ACCESS)
    m_pIntfAdaptMatMgr     = new CIntfDBAdaptMatMgr(*m_pCfgEAF, *m_pIntfMatMgr);
    m_pIntfAdaptPurposeMgr = new CIntfDBAdaptPurposeMgr(*m_pCfgEAF, *m_pIntfPurposeMgr);
    m_pIntfAdaptParamMgr   = new CIntfDBAdaptParamMgr(*m_pCfgEAF, *m_pIntfParamMgr);
  #elif defined(ODBC_ACCESS)
    m_pIntfAdaptMatMgr     = new CIntfODBCAdaptMatMgr(*m_pCfgEAF, *m_pIntfMatMgr);
    m_pIntfAdaptPurposeMgr = new CIntfODBCAdaptPurposeMgr(*m_pCfgEAF, *m_pIntfPurposeMgr);
    m_pIntfAdaptParamMgr   = new CIntfODBCAdaptParamMgr(*m_pCfgEAF, *m_pIntfParamMgr);
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

  // input/output interface for EAF model
  m_pIntfEAF = CIntfEAF::createModelInterfaceEAF(*m_pCfgEAF,*m_pIntfMatMgr,*m_pIntfParamMgr,*m_pIntfPurposeMgr);

  // instantiation and registration of all EventHandler classes
  // register in order of increasing frequency of handled events.
  // this may reduce average effort in resolving the proper handler for 
  // an event.
  //
  CEAFEventHandler *pEventHandler = 0;

  pEventHandler = new CEAFPurposeEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CEAFAnalysisEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CEAFMaterialHandlingEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CEAFTreatmentManagerEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  pEventHandler = new CEAFSignalAndMeasurementEventHandler(this);
  pEventTask->registerEventHandler(pEventHandler);

  m_pEAFModelResultWrapper = new CEAFModelResultWrapper();
  m_pEAFModelResultWrapper->setpModelTask(this);


  return RetCode;
}

//##ModelId=4146BA48015B
CIntfEAF* CEAFModelTask::getpIntfEAF()
{
	return m_pIntfEAF;
}

// should be const and return a const pointer, but parameter mgr lacks const. get-operations
CParamMgr* CEAFModelTask::getpParamMgr()
{
  return const_cast< CParamMgr* >(m_pIntfParamMgr->getpActParamMgr());
}
const CCfgEAF* CEAFModelTask::getpCfgEAF() const
{
  return m_pCfgEAF;
}

CCfgEAF* CEAFModelTask::getUnConstpCfgEAF()
{
  return m_pCfgEAF;
}

//##ModelId=4146BA480147
CEAFModelTask* CEAFModelTask::getInstance()
{
  if ( 0 == Instance )
  {
    Instance = new CEAFModelTask();
  }
	return Instance;
}


//##ModelId=467647CB0394
bool CEAFModelTask::callModelResultWrapper(const std::string& Type ,CEventMessage& Event)
{
  bool RetValue = false;

  if ( m_pEAFModelResultWrapper )
  {
    RetValue = m_pEAFModelResultWrapper->doModelResult(Event);
  }

  return RetValue;
}
bool CEAFModelTask::callModelResultWrapper(const std::string& Type ,CEventMessage& Event, CEAFModelWrapper& CallMeBack)
{
  bool RetValue = false;

  if ( m_pEAFModelResultWrapper )
  {
    RetValue = m_pEAFModelResultWrapper->doModelResult(Event, CallMeBack);
  }

  return RetValue;
}

//##ModelId=467647CB03C6
CIntf* CEAFModelTask::getpModelInterface(const std::string& Type)
{
  	return m_pIntfEAF;
}


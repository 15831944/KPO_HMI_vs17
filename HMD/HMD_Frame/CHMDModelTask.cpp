// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"

#include "CHMDTreatmentManagerEventHandler.h"
#include "CHMDModelResultWrapper.h"

#include "CHMDModelTask.h"

//##ModelId=4124B2550204
CHMDModelTask* CHMDModelTask::Instance = 0;

//##ModelId=4110E48B0136
void CHMDModelTask::ownStartUp()
{
  try
  {
    setWorking(true);
    cCBS_Task::ownStartUp();
  }
  catch(...) 
  {
    std::cout << "exception caught in CHMDModelTask::ownStartUp()" << std::endl;
  }
}

//##ModelId=4110E48D014F
void CHMDModelTask::ownRunDown()
{
  setWorking(false);
  
  cCBS_Task::ownRunDown();
}

//##ModelId=411120B001EC
CHMDModelTask::~CHMDModelTask()
{
  if (m_pHMDModelResultWrapper) delete m_pHMDModelResultWrapper;

}

//##ModelId=411120B8025D
CHMDModelTask::CHMDModelTask() 
: m_pHMDModelResultWrapper(0)
{
}

//##ModelId=4110E49900E7
bool CHMDModelTask::initialize()
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
  std::string IniFileName = pStdInitBase->getConfigName();
  // searching valid value in inifile
  pStdInitBase->replaceWithEntry("PATH","ModelIniFileName",IniFileName);

  // combination with environment variable
  IniFileName = pStdInitBase->getXPACT_SMC() + IniFileName;
 
  // getting pointer to frame task
  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

  // instantiation and registration of all EventHandler classes
  CHMDEventHandler *pEventHandler = 0;


  pEventHandler = new CHMDTreatmentManagerEventHandler(this);

  pEventTask->registerEventHandler(pEventHandler); 

  // create new model result wrapper (to call special doModelResult method in HMD heating mode)
  m_pHMDModelResultWrapper = new CHMDModelResultWrapper();
  m_pHMDModelResultWrapper->setpModelTask(this);

  return RetCode;

}

//##ModelId=4124B26E0215
CHMDModelTask* CHMDModelTask::getInstance()
{
  if ( 0 == Instance )
  {
    Instance = new CHMDModelTask();
  }
  return Instance;
}

bool CHMDModelTask::callModelResultWrapper(const std::string& Type ,CEventMessage& Event)
{
  bool RetValue = false;

  if ( m_pHMDModelResultWrapper )
  {
    RetValue = m_pHMDModelResultWrapper->doModelResult(Event);
  }

  return RetValue;
}
#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
  #pragma warning(disable:4099)
#endif

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"

#include "CDM_EAFTask.h"
#include "CDM_EAFDBManagerTask.h"
#include "CTSM_EAF_Task.h"
#include "CDH_HMI_Task.h"
//#include "CDH_L1_EAF_IN_Task.h"
#include "CEAFModelTask.h"
#include "CARCHIVER_EAFTask.h"

#include "CSMC_AsyncFileLogHandler.h"

// use config file e.g.: -config $(X-Pact)\cfg\SMC_OFFLINE\EAF_OFFLINE_RT.ini

int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    bool AsyncLog = true;

    cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG", "AsyncLog", AsyncLog);

    if (AsyncLog)
    {
      CSMC_AsyncFileLogHandler* pSMC_FileLogHandler = new CSMC_AsyncFileLogHandler();
      pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);
    }
    else
    {
      CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
      pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);
    }

    std::string TaskName;

    // init DM_EAF Task and register
    TaskName = "DM_EAFTask";
    CDM_EAFTask* pDM_EAFTask = CDM_EAFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDM_EAFTask);

    TaskName = "DM_EAFDBManager_Task";
    CDM_EAFDBManagerTask * pDM_EAFDBManagerTask = CDM_EAFDBManagerTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDM_EAFDBManagerTask);

    // init TSM_EAF Task and register
    TaskName = "TSM_EAFTask";
    CTSM_EAF_Task* pTSM_EAF_Task = CTSM_EAF_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pTSM_EAF_Task);

    //init EAFModelTask and register
    TaskName = "EAFTask";
    CEAFModelTask* pEAFModelTask = CEAFModelTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pEAFModelTask);

    //init ARCHIVER_EAFTask and register
    TaskName = "ARCHIVER_EAFTask";
    CARCHIVER_EAFTask* pARCHIVER_EAFTask = CARCHIVER_EAFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pARCHIVER_EAFTask);

    //init DH_HMI_Task and register
    TaskName = "DH_HMI_Task";
    CDH_HMI_Task* pDH_HMI_Task = CDH_HMI_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDH_HMI_Task);

    // run the application / CORBA
    pCBS_StdFrame->runAsServer();
  }
  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}


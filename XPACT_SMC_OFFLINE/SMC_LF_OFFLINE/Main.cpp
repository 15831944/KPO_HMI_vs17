#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
  #pragma warning(disable:4099)
#endif

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"

#include "CDM_LFTask.h"
#include "CTSM_LF_Task.h"
#include "CDH_HMI_Task.h"
//#include "CDH_L1_LF_IN_Task.h"
#include "CLFModelTask.h"
#include "CARCHIVER_LFTask.h"

#include "CSMC_AsyncFileLogHandler.h"

// use config file e.g.: -config $(X-Pact)\cfg\SMC_OFFLINE\LF_OFFLINE_RT.ini

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

    // init DM_LF Task and register
    TaskName = "DM_LFTask";
    CDM_LFTask* pDM_LFTask = CDM_LFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDM_LFTask);

    TaskName = "DM_LFDBManager_Task";
    CDM_LFDBManagerTask * pDM_LFDBManagerTask = CDM_LFDBManagerTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDM_LFDBManagerTask);

    // init TSM_LF Task and register
    TaskName = "TSM_LFTask";
    CTSM_LF_Task* pTSM_LF_Task = CTSM_LF_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pTSM_LF_Task);

    //init LFModelTask and register
    TaskName = "LFTask";
    CLFModelTask* pLFModelTask = CLFModelTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pLFModelTask);

    //init ARCHIVER_LFTask and register
    TaskName = "ARCHIVER_LFTask";
    CARCHIVER_LFTask* pARCHIVER_LFTask = CARCHIVER_LFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pARCHIVER_LFTask);

    //init DH_HMI_Task and register
    TaskName = "DH_HMI_Task";
    CDH_HMI_Task* pDH_HMI_Task = CDH_HMI_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDH_HMI_Task);

    // run the application / CORBA
    pCBS_StdFrame->runAsServer();


    // run the application / CORBA
    pCBS_StdFrame->runAsServer();

  }
  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}


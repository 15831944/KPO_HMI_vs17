#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
  #pragma warning(disable:4099)
#endif

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"

#include "CDM_GENTask.h"
#include "CTSM_GEN_Task.h"
#include "CDM_GENDBManagerTask.h"
#include "CDH_HMI_Task.h"

#include "CSMC_AsyncFileLogHandler.h"

// use config file e.g.: -config $(X-Pact)\cfg\SMC_OFFLINE\GEN_OFFLINE_RT.ini

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

    // init DM_GEN Task and register
    TaskName = "DM_GENTask";
    CDM_GENTask* pDM_GENTask = CDM_GENTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDM_GENTask);

    // init TSM_GEN Task and register
    TaskName = "TSM_GENTask";
    CTSM_GEN_Task* pTSM_GEN_Task = CTSM_GEN_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pTSM_GEN_Task);

    TaskName = "DM_GENDBManager_Task";
    CDM_GENDBManagerTask * pDM_GENDBManagerTask = CDM_GENDBManagerTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDM_GENDBManagerTask);

    //init DH_HMI_Task and register
    TaskName = "DH_HMI_Task";
    CDH_HMI_Task* pDH_HMI_GEN_Task = CDH_HMI_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pDH_HMI_GEN_Task);

    // run the application / CORBA
    pCBS_StdFrame->runAsServer();

  }
  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}


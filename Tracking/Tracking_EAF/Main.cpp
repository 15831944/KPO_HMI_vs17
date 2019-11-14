

#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CTSM_EAF_Task.h"
#include "CDM_EAFTask.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"
#include "CDM_EAFDBManagerTask.h"

// -config $(X-Pact)\cfg\Tracking\Tracking_EAF_1.ini

int main(int argc, const char **argv)
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pFrame = new cCBS_StdFrame(argc, argv);

    bool AsyncLog = true;

    cCBS_StdInitBase::getInstance()->replaceWithEntry("LOG", "AsyncLog", AsyncLog);

    if (AsyncLog)
    {
      CSMC_AsyncFileLogHandler* pSMC_FileLogHandler = new CSMC_AsyncFileLogHandler();
      pFrame->registerLogHandler(pSMC_FileLogHandler);
    }
    else
    {
      CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
      pFrame->registerLogHandler(pSMC_FileLogHandler);
    }

    std::string TaskName;

    TaskName = "TSM_Task";
    CTSM_EAF_Task * pTSM_EAF_Task = CTSM_EAF_Task::getInstance();
    pFrame->registerTask(TaskName, pTSM_EAF_Task);

    TaskName = "DM_Task";
    CDM_EAFTask * pDM_EAFTask = CDM_EAFTask::getInstance();
    pFrame->registerTask(TaskName, pDM_EAFTask);

    TaskName = "DBManager_Task";
    CDM_EAFDBManagerTask * pDM_EAFDBManagerTask = CDM_EAFDBManagerTask::getInstance();
    pFrame->registerTask(TaskName, pDM_EAFDBManagerTask);


    // run the application / CORBA
    pFrame->runAsServer();

  }
  catch(cCBS_Exception &Exc)
  {
    std::cout << Exc << std::endl;
  }
  catch(...)
  {
    std::cout << "exception caught "  << std::endl;
  }

  return 0;
}


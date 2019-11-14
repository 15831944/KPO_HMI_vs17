#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CTSM_GEN_Task.h"
#include "CDM_GENTask.h"
#include "CSMC_FileLogHandler.h"
#include "CDM_GENDBManagerTask.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(X-Pact)\cfg\Tracking\Tracking_GEN.ini

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
    CTSM_GEN_Task * pTSM_GEN_Task = CTSM_GEN_Task::getInstance();
    pFrame->registerTask(TaskName, pTSM_GEN_Task);

    TaskName = "DM_Task";
    CDM_GENTask * pDM_GENTask = CDM_GENTask::getInstance();
    pFrame->registerTask(TaskName, pDM_GENTask);

    TaskName = "DBManager_Task";
    CDM_GENDBManagerTask * pDM_GENDBManagerTask = CDM_GENDBManagerTask::getInstance();
    pFrame->registerTask(TaskName, pDM_GENDBManagerTask);

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


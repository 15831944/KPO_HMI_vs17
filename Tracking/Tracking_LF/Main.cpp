#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CTSM_LF_Task.h"
#include "CDM_LFTask.h"
#include "CSMC_FileLogHandler.h"

// -config $(X-Pact)\cfg\Tracking\Tracking_LF_1.ini
// -config $(X-Pact)\cfg\Tracking\Tracking_LF_2.ini

int main(int argc, const char **argv)
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pFrame->registerLogHandler(pSMC_FileLogHandler);

    std::string TaskName;

    TaskName = "TSM_Task";
    CTSM_LF_Task * pTSM_LF_Task = CTSM_LF_Task::getInstance();
    pFrame->registerTask(TaskName, pTSM_LF_Task);

    TaskName = "DM_Task";
    CDM_LFTask * pDM_LFTask = CDM_LFTask::getInstance();
    pFrame->registerTask(TaskName, pDM_LFTask);

    TaskName = "DBManager_Task";
    CDM_LFDBManagerTask * pDM_LFDBManagerTask = CDM_LFDBManagerTask::getInstance();
    pFrame->registerTask(TaskName, pDM_LFDBManagerTask);

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


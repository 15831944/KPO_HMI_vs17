#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CTSM_HMD_Task.h"
#include "CDM_HMDTask.h"
#include "CSMC_FileLogHandler.h"

// -config $(XPACT_SMC)\cfg\Tracking\Tracking_HMD_1.ini
// -config $(XPACT_SMC)\cfg\Tracking\Tracking_HMD_2.ini

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
    CTSM_HMD_Task * pTSM_HMD_Task = CTSM_HMD_Task::getInstance();
    pFrame->registerTask(TaskName, pTSM_HMD_Task);

    TaskName = "DM_Task";
    CDM_HMDTask * pDM_HMDTask = CDM_HMDTask::getInstance();
    pFrame->registerTask(TaskName, pDM_HMDTask);

    TaskName = "DBManager_Task";
    CDM_HMDDBManagerTask * pDM_HMDDBManagerTask = CDM_HMDDBManagerTask::getInstance();
    pFrame->registerTask(TaskName, pDM_HMDDBManagerTask);

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


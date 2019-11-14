#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_ConfigBase.h"
#include "cCBS_StdFrame.h"
#include "CEventHandler.h"
#include "CHMDModelTask.h"
#include "CSMC_FileLogHandler.h"
#include "cCBS_StdInitBase.h"

// use config file e.g.: -config $(XPACT_SMC)\cfg\HMD\HMD_1.ini

int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    std::string TaskName = cCBS_StdInitBase::getInstance()->m_ServerName + "Task";
    CHMDModelTask * pHMDModelTask = CHMDModelTask::getInstance( );
    pCBS_StdFrame->registerTask(TaskName,pHMDModelTask);
    
    // run the application / CORBA
    pCBS_StdFrame->runAsServer();

  }
  catch(cCBS_Exception Exc)
  {
    std::cout << Exc << std::endl;
  }
  catch(...)
  {
    std::cout << "exception caught "  << std::endl;
  }

  return 0;
}


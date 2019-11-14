#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CSYSMON_Task.h"
#include "CSMC_FileLogHandler.h"

// -config $(X-Pact)\cfg\Tools\Sysmon.ini

int main(int argc, const char **argv)
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pFrame = new cCBS_StdFrame(argc, argv);

    CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    pFrame->registerLogHandler(pSMC_FileLogHandler);

    std::string TaskName;

    TaskName = "CSYSMON_Task";
    CSYSMON_Task * pSYSMON_Task = new CSYSMON_Task();
    pFrame->registerTask(TaskName, pSYSMON_Task);


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


#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_ConfigBase.h"
#include "cCBS_StdFrame.h"
#include "CARCHIVER_LFTask.h"
#include "CEventHandler.h"
#include "CSMC_FileLogHandler.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_AsyncFileLogHandler.h"


// use command line argument: -config $(X-Pact)\cfg\ARCHIVER\ARCHIVER_LF_1.ini
// use command line argument: -config $(X-Pact)\cfg\ARCHIVER\ARCHIVER_LF_2.ini
// use command line argument: -config $(X-Pact)\cfg\ARCHIVER\ARCHIVER_LF_3.ini

int main( int argc, const char *argv[])
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

    std::string TaskName = "ARCHIVER_LF_Task";
    CARCHIVER_LFTask * pARCHIVER_LFTask = CARCHIVER_LFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pARCHIVER_LFTask);

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


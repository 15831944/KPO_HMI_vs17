#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdInitBase.h"
#include "cCBS_ConfigBase.h"
#include "cCBS_StdFrame.h"
#include "CARCHIVER_EAFTask.h"
#include "CEventHandler.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"



// use command line argument: -config $(X-Pact)/cfg/ARCHIVER/ARCHIVER_EAF_1.ini

int main( int argc, const char *argv[])
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    //CSMC_FileLogHandler* pSMC_FileLogHandler = new CSMC_FileLogHandler();
    //pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

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



    std::string TaskName = "ARCHIVER_EAF_Task";
    CARCHIVER_EAFTask * pARCHIVER_EAFTask = CARCHIVER_EAFTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pARCHIVER_EAFTask);


    // run the application / CORBA
    pCBS_StdFrame->runAsServer();

  }
  catch(cCBS_Exception Exc)
  {
    cout << Exc << endl;
  }
  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}


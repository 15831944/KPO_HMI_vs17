#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
  #pragma warning(disable:4099)
#endif

#include <sstream>
#include "cCBS_ConfigBase.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdFrame.h"
#include "CEventHandler.h"
#include "CLFModelTask.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

// use the following argument during debugging
// -config $(X-Pact)\cfg\LF\LF_11.ini
// -config $(X-Pact)\cfg\LF\LF_12.ini

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


    std::string TaskName = cCBS_StdInitBase::getInstance()->m_ServerName + "Task";
    CLFModelTask * pLFModelTask = CLFModelTask::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pLFModelTask);
    
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


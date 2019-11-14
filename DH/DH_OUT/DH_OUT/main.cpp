#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_ConfigBase.h"
#include <sstream>

using namespace std;

#include "cCBS_StdFrame.h"
#include "CDH_OUT_Task.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(X-Pact)\CFG\DH\DH_L1_LF_1_OUT.ini
// -config $(X-Pact)\CFG\DH\DH_L1_EAF_1_OUT.ini
// -config $(X-Pact)\CFG\DH\DH_LAB_OUT.ini
// -config $(X-Pact)\CFG\DH\DH_CCS_OUT.ini
// -config $(X-Pact)\CFG\DH\DH_IPQS_OUT.ini


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
		
    // activate SMC Application Environment
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
    CDH_OUT_Task * pDH_OUT_Task = CDH_OUT_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDH_OUT_Task);

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


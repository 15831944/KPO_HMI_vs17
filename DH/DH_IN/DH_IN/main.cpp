#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_ConfigBase.h"
#include <sstream>

using namespace std;

#include "cCBS_StdFrame.h"
#include "CDH_IN_Task.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(X-Pact)\CFG\DH\DH_L1_AOD_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_BOF_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_CCS_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_EAF_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_CONARC_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_HMD_IN.ini
// -config $(X-Pact)\CFG\DH\DH_HMP_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L2LF_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L3_IN.ini
// -config $(X-Pact)\CFG\DH\DH_LAB_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_LF_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_RH_1_IN.ini
// -config $(X-Pact)\CFG\DH\DH_L1_VD_1_IN.ini



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
    CDH_IN_Task * pDH_IN_Task = CDH_IN_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDH_IN_Task);

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


#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_ConfigBase.h"
#include <sstream>

using namespace std;

#include "cCBS_StdFrame.h"
#include "CDH_HMI_Task.h"
#include "cCBS_StdInitBase.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(X-Pact)\CFG\DH\DH_HMI_BOF.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_AOD.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_EAF.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_RH.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_HMD.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_LF.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_VD.ini
// -config $(X-Pact)\CFG\DH\DH_HMI_ConArc.ini


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
    CDH_HMI_Task * pDH_HMI_Task = CDH_HMI_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName,pDH_HMI_Task);

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


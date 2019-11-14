// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : Process_Monitor 
//  filename      : main.cpp
//  originator    : joge
//  department    : 
//  creation date : 17.03.2009
//  description   : CBS based main function
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy   author  remarks
//  
// 
// ----------------------------------------------------------------------------
// 


#include "cCBS_StdFrame.h"
#include "CSMC_FileLogHandler.h"
#include "CProcess_Monitor_Check_Task.h"
#include "CProcess_Monitor_Task.h"
#include "CSMC_AsyncFileLogHandler.h"

// -config $(XPACT_SMC)\cfg\Process_Monitor\Process_Monitor.ini

int main(int argc, const char *argv[])
{

  try
  {
    cCBS_StdFrame * pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

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

    CProcess_Monitor_Check_Task * pMonitor_Check_Task = CProcess_Monitor_Check_Task::getInstance();
    pCBS_StdFrame->registerTask("Control_Task",pMonitor_Check_Task);

    CProcess_Monitor_Task * pMonitor_Task = CProcess_Monitor_Task::getInstance();
    pCBS_StdFrame->registerTask("Task",pMonitor_Task);

    pCBS_StdFrame->runAsServer();

    //if (pMonitor_Check_Task) delete pMonitor_Check_Task;
    if (pMonitor_Task) delete pMonitor_Task;

  }
  catch(cCBS_Exception &Exc)
  {
    std::cout << Exc << std::endl;
  }
  catch(...)
  {
    std::cout << "Exception caught at main() !\n";
    getchar();
  }

  return EXIT_SUCCESS;
}

//---------------------------------------------------------------------
//--- end of file: mainDataHandler.cpp

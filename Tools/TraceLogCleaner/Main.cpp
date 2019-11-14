// Copyright SMS Demag AG 2004
// TraceLogCleaner Test program 

#include "cCBS_StdFrame.h"
#include "CTraceLogCleaner_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "CSMC_AsyncFileLogHandler.h"


// start with -config $(X-Pact)\cfg\Tools\TraceLogCleaner.ini

int main(int argc, const char * argv[])
{
  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    CSMC_AsyncFileLogHandler* pSMC_FileLogHandler = new CSMC_AsyncFileLogHandler();
    pCBS_StdFrame->registerLogHandler(pSMC_FileLogHandler);

    std::string TaskName;

    TaskName = "TraceLogCleaner_Task";
    CTraceLogCleaner_Task * pTraceLogCleaner_Task = CTraceLogCleaner_Task::getInstance();
    pCBS_StdFrame->registerTask(TaskName, pTraceLogCleaner_Task);


    // run the application / CORBA
    pCBS_StdFrame->runAsServer();
  }
  catch(...)
  {
    std::cout << "Exception caught at main() !" << std::endl;
  }
  return 0;
}
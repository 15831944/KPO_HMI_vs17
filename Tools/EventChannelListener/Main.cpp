// Copyright SMS Demag AG 2004
// EventChannelListener Test program 

#include "cCBS_StdFrame.h"
#include "cCBS_StdInitBase.h"
#include "CEventChannelListenerEventHandler.h"
#include "cCBS_StdEvent_Task.h"
#include "CSMC_FileLogHandler.h"
#include "CSMC_AsyncFileLogHandler.h"


// start with -config $(X-Pact)\cfg\Tools\EventChannelListener.ini

int main(int argc, const char * argv[])
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

    CEventChannelListenerEventHandler * pEventHandler = new CEventChannelListenerEventHandler();

    cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

    if(pEventTask)
    {
      pEventTask->registerEventHandler(pEventHandler);
    }


    pCBS_StdFrame->runAsServer();
  }
  catch(...)
  {
    std::cout << "Exception caught at main() !" << std::endl;
  }
  return 0;
}
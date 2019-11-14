
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEvent_Task.h"
#include "CARCHIVER_SRVTask.h"
#include "CARCHIVER_SRVEventHandler.h"

CARCHIVER_SRVTask* CARCHIVER_SRVTask::m_Instance = 0;

CARCHIVER_SRVTask::CARCHIVER_SRVTask()
{
}

CARCHIVER_SRVTask::~CARCHIVER_SRVTask()
{
}

bool CARCHIVER_SRVTask::initialize()
{
	bool RetCode = CARCHIVER_Task::initialize(); // calls setCORBAConnections();

  // registering event handler
  CARCHIVER_SRVEventHandler * pEventHandler = new CARCHIVER_SRVEventHandler(this);
  
  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();
  if (pEventTask)
  {
    pEventTask->registerEventHandler(pEventHandler);
  }

  return RetCode;
}

void CARCHIVER_SRVTask::ownStartUp()
{
  // trigger exetution by simulation of external event
  CEventMessage Event;
  Event.setMessage("ownStartUp");
  Event.dispatch("ARCHIVER_SRV","ARCHIVER_SRV",false);

  cCBS_StdFrame_Task::ownStartUp();
}

CARCHIVER_SRVTask* CARCHIVER_SRVTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CARCHIVER_SRVTask();
	}
	return m_Instance;
}

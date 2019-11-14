// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"

#include "CARCHIVER_EAFEventHandler.h"
#include "CARCHIVER_EAFTask.h"

//##ModelId=419A2FC10223
CARCHIVER_EAFTask* CARCHIVER_EAFTask::m_Instance = 0;

//##ModelId=4152992A0113
CARCHIVER_EAFTask::CARCHIVER_EAFTask()
{
}

//##ModelId=4152992901EF
CARCHIVER_EAFTask::~CARCHIVER_EAFTask()
{
}

//##ModelId=419A1E7C001D
bool CARCHIVER_EAFTask::initialize()
{
	bool RetCode = CARCHIVER_Task::initialize(); // calls setCORBAConnections();

  // registering event handler
  CARCHIVER_EAFEventHandler * pEventHandler = new CARCHIVER_EAFEventHandler(this);

  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();
  if (pEventTask)
  {
    pEventTask->registerEventHandler(pEventHandler);
  }

  return RetCode;

}

//##ModelId=419B7B310072
CARCHIVER_EAFTask* CARCHIVER_EAFTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CARCHIVER_EAFTask( );
	}
	return m_Instance;
}

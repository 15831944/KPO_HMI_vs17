// Copyright (C) 2007 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"

#include "CARCHIVER_LFEventHandler.h"
#include "CARCHIVER_LFTask.h"

CARCHIVER_LFTask* CARCHIVER_LFTask::m_Instance = 0;

CARCHIVER_LFTask* CARCHIVER_LFTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CARCHIVER_LFTask();
	}
  return m_Instance;
}

CARCHIVER_LFTask::CARCHIVER_LFTask()
{
}

CARCHIVER_LFTask::~CARCHIVER_LFTask()
{
}

bool CARCHIVER_LFTask::initialize()
{
  bool RetCode = CARCHIVER_Task::initialize();  // calls setCORBAConnections();

  // registering event handler
  CARCHIVER_LFEventHandler * pEventHandler = new CARCHIVER_LFEventHandler(this);
  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

  if (pEventTask)
  {
    pEventTask->registerEventHandler(pEventHandler);
  }

  return RetCode;

}


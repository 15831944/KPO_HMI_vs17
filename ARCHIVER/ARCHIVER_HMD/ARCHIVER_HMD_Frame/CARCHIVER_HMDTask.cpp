// Copyright (C) 2007 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdInitBase.h"

#include "CARCHIVER_HMDEventHandler.h"
#include "CARCHIVER_HMDTask.h"

//##ModelId=4670F158032A
CARCHIVER_HMDTask* CARCHIVER_HMDTask::m_Instance = 0;

//##ModelId=45D5899B0306
CARCHIVER_HMDTask* CARCHIVER_HMDTask::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CARCHIVER_HMDTask();
	}
  return m_Instance;
}

//##ModelId=45D5899B0387
CARCHIVER_HMDTask::CARCHIVER_HMDTask()
{
}

//##ModelId=45D5899B0338
CARCHIVER_HMDTask::~CARCHIVER_HMDTask()
{
}

//##ModelId=45D5899B03AF
void CARCHIVER_HMDTask::getOwnStateDetails(CORBA::String_out details)
{
	std::ostringstream buf;
  // mrut 2015-01-20: next line deleted due to memory leakage
	//cCBS_Task::getOwnStateDetails(details);
	buf << '\n' << "CARCHIVER_HMDTask!" << std::ends;
	details = CORBA::string_dup(buf.str().c_str());
}

//##ModelId=45D5899C000D
bool CARCHIVER_HMDTask::initialize()
{
  bool RetCode;
  
  RetCode = CARCHIVER_Task::initialize();

  // registering event handler
  CARCHIVER_HMDEventHandler * pEventHandler = new CARCHIVER_HMDEventHandler(this);
  cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

  if (pEventTask)
  {
    pEventTask->registerEventHandler(pEventHandler);
  }
  return RetCode;
}

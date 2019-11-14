// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdInitBase.h"

//##ModelId=40EBCAAE030B
#include "cCBS_StdEventHandler.h"
#include "cCBS_StdFrame_Task.h"



//##ModelId=40EBCAAE030B
void cCBS_StdEventHandler::log(const std::string& Message, long Level)
{
  if (m_pEventTask)
    m_pEventTask->log(Message, Level);
}

//##ModelId=41090DE700CE
cCBS_StdEventHandler::~cCBS_StdEventHandler()
{
}

//##ModelId=433BA955033A
void cCBS_StdEventHandler::setpTask(cCBS_StdFrame_Task* value)
{
	m_pTask = value;
	return;
}


//##ModelId=41090DE60392
cCBS_StdEventHandler::cCBS_StdEventHandler(cCBS_StdFrame_Task* pTask) 
: m_pEventTask(0)
, m_pTask(pTask)
{
	m_pEventTask = cCBS_StdEvent_Task::getInstance();
}

long cCBS_StdEventHandler::getTraceLevel()
{
  if (m_pEventTask)
    return m_pEventTask->getTraceLevel();
  else
    return 0;
}

void cCBS_StdEventHandler::setEventHandlerTaskName( const std::string& EventHandlerTaskName)
{
  m_EventHandlerTaskName = EventHandlerTaskName;
}

std::string cCBS_StdEventHandler::getEventHandlerTaskName()
{
  return m_EventHandlerTaskName;
}


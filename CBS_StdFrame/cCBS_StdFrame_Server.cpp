// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "CBS_Utilities.h"


#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdFrame_Server.h"
#include "cCBS_StdFrame_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdLogHandler.h"
#include "cCBS_StdInitBase.h"


//##ModelId=40EAA093014E
void cCBS_StdFrame_Server::createTasks()
{
  if (m_pServer_Component)
  {
    m_pServer_Component->setpServer(this);
  	m_pServer_Component->activate(s_componentPOA, getComponentName());
  }
}

//##ModelId=40EAA0930151
cCBS_StdFrame_Server::~cCBS_StdFrame_Server()
{
  if (m_pServer_Component)
	{
		delete m_pServer_Component;
    m_pServer_Component = NULL;
	}
}

//##ModelId=40EAA0930154
cCBS_StdFrame_Server::cCBS_StdFrame_Server(int argc, const char* argv[])
: m_pServer_Component(0),m_pCORBA_Task(0),m_pDB_Task(0),m_pEvent_Task(0),m_pLog_Task(0)
, cCBS_StdServer( argc, argv )
{
  // instantiate all necessary SMC Application_Frame tasks
  // Log_Task first !!!!!! to ensure that all logs will be written
  m_pLog_Task = cCBS_StdLog_Task::getInstance();

  m_pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
  m_pDB_Task = cCBS_StdDB_Task::getInstance();
  m_pEvent_Task = cCBS_StdEvent_Task::getInstance();

  // instantiate component
	m_pServer_Component = new cCBS_StdFrame_Component();
 

  registerTask("LogTask",m_pLog_Task);

  registerTask("CorbaTask", m_pCORBA_Task);
  registerTask("DBTask", m_pDB_Task);
  registerTask("EventTask", m_pEvent_Task);
}


//##ModelId=40EAA0930160
void cCBS_StdFrame_Server::runAsServer()
{
  // create all tasks before running CORBA
  createTasks();
	
	cCBS_StdFrame_Server::run();

//  runDownTasks();
}

//##ModelId=40EAA0930163
void cCBS_StdFrame_Server::runAsClient()
{
  // create all tasks before running CORBA
  createTasks();
}


//##ModelId=40EBCAAD0327
void cCBS_StdFrame_Server::registerTask(const std::string & TaskName, cCBS_StdFrame_Task *pTask)
{
  if (m_pServer_Component)
  {
    m_pServer_Component->registerTask(TaskName,pTask);
  }
}



//##ModelId=41FE119C0329
void cCBS_StdFrame_Server::registerLogHandler(cCBS_StdLogHandler* NewHandler)
{
  if (m_pLog_Task)
  {
    m_pLog_Task->registerLogHandler(NewHandler);
  }
}



//##ModelId=4215D15F0192
void cCBS_StdFrame_Server::runDownTasks()
{
  if (m_pServer_Component)
  {
    m_pServer_Component->runDownSubtasks();
  }
}


// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>

#include "cbs.h"
#include "CBS_Utilities.h"
#include "cCBS_StdFrame_Task.h"
#include "cCBS_StdFrame_Server.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdFrame_Component.h"

//##ModelId=42146A510242
void cCBS_StdFrame_Component::beforeSubtaskEnd()
{
}

//##ModelId=42146A53033F
void cCBS_StdFrame_Component::beforeSubtaskStart()
{
}


//##ModelId=40EAA0930115
void cCBS_StdFrame_Component::afterSubtaskEnd()
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ProcessStopped(Message,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

  try
  {
    CBS::shutdown();
  }
  catch(...)
  {
    log("Exception at CBS::shutdown() caught !", 4);
  }
}

//##ModelId=40EAA0930118
void cCBS_StdFrame_Component::afterSubtaskStart()
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ProcessStarted(Message,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());
}


//##ModelId=40EAA093011B
void cCBS_StdFrame_Component::createSubtasks()
{
  // Create task data and set task properties

	log("cCBS_StdFrame_Component: createSubtasks()", 4);

  // Prepare task name string for usage in configuration base
  cCBS_ConfigBase * configBase = cCBS_ConfigBase::getConfigBase();

  std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>::iterator it;

  for ( it = m_TaskList.begin(); it != m_TaskList.end(); it++ )
  {
    std::string TaskName        = it->first;    
    cCBS_StdFrame_Task* pTask   = it->second; 

    if(pTask) 
    {
      TaskName = pTask->generateName(TaskName);
      // setting pointer to component, will be used for task control or component run-down
      pTask->setpComponent(this);

      std::string Message("cCBS_StdFrame_Component::createSubtasks(): Activating Task : ");
      Message += TaskName;
      log(Message,3);

      if (pTask->activate(TaskName.c_str()))
      {
        addSubtask(pTask->getReference());
      }
      else
      {
        std::string Message("cCBS_StdFrame_Component::createSubtasks(): Task not activated : ");
        Message += TaskName;
        log(Message,1);
      }

    }
  } // for ( it = m_TaskList.begin(); it < m_TaskList.end() it++ )


  startUp();
  
}

//##ModelId=40EAA093011E
void cCBS_StdFrame_Component::getOwnStateDetails(std::string& details)
{
	std::ostringstream buf;
	cCBS_StdComponent::getOwnStateDetails(details);
	buf << '\n' << "CComponent!" << std::ends;
	
  details = buf.str().c_str();
}

//##ModelId=40EAA0930123
cCBS_StdFrame_Component::~cCBS_StdFrame_Component()
{
  if ( m_pControlThread )
  {
    delete m_pControlThread;
  }

  std::vector<std::pair<std::string, cCBS_StdFrame_Task*>>::reverse_iterator it;

  for (it = m_TaskList.rbegin(); it != m_TaskList.rend(); ++it)
  {
    delete it->second;
  } // for ( it = m_TaskList.begin(); it < m_TaskList.end() it++ )

}

//##ModelId=40EAA0930126
cCBS_StdFrame_Component::cCBS_StdFrame_Component()
: cCBS_StdComponent()
, m_pControlThread(0)
{
}


//##ModelId=40EBCAAD025F
void cCBS_StdFrame_Component::setpServer(cCBS_StdFrame_Server* value)
{
	m_pServer = value;
	return;
}


//##ModelId=40EBCAAD022D
void cCBS_StdFrame_Component::log( const std::string  & Message, long Level)
{
  // store last XXX logs for state detail information
  cCBS_StdLog_Task::getInstance()->setStateDetails(Message);

  // log if trace level of actual Task => output level from message
  if ( (long)getTraceLevel() >= Level )
  {
    cCBS_StdLog_Task::getInstance()->writeLog(Message,Level);
  }
}

void cCBS_StdFrame_Component::registerTask(const std::string & TaskName, cCBS_StdFrame_Task* pTask)
{
  if ( pTask && !TaskName.empty() )
  {
    m_TaskList.push_back( std::pair<std::string,cCBS_StdFrame_Task*> (TaskName,pTask) );
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorTaskRegistration(Message);
  }
}

//##ModelId=4120A65201DC
void cCBS_StdFrame_Component::ownRunDown()
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ProcessRunDown(Message,cCBS_StdInitBase::getInstance()->m_ServerName.c_str());

  if (m_pControlThread)
  {
    // terminates thread
    if (m_pControlThread->running())
    {
      m_pControlThread->setTerminateThread(true);
      m_pControlThread->waitForExit();
    }
  }

	setWorking(false);

  std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>::iterator it;

  for ( it = m_TaskList.begin(); it != m_TaskList.end(); it++ )
  {
    // stop control thread of tasks
    it->second->terminateControlThread();

  } // for ( it = m_TaskList.begin(); it < m_TaskList.end() it++ )
}

//##ModelId=4120A6530025
void cCBS_StdFrame_Component::ownStartUp()
{
  log("cCBS_StdFrame_Component: ownStartUp()", 4);

  setWorking(true);

  runControlThread();

  std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>::iterator it;

  for ( it = m_TaskList.begin(); it != m_TaskList.end(); it++ )
  {
    // start control thread of tasks
    it->second->runControlThread();

    // call special startup functions
    it->second->doOnComponentStartup();
  } // for ( it = m_TaskList.begin(); it < m_TaskList.end() it++ )
}

//##ModelId=4215D14E02EB
void cCBS_StdFrame_Component::runDownSubtasks()
{
  // Not required to call this function.
  // CBS is doing it if component is stopped

	//log("cCBS_StdFrame_Component: runDownSubtasks()", 4);

 // std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>::iterator it;

 // for ( it = m_TaskList.begin(); it != m_TaskList.end(); it++ )
 // {
 //   it->second->ownRunDown();
 // } // for ( it = m_TaskList.begin(); it < m_TaskList.end() it++ )

 // runDown();
}

//##ModelId=44FE88B20325
std::vector<std::pair<std::string,cCBS_StdFrame_Task*>> cCBS_StdFrame_Component::getTaskList()
{
  return m_TaskList;
}

//##ModelId=48AD3F9900CD
void cCBS_StdFrame_Component::terminate()
{
  // termiate component immediatelly
  exit(EXIT_FAILURE);
}

//##ModelId=48AD6B190016
void cCBS_StdFrame_Component::doOnThreadControlError()
{
  logStateDetails();
}

void cCBS_StdFrame_Component::logStateDetails()
{
  // The mutex is required to synchronize output of several control threads
  cCBS_StdMutex Mutex("cCBS_StdFrame_Component::logStateDetails()");

  std::ofstream LogFile;
  std::string FileName = cCBS_StdInitBase::getInstance()->getXPACT_SMC_LOG() + getTaskName() + "TaskStatus.log";
  LogFile.open(FileName.c_str(), std::ios::app);
  std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>::iterator it;
 
  CBS_LocalTime TimeNow;

  cCBS_Time::localTime(TimeNow);

  std::stringstream T;
  T << "\n" << "******************************************************" << "\n" << TimeNow.day << "." << TimeNow.month << "." << TimeNow.year << " " << TimeNow.hour << ":" << TimeNow.minute << ":" << TimeNow.second << "\n";

  std::string buffer = T.str();

  LogFile.write(buffer.c_str(), buffer.length());
  LogFile.flush();

  for ( it = m_TaskList.begin(); it != m_TaskList.end(); it++ )
  {
    buffer = it->second->getStateDetails();
    buffer += it->second->getControlThreadStateDetails();

    buffer += "\n";

    LogFile.write(buffer.c_str(), buffer.length());
    LogFile.flush();
  }

  T.str("");
  T << "******************************************************" << "\n";

  buffer = T.str();

  LogFile.write(buffer.c_str(), buffer.length());
  LogFile.flush();

  LogFile.close();
}


//##ModelId=48AD7A70017C
void cCBS_StdFrame_Component::runControlThread()
{
  // if time > 0 is set in ini file, control is active
  long ControlTime = -1;

  // first check general entries 
  // usable value is at least 20 secs
  cCBS_StdInitBase::getInstance()->replaceWithEntry("ProcessControl","ControlTime",ControlTime);

  // overwrite with task specific entries 
  std::string TaskName = getTaskName();
  cCBS_StdInitBase::getInstance()->replaceWithEntry(cCBS_StdInitBase::getInstance()->m_ServerName, "ControlTime", ControlTime);

  if ( ControlTime > 0 && ! m_pControlThread  )
  {
    std::stringstream Message;

    Message << "Starting control thread for component " 
            << TaskName 
            << " using control time " 
            << ControlTime 
            << " (msecs) ";
    
    log(Message.str(),3);

    m_pControlThread = new cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread(this,ControlTime);
    m_pControlThread->setFreeOnTerminate(false); // will be deleted in destructor
    m_pControlThread->run();
  }

  if (ControlTime > 0)
  {
    if (!m_pControlThread->running())
    {
      setWorking(false);
    }
  }
}

void cCBS_StdFrame_Component::control()
{
  if ( m_pControlThread )
  {
    m_pControlThread->control();
  }
}


//##ModelId=48A558E801CE
void cCBS_StdFrame_Component::uncontrol()
{
  if ( m_pControlThread )
  {
    m_pControlThread->uncontrol();
  }
}

void cCBS_StdFrame_Component::control(bool forceControlError)
{
  if ( m_pControlThread )
  {
    if ( forceControlError )
    {
      m_pControlThread->forceControlError();
    }

    m_pControlThread->control();
  }
}



//******************************************************************************************
//******************************************************************************************
// Thread handling !!!!
//******************************************************************************************
//******************************************************************************************


//##ModelId=48AD61FE00D2
cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::cCBS_StdFrame_ComponentControlThread(cCBS_StdFrame_Component* pComponent, long ControlTime)
: m_ControlTime(ControlTime)
, m_pComponent(pComponent)
, m_doControl(false)
, m_doforceControlError(false)
{
  cCBS_Time::localTime(m_StartTime);
}

//##ModelId=48AD61FE00D5
cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::~cCBS_StdFrame_ComponentControlThread()
{
}

//##ModelId=48AD61FE00D6
void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::work()","performing Working Step");
  }
}



//##ModelId=48AD61FE00D7
void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::terminate()
{
  forceTerminate();
}

//##ModelId=48AD61FE00D8
void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::performWorkingStep()
{
  try
  {
    if ( !getTerminateThread() )
    {
      if ( m_doforceControlError )
      {
        if (m_pComponent)
        {
          // call error handling method and terminate thread
          m_pComponent->doOnThreadControlError();
          m_pComponent->terminate();
        }
      }

      if ( m_doControl == true )
      {
        // calculate time between now and last thread start time
        CBS_LocalTime Now;
        cCBS_Time::localTime(Now);

        long DiffTime = cCBS_Time::diffTime(Now,m_StartTime);

        if ( DiffTime > m_ControlTime  )
        {
          if (m_pComponent)
          {
            // call error handling method and terminate thread
            m_pComponent->doOnThreadControlError();
            m_pComponent->terminate();
          }
        }
      }
    }
  
    // sleep for some seconds, in general 1000 times per Control Cycle but at least 200 msecs !
    long doSleep = max(200,long(m_ControlTime/1000) );
    Sleep(doSleep);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }
}

void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::control()
{
  cCBS_Time::localTime(m_StartTime);
	m_doControl = true;
}

//##ModelId=48A95F550268
void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::uncontrol()
{
	m_doControl = false;
}

void cCBS_StdFrame_Component::cCBS_StdFrame_ComponentControlThread::forceControlError()
{
  m_doforceControlError = true;
}


// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <iomanip>
#include <sstream>

#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdFrame_Task.h"

std::string cCBS_StdFrame_Task::getCurrentTimeAsString()
{
  // Auxiliary variables
  CBS_LocalTime crtTime;
  // Obtains the current time
  cCBS_Time::localTime(crtTime);

  std::stringstream sstr;

  sstr << std::setw(4) << crtTime.day  << "-";
  sstr << std::setw(2) << crtTime.month << "-";
  sstr << std::setw(2) << crtTime.year  << "  ";
  sstr << std::setw(2) << crtTime.hour << ":";
  sstr << std::setw(2) << crtTime.minute  << ":";
  sstr << std::setw(2) << crtTime.second  << ".";
  sstr << std::setw(3) << crtTime.msec;
 
  return sstr.str(); 
}

void cCBS_StdFrame_Task::setStateDetails(const std::string& value)
{
  setStateDetails(" ", value);
}

void cCBS_StdFrame_Task::setStateDetails(const std::string& item, const std::string& value)
{
  cCBS_StdMutex Mutex("m_StateDetailItems");

  std::map<std::string, std::string>::iterator it = m_StateDetailItems.find(item);

  if ( it == m_StateDetailItems.end() )
  {
    m_StateDetailItems.insert( std::pair<std::string,std::string> (item, value) );
  }
  else
  {
    it->second = value;
  }
}

void cCBS_StdFrame_Task::setWorking(bool state)
{
  cCBS_StdTask::setWorking(state);
}


void cCBS_StdFrame_Task::setStateDetails(const std::string& item, const std::string& value, long Level)
{
  cCBS_StdMutex Mutex("m_StateDetailItems");

  std::map<std::string, std::string>::iterator it = m_StateDetailItems.find(item);

  if (  it == m_StateDetailItems.end() )
  {
    if ( (long)cCBS_StdTask::getTraceLevel() >= Level )
    {
      m_StateDetailItems.insert( std::pair<std::string,std::string> (item, value) );
    }
  }
  else
  {
    if ( (long)cCBS_StdTask::getTraceLevel() >= Level )
    {
      it->second = value;
    }
    else
    {
      m_StateDetailItems.erase(it);  
    }
  }
}

std::string cCBS_StdFrame_Task::getStateDetails()
{
  cCBS_StdMutex Mutex("m_StateDetailItems");

  std::string StateDetails = getTaskName();

  StateDetails = StateDetails + "::getStateDetails()" + '\n';

  std::map<std::string, std::string>::iterator it;

  for ( it = m_StateDetailItems.begin(); it != m_StateDetailItems.end(); ++it )
  {
    StateDetails = StateDetails + it->first + " : " + it->second + '\n';
  }

  return StateDetails;
}

//##ModelId=40EAA0930185
void cCBS_StdFrame_Task::getOwnStateDetails(std::string& details)
{
  cCBS_StdMutex Mutex("CBS_StdFrame_Task::StateDetails");

  std::ostringstream buf;

  buf << getTaskName() << "::getOwnStateDetails()" << '\n' << details << '\n' << getStateDetails() << std::ends;

  details = buf.str().c_str();
}

//##ModelId=40EAA093018A
cCBS_StdFrame_Task::~cCBS_StdFrame_Task()
{
  if ( m_pControlThread )
  {
    // terminates thread
    if (m_pControlThread->running())
    {
      m_pControlThread->setTerminateThread();
      m_pControlThread->waitForExit();
    }
    delete m_pControlThread;
    m_pControlThread = 0;
  }

  std::map<std::string, cCBS_StdTask*>::iterator it;
  for (it = m_SubTaskList.begin(); it != m_SubTaskList.end(); it++)
  {
    delete it->second;
  } // for ( it = m_SubTaskList.begin(); it < m_SubTaskList.end() it++ )

}

//##ModelId=40EAA093018D
cCBS_StdFrame_Task::cCBS_StdFrame_Task()
: m_pLogTask(0)
, m_InternalTraceLevel(0)
, m_pComponent(0)
, m_pControlThread(0)
{
}

//##ModelId=48A95F5500CE
void cCBS_StdFrame_Task::runControlThread()
{
  // Function called by the component on ownStartUp()

  // if time > 0 is set in ini file, control is active
  long ControlTime = -1;

  // first check general entries 
  // usable value is at least 20 secs
  cCBS_StdInitBase::getInstance()->replaceWithEntry("ProcessControl","ControlTime",ControlTime);

  // overwrite with task specific entries 
  std::string TaskName = getTaskName();
  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(),"ControlTime",ControlTime);

  if ( ControlTime > 0 && ! m_pControlThread )
  {
    std::stringstream Message;

    Message << "Starting control thread for Task " 
            << TaskName 
            << " using control time " 
            << ControlTime 
            << " (msecs) ";
    
    log(Message.str(),3);

    m_pControlThread = new cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread(this, ControlTime);
    m_pControlThread->setFreeOnTerminate(false);
    m_pControlThread->run();
  }
}


//##ModelId=48A95F550073
void cCBS_StdFrame_Task::terminateControlThread()
{
  // Function called by the component on ownRunDown() only
  if (m_pControlThread)
  {
    if (m_pControlThread->running())
    {
      m_pControlThread->setTerminateThread();
      m_pControlThread->waitForExit();
    }
  }
}


//##ModelId=40EAA093017F
void cCBS_StdFrame_Task::ownStartUp()
{
  cCBS_StdMutex Mutex("cCBS_StdFrame_Task::ownStartUp()");

  log(std::string(getTaskName()) + ": ownStartUp()",3);
  
  setWorking(true);

  // It's pure virtual
  //cCBS_StdTask::ownStartUp();

}

//##ModelId=40EAA0930182
void cCBS_StdFrame_Task::ownRunDown()
{
  log(std::string(getTaskName()) + ": ownRunDown()",3);

	setWorking(false);

  // It's pure virtual
  //cCBS_StdTask::ownRunDown();
}



//##ModelId=40EAA093018F
bool cCBS_StdFrame_Task::initialize()
{
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TRACING","TraceLevel",m_InternalTraceLevel);

  return cCBS_StdTask::initialize();
}



//##ModelId=40EBCAAD0024
cCBS_StdFrame_Task::cCBS_StdFrame_Task(cCBS_StdFrame* pApplication_Frame,int argc, const char *argv[])
:m_Application_Frame(pApplication_Frame)
{
  int i   = 0;

  m_argc = argc;
  
  m_argv = new const char*[argc];

  for ( i = 0 ; i < argc ; i++)
  {
    m_argv[i] = argv[i];
  }

}

//##ModelId=40EAA09301A1
std::string cCBS_StdFrame_Task::generateName(const std::string  & TaskName)
{
  std::string generatedName;

  // older version, look at [CORBA]
  cCBS_ConfigBase::getConfigBase()->getActGrpEle("CORBA", TaskName.c_str(), generatedName);

  // new version, look at [TASKS]
  cCBS_ConfigBase::getConfigBase()->getActGrpEle("TASKS", TaskName.c_str(), generatedName);

  // nothing found at inifile
  if (generatedName.empty())
  {
    generatedName = cCBS_StdInitBase::getInstance()->m_ServerName + TaskName;
  }

  return generatedName;
}




//##ModelId=410DFB3202CC
void cCBS_StdFrame_Task::registerSubTask(cCBS_StdTask* pTask, const std::string & TaskName)
{
  if ( pTask && !TaskName.empty() )
  {
    m_SubTaskList.insert(std::pair<std::string, cCBS_StdTask*>(TaskName, pTask));
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorTaskRegistration(Message);
  }
}



//##ModelId=410DFB58021C
void cCBS_StdFrame_Task::createSubtasks()
{
  CBS_TaskData taskData;

	taskData.critical     = true;
	taskData.autoRecovery = true;
	taskData.priority     = CBS_PrioNormal;

  std::map<std::string,cCBS_StdTask*>::iterator it;

  if (!m_SubTaskList.empty())
  {
    for ( it = m_SubTaskList.begin(); it != m_SubTaskList.end(); it++ )
    {
      std::string TaskName = it->first;
      cCBS_StdTask* pTask  = it->second;

      if(pTask) 
      {
        TaskName = generateName(TaskName);

        std::string Message("cCBS_StdFrame_Task::createSubtasks(): Activating Task : ");
        Message += TaskName;
        log(Message,3);

        if (pTask->activate(TaskName.c_str()))
        {
          addSubtask(pTask->getReference());

          pTask->startUp();
        }
        else
        {
          std::string Message("cCBS_StdFrame_Task::createSubtasks(): Task not activated : ");
          Message += TaskName;
          log(Message,1);
        }
      }
    } // for ( It = m_SubTaskList.begin(); It < m_SubTaskList.end() It++ )
  } // if (!m_SubTaskList.empty())
	
	cCBS_StdTask::createSubtasks();
}



//##ModelId=4149A0830208
void cCBS_StdFrame_Task::log(const std::string& Message, long Level)
{
  // store last XXX logs for state detail information
  cCBS_StdLog_Task::getInstance()->setStateDetails(Message);

  // log if trace level of actual Task => output level from message
  if ( (long)getTraceLevel() >= Level )
  {
    cCBS_StdLog_Task::getInstance()->writeLog(Message,Level);
  }
}


//##ModelId=4253E8DD038D
void cCBS_StdFrame_Task::doOnException(const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,"",Function.c_str(),Action.c_str());
}



//##ModelId=42724A0C00B3
bool cCBS_StdFrame_Task::isLoggingOn()
{
  bool RetValue = false;

  if( getTraceLevel() > 0 )
  {
    RetValue = true;
  }

  return RetValue;
}

//##ModelId=44FE88B2022A
long cCBS_StdFrame_Task::checkWorkingState()
{
  return getOwnWorkState();
}

//##ModelId=48A53B8E01AB
void cCBS_StdFrame_Task::doOnComponentStartup()
{
}

// search maximum of external(set via CBS_TaskViewer) and internal(set via ini file) trace level
//##ModelId=48A53B8E0238
unsigned long cCBS_StdFrame_Task::getTraceLevel()
{
  unsigned long RetValue = 0;

  if ( m_pComponent )
  {
    // use maximum of component or ini-file level as over-all value
    RetValue = max((long)m_pComponent->getTraceLevel(),m_InternalTraceLevel);
    
    // use task level to overwrite
    RetValue = max(cCBS_StdTask::getTraceLevel(),RetValue);
  }
  else
  {
    // use maximum of task or ini-file level
    RetValue = max((long)cCBS_StdTask::getTraceLevel(),m_InternalTraceLevel);
  }

  

  return RetValue;
}


//##ModelId=48A5407101DF
const cCBS_StdFrame_Component* cCBS_StdFrame_Task::getpComponent() const
{
	return m_pComponent;
}

//##ModelId=48A5407103DC
void cCBS_StdFrame_Task::setpComponent(cCBS_StdFrame_Component* value)
{
	m_pComponent = value;
	return;
}


//##ModelId=48A556380301
void cCBS_StdFrame_Task::control()
{
  if ( m_pControlThread )
  {
    m_pControlThread->control();
  }
}


//##ModelId=48A558E801CE
void cCBS_StdFrame_Task::uncontrol()
{
  if ( m_pControlThread )
  {
    m_pControlThread->uncontrol();
  }
}


// this method starts the control thread of the FrameComponent
// this thread will terminate the component / application after the configured control time for the components
// this will be done before eventlogs or tracelogs will be written
// this is because also file access might block the sytem at this state !
// please do not implement any logs from this point until the "EXIT" command in Frame component!
//##ModelId=48A56AE80317
void cCBS_StdFrame_Task::doOnThreadControlError()
{
  // The mutex is required to synchronize output of several control threads
  cCBS_StdMutex Mutex("cCBS_StdFrame_Task::doOnThreadControlError()");

// terminating process in RELEASED verions only !
#ifdef _DEBUG

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskControl(sMessage,getTaskName(),"ControlTime for TaskControl exceeded");
  pEventLog->EL_ErrorTaskControl(sMessage,getTaskName(),"No termination in DEBUG application");

  if ( m_pComponent )
  {
    m_pComponent->logStateDetails();
  }

#else

  // try to make some outputs before FrameComponents terminates the application
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskControl(sMessage,getTaskName(),"ControlTime for TaskControl exceeded");
  pEventLog->EL_ProcessTerminated(sMessage,cCBS_StdInitBase::getInstance()->m_ServerName.c_str(),"Fatal error !");

  // initializes control thread and terminates component immediately
  if ( m_pComponent )
  {
    m_pComponent->control(true);
  }

#endif

}

std::string cCBS_StdFrame_Task::getControlThreadStateDetails()
{
  std::string StateDetails;

  if (m_pControlThread)
  {
    StateDetails = '\n' + m_pControlThread->getStateDetails() + '\n';
  }
  else
  {
    StateDetails = "\nNo control thread activated\n";
  }
  return StateDetails;
}

// ******************************************************************
// ******************************************************************
// Thread handling
// ******************************************************************
// ******************************************************************

//##ModelId=48A552D7008E
cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::cCBS_StdFrame_TaskControlThread(cCBS_StdFrame_Task* pTask , long ControlTime)
: m_ControlTime(ControlTime)
, m_pTask(pTask)
, m_doControl(false)
{
  cCBS_Time::localTime(m_StartTime);
}

//##ModelId=48A552D700A6
cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::~cCBS_StdFrame_TaskControlThread()
{
}

//Virtual work method. Sleeps for the specified ControlTime and checks status 
//will run down task and component in case of errors
//##ModelId=48A552D700AC
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      performWorkingStep();
    }

    m_pTask->log(std::string("Request to terminate.") + m_pTask->getTaskName(),3);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::work()","performing Working Step");
  }
}


//##ModelId=48A559F7000F
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::terminate()
{
  setTerminateThread();
}



//##ModelId=48A55A91031B
std::string cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::getCurrentThreadId()
{
  std::stringstream Message;
  Message << GetCurrentThreadId() ;

  return Message.str();
}

//##ModelId=48A55A910325
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::logThreadInformation(const std::string& Message)
{
  std::stringstream LogMessage;
  LogMessage << Message << " thread " << getCurrentThreadId() ;

  if ( m_pTask )
  {
    m_pTask->log(LogMessage.str(),3);
  }
}

//##ModelId=48A55A910307
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::performWorkingStep()
{
  try
  {
    if ( !getTerminateThread() )
    {
      if ( m_doControl == true )
      {
        // calculate time between now and last thread start time
        CBS_LocalTime Now;
        cCBS_Time::localTime(Now);

        long DiffTime = cCBS_Time::diffTime(Now,m_StartTime);

        if ( DiffTime > m_ControlTime  )
        {
          if (m_pTask)
          {
            // call error handling method and uncontrol thread
            // doOnThreadControlError is virtual and may have different implementations at each task
            m_pTask->doOnThreadControlError();

            uncontrol();
          }
        }
      }
    }

    // sleep for some seconds, in general 1000 times per Control Cycle but at least 200 msecs !
    long doSleep = max(200,long(m_ControlTime/1000) );
    sleep(doSleep);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }
}


//##ModelId=48A95F55024A
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::control()
{
  cCBS_Time::localTime(m_StartTime);
	m_doControl = true;
}

//##ModelId=48A95F550268
void cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::uncontrol()
{
	m_doControl = false;
}

std::string cCBS_StdFrame_Task::cCBS_StdFrame_TaskControlThread::getStateDetails()
{
  std::string RetValue = m_pTask->getTaskName();
  RetValue += "::ControlThread::No details";
	return RetValue;
}


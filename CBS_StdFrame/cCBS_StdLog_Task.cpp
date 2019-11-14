// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <sstream>

#include "cCBS_EventLog.h"

#include "cCBS_StdFrame_TaskController.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdLogHandlerAdapter.h"
#include "cCBS_StdLogHandler.h"

//##ModelId=410A4564018E
cCBS_StdLog_Task* cCBS_StdLog_Task::m_Instance = 0;


void cCBS_StdLog_Task::setStateDetails(const std::string& value)
{
  cCBS_StdMutex CBS_StdMutex("m_LogDetailItems");

  if ( m_LogDetailEntries > 0 )
  {
    std::string tmpTime = getCurrentTimeAsString(); 

    m_LogDetailItems.push_back(tmpTime + " " + value);

    if ( (long)m_LogDetailItems.size() > m_LogDetailEntries )
    {
      m_LogDetailItems.erase(m_LogDetailItems.begin()); 
    }
  }
}

std::string cCBS_StdLog_Task::getStateDetails()
{
  cCBS_StdMutex CBS_StdMutex("m_LogDetailItems");

  std::string StateDetails = getTaskName();

  StateDetails = StateDetails + "::getStateDetails()" + "\n";

  // read last log entries from internal list
  std::vector<std::string>::iterator it;

  for ( it = m_LogDetailItems.begin() ; it != m_LogDetailItems.end() ; ++it )
  {
    StateDetails += (*it) + '\n';
  }


  return StateDetails;

}

//##ModelId=410A44F20146
void cCBS_StdLog_Task::getOwnStateDetails(std::string& details)
{
  std::ostringstream buf;

  cCBS_StdFrame_Task::getOwnStateDetails(details);

  buf << details << '\n';

  if (m_pLogHandlerAdapter)
  {
    long qzize = m_pLogHandlerAdapter->getLogHandler().front()->getQueueSize();
    if ( qzize > -1)
    {
      std::vector<cCBS_StdLogHandler*> &t = m_pLogHandlerAdapter->getLogHandler();
      std::vector<cCBS_StdLogHandler*>::iterator i;
      i = t.begin();
      while (i != t.end())
      {
        buf << "cCBS_StdLogHandler::Queue size: " << (*i)->getQueueSize() << '\n';
        i++;
      }
    }
  }

  details = buf.str().c_str();
}

//##ModelId=410A455C027D
 cCBS_StdLog_Task* cCBS_StdLog_Task::getInstance() 
{
	if ( m_Instance == 0 )
	{
		m_Instance = new cCBS_StdLog_Task( );
	}

	return m_Instance;

}

//##ModelId=410A457401CD
cCBS_StdLog_Task::cCBS_StdLog_Task()
: m_pLogHandlerAdapter(0)
, m_pCBS_EventLog(0)
, m_SeverityList(0)
, m_ReminderTime(0)
, m_LogDetailEntries(0)
{
  m_pLogHandlerAdapter = new cCBS_StdLogHandlerAdapter();
}

//##ModelId=410A4575011B
cCBS_StdLog_Task::~cCBS_StdLog_Task()
{
  if( m_pLogHandlerAdapter )
    delete m_pLogHandlerAdapter;

  if (m_pCBS_EventLog)
    delete m_pCBS_EventLog;

  m_SeverityList.erase(m_SeverityList.begin(),m_SeverityList.end());
}

//##ModelId=410A44F40074
bool cCBS_StdLog_Task::initialize()
{
  cCBS_StdFrame_Task::initialize();

  log("cCBS_StdLog_Task: initialize()",3);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","ServiceName",m_ServiceName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","ContextName",m_ContextName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","ServiceName2",m_ServiceName2);


  m_ReminderTime        = 20000;
  m_LogDetailEntries    = 10;
  m_EventLogPlantUnit   = getEventLogProcessName();
  m_EventLogLocation    = getEventLogProcessName();
  m_EventLogAggregate   = getEventLogProcessName();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","PlantUnit",m_EventLogPlantUnit);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","Location",m_EventLogLocation);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","Aggregate",m_EventLogAggregate);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","ReminderTime",m_ReminderTime);

  cCBS_StdInitBase::getInstance()->replaceWithEntry("TRACING","LogDetailEntries",m_LogDetailEntries);

  std::vector<std::string>::iterator it;
  std::string ServiceName = "TestmessageServer";
  std::string ServiceName2;
  std::string ContextName;
  bool RunTestLog = true;

  // preset severity list
  m_SeverityList.push_back("FATAL_ERROR");
  m_SeverityList.push_back("ERROR");
  m_SeverityList.push_back("WARNING");
  m_SeverityList.push_back("INFO");
  m_SeverityList.push_back("TEST");

  // check if inifile entries for test eventlog are configured
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TESTLOG","ServiceName",ServiceName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TESTLOG","ServiceName2",ServiceName2);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TESTLOG","ContextName",ContextName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TESTLOG","SeverityList",m_SeverityList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("TESTLOG","Run",RunTestLog);

  // instantiation of second eventlogserver connection !!!!
  if (RunTestLog)
  {
    m_pCBS_EventLog = new cCBS_EventLog(getEventLogProcessName(),ServiceName,ContextName,"",ServiceName2);
  }

  return true;
}


//##ModelId=411A40F7012A
void cCBS_StdLog_Task::registerLogHandler(cCBS_StdLogHandler* MessageHandler)
{
  if (m_pLogHandlerAdapter)
  {
    m_pLogHandlerAdapter->registerLogHandler(MessageHandler);
  }	
}



//##ModelId=414AB3D80190
void cCBS_StdLog_Task::writeToLogHandler(const std::string& Message, long level)
{
  if (m_pLogHandlerAdapter)
  {
    m_pLogHandlerAdapter->log(Message, level);
  }	
}



//##ModelId=414AB55201E5
void cCBS_StdLog_Task::log(const std::string& Message, long Level)
{
  cCBS_StdFrame_Task::log(Message, Level);
}


void cCBS_StdLog_Task::logStateDetails(long Level)
{
  // log if trace level of actual Task => output level from message
  if ( (long)getTraceLevel() >= Level )
  {
    std::string Message = getStateDetails();

    writeLog(Message,Level);
  }
}

//##ModelId=42B7C6D700BC
void cCBS_StdLog_Task::writeLog(const std::string& Message, long Level)
{
  cCBS_StdMutex Mutex("cCBS_StdLog_Task::writeLog()");

  // instantiating task controller
  // will work in RELEASED version only !
  // terminates task AND component, if execution of event will take longer than
  // configured time from [ProcessControl] ControlTime = ...
  cCBS_StdFrame_TaskController Controller( this );

  std::stringstream LogMessage;

  switch (Level)
  {
      case 1:
        {
          LogMessage << "E";
          break;
        }
      case 2:
        {
          LogMessage << "W";
          break;
        }
      case 3:
        {
          LogMessage << "I";
          break;
        }
      default : 
        {
          LogMessage << Level;
          break;
        }
  }

  LogMessage << " : " << Message;

  // moved to FrameTask
  // setStateDetails("cCBS_StdLog_Task::writeLog", LogMessage.str() );

  writeToLogHandler(LogMessage.str(), Level);

  writeToConsole(LogMessage.str());
}


//##ModelId=41FF414901E3
void cCBS_StdLog_Task::writeToConsole(const std::string& Message)
{
  std::cout << Message << std::endl;
}


//##ModelId=42C922BA03DA
std::string cCBS_StdLog_Task::getEventLogProcessName()
{
  return cCBS_StdInitBase::getInstance()->m_ServerName;
}

//##ModelId=42C922BB001A
std::string cCBS_StdLog_Task::getEventLogServiceName()
{
  return m_ServiceName;
}

std::string cCBS_StdLog_Task::getEventLogServiceName2()
{
  return m_ServiceName2;
}

//##ModelId=42C922BB0038
std::string cCBS_StdLog_Task::getEventLogContextName()
{
  return m_ContextName;
}

//##ModelId=48A53B8D01EE
long cCBS_StdLog_Task::getReminderTime()
{
  return m_ReminderTime;
}



//##ModelId=43FC5016018E
long cCBS_StdLog_Task::sendEventLogMessage(sEventLogMessage& EventLogMessage)
{
  long RetValue = -1;

  if (m_pCBS_EventLog && checkSeverity(m_SeverityList,EventLogMessage.severity) )
  {
    RetValue = m_pCBS_EventLog->sendMessage(EventLogMessage);
  }
	return RetValue;
}



//##ModelId=43FC68920187
bool cCBS_StdLog_Task::checkSeverity(std::vector<std::string>& SeverityList, long Severity)
{
  bool RetValue = false;

  std::vector<std::string>::iterator it;

  if ( SeverityList.empty() )
  {
    RetValue = true;
  }
  else    // check list entries against actual severity, if identical send eventlog
  {
    std::string Sev;

    switch (Severity)
    {
      case c_e_fatal:
        {
          Sev = "FATAL_ERROR";  
          break;
        }
      case c_e_error:
        {
          Sev = "ERROR";
          break;
        }
      case c_e_warning:
        {
          Sev = "WARNING";
          break;
        }
      case c_e_info:
        {
          Sev = "INFO";  
          break;
        }
      case c_e_test:
        {
          Sev = "TEST";
          break;
        }

      default : 
        {
          Sev = "INFO";
          break;
        }
    }

    for ( it = SeverityList.begin() ; it != SeverityList.end() ; ++it )
    {
      if ( Sev == (*it) )
      {
        RetValue = true;
        break;
      }
    }
  }

  return RetValue;
}

//##ModelId=445EF9E70148
std::string cCBS_StdLog_Task::getEventLogPlantUnit()
{
  return m_EventLogPlantUnit;
}

//##ModelId=48A53B8D0189
std::string cCBS_StdLog_Task::getEventLogAggregate()
{
  return m_EventLogAggregate;
}
//##ModelId=445EF9E7018F
std::string cCBS_StdLog_Task::getEventLogLocation()
{
  return m_EventLogLocation;
}

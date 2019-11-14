// Copyright (C) 1999 - 2004 SMS Demag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <sstream>

#include "cCBS_Time.h"

#include "cCBS_EventLogMessage.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdMutex.h"

#include "cCBS_StdEventLog.h"


cCBS_StdEventLog::~cCBS_StdEventLog()
{
}

cCBS_StdEventLog::cCBS_StdEventLog()
: cCBS_EventLog(cCBS_StdEventLog::getProcessName(),
                cCBS_StdEventLog::getServiceName(),
                cCBS_StdEventLog::getContextName())
, m_SeverityList(0)
{
  init();
}

cCBS_StdEventLog::cCBS_StdEventLog(std::string ProcessName, std::string ServiceName, std::string ContextName  )
: cCBS_EventLog(ProcessName, ServiceName, ContextName,"",cCBS_StdLog_Task::getInstance()->getEventLogServiceName2())
, m_SeverityList(0)                
{
  init();
}

cCBS_StdEventLog::cCBS_StdEventLog(int ac, char **av, const char *location)
: cCBS_EventLog(ac, av)
, m_SeverityList(0)
{
  init();
}
 
// now connectServerByNS will be done at LogTask
void cCBS_StdEventLog::init()
{
  // preset entries for valid severity to be send to eventlogserver
  m_SeverityList.push_back("FATAL_ERROR");
  m_SeverityList.push_back("ERROR");
  m_SeverityList.push_back("WARNING");
  m_SeverityList.push_back("INFO");

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","SeverityList",m_SeverityList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","EventIdList",m_EventIdList);

  // connect to EventLogServer
  connectServerByNS();
}

void cCBS_StdEventLog::initDestination()
{
  // extend already known destinations from ini file
  std::vector<std::string> m_DestinationList;
  std::vector<std::string>::iterator it ;

  if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","DestinationList",m_DestinationList) )
  {
    //Settings for dedicated events
    //DestinationList = Dest1, Dest2    defining free additional destinatons
    //                                  according to Syntax given by CBS Event
    //                                  Log Systems EXCEL definition files(bit pattern)
    //Dest1 = 101000001                 (reading from right to left)
    //Dest2 = 101000011                 (reading from right to left)
    //AOD_BottomLine = AOD_1BottomLine  redirects event log to already defined destination
    //AOD_BottomLine = Dest1            redirects event log to addition defined destination

    for ( it = m_DestinationList.begin() ; it != m_DestinationList.end() ; ++it)
    {
      std::string DestinationName = (*it);

      // local copy necessary for use of reverse_iterator
      std::string DestinationValue;

      if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG",DestinationName,DestinationValue) )
      {
        // convert bits to respective long value 
        std::basic_string<char>::reverse_iterator it;

        long long lDestination = -1;
        resetBits(lDestination);

        // local copy necessary for use of reverse_iterator
        std::string strDestination = DestinationValue;

        short index = 0;
        for ( it = strDestination.rbegin(); it != strDestination.rend(); ++it)
        {
          if ( *it == '1' ) // check for character not for string like == "1"
          {
            setBit(lDestination,index,true);
          }

          index++;
        }

        setDestinationListEntry(DestinationName, lDestination);

      } // if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG",DestinationName,DestinationValue) )
    }
  }

  // now find destination replacements
  // check if members of m_DestCodeList have ini file entries
  std::map<std::string,long long>::iterator itDestCode;
  for ( itDestCode = m_DestCodeList.begin() ; itDestCode != m_DestCodeList.end() ; ++itDestCode)
  {
    std::string DestinationName   = itDestCode->first;
    long long DestinationValue    = itDestCode->second;
    std::string ReplaceName;

    if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG",DestinationName,ReplaceName) )
    {
      long long ReplaceValue = getDestination(ReplaceName);
      
      if ( ReplaceValue > -1 )
      {
        m_ReplaceList.insert( std::pair<long long,long long>(DestinationValue,ReplaceValue));
      }
    }
  }

  // connect to EventLogServer
  connectServerByNS();
}

long cCBS_StdEventLog::sendMessage(sEventLogMessage& EventLogMessage)
{
  long RetValue   = -1;
  
  try
  {
    log(EventLogMessage);

    // set general message information
    changeEventLogMessage(EventLogMessage);

    // check if EventLog should be recalled in case of operator acknowlage!
    if ( EventLogMessage.opAckn == 1 )
    {
      if ( checkSeverity(EventLogMessage.severity))
      {
        // send event to event log server
        // eventlog will be send only once in an 20 seconds interval

        log("calling m_EventLogCyclicReminder.sendMessage(EventLogMessage,getReminderTime());", 4);

        m_EventLogCyclicReminder.sendMessage(EventLogMessage,getReminderTime());
      }

      RetValue = true;

    }
    else
    {

      if ( checkSeverity(EventLogMessage.severity))
      {
        // send event to event log server for processs messages
        log("cCBS_StdEventLog::sendMessage(sEventLogMessage& EventLogMessage) - calling cCBS_EventLog::sendMessage(EventLogMessage);", 4);

        RetValue = cCBS_EventLog::sendMessage(EventLogMessage);
      }
    }

    // send event to event log server for analysis messages
    RetValue = cCBS_StdLog_Task::getInstance()->sendEventLogMessage(EventLogMessage);

  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(Message, "Unknown exception", "cCBS_StdEventLog::send_message", "");
  }

	return RetValue;
} 


long cCBS_StdEventLog::sendMessage()
{
  return sendMessage(m_EventLogMessage);
}

// write values from ini file to EventLogMessage
void cCBS_StdEventLog::changeEventLogMessage(sEventLogMessage & EventLogMessage)
{
  // read from [EVENTLOG] PlantUnit,Aggregate and Location
  std::string PlantUnit = getEventLogPlantUnit();
  std::string Aggregate = getEventLogAggregate();
  std::string Location  = getEventLogLocation(); // will appear as LOCATION at CBS EventLogGUI

  long long Destination   = EventLogMessage.destination;
  long long OpAckn        = EventLogMessage.opAckn;
  long EventId            = EventLogMessage.eventId;
  long Severity           = EventLogMessage.severity;
  std::string Spare1      = EventLogMessage.spare1;
  std::string Spare2      = EventLogMessage.spare2;
  std::string Spare3      = EventLogMessage.spare3;
  bool ReplaceStaticPlantUnit = false;// per default the plant unit will be used from getEventLogPlantUnit() 

  // prepare EventId to be used as string !
  std::stringstream id;
  id << EventId;
  std::string strEventId  = id.str();

  // replace dedicated destinations only
  cCBS_StdInitBase::getInstance()->getEntry("EVENTLOG","Destination",Destination);
  cCBS_StdInitBase::getInstance()->getEntry("EVENTLOG", "ReplacePlantUnit", ReplaceStaticPlantUnit);

  // keep the plant unit in event log message,
  // if replace of static plant unit is required and
  // plantUnit in event log message is not empty
  if (ReplaceStaticPlantUnit
    && !EventLogMessage.plantUnit.empty()
    )
  {
    PlantUnit = EventLogMessage.plantUnit;
  }

  // searching in m_ReplaceList
  // try to find entry for destination and replace destination with defined value
  long long ReplacedDest = getReplacedDestination(Destination);
  if ( ReplacedDest > -1 )
  {
    Destination = ReplacedDest;
  }

  // look for id related settings to change eventlog data
  // entry can be as follows

  // [EVENTLOG]
  // EventIdList = 11002
  // [11002]
  // Location = Tracking
  // Severity = 1 // c_e_info ... 0 = c_e_test up to 4 = c_e_fatal
  // OpAckn = 1

  // precheck to keep performance
  // returns true if strEventId is in ini file entry of "EVENTLOG","EventIdList"
  if ( checkEventIdList(strEventId) )
  {
    std::string BlockName = strEventId;

    // now search for entries for respective EventLogId as BlockName
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Location",Location);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Severity",Severity);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Destination",Destination);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"OpAckn",OpAckn);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare1",Spare1);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare2",Spare2);
    cCBS_StdInitBase::getInstance()->replaceWithEntry(BlockName,"Spare3",Spare3);
  }
  
  // overwrite values
  EventLogMessage.plantUnit       = PlantUnit;
  EventLogMessage.aggregate       = Aggregate;
  EventLogMessage.originLocation  = Location;
  EventLogMessage.destination     = Destination;
  EventLogMessage.opAckn          = OpAckn;
  EventLogMessage.spare1          = Spare1;
  EventLogMessage.spare2          = Spare2;
  EventLogMessage.spare3          = Spare3;

  switch (Severity)
  {
    case 0:
      {
        EventLogMessage.severity        = c_e_test;
        break;
      }
    case 1:
      {
        EventLogMessage.severity        = c_e_info;
        break;
      }
    case 2:
      {
        EventLogMessage.severity        = c_e_warning;
        break;
      }
    case 3:
      {
        EventLogMessage.severity        = c_e_error;
        break;
      }

    case 4:
      {
        EventLogMessage.severity        = c_e_fatal;
        break;
      }
    default : 
      {
        EventLogMessage.severity        = c_e_test;
        break;
      }
  }// switch (Severity)}

  // extend Message with external HeatID and ProcessState if required
  bool extendMessage = false;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("EVENTLOG","ExtendMessage",extendMessage);

  if (extendMessage)
  {
    std::stringstream extendedMessage;

    if ( !EventLogMessage.productId.empty() )
    {
      extendedMessage << EventLogMessage.productId << " " ;
    }
  
    if ( !EventLogMessage.processState.empty() )
    {
      extendedMessage << EventLogMessage.processState << " " ;
    }

    if ( extendedMessage.str().size() > 0 )
    {
      extendedMessage << EventLogMessage.messageText;

      EventLogMessage.messageText = extendedMessage.str();
    }

  }


  cCBS_Time::localTime(EventLogMessage.applDateTime);

}


std::string cCBS_StdEventLog::getEventLogPlantUnit()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogPlantUnit();
}

std::string cCBS_StdEventLog::getEventLogAggregate()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogAggregate();
}


std::string cCBS_StdEventLog::getEventLogLocation()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogLocation();
}


std::string cCBS_StdEventLog::getProcessName()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogProcessName();
}

std::string cCBS_StdEventLog::getServiceName()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogServiceName();
}

std::string cCBS_StdEventLog::getContextName()
{
  return cCBS_StdLog_Task::getInstance()->getEventLogContextName();
}

long cCBS_StdEventLog::getReminderTime()
{
  return cCBS_StdLog_Task::getInstance()->getReminderTime();
}


sEventLogMessage cCBS_StdEventLog::initMessage(const std::string& File, long Line, long long Destination)
{
  sEventLogMessage LogMessage;

  // init LogMessage
  LogMessage.severity     = c_e_test;
  LogMessage.language     = 1;

  LogMessage.eventId      = 0;

  LogMessage.destination  = 0;
  LogMessage.opAckn       = 0;


  // write file and line information to spare1
  if ( !File.empty() ) 
  {
    std::stringstream SourceInfo;
    SourceInfo << "File : " << File << " Line : " << Line ;

    LogMessage.spare1 = SourceInfo.str();
  }

  // overwrite destination
  if ( Destination >= 0 )
  {
    LogMessage.destination = Destination;
  }

  return LogMessage;

}

sEventLogMessage cCBS_StdEventLog::initMessage(const std::string& File, long Line, const std::string& Destination)
{
  long long lDestination = -1;

  std::basic_string<char>::reverse_iterator it;
  
  // local copy necessary for use of reverse_iterator
  std::string strDestination = Destination;

  // search entries of type "1" at Destination, e.g. "000000011" == "3"
  if ( !strDestination.empty() )
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    pEventLog->resetBits(lDestination);

    short index = 0;
    for ( it = strDestination.rbegin(); it != strDestination.rend(); ++it)
    {
      if ( *it == '1' ) // check for character not for string like == "1"
      {
        pEventLog->setBit(lDestination,index,true);
      }

      index++;
    }
  }

  return cCBS_StdEventLog::initMessage( File, Line, lDestination);
}




bool cCBS_StdEventLog::checkSeverity(long Severity)
{
  return cCBS_StdLog_Task::getInstance()->checkSeverity(m_SeverityList,Severity);
}

bool cCBS_StdEventLog::checkEventIdList(std::string EventId)
{
  bool RetValue = false;

  std::vector<std::string>::iterator it;

  for ( it = m_EventIdList.begin() ; it != m_EventIdList.end() ; ++it )
  {
    if ( EventId == (*it) )
    {
      RetValue = true;
      break;
    }
  }

  return RetValue;
}




sEventLogMessage cCBS_StdEventLog::initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal /* = "" */)
{
  sEventLogMessage LogMessage = initMessage(File,Line);

  LogMessage.processState = ProcessState;
  LogMessage.productId    = ProductIDExternal;
  LogMessage.spare2       = ProductIDInternal;

  return LogMessage;
}

sEventLogMessage cCBS_StdEventLog::initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal, long Destination, const std::string& Spare3)
{
  sEventLogMessage LogMessage = initMessage(File,Line,Destination);

  LogMessage.processState = ProcessState;
  LogMessage.productId    = ProductIDExternal;
  LogMessage.spare2       = ProductIDInternal;
  LogMessage.spare3       = Spare3;

  return LogMessage;
}

sEventLogMessage cCBS_StdEventLog::initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal, const std::string& Destination, const std::string& Spare3)
{
  sEventLogMessage LogMessage = initMessage(File,Line,Destination);

  LogMessage.processState = ProcessState;
  LogMessage.productId    = ProductIDExternal;
  LogMessage.spare2       = ProductIDInternal;
  LogMessage.spare3       = Spare3;

  return LogMessage;
}


void cCBS_StdEventLog::setDestinationListEntry(const std::string& Destination, long long value)
{
  m_DestCodeList.insert( std::pair<std::string,long long>(Destination,value));
}

long long cCBS_StdEventLog::getDestination(const std::string& Destination)
{
  long long RetValue = -1;

  std::map<std::string,long long>::iterator it;

  it = m_DestCodeList.find(Destination);

  if ( it != m_DestCodeList.end() )
  {
    RetValue = it->second;
  }

  return RetValue;
}

long long cCBS_StdEventLog::getReplacedDestination(long long Value)
{
  long long RetValue = -1;

  std::map<long long,long long>::iterator it;

  it = m_ReplaceList.find(Value);

  if ( it != m_ReplaceList.end() )
  {
    RetValue = it->second;
  }

  return RetValue;
}

void cCBS_StdEventLog::log(sEventLogMessage & EventLogMessage)
{
  long TraceLevel = 5;
  std::string Severity;

  // set leading message information and check if message should be send regarding TraceLevel
  switch (EventLogMessage.severity)
  {
    case c_e_fatal:
      {
        Severity   = "FATAL_ERROR";  
        TraceLevel = 0;
        break;
      }
    case c_e_error:
      {
        Severity   = "ERROR";
        TraceLevel = 1;
        break;
      }
    case c_e_warning:
      {
        Severity   = "WARNING";
        TraceLevel = 2;
        break;
      }
    case c_e_info:
      {
        Severity   = "INFO";  
        TraceLevel = 3;
        break;
      }
    case c_e_test:
      {
        Severity   = "TEST";
        TraceLevel = 4;
        break;
      }

    default : 
      {
        Severity   = "INFO";
        TraceLevel = 3;
        break;
      }
  }

  if (cCBS_StdLog_Task::getInstance()->getTraceLevel() >= TraceLevel) 
  {
    std::ostringstream Message;
    Message << EventLogMessage.eventId      << " " ;
    Message << Severity                     << " " ; 
    Message << EventLogMessage.productId    << " " ;
    Message << EventLogMessage.processState << " " ;
    Message << EventLogMessage.messageText  << " " ; 
    Message << EventLogMessage.spare1       << " " ;

    cCBS_StdLog_Task::getInstance()->log(Message.str(),TraceLevel);
  }
}

void cCBS_StdEventLog::log(const std::string & Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message, Level);
}


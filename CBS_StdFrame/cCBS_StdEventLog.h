// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTLOG_40EE9AC8030E_INCLUDED
#define _INC_CEVENTLOG_40EE9AC8030E_INCLUDED

#include <string>
#include "cCBS_EventLog.h"
#include "cCBS_StdEventLogCyclicReminder.h"

class cCBS_StdLog_Task;

//Class providing CBS EventLog functionalities
class cCBS_StdEventLog : public cCBS_EventLog
{
private:
	std::vector<std::string> m_SeverityList;
	std::vector<std::string> m_EventIdList;

  cCBS_StdEventLogCyclicReminder m_EventLogCyclicReminder;

  std::map<std::string,long long> m_DestCodeList;
  std::map<long long, long long> m_ReplaceList;
  long long getReplacedDestination(long long Value);

  // to be independent of old style of event logs and event log server v1
  // original definition was in errorlog.h from CBS
  enum {E_TEST=0, E_INFO=8,E_WARNING=16, E_ERROR=24, E_FATAL_ERROR=40};

protected:
	virtual void changeEventLogMessage(sEventLogMessage & EventLogMessage);

	cCBS_StdEventLog(std::string ProcessName  , std::string ServiceName = "", std::string ContextName = ""  );

  cCBS_StdEventLog(int ac, char **av, const char *location);


  void init();

public:

  long long getDestination(const std::string& Destination);

	static sEventLogMessage initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal );

	static sEventLogMessage initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal, long Destination, const std::string& Spare3 = "");

	static sEventLogMessage initMessage(const std::string& File, long Line, const std::string& ProcessState, const std::string& ProductIDInternal, const std::string& ProductIDExternal, const std::string& Destination, const std::string& Spare3 = "");

	static sEventLogMessage initMessage(const std::string& File, long Line, const std::string& Destination);
	
	static sEventLogMessage initMessage(const std::string& File, long Line, long long Destination = -1);

	bool checkSeverity(long Severity);

  bool checkEventIdList(std::string EventId);

	virtual long sendMessage();

	virtual long sendMessage(sEventLogMessage& EventLogMessage);

	cCBS_StdEventLog();

	static std::string getEventLogPlantUnit();

  static std::string getEventLogAggregate();

	static std::string getEventLogLocation();

	static std::string getProcessName();

	static std::string getServiceName();

	static std::string getContextName();

	static long getReminderTime();

	virtual ~cCBS_StdEventLog();

  void setDestinationListEntry(const std::string& Destination, long long value);
  void initDestination();

  void log(sEventLogMessage & EventLogMessage);

  void log(const std::string & Message, long Level);

};

#endif /* _INC_CEVENTLOG_40EE9AC8030E_INCLUDED */

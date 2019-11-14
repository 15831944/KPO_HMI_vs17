// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_LOGTASK_410A44C8012F_INCLUDED
#define _INC_CCBS_LOGTASK_410A44C8012F_INCLUDED

#include "cCBS_StdFrame_Task.h"

class cCBS_StdLogHandlerAdapter;
class cCBS_StdLogHandler;
class cCBS_EventLog;

//class providing all trace logging and CBS EventLog 
//functionality
//##ModelId=410A44C8012F
class cCBS_StdLog_Task 
: public cCBS_StdFrame_Task
{
public:
	//##ModelId=43FC68920187
	bool checkSeverity(std::vector<std::string>  & SeverityList, long Severity);

	//##ModelId=43FC5016018E
	long sendEventLogMessage(sEventLogMessage& EventLogMessage);

	//##ModelId=42C922BA03DA
	std::string getEventLogProcessName();


	std::string getEventLogAggregate();

	//##ModelId=445EF9E70148
	std::string getEventLogPlantUnit();
	//##ModelId=445EF9E7018F
	std::string getEventLogLocation();

	//##ModelId=42C922BB001A
	std::string getEventLogServiceName();

  // returns the name of the second name service
	std::string getEventLogServiceName2();

	//##ModelId=42C922BB0038
	std::string getEventLogContextName();

	long getReminderTime();

	//##ModelId=42B7C6D700BC
	virtual void writeLog(const std::string& Message, long Level);

	//##ModelId=41FF414901E3
	void writeToConsole(const std::string& Message);

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	//##ModelId=414AB55201E5
	virtual void log(const std::string& Message, long Level);

  virtual void logStateDetails(long Level);

	//Dirceting Task relevant programming outputs to 
	//LogHandlerAdapter.
	//##ModelId=414AB3D80190
	void writeToLogHandler(const std::string& Message, long level);

	//Register LogHandler (derived form cCBS_StdLogHandler) 
	//at LogHandlerAdapter. Log Messages will be directed to 
	//all registered LogHandlers by the LogHandlerAdapter.
	//##ModelId=411A40F7012A
	void registerLogHandler(cCBS_StdLogHandler* MessageHandler);

	//##ModelId=410A44F20146
	virtual void getOwnStateDetails(std::string& details);

	//Returning valid pointer to class if instatiated.
	//##ModelId=410A455C027D
	static cCBS_StdLog_Task* getInstance();


	//##ModelId=410A4575011B
	virtual ~cCBS_StdLog_Task();

  void setStateDetails(const std::string& value);

  virtual std::string getStateDetails();

protected:
	//##ModelId=410A457401CD
	cCBS_StdLog_Task();
	//Pointer to class itself, will be usable after 
	//instantiation of the class
	//##ModelId=410A4564018E
	static cCBS_StdLog_Task* m_Instance;


	//##ModelId=411A19FB00E7
	cCBS_StdLogHandlerAdapter* m_pLogHandlerAdapter;

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=410A44F40074
	virtual bool initialize();

private:

	//##ModelId=43FC680303DA
	std::vector<std::string> m_SeverityList;

	//##ModelId=43FC4FE302F3
	cCBS_EventLog* m_pCBS_EventLog;

	//##ModelId=42DFAA45012C
	std::string m_ProcessName;

	// corba objectname of EventLogServer 
	std::string m_ServiceName;

	// corba objectname of EventLogServer2 
	std::string m_ServiceName2;

  // context name for NamingService 
	std::string m_ContextName;

  long m_ReminderTime;

  long m_LogDetailEntries;

  std::string m_EventLogPlantUnit;
  std::string m_EventLogLocation;
  std::string m_EventLogAggregate;

  std::vector<std::string> m_LogDetailItems;
};

#endif /* _INC_CCBS_LOGTASK_410A44C8012F_INCLUDED */

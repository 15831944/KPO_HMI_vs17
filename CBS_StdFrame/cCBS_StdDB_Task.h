// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDB_TASK_40850C0D01E1_INCLUDED
#define _INC_CDB_TASK_40850C0D01E1_INCLUDED

#include <windows.h>
#include <sql.h>

#include "CBS_StdAPI.h"
#include "cCBS_Connection.h"
#include "cCBS_ODBCDriver.h"
#include "cCBS_DriverManager.h"

#include "cCBS_StdConnection.h"
#include "cCBS_StdFrame_Task.h"

class cCBS_DBExc;
class cCBS_StdDB_Task : public cCBS_StdFrame_Task
  
{
private:
	//List containing all activated connections. A connection 
	//will be used only once!
	std::vector<cCBS_StdConnection*>  m_ConnectionList;

  class cCBS_StdDB_TaskControlThread 
  : public cCBS_StdFrame_TaskControlThread
  {
  public:
    std::string m_URL;
    std::string m_DBUser;
    std::string m_DBPassword;

    virtual std::string getStateDetails();

		cCBS_StdDB_TaskControlThread(cCBS_StdDB_Task* pTask , long ControlTime);
  };

public:
	virtual void doOnComponentStartup();

	void runControlThread();

	void freeConnections();

	void freeConnection(const std::string  & Url,  const std::string  & Login,  const std::string  & Password);

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string & Message, long Level);

  bool checkConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password);


	//Returning pointer to valid connection depending on URL, 
	//User and Password.
	cCBS_Connection* getConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password);

	cCBS_StdConnection* getCBS_StdConnection( const std::string  & Url,  const std::string  & Login,  const std::string  & Password);

  cCBS_StdConnection* getCBS_StdConnection(cCBS_Connection* pConnection);

	//Returning valid pointer to class if instatiated.
	static  cCBS_StdDB_Task* getInstance();


	virtual ~cCBS_StdDB_Task();


protected:
	void doOnCBS_DBExcConnectionError(cCBS_DBExc &ex, const std::string &url, const std::string &user, const std::string &passwd);
	void doOnCBS_DBExcConnectionError(cCBS_DBExc &ex, cCBS_StdConnection* pConnection);

	//Pointer to class itself, will be usable after 
	//instantiation of the class
	static cCBS_StdDB_Task * m_Instance;
	cCBS_StdDB_Task();


	//Adding connection to ConnectionList
	void registerConnection(cCBS_StdConnection * Connection);
	//Searching already opended connection in ConnectionList
	cCBS_StdConnection* findConnection(const std::string  & Url, const std::string  & Login, const std::string  & Password, bool Reconnect = false);

	cCBS_ODBCDriver* m_pODBCDriver;

	cCBS_DriverManager m_DriverManager;

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.
	virtual void ownStartUp();

	//Virtual task run down method. Called by the runDown 
	//method before stopping the subtasks. The default 
	//implementation sets only the state of the task to 
	//NotRunning. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would stop thread execution.
	virtual void ownRunDown();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

};

#endif /* _INC_CDB_TASK_40850C0D01E1_INCLUDED */

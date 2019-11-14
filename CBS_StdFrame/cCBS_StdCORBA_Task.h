// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCORBA_TASK_4084F87B0161_INCLUDED
#define _INC_CCORBA_TASK_4084F87B0161_INCLUDED

#include "CBS_Component_s.hh"
#include "CBS_Tasks_s.hh"

#include "cCBS_StdCORBA_ServerTask.h"
#include "cCBS_StdCORBA_ClientTask.h"
#include "cCBS_StdFrame_Task.h"

#include "cCBS_ProxyBase.h"


//Class providing CBS-CORBA functionality.
class cCBS_StdCORBA_Task : public cCBS_StdFrame_Task
  
{
private:

public:
	virtual void doOnThreadControlError();

	//Virtual method called before the subtask runDown call. 
	//Can be redefined by subclasses. The default 
	//implementation does nothing.
	virtual void beforeSubtaskEnd();

	void doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

	void connectProxy(const std::string& ServantName, bool reconnect = false   );

	void doOnCorbaException(CORBA::Exception& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string & Message, long Level);

	//Returning pointer to Proxy of given Name.
  cCBS_ProxyBase* getCorbaProxy(const std::string & proxyName);

	//Returning valid pointer to class if instatiated.
	static  cCBS_StdCORBA_Task* getInstance();

	//Method to register CORBA Proxy (Client). The Proxy will 
	//be bind to the respctive Servant by the ORB.
	void registerProxy(cCBS_ProxyBase* pCBS_ProxyBase, const std::string  & ServantName = "MyServantName", const std::string  &ServerTask = "MyServerTask", const std::string  &ServerTaskPOA = "MyServerTaskPOA");

	cCBS_StdCORBA_ClientTask* m_pCBS_StdCORBA_ClientTask;

	//Method to register CORBA Servants. The Servant object 
	//will be published by the ORB.
	cCBS_CorbaServant* registerServant(PortableServer::ServantBase* pServant, const std::string  & ServantName = "MyServantName");
	//Virtual method called after the subtask startUp call. 
	//Can be redefined by subclasses. The default 
	//implementation does nothing.
	virtual void afterSubtaskStart();

	cCBS_StdCORBA_ServerTask * m_pCBS_StdCORBA_ServerTask;

	virtual ~cCBS_StdCORBA_Task();

  cCBS_Corba getClientCorbaSettings();

  cCBS_Corba getServerCorbaSettings();

  iCBS_Component_var cCBS_StdCORBA_Task::getComponent(const std::string& componentName);

  iCBS_Task_var cCBS_StdCORBA_Task::getTask(const std::string& taskName);


protected:
	//Pointer to class itself, will be usable after 
	//instantiation of the class
	static cCBS_StdCORBA_Task* m_Instance;

  cCBS_StdCORBA_Task();

  virtual bool initialize();
};

#endif /* _INC_CCORBA_TASK_4084F87B0161_INCLUDED */

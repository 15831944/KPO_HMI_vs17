// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCORBA_SERVERTASK_4084F87B0161_INCLUDED
#define _INC_CCORBA_SERVERTASK_4084F87B0161_INCLUDED

#include <CBS_StdAPI/cCBS_StdCorbaServerTask.h>

//Class providing CBS-CORBA functionality.
class cCBS_StdCORBA_ServerTask : public cCBS_StdCorbaServerTask
  
{
private:

  std::string m_CorbaServerTaskName;

  std::string m_CorbaServerTaskPOA;

  // create ApplServer
  cCBS_CorbaApplServer m_corbaApplServer;


public:
	void deactivateAllServants();

	void doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

	void doOnCorbaException(CORBA::Exception& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

  void doOnException(const std::string &Function, const std::string &Action, const std::string  & File = "", long Line = 0);

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string & Message, long Level);

	//Setting CORBA relevant traits.
	cCBS_Corba getCorbaOptions();

	//Before registered CORBA Servant objects will be 
	//activated by the ORB
	void activateAllServants();

	//Method to register CORBA Servants. The Servant object 
	//will be published by the ORB.
	cCBS_CorbaServant* registerServant(PortableServer::ServantBase* pServant, const std::string  & ServantName = "MyServantName");

	virtual ~cCBS_StdCORBA_ServerTask();

	cCBS_StdCORBA_ServerTask();

  std::string getCorbaServerTaskName();

  std::string getCorbaServerTaskPOA();

  cCBS_Corba getCorbaSettings();


protected:

  virtual bool initialize();

};

#endif /* _INC_CCORBA_SERVERTASK_4084F87B0161_INCLUDED */

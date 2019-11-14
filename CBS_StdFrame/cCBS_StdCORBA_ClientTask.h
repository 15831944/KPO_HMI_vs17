// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCORBA_CLIENTTASK_4084F87B0161_INCLUDED
#define _INC_CCORBA_CLIENTTASK_4084F87B0161_INCLUDED

#include "corba.h"
#include "cCBS_ProxyBase.h"
#include <CBS_StdAPI/cCBS_StdCorbaClientTask.h>


//Class providing CBS-CORBA functionality.
class cCBS_StdCORBA_ClientTask : public cCBS_StdCorbaClientTask
  
{
private:

  std::map<std::string, cCBS_ProxyBase*> m_ProxyList;

public:
	//##ModelId=426638ED0355
	void disconnectAllProxies();

	void doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

	void doOnCorbaException(CORBA::Exception& Exc, const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);

  void doOnException(const std::string &Function, const std::string &Action, const std::string  & File = "", long Line = 0);

	void connectProxy(const std::string& ServantName, bool reconnect = false   );

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string & Message, long Level);

	//Setting CORBA relevant traits.
	void setTraits();

	//Returning pointer to Proxy of given Name.
  cCBS_ProxyBase* getCorbaProxy(const std::string & proxyName);

	//Before registered CORBA Proxies objects will be bind by 
	//the ORB
	void connectAllProxies();

	//Method to register CORBA Proxy (Client). The Proxy will 
	//be bind to the respctive Servant by the ORB.
	void registerProxy(cCBS_ProxyBase* pCBS_ProxyBase, const std::string  & ServantName = "MyServantName", const std::string  &ServerTask = "MyServerTask", const std::string  &ServerTaskPOA = "MyServerTaskPOA");

	virtual ~cCBS_StdCORBA_ClientTask();

	cCBS_StdCORBA_ClientTask();

  cCBS_Corba getCorbaSettings();

protected:

  virtual bool initialize();

};

#endif /* _INC_CCORBA_CLIENTTASK_4084F87B0161_INCLUDED */

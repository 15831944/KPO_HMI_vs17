// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSERVER_4044558F0309_INCLUDED
#define _INC_CSERVER_4044558F0309_INCLUDED

#include "CBS_StdAPI.h"

class cCBS_StdFrame_Component;

class cCBS_StdFrame_Task;

class cCBS_StdDB_Task;
class cCBS_StdCORBA_Task;
class cCBS_StdEvent_Task;

class cCBS_StdLog_Task;

class cCBS_StdLogHandler;

//Class providing cCBS_Server functionality.
//##ModelId=40EAA0930140
class cCBS_StdFrame_Server 
: public cCBS_StdServer
{
private:
	//##ModelId=410A48590309
	cCBS_StdLog_Task* m_pLog_Task;

	//##ModelId=40EBCAAD02EC
  cCBS_StdCORBA_Task* m_pCORBA_Task ;
	//##ModelId=40EBCAAD02F6
  cCBS_StdDB_Task* m_pDB_Task ;
	//##ModelId=40EBCAAD030A
  cCBS_StdEvent_Task* m_pEvent_Task ;



public:
	//##ModelId=4215D15F0192
	virtual void runDownTasks();

	//##ModelId=41FE119C0329
	void registerLogHandler(cCBS_StdLogHandler* NewHandler);

	//Register new Task at cCBS_StdComponent.
	//##ModelId=40EBCAAD0327
	void registerTask(const std::string & TaskName, cCBS_StdFrame_Task *pTask);

	//Starts the cCBS_StdFrame system as Server. After 
	//calling runAsServer the process is available via CORBA 
	//interfaces only. (ORB->run() will be called internally!)
	//##ModelId=40EAA0930160
	virtual void runAsServer();

	//Starts the cCBS_StdFrame system as Client.
	//##ModelId=40EAA0930163
	virtual void runAsClient();

  //Abstract method. Should create the tasks that are part 
  //of this server.
  //##ModelId=40EAA093014E
  virtual void createTasks();

  //##ModelId=40EAA0930151
  virtual ~cCBS_StdFrame_Server();

  //##ModelId=40EAA0930154
  cCBS_StdFrame_Server(int argc, const char* argv[]);

protected:
  //##ModelId=40EBC601010F
  cCBS_StdFrame_Component* m_pServer_Component;

};

#endif /* _INC_CSERVER_4044558F0309_INCLUDED */

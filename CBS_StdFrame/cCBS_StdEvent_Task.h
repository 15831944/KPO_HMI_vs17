// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENT_TASK_40AE1C21004F_INCLUDED
#define _INC_CEVENT_TASK_40AE1C21004F_INCLUDED

#include "cCBS_StdFrame_Task.h"

class cCBS_StdCORBA_Task;
class cCBS_StdEventSender_Task;
class cCBS_StdEventHandler_Task;
class cCBS_StdEventHandler;

//##ModelId=40EAA093020E
class cCBS_StdEvent_Task : public cCBS_StdFrame_Task
  
{
public:
	//##ModelId=48AD0F1A0108
	virtual void doOnThreadControlError();


	//##ModelId=44FE88B301BD
  virtual long checkWorkingState();

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	//##ModelId=41499CA60384
	virtual void log(const std::string & Message, long Level);

	//Registering Event Handler (derived from cCBS_StdEventHandler) 
  //##ModelId=40EBCAAE01D4
  bool registerEventHandler(cCBS_StdEventHandler* pEventHandler, const std::string& TaskName = ""  );


	//Sends event to EventChannel.
  //##ModelId=40EAA0930231
  bool sendEvent(const FRIESEvent& Event);

	//##ModelId=48A53B920193
  bool sendEvent(const FRIESEvent& Event, bool External );

  bool sendEvent(const FRIESEvent& Event, bool External , const std::string& TaskName);

  //Virtual method called after the subtask startUp call. 
  //Can be redefined by subclasses. The default 
  //implementation does nothing.
  //##ModelId=40EAA093022E
  virtual void afterSubtaskStart();

	virtual std::string getStateDetails();

	//##ModelId=40EAA0930213
	virtual ~cCBS_StdEvent_Task();


	//Returning valid pointer to class if instatiated.
	//##ModelId=40EAA0930218
	static  cCBS_StdEvent_Task* getInstance();

	//Handling Event received by cCBS_StdEventHandler_Task and 
	//direct it to the EventHandlerAdapter.
	//##ModelId=40EAA0930229
  virtual bool handleEvent(const FRIESEvent & Event);

  void registerEventHandlerTask(cCBS_StdEventHandler_Task* pCBS_StdEventHandlerTask, const std::string TaskName);

  void registerEventSenderTask(cCBS_StdEventSender_Task* pCBS_StdEventSender_Task, const std::string TaskName);

protected:
	//##ModelId=40EAA0930216
	cCBS_StdEvent_Task();
	//Pointer to class itself, will be usable after 
	//instantiation of the class
	//##ModelId=40EAA0930239
	static cCBS_StdEvent_Task* m_Instance;

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.
	//##ModelId=40EAA0930226
	virtual void ownStartUp();

	//Virtual task run down method. Called by the runDown 
	//method before stopping the subtasks. The default 
	//implementation sets only the state of the task to 
	//NotRunning. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would stop thread execution.
	//##ModelId=40EAA0930223
	virtual void ownRunDown();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=40EAA0930220
	virtual bool initialize();

private:
  std::map<std::string, cCBS_StdEventHandler_Task*> m_EventHandlerTaskList;
  std::map<std::string, cCBS_StdEventSender_Task*> m_EventSenderTaskList;

  std::map<std::string, cCBS_StdEventHandler_Task*> getEventHandlerTaskList();
  std::map<std::string, cCBS_StdEventSender_Task*> getEventSenderTaskList();

};

#endif /* _INC_CEVENT_TASK_40AE1C21004F_INCLUDED */

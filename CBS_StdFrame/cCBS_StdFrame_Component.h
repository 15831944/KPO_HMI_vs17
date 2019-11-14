// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCOMPONENT_404455D7015E_INCLUDED
#define _INC_CCOMPONENT_404455D7015E_INCLUDED

#include "CBS_StdAPI.h"
#include "cCBS_Thread.h"

class cCBS_StdFrame_Task;

class cCBS_StdFrame_Server;


//Class providing CBS component functionalities.
//##ModelId=40EAA0930110
class cCBS_StdFrame_Component 
: public cCBS_StdComponent
{

private:

	///<summary>Vector with pairs of names and tasks.</summary>
  ///<remarks>This must be a vector to preserve the ordering of the task insertion to ensure that the log task is activated first!</remarks>
	std::vector<std::pair<std::string,cCBS_StdFrame_Task*>>  m_TaskList;

	//##ModelId=40EAA093013C
	cCBS_StdFrame_Server* m_pServer;

protected:

//task controller thread. this calls cecks the time 
//difference between the time when the "control" method has 
//been called . If the duraction reaches the given 
//ControlTime, the doOnThreadControlError of the respective 
//task will be called.
	//##ModelId=48AD61FE00C7
	class cCBS_StdFrame_ComponentControlThread 
	: public cCBS_Thread
	{
	public:
		//Expects the ControlTime in ms
		//##ModelId=48AD61FE00D2
		cCBS_StdFrame_ComponentControlThread(cCBS_StdFrame_Component* pComponent, long ControlTime);

		//##ModelId=48AD61FE00D7
		void terminate();

    friend class cCBS_StdFrame_Component;

		void control();

		void uncontrol();

    void forceControlError();

	protected:
		//##ModelId=48AD61FE00DE
		long m_ControlTime;

		//##ModelId=48AD61FE00D5
		virtual ~cCBS_StdFrame_ComponentControlThread();

	//Virtual work method. Sleeps for the specified 
	//ControlTime and checks status 
	//will run down task and component in case of errors
		//##ModelId=48AD61FE00D6
		virtual void work();

		//Work function called in a loop by the thread (via the 
	//work method). Can be redefined by subclasses. 
	//
	//The default implementation does nothing (except 
	//sleeping for 1 second). This method could have been 
	//declared abstract. Anyway, in order to allow instances 
	//of cCBS_Thread to be created (in the case where a 
	//thread function has been specified for execution), it 
	//has been implemented doing nothing.
		//##ModelId=48AD61FE00D8
		virtual void performWorkingStep();

	private:

		//##ModelId=48AD6831010C
    cCBS_StdFrame_Component * m_pComponent;

		bool m_doControl;

    bool m_doforceControlError;

		CBS_LocalTime m_StartTime;

	};



	//Virtual task run down method. Called by the runDown 
	//method before stopping the subtasks. The default 
	//implementation sets only the state of the task to 
	//NotRunning. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would stop thread execution.
	//##ModelId=4120A65201DC
	virtual void ownRunDown();

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.
	//##ModelId=4120A6530025
	virtual void ownStartUp();

public:
	//##ModelId=48AD7A70017C
	void runControlThread();

	//##ModelId=48AD6B190016
	virtual void doOnThreadControlError();

  void logStateDetails();

	//##ModelId=48AD3F9900CD
	void terminate();

  void control();

  void uncontrol();

  void control(bool forceControlError);

	//##ModelId=4215D14E02EB
	virtual void runDownSubtasks();

	//Virtual method called before the subtask runDown call. 
	//Can be redefined by subclasses. The default 
	//implementation does nothing.
	//##ModelId=42146A510242
	virtual void beforeSubtaskEnd();

	//Virtual method called before the subtask startUp call. 
	//Can be redefined by subclasses. The default 
	//implementation does nothing.
	//##ModelId=42146A53033F
	virtual void beforeSubtaskStart();

	//Register new Task (derived form cCBS_StdFrame_Task) at 
	//TaskList. All registered Task will be handled at 
	//createSubtask method during System startup.
	//##ModelId=410DFAF30235
	void registerTask(const std::string & TaskName, cCBS_StdFrame_Task* pTask);


	//##ModelId=40EBCAAD022D
  void log( const std::string  & Message, long Level);

	//##ModelId=40EBCAAD025F
	void setpServer(cCBS_StdFrame_Server* value);

  //Virtual method called after the subtask runDown call. 
  //Can be redefined by subclasses. The default 
  //implementation does nothing.
  //##ModelId=40EAA0930115
  virtual void afterSubtaskEnd();

  //Virtual method called after the subtask startUp call. 
  //Can be redefined by subclasses. The default 
  //implementation does nothing.
  //##ModelId=40EAA0930118
  virtual void afterSubtaskStart();

  //Virtual subtask creation method. Called by activate 
  //after initialization. Subclasses may implement this 
  //method to create their subtasks.
  //##ModelId=40EAA093011B
  virtual void createSubtasks();

  //##ModelId=40EAA093011E
  virtual void getOwnStateDetails(std::string& details);

  //##ModelId=40EAA0930123
  virtual ~cCBS_StdFrame_Component();

  //##ModelId=40EAA0930126
  cCBS_StdFrame_Component();

	//##ModelId=44FE88B20325
  std::vector<std::pair<std::string,cCBS_StdFrame_Task*>> getTaskList();

protected:

	//##ModelId=48AD6785022D
	cCBS_StdFrame_ComponentControlThread* m_pControlThread;


};

#endif /* _INC_CCOMPONENT_404455D7015E_INCLUDED */

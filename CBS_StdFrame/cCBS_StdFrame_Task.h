// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTASK_404C79C40253_INCLUDED
#define _INC_CTASK_404C79C40253_INCLUDED

#include <CBS_StdAPI.h>
#include "cCBS_Thread.h"
#include "cCBS_Time.h"
#include "cCBS_StdFrame.h"

class cCBS_StdLog_Task;

class cCBS_StdFrame_Component;

//Base class for all process tasks.
//##ModelId=40EAA093017A
class cCBS_StdFrame_Task : public cCBS_StdTask
{
protected:
	//task controller thread. this calls cecks the time 
//difference between the time when the "control" method has 
//been called . If the duraction reaches the given 
//ControlTime, the doOnThreadControlError of the respective 
//task will be called.
	//##ModelId=48A552D7005B
  class cCBS_StdFrame_TaskControlThread 
	: public cCBS_Thread
	{
	private:
		//##ModelId=48A94A8B014F
		bool m_doControl;

		//##ModelId=48A56DD80180
		CBS_LocalTime m_StartTime;

    friend class cCBS_StdFrame_Task;

	public:
    virtual std::string getStateDetails();

    //##ModelId=48A95F55024A
		void control();

		//##ModelId=48A95F550268
		void uncontrol();

		//##ModelId=48A55A91031B
		std::string getCurrentThreadId();

		//##ModelId=48A55A910325
		void logThreadInformation(const std::string& Message);

		//##ModelId=48A559F7000F
		void terminate();

		//Expects the ControlTime in ms
		//##ModelId=48A552D7008E
		cCBS_StdFrame_TaskControlThread(cCBS_StdFrame_Task* pTask , long ControlTime);

	protected:
		//Work function called in a loop by the thread (via the 
	//work method). Can be redefined by subclasses. 
	//
	//The default implementation does nothing (except 
	//sleeping for 1 second). This method could have been 
	//declared abstract. Anyway, in order to allow instances 
	//of cCBS_Thread to be created (in the case where a 
	//thread function has been specified for execution), it 
	//has been implemented doing nothing.
		//##ModelId=48A55A910307
		virtual void performWorkingStep();

		//##ModelId=48A557640018
		cCBS_StdFrame_Task* m_pTask;

		//##ModelId=48A552D70098
		long m_ControlTime;
    
		//##ModelId=48A552D700A6
		virtual ~cCBS_StdFrame_TaskControlThread();

		//Virtual work method. Sleeps for the specified ControlTime and checks status 
	  //will run down task and component in case of errors
		//##ModelId=48A552D700AC
		virtual void work();

	};

private:


	//##ModelId=4149A27803DA
	cCBS_StdLog_Task* m_pLogTask;

	//##ModelId=410DFB240330
	std::map<std::string,cCBS_StdTask*>  m_SubTaskList;

	//##ModelId=48A53B8E0115
  long m_InternalTraceLevel;

public:

  std::string getCurrentTimeAsString();

  virtual std::string getStateDetails();

	//##ModelId=48A95F550073
	void terminateControlThread();

	//##ModelId=48A95F5500CE
	virtual void runControlThread();

	//##ModelId=48A56AE80317
	virtual void doOnThreadControlError();

	//##ModelId=48A558E801CE
	 void uncontrol();

	//##ModelId=48A556380301
	 void control(   );

	//##ModelId=48A5407101DF
	const cCBS_StdFrame_Component* getpComponent() const;

	//##ModelId=48A5407103DC
	void setpComponent(cCBS_StdFrame_Component* value);


	//##ModelId=48A53B8E01AB
  virtual void doOnComponentStartup();

  // search maximum of external(set via CBS_TaskViewer) and internal(set via ini file) trace level
	//##ModelId=48A53B8E0238
  unsigned long getTraceLevel();

	//##ModelId=44FE88B2022A
  virtual long checkWorkingState();

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	//##ModelId=4149A0830208
	virtual void log(const std::string& Message, long Level);

	//##ModelId=42724A0C00B3
	virtual bool isLoggingOn();

	//##ModelId=4253E8DD038D
	void doOnException(const std::string &Function = "", const std::string &Action = "", const std::string  & File = "", long Line = 0);


  //Virtual task run down method. Called by the runDown 
  //method before stopping the subtasks. The default 
  //implementation sets only the state of the task to 
  //NotRunning. Note that the work state is not set.
  //
  //This method may be redefined if the task represents for 
  //example a thread or a process. In this case, the method 
  //redefinition would stop thread execution.
  //##ModelId=40EAA0930182
  virtual void ownRunDown();


	//Virtual subtask creation method. Called by activate 
	//after initialization. Subclasses may implement this 
	//method to create their subtasks.
	//##ModelId=410DFB58021C
	virtual void createSubtasks();

	//Registering SubTask at SubTaskList. These Tasks will be 
	//handled by CreateSubtasks by CBS mechanisms.
	//##ModelId=410DFB3202CC
	void registerSubTask(cCBS_StdTask* pTask, const std::string & TaskName);

	//Generate valid TaskName depending on TaskName and 
	//ServerName.
  //##ModelId=40EAA09301A1
  std::string generateName(const std::string  & TaskName);

  // set the memeber m_taskname is not allowed to set. When task is activated the taskname will be set.
  //virtual const char* getTaskName();

  //##ModelId=40EAA0930185
  virtual void getOwnStateDetails(std::string& details);

  //##ModelId=40EAA093018A
  virtual ~cCBS_StdFrame_Task();
  
  virtual void setStateDetails(const std::string& value);

  virtual void setStateDetails(const std::string& item, const std::string& value, long Level);

  virtual void setWorking(bool state);

  std::string getControlThreadStateDetails();

protected:

  virtual void setStateDetails(const std::string& item, const std::string& value);

	//##ModelId=48A53E310054
	cCBS_StdFrame_Component* m_pComponent;

	//##ModelId=48A553940016
	cCBS_StdFrame_TaskControlThread* m_pControlThread;


  //##ModelId=40EAA093018D
  cCBS_StdFrame_Task();

	//##ModelId=40EBCAAD0024
	cCBS_StdFrame_Task(cCBS_StdFrame* pApplication_Frame, int argc, const char *argv[]);


	//##ModelId=40EBCAAD013D
 	cCBS_StdFrame* m_Application_Frame;

	//##ModelId=40EAA09301A7
  int m_argc;
	//##ModelId=40EAA09301A9
  const char** m_argv;

  //Virtual initialization method. Creates the task POA 
  //with the policies created by the createPolicies method 
  //and activates the task servant on this POA. Called by 
  //the activate method. Returns true on success.
  //##ModelId=40EAA093018F
  virtual bool initialize();

  //Virtual task start up method. Called by the 
  //runtimeStartUp method after starting up the subtasks. 
  //The default implementation sets only the state of the 
  //task to Running. Note that the work state is not set.
  //
  //This method may be redefined if the task represents for 
  //example a thread or a process. In this case, the method 
  //redefinition would start thread execution.
  //##ModelId=40EAA093017F
  virtual void ownStartUp();

  std::map<std::string, std::string> m_StateDetailItems;
};

#endif /* _INC_CTASK_404C79C40253_INCLUDED */

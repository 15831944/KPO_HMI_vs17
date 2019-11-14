
#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED
#define _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED

#include <string>
#include <iostream>
#include <map>

#include "cCBS_Thread.h"
#include "CBS_Tasks_s.hh"
#include "CProxyManager.h"

#include "cCBS_StdFrame_Task.h"

class IntrfImpl;

//##ModelId=41C93DBC000E
class CSYSMON_Task 
: public cCBS_StdFrame_Task
{
	
public:

	//##ModelId=41DE98430194
	virtual ~CSYSMON_Task();

  //##ModelId=41C975500085
	virtual void getOwnStateDetails(CORBA::String_out details);

  void setStateDetailsThreadSave(const std::string& item, const std::string& value);

//task controller thread. this calls cecks the time 
//difference between the time when the "control" method has 
//been called . If the duraction reaches the given 
//ControlTime, the doOnThreadControlError of the respective 
//task will be called.
	//##ModelId=48AD61FE00C7
	class CSYSMON_TaskThread 
	: public cCBS_Thread
	{
	public:
		//Expects the ControlTime in ms
		//##ModelId=48AD61FE00D2
		CSYSMON_TaskThread(long ControlTime, CSYSMON_Task* Parent);

		//##ModelId=48AD61FE00D7
		void terminate();

    friend class CSYSMON_Task;

	protected:
		//##ModelId=48AD61FE00DE
		long m_ControlTime;

    CSYSMON_Task* m_pParent;
    std::string m_DateTimeFormat;

		//##ModelId=48AD61FE00D5
		virtual ~CSYSMON_TaskThread();

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

    void setCORBAConnections();

	private:

	  CProxyManager<iCBS_Task>* m_pCBS_ProxyManager;

    std::map <std::string,std::string> m_ProxyList;

    IntrfImpl * m_pIntrfImpl;
	};


  long m_ScanInterval;

	//contructor
	CSYSMON_Task();


	virtual void performWorkingStep();

protected:

	CSYSMON_TaskThread* m_pThread;


};
//-------------------------------------------------------------------------------------------------
#endif /* _INC_CSOM_STATUSCHECKTASK_41C93DBC000E_INCLUDED */

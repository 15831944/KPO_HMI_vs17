// Copyright (C) 2007 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_OUTTASK_45ABA484012F_INCLUDED
#define _INC_CTELCOM_OUTTASK_45ABA484012F_INCLUDED

#include "cCBS_Thread.h"
#include "CTelcom_Task.h"
#include "CTelcom_OutProt.h"

class CTelcom_OutAppCommunication;
class CTelcom_OutEventHandler;


class CTelcom_OutTask : public CTelcom_Task
{
protected:

	//Thread to create the wotchdog telegram
  //independent of the send process of other 
  //telegrams
  class CTelcom_OutTask_Watchdog_Thread
	: public cCBS_Thread
	{
	private:
    friend class cCBS_StdFrame_Task;

	public:
		void terminate();

		//Expects the WatchdogTime in ms
		CTelcom_OutTask_Watchdog_Thread(CTelcom_OutTask* pTask , long WatchdogTime);

	protected:

		CTelcom_OutTask* m_pTask;

		long m_WatchdogTime;

		virtual ~CTelcom_OutTask_Watchdog_Thread();

		//Sleeps for the specified WatchdogTime and 
    //calls performWatchDog function of the task
		virtual void work();

	};


public:

  void runWatchdogThread();

	void getOwnStateDetails(CORBA::String_out details);

	CTelcom_OutTask();

	virtual ~CTelcom_OutTask();

	virtual void setCORBAConnections();

	//method stops thread execution.
	virtual void ownRunDown();

	static CTelcom_OutTask* getInstance();

  CTelcom_OutAppCommunication* getpOutAppCommunication();

protected:
	CTelcom_OutAppCommunication* m_pOutAppCommunication;

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	//method starts thread execution.
	virtual void ownStartUp();

	virtual void performWorkingStep();

private:
  
  void performWatchDog();

  static CTelcom_OutTask* m_Instance;

  CTelcom_OutEventHandler* m_evHandler;

  std::string m_WatchdogType;

  // Plant unit number(s) eg. 1,2,... 
  std::vector<std::string> m_UnitNoList;


public:

    CTelcom_OutTask_Watchdog_Thread* m_pWatchdog_Thread;

};

#endif /* _INC_CTELCOM_OUTTASK_45ABA484012F_INCLUDED */

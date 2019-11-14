// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCYCLICTRIGGERCALL_426610AC0013_INCLUDED
#define _INC_CCYCLICTRIGGERCALL_426610AC0013_INCLUDED

#include "CDateTime.h"

#include "cCBS_Thread.h"

class CEventMessage;

//##ModelId=426610AC0013
class CCyclicTriggerCall 
{
public:
	//##ModelId=426610D603B7
	class CCyclicTrig 
	: public cCBS_Thread
	{
    friend class CCyclicTriggerCall;

	private:
		//Time of last trigger call
		//##ModelId=44E3411B03AC
		CDateTime m_LastActionTime;
		//How long trigger have to be alive (in seconds) before 
		//terminating
		//##ModelId=44E340670178
    long m_LifeTime;
    long m_elapsedTime;

		//##ModelId=44E5C8B503A0
    CCyclicTriggerCall* m_Parent;

	public:
		//##ModelId=42BAA990020F
		void update(CEventMessage& Event);

		//reset trigger cycle for sending event immediately
		//##ModelId=42661F0902F8
		void resetAndSend();

    //reset trigger cycle for sending event after elapsed time
		void resetAndWait();

		//##ModelId=4266115103E6
		virtual ~CCyclicTrig();

		//##ModelId=42661152028B
		CCyclicTrig(CCyclicTriggerCall* parent, CEventMessage& ev, long cycle);

		//##ModelId=44E34307020C
		std::string getCurrentThreadId();

		//##ModelId=44E343070217
		void logThreadInformation(const std::string& Message);

		//##ModelId=44E343070235
		void terminate();

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
		//##ModelId=426664040345
		virtual void performWorkingStep();

		virtual void work();

		//Cycle time in mseconds
		//##ModelId=4266120A00F3
		long m_cycleTime;

		//##ModelId=4266110A01DB
		CEventMessage m_eventMessage;

	};

	//##ModelId=4266118F017A
	virtual ~CCyclicTriggerCall();

	//##ModelId=4266118F0331
	CCyclicTriggerCall(CEventMessage& arg, long msec);

protected:
	//##ModelId=42661AFC00F6
	CCyclicTrig* m_pTrig;

	//##ModelId=44E5C8B5027B
	bool m_Terminated;

public:
	//##ModelId=44E3417600B1
	void updateActionTime(CDateTime& value);

	//##ModelId=44E3418702C3
	CDateTime& getLastActionTime();

	//##ModelId=44E3444C01B8
	void setLifeTime(long value);

	//##ModelId=44E3444B02CD
	long getLifeTime();

	//##ModelId=42BAA975022C
	void update(CEventMessage& Event);

	void reset();

	//method to interrupt cyclicTrigger and perform 
	//immediately
	//##ModelId=4266138A03C6
	void send();

  //return true if thread has been terminated
	//##ModelId=44E5C8B5031C
	bool isTerminated();

  // set term status
	//##ModelId=44E5C8B50330
	void setTerminated(bool _t);
};

#endif /* _INC_CCYCLICTRIGGERCALL_426610AC0013_INCLUDED */

// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVCHANNELEVENTHANDLER_40C417DD0283_INCLUDED
#define _INC_CEVCHANNELEVENTHANDLER_40C417DD0283_INCLUDED


#include <vector>


class CEvChannelEvent;

class CEventHandler;

class cCBS_StdEventHandler;

class cCBS_StdEvent_Task;

//Class dircecting incoming events registered EventHandlers.
//##ModelId=40EAA09302F8
class cCBS_StdEventHandlerAdapter 
{
protected:
	//task controller thread. this calls cecks the time 
//difference between the time when the "control" method has 
//been called . If the duraction reaches the given 
//ControlTime, the doOnThreadControlError of the respective 
//task will be called.

  class cCBS_StdEventHandlerAdapterWorkerThread 
	: public cCBS_Thread
	{
	private:
    std::string m_EventHandlerName;

	public:

    void terminate();

		cCBS_StdEventHandlerAdapterWorkerThread(cCBS_StdEventHandlerAdapter* pEventHandlerAdapter, const std::string& EventHandlerName);

    //void addEvent(const FRIESEvent& Event);

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
		cCBS_StdEventHandlerAdapter* m_pEventHandlerAdapter;

		//##ModelId=48A552D700A6
		virtual ~cCBS_StdEventHandlerAdapterWorkerThread();

		//Virtual work method. Sleeps for the specified ControlTime and checks status 
	  //will run down task and component in case of errors
		//##ModelId=48A552D700AC
		virtual void work();

	};



	//##ModelId=410E4778006D
	cCBS_StdEvent_Task* m_pEvent_Task;

  bool checkEventAcceptance(const FRIESEvent& Event);

  bool doEvent(const FRIESEvent& Event);

protected:

	cCBS_StdEventHandlerAdapterWorkerThread* m_pWorkerThread;

  std::vector<FRIESEvent> m_EventList;

  bool checkReplaceEvent(const FRIESEvent& FirstEvent, const FRIESEvent& NewEvent);

public:

  virtual ~cCBS_StdEventHandlerAdapter();

	//##ModelId=410DFAA20171
	cCBS_StdEventHandlerAdapter(cCBS_StdEvent_Task *pEventTask);
  cCBS_StdEventHandlerAdapter(cCBS_StdEvent_Task *pEventTask, const std::string EventHandlerName);

	//Adding EventHandler classes to EventHandlerList
  //##ModelId=40EBCAAE027E
  bool registerEventHandler(cCBS_StdEventHandler* pEventHandler);

	//Directing events to EventHandlerList members.
  //##ModelId=40EAA09302FD
  bool handleEvent(const FRIESEvent& Event);

	//##ModelId=40EBCAAE02A6
  void log( const std::string  & Message, long Level);

  std::string  getStateDetails();

  void setStateDetails(const std::string& item, const std::string& value);

  // insert new event at front of EventList and replace existing event if required
  void insertEvent(const FRIESEvent& NewEvent);

  // get next event from EventList and remove it from list
  bool getNextEvent(FRIESEvent& NextEvent);

private:
	//##ModelId=42E0F0F50261
	CBS_LocalTime m_EventAcceptanceTime;

	//##ModelId=43131E190238
	CBS_LocalTime m_EventRejectionTime;


	//##ModelId=42E0F0D7035D
	void doAfterEventHandling(long Success);

	//##ModelId=42E0EE990365
	CBS_LocalTime m_EventReceptionTime;

	//##ModelId=42DF9F210199
  void doOnEventRejection();

	//##ModelId=42DF9E3C0353
	long m_NoOfIncomingEvents;

	//##ModelId=42DF9EB90104
	void doBeforeEventHandling();

	//##ModelId=410DFA920286
	std::string  m_Receiver;

	//List representing all registered EventHandler classes.
  //##ModelId=40EAA0930305
  std::vector<cCBS_StdEventHandler*>  m_EventHandlerList;
  std::vector<cCBS_StdEventHandler*>  getEventHandlerList();

  std::string m_EventHandlerName;

  //To indicate in the task viewer the problem with event processing 
  long m_ThresholdEventQueueNotWorking;

  std::map<std::string, std::string> m_StateDetailItems;

};

#endif /* _INC_CEVCHANNELEVENTHANDLER_40C417DD0283_INCLUDED */

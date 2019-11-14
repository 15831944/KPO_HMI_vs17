// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVCHANNELEVENT_40C4179403C8_INCLUDED
#define _INC_CEVCHANNELEVENT_40C4179403C8_INCLUDED

#include "CBS_StdAPI.h"

class cCBS_StdEvent_Task;
class cCBS_StdFrame_Task;

//Class handling received EventChannel events.
//##ModelId=40EAA09302EC
class cCBS_StdEventHandler 
{
private:

public:
	//##ModelId=41090DE60392
	cCBS_StdEventHandler(cCBS_StdFrame_Task* pTask = 0);

	//##ModelId=433BA955033A
	virtual void setpTask(cCBS_StdFrame_Task* value);

	//##ModelId=42C290A000BA
	virtual bool doOnEventHandlingError(const FRIESEvent& Event) = 0;

	//##ModelId=42B7EDED0063
	virtual bool checkEventAcceptance(const FRIESEvent& Event) = 0;

  virtual bool checkReplaceEvent(const FRIESEvent& FirstEvent, const FRIESEvent& NewEvent) = 0;

	//##ModelId=41090DE700CE
	virtual ~cCBS_StdEventHandler();

	//Handling received EventChannel event and dircting the 
	//Event to the EventHandlerAdapter.
  //##ModelId=40EAA09302EE
  virtual bool handleEvent(const FRIESEvent& Event) = 0;

	//##ModelId=40EBCAAE030B
  void log( const std::string  & Message, long Level);

  virtual bool afterHandleEvent(const FRIESEvent& Event) = 0;

  virtual bool beforeHandleEvent(const FRIESEvent& Event) = 0;

  virtual void setEventHandlerTaskName( const std::string& EventHandlerTaskName);

  virtual std::string getEventHandlerTaskName();


protected:
	//##ModelId=433BA90503A3
	cCBS_StdFrame_Task* m_pTask;

	//##ModelId=41090E5F00B6
	cCBS_StdEvent_Task* m_pEventTask;

  long getTraceLevel();

  std::string m_EventHandlerTaskName;
};

#endif /* _INC_CEVCHANNELEVENT_40C4179403C8_INCLUDED */

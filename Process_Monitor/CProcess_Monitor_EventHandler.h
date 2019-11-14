// Copyright (C) 2009 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPROCESS_MONITOR_EVENTHANDLER_INCLUDED
#define _INC_CPROCESS_MONITOR_EVENTHANDLER_INCLUDED

#include "CProcess_Monitor_Task.h"
#include "CEventHandler.h"

// class to handle events to start and stop monitoring
// for received plant and product
class CProcess_Monitor_EventHandler
: public CEventHandler
{
private:
  // turn-on procedure to control registered components 
  bool enable(CEventMessage& Event);

  // turn-off the procedure to control registered components 
  bool disable(CEventMessage& Event);

  CProcess_Monitor_Task* m_pProcMonTask;

public:
  virtual ~CProcess_Monitor_EventHandler();

  CProcess_Monitor_EventHandler(CProcess_Monitor_Task* _task);

  bool handleEvent(const FRIESEvent& Event);

  bool doOnEventHandlingError(const FRIESEvent& Event);

};

#endif /* _INC_CPROCESS_MONITOR_EVENTHANDLER_INCLUDED */

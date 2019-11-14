// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EVENTHANDLER_42971F1C01AD_INCLUDED
#define _INC_CARCHIVER_EVENTHANDLER_42971F1C01AD_INCLUDED

#include "CEventHandler.h"

class CEventMessage;

class CARCHIVER_Task;

class CARCHIVER_EventHandler 
: public CEventHandler
{
protected:
	CARCHIVER_Task* m_pARCHIVER_Task;
  std::string m_HMIReceiver;

private:
public:
	virtual bool dispatchEvent(CEventMessage& Event);

	virtual ~CARCHIVER_EventHandler();

	CARCHIVER_EventHandler(CARCHIVER_Task *Task);

	virtual bool handleEvent(CEventMessage& Event) = 0;

	virtual bool handleEvent(const FRIESEvent& Event);

};

#endif /* _INC_CARCHIVER_EVENTHANDLER_42971F1C01AD_INCLUDED */

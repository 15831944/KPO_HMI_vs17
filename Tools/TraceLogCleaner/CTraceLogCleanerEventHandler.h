// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTraceLogCleanerEVENTHANDLER_41344FE603C7_INCLUDED
#define _INC_CTraceLogCleanerEVENTHANDLER_41344FE603C7_INCLUDED


#include "CEventHandler.h"

class CEventMessage;


class CTraceLogCleanerEventHandler 
: public CEventHandler
{
private:
  
  bool doOnEventMessage(const CEventMessage& EventMessage);

public:
	virtual bool doOnEventHandlingError(const FRIESEvent& Event);

	virtual bool checkEventAcceptance(const FRIESEvent& Event);

	virtual bool handleEvent(const FRIESEvent& Event);

  CTraceLogCleanerEventHandler();
  ~CTraceLogCleanerEventHandler();

};

#endif /* _INC_CTraceLogCleanerEVENTHANDLER_41344FE603C7_INCLUDED */

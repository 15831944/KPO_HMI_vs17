// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED
#define _INC_CDM_EAFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED

#include "CDM_EAFEventHandler.h"

class CDM_EAFPurposeEventHandler 
: public CDM_EAFEventHandler
{
public:
	CDM_EAFPurposeEventHandler();

	virtual ~CDM_EAFPurposeEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

  bool doEAFHandleUpdatePurpose(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED */

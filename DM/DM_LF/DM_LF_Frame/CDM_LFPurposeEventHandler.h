// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED
#define _INC_CDM_LFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED

#include "CDM_EventHandler.h"
#include "CDM_LFEventHandler.h"

class CDM_LFPurposeEventHandler 
: public CDM_LFEventHandler
{
public:
	CDM_LFPurposeEventHandler();

	virtual ~CDM_LFPurposeEventHandler();

	virtual bool handleEvent(CEventMessage& evMessage);

  virtual bool doLFHandleUpdatePurpose(CEventMessage& Event);

};

#endif /* _INC_CDM_LFPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED */

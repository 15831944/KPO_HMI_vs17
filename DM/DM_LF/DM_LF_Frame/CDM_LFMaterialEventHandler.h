// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFMATERIALEVENTHANDLER_412F156103AA_INCLUDED
#define _INC_CDM_LFMATERIALEVENTHANDLER_412F156103AA_INCLUDED

#include "CDM_EventHandler.h"
#include "CDM_LFEventHandler.h"

class CDM_LFMaterialEventHandler 
: public CDM_LFEventHandler
{
public:
	virtual ~CDM_LFMaterialEventHandler();

	CDM_LFMaterialEventHandler();

	virtual bool handleEvent(CEventMessage& evMessage);

	bool doLFHMIMaterialDischarged(CEventMessage& Event);

	bool doLFMaterialHandlingReport( CEventMessage& Event);

  bool doLFChangeLiquidAdditionData(CEventMessage& Event);
};

#endif /* _INC_CDM_LFMATERIALEVENTHANDLER_412F156103AA_INCLUDED */

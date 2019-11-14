// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_GEN_EVENTHANDLER_40FE8B15024C_INCLUDED
#define _INC_CTSM_GEN_EVENTHANDLER_40FE8B15024C_INCLUDED

#include "CEventHandler.h"

#include <string>

class CEventMessage;
class CTsmBaseApplication;

class CTSM_GEN_EventHandler
: public CEventHandler
{
public:
	CTSM_GEN_EventHandler();

	void connectToTsmApplication(CTsmBaseApplication * pTsmApp);

	virtual bool handleEvent(const FRIESEvent& Event);

protected:
	CTsmBaseApplication * m_pTsmApplication;
};

#endif /* _INC_CTSM_GEN_EVENTHANDLER_40FE8B15024C_INCLUDED */

// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_LF_EVENTHANDLER_40FE8B15024C_INCLUDED
#define _INC_CTSM_LF_EVENTHANDLER_40FE8B15024C_INCLUDED

#include "CEventHandler.h"

#include <string>

class CEventMessage;
class CTsmBaseApplication;

class CTSM_LF_EventHandler : public CEventHandler

{
protected:
	CTsmBaseApplication * m_pTsmApplication;

	//remove product from TSM
	bool doGenRemoveTrackedProduct(CEventMessage & evMessage);

public:

	void handlePhaseTrackingEvents(CEventMessage& evMessage);

	CTSM_LF_EventHandler();

	void connectToTsmApplication(CTsmBaseApplication * pTsmApp);

	virtual bool handleEvent(const FRIESEvent& Event);

	bool doLFHeatAnnouncement(CEventMessage& evMessage);

	bool doLFHeatAnnouncementOffline(CEventMessage & evMessage);

	bool doLFHeatCancellation(CEventMessage& evMessage);

	bool doLFTsmCreateProduct(CEventMessage & evMessage);

	bool doLFResetOfHeat(CEventMessage & evMessage);

};

#endif /* _INC_CTSM_LF_EVENTHANDLER_40FE8B15024C_INCLUDED */

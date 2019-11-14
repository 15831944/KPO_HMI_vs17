// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_EAF_EVENTHANDLER_40FE8B15024C_INCLUDED
#define _INC_CTSM_EAF_EVENTHANDLER_40FE8B15024C_INCLUDED

#include "CEventHandler.h"

#include <string>

class CEventMessage;
class CTsmBaseApplication;

class CTSM_EAF_EventHandler : public CEventHandler
{
protected:
	CTsmBaseApplication * m_pTsmApplication;

public:
	bool handlePhaseTrackingEvents(CEventMessage& evMessage);

  CTSM_EAF_EventHandler();

	void connectToTsmApplication(CTsmBaseApplication * pTsmApp);

	virtual bool handleEvent(const FRIESEvent& Event);

  bool doEAFHeatAnnouncement(CEventMessage& evMessage);

	bool doEAFHeatAnnouncementOffline(CEventMessage & evMessage);

	bool doEAFHeatCancellation(CEventMessage& evMessage);

	bool doEAFTsmCreateProduct(CEventMessage & evMessage);
	bool doEAFResetOfHeat(CEventMessage & evMessage);

	//remove product from TSM
	bool doGenRemoveTrackedProduct(CEventMessage & evMessage);

};

#endif /* _INC_CTSM_EAF_EVENTHANDLER_40FE8B15024C_INCLUDED */

// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_HMD_EVENTHANDLER_INCLUDED
#define _INC_CTSM_HMD_EVENTHANDLER_INCLUDED

#include "CEventHandler.h"

#include <string>

class CEventMessage;
class CTsmBaseApplication;

//##ModelId=45A21C36021F
class CTSM_HMD_EventHandler : public CEventHandler

{
protected:
	//##ModelId=45A2278D0159
	CTsmBaseApplication * m_pTsmApplication;

	//remove product from TSM
	bool doGenRemoveTrackedProduct(CEventMessage & evMessage);

public:

	//##ModelId=45A21E8E0074
	void handlePhaseTrackingEvents(CEventMessage& evMessage);

	//##ModelId=45A21E8E0088
  CTSM_HMD_EventHandler();

	//##ModelId=45A21E8E0092
	void connectToTsmApplication(CTsmBaseApplication * pTsmApp);

	//##ModelId=45A21E8E00BA
	virtual bool handleEvent(const FRIESEvent& Event);

  //##ModelId=45A21E8E00E2
  bool doHMDHeatAnnouncement(CEventMessage& evMessage);

	//##ModelId=45A21E8E0100
	bool doHMDHeatAnnouncementOffline(CEventMessage & evMessage);

	//##ModelId=45A21E8E0151
	bool doHMDHeatCancellation(CEventMessage& evMessage);

	//##ModelId=46D28CE40182
	bool doHMDSetUpOfHeat(CEventMessage & evMessage);

	//##ModelId=46D28CE40196
	bool doHMDResetOfHeat(CEventMessage & evMessage);

};

#endif /* _INC_CTSM_HMD_EVENTHANDLER_40FE8B15024C_INCLUDED */

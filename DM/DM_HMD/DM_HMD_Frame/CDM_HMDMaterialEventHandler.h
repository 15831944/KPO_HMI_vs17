// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDMATERIALEVENTHANDLER_412F156103AA_INCLUDED
#define _INC_CDM_HMDMATERIALEVENTHANDLER_412F156103AA_INCLUDED

#include "CDM_HMDEventHandler.h"

//##ModelId=45139A7200E0
class CDM_HMDMaterialEventHandler 
: public CDM_HMDEventHandler
{
public:
	//##ModelId=45139A7200EE
	virtual ~CDM_HMDMaterialEventHandler();

	//##ModelId=45139A7200F0
	CDM_HMDMaterialEventHandler();

  //##ModelId=45139A7200F1
	virtual bool handleEvent(CEventMessage& evMessage);

	bool doHMDPowderBlowingEnd(CEventMessage& Event);

	bool doHMDPowderBlowingStart(CEventMessage& Event);

protected:
	//##ModelId=45C9A0C70379
  bool doHMDHMIMaterialDischarged(CEventMessage& Event);
};

#endif /* _INC_CDM_HMDMATERIALEVENTHANDLER_412F156103AA_INCLUDED */

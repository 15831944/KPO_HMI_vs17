// Copyright (C) 1991 - 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENMATERIALEVENTHANDLER_412F156103AA_INCLUDED
#define _INC_CDM_GENMATERIALEVENTHANDLER_412F156103AA_INCLUDED

#include "CDM_GENEventHandler.h"

class CDM_GENMaterialEventHandler 
: public CDM_GENEventHandler
{
public:
	virtual ~CDM_GENMaterialEventHandler();

	CDM_GENMaterialEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

  //handle scrap loading instructions request from L1, this can concern more than one unit and must be handled here
  bool doScrapChuteRequest(CEventMessage& Event);

  //handle hot metal loading instructions request from L1, this can concern more than one unit and must be handled here
  bool doHotMetalLadleRequest(CEventMessage& Event);

};

#endif /* _INC_CDM_GENMATERIALEVENTHANDLER_412F156103AA_INCLUDED */

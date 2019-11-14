// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED
#define _INC_CDM_HMDPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED

#include "CDM_HMDEventHandler.h"

//##ModelId=45139A710397
class CDM_HMDPurposeEventHandler 
: public CDM_HMDEventHandler
{
public:
	//##ModelId=45139A71039F
	CDM_HMDPurposeEventHandler();

	//##ModelId=45139A7103A0
	virtual ~CDM_HMDPurposeEventHandler();

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	//##ModelId=45139A7103A2
	virtual bool handleEvent(CEventMessage& evMessage);

};

#endif /* _INC_CDM_HMDPURPOSEEVENTHANDLER_412F15AD02D5_INCLUDED */

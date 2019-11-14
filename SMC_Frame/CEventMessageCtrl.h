// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTMESSAGECTRL_413D88A20021_INCLUDED
#define _INC_CEVENTMESSAGECTRL_413D88A20021_INCLUDED

#include "CEventMessage.h"

//Provide acces to a event message on a glabal level via 
//static member. Must be set explicitely in e.g. handle 
//event method.
//##ModelId=4225A6010217
class CEventMessageCtrl 
{
public:
	//##ModelId=4225A6010240
	static const CEventMessage& getEventMessage();

	//##ModelId=4225A6010242
	static void setEventMessage(CEventMessage& value);

protected:
	//##ModelId=4225A601024D
	static CEventMessage m_EventMessage;

};

#endif /* _INC_CEVENTMESSAGECTRL_413D88A20021_INCLUDED */

// Copyright (C) 2004 SMS Demag AG

#include "CEventMessageCtrl.h"

//##ModelId=4225A601024D
CEventMessage CEventMessageCtrl::m_EventMessage;

//##ModelId=4225A6010240
const CEventMessage& CEventMessageCtrl::getEventMessage() 
{
	return m_EventMessage;
}

//##ModelId=4225A6010242
void CEventMessageCtrl::setEventMessage(CEventMessage& value)
{
	m_EventMessage = value;
}


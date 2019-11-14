// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_EVENTHANDLER_45ABB3D40099_INCLUDED
#define _INC_CTELCOM_EVENTHANDLER_45ABB3D40099_INCLUDED

#include "CEventHandler.h"
#include <telcom.h>

///////////////////////////////////////////////
//
//In this class we handle received events.
//Construct the required telegram, 
//fetch the necessary data from data provider 
//and put it into the send queue.
//
///////////////////////////////////////////////
//##ModelId=45ABB3D40099
class CTelcom_EventHandler : public CEventHandler
{
public:
	//##ModelId=45ABB42F033E
	CTelcom_EventHandler();

	//##ModelId=45ABB4300156
	virtual ~CTelcom_EventHandler();

	//##ModelId=45ABB43D0013
	virtual bool handleEvent(const FRIESEvent& Event);

protected:
	//Container of telegram names that should be sended.
	//##ModelId=45ABB67001B1
	std::set<std::string> m_TelList;

	//Construct the required telegram, 
	//fetch the necessary data from data provider 
	//and put it into the send queue.
	//##ModelId=45ABB6A502F5
	bool handleEvent(const CEventMessage& Message);

	//##ModelId=45ABB6A50313
	bool collectTelegramData(std::string TlgType, const std::string& key, Tlg& theTlg);

	//##ModelId=45ABB6A5033B
	bool getSendValues(const std::string& Name, TlgElem& te);

};

#endif /* _INC_CTELCOM_EVENTHANDLER_45ABB3D40099_INCLUDED */

// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_MSGQUEUE_45AB797F0172_INCLUDED
#define _INC_CTELCOM_MSGQUEUE_45AB797F0172_INCLUDED

#include <deque>
class CTelcom_Msg;

//Container for messages
//##ModelId=45AB797F0172
class CTelcom_MsgQueue : public std::deque<CTelcom_Msg*>
{
public:
	//##ModelId=45AB962B01AF
	CTelcom_MsgQueue();

	//##ModelId=45AB962B03C2
	virtual ~CTelcom_MsgQueue();

};

#endif /* _INC_CTELCOM_MSGQUEUE_45AB797F0172_INCLUDED */

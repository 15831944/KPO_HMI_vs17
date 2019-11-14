// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_INTCPIPTRANSPORT_45AB541F00B0_INCLUDED
#define _INC_CTELCOM_INTCPIPTRANSPORT_45AB541F00B0_INCLUDED

#include "CTelcom_TcpipTransport.h"

//////////////////////////////////////////////////
//
//The overloaded virtual method "readMsgHeader" - reads 
//first few bytes of each message to determine the remaining 
//number of bytes to read so that Telcom can handle 
//the remainder of the message.
//
//////////////////////////////////////////////////
//##ModelId=45AB541F00B0
class CTelcom_InTcpipTransport : public CTelcom_TcpipTransport
{
public:
	//##ModelId=45AB96E8003D
	CTelcom_InTcpipTransport();

	//##ModelId=45AB96E801C3
	virtual ~CTelcom_InTcpipTransport();

protected:
	//##ModelId=45ABB0FA0161
	virtual int readMsgHeader(char* msg, int msgmax, int* plmsg);

	//##ModelId=45AC9EE60092
	int doDisconnect();
};

#endif /* _INC_CTELCOM_INTCPIPTRANSPORT_45AB541F00B0_INCLUDED */

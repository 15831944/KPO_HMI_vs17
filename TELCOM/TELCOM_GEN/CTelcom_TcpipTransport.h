// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_TCPIPTRANSPORT_45ABB05D0285_INCLUDED
#define _INC_CTELCOM_TCPIPTRANSPORT_45ABB05D0285_INCLUDED

#include "telcom.h"
#include "TcpipTransport.h"

//##ModelId=45ABB05D0285
class CTelcom_TcpipTransport : public TcpipTransport
{
public:
	//##ModelId=45ABB08401C1
	CTelcom_TcpipTransport();

	//##ModelId=45ABB084038D
	virtual ~CTelcom_TcpipTransport();

	//##ModelId=45ABB08E002D
	void switchConnection();

  virtual int receive(TCMessage & msg);

protected:
	// true if more than one connection is posible
	//##ModelId=45AE6992006C
	bool isRedundancy;

	//##ModelId=45ACB52A0152
	bool BigEndPlatf;

	//Must be the real header length
	//##ModelId=45ABB3AE02ED
	int m_iHeaderLen;

	//Length in bytes of the value that specifies the body 
	//length of telegram . Must be set in constructor
	//##ModelId=45ABB3AE035B
	int m_iLenOfLen;

	//Position from telegram beginning where the body length 
	//information is given.Must be set in constructor
	//##ModelId=45ABB3AE03B5
	int m_iLenPos;

	//##ModelId=45ABB3AF0031
	std::string m_ConnectInfo1;

	//##ModelId=45ABB3AF006D
	std::string m_ConnectInfo2;

	//##ModelId=45ABB08E004B
	virtual void configure(const std::string& section, bas::Configuration& c);

  virtual void setConnectInfo(string info);
};

#endif /* _INC_CTELCOM_TCPIPTRANSPORT_45ABB05D0285_INCLUDED */

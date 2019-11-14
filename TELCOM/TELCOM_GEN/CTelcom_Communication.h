// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_COMMUNICATION_45ACADD30329_INCLUDED
#define _INC_CTELCOM_COMMUNICATION_45ACADD30329_INCLUDED

#include <string>

//##ModelId=45ACADD30329
class CTelcom_Communication 
{
public:
	//##ModelId=45ACED8E0009
	virtual void startComm() = 0;

	//##ModelId=45ACED8E0045
	virtual void stopComm() = 0;

	//##ModelId=45ACADF00044
	virtual ~CTelcom_Communication();

protected:
	//##ModelId=45ACEE43036F
	int m_argc;

	//##ModelId=45ACEE4303A1
	char** m_argv;

	//Here you have to initialize TransTypeDict, FormatMgr 
	//and 
	//program arguments.
	//##ModelId=45ACC8F100B0
	virtual void initComm();

	//##ModelId=45ACADEF01AA
	CTelcom_Communication();

};

#endif /* _INC_CTELCOM_COMMUNICATION_45ACADD30329_INCLUDED */

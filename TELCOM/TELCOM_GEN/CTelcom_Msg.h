// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_MSG_45AB7A83027A_INCLUDED
#define _INC_CTELCOM_MSG_45AB7A83027A_INCLUDED

#include <string>
#include <sstream>
#include "Tlg.h"

/////////////////////////////////////////////////////////
//
//Object of this class contains the message body to be sent. 
//This object will be saved in the queue. If a receiver is 
//available, the message will be converted into 
//the 'TCMessage' and sent away.
//
/////////////////////////////////////////////////////////
//##ModelId=45AB7A83027A
class CTelcom_Msg 
{
protected:
	//##ModelId=45B0DE2F03B0
	static long GlobalCounter;

	//##ModelId=45B0DE2F03CE
	std::string m_OrderID;

	//##ModelId=45B0DE300004
	std::string m_PlantID;

private:
	//##ModelId=45B0E4C502CE
	std::string m_Sender;

	//##ModelId=45B0DF4B00A8
	long m_IamNo;

	//##ModelId=45B0D87003BC
	Tlg* m_pTlg;

	// type of telegramm
	//##ModelId=45B0D9D70090
	std::string m_MsgType;

	// serialized body of TCMessage
	//##ModelId=45B0D9D700A4
	std::string m_MsgBuffer;

public:
	//##ModelId=45B0E4E50072
	void setSender(const std::string& value);

	//##ModelId=45B0E4F501D3
	std::string getSender();

	//##ModelId=45B0E51300B9
	std::string getOrderID();

	//##ModelId=45B0E5210366
	void setOrderID(const std::string& value);

	//##ModelId=45B0E044009C
	long getCounter();

	//##ModelId=45B0DFD70037
	std::string getPlantID();

	//##ModelId=45B0DFEC0107
	void setPlantID(const std::string& value);

	//##ModelId=45B0D9D7012F
	Tlg* getTlg();

	//##ModelId=45B0DC93026D
	void setTlg(Tlg* value);

	//##ModelId=45AB998A02BE
	CTelcom_Msg();

	//##ModelId=45AB998B0180
	virtual ~CTelcom_Msg();

	//##ModelId=45B0D9D700C1
	std::string getType();

	//##ModelId=45B0D9D700F3
	void setType(std::string& value);

};

#endif /* _INC_CTELCOM_MSG_45AB7A83027A_INCLUDED */

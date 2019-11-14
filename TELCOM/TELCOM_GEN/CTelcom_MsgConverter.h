// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_MSGCONVERTER_45B0C3A5001B_INCLUDED
#define _INC_CTELCOM_MSGCONVERTER_45B0C3A5001B_INCLUDED

class CTelcom_Msg;
class TCMessage;

class CTelcom_MsgTypeTranslator;

//##ModelId=45B0C3A5001B
class CTelcom_MsgConverter 
{
protected:
	//##ModelId=45B0CCC80252
	CTelcom_MsgTypeTranslator* m_pMsgTypeTranslator;

	// setting data for test before sending
	void setTestData(Tlg& tlg);

private:
  std::string m_WatchdogType;
	//##ModelId=45B0C6A50358
	std::string m_LocalFormat;

	//##ModelId=45B0C6C3008B
	std::string m_RemoteFormat;

public:
	//##ModelId=45B0F012013E
	void setMsgTypeTranslator(CTelcom_MsgTypeTranslator* value);

	//##ModelId=45B0E1EC033F
	void setLocalFormat(std::string& value);

	//##ModelId=45B0E209005B
	void setRemoteFormat(std::string& value);

	//##ModelId=45B0C3D502AD
	CTelcom_MsgConverter();

	//##ModelId=45B0C3D70011
	virtual ~CTelcom_MsgConverter();

	//##ModelId=45B0C3F3012A
	bool fillTCMessage(CTelcom_Msg* telcommsg, TCMessage& tcmsg);

};

#endif /* _INC_CTELCOM_MSGCONVERTER_45B0C3A5001B_INCLUDED */

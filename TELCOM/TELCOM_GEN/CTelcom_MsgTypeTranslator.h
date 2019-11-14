// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_MSGTYPETRANSLATOR_45ABA1E200BE_INCLUDED
#define _INC_CTELCOM_MSGTYPETRANSLATOR_45ABA1E200BE_INCLUDED

#include <map>
#include <string>

//////////////////////////////////////////////////
//
//With insert() you can add a pair of name and number. 
//Depends on convert direction the translate()-method 
//returns the result.
//
//////////////////////////////////////////////////
//##ModelId=45ABA1E200BE
class CTelcom_MsgTypeTranslator 
{
public:
	//##ModelId=45ABA28001E3
	virtual ~CTelcom_MsgTypeTranslator();

	//Returns Telegram Number
	//##ModelId=45ABA29501EE
	long translate(const std::string& MsgName);

	//Returns Telegram Id string
	//##ModelId=45ABA2950216
	std::string translate(const long MsgNum);

	//##ModelId=45ABA295023E
	void insert(const std::string MsgName, const long MsgNum);

protected:
	//Tlg No->Tlg Id
	//##ModelId=45ABA2320296
	std::map<long,std::string> TlgNumStringMap;

	//Tlg Id string -> Tlg No
	//##ModelId=45ABA23202DC
	std::map<std::string,long> TlgStringNumMap;

	//##ModelId=45ABA2800016
	CTelcom_MsgTypeTranslator();

};

#endif /* _INC_CTELCOM_MSGTYPETRANSLATOR_45ABA1E200BE_INCLUDED */

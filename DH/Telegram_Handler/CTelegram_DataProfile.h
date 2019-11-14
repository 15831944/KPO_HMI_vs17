// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELEGRAM_DATAPROFILE_426E33EC0364_INCLUDED
#define _INC_CTELEGRAM_DATAPROFILE_426E33EC0364_INCLUDED

#include <string>
#include "CDateTime.h"

//////////////////////////////////////////////////
//
//This class represents a profile for data mapping from level 
//1 to level 2. This profile maps only simple tape of values. 
//There are two possibilities to create a profile. If a value 
//must have prefix or suffix or both of them, you can do it 
//here in constructor.  The telegram Id is the telegram name.
//
//////////////////////////////////////////////////
//##ModelId=426E33EC0364
class CTelegram_DataProfile 
{
public:
	//##ModelId=426F9886008F
	void log(const std::string& Message, long Level);

	//##ModelId=426E3B1302BD
	virtual ~CTelegram_DataProfile();

	//##ModelId=426E3B1400A4
	CTelegram_DataProfile(const std::string& TelegramID);

	//##ModelId=426F8E9102C4
	virtual bool check();

protected:
	//This prefix will be prefixed to value.
	//##ModelId=426FB2560180
	CDateTime m_StartOfLastIntervalShortTerm;
	//##ModelId=45337FB90096
	CDateTime m_StartOfLastIntervalLongTerm;

	//The type of value that has to be read from an interface.
	//##ModelId=426E340A01D9
	long m_IntervalShortTerm;
	//##ModelId=45337FB900A9
	long m_IntervalLongTerm;

  //The type of value to that IN_Type should be mapped.
	//##ModelId=426E341D035F
	long m_MaxTelegramsShortTerm;
	//##ModelId=45337FB900D2
	long m_MaxTelegramsLongTerm;

  //The value name that has to be read from an interface.
	//##ModelId=426E342E0185
	long m_ActTelegramsShortTerm;
	//##ModelId=45337FB900F0
	long m_ActTelegramsLongTerm;

	//##ModelId=45337FB9010E
	bool m_hasShortTermError;
	//##ModelId=45337FB90122
	bool m_hasLongTermError;


  //Telegram name of value.
	//##ModelId=426E35B301E1
	std::string m_TelegramID;

};

#endif /* _INC_CTELEGRAM_DATAPROFILE_426E33EC0364_INCLUDED */

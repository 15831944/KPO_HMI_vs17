// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDATETIMEFORMAT_4135787E03C1_INCLUDED
#define _INC_CDATETIMEFORMAT_4135787E03C1_INCLUDED

#include <time.h>
#include <string>


//##ModelId=4135787E03C1
class CDateTimeFormat 
{
public:
	//##ModelId=41370B8B0387
	CDateTimeFormat();

	//##ModelId=41370B8B03A5
	virtual ~CDateTimeFormat();

	//##ModelId=41357C710036
	std::string getFormat() const;

	//set Date/Time Format to overwrite default. The new 
	//format string is tested for usability.
	//Return value is TRUE if Date/Time format seems 
	//reasonable, otherwise FALSE.
	//##ModelId=41357C8F0061
	bool setFormat( std::string newFormat = "");

	//returns the formatted time string of the time given in 
	//the argument, using the current Format
	//##ModelId=41357DA7008B
	std::string formatATime(time_t timeT, unsigned long milliSeconds = 0) const ;

	//##ModelId=41370B8C01BC
  enum FormatTypes
  {
		//##ModelId=41370B8C01E4
    StandardFormat,
		//##ModelId=41370B8C02F2
    DataTransferFormat,
		//##ModelId=41370B8C02FC
    PrivateFormat
  };

	//##ModelId=41370B8B03B0
  bool getInput (time_t &timeT, unsigned long &milliSeconds, 
                 FormatTypes ft, const std::string &inputDateTime,
                 const std::string userFormat[]=0,
                 const std::string userFormatDST = ""); 


private:
	//The Format String is a superset of the Format argument 
	//for the ANSI <time.h> function strftime. The Extension:
	//since strftime does not handle fractions of a second, 
	//replace the position of the fraction part of the seconds
	//with a number (0-3) of 'F'.  Example: "It is 
	//%H:%M:%S.FF  O\'Clock." will format a given time to 
	//look like
	//"It is 09:30:15.12 O'Clock." 
	//##ModelId=413578B80017
	std::string m_CurrentFormatString;    // OUTPUT FORMAT ! 

	//##ModelId=41370B8C0022
  std::string m_CurrentInputFormat_d;   // INPUT FORMAT for DAY
	//##ModelId=41370B8C002C
  std::string m_CurrentInputFormat_m;   //                  MONTH
	//##ModelId=41370B8C0040
  std::string m_CurrentInputFormat_y;   //                  YEAR
	//##ModelId=41370B8C004A
  std::string m_CurrentInputFormat_h;   //                  HOUR
	//##ModelId=41370B8C005E
  std::string m_CurrentInputFormat_min; //                  Minute
	//##ModelId=41370B8C0072
  std::string m_CurrentInputFormat_s;   //                  Second
	//##ModelId=41370B8C0086
  std::string m_CurrentInputFormat_ms;  //                  MilliSecond

  std::string m_CurrentInputFormat_DST; //                  isDST?

	//##ModelId=41370B8C0090
  std::string m_CurrentDTInputFormat_d;   // INPUT FORMAT for DAY
	//##ModelId=41370B8C00A4
  std::string m_CurrentDTInputFormat_m;   //                  MONTH
	//##ModelId=41370B8C00C2
  std::string m_CurrentDTInputFormat_y;   //                  YEAR
	//##ModelId=41370B8C00E0
  std::string m_CurrentDTInputFormat_h;   //                  HOUR
	//##ModelId=41370B8C00F4
  std::string m_CurrentDTInputFormat_min; //                  Minute
	//##ModelId=41370B8C0108
  std::string m_CurrentDTInputFormat_s;   //                  Second
	//##ModelId=41370B8C0127
  std::string m_CurrentDTInputFormat_ms;  //                  MilliSecond

  std::string m_CurrentDTInputFormat_DST; //                  isDST?


	//##ModelId=41357EBC00BC
	static const std::string m_DefaultFormatString;
	//##ModelId=41370B8C013B
  static const std::string m_DefaultInputStrings[8];
	//##ModelId=41370B8C0159
  static const std::string m_DefaultDTInputStrings[8];
};

#endif /* _INC_CDATETIMEFORMAT_4135787E03C1_INCLUDED */

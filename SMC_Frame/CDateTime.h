// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDATETIME_4134353B036B_INCLUDED
#define _INC_CDATETIME_4134353B036B_INCLUDED


#include <time.h>
#include <string>

#include "iSMC_DataProvider_s.hh"

#include "CTimeBase.h"
#include "CDeltaTime.h"
#include "DB_CLASSLIB_DATE.h"
#include "corba.h"

#include "CDateTimeFormat.h"


// We need this using declaration only for the Rose code generation for the operator
// bool operator <<(const std::string& dateTime);
// if you specify std::string code generation will not work.

using std::string;

//##ModelId=4134353B036B
class CDateTime 
: public CTimeBase
{
public:
  //##ModelId=416168DF0311
  bool operator!=(const CDateTime& rhs) const;

  //##ModelId=416168E30123
  bool operator==(const CDateTime& rhs) const;

  bool operator>(const CDateTime& rhs) const;
  bool operator<(const CDateTime& rhs) const;

  bool operator>=(const CDateTime& rhs) const;
  bool operator<=(const CDateTime& rhs) const;


  //gives structure DB_CLASSLIB_DATE for usage with the 
  //CBS_DB classes
  //##ModelId=415A7535019C
  DB_CLASSLIB_DATE asDB_CLASSLIB_DATE() const;

  //Set Date/Time according to the CBS_DB time 
  //representation.
  //##ModelId=415970C60196
  bool SetTime(DB_CLASSLIB_DATE const *pDateTime);

  //The default constructor presets the internal time value 
  //with the current date/time value.
  //##ModelId=4134373E0244
  CDateTime();

  //the copy constructor
  CDateTime(const CDateTime& From);

  //the assignment operator
  CDateTime& operator=(const CDateTime& Value);

  //##ModelId=41370B8C03CE
  CDateTime (const std::string & dateTimeString, 
    const std::string userInputFormat [] = 0);

  // Create me with a time_t initialization
  //##ModelId=4161665300B6
  CDateTime(time_t timeT);

  CDateTime (sDate &DateTime);

  //##ModelId=41370B8D000F
  CDateTime (const std::string & dateString, const std::string & timeString, const std::string userInputFormat[]=0);

  //Presets the internal time value with the current 
  //date/time PLUS the DeltaTime argument
  //##ModelId=41344A2600AA
  CDateTime( CDeltaTime & timeOffset);

  // Create me from data as received (CORBA Any)
  // Any consists of DEF::seqLong with lenght og 8 !
	//##ModelId=471C726000D0
  CDateTime( CORBA::Any seqAny );

  //Return value is  TRUE if operation succeeded,
  //Return value is FALSE if argument string cannot be 
  //evaluated.
  //
  //Input string must match the DisplayFormat.
  //##ModelId=4134374B0062
  bool SetTime(const std::string & dateTimeString, const std::string privateFormat[]=0);

  //Set Date/Time according to the numeric arguments. 
  //
  //Return value is TRUE if operation succeeded,
  //Return value is FALSE if input can not be evaluated
  //##ModelId=413437580056
  bool SetTime(const sDate &DateTime);

  //Set time from a Unix time_t (seconds counter since 
  //1-Jan-1970)
  //##ModelId=41344648026A
  bool SetTime(time_t t);

  //Operators << offers an alternate way of setting the 
  //time content (Standard Input Format only!)
  //##ModelId=415A6689022A
  bool operator <<(const std::string& dateTime);

  //##ModelId=415A63AB012B
  bool operator <<(time_t t);

  //##ModelId=415A66BF0065
  bool operator <<(sDate & dateTime);

  bool adjDST (CDeltaTime deltaT = CDeltaTime(0,0,50));

  //Return Date/Time string in Default Format
  //##ModelId=413437FD0373
  std::string asString() const;

  //Return Date/Time string in format for database
	//##ModelId=416D12500366
	std::string toDBString() const;

	//##ModelId=416E8F4602F1
  void fromDBString(const std::string &value);

  //Return Date/Time using the Format as given in the 
  //Argument. 
  //
  //Returns "" (empty string) if Format is invalid
  //##ModelId=4134384102B2
  std::string asString(const std::string &Format);

  // puts content in current Format to output Stream:
  //##ModelId=41370B8D00B9
  friend std::ostream & operator<<(std::ostream &os, CDateTime &dateTime);
  //##ModelId=41343832017A
  sDate assDate() const;

  //Returns the time as UNIX time_t seconds counter
  //##ModelId=413446D4025F
  time_t asTime_T() const;

  // Returns the current Week Number (ISO 8601)
	//##ModelId=41F763DA02F9
  long getWeekNo() const;

  // returns days since sunday [0...6]
  long getDayOfWeek() const;

  //##ModelId=41343853002D
  bool addTime(CDeltaTime & deltaT);

  void UTCtoLocalTime(long TimeZone /* = 0 */);

  // get e.g. last sunday in october, DayOfWeek according to tm struct 0 = Sunday
  long getLastDayOfWeek(long Month);

  //Add n seconds to internal time value. nSeonds might be 
  //a negative number,
  //in which case the time is subtracted.
  //##ModelId=4134472200D0
  bool addTime(long nSeconds, long nMilliSeconds=0);
  
  // add double value dSeconds to internal time value.
  // dSeconds may be negative.
  //##ModelId=4134AF2801C7
  bool addTime (double dSeconds);

  //Calculate Difference "T1-T2" between two absolute times 
  //T1 and T2; return result as DeltaTime.
  //##ModelId=41343F8802A8
  static CDeltaTime subTimes(const CDateTime & T1, const CDateTime & T2);

  //##ModelId=4134391A01B8
  bool setDisplayFormat(const std::string & newFormat);

  //##ModelId=413439E1023E
  virtual ~CDateTime();

  //Add "T+dT" ,  absolute times T plus delta time dT; 
  //return result as DateTime.
  //##ModelId=41345DBF00A4
  static CDateTime addTimes(const CDateTime & T, const CDeltaTime & dT);

  //Add "dT+T" ,  absolute times T plus delta time dT; 
  //return result as DateTime.
  //##ModelId=41345E2903C7
  static CDateTime addTimes(const CDeltaTime & dT, const CDateTime & T);

  //##ModelId=416D103C00BE
  bool get_DST()const ;


	//##ModelId=44FE9C3000A5
  void resetTime();

  // Create me from data as received via DT (8 integers)
	//##ModelId=44FE9C3000A6
  CDateTime (long year, long month, long day, long hour, long minute, long second, long millisec, long isDST = 0 /* false */);

  // returns the famous C23 string as "2001-12-24 17W30:00.000"
  //                               or "2002-07-20 17S30:00.000"
	//##ModelId=44FE9C3000CD
  std::string asSMString (void);

	//##ModelId=471C72600123
  static CDateTime InvalidDateTime();
	//##ModelId=471C7260012B
  static sDate InvalidDate();
	//##ModelId=471C72600134
  CORBA::Any asCORBAAny();

  void fromCORBAAny(CORBA::Any anyTime);

  CDeltaTime subTime(const CDateTime& RefTime);

  bool isAmbiguous() const;

private:

  //##ModelId=41345D1703A7
  CDateTimeFormat m_DisplayFormat;
  //##ModelId=4134AF280253
  bool m_DST; // 1: Summer Time, 0: Winter Time 

  //the usage of the DST flag in the DB is determined by the operating system configuration
  //bool m_UseDST;
  bool m_IsDST_Region;

  bool isDST_Region() const;

  friend class CDeltaTime;

  bool isValidDateTime();

};

#endif /* _INC_CDATETIME_4134353B036B_INCLUDED */

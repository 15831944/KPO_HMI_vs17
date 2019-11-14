// Copyright (C) 2004 SMS Demag AG

#include "CTimeBase.h"

//##ModelId=4134AF27037E
CTimeBase::CTimeBase()
:	m_Year(0),
  m_Month(0),
  m_Day(0),
  m_Hour(0),
  m_Minute(0),
  m_Second(0),
  m_MilliSecond(0)
{
}

//##ModelId=4134AF270388
CTimeBase::CTimeBase(long nSeconds, long nMilliSeconds, long nMinutes, long nHours, 
                     long nDays, long nMonths, long nYears)
:	m_Year(nYears),
  m_Month(nMonths),
  m_Day(nDays),
  m_Hour(nHours),
  m_Minute(nMinutes),
  m_Second(nSeconds),
  m_MilliSecond(nMilliSeconds)
{
}

//##ModelId=41599D310386
long CTimeBase::getDay() const
{
	return m_Day;
}

//##ModelId=41599D41018A
void CTimeBase::setDay(long value)
{
	m_Day = value;
}

//##ModelId=41599D4B026B
long CTimeBase::getHour() const
{
	return m_Hour;
}

//##ModelId=41599D4C0048
void CTimeBase::setHour(long value)
{
	m_Hour = value;
}

//##ModelId=41599D4C021D
long CTimeBase::getMilliSecond() const
{
	return m_MilliSecond;
}

//##ModelId=41599D4C03A3
void CTimeBase::setMilliSecond(long value)
{
	m_MilliSecond = value;
}

//##ModelId=41599D4D01D0
long CTimeBase::getMinute() const
{
	return m_Minute;
}

//##ModelId=41599D4D0373
void CTimeBase::setMinute(long value)
{
	m_Minute = value;
}

//##ModelId=41599D4E0180
long CTimeBase::getMonth() const
{
	return m_Month;
}

//##ModelId=41599D4E0310
void CTimeBase::setMonth(long value)
{
	m_Month = value;
}

//##ModelId=41599D4F014F
long CTimeBase::getSecond() const
{
	return m_Second;
}

//##ModelId=41599D4F0308
void CTimeBase::setSecond(long value)
{
	m_Second = value;
}

//##ModelId=41599D50010B
long CTimeBase::getYear() const
{
	return m_Year;
}

//##ModelId=41599D510120
void CTimeBase::setYear(long value)
{
	m_Year = value;
}

//##ModelId=416169C70188
bool CTimeBase::operator!=(const CTimeBase& rhs) const
{
	return !operator==(rhs);
}

//##ModelId=416169C80324
bool CTimeBase::operator==(const CTimeBase& rhs) const
{
  return (m_MilliSecond == rhs.m_MilliSecond &&
          m_Second == rhs.m_Second &&
          m_Minute == rhs.m_Minute &&
          m_Hour == rhs.m_Hour &&
          m_Day == rhs.m_Day &&
          m_Month == rhs.m_Month &&
          m_Year == rhs.m_Year);
}

//##ModelId=44FE9C2A03CB
// will not work in the hour which is double due to DST switch over
bool CTimeBase::operator>(const CTimeBase& rhs) const
{
  //return (m_MilliSecond > rhs.m_MilliSecond ||
  //        m_Second > rhs.m_Second ||
  //        m_Minute > rhs.m_Minute ||
  //        m_Day > rhs.m_Day ||
  //        m_Month > rhs.m_Month ||
  //        m_Year > rhs.m_Year);
  bool RetValue = true;

  //if ( m_Year < rhs.m_Year || m_Year == rhs.m_Year)
  //  if ( m_Month < rhs.m_Month || m_Month == rhs.m_Month )
  //    if ( m_Day < rhs.m_Day || m_Day == rhs.m_Day )
  //      if ( m_Hour < rhs.m_Hour || m_Hour == rhs.m_Hour )
  //        if (m_Minute < rhs.m_Minute || m_Minute == rhs.m_Minute )
  //          if ( m_Second < rhs.m_Second || m_Second == rhs.m_Second )
  //            if ( m_MilliSecond < rhs.m_MilliSecond || m_MilliSecond == rhs.m_MilliSecond ) // counterexample 2000-02-02 00:00:00,000 > 2001-03-01 00:00:00,000 returns true
  //              RetValue = false;

  if (    m_Year < rhs.m_Year
      || (m_Year == rhs.m_Year && m_Month < rhs.m_Month)
      || (m_Year == rhs.m_Year && m_Month == rhs.m_Month && m_Day < rhs.m_Day)
      || (m_Year == rhs.m_Year && m_Month == rhs.m_Month && m_Day == rhs.m_Day && 
          60*60*1000*m_Hour+60*1000*m_Minute+1000*m_Second+m_MilliSecond 
            <= 60*60*1000*rhs.m_Hour+60*1000*rhs.m_Minute+1000*rhs.m_Second+rhs.m_MilliSecond))
    return false;

  return RetValue;

}
//##ModelId=44FE9C2A03B7
// will not work in the hour which is double due to DST switch over
bool CTimeBase::operator<(const CTimeBase& rhs) const
{
//  return (m_MilliSecond < rhs.m_MilliSecond ||
//          m_Second < rhs.m_Second ||
//          m_Minute < rhs.m_Minute ||
//          m_Day < rhs.m_Day ||
//          m_Month < rhs.m_Month ||
//          m_Year < rhs.m_Year);
  
  bool RetValue = false;

  //if ( m_Year < rhs.m_Year || m_Year == rhs.m_Year)
  //  if ( m_Month < rhs.m_Month || m_Month == rhs.m_Month )
  //    if ( m_Day < rhs.m_Day || m_Day == rhs.m_Day )
  //      if ( m_Hour < rhs.m_Hour || m_Hour == rhs.m_Hour )
  //        if (m_Minute < rhs.m_Minute || m_Minute == rhs.m_Minute )
  //          if ( m_Second < rhs.m_Second || m_Second == rhs.m_Second )
  //            if ( m_MilliSecond < rhs.m_MilliSecond ) // counterexample 1999-01-01 01:01:01,999 < 2001-03-04 00:00:00,000 is false
  //              RetValue = true;

  if (    m_Year < rhs.m_Year
      || (m_Year == rhs.m_Year && m_Month < rhs.m_Month)
      || (m_Year == rhs.m_Year && m_Month == rhs.m_Month && m_Day < rhs.m_Day)
      || (m_Year == rhs.m_Year && m_Month == rhs.m_Month && m_Day == rhs.m_Day && 
          60*60*1000*m_Hour+60*1000*m_Minute+1000*m_Second+m_MilliSecond 
            < 60*60*1000*rhs.m_Hour+60*1000*rhs.m_Minute+1000*rhs.m_Second+rhs.m_MilliSecond))
    return true;

  return RetValue;
}

CTimeBase::CTimeBase(const CTimeBase& From)
{
  m_Year = From.m_Year;
  m_Month = From.m_Month;
	m_Day = From.m_Day;
	m_Hour = From.m_Hour;
  m_Minute = From.m_Minute;
  m_Second = From.m_Second;
  m_MilliSecond = From.m_MilliSecond;
}

CTimeBase& CTimeBase::operator=(const CTimeBase& Value)
{
  if (this != &Value) 
  {
    m_Year = Value.m_Year;
    m_Month = Value.m_Month;
	  m_Day = Value.m_Day;
	  m_Hour = Value.m_Hour;
    m_Minute = Value.m_Minute;
    m_Second = Value.m_Second;
    m_MilliSecond = Value.m_MilliSecond;   
  }

  return *this;
}

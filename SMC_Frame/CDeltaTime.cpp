// Copyright (C) 2004 SMS Demag AG

#include <time.h>
#include "CDeltaTime.h"



//##ModelId=41344E6B01FF
CDeltaTime::CDeltaTime()
{
	// nix
}


//##ModelId=41344E7800DB
CDeltaTime::CDeltaTime(long nSeconds, long nMilliSeconds, long nMinutes, 
                       long nHours, long nDays, long nMonths, long nYears)
: CTimeBase(nSeconds,  nMilliSeconds,  nMinutes,  nHours,  nDays,  nMonths,  nYears)
{
	// nix
}

//##ModelId=4134511F0211
CDeltaTime& CDeltaTime::operator-()
{
  // negating all values makes a negative delta time.
	m_Year=-m_Year;
  m_Month = -m_Month;
  m_Day = -m_Day;
  m_Hour = -m_Hour;
  m_Minute = -m_Minute;
  m_Second = -m_Second;
  m_MilliSecond = -m_MilliSecond;
  return *this;
}


//##ModelId=415D5BC803CA
double CDeltaTime::asSeconds()
{
  double retval = m_Second +  m_MilliSecond/1000.  // after calculation, only these values are not null.
      +                          60. * m_Minute    // 60 seconds per minute
      +                    60. * 60. * m_Hour      // 60 minutes per hour, with 60 seconds each
      +              24. * 60. * 60. * m_Day
      +        30. * 24. * 60. * 60. * m_Month
      +       365. * 24. * 60. * 60. * m_Year;
  return retval;
}

std::ostream & operator<< (std::ostream &os,  CDeltaTime &deltaTime)
{
  double theSeconds       = deltaTime.asSeconds();
  long long ms =  (long long) (1000. * theSeconds+0.5);

  long long            ls  = (long) (ms/1000.) ;
  long long            lms = ms - 1000*ls;

  os << ls << "." << lms;
  return os;
}


// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDELTATIME_41343EAD00E3_INCLUDED
#define _INC_CDELTATIME_41343EAD00E3_INCLUDED

#include "CTimeBase.h"
#include <iostream>
//A Class for calculating Time Differences
//##ModelId=41343EAD00E3
class CDeltaTime 
: public CTimeBase
{
public:
	//##ModelId=41344E6B01FF
	CDeltaTime();

	//Create a Delta time from numeric arguments. Any 
	//argument may be negative.
	//##ModelId=41344E7800DB
	CDeltaTime(long nSeconds, long nMilliSeconds = 0, long nMinutes = 0, long nHours = 0, long nDays = 0, long nMonths = 0, long nYears = 0);

	//Invert delta time: dT -> -(dT)
	//##ModelId=4134511F0211
	CDeltaTime& operator-();
  
  // return number of seconds delta time.
  // Attention: the return value is exact only if the CDeltaTime is a result of
  //            a calculation, e.g. as the difference between two CDateTime values.
  //            It can not be exact if it has been created with valus nMonths and/or 
  //            nYears! (in these cases, it ALWAYS calculates with 30 days per month and
  //            365 days/year)
	//##ModelId=415D5BC803CA
  double asSeconds();

  // formatted output to an OStream: writes number of seconds and milliseconds.
  // If necessary, months and years are converted (using 30 d/month and 365 d/year).

	//##ModelId=415D5BC803DE
  friend std::ostream & operator<<(std::ostream &os, CDeltaTime &deltaTime);

	friend class CDateTime;
};

#endif /* _INC_CDELTATIME_41343EAD00E3_INCLUDED */

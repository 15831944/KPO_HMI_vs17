// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTIMEBASE_41345AB60131_INCLUDED
#define _INC_CTIMEBASE_41345AB60131_INCLUDED

//##ModelId=41345AB60131
class CTimeBase 
{
public:
	//##ModelId=416169C70188
	bool operator!=(const CTimeBase& rhs) const;

	//##ModelId=416169C80324
	bool operator==(const CTimeBase& rhs) const;

	//##ModelId=44FE9C2A03B7
	bool operator<(const CTimeBase& rhs) const;
	//##ModelId=44FE9C2A03CB
	bool operator>(const CTimeBase& rhs) const;


	//##ModelId=41599D310386
	long getDay() const;

	//##ModelId=41599D41018A
	void setDay(long value);

	//##ModelId=41599D4B026B
	long getHour() const;

	//##ModelId=41599D4C0048
	void setHour(long value);

	//##ModelId=41599D4C021D
	long getMilliSecond() const;

	//##ModelId=41599D4C03A3
	void setMilliSecond(long value);

	//##ModelId=41599D4D01D0
	long getMinute() const;

	//##ModelId=41599D4D0373
	void setMinute(long value);

	//##ModelId=41599D4E0180
	long getMonth() const;

	//##ModelId=41599D4E0310
	void setMonth(long value);

	//##ModelId=41599D4F014F
	long getSecond() const;

	//##ModelId=41599D4F0308
	void setSecond(long value);

	//##ModelId=41599D50010B
	long getYear() const;

	//##ModelId=41599D510120
	void setYear(long value);

	//##ModelId=4134AF27037E
  CTimeBase ();
	//##ModelId=4134AF270388
  CTimeBase (long nSeconds, long nMilliSeconds, long nMinutes, long nHours, long nDays, long nMonths, long nYears);

  CTimeBase(const CTimeBase& From);

  CTimeBase& operator=(const CTimeBase& Value);

protected:
	//##ModelId=41345B20033B
	long m_Year;

	//##ModelId=41345B200345
	long m_Month;

	//##ModelId=41345B20034F
	long m_Day;

	//##ModelId=41345B200359
	long m_Hour;

	//##ModelId=41345B4602EF
	long m_Minute;

	//##ModelId=41345B4901F9
	long m_Second;

	//##ModelId=41345B4C01F3
	long m_MilliSecond;

};

#endif /* _INC_CTIMEBASE_41345AB60131_INCLUDED */

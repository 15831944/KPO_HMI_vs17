// Copyright 2006 SMS - Demag AG

//------------------------------------------------
#include "CTimeFormat.h"
//------------------------------------------------

//-------------------------------------------------------
CTimeFormat::CTimeFormat():
DateDel1("-"),DateDel2("-"),TimeDel1(":"),TimeDel2(":"),TimeDel3(".")
{
}
//-------------------------------------------------------
CTimeFormat::~CTimeFormat()
{
}
//-------------------------------------------------------
void CTimeFormat::clearDateFormat()
{
  DateTemplate.clear();
	DateDel1.clear();
	DateDel2.clear();
}
//-------------------------------------------------------
void CTimeFormat::clearTimeFormat()
{
  TimeTemplate.clear();
	TimeDel1.clear();
	TimeDel2.clear();
	TimeDel3.clear();
}
//-------------------------------------------------------
void CTimeFormat::setDateFormat(CTimeFormat::DateTyp f1,const std::string& d1,CTimeFormat::DateTyp f2,
								const std::string& d2,CTimeFormat::DateTyp f3,CTimeFormat::YearFormat year)
{
	clearDateFormat();
	addToDateTemplate(f1,year);
	if(!d1.empty())
	{
		DateTemplate.append(d1);
		DateDel1 = d1;
	}
	else
	{
		DateDel1.clear();
	}
	addToDateTemplate(f2,year);
	if(!d2.empty())
	{
		DateTemplate.append(d2);
		DateDel2 = d2;
	}
	else
	{
		DateDel2.clear();
	}
	addToDateTemplate(f3,year);
}
//-------------------------------------------------------
void CTimeFormat::setTimeFormat(CTimeFormat::TimeTyp t1,const std::string& d1,CTimeFormat::TimeTyp t2,const std::string& d2,
				CTimeFormat::TimeTyp t3,const std::string& d3,CTimeFormat::TimeTyp t4,int msc)
{
	clearTimeFormat();
	addToTimeTemplate(t1,msc);
	if(!d1.empty())
	{
		TimeTemplate.append(d1);
		TimeDel1 = d1;
	}
	else
	{
		TimeDel1.clear();
	}
	addToTimeTemplate(t2,msc);
	if(!d2.empty())
	{
		TimeTemplate.append(d2);
		TimeDel2 = d2;
	}
	else
	{
		TimeDel2.clear();
	}
	addToTimeTemplate(t3,msc);
	if(!d3.empty())
	{
		TimeTemplate.append(d3);
		TimeDel3 = d3;
	}
	else
	{
		TimeDel3.clear();
	}
	addToTimeTemplate(t4,msc);
}
//--------------------------------------------------------
const std::string& CTimeFormat::getDateDelimeter1()const
{
	return DateDel1;
}
//----------------------------------------------------------
const std::string& CTimeFormat::getDateDelimeter2()const
{
	return DateDel2;
}
//--------------------------------------------------------
const std::string&  CTimeFormat::getTimeDelimeter1() const
{
	return TimeDel1;
}
//---------------------------------------------------------
const std::string&  CTimeFormat::getTimeDelimeter2() const
{
	return TimeDel2;
}
//---------------------------------------------------------
const std::string&  CTimeFormat::getTimeDelimeter3() const
{
	return TimeDel3;
}
//--------------------------------------------------------
void CTimeFormat::addToDateTemplate(DateTyp d,YearFormat year)
{
	if(d == tYear)
	{
		int count;
		if(year == tShort)
			count=2;
		if(year == tLang)
			count=4;
		DateTemplate.append(count,Year);
	}
	if(d == tMon)
		DateTemplate.append(2,Mon);
	if(d == tDay)
		DateTemplate.append(2,Day);
}
//-------------------------------------------------------
void CTimeFormat::addToTimeTemplate(TimeTyp t,int count)
{
	if(t == tHour)
		TimeTemplate.append(count,Hour);
	if(t == tMin)
		TimeTemplate.append(count,Min);
	if(t == tSec)
		TimeTemplate.append(count,Sec);
	if(t == tMSec)
		TimeTemplate.append(count,MSec);
}
//-------------------------------------------------------
const std::string& CTimeFormat::getDateFormat() const
{
	return DateTemplate;
}
//-------------------------------------------------------
const std::string& CTimeFormat::getTimeFormat() const
{
	return TimeTemplate;
}
//-------------------------------------------------------
void CTimeFormat::getYearFormatPlace(int* pos,int* length) const
{
	getDateFormatPlace(Year,pos,length);
}
//------------------------------------------------------
void CTimeFormat::getMonFormatPlace(int* pos,int* length) const
{
	getDateFormatPlace(Mon,pos,length);
}
//--------------------------------------------------------
void CTimeFormat::getDayFormatPlace(int* pos,int* length) const
{
	getDateFormatPlace(Day,pos,length);
}
//-------------------------------------------------------
void CTimeFormat::getHourFormatPlace(int* pos,int* length) const
{
	getTimeFormatPlace(Hour,pos,length);
}
//--------------------------------------------------------
void CTimeFormat::getMinFormatPlace(int* pos,int* length) const
{
	getTimeFormatPlace(Min,pos,length);
}
//---------------------------------------------------------
void CTimeFormat::getSecFormatPlace(int* pos,int* length) const
{
	getTimeFormatPlace(Sec,pos,length);
}
//-------------------------------------------------------
void CTimeFormat::getDateFormatPlace(const char c,int* pos,int* length) const
{
	int pos1 = int(DateTemplate.find_first_of(c));
	int pos2 = int(DateTemplate.find_last_of(c));

	(*pos) = pos1;
	(*length) = pos2-pos1+1;
}
//-------------------------------------------------------
void CTimeFormat::getTimeFormatPlace(const char c,int* pos,int* length) const
{
	int pos1 = int(TimeTemplate.find_first_of(c));
	int pos2 = int(TimeTemplate.find_last_of(c));

	(*pos) = pos1;
	(*length) = pos2-pos1+1;
}
//-------------------------------------------------------
const char CTimeFormat::Year = 'Y';
const char CTimeFormat::Mon = 'M';
const char CTimeFormat::Day = 'D';
//-------------------------------------------------------
const char CTimeFormat::Hour = 'H';
const char CTimeFormat::Min = 'M';
const char CTimeFormat::Sec = 'S';
const char CTimeFormat::MSec = 'm';
//-------------------------------------------------------

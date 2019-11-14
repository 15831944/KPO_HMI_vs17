// Copyright 2006 SMS - Demag AG

//------------------------------------------------------------------------
#include "CTelTime.h"
//------------------------------------------------------------------------
#include <math.h>
#include <time.h>

#pragma warning( disable : 4996 )
//------------------------------------------------------------------------
CTelTime::CTelTime()
{
}
//------------------------------------------------------------------------
CTelTime::~CTelTime()
{
}
//------------------------------------------------------------------------
void CTelTime::setTime(const double t)
{
  this->TlgTime = t;
}
//------------------------------------------------------------------------
double CTelTime::getTimeAsDouble() const
{
  return this->TlgTime;
}
//------------------------------------------------------------------------
void CTelTime::setDateFormat(CTimeFormat::DateTyp f1,const std::string& d1,CTimeFormat::DateTyp f2,
               const std::string& d2,CTimeFormat::DateTyp f3,CTimeFormat::YearFormat year)
{
  TimeFormat.setDateFormat(f1,d1,f2,d2,f3,year);
}
//------------------------------------------------------------------------
void CTelTime::setTimeFormat(CTimeFormat::TimeTyp t1,const std::string& d1,CTimeFormat::TimeTyp t2,const std::string& d2,
        CTimeFormat::TimeTyp t3,const std::string& d3,CTimeFormat::TimeTyp t4,int msc)
{
  TimeFormat.setTimeFormat(t1,d1,t2,d2,t3,d3,t4,msc);
}
//------------------------------------------------------------------------
std::string CTelTime::getDateAsString() const
{
  std::string ret("");
  char buffer[128];
  double t1;
  long t2;
  struct tm* tm_d = 0; 
	time_t temp;
  std::string format("");
  t1 = floor(TlgTime);
  t2=(long)t1;
  format = getDateFormatString();
  //tm_d = gmtime(&t2);
  temp=t2;
	tm_d = localtime(&temp);
  //(*tm_d).tm_mon =  (*tm_d).tm_mon + 1;
  strftime(buffer,128,format.c_str(),tm_d);
  ret.assign(buffer);
  
  return ret;
}
//------------------------------------------------------------------------
std::string CTelTime::getTimeAsString() const
{
  std::string ret("");
  char buffer[128];
  double t1;
  double t2;
  long t3;
  struct tm* tm_t = 0;
	time_t temp;
  std::string format("");
  t1 = floor(TlgTime);
  t2 = TlgTime - t1;
  t3 = long(t1);
  format = getTimeFormatString();
	temp=t3;
  tm_t=localtime(&temp);
  //tm_t = gmtime(&t3);
  strftime(buffer,128,format.c_str(),tm_t);
  ret.assign(buffer);
  std::string ms = CFormatConverter::DoublToString(t2);
  ms.erase(0,2);
  int pos1 = int(ret.find_first_of(CTimeFormat::MSec));
  int pos2 = int(ret.find_last_of(CTimeFormat::MSec));
  if((pos2-pos1+1) > int(ms.length()))
  {
    //ms.insert(0,(pos2-pos1+1)-ms.length(),'0');
    ms.insert(ms.length(),(pos2-pos1+1)-ms.length(),'0');
    //ret.erase(pos1,pos2-pos1+1);
    //ret.insert(pos1,ms);
  }
  ret.erase(pos1,pos2-pos1+1);
  ret.insert(pos1,ms);
  return ret;
}
//-------------------------------------------------------------------------
const std::string& CTelTime::getDateFormat() const
{
  return TimeFormat.getDateFormat();
}
//-----------------------------------------------------------------------
const std::string& CTelTime::getTimeFormat() const
{
  return TimeFormat.getTimeFormat();
}
//------------------------------------------------------------------------
void CTelTime::setTime(const std::string& date,const std::string& timestr)
{
  struct tm tm_t;

  if(!checkDateFormat(date))
    throw CExpDateError(TimeFormat.getDateFormat(),date);

  if(!checkTimeFormat(timestr))
    throw CExpTimeError(TimeFormat.getTimeFormat(),timestr);
      
  setDate(date,&tm_t);
  setTime(timestr,&tm_t);
   
  long tl = mktime(&tm_t);
  double td = (double)tl;
  std::string timeformat = TimeFormat.getTimeFormat();
  int pos1=int(timeformat.find_first_of(CTimeFormat::MSec));
  int pos2=int(timeformat.find_last_of(CTimeFormat::MSec));
  std::string ms(timestr.substr(pos1,pos2-pos1+1));
  
  ms =  "0." + ms; 
  //Veraendert EMAL DIRE
  double ms_d = CFormatConverter::StringToDouble(ms);
  /*while(ms_d >= 1.0)
  {
    ms_d = ms_d/10.0;
  }*/

  td=td+ms_d;
  TlgTime=td;
}
//------------------------------------------------------------------------
std::string CTelTime::getDateFormatString() const
{
  std::string ret("");
  std::string date("");
  std::string del1("");
  std::string del2("");
  char sym = ' ';
  int count=1;

  date = TimeFormat.getDateFormat();
  del1 = TimeFormat.getDateDelimeter1();
  del2 = TimeFormat.getDateDelimeter2();

  for(int i=0;i<int(date.length());i++)
  {
    if(sym != date[i])
    {
      sym = date[i];
      if(sym == CTimeFormat::Year)
      {
        int j = i+2;
        if(j > (int(date.length()) -1))
        {
          ret.append("%y");
        }
        else
        {
          if(date[j] != CTimeFormat::Year)
            ret.append("%y");
          else
            ret.append("%Y");
        }
      }
      else
      {
        if(sym == CTimeFormat::Mon)
        {
          ret.append("%m");
        }
        else
        {
          if(sym == CTimeFormat::Day)
          {
            ret.append("%d");
          }
          else
          {
            if((count == 1) && (!del1.empty()))
              ret.append(del1);
            if((count == 2) && (!del2.empty()))
              ret.append(del2);
            count++;
          }
        }
      }
    }
  }

  return ret;
}
//-----------------------------------------------------------------------
std::string CTelTime::getTimeFormatString() const
{
  std::string ret("");
  std::string time("");
  std::string del1("");
  std::string del2("");
  std::string del3("");
  char sym = ' ';
  int count=1;
    
  time = TimeFormat.getTimeFormat();
  del1 = TimeFormat.getTimeDelimeter1();
  del2 = TimeFormat.getTimeDelimeter2();
  del3 = TimeFormat.getTimeDelimeter3();

  for(int i=0;i<int(time.length());i++)
  {
    if(sym != time[i])
    {
      sym = time[i];
      if(sym == CTimeFormat::Hour)
      {
        ret.append("%H");
      }
      else
      {
        if(sym == CTimeFormat::Min)
        {
          ret.append("%M");
        }
        else
        {
          if(sym == CTimeFormat::Sec)
          {
            ret.append("%S");
          }
          else
          {
            if(sym == CTimeFormat::MSec)
            {
              int j=i+1;
              ret.append(1,CTimeFormat::MSec);
              while((j < int(time.length())) || (time[j] == CTimeFormat::MSec))
              {
                ret.append(1,CTimeFormat::MSec);
                j++;
              }
            }
            else
            {
              if((count == 1) && (!del1.empty()))
                ret.append(del1);
              if((count == 2) && (!del2.empty()))
                ret.append(del2);
              if((count == 3) && (!del3.empty()))
                ret.append(del3);
              count++;
            }

          }
        }
      }
    }
  }
  return ret;
}
//-----------------------------------------------------------------------
double CTelTime::getDiffTimeAsSecond(CTelTime* t)
{
    return (TlgTime - t->getTimeAsDouble());
}
//-----------------------------------------------------------------------
void CTelTime::setDate(const std::string& date,struct tm* tm_t)
{
  int pos,length;
  std::string str;
  long l;
  try
  {
    TimeFormat.getYearFormatPlace(&pos,&length);
    str=date.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_year=l-1900;
  
    TimeFormat.getMonFormatPlace(&pos,&length);
    str=date.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_mon = l-1;

    TimeFormat.getDayFormatPlace(&pos,&length);
    str=date.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_mday=l;
  }
  catch(...)
  {
    throw CExpDateError(TimeFormat.getDateFormat(),date);
  }
}
//-----------------------------------------------------------------------
void CTelTime::setTime(const std::string& time,struct tm* tm_t)
{
  int pos,length;
  std::string str;
  long l;

  try
  {
    TimeFormat.getHourFormatPlace(&pos,&length);
    str=time.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_hour = l;

    TimeFormat.getMinFormatPlace(&pos,&length);
    str=time.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_min = l;

    TimeFormat.getSecFormatPlace(&pos,&length);
    str=time.substr(pos,length);
    l=CFormatConverter::StringToLong(str);
    (*tm_t).tm_sec = l;
  }
  catch(...)
  {
      throw CExpTimeError(TimeFormat.getTimeFormat(),time);
  }
}
//-----------------------------------------------------------------------
bool CTelTime::checkDateFormat(const std::string& date)
{
  std::string del1 = TimeFormat.getDateDelimeter1();
  std::string del2 = TimeFormat.getDateDelimeter2();
  if(!del1.empty())
  {
    int pos1 = int(TimeFormat.getDateFormat().find(del1));
    int pos2 = int(date.find(del1));
    if(pos1 != pos2)
      return false;
  }
  if(!del2.empty())
  {
    int pos1 = int(TimeFormat.getDateFormat().find(del2));
    int pos2 = int(date.find(del2));
    if(pos1 != pos2)
      return false;
  }
  return true;
}
 //----------------------------------------------------------------------
bool CTelTime::checkTimeFormat(const std::string& time)
{
  std::string del1 = TimeFormat.getTimeDelimeter1();
  std::string del2 = TimeFormat.getTimeDelimeter2();
  std::string del3 = TimeFormat.getTimeDelimeter3();
  if(!del1.empty())
  {
    int pos1 = int(TimeFormat.getTimeFormat().find(del1));
    int pos2 = int(time.find(del1));
    if(pos1 != pos2)
      return false;
  }
  if(!del2.empty())
  {
    int pos1 = int(TimeFormat.getTimeFormat().find(del2));
    int pos2 = int(time.find(del2));
    if(pos1 != pos2)
      return false;
  }
  if(!del3.empty())
  {
    int pos1 = int(TimeFormat.getTimeFormat().find(del3));
    int pos2 = int(time.find(del3));
    if(pos1 != pos2)
      return false;
  }
  return true;
}
//-----------------------------------------------------------------------
void CTelTime::setTimeFormat(const CTimeFormat& format)
{
  TimeFormat=format;
}
//-----------------------------------------------------------------------
const CTimeFormat& CTelTime::getTimeFormat()
{
  return TimeFormat;
}
//-----------------------------------------------------------------------

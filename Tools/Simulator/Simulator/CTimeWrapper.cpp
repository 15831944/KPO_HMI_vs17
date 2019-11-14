// Copyright 2006 SMS - Demag AG

//--------------------------------------------------------------
#include "stdafx.h"
#include "CTimeWrapper.h"
#include "CStdConverter.h"
//--------------------------------------------------------------
CTimeWrapper::CTimeWrapper()
{
	Time = new CTelTime();
}
//--------------------------------------------------------------
CTimeWrapper::~CTimeWrapper()
{
	delete Time;
}
//--------------------------------------------------------------
CTimeWrapper^ CTimeWrapper::clone()
{
	CTimeWrapper^ ret = gcnew CTimeWrapper();
	ret->setTime(Time);
	return ret;
}
//--------------------------------------------------------------
void CTimeWrapper::setTime(CTelTime* tm)
{
  (*Time) = (*tm);
}
//--------------------------------------------------------------
double CTimeWrapper::getDifferenzTimeAsSecond(CTimeWrapper^ tm)
{ 
	return Time->getDiffTimeAsSecond(tm->getTime());
}
//--------------------------------------------------------------
void CTimeWrapper::setDate(String^ date)
{
  std::string datestr("");
  std::string del("");

  //CStdConverter::StringToStdStr(date,datestr);
  //del=Time->getDateDelim();
  //datestr.insert(4,del);
  //datestr.insert(7,del);
  //Time->setDate(datestr);
}
//--------------------------------------------------------------
void CTimeWrapper::setTime(String^ time)
{
  std::string timestr("");
  std::string del("");

  //CStdConverter::StringToStdStr(time,timestr);
  //del=Time->getTimeHourDelim();
  //timestr.insert(2,del);
  //timestr.insert(5,del);
  //del=Time->getTimeMSecDelim();
  //timestr.insert(8,del);
  //timestr.erase(timestr.length()-1,1);
  //Time->setTime(timestr);
}
//--------------------------------------------------------------
CTelTime* CTimeWrapper::getTime()
{
  return Time;
}
//--------------------------------------------------------------
bool CTimeWrapper::isGreater(CTimeWrapper^ tm)
{
  return true;		//((*(tm->getTime())) < (*Time) );
}
String^ CTimeWrapper::getNowDateAndTimeForFilePath()
{
	String^ timePath = nullptr;
	DateTime time = DateTime::Now;
	timePath = String::Concat(time.Year.ToString(),"_",time.Month.ToString(),"_",time.Day.ToString());
	timePath = String::Concat(timePath,"_",time.Hour.ToString(),"_",time.Minute.ToString(),"_",time.Second.ToString());
	return timePath;
}
//--------------------------------------------------------------
String^ CTimeWrapper::getNowDate()
{
  String^ timeStr=nullptr;
  int pos;
  DateTime time = DateTime::Now;
	timeStr=time.Today.ToString();
  pos=timeStr->LastIndexOf(" ");
  if(pos != -1)
    timeStr=timeStr->Substring(0,timeStr->Length-pos+1);

  return timeStr;
}

//--------------------------------------------------------------
String^ CTimeWrapper::getNowTime()
{
  String^ timeStr=nullptr;
  int pos;
  DateTime time = DateTime::Now;
  timeStr=time.TimeOfDay.ToString();
  pos=timeStr->LastIndexOf(".");
  if(pos != -1)
    timeStr=timeStr->Substring(0,timeStr->Length-pos);

  return timeStr;
}
//--------------------------------------------------------------

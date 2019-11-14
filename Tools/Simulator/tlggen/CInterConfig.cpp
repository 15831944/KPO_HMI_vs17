// // Copyright 2006 SMS - Demag AG
//--------------------------------------------------------------
#include "CInterConfig.h"
//--------------------------------------------------------------
CInterConfig::CInterConfig():
// TelIdName("Head"),ElemIdName(""),TypId(""),ElemLenName("")
TelIdName(""),ElemIdName(""),TypId(""),ElemLenName("")
{
  LogTimeFormat = new CTimeFormat();
  LogTimeFormat->setDateFormat(CTimeFormat::tYear,"-",CTimeFormat::tMon,"-",
                                CTimeFormat::tDay,CTimeFormat::tLang);

  LogTimeFormat->setTimeFormat(CTimeFormat::tHour,":",CTimeFormat::tMin,":",
                                 CTimeFormat::tSec,".",CTimeFormat::tMSec,2);
}
//--------------------------------------------------------------
CInterConfig::~CInterConfig()
{
  delete LogTimeFormat;
}
//--------------------------------------------------------------
CInterConfig* CInterConfig::getInterConfig(const std::string& name)
{
  CInterConfig* ret = 0;
  std::map<std::string,CInterConfig*>::iterator iter;
  iter = InterConfContainer.find(name);
  if(iter != InterConfContainer.end())
  {
    ret = iter->second;
  }
  else
  {
    ret = new CInterConfig();
    InterConfContainer.insert(std::pair<std::string,CInterConfig*>(name,ret));
  }
  return ret;
}
//--------------------------------------------------------------
void CInterConfig::addTelId(const std::string& telName,const std::string& id)
{
  TelId.insert(std::pair<std::string,std::string>(telName,id));
}
//--------------------------------------------------------------
void CInterConfig::clearTelId()
{
	TelId.clear();
}
//--------------------------------------------------------------
void CInterConfig::setTelIdInfo(const std::string& TelIdName,const std::string& ElemIdName,
                                const std::string& TypId,const std::string& ElemLenName)
{
  this->TelIdName   = TelIdName;
  this->ElemIdName  = ElemIdName;
  this->TypId       = TypId;
  this->ElemLenName = ElemLenName;
}
//--------------------------------------------------------------
const std::string& CInterConfig::getTelIdName()
{
  return TelIdName;
}
//--------------------------------------------------------------
void CInterConfig::getTelId(const std::string& tel,std::string& val)
{
  std::map<std::string,std::string>::iterator iter;
  iter = TelId.find(tel);
  if(iter != TelId.end())
  {
    val = iter->second;
  }
  else
  {
    val.clear();
  }
}
//--------------------------------------------------------------
void CInterConfig::getTelName(const std::string& id,std::string& val)
{
 std::map<std::string,std::string>::iterator iter;
 bool flag=false;
 val.clear();
 iter = TelId.begin();
 while((iter != TelId.end()) && (!flag))
 {
	 if(id == iter->second)
	 {
		 val=iter->first;
		 flag=true;
	 }
	 else
	 {
		 ++iter;
	 }
 }
}
//--------------------------------------------------------------
const std::string& CInterConfig::getElemIdName()
{
  return ElemIdName;
}
//---------------------------------------------------------------
const std::string& CInterConfig::getElemLenName()
{
  return ElemLenName;
}
//---------------------------------------------------------------
void CInterConfig::setSwapping(bool swop)
{
	this->Swapping = swop;
}
//---------------------------------------------------------------
bool CInterConfig::getSwapping() const
{
	return this->Swapping;
}
//--------------------------------------------------------------
void CInterConfig::setPaddingDirection(CInterConfig::PaddingTyp Dir)
{
	this->PaddingDir = Dir;
}
//--------------------------------------------------------------
CInterConfig::PaddingTyp CInterConfig::getPaddingDirection() const
{
	return this->PaddingDir;
}
//--------------------------------------------------------------
void CInterConfig::setPaddingString(const std::string& str)
{
	this->PaddingString = str;
}
//--------------------------------------------------------------
char CInterConfig::getPaddingString() const
{
	return this->PaddingString[0];
}
//---------------------------------------------------------------
void CInterConfig::setTreatLenIdMode(CInterConfig::LenTlgIdTyp treat)
{
	LenTlgId=treat;
}
//----------------------------------------------------------------
CInterConfig::LenTlgIdTyp CInterConfig::getTreatLenIdMode()
{
	return LenTlgId;
}
//---------------------------------------------------------------
void CInterConfig::setLimitTreatment(LimitValueTyp lim)
{
	this->LimitValue=lim;
}
//---------------------------------------------------------------
CInterConfig::LimitValueTyp CInterConfig::getLimitTreatment()
{
	return this->LimitValue;
}
//---------------------------------------------------------------
void CInterConfig::setLogDelimeter(char del)
{
	this->DelLog=del;
}
//----------------------------------------------------------------
char CInterConfig::getLogDelimeter()
{
	return this->DelLog;
}
//---------------------------------------------------------------
void CInterConfig::setTime(const std::string& date,const std::string& time)
{
	buildDateTemplate(date);
	buildTimeTemplate(time);
}
//---------------------------------------------------------------
void CInterConfig::buildDateTemplate(const std::string& date)
{
	CTimeFormat::DateTyp f1;
	CTimeFormat::DateTyp f2;
	CTimeFormat::DateTyp f3;
	std::string d1("");
	std::string d2("");
	CTimeFormat::YearFormat yf;
	std::string d(date);
	char sym;
	int pos;
	sym=d[0];
	pos=int(d.find_last_of(sym));
	f1=getDateIdent(sym);
	if(f1==CTimeFormat::tYear)
	{
		if((pos+1) == 4)
			yf=CTimeFormat::tLang;
		else
			yf=CTimeFormat::tShort;
	}
	d.erase(0,pos+1);
	d1=d[0];
	d.erase(0,1);
	
	sym=d[0];
	pos=int(d.find_last_of(sym));
	f2=getDateIdent(sym);
	if(f2==CTimeFormat::tYear)
	{
		if((pos+1) == 4)
			yf=CTimeFormat::tLang;
		else
			yf=CTimeFormat::tShort;
	}
	d.erase(0,pos+1);
	d2=d[0];
	d.erase(0,1);

	sym=d[0];
	pos=int(d.find_last_of(sym));
	f3=getDateIdent(sym);
	if(f3==CTimeFormat::tYear)
	{
		if((pos+1) == 4)
			yf=CTimeFormat::tLang;
		else
			yf=CTimeFormat::tShort;
	}

	LogTimeFormat->setDateFormat(f1,d1,f2,d2,f3,yf);
}
//---------------------------------------------------------------
void CInterConfig::buildTimeTemplate(const std::string& time)
{
	CTimeFormat::TimeTyp t1;
	CTimeFormat::TimeTyp t2;
	CTimeFormat::TimeTyp t3;
	CTimeFormat::TimeTyp t4;
	std::string d1("");
	std::string d2("");
	std::string d3("");

	std::string t(time);
	char sym;
	int pos;
	int count=0;

	sym=t[0];
	pos=int(t.find_last_of(sym));
	t1=getTimeIdent(sym);
	if(t1 == CTimeFormat::tMSec)
	{
		count=pos+1;
	}
	t.erase(0,pos+1);
	d1=t[0];
	t.erase(0,1);

	sym=t[0];
	pos=int(t.find_last_of(sym));
	t2=getTimeIdent(sym);
	if(t2 == CTimeFormat::tMSec)
	{
		count=pos+1;
	}
	t.erase(0,pos+1);
	d2=t[0];
	t.erase(0,1);

	sym=t[0];
	pos=int(t.find_last_of(sym));
	t3=getTimeIdent(sym);
	if(t3 == CTimeFormat::tMSec)
	{
		count=pos+1;
	}
	t.erase(0,pos+1);
	d3=t[0];
	t.erase(0,1);

	sym=t[0];
	pos=int(t.find_last_of(sym));
	t4=getTimeIdent(sym);
	if(t4 == CTimeFormat::tMSec)
	{
		count=pos+1;
	}
	LogTimeFormat->setTimeFormat(t1,d1,t2,d2,t3,d3,t4,count);
}
//---------------------------------------------------------------
CTimeFormat::DateTyp CInterConfig::getDateIdent(char sym)
{
	CTimeFormat::DateTyp ret;
	if(sym == CTimeFormat::Year)
		ret = CTimeFormat::tYear;
	if(sym == CTimeFormat::Mon)
		ret = CTimeFormat::tMon;
	if(sym == CTimeFormat::Day)
		ret = CTimeFormat::tDay;

	return ret;
}
//---------------------------------------------------------------
CTimeFormat::TimeTyp CInterConfig::getTimeIdent(char sym)
{
	CTimeFormat::TimeTyp ret;
	if(sym == CTimeFormat::Hour)
		ret = CTimeFormat::tHour;
	if(sym == CTimeFormat::Min)
		ret = CTimeFormat::tMin;
	if(sym == CTimeFormat::Sec)
		ret = CTimeFormat::tSec;
	if(sym == CTimeFormat::MSec)
		ret = CTimeFormat::tMSec;

	return ret;
}
//---------------------------------------------------------------
const CTimeFormat& CInterConfig::getTimeFormat()
{
	return (*LogTimeFormat);
}
//---------------------------------------------------------------
std::map<std::string,CInterConfig*> CInterConfig::InterConfContainer;
//--------------------------------------------------------------

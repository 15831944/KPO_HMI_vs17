// Copyright 2006 SMS - Demag AG
#include "stdafx.h"
#include "CSzenItem.h"

//------------------------------------------------------------------
CSzenItem::CSzenItem(CItemWrapper^ tlg,double time)
{
  Tlg = tlg->clone();
  Time = time;
  TimeDelay = 0.0;
  ChangeTime = 0.0;
  SendStatus = true;
  BreakPoint = false;
  ChangeFlag = false;
  IsCyclic = false;
  TimeBarredDelay = 0.0;
}
//------------------------------------------------------------------
void CSzenItem::setBarredDelay (double val)
{
  this->TimeBarredDelay = val;
}

//------------------------------------------------------------------
double CSzenItem::getBarredDelay()
{
  return this->TimeBarredDelay;
}
//------------------------------------------------------------------
void CSzenItem::setIsCyclic(bool cyclic)
{
  IsCyclic = cyclic;
}
//------------------------------------------------------------------
bool CSzenItem::getIsCyclic()
{
  return IsCyclic;
}
//------------------------------------------------------------------
CSzenItem::~CSzenItem()
{
}
//------------------------------------------------------------------
void CSzenItem::setDelay(double delay)
{
  TimeDelay = delay;
}
//------------------------------------------------------------------
void CSzenItem::setItem(CItemWrapper^ tlg)
{
  Tlg->clearWrapperTlg();
  Tlg=tlg;
}
//------------------------------------------------------------------
double CSzenItem::getDelay()
{
  return TimeDelay;
}
//-------------------------------------------------------------------
String^ CSzenItem::getItemName()
{
  return Tlg->getName();
}
//-------------------------------------------------------------------
double CSzenItem::getTime()
{
  return Time;
}
//-------------------------------------------------------------------
int CSzenItem::getSerializeTlg(char* buffer,int length)
{
  return Tlg->getSerializeTlg(buffer,length);
}
//--------------------------------------------
/*String^ CSzenItem::SerializeTlgAsByteStream()
{
    return Tlg->getSerializeTlgAsByteSteam();
}*/
//--------------------------------------------
String^ CSzenItem::SerializeTlgAsString()
{
  return Tlg->getSerialiseTlgAsString("|");
}
//-------------------------------------------
void CSzenItem::setSendStatus(bool stat)
{
  SendStatus=stat;
}
//--------------------------------------------
bool CSzenItem::getSendStatus()
{
  return SendStatus;
}
//--------------------------------------------
CItemWrapper^ CSzenItem::getTlgWrapper()
{
  return Tlg;
}
//--------------------------------------------
String^ CSzenItem::getItemAsString()
{
  return Tlg->getSerialiseTlgAsString("|");
}
//--------------------------------------------
String^ CSzenItem::getInterface()
{
  return Tlg->getInterfece();
}
//--------------------------------------------
void CSzenItem::clearItem()
{
  Tlg->clearWrapperTlg();
}
//--------------------------------------------
void CSzenItem::setTime(double time)
{
  Time = time;
}
//--------------------------------------------
CSzenItem^ CSzenItem::clone()
{
  CSzenItem^ ret = nullptr;
  ret = gcnew CSzenItem(Tlg,this->Time);
  ret->setBreakPoint(this->getBreakPoint());
  ret->setDelay(this->getDelay());
  ret->setSendStatus(this->getSendStatus());
  ret->setTime(this->getTime());
  if(getChangeTimeStatus())
  {
      ret->setChangeTime(this->getChangeTime());
  }
  return ret;
}
//--------------------------------------------
void CSzenItem::setBreakPoint(bool flag)
{
  BreakPoint = flag;
}
//--------------------------------------------
bool CSzenItem::getBreakPoint()
{
  return this->BreakPoint;
}
//--------------------------------------------
int CSzenItem::getTlgLen()
{
  return Tlg->getTlgLen();
}
//--------------------------------------------
void CSzenItem::setChangeTime(double changeTime)
{
  this->ChangeTime = changeTime;
  this->ChangeFlag = true;
}
//--------------------------------------------
void CSzenItem::acceptChangeTime(bool flag,double rel)
{
  if(flag)
  {
    //Time = (Time*ChangeTime)/TimeDelay; //tolik   
    //Time = Time +ChangeTime-TimeDelay; //richtig Time +(ChangeTime-TimeDelay)*rel;
    Time = Time +(ChangeTime-TimeDelay)*rel; //richtig Time +(ChangeTime-TimeDelay)*rel;
    TimeDelay = ChangeTime;
    ChangeTime=0.0;
    ChangeFlag=false;
  }
  else
  {
    ChangeTime=0.0;
    ChangeFlag=false;
  }
}
//--------------------------------------------
void CSzenItem::acceptChangeTime(bool flag,double rel,double t0,double d0)
{
  if(flag)
  {
    //Time = (Time*ChangeTime)/TimeDelay; //tolik   
    //Time = Time +ChangeTime-TimeDelay; //richtig Time +(ChangeTime-TimeDelay)*rel;
    Time = t0 +((ChangeTime/rel) - d0); //richtig Time +(ChangeTime-TimeDelay)*rel;
    TimeDelay = ChangeTime;
    ChangeTime=0.0;
    ChangeFlag=false;
  }
  else
  {
    ChangeTime=0.0;
    ChangeFlag=false;
  }
}

//--------------------------------------------
bool CSzenItem::getChangeTimeStatus()
{
  return ChangeFlag;
}

//--------------------------------------------
void CSzenItem::setChangeTimeStatus(bool status) 
{
  ChangeFlag=status;
}
//--------------------------------------------
double CSzenItem::getChangeTime()
{
  return this->ChangeTime;
}
//--------------------------------------------
int CSzenItem::getTlgTransBytesCount()
{
  return Tlg->getTlgTransBytesCount();
}
//--------------------------------------------
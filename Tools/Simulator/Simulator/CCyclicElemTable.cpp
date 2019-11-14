#include "stdafx.h"
#include "CCyclicElemTable.h"
#include "CFormatConverterWrapper.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CCyclicElemStatus.h"
#include "CTlgWrapper.h"

//------------------------------------------
CCyclicElemTable::CCyclicElemTable(CItemWrapper^ item)
{
  this->Item=item;
  elemTable = gcnew System::Collections::Hashtable();
  //Dafault Wert
  timeInterval = 10000;
  FillElemTable();
}
//------------------------------------------
CCyclicElemTable::~CCyclicElemTable()
{
}
//------------------------------------------
CItemWrapper^ CCyclicElemTable::getItem()
{
  return this->Item;
}
//------------------------------------------
int CCyclicElemTable::getTimeInterval()
{
  return timeInterval;
}
//------------------------------------------
int CCyclicElemTable::getElemCount()
{
  return elemTable->Count;
}
//------------------------------------------
Collections::ICollection^ CCyclicElemTable::getTableKeys()
{
  return elemTable->Keys;
}
//------------------------------------------
void CCyclicElemTable::updateElem(CTlgElemWrapper^ elem,CCyclicElemStatus^ status)
{
  elemTable[elem->getElemName()]=status;
  
  /*if (elemTable->ContainsKey(elem->getElemName()))
  {
    return false;
  }
  else
  {
    elemTable->Add(elem->getElemName(),status);
    return true;
  }*/
}
void CCyclicElemTable::updateElem(String^ elem,CCyclicElemStatus^ status)
{
  elemTable[elem] = status;
 /* if (elemTable->ContainsKey(elem))
  {
    return false;
  }
  else
  {
    elemTable->Add(elem,status);
    return true;
  }*/
}
//-------------------------------------------
bool CCyclicElemTable::updateElemStatus(CTlgElemWrapper^ elem,CCyclicElemStatus::changeTyp typ,
                     double max,double min,double variabelValue)
{
  if (! (elemTable->ContainsKey(elem->getElemName())) )
  {
    return false;
  }
  else
  {
    CCyclicElemStatus^ elemStatus = nullptr;
    elemStatus = safe_cast <CCyclicElemStatus^>(elemTable[elem->getElemName()]);
    if (elem)
    {
      elemStatus->setMaxValue(max);
      elemStatus->setMinValue(min);
      elemStatus->setVariabelTyp(typ);
      elemStatus->setVariabelValue(variabelValue);
      return true;
    }
    else
    {
      return false;
    }
  }  
}
//-------------------------------------------
void CCyclicElemTable::setTimeInterval(int time)
{
  this->timeInterval=time;
}
//-------------------------------------------
CCyclicElemStatus^ CCyclicElemTable::getElemStatus(String^ name)
{
  CCyclicElemStatus^ ret=nullptr;
  ret = safe_cast <CCyclicElemStatus^> (elemTable[name]);
  return ret;
}
//-------------------------------------------
CCyclicElemStatus^ CCyclicElemTable::getElemStatus(CTlgElemWrapper^ elem)
{
  CCyclicElemStatus^ ret=nullptr;
  ret = safe_cast <CCyclicElemStatus^> (elemTable[elem->getElemName()]);
  return ret;
}

//-------------------------------------------
String^ CCyclicElemTable::getItemName()
{
  return Item->getName();
}
//-------------------------------------------
String^ CCyclicElemTable::getInterfaceName()
{
  return Item->getInterfece();
}
//-------------------------------------------
void CCyclicElemTable::FillElemTable()
{
  CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
  for (int i=1;i<=Item->getTlgElemCount();i++)
  {
    elem->setTlgElem(Item->getElem(i));
    
    if (elem->getSubElemCount()>0)
      FillElemTable(elem);
    else if (elem->getElemType()->Equals("Double") || elem->getElemType()->Equals("Float")
			|| elem->getElemType()->Equals("Integer") || elem->getElemType()->Equals("ShortInteger"))
    {
      CCyclicElemStatus^ tmp = gcnew CCyclicElemStatus();
      //tmp->setDafaultDataTypeValuesForMinAndMax(elem);
      elemTable->Add(elem->getElemName(),tmp);
    }
  }
}
//-------------------------------------------
void CCyclicElemTable::FillElemTable(CTlgElemWrapper^ elem)
{
  CTlgElemWrapper^ subElem = gcnew CTlgElemWrapper();
  for (int i=1;i<=elem->getSubElemCount();i++)
  {
    subElem->setTlgElem(elem->getSubElem(i));
    
    if (subElem->getSubElemCount()>0)
      FillElemTable(subElem);
    else if (subElem->getElemType()->Equals("Double") || subElem->getElemType()->Equals("Float")
      || subElem->getElemType()->Equals("Integer") || subElem->getElemType()->Equals("ShortInteger"))
    {
      CCyclicElemStatus^ tmp = gcnew CCyclicElemStatus();
      //tmp->setDafaultDataTypeValuesForMinAndMax(subElem);
      elemTable->Add(subElem->getElemName(),tmp);
    }
  }
}
#include "stdafx.h"
#include "CCyclicElemStatus.h"
#include "CFormatConverterWrapper.h"

//------------------------------------------
CCyclicElemStatus::~CCyclicElemStatus()

{
}
//------------------------------------------
CCyclicElemStatus::CCyclicElemStatus()
{
  minValue = 0;
  maxValue = 10000;
	change = changeTyp::none;
	changeValue = 1;
}
//------------------------------------------
CCyclicElemStatus::CCyclicElemStatus(int typ, double value,double min, double max)
{
  minValue = min;
  maxValue = max;
	change = (changeTyp)typ;
	changeValue = value;
}
//------------------------------------------
CCyclicElemStatus::CCyclicElemStatus(changeTyp typ, double value,double min, double max)
{
  minValue = min;
  maxValue = max;
	change = typ;
	changeValue = value;
}
//------------------------------------------
double CCyclicElemStatus::getMaxValue()
{
  return maxValue;
}
//------------------------------------------
double CCyclicElemStatus::getMinValue()
{
  return minValue;
}
//------------------------------------------
double CCyclicElemStatus::getVariabelValue()
{
  return this->changeValue;
}
//------------------------------------------
CCyclicElemStatus::changeTyp CCyclicElemStatus::getVariabelTyp()
{
  return this->change;
}
//------------------------------------------
System::String^ CCyclicElemStatus::getVariabelTypAsString()
{
  if (change == changeTyp::plus)
    return "plu";
  else if (change == changeTyp::minus)
    return "minu";
  else if (change == changeTyp::multiple)
    return "multiple";
  else if (change == changeTyp::divide)
    return "divide";
  else
    return "none";
}
//------------------------------------------
void CCyclicElemStatus::setMaxValue(double maxValue)
{
  this->maxValue=maxValue;
}
//------------------------------------------
void CCyclicElemStatus::setMinValue(double minValue)
{
  this->minValue=minValue;
}
//------------------------------------------
void CCyclicElemStatus::setVariabelValue(double changeValue)
{
  this->changeValue=changeValue;
}
//------------------------------------------
void CCyclicElemStatus::setVariabelTyp(CCyclicElemStatus::changeTyp typ)
{
  this->change=typ;
}
//------------------------------------------
void CCyclicElemStatus::setMinimalAndMaximalValuesForMinAndMax(CTlgElemWrapper^ subElem)
{
 
  if (subElem == nullptr)
    return;

   String^ type = subElem->getElemType();

  //Default - Wert abhaengig vom Datentyp intialisieren
  if (type->Equals("Double"))
  {
    this->maxValue = Double::MaxValue;
    this->minValue = Double::MinValue;
    return;
  }
  if (type->Equals("Float"))
  {
    this->maxValue = Single::MaxValue; 
    this->minValue = Single::MinValue;
    return;
  }
  if (type->Equals("Integer"))
  {
    int lenght = subElem->getElemLenght();
    this->maxValue = (int)(Math::Pow(2,lenght*8-1))-1; 
    this->minValue = (int)Math::Pow(2,lenght*8-1)*(-1);
    return;
  }
  if (type->Equals("ShortInteger"))
  {
    int lenght = subElem->getElemLenght();
    this->maxValue = (int)Math::Pow(2,lenght*8); 
    this->minValue = (0);
    return;
  }
}
//-------------------------------------------
void CCyclicElemStatus::setMinimumValueForMin(CTlgElemWrapper^ subElem)
{
 
  if (subElem == nullptr)
    return;

   String^ type = subElem->getElemType();

  //Default - Wert abhaengig vom Datentyp intialisieren
  if (type->Equals("Double"))
  {
    this->minValue = Double::MinValue;
    return;
  }
  if (type->Equals("Float"))
  {
    this->minValue = Single::MinValue;
    return;
  }
  if (type->Equals("Integer"))
  {
    int lenght = subElem->getElemLenght();
    this->minValue = (int)Math::Pow(2,lenght*8-1)*(-1);
    return;
  }
  if (type->Equals("ShortInteger"))
  {
    int lenght = subElem->getElemLenght();
    this->minValue = (0);
    return;
  }
}
//-------------------------------------------
void CCyclicElemStatus::setMaximumValueForMax(CTlgElemWrapper^ subElem)
{
 
  if (subElem == nullptr)
    return;

   String^ type = subElem->getElemType();

  //Default - Wert abhaengig vom Datentyp intialisieren
  if (type->Equals("Double"))
  {
    this->maxValue = Double::MaxValue;
    return;
  }
  if (type->Equals("Float"))
  {
    this->maxValue = Single::MaxValue; 
    return;
  }
  if (type->Equals("Integer"))
  {
    int lenght = subElem->getElemLenght();
    this->maxValue = (int)(Math::Pow(2,lenght*8-1))-1; 
    return;
  }
  if (type->Equals("ShortInteger"))
  {
    int lenght = subElem->getElemLenght();
    this->maxValue = (int)Math::Pow(2,lenght*8); 
    return;
  }
}
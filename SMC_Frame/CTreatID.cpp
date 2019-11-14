// Copyright (C) 2004 SMS Demag AG


#include <valarray>
#include <sstream>
#include <algorithm>
#include <iomanip>


#include "cCBS_StdInitBase.h"

#include "CFormattedIDElement.h"

#include "CTreatID.h"



//##ModelId=439ECE040269
std::string CTreatID::m_QualifierPrefix("T");

//##ModelId=439ECE040273
std::string CTreatID::m_QualifierCounter("C");

//##ModelId=439ED57303DF
std::string CTreatID::m_QualifierSeparator("_");


//##ModelId=439ECDFE0110
CTreatID::~CTreatID()
{
}

//##ModelId=439ECDFE0115
CTreatID::CTreatID()
{
  this->init();
}

//##ModelId=439EDC1601E5
void CTreatID::init()
{
	// try to find TreatID Format at inifile, else use default
  std::string TreatIDFormat = "CCC";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","TreatIDFormat",TreatIDFormat);

  // setting format qualifier
  addFormattedIDElement(CTreatID::m_QualifierPrefix);
  addFormattedIDElement(CTreatID::m_QualifierCounter,CFormattedIDElement::Numeric);
  addFormattedIDElement(CTreatID::m_QualifierSeparator);


  // setting format accortinmg to actual TreatID Format 
  setFormat(TreatIDFormat);
}


//##ModelId=439ECDFE00F7
std::string CTreatID::getTreatID(const std::string Prefix, long Counter)
{
  return generateTreatID(Prefix, Counter);
}


//##ModelId=439ECDFE011F
long CTreatID::getMaxCounter()
{
  return (long)pow(10.,getCounterLength()) - 1;
}

//##ModelId=439ECDFE0129
long CTreatID::getCounter(const std::string& TreatID)
{
  return getLong(TreatID,m_TreatID,CTreatID::m_QualifierCounter);
}

//##ModelId=439ECDFE0133
long CTreatID::getCounterLength()
{
  // find Length of Qualifier "C" and calculate Length
  CFormattedIDElement* pFormattedIDElementCounter = getFormattedIDElement(CTreatID::m_QualifierCounter);

  return pFormattedIDElementCounter->getLength();
}

//##ModelId=439ECDFE013D
std::string CTreatID::getPrefix(const std::string& TreatID)
{
  return getString(TreatID,m_TreatID,CTreatID::m_QualifierPrefix);
}

//##ModelId=439ECDFE010B
std::string CTreatID::generateTreatID(const std::string Prefix, long Counter)
{
  // reset 
  m_TreatID.erase();

  std::stringstream ssCounter;
  ssCounter << Counter;

  // preset 
  m_TreatID.insert(0,m_FormattedIDLength,*CTreatID::m_QualifierSeparator.c_str());

  // build according to m_Format.
  generateString(CTreatID::m_QualifierPrefix,Prefix,m_TreatID);
  generateString(CTreatID::m_QualifierCounter,ssCounter.str(),m_TreatID,"0");

  return m_TreatID;
}

std::string CTreatID::generateNextTreatID(const std::string TreatID)
{
  return generateTreatID( getPrefix(TreatID) ,getCounter(TreatID) + 1 ) ;
}


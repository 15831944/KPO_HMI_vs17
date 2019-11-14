// Copyright (C) 2004 SMS Demag AG


#include <valarray>
#include <sstream>
#include <algorithm>
#include <iomanip>


#include "cCBS_StdInitBase.h"

#include "CFormattedIDElement.h"

#include "CTreatIDCust.h"



std::string CTreatIDCust::m_QualifierPrefix("T");

std::string CTreatIDCust::m_QualifierCounter("C");

std::string CTreatIDCust::m_QualifierSeparator("_");


CTreatIDCust::~CTreatIDCust()
{
}

CTreatIDCust::CTreatIDCust()
{
  this->init();
}

void CTreatIDCust::init()
{
	// try to find TreatIDCust Format at inifile, else use default
  std::string TreatIDCustFormat = "CCC";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","TreatIDCustFormat",TreatIDCustFormat);

  // setting format qualifier
  addFormattedIDElement(CTreatIDCust::m_QualifierPrefix);
  addFormattedIDElement(CTreatIDCust::m_QualifierCounter,CFormattedIDElement::Numeric);
  addFormattedIDElement(CTreatIDCust::m_QualifierSeparator);


  // setting format accortinmg to actual TreatIDCust Format 
  setFormat(TreatIDCustFormat);
}


std::string CTreatIDCust::getTreatID(const std::string Prefix, long Counter)
{
  return generateTreatID(Prefix, Counter);
}


long CTreatIDCust::getMaxCounter()
{
  return (long)pow(10.,getCounterLength()) - 1;
}

long CTreatIDCust::getCounter(const std::string& TreatIDCust)
{
  return getLong(TreatIDCust,m_TreatID,CTreatIDCust::m_QualifierCounter);
}

long CTreatIDCust::getCounterLength()
{
  // find Length of Qualifier "C" and calculate Length
  CFormattedIDElement* pFormattedIDElementCounter = getFormattedIDElement(CTreatIDCust::m_QualifierCounter);

  return pFormattedIDElementCounter->getLength();
}

std::string CTreatIDCust::getPrefix(const std::string& TreatIDCust)
{
  return getString(TreatIDCust,m_TreatID,CTreatIDCust::m_QualifierPrefix);
}

std::string CTreatIDCust::generateTreatID(const std::string Prefix, long Counter)
{
  // reset 
  m_TreatID.erase();

  std::stringstream ssCounter;
  ssCounter << Counter;

  // preset 
  m_TreatID.insert(0,m_FormattedIDLength,*CTreatIDCust::m_QualifierSeparator.c_str());

  // build according to m_Format.
  generateString(CTreatIDCust::m_QualifierPrefix,Prefix,m_TreatID);
  generateString(CTreatIDCust::m_QualifierCounter,ssCounter.str(),m_TreatID,"0");

  return m_TreatID;
}

std::string CTreatIDCust::generateNextTreatID(const std::string TreatIDCust)
{
  return generateTreatID( getPrefix(TreatIDCust) ,getCounter(TreatIDCust) + 1 ) ;
}


// Copyright (C) 2010 SMS Demag AG


#include <valarray>
#include <sstream>
#include <algorithm>
#include <iomanip>


#include "cCBS_StdInitBase.h"

#include "CFormattedIDElement.h"

#include "CHeatIDCust.h"

std::string CHeatIDCust::m_QualifierPrefix("P");

std::string CHeatIDCust::m_QualifierCounter("C");

std::string CHeatIDCust::m_QualifierSeparator("_");

CHeatIDCust::~CHeatIDCust()
{
}

CHeatIDCust::CHeatIDCust()
{
  this->init();
}

void CHeatIDCust::init()
{
	// try to find HeatIDCust Format at inifile, else use default
  std::string HeatIDCustFormat = "CCCCCCCCCC";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","HeatIDCustFormat",HeatIDCustFormat);

  // setting format qualifier
  addFormattedIDElement(CHeatIDCust::m_QualifierPrefix);
  addFormattedIDElement(CHeatIDCust::m_QualifierCounter,CFormattedIDElement::Numeric);
  addFormattedIDElement(CHeatIDCust::m_QualifierSeparator);


  // setting format accortinmg to actual HeatIDCust Format 
  setFormat(HeatIDCustFormat);
}

std::string CHeatIDCust::getHeatIDCust(const std::string Prefix, long Counter)
{
  return generateHeatIDCust(Prefix, Counter);
}

long CHeatIDCust::getMaxCounter()
{
  return (long)pow(10.,getCounterLength()) - 1;
}

long CHeatIDCust::getCounter(const std::string& HeatIDCust)
{
  return getLong(HeatIDCust,m_HeatIDCust,CHeatIDCust::m_QualifierCounter);
}

long CHeatIDCust::getCounterLength()
{
  // find Length of Qualifier "C" and calculate Length
  CFormattedIDElement* pFormattedIDElementCounter = getFormattedIDElement(CHeatIDCust::m_QualifierCounter);

  return pFormattedIDElementCounter->getLength();
}

std::string CHeatIDCust::getPrefix(const std::string& HeatIDCust)
{
  return getString(HeatIDCust,m_HeatIDCust,CHeatIDCust::m_QualifierPrefix);
}

std::string CHeatIDCust::generateHeatIDCust(const std::string Prefix, long Counter)
{
  // reset 
  m_HeatIDCust.erase();

  std::stringstream ssCounter;
  ssCounter << Counter;

  // preset 
  m_HeatIDCust.insert(0,m_FormattedIDLength,*CHeatIDCust::m_QualifierSeparator.c_str());

  // build according to m_Format.
  generateString(CHeatIDCust::m_QualifierPrefix,Prefix,m_HeatIDCust);
  generateString(CHeatIDCust::m_QualifierCounter,ssCounter.str(),m_HeatIDCust,"0");

  return m_HeatIDCust;
}

std::string CHeatIDCust::generateNextHeatIDCust(const std::string HeatIDCust)
{
  return generateHeatIDCust( getPrefix(HeatIDCust) ,getCounter(HeatIDCust) + 1 ) ;
}

std::string CHeatIDCust::generateNextHeatIDCust(const std::string Prefix, long Counter)
{
  return generateHeatIDCust( Prefix ,Counter + 1 ) ;
}

// Copyright (C) 2004 SMS Demag AG

#include <valarray>
#include <sstream>
#include <algorithm>
#include <iomanip>


#include "iSMC_DataDefinitions_s.hh"
#include "cCBS_StdInitBase.h"

#include "CFormattedIDElement.h"
#include "CSampleCode.h"


//##ModelId=43749B5D00A4
std::string CSampleCode::m_QualifierSampleType("T");

//##ModelId=43749B7B026D
std::string CSampleCode::m_QualifierPlantID("P");

//##ModelId=44FE9C2D02BB
std::string CSampleCode::m_QualifierPlantNo("N");

//##ModelId=43749B8700BE
std::string CSampleCode::m_QualifierProcessStage("S");

//##ModelId=43749B93009E
std::string CSampleCode::m_QualifierCounter("C");

std::string CSampleCode::m_QualifierLocation("L");

//##ModelId=4379A768000E
std::string CSampleCode::m_QualifierSeparator("_");

//##ModelId=4374988A0070
CSampleCode::CSampleCode()
{
  this->init();
}

//##ModelId=43749889021B
CSampleCode::~CSampleCode()
{
}


//##ModelId=439EDC1D0358
void CSampleCode::init()
{
	// try to find SampleCode Format at inifile, else use default
  std::string SampleCodeFormat = "TPNSSLLCC";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","SampleCodeFormat",SampleCodeFormat);

  // setting format qualifier
  addFormattedIDElement(CSampleCode::m_QualifierPlantID);
  addFormattedIDElement(CSampleCode::m_QualifierPlantNo);
  addFormattedIDElement(CSampleCode::m_QualifierCounter,CFormattedIDElement::Numeric);
  addFormattedIDElement(CSampleCode::m_QualifierLocation);
  addFormattedIDElement(CSampleCode::m_QualifierSampleType);
  addFormattedIDElement(CSampleCode::m_QualifierProcessStage);
  addFormattedIDElement(CSampleCode::m_QualifierSeparator);

  // setting format accortinmg to actual Sample Code Format 
  setFormat(SampleCodeFormat);
}



//##ModelId=437B44B90312
std::string CSampleCode::getSampleIDFromCode(const std::string& SampleCode)
{
  return getSampleID(getSampleType(SampleCode),getPlantId(SampleCode),getProcessStage(SampleCode));
}

//##ModelId=437497C501B0
std::string CSampleCode::getSampleID(const std::string SampleType, const std::string PlantID, const std::string ProcessStage)
{
  return generateSampleID(SampleType,PlantID,ProcessStage);
}

//##ModelId=4374983203C4
std::string CSampleCode::getSampleCode(const std::string SampleType, const std::string PlantID, const std::string ProcessStage, long Counter, const std::string Location)
{
  return generateSampleCode(SampleType, PlantID, ProcessStage, Counter, Location);
}

//##
std::string CSampleCode::getSampleCode(long SampleType, long Counter, const std::string Location)
{
  return generateSampleCode(SampleType, Counter, Location);
}

std::string CSampleCode::getSampleCode(long SampleType, const std::string PlantID, const std::string ProcessStage, long Counter, const std::string Location)
{
  return generateSampleCode(SampleType, PlantID, ProcessStage, Counter, Location);
}





//##ModelId=44FE9C2D02E2
std::string CSampleCode::generateSampleCode(long SampleType, long Counter, const std::string Location)
{
  
  // reset 
  m_SampleCode.erase();

  // preset 
  m_SampleCode.insert(0,m_FormattedIDLength,*CSampleCode::m_QualifierSeparator.c_str());

  std::stringstream ssCounter;
  ssCounter << Counter;

  std::stringstream ssSampleType;
  ssSampleType << SampleType;

  generateString(CSampleCode::m_QualifierSampleType,ssSampleType.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierLocation,Location,m_SampleCode,"XX");
  generateString(CSampleCode::m_QualifierCounter,ssCounter.str(),m_SampleCode,"00");


  return m_SampleCode;
}

//##ModelId=44FE9C2D02E2
std::string CSampleCode::generateSampleCode(long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long Counter, const std::string Location)
{
  // reset 
  m_SampleCode.erase();


  // preset 
  m_SampleCode.insert(0,m_FormattedIDLength,*CSampleCode::m_QualifierSeparator.c_str());

  // build according to m_Format.
  std::stringstream ssPlantNo;
  ssPlantNo << PlantNo;

  std::stringstream ssCounter;
  ssCounter << Counter;

  std::stringstream ssSampleType;
  ssSampleType << SampleType;

  generateString(CSampleCode::m_QualifierSampleType,ssSampleType.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierPlantID,PlantID,m_SampleCode);
  generateString(CSampleCode::m_QualifierPlantNo,ssPlantNo.str(),m_SampleCode);
  generateString(CSampleCode::m_QualifierProcessStage,ProcessStage,m_SampleCode);
  generateString(CSampleCode::m_QualifierCounter,ssCounter.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierLocation,Location,m_SampleCode);


  return m_SampleCode;
}

//##ModelId=43785AA1022A
std::string CSampleCode::generateSampleID(const std::string SampleType, const std::string PlantID, const std::string ProcessStage)
{
  // reset
  m_SampleID.erase();

  // preset
  m_SampleID.insert(0,m_FormattedIDLength - getCounterLength() ,*CSampleCode::m_QualifierSeparator.c_str());

  // build according to m_Format.
  generateString(CSampleCode::m_QualifierSampleType,SampleType,m_SampleID);
  generateString(CSampleCode::m_QualifierPlantID,PlantID,m_SampleID);
  generateString(CSampleCode::m_QualifierProcessStage,ProcessStage,m_SampleID);

  return m_SampleID;
}

//##ModelId=43785AAC0317
std::string CSampleCode::generateSampleCode(const std::string SampleType, const std::string PlantID, const std::string ProcessStage, long Counter, const std::string Location)
{
  // reset
  m_SampleCode.erase();

  // preset
  m_SampleCode.insert(0,m_FormattedIDLength,*CSampleCode::m_QualifierSeparator.c_str());

  // build according to m_Format.
  std::stringstream ssCounter;
  ssCounter << Counter;

  generateString(CSampleCode::m_QualifierSampleType,SampleType,m_SampleCode);
  generateString(CSampleCode::m_QualifierPlantID,PlantID,m_SampleCode);
  generateString(CSampleCode::m_QualifierProcessStage,ProcessStage,m_SampleCode);
  generateString(CSampleCode::m_QualifierCounter,ssCounter.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierLocation,Location,m_SampleCode);

  return m_SampleCode;
}


//##ModelId=4379C47C00A8
long CSampleCode::getMaxCounter()
{
  return (long)pow(10.,getCounterLength()) - 1;
}


//##ModelId=437A11FA0139
long CSampleCode::getCounter(const std::string& SampleCode)
{
  return getLong(SampleCode,m_SampleCode,CSampleCode::m_QualifierCounter);
}

//##ModelId=437A11A80203
long CSampleCode::getSampleType(const std::string& SampleCode)
{
  return getLong(SampleCode,m_SampleCode,CSampleCode::m_QualifierSampleType);
}

//##ModelId=44FE9C2D026A
long CSampleCode::getPlantNo(const std::string& SampleCode)
{
  return getLong(SampleCode,m_SampleCode,CSampleCode::m_QualifierPlantNo);
}

//##ModelId=437A11BD0256
std::string CSampleCode::getPlantId(const std::string& SampleCode)
{
  return getString(SampleCode,m_SampleCode,CSampleCode::m_QualifierPlantID);
}

std::string CSampleCode::getLocation(const std::string& SampleCode)
{
  return getString(SampleCode,m_SampleCode,CSampleCode::m_QualifierLocation);
}

//##ModelId=437A11CD00AC
std::string CSampleCode::getProcessStage(const std::string& SampleCode)
{
  return getString(SampleCode,m_SampleCode,CSampleCode::m_QualifierProcessStage);
}


//##ModelId=439EA5F10129
long CSampleCode::getCounterLength()
{
  long RetValue = 0;

  // find Length of Qualifier "C" and calculate Length
  RetValue += getLength(CSampleCode::m_QualifierCounter);

  return RetValue;
}

//##ModelId=44FE9C2D01F2
std::string CSampleCode::getSampleCode(long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long Counter)
{
  return generateSampleCode(SampleType, PlantID, PlantNo, ProcessStage, Counter, "");
}

//##ModelId=43F2130E0398
std::string CSampleCode::getSampleCode(long SampleType, const std::string PlantID, const std::string ProcessStage, long Counter)
{
  return generateSampleCode(SampleType, PlantID, ProcessStage, Counter, "");
}

//##ModelId=43F213B7039B
std::string CSampleCode::generateSampleCode(long SampleType, const std::string PlantID, const std::string ProcessStage, long Counter, const std::string Location)
{
  // reset
  m_SampleCode.erase();

  // preset
  m_SampleCode.insert(0,m_FormattedIDLength,*CSampleCode::m_QualifierSeparator.c_str());

  // build according to m_Format.
  std::stringstream ssCounter;
  ssCounter << Counter;

  std::stringstream ssSampleType;
  ssSampleType << SampleType;

  generateString(CSampleCode::m_QualifierSampleType,ssSampleType.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierPlantID,PlantID,m_SampleCode);
  generateString(CSampleCode::m_QualifierProcessStage,ProcessStage,m_SampleCode);
  generateString(CSampleCode::m_QualifierCounter,ssCounter.str(),m_SampleCode,"0");
  generateString(CSampleCode::m_QualifierLocation,Location,m_SampleCode);

  return m_SampleCode;
}





//##ModelId=43F2F2D70027
std::string CSampleCode::generateSampleID(long SampleType, const std::string PlantID, const std::string ProcessStage)
{
  // reset
  m_SampleID.erase();

  // preset
  m_SampleID.insert(0,m_FormattedIDLength - getCounterLength() ,*CSampleCode::m_QualifierSeparator.c_str());

  // build according to m_Format.
  std::stringstream ssSampleType;
  ssSampleType << SampleType;

  generateString(CSampleCode::m_QualifierSampleType,ssSampleType.str(),m_SampleID,"0");
  generateString(CSampleCode::m_QualifierPlantID,PlantID,m_SampleID);
  generateString(CSampleCode::m_QualifierProcessStage,ProcessStage,m_SampleID);

  return m_SampleID;
}



//##ModelId=43F2F3730343
std::string CSampleCode::getSampleID(long SampleType, const std::string PlantID, const std::string ProcessStage)
{
  return generateSampleID(SampleType,PlantID,ProcessStage);
}

//##ModelId=44FE9C2D0292
void CSampleCode::reset()
{
  m_SampleCode.erase();
  m_SampleID.erase();
}

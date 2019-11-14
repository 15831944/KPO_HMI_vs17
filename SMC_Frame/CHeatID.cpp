// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdInitBase.h"
#include "CHeatID.h"


//##ModelId=43FDD12B01AA
std::string CHeatID::m_QualifierHeatID("H");

//##ModelId=471C72590387
std::string CHeatID::m_QualifierSeparator("_");

std::string CHeatID::m_QualifierPlantIDPrefix("P");

//##ModelId=43FDD13F0180
CHeatID::~CHeatID()
{
}

//##ModelId=43FDD13F032F
CHeatID::CHeatID()
{
	this->init();
}

//##ModelId=43FDD1210227
void CHeatID::init()
{
	// try to find HeatID Format at inifile, else use default
  std::string HeatIDFormat = "HHHHHHHHHH";
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS","HeatIDFormat",HeatIDFormat);

  // setting format qualifier
  addFormattedIDElement(CHeatID::m_QualifierHeatID);
  addFormattedIDElement(CHeatID::m_QualifierSeparator);
  addFormattedIDElement(CHeatID::m_QualifierPlantIDPrefix);

  // setting format accortinmg to actual HeatID Format 
  setFormat(HeatIDFormat);
}

//##ModelId=44FE9C2E036C
std::string CHeatID::generateHeatID(const std::string ID, const std::string PlantPrefix)
{
  // reset 
  m_HeatID.erase();

  // preset 
  m_HeatID.insert(0,m_FormattedIDLength,*CHeatID::m_QualifierSeparator.c_str());

  // build according to m_Format.
  generateString(CHeatID::m_QualifierHeatID,ID,m_HeatID,"0");
  generateString(CHeatID::m_QualifierPlantIDPrefix,PlantPrefix,m_HeatID,"0");

  return m_HeatID;
}

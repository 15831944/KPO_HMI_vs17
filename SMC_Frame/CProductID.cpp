// Copyright (C) 2004 SMS Demag AG

#include <iostream>
#include <sstream>

#include "iSMC_DataDefinitions_s.hh"

#include "CProductID.h"


std::string CProductID::m_QualifierSeparator("_");

std::string CProductID::getProductID(const std::string& HeatID, const std::string& TreatID)
{
  std::string ID = HeatID + CProductID::m_QualifierSeparator + TreatID ;
  
  return ID;
}

std::string CProductID::getHeatID(const std::string& ProductID)
{
  std::string RetValue = DEF::Inv_String;

  long Position = -1;

  if ( std::string::npos != (Position = (long)ProductID.find_first_of(CProductID::m_QualifierSeparator)) )
  {
    RetValue = ProductID.substr(0,Position);
  }

  return RetValue;
}

std::string CProductID::getTreatID(const std::string& ProductID)
{
  std::string RetValue = DEF::Inv_String;

  long Position = -1;

  if ( std::string::npos != (Position = (long)ProductID.find_first_of(CProductID::m_QualifierSeparator)) )
  {
    RetValue = ProductID.substr(Position + 1 ,ProductID.length());
  }

  return RetValue;
}

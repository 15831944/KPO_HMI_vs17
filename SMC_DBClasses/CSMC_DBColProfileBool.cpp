// Copyright (C) 2004 SMS Demag AG

#include "CSMC_DBColProfileBool.h"

//##ModelId=41513350002A
CSMC_DBColProfileBool::CSMC_DBColProfileBool(const std::string &TableName, const std::string &ColName)
: CSMC_DBColProfile(TableName,SMC_DB_Bool,ColName)
{
}

//##ModelId=415133500265
CSMC_DBColProfileBool::~CSMC_DBColProfileBool()
{
}




//##ModelId=41AC4EC303C2
std::string CSMC_DBColProfileBool::getSQLString()
{
  std::stringstream strValue;
  strValue << m_value ;
	
  return strValue.str();
}


//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.5.8 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CMDB_GRADE_ELEMENTS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
CMDB_GRADE_ELEMENTS::CMDB_GRADE_ELEMENTS(cCBS_Connection* Connection)
:CSMC_DBData("MDB_GRADE_ELEMENTS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CMDB_GRADE_ELEMENTS::~CMDB_GRADE_ELEMENTS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CMDB_GRADE_ELEMENTS::getSTEEL_GRADE_ID(long Row)
{
 return getString("STEEL_GRADE_ID", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setSTEEL_GRADE_ID(const std::string& value)
{
  setString("STEEL_GRADE_ID", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CMDB_GRADE_ELEMENTS::getELEMENT_CODE(long Row)
{
  return getLong("ELEMENT_CODE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setELEMENT_CODE(long value)
{
  setLong("ELEMENT_CODE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CMDB_GRADE_ELEMENTS::getMIN_VALUE(long Row)
{
  return getDouble("MIN_VALUE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setMIN_VALUE(double value)
{
  setDouble("MIN_VALUE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CMDB_GRADE_ELEMENTS::getAIM_VALUE(long Row)
{
  return getDouble("AIM_VALUE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setAIM_VALUE(double value)
{
  setDouble("AIM_VALUE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CMDB_GRADE_ELEMENTS::getMAX_VALUE(long Row)
{
  return getDouble("MAX_VALUE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setMAX_VALUE(double value)
{
  setDouble("MAX_VALUE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CMDB_GRADE_ELEMENTS::getQUALIFIER(long Row)
{
 return getString("QUALIFIER", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_GRADE_ELEMENTS::setQUALIFIER(const std::string& value)
{
  setString("QUALIFIER", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CMDB_GRADE_ELEMENTS::select(const std::string& STEEL_GRADE_ID, long ELEMENT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause("STEEL_GRADE_ID",STEEL_GRADE_ID);
  addWhereClause("ELEMENT_CODE",ELEMENT_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 


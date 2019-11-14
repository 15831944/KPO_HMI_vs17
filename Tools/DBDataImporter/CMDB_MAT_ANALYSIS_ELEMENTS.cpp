//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.5.8 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CMDB_MAT_ANALYSIS_ELEMENTS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
CMDB_MAT_ANALYSIS_ELEMENTS::CMDB_MAT_ANALYSIS_ELEMENTS(cCBS_Connection* Connection)
:CSMC_DBData("MDB_MAT_ANALYSIS_ELEMENTS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CMDB_MAT_ANALYSIS_ELEMENTS::~CMDB_MAT_ANALYSIS_ELEMENTS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CMDB_MAT_ANALYSIS_ELEMENTS::getMATERIAL_ID(long Row)
{
 return getString("MATERIAL_ID", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_MAT_ANALYSIS_ELEMENTS::setMATERIAL_ID(const std::string& value)
{
  setString("MATERIAL_ID", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CMDB_MAT_ANALYSIS_ELEMENTS::getELEMENT_CODE(long Row)
{
  return getLong("ELEMENT_CODE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_MAT_ANALYSIS_ELEMENTS::setELEMENT_CODE(long value)
{
  setLong("ELEMENT_CODE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CMDB_MAT_ANALYSIS_ELEMENTS::getVALUE(long Row)
{
  return getDouble("VALUE", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_MAT_ANALYSIS_ELEMENTS::setVALUE(double value)
{
  setDouble("VALUE", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CMDB_MAT_ANALYSIS_ELEMENTS::getAIR_OX_YIELD(long Row)
{
  return getDouble("AIR_OX_YIELD", Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CMDB_MAT_ANALYSIS_ELEMENTS::setAIR_OX_YIELD(double value)
{
  setDouble("AIR_OX_YIELD", value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CMDB_MAT_ANALYSIS_ELEMENTS::select(const std::string& MATERIAL_ID, long ELEMENT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause("MATERIAL_ID",MATERIAL_ID);
  addWhereClause("ELEMENT_CODE",ELEMENT_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_MEASUREMENT_TYPE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_MEASUREMENT_TYPE::MEASTYPENO("MEASTYPENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_MEASUREMENT_TYPE::MEASTYPENAME("MEASTYPENAME");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_TYPE::CGC_MEASUREMENT_TYPE(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_MEASUREMENT_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_TYPE::CGC_MEASUREMENT_TYPE(cCBS_Connection* Connection)
:CSMC_DBData("GC_MEASUREMENT_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_TYPE::CGC_MEASUREMENT_TYPE()
:CSMC_DBData("GC_MEASUREMENT_TYPE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_TYPE::~CGC_MEASUREMENT_TYPE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Identifies the type of measurement
long CGC_MEASUREMENT_TYPE::getMEASTYPENO(long Row)
{
  return getLong(CGC_MEASUREMENT_TYPE::MEASTYPENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_MEASUREMENT_TYPE::setMEASTYPENO(long value)
{
  setLong(CGC_MEASUREMENT_TYPE::MEASTYPENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Identifies the name of measurement
std::string CGC_MEASUREMENT_TYPE::getMEASTYPENAME(long Row)
{
  return getString(CGC_MEASUREMENT_TYPE::MEASTYPENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_MEASUREMENT_TYPE::setMEASTYPENAME(const std::string& value)
{
  setString(CGC_MEASUREMENT_TYPE::MEASTYPENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_MEASUREMENT_TYPE::select(long MEASTYPENO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_MEASUREMENT_TYPE::MEASTYPENO,MEASTYPENO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



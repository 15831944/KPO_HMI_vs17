//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_SCRAP_CONTAINER_TYPE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_SCRAP_CONTAINER_TYPE::CONTAINERTYPE("CONTAINERTYPE");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_SCRAP_CONTAINER_TYPE::CGC_SCRAP_CONTAINER_TYPE(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_SCRAP_CONTAINER_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_SCRAP_CONTAINER_TYPE::CGC_SCRAP_CONTAINER_TYPE(cCBS_Connection* Connection)
:CSMC_DBData("GC_SCRAP_CONTAINER_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_SCRAP_CONTAINER_TYPE::CGC_SCRAP_CONTAINER_TYPE()
:CSMC_DBData("GC_SCRAP_CONTAINER_TYPE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_SCRAP_CONTAINER_TYPE::~CGC_SCRAP_CONTAINER_TYPE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##basket or chute
std::string CGC_SCRAP_CONTAINER_TYPE::getCONTAINERTYPE(long Row)
{
  return getString(CGC_SCRAP_CONTAINER_TYPE::CONTAINERTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_SCRAP_CONTAINER_TYPE::setCONTAINERTYPE(const std::string& value)
{
  setString(CGC_SCRAP_CONTAINER_TYPE::CONTAINERTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_SCRAP_CONTAINER_TYPE::select(const std::string& CONTAINERTYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_SCRAP_CONTAINER_TYPE::CONTAINERTYPE,CONTAINERTYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



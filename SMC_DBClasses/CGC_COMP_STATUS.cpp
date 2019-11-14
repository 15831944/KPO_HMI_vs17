//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_COMP_STATUS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMP_STATUS::STATUS("STATUS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMP_STATUS::STATUSDESCR("STATUSDESCR");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMP_STATUS::CGC_COMP_STATUS(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_COMP_STATUS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMP_STATUS::CGC_COMP_STATUS(cCBS_Connection* Connection)
:CSMC_DBData("GC_COMP_STATUS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMP_STATUS::CGC_COMP_STATUS()
:CSMC_DBData("GC_COMP_STATUS")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMP_STATUS::~CGC_COMP_STATUS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGC_COMP_STATUS::getSTATUS(long Row)
{
  return getLong(CGC_COMP_STATUS::STATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMP_STATUS::setSTATUS(long value)
{
  setLong(CGC_COMP_STATUS::STATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGC_COMP_STATUS::getSTATUSDESCR(long Row)
{
  return getString(CGC_COMP_STATUS::STATUSDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMP_STATUS::setSTATUSDESCR(const std::string& value)
{
  setString(CGC_COMP_STATUS::STATUSDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_COMP_STATUS::select(long STATUS)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_COMP_STATUS::STATUS,STATUS);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



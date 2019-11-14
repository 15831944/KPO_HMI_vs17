//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGCH_TREAT_TYPE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCH_TREAT_TYPE::TREAT_TYPE("TREAT_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCH_TREAT_TYPE::TREAT_TYPE_DESC("TREAT_TYPE_DESC");

//##DBClassCodeUtility ! DO NOT EDIT !
CGCH_TREAT_TYPE::CGCH_TREAT_TYPE(cCBS_StdConnection* Connection)
:CSMC_DBData("GCH_TREAT_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCH_TREAT_TYPE::CGCH_TREAT_TYPE(cCBS_Connection* Connection)
:CSMC_DBData("GCH_TREAT_TYPE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCH_TREAT_TYPE::CGCH_TREAT_TYPE()
:CSMC_DBData("GCH_TREAT_TYPE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCH_TREAT_TYPE::~CGCH_TREAT_TYPE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGCH_TREAT_TYPE::getTREAT_TYPE(long Row)
{
  return getLong(CGCH_TREAT_TYPE::TREAT_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCH_TREAT_TYPE::setTREAT_TYPE(long value)
{
  setLong(CGCH_TREAT_TYPE::TREAT_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGCH_TREAT_TYPE::getTREAT_TYPE_DESC(long Row)
{
  return getString(CGCH_TREAT_TYPE::TREAT_TYPE_DESC, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCH_TREAT_TYPE::setTREAT_TYPE_DESC(const std::string& value)
{
  setString(CGCH_TREAT_TYPE::TREAT_TYPE_DESC, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGCH_TREAT_TYPE::select(long TREAT_TYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGCH_TREAT_TYPE::TREAT_TYPE,TREAT_TYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



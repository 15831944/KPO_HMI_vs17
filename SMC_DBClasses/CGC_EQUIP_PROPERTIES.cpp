//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_EQUIP_PROPERTIES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_PROPERTIES::EQUIP_TYPE("EQUIP_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_PROPERTIES::PROPERTY("PROPERTY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_PROPERTIES::REMARK("REMARK");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_PROPERTIES::CGC_EQUIP_PROPERTIES(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_EQUIP_PROPERTIES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_PROPERTIES::CGC_EQUIP_PROPERTIES(cCBS_Connection* Connection)
:CSMC_DBData("GC_EQUIP_PROPERTIES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_PROPERTIES::CGC_EQUIP_PROPERTIES()
:CSMC_DBData("GC_EQUIP_PROPERTIES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_PROPERTIES::~CGC_EQUIP_PROPERTIES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment type 
std::string CGC_EQUIP_PROPERTIES::getEQUIP_TYPE(long Row)
{
  return getString(CGC_EQUIP_PROPERTIES::EQUIP_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_PROPERTIES::setEQUIP_TYPE(const std::string& value)
{
  setString(CGC_EQUIP_PROPERTIES::EQUIP_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of the property
std::string CGC_EQUIP_PROPERTIES::getPROPERTY(long Row)
{
  return getString(CGC_EQUIP_PROPERTIES::PROPERTY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_PROPERTIES::setPROPERTY(const std::string& value)
{
  setString(CGC_EQUIP_PROPERTIES::PROPERTY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Remark / Comment
std::string CGC_EQUIP_PROPERTIES::getREMARK(long Row)
{
  return getString(CGC_EQUIP_PROPERTIES::REMARK, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_PROPERTIES::setREMARK(const std::string& value)
{
  setString(CGC_EQUIP_PROPERTIES::REMARK, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_EQUIP_PROPERTIES::select(const std::string& EQUIP_TYPE, const std::string& PROPERTY)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_EQUIP_PROPERTIES::EQUIP_TYPE,EQUIP_TYPE);
  addWhereClause(CGC_EQUIP_PROPERTIES::PROPERTY,PROPERTY);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



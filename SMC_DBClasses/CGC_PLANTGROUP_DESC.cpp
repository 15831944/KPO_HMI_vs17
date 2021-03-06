//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_PLANTGROUP_DESC.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP_DESC::UNITGROUPNO("UNITGROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP_DESC::UNITGROUPDESCR("UNITGROUPDESCR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP_DESC::HIERARCHY("HIERARCHY");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP_DESC::CGC_PLANTGROUP_DESC(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_PLANTGROUP_DESC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP_DESC::CGC_PLANTGROUP_DESC(cCBS_Connection* Connection)
:CSMC_DBData("GC_PLANTGROUP_DESC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP_DESC::CGC_PLANTGROUP_DESC()
:CSMC_DBData("GC_PLANTGROUP_DESC")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP_DESC::~CGC_PLANTGROUP_DESC()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unit group number, see GC_PLANT_GROUP
long CGC_PLANTGROUP_DESC::getUNITGROUPNO(long Row)
{
  return getLong(CGC_PLANTGROUP_DESC::UNITGROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP_DESC::setUNITGROUPNO(long value)
{
  setLong(CGC_PLANTGROUP_DESC::UNITGROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGC_PLANTGROUP_DESC::getUNITGROUPDESCR(long Row)
{
  return getString(CGC_PLANTGROUP_DESC::UNITGROUPDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP_DESC::setUNITGROUPDESCR(const std::string& value)
{
  setString(CGC_PLANTGROUP_DESC::UNITGROUPDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGC_PLANTGROUP_DESC::getHIERARCHY(long Row)
{
  return getLong(CGC_PLANTGROUP_DESC::HIERARCHY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP_DESC::setHIERARCHY(long value)
{
  setLong(CGC_PLANTGROUP_DESC::HIERARCHY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_PLANTGROUP_DESC::select(long UNITGROUPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PLANTGROUP_DESC::UNITGROUPNO,UNITGROUPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



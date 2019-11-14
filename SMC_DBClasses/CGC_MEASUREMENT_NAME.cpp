//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_MEASUREMENT_NAME.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_MEASUREMENT_NAME::MEASNAME("MEASNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_MEASUREMENT_NAME::SCOPENO("SCOPENO");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_NAME::CGC_MEASUREMENT_NAME(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_MEASUREMENT_NAME",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_NAME::CGC_MEASUREMENT_NAME(cCBS_Connection* Connection)
:CSMC_DBData("GC_MEASUREMENT_NAME",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_NAME::CGC_MEASUREMENT_NAME()
:CSMC_DBData("GC_MEASUREMENT_NAME")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_MEASUREMENT_NAME::~CGC_MEASUREMENT_NAME()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Measured Element/compound names for analysis, or names like TEMP, EMF or other measuremens
std::string CGC_MEASUREMENT_NAME::getMEASNAME(long Row)
{
  return getString(CGC_MEASUREMENT_NAME::MEASNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_MEASUREMENT_NAME::setMEASNAME(const std::string& value)
{
  setString(CGC_MEASUREMENT_NAME::MEASNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Type specifier
long CGC_MEASUREMENT_NAME::getSCOPENO(long Row)
{
  return getLong(CGC_MEASUREMENT_NAME::SCOPENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_MEASUREMENT_NAME::setSCOPENO(long value)
{
  setLong(CGC_MEASUREMENT_NAME::SCOPENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_MEASUREMENT_NAME::select(const std::string& MEASNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_MEASUREMENT_NAME::MEASNAME,MEASNAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGC_MEASUREMENT_NAME::isOfElement(const std::string &MEASNAME, long SCOPENO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_MEASUREMENT_NAME::MEASNAME,MEASNAME);
  addWhereClause(CGC_MEASUREMENT_NAME::SCOPENO,SCOPENO);

  addWhereClause(CGC_MEASUREMENT_NAME::MEASNAME + " is not null");
  addWhereClause(CGC_MEASUREMENT_NAME::SCOPENO + " is not null");

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}



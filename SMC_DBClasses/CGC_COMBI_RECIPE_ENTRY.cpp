//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_COMBI_RECIPE_ENTRY.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::COMBINATION_NAME("COMBINATION_NAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::RECIPENAME("RECIPENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::SOURCE("SOURCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::RESTRITYPE("RESTRITYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_COMBI_RECIPE_ENTRY::DESCR_PP("DESCR_PP");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMBI_RECIPE_ENTRY::CGC_COMBI_RECIPE_ENTRY(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_COMBI_RECIPE_ENTRY",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMBI_RECIPE_ENTRY::CGC_COMBI_RECIPE_ENTRY(cCBS_Connection* Connection)
:CSMC_DBData("GC_COMBI_RECIPE_ENTRY",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMBI_RECIPE_ENTRY::CGC_COMBI_RECIPE_ENTRY()
:CSMC_DBData("GC_COMBI_RECIPE_ENTRY")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_COMBI_RECIPE_ENTRY::~CGC_COMBI_RECIPE_ENTRY()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_COMBI_RECIPE_ENTRY::getPLANT(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setPLANT(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of this combination
std::string CGC_COMBI_RECIPE_ENTRY::getCOMBINATION_NAME(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::COMBINATION_NAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setCOMBINATION_NAME(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::COMBINATION_NAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Recipes defined for this group.
std::string CGC_COMBI_RECIPE_ENTRY::getRECIPENAME(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::RECIPENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setRECIPENAME(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::RECIPENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Valid Sources of a Recipe., SOURCE = ALL means all SOURCES for the recipe
std::string CGC_COMBI_RECIPE_ENTRY::getSOURCE(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::SOURCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setSOURCE(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::SOURCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Restriction type according model interface., (eg. Relative, Absolute,...)
std::string CGC_COMBI_RECIPE_ENTRY::getRESTRITYPE(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::RESTRITYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setRESTRITYPE(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::RESTRITYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of practice pointer or practice group
std::string CGC_COMBI_RECIPE_ENTRY::getDESCR_PP(long Row)
{
  return getString(CGC_COMBI_RECIPE_ENTRY::DESCR_PP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_COMBI_RECIPE_ENTRY::setDESCR_PP(const std::string& value)
{
  setString(CGC_COMBI_RECIPE_ENTRY::DESCR_PP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_COMBI_RECIPE_ENTRY::select(const std::string& PLANT, const std::string& COMBINATION_NAME, const std::string& RECIPENAME, const std::string& SOURCE, const std::string& RESTRITYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_COMBI_RECIPE_ENTRY::PLANT,PLANT);
  addWhereClause(CGC_COMBI_RECIPE_ENTRY::COMBINATION_NAME,COMBINATION_NAME);
  addWhereClause(CGC_COMBI_RECIPE_ENTRY::RECIPENAME,RECIPENAME);
  addWhereClause(CGC_COMBI_RECIPE_ENTRY::SOURCE,SOURCE);
  addWhereClause(CGC_COMBI_RECIPE_ENTRY::RESTRITYPE,RESTRITYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGC_COMBI_RECIPE_ENTRY::selectByPlant(const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_COMBI_RECIPE_ENTRY::PLANT,PLANT);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}



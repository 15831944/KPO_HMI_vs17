//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_RECIPE_SOURCE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_RECIPE_SOURCE::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_RECIPE_SOURCE::RECIPENAME("RECIPENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_RECIPE_SOURCE::SOURCE("SOURCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_RECIPE_SOURCE::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_RECIPE_SOURCE::CGC_RECIPE_SOURCE(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_RECIPE_SOURCE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_RECIPE_SOURCE::CGC_RECIPE_SOURCE(cCBS_Connection* Connection)
:CSMC_DBData("GC_RECIPE_SOURCE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_RECIPE_SOURCE::CGC_RECIPE_SOURCE()
:CSMC_DBData("GC_RECIPE_SOURCE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_RECIPE_SOURCE::~CGC_RECIPE_SOURCE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_RECIPE_SOURCE::getPLANT(long Row)
{
  return getString(CGC_RECIPE_SOURCE::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_RECIPE_SOURCE::setPLANT(const std::string& value)
{
  setString(CGC_RECIPE_SOURCE::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Recipe name
std::string CGC_RECIPE_SOURCE::getRECIPENAME(long Row)
{
  return getString(CGC_RECIPE_SOURCE::RECIPENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_RECIPE_SOURCE::setRECIPENAME(const std::string& value)
{
  setString(CGC_RECIPE_SOURCE::RECIPENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Valid Sources of a Recipe., SOURCE = ALL means all SOURCES for the recipe
std::string CGC_RECIPE_SOURCE::getSOURCE(long Row)
{
  return getString(CGC_RECIPE_SOURCE::SOURCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_RECIPE_SOURCE::setSOURCE(const std::string& value)
{
  setString(CGC_RECIPE_SOURCE::SOURCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Display order in RecipePurposeOverview
long CGC_RECIPE_SOURCE::getDISPLAY_ORDER(long Row)
{
  return getLong(CGC_RECIPE_SOURCE::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_RECIPE_SOURCE::setDISPLAY_ORDER(long value)
{
  setLong(CGC_RECIPE_SOURCE::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_RECIPE_SOURCE::select(const std::string& PLANT, const std::string& RECIPENAME, const std::string& SOURCE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_RECIPE_SOURCE::PLANT,PLANT);
  addWhereClause(CGC_RECIPE_SOURCE::RECIPENAME,RECIPENAME);
  addWhereClause(CGC_RECIPE_SOURCE::SOURCE,SOURCE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGC_RECIPE_SOURCE::selectByPlant(const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_RECIPE_SOURCE::PLANT,PLANT);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}



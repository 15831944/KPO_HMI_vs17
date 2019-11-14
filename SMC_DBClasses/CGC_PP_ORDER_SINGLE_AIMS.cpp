//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_PP_ORDER_SINGLE_AIMS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PP_ORDER_SINGLE_AIMS::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PP_ORDER_SINGLE_AIMS::TYPE("TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PP_ORDER_SINGLE_AIMS::VARNAME("VARNAME");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PP_ORDER_SINGLE_AIMS::CGC_PP_ORDER_SINGLE_AIMS(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_PP_ORDER_SINGLE_AIMS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PP_ORDER_SINGLE_AIMS::CGC_PP_ORDER_SINGLE_AIMS(cCBS_Connection* Connection)
:CSMC_DBData("GC_PP_ORDER_SINGLE_AIMS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PP_ORDER_SINGLE_AIMS::CGC_PP_ORDER_SINGLE_AIMS()
:CSMC_DBData("GC_PP_ORDER_SINGLE_AIMS")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PP_ORDER_SINGLE_AIMS::~CGC_PP_ORDER_SINGLE_AIMS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_PP_ORDER_SINGLE_AIMS::getPLANT(long Row)
{
  return getString(CGC_PP_ORDER_SINGLE_AIMS::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PP_ORDER_SINGLE_AIMS::setPLANT(const std::string& value)
{
  setString(CGC_PP_ORDER_SINGLE_AIMS::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specifies data type of value. 1=long, 2=double,3=string
long CGC_PP_ORDER_SINGLE_AIMS::getTYPE(long Row)
{
  return getLong(CGC_PP_ORDER_SINGLE_AIMS::TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PP_ORDER_SINGLE_AIMS::setTYPE(long value)
{
  setLong(CGC_PP_ORDER_SINGLE_AIMS::TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGC_PP_ORDER_SINGLE_AIMS::getVARNAME(long Row)
{
  return getString(CGC_PP_ORDER_SINGLE_AIMS::VARNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PP_ORDER_SINGLE_AIMS::setVARNAME(const std::string& value)
{
  setString(CGC_PP_ORDER_SINGLE_AIMS::VARNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_PP_ORDER_SINGLE_AIMS::select(const std::string& PLANT, long TYPE, const std::string& VARNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PP_ORDER_SINGLE_AIMS::PLANT,PLANT);
  addWhereClause(CGC_PP_ORDER_SINGLE_AIMS::TYPE,TYPE);
  addWhereClause(CGC_PP_ORDER_SINGLE_AIMS::VARNAME,VARNAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

long CGC_PP_ORDER_SINGLE_AIMS::getTypeDirectly(const std::string& PLANT, const std::string& VARNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PP_ORDER_SINGLE_AIMS::PLANT,PLANT);
  addWhereClause(CGC_PP_ORDER_SINGLE_AIMS::VARNAME,VARNAME);

  m_Statement += getWhereStatement() + ";";

  if ((CSMC_DBData::select()) && (CSMC_DBData::getLastRow() == 1))
  {
    return getTYPE(1);
  }
  else
  {
    if (CSMC_DBData::getLastRow() > 1)
      log("ERROR: PLANT and VARNAME are not unique!", 1);

    return CSMC_DBData::unspecLong;
  }
}



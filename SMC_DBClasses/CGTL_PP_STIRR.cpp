//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTL_PP_STIRR.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::DESCR_E("DESCR_E");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::DESCR_C("DESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTL_PP_STIRR::USERCODE("USERCODE");

//##DBClassCodeUtility ! DO NOT EDIT !
CGTL_PP_STIRR::CGTL_PP_STIRR(cCBS_StdConnection* Connection)
:CSMC_DBData("GTL_PP_STIRR",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTL_PP_STIRR::CGTL_PP_STIRR(cCBS_Connection* Connection)
:CSMC_DBData("GTL_PP_STIRR",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTL_PP_STIRR::CGTL_PP_STIRR()
:CSMC_DBData("GTL_PP_STIRR")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTL_PP_STIRR::~CGTL_PP_STIRR()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTL_PP_STIRR::getPLANTNO(long Row)
{
  return getLong(CGTL_PP_STIRR::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setPLANTNO(long value)
{
  setLong(CGTL_PP_STIRR::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTL_PP_STIRR::getPRACNO(long Row)
{
  return getLong(CGTL_PP_STIRR::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setPRACNO(long value)
{
  setLong(CGTL_PP_STIRR::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CGTL_PP_STIRR::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CGTL_PP_STIRR::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setREVTIME(const CDateTime& value)
{
 setString(CGTL_PP_STIRR::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTL_PP_STIRR::getDESCR_E(long Row)
{
  return getString(CGTL_PP_STIRR::DESCR_E, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setDESCR_E(const std::string& value)
{
  setString(CGTL_PP_STIRR::DESCR_E, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTL_PP_STIRR::getDESCR_C(long Row)
{
  return getString(CGTL_PP_STIRR::DESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setDESCR_C(const std::string& value)
{
  setString(CGTL_PP_STIRR::DESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTL_PP_STIRR::getUSERCODE(long Row)
{
  return getString(CGTL_PP_STIRR::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTL_PP_STIRR::setUSERCODE(const std::string& value)
{
  setString(CGTL_PP_STIRR::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGTL_PP_STIRR::select(long PLANTNO, long PRACNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGTL_PP_STIRR::PLANTNO,PLANTNO);
  addWhereClause(CGTL_PP_STIRR::PRACNO,PRACNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



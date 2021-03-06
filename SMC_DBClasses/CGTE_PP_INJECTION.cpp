//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_INJECTION.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::DEVICENAME("DEVICENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::DESCR_E("DESCR_E");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::DESCR_C("DESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_INJECTION::USERCODE("USERCODE");

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_INJECTION::CGTE_PP_INJECTION(cCBS_StdConnection* Connection)
:CSMC_DBData("GTE_PP_INJECTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_INJECTION::CGTE_PP_INJECTION(cCBS_Connection* Connection)
:CSMC_DBData("GTE_PP_INJECTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_INJECTION::CGTE_PP_INJECTION()
:CSMC_DBData("GTE_PP_INJECTION")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_INJECTION::~CGTE_PP_INJECTION()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_INJECTION::getPLANT(long Row)
{
  return getString(CGTE_PP_INJECTION::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setPLANT(const std::string& value)
{
  setString(CGTE_PP_INJECTION::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_INJECTION::getPLANTNO(long Row)
{
  return getLong(CGTE_PP_INJECTION::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setPLANTNO(long value)
{
  setLong(CGTE_PP_INJECTION::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_INJECTION::getPRACNO(long Row)
{
  return getLong(CGTE_PP_INJECTION::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setPRACNO(long value)
{
  setLong(CGTE_PP_INJECTION::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_INJECTION::getTREATMODENO(long Row)
{
  return getLong(CGTE_PP_INJECTION::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setTREATMODENO(long value)
{
  setLong(CGTE_PP_INJECTION::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_INJECTION::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CGTE_PP_INJECTION::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CGTE_PP_INJECTION::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_INJECTION::getDEVICENAME(long Row)
{
  return getString(CGTE_PP_INJECTION::DEVICENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setDEVICENAME(const std::string& value)
{
  setString(CGTE_PP_INJECTION::DEVICENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CGTE_PP_INJECTION::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CGTE_PP_INJECTION::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setREVTIME(const CDateTime& value)
{
 setString(CGTE_PP_INJECTION::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_INJECTION::getDESCR_E(long Row)
{
  return getString(CGTE_PP_INJECTION::DESCR_E, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setDESCR_E(const std::string& value)
{
  setString(CGTE_PP_INJECTION::DESCR_E, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_INJECTION::getDESCR_C(long Row)
{
  return getString(CGTE_PP_INJECTION::DESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setDESCR_C(const std::string& value)
{
  setString(CGTE_PP_INJECTION::DESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_INJECTION::getUSERCODE(long Row)
{
  return getString(CGTE_PP_INJECTION::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_INJECTION::setUSERCODE(const std::string& value)
{
  setString(CGTE_PP_INJECTION::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGTE_PP_INJECTION::select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& DEVICENAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGTE_PP_INJECTION::PLANT,PLANT);
  addWhereClause(CGTE_PP_INJECTION::PLANTNO,PLANTNO);
  addWhereClause(CGTE_PP_INJECTION::PRACNO,PRACNO);
  addWhereClause(CGTE_PP_INJECTION::TREATMODENO,TREATMODENO);
  addWhereClause(CGTE_PP_INJECTION::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CGTE_PP_INJECTION::DEVICENAME,DEVICENAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



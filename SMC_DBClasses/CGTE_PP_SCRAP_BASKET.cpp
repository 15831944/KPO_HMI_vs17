//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_SCRAP_BASKET.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::PROCPHASE("PROCPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::PROCPHASENO("PROCPHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::BASKET_SEQUENCE_NO("BASKET_SEQUENCE_NO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::LOADINGSEQUENCE("LOADINGSEQUENCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::MAT_WEIGHT("MAT_WEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_SCRAP_BASKET::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_SCRAP_BASKET::CGTE_PP_SCRAP_BASKET(cCBS_StdConnection* Connection)
:CSMC_DBData("GTE_PP_SCRAP_BASKET",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_SCRAP_BASKET::CGTE_PP_SCRAP_BASKET(cCBS_Connection* Connection)
:CSMC_DBData("GTE_PP_SCRAP_BASKET",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_SCRAP_BASKET::CGTE_PP_SCRAP_BASKET()
:CSMC_DBData("GTE_PP_SCRAP_BASKET")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_SCRAP_BASKET::~CGTE_PP_SCRAP_BASKET()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_SCRAP_BASKET::getPLANT(long Row)
{
  return getString(CGTE_PP_SCRAP_BASKET::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setPLANT(const std::string& value)
{
  setString(CGTE_PP_SCRAP_BASKET::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getPLANTNO(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setPLANTNO(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getPRACNO(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setPRACNO(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getTREATMODENO(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setTREATMODENO(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_SCRAP_BASKET::getPROCPHASE(long Row)
{
  return getString(CGTE_PP_SCRAP_BASKET::PROCPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setPROCPHASE(const std::string& value)
{
  setString(CGTE_PP_SCRAP_BASKET::PROCPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getPROCPHASENO(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::PROCPHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setPROCPHASENO(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::PROCPHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getBASKET_SEQUENCE_NO(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::BASKET_SEQUENCE_NO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setBASKET_SEQUENCE_NO(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::BASKET_SEQUENCE_NO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getLOADINGSEQUENCE(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::LOADINGSEQUENCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setLOADINGSEQUENCE(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::LOADINGSEQUENCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_SCRAP_BASKET::getMAT_CODE(long Row)
{
  return getString(CGTE_PP_SCRAP_BASKET::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setMAT_CODE(const std::string& value)
{
  setString(CGTE_PP_SCRAP_BASKET::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_SCRAP_BASKET::getMAT_WEIGHT(long Row)
{
  return getDouble(CGTE_PP_SCRAP_BASKET::MAT_WEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setMAT_WEIGHT(double value)
{
  setDouble(CGTE_PP_SCRAP_BASKET::MAT_WEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_SCRAP_BASKET::getDISPLAY_ORDER(long Row)
{
  return getLong(CGTE_PP_SCRAP_BASKET::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_SCRAP_BASKET::setDISPLAY_ORDER(long value)
{
  setLong(CGTE_PP_SCRAP_BASKET::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGTE_PP_SCRAP_BASKET::select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PROCPHASE, long PROCPHASENO, long BASKET_SEQUENCE_NO, long LOADINGSEQUENCE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGTE_PP_SCRAP_BASKET::PLANT,PLANT);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PLANTNO,PLANTNO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PRACNO,PRACNO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::TREATMODENO,TREATMODENO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PROCPHASE,PROCPHASE);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PROCPHASENO,PROCPHASENO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::BASKET_SEQUENCE_NO,BASKET_SEQUENCE_NO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::LOADINGSEQUENCE,LOADINGSEQUENCE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGTE_PP_SCRAP_BASKET::selectByNextLiqAdd(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PROCPHASE, long PROCPHASENO, long BASKET_SEQUENCE_NO, long LOADINGSEQUENCE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGTE_PP_SCRAP_BASKET::PLANT,PLANT);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PLANTNO,PLANTNO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PRACNO,PRACNO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::TREATMODENO,TREATMODENO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PROCPHASE,PROCPHASE);
  addWhereClause(CGTE_PP_SCRAP_BASKET::PROCPHASENO,PROCPHASENO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::BASKET_SEQUENCE_NO,BASKET_SEQUENCE_NO);
  addWhereClause(CGTE_PP_SCRAP_BASKET::LOADINGSEQUENCE,LOADINGSEQUENCE);

  std::string Clause1 = getWhereStatement();
  Clause1.erase(Clause1.find_last_of(")"));

  addWhereClause(CGTE_PP_SCRAP_BASKET::LIQ_ADD_AMOUNT, LIQ_ADD_AMOUNT, "<=");

  std::string Clause2 = " AND LIQ_ADD_AMOUNT = (select MAX(LIQ_ADD_AMOUNT) from " + m_TableName + getWhereStatement() + ")";

  m_Statement += Clause1 + Clause2 + ");"; //add removed ")"

  return CSMC_DBData::select();
}



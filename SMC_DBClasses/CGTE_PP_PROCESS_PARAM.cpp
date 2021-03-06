//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_PROCESS_PARAM.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::REMEGY("REMEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::BEGINEGYWALLTEMPCTRL("BEGINEGYWALLTEMPCTRL");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::MELTDOWNRATEBSK("MELTDOWNRATEBSK");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::MAXEGYWITHOUTBSKDATA("MAXEGYWITHOUTBSKDATA");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::MAXEGYWITHBSKDATA("MAXEGYWITHBSKDATA");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::AIMTEMP("AIMTEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGTE_PP_PROCESS_PARAM::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_PROCESS_PARAM::CGTE_PP_PROCESS_PARAM(cCBS_StdConnection* Connection)
:CSMC_DBData("GTE_PP_PROCESS_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_PROCESS_PARAM::CGTE_PP_PROCESS_PARAM(cCBS_Connection* Connection)
:CSMC_DBData("GTE_PP_PROCESS_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_PROCESS_PARAM::CGTE_PP_PROCESS_PARAM()
:CSMC_DBData("GTE_PP_PROCESS_PARAM")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGTE_PP_PROCESS_PARAM::~CGTE_PP_PROCESS_PARAM()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_PROCESS_PARAM::getPLANT(long Row)
{
  return getString(CGTE_PP_PROCESS_PARAM::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setPLANT(const std::string& value)
{
  setString(CGTE_PP_PROCESS_PARAM::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_PROCESS_PARAM::getPLANTNO(long Row)
{
  return getLong(CGTE_PP_PROCESS_PARAM::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setPLANTNO(long value)
{
  setLong(CGTE_PP_PROCESS_PARAM::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_PROCESS_PARAM::getPRACNO(long Row)
{
  return getLong(CGTE_PP_PROCESS_PARAM::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setPRACNO(long value)
{
  setLong(CGTE_PP_PROCESS_PARAM::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_PROCESS_PARAM::getTREATMODENO(long Row)
{
  return getLong(CGTE_PP_PROCESS_PARAM::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setTREATMODENO(long value)
{
  setLong(CGTE_PP_PROCESS_PARAM::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_PROCESS_PARAM::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CGTE_PP_PROCESS_PARAM::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CGTE_PP_PROCESS_PARAM::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGTE_PP_PROCESS_PARAM::getPRACPHASE(long Row)
{
  return getString(CGTE_PP_PROCESS_PARAM::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setPRACPHASE(const std::string& value)
{
  setString(CGTE_PP_PROCESS_PARAM::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getREMEGY(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::REMEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setREMEGY(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::REMEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getBEGINEGYWALLTEMPCTRL(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::BEGINEGYWALLTEMPCTRL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setBEGINEGYWALLTEMPCTRL(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::BEGINEGYWALLTEMPCTRL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getMELTDOWNRATEBSK(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::MELTDOWNRATEBSK, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setMELTDOWNRATEBSK(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::MELTDOWNRATEBSK, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getMAXEGYWITHOUTBSKDATA(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::MAXEGYWITHOUTBSKDATA, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setMAXEGYWITHOUTBSKDATA(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::MAXEGYWITHOUTBSKDATA, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getMAXEGYWITHBSKDATA(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::MAXEGYWITHBSKDATA, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setMAXEGYWITHBSKDATA(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::MAXEGYWITHBSKDATA, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CGTE_PP_PROCESS_PARAM::getAIMTEMP(long Row)
{
  return getDouble(CGTE_PP_PROCESS_PARAM::AIMTEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setAIMTEMP(double value)
{
  setDouble(CGTE_PP_PROCESS_PARAM::AIMTEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGTE_PP_PROCESS_PARAM::getDISPLAY_ORDER(long Row)
{
  return getLong(CGTE_PP_PROCESS_PARAM::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGTE_PP_PROCESS_PARAM::setDISPLAY_ORDER(long value)
{
  setLong(CGTE_PP_PROCESS_PARAM::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGTE_PP_PROCESS_PARAM::select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PRACPHASE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGTE_PP_PROCESS_PARAM::PLANT,PLANT);
  addWhereClause(CGTE_PP_PROCESS_PARAM::PLANTNO,PLANTNO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::PRACNO,PRACNO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::TREATMODENO,TREATMODENO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CGTE_PP_PROCESS_PARAM::PRACPHASE,PRACPHASE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

long CGTE_PP_PROCESS_PARAM::GetMaxLiqAddAmount(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT)
{
  cleanWhereStatement();

  m_Statement = "Select max(LIQ_ADD_AMOUNT) as LIQ_ADD_AMOUNT from " + m_TableName;

  addWhereClause(CGTE_PP_PROCESS_PARAM::PLANT,PLANT);
  addWhereClause(CGTE_PP_PROCESS_PARAM::PLANTNO,PLANTNO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::PRACNO,PRACNO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::TREATMODENO,TREATMODENO);
  addWhereClause(CGTE_PP_PROCESS_PARAM::LIQ_ADD_AMOUNT ,LIQ_ADD_AMOUNT, "<=");

  m_Statement += getWhereStatement();

  if ( CSMC_DBData::select() )
  {
    LIQ_ADD_AMOUNT = getLIQ_ADD_AMOUNT(1);
  }

  return LIQ_ADD_AMOUNT;
}



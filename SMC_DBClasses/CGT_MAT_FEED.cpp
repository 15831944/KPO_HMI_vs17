//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_MAT_FEED.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::FEEDINGRATE_ABS("FEEDINGRATE_ABS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::FEEDINGRATE_REL("FEEDINGRATE_REL");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::FEEDINGRATE_INPUT("FEEDINGRATE_INPUT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_FEED::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_FEED::CGT_MAT_FEED(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_MAT_FEED",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_FEED::CGT_MAT_FEED(cCBS_Connection* Connection)
:CSMC_DBData("GT_MAT_FEED",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_FEED::CGT_MAT_FEED()
:CSMC_DBData("GT_MAT_FEED")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_FEED::~CGT_MAT_FEED()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGT_MAT_FEED::getPLANT(long Row)
{
  return getString(CGT_MAT_FEED::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setPLANT(const std::string& value)
{
  setString(CGT_MAT_FEED::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant number
long CGT_MAT_FEED::getPLANTNO(long Row)
{
  return getLong(CGT_MAT_FEED::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setPLANTNO(long value)
{
  setLong(CGT_MAT_FEED::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Production Practice Number
long CGT_MAT_FEED::getPRACNO(long Row)
{
  return getLong(CGT_MAT_FEED::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setPRACNO(long value)
{
  setLong(CGT_MAT_FEED::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment mode number
long CGT_MAT_FEED::getTREATMODENO(long Row)
{
  return getLong(CGT_MAT_FEED::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setTREATMODENO(long value)
{
  setLong(CGT_MAT_FEED::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Phases are e.g. Basket, LiqAdd for EAF
std::string CGT_MAT_FEED::getPRACPHASE(long Row)
{
  return getString(CGT_MAT_FEED::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setPRACPHASE(const std::string& value)
{
  setString(CGT_MAT_FEED::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Amount of  liquid addition relative to aim steel weight into EAF/Conarc., AOD, LF... = 0. Unit: % without precision
long CGT_MAT_FEED::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CGT_MAT_FEED::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CGT_MAT_FEED::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code of feeding material
std::string CGT_MAT_FEED::getMAT_CODE(long Row)
{
  return getString(CGT_MAT_FEED::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setMAT_CODE(const std::string& value)
{
  setString(CGT_MAT_FEED::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGT_MAT_FEED::getSTEPNO(long Row)
{
  return getLong(CGT_MAT_FEED::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setSTEPNO(long value)
{
  setLong(CGT_MAT_FEED::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Absolute feeding rate in kg/min
double CGT_MAT_FEED::getFEEDINGRATE_ABS(long Row)
{
  return getDouble(CGT_MAT_FEED::FEEDINGRATE_ABS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setFEEDINGRATE_ABS(double value)
{
  setDouble(CGT_MAT_FEED::FEEDINGRATE_ABS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Relative feeding rate in kg/minMW
double CGT_MAT_FEED::getFEEDINGRATE_REL(long Row)
{
  return getDouble(CGT_MAT_FEED::FEEDINGRATE_REL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setFEEDINGRATE_REL(double value)
{
  setDouble(CGT_MAT_FEED::FEEDINGRATE_REL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Feeding rate can be entered absolute or relative. The corresponding other value is calculated., 1- Indicates that relative feeding rate was calculated from absolute, 2- Indicates that absolute feeding rate was calculated from relative
long CGT_MAT_FEED::getFEEDINGRATE_INPUT(long Row)
{
  return getLong(CGT_MAT_FEED::FEEDINGRATE_INPUT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setFEEDINGRATE_INPUT(long value)
{
  setLong(CGT_MAT_FEED::FEEDINGRATE_INPUT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Display order of feeding materials for HMI
long CGT_MAT_FEED::getDISPLAY_ORDER(long Row)
{
  return getLong(CGT_MAT_FEED::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_FEED::setDISPLAY_ORDER(long value)
{
  setLong(CGT_MAT_FEED::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_MAT_FEED::select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, const std::string& PRACPHASE, long LIQ_ADD_AMOUNT, const std::string& MAT_CODE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_MAT_FEED::PLANT,PLANT);
  addWhereClause(CGT_MAT_FEED::PLANTNO,PLANTNO);
  addWhereClause(CGT_MAT_FEED::PRACNO,PRACNO);
  addWhereClause(CGT_MAT_FEED::TREATMODENO,TREATMODENO);
  addWhereClause(CGT_MAT_FEED::PRACPHASE,PRACPHASE);
  addWhereClause(CGT_MAT_FEED::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CGT_MAT_FEED::MAT_CODE,MAT_CODE);
  addWhereClause(CGT_MAT_FEED::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



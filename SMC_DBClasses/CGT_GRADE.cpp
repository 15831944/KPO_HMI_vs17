//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_GRADE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::STEELGRADECODE("STEELGRADECODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::STEELGRADECODEDESCR("STEELGRADECODEDESCR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::STEELGRADECODEDESCR_C("STEELGRADECODEDESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::LIQTEMP("LIQTEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::USERCODE("USERCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE::CGT_GRADE(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_GRADE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE::CGT_GRADE(cCBS_Connection* Connection)
:CSMC_DBData("GT_GRADE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE::CGT_GRADE()
:CSMC_DBData("GT_GRADE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE::~CGT_GRADE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code
std::string CGT_GRADE::getSTEELGRADECODE(long Row)
{
  return getString(CGT_GRADE::STEELGRADECODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setSTEELGRADECODE(const std::string& value)
{
  setString(CGT_GRADE::STEELGRADECODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code description
std::string CGT_GRADE::getSTEELGRADECODEDESCR(long Row)
{
  return getString(CGT_GRADE::STEELGRADECODEDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setSTEELGRADECODEDESCR(const std::string& value)
{
  setString(CGT_GRADE::STEELGRADECODEDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code description
std::string CGT_GRADE::getSTEELGRADECODEDESCR_C(long Row)
{
  return getString(CGT_GRADE::STEELGRADECODEDESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setSTEELGRADECODEDESCR_C(const std::string& value)
{
  setString(CGT_GRADE::STEELGRADECODEDESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Liquidus temperature
double CGT_GRADE::getLIQTEMP(long Row)
{
  return getDouble(CGT_GRADE::LIQTEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setLIQTEMP(double value)
{
  setDouble(CGT_GRADE::LIQTEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##User who entered/changed entry. User code <> L3 indicates manual entered.
std::string CGT_GRADE::getUSERCODE(long Row)
{
  return getString(CGT_GRADE::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setUSERCODE(const std::string& value)
{
  setString(CGT_GRADE::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CGT_GRADE::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CGT_GRADE::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE::setREVTIME(const CDateTime& value)
{
 setString(CGT_GRADE::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_GRADE::select(const std::string& STEELGRADECODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_GRADE::STEELGRADECODE,STEELGRADECODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGT_GRADE::deleteGrade(const std::string& STEELGRADECODE )
{
  cleanWhereStatement();
  
  addWhereClause(CGT_GRADE::STEELGRADECODE, STEELGRADECODE);

  return deleteRows();
}

bool CGT_GRADE::writeGrade(const std::string& STEELGRADECODE, const std::string& STEELGRADECODEDESCR, const std::string& STEELGRADECODEDESCR_C, double LIQTEMP, const std::string& USERCODE, long VERSION, const CDateTime & REVTIME, bool Commit)
{
  bool RetValue = false;

  setSTEELGRADECODEDESCR(STEELGRADECODEDESCR);
  setSTEELGRADECODEDESCR_C(STEELGRADECODEDESCR_C);
  setLIQTEMP(LIQTEMP);
  setUSERCODE(USERCODE);
  setREVTIME(REVTIME);
  //setVERSION(VERSION);

  if ( select(STEELGRADECODE) )
  {
    RetValue = update();
  }
  else
  {
    setSTEELGRADECODE(STEELGRADECODE);
    RetValue = insert();
  }

  if ( Commit )
  {
    if ( RetValue )
    {
      commit();
    }
    else
    {
      rollback();
    }
  }

  return RetValue;
}



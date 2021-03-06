//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "cCBS_StdEventLogFrameController.h"
#include "CIntfData.h"
#include "CGT_GRADE_ANL.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE_ANL::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE_ANL::STEELGRADECODE("STEELGRADECODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE_ANL::AIMTYPE("AIMTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE_ANL::ENAME("ENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_GRADE_ANL::ANL("ANL");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE_ANL::CGT_GRADE_ANL(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_GRADE_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE_ANL::CGT_GRADE_ANL(cCBS_Connection* Connection)
:CSMC_DBData("GT_GRADE_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE_ANL::CGT_GRADE_ANL()
:CSMC_DBData("GT_GRADE_ANL")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_GRADE_ANL::~CGT_GRADE_ANL()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGT_GRADE_ANL::getPLANT(long Row)
{
  return getString(CGT_GRADE_ANL::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE_ANL::setPLANT(const std::string& value)
{
  setString(CGT_GRADE_ANL::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code
std::string CGT_GRADE_ANL::getSTEELGRADECODE(long Row)
{
  return getString(CGT_GRADE_ANL::STEELGRADECODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE_ANL::setSTEELGRADECODE(const std::string& value)
{
  setString(CGT_GRADE_ANL::STEELGRADECODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Min, Max, Aim
std::string CGT_GRADE_ANL::getAIMTYPE(long Row)
{
  return getString(CGT_GRADE_ANL::AIMTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE_ANL::setAIMTYPE(const std::string& value)
{
  setString(CGT_GRADE_ANL::AIMTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Element or slag compound name
std::string CGT_GRADE_ANL::getENAME(long Row)
{
  return getString(CGT_GRADE_ANL::ENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE_ANL::setENAME(const std::string& value)
{
  setString(CGT_GRADE_ANL::ENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Analysis value
double CGT_GRADE_ANL::getANL(long Row)
{
  return getDouble(CGT_GRADE_ANL::ANL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_GRADE_ANL::setANL(double value)
{
  setDouble(CGT_GRADE_ANL::ANL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_GRADE_ANL::select(const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& AIMTYPE, const std::string& ENAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_GRADE_ANL::PLANT,PLANT);
  addWhereClause(CGT_GRADE_ANL::STEELGRADECODE,STEELGRADECODE);
  addWhereClause(CGT_GRADE_ANL::AIMTYPE,AIMTYPE);
  addWhereClause(CGT_GRADE_ANL::ENAME,ENAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGT_GRADE_ANL::deleteGrade(const std::string& STEELGRADECODE )
{
  cleanWhereStatement();
  
  addWhereClause(CGT_GRADE_ANL::STEELGRADECODE, STEELGRADECODE);

  return deleteRows();
}

bool CGT_GRADE_ANL::writeAnalysis(const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& AIMTYPE, seqAnalysis SeqAnalysis, bool Commit)
{
  // empty SeqAnalysis may not force return value == false
  bool RetValue = false;

  if ( CIntfData::getLength(SeqAnalysis) == 0 )
  {
    // empty SeqAnalysis may not force return value == false
    RetValue = true;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBWriteInfo(sMessage,"", m_TableName.c_str(), "no analysis data received" );
  }
  else
  {
    for ( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
    {
      sAnalysis Analysis;
      CIntfData::getAt(Analysis,SeqAnalysis,i);

      std::string ENAME = Analysis.Element;
      double ANL        = Analysis.Concentration;

      if ( ANL == DEF::Inv_Double )
      {
        cleanWhereStatement();

        addWhereClause(CGT_GRADE_ANL::PLANT,PLANT);
        addWhereClause(CGT_GRADE_ANL::STEELGRADECODE,STEELGRADECODE);
        addWhereClause(CGT_GRADE_ANL::AIMTYPE,AIMTYPE);
        addWhereClause(CGT_GRADE_ANL::ENAME,ENAME);

        RetValue = CSMC_DBData::deleteRows();
      }
      else if ( select(PLANT, STEELGRADECODE,AIMTYPE,ENAME) )
      {
        setANL(ANL);
        RetValue = update();
      }
      else
      {
        setPLANT(PLANT);
        setSTEELGRADECODE(STEELGRADECODE);
        setAIMTYPE(AIMTYPE);
        setENAME(ENAME);
        setANL(ANL);

        RetValue = insert();
      }
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
  }

  return RetValue;
}



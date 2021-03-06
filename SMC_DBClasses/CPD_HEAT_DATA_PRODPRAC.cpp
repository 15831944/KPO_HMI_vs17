//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "cCBS_StdEventLogFrameController.h"
#include "CGC_PRODPRAC_DEF.h"
#include "CGT_RESTRI.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::DESCR_PP("DESCR_PP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::STEELGRADECODE("STEELGRADECODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN("PRODPRACID_PLAN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD("PRODPRACID_MOD");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_DATA_PRODPRAC::CPD_HEAT_DATA_PRODPRAC(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_HEAT_DATA_PRODPRAC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_DATA_PRODPRAC::CPD_HEAT_DATA_PRODPRAC(cCBS_Connection* Connection)
:CSMC_DBData("PD_HEAT_DATA_PRODPRAC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_DATA_PRODPRAC::CPD_HEAT_DATA_PRODPRAC()
:CSMC_DBData("PD_HEAT_DATA_PRODPRAC")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_DATA_PRODPRAC::~CPD_HEAT_DATA_PRODPRAC()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_HEAT_DATA_PRODPRAC::getHEATID(long Row)
{
  return getString(CPD_HEAT_DATA_PRODPRAC::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setHEATID(const std::string& value)
{
  setString(CPD_HEAT_DATA_PRODPRAC::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_HEAT_DATA_PRODPRAC::getTREATID(long Row)
{
  return getString(CPD_HEAT_DATA_PRODPRAC::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setTREATID(const std::string& value)
{
  setString(CPD_HEAT_DATA_PRODPRAC::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_HEAT_DATA_PRODPRAC::getPLANT(long Row)
{
  return getString(CPD_HEAT_DATA_PRODPRAC::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setPLANT(const std::string& value)
{
  setString(CPD_HEAT_DATA_PRODPRAC::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of practice pointer or practice group
std::string CPD_HEAT_DATA_PRODPRAC::getDESCR_PP(long Row)
{
  return getString(CPD_HEAT_DATA_PRODPRAC::DESCR_PP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setDESCR_PP(const std::string& value)
{
  setString(CPD_HEAT_DATA_PRODPRAC::DESCR_PP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code
std::string CPD_HEAT_DATA_PRODPRAC::getSTEELGRADECODE(long Row)
{
  return getString(CPD_HEAT_DATA_PRODPRAC::STEELGRADECODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setSTEELGRADECODE(const std::string& value)
{
  setString(CPD_HEAT_DATA_PRODPRAC::STEELGRADECODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Planned production practice pointer
long CPD_HEAT_DATA_PRODPRAC::getPRODPRACID_PLAN(long Row)
{
  return getLong(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setPRODPRACID_PLAN(long value)
{
  setLong(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Modified production practice pointer
long CPD_HEAT_DATA_PRODPRAC::getPRODPRACID_MOD(long Row)
{
  return getLong(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_DATA_PRODPRAC::setPRODPRACID_MOD(long value)
{
  setLong(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_HEAT_DATA_PRODPRAC::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& DESCR_PP)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HEAT_DATA_PRODPRAC::HEATID,HEATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::TREATID,TREATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::PLANT,PLANT);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::DESCR_PP,DESCR_PP);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_HEAT_DATA_PRODPRAC::selectRestriPractice(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool WithDefault)
{
  // function returns set of restriction practice pointer
  // with defaults is the flag (WithDefault) is true
  // ordered by PRODPRACID_MOD DESC and PRODPRACID_PLAN  DESC

	bool RetValue = false;

  CGC_PRODPRAC_DEF GC_PRODPRAC_DEF(m_pCBS_StdConnection);

  std::vector<std::string> RestriDef; // to collect restrictions 

  // get first restriction definitions 
  if ( GC_PRODPRAC_DEF.selectRestriction(PLANT, WithDefault) )
  {
    for ( int i = 1; i <= GC_PRODPRAC_DEF.getLastRow(); i++ )
    {
      std::string DESCR_PP = GC_PRODPRAC_DEF.getDESCR_PP(i);
      RestriDef.push_back(DESCR_PP);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage, "DESCR_PP", "GC_PRODPRAC_DEF", GC_PRODPRAC_DEF.getActStatement().c_str());
  }

  if ( RestriDef.empty() )
  {
    return RetValue;
  }

  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HEAT_DATA_PRODPRAC::HEATID,HEATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::TREATID,TREATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::PLANT,PLANT);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::DESCR_PP, RestriDef);

  m_Statement += getWhereStatement() + " ORDER BY PRODPRACID_MOD DESC, PRODPRACID_PLAN  DESC;";

  return CSMC_DBData::select();
}

bool CPD_HEAT_DATA_PRODPRAC::selectRestriPracticeDefault(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  // function returns set of default restriction practice pointer only
  // ordered by PRODPRACID_MOD DESC and PRODPRACID_PLAN  DESC

	bool RetValue = false;

  CGC_PRODPRAC_DEF GC_PRODPRAC_DEF(m_pCBS_StdConnection);

  std::vector<std::string> RestriDef; // to collect restrictions 

  // get first default restriction definitions 
  if ( GC_PRODPRAC_DEF.selectOnlyStandard(PLANT) )
  {
    for ( int i = 1; i <= GC_PRODPRAC_DEF.getLastRow(); i++ )
    {
      std::string DESCR_PP = GC_PRODPRAC_DEF.getDESCR_PP(i);
      RestriDef.push_back(DESCR_PP);
    }
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage, "DESCR_PP", "GC_PRODPRAC_DEF", GC_PRODPRAC_DEF.getActStatement().c_str());
  }

  if ( RestriDef.empty() )
  {
    return RetValue;
  }

  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HEAT_DATA_PRODPRAC::HEATID,HEATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::TREATID,TREATID);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::PLANT,PLANT);
  addWhereClause(CPD_HEAT_DATA_PRODPRAC::DESCR_PP, RestriDef);

  m_Statement += getWhereStatement() + " ORDER BY PRODPRACID_MOD DESC, PRODPRACID_PLAN  DESC;";

  return CSMC_DBData::select();
}

bool CPD_HEAT_DATA_PRODPRAC::deleteHeat(const std::string& PLANT, const std::string& HEATID, const std::string& TREATID, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = false;

  if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecString) )
  {
    result = deleteRows();

	  if (!result)
    {
		  Error = getLastError();
    }
  }
	
	
	if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}

bool CPD_HEAT_DATA_PRODPRAC::doAnnouncement(const std::string& PLANT, long PLANTNO, const std::string& HEATID, const std::string& TREATID, bool Commit, cCBS_ODBC_DBError &Error)
{
	return doChangeAimData(PLANT, PLANTNO, HEATID, TREATID, Commit, Error);
}

bool CPD_HEAT_DATA_PRODPRAC::doChangeAimData(const std::string& PLANT, long PLANTNO, const std::string& HEATID, const std::string& TREATID, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = false;

  if (exists(HEATID, TREATID, PLANT))
  {
		//delete previous items if any
		result = deleteHeat(PLANT, HEATID, TREATID, Commit, Error);
  }

  CPD_HEAT_DATA       PD_HEAT_DATA     (m_pCBS_StdConnection);
  CGT_GRADE_PRODPRAC  GT_GRADE_PRODPRAC(m_pCBS_StdConnection);

  if (PD_HEAT_DATA.select(HEATID, TREATID, PLANT) )
  {
    std::string STEELGRADECODE = PD_HEAT_DATA.getSTEELGRADECODE_ACT(1);

    if ( GT_GRADE_PRODPRAC.select(PLANT, PLANTNO, STEELGRADECODE, CSMC_DBData::unspecString,CSMC_DBData::unspecLong) )
    {
      for ( long i = 1; i<= GT_GRADE_PRODPRAC.getLastRow(); ++i )
      {
        setHEATID(HEATID);
        setTREATID(TREATID);
        setPLANT(PLANT);
        setDESCR_PP(GT_GRADE_PRODPRAC.getDESCR_PP(i));
        setSTEELGRADECODE(GT_GRADE_PRODPRAC.getSTEELGRADECODE(i));
        setPRODPRACID_MOD (GT_GRADE_PRODPRAC.getPRODPRAC_ID(i));
        setPRODPRACID_PLAN(GT_GRADE_PRODPRAC.getPRODPRAC_ID(i));

        result = insert();

        if ( !result )
        {
     		  Error = getLastError();
          break;
        }
      }
    }
    else
    {
      setLastError(std::string("NO_PROD_PRAC_POINTER_DEFINED"), 0, getActStatement());
    }
  }
  else
  {
    setLastError(std::string("NO_DATA_FOUND"), 0, getActStatement());
  }

  if ( !result )
  {
	  Error = getLastError();
  }

  if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}

	return result;
}

bool CPD_HEAT_DATA_PRODPRAC::doChangeProdPrac(const std::string& PLANT, long PLANTNO, const std::string& HEATID, const std::string& TREATID, const std::string &DESCR_PP, long PRODPRAC, bool Commit, cCBS_ODBC_DBError &Error)
{
  //using this way update to avoid return false when no record is updated using sql
  bool result = true;

  if(select(HEATID, TREATID, PLANT, DESCR_PP))
  {
    // prohibit changes to NULL because field PRODPRACID_MOD is not nullable
    if ( PRODPRAC != CSMC_DBData::unspecLong )
    {
      setPRODPRACID_MOD(PRODPRAC);
    }

    result = update();

    if (!result)
    {
		  Error = getLastError();
    }

    if (Commit)
    {
      if (result)
      {
        commit();
      }
      else
      {
        rollback();
      }
    }
  }

  return result;	
}

bool CPD_HEAT_DATA_PRODPRAC::doProdOrderChange(const std::string& PLANT, long PLANTNO, const std::string& HEATID, const std::string& TREATID, bool Commit, cCBS_ODBC_DBError &Error)
{
	return doChangeAimData(PLANT, PLANTNO, HEATID, TREATID, Commit, Error);
}

bool CPD_HEAT_DATA_PRODPRAC::doSteelGradeChange(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, const std::string& STEELGRADECODE, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = false;

	if (exists(HEATID, TREATID, PLANT))
	{
		//delete previous items if any
		result = deleteHeat(PLANT, HEATID, TREATID, Commit, Error);
	}

  CGT_GRADE_PRODPRAC GT_GRADE_PRODPRAC(m_pCBS_StdConnection);

  if (GT_GRADE_PRODPRAC.select(PLANT, PLANTNO, STEELGRADECODE, CSMC_DBData::unspecString, CSMC_DBData::unspecLong))
  {
    for ( long i = 1; i<= GT_GRADE_PRODPRAC.getLastRow(); ++i )
    {
      setHEATID(HEATID);
      setTREATID(TREATID);
      setPLANT(PLANT);
      setDESCR_PP       (GT_GRADE_PRODPRAC.getDESCR_PP(i));
      setSTEELGRADECODE (GT_GRADE_PRODPRAC.getSTEELGRADECODE(i));
      setPRODPRACID_MOD (GT_GRADE_PRODPRAC.getPRODPRAC_ID(i));
      setPRODPRACID_PLAN(GT_GRADE_PRODPRAC.getPRODPRAC_ID(i));

      result = insert();

      if ( !result )
      {
   		  Error = getLastError();
        break;
      }
    }
  }
  else
  {
		setLastError(std::string("NO_PRODPRAC_DATA_FOUND"), 0, getActStatement());
  }

	
  if (!result)
  {
		Error = getLastError();
  }

	if (Commit)
	{
		if (result)
    {
			commit();
    }
		else
    {
			rollback();
    }
	}

	return result;
}

bool CPD_HEAT_DATA_PRODPRAC::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CPD_HEAT_DATA_PRODPRAC::HEATID,HEATID);
	addWhereClause(CPD_HEAT_DATA_PRODPRAC::TREATID,TREATID);
	addWhereClause(CPD_HEAT_DATA_PRODPRAC::PLANT,PLANT);
   
  std::string sWhereStatement = getWhereStatement();
  //to avoid the exception like 'Select HEATID from PP_HEAT AND ROWNUM = 1 '
  if(sWhereStatement.length() > 0 ) 
  {
    // do not use ROWNUM in "addWhereClause", ROWNUM is not a table column and where statement will be used for deletion at "deleteRows"
    m_Statement += sWhereStatement + " AND ROWNUM = 1 ;";
  }
  else
  {
    return false;
  }

	return CSMC_DBData::select();
}



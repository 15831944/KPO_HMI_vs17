//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_MEASUREMENT_NAME.h"
#include "CGT_GRADE_ANL.h"
#include "CHD_GRADE_ANL.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::STEELGRADECODE("STEELGRADECODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::ENAME("ENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::AIMTYPE("AIMTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_GRADE_ANL::ANL("ANL");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_GRADE_ANL::CHD_GRADE_ANL(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_GRADE_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_GRADE_ANL::CHD_GRADE_ANL(cCBS_Connection* Connection)
:CSMC_DBData("HD_GRADE_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_GRADE_ANL::CHD_GRADE_ANL()
:CSMC_DBData("HD_GRADE_ANL")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_GRADE_ANL::~CHD_GRADE_ANL()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_GRADE_ANL::getHEATID(long Row)
{
  return getString(CHD_GRADE_ANL::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setHEATID(const std::string& value)
{
  setString(CHD_GRADE_ANL::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_GRADE_ANL::getTREATID(long Row)
{
  return getString(CHD_GRADE_ANL::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setTREATID(const std::string& value)
{
  setString(CHD_GRADE_ANL::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_GRADE_ANL::getPLANT(long Row)
{
  return getString(CHD_GRADE_ANL::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setPLANT(const std::string& value)
{
  setString(CHD_GRADE_ANL::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel grade code
std::string CHD_GRADE_ANL::getSTEELGRADECODE(long Row)
{
  return getString(CHD_GRADE_ANL::STEELGRADECODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setSTEELGRADECODE(const std::string& value)
{
  setString(CHD_GRADE_ANL::STEELGRADECODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Element or slag compound name
std::string CHD_GRADE_ANL::getENAME(long Row)
{
  return getString(CHD_GRADE_ANL::ENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setENAME(const std::string& value)
{
  setString(CHD_GRADE_ANL::ENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Min, Max, Aim
std::string CHD_GRADE_ANL::getAIMTYPE(long Row)
{
  return getString(CHD_GRADE_ANL::AIMTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setAIMTYPE(const std::string& value)
{
  setString(CHD_GRADE_ANL::AIMTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Analysis value
double CHD_GRADE_ANL::getANL(long Row)
{
  return getDouble(CHD_GRADE_ANL::ANL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_GRADE_ANL::setANL(double value)
{
  setDouble(CHD_GRADE_ANL::ANL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_GRADE_ANL::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& ENAME, const std::string& AIMTYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_GRADE_ANL::HEATID,HEATID);
  addWhereClause(CHD_GRADE_ANL::TREATID,TREATID);
  addWhereClause(CHD_GRADE_ANL::PLANT,PLANT);
  addWhereClause(CHD_GRADE_ANL::STEELGRADECODE,STEELGRADECODE);
  addWhereClause(CHD_GRADE_ANL::ENAME,ENAME);
  addWhereClause(CHD_GRADE_ANL::AIMTYPE,AIMTYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_GRADE_ANL::selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& ENAME, const std::string& AIMTYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_GRADE_ANL::HEATID,HEATID);
  addWhereClause(CHD_GRADE_ANL::TREATID,TREATID);
  addWhereClause(CHD_GRADE_ANL::PLANT,PLANT);
  addWhereClause(CHD_GRADE_ANL::STEELGRADECODE,STEELGRADECODE);
  addWhereClause(CHD_GRADE_ANL::ENAME,ENAME);
  addWhereClause(CHD_GRADE_ANL::AIMTYPE,AIMTYPE);

  m_Statement += getWhereStatement() + " ORDER BY ENAME ;";

  return CSMC_DBData::select();
}

bool CHD_GRADE_ANL::copy(const std::string &STEELGRADECODE, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(HEATID, TREATID, PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

  // preparing setting for source table
  CGT_GRADE_ANL GT_GRADE_ANL(m_pCBS_StdConnection);
  GT_GRADE_ANL.addWhereClause(CGT_GRADE_ANL::STEELGRADECODE,STEELGRADECODE);
  GT_GRADE_ANL.addWhereClause(CGT_GRADE_ANL::PLANT,PLANT);

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);

  result = result && copyByInsert(&GT_GRADE_ANL);

	if (!result)
		Error = getLastError();

	if(Commit)
  {
		if (result)
			this->commit();
		else
			rollback();
  }

	return result;
}

bool CHD_GRADE_ANL::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_GRADE_ANL::HEATID,HEATID);
	addWhereClause(CHD_GRADE_ANL::TREATID,TREATID);
	addWhereClause(CHD_GRADE_ANL::PLANT,PLANT);
   
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

std::set<std::string> CHD_GRADE_ANL::getENAMEList(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& AIMTYPE, long MEASUREMENT_NAME_SCOPE )
{
  std::set<std::string> ENAMEList;

  CGC_MEASUREMENT_NAME   GC_MEASUREMENT_NAME (m_pCBS_StdConnection);

  
  if ( select (HEATID, TREATID, PLANT, STEELGRADECODE, CSMC_DBData::unspecString, AIMTYPE) )
  {
    for ( long i = 1 ; i <= getLastRow() ; ++i )
    {
      std::string ENAME = getENAME(i);

      if ( GC_MEASUREMENT_NAME.isOfElement(ENAME, MEASUREMENT_NAME_SCOPE) )
      {
        if ( ENAMEList.find(ENAME) == ENAMEList.end() )
        {
          ENAMEList.insert(ENAME);
        }
      }
    } // for ( long i = 1 ; i <= getLastRow() ; ++i )
  }

  return ENAMEList;
}

bool CHD_GRADE_ANL::updateAnl(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& ENAME, const std::string& AIMTYPE, double ANL, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = false;

  if (select(HEATID, TREATID, PLANT, STEELGRADECODE, ENAME, AIMTYPE))
  {
    setANL(ANL);

    result = update();
  }
  else
  {
    setHEATID(HEATID);
    setTREATID(TREATID);
    setPLANT(PLANT);
    setSTEELGRADECODE(STEELGRADECODE);
    setENAME(ENAME);
    setAIMTYPE(AIMTYPE);
    setANL(ANL);

    result = insert();
  }

  if (!result)
    Error = getLastError();

  if(Commit)
  {
    if (result)
      this->commit();
    else
      rollback();
  }

  return result;
}



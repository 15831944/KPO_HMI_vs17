//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_STIRR.h"
#include "CHDE_PP_STIRR.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::DESCR_E("DESCR_E");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::DESCR_C("DESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR::USERCODE("USERCODE");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR::CHDE_PP_STIRR(cCBS_StdConnection* Connection)
:CSMC_DBData("HDE_PP_STIRR",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR::CHDE_PP_STIRR(cCBS_Connection* Connection)
:CSMC_DBData("HDE_PP_STIRR",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR::CHDE_PP_STIRR()
:CSMC_DBData("HDE_PP_STIRR")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR::~CHDE_PP_STIRR()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getHEATID(long Row)
{
  return getString(CHDE_PP_STIRR::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setHEATID(const std::string& value)
{
  setString(CHDE_PP_STIRR::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getTREATID(long Row)
{
  return getString(CHDE_PP_STIRR::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setTREATID(const std::string& value)
{
  setString(CHDE_PP_STIRR::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getPLANT(long Row)
{
  return getString(CHDE_PP_STIRR::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setPLANT(const std::string& value)
{
  setString(CHDE_PP_STIRR::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR::getPRACNO(long Row)
{
  return getLong(CHDE_PP_STIRR::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setPRACNO(long value)
{
  setLong(CHDE_PP_STIRR::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR::getTREATMODENO(long Row)
{
  return getLong(CHDE_PP_STIRR::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setTREATMODENO(long value)
{
  setLong(CHDE_PP_STIRR::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CHDE_PP_STIRR::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CHDE_PP_STIRR::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDE_PP_STIRR::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDE_PP_STIRR::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setREVTIME(const CDateTime& value)
{
 setString(CHDE_PP_STIRR::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getDESCR_E(long Row)
{
  return getString(CHDE_PP_STIRR::DESCR_E, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setDESCR_E(const std::string& value)
{
  setString(CHDE_PP_STIRR::DESCR_E, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getDESCR_C(long Row)
{
  return getString(CHDE_PP_STIRR::DESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setDESCR_C(const std::string& value)
{
  setString(CHDE_PP_STIRR::DESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR::getUSERCODE(long Row)
{
  return getString(CHDE_PP_STIRR::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR::setUSERCODE(const std::string& value)
{
  setString(CHDE_PP_STIRR::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDE_PP_STIRR::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDE_PP_STIRR::HEATID,HEATID);
  addWhereClause(CHDE_PP_STIRR::TREATID,TREATID);
  addWhereClause(CHDE_PP_STIRR::PLANT,PLANT);
  addWhereClause(CHDE_PP_STIRR::PRACNO,PRACNO);
  addWhereClause(CHDE_PP_STIRR::TREATMODENO,TREATMODENO);
  addWhereClause(CHDE_PP_STIRR::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDE_PP_STIRR::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, bool Commit, cCBS_ODBC_DBError &Error)
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
  CGTE_PP_STIRR GTE_PP_STIRR(m_pCBS_StdConnection);
  GTE_PP_STIRR.addWhereClause(CGTE_PP_STIRR::PRACNO,PRACNO);
  GTE_PP_STIRR.addWhereClause(CGTE_PP_STIRR::PLANT,PLANT);
  GTE_PP_STIRR.addWhereClause(CGTE_PP_STIRR::PLANTNO,PLANTNO);
  GTE_PP_STIRR.addWhereClause(CGTE_PP_STIRR::TREATMODENO,TREATMODENO);
  GTE_PP_STIRR.addWhereClause(CGTE_PP_STIRR::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT, "<=");

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GTE_PP_STIRR);

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

bool CHDE_PP_STIRR::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDE_PP_STIRR::HEATID,HEATID);
	addWhereClause(CHDE_PP_STIRR::TREATID,TREATID);
	addWhereClause(CHDE_PP_STIRR::PLANT,PLANT);
   
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



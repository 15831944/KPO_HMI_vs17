//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_HOT_METAL_ORDER.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::PRODORDERID("PRODORDERID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ("HM_LADLE_IN_SEQ");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::HOTMETAL_COUNTER("HOTMETAL_COUNTER");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::WEIGHT_PLAN("WEIGHT_PLAN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::TEMP_PLAN("TEMP_PLAN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::ORDERTIME("ORDERTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::DISCHARGETIME("DISCHARGETIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HOT_METAL_ORDER::STATUSNO("STATUSNO");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HOT_METAL_ORDER::CPD_HOT_METAL_ORDER(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_HOT_METAL_ORDER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HOT_METAL_ORDER::CPD_HOT_METAL_ORDER(cCBS_Connection* Connection)
:CSMC_DBData("PD_HOT_METAL_ORDER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HOT_METAL_ORDER::CPD_HOT_METAL_ORDER()
:CSMC_DBData("PD_HOT_METAL_ORDER")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HOT_METAL_ORDER::~CPD_HOT_METAL_ORDER()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_HOT_METAL_ORDER::getPLANT(long Row)
{
  return getString(CPD_HOT_METAL_ORDER::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setPLANT(const std::string& value)
{
  setString(CPD_HOT_METAL_ORDER::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Production oder identification
std::string CPD_HOT_METAL_ORDER::getPRODORDERID(long Row)
{
  return getString(CPD_HOT_METAL_ORDER::PRODORDERID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setPRODORDERID(const std::string& value)
{
  setString(CPD_HOT_METAL_ORDER::PRODORDERID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##HM ladle sequence. Default value = 1, if required at mulitple charging > 1
long CPD_HOT_METAL_ORDER::getHM_LADLE_IN_SEQ(long Row)
{
  return getLong(CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setHM_LADLE_IN_SEQ(long value)
{
  setLong(CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique counter
long CPD_HOT_METAL_ORDER::getHOTMETAL_COUNTER(long Row)
{
  return getLong(CPD_HOT_METAL_ORDER::HOTMETAL_COUNTER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setHOTMETAL_COUNTER(long value)
{
  setLong(CPD_HOT_METAL_ORDER::HOTMETAL_COUNTER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Planned/requested weight
double CPD_HOT_METAL_ORDER::getWEIGHT_PLAN(long Row)
{
  return getDouble(CPD_HOT_METAL_ORDER::WEIGHT_PLAN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setWEIGHT_PLAN(double value)
{
  setDouble(CPD_HOT_METAL_ORDER::WEIGHT_PLAN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Required HM temperature
double CPD_HOT_METAL_ORDER::getTEMP_PLAN(long Row)
{
  return getDouble(CPD_HOT_METAL_ORDER::TEMP_PLAN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setTEMP_PLAN(double value)
{
  setDouble(CPD_HOT_METAL_ORDER::TEMP_PLAN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Time HM was ordered
CDateTime CPD_HOT_METAL_ORDER::getORDERTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_HOT_METAL_ORDER::ORDERTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setORDERTIME(const CDateTime& value)
{
 setString(CPD_HOT_METAL_ORDER::ORDERTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Time HM was discharged in furnace
CDateTime CPD_HOT_METAL_ORDER::getDISCHARGETIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_HOT_METAL_ORDER::DISCHARGETIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setDISCHARGETIME(const CDateTime& value)
{
 setString(CPD_HOT_METAL_ORDER::DISCHARGETIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Number of the order status
long CPD_HOT_METAL_ORDER::getSTATUSNO(long Row)
{
  return getLong(CPD_HOT_METAL_ORDER::STATUSNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HOT_METAL_ORDER::setSTATUSNO(long value)
{
  setLong(CPD_HOT_METAL_ORDER::STATUSNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_HOT_METAL_ORDER::select(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HOT_METAL_ORDER::PLANT,PLANT);
  addWhereClause(CPD_HOT_METAL_ORDER::PRODORDERID,PRODORDERID);
  addWhereClause(CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ,HM_LADLE_IN_SEQ);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_HOT_METAL_ORDER::selectByHotMetalCounter(long HOTMETAL_COUNTER)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HOT_METAL_ORDER::HOTMETAL_COUNTER,HOTMETAL_COUNTER);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CPD_HOT_METAL_ORDER::selectOrderedButNotCharged(const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;
  
  addWhereClause(CPD_HOT_METAL_ORDER::PLANT,PLANT);
  addWhereClause(CPD_HOT_METAL_ORDER::ORDERTIME + " is not null");
  addWhereClause(CPD_HOT_METAL_ORDER::DISCHARGETIME + " is null");

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CPD_HOT_METAL_ORDER::selectOrderedBySeq(const std::string& PLANT, const std::string& PRODORDERID)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HOT_METAL_ORDER::PLANT,PLANT);
  addWhereClause(CPD_HOT_METAL_ORDER::PRODORDERID,PRODORDERID);

  m_Statement += getWhereStatement() + " ORDER BY " + CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ +";";

  return CSMC_DBData::select();
}

bool CPD_HOT_METAL_ORDER::deleteRow(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ)
{
  cleanWhereStatement();

  m_Statement = "delete from " + m_TableName;

  addWhereClause(CPD_HOT_METAL_ORDER::PLANT,PLANT);
  addWhereClause(CPD_HOT_METAL_ORDER::PRODORDERID,PRODORDERID);
  addWhereClause(CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ,HM_LADLE_IN_SEQ);
  
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::deleteRows();
}

bool CPD_HOT_METAL_ORDER::doDischarged(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    // where clause is set in exists
    setDISCHARGETIME(CDateTime());

    result = update();
	}

  if (!result)
		Error = getLastError();

	if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}

	return result;
}

bool CPD_HOT_METAL_ORDER::exists(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ)
{
	cleanWhereStatement();

	m_Statement = "Select PLANT from " + m_TableName;

	addWhereClause(CPD_HOT_METAL_ORDER::PLANT,PLANT);
	addWhereClause(CPD_HOT_METAL_ORDER::PRODORDERID,PRODORDERID);
  addWhereClause(CPD_HOT_METAL_ORDER::HM_LADLE_IN_SEQ,HM_LADLE_IN_SEQ);
   
  std::string sWhereStatement = getWhereStatement();
  //to avoid the exception like 'Select PLANT from PP_HEAT AND ROWNUM = 1 '
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

// beeing backwards compatible
bool CPD_HOT_METAL_ORDER::insertData(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, long HOTMETAL_COUNTER, bool Commit, cCBS_ODBC_DBError &Error)
{
  return insertData(PLANT, PRODORDERID, HM_LADLE_IN_SEQ, HOTMETAL_COUNTER, CSMC_DBData::unspecLong, CSMC_DBData::unspecDouble, CSMC_DBData::unspecDate, CSMC_DBData::unspecDate, Commit, Error);
}

bool CPD_HOT_METAL_ORDER::insertData(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, long HOTMETAL_COUNTER, long WEIGHT_PLAN, double TEMP_PLAN, const CDateTime& ORDERTIME, const CDateTime& DISCHARGETIME, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = false;

  setPLANT(PLANT);
  setPRODORDERID(PRODORDERID);
  setHM_LADLE_IN_SEQ(HM_LADLE_IN_SEQ);
  setHOTMETAL_COUNTER(HOTMETAL_COUNTER);
  setWEIGHT_PLAN(WEIGHT_PLAN);
  setTEMP_PLAN(TEMP_PLAN);
  setORDERTIME(ORDERTIME);
  setDISCHARGETIME(DISCHARGETIME);

  result = insert();
	if (!result)
		Error = getLastError();

	if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}

bool CPD_HOT_METAL_ORDER::setOrderedTime(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true;

  if ( select(PLANT, PRODORDERID, HM_LADLE_IN_SEQ) )
  {
    if ( getORDERTIME(1) == CSMC_DBData::unspecDate )
    {
      setORDERTIME(CDateTime());
      result = update();
    }
  }
  else
  {
    setPLANT(PLANT);
    setPRODORDERID(PRODORDERID);
    setHM_LADLE_IN_SEQ(HM_LADLE_IN_SEQ);
    setORDERTIME(CDateTime());

    result = insert();
  }

  if ( Commit )
  {
    if ( result )
      commit();
    else 
      rollback();
  }

  return result;
}

bool CPD_HOT_METAL_ORDER::updateData(const std::string& PLANT, const std::string &PRODORDERID, long HM_LADLE_IN_SEQ, long WEIGHT_PLAN, double TEMP_PLAN, const CDateTime& ORDERTIME, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    //where clause is set by calling of exists
    setPLANT(PLANT);
    setPRODORDERID(PRODORDERID);
    setHM_LADLE_IN_SEQ(HM_LADLE_IN_SEQ);
    setWEIGHT_PLAN(WEIGHT_PLAN);
    setTEMP_PLAN(TEMP_PLAN);
    setORDERTIME(ORDERTIME);

    result = update();
	}

	if (!result)
		Error = getLastError();

  if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}

bool CPD_HOT_METAL_ORDER::updateDischargeTime(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, const CDateTime& DISCHARGETIME, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    // where clause is set in exists
    setDISCHARGETIME(DISCHARGETIME);

    result = update();
	}

  if (!result)
		Error = getLastError();

	if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}

	return result;
}

bool CPD_HOT_METAL_ORDER::updateHotMetalData(const std::string& PLANT, const std::string &PRODORDERID, long HM_LADLE_IN_SEQ, long HOTMETAL_COUNTER, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    //where clause is set by calling of exists

    setHOTMETAL_COUNTER(HOTMETAL_COUNTER);

    result = update();
	}

	if (!result)
		Error = getLastError();

  if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}

bool CPD_HOT_METAL_ORDER::updateOrderTime(const std::string& PLANT, const std::string& PRODORDERID, long HM_LADLE_IN_SEQ, const CDateTime& ORDERTIME, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    // where clause is set in exists
    setORDERTIME(ORDERTIME);

    result = update();
	}

  if (!result)
		Error = getLastError();

	if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}

	return result;
}

bool CPD_HOT_METAL_ORDER::updatePlanData(const std::string& PLANT, const std::string &PRODORDERID, long HM_LADLE_IN_SEQ, long WEIGHT_PLAN, double TEMP_PLAN, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = exists(PLANT, PRODORDERID, HM_LADLE_IN_SEQ);
	if (result)
	{
    //where clause is set by calling of exists
    setWEIGHT_PLAN(WEIGHT_PLAN);
    setTEMP_PLAN(TEMP_PLAN);

    result = update();
	}

	if (!result)
		Error = getLastError();

  if (Commit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}



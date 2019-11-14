//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_STIRR_SPEC.h"
#include "CHDE_PP_STIRR_SPEC.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::SPECEGY("SPECEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::ELEC_ENERGY("ELEC_ENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::STIRRFLOW("STIRRFLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::STIRRGASTYPE("STIRRGASTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_STIRR_SPEC::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR_SPEC::CHDE_PP_STIRR_SPEC(cCBS_StdConnection* Connection)
:CSMC_DBData("HDE_PP_STIRR_SPEC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR_SPEC::CHDE_PP_STIRR_SPEC(cCBS_Connection* Connection)
:CSMC_DBData("HDE_PP_STIRR_SPEC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR_SPEC::CHDE_PP_STIRR_SPEC()
:CSMC_DBData("HDE_PP_STIRR_SPEC")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_STIRR_SPEC::~CHDE_PP_STIRR_SPEC()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR_SPEC::getHEATID(long Row)
{
  return getString(CHDE_PP_STIRR_SPEC::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setHEATID(const std::string& value)
{
  setString(CHDE_PP_STIRR_SPEC::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR_SPEC::getTREATID(long Row)
{
  return getString(CHDE_PP_STIRR_SPEC::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setTREATID(const std::string& value)
{
  setString(CHDE_PP_STIRR_SPEC::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR_SPEC::getPLANT(long Row)
{
  return getString(CHDE_PP_STIRR_SPEC::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setPLANT(const std::string& value)
{
  setString(CHDE_PP_STIRR_SPEC::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getPRACNO(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setPRACNO(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getTREATMODENO(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setTREATMODENO(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR_SPEC::getPRACPHASE(long Row)
{
  return getString(CHDE_PP_STIRR_SPEC::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setPRACPHASE(const std::string& value)
{
  setString(CHDE_PP_STIRR_SPEC::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getSTEPNO(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setSTEPNO(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_STIRR_SPEC::getSPECEGY(long Row)
{
  return getDouble(CHDE_PP_STIRR_SPEC::SPECEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setSPECEGY(double value)
{
  setDouble(CHDE_PP_STIRR_SPEC::SPECEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getELEC_ENERGY(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setELEC_ENERGY(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_STIRR_SPEC::getSTIRRFLOW(long Row)
{
  return getDouble(CHDE_PP_STIRR_SPEC::STIRRFLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setSTIRRFLOW(double value)
{
  setDouble(CHDE_PP_STIRR_SPEC::STIRRFLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_STIRR_SPEC::getSTIRRGASTYPE(long Row)
{
  return getString(CHDE_PP_STIRR_SPEC::STIRRGASTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setSTIRRGASTYPE(const std::string& value)
{
  setString(CHDE_PP_STIRR_SPEC::STIRRGASTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_STIRR_SPEC::getDISPLAY_ORDER(long Row)
{
  return getLong(CHDE_PP_STIRR_SPEC::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_STIRR_SPEC::setDISPLAY_ORDER(long value)
{
  setLong(CHDE_PP_STIRR_SPEC::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDE_PP_STIRR_SPEC::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PRACPHASE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDE_PP_STIRR_SPEC::HEATID,HEATID);
  addWhereClause(CHDE_PP_STIRR_SPEC::TREATID,TREATID);
  addWhereClause(CHDE_PP_STIRR_SPEC::PLANT,PLANT);
  addWhereClause(CHDE_PP_STIRR_SPEC::PRACNO,PRACNO);
  addWhereClause(CHDE_PP_STIRR_SPEC::TREATMODENO,TREATMODENO);
  addWhereClause(CHDE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CHDE_PP_STIRR_SPEC::PRACPHASE,PRACPHASE);
  addWhereClause(CHDE_PP_STIRR_SPEC::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDE_PP_STIRR_SPEC::selectByOrder(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PRACPHASE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDE_PP_STIRR_SPEC::HEATID,HEATID);
  addWhereClause(CHDE_PP_STIRR_SPEC::TREATID,TREATID);
  addWhereClause(CHDE_PP_STIRR_SPEC::PLANT,PLANT);
  addWhereClause(CHDE_PP_STIRR_SPEC::PRACNO,PRACNO);
  addWhereClause(CHDE_PP_STIRR_SPEC::TREATMODENO,TREATMODENO);
  addWhereClause(CHDE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CHDE_PP_STIRR_SPEC::PRACPHASE,PRACPHASE);
  addWhereClause(CHDE_PP_STIRR_SPEC::STEPNO,STEPNO);

  m_Statement += getWhereStatement() +" order by HEATID,TREATID,PLANT,PRACNO,TREATMODENO,PRACPHASE,STEPNO ASC;";

  return CSMC_DBData::select();
}

bool CHDE_PP_STIRR_SPEC::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT ,bool Commit, cCBS_ODBC_DBError &Error)
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
  CGTE_PP_STIRR_SPEC GTE_PP_STIRR_SPEC(m_pCBS_StdConnection);
  GTE_PP_STIRR_SPEC.addWhereClause(CGTE_PP_STIRR_SPEC::PLANT,PLANT);
  GTE_PP_STIRR_SPEC.addWhereClause(CGTE_PP_STIRR_SPEC::PLANTNO,PLANTNO);
  GTE_PP_STIRR_SPEC.addWhereClause(CGTE_PP_STIRR_SPEC::PRACNO,PRACNO);
  GTE_PP_STIRR_SPEC.addWhereClause(CGTE_PP_STIRR_SPEC::TREATMODENO,TREATMODENO);
  GTE_PP_STIRR_SPEC.addWhereClause(CGTE_PP_STIRR_SPEC::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT, "<=");

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GTE_PP_STIRR_SPEC);

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

bool CHDE_PP_STIRR_SPEC::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDE_PP_STIRR_SPEC::HEATID,HEATID);
	addWhereClause(CHDE_PP_STIRR_SPEC::TREATID,TREATID);
	addWhereClause(CHDE_PP_STIRR_SPEC::PLANT,PLANT);
   
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


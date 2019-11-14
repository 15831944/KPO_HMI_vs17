//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_MAT_FEED_RES.h"
#include "CHD_MAT_FEED_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::PROCPHASE("PROCPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::PROCPHASENO("PROCPHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::STEPDUR("STEPDUR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::ELECENERGY("ELECENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::MATWEIGHT("MATWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::FEEDINGRATE("FEEDINGRATE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_MAT_FEED_RES::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_MAT_FEED_RES::CHD_MAT_FEED_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_MAT_FEED_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_MAT_FEED_RES::CHD_MAT_FEED_RES(cCBS_Connection* Connection)
:CSMC_DBData("HD_MAT_FEED_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_MAT_FEED_RES::CHD_MAT_FEED_RES()
:CSMC_DBData("HD_MAT_FEED_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_MAT_FEED_RES::~CHD_MAT_FEED_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_MAT_FEED_RES::getHEATID(long Row)
{
  return getString(CHD_MAT_FEED_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setHEATID(const std::string& value)
{
  setString(CHD_MAT_FEED_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_MAT_FEED_RES::getTREATID(long Row)
{
  return getString(CHD_MAT_FEED_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setTREATID(const std::string& value)
{
  setString(CHD_MAT_FEED_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_MAT_FEED_RES::getPLANT(long Row)
{
  return getString(CHD_MAT_FEED_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setPLANT(const std::string& value)
{
  setString(CHD_MAT_FEED_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Phases are e.g. Basket, LiqAdd for EAF
std::string CHD_MAT_FEED_RES::getPROCPHASE(long Row)
{
  return getString(CHD_MAT_FEED_RES::PROCPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setPROCPHASE(const std::string& value)
{
  setString(CHD_MAT_FEED_RES::PROCPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##If process phases are countable we use ths as the counter. For EAF e.g, MeltDownBsk: 1
long CHD_MAT_FEED_RES::getPROCPHASENO(long Row)
{
  return getLong(CHD_MAT_FEED_RES::PROCPHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setPROCPHASENO(long value)
{
  setLong(CHD_MAT_FEED_RES::PROCPHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code
std::string CHD_MAT_FEED_RES::getMAT_CODE(long Row)
{
  return getString(CHD_MAT_FEED_RES::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setMAT_CODE(const std::string& value)
{
  setString(CHD_MAT_FEED_RES::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Energy step
long CHD_MAT_FEED_RES::getSTEPNO(long Row)
{
  return getLong(CHD_MAT_FEED_RES::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setSTEPNO(long value)
{
  setLong(CHD_MAT_FEED_RES::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Relative start time since heat announcement
double CHD_MAT_FEED_RES::getSTARTTIME(long Row)
{
  return getDouble(CHD_MAT_FEED_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setSTARTTIME(double value)
{
  setDouble(CHD_MAT_FEED_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Calculated duration of step in minutes
double CHD_MAT_FEED_RES::getSTEPDUR(long Row)
{
  return getDouble(CHD_MAT_FEED_RES::STEPDUR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setSTEPDUR(double value)
{
  setDouble(CHD_MAT_FEED_RES::STEPDUR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Total electric energy consumption in case of electric heating, kWh
double CHD_MAT_FEED_RES::getELECENERGY(long Row)
{
  return getDouble(CHD_MAT_FEED_RES::ELECENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setELECENERGY(double value)
{
  setDouble(CHD_MAT_FEED_RES::ELECENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Actual weight
double CHD_MAT_FEED_RES::getMATWEIGHT(long Row)
{
  return getDouble(CHD_MAT_FEED_RES::MATWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setMATWEIGHT(double value)
{
  setDouble(CHD_MAT_FEED_RES::MATWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Absolute feeding rate in kg/min
double CHD_MAT_FEED_RES::getFEEDINGRATE(long Row)
{
  return getDouble(CHD_MAT_FEED_RES::FEEDINGRATE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setFEEDINGRATE(double value)
{
  setDouble(CHD_MAT_FEED_RES::FEEDINGRATE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CHD_MAT_FEED_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_MAT_FEED_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_MAT_FEED_RES::setREVTIME(const CDateTime& value)
{
 setString(CHD_MAT_FEED_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_MAT_FEED_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long PROCPHASENO, const std::string& MAT_CODE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_MAT_FEED_RES::HEATID,HEATID);
  addWhereClause(CHD_MAT_FEED_RES::TREATID,TREATID);
  addWhereClause(CHD_MAT_FEED_RES::PLANT,PLANT);
  addWhereClause(CHD_MAT_FEED_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CHD_MAT_FEED_RES::PROCPHASENO,PROCPHASENO);
  addWhereClause(CHD_MAT_FEED_RES::MAT_CODE,MAT_CODE);
  addWhereClause(CHD_MAT_FEED_RES::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_MAT_FEED_RES::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = true;
	//some data found -> delete them
	if (exists(HEATID, TREATID, PLANT))
	{
		result = deleteRows();
		if (!result)
      setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

  // preparing setting for source table
  CPD_MAT_FEED_RES PD_MAT_FEED_RES(m_pCBS_StdConnection);
  PD_MAT_FEED_RES.addWhereClause(CPD_MAT_FEED_RES::HEATID,HEATID);
  PD_MAT_FEED_RES.addWhereClause(CPD_MAT_FEED_RES::TREATID,TREATID);
  PD_MAT_FEED_RES.addWhereClause(CPD_MAT_FEED_RES::PLANT,PLANT);

  result = result && copyByInsert(&PD_MAT_FEED_RES);

	if (!result)
		Error = getLastError();

	if(Commit)
  {
		if (result)
			commit();
		else
			rollback();
  }

	return result;
}

bool CHD_MAT_FEED_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_MAT_FEED_RES::HEATID,HEATID);
	addWhereClause(CHD_MAT_FEED_RES::TREATID,TREATID);
	addWhereClause(CHD_MAT_FEED_RES::PLANT,PLANT);
   
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



//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTL_PP_EL_STEP.h"
#include "CHDL_PP_EL_STEP.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::ACTIVITYNAME("ACTIVITYNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::DURATION("DURATION");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::DELTA_TEMP("DELTA_TEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::VOLTTAP("VOLTTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_EL_STEP::IMPCURVE("IMPCURVE");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_EL_STEP::CHDL_PP_EL_STEP(cCBS_StdConnection* Connection)
:CSMC_DBData("HDL_PP_EL_STEP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_EL_STEP::CHDL_PP_EL_STEP(cCBS_Connection* Connection)
:CSMC_DBData("HDL_PP_EL_STEP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_EL_STEP::CHDL_PP_EL_STEP()
:CSMC_DBData("HDL_PP_EL_STEP")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_EL_STEP::~CHDL_PP_EL_STEP()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_EL_STEP::getHEATID(long Row)
{
  return getString(CHDL_PP_EL_STEP::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setHEATID(const std::string& value)
{
  setString(CHDL_PP_EL_STEP::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_EL_STEP::getTREATID(long Row)
{
  return getString(CHDL_PP_EL_STEP::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setTREATID(const std::string& value)
{
  setString(CHDL_PP_EL_STEP::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_EL_STEP::getPLANT(long Row)
{
  return getString(CHDL_PP_EL_STEP::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setPLANT(const std::string& value)
{
  setString(CHDL_PP_EL_STEP::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getPRACNO(long Row)
{
  return getLong(CHDL_PP_EL_STEP::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setPRACNO(long value)
{
  setLong(CHDL_PP_EL_STEP::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_EL_STEP::getACTIVITYNAME(long Row)
{
  return getString(CHDL_PP_EL_STEP::ACTIVITYNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setACTIVITYNAME(const std::string& value)
{
  setString(CHDL_PP_EL_STEP::ACTIVITYNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_EL_STEP::getPRACPHASE(long Row)
{
  return getString(CHDL_PP_EL_STEP::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setPRACPHASE(const std::string& value)
{
  setString(CHDL_PP_EL_STEP::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getSTEPNO(long Row)
{
  return getLong(CHDL_PP_EL_STEP::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setSTEPNO(long value)
{
  setLong(CHDL_PP_EL_STEP::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getDURATION(long Row)
{
  return getLong(CHDL_PP_EL_STEP::DURATION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setDURATION(long value)
{
  setLong(CHDL_PP_EL_STEP::DURATION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getDELTA_TEMP(long Row)
{
  return getLong(CHDL_PP_EL_STEP::DELTA_TEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setDELTA_TEMP(long value)
{
  setLong(CHDL_PP_EL_STEP::DELTA_TEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getVOLTTAP(long Row)
{
  return getLong(CHDL_PP_EL_STEP::VOLTTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setVOLTTAP(long value)
{
  setLong(CHDL_PP_EL_STEP::VOLTTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_EL_STEP::getIMPCURVE(long Row)
{
  return getLong(CHDL_PP_EL_STEP::IMPCURVE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_EL_STEP::setIMPCURVE(long value)
{
  setLong(CHDL_PP_EL_STEP::IMPCURVE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDL_PP_EL_STEP::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, const std::string& ACTIVITYNAME, const std::string& PRACPHASE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDL_PP_EL_STEP::HEATID,HEATID);
  addWhereClause(CHDL_PP_EL_STEP::TREATID,TREATID);
  addWhereClause(CHDL_PP_EL_STEP::PLANT,PLANT);
  addWhereClause(CHDL_PP_EL_STEP::PRACNO,PRACNO);
  addWhereClause(CHDL_PP_EL_STEP::ACTIVITYNAME,ACTIVITYNAME);
  addWhereClause(CHDL_PP_EL_STEP::PRACPHASE,PRACPHASE);
  addWhereClause(CHDL_PP_EL_STEP::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDL_PP_EL_STEP::selectByHeatPlant(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDL_PP_EL_STEP::HEATID,HEATID);
  addWhereClause(CHDL_PP_EL_STEP::TREATID,TREATID);
  addWhereClause(CHDL_PP_EL_STEP::PLANT,PLANT);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CHDL_PP_EL_STEP::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error)
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
  CGTL_PP_EL_STEP GTL_PP_EL_STEP(m_pCBS_StdConnection);
  if ( GTL_PP_EL_STEP.select(PLANTNO, PRACNO, CSMC_DBData::unspecString, CSMC_DBData::unspecString, CSMC_DBData::unspecLong) )
  {
    GTL_PP_EL_STEP.cleanWhereStatement();
    GTL_PP_EL_STEP.addWhereClause(CGTL_PP_EL_STEP::PLANTNO,PLANTNO);
    GTL_PP_EL_STEP.addWhereClause(CGTL_PP_EL_STEP::PRACNO,PRACNO);
  }
  else
  {
    //copy with general plant number
    GTL_PP_EL_STEP.cleanWhereStatement();
    GTL_PP_EL_STEP.addWhereClause(CGTL_PP_EL_STEP::PLANTNO,(long)0);
    GTL_PP_EL_STEP.addWhereClause(CGTL_PP_EL_STEP::PRACNO,PRACNO);
  }

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GTL_PP_EL_STEP);

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

bool CHDL_PP_EL_STEP::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDL_PP_EL_STEP::HEATID,HEATID);
	addWhereClause(CHDL_PP_EL_STEP::TREATID,TREATID);
	addWhereClause(CHDL_PP_EL_STEP::PLANT,PLANT);
   
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



//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDL_ACTIVITY_RES.h"
#include "CHDL_ACTIVITY_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::ACTIVITYNAME("ACTIVITYNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::STEELMASS("STEELMASS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::SLAGMASS("SLAGMASS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::TEMP("TEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::DURUNTENDOFPHASE("DURUNTENDOFPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::DATEENDOFPHASE("DATEENDOFPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::VOLTTAP("VOLTTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::IMPCURVE("IMPCURVE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::ELEC_ENERGY("ELEC_ENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::UPDATENO("UPDATENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::STIRR_FLOW("STIRR_FLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::STIRR_GAS_TYPE("STIRR_GAS_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::STIRR_INTENSITY("STIRR_INTENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::ENABLE("ENABLE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::PRIORITY("PRIORITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_ACTIVITY_RES::ORDERNO("ORDERNO");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_ACTIVITY_RES::CHDL_ACTIVITY_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("HDL_ACTIVITY_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_ACTIVITY_RES::CHDL_ACTIVITY_RES(cCBS_Connection* Connection)
:CSMC_DBData("HDL_ACTIVITY_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_ACTIVITY_RES::CHDL_ACTIVITY_RES()
:CSMC_DBData("HDL_ACTIVITY_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_ACTIVITY_RES::~CHDL_ACTIVITY_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_ACTIVITY_RES::getHEATID(long Row)
{
  return getString(CHDL_ACTIVITY_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setHEATID(const std::string& value)
{
  setString(CHDL_ACTIVITY_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_ACTIVITY_RES::getTREATID(long Row)
{
  return getString(CHDL_ACTIVITY_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setTREATID(const std::string& value)
{
  setString(CHDL_ACTIVITY_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_ACTIVITY_RES::getPLANT(long Row)
{
  return getString(CHDL_ACTIVITY_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setPLANT(const std::string& value)
{
  setString(CHDL_ACTIVITY_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_ACTIVITY_RES::getACTIVITYNAME(long Row)
{
  return getString(CHDL_ACTIVITY_RES::ACTIVITYNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setACTIVITYNAME(const std::string& value)
{
  setString(CHDL_ACTIVITY_RES::ACTIVITYNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getSTEELMASS(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::STEELMASS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSTEELMASS(double value)
{
  setDouble(CHDL_ACTIVITY_RES::STEELMASS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getSLAGMASS(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::SLAGMASS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSLAGMASS(double value)
{
  setDouble(CHDL_ACTIVITY_RES::SLAGMASS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getTEMP(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::TEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setTEMP(double value)
{
  setDouble(CHDL_ACTIVITY_RES::TEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getDURUNTENDOFPHASE(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::DURUNTENDOFPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setDURUNTENDOFPHASE(double value)
{
  setDouble(CHDL_ACTIVITY_RES::DURUNTENDOFPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDL_ACTIVITY_RES::getDATEENDOFPHASE(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDL_ACTIVITY_RES::DATEENDOFPHASE, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setDATEENDOFPHASE(const CDateTime& value)
{
 setString(CHDL_ACTIVITY_RES::DATEENDOFPHASE, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDL_ACTIVITY_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDL_ACTIVITY_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setREVTIME(const CDateTime& value)
{
 setString(CHDL_ACTIVITY_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getVOLTTAP(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::VOLTTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setVOLTTAP(long value)
{
  setLong(CHDL_ACTIVITY_RES::VOLTTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getIMPCURVE(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::IMPCURVE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setIMPCURVE(long value)
{
  setLong(CHDL_ACTIVITY_RES::IMPCURVE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getELEC_ENERGY(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setELEC_ENERGY(double value)
{
  setDouble(CHDL_ACTIVITY_RES::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getUPDATENO(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::UPDATENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setUPDATENO(long value)
{
  setLong(CHDL_ACTIVITY_RES::UPDATENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getSTARTTIME(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSTARTTIME(double value)
{
  setDouble(CHDL_ACTIVITY_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_ACTIVITY_RES::getSTIRR_FLOW(long Row)
{
  return getDouble(CHDL_ACTIVITY_RES::STIRR_FLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSTIRR_FLOW(double value)
{
  setDouble(CHDL_ACTIVITY_RES::STIRR_FLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_ACTIVITY_RES::getSTIRR_GAS_TYPE(long Row)
{
  return getString(CHDL_ACTIVITY_RES::STIRR_GAS_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSTIRR_GAS_TYPE(const std::string& value)
{
  setString(CHDL_ACTIVITY_RES::STIRR_GAS_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getSTIRR_INTENSITY(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::STIRR_INTENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setSTIRR_INTENSITY(long value)
{
  setLong(CHDL_ACTIVITY_RES::STIRR_INTENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getENABLE(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::ENABLE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setENABLE(long value)
{
  setLong(CHDL_ACTIVITY_RES::ENABLE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getPRIORITY(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::PRIORITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setPRIORITY(long value)
{
  setLong(CHDL_ACTIVITY_RES::PRIORITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_ACTIVITY_RES::getORDERNO(long Row)
{
  return getLong(CHDL_ACTIVITY_RES::ORDERNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_ACTIVITY_RES::setORDERNO(long value)
{
  setLong(CHDL_ACTIVITY_RES::ORDERNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDL_ACTIVITY_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& ACTIVITYNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDL_ACTIVITY_RES::HEATID,HEATID);
  addWhereClause(CHDL_ACTIVITY_RES::TREATID,TREATID);
  addWhereClause(CHDL_ACTIVITY_RES::PLANT,PLANT);
  addWhereClause(CHDL_ACTIVITY_RES::ACTIVITYNAME,ACTIVITYNAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDL_ACTIVITY_RES::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
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
  CPDL_ACTIVITY_RES PDL_ACTIVITY_RES(m_pCBS_StdConnection);
  PDL_ACTIVITY_RES.addWhereClause(CPDL_ACTIVITY_RES::HEATID,HEATID);
  PDL_ACTIVITY_RES.addWhereClause(CPDL_ACTIVITY_RES::TREATID,TREATID);
  PDL_ACTIVITY_RES.addWhereClause(CPDL_ACTIVITY_RES::PLANT,PLANT);

  result = result && copyByInsert(&PDL_ACTIVITY_RES);

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

bool CHDL_ACTIVITY_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDL_ACTIVITY_RES::HEATID,HEATID);
	addWhereClause(CHDL_ACTIVITY_RES::TREATID,TREATID);
	addWhereClause(CHDL_ACTIVITY_RES::PLANT,PLANT);
  
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



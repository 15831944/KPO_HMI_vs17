//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CHDH_CYCL_MEAS_DATA.h"
#include "CPDH_CYCL_MEAS_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::TREATTYPE("TREATTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE("DURSINCEHEATANNOUNCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::FLOW_LIME("FLOW_LIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::FLOW_MG("FLOW_MG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::FLOW_CARBIDE("FLOW_CARBIDE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::CONS_LIME("CONS_LIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::CONS_MG("CONS_MG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_CYCL_MEAS_DATA::CONS_CARBIDE("CONS_CARBIDE");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_CYCL_MEAS_DATA::CHDH_CYCL_MEAS_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("HDH_CYCL_MEAS_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_CYCL_MEAS_DATA::CHDH_CYCL_MEAS_DATA(cCBS_Connection* Connection)
:CSMC_DBData("HDH_CYCL_MEAS_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_CYCL_MEAS_DATA::CHDH_CYCL_MEAS_DATA()
:CSMC_DBData("HDH_CYCL_MEAS_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_CYCL_MEAS_DATA::~CHDH_CYCL_MEAS_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_CYCL_MEAS_DATA::getHM_ID(long Row)
{
  return getString(CHDH_CYCL_MEAS_DATA::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setHM_ID(const std::string& value)
{
  setString(CHDH_CYCL_MEAS_DATA::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_CYCL_MEAS_DATA::getTREATID(long Row)
{
  return getString(CHDH_CYCL_MEAS_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setTREATID(const std::string& value)
{
  setString(CHDH_CYCL_MEAS_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_CYCL_MEAS_DATA::getPLANT(long Row)
{
  return getString(CHDH_CYCL_MEAS_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setPLANT(const std::string& value)
{
  setString(CHDH_CYCL_MEAS_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDH_CYCL_MEAS_DATA::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDH_CYCL_MEAS_DATA::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setREVTIME(const CDateTime& value)
{
 setString(CHDH_CYCL_MEAS_DATA::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDH_CYCL_MEAS_DATA::getTREATTYPE(long Row)
{
  return getLong(CHDH_CYCL_MEAS_DATA::TREATTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setTREATTYPE(long value)
{
  setLong(CHDH_CYCL_MEAS_DATA::TREATTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getDURSINCEHEATANNOUNCE(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setDURSINCEHEATANNOUNCE(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getFLOW_LIME(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::FLOW_LIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setFLOW_LIME(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::FLOW_LIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getFLOW_MG(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::FLOW_MG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setFLOW_MG(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::FLOW_MG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getFLOW_CARBIDE(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::FLOW_CARBIDE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setFLOW_CARBIDE(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::FLOW_CARBIDE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getCONS_LIME(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::CONS_LIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setCONS_LIME(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::CONS_LIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getCONS_MG(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::CONS_MG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setCONS_MG(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::CONS_MG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_CYCL_MEAS_DATA::getCONS_CARBIDE(long Row)
{
  return getDouble(CHDH_CYCL_MEAS_DATA::CONS_CARBIDE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_CYCL_MEAS_DATA::setCONS_CARBIDE(double value)
{
  setDouble(CHDH_CYCL_MEAS_DATA::CONS_CARBIDE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDH_CYCL_MEAS_DATA::select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, const CDateTime& REVTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDH_CYCL_MEAS_DATA::HM_ID,HM_ID);
  addWhereClause(CHDH_CYCL_MEAS_DATA::TREATID,TREATID);
  addWhereClause(CHDH_CYCL_MEAS_DATA::PLANT,PLANT);
  addWhereClause(CHDH_CYCL_MEAS_DATA::REVTIME,REVTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
bool CHDH_CYCL_MEAS_DATA::copy(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(HM_ID, TREATID, PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}
	
  // preparing setting for source table
  CPDH_CYCL_MEAS_DATA PDH_CYCL_MEAS_DATA(getpCBSConnection());
  PDH_CYCL_MEAS_DATA.addWhereClause("HM_ID"  ,HM_ID);
  PDH_CYCL_MEAS_DATA.addWhereClause("TREATID" ,TREATID);
  PDH_CYCL_MEAS_DATA.addWhereClause("PLANT"   ,PLANT);

  result = result && copyByInsert(&PDH_CYCL_MEAS_DATA);

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

bool CHDH_CYCL_MEAS_DATA::exists(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HM_ID from " + m_TableName;

	addWhereClause("HM_ID",HM_ID);
	addWhereClause("TREATID",TREATID);
	addWhereClause("PLANT",PLANT);

  // do not use ROWNUM in "addWhereClause", ROWNUM is not a table column and where statement will be used for deletion at "deleteRows"
	m_Statement += getWhereStatement() + " AND ROWNUM = 1 ;";


	return CSMC_DBData::select();
}


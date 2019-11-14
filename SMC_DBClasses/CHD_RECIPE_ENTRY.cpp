//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_RECIPE_ENTRY.h"
#include "CHD_RECIPE_ENTRY.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::RECIPENAME("RECIPENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::RECIPENO("RECIPENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::SOURCE("SOURCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::BATCHSTATUSNO("BATCHSTATUSNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::MATWEIGHT("MATWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::CHARGINGPRIO("CHARGINGPRIO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_RECIPE_ENTRY::MATFEEDSPEED("MATFEEDSPEED");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_RECIPE_ENTRY::CHD_RECIPE_ENTRY(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_RECIPE_ENTRY",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_RECIPE_ENTRY::CHD_RECIPE_ENTRY(cCBS_Connection* Connection)
:CSMC_DBData("HD_RECIPE_ENTRY",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_RECIPE_ENTRY::CHD_RECIPE_ENTRY()
:CSMC_DBData("HD_RECIPE_ENTRY")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_RECIPE_ENTRY::~CHD_RECIPE_ENTRY()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_RECIPE_ENTRY::getHEATID(long Row)
{
  return getString(CHD_RECIPE_ENTRY::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setHEATID(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_RECIPE_ENTRY::getTREATID(long Row)
{
  return getString(CHD_RECIPE_ENTRY::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setTREATID(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_RECIPE_ENTRY::getPLANT(long Row)
{
  return getString(CHD_RECIPE_ENTRY::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setPLANT(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHD_RECIPE_ENTRY::getRECIPENAME(long Row)
{
  return getString(CHD_RECIPE_ENTRY::RECIPENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setRECIPENAME(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::RECIPENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHD_RECIPE_ENTRY::getRECIPENO(long Row)
{
  return getLong(CHD_RECIPE_ENTRY::RECIPENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setRECIPENO(long value)
{
  setLong(CHD_RECIPE_ENTRY::RECIPENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHD_RECIPE_ENTRY::getSOURCE(long Row)
{
  return getString(CHD_RECIPE_ENTRY::SOURCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setSOURCE(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::SOURCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Batch Status number (Number in the L1/L2 Telgramm in the, Material handling report
long CHD_RECIPE_ENTRY::getBATCHSTATUSNO(long Row)
{
  return getLong(CHD_RECIPE_ENTRY::BATCHSTATUSNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setBATCHSTATUSNO(long value)
{
  setLong(CHD_RECIPE_ENTRY::BATCHSTATUSNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code
std::string CHD_RECIPE_ENTRY::getMAT_CODE(long Row)
{
  return getString(CHD_RECIPE_ENTRY::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setMAT_CODE(const std::string& value)
{
  setString(CHD_RECIPE_ENTRY::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material weight in kg.
double CHD_RECIPE_ENTRY::getMATWEIGHT(long Row)
{
  return getDouble(CHD_RECIPE_ENTRY::MATWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setMATWEIGHT(double value)
{
  setDouble(CHD_RECIPE_ENTRY::MATWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Charging Priority (Defined in Materila data)
long CHD_RECIPE_ENTRY::getCHARGINGPRIO(long Row)
{
  return getLong(CHD_RECIPE_ENTRY::CHARGINGPRIO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setCHARGINGPRIO(long value)
{
  setLong(CHD_RECIPE_ENTRY::CHARGINGPRIO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Batch Material feed speed., BATCHMATFEEDSPEED=, TOTALBATCHWEIGHT/, Discharged Time Discharge Start Time, Only filled for Status 10!!!
double CHD_RECIPE_ENTRY::getMATFEEDSPEED(long Row)
{
  return getDouble(CHD_RECIPE_ENTRY::MATFEEDSPEED, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_RECIPE_ENTRY::setMATFEEDSPEED(double value)
{
  setDouble(CHD_RECIPE_ENTRY::MATFEEDSPEED, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_RECIPE_ENTRY::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& RECIPENAME, long RECIPENO, const std::string& SOURCE, long BATCHSTATUSNO, const std::string& MAT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_RECIPE_ENTRY::HEATID,HEATID);
  addWhereClause(CHD_RECIPE_ENTRY::TREATID,TREATID);
  addWhereClause(CHD_RECIPE_ENTRY::PLANT,PLANT);
  addWhereClause(CHD_RECIPE_ENTRY::RECIPENAME,RECIPENAME);
  addWhereClause(CHD_RECIPE_ENTRY::RECIPENO,RECIPENO);
  addWhereClause(CHD_RECIPE_ENTRY::SOURCE,SOURCE);
  addWhereClause(CHD_RECIPE_ENTRY::BATCHSTATUSNO,BATCHSTATUSNO);
  addWhereClause(CHD_RECIPE_ENTRY::MAT_CODE,MAT_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_RECIPE_ENTRY::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select * from " + m_TableName;

	addWhereClause(CHD_RECIPE_ENTRY::HEATID,HEATID);
	addWhereClause(CHD_RECIPE_ENTRY::TREATID,TREATID);
	addWhereClause(CHD_RECIPE_ENTRY::PLANT,PLANT);

	m_Statement += getWhereStatement() + ";";

	return CSMC_DBData::select();
}

bool CHD_RECIPE_ENTRY::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !select(HEATID, TREATID, PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

  // preparing setting for source table
  CPD_RECIPE_ENTRY PD_RECIPE_ENTRY(m_pCBS_StdConnection);
  PD_RECIPE_ENTRY.addWhereClause(CPD_RECIPE_ENTRY::HEATID,HEATID);
  PD_RECIPE_ENTRY.addWhereClause(CPD_RECIPE_ENTRY::TREATID,TREATID);
  PD_RECIPE_ENTRY.addWhereClause(CPD_RECIPE_ENTRY::PLANT,PLANT);

  result = result && copyByInsert(&PD_RECIPE_ENTRY);

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

bool CHD_RECIPE_ENTRY::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_RECIPE_ENTRY::HEATID,HEATID);
	addWhereClause(CHD_RECIPE_ENTRY::TREATID,TREATID);
	addWhereClause(CHD_RECIPE_ENTRY::PLANT,PLANT);
   
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



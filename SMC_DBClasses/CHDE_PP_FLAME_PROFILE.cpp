//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTE_PP_FLAME_PROFILE.h"
#include "CHDE_PP_FLAME_PROFILE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::BURNERNAME("BURNERNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::FLAMEPROFILENO("FLAMEPROFILENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::OXYGENFLOW("OXYGENFLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::GASFLOW("GASFLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::AIRFLOW("AIRFLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::OXYGENGASRATIO("OXYGENGASRATIO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_FLAME_PROFILE::CORRECTIONPOWER("CORRECTIONPOWER");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_FLAME_PROFILE::CHDE_PP_FLAME_PROFILE(cCBS_StdConnection* Connection)
:CSMC_DBData("HDE_PP_FLAME_PROFILE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_FLAME_PROFILE::CHDE_PP_FLAME_PROFILE(cCBS_Connection* Connection)
:CSMC_DBData("HDE_PP_FLAME_PROFILE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_FLAME_PROFILE::CHDE_PP_FLAME_PROFILE()
:CSMC_DBData("HDE_PP_FLAME_PROFILE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_FLAME_PROFILE::~CHDE_PP_FLAME_PROFILE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_FLAME_PROFILE::getHEATID(long Row)
{
  return getString(CHDE_PP_FLAME_PROFILE::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setHEATID(const std::string& value)
{
  setString(CHDE_PP_FLAME_PROFILE::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_FLAME_PROFILE::getTREATID(long Row)
{
  return getString(CHDE_PP_FLAME_PROFILE::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setTREATID(const std::string& value)
{
  setString(CHDE_PP_FLAME_PROFILE::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_FLAME_PROFILE::getPLANT(long Row)
{
  return getString(CHDE_PP_FLAME_PROFILE::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setPLANT(const std::string& value)
{
  setString(CHDE_PP_FLAME_PROFILE::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_FLAME_PROFILE::getBURNERNAME(long Row)
{
  return getString(CHDE_PP_FLAME_PROFILE::BURNERNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setBURNERNAME(const std::string& value)
{
  setString(CHDE_PP_FLAME_PROFILE::BURNERNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_FLAME_PROFILE::getFLAMEPROFILENO(long Row)
{
  return getLong(CHDE_PP_FLAME_PROFILE::FLAMEPROFILENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setFLAMEPROFILENO(long value)
{
  setLong(CHDE_PP_FLAME_PROFILE::FLAMEPROFILENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_FLAME_PROFILE::getOXYGENFLOW(long Row)
{
  return getDouble(CHDE_PP_FLAME_PROFILE::OXYGENFLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setOXYGENFLOW(double value)
{
  setDouble(CHDE_PP_FLAME_PROFILE::OXYGENFLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_FLAME_PROFILE::getGASFLOW(long Row)
{
  return getDouble(CHDE_PP_FLAME_PROFILE::GASFLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setGASFLOW(double value)
{
  setDouble(CHDE_PP_FLAME_PROFILE::GASFLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_FLAME_PROFILE::getAIRFLOW(long Row)
{
  return getDouble(CHDE_PP_FLAME_PROFILE::AIRFLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setAIRFLOW(double value)
{
  setDouble(CHDE_PP_FLAME_PROFILE::AIRFLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_FLAME_PROFILE::getOXYGENGASRATIO(long Row)
{
  return getDouble(CHDE_PP_FLAME_PROFILE::OXYGENGASRATIO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setOXYGENGASRATIO(double value)
{
  setDouble(CHDE_PP_FLAME_PROFILE::OXYGENGASRATIO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_FLAME_PROFILE::getCORRECTIONPOWER(long Row)
{
  return getLong(CHDE_PP_FLAME_PROFILE::CORRECTIONPOWER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_FLAME_PROFILE::setCORRECTIONPOWER(long value)
{
  setLong(CHDE_PP_FLAME_PROFILE::CORRECTIONPOWER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDE_PP_FLAME_PROFILE::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& BURNERNAME, long FLAMEPROFILENO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDE_PP_FLAME_PROFILE::HEATID,HEATID);
  addWhereClause(CHDE_PP_FLAME_PROFILE::TREATID,TREATID);
  addWhereClause(CHDE_PP_FLAME_PROFILE::PLANT,PLANT);
  addWhereClause(CHDE_PP_FLAME_PROFILE::BURNERNAME,BURNERNAME);
  addWhereClause(CHDE_PP_FLAME_PROFILE::FLAMEPROFILENO,FLAMEPROFILENO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDE_PP_FLAME_PROFILE::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
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
  CGTE_PP_FLAME_PROFILE GTE_PP_FLAME_PROFILE(m_pCBS_StdConnection);

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GTE_PP_FLAME_PROFILE);

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

bool CHDE_PP_FLAME_PROFILE::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDE_PP_FLAME_PROFILE::HEATID,HEATID);
	addWhereClause(CHDE_PP_FLAME_PROFILE::TREATID,TREATID);
	addWhereClause(CHDE_PP_FLAME_PROFILE::PLANT,PLANT);
   
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



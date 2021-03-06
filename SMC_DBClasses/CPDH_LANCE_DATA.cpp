//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDH_LANCE_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::LANCE_NO("LANCE_NO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::LANCE_IN_USE_HEAT("LANCE_IN_USE_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_LANCE_DATA::LANCE_IN_USE_TOTAL("LANCE_IN_USE_TOTAL");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_LANCE_DATA::CPDH_LANCE_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("PDH_LANCE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_LANCE_DATA::CPDH_LANCE_DATA(cCBS_Connection* Connection)
:CSMC_DBData("PDH_LANCE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_LANCE_DATA::CPDH_LANCE_DATA()
:CSMC_DBData("PDH_LANCE_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_LANCE_DATA::~CPDH_LANCE_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDH_LANCE_DATA::getHM_ID(long Row)
{
  return getString(CPDH_LANCE_DATA::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setHM_ID(const std::string& value)
{
  setString(CPDH_LANCE_DATA::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDH_LANCE_DATA::getTREATID(long Row)
{
  return getString(CPDH_LANCE_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setTREATID(const std::string& value)
{
  setString(CPDH_LANCE_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDH_LANCE_DATA::getPLANT(long Row)
{
  return getString(CPDH_LANCE_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setPLANT(const std::string& value)
{
  setString(CPDH_LANCE_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDH_LANCE_DATA::getLANCE_NO(long Row)
{
  return getLong(CPDH_LANCE_DATA::LANCE_NO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setLANCE_NO(long value)
{
  setLong(CPDH_LANCE_DATA::LANCE_NO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDH_LANCE_DATA::getLANCE_IN_USE_HEAT(long Row)
{
  return getLong(CPDH_LANCE_DATA::LANCE_IN_USE_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setLANCE_IN_USE_HEAT(long value)
{
  setLong(CPDH_LANCE_DATA::LANCE_IN_USE_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDH_LANCE_DATA::getLANCE_IN_USE_TOTAL(long Row)
{
  return getLong(CPDH_LANCE_DATA::LANCE_IN_USE_TOTAL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_LANCE_DATA::setLANCE_IN_USE_TOTAL(long value)
{
  setLong(CPDH_LANCE_DATA::LANCE_IN_USE_TOTAL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDH_LANCE_DATA::select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long LANCE_NO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDH_LANCE_DATA::HM_ID,HM_ID);
  addWhereClause(CPDH_LANCE_DATA::TREATID,TREATID);
  addWhereClause(CPDH_LANCE_DATA::PLANT,PLANT);
  addWhereClause(CPDH_LANCE_DATA::LANCE_NO,LANCE_NO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPDH_LANCE_DATA::exists(const string& HMID, const string& TREATID, const string& PLANT, long LANCENO)
{
	cleanWhereStatement();

	m_Statement = "Select count(*) as DATA_EXISTS from " + m_TableName;

	addWhereClause("HM_ID",HMID);
	addWhereClause("TREATID",TREATID);
	addWhereClause("PLANT",PLANT);
	addWhereClause("LANCE_NO",LANCENO);
	m_Statement += getWhereStatement() + ";";

	bool result = CSMC_DBData::select();
	return result && getLong("DATA_EXISTS", 1) > 0;
}

bool CPDH_LANCE_DATA::doONPowerBlowing(const string& HMID, const string& TREATID, const string& PLANT, long LANCENO,bool pCommit)
{
	std::stringstream sql;
	CDateTime tmExpire;
	if (exists(HMID, TREATID, PLANT,LANCENO))
	{
		//Heat exists -> update
		sql << "update PDH_LANCE_DATA set ("
				<< "LANCE_NO = " << LANCENO << ", "
				<< "LANCE_IN_USE_HEAT = " << 1 << ", "
				<< "LANCE_IN_USE_TOTAL = " << 1 
				<< " where HM_ID = '" << HMID << "' "
				<< " and TREATID = '" << TREATID << "' "
				<< "and PLANT = '" << PLANT << "'";
	}
	else
	{
		//Heat not exists -> insert
		sql << "insert into PDH_LANCE_DATA ("
				<< "  HM_ID, TREATID, PLANT, LANCE_NO, LANCE_IN_USE_HEAT, LANCE_IN_USE_TOTAL) "
				<< " values('" << HMID << "', '" << TREATID << "', '" << PLANT << "', " << LANCENO  << ", 1,1)";
			
	}

	bool result = executeSQL(sql.str());
	if (!result)
      log("ERROR: CPDH_LANCE_DATA::doONPowerBlowing failed",1);
	
	if (pCommit)
	{
		if (result)
			commit();
		else
			rollback();
	}
	return result;
}




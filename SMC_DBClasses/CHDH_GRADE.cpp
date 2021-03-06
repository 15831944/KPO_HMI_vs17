//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CHDH_GRADE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::STEELGRADECODE("STEELGRADECODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::LIQTEMP("LIQTEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::USERCODE("USERCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_GRADE::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_GRADE::CHDH_GRADE(cCBS_StdConnection* Connection)
:CSMC_DBData("HDH_GRADE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_GRADE::CHDH_GRADE(cCBS_Connection* Connection)
:CSMC_DBData("HDH_GRADE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_GRADE::CHDH_GRADE()
:CSMC_DBData("HDH_GRADE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_GRADE::~CHDH_GRADE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_GRADE::getHM_ID(long Row)
{
  return getString(CHDH_GRADE::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setHM_ID(const std::string& value)
{
  setString(CHDH_GRADE::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_GRADE::getTREATID(long Row)
{
  return getString(CHDH_GRADE::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setTREATID(const std::string& value)
{
  setString(CHDH_GRADE::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_GRADE::getPLANT(long Row)
{
  return getString(CHDH_GRADE::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setPLANT(const std::string& value)
{
  setString(CHDH_GRADE::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_GRADE::getSTEELGRADECODE(long Row)
{
  return getString(CHDH_GRADE::STEELGRADECODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setSTEELGRADECODE(const std::string& value)
{
  setString(CHDH_GRADE::STEELGRADECODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_GRADE::getLIQTEMP(long Row)
{
  return getDouble(CHDH_GRADE::LIQTEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setLIQTEMP(double value)
{
  setDouble(CHDH_GRADE::LIQTEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_GRADE::getUSERCODE(long Row)
{
  return getString(CHDH_GRADE::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setUSERCODE(const std::string& value)
{
  setString(CHDH_GRADE::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDH_GRADE::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDH_GRADE::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_GRADE::setREVTIME(const CDateTime& value)
{
 setString(CHDH_GRADE::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDH_GRADE::select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDH_GRADE::HM_ID,HM_ID);
  addWhereClause(CHDH_GRADE::TREATID,TREATID);
  addWhereClause(CHDH_GRADE::PLANT,PLANT);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
bool CHDH_GRADE::copyHDHGrade(const string &pSteelGrade, const string& pHeatId, const string& pTreatId, const string& pPlant, bool pCommit)
{
	bool result=true;
	std::stringstream sql;
	//some data found -> delete them
	/*if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(string("delete from HD_GRADE faild"), 0, "delete from HD_GRADE where " + getWhereStatement());
	}*/

	sql << "insert into HDH_GRADE (HM_ID, TREATID, PLANT, STEELGRADECODE, LIQTEMP, USERCODE, REVTIME) "
		<< "(select '" << pHeatId << "', '" << pTreatId << "', '" << pPlant << "', STEELGRADECODE_ACT, TEMP_INITIAL, USERCODE, REVTIME "
		<< "from PDH_HM_DATA where STEELGRADECODE_ACT = '" << pSteelGrade << "')";

	result = result && executeSQL(sql.str());
	if (!result)
		/*pError = getLastError();*/

	if(pCommit)
  {
		if (result)
			this->commit();
		else
			rollback();
  }

	return result;
}



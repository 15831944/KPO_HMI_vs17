//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CHDH_ACTION.h"
#include "CGC_ACTION_DEF.h"
#include "DEF_GC_ACTION_DEF.h"

//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::ACTIONNO("ACTIONNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::DURSINCEHEATANNOUNCEMENT("DURSINCEHEATANNOUNCEMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::ACTIONNAME("ACTIONNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::ACTIONUNIT("ACTIONUNIT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::ACTIONVALUE("ACTIONVALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::ACTIONSTATUS("ACTIONSTATUS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDH_ACTION::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_ACTION::CHDH_ACTION(cCBS_StdConnection* Connection)
:CSMC_DBData("HDH_ACTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_ACTION::CHDH_ACTION(cCBS_Connection* Connection)
:CSMC_DBData("HDH_ACTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_ACTION::CHDH_ACTION()
:CSMC_DBData("HDH_ACTION")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDH_ACTION::~CHDH_ACTION()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getHM_ID(long Row)
{
  return getString(CHDH_ACTION::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setHM_ID(const std::string& value)
{
  setString(CHDH_ACTION::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getTREATID(long Row)
{
  return getString(CHDH_ACTION::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setTREATID(const std::string& value)
{
  setString(CHDH_ACTION::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getPLANT(long Row)
{
  return getString(CHDH_ACTION::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setPLANT(const std::string& value)
{
  setString(CHDH_ACTION::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDH_ACTION::getACTIONNO(long Row)
{
  return getLong(CHDH_ACTION::ACTIONNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setACTIONNO(long value)
{
  setLong(CHDH_ACTION::ACTIONNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_ACTION::getDURSINCEHEATANNOUNCEMENT(long Row)
{
  return getDouble(CHDH_ACTION::DURSINCEHEATANNOUNCEMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setDURSINCEHEATANNOUNCEMENT(double value)
{
  setDouble(CHDH_ACTION::DURSINCEHEATANNOUNCEMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDH_ACTION::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CHDH_ACTION::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CHDH_ACTION::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getACTIONNAME(long Row)
{
  return getString(CHDH_ACTION::ACTIONNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setACTIONNAME(const std::string& value)
{
  setString(CHDH_ACTION::ACTIONNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getACTIONUNIT(long Row)
{
  return getString(CHDH_ACTION::ACTIONUNIT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setACTIONUNIT(const std::string& value)
{
  setString(CHDH_ACTION::ACTIONUNIT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDH_ACTION::getACTIONVALUE(long Row)
{
  return getString(CHDH_ACTION::ACTIONVALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setACTIONVALUE(const std::string& value)
{
  setString(CHDH_ACTION::ACTIONVALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDH_ACTION::getACTIONSTATUS(long Row)
{
  return getLong(CHDH_ACTION::ACTIONSTATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setACTIONSTATUS(long value)
{
  setLong(CHDH_ACTION::ACTIONSTATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDH_ACTION::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDH_ACTION::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDH_ACTION::setREVTIME(const CDateTime& value)
{
 setString(CHDH_ACTION::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDH_ACTION::select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDH_ACTION::HM_ID,HM_ID);
  addWhereClause(CHDH_ACTION::TREATID,TREATID);
  addWhereClause(CHDH_ACTION::PLANT,PLANT);
  addWhereClause(CHDH_ACTION::ACTIONNO,ACTIONNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
bool CHDH_ACTION::copyHDH_Action(const string& pHeatId, const string& pTreatId, const string& pPlant, bool pCommit)
{
	bool result=true;
	std::stringstream sql;
	//some data found -> delete them
	/*if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(string("delete from HDH_ACTION faild"), 0, "delete from HDH_ACTION where " + getWhereStatement());
	}*/

	sql << "insert into HDH_ACTION (select * from PDH_ACTION "
		<< "  where HM_ID = '" << pHeatId << "'"
		<< "    and TREATID = '" << pTreatId << "'"
		<< "    and PLANT = '" << pPlant << "')";

	result = result && executeSQL(sql.str());
	if (!result)
		//pError = getLastError();

	if(pCommit)
  {
		if (result)
			this->commit();
		else
			rollback();
  }

	return result;
}
bool CHDH_ACTION::update_HeatStart(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT,long pDurSinceHeatStart,long pDurSinceHeatAnnounce)
{
	bool result;
	int i=1;
	CDateTime now;
  std::stringstream sql;
	try
	{

		std::string actionName = "";
		CGC_ACTION_DEF   GC_ACTION_DEF (m_pCBS_StdConnection);
		if(GC_ACTION_DEF.select(DEF_GC_ACTION_DEF::HeatStart))
		{
			actionName = GC_ACTION_DEF.getACTIONNAME(1);
		}

	sql << "update HDH_ACTION set " 
			<< "ACTIONNO = " << DEF_GC_ACTION_DEF::HeatStart << " ,"   // 1001
			<< "ACTIONNAME = '" << actionName << "' ," 
			<< "DURSINCEHEATANNOUNCEMENT = " << pDurSinceHeatAnnounce << " ,"		
			<< "DURSINCESTARTOFHEAT = " << pDurSinceHeatStart << " ,"					
			<< "REVTIME = '" << now.toDBString() << "' "
			<< "where HM_ID = '" << HM_ID<< "' and TREATID = '" << TREATID << "' and PLANT = '" << PLANT << "'"  ;

	result = executeSQL(sql.str());
	if (result)
    {
      commit();
    }
    else
    {
      rollback();
      log("ERROR: CPDH_ACTION::doHeatStart failed",1);
    }
	}
	catch(...)
	{
		result=false;
	}

	return result;
}

bool CHDH_ACTION::delete_HDH_ACTION(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT)
{
	bool result;
  std::stringstream sql;
	try
	{
		addWhereClause("HM_ID",HM_ID);
		addWhereClause("TREATID",TREATID);
		addWhereClause("PLANT",PLANT);
		//sql += getWhereStatement() + ";";
		sql << "delete from HDH_ACTION" 
			  << getWhereStatement();
		/*<< "  where HEATID = '" << pHeatId << "'"
		<< "   and TREATID = '" << pTreatId << "'"
		<< "   and PLANT = '" << pPlant << "'";*/

	result = executeSQL(sql.str());
	if (result)
    {
      commit();
    }
    else
    {
      rollback();
      log("ERROR: CHDH_ACTION::delete_HDH_ACTION failed",1);
    }
	}
	catch(...)
	{
		result=false;
	}

	return result;
}
bool CHDH_ACTION::update_HeatDeparture(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT,long pDurSinceHeatStart,long pDurSinceHeatAnnounce)
{
	bool result;
	int i=1;
	CDateTime now;
  std::stringstream sql;
	try
	{

		std::string actionName = "";
		CGC_ACTION_DEF   GC_ACTION_DEF (m_pCBS_StdConnection);
		if(GC_ACTION_DEF.select(DEF_GC_ACTION_DEF::Departure))
		{
			actionName = GC_ACTION_DEF.getACTIONNAME(1);
		}

	sql << "update HDH_ACTION set " 
			<< "ACTIONNO = " << DEF_GC_ACTION_DEF::Departure << " ,"   //1004
			<< "ACTIONNAME = '" << actionName << "' ," 
			<< "DURSINCEHEATANNOUNCEMENT = " << pDurSinceHeatAnnounce << " ,"		
			<< "DURSINCESTARTOFHEAT = " << pDurSinceHeatStart << " ,"					
			<< "ACTIONSTATUS  = " << i << " ,"			// TO DO LATER
			<< "REVTIME = '" << now.toDBString() << "' "
			<< "where HM_ID = '" << HM_ID << "' and TREATID = '" << TREATID << "' and PLANT = '" << PLANT << "'"  ;

	result = executeSQL(sql.str());
	if (result)
    {
      commit();
    }
    else
    {
      rollback();
      log("ERROR: CHDH_ACTION::update_HeatDeparture failed",1);
    }
	}
	catch(...)
	{
		result=false;
	}

	return result;
}


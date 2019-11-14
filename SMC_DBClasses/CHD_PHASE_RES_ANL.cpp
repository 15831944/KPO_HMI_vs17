//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CSMC_EventLogFrameController.h"
#include "CPD_PHASE_RES_ANL.h"
#include "CHD_PHASE_RES_ANL.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::RES_PHASENO("RES_PHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::ENAME("ENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PHASE_RES_ANL::ANL("ANL");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PHASE_RES_ANL::CHD_PHASE_RES_ANL(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_PHASE_RES_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PHASE_RES_ANL::CHD_PHASE_RES_ANL(cCBS_Connection* Connection)
:CSMC_DBData("HD_PHASE_RES_ANL",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PHASE_RES_ANL::CHD_PHASE_RES_ANL()
:CSMC_DBData("HD_PHASE_RES_ANL")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PHASE_RES_ANL::~CHD_PHASE_RES_ANL()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_PHASE_RES_ANL::getHEATID(long Row)
{
  return getString(CHD_PHASE_RES_ANL::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setHEATID(const std::string& value)
{
  setString(CHD_PHASE_RES_ANL::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_PHASE_RES_ANL::getTREATID(long Row)
{
  return getString(CHD_PHASE_RES_ANL::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setTREATID(const std::string& value)
{
  setString(CHD_PHASE_RES_ANL::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_PHASE_RES_ANL::getPLANT(long Row)
{
  return getString(CHD_PHASE_RES_ANL::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setPLANT(const std::string& value)
{
  setString(CHD_PHASE_RES_ANL::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Result Phase No for storing into the Result tables
long CHD_PHASE_RES_ANL::getRES_PHASENO(long Row)
{
  return getLong(CHD_PHASE_RES_ANL::RES_PHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setRES_PHASENO(long value)
{
  setLong(CHD_PHASE_RES_ANL::RES_PHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Element or slag compound name
std::string CHD_PHASE_RES_ANL::getENAME(long Row)
{
  return getString(CHD_PHASE_RES_ANL::ENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setENAME(const std::string& value)
{
  setString(CHD_PHASE_RES_ANL::ENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Analysis value
double CHD_PHASE_RES_ANL::getANL(long Row)
{
  return getDouble(CHD_PHASE_RES_ANL::ANL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PHASE_RES_ANL::setANL(double value)
{
  setDouble(CHD_PHASE_RES_ANL::ANL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_PHASE_RES_ANL::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long RES_PHASENO, const std::string& ENAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_PHASE_RES_ANL::HEATID,HEATID);
  addWhereClause(CHD_PHASE_RES_ANL::TREATID,TREATID);
  addWhereClause(CHD_PHASE_RES_ANL::PLANT,PLANT);
  addWhereClause(CHD_PHASE_RES_ANL::RES_PHASENO,RES_PHASENO);
  addWhereClause(CHD_PHASE_RES_ANL::ENAME,ENAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_PHASE_RES_ANL::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
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
  CPD_PHASE_RES_ANL PD_PHASE_RES_ANL(m_pCBS_StdConnection);
  PD_PHASE_RES_ANL.addWhereClause(CPD_PHASE_RES_ANL::HEATID,HEATID);
  PD_PHASE_RES_ANL.addWhereClause(CPD_PHASE_RES_ANL::TREATID,TREATID);
  PD_PHASE_RES_ANL.addWhereClause(CPD_PHASE_RES_ANL::PLANT,PLANT);

  result = result && copyByInsert(&PD_PHASE_RES_ANL);

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

bool CHD_PHASE_RES_ANL::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_PHASE_RES_ANL::HEATID,HEATID);
	addWhereClause(CHD_PHASE_RES_ANL::TREATID,TREATID);
	addWhereClause(CHD_PHASE_RES_ANL::PLANT,PLANT);
   
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


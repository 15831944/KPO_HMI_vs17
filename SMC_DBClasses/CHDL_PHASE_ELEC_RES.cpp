//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDL_PHASE_ELEC_RES.h"
#include "CHDL_PHASE_ELEC_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::ACTIVITYNAME("ACTIVITYNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::BASWEIGHT("BASWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::VOLTTAP("VOLTTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::IMPCURVE("IMPCURVE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::SPECEGY("SPECEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::PHASEDUR("PHASEDUR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PHASE_ELEC_RES::ELEC_ENERGY("ELEC_ENERGY");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PHASE_ELEC_RES::CHDL_PHASE_ELEC_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("HDL_PHASE_ELEC_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PHASE_ELEC_RES::CHDL_PHASE_ELEC_RES(cCBS_Connection* Connection)
:CSMC_DBData("HDL_PHASE_ELEC_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PHASE_ELEC_RES::CHDL_PHASE_ELEC_RES()
:CSMC_DBData("HDL_PHASE_ELEC_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PHASE_ELEC_RES::~CHDL_PHASE_ELEC_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PHASE_ELEC_RES::getHEATID(long Row)
{
  return getString(CHDL_PHASE_ELEC_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setHEATID(const std::string& value)
{
  setString(CHDL_PHASE_ELEC_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PHASE_ELEC_RES::getTREATID(long Row)
{
  return getString(CHDL_PHASE_ELEC_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setTREATID(const std::string& value)
{
  setString(CHDL_PHASE_ELEC_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PHASE_ELEC_RES::getPLANT(long Row)
{
  return getString(CHDL_PHASE_ELEC_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setPLANT(const std::string& value)
{
  setString(CHDL_PHASE_ELEC_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PHASE_ELEC_RES::getACTIVITYNAME(long Row)
{
  return getString(CHDL_PHASE_ELEC_RES::ACTIVITYNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setACTIVITYNAME(const std::string& value)
{
  setString(CHDL_PHASE_ELEC_RES::ACTIVITYNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PHASE_ELEC_RES::getPRACPHASE(long Row)
{
  return getString(CHDL_PHASE_ELEC_RES::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setPRACPHASE(const std::string& value)
{
  setString(CHDL_PHASE_ELEC_RES::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PHASE_ELEC_RES::getSTEPNO(long Row)
{
  return getLong(CHDL_PHASE_ELEC_RES::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setSTEPNO(long value)
{
  setLong(CHDL_PHASE_ELEC_RES::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_PHASE_ELEC_RES::getBASWEIGHT(long Row)
{
  return getDouble(CHDL_PHASE_ELEC_RES::BASWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setBASWEIGHT(double value)
{
  setDouble(CHDL_PHASE_ELEC_RES::BASWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PHASE_ELEC_RES::getVOLTTAP(long Row)
{
  return getLong(CHDL_PHASE_ELEC_RES::VOLTTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setVOLTTAP(long value)
{
  setLong(CHDL_PHASE_ELEC_RES::VOLTTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PHASE_ELEC_RES::getIMPCURVE(long Row)
{
  return getLong(CHDL_PHASE_ELEC_RES::IMPCURVE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setIMPCURVE(long value)
{
  setLong(CHDL_PHASE_ELEC_RES::IMPCURVE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_PHASE_ELEC_RES::getSPECEGY(long Row)
{
  return getDouble(CHDL_PHASE_ELEC_RES::SPECEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setSPECEGY(double value)
{
  setDouble(CHDL_PHASE_ELEC_RES::SPECEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_PHASE_ELEC_RES::getSTARTTIME(long Row)
{
  return getDouble(CHDL_PHASE_ELEC_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setSTARTTIME(double value)
{
  setDouble(CHDL_PHASE_ELEC_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_PHASE_ELEC_RES::getPHASEDUR(long Row)
{
  return getDouble(CHDL_PHASE_ELEC_RES::PHASEDUR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setPHASEDUR(double value)
{
  setDouble(CHDL_PHASE_ELEC_RES::PHASEDUR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHDL_PHASE_ELEC_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHDL_PHASE_ELEC_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setREVTIME(const CDateTime& value)
{
 setString(CHDL_PHASE_ELEC_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDL_PHASE_ELEC_RES::getELEC_ENERGY(long Row)
{
  return getDouble(CHDL_PHASE_ELEC_RES::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PHASE_ELEC_RES::setELEC_ENERGY(double value)
{
  setDouble(CHDL_PHASE_ELEC_RES::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDL_PHASE_ELEC_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& ACTIVITYNAME, const std::string& PRACPHASE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDL_PHASE_ELEC_RES::HEATID,HEATID);
  addWhereClause(CHDL_PHASE_ELEC_RES::TREATID,TREATID);
  addWhereClause(CHDL_PHASE_ELEC_RES::PLANT,PLANT);
  addWhereClause(CHDL_PHASE_ELEC_RES::ACTIVITYNAME,ACTIVITYNAME);
  addWhereClause(CHDL_PHASE_ELEC_RES::PRACPHASE,PRACPHASE);
  addWhereClause(CHDL_PHASE_ELEC_RES::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDL_PHASE_ELEC_RES::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
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
  CPDL_PHASE_ELEC_RES PDL_PHASE_ELEC_RES(m_pCBS_StdConnection);
  PDL_PHASE_ELEC_RES.addWhereClause(CPDL_PHASE_ELEC_RES::HEATID,HEATID);
  PDL_PHASE_ELEC_RES.addWhereClause(CPDL_PHASE_ELEC_RES::TREATID,TREATID);
  PDL_PHASE_ELEC_RES.addWhereClause(CPDL_PHASE_ELEC_RES::PLANT,PLANT);

  result = result && copyByInsert(&PDL_PHASE_ELEC_RES);

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

bool CHDL_PHASE_ELEC_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select HEATID from " + m_TableName;

  addWhereClause(CHDL_PHASE_ELEC_RES::HEATID,HEATID);
  addWhereClause(CHDL_PHASE_ELEC_RES::TREATID,TREATID);
  addWhereClause(CHDL_PHASE_ELEC_RES::PLANT,PLANT);
   

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



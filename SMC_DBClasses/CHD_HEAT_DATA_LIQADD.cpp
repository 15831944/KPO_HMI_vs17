//## Copyright (C) 2012 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_HEAT_DATA_LIQADD.h"
#include "CHD_HEAT_DATA_LIQADD.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::LIQADDNO("LIQADDNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::STEELWEIGHT("STEELWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::SLAGWEIGHT("SLAGWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::SAMPLE_REF("SAMPLE_REF");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::LADLENO("LADLENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::LADLETYPE("LADLETYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::STATUS("STATUS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::LIQADDTYPE("LIQADDTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::DISCHARGETIME("DISCHARGETIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::MANUALCHANGED("MANUALCHANGED");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::LASTPLANT("LASTPLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::THERMALSTATUS("THERMALSTATUS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::SCULLMASS("SCULLMASS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::PRETREAT_CNT("PRETREAT_CNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_HEAT_DATA_LIQADD::HOTMETAL_CNT("HOTMETAL_CNT");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_HEAT_DATA_LIQADD::CHD_HEAT_DATA_LIQADD(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_HEAT_DATA_LIQADD",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_HEAT_DATA_LIQADD::CHD_HEAT_DATA_LIQADD(cCBS_Connection* Connection)
:CSMC_DBData("HD_HEAT_DATA_LIQADD",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_HEAT_DATA_LIQADD::CHD_HEAT_DATA_LIQADD()
:CSMC_DBData("HD_HEAT_DATA_LIQADD")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_HEAT_DATA_LIQADD::~CHD_HEAT_DATA_LIQADD()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_HEAT_DATA_LIQADD::getHEATID(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setHEATID(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_HEAT_DATA_LIQADD::getTREATID(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setTREATID(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_HEAT_DATA_LIQADD::getPLANT(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setPLANT(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Number of liquid addition
long CHD_HEAT_DATA_LIQADD::getLIQADDNO(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::LIQADDNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setLIQADDNO(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::LIQADDNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Steel weight in kg
double CHD_HEAT_DATA_LIQADD::getSTEELWEIGHT(long Row)
{
  return getDouble(CHD_HEAT_DATA_LIQADD::STEELWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setSTEELWEIGHT(double value)
{
  setDouble(CHD_HEAT_DATA_LIQADD::STEELWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Slag weight in kg
double CHD_HEAT_DATA_LIQADD::getSLAGWEIGHT(long Row)
{
  return getDouble(CHD_HEAT_DATA_LIQADD::SLAGWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setSLAGWEIGHT(double value)
{
  setDouble(CHD_HEAT_DATA_LIQADD::SLAGWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique sample reference
long CHD_HEAT_DATA_LIQADD::getSAMPLE_REF(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::SAMPLE_REF, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setSAMPLE_REF(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::SAMPLE_REF, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique ladle number
long CHD_HEAT_DATA_LIQADD::getLADLENO(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::LADLENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setLADLENO(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::LADLENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##e.g. Hot Metal -> H, Teeming -> T
std::string CHD_HEAT_DATA_LIQADD::getLADLETYPE(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::LADLETYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setLADLETYPE(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::LADLETYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Status of liquid addition
std::string CHD_HEAT_DATA_LIQADD::getSTATUS(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::STATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setSTATUS(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::STATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Type of liquid addition
std::string CHD_HEAT_DATA_LIQADD::getLIQADDTYPE(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::LIQADDTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setLIQADDTYPE(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::LIQADDTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHD_HEAT_DATA_LIQADD::getDISCHARGETIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_HEAT_DATA_LIQADD::DISCHARGETIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setDISCHARGETIME(const CDateTime& value)
{
 setString(CHD_HEAT_DATA_LIQADD::DISCHARGETIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##1= Manual Changed on HMI, 0 = Not Manual changed
long CHD_HEAT_DATA_LIQADD::getMANUALCHANGED(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::MANUALCHANGED, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setMANUALCHANGED(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::MANUALCHANGED, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Where does the ladle comes from? Taken from PD_PRETREATDATA during announcement.
std::string CHD_HEAT_DATA_LIQADD::getLASTPLANT(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::LASTPLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setLASTPLANT(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::LASTPLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##H=Hot, M=Medium, C=Cold
std::string CHD_HEAT_DATA_LIQADD::getTHERMALSTATUS(long Row)
{
  return getString(CHD_HEAT_DATA_LIQADD::THERMALSTATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setTHERMALSTATUS(const std::string& value)
{
  setString(CHD_HEAT_DATA_LIQADD::THERMALSTATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng. Unit : kg, Mass of ladle scull
double CHD_HEAT_DATA_LIQADD::getSCULLMASS(long Row)
{
  return getDouble(CHD_HEAT_DATA_LIQADD::SCULLMASS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setSCULLMASS(double value)
{
  setDouble(CHD_HEAT_DATA_LIQADD::SCULLMASS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment data for liquid addition from pretreatment data
long CHD_HEAT_DATA_LIQADD::getPRETREAT_CNT(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::PRETREAT_CNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setPRETREAT_CNT(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::PRETREAT_CNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment data for liquid addition from hot metal
long CHD_HEAT_DATA_LIQADD::getHOTMETAL_CNT(long Row)
{
  return getLong(CHD_HEAT_DATA_LIQADD::HOTMETAL_CNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_HEAT_DATA_LIQADD::setHOTMETAL_CNT(long value)
{
  setLong(CHD_HEAT_DATA_LIQADD::HOTMETAL_CNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_HEAT_DATA_LIQADD::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long LIQADDNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_HEAT_DATA_LIQADD::HEATID,HEATID);
  addWhereClause(CHD_HEAT_DATA_LIQADD::TREATID,TREATID);
  addWhereClause(CHD_HEAT_DATA_LIQADD::PLANT,PLANT);
  addWhereClause(CHD_HEAT_DATA_LIQADD::LIQADDNO,LIQADDNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_HEAT_DATA_LIQADD::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true;

  //the heat ID, treat ID and PLANT must be set
  if ( CSMC_DBData::unspecString == HEATID
    || CSMC_DBData::unspecString == TREATID
    || CSMC_DBData::unspecString == PLANT
     )
  {
    setLastError("HEAT_INFORMATION_NOT_SET",-1,"");
    Error = getLastError();
    log ("CHD_HEAT_DATA_LIQADD::copy heat information not set!",1);
    return false;
  }

  //some data found -> delete them
  if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecLong) )
  {
    result = deleteRows();

    if (!result)
    {
      Error = getLastError();
      return result;
    }
  }//if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecLong) )

  // preparing setting for source table
  CPD_HEAT_DATA_LIQADD PD_HEAT_DATA_LIQADD(m_pCBS_StdConnection);

  PD_HEAT_DATA_LIQADD.addWhereClause(CPD_HEAT_DATA_LIQADD::HEATID  ,HEATID);
  PD_HEAT_DATA_LIQADD.addWhereClause(CPD_HEAT_DATA_LIQADD::TREATID ,TREATID);
  PD_HEAT_DATA_LIQADD.addWhereClause(CPD_HEAT_DATA_LIQADD::PLANT   ,PLANT);

  result = result && copyByInsert(&PD_HEAT_DATA_LIQADD);

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



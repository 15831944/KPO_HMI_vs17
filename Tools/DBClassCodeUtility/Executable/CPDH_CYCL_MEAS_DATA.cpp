//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDH_CYCL_MEAS_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::TREATTYPE("TREATTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE("DURSINCEHEATANNOUNCE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::FLOW_LIME("FLOW_LIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::FLOW_MG("FLOW_MG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::FLOW_CARBIDE("FLOW_CARBIDE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::CONS_LIME("CONS_LIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::CONS_MG("CONS_MG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::CONS_CARBIDE("CONS_CARBIDE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::GAS_FLOW_N2("GAS_FLOW_N2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::GAS_PRESSURE_N2("GAS_PRESSURE_N2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::CONS_N2("CONS_N2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDH_CYCL_MEAS_DATA::LANCEPOS("LANCEPOS");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_CYCL_MEAS_DATA::CPDH_CYCL_MEAS_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("PDH_CYCL_MEAS_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_CYCL_MEAS_DATA::CPDH_CYCL_MEAS_DATA(cCBS_Connection* Connection)
:CSMC_DBData("PDH_CYCL_MEAS_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_CYCL_MEAS_DATA::CPDH_CYCL_MEAS_DATA()
:CSMC_DBData("PDH_CYCL_MEAS_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDH_CYCL_MEAS_DATA::~CPDH_CYCL_MEAS_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal ID of treatment at HMDS
std::string CPDH_CYCL_MEAS_DATA::getHM_ID(long Row)
{
  return getString(CPDH_CYCL_MEAS_DATA::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setHM_ID(const std::string& value)
{
  setString(CPDH_CYCL_MEAS_DATA::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal ID for counting repeated L2-activities for same HM_ID
std::string CPDH_CYCL_MEAS_DATA::getTREATID(long Row)
{
  return getString(CPDH_CYCL_MEAS_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setTREATID(const std::string& value)
{
  setString(CPDH_CYCL_MEAS_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDH_CYCL_MEAS_DATA::getPLANT(long Row)
{
  return getString(CPDH_CYCL_MEAS_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setPLANT(const std::string& value)
{
  setString(CPDH_CYCL_MEAS_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of revision
CDateTime CPDH_CYCL_MEAS_DATA::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDH_CYCL_MEAS_DATA::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setREVTIME(const CDateTime& value)
{
 setString(CPDH_CYCL_MEAS_DATA::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDH_CYCL_MEAS_DATA::getTREATTYPE(long Row)
{
  return getLong(CPDH_CYCL_MEAS_DATA::TREATTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setTREATTYPE(long value)
{
  setLong(CPDH_CYCL_MEAS_DATA::TREATTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDH_CYCL_MEAS_DATA::getDURSINCEHEATANNOUNCE(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setDURSINCEHEATANNOUNCE(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::DURSINCEHEATANNOUNCE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDH_CYCL_MEAS_DATA::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Lime injection rate [kg/min]
double CPDH_CYCL_MEAS_DATA::getFLOW_LIME(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::FLOW_LIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setFLOW_LIME(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::FLOW_LIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Magnesium injection rate [kg/min]
double CPDH_CYCL_MEAS_DATA::getFLOW_MG(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::FLOW_MG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setFLOW_MG(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::FLOW_MG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Carbide injection rate [kg/min]
double CPDH_CYCL_MEAS_DATA::getFLOW_CARBIDE(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::FLOW_CARBIDE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setFLOW_CARBIDE(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::FLOW_CARBIDE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Lime consumption since heat announcement
double CPDH_CYCL_MEAS_DATA::getCONS_LIME(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::CONS_LIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setCONS_LIME(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::CONS_LIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Magnesium consumption since heat announcement
double CPDH_CYCL_MEAS_DATA::getCONS_MG(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::CONS_MG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setCONS_MG(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::CONS_MG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Carbon consumption since heat announcement
double CPDH_CYCL_MEAS_DATA::getCONS_CARBIDE(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::CONS_CARBIDE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setCONS_CARBIDE(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::CONS_CARBIDE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDH_CYCL_MEAS_DATA::getGAS_FLOW_N2(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::GAS_FLOW_N2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setGAS_FLOW_N2(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::GAS_FLOW_N2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDH_CYCL_MEAS_DATA::getGAS_PRESSURE_N2(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::GAS_PRESSURE_N2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setGAS_PRESSURE_N2(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::GAS_PRESSURE_N2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDH_CYCL_MEAS_DATA::getCONS_N2(long Row)
{
  return getDouble(CPDH_CYCL_MEAS_DATA::CONS_N2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setCONS_N2(double value)
{
  setDouble(CPDH_CYCL_MEAS_DATA::CONS_N2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDH_CYCL_MEAS_DATA::getLANCEPOS(long Row)
{
  return getLong(CPDH_CYCL_MEAS_DATA::LANCEPOS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDH_CYCL_MEAS_DATA::setLANCEPOS(long value)
{
  setLong(CPDH_CYCL_MEAS_DATA::LANCEPOS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDH_CYCL_MEAS_DATA::select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, const CDateTime& REVTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDH_CYCL_MEAS_DATA::HM_ID,HM_ID);
  addWhereClause(CPDH_CYCL_MEAS_DATA::TREATID,TREATID);
  addWhereClause(CPDH_CYCL_MEAS_DATA::PLANT,PLANT);
  addWhereClause(CPDH_CYCL_MEAS_DATA::REVTIME,REVTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



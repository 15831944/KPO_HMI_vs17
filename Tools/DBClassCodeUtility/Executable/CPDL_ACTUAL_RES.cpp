//## Copyright (C) 2015 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDL_ACTUAL_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELEC_ENERGY("ELEC_ENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::UPDATENO("UPDATENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::DURSINCEHEATANNOUNCEMENT("DURSINCEHEATANNOUNCEMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::CURELECPRACPHASE("CURELECPRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::CURELECSTEPNO("CURELECSTEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::STEELMASS("STEELMASS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::SLAGMASS("SLAGMASS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::TEMP("TEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::VOLTTAP("VOLTTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::IMPCURVE("IMPCURVE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::REMELECENERGY("REMELECENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::STIRRINTENSITY("STIRRINTENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::STIRRFLOW("STIRRFLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::CURPHASE("CURPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::STIRRGASTYPE("STIRRGASTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO1("ACTIVITYNAME_PRIO1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO2("ACTIVITYNAME_PRIO2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO3("ACTIVITYNAME_PRIO3");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::COMPAVAIL_MAT("COMPAVAIL_MAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::COMPAVAIL_STIRR("COMPAVAIL_STIRR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::COMPAVAIL_ELEC("COMPAVAIL_ELEC");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELECTRODEPULLREQ("ELECTRODEPULLREQ");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELECTRODELOCKREQ("ELECTRODELOCKREQ");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELEC_EGY_INIT_HEAT("ELEC_EGY_INIT_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELEC_EGY_MAIN_HEAT("ELEC_EGY_MAIN_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::ELEC_EGY_FINAL_HEAT("ELEC_EGY_FINAL_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::TEMP_INIT_HEAT("TEMP_INIT_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::TEMP_MAIN_HEAT("TEMP_MAIN_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDL_ACTUAL_RES::TEMP_FINAL_HEAT("TEMP_FINAL_HEAT");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDL_ACTUAL_RES::CPDL_ACTUAL_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("PDL_ACTUAL_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDL_ACTUAL_RES::CPDL_ACTUAL_RES(cCBS_Connection* Connection)
:CSMC_DBData("PDL_ACTUAL_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDL_ACTUAL_RES::CPDL_ACTUAL_RES()
:CSMC_DBData("PDL_ACTUAL_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDL_ACTUAL_RES::~CPDL_ACTUAL_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPDL_ACTUAL_RES::getHEATID(long Row)
{
  return getString(CPDL_ACTUAL_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setHEATID(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPDL_ACTUAL_RES::getTREATID(long Row)
{
  return getString(CPDL_ACTUAL_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setTREATID(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPDL_ACTUAL_RES::getPLANT(long Row)
{
  return getString(CPDL_ACTUAL_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setPLANT(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CPDL_ACTUAL_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDL_ACTUAL_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setREVTIME(const CDateTime& value)
{
 setString(CPDL_ACTUAL_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Electrical Energy
double CPDL_ACTUAL_RES::getELEC_ENERGY(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELEC_ENERGY(double value)
{
  setDouble(CPDL_ACTUAL_RES::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Number of updates in heat., First entry 1, Second    2, ...
long CPDL_ACTUAL_RES::getUPDATENO(long Row)
{
  return getLong(CPDL_ACTUAL_RES::UPDATENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setUPDATENO(long value)
{
  setLong(CPDL_ACTUAL_RES::UPDATENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since heat announcement
double CPDL_ACTUAL_RES::getDURSINCEHEATANNOUNCEMENT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::DURSINCEHEATANNOUNCEMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setDURSINCEHEATANNOUNCEMENT(double value)
{
  setDouble(CPDL_ACTUAL_RES::DURSINCEHEATANNOUNCEMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##LF Electric Pratice Phase
std::string CPDL_ACTUAL_RES::getCURELECPRACPHASE(long Row)
{
  return getString(CPDL_ACTUAL_RES::CURELECPRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCURELECPRACPHASE(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::CURELECPRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Current step in phase for electric
long CPDL_ACTUAL_RES::getCURELECSTEPNO(long Row)
{
  return getLong(CPDL_ACTUAL_RES::CURELECSTEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCURELECSTEPNO(long value)
{
  setLong(CPDL_ACTUAL_RES::CURELECSTEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getSTEELMASS(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::STEELMASS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setSTEELMASS(double value)
{
  setDouble(CPDL_ACTUAL_RES::STEELMASS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getSLAGMASS(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::SLAGMASS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setSLAGMASS(double value)
{
  setDouble(CPDL_ACTUAL_RES::SLAGMASS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getTEMP(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::TEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setTEMP(double value)
{
  setDouble(CPDL_ACTUAL_RES::TEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Transformer Voltage Tap
long CPDL_ACTUAL_RES::getVOLTTAP(long Row)
{
  return getLong(CPDL_ACTUAL_RES::VOLTTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setVOLTTAP(long value)
{
  setLong(CPDL_ACTUAL_RES::VOLTTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Impedance curve
long CPDL_ACTUAL_RES::getIMPCURVE(long Row)
{
  return getLong(CPDL_ACTUAL_RES::IMPCURVE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setIMPCURVE(long value)
{
  setLong(CPDL_ACTUAL_RES::IMPCURVE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Remaining Electrical Energy
double CPDL_ACTUAL_RES::getREMELECENERGY(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::REMELECENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setREMELECENERGY(double value)
{
  setDouble(CPDL_ACTUAL_RES::REMELECENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value for Stirring Intensity
long CPDL_ACTUAL_RES::getSTIRRINTENSITY(long Row)
{
  return getLong(CPDL_ACTUAL_RES::STIRRINTENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setSTIRRINTENSITY(long value)
{
  setLong(CPDL_ACTUAL_RES::STIRRINTENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Stirring flow
double CPDL_ACTUAL_RES::getSTIRRFLOW(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::STIRRFLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setSTIRRFLOW(double value)
{
  setDouble(CPDL_ACTUAL_RES::STIRRFLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Actual process phase
std::string CPDL_ACTUAL_RES::getCURPHASE(long Row)
{
  return getString(CPDL_ACTUAL_RES::CURPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCURPHASE(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::CURPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Values are, N2  or, AR
std::string CPDL_ACTUAL_RES::getSTIRRGASTYPE(long Row)
{
  return getString(CPDL_ACTUAL_RES::STIRRGASTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setSTIRRGASTYPE(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::STIRRGASTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of Activity.
std::string CPDL_ACTUAL_RES::getACTIVITYNAME_PRIO1(long Row)
{
  return getString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setACTIVITYNAME_PRIO1(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of Activity.
std::string CPDL_ACTUAL_RES::getACTIVITYNAME_PRIO2(long Row)
{
  return getString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setACTIVITYNAME_PRIO2(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of Activity.
std::string CPDL_ACTUAL_RES::getACTIVITYNAME_PRIO3(long Row)
{
  return getString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO3, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setACTIVITYNAME_PRIO3(const std::string& value)
{
  setString(CPDL_ACTUAL_RES::ACTIVITYNAME_PRIO3, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Computer Mode Availibility Material
long CPDL_ACTUAL_RES::getCOMPAVAIL_MAT(long Row)
{
  return getLong(CPDL_ACTUAL_RES::COMPAVAIL_MAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCOMPAVAIL_MAT(long value)
{
  setLong(CPDL_ACTUAL_RES::COMPAVAIL_MAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Computer Mode Availibility Model
long CPDL_ACTUAL_RES::getCOMPAVAIL_STIRR(long Row)
{
  return getLong(CPDL_ACTUAL_RES::COMPAVAIL_STIRR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCOMPAVAIL_STIRR(long value)
{
  setLong(CPDL_ACTUAL_RES::COMPAVAIL_STIRR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Computer Mode Availibility Electric
long CPDL_ACTUAL_RES::getCOMPAVAIL_ELEC(long Row)
{
  return getLong(CPDL_ACTUAL_RES::COMPAVAIL_ELEC, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setCOMPAVAIL_ELEC(long value)
{
  setLong(CPDL_ACTUAL_RES::COMPAVAIL_ELEC, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Electrode Pull request
long CPDL_ACTUAL_RES::getELECTRODEPULLREQ(long Row)
{
  return getLong(CPDL_ACTUAL_RES::ELECTRODEPULLREQ, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELECTRODEPULLREQ(long value)
{
  setLong(CPDL_ACTUAL_RES::ELECTRODEPULLREQ, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Electrode lock request
long CPDL_ACTUAL_RES::getELECTRODELOCKREQ(long Row)
{
  return getLong(CPDL_ACTUAL_RES::ELECTRODELOCKREQ, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELECTRODELOCKREQ(long value)
{
  setLong(CPDL_ACTUAL_RES::ELECTRODELOCKREQ, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getELEC_EGY_INIT_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::ELEC_EGY_INIT_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELEC_EGY_INIT_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::ELEC_EGY_INIT_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getELEC_EGY_MAIN_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::ELEC_EGY_MAIN_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELEC_EGY_MAIN_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::ELEC_EGY_MAIN_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getELEC_EGY_FINAL_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::ELEC_EGY_FINAL_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setELEC_EGY_FINAL_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::ELEC_EGY_FINAL_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getTEMP_INIT_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::TEMP_INIT_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setTEMP_INIT_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::TEMP_INIT_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getTEMP_MAIN_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::TEMP_MAIN_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setTEMP_MAIN_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::TEMP_MAIN_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDL_ACTUAL_RES::getTEMP_FINAL_HEAT(long Row)
{
  return getDouble(CPDL_ACTUAL_RES::TEMP_FINAL_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDL_ACTUAL_RES::setTEMP_FINAL_HEAT(double value)
{
  setDouble(CPDL_ACTUAL_RES::TEMP_FINAL_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDL_ACTUAL_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& REVTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDL_ACTUAL_RES::HEATID,HEATID);
  addWhereClause(CPDL_ACTUAL_RES::TREATID,TREATID);
  addWhereClause(CPDL_ACTUAL_RES::PLANT,PLANT);
  addWhereClause(CPDL_ACTUAL_RES::REVTIME,REVTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CIntfData.h"
#include "DEF_GT_PURP.h"
#include "CGCE_INJECTION.h"
#include "CGCE_INJECTION_TYPE.h"
#include "CPDE_PHASE_INJECT_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::PROCPHASE("PROCPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::PROCPHASENO("PROCPHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::DEVICENAME("DEVICENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::BASWEIGHT("BASWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::SPECEGY("SPECEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::STEPDUR("STEPDUR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::ELEC_ENERGY("ELEC_ENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::FLOWRATE_1("FLOWRATE_1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::FLOWRATE_2("FLOWRATE_2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::GASAMOUNT_1("GASAMOUNT_1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::GASAMOUNT_2("GASAMOUNT_2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::MATWEIGHT_1("MATWEIGHT_1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::MATWEIGHT_2("MATWEIGHT_2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::MAT_CODE_1("MAT_CODE_1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::MAT_CODE_2("MAT_CODE_2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_INJECT_RES::INJTYPE("INJTYPE");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_INJECT_RES::CPDE_PHASE_INJECT_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("PDE_PHASE_INJECT_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_INJECT_RES::CPDE_PHASE_INJECT_RES(cCBS_Connection* Connection)
:CSMC_DBData("PDE_PHASE_INJECT_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_INJECT_RES::CPDE_PHASE_INJECT_RES()
:CSMC_DBData("PDE_PHASE_INJECT_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_INJECT_RES::~CPDE_PHASE_INJECT_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getHEATID(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setHEATID(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getTREATID(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setTREATID(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getPLANT(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setPLANT(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getPROCPHASE(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::PROCPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setPROCPHASE(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::PROCPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_INJECT_RES::getPROCPHASENO(long Row)
{
  return getLong(CPDE_PHASE_INJECT_RES::PROCPHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setPROCPHASENO(long value)
{
  setLong(CPDE_PHASE_INJECT_RES::PROCPHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_INJECT_RES::getSTEPNO(long Row)
{
  return getLong(CPDE_PHASE_INJECT_RES::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setSTEPNO(long value)
{
  setLong(CPDE_PHASE_INJECT_RES::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getDEVICENAME(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::DEVICENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setDEVICENAME(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::DEVICENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getBASWEIGHT(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::BASWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setBASWEIGHT(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::BASWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getSPECEGY(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::SPECEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setSPECEGY(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::SPECEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getSTARTTIME(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setSTARTTIME(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getSTEPDUR(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::STEPDUR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setSTEPDUR(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::STEPDUR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getELEC_ENERGY(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setELEC_ENERGY(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CPDE_PHASE_INJECT_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDE_PHASE_INJECT_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setREVTIME(const CDateTime& value)
{
 setString(CPDE_PHASE_INJECT_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getFLOWRATE_1(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::FLOWRATE_1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setFLOWRATE_1(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::FLOWRATE_1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getFLOWRATE_2(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::FLOWRATE_2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setFLOWRATE_2(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::FLOWRATE_2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getGASAMOUNT_1(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::GASAMOUNT_1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setGASAMOUNT_1(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::GASAMOUNT_1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getGASAMOUNT_2(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::GASAMOUNT_2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setGASAMOUNT_2(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::GASAMOUNT_2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getMATWEIGHT_1(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::MATWEIGHT_1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setMATWEIGHT_1(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::MATWEIGHT_1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_INJECT_RES::getMATWEIGHT_2(long Row)
{
  return getDouble(CPDE_PHASE_INJECT_RES::MATWEIGHT_2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setMATWEIGHT_2(double value)
{
  setDouble(CPDE_PHASE_INJECT_RES::MATWEIGHT_2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getMAT_CODE_1(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::MAT_CODE_1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setMAT_CODE_1(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::MAT_CODE_1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getMAT_CODE_2(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::MAT_CODE_2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setMAT_CODE_2(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::MAT_CODE_2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_INJECT_RES::getINJTYPE(long Row)
{
  return getString(CPDE_PHASE_INJECT_RES::INJTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_INJECT_RES::setINJTYPE(const std::string& value)
{
  setString(CPDE_PHASE_INJECT_RES::INJTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDE_PHASE_INJECT_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long PROCPHASENO, long STEPNO, const std::string& DEVICENAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDE_PHASE_INJECT_RES::HEATID,HEATID);
  addWhereClause(CPDE_PHASE_INJECT_RES::TREATID,TREATID);
  addWhereClause(CPDE_PHASE_INJECT_RES::PLANT,PLANT);
  addWhereClause(CPDE_PHASE_INJECT_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CPDE_PHASE_INJECT_RES::PROCPHASENO,PROCPHASENO);
  addWhereClause(CPDE_PHASE_INJECT_RES::STEPNO,STEPNO);
  addWhereClause(CPDE_PHASE_INJECT_RES::DEVICENAME,DEVICENAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPDE_PHASE_INJECT_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CPDE_PHASE_INJECT_RES::HEATID,HEATID);
	addWhereClause(CPDE_PHASE_INJECT_RES::TREATID,TREATID);
	addWhereClause(CPDE_PHASE_INJECT_RES::PLANT,PLANT);
   
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

bool CPDE_PHASE_INJECT_RES::writeResults(const std::string & HeatID, const std::string & TreatID,const std::string & PLANT,  double DurSinceHeatAnnounce, const seqEAFInjectLance &EAFInjectLance)
{
  bool            RetValue   = false;
  sEAFInjectLance InjectLance;
  double          StartTime  = 0;

  //SANKAR : 05.03.2010
  try
  {
    CDateTime Now;

    RetValue = !exists(HeatID, TreatID, PLANT);
    //some data found -> delete them
    if (!RetValue && CIntfData::getLength(EAFInjectLance) > 0 )
    {
      RetValue = deleteRows();
      if (!RetValue)
        setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
    }


    for (int i = 0 ; i < CIntfData::getLength(EAFInjectLance) ; i++)
    {
      CIntfData::getAt(InjectLance,&EAFInjectLance,i);

      seqInjectLanceData SeqInjectLanceData = InjectLance.InjectFlow;
      for (int j = 0 ; j < CIntfData::getLength(SeqInjectLanceData) ; j++)
      {
        sInjectLanceData   InjectLanceData;
        CIntfData::getAt(InjectLanceData, SeqInjectLanceData, j);
      
        setMAT_CODE_1(string(InjectLanceData.MatCode));
        setFLOWRATE_1(InjectLanceData.Value);
        setMATWEIGHT_1(InjectLanceData.Value * InjectLance.DurStep);

        std::string Phase = InjectLance.Phase;
        std::string Code  = InjectLanceData.MatCode;
      
        setHEATID(HeatID);
        setTREATID(TreatID);
        setPLANT(PLANT);
        setPROCPHASENO(InjectLance.PhaseNo);
        setPROCPHASE(Phase);      
        setSTEPNO(InjectLance.Step);
        setBASWEIGHT(InjectLance.BaseMass);
        setSPECEGY(InjectLance.SpecEgy); 
        setSTARTTIME(InjectLance.DurUntilStartOfStep); //DurSinceHeatAnnounce
        setSTEPDUR(InjectLance.DurStep);
        setELEC_ENERGY(InjectLance.Egy);
        setREVTIME(Now);
        setDEVICENAME(string(InjectLanceData.Device)); 
        setINJTYPE(std::string(InjectLanceData.InjectionType));

        if (select(HeatID, TreatID,PLANT, Phase,InjectLance.PhaseNo , InjectLance.Step, string(InjectLanceData.Device)))
          RetValue = update();
        else
          RetValue = insert();

        if (!RetValue)
          break;
      }
    }

    if (RetValue)
    {
      commit();
    }
    else
    {
      rollback();
    }
  }
  catch(...)
  {
    RetValue = false;
    rollback();
  }
  return RetValue;
}



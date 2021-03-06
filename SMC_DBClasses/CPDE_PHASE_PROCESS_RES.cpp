//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 



//#include "iSMC_DataProvider_s.hh"
#include "CIntfData.h"
#include "CPDE_PHASE_PROCESS_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::PROCPHASE("PROCPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::PROCPHASENO("PROCPHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::BASWEIGHT("BASWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::SPECEGY("SPECEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::STEPDUR("STEPDUR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::ELEC_ENERGY("ELEC_ENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::REACTORTAP("REACTORTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::VOLTTAP("VOLTTAP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::IMPCURVE("IMPCURVE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_PHASE_PROCESS_RES::O2_FLOW("O2_FLOW");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_PROCESS_RES::CPDE_PHASE_PROCESS_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("PDE_PHASE_PROCESS_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_PROCESS_RES::CPDE_PHASE_PROCESS_RES(cCBS_Connection* Connection)
:CSMC_DBData("PDE_PHASE_PROCESS_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_PROCESS_RES::CPDE_PHASE_PROCESS_RES()
:CSMC_DBData("PDE_PHASE_PROCESS_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_PHASE_PROCESS_RES::~CPDE_PHASE_PROCESS_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_PROCESS_RES::getHEATID(long Row)
{
  return getString(CPDE_PHASE_PROCESS_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setHEATID(const std::string& value)
{
  setString(CPDE_PHASE_PROCESS_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_PROCESS_RES::getTREATID(long Row)
{
  return getString(CPDE_PHASE_PROCESS_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setTREATID(const std::string& value)
{
  setString(CPDE_PHASE_PROCESS_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_PROCESS_RES::getPLANT(long Row)
{
  return getString(CPDE_PHASE_PROCESS_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setPLANT(const std::string& value)
{
  setString(CPDE_PHASE_PROCESS_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_PHASE_PROCESS_RES::getPROCPHASE(long Row)
{
  return getString(CPDE_PHASE_PROCESS_RES::PROCPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setPROCPHASE(const std::string& value)
{
  setString(CPDE_PHASE_PROCESS_RES::PROCPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_PROCESS_RES::getPROCPHASENO(long Row)
{
  return getLong(CPDE_PHASE_PROCESS_RES::PROCPHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setPROCPHASENO(long value)
{
  setLong(CPDE_PHASE_PROCESS_RES::PROCPHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_PROCESS_RES::getSTEPNO(long Row)
{
  return getLong(CPDE_PHASE_PROCESS_RES::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setSTEPNO(long value)
{
  setLong(CPDE_PHASE_PROCESS_RES::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getBASWEIGHT(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::BASWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setBASWEIGHT(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::BASWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getSPECEGY(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::SPECEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setSPECEGY(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::SPECEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getSTARTTIME(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setSTARTTIME(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getSTEPDUR(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::STEPDUR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setSTEPDUR(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::STEPDUR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getELEC_ENERGY(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::ELEC_ENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setELEC_ENERGY(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::ELEC_ENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CPDE_PHASE_PROCESS_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDE_PHASE_PROCESS_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setREVTIME(const CDateTime& value)
{
 setString(CPDE_PHASE_PROCESS_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_PROCESS_RES::getREACTORTAP(long Row)
{
  return getLong(CPDE_PHASE_PROCESS_RES::REACTORTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setREACTORTAP(long value)
{
  setLong(CPDE_PHASE_PROCESS_RES::REACTORTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_PROCESS_RES::getVOLTTAP(long Row)
{
  return getLong(CPDE_PHASE_PROCESS_RES::VOLTTAP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setVOLTTAP(long value)
{
  setLong(CPDE_PHASE_PROCESS_RES::VOLTTAP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPDE_PHASE_PROCESS_RES::getIMPCURVE(long Row)
{
  return getLong(CPDE_PHASE_PROCESS_RES::IMPCURVE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setIMPCURVE(long value)
{
  setLong(CPDE_PHASE_PROCESS_RES::IMPCURVE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_PHASE_PROCESS_RES::getO2_FLOW(long Row)
{
  return getDouble(CPDE_PHASE_PROCESS_RES::O2_FLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_PHASE_PROCESS_RES::setO2_FLOW(double value)
{
  setDouble(CPDE_PHASE_PROCESS_RES::O2_FLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDE_PHASE_PROCESS_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long PROCPHASENO, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDE_PHASE_PROCESS_RES::HEATID,HEATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::TREATID,TREATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PLANT,PLANT);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PROCPHASENO,PROCPHASENO);
  addWhereClause(CPDE_PHASE_PROCESS_RES::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPDE_PHASE_PROCESS_RES::selectMaxValuesByGroup(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select PROCPHASE, PROCPHASENO, MAX(STEPDUR) as STEPDUR, MAX(ELECENERGY) as ELECENERGY, MAX(O2_FLOW) as O2_FLOW  from " + m_TableName;

  addWhereClause(CPDE_PHASE_PROCESS_RES::HEATID,HEATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::TREATID,TREATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PLANT,PLANT);

  m_Statement += getWhereStatement() + " group by PROCPHASE,PROCPHASENO;";

  return CSMC_DBData::select();
}

bool CPDE_PHASE_PROCESS_RES::selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDE_PHASE_PROCESS_RES::HEATID,HEATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::TREATID,TREATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PLANT,PLANT);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CPDE_PHASE_PROCESS_RES::STEPNO,STEPNO);

  m_Statement += getWhereStatement() + " Order by HEATID,TREATID,PLANT,PROCPHASE,STEPNO;";

  return CSMC_DBData::select();
}

bool CPDE_PHASE_PROCESS_RES::selectSumValuesByGroup(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  m_Statement = "Select PROCPHASE,PROCPHASENO,SUM(STEPDUR) as STEPDUR, SUM(ELECENERGY) as ELECENERGY, SUM(O2_FLOW) as O2_FLOW  from " + m_TableName;

  addWhereClause(CPDE_PHASE_PROCESS_RES::HEATID,HEATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::TREATID,TREATID);
  addWhereClause(CPDE_PHASE_PROCESS_RES::PLANT,PLANT);

  m_Statement += getWhereStatement() + " group by PROCPHASE,PROCPHASENO;";

  return CSMC_DBData::select();
}

bool CPDE_PHASE_PROCESS_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CPDE_PHASE_PROCESS_RES::HEATID,HEATID);
	addWhereClause(CPDE_PHASE_PROCESS_RES::TREATID,TREATID);
	addWhereClause(CPDE_PHASE_PROCESS_RES::PLANT,PLANT);
   
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

bool CPDE_PHASE_PROCESS_RES::writeResults(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, double DurSinceHeatAnnounce, const seqEAFProcessPredRes &EAFProcessPredRes)
{
  bool            RetValue   = false;
  long            PredLength = 0;
  long            i;
  CDateTime       now;
  sEAFProcessPredRes ProcessPredRes;
  string          Phase;
  double dO2Flow;

  //SANKAR : 05.03.2010
  try
  {
    long PredLength = CIntfData::getLength(EAFProcessPredRes);

    RetValue = !exists(HeatID, TreatID, Plant);
    //some data found -> delete them
    if (!RetValue && PredLength > 0 )
    {
      RetValue = deleteRows();
      if (!RetValue)
        setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
    }

    for (i = 0 ; i < PredLength ; ++i)
    {
      CIntfData::getAt(ProcessPredRes,&EAFProcessPredRes,i);

      Phase = ProcessPredRes.Phase;

      dO2Flow = ProcessPredRes.O2Flow;

      RetValue = select(HeatID, TreatID, Plant, Phase,ProcessPredRes.PhaseNo, ProcessPredRes.Step);

      setHEATID(HeatID);
      setTREATID(TreatID);
      setPLANT(Plant);
      setREVTIME(now);
      setPROCPHASE(Phase);
      setSTEPNO(ProcessPredRes.Step);
      setPROCPHASENO(ProcessPredRes.PhaseNo);
      setBASWEIGHT(ProcessPredRes.BaseMass);

      if (ProcessPredRes.VoltTap > 0)
        setVOLTTAP(ProcessPredRes.VoltTap);

      if (ProcessPredRes.ImpCurve > 0)
        setIMPCURVE(ProcessPredRes.ImpCurve);

      if (ProcessPredRes.ReactorTap > 0)
        setREACTORTAP(ProcessPredRes.ReactorTap);


      setSPECEGY(ProcessPredRes.SpecEgy);
      setSTARTTIME(ProcessPredRes.DurUntilStartOfStep); //DurSinceHeatAnnounce
      setSTEPDUR(ProcessPredRes.DurStep);
      setELEC_ENERGY(ProcessPredRes.ElecEgy);

      if(dO2Flow > 0)
        setO2_FLOW(dO2Flow);


      if (RetValue)
        RetValue = update();
      else
        RetValue = insert();

      if (!RetValue) break;
    }

    // commit only if own values  are successfully written
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



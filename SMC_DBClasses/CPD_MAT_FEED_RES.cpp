//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "DEF_GC_PLANT_DEF.h"
#include "CIntfData.h"
#include "CDataConversion.h"
#include "CSMC_EventLogFrameController.h"
#include "CGC_Plantgroup_Container.h"
#include "CGT_PARAM.h"
#include "CPD_MAT_FEED_RES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::PROCPHASE("PROCPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::PROCPHASENO("PROCPHASENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::STEPNO("STEPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::STEPDUR("STEPDUR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::ELECENERGY("ELECENERGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::MATWEIGHT("MATWEIGHT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::FEEDINGRATE("FEEDINGRATE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_MAT_FEED_RES::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_MAT_FEED_RES::CPD_MAT_FEED_RES(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_MAT_FEED_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_MAT_FEED_RES::CPD_MAT_FEED_RES(cCBS_Connection* Connection)
:CSMC_DBData("PD_MAT_FEED_RES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_MAT_FEED_RES::CPD_MAT_FEED_RES()
:CSMC_DBData("PD_MAT_FEED_RES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_MAT_FEED_RES::~CPD_MAT_FEED_RES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_MAT_FEED_RES::getHEATID(long Row)
{
  return getString(CPD_MAT_FEED_RES::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setHEATID(const std::string& value)
{
  setString(CPD_MAT_FEED_RES::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_MAT_FEED_RES::getTREATID(long Row)
{
  return getString(CPD_MAT_FEED_RES::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setTREATID(const std::string& value)
{
  setString(CPD_MAT_FEED_RES::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_MAT_FEED_RES::getPLANT(long Row)
{
  return getString(CPD_MAT_FEED_RES::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setPLANT(const std::string& value)
{
  setString(CPD_MAT_FEED_RES::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Phases are e.g. Basket, LiqAdd for EAF
std::string CPD_MAT_FEED_RES::getPROCPHASE(long Row)
{
  return getString(CPD_MAT_FEED_RES::PROCPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setPROCPHASE(const std::string& value)
{
  setString(CPD_MAT_FEED_RES::PROCPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##If process phases are countable we use ths as the counter. For EAF e.g, MeltDownBsk: 1
long CPD_MAT_FEED_RES::getPROCPHASENO(long Row)
{
  return getLong(CPD_MAT_FEED_RES::PROCPHASENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setPROCPHASENO(long value)
{
  setLong(CPD_MAT_FEED_RES::PROCPHASENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code
std::string CPD_MAT_FEED_RES::getMAT_CODE(long Row)
{
  return getString(CPD_MAT_FEED_RES::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setMAT_CODE(const std::string& value)
{
  setString(CPD_MAT_FEED_RES::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Energy step
long CPD_MAT_FEED_RES::getSTEPNO(long Row)
{
  return getLong(CPD_MAT_FEED_RES::STEPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setSTEPNO(long value)
{
  setLong(CPD_MAT_FEED_RES::STEPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Relative start time since heat announcement
double CPD_MAT_FEED_RES::getSTARTTIME(long Row)
{
  return getDouble(CPD_MAT_FEED_RES::STARTTIME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setSTARTTIME(double value)
{
  setDouble(CPD_MAT_FEED_RES::STARTTIME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Calculated duration of step in minutes
double CPD_MAT_FEED_RES::getSTEPDUR(long Row)
{
  return getDouble(CPD_MAT_FEED_RES::STEPDUR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setSTEPDUR(double value)
{
  setDouble(CPD_MAT_FEED_RES::STEPDUR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Total electric energy consumption in case of electric heating, kWh
double CPD_MAT_FEED_RES::getELECENERGY(long Row)
{
  return getDouble(CPD_MAT_FEED_RES::ELECENERGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setELECENERGY(double value)
{
  setDouble(CPD_MAT_FEED_RES::ELECENERGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Actual weight
double CPD_MAT_FEED_RES::getMATWEIGHT(long Row)
{
  return getDouble(CPD_MAT_FEED_RES::MATWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setMATWEIGHT(double value)
{
  setDouble(CPD_MAT_FEED_RES::MATWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Absolute feeding rate in kg/min
double CPD_MAT_FEED_RES::getFEEDINGRATE(long Row)
{
  return getDouble(CPD_MAT_FEED_RES::FEEDINGRATE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setFEEDINGRATE(double value)
{
  setDouble(CPD_MAT_FEED_RES::FEEDINGRATE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CPD_MAT_FEED_RES::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_MAT_FEED_RES::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_MAT_FEED_RES::setREVTIME(const CDateTime& value)
{
 setString(CPD_MAT_FEED_RES::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_MAT_FEED_RES::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long PROCPHASENO, const std::string& MAT_CODE, long STEPNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_MAT_FEED_RES::HEATID,HEATID);
  addWhereClause(CPD_MAT_FEED_RES::TREATID,TREATID);
  addWhereClause(CPD_MAT_FEED_RES::PLANT,PLANT);
  addWhereClause(CPD_MAT_FEED_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CPD_MAT_FEED_RES::PROCPHASENO,PROCPHASENO);
  addWhereClause(CPD_MAT_FEED_RES::MAT_CODE,MAT_CODE);
  addWhereClause(CPD_MAT_FEED_RES::STEPNO,STEPNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_MAT_FEED_RES::selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& PROCPHASE, long PROCPHASENO, const std::string& MAT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_MAT_FEED_RES::HEATID,HEATID);
  addWhereClause(CPD_MAT_FEED_RES::TREATID,TREATID);
  addWhereClause(CPD_MAT_FEED_RES::PLANT,PLANT);
  addWhereClause(CPD_MAT_FEED_RES::PROCPHASE,PROCPHASE);
  addWhereClause(CPD_MAT_FEED_RES::PROCPHASENO,PROCPHASENO);
  addWhereClause(CPD_MAT_FEED_RES::MAT_CODE,MAT_CODE);

  m_Statement += getWhereStatement() + " Order by HEATID,TREATID,PLANT,PROCPHASE,PROCPHASENO,MAT_CODE;";

  return CSMC_DBData::select();
}

bool CPD_MAT_FEED_RES::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CPD_MAT_FEED_RES::HEATID,HEATID);
	addWhereClause(CPD_MAT_FEED_RES::TREATID,TREATID);
	addWhereClause(CPD_MAT_FEED_RES::PLANT,PLANT);
   
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

bool CPD_MAT_FEED_RES::writeResults(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, const seqEAFMatFeedPredRes &SeqEAFMatFeedPredRes)
{
  bool            RetValue   = false;
  CDateTime       now;
  
  try
  {
    long PredLength = CIntfData::getLength(SeqEAFMatFeedPredRes);

    RetValue = !exists(HeatID, TreatID, Plant);
    //some data found -> delete them
    if (!RetValue &&  PredLength > 0 )
    {
      RetValue = deleteRows();
      if (!RetValue)
        setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
    }

    // we are iterating and will not write data without material code 
    for (long i = 0; i < CIntfData::getLength(SeqEAFMatFeedPredRes); ++i)
    {
      sEAFMatFeedPredRes EAFMatFeedPredRes;
      CIntfData::getAt(EAFMatFeedPredRes,SeqEAFMatFeedPredRes,i);

      std::string Phase       = EAFMatFeedPredRes.PhaseName;
      seqBatch seqMatFeedData = EAFMatFeedPredRes.MatFeedData;

      for(long p = 0; p < CIntfData::getLength(seqMatFeedData); ++p)
      {
        sBatch Batch;
        CIntfData::getAt(Batch,seqMatFeedData,p);

        std::string MatCode = Batch.MatCode;

        if( MatCode == DEF::Inv_String || MatCode.empty() ) continue;

        double DurStep      = CDataConversion::SetInvalidToDefault(EAFMatFeedPredRes.DurStep  ,0.);
        double MatFeedSpeed = CDataConversion::SetInvalidToDefault(Batch.MatFeedSpeed         ,0.);
        double MatWeight    = DurStep * MatFeedSpeed;

        RetValue = select(HeatID, TreatID, Plant, Phase,EAFMatFeedPredRes.BasketNo, std::string(Batch.MatCode) ,EAFMatFeedPredRes.Step);

        setHEATID(HeatID);
        setTREATID(TreatID);
        setPLANT(Plant);
        setREVTIME(now);
        setPROCPHASE(Phase);
        setSTEPNO(EAFMatFeedPredRes.Step);
        setPROCPHASENO(EAFMatFeedPredRes.BasketNo);
        setMAT_CODE(MatCode);
        setFEEDINGRATE(MatFeedSpeed);
        setMATWEIGHT(MatWeight);
        
        setSTARTTIME(EAFMatFeedPredRes.DurUntilStartOfStep); //DurSinceHeatAnnounce
        setSTEPDUR(EAFMatFeedPredRes.DurStep);
        setELECENERGY(EAFMatFeedPredRes.Egy);

        if (RetValue)
        {
          RetValue = update();
        }
        else
        {
          RetValue = insert();
        }

        if (!RetValue) 
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"","PD_MAT_FEED_RES","");

          break;
        }
      }

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



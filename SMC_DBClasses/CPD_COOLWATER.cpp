//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 



//#include "iSMC_DataDefinitions_s.hh"
#include "CIntfData.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "CPD_COOLWATER.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::COOL_EQUIP("COOL_EQUIP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::COOL_LOOP_NO("COOL_LOOP_NO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::O2_MOMENT("O2_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::N2_MOMENT("N2_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::AR_MOMENT("AR_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::ELEC_EGYTOT("ELEC_EGYTOT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::CW_TEMP_IN("CW_TEMP_IN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::CW_TEMP_OUT("CW_TEMP_OUT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::CW_FLOW("CW_FLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::DURSINCEHEATANNOUNCEMENT("DURSINCEHEATANNOUNCEMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COOLWATER::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COOLWATER::CPD_COOLWATER(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_COOLWATER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COOLWATER::CPD_COOLWATER(cCBS_Connection* Connection)
:CSMC_DBData("PD_COOLWATER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COOLWATER::CPD_COOLWATER()
:CSMC_DBData("PD_COOLWATER")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COOLWATER::~CPD_COOLWATER()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_COOLWATER::getHEATID(long Row)
{
  return getString(CPD_COOLWATER::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setHEATID(const std::string& value)
{
  setString(CPD_COOLWATER::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_COOLWATER::getTREATID(long Row)
{
  return getString(CPD_COOLWATER::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setTREATID(const std::string& value)
{
  setString(CPD_COOLWATER::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_COOLWATER::getPLANT(long Row)
{
  return getString(CPD_COOLWATER::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setPLANT(const std::string& value)
{
  setString(CPD_COOLWATER::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Cool water equipment
std::string CPD_COOLWATER::getCOOL_EQUIP(long Row)
{
  return getString(CPD_COOLWATER::COOL_EQUIP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setCOOL_EQUIP(const std::string& value)
{
  setString(CPD_COOLWATER::COOL_EQUIP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Cooling loop number
long CPD_COOLWATER::getCOOL_LOOP_NO(long Row)
{
  return getLong(CPD_COOLWATER::COOL_LOOP_NO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setCOOL_LOOP_NO(long value)
{
  setLong(CPD_COOLWATER::COOL_LOOP_NO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CPD_COOLWATER::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_COOLWATER::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setREVTIME(const CDateTime& value)
{
 setString(CPD_COOLWATER::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Metallurgical Nm3 since start of heat
double CPD_COOLWATER::getO2_MOMENT(long Row)
{
  return getDouble(CPD_COOLWATER::O2_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setO2_MOMENT(double value)
{
  setDouble(CPD_COOLWATER::O2_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Metallurgical Nm3 since start of heat
double CPD_COOLWATER::getN2_MOMENT(long Row)
{
  return getDouble(CPD_COOLWATER::N2_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setN2_MOMENT(double value)
{
  setDouble(CPD_COOLWATER::N2_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Argon consumption
double CPD_COOLWATER::getAR_MOMENT(long Row)
{
  return getDouble(CPD_COOLWATER::AR_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setAR_MOMENT(double value)
{
  setDouble(CPD_COOLWATER::AR_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Total electric energy consumption in case of electric heating, kWh
double CPD_COOLWATER::getELEC_EGYTOT(long Row)
{
  return getDouble(CPD_COOLWATER::ELEC_EGYTOT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setELEC_EGYTOT(double value)
{
  setDouble(CPD_COOLWATER::ELEC_EGYTOT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Cool water inlet temperature
double CPD_COOLWATER::getCW_TEMP_IN(long Row)
{
  return getDouble(CPD_COOLWATER::CW_TEMP_IN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setCW_TEMP_IN(double value)
{
  setDouble(CPD_COOLWATER::CW_TEMP_IN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Cool water outlet temperature
double CPD_COOLWATER::getCW_TEMP_OUT(long Row)
{
  return getDouble(CPD_COOLWATER::CW_TEMP_OUT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setCW_TEMP_OUT(double value)
{
  setDouble(CPD_COOLWATER::CW_TEMP_OUT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Cool water flow
double CPD_COOLWATER::getCW_FLOW(long Row)
{
  return getDouble(CPD_COOLWATER::CW_FLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setCW_FLOW(double value)
{
  setDouble(CPD_COOLWATER::CW_FLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since heat announcement
double CPD_COOLWATER::getDURSINCEHEATANNOUNCEMENT(long Row)
{
  return getDouble(CPD_COOLWATER::DURSINCEHEATANNOUNCEMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setDURSINCEHEATANNOUNCEMENT(double value)
{
  setDouble(CPD_COOLWATER::DURSINCEHEATANNOUNCEMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since start of heat
double CPD_COOLWATER::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CPD_COOLWATER::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COOLWATER::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CPD_COOLWATER::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_COOLWATER::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& COOL_EQUIP, long COOL_LOOP_NO, const CDateTime& REVTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_COOLWATER::HEATID,HEATID);
  addWhereClause(CPD_COOLWATER::TREATID,TREATID);
  addWhereClause(CPD_COOLWATER::PLANT,PLANT);
  addWhereClause(CPD_COOLWATER::COOL_EQUIP,COOL_EQUIP);
  addWhereClause(CPD_COOLWATER::COOL_LOOP_NO,COOL_LOOP_NO);
  addWhereClause(CPD_COOLWATER::REVTIME,REVTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_COOLWATER::selectSetofData(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select * from " + m_TableName;
	
	addWhereClause(CPD_COOLWATER::HEATID,HEATID);
	addWhereClause(CPD_COOLWATER::TREATID,TREATID);
	addWhereClause(CPD_COOLWATER::PLANT,PLANT);	

	m_Statement += getWhereStatement() + ";";

	return CSMC_DBData::select();
}

bool CPD_COOLWATER::writeData(const std::string& HeatID, const std::string& TreatID, const std::string& Plant,
                                 double durSinceA, double durSinceH, double ElecCons, const seqStirringData& StirringAmount, 
                                 seqCoolWaterData& pMeasCoolWaterData)
{
  bool RetValue = false;

  double AR_Moment = 0;
  double N2_Moment = 0;
  long SeqLength = 0;
  std::string Device, GasType;

  CDateTime Now;
  sStirringData SStirringData;
  sGasData GasData;

  long seqLength = CIntfData::getLength(pMeasCoolWaterData);
  if (0 == seqLength)
  {
    log("INFO: CoolingWaterData sequence is empty!",2);
    return RetValue;
  }

  for (long j = 0; j < seqLength; ++j)
  {
    // read all CoolWaterDevices
    sCoolWaterDevice CoolWaterDevice;
    CIntfData::getAt(CoolWaterDevice, pMeasCoolWaterData, j);

    // read CoolWaterData from CoolWaterDevice
    sCoolWater CoolWater = CoolWaterDevice.CoolWaterData;

    // if car is out of Operating Position temperatures and the flow are set to 0.0 by DM_LF. Check only the flow.
    if (CoolWater.WaterFlow != 0.0)
    {
      setPLANT(Plant);
      setHEATID(HeatID);
      setTREATID(TreatID);
      setDURSINCEHEATANNOUNCEMENT(durSinceA);
      setDURSINCESTARTOFHEAT(durSinceH);
      setREVTIME(Now);
      setCOOL_EQUIP(std::string(CoolWaterDevice.CoolWaterDevice));
      setCOOL_LOOP_NO(CoolWaterDevice.CoolWaterDeviceNo);
      setCW_FLOW(CoolWater.WaterFlow);
      setCW_TEMP_IN(CoolWater.InletTemp);
      setCW_TEMP_OUT(CoolWater.OutletTemp);
      setELEC_EGYTOT(ElecCons);

      SeqLength = CIntfData::getLength(StirringAmount);
      for (long k = 0; k < SeqLength; ++k)
      {
        CIntfData::getAt(SStirringData, StirringAmount, k);
        Device = SStirringData.Device;

        long GasDataLength = CIntfData::getLength(SStirringData.GasData);
        for (long x = 0; x < GasDataLength; ++x)
        {
          CIntfData::getAt(GasData, SStirringData.GasData, x);
          GasType = GasData.GasType;

          if (GasType == DEF_GC_STIRR_GAS_TYPE::Ar)
            setAR_MOMENT(GasData.GasValue);
          else if (GasType == DEF_GC_STIRR_GAS_TYPE::N2)
            setN2_MOMENT(GasData.GasValue);
        }
      }//for (i = 0 ; i < SeqLength ; ++j)

      RetValue = insert();

      if (RetValue)
        commit();
      else
        rollback();
    }
  }

  return RetValue;

}



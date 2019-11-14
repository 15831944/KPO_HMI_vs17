//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include <iomanip>
#include "cCBS_StdEventLogFrameController.h"
#include "CIntfData.h"
#include "CGT_MAT_CHEM.h"
#include "CGT_MAT_EFF.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPD_PHASE_RES.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_REF.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_EFF.h"
#include "CPD_HEAT_YIELDS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::ENAME("ENAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::ELEMENTWEIGHTIN("ELEMENTWEIGHTIN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::ELEMENTWEIGHTOUT("ELEMENTWEIGHTOUT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::SPEC_CONS("SPEC_CONS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::ELEMENTYIELD("ELEMENTYIELD");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_HEAT_YIELDS::ELEMWEIGHTADDITIONS("ELEMWEIGHTADDITIONS");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_YIELDS::CPD_HEAT_YIELDS(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_HEAT_YIELDS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_YIELDS::CPD_HEAT_YIELDS(cCBS_Connection* Connection)
:CSMC_DBData("PD_HEAT_YIELDS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_YIELDS::CPD_HEAT_YIELDS()
:CSMC_DBData("PD_HEAT_YIELDS")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_HEAT_YIELDS::~CPD_HEAT_YIELDS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_HEAT_YIELDS::getHEATID(long Row)
{
  return getString(CPD_HEAT_YIELDS::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setHEATID(const std::string& value)
{
  setString(CPD_HEAT_YIELDS::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_HEAT_YIELDS::getTREATID(long Row)
{
  return getString(CPD_HEAT_YIELDS::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setTREATID(const std::string& value)
{
  setString(CPD_HEAT_YIELDS::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_HEAT_YIELDS::getPLANT(long Row)
{
  return getString(CPD_HEAT_YIELDS::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setPLANT(const std::string& value)
{
  setString(CPD_HEAT_YIELDS::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Element or slag compound name
std::string CPD_HEAT_YIELDS::getENAME(long Row)
{
  return getString(CPD_HEAT_YIELDS::ENAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setENAME(const std::string& value)
{
  setString(CPD_HEAT_YIELDS::ENAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPD_HEAT_YIELDS::getELEMENTWEIGHTIN(long Row)
{
  return getDouble(CPD_HEAT_YIELDS::ELEMENTWEIGHTIN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setELEMENTWEIGHTIN(double value)
{
  setDouble(CPD_HEAT_YIELDS::ELEMENTWEIGHTIN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPD_HEAT_YIELDS::getELEMENTWEIGHTOUT(long Row)
{
  return getDouble(CPD_HEAT_YIELDS::ELEMENTWEIGHTOUT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setELEMENTWEIGHTOUT(double value)
{
  setDouble(CPD_HEAT_YIELDS::ELEMENTWEIGHTOUT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##kg/Ton Final Steel
double CPD_HEAT_YIELDS::getSPEC_CONS(long Row)
{
  return getDouble(CPD_HEAT_YIELDS::SPEC_CONS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setSPEC_CONS(double value)
{
  setDouble(CPD_HEAT_YIELDS::SPEC_CONS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Yield in %
double CPD_HEAT_YIELDS::getELEMENTYIELD(long Row)
{
  return getDouble(CPD_HEAT_YIELDS::ELEMENTYIELD, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setELEMENTYIELD(double value)
{
  setDouble(CPD_HEAT_YIELDS::ELEMENTYIELD, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPD_HEAT_YIELDS::getELEMWEIGHTADDITIONS(long Row)
{
  return getDouble(CPD_HEAT_YIELDS::ELEMWEIGHTADDITIONS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_HEAT_YIELDS::setELEMWEIGHTADDITIONS(double value)
{
  setDouble(CPD_HEAT_YIELDS::ELEMWEIGHTADDITIONS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_HEAT_YIELDS::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& ENAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_HEAT_YIELDS::HEATID,HEATID);
  addWhereClause(CPD_HEAT_YIELDS::TREATID,TREATID);
  addWhereClause(CPD_HEAT_YIELDS::PLANT,PLANT);
  addWhereClause(CPD_HEAT_YIELDS::ENAME,ENAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_HEAT_YIELDS::calculateYields(std::string& Heatid, std::string& Treatid, std::string& Plant)
{
  log("Start of yield calulation",3);

  bool FoundFinalSteelMass = false;
  double FinalSteelMass = 0;

  std::set<std::string>         ConsideredElements;
  std::map<std::string, double> PreTreatMasses;         // Masses based on pretreatment analysis
  std::map<std::string, double> ChargedMaterialMasses;  // Masses based on charged material analysis

  std::string EffyName;

  if (Plant == DEF_GC_PLANT_DEF::LF)
    EffyName = DEF_GC_EFF::Ladle;
  else
    EffyName = DEF_GC_EFF::Furnace;

  //  Collect pretreatment data from PD_HEAT_DATA_LIQADD and analysis from PD_HEAT_DATA_LIQADD_ANL
  if (m_pPD_HEAT_DATA_LIQADD->select(Heatid, Treatid,  Plant, CSMC_DBData::unspecLong) )
  {
    // Collect information about all liquid addition numbers
    long LiqAddNumbers = m_pPD_HEAT_DATA_LIQADD->getLastRow();

    std::stringstream Msg;
    Msg << "Liquid additions: " << LiqAddNumbers << std::endl;

    for (int i = 1; i <= LiqAddNumbers; ++i)
    {
      long    SampleRef = m_pPD_HEAT_DATA_LIQADD->getSAMPLE_REF(i);
      double  SteelMass = m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(i);
      Msg << "Steel mass[" << i << "]: " << SteelMass << std::endl;

      // collect all element entries
      if ( m_pPD_SAMPLE_REF->select(SampleRef) )
      {
        long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSTEEL(1);

        if ( m_pPD_SAMPLE->select(SAMPLE_COUNTER) )
        {
          double CheckMass = 0;

          seqSample SeqSample = m_pPD_SAMPLE->getSample(SAMPLE_COUNTER);

          for ( long i = 0 ; i < CIntfData::getLength(SeqSample); ++i )
          {
            sSample Sample;
            CIntfData::getAt(Sample,SeqSample,i);

            std::string Element = Sample.MeasName;
            double Conc         = Sample.MeasValue;
            
            ConsideredElements.insert(Element);
            PreTreatMasses[Element] += Conc*SteelMass/100.;

            CheckMass += Conc*SteelMass/100.;
            Msg << "Element: " << std::setw(5) << Element << ", conc.: " << Conc 
                << ", PreTreatMasses[" << Element << "]: " << PreTreatMasses[Element] << std::endl;
          }

          Msg << "Total mass: " << CheckMass << std::endl;
        }
      }
      else
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage,"", m_TableName.c_str(), "" );
      }
    }
    log(Msg.str(), 3);
  }
  else
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"", m_TableName.c_str(), "" );
  }

  // Merge all input data
  std::map<std::string,double>::const_iterator MI;
  {
    std::stringstream Msg;
    Msg << "Summary of weight additions: " << std::endl;
    for ( MI = ChargedMaterialMasses.begin(); MI != ChargedMaterialMasses.end(); ++MI)
    {
      Msg << "Mass[" << MI->first << "]: " << MI->second << std::endl;
    }
    log(Msg.str(),3);
  }

  //  Read final steel mass from PD_PHASE_RES, PheaseResNo is always 1 for phase actual, see GC_PHASE
  if (m_pPD_PHASE_RES->select(Heatid, Treatid, Plant, 1 ))
  {
    std::stringstream Msg;
    FinalSteelMass = m_pPD_PHASE_RES->getSTEELMASS(1);

    if (FinalSteelMass == DEF::Inv_Double || FinalSteelMass == CSMC_DBData::unspecDouble)
    {
      FinalSteelMass = 0;
      Msg << "Invalid steel mass found: " << FinalSteelMass << "! Terminating yield calculation!";;
      log(Msg.str(),1);
    }
    else
    {
      FoundFinalSteelMass = true;
      Msg << "Final steel mass found: " << FinalSteelMass;
      log(Msg.str(), 3);
    }
  }
  else
  {
    std::stringstream ErrMsg;
    ErrMsg << "Final steel mass not found with keys: " << Heatid << ", " << Treatid << ", " << Plant;
    log(ErrMsg.str(), 1);
  }

  // Masses based on the final STEEL mass 
  // and the corresponding analysis values are considered as WeightOut
  std::map<std::string,double> FinalMasses;


  std::set<std::string>::const_iterator SI;
  log("Calulating yields!!",3);

  // Iterate over final masses based on last steel sample taken and the final steel weight
  for (SI = ConsideredElements.begin(); SI != ConsideredElements.end(); ++SI)
  {
    std::stringstream Msg;

    double WeightOut = 0;
    if ( (MI = FinalMasses.find(*SI)) != FinalMasses.end() )
    {
      WeightOut = MI->second;
    }

    double WeightIn = 0;
    if ( (MI = PreTreatMasses.find(*SI)) != PreTreatMasses.end() )
    {
      WeightIn = MI->second;
    }

    double SpecCons  = 0;
    double WeightAdditions = 0;
    if ( (MI = ChargedMaterialMasses.find(*SI)) != ChargedMaterialMasses.end() )
    {
      WeightAdditions = MI->second;
      if (FoundFinalSteelMass && FinalSteelMass > 0)
        SpecCons  = 1000.*WeightAdditions/FinalSteelMass; // Specific consumptions in Kg/T
    }

    double Yield = 0;
    if ((WeightAdditions+WeightIn) > 0)
      Yield = 100.*WeightOut/(WeightAdditions+WeightIn);

    Msg << "Element: " <<  std::setw(5) << *SI << std::endl 
        << "WeightIn : " << WeightIn << ", WeightAdditions : " << WeightAdditions
        << ", WeightOut: " << WeightOut << ", Yield: " << Yield << ", SpecCons: " << SpecCons;
    log(Msg.str(), 3);

    this->setELEMENTWEIGHTIN(WeightIn);
    this->setELEMENTWEIGHTOUT(WeightOut);
    this->setELEMENTYIELD(Yield);
    this->setELEMWEIGHTADDITIONS(WeightAdditions);
    this->setSPEC_CONS(SpecCons);

    if (select(Heatid,Plant,*SI,Treatid))
    {
      update();
    }
    else
    {
      setHEATID(Heatid);
      setTREATID(Treatid);
      setPLANT(Plant);
      setENAME(*SI);

      insert();
    }
  }
  commit();
  log("End of yield calulation",3);

  return true;
}

void CPD_HEAT_YIELDS::doOnConstruct()
{
  m_pGT_MAT_EFF                 = new CGT_MAT_EFF(m_pCBS_StdConnection);
  m_pGT_MAT_CHEM                = new CGT_MAT_CHEM(m_pCBS_StdConnection);
  m_pPD_HEAT_DATA_LIQADD        = new CPD_HEAT_DATA_LIQADD(m_pCBS_StdConnection);
  m_pPD_PHASE_RES               = new CPD_PHASE_RES(m_pCBS_StdConnection);
  m_pPD_SAMPLE                  = new CPD_SAMPLE(m_pCBS_StdConnection);
  m_pPD_SAMPLE_REF              = new CPD_SAMPLE_REF(m_pCBS_StdConnection); 
}

void CPD_HEAT_YIELDS::doOnDestruct()
{
  if (m_pGT_MAT_EFF)                { delete m_pGT_MAT_EFF; } 
  if (m_pGT_MAT_CHEM)               { delete m_pGT_MAT_CHEM; } 
  if (m_pPD_HEAT_DATA_LIQADD)       { delete m_pPD_HEAT_DATA_LIQADD; } 
  if (m_pPD_PHASE_RES)              { delete m_pPD_PHASE_RES; } 
  if (m_pPD_SAMPLE)                 { delete m_pPD_SAMPLE; } 
  if (m_pPD_SAMPLE_REF)             { delete m_pPD_SAMPLE_REF; } 
}


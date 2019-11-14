// Copyright (C) 2004 SMS Demag AG

#include <sstream>

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"
#include "CSMC_RecipeHandler.h"

#include "CCtrlSystemCodesLF.h"
#include "CStirrPhaseCodesLF.h"
#include "CTempLossStat.h"
#include "CRS.h"
#include "CInv.h"
#include "CSMM.h"
#include "CDataConversion.h"


#include "CStirrPhaseCodesLF.h"
#include "CProcPhaseCodesLF.h"
#include "CStirrPhaseCodesLF.h"
#include "CSubRecipeCodesLF.h"
#include "CSourceLF.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_PRODPRAC_DEF.h"


#include "CPD_SAMPLE_ENTRY.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_THERM_STAT.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"

#include "CLFModelWrapper.h"

//##ModelId=4151820803CC
CLFModelWrapper::CLFModelWrapper():
  m_pGC_PHASE(0),
  m_pGC_RESTRI_DEF(0),
  m_pGC_RECIPE_SOURCE(0),
  m_pGCL_STIRR_INT(0),
  m_pGCL_STIRR_PHASE(0),
  m_pGT_PARAM(0),
  m_pGT_PARAM_MATRIX(0),
  m_pHD_RESTRI(0),
  m_pHD_RESTRI_ENTRY(0),
  m_pPD_MAT_AVAIL(0),
  m_pGT_MAT(0),
  m_pHD_GRADE_ANL(0),
  m_pHD_GRADE_EQUIV(0),
  m_pHD_TREATMODE(0),
  m_pHD_GRADE(0),
  m_pGT_EQUIV(0),
  m_pPP_HEAT(0),
  m_pPP_ORDER_SINGLE_AIMS(0),
  m_pGC_RECIPE_L1(0),
  m_pPD_HEAT_DATA(0),
  m_pPD_HEAT_DATA_LIQADD(0),
  m_pPD_LADLE(0),
  m_pPD_SAMPLE(0),
  m_pPD_HEAT_DATA_PRODPRAC(0),
  m_pPD_SAMPLE_REF(0),
  m_pPD_PRETREATDATA(0),
  m_pHDL_PP_EL_STEP(0),
  m_pHDL_PP_EL(0),
  m_pHDL_PP_STIRR(0),
  m_pHDL_PP_STIRR_SPEC(0),
  m_pGCL_EL_PHASE(0),
  m_pGC_COMBI_RECIPE_ENTRY(0),
  m_pGCL_ACTIVITY(0),
  m_pChem_Elem_Container(0),
  m_pGC_Plant_Container(0),
  m_pRecipeHandler(0),
  m_pPD_SAMPLE_ENTRY(0)
{
}

//##ModelId=4151820803E0
CLFModelWrapper::~CLFModelWrapper()
{
  deleteDBClasses();
}

//##ModelId=42A06E2B0277
void CLFModelWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  if (pConnection)
  {
    m_pRecipeHandler              = new CSMC_RecipeHandler();

    m_pGC_PHASE                   = new CGC_PHASE(pConnection);
    m_pGC_RECIPE_SOURCE           = new CGC_RECIPE_SOURCE(pConnection);
    m_pGC_COMBI_RECIPE_ENTRY      = new CGC_COMBI_RECIPE_ENTRY(pConnection);
    m_pGC_RESTRI_DEF              = new CGC_RESTRI_DEF(pConnection);
    m_pGT_PARAM                   = new CGT_PARAM(pConnection);
    m_pGT_PARAM_MATRIX            = new CGT_PARAM_MATRIX(pConnection);
    m_pHD_RESTRI_ENTRY            = new CHD_RESTRI_ENTRY(pConnection);
    m_pHD_RESTRI                  = new CHD_RESTRI(pConnection);
    m_pPD_HEAT_DATA_LIQADD        = new CPD_HEAT_DATA_LIQADD(pConnection);
    m_pPD_HEAT_DATA_PRODPRAC      = new CPD_HEAT_DATA_PRODPRAC(pConnection);
    m_pPD_LADLE                   = new CPD_LADLE(pConnection);
    m_pPD_SAMPLE                  = new CPD_SAMPLE(pConnection);
    m_pPD_SAMPLE_REF	            = new CPD_SAMPLE_REF(pConnection);
    m_pPD_PRETREATDATA	          = new CPD_PRETREATDATA(pConnection);
    m_pHD_GRADE_ANL               = new CHD_GRADE_ANL(pConnection);
    m_pHD_GRADE_EQUIV             = new CHD_GRADE_EQUIV(pConnection);
    m_pHD_TREATMODE               = new CHD_TREATMODE(pConnection);
    m_pHD_GRADE                   = new CHD_GRADE(pConnection);
    m_pGT_EQUIV                   = new CGT_EQUIV(pConnection);
    m_pGCL_ACTIVITY               = new CGCL_ACTIVITY(pConnection);
    m_pGCL_EL_PHASE               = new CGCL_EL_PHASE(pConnection);
    m_pGCL_STIRR_INT              = new CGCL_STIRR_INT(pConnection);
    m_pGCL_STIRR_PHASE            = new CGCL_STIRR_PHASE(pConnection);
    m_pHDL_PP_EL_STEP             = new CHDL_PP_EL_STEP(pConnection);
    m_pHDL_PP_STIRR               = new CHDL_PP_STIRR(pConnection);
    m_pHDL_PP_STIRR_SPEC          = new CHDL_PP_STIRR_SPEC(pConnection);
    m_pHDL_PP_EL                  = new CHDL_PP_EL(pConnection);
    m_pPD_MAT_AVAIL               = new CPD_MAT_AVAIL(pConnection);
    m_pGT_MAT                     = new CGT_MAT(pConnection);
    m_pPD_HEAT_DATA               = new CPD_HEAT_DATA(pConnection);
    m_pPP_HEAT                    = new CPP_HEAT(pConnection);
    m_pPP_ORDER_SINGLE_AIMS       = new CPP_ORDER_SINGLE_AIMS(pConnection);
    m_pGC_RECIPE_L1               = new CGC_RECIPE_L1(pConnection);
    m_pChem_Elem_Container        = new CChem_Elem_Container(pConnection);
    m_pGC_Plant_Container         = new CGC_Plant_Container(pConnection);
    m_pPD_SAMPLE_ENTRY            = new CPD_SAMPLE_ENTRY(pConnection)  ;
  }
}

//##ModelId=42A06E2B02A9
void CLFModelWrapper::deleteDBClasses()
{

    delete m_pRecipeHandler;

    delete m_pGC_PHASE;
    delete m_pGC_RECIPE_SOURCE;
    delete m_pGC_RESTRI_DEF;
    delete m_pGT_PARAM;
    delete m_pGT_PARAM_MATRIX;
    delete m_pHD_RESTRI;
    delete m_pHD_RESTRI_ENTRY;
    delete m_pPD_HEAT_DATA_LIQADD;
    delete m_pPD_HEAT_DATA_PRODPRAC;
    delete m_pPD_LADLE;
    delete m_pPD_SAMPLE;
    delete m_pPD_SAMPLE_REF;
    delete m_pPD_PRETREATDATA;
		delete m_pHD_GRADE_ANL;
    delete m_pHD_GRADE_EQUIV;
		delete m_pHD_TREATMODE;
		delete m_pHD_GRADE;
		delete m_pGT_EQUIV;
    delete m_pGCL_ACTIVITY;
    delete m_pGCL_EL_PHASE;
    delete m_pGCL_STIRR_INT;
    delete m_pGCL_STIRR_PHASE;
    delete m_pGC_COMBI_RECIPE_ENTRY;
    delete m_pHDL_PP_EL_STEP;
    delete m_pHDL_PP_STIRR;
    delete m_pHDL_PP_STIRR_SPEC;
    delete m_pHDL_PP_EL;
    delete m_pPD_MAT_AVAIL;
    delete m_pGT_MAT;
    delete m_pPD_HEAT_DATA;
    delete m_pPP_HEAT;
    delete m_pPP_ORDER_SINGLE_AIMS;
    delete m_pGC_RECIPE_L1;
    delete m_pChem_Elem_Container;
    delete m_pPD_SAMPLE_ENTRY ;
	  delete m_pGC_Plant_Container;

}

//##ModelId=42A06E2B02E5
void CLFModelWrapper::handleError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage,"", Function, Action);    
}

//##ModelId=42A06E2C000C
void CLFModelWrapper::handleCORBAConnectionError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",  Function, Action);    
}

//##ModelId=42A06E2C0110
void CLFModelWrapper::handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function, Action);    

  handleDBConnectionError();
}

//##ModelId=42A06E2C02A1
void CLFModelWrapper::handleDBConnectionError()
{
  if (m_pModelTask)
  {
    m_pModelTask->handleDBConnectionError();
  }

}

//##ModelId=417615BD0085
bool CLFModelWrapper::doModelResult(CEventMessage& Event)
{
  bool RetValue = false;

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (m_pModelTask)
  {
    RetValue = m_pModelTask->callModelResultWrapper(ActPlant,Event);
  }

  return RetValue;
}


//##ModelId=415182090124
bool CLFModelWrapper::sequence_set_aim_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long PlantNo, bool Online)
{
  bool RetValue = false;
  std::string Function = "CLFModelWrapper::sequence_set_aim_data" ;

  CIntfLF *pIntfLF = getpModelIntf();
  
  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("Error " +  Function + ", (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try 
  { 
    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant)) // only 1 row can be selected
    {
      CDateTime     TreatStartTime, TreatEndTime;
      CDeltaTime    DurAimTreatmentTime;
      std::string   EquivalenceName;
      double        Value = 0.;

      stringstream tmp;
      tmp << "Heat Announcement Aim Data: " << "\n";

      //CLFModelTask::getInstance()->AimSteelWeight=0.;
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMSTEELWGT_MOD, 1)) 
      {
        pIntfLF->setAimMass(m_pPD_HEAT_DATA->getAIMSTEELWGT_PLAN(1));
      }
      else
      {
        pIntfLF->setAimMass(m_pPD_HEAT_DATA->getAIMSTEELWGT_MOD(1));
      }

      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::AIMTEMP_MOD, 1)) 
      {
        pIntfLF->setAimTemp(m_pPD_HEAT_DATA->getAIMTEMP_PLAN(1));
      }
      else 
      {
        pIntfLF->setAimTemp(m_pPD_HEAT_DATA->getAIMTEMP_MOD(1));
      } 

      std::string SteelGradeCode;
      if (m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::STEELGRADECODE_ACT, 1)) 
      {
        SteelGradeCode = m_pPD_HEAT_DATA->getSTEELGRADECODE_PLAN(1);
      }
      else         
      {
        SteelGradeCode = m_pPD_HEAT_DATA->getSTEELGRADECODE_ACT(1);      
      }

      // **********************************************************
      // according to UML design sequence must be called as follows
      // **********************************************************
      // pIntfLF->declareEquivalenceName(EquivalenceName,isActive);
      // pIntfLF->declareEquivalenceTerm(EquivalenceName,Value,true);
      // pIntfLF->setAimSteelGradeCode(SteelGradeCode);      

      // try to find existing equivalences
      if ( m_pHD_GRADE_EQUIV->select(HeatID, TreatID, Plant, SteelGradeCode, CSMC_DBData::unspecString) )
      {
        // JAST EL_

        for ( long i = 1 ; i <= m_pHD_GRADE_EQUIV->getLastRow() ; ++i )
        {
          EquivalenceName = m_pHD_GRADE_EQUIV->getEQ_NAME(i);
            
          if ( m_pGT_EQUIV->select(EquivalenceName) )
          {
            pIntfLF->declareEquivalenceName(EquivalenceName,true);

            // handle offset
            Value = m_pGT_EQUIV->getOFFSET(1);
            pIntfLF->declareEquivalenceTerm(EquivalenceName,Value,true);

            std::map<std::string,double> Numerator    = m_pGT_EQUIV->getNumerator(EquivalenceName);
            std::map<std::string,double> Denominator  = m_pGT_EQUIV->getDenominator(EquivalenceName);
            std::map<std::string,double>::iterator it;

            // handle Numerator
            for ( it = Numerator.begin() ; it != Numerator.end(); ++it )
            {
              pIntfLF->declareEquivalenceTerm(EquivalenceName,it->second,true,it->first);
            }
            // handle Denominator
            for ( it = Denominator.begin() ; it != Denominator.end(); ++it )
            {
              pIntfLF->declareEquivalenceTerm(EquivalenceName,it->second,false,it->first);
            }
          }
          else
          {
            // JAST EL_
          }
        } // for ( long i = 1 ; i <= m_pHD_GRADE_EQUIV.getLastRow() ; ++i )
      } // if ( m_pHD_GRADE_EQUIV->select(HeatID, TreatID, m_PlantName, SteelGradeCode, CSMC_DBData::unspecString) )


      // set aim steel grade code        
      pIntfLF->setAimSteelGradeCode(SteelGradeCode);      

      //Jiantao TREATSTART_ACT should not be used for calculate duration
      /*if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATSTART_ACT, 1)) 
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_ACT(1);
      }
      else */
      if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATSTART_MOD, 1))
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_MOD(1);
      }
      else 
      {
        TreatStartTime = m_pPD_HEAT_DATA->getTREATSTART_PLAN(1);
      }

      //consider case of missing data
      bool TreatEndTimeGiven = false;
      //Jiantao TREATEND_ACT should not be used for calculate duration
      /*if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATEND_ACT, 1))
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_ACT(1);
      }
      else */
      if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATEND_MOD, 1)) 
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_MOD(1);
      }
      else if (!m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::TREATEND_PLAN, 1))
      {
        TreatEndTime = m_pPD_HEAT_DATA->getTREATEND_PLAN(1);
      }

      DurAimTreatmentTime  = CDateTime::subTimes(TreatEndTime, TreatStartTime);

      double DurAimTreatmentTime_Tmp = DurAimTreatmentTime.asSeconds();

      if (DurAimTreatmentTime_Tmp < 1.)      
      {
        DurAimTreatmentTime_Tmp = CInv::InvalidDouble;          // invalid
      }
      else
      {
        DurAimTreatmentTime_Tmp /= 60;                          // minutes
      }

      if(Online) 
      {
        pIntfLF->setAimDepartTime(DurAimTreatmentTime_Tmp);
      }

      // repeat for all types of analyses as specified in CAnlType
      if (m_pHD_GRADE->select(HeatID, TreatID, Plant))
      {
        if (m_pHD_GRADE_ANL->select(HeatID, TreatID, Plant, SteelGradeCode, CSMC_DBData::unspecString, CSMC_DBData::unspecString))
        {
          // update container because Eyuivalences can be added dynamically
          m_pChem_Elem_Container->init();

          for (int i = 1; i <= m_pHD_GRADE_ANL->getLastRow(); i++)
          {
            std::string AIMTYPE = m_pHD_GRADE_ANL->getAIMTYPE(i);
            std::string ENAME   = m_pHD_GRADE_ANL->getENAME(i);
            double ANL          = m_pHD_GRADE_ANL->getANL(i);

            // adaption of analysis elements
            adaptAimAnl(HeatID,TreatID,Plant,PlantNo,AIMTYPE,ENAME,ANL);

            if ( m_pChem_Elem_Container->isSteelElem(ENAME)    || 
                 m_pChem_Elem_Container->isEquivalence(ENAME)  || 
                 m_pChem_Elem_Container->isSlagElem (ENAME)    )
            {
              pIntfLF->setAimAnl(AIMTYPE,ENAME,ANL);
            }

          } //for
        }
      }

      RetValue = true;

    } // if select m_pPD_HEAT_DATA 

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelWrapper::sequence_set_aim_data()", ""  );    
  }

  return RetValue;
}

//##ModelId=4151820901CF
bool CLFModelWrapper::sequence_set_tap_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue = false;

  std::string Function     = "CLFModelWrapper::sequence_set_tap_ladle_data";
  std::stringstream ExceptionMsg;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF)
  {
    std::string LadleType;
    long LadleNo = -1;
    std::string TempStatus;

    try // common catch
    { 
      if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant))
      {
        LadleType = m_pPD_HEAT_DATA->getLADLETYPE(1);
        LadleNo   = m_pPD_HEAT_DATA->getLADLENO(1);

        // setTapLadleId(LadleID : const string&)              
        // Ladle Data. The Ladle Id is Ladletype + LadleNo
        
        pIntfLF->setTapLadleId( LadleType + CDataConversion::LongToString(LadleNo) );              

        if (m_pPD_LADLE->select(LadleNo, LadleType)) 
        {
          TempStatus = m_pPD_LADLE->getTHERMALSTATUS(1);

          // setTapLadleTempLossStat(LadleStatus : const string&)
          if (TempStatus == DEF_GC_THERM_STAT::H) 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::High);
          }
          else if (TempStatus == DEF_GC_THERM_STAT::C) 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::Low);
          }
          else 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::Medium);
          }

          long PRETREAT_CNT_PREV  = m_pPD_LADLE->getPRETREAT_CNT_PREV(1);
          long SAMPLE_REF         = CSMC_DBData::unspecLong;
          double STEELWEIGHT      = CSMC_DBData::unspecDouble;
          double SLAGWEIGHT       = CSMC_DBData::unspecDouble;

          if ( m_pPD_PRETREATDATA->select(PRETREAT_CNT_PREV) )
          {
            STEELWEIGHT   = m_pPD_PRETREATDATA->getSTEELWEIGHT(1);
            SLAGWEIGHT    = m_pPD_PRETREATDATA->getSLAGWEIGHT(1);
            SAMPLE_REF    = m_pPD_PRETREATDATA->getSAMPLE_REF(1);
          }

          // setTapLadleIniSteelWgt(IniSteelWgt : double)
          pIntfLF->setTapLadleIniSteelWgt(STEELWEIGHT);
          // setTapLadleIniSlagWgt(IniSlagWgt : double)
          pIntfLF->setTapLadleIniSlagWgt(SLAGWEIGHT);

          if ( SAMPLE_REF  != CSMC_DBData::unspecLong )
          {
            long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSTEEL(SAMPLE_REF);

            if (SAMPLE_COUNTER != CSMC_DBData::unspecLong && m_pPD_SAMPLE->select(SAMPLE_COUNTER) )
            {
              // update container because Eyuivalences can be added dynamically
              m_pChem_Elem_Container->init();

              seqSample SeqSample = m_pPD_SAMPLE->getSample(SAMPLE_COUNTER);

              // repeat for all valid types of analyses and all elements to be specified.
              for (int i = 0; i <= CIntfData::getLength(SeqSample); i++)
              {
                sSample Sample;
                CIntfData::getAt(Sample,SeqSample,i);

                std::string elemName = Sample.MeasName;

                if (m_pChem_Elem_Container->isSteelElem(elemName)) 
                {
                  pIntfLF->setTapLadleIniSteelAna(elemName, Sample.MeasValue);
                }
                else if (m_pChem_Elem_Container->isSlagElem(elemName))
                {
                  pIntfLF->setTapLadleIniSlagAna(elemName, Sample.MeasValue);
                }
                else
                {
                  std::string mes;
                  mes = "WARNING: Analysis element: '";
                  mes += elemName + "' is defined neither as steel nor as slag element!";
                  log(mes,2);
                }
              }
            }
            else
            {
              std::string SearchKey = LadleType + CDataConversion::LongToString(LadleNo);
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_SAMPLE");
            }
          }
        }
        else
        {
          std::string SearchKey = LadleType + CDataConversion::LongToString(LadleNo);
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_LADLE");
        }

        RetValue = true;
      }
      else
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA");
      }
    } 
    catch(cCBS_DBExc &e) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), ExceptionMsg.str().c_str());

      CLFModelWrapper::handleDBConnectionError();
    } // db catch
    catch (...)
    {
      RetValue = false;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        Function.c_str(), std::string("Unknown exception").c_str());    
    } // common catch
  }
  else
  {
    handleError("CLFModelWrapper", "sequence_set_tap_ladle_data(): pIntfLF = 0");
  }

  return RetValue;
}

//##ModelId=4151820903D7
bool CLFModelWrapper::sequence_set_production_practice_data_electric(CEventMessage& Event)
{  
  bool RetValue = false;

  std::string Message   = Event.getMessage();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelWrapper::sequence_set_production_practice_data_electric(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  std::string Phase;
  stringstream PhaseStream;
  int Step=1;

  long ProdPracPointer = getProdPracticePointer(HeatID,TreatID,ActPlant, DEF_GC_PRODPRAC_DEF::Electric);

  try 
  {
    if (!m_pHDL_PP_EL->select(HeatID,TreatID,ActPlant,CSMC_DBData::unspecLong))
    {
      std::stringstream SearchKey;
      SearchKey << HeatID << " " << TreatID << " " << ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"HDL_PP_EL");

      return RetValue;
    }

    if ( Message != LF_EvMsg::evLFHeatAnnouncement && Message != LF_EvMsg::evLFHeatAnnouncementOffline  )  
    {
      pIntfLF->indicateChgProdPracElec(); 
      pIntfLF->setProdPracPtElec(m_pHDL_PP_EL->getPRACNO(1));
    }
    else
    {
      pIntfLF->setProdPracPtElec(ProdPracPointer);
    }

    if (m_pHDL_PP_EL_STEP->selectByHeatPlant(HeatID, TreatID, ActPlant )) 
    {
      for (int i = 1; i <= m_pHDL_PP_EL_STEP-> getLastRow(); i++)
      {
        /*if (Phase != m_pHDL_PP_EL_STEP->getPRACPHASE(i))
        {
          Phase = m_pHDL_PP_EL_STEP->getPRACPHASE(i),
          pIntfLF->focusOnElecPhase(Phase);
        }*/

        pIntfLF->focusOnActivity(m_pHDL_PP_EL_STEP->getACTIVITYNAME(i));
        //  take care about inv long/double
        double tempDur=m_pHDL_PP_EL_STEP->getDURATION(i)/60.0;  
        pIntfLF->setProdPracElec(m_pHDL_PP_EL_STEP->getVOLTTAP(i),
                                   m_pHDL_PP_EL_STEP->getIMPCURVE(i),
                                   tempDur,
                                   m_pHDL_PP_EL_STEP->getDELTA_TEMP(i));
      }   
      RetValue = true;
    }                    
	                            
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelWrapper::sequence_set_production_practice_data_electric()", ""  );    
  }

  return RetValue;
}


//##ModelId=42A06E2D00E9
bool CLFModelWrapper::sequence_set_production_practice_data_stirring(CEventMessage& Event)
{
  //
  // mrut 2013-03-07 : Changed by mrut for usage of improved interface-method and simpler code.
  //	
  bool RetValue = false;
  
  CIntfLF *pIntfLF = getpModelIntf();
  std::string Message   = Event.getMessage();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelWrapper::sequence_set_production_practice_data_stirring(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  long ProdPracPointer = getProdPracticePointer(HeatID,TreatID,ActPlant, DEF_GC_PRODPRAC_DEF::Stirring);

  try 
  {
    std::stringstream tmp_Stirr_Practice;
 
    if (!m_pHDL_PP_STIRR->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
    {
      std::stringstream SearchKey;
      SearchKey << HeatID << " " << TreatID << " " << ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"HDL_PP_STIRR");

      return RetValue;
    }

    if ( Message != LF_EvMsg::evLFHeatAnnouncement && Message != LF_EvMsg::evLFHeatAnnouncementOffline  ) 
    {
      pIntfLF->indicateChgProdPracStirr();

      ProdPracPointer = m_pHDL_PP_STIRR->getPRACNO(1);
    }


    pIntfLF->setProdPracPtStirr(ProdPracPointer);

    tmp_Stirr_Practice << "Stirr Prac Data for practice: " << ProdPracPointer << "\n";


    if (m_pHDL_PP_STIRR_SPEC->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong, CSMC_DBData::unspecString))
    {
      int    i = 1;
      int    inough = m_pHDL_PP_STIRR_SPEC->getLastRow();
      for (; i <= inough; ++i)
      {
        std::string Phase ( m_pHDL_PP_STIRR_SPEC->getPRACPHASE(i) );
       
        if ( !m_pGCL_STIRR_PHASE->select(Phase) )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,Phase.c_str(),"GCL_STIRR_PHASE");
          break;
        }
        else
        {          	
          std::string StirringStepCode (m_pGCL_STIRR_PHASE->getPRACPHASEMODEL(1));

          std::string GasTyp   =  m_pHDL_PP_STIRR_SPEC->getSTIRRGASTYPE(i);
          long   IntensityCode =  m_pHDL_PP_STIRR_SPEC->getINTENSITY(i);                
          long   Duration      =  m_pHDL_PP_STIRR_SPEC->getDURATION(i);
          double DurDur        = (Duration == CSMC_DBData::unspecLong ) ? CSMC_DBData::unspecDouble : Duration;
              
          if (m_pGCL_STIRR_INT->select(IntensityCode))
          {
            double StirrFlow = m_pGCL_STIRR_INT->getSTIRRFLOW(1);                       //Nm3/min set by L1

            std::string IntensityCodeModel = m_pGCL_STIRR_INT->getINTCODEMODEL(1);

            pIntfLF->setProdPracStirring(StirringStepCode, IntensityCodeModel, GasTyp,  StirrFlow, DurDur);

            tmp_Stirr_Practice << "PracPhase: " << Phase << endl;
            tmp_Stirr_Practice << "IntModel: " << IntensityCodeModel << " GaseType: " << GasTyp;
            tmp_Stirr_Practice << " Flow in Nm3/Min: " <<StirrFlow <<" Dur: "  << DurDur <<endl;
          }
          else
          {
            std::stringstream SearchKey;
            SearchKey << "StirrInt " << IntensityCode;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"GCL_Stirr_Int");
            break;          
          }
        }
      } // for ..

      //pIntfLF->setDurCleanBubblg(durCleanBubblg);    // replaced by new call: setProdPracStirring
      //pIntfLF->setDurSoftBubblg (durSoftBubblg);     // replaced by new call: setProdPracStirring

      //pIntfLF->setOxyMaxSlagForSoftBubblg(0.0);      // we do not have this data in DB
      //pIntfLF->setAlsMinForSoftBubblg(0.03);         // we do not have this data in DB
      //pIntfLF->setSulfMaxForSoftBubblg(0.012);       // we do not have this data in DB
      //pIntfLF->setPctRedSoftBubblgFastDesul(0.0);    // we do not have this data in DB
      
      log(tmp_Stirr_Practice.str(), 3);
      if (i > inough)                                  // loop finished completely
          RetValue = true;
    }                    
    else
    {
      std::stringstream SearchKey;
      SearchKey << HeatID << " " << TreatID << " " << ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"HDL_PP_STIRR_SPEC");
    }


  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelWrapper::sequence_set_production_practice_data_stirring()", ""  );    

  }

  return RetValue;
}


//##ModelId=42A06E2D037E
bool CLFModelWrapper::sequence_set_production_practice_data_recipe_ctrl(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Function = "CLFModelWrapper::sequence_set_production_practice_data_recipe_ctrl()";

  std::string Message   = Event.getMessage();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFModelWrapper::sequence_set_production_practice_data_recipe_ctrl(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  long ProdPracPointer = getProdPracticePointer(HeatID,TreatID,ActPlant, DEF_GC_PRODPRAC_DEF::Restriction);
  long TreatmentModeNo = getTreatmentModeNo(HeatID, TreatID, ActPlant);

  try 
  {
    const std::string DescrPP         = DEF_GC_PRODPRAC_DEF::Restriction;
    const long        LiqAddNo        = CSMC_DBData::unspecLong;
    const long        LineNo          = CSMC_DBData::unspecLong;

    if (!m_pHD_RESTRI->select( HeatID, TreatID, ActPlant, DescrPP, ProdPracPointer, TreatmentModeNo, LiqAddNo))
    {
      std::stringstream SearchKey;
      SearchKey << HeatID << " " << TreatID << " " << ActPlant << " "  << " ProdPac " << ProdPracPointer;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.str().c_str(),"HD_RESTRI");

      return false;
    }

    m_pGC_COMBI_RECIPE_ENTRY->selectByPlant(ActPlant);

    for (int i = 1; i <= m_pGC_COMBI_RECIPE_ENTRY->getLastRow(); i++)
    {
      const std::string CombinationName   = m_pGC_COMBI_RECIPE_ENTRY->getCOMBINATION_NAME(i);
      const std::string RecipeName        = m_pGC_COMBI_RECIPE_ENTRY->getRECIPENAME(i);
      const long        RecipeNo          = 1;
      const std::string RecipeSource      = m_pGC_COMBI_RECIPE_ENTRY->getSOURCE(i);

      std::string       RecipeNameModel;
		  long              RecipeNoModel     = 0;

      if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
      {
        if (m_pHD_RESTRI_ENTRY->selectBySourceAndCombiName( HeatID, TreatID, ActPlant, ActPlantNo, DescrPP, ProdPracPointer, TreatmentModeNo, LiqAddNo, LineNo, RecipeSource, CombinationName ) )
        {      
          if (RecipeSource == DEF_GC_RECIPE_SOURCE::All)
          {
            pIntfLF->focusOnRecipe(RecipeNameModel,RecipeNoModel, true);
          }
          else
          {
            pIntfLF->focusOnRecipeOrig(RecipeNameModel,RecipeNoModel, RecipeSource, true);
          }

          for (int j = 1; j <= m_pHD_RESTRI_ENTRY->getLastRow(); j++)
          {
            std::string Mat_PurpCode;
            std::string RestriType    = m_pHD_RESTRI_ENTRY->getRESTRITYPE(j);;

            if (m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::MAT_CODE, j))
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getPURP_CODE(j);
            }
            else
            {
              Mat_PurpCode = m_pHD_RESTRI_ENTRY->getMAT_CODE(j);
            }

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_HandleRestriction(sMessage, RecipeSource.c_str(), CombinationName.c_str(), Mat_PurpCode.c_str() );

            if (m_pGC_RESTRI_DEF->select(RestriType))
            {                  
              if (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMIN, j))
              {                  
                if (m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j) > 0)
                {
                  pIntfLF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMIN(j),m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MIN(1));
                }
              }
              if (!m_pHD_RESTRI_ENTRY->isNull(CHD_RESTRI_ENTRY::RESTRI_VALMAX, j))
              {
                pIntfLF->setMatRestr(Mat_PurpCode, m_pHD_RESTRI_ENTRY->getRESTRI_VALMAX(j), m_pGC_RESTRI_DEF->getRESTRITYPEMODEL_MAX(1));
              }
            }
            else
            {
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ErrorSearchingData(sMessage,RestriType.c_str(),"GC_RESTRI_DEF");
            } // select m_pGC_RESTRI_DEF
          } // for m_pHD_RESTRI_ENTRY
        } // 
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
      }

    }//for (...) 

    RetValue = true;
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    
  }

  return RetValue;
}

//##ModelId=4151820A00E0
bool CLFModelWrapper::sequence_set_liquid_material_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant, long TreatNo, std::string LadleType, long LadleNo, long SampleRef, double SteelWeight, double SlagWeight)
{
  bool RetValue = false;
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFModelWrapper::sequence_set_liquid_material_data(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    CDateTime Now;
    std::string TempStatus                = CTempLossStat::Medium;
    double TempTimeRelToAnnouncementtime  = 0.0;
    double FillTimeRelToAnnouncementtime  = 0.0;
    CDateTime LastFillTime                = CSMC_DBData::unspecDate;
 
    if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
    {
      CDateTime SampleTimeTEMP;
      CDeltaTime DeltaTimeAnnTempTime;
      CDeltaTime DeltaTimeLastFillTime;

      CDateTime TimeAnnounce          = m_pPD_HEAT_DATA->getHEATANNOUNCE_ACT(1);

      if ( SampleRef != CSMC_DBData::unspecLong )
      {
        SampleTimeTEMP = m_pPD_SAMPLE_REF->getSampleTimeTEMP(SampleRef);
      }

      if ( LadleNo != CSMC_DBData::unspecLong && LadleType!= CSMC_DBData::unspecString )
      {
        LadleNo = m_pPD_HEAT_DATA->getLADLENO(1);
        LadleType = m_pPD_HEAT_DATA->getLADLETYPE(1);
      }

      if ( LadleNo != CSMC_DBData::unspecLong && LadleType!= CSMC_DBData::unspecString )
      {
        if (m_pPD_LADLE->select(LadleNo, LadleType)) 
        {
          std::string THERMALSTATUS = m_pPD_LADLE->getTHERMALSTATUS(1);

          if (THERMALSTATUS == DEF_GC_THERM_STAT::H) 
          {
            TempStatus = CTempLossStat::High;
          }
          else if (THERMALSTATUS == DEF_GC_THERM_STAT::C) 
          {
            TempStatus = CTempLossStat::Low;
          }
          else
          {
            TempStatus = CTempLossStat::Medium;
          }

          // last time when ladle was filled
          LastFillTime      = m_pPD_LADLE->getLAST_FILL_TIME(1);
        }

        // *******************************************************************
        // calculate time between last temperature measurement and announcment
        // *******************************************************************
        SampleTimeTEMP                = CDataConversion::SetInvalidToDefault(SampleTimeTEMP,Now);
        TimeAnnounce                  = CDataConversion::SetInvalidToDefault(TimeAnnounce,Now);

        DeltaTimeAnnTempTime          = CDateTime::subTimes(TimeAnnounce, SampleTimeTEMP);
        TempTimeRelToAnnouncementtime = max(0.0, DeltaTimeAnnTempTime.asSeconds()/60.) ;

        // ******************************************************
        // calculate time between last ladle fill and announcment
        // ******************************************************
        LastFillTime                  = CDataConversion::SetInvalidToDefault(LastFillTime,Now);

        DeltaTimeLastFillTime         = CDateTime::subTimes(TimeAnnounce, LastFillTime);
        FillTimeRelToAnnouncementtime = max(0.0, DeltaTimeLastFillTime.asSeconds()/60.) ;

      }
    }

    pIntfLF->focusOnLiqAddSteel(HeatID, TreatNo); 

    pIntfLF->setLadleData(LadleType + CDataConversion::LongToString(LadleNo), TempStatus);

    pIntfLF->setSteelMass(SteelWeight);

    pIntfLF->setSlagMass(SlagWeight);      

    pIntfLF->setSteelTempTime(TempTimeRelToAnnouncementtime);

    pIntfLF->setResidenceTimeInLadle(FillTimeRelToAnnouncementtime);


    if( (SampleRef != CSMC_DBData::unspecLong) && m_pPD_SAMPLE_REF->select(SampleRef))
    {
      long SAMPLE_COUNTER_Steel  = m_pPD_SAMPLE_REF->getSTEEL(1);
      long SAMPLE_COUNTER_Slag   = m_pPD_SAMPLE_REF->getSLAG(1);
      long SAMPLE_COUNTER_Temp   = m_pPD_SAMPLE_REF->getTEMP(1);

      // update container because Eyuivalences can be added dynamically
      m_pChem_Elem_Container->init();

      if(SAMPLE_COUNTER_Temp != CSMC_DBData::unspecLong && m_pPD_SAMPLE_ENTRY->select(SAMPLE_COUNTER_Temp,DEF_GC_MEASUREMENT_NAME::Temp))
      {
        pIntfLF->setSteelTemp(m_pPD_SAMPLE_ENTRY->getMEASVALUE(1)); 
      }

      if( SAMPLE_COUNTER_Steel != CSMC_DBData::unspecLong && m_pPD_SAMPLE_ENTRY->select(SAMPLE_COUNTER_Steel,CSMC_DBData::unspecString))
      {
        for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
        {
          if (m_pChem_Elem_Container->isSteelElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
          {
            pIntfLF->setAnlArr(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
          }
        }
      }

      if(SAMPLE_COUNTER_Slag != CSMC_DBData::unspecLong && m_pPD_SAMPLE_ENTRY->select(SAMPLE_COUNTER_Slag,CSMC_DBData::unspecString))
      {
        for ( long i = 1 ; i <= m_pPD_SAMPLE_ENTRY->getLastRow(); ++i )
        {
          if (m_pChem_Elem_Container->isSlagElem(m_pPD_SAMPLE_ENTRY->getMEASNAME(i))) 
          {
            pIntfLF->setAnlArr(m_pPD_SAMPLE_ENTRY->getMEASNAME(i),m_pPD_SAMPLE_ENTRY->getMEASVALUE(i));
          }
        }
      }
    }

    RetValue = true;
  
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModelWrapper::sequence_set_liquid_material_data()", ""  );    
  }

  return RetValue;
}

//##ModelId=4151820A018A
bool CLFModelWrapper::sequence_set_plant_status(const std::string& HeatID, const std::string& TreatID)
{
  bool RetValue = false;
  return RetValue;
}

//##ModelId=462767AC0266
CIntfLF* CLFModelWrapper::getpModelIntf()
{
  CSMM_ModelTask* pSMMModelTask = static_cast<CSMM_ModelTask*>(m_pModelTask);

  return static_cast<CIntfLF*>(pSMMModelTask->getpModelInterface(DEF_GC_PLANT_DEF::LF));
}

// adaption of ANL, ANL given as referecne
// method writes EventLog if ANL of ENAME is changes by Parameter
bool CLFModelWrapper::adaptAimAnl(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, const std::string& AIMTYPE, const std::string& ENAME, double& ANL)
{
  bool RetValue = true;

  // check element
  // was special implementation for CORUS
  //if ( ENAME == DEF_GC_MEASUREMENT_NAME::Ca )
  //{
  //  std::string ROUTECODE;
  //  std::string NOHEATSEQ;
  //  
  //  long CASTERSEQNO      = CSMC_DBData::unspecLong;
  //  long ProdPracPointer  = getProdPracticePointer(HEATID, TREATID, PLANT, DEF_GC_PRODPRAC_DEF::Parameter);

  //  double CorrectionFactor = CSMC_DBData::unspecDouble;

  //  // get ROUTECODE
  //  if ( m_pPP_HEAT && m_pPP_HEAT->select(HEATID) )
  //  {
  //    ROUTECODE   = m_pPP_HEAT->getROUTECODE_PLAN(1);
  //    CASTERSEQNO = m_pPP_HEAT->getCASTERSEQNO(1);
  //    NOHEATSEQ   = CDataConversion::LongToString(m_pPP_HEAT->getNOHEATSEQ(1));
  //  }

  //  // read respective parameter
  //  // first find CasterID by ROUTECODE
  //  if ( m_pGT_PARAM_MATRIX->selectByPlant(PLANT, PLANTNO, "CasterNo",ProdPracPointer,7 /*string - string*/,ROUTECODE,CSMC_DBData::unspecString) )
  //  {
  //    std::string CASTERID = m_pGT_PARAM_MATRIX->getVALUE(1);
  //    if ( m_pGT_PARAM_MATRIX->selectByPlant(PLANT, PLANTNO, "Ca_Adaption",ProdPracPointer,9 /*long - long - double*/,CASTERID,NOHEATSEQ) )
  //    {
  //      CorrectionFactor = CDataConversion::StringToDouble( m_pGT_PARAM_MATRIX->getVALUE(1) );
  //    }
  //  }

  //  if ( CorrectionFactor != CSMC_DBData::unspecDouble )
  //  {
  //    ANL = ANL * CorrectionFactor;
  //    RetValue = true;
  //  }


  //}

  return RetValue;
}

bool CLFModelWrapper::sequence_set_ladle_data(const std::string& HeatID, const std::string& TreatID, const std::string& Plant)
{
  bool RetValue = false;

  std::string Function     = "CLFModelResultWrapper::sequence_set_ladle_data";
  std::stringstream ExceptionMsg;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF)
  {
    std::string LadleType;
    long LadleNo = -1;
    std::string TempStatus;

    try // common catch
    { 
      if (m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant))
      {
        if ( !m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::LADLENO, 1) &&
             !m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::LADLETYPE, 1) )
        {
          LadleType = m_pPD_HEAT_DATA->getLADLETYPE(1);
          LadleNo   = m_pPD_HEAT_DATA->getLADLENO(1);

          if (m_pPD_LADLE->select(LadleNo, LadleType)) 
          {
            TempStatus = m_pPD_LADLE->getTHERMALSTATUS(1);
          }
      
          pIntfLF->setTapLadleId( LadleType + CDataConversion::LongToString(LadleNo) );              


          // setTapLadleTempLossStat(LadleStatus : const string&)
          if (TempStatus == DEF_GC_THERM_STAT::H) 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::High);
          }
          else if (TempStatus == DEF_GC_THERM_STAT::C) 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::Low);
          }
          else 
          {
            pIntfLF->setTapLadleTempLossStat(CTempLossStat::Medium);
          }
          RetValue = true;
        }
        else
        {
          std::string SearchKey = "LADLENO and LADLETYPE";
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA");
        }
      }
      else
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA");
      }
    } 
    catch(cCBS_DBExc &e) 
    {
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        Function.c_str(), ExceptionMsg.str().c_str());
    
      CLFModelWrapper::handleDBConnectionError();
    } // db catch
    catch (...)
    {
      RetValue = false;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        Function.c_str(), std::string("Unknown exception").c_str());    
    } // common catch
  }
  else
  {
    handleError("CLFModelWrapper", "sequence_set_ladle_data(): pIntfLF = 0");
  }

  return RetValue;
}

long CLFModelWrapper::getProdPracticePointer(const std::string & HeatID, const std::string & TreatID, const std::string& Plant, const std::string & PracticeCode)
{
  long ProdPracPointer = CInv::InvalidLong;

  if (m_pPD_HEAT_DATA_PRODPRAC->select(HeatID,TreatID,Plant,PracticeCode)) 
  { 
    if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_MOD, 1))
    {
      ProdPracPointer = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"PRODPRACID_MOD");
    }
    else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull(CPD_HEAT_DATA_PRODPRAC::PRODPRACID_PLAN, 1))
    {
      ProdPracPointer = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(1);
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"PRODPRACID_PLAN");
    }
    else 
    {
      ProdPracPointer = (DEF_GC_PRODPRAC_DEF::Parameter == PracticeCode) ? 0 : 1; // for parameter set, the default is zero
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_UseOfProdPracPt(sMessage, PracticeCode.c_str(), ProdPracPointer,"default");
    }
  }
  else
  {
    std::string SearchKey = HeatID + " " + TreatID + PracticeCode;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_PRODPRAC");
  }
  return ProdPracPointer;
}

long CLFModelWrapper::getTreatmentModeNo(CEventMessage &Event)
{
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string OrderID   = Event.getOrderID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  return getTreatmentModeNo(HeatID,TreatID,ActPlant);

}


long CLFModelWrapper::getTreatmentModeNo(const std::string & HeatID, const std::string & TreatID, const std::string& Plant)
{
  long TreatmentModeNo = 0;

  return TreatmentModeNo;
}

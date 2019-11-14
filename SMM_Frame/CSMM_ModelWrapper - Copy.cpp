// Copyright (C) 2012 SMS Siemag AG

#include "iData_Provider_s.hh"
#include "cCBS_StdLog_Task.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"

#include "CPD_RECIPE.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_HEAT_DATA.h"

#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_SAMPLEMODE.h"

#include "CDataConversion.h"

#include "CSMM_ModelWrapper.h"

std::string CSMM_ModelWrapper::m_PrevSetpointsKey;

//##ModelId=4118A58E0087
bool CSMM_ModelWrapper::doResultCodeAndMessage(CEventMessage &Event)
{
  return true;
}

//##ModelId=4118A5E50032
bool CSMM_ModelWrapper::doMatRecipeSetpoints(CEventMessage &Event)
{
  return true;
}

//##ModelId=4118CA510240
bool CSMM_ModelWrapper::doModelResult(CEventMessage &Event)
{
  return true;
}

//##ModelId=4118CD7B037B
bool CSMM_ModelWrapper::doModelHeatStatus(CEventMessage &Event)
{
  return true;
}

//##ModelId=4119D91000CA
long CSMM_ModelWrapper::getTypeOfCalc()
{
  return (long)0;
}

//##ModelId=411A5D23034F
long CSMM_ModelWrapper::getHeatIdetificationData()
{
  return (long)0;
}

//##ModelId=411A5EB10279
long CSMM_ModelWrapper::ValidateEvent()
{
  return (long)0;
}

void CSMM_ModelWrapper::setpModelTask(CModelTask* pModelTask)
{
  m_pModelTask = pModelTask;
  initDBClasses();

  cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

  if (pConnection)
  {
    m_pGC_Plant_Container  = new CGC_Plant_Container(pConnection);
    m_pChem_Elem_Container = new CChem_Elem_Container(pConnection);
  }
}

CSMM_ModelWrapper::CSMM_ModelWrapper() :
m_pGC_Plant_Container(0),
m_pChem_Elem_Container(0)
{
   m_HeatPredCalcNo = 0;
   m_HeatCyclCalcNo = 0;
}

//##ModelId=4123A07000E8
CSMM_ModelWrapper::~CSMM_ModelWrapper()
{
  if (m_pGC_Plant_Container)  { delete m_pGC_Plant_Container ; m_pGC_Plant_Container = 0;}
  if (m_pChem_Elem_Container) { delete m_pChem_Elem_Container; m_pChem_Elem_Container = 0;}
}

//****** writes new calculated setpoints to DataBase ****************************************
bool CSMM_ModelWrapper::writeRecipeSetpointsToDB(CEventMessage& Event, const seqRecipeList &SeqRecipeList, double DurSinceHeatAnnounce, double DurSinceHeatStart)
{
  log("++++++ CSMM_ModelWrapper::writeRecipeSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CSMM_ModelWrapper::writeRecipeSetpointsToDB";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    if (m_pModelTask)
    {
      cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

      if (!pConnection)
      {
        m_pModelTask->handleDBConnectionError();

        if (!pConnection)
        {
          log(Function + " : database connection error, null pointer received",0);
          return false;
        }
      }// if (!checkDBConnection())

      //Required initialisation for database
      CPD_RECIPE              PD_RECIPE(pConnection);

      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      // main part
      //
      // Purge those rows having the batch status number of 0 and 90;
      //

      // remove entries only if BATCH is not yet used by L1 for Bin, Hand, Wire!      
      std::vector<std::string> SOURCE_LIST;
      SOURCE_LIST.push_back(DEF_GC_RECIPE_SOURCE::Bin);
      SOURCE_LIST.push_back(DEF_GC_RECIPE_SOURCE::Hand);
      SOURCE_LIST.push_back(DEF_GC_RECIPE_SOURCE::Wire);

      if ( PD_RECIPE.selectNotUsedRecipes(HeatId, TreatId, ActPlant, CSMC_DBData::unspecString, CSMC_DBData::unspecLong, SOURCE_LIST) )
      {
        // does not perform commit !
        if ( PD_RECIPE.deleteRows() )
        {
          PD_RECIPE.commit();
        }
        else
        {
          PD_RECIPE.rollback();
        }
      }

      log(Event.getMessage(), 3);
      log(CIntfData::getContent(CIntfData::ToAny(SeqRecipeList)),4);

      // insert recipe for each recipe in SeqRecipeList
      for ( long i = 0 ; i < CIntfData::getLength(SeqRecipeList); ++i )
      {
        sRecipe Recipe;
        CIntfData::getAt(Recipe,SeqRecipeList,i);

        double MatFeedRate              = Recipe.MatFeedRate;
        double ChargeMoment             = Recipe.ChargeMoment;
        long RecipeNo_Model             = Recipe.RecipeNo_Model;
        long RecipeNo                   = Recipe.RecipeNo;
        std::string RecipeName          = Recipe.RecipeName;
        std::string RecipeSource        = Recipe.RecipeSource;
        std::string RecipeName_Model    = Recipe.RecipeName_Model;

        seqBatchPrio RecipeContent      = Recipe.RecipeContent;
        sMetTimeStamp MetTimeStamp      = Recipe.TimeStamp;
        sProductIdentification Product  = Recipe.Product;
        sRecipeProperties RecipeData    = Recipe.RecipeData;

        sRecipeInfo SRecipeInfo;

        //SRecipeInfo.DurSinceHeatAnnounce = MetTimeStamp.DurSinceHeatAnnouncement;
        //SRecipeInfo.DurSinceHeatStart    = MetTimeStamp.DurSinceStartOfHeat;
        SRecipeInfo.DurSinceHeatAnnounce = DurSinceHeatAnnounce;
        SRecipeInfo.DurSinceHeatStart    = DurSinceHeatStart;
        SRecipeInfo.RecipeName           = RecipeName;
        SRecipeInfo.RecipeNo             = RecipeNo;
        SRecipeInfo.RecipeSource         = RecipeSource;
        SRecipeInfo.RecipeStatus         = DEF_GC_RECIPE_STATUS::Calculated;
        SRecipeInfo.RecipeTarget         = "";
        SRecipeInfo.ChargeMoment         = ChargeMoment;


        MetTimeStamp.DurSinceHeatAnnouncement = DurSinceHeatAnnounce;
        MetTimeStamp.DurSinceHeatAnnouncement = DurSinceHeatStart;

        // write calculated data   
        RetValue = PD_RECIPE.writeBatchPrio(HeatId,TreatId,ActPlant,SRecipeInfo,MetTimeStamp,RecipeContent, true, m_lastError);
        // performs commit !

        if(!RetValue)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"HEATId - TREATId", "PD_RECIPE", Function.c_str());
        }
      }
    }//if (m_pModelTask)
    else 
    {
      if (!m_pModelTask)
      {
        RetValue = false;
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    m_pModelTask->handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

//****** updates new calculated setpoints to DataBase ****************************************
bool CSMM_ModelWrapper::updateRecipeSetpointsToDB(CEventMessage& Event, const seqRecipeList &SeqRecipeList)
{
  log("++++++ CSMM_ModelWrapper::updateRecipeSetpointsToDB",3);
  bool RetValue = false;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CSMM_ModelWrapper::updateRecipeSetpointsToDB";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    if (m_pModelTask)
    {
      cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

      if (!pConnection)
      {
        m_pModelTask->handleDBConnectionError();

        if (!pConnection)
        {
          log(Function + " : database connection error, null pointer received",0);
          return false;
        }
      }// if (!checkDBConnection())

      //Required initialisation for database
      CPD_RECIPE              PD_RECIPE(pConnection);

      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      // main part
      //
      // Purge those rows having the batch status number of 0 and 90;
      //

      log(Event.getMessage(), 3);
      log(CIntfData::getContent(CIntfData::ToAny(SeqRecipeList)),4);

      // insert recipe for each recipe in SeqRecipeList
      for ( long i = 0 ; i < CIntfData::getLength(SeqRecipeList); ++i )
      {
        sRecipe Recipe;
        CIntfData::getAt(Recipe,SeqRecipeList,i);

        double ChargeMoment             = Recipe.ChargeMoment;
        long RecipeNo                   = Recipe.RecipeNo;
        std::string RecipeName          = Recipe.RecipeName;
        std::string RecipeSource        = Recipe.RecipeSource;
        long RecipeStatus               = Recipe.RecipeData.RecipeStatus;

        sRecipeInfo SRecipeInfo;

        SRecipeInfo.DurSinceHeatAnnounce = 0.0;
        SRecipeInfo.DurSinceHeatStart    = 0.0;
        SRecipeInfo.RecipeName           = RecipeName;
        SRecipeInfo.RecipeNo             = RecipeNo;
        SRecipeInfo.RecipeSource         = RecipeSource;
        SRecipeInfo.RecipeStatus         = RecipeStatus;
        SRecipeInfo.ChargeMoment         = ChargeMoment;

        // performs commit !
        RetValue = PD_RECIPE.updateChargeMoment(HeatId, TreatId, ActPlant, SRecipeInfo, true, m_lastError);

        if(!RetValue)
        {
          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,std::string("HEATID - TREATID - " + SRecipeInfo.RecipeName).c_str(), "PD_RECIPE", Function.c_str());
        }
      }
    }//if (m_pModelTask)
    else 
    {
      if (!m_pModelTask)
      {
        RetValue = false;
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    m_pModelTask->handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

bool CSMM_ModelWrapper::checkDBConnection()
{
  return true;
}

cCBS_StdConnection * CSMM_ModelWrapper::getStdConnection()
{
  cCBS_StdConnection *pConnection = 0;

  if ( m_pModelTask )
  {
    pConnection = m_pModelTask->getStdConnection();
  }

  return pConnection;
}

bool CSMM_ModelWrapper::writeCalculatedAnalysis(CEventMessage& Event, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool Commit)
{
  log("++++++ CSMM_ModelWrapper::writeCalculatedAnalysis",3);
  bool RetValue = true;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CSMM_ModelWrapper::writeCalculatedAnalysis";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    if ( m_pModelTask
      && m_pChem_Elem_Container )
    {
      cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

      if (!pConnection)
      {
        m_pModelTask->handleDBConnectionError();

        if (!pConnection)
        {
          log(Function + " : database connection error, null pointer received",0);
          return false;
        }
      }// if (!checkDBConnection())

      CPD_SAMPLE           PD_SAMPLE(pConnection);
      CPD_SAMPLE_REF       PD_SAMPLE_REF(pConnection);

      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      seqAnalysis SeqAnalysisSteel;
      seqAnalysis SeqAnalysisSlag;

      seqSample   SeqSample;
      sSample     Sample;

      CDateTime Now;

      std::string UserCode = "Model";

      for( long i = 0; i < CIntfData::getLength(SeqAnalysis); ++i )
      {
        sAnalysis Analysis;
        CIntfData::getAt(Analysis,SeqAnalysis,i);

        if ( m_pChem_Elem_Container->isSteelElem(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSteel,Analysis);
        }
        if ( m_pChem_Elem_Container->isEquivalence(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSteel,Analysis);
        }
        if ( m_pChem_Elem_Container->isSlagElem(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSlag,Analysis);
        }
      }

      if( 0 < CIntfData::getLength(SeqAnalysisSteel) )
      {
        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated Steel analysis
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getSTEEL_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertAnalysis(HeatId, TreatId, ActPlant, ActPlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Steel, CSMC_DBData::unspecLong,
                              SeqAnalysisSteel, false, m_lastError);

            long SampleUseable = CSMC_DBData::unspecLong;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setSTEEL_CALC(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSteel, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if( 0 < CIntfData::getLength(SeqAnalysisSlag) )
      {
        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated Slag analysis
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getSLAG_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertAnalysis(HeatId, TreatId, ActPlant, ActPlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Slag, CSMC_DBData::unspecLong,
                              SeqAnalysisSlag,false,m_lastError);

            long SampleUseable = CSMC_DBData::unspecLong;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setSLAG_CALC(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSlag, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if ( Temp != DEF::Inv_Double )
      {
        Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Temp.c_str();
        /*"Temp_Calc"*/
        Sample.MeasValue = CDataConversion::RoundToDecimals(Temp);  

        CIntfData::insert(SeqSample,Sample);

        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated temp
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getTEMP_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertSample(HeatId, TreatId, ActPlant, ActPlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Temp, CSMC_DBData::unspecLong, 
                              SeqSample, false, m_lastError);

            long SampleUseable = CSMC_DBData::unspecLong;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setTEMP_CALC(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateSample(SAMPLE_COUNTER, SeqSample, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      }

      if ( Commit )
      {
        if ( RetValue )
        {
          PD_SAMPLE_REF.commit();
        }
        else
        {
          PD_SAMPLE_REF.rollback();
        }
      }
    }
    else 
    {
      RetValue = false;
      if ( !m_pModelTask )
      {
        log( "Error: m_pModelTask is invalid!", 1 );
      }
      if ( !m_pChem_Elem_Container )
      {
        log( "Error: m_pChem_Elem_Container is invalid!", 1 );
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    m_pModelTask->handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

bool CSMM_ModelWrapper::writeFinalCalculatedAnalysis(CEventMessage& Event, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool Commit)
{
  log("++++++ CSMM_ModelWrapper::writeFinalCalculatedAnalysis",3);
  bool RetValue = true;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CSMM_ModelWrapper::writeFinalCalculatedAnalysis";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    // We only return true for successfull task so that all other task called by caller are also executed
    RetValue = true;

    if ( m_pModelTask
      && m_pChem_Elem_Container )
    {
      cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

      if (!pConnection)
      {
        m_pModelTask->handleDBConnectionError();

        if (!pConnection)
        {
          log(Function + " : database connection error, null pointer received",0);
          return false;
        }
      }// if (!checkDBConnection())

      CPD_SAMPLE           PD_SAMPLE(pConnection);
      CPD_SAMPLE_REF       PD_SAMPLE_REF(pConnection);

      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);

      seqAnalysis SeqAnalysisSteel;
      seqAnalysis SeqAnalysisSlag;

      seqSample   SeqSample;
      sSample     Sample;

      CDateTime Now;

      std::string UserCode = "Model";

      for( long i = 0; i < CIntfData::getLength(SeqAnalysis); ++i )
      {
        sAnalysis Analysis;
        CIntfData::getAt(Analysis,SeqAnalysis,i);

        if ( m_pChem_Elem_Container->isSteelElem(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSteel,Analysis);
        }
        if ( m_pChem_Elem_Container->isEquivalence(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSteel,Analysis);
        }
        if ( m_pChem_Elem_Container->isSlagElem(std::string(Analysis.Element)) )
        {
          CIntfData::insert(SeqAnalysisSlag,Analysis);
        }
      }

      if( 0 < CIntfData::getLength(SeqAnalysisSteel) )
      {
        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated Steel analysis
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getSTEEL_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertAnalysis(HeatId, TreatId, ActPlant, ActPlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Steel, CSMC_DBData::unspecLong,
                              SeqAnalysisSteel, false, m_lastError);

            long SampleUseable = 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setSTEEL_CALC_FINAL(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSteel, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if( 0 < CIntfData::getLength(SeqAnalysisSlag) )
      {
        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated Slag analysis
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getSLAG_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertAnalysis(HeatId, TreatId, ActPlant, ActPlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Slag, CSMC_DBData::unspecLong,
                              SeqAnalysisSlag,false,m_lastError);

            long SampleUseable = 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setSLAG_CALC_FINAL(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSlag, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if ( Temp != DEF::Inv_Double )
      {
        Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Temp.c_str();
        /*"Temp_Calc"*/
        Sample.MeasValue = CDataConversion::RoundToDecimals(Temp);  

        CIntfData::insert(SeqSample,Sample);

        if ( PD_SAMPLE_REF.select(SampleRef) )
        {
          // handle calculated temp
          long SAMPLE_COUNTER = PD_SAMPLE_REF.getTEMP_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            SAMPLE_COUNTER = PD_SAMPLE.insertSample(HeatId, TreatId, ActPlant, ActPlantNo,
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Temp, CSMC_DBData::unspecLong, 
                              SeqSample, false, m_lastError);

            long SampleUseable = 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              PD_SAMPLE.updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUseable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              PD_SAMPLE_REF.setTEMP_CALC_FINAL(SAMPLE_COUNTER);
              PD_SAMPLE_REF.setREVTIME(Now);
              RetValue = RetValue && PD_SAMPLE_REF.update();
            }
          }
          else
          {
            PD_SAMPLE.setSAMPLETIME(Now);
            RetValue = RetValue && PD_SAMPLE.updateSample(SAMPLE_COUNTER, SeqSample, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && PD_SAMPLE_REF.select(SampleRef) )
      }

      if ( Commit )
      {
        if ( RetValue )
        {
          PD_SAMPLE_REF.commit();
        }
        else
        {
          PD_SAMPLE_REF.rollback();
        }
      }
    }
    else 
    {
      RetValue = false;
      if ( !m_pModelTask )
      {
        log( "Error: m_pModelTask is invalid!", 1 );
      }
      if ( !m_pChem_Elem_Container )
      {
        log( "Error: m_pChem_Elem_Container is invalid!", 1 );
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    m_pModelTask->handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

bool CSMM_ModelWrapper::writeCalculatedWeightsAndTemp(CEventMessage& Event, double SteelWeightCalc, double SlagWeightCalc, double TempCalc, bool Commit)
{
  log("++++++ CSMM_ModelWrapper::writeCalculatedWeightsAndTemp",3);
  bool RetValue = true;

  //------------ read the data from Event ------------------
  std::string HeatId    = Event.getHeatID();
  std::string TreatId   = Event.getTreatID(); 
  std::string ProductId = Event.getProductID();
  std::string OrderId   = Event.getOrderID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantId   = Event.getPlantID();

  std::string Function     = "CSMM_ModelWrapper::writeCalculatedWeightsAndTemp";
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getMessage() << " from " << Event.getSender()
    << ", " << ProductId << ", " << HeatId
    << ", " << TreatId   << ", " << DataKey;

  try
  {
    if ( m_pModelTask )
    {
      cCBS_StdConnection *pConnection = m_pModelTask->getStdConnection();

      if (!pConnection)
      {
        m_pModelTask->handleDBConnectionError();

        if (!pConnection)
        {
          log(Function + " : database connection error, null pointer received",0);
          return false;
        }
      }// if (!checkDBConnection())

      CPD_HEAT_DATA           PD_HEAT_DATA(pConnection);

      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantId);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantId);
      bool isUpdateRequired = false;

      if (PD_HEAT_DATA.select(HeatId, TreatId, ActPlant) )
      {
        // select data
        double SteelMassStart  = PD_HEAT_DATA.getSTEELMASS_START(1);
        double SlagMassStart   = PD_HEAT_DATA.getSLAGMASS_START(1);

        if ( SteelWeightCalc > 0. || SlagWeightCalc > 0. || TempCalc > 0 )
        {
          if ( SteelWeightCalc > 0. )
          {
            if ( SteelMassStart == CSMC_DBData::unspecDouble || SteelMassStart <= 0. )
            {
              PD_HEAT_DATA.setSTEELMASS_START( SteelWeightCalc );
            }

            PD_HEAT_DATA.setSTEELMASS( SteelWeightCalc );
            isUpdateRequired = true;
          }

          if ( SlagWeightCalc > 0. )
          {
            if ( SlagMassStart == CSMC_DBData::unspecDouble || SlagMassStart <= 0. )
            {
             PD_HEAT_DATA.setSLAGMASS_START( SlagWeightCalc );
            }

           PD_HEAT_DATA.setSLAGMASS( SlagWeightCalc );
            isUpdateRequired = true;
          }

          if ( TempCalc > 0 )
          {
           PD_HEAT_DATA.setFINALTEMP( CDataConversion::RoundToLong( TempCalc ) );
            isUpdateRequired = true;
          }
        } // if ( SteelWeightCalc > 0. || SlagWeightCalc > 0. || PredRes.GenRes.Temp > 0 )

        if ( isUpdateRequired )
        {
          RetValue = RetValue &&PD_HEAT_DATA.update();

          if (RetValue)
          {
            if ( Commit )
            {
             PD_HEAT_DATA.commit();
            }
          }
          else
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DBWriteError(sMessage,"STEELMASS SLAGMASS FINALTEMP","PD_HEAT_DATA","");

            if ( Commit )
            {
             PD_HEAT_DATA.rollback();
            }
          }
        } // if ( isUpdateRequired )
      } // if (PD_HEAT_DATA.select(HeatID, TreatID, ActPlant) )
    }
    else 
    {
      RetValue = false;
      if ( !m_pModelTask )
      {
        log( "Error: m_pModelTask is invalid!", 1 );
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Function.c_str(), ExceptionMsg.str().c_str());
    m_pModelTask->handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Function.c_str(), ExceptionMsg.str().c_str());    
  }
  catch(std::exception & e)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,e.what(),
      Function.c_str(), ExceptionMsg.str().c_str()); 
  }
  catch(...)
  {
    RetValue = false;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Function.c_str(), std::string("Unknown exception").c_str());    
  }

  return RetValue;
}

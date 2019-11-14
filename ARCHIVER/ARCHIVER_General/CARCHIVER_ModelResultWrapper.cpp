// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_NAME_SCOPE.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_SAMPLEMODE.h"
#include "DEF_GC_SAMPLEUSABLE.h"

#include "CGC_MEASUREMENT_NAME.h"
#include "CChem_Elem_Container.h"

#include "CDataConversion.h"

#include "CIntfData.h"
#include "CEventMessage.h"
#include "CARCHIVER_Task.h"
#include "CARCHIVER_ModelResultWrapper.h"

//##ModelId=45D5829901D4
CARCHIVER_ModelResultWrapper::CARCHIVER_ModelResultWrapper()
:m_pGC_MEASUREMENT_NAME(0)
,m_pChem_Elem_Container(0)
,m_pGC_PHASE(0)
,m_pGC_PHASE_RES_PLANT(0)
,m_pGC_Plant_Container(0)
,m_pGT_MAT(0)
,m_pGT_MAT_PURP(0)
,m_pPD_ACTION(0)
,m_pPD_HEAT_DATA(0)	
,m_pPD_MAT_FEED_RES(0)
,m_pPD_PHASE_RES(0)
,m_pPD_PHASE_RES_PLANT(0)
,m_pPD_PLANTSTATUS(0)
,m_pPD_RECIPE(0)
,m_pPD_RECIPE_ENTRY(0)
,m_pPD_SAMPLE(0)
,m_pPD_SAMPLE_REF(0)
{
}

//##ModelId=45D5829A003A
CARCHIVER_ModelResultWrapper::~CARCHIVER_ModelResultWrapper()
{
	deleteDBClasses();
}

//##ModelId=45D5829E025A
void CARCHIVER_ModelResultWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pGC_MEASUREMENT_NAME = new CGC_MEASUREMENT_NAME(pConnection);
  m_pChem_Elem_Container = new CChem_Elem_Container(pConnection);
  m_pGC_PHASE            = new CGC_PHASE(pConnection);
  m_pGC_PHASE_RES_PLANT  = new CGC_PHASE_RES_PLANT(pConnection);
  m_pGC_Plant_Container  = new CGC_Plant_Container(pConnection);

  m_pGT_MAT              = new CGT_MAT(pConnection);
  m_pGT_MAT_PURP         = new CGT_MAT_PURP(pConnection);

  m_pPD_ACTION           = new CPD_ACTION(pConnection);
  m_pPD_HEAT_DATA        = new CPD_HEAT_DATA(pConnection);	
  m_pPD_MAT_FEED_RES     = new CPD_MAT_FEED_RES(pConnection);
  m_pPD_PHASE_RES        = new CPD_PHASE_RES(pConnection);  
  m_pPD_PHASE_RES_PLANT  = new CPD_PHASE_RES_PLANT(pConnection);
  m_pPD_PLANTSTATUS      = new CPD_PLANTSTATUS(pConnection);
  m_pPD_RECIPE           = new CPD_RECIPE(pConnection);
  m_pPD_RECIPE_ENTRY     = new CPD_RECIPE_ENTRY(pConnection);
  m_pPD_SAMPLE           = new CPD_SAMPLE(pConnection);
  m_pPD_SAMPLE_REF       = new CPD_SAMPLE_REF(pConnection);
}

//##ModelId=45D5829F00FD
void CARCHIVER_ModelResultWrapper::deleteDBClasses()
{
  if (m_pGC_MEASUREMENT_NAME) {delete m_pGC_MEASUREMENT_NAME; m_pGC_MEASUREMENT_NAME = 0; }
  if (m_pChem_Elem_Container) {delete m_pChem_Elem_Container; m_pChem_Elem_Container = 0; }
  if (m_pGC_PHASE)            {delete m_pGC_PHASE; m_pGC_PHASE = 0; }
  if (m_pGC_PHASE_RES_PLANT)  {delete m_pGC_PHASE_RES_PLANT; m_pGC_PHASE_RES_PLANT = 0; }
  if (m_pGC_Plant_Container)  {delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
  if (m_pGT_MAT)              {delete m_pGT_MAT; m_pGT_MAT = 0; }
  if (m_pGT_MAT_PURP)         {delete m_pGT_MAT_PURP; m_pGT_MAT_PURP = 0;}
  if (m_pPD_ACTION)           {delete m_pPD_ACTION; m_pPD_ACTION = 0; }
  if (m_pPD_HEAT_DATA)        {delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
  if (m_pPD_MAT_FEED_RES)     {delete m_pPD_MAT_FEED_RES; m_pPD_MAT_FEED_RES = 0;}
  if (m_pPD_PHASE_RES)        {delete m_pPD_PHASE_RES; m_pPD_PHASE_RES = 0; }
  if (m_pPD_PHASE_RES_PLANT)  {delete m_pPD_PHASE_RES_PLANT; m_pPD_PHASE_RES_PLANT = 0; }
  if (m_pPD_PLANTSTATUS)      {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0; }
  if (m_pPD_RECIPE)           {delete m_pPD_RECIPE; m_pPD_RECIPE = 0; }
  if (m_pPD_RECIPE_ENTRY)     {delete m_pPD_RECIPE_ENTRY; m_pPD_RECIPE_ENTRY = 0; }
  if (m_pPD_SAMPLE)           {delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0; }
  if (m_pPD_SAMPLE_REF)       {delete m_pPD_SAMPLE_REF; m_pPD_SAMPLE_REF = 0; }
}


//##ModelId=45D582D5013A
bool CARCHIVER_ModelResultWrapper::handleGenParameterUpdate(CEventMessage& Event)
{
	log("WARNING: CARCHIVER_ModelResultWrapper::handleGenParameterUpdate: Not implemented!",3);
	return false;
}

//##ModelId=45D582D50158
bool CARCHIVER_ModelResultWrapper::handleRecipeSetpoints(CEventMessage& Event, seqRecipeList& SeqRecipeList)
{
	bool RetValue = false;

	std::string ProductID = Event.getProductID();
	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
	std::string DataKey   = Event.getDataKey();
	std::string PlantID   = Event.getPlantID();
	std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
	std::string OrderID   = Event.getOrderID();

	// Unified exception handling *******************************************************
	std::string Scope("CARCHIVER_ModelResultWrapper::handleRecipeSetpoints");
	std::stringstream ExceptionMsg;
	ExceptionMsg << "Handling event: " << Event.getSender()
		<< ", " << ProductID << ", " << HeatID
		<< ", " << TreatID   << ", " << DataKey
		<< Scope << std::endl;
	//***********************************************************************************

	try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if (!m_pDM_Interface)
    {
      log("setpDM_Interface(Event.getSender(),DM::PRODUCT) failed", 0);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PLANT);
    double ElecCons     = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceHeatAnnounce     = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart        = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

    //
    // Purge those rows having the batch status number of 0 and 90;
    //

    // remove entries only if BATCH is not yet used by L1 !      
    if ( m_pPD_RECIPE->selectNotUsedRecipes(HeatID, TreatID, ActPlant, CSMC_DBData::unspecString, CSMC_DBData::unspecLong, DEF_GC_RECIPE_SOURCE::Bin) )
    {
      // does not perform commit !
      m_pPD_RECIPE->deleteRows();
    }

    log(Event.getMessage(),4);
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

      MetTimeStamp.DurSinceHeatAnnouncement = DurSinceHeatAnnounce;
      MetTimeStamp.DurSinceHeatAnnouncement = DurSinceHeatStart;
      MetTimeStamp.Elec_Moment              = CDataConversion::SetInvalidToDefault(ElecCons,DEF::Inv_Double);

      // write calculated data   
      RetValue = m_pPD_RECIPE->writeBatchPrio(HeatID,TreatID,ActPlant,SRecipeInfo,MetTimeStamp,RecipeContent, true, m_lastError);
      // performs commit !

      if(!RetValue)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_RECIPE", m_pPD_RECIPE->getActStatement().c_str());

        m_pPD_RECIPE->logLastError(1);
      }
    }
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}


long CARCHIVER_ModelResultWrapper::getResPhaseNo(std::string PhaseName, long PhaseNo , std::string Plant)
{
	long RetValue = CSMC_DBData::unspecLong;

	if ( m_pGC_PHASE && m_pGC_PHASE->selectByPhase(Plant, PhaseName, PhaseNo,CSMC_DBData::unspecLong) )
	{
		RetValue = m_pGC_PHASE->getRES_PHASENO(1);
	}

	return RetValue;
}


double CARCHIVER_ModelResultWrapper::getDurUntEndOfPhase(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long ResPhaseNo)
{
	double RetValue = CSMC_DBData::unspecDouble;

	if ( m_pPD_PHASE_RES && m_pPD_PHASE_RES->select(HeatID,TreatID,Plant,ResPhaseNo) )
	{
		RetValue = m_pPD_PHASE_RES->getDURUNTENDOFPHASE(1);
	}

	return RetValue;
}


double CARCHIVER_ModelResultWrapper::getDurUntEndOfPhase(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, const std::string & PhaseName, long PhaseNo)
{
	double RetValue = CSMC_DBData::unspecDouble;
	long ResPhaseNo = getResPhaseNo(PhaseName, PhaseNo ,Plant);

	if ( ResPhaseNo != CSMC_DBData::unspecDouble )
	{
		RetValue = getDurUntEndOfPhase(HeatID, TreatID, Plant, ResPhaseNo);
	}

	return RetValue;
}


double CARCHIVER_ModelResultWrapper::getPhaseDuration(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, const std::string & PhaseName, long PhaseNo, const std::string & PrevPhaseName /*= CSMC_DBData::unspecString*/, long PrevPhaseNo /*= CSMC_DBData::unspecLong*/)
{
	double RetValue   = 0.0;
	double PhaseStart = 0.0;
	double PhaseEnd   = 0.0;

	// this seems to be a phase lenght difference !
	if ( PrevPhaseName != CSMC_DBData::unspecString )
	{
		PhaseStart = getDurUntEndOfPhase(HeatID, TreatID, Plant, PrevPhaseName, PrevPhaseNo);
	}

	PhaseEnd = getDurUntEndOfPhase(HeatID, TreatID, Plant, PhaseName, PhaseNo);

	if ( PhaseStart != CSMC_DBData::unspecDouble && 
		PhaseEnd != CSMC_DBData::unspecDouble )
	{
		RetValue = max( PhaseEnd - PhaseStart , 0.0 );
	}



	return RetValue;
}

double CARCHIVER_ModelResultWrapper::getPhaseDuration(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long ResPhaseNo, long PrevResPhaseNo /*= CSMC_DBData::unspecLong*/)
{
	double RetValue   = 0.0;
	double PhaseStart = 0.0;
	double PhaseEnd   = 0.0;

	// this seems to be a phase lenght difference !
	if ( PrevResPhaseNo != CSMC_DBData::unspecLong )
	{
		PhaseStart = getDurUntEndOfPhase(HeatID, TreatID, Plant, PrevResPhaseNo);
	}

	PhaseEnd = getDurUntEndOfPhase(HeatID, TreatID, Plant, ResPhaseNo);

	if ( PhaseStart != CSMC_DBData::unspecDouble && 
		PhaseEnd != CSMC_DBData::unspecDouble )
	{
		RetValue = max( PhaseEnd - PhaseStart , 0.0 );
	}



	return RetValue;
}


bool CARCHIVER_ModelResultWrapper::writeCalculatedAnalysis(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long PlantNo, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool commit)
{
	bool RetValue = true;

	// Unified exception handling *******************************************************
	std::string Scope("CARCHIVER_ModelResultWrapper::writeCalculatedAnalysis");
	std::stringstream ExceptionMsg;
	ExceptionMsg << Scope << std::endl;
	//***********************************************************************************

	try
	{
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }
 
    if ( m_pPD_SAMPLE && m_pPD_SAMPLE_REF && m_pChem_Elem_Container)
    {
      seqAnalysis SeqAnalysisSteel;
      seqAnalysis SeqAnalysisSlag;

      seqSample   SeqSample;
      sSample     Sample;

      CDateTime Now;

      std::string UserCode = "Model";

      // update container because Eyuivalences can be added dynamically
      m_pChem_Elem_Container->init();

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
        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated Steel analysis
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSTEEL_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Steel, CSMC_DBData::unspecLong,
                              SeqAnalysisSteel, false, m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::notusable; // 0;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setSTEEL_CALC(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSteel, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if( 0 < CIntfData::getLength(SeqAnalysisSlag) )
      {
        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated Slag analysis
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSLAG_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Slag, CSMC_DBData::unspecLong,
                              SeqAnalysisSlag,false,m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::notusable; // 0;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setSLAG_CALC(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSlag, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if ( Temp != DEF::Inv_Double )
      {
        Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Temp.c_str();
        /*"Temp_Calc"*/
        Sample.MeasValue = CDataConversion::RoundToDecimals(Temp);  

        CIntfData::insert(SeqSample,Sample);

        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated temp
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getTEMP_CALC(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertSample(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Temp, CSMC_DBData::unspecLong, 
                              SeqSample, false, m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::notusable; // 0;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setTEMP_CALC(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateSample(SAMPLE_COUNTER, SeqSample, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      }

      if ( commit )
      {
        if ( RetValue )
        {
          m_pPD_SAMPLE_REF->commit();
        }
        else
        {
          m_pPD_SAMPLE_REF->rollback();
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"","PD_SAMPLE_REF","update failed!");
        }
      }
    } // if ( m_pPD_SAMPLE && m_pPD_SAMPLE_REF )
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

bool CARCHIVER_ModelResultWrapper::writeFinalCalculatedAnalysis(const std::string & HeatID, const std::string & TreatID, const std::string & Plant, long PlantNo, long SampleRef, seqAnalysis& SeqAnalysis, double Temp, bool commit)
{
	bool RetValue = true;

	// Unified exception handling *******************************************************
	std::string Scope("CARCHIVER_ModelResultWrapper::writeFinalCalculatedAnalysis");
	std::stringstream ExceptionMsg;
	ExceptionMsg << Scope << std::endl;
	//***********************************************************************************

	try
	{
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }
 
    if ( m_pPD_SAMPLE && m_pPD_SAMPLE_REF && m_pChem_Elem_Container)
    {
      seqAnalysis SeqAnalysisSteel;
      seqAnalysis SeqAnalysisSlag;

      seqSample   SeqSample;
      sSample     Sample;

      CDateTime Now;

      std::string UserCode = "Model";

      // update container because Eyuivalences can be added dynamically
      m_pChem_Elem_Container->init();

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
        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated Steel analysis
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSTEEL_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Steel, CSMC_DBData::unspecLong,
                              SeqAnalysisSteel, false, m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithoutsampletaken; // 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setSTEEL_CALC_FINAL(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSteel, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if( 0 < CIntfData::getLength(SeqAnalysisSlag) )
      {
        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated Slag analysis
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getSLAG_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Slag, CSMC_DBData::unspecLong,
                              SeqAnalysisSlag,false,m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithoutsampletaken; // 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setSLAG_CALC_FINAL(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateAnalysis(SAMPLE_COUNTER, SeqAnalysisSlag, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      } // if( 0 < CIntfData::getLength(SeqAnalysisSteel) )

      if ( Temp != DEF::Inv_Double )
      {
        Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Temp.c_str();
        /*"Temp_Calc"*/
        Sample.MeasValue = CDataConversion::RoundToDecimals(Temp);  

        CIntfData::insert(SeqSample,Sample);

        if ( m_pPD_SAMPLE_REF->select(SampleRef) )
        {
          // handle calculated temp
          long SAMPLE_COUNTER = m_pPD_SAMPLE_REF->getTEMP_CALC_FINAL(1);

          if ( SAMPLE_COUNTER == CSMC_DBData::unspecLong )
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            SAMPLE_COUNTER = m_pPD_SAMPLE->insertSample(HeatID, TreatID, Plant, PlantNo, 
                              DEF_GC_MEASUREMENT_ORIGIN::Calculated, DEF_GC_MEASUREMENT_TYPE::Temp, CSMC_DBData::unspecLong, 
                              SeqSample, false, m_lastError);

            long SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithoutsampletaken; // 2;

            if ( SAMPLE_COUNTER != CSMC_DBData::unspecLong )
            {
              m_pPD_SAMPLE->updateSampleDetails(SAMPLE_COUNTER, CSMC_DBData::unspecString, DEF_GC_SAMPLEMODE::automatic, CSMC_DBData::unspecString,
                                                SampleUsable, UserCode, CSMC_DBData::unspecString, DEF_GC_MEASUREMENT_ORIGIN::Calculated);

              m_pPD_SAMPLE_REF->setTEMP_CALC_FINAL(SAMPLE_COUNTER);
              m_pPD_SAMPLE_REF->setREVTIME(Now);
              RetValue = m_pPD_SAMPLE_REF->update();
            }
          }
          else
          {
            m_pPD_SAMPLE->setSAMPLETIME(Now);
            RetValue = m_pPD_SAMPLE->updateSample(SAMPLE_COUNTER, SeqSample, false, m_lastError);
          }
        } // if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_SAMPLE_REF->select(SampleRef) )
      }

      if ( commit )
      {
        if ( RetValue )
        {
          m_pPD_SAMPLE_REF->commit();
        }
        else
        {
          m_pPD_SAMPLE_REF->rollback();
        }
      }
    } // if ( m_pPD_SAMPLE && m_pPD_SAMPLE_REF )
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

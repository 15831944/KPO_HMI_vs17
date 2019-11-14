// Copyright (C) 2004 SMS Demag AG

//#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CEAFModelWrapper.h"

#include "CIntfData.h"
#include "CInv.h"
#include "CRS.h"

#include "CGC_RECIPE_L1.h"

#include "CEAFSolidMaterialHandlingWrapper.h"


//##ModelId=4152C08B01E1
bool CEAFSolidMaterialHandlingWrapper::doOnChangedMatSetPointsOperator( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnChangedMatSetPointsOperator()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!pIntfEAF ) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try
	{
		string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));

		long RecipeNo = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
													 Event.getDataKey().c_str(), DATA::RecipeNo);

		string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));

		seqBatch Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
											 Event.getDataKey().c_str(), DATA::RecipeContent));

		long SeqLength = CIntfData::getLength(Batch);
		if ( SeqLength == 0)  return false;

  
		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
		    if ( isCombiRecipe(RecipeNameModel) ) 
        {
          Source.clear();
        }

		    pIntfEAF->indicateChgRecipeOrigSetPt(RecipeNameModel,RecipeNoModel, Source);

		    // repeat for all setpoints Changed by operator
		    long      GetAtValue;
		    sBatch    MatData;
		    for (int x = 0; x < SeqLength; ++x) 
		    {
			    GetAtValue    = CIntfData::getAt(MatData, Batch, x);
			    string Code   = MatData.MatCode;
			    pIntfEAF->setMatSetPt(Code, MatData.Mass);
		    }

		    pIntfEAF->hndlEvent() ;

		    // Sequence Diagram: get model results / Call Sequence
		    RetValue = doModelResult(Event);
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
      }
    } 
	}
	catch (...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(),  "" );    
	}


	return RetValue;
}

//##ModelId=4152C08E01AA
bool CEAFSolidMaterialHandlingWrapper::doOnDisableSourceRecipe( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnDisableSourceRecipe()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try
	{  
		string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));
		string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));
		long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
											 Event.getDataKey().c_str(), DATA::RecipeNo);


		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
		    // check whether it is a combi-recipe, which by definition does not have recipe sources.
		    // a combi-recipe must have a Dollar-character as the first letter.
		    if ( isCombiRecipe(RecipeNameModel) ) 
        {
          Source.clear();
        }

		    RetValue = ( CRS::OK == pIntfEAF->hndlDisableRecipe(RecipeNameModel, RecipeNoModel, Source) );

		    // Sequence Diagram: get model results / Call Sequence
		    RetValue &= doModelResult(Event);;
      }
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    } 

	}
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "",Scope.c_str(), "" ); 
	}

	return RetValue;
}

//##ModelId=4152C0900289
bool CEAFSolidMaterialHandlingWrapper::doOnEnableSourceRecipe( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnEnableSourceRecipe()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try 
	{
	  string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));
	  string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));
	  long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
											 Event.getDataKey().c_str(), DATA::RecipeNo);

	  // repeat for all setpoints enabled by operator
	  seqBatch Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
											 Event.getDataKey().c_str(), DATA::RecipeContent));

	  long SeqLength = CIntfData::getLength(Batch);
	  if ( SeqLength == 0) return false;	 
	  
		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
	      // check whether it is a combi-recipe, which by definition does not have recipe sources.
	      // a combi-recipe must have a Dollar-character as the first letter.
	      if ( isCombiRecipe(RecipeNameModel) ) 
        {
          Source.clear();
        }
	  
	      long RetCode = pIntfEAF->indicateEnableRecipeOrig(RecipeNameModel, RecipeNoModel, Source);

	      long      GetAtValue;
	      sBatch    MatData;
	      for (int x = 0; x < SeqLength; ++x) 
	      {
		      GetAtValue    = CIntfData::getAt(MatData, Batch, x);
		      string Code   = MatData.MatCode;		
		      pIntfEAF->setMatSetPt(Code, MatData.Mass);
	      }

	      RetValue = ( CRS::OK == pIntfEAF->hndlEvent() );

	      // Sequence Diagram: get model results / Call Sequence
	      RetValue &= doModelResult(Event);;
      }
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    }

	}
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), "" );    
	}

	return RetValue;	
}

//##ModelId=4152C09402E9
bool CEAFSolidMaterialHandlingWrapper::doOnRecipeMaterialCharged( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnRecipeMaterialCharged()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try 
	{
		string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));
		string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));
		long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
											 Event.getDataKey().c_str(), DATA::RecipeNo);

		seqBatch Batch    = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
											 Event.getDataKey().c_str(), DATA::RecipeContent));

		long      SeqLength = CIntfData::getLength(Batch);
		if(SeqLength < 1) return false;

		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {

		    // check whether it is a combi-recipe, which by definition does not have recipe sources.
		    // a combi-recipe must have a Dollar-character as the first letter.
		    if ( isCombiRecipe(RecipeNameModel) )
        {
          Source.clear();
        }

		    long      GetAtValue;
		    sBatch    MatData;

		    for (int x = 0; x < SeqLength; ++x) 
		    {
			      GetAtValue    = CIntfData::getAt(MatData, Batch, x);
			      string Code   = MatData.MatCode;
			      pIntfEAF->hndlRecipeOrigMatChg(RecipeNameModel, RecipeNoModel, Source, Code, MatData.Mass);
		    }
	
		    RetValue = doModelResult(Event);
      }
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    }

	}
	catch (...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(),  ""  ); 
	}


	return RetValue;
}

//##ModelId=4152C0970134
bool CEAFSolidMaterialHandlingWrapper::doOnRecipeMaterialDischarged( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnRecipeMaterialDischarged()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try
	{
		string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));
		string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));
		string Loc        = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeTarget));
		long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
											 Event.getDataKey().c_str(), DATA::RecipeNo);

		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
		    // check whether it is a combi-recipe, which by definition does not have recipe sources.
		    // a combi-recipe must have a Dollar-character as the first letter.
		    if ( isCombiRecipe(RecipeNameModel) )
        {
          Source.clear();
        }

		    RetValue = ( CRS::OK == pIntfEAF->hndlRecipeOrigMatDischg(RecipeNameModel, RecipeNoModel, Source, Loc) );

		    // Sequence Diagram: get model results / Call Sequence
		    RetValue = RetValue && doModelResult(Event);
      }
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    }

	}
	catch (...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), "" ); 
	}


	return RetValue;
}

//##ModelId=4152C098037D
bool CEAFSolidMaterialHandlingWrapper::doOnRecipeWeighingComplete( CEventMessage &Event )
{
	bool RetValue = false;

  std::string Scope = "CEAFSolidMaterialHandlingWrapper::doOnRecipeWeighingComplete()" ;

	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

	std::string HeatID    = Event.getHeatID();
	std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

	try
	{
		string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeName));
		string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
											 Event.getDataKey().c_str(), DATA::RecipeSource));
		long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
											 Event.getDataKey().c_str(), DATA::RecipeNo);

	  
		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      if ( isValidModelRecipeName(RecipeNameModel) )
      {
		    // check whether it is a combi-recipe, which by definition does not have recipe sources.
		    // a combi-recipe must have a Dollar-character as the first letter.
		    if ( isCombiRecipe(RecipeNameModel) )
        {
          Source.clear();
        }

		    RetValue = ( CRS::OK == pIntfEAF->hndlRecipeWeighingComplete(RecipeNameModel, RecipeNoModel, Source) );

		    // Sequence Diagram: get model results / Call Sequence
		    RetValue &= doModelResult(Event);
      }
    } 
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Scope.c_str());
    }

	}
	catch (...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "",Scope.c_str(), "" ); 
	}


	return RetValue;
}



//##ModelId=416CF2820285
bool CEAFSolidMaterialHandlingWrapper::doOnRecipeWeighingCompleteUpdate(CEventMessage& Event)
{
	// TODO: Add your specialized code here.
	return (bool)0;
}

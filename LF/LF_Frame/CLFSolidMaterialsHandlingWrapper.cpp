// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CIntfData.h"
#include "CIntfLF.h"
#include "CDataConversion.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CRecipeCodesLF.h"
//mrut
#include "DEF_GC_RECIPE_STATUS.h"
#include "CGC_RECIPE_L1.h"
#include "CRS.h"

#include "CLFModelTask.h"
#include "CLFSolidMaterialsHandlingWrapper.h"

//##ModelId=41111A2302FB
bool CLFSolidMaterialsHandlingWrapper::doOnWireFeedingEnd(CEventMessage& Event)
{
  bool RetValue = false;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnWireFeedingEnd(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    seqWireFeeder  FeederData   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getWireFeeder(Event.getDataKey().c_str(), DATA::WireFeederData));
    long           SeqLength    = 0;
    long           GetAtValue   = 0;
    sWireFeeder    MatData;

    SeqLength = CIntfData::getLength(FeederData);
    for (int x = 0; x < SeqLength; x++) 
    {
      GetAtValue    = CIntfData::getAt(MatData, FeederData, x);
      string Code   = MatData.WireFeederMatCode;

      pIntfLF->hndlWireFeederEnd(Code, MatData.WireFeederAmount);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFSolidMaterialHandlingWrapper::doOnWireFeedingEnd()",  "" );    
  }

  return RetValue;
}

//##ModelId=41111AA6024F
bool CLFSolidMaterialsHandlingWrapper::doOnWireFeedingStart(CEventMessage& Event)
{
  bool RetValue = false;
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnWireFeedingStart(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    seqWireFeeder  FeederData   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getWireFeeder(Event.getDataKey().c_str(), DATA::WireFeederData));
    long           SeqLength    = 0;
    long           GetAtValue   = 0;
    sWireFeeder    MatData;

    SeqLength = CIntfData::getLength(FeederData);
    for (int x = 0; x < SeqLength; x++) 
    {
      GetAtValue    = CIntfData::getAt(MatData, FeederData, x);
      string Code   = MatData.WireFeederMatCode;

      pIntfLF->hndlWireFeederStart(Code);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFSolidMaterialHandlingWrapper::doOnWireFeedingStart()",  "" );    
  }

  return RetValue;
}

//##ModelId=416691B80315
bool CLFSolidMaterialsHandlingWrapper::doOnChangedMatSetPointsOperator(CEventMessage& Event)
{
  bool RetValue = false; 

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnChangedMatSetPointsOperator";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnChangedMatSetPointsOperator(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeName));
    long RecipeNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
                                           Event.getDataKey().c_str(), DATA::RecipeNo);

    string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeSource));


		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->indicateChgRecipeOrigSetPt(RecipeNameModel, Source);
      if ( CRS::OK == RetCode)
      {
        seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
                                              Event.getDataKey().c_str(), DATA::RecipeContent));

        long      SeqLength   = 0;
        long      GetAtValue  = 0;
        sBatch    MatData;
        SeqLength = CIntfData::getLength(Batch);
        for (int x = 0; x < SeqLength; x++) 
        {
          GetAtValue    = CIntfData::getAt(MatData, Batch, x);
          string Code   = MatData.MatCode;
          pIntfLF->setMatSetPt(Code, MatData.Mass);
        }

        pIntfLF->hndlEvent();
      }
      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && ( CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFSolidMaterialHandlingWrapper::doOnChangedMatSetPointsOperator()", "" );    
  }

  return RetValue;
}

//##ModelId=416691B90279
bool CLFSolidMaterialsHandlingWrapper::doOnDisableSourceRecipe(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnDisableSourceRecipe";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnDisableSourceRecipe(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeName));
    long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
                                           Event.getDataKey().c_str(), DATA::RecipeNo);

    string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeSource));

		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->hndlDisableRecipe(RecipeNameModel, Source);

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && ( CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(),  "" ); 
  }

  return RetValue;
}

//##ModelId=416691BA01B2
bool CLFSolidMaterialsHandlingWrapper::doOnEnableSourceRecipe(CEventMessage& Event)
{
  bool RetValue = false;  

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnEnableSourceRecipe";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnEnableSourceRecipe(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try 
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

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

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->indicateEnableRecipeOrig(RecipeNameModel, Source);

      if (CRS::OK == RetCode)
      {
        seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
                                              Event.getDataKey().c_str(), DATA::RecipeContent));

        long      SeqLength   = 0;
        long      GetAtValue  = 0;
        sBatch    MatData;
        SeqLength = CIntfData::getLength(Batch);
        for (int x = 0; x < SeqLength; x++) 
        {
          GetAtValue    = CIntfData::getAt(MatData, Batch, x);
          string Code   = MatData.MatCode;
          pIntfLF->setMatSetPt(Code, MatData.Mass);
        }

        RetCode = pIntfLF->hndlEvent();
      }

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && (CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), "" );    
  }

  return RetValue;	
}

//##ModelId=416691BB0034
bool CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialCharged(CEventMessage& Event)
{
  bool RetValue = false;  

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialCharged";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialCharged(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try 
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeName));
    string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                           Event.getDataKey().c_str(), DATA::RecipeSource));
    long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
                                           Event.getDataKey().c_str(), DATA::RecipeNo);

    seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getBatch(
                                           Event.getDataKey().c_str(), DATA::RecipeContent));


		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long      SeqLength   = 0;
      long      GetAtValue  = 0;
      sBatch    MatData;
      SeqLength = CIntfData::getLength(Batch);

      if (SeqLength > 0)
      {
        pIntfLF->indicateMatChg();

        for (int x = 0; x < SeqLength; x++) 
        {
          GetAtValue    = CIntfData::getAt(MatData, Batch, x);
          string Code   = MatData.MatCode;
          pIntfLF->hndlRecipeOrigMatChg(RecipeNameModel, Source, Code, MatData.Mass);
        }
        long RetCode = pIntfLF->hndlEvent();

        // Sequence Diagram: get model results / Call Sequence
        RetValue = doModelResult(Event);
        RetValue = RetValue && ( CRS::OK == RetCode);
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), "" ); 
  }

  return RetValue;
}

//##ModelId=416691BB02E7
bool CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialDischarged(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialDischarged";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnRecipeMaterialDischarged(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

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

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->hndlRecipeOrigMatDischg(RecipeNameModel, Source, Loc);

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && ( CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(),  "" ); 
  }

  return RetValue;
}

//##ModelId=416691BC01C6
bool CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingComplete(CEventMessage& Event)
{
  bool RetValue = false;  

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingComplete";

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingComplete(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

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

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->hndlRecipeWeighingComplete(RecipeNameModel, Source);

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && ( CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",  Function.c_str(), "" ); 
  }

  return RetValue;
}


//##ModelId=417E1109024E
bool CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingCompleteUpdate(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingCompleteUpdate";
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFSolidMaterialsHandlingWrapper::doOnRecipeWeighingCompleteUpdate(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                           getString(Event.getDataKey().c_str(), DATA::RecipeName));
    string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                           getString(Event.getDataKey().c_str(), DATA::RecipeSource));
    long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                           getLong(Event.getDataKey().c_str(), DATA::RecipeNo);

    seqBatch  Batch   = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                           getBatch(Event.getDataKey().c_str(), DATA::RecipeContent));

		std::string RecipeNameModel;
		long  RecipeNoModel = 0;

    if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
    {
      long      SeqLength   = 0;
      long      GetAtValue  = 0;
      sBatch    MatData;

      if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
        Source.clear();

      long RetCode = pIntfLF->indicateRecipeWeighingCompleteUpdOrig(RecipeNameModel, Source);
      if ( CRS::OK == RetCode)
      {
        SeqLength = CIntfData::getLength(Batch);
        for (int x = 0; x < SeqLength; x++) 
        {
          GetAtValue    = CIntfData::getAt(MatData, Batch, x);
          string Code   = MatData.MatCode;

          pIntfLF->setMatUpd(Code, MatData.Mass);
        }

        RetCode = pIntfLF->hndlEvent();
      }

      // Sequence Diagram: get model results / Call Sequence
      RetValue = doModelResult(Event);
      RetValue = RetValue && ( CRS::OK == RetCode);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
    }

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""  );    

  }

  return RetValue;
}

bool CLFSolidMaterialsHandlingWrapper::doOnRecipeDischargeStart(CEventMessage & Event)
{
  bool RetValue = false;

  std::string Function     = "CLFSolidMaterialsHandlingWrapper::doOnRecipeDischargeStart";
  
  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF && m_pModelTask) 
  {
    try
    {
      std::string PlantID   = Event.getPlantID();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

      string RecipeName = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getString(Event.getDataKey().c_str(), DATA::RecipeName));
      string Source     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getString(Event.getDataKey().c_str(), DATA::RecipeSource));
      long   RecipeNo   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getLong(Event.getDataKey().c_str(), DATA::RecipeNo);
      string Loc        = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
                                             Event.getDataKey().c_str(), DATA::RecipeTarget));

		  std::string RecipeNameModel;
		  long  RecipeNoModel = 0;

      if ( m_pRecipeHandler->translateToModelRecipe(ActPlant, RecipeName, RecipeNo, RecipeNameModel, RecipeNoModel) )
      {

        long      SeqLength   = 0;
        long      GetAtValue  = 0;
	      sBatch    MatData;

        if (CRecipeCodesLF::HighPriority == RecipeNameModel)    // mrut 2008-06-03 no high-prio recipe has no source
          Source.clear();

        long RetCode = pIntfLF->hndlRecipeOrigMatDischgStart(RecipeNameModel, RecipeNoModel, Source, Loc);

        RetValue = doModelResult(Event);
        RetValue = RetValue && ( CRS::OK == RetCode);
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingRecipe(sMessage, RecipeName.c_str(), RecipeNo, Function.c_str());
      }

    }
    catch (...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", Function.c_str(), ""); 
    }
  } 
  else 
  {
    handleError("CLFSolidMaterialsHandlingWrapper", "doOnRecipeDischargeStart(): pIntfLF or m_pModelTask = 0");
  }

  return RetValue;
}

// check if expected sequence of material handling signals is in correct order
// call respective cases in case of missing signals
bool CLFSolidMaterialsHandlingWrapper::doOnMaterialData(CEventMessage & Event)
{
  bool RetValue = false;

  // we expect the following sequence
  // enable
  // weighing
  // weighingComplete
  // weighingCompleteUpdate
  // chargee
  // dischargeStart
  // discharged

  if (m_pModelTask) 
  {
    try
    {
      std::string HeatID    = Event.getHeatID();
      std::string TreatID   = Event.getTreatID();
      std::string PlantID   = Event.getPlantID();
      std::string Message   = Event.getMessage();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);


      string RecipeName   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getString(Event.getDataKey().c_str(), DATA::RecipeName));
      string Source       = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getString(Event.getDataKey().c_str(), DATA::RecipeSource));
      long   RecipeNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getLong(Event.getDataKey().c_str(), DATA::RecipeNo);
      long RecipeStatus   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->
                             getLong(Event.getDataKey().c_str(), DATA::RecipeStatus);

      // all recipe states that have been set before includig RecipeStatus that has been set at tracking
      std::set<long> ExistingRecipeStates = m_pRecipeHandler->getBatchStatusList(ActPlant, HeatID, TreatID, RecipeName, RecipeNo);

      // all states that must be set
      std::set<long> ActionStatusList;
      std::set<long>::iterator itAction;

      // the most importatnt states
      std::set<long> MainBatchStatusList;
      std::set<long>::iterator it;

      MainBatchStatusList.insert(DEF_GC_RECIPE_STATUS::Enabled);
      MainBatchStatusList.insert(DEF_GC_RECIPE_STATUS::Weighed);
      MainBatchStatusList.insert(DEF_GC_RECIPE_STATUS::WeighingComplete);
      MainBatchStatusList.insert(DEF_GC_RECIPE_STATUS::Discharged);

      // check if RecipeStatus has to be regarded
      if ( MainBatchStatusList.find(RecipeStatus) != MainBatchStatusList.end())
      {
        // we assume that first step during additionan actions will be disabling recipe
        ActionStatusList.insert(DEF_GC_RECIPE_STATUS::Disabled);

        // detect missing states for batch as new action status
        for ( it = MainBatchStatusList.begin(); it != MainBatchStatusList.end(); ++it )
        {
          // if MainBatchStatusList is not part of ExistingRecipeStates this is a candidate for additional action
          if ( ExistingRecipeStates.find((*it)) == ExistingRecipeStates.end() )
          {
            if ( RecipeStatus > (*it) )
            {
              ActionStatusList.insert((*it));
            }
          }
        }

        // check if more entreis that DEF_GC_RECIPE_STATUS::Disabled have been detected
        if ( ActionStatusList.size() > 1 )
        {
          // missing actions detected
          for ( itAction = ActionStatusList.begin(); itAction != ActionStatusList.end(); ++itAction )
          {
            long Status = (*itAction);

            if ( Status == DEF_GC_RECIPE_STATUS::Disabled ) 
            {
              doOnDisableSourceRecipe(Event);     
            }
            else if ( Status == DEF_GC_RECIPE_STATUS::Enabled ) 
            {
              doOnEnableSourceRecipe(Event);     
            }
            else if ( Status == DEF_GC_RECIPE_STATUS::Weighed ) 
            {
              doOnRecipeMaterialCharged(Event);     
            }
            else if ( Status == DEF_GC_RECIPE_STATUS::WeighingComplete ) 
            {
              doOnRecipeWeighingComplete(Event);     
            }
            else if ( Status == DEF_GC_RECIPE_STATUS::Discharged ) 
            {
              doOnRecipeMaterialDischarged(Event);     
            }
          } // for ( it = ActionStatusList.begin(); it != ActionStatusList.end(); ++it )
        }
      }


      // solid materials - recipe related usecases
      if (LF_EvMsg::evLFChangedMatSetPointsByOperator == Message )             
      {
        doOnChangedMatSetPointsOperator(Event);     
      }
      else if (LF_EvMsg::evLFDisableSourceRecipe == Message )             
      {
        doOnDisableSourceRecipe(Event);     
      }
      else if (LF_EvMsg::evLFEnableSourceRecipe == Message )             
      {
        doOnEnableSourceRecipe(Event);     
      }
      else if (LF_EvMsg::evLFRecipeMatCharged == Message )             
      {
        doOnRecipeMaterialCharged(Event);     
      }
      else if (LF_EvMsg::evLFRecipeMatDischarged == Message )             
      {
        doOnRecipeMaterialDischarged(Event);     
      }
      else if (LF_EvMsg::evLFRecipeWeighingComplete == Message )             
      {
        doOnRecipeWeighingComplete(Event);     
      }
      else if (LF_EvMsg::evLFRecipeWeighingCompleteUpdate == Message )          
      {
        doOnRecipeWeighingCompleteUpdate(Event);     
      }
      else if (LF_EvMsg::evLFRecipeMatDischargedStart == Message ) 
      {
        doOnRecipeDischargeStart(Event);
      }
      // solid materials - wire feeding material usecases
      else if (LF_EvMsg::evLFWireFeedingEnd == Message )             
      {
        doOnWireFeedingEnd(Event);     
      }
      else if (LF_EvMsg::evLFWireFeedingStart == Message )             
      {
        doOnWireFeedingStart(Event);     
      }
    }
    catch (...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CLFSolidMaterialsHandlingWrapper::doOnMaterialData()",
        ""
      ); 
    }
  } 
  else 
  {
    handleError("CLFSolidMaterialsHandlingWrapper", "doOnMaterialData(): m_pModelTask = 0");
  }

  return RetValue;
}

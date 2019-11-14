// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_LFTask.h"
#include "CIntfData.h"
#include "CSMC_EventLogLFController.h"
#include "CDM_LFEventLogHandlerMaterial.h"
#include "CDataConversion.h"

bool CDM_LFEventLogHandlerMaterial::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {
    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();

    if ( Message == LF_EvMsg::evLFChangeLiquidAdditionData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeLiquidAdditionData(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFRemoveLiquidSteelData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RemoveLiquidAdditionData(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFMaterialHandlingReport )
    {
      //
      // First log the general information about this event ( those data that are of simple type. )
      //
      std::string strRecipeName = m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str();
      std::string strRecipeSource = m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str();
      std::string strRecipeStatus = m_pDataInterface->getString(DataKey,DATA::RecipeStatus).c_str();

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));

      //
      // log the detailed information for those items that are of complex type 
      // ( e.g. structures or sequences, and so on )
      //
      seqBatch RecipeBatch = CIntfData::ToCORBAType(m_pDataInterface->getBatch(DataKey.c_str(),DATA::RecipeContent));

      long seqLength = CIntfData::getLength(RecipeBatch);
      for(int i=0;i<seqLength;i++)
      {
        sBatch sRecipeElement;
        CIntfData::getAt(sRecipeElement, RecipeBatch,i);
        pEventLog->EL_MaterialHandlingReport(sMessage,
                                           m_pDataInterface->getString(DataKey,DATA::LadleTransferCarId).c_str(),
                                           strRecipeName.c_str(),
                                           strRecipeSource.c_str(),
                                           strRecipeStatus.c_str(),
                                           sRecipeElement.MatCode,
                                           sRecipeElement.Mass);

      }

    }

    else if ( Message == LF_EvMsg::evLFChangePhysicalMatAvailibility )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangePhysicalMatAvailibility(sMessage,
        m_pDataInterface->getString(DataKey,DATA::MatCode).c_str());
    }

    else if ( Message == LF_EvMsg::evLFHandleUpdatePurpose )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HandleUpdatePurpose(sMessage);
    }

    else if ( Message == LF_EvMsg::evLFMatBatchCharged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MatBatchCharged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeStatus));
    }

    else if ( Message == LF_EvMsg::evLFMatBatchDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MatBatchDischarged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeStatus));
    }

    else if ( Message == LF_EvMsg::evLFDisableSourceRecipe )

    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DisableSourceRecipe(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == LF_EvMsg::evLFEnableSourceRecipe )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_EnableSourceRecipe(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == LF_EvMsg::evLFRecipeMatCharged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeMaterialCharged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == LF_EvMsg::evLFRecipeMatDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeMaterialDischarged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == LF_EvMsg::evLFLiquidSteelCharged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LiquidSteelCharged(sMessage);
    }     
    else if ( Message == LF_EvMsg::evLFLiqMatHandlReport )
    {
      std::string statusVal, strVal;      
      statusVal = m_pDataInterface->getString(DataKey,DATA::LadleDeslagged);

      if(statusVal=="1")
        strVal="Deslagged";
      else if(statusVal=="0")
        strVal="Not deslagged";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LiqMatHandlReport(sMessage,
        m_pDataInterface->getString(DataKey,DATA::MeasWeight).c_str(),
        m_pDataInterface->getString(DataKey,DATA::WeighingType).c_str(),
        (m_pDataInterface->getString(DataKey,DATA::LadleType) + 
         CDataConversion::IntToString(m_pDataInterface->getLong(DataKey,DATA::LadleNo))     ).c_str(),
        strVal.c_str());
    }
    else if ( Message == LF_EvMsg::evLFWireFeedingStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_WireFeedingStart(sMessage,
        m_pDataInterface->getString(DataKey,DATA::WireFeederMatCode).c_str(),
        m_pDataInterface->getString(DataKey,DATA::WireFeederLineNo).c_str());
    }
    else if ( Message == LF_EvMsg::evLFWireFeedingEnd )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_WireFeedingEnd(sMessage,
        m_pDataInterface->getString(DataKey,DATA::WireFeederLineNo).c_str());
    }
    else if ( Message == LF_EvMsg::evLFRecipeWeighingComplete )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeWeighingComplete(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFRecipeWeighingCompleteUpdate )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeWeighingCompleteUpdate(sMessage);
    }
    else if ( Message == LF_EvMsg::evLFMinChargeableBinWeightUpdate )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MinChargeableBinWeightUpdate(sMessage);
    }
    else
    {
      RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
    }
  }
  return RetValue;
}

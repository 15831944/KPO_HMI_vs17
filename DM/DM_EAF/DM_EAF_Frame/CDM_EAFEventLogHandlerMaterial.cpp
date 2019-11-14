// Copyright (C) 2005 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDataConversion.h"
#include "CDateTime.h"
#include "CDM_EAFTask.h"
#include "CSMC_EventLogEAFController.h"
#include "CIntfData.h"

#include "CDM_EAFEventLogHandlerMaterial.h"

bool CDM_EAFEventLogHandlerMaterial::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {

    CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();

    if ( Message == EAF_EvMsg::evEAFChangeLiquidAdditionData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangeLiquidAdditionData(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFRemoveLiquidAdditionData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RemoveLiquidAdditionData(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFMaterialHandlingReport )
    {
      //
      // First log the general information about this event ( those data that are of simple type. )
      //
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MaterialHandlingReport(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeStatus).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeNo).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());

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
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
        pEventLog->EL_MaterialHandlingReport(sMessage,
                                          sRecipeElement.MatCode,
                                          sRecipeElement.Mass);
      }

    }

    else if ( Message == EAF_EvMsg::evEAFChangePhysicalMatAvailibility )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ChangePhysicalMatAvailibility(sMessage,
        m_pDataInterface->getString(DataKey,DATA::MatCode).c_str());
    }

    else if ( Message == EAF_EvMsg::evEAFMatBatchDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MatBatchCharged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeStatus));
    }

    else if ( Message == EAF_EvMsg::evEAFDisableSourceRecipe )

    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DisableSourceRecipe(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFEnableSourceRecipe )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_EnableSourceRecipe(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFRecipeMaterialCharged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeMaterialCharged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFRecipeMaterialDischarged )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RecipeMaterialDischarged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::RecipeName).c_str(),
        m_pDataInterface->getLong(DataKey.c_str(),DATA::RecipeNo),
        m_pDataInterface->getString(DataKey,DATA::RecipeSource).c_str(),
        m_pDataInterface->getString(DataKey,DATA::RecipeTarget).c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHandleBasketDischarged )
    {
      std::string statusVal, strVal;      
      statusVal = m_pDataInterface->getString(DataKey,DATA::LastBasket);

      if(statusVal=="1")
        strVal="Last Basket";
      else if(statusVal=="0")
        strVal="Not last basket";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HandleScrapContainerDischarged(sMessage,
        m_pDataInterface->getString(DataKey,DATA::BasketId).c_str(),
        m_pDataInterface->getString(DataKey,DATA::BasketInSeq).c_str(),
        strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFHandleSetBasketData )
    {
      std::string statusVal, strVal;      
      statusVal = m_pDataInterface->getString(DataKey,DATA::LastBasket);

      if(statusVal=="1")
        strVal="Last Basket";
      else if(statusVal=="0")
        strVal="Not last basket";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HandleSetScrapContainerData(sMessage,
        m_pDataInterface->getString(DataKey,DATA::BasketId).c_str(),
        m_pDataInterface->getString(DataKey,DATA::BasketInSeq).c_str(),
        strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFRemoveLiquidAdditionData )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_RemoveLiquidAdditionData(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFLiquidAdditionCharged )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LiquidAdditionCharged(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFLiqMatHandlReport )
    {
      std::string statusVal, strVal;      
      statusVal = m_pDataInterface->getString(DataKey,DATA::LadleDeslagged);
      long nLadleNo = m_pDataInterface->getLong(DataKey,DATA::LadleNo);

      if(statusVal=="1")
        strVal="Deslagged";
      else if(statusVal=="0")
        strVal="Not deslaged";

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_LiqMatHandlReport(sMessage,
        m_pDataInterface->getString(DataKey,DATA::MeasWeight).c_str(),
        m_pDataInterface->getString(DataKey,DATA::WeighingType).c_str(),
        CDataConversion::LongToString(nLadleNo).c_str(),
        strVal.c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFMinChargeableBinWeightUpdate )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MinChargeableBinWeightUpdate(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFMatFeedingStart )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MatFeedingStart(sMessage);
    }
    else if ( Message == EAF_EvMsg::evEAFMatFeedingStop )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_MatFeedingStop(sMessage);
    }
    else
      RetValue = false;
  }
  return RetValue;
}
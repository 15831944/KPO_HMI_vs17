// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFMaterialHandlingEventHandler.h"

CLFMaterialHandlingEventHandler::CLFMaterialHandlingEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFChangePhysicalMaterialAvailabilityWrapper.setpModelTask(pModelTask);

  LFLiquidMaterialsHandlingWrapper.setpModelTask(pModelTask);

  LFManualMaterialBatchWrapper.setpModelTask(pModelTask);

  LFSolidMaterialsHandlingWrapper.setpModelTask(pModelTask);

}

bool CLFMaterialHandlingEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  // calling respective model wrapper functions
  if ( checkProductAcceptance(EventMessage) ) 
  {
    std::string Message = EventMessage.getMessage();

    // Liquid Materials Handling
	  if ( LF_EvMsg::evLFChangeLiquidAdditionData == Message )
    { 
      LFLiquidMaterialsHandlingWrapper.doOnChangeOfLiquidAdditionData(EventMessage);      
    } 
    else if (LF_EvMsg::evLFLiquidSteelCharged == Message ) 
    {
      LFLiquidMaterialsHandlingWrapper.doOnLiquidAdditionCharged(EventMessage);     
    }
    else if (LF_EvMsg::evLFRemoveLiquidSteelData == Message ) 
    { 
      LFLiquidMaterialsHandlingWrapper.doOnRemoveLiquidSteelData(EventMessage);     
    }
    // solid materials - material related usecases
    else if (LF_EvMsg::evLFChangePhysicalMatAvailibility == Message ) 
    {
      LFChangePhysicalMaterialAvailabilityWrapper.doOnChangedPhysicalMatAvail(EventMessage);  
    }
    else if (LF_EvMsg::evLFMatBatchCharged == Message )       
    {
      LFManualMaterialBatchWrapper.doOnMaterialBatchCharged(EventMessage);     
    }
    else if (LF_EvMsg::evLFMatBatchDischarged == Message )       
    {
      LFManualMaterialBatchWrapper.doOnMaterialBatchDischarged(EventMessage);     
    }
    // solid materials - recipe related usecases
    else if (LF_EvMsg::evLFChangedMatSetPointsByOperator == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnChangedMatSetPointsOperator(EventMessage);     
    }
    else if (LF_EvMsg::evLFDisableSourceRecipe == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnDisableSourceRecipe(EventMessage);     
    }
    else if (LF_EvMsg::evLFEnableSourceRecipe == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnEnableSourceRecipe(EventMessage);     
    }
    else if (LF_EvMsg::evLFRecipeMatCharged == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnRecipeMaterialCharged(EventMessage);     
    }
    else if (LF_EvMsg::evLFRecipeMatDischarged == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnRecipeMaterialDischarged(EventMessage);     
    }
    else if (LF_EvMsg::evLFRecipeWeighingComplete == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnRecipeWeighingComplete(EventMessage);     
    }
    else if (LF_EvMsg::evLFRecipeWeighingCompleteUpdate == Message )          
    {
      LFSolidMaterialsHandlingWrapper.doOnRecipeWeighingCompleteUpdate(EventMessage);     
    }
    else if (LF_EvMsg::evLFRecipeMatDischargedStart == Message ) 
    {
      LFSolidMaterialsHandlingWrapper.doOnRecipeDischargeStart(EventMessage);
    }
    // solid materials - wire feeding material usecases
    else if (LF_EvMsg::evLFWireFeedingEnd == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnWireFeedingEnd(EventMessage);     
    }
    else if (LF_EvMsg::evLFWireFeedingStart == Message )             
    {
      LFSolidMaterialsHandlingWrapper.doOnWireFeedingStart(EventMessage);     
    }
    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}

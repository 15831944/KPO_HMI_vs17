// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CEAFMaterialHandlingEventHandler.h"

//##ModelId=467645DE03C7
CEAFMaterialHandlingEventHandler::CEAFMaterialHandlingEventHandler(CModelTask* pModelTask)
: CEAFEventHandler(pModelTask)
{
	EAFLiquidMaterialsHandlingWrapper.setpModelTask(pModelTask);
	EAFChangePhysicalMaterialAvailabilityWrapper.setpModelTask(pModelTask);
	EAFManualMaterialBatchWrapper.setpModelTask(pModelTask);
	EAFSolidMaterialHandlingWrapper.setpModelTask(pModelTask);
	EAFInjectionMaterialHandlingWrapper.setpModelTask(pModelTask);
	EAFBasketMaterialHandlingWrapper.setpModelTask(pModelTask);
	EAFFeedingMaterialHandlingWrapper.setpModelTask(pModelTask);
}

//##ModelId=4118E0A600E2
bool CEAFMaterialHandlingEventHandler::handleEvent(CEventMessage& EventMessage)
{
	bool RetValue = true;  
  std::string Message = EventMessage.getMessage();
  
	if ( !checkProductAcceptance(EventMessage) ) 
	{
		return false;		
	}

		
	// Basket Material Handling Events
	if ( EAF_EvMsg::evEAFHandleBasketAssignedToHeat == Message )
	{
	  EAFBasketMaterialHandlingWrapper.doOnBasketAssignment(EventMessage);      
	} 
	else if ( EAF_EvMsg::evEAFHandleSetBasketData == Message )
	{
	  EAFBasketMaterialHandlingWrapper.doOnBasketData(EventMessage);      
	} 
	else if (EAF_EvMsg::evEAFHandleBasketDischarged == Message) 
	{ 
	  EAFBasketMaterialHandlingWrapper.doOnBasketDischarged(EventMessage);      
	} 
	// Feeding Material Handling Events
  else if ( EAF_EvMsg::evEAFMatFeedingStart == Message )
	{ 
	  EAFFeedingMaterialHandlingWrapper.doOnBinMaterialHandlingStart(EventMessage);      
	} 
  else if (EAF_EvMsg::evEAFMatFeedingStop == Message) 
	{ 
	  EAFFeedingMaterialHandlingWrapper.doOnBinMaterialHandlingStop(EventMessage);      
	} 
	// Liquid Materials Handling Events
	else if ( EAF_EvMsg::evEAFChangeLiquidAdditionData == Message)
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnChangeOfLiquidAdditionData(EventMessage);      
	}
	else if ( EAF_EvMsg::evEAFLiquidAdditionCharged == Message )
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnLiquidAdditionCharged(EventMessage);      
	}
  else if (EAF_EvMsg::evEAFHotMetalLadleData == Message ) 
	{
    EAFLiquidMaterialsHandlingWrapper.doOnChangeOfLiquidAdditionData(EventMessage);
	}
  else if (EAF_EvMsg::evEAFHotMetalAssigned == Message ) 
	{
    EAFLiquidMaterialsHandlingWrapper.doOnChangeOfLiquidAdditionData(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFChargedHotMetal == Message ) 
	{
	  EAFLiquidMaterialsHandlingWrapper.doOnHotMetalCharged(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFChargedLiquidFeCr == Message ) 
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnLiquidFeCrCharged(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFChargedLiquidSteel == Message ) 
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnLiquidSteelCharged(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFRemoveHotMetalData == Message ) 
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnRemoveHotMetalData(EventMessage);     
	}		
	else if (EAF_EvMsg::evEAFRemoveLiquidFeCr == Message ) 
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnRemoveLiquidFeCrData(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFRemoveLiquidSteel == Message ) 
	{ 
	  EAFLiquidMaterialsHandlingWrapper.doOnRemoveLiquidSteelData(EventMessage);     
	}
	// Change Physical Material Availability Events
	else if (EAF_EvMsg::evEAFChangePhysicalMatAvailibility == Message ) 
	{ 
	  EAFChangePhysicalMaterialAvailabilityWrapper.doOnChangedPhysicalMatAvail(EventMessage);     
	}
	// Manual Material Batch Handling Events
	else if (EAF_EvMsg::evEAFMatBatchCharged == Message ) 
	{ 
	  EAFManualMaterialBatchWrapper.doOnMaterialBatchCharged(EventMessage);     
	}
	else if (EAF_EvMsg::evEAFMatBatchDischarged == Message ) 
	{ 
	  EAFManualMaterialBatchWrapper.doOnMaterialBatchDischarged(EventMessage);   
	}
	// Solid Materials Handling Events
	else if (EAF_EvMsg::evEAFChangedMatSetPointsByOperator == Message ) 
	{ 
	  EAFSolidMaterialHandlingWrapper.doOnChangedMatSetPointsOperator(EventMessage);   
	}		
	else if (EAF_EvMsg::evEAFDisableSourceRecipe == Message ) 
	{ 
	  EAFSolidMaterialHandlingWrapper.doOnDisableSourceRecipe(EventMessage);   
	}
	else if (EAF_EvMsg::evEAFEnableSourceRecipe == Message ) 
	{ 
	  EAFSolidMaterialHandlingWrapper.doOnEnableSourceRecipe(EventMessage);   
	}
	else if (EAF_EvMsg::evEAFRecipeMaterialCharged == Message ) 
	{ 
	  EAFSolidMaterialHandlingWrapper.doOnRecipeMaterialCharged(EventMessage);   
	}
	else if (EAF_EvMsg::evEAFRecipeMaterialDischarged == Message ) 
	{ 
	  EAFSolidMaterialHandlingWrapper.doOnRecipeMaterialDischarged(EventMessage);   
	}
	else if (EAF_EvMsg::evEAFRecipeWeighingComplete == Message ||
			 EAF_EvMsg::evEAFRecipeWeighingCompleteUpdate == Message) 
	{ 		  
	  EAFSolidMaterialHandlingWrapper.doOnRecipeWeighingComplete(EventMessage);   
	}
	else
  {
		RetValue = false; 
  }


	return RetValue;
}

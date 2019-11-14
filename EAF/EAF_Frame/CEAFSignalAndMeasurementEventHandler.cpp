// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CEAFSignalAndMeasurementEventHandler.h"

//##ModelId=467645D603BC
CEAFSignalAndMeasurementEventHandler::CEAFSignalAndMeasurementEventHandler(CModelTask* pModelTask)
: CEAFEventHandler(pModelTask)
{
	EAFCeloxMeasurementWrapper.setpModelTask(pModelTask);
	EAFBurnerWrapper.setpModelTask(pModelTask);
	EAFComputerModeWrapper.setpModelTask(pModelTask);
	EAFCyclicMeasurementWrapper.setpModelTask(pModelTask);
	EAFDeslaggingWrapper.setpModelTask(pModelTask);
	EAFElectricSignalsWrapper.setpModelTask(pModelTask);
	EAFJetModuleWrapper.setpModelTask(pModelTask);
	EAFLanceManipWrapper.setpModelTask(pModelTask);
	EAFOxygenMeasurementWrapper.setpModelTask(pModelTask);
	EAFOxygenSideLancesWrapper.setpModelTask(pModelTask);
	EAFRoofPositionWrapper.setpModelTask(pModelTask);
	EAFTappedWeightWrapper.setpModelTask(pModelTask);
	EAFTappingLadleWrapper.setpModelTask(pModelTask);
	EAFTappingWrapper.setpModelTask(pModelTask);
	EAFTemperatureMeasurementWrapper.setpModelTask(pModelTask);
}

//##ModelId=4118DE15015F
bool CEAFSignalAndMeasurementEventHandler::handleEvent( CEventMessage& EventMessage)
{
	bool RetValue = true; 

	std::string Message = EventMessage.getMessage();
	
	if ( !checkProductAcceptance(EventMessage) ) 
	{
		return false;
	}

	if ( EAF_EvMsg::evEAFBurnerStart == Message )
	{ 	  
		EAFBurnerWrapper.doOnBurnerStart(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFBurnerStop == Message )
	{ 	  
		EAFBurnerWrapper.doOnBurnerEnd(EventMessage); 
	} 	
	if ( EAF_EvMsg::evEAFCeloxMeasurement == Message ) // Celox measurement: very rare
	{ 	  
		RetValue = EAFCeloxMeasurementWrapper.doOnCeloxMeasurement(EventMessage); 
	} 	  	
  else if ( EAF_EvMsg::evEAFCyclicMeasurement == Message ) // Cyclical measurement
	{ 	  
		RetValue = EAFCyclicMeasurementWrapper.doOnCyclicMeasurement(EventMessage); 
	} 	
	else if ( EAF_EvMsg::evEAFGantrySwungIn == Message ) // Roof Position Events: medium rare
	{ 	  
		RetValue = EAFRoofPositionWrapper.doOnGantrySwungIn(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFGantrySwungOut == Message )
	{ 	  
		RetValue = EAFRoofPositionWrapper.doOnGantrySwungOut(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFRoofArrivesInDownPosition == Message )
	{ 	  
		RetValue = EAFRoofPositionWrapper.doOnRoofInDownPos(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFRoofArrivesInUpPosition == Message )
	{ 	  
		RetValue = EAFRoofPositionWrapper.doOnRoofInUpPos(EventMessage); 
	} 	
	else if ( EAF_EvMsg::evEAFElectrodesInOperatingPosition == Message ) // Electric Signals: medium rare
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnElectrodInOperationPos(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFElectrodesOutOperatingPosition == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnElectrodOutOperationPos(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFFurnaceBreakerOn == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnFurnBreakerOn(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFFurnaceBreakerOff == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnFurnBreakerOff(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFPowerOff == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnPowerOff(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFPowerOn == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnPowerOn(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFTapChangeFinished == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnTapChangeFinished(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFTapChangeStart == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnTapChangeStart(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFElectrodeRegCurveNum == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnRegCurvNumChange(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFActivateWallTempCtrl == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnActivWallTempContr(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFDeactivateWallTempCtrl == Message )
	{ 	  
		RetValue = EAFElectricSignalsWrapper.doOnDeactivVallTempContr(EventMessage); 
	} 	
	else if ( EAF_EvMsg::evEAFTempMeasurement == Message ) // Temperature measurement: rare
	{ 	  
		RetValue = EAFTemperatureMeasurementWrapper.doOnTempMeasurement(EventMessage); 
	}	
	else if ( EAF_EvMsg::evEAFManipInjectLanceStart == Message || EAF_EvMsg::evEAFCarbonInjectStart == Message )
	{ 	  
		RetValue = EAFLanceManipWrapper.doOnManipInjLanceStart(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFManipInjectLanceStop == Message || EAF_EvMsg::evEAFCarbonInjectStop == Message)
	{ 	  
		RetValue = EAFLanceManipWrapper.doOnManipInjLanceStop(EventMessage);  
	}
	else if ( EAF_EvMsg::evEAFManipGasLanceStart == Message /* to do EAF_EvMsg::evEAFOxygenEBTStart == Message||*/ )
	{ 	  
		RetValue = EAFLanceManipWrapper.doOnManipGasLanceStart(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFManipGasLanceStop == Message /* to do EAF_EvMsg::evEAFOxygenEBTStop == Message||*/ )
	{ 	  
		RetValue = EAFLanceManipWrapper.doOnManipGasLanceStop(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFTappingStart == Message ) 
	{ 	  
		RetValue = EAFTappingWrapper.doOnTappingStart(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFTappingEnd == Message )
	{ 	  
		EAFTappingWrapper.doOnTappingEnd(EventMessage); 
	} 

  // use case also handle in CEAFTreatmentManagerEventHandler calling 
  // CEAFTreatmentManagerDataWrapper::doOnChangeTapLadleData as correct implementation
  // EAFTappingWrapper.doOnTapLadleData is obsolete
  // else if ( EAF_EvMsg::evEAFChangeTapLadleData == Message )
	//{ 	  
	//	EAFTappingWrapper.doOnTapLadleData(EventMessage); 
	//} 
	else if ( EAF_EvMsg::evEAFSetTappingMasses == Message ) 
	{ 	  
		// should come after tapping end when there is a new measurement of weight then this call
    // RetValue = EAFTappedWeightWrapper.doOnSetTappedWeight(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFLadleStirringStart == Message )
	{ 	  
		RetValue = EAFTappingLadleWrapper.doOnLadleStirringStart(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFLadleStirringStop == Message )
	{ 	  
		RetValue = EAFTappingLadleWrapper.doOnLadleStirringStop(EventMessage);
	} 	
	else if ( EAF_EvMsg::evEAFBottomStirringStart == Message )
	{ 	  
		RetValue = EAFTappingLadleWrapper.doOnFurnaceBottomStirringStart(EventMessage);
	} 
	else if ( EAF_EvMsg::evEAFBottomStirringEnd == Message )
	{ 	  
		RetValue = EAFTappingLadleWrapper.doOnFurnaceBottomStirringStop(EventMessage);
	} 	
	else if ( EAF_EvMsg::evEAFSetComputerMode == Message ) // Computer Modes events: rare .. very rare
	{ 	  
		RetValue = RetValue = EAFComputerModeWrapper.doOnSetComputerMode(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFMaintenance == Message )
	{ 	  
		RetValue = EAFComputerModeWrapper.doOnSetEAFMaintenanceMode(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFJetModuleStart == Message )
	{ 	  
		RetValue = RetValue = EAFJetModuleWrapper.doOnJetModuleStart(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFJetModuleStop == Message )
	{ 	  
		RetValue = EAFJetModuleWrapper.doOnJetModuleStop(EventMessage);   
	} 
	else if ( EAF_EvMsg::evEAFCarbonInjectStart == Message )
	{ 	  
		// wrong method EAFOxygenSideLancesWrapper.doOnOxygenSideLanceStart(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFCarbonInjectStop == Message )
	{ 	  
		// wrong method EAFOxygenSideLancesWrapper.doOnOxygenSideLanceStop(EventMessage);   
	} 
	else if ( EAF_EvMsg::evEAFOxygenMeasurement == Message ) // Oxygen measurement:  : usually never occurr
	{ 	  
		RetValue = EAFOxygenMeasurementWrapper.doOnOxygenMeusurement(EventMessage);  
	} 	
	else if ( EAF_EvMsg::evEAFDeslaggingStart == Message ) // Deslagging events : usually never occurr
	{ 	  
		RetValue = EAFDeslaggingWrapper.doOnDeslaggingStart(EventMessage);  
	} 
	else if ( EAF_EvMsg::evEAFDeslaggingEnd == Message )
	{ 	  
		RetValue = RetValue = EAFDeslaggingWrapper.doOnDeslaggingEnd(EventMessage);  
	} 	
	else if ( EAF_EvMsg::evEAFDoorOpened == Message ) // Door position events : usually never occurr
	{	  
		RetValue = EAFRoofPositionWrapper.doOnDoorOpened(EventMessage); 
	} 
	else if ( EAF_EvMsg::evEAFDoorClosed == Message )
	{ 	  
		RetValue = EAFRoofPositionWrapper.doOnDoorClosed(EventMessage); 
	} 
	else
	{
	  RetValue = false; // The event is not for this handler
	}


	return RetValue;
}

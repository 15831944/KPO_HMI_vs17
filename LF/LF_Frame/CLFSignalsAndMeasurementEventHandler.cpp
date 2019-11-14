// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CLFSignalsAndMeasurementEventHandler.h"

//##ModelId=462767AB001D
CLFSignalsAndMeasurementEventHandler::CLFSignalsAndMeasurementEventHandler(CModelTask* pModelTask)
: CLFEventHandler(pModelTask)
{
  LFBottomStirringWrapper.setpModelTask(pModelTask);
  LFCeloxMeasurementWrapper.setpModelTask(pModelTask);
  LFCyclicMeasurementWrapper.setpModelTask(pModelTask);
  LFElectricSignalsWrapper.setpModelTask(pModelTask);
  LFRoofPositionWrapper.setpModelTask(pModelTask);
  LFTemperaturMeasurementWrapper.setpModelTask(pModelTask);
}

//##ModelId=4118E6FD0013
bool CLFSignalsAndMeasurementEventHandler::handleEvent( CEventMessage& EventMessage)
{
  bool RetValue = true;
  
  // calling respective model wrapper functions
  if ( checkProductAcceptance(EventMessage) ) 
  {          
    std::string Message = EventMessage.getMessage();

    if (LF_EvMsg::evLFCyclicMeasurement == Message) 
    { 
      LFCyclicMeasurementWrapper.doOnCyclicMeasurements(EventMessage);      
    } 
    else if (LF_EvMsg::evLFPowerOff == Message) 
    {
      LFElectricSignalsWrapper.doOnPowerOff(EventMessage);      
    } 
    else if (LF_EvMsg::evLFPowerOn == Message) 
    { 
      LFElectricSignalsWrapper.doOnPowerOn(EventMessage);      
    } 
    else if (LF_EvMsg::evLFTempMeasurement == Message) 
    { 
      LFTemperaturMeasurementWrapper.doOnTempMeasurement(EventMessage);      
    } 
    else if (LF_EvMsg::evLFCeloxMeasurement == Message) 
    { 
      LFCeloxMeasurementWrapper.doOnCeloxMeasurement(EventMessage);      
    } 
    else if (LF_EvMsg::evLFElectrodesInOperatingPosition == Message) 
    { 
      LFElectricSignalsWrapper.doOnElectrodInOperationPos(EventMessage);      
    } 
    else if (LF_EvMsg::evLFElectrodesOutOperatingPosition == Message) 
    { 
      LFElectricSignalsWrapper.doOnElectrodOutOperationPos(EventMessage);      
    } 
    else if (LF_EvMsg::evLFRoofArrivesInDownPosition == Message) 
    { 
      LFRoofPositionWrapper.doOnRoofInDownPos(EventMessage);      
    } 
    else if (LF_EvMsg::evLFRoofArrivesInUpPosition == Message) 
    { 
      LFRoofPositionWrapper.doOnRoofInUpPos(EventMessage);      
    } 
    else if (LF_EvMsg::evLFFurnaceBreakerOff == Message) 
    { 
      LFElectricSignalsWrapper.doOnFurnBreakerOff(EventMessage);      
    } 
    else if (LF_EvMsg::evLFFurnaceBreakerOn == Message) 
    { 
      LFElectricSignalsWrapper.doOnFurnBreakerOn(EventMessage);      
    } 
    else if (LF_EvMsg::evLFGantrySwungOut == Message) 
    { 
      LFRoofPositionWrapper.doOnGantrySwungOut(EventMessage);      
    } 
    else if (LF_EvMsg::evLFGantrySwungIn == Message) 
    { 
      LFRoofPositionWrapper.doOnGantrySwungIn(EventMessage);      
    } 
    else if (LF_EvMsg::evLFTapChangeFinished == Message) 
    { 
      LFElectricSignalsWrapper.doOnTapChangeFinished(EventMessage);      
    } 
    else if (LF_EvMsg::evLFTapChangeStart == Message) 
    { 
      LFElectricSignalsWrapper.doOnTapChangeStart(EventMessage);      
    } 
    else if (LF_EvMsg::evLFBottomStirringStart == Message )
    { 
      LFBottomStirringWrapper.doOnStirringStart(EventMessage);      
    } 
    else if (LF_EvMsg::evLFBottomStirringEnd == Message) 
    { 
      LFBottomStirringWrapper.doOnStirringEnd(EventMessage);      
    } 
    else if (LF_EvMsg::evLFBottomStirringByPassOff == Message )  // NOT as per USE CASE
    { 
      LFBottomStirringWrapper.doOnStirringBypassOff(EventMessage);      
    } 
    else if (LF_EvMsg::evLFBottomStirringByPassOn == Message )
    { 
      LFBottomStirringWrapper.doOnStirringBypassOn(EventMessage);      
    }
    else
      RetValue = false; // The event is not for this handler
  }
  else
    RetValue = false; // The event is not for this product

  return RetValue;
}

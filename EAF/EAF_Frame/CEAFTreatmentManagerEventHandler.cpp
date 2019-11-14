// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CEAFTreatmentManagerEventHandler.h"

//##ModelId=467645D602CB
CEAFTreatmentManagerEventHandler::CEAFTreatmentManagerEventHandler(CModelTask* pModelTask)
: CEAFEventHandler(pModelTask)
{
	EAFTreatmentManagerDataWrapper.setpModelTask(pModelTask);
}

//##ModelId=4118B7C70111
bool CEAFTreatmentManagerEventHandler::handleEvent( CEventMessage &EventMessage)
{
	bool RetValue = true;
	std::string Message = EventMessage.getMessage();

  

	// check DM in case of Heat Announcement
	if ( EAF_EvMsg::evEAFHeatAnnouncement == Message )
	{
		RetValue = checkAnnouncement(EventMessage,false);
	}
	else if ( EAF_EvMsg::evEAFHeatAnnouncementOffline == Message )
	{
		RetValue = checkAnnouncement(EventMessage,true);
	}

	if ( !checkProductAcceptance(EventMessage) ) 
	{
		return false;		
	}

	if ( EAF_EvMsg::evEAFHeatAnnouncement == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnHandleHeatAnnouncement(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFHeatCancellation == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnHeatCancellation(EventMessage);    
	}
  else if ( EAF_EvMsg::evEAFChangeTreatmentMode == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeTreatmentMode(EventMessage);    
  }
	else if ( EAF_EvMsg::evEAFChangeAimData       == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeAimData(EventMessage);    
  }
	else if ( EAF_EvMsg::evEAFSteelGradeChanged   == Message   )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeSteelGrade(EventMessage);    
  }
	else if ( EAF_EvMsg::evEAFChangeTapLadleData == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeTapLadleData(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFChangeHotHeelData == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeHotHeelData(EventMessage);    
	}
	else if (  ( EAF_EvMsg::evEAFChangeProdPracPointerElec == Message ) ||
			       ( EAF_EvMsg::evEAFChangeProdPracDataElec    == Message )   )
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracElectric(EventMessage);    
	}
	else if (  ( EAF_EvMsg::evEAFChangeProdPracManipGasLance == Message ) ||
			       ( EAF_EvMsg::evEAFChangeProdPracDataOxygen    == Message )    ) 
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracOxygen(EventMessage);    
	}
	else if (  ( EAF_EvMsg::evEAFChangeProdPracPointerRestriction == Message ) ||
	           ( EAF_EvMsg::evEAFChangeProdPracPointerPlantRestriction == Message ) ||
             ( EAF_EvMsg::evEAFChangeProdPracDataRestriction    == Message ) ||
             ( EAF_EvMsg::evEAFChangeProdPracDataPlantRestriction    == Message ) ||
			       ( EAF_EvMsg::evEAFChangeProdPracDataRecipeCTRL     == Message )    )
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracRecipeControl(EventMessage);    
	}
  else if ( EAF_EvMsg::evEAFChangeProdPracPointerProcess == Message || 
            EAF_EvMsg::evEAFChangeProdPracDataProcess    == Message    )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProcPattern(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFChangeProdPracPointerInjection == Message ||
            EAF_EvMsg::evEAFChangeProdPracDataInjection == Message   )   
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracInjection(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFChangeProdPracDataBurner == Message )
	{
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracBurner(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFChangeProdPracDataJetModule == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracJetMod(EventMessage);    
	}
	else if ( EAF_EvMsg::evEAFChangeProdPracPointerStirring == Message ||
            EAF_EvMsg::evEAFChangeProdPracDataStirring    == Message   )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangeProdPracBottomStirring(EventMessage);    
	}  
	else if ( EAF_EvMsg::evEAFChangeThermalStatus == Message ||
            EAF_EvMsg::evEAFUpdatePlantStatus   == Message )    
	{ 
	  EAFTreatmentManagerDataWrapper.doOnChangePlantStatus(EventMessage);    
	}
  else if (EAF_EvMsg::evEAFChangeProdPracPointerParameter == Message ||
           EAF_EvMsg::evEAFChangeProdPracDataParameter    == Message   ) 
  { 
    EAFTreatmentManagerDataWrapper.doOnChangeProdPracParameter(EventMessage);      
  }
	else
  {
    RetValue = false; 
  }

	return RetValue;
}

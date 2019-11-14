// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

#include "DEF_GC_RECIPE_STATUS.h"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CEAFBasketMaterialHandlingWrapper.h"
#include "CSMC_EventLogFrameController.h"


//##ModelId=4111226201AC
bool CEAFBasketMaterialHandlingWrapper::doOnBasketAssignment(CEventMessage &Event)
{
	bool RetValue = true;

	try 
	{
	  std::string HeatID  = Event.getHeatID();
	  std::string TreatID = Event.getTreatID();

	  if (!sequence_set_basket_data(HeatID, TreatID,Event))
	  {
		  std::string SearchKey = HeatID + " " + TreatID;
		  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_basket_data",SearchKey.c_str());
	  }
	}
	catch (...) 
	{
		  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFBasketMaterialHandlingWrapper::doOnBasketData()", ""  );    
	} 

	return RetValue;
}

bool CEAFBasketMaterialHandlingWrapper::doOnBasketData(CEventMessage &Event)
{
	bool RetValue = true;

	try 
	{
		long RecipeStatus = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::RecipeStatus);

	  std::string HeatID  = Event.getHeatID();
	  std::string TreatID = Event.getTreatID();

    if ( RecipeStatus == DEF_GC_RECIPE_STATUS::WeighingComplete )
    {
	    if (!sequence_set_basket_data(HeatID, TreatID,Event))
	    {
		    std::string SearchKey = HeatID + " " + TreatID;
		    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
		    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		    pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_basket_data",SearchKey.c_str());
	    }
    }
	}
	catch (...) 
	{
		  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFBasketMaterialHandlingWrapper::doOnBasketData()", ""  );    
	} 

	return RetValue;
}


//##ModelId=4111239E0229
bool CEAFBasketMaterialHandlingWrapper::doOnBasketDischarged(CEventMessage & Event)
{
  bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

	if (!m_pModelTask) 
	{
		log("error CEAFBasketMaterialHandlingWrapper::doOnBasketDischarged(), (m_pModelTask) == false", 1);
		return RetValue;
	}

	if (!pIntfEAF ) return RetValue;

	try 
	{
		long BasketInSeq = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
      Event.getDataKey().c_str(), DATA::BasketInSeq);

    pIntfEAF->hndlBasketDischg(BasketInSeq); 

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
		  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFBasketMaterialHandlingWrapper::doOnBasketDischarged()", ""  );    
	} 
		
	return RetValue;
}

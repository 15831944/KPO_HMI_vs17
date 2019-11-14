// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "CEventMessage.h"
#include "CDM_GENProdMgtEventHandler.h"

CDM_GENProdMgtEventHandler::CDM_GENProdMgtEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_GENProdMgtEventHandler::~CDM_GENProdMgtEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_GENProdMgtEventHandler::handleEvent(CEventMessage& evMessage)
{
  HANDLE_EVENT( GenParameterUpdate );
  HANDLE_EVENT( GenOrderStatusUpdate );
  HANDLE_EVENT( GenHeatStatusUpdate );
  HANDLE_EVENT( GenAnalysisData );
  HANDLE_EVENT( GenHeatScheduleUpdate );
  HANDLE_EVENT( GenProductionOrderDataUpdate );
	return false;
}


bool CDM_GENProdMgtEventHandler::doGenParameterUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENProdMgtEventHandler::doGenOrderStatusUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENProdMgtEventHandler::doGenHeatStatusUpdate(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENProdMgtEventHandler::doGenAnalysisData(CEventMessage& evMessage)
{
	doDataEvent(evMessage);
	return true;
}

bool CDM_GENProdMgtEventHandler::doGenHeatScheduleUpdate(CEventMessage& evMessage)
{
  //
	// Just forward this event to respective destinations
  //
  evMessage.setMessage(EAF_EvMsg::evEAFHeatScheduleUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(AOD_EvMsg::evAODHeatScheduleUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(LF_EvMsg::evLFHeatScheduleUpdate);
  dispatchEvent(evMessage);

  return true;
}

bool CDM_GENProdMgtEventHandler::doGenProductionOrderDataUpdate(CEventMessage& evMessage)
{
  //
	// Just forward this event to respective destinations
  //
  evMessage.setMessage(EAF_EvMsg::evEAFProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(AOD_EvMsg::evAODProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  evMessage.setMessage(LF_EvMsg::evLFProductionOrderDataUpdate);
  dispatchEvent(evMessage);

  return true;
}

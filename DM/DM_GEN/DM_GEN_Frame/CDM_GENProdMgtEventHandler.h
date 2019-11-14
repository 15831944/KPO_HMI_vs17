// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENPRODMGTEVENTHANDLER_41E4FE110025_INCLUDED
#define _INC_CDM_GENPRODMGTEVENTHANDLER_41E4FE110025_INCLUDED

#include "CDM_GENEventHandler.h"

//This class will handle the these events coming from L3 or 
//HMI: heat schedule update, grade code changes and so on.
class CDM_GENProdMgtEventHandler 
: public CDM_GENEventHandler
{
public:

	CDM_GENProdMgtEventHandler();

	virtual ~CDM_GENProdMgtEventHandler();

  //This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage& evMessage);

  
	bool doGenParameterUpdate(CEventMessage& evMessage);

	bool doGenOrderStatusUpdate(CEventMessage& evMessage);

	bool doGenHeatStatusUpdate(CEventMessage& evMessage);

	bool doGenAnalysisData(CEventMessage& evMessage);

	//This is the event handler for the event - 
	//HEAT_SCHEDULE_UPDATE, which comes from the server 
	//ARCHIVER_GEN. The behavior of this operation is just to 
	//send three events: EAF_HEAT_SCHEDULE_UPDATE, 
	//AOD_HEAT_SCHEDULE_UPDATE, and LF_HEAT_SCHEDULE_UPDATE 
	//to DM_EAF, DM_AOD and DM_LF respectively. It seems that 
	//there is no event related data for these three events.
	bool doGenHeatScheduleUpdate(CEventMessage& evMessage);

	//This is the event handler for the event - 
	//PRODUCTION_ORDER_DATA_UPDATE, which comes from the 
	//server ARCHIVER_GEN. The behavior of this operation is 
	//just to send three events: 
	//EAF_PRODUCTION_ORDER_DATA_UPDATE,AOD_PRODUCTION_ORDER_DA
	//TA_UPDATE, and LF_PRODUCTION_ORDER_DATA_UPDATE to 
	//DM_EAF, DM_AOD and DM_LF respectively. It seems that 
	//there is no event related data for these three events.
	bool doGenProductionOrderDataUpdate(CEventMessage& evMessage);

};

#endif /* _INC_CDM_GENPRODMGTEVENTHANDLER_41E4FE110025_INCLUDED */

// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_EVENTHANDLER_41C7086801BE_INCLUDED
#define _INC_CDH_EVENTHANDLER_41C7086801BE_INCLUDED

#include "CEventHandler.h"

#include "CEventMessage.h"
#include "CGC_Plant_Container.h"
#include "CHeatDataConverter.h"
#include "CDataConversion.h"
#include "CStatusHandler.h"
#include "CGT_GRADE_SAMPLE_FLAG.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_HEAT_REF.h"
#include "CHeatStatusContainer.h"

class CDH_Task;
class CSMC_DataProvider_Impl;
class CInterfaceAccess_Task;

class CDH_EventHandler 
: public CEventHandler
{
public:
	void setpDHTask(CInterfaceAccess_Task* value);

	CDH_EventHandler();

	std::string generateDataKey(const std::string& DataKey, const std::string& ActKey, const std::string &Message);

	std::string generateDataKey(CEventMessage& Event, const std::string &ActKey);

	virtual bool sendAdditionalEvents(CEventMessage& Event);

	//removing all cylic trigger calls from respective 
	//handler for the respective ProductID
	bool removeAllCyclicTriggerCalls(CEventMessage& Event);

	//adding cylic trigger call o respective handler
	bool handleCyclicTriggerCall(CEventMessage& Event    );

	virtual bool beforeDispatchEvent(CEventMessage& Event);

	virtual bool afterDispatchEvent(CEventMessage& Event);

	virtual ~CDH_EventHandler();

	CDH_EventHandler(CInterfaceAccess_Task *pIntAccess);

	//Sends the event Event to corresponding destinations.
	bool dispatchEvent(const std::string& SenderName, const std::string & DestinationName, CEventMessage& Event);

  virtual bool handleEvent(const FRIESEvent& Event);

	virtual bool afterHandleEvent(const FRIESEvent& Event);

	virtual bool beforeHandleEvent(const FRIESEvent& Event);

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage &evMessage) = 0;

protected:
	DynamicAny::DynAnyFactory_var m_DynAnyFact;

	CInterfaceAccess_Task* m_pDHTask;

	std::string m_DestinationName;

	//PlantID converter between L1<-->L2
	CGC_Plant_Container* m_pGC_Plant_Container;
  CGT_GRADE_SAMPLE_FLAG* m_pGT_GRADE_SAMPLE_FLAG;
	CHeatDataConverter* m_pHeatDataConverter;
  CPD_HEAT_DATA* m_pPD_HEAT_DATA;

  bool checkInternalData(const std::string& TlgName, std::string& HeatId, std::string& TreatId, std::string Plant, std::string& CustHeatId, std::string& CustTreatId);

  CStatusHandler m_StatusHandler;

};

#endif /* _INC_CDH_EVENTHANDLER_41C7086801BE_INCLUDED */

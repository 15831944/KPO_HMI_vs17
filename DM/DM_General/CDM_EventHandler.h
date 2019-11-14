// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EVENTHANDLER_41C7086801BE_INCLUDED
#define _INC_CDM_EVENTHANDLER_41C7086801BE_INCLUDED

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"
#include "iModelResults_s.hh"


#include "CEventMessage.h"
#include "CEventHandler.h"
#include "iDH_Interface_s.hh"

#include "CDM_Task.h"


#if defined (HANDLE_EVENT_DATA_FORWARD)
 #undef HANDLE_EVENT_DATA_FORWARD
#endif
#define HANDLE_EVENT_DATA_FORWARD(action) \
	if (action == evMessage.getMessage()) \
			     return doDataEventForward(evMessage);


class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;
class CDM_ProductManagementInterface_Impl;


class CDM_CyclicTriggerCallHandler;

class CDM_EventHandler 
: public CEventHandler
{
public:

	bool setpModelResultInterface(CEventMessage& Event);
	bool doModelEvent(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");
	bool doModelEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");
	bool copyModelEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");
	bool copyModelEventData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	bool doDMDataEvent(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");
	bool doDMDataEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");
	bool copyDMDataEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");
	bool copyDMDataEventData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	bool doDataEventForward(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");

	bool doDataEventForward(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	virtual bool sendAdditionalEvents(CEventMessage& Event);

	//removing all cylic trigger calls from respective 
	//handler for the respective ProductID
	bool removeAllCyclicTriggerCalls(CEventMessage& Event);
  bool removeAllCyclicTriggerCalls(const std::string& ProductID);

	//adding cylic trigger call o respective handler
	bool handleCyclicTriggerCall(CEventMessage& Event    );

  // reset cyclic trigger and wait for cycle time to send event
  bool resetCyclicTriggerCall(CEventMessage& Event);

  bool startCyclicTriggerCalls(CEventMessage& Event);

	virtual bool beforeDispatchEvent(CEventMessage& Event);

	virtual bool afterDispatchEvent(CEventMessage& Event);

	CDM_DataInterface_Impl* m_pDataInterface;

	CDM_PlantManagementInterface_Impl* m_pPlantManagementInterface;

	CDM_ProductManagementInterface_Impl* m_pProductManagementInterface;

	virtual ~CDM_EventHandler();

	CDM_EventHandler(CDM_Task *pDM_Task);

	virtual bool checkEventAssignment(CEventMessage& Event    );

	//Sends the event Event to corresponding destinations.
  bool dispatchEvent(CEventMessage& Event);

	virtual bool handleEvent(const FRIESEvent& Event);

	//This hook operation would be called automatically by 
	//handleEvent( FRISEVENT &event) 
	//when an event is received. And this operation must be 
	//implemented by the user or client
	//in order to use it.
	virtual bool handleEvent(CEventMessage &evMessage) = 0;

	//This operation just acquires the 3 interfaces to the 
	//Data Provider of the local Data Manager via m_pDMTask,
	//because CDM_Task already intitializes thems.
	virtual void init();

protected:

	iModelResults_var m_pModelResultInterface;

	//Sends additional events in container to destinations in ini-file.
  bool dispatchEvents(CEventMessage& Event, std::vector<std::string>& Messages);

	std::string generateDataKey(const std::string& DataKey, const std::string& ActKey, const std::string &Message = "");

	std::string generateDataKey(CEventMessage& Event, const std::string &ActKey);


  DynamicAny::DynAnyFactory_var m_DynAnyFact;

	bool validateProductInterfaceData(CEventMessage& Event, const std::string& Key = "");

	bool validatePlantInterfaceData(CEventMessage& Event, const std::string& Key = "");

	bool validateDataInterfaceData(CEventMessage& Event, const std::string& Key = "");

	CDM_Task* m_pDMTask;

	//This operation internally calls the operation 
	//copyDataeEventData to batch processing
	// a list of the name-value pairs , then sends the event 
	//to corresponding destination(s).
	bool doDataEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = ""    );

	//This operation first fetch event-related data via CORBA 
	//interface, then send the event to
	// corresponding destination(s) for a particular key-name 
	//pair.
	bool doDataEvent(CEventMessage& Event, const std::string& Name = "", const std::string& Key = ""    );

	//This operation does the actual work for  plant related 
	//event handling. And this is a batch operation
	//since the data extraction is in batch mode.
	bool doPlantEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = ""    );

	//This operation does the actual work for  plant related 
	//event handling.
	bool doPlantEvent(CEventMessage& Event, const std::string& Name = "", const std::string& Key = ""    );

	//This operation does the actual work for  PRODUCT 
	//related event handling. And this is a batch operation
	//since the data extraction is in batch mode.
	bool doProductEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = ""    );

	//This operation does the actual work for  PRODUCT 
	//related event handling.
	bool doProductEvent(CEventMessage& Event, const std::string& Name = "", const std::string& Key = ""    );

	//Batch fetch data via Level 1 datahandler CORBA 
	//interface.
	bool copyDataEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");

	//Fetch data via Level 1 datahandler CORBA interface.
	bool copyDataEventData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	//Batch fetch plant related data via Level 1 Data Handler 
	//CORBA interface into the local Data Manager.
	bool copyPlantEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");

	//Fetch plant related data via Level 1 Data Handler CORBA 
	//interface into the local DM Data Provider.
	bool copyPlantEventData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	//Batch fetch plant related data via Level 1 Data Handler 
	//CORBA interface into the local Data Manager.
	bool copyProductEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key = "");

	//Fetch plant related data via Level 1 Data Handler CORBA 
	//interface into the local Data Manager.
	bool copyProductEventData(CEventMessage& Event, const std::string& Name = "", const std::string& Key = "");

	//This operation just deletes the key-related data from 
	//the Data Provider of the General Data Manager.
	//bool resetDataEventData(CEventMessage& Event, const std::string& Key = "");

	//This operation just deletes the key-related data from 
	//the Data Provider of the Plant Manager 
	//Data Manager.
	//bool resetProductEventData(CEventMessage& Event, const std::string& Key = "");

	//This operation just deletes the key-related data from 
	//the Data Provider of the Plant Manager 
	//Data Manager.
	//bool resetPlantEventData(CEventMessage& Event, const std::string& Key = "");

	//This operation resets or purges the 3 Data Providers 
	//within a particular Data Manager.
	//bool resetData(CEventMessage& Event, const std::string& Key = "");

  virtual bool doOnUnknownProduct(CEventMessage& Event);
  
  bool handleUnknownProduct(CEventMessage& Event);

};

#endif /* _INC_CDM_EVENTHANDLER_41C7086801BE_INCLUDED */

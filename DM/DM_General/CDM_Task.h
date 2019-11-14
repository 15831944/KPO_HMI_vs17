// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_TASK_416A957801CC_INCLUDED
#define _INC_CDM_TASK_416A957801CC_INCLUDED

#include "iDH_Interface_s.hh"
#include "iModelResults_s.hh"

//#include "cCorbaProxyAdapter.h"//ffra31102018
#include "CProxyManager.h"

#include "CSMC_FrameTask.h"

#include "CDM_ProductManager.h"
#include "CDM_PlantManager.h"

#include "CSMC_EventValidator.h"


class CDM_ProductManagementInterface_Impl;
class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;
class CDM_EventLogHandlerAdapter;

class CDM_EventLogHandler;
class CPD_HEAT_DATA;
class CPD_HEAT_REF;
class CPD_HEAT_PLANT_REF;
class CGC_Plant_Container;
class CGC_STATUS;

class CDM_Task 
: public CSMC_FrameTask
{
public:
  virtual bool setProductionPractice(CEventMessage& Event, std::string& Grade);
  virtual bool setProductData(CEventMessage& Event);
  bool doOnDeleteProductFromInterface(const std::string& ProductID);

  // read customer data from database
  bool getCustData(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, std::string& HEATID_CUST, std::string& TREATID_CUST);

  std::string getExternalHeatID(const std::string& ID);
  std::string getExternalTreatID(const std::string& ID);
  virtual long getEventLogDestination(const std::string& ID);

  sEventLogMessage initEventLogMessage(const std::string& File, long Line, const std::string& ID);

  sEventLogMessage initEventLogMessage(const std::string& File, long Line); 

  virtual bool isProductInProduction(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, std::string& OrderId);
  bool deleteDBClasses();
  virtual bool initDBClasses();
  bool handleUnknownProduct(CEventMessage& Event, const std::string& CustHeatID, const std::string& CustTreatID, const std::string& PlantID);

  virtual void doOnComponentStartup();

	virtual void sendInitialEvents();

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string& Message, long Level);

	std::set<std::string> getRuleSetNames(const std::string& Key);

	virtual std::string getProcessState(const std::string& ID) = 0;

	void copyDataFromProductToPlantInterface(const std::string& SourceKey, const std::string& DestKey, std::vector<std::string> DataList);

	void EventLog(CEventMessage& Event);

	void registerEventLogHandler(CDM_EventLogHandler *EventLogHandler);

  //
  // Data Handler proxy manager.
  //
  CProxyManager<DH::iDH_Interface>* m_pDHProxyManager;

  CProxyManager<iModelResults>* m_pModelResultsProxyManager;

  CProxyManager<DM::iDM_Interface>* m_pDMProxyManager;

 /* cCorbaProxyAdapter<iModelResults> * m_ModelResultInterface;*/ //ffra31102018

	CDM_PlantManager* getpPlantManager();

	void setpPlantManager(CDM_PlantManager* value);

	CDM_ProductManager* getpProductManager();

	void setpProductManager(CDM_ProductManager* value);

	DH::iDH_Interface_var m_pDH_Interface;

	iModelResults_var m_pModelResultInterface;

	DM::iDM_Interface_var m_pDM_Interface;

  virtual DH::iDH_Interface_var& getpDH_Interface(const std::string& ServerName);

  virtual iModelResults_var& getpModelResultInterface(const std::string &ServerName);

  virtual DM::iDM_Interface_var& getpDM_Interface(const std::string &ServerName, const std::string& InterfaceTypeName = "");


	CDM_Task();

	virtual CDM_DataInterface_Impl* getpDataInterface();
	virtual CDM_ProductManagementInterface_Impl* getpProductManagementInterface();
	virtual CDM_PlantManagementInterface_Impl* getpPlantManagementInterface();

	CDM_ProductManagementInterface_Impl* m_pProductManagementInterface;

	CDM_DataInterface_Impl* m_pDataInterface;

	CDM_PlantManagementInterface_Impl* m_pPlantManagementInterface;

	virtual ~CDM_Task();

  std::string getPlantFromEventMessage(CEventMessage& Event);
  long getPlantNoFromEventMessage(CEventMessage& Event);


protected:
	CPD_HEAT_DATA       * m_pPD_HEAT_DATA;
  CPD_HEAT_REF        * m_pPD_HEAT_REF;
  CPD_HEAT_PLANT_REF  * m_pPD_HEAT_PLANT_REF;
  CGC_STATUS          * m_pGC_STATUS;

	CGC_Plant_Container * m_pGC_Plant_Container;

	virtual void doOnTaskWorkingError();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.

	CSMC_EventValidator m_Validator;

	virtual void registerEventLogHandlers() = 0;

	CDM_EventLogHandlerAdapter* m_pEventLogHandlerAdapter;
	CDM_ProductManager * m_pProductManager;
	CDM_PlantManager * m_pPlantManager;

	//The purpose of using this operation is to define a 
	//general event handler registration interface 
	//which will be invoked automatically by the containing 
	//class CDM_Task constructor, and it must be overriden by 
	//specialized classes.
	virtual void registerEventHandlers() = 0;


	//This operation is used to initialize the three external 
	//CORBA interfaces: L1, HMI, and LAB.
	//Also additional CORBA interface(s) ,if any, can be 
	//added to the derived version of this operation.
	virtual void initCORBAInterfaces();

	//Virtual task start up method. Called by the 
	//runtimeStartUp method after starting up the subtasks. 
	//The default implementation sets only the state of the 
	//task to Running. Note that the work state is not set.
	//
	//This method may be redefined if the task represents for 
	//example a thread or a process. In this case, the method 
	//redefinition would start thread execution.
	virtual void ownStartUp();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual void initManager();
 
};

#endif /* _INC_CDM_TASK_416A957801CC_INCLUDED */

// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LF_TASK_40C5C0B8018F_INCLUDED
#define _INC_CDM_LF_TASK_40C5C0B8018F_INCLUDED

#include "CDM_LFPlantManager.h"
#include "CDM_LFProductManager.h"


#include "CDM_LFDBManagerTask.h"
#include "CDM_Task.h"

class CDM_LFModelResultEventHandler;
class CDM_LFModesAndAvailabilitiesEventHandler;
class CDM_LFMaterialEventHandler;
class CDM_LFPurposeEventHandler;
class CDM_LFTreatmentManagementEventHandler;
class CDM_LFSignalsAndMeasurementsEventHandler;

class CDM_LFTask : public CDM_Task
  
{
public:
	virtual void sendInitialEvents();

	virtual std::string getProcessState(const std::string& ID);

	CDM_LFProductManager ProductManager;

	CDM_LFPlantManager PlantManager;

	static  CDM_LFTask* getInstance();



  virtual ~CDM_LFTask();

protected:
  // set transfer car
  bool setProductData(CEventMessage& Event);

  virtual void registerEventLogHandlers();

	//The purpose of using this operation is to define a 
	//general event handler registration interface 
	//which will be invoked automatically by the containing 
	//class CDM_Task constructor, and it must be overriden by 
	//specialized classes.
	virtual void registerEventHandlers();

	// Don't allow explicit instantiation. The only way to 
	//get this class instantiated is 
	//to call CDM_AODTask::getInstance( ).
  CDM_LFTask();



	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

  virtual bool isProductInProduction(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, std::string& OrderID);


private:
	std::vector<std::string> m_GasDataList;





	 static CDM_LFTask* m_Instance;


};

#endif /* _INC_CDM_LF_TASK_40C5C0B8018F_INCLUDED */

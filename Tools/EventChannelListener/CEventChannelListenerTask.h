// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAF_TASK_40C5C0B8018F_INCLUDED
#define _INC_CDM_EAF_TASK_40C5C0B8018F_INCLUDED

#include "CDM_EAFPlantManager.h"
#include "CDM_EAFProductManager.h"


#include "CDM_Task.h"

class CDM_EAFAnalysisEventHandler;
class CDM_EAFMaterialEventHandler;
class CDM_EAFModelResultEventHandler;
class CDM_EAFModesAndAvailabilitiesEventHandler;
class CDM_EAFSignalsAndMeasurementsEventHandler;
class CDM_EAFTreatmentManagementEventHandler;
class CDM_EAFPurposeEventHandler;

class CDM_EAFTask : public CDM_Task
  
{
public:
	virtual void sendInitialEvents();

	virtual std::string getProcessState(const std::string& ID);

	static  CDM_EAFTask* getInstance();


  virtual ~CDM_EAFTask();

protected:
	virtual void registerEventLogHandlers();

	//The purpose of using this operation is to define a 
	//general event handler registration interface 
	//which will be invoked automatically by the containing 
	//class CDM_Task constructor, and it must be overriden by 
	//specialized classes.
	virtual void registerEventHandlers();

	// Don't allow explicit instantiation. The only way to 
	//get this class instantiated is 
	//to call CDM_EAFTask::getInstance( ).
  CDM_EAFTask();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

private:
  static CDM_EAFTask* m_Instance;
};

#endif /* _INC_CDM_EAF_TASK_40C5C0B8018F_INCLUDED */

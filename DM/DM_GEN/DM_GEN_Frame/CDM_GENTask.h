// Copyright (C) 1999 - 2000 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GEN_TASK_40C5C0B8018F_INCLUDED
#define _INC_CDM_GEN_TASK_40C5C0B8018F_INCLUDED


#include "CDM_Task.h"

class CDM_GENPlantManager;
class CDM_GENProductManager;
class CDM_GENHMIEventHandler;
class CDM_GENL3EventHandler;
class CDM_GENModesAndAvailabilitiesEventHandler;
class CDM_GENTreatmentManagementEventHandler;

class CDM_GENTask : public CDM_Task
  
{
public:
	static  CDM_GENTask* getInstance();

  virtual ~CDM_GENTask();

	virtual std::string getProcessState(const std::string& ID);


protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	CDM_GENTask();

	virtual void registerEventLogHandlers();

  //The purpose of using this operation is to define a 
	//general event handler registration interface 
	//which will be invoked automatically by the containing 
	//class CDM_Task constructor, and it must be overriden by 
	//specialized classes.
	virtual void registerEventHandlers();


private:
	  static CDM_GENTask* m_Instance;
};

#endif /* _INC_CDM_GEN_TASK_40C5C0B8018F_INCLUDED */

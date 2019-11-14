// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMD_TASK_40C5C0B8018F_INCLUDED
#define _INC_CDM_HMD_TASK_40C5C0B8018F_INCLUDED

#include "CDM_HMDPlantManager.h"
#include "CDM_HMDProductManager.h"
#include "CDM_Task.h"
#include "CDM_HMDDBManagerTask.h"

class CDM_HMDMaterialEventHandler;
class CDM_HMDAnalysisEventHandler;
class CDM_HMDSignalsAndMeasurementsEventHandler;
class CDM_HMDModesAndAvailabilitiesEventHandler;
class CDM_HMDTreatmentManagementEventHandler;
class CDM_HMDPurposeEventHandler;
class CDM_HMDEventLogHandler;

class CDM_HMDModelResultEventHandler;

//##ModelId=45139A710306
class CDM_HMDTask : public CDM_Task
  
{
public:
	//##ModelId=45139A710310
	virtual std::string getProcessState(const std::string& ID);

	//##ModelId=45139A710313
	virtual void sendInitialEvents();

	//##ModelId=45139A710331
	static  CDM_HMDTask* getInstance();



  //##ModelId=45139A710333
  virtual ~CDM_HMDTask();

protected:
	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	//##ModelId=45139A710335
	virtual bool initialize();

	//##ModelId=45139A710337
	virtual void registerEventLogHandlers();

	//The purpose of using this operation is to define a 
	//general event handler registration interface 
	//which will be invoked automatically by the containing 
	//class CDM_Task constructor, and it must be overriden by 
	//specialized classes.
	//##ModelId=45139A710339
	virtual void registerEventHandlers();

	// Don't allow explicit instantiation. The only way to 
	//get this class instantiated is 
	//to call CDM_HMDTask::getInstance( ).
	//##ModelId=45139A71033B
  CDM_HMDTask();

private:
	//##ModelId=45C9A0C70258
	std::vector<std::string> m_GasDataList;

	//##ModelId=45C9A46A0348
	 static CDM_HMDTask* m_Instance;


};

#endif /* _INC_CDM_HMD_TASK_40C5C0B8018F_INCLUDED */

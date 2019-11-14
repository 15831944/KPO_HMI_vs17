// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTSM_TASK_434E793E0174_INCLUDED
#define _INC_CTSM_TASK_434E793E0174_INCLUDED

#include "iDM_Interface_s.hh"

#include "cCBS_StdEvent_Task.h"

#include "CProxyManager.h"

#include "CSMC_FrameTask.h"

class CTsmBaseApplication;
class CEventMessage;
class cCBS_StdEvent_Task;

class CTSM_Task 
: public CSMC_FrameTask
{
public:

  static void getEventReceiverNames(std::vector<std::string>& EventReceiverNames, const std::string & EventReceiverName);
  static void changeEventTransmitterName(CEventMessage& evMessage);

	CTsmBaseApplication* getpTsmApplication() const;

	virtual ~CTSM_Task();

	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	virtual void log(const std::string& Message, long Level);

	virtual DM::iDM_Interface_var& getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName);

protected:
	CTSM_Task();

	DM::iDM_Interface_var m_pDM_Interface;

	cCBS_StdEvent_Task* m_pEventTask;

	std::auto_ptr<CTsmBaseApplication> m_pTsmApplication;

	CProxyManager<DM::iDM_Interface>* m_pDM_ProxyManager;

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

};

#endif /* _INC_CTSM_TASK_434E793E0174_INCLUDED */

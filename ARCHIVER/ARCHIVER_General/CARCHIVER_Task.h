// Copyright (C) 2007 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_TASK_42971B6702B7_INCLUDED
#define _INC_CARCHIVER_TASK_42971B6702B7_INCLUDED

#include "iDM_Interface_s.hh"

#include "CProxyManager.h"
#include "CSMC_FrameTask.h"

//##ModelId=42971B6702B7
class CARCHIVER_Task 
: public CSMC_FrameTask
{
public:

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

	//##ModelId=42971EF40051
	virtual void setCORBAConnections();

	//##ModelId=42971EE1020C
	virtual DM::iDM_Interface_var& getpDM_Interface();

	//##ModelId=45F6E0130110
	virtual void setpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName);

	//##ModelId=42971E4102FF
	virtual ~CARCHIVER_Task();

	//##ModelId=42971E420005
	CARCHIVER_Task();
protected:
	//Dirceting Task relevant programming outputs to 
	//cCBS_StdLog_Task depending on Task Trace Level.
	//##ModelId=42B8117302EB
	virtual void log(const std::string& Message, long Level);

	//##ModelId=42971EC80120
	DM::iDM_Interface_var m_pDM_Interface;

	//##ModelId=4297279703D6
	CProxyManager<DM::iDM_Interface>* m_pDM_ProxyManager;

};

#endif /* _INC_CARCHIVER_TASK_42971B6702B7_INCLUDED */

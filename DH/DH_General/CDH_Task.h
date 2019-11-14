// Copyright (C) 2005 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDH_TASK_4253CDEE012D_INCLUDED
#define _INC_CDH_TASK_4253CDEE012D_INCLUDED


#include <string>
#include "iDM_Interface_s.hh"

#include "CProxyManager.h"
#include "CSMC_FrameTask.h"
#include "cCBS_StdInitBase.h"

class CSMC_DataProvider_Impl;

class CDH_Task 
: public CSMC_FrameTask
{

public:

	virtual ~CDH_Task();

  virtual void log(const std::string& Message, long Level);

protected:
	virtual void setCORBAConnections() = 0;

	CProxyManager<DM::iDM_Interface>* m_pDMProxyManager;

	CDH_Task();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

};

#endif /* _INC_CDH_TASK_4253CDEE012D_INCLUDED */

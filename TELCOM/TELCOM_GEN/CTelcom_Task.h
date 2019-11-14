// Copyright (C) 2007 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_TASK_45AB47FC0056_INCLUDED
#define _INC_CTELCOM_TASK_45AB47FC0056_INCLUDED

#include "CSMC_FrameTask.h"
#include "CProxyManager.h"
#include "iDH_Telcom_s.hh"

class CTelcom_Task : public CSMC_FrameTask, public cCBS_Thread
{
public:
	DH_Telcom::iDH_Telcom_var& getpDH_Interface(std::string& ServerName, const std::string & InterfaceTypeName = "");

	DH_Telcom::iDH_Telcom_var m_pDH_Interface;

	virtual void setCORBAConnections() = 0;

	CTelcom_Task();

	virtual ~CTelcom_Task();

protected:
	virtual bool initialize();

  CProxyManager<DH_Telcom::iDH_Telcom>* m_pDHProxyManager;

  virtual bool checkDBConnection();

};

#endif /* _INC_CTELCOM_TASK_45AB47FC0056_INCLUDED */

// Copyright (C) 2005 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTERFACEACCESS_TASK_4586D82D034A_INCLUDED
#define _INC_CINTERFACEACCESS_TASK_4586D82D034A_INCLUDED

#include "iDH_Interface_s.hh"

#include "CDH_Task.h"

class CInterfaceAccess_Task 
: public CDH_Task
{
protected:
	CSMC_DataProvider_Impl* m_pInterface_OUT;

	DM::iDM_Interface_var m_pDM_Interface;

  DH::iDH_Interface_var m_pDH_Interface;

  CProxyManager<DH::iDH_Interface>* m_pDHProxyManager;

public:
	CSMC_DataProvider_Impl* getpInterface_OUT();

	virtual DM::iDM_Interface_var& getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName = "");

	virtual DH::iDH_Interface_var& getpDH_Interface(const std::string& ServerName, const std::string& InterfaceTypeName = "");

	CInterfaceAccess_Task();

	virtual ~CInterfaceAccess_Task();

};

#endif /* _INC_CINTERFACEACCESS_TASK_4586D82D034A_INCLUDED */

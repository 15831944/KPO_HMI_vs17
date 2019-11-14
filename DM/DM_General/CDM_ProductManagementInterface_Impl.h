// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_PRODUCTMANAGEMENTINTERFACE_IMPL_416A96F00323_INCLUDED
#define _INC_CDM_PRODUCTMANAGEMENTINTERFACE_IMPL_416A96F00323_INCLUDED

#include "iDM_Interface_s.hh"
#include "iEventData_s.hh"

#include "CSMC_DataProvider_Impl.h"
#include "CDM_Task.h"

#include "CDateTime.h"

class CDM_ProductManagementInterface_Impl 
  : public CSMC_DataProvider_Impl
  , public POA_DM::iDM_Interface
{

public:

  CDM_ProductManagementInterface_Impl();

  void setpDM_Task(CDM_Task * pDM_Task);
  
	virtual void afterDataAccess(const std::string & Key,const std::string & Name);

	virtual void beforeDataAccess(const std::string & Key,const std::string & Name);

	virtual long onComplete(const std::string & Key,const std::string & Action);

	virtual void onIndicate(const std::string & Key);

	virtual void onDeleteDataKey(const std::string & Key);

  virtual ::CORBA::Boolean setProductFromTreatmentPos(const char* TreatmentPosition, ::sEventData_out EventData);

private:

  CDM_Task * m_pDM_Task;


};

#endif /* _INC_CDM_PRODUCTMANAGEMENTINTERFACE_IMPL_416A96F00323_INCLUDED */

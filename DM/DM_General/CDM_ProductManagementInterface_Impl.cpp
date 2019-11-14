// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iEventData_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "CDateTime.h"


#include "CDM_ProductManagementInterface_Impl.h"

CDM_ProductManagementInterface_Impl::CDM_ProductManagementInterface_Impl()
: m_pDM_Task(0)
{
}

void CDM_ProductManagementInterface_Impl::setpDM_Task(CDM_Task * pDM_Task)
{
  m_pDM_Task = pDM_Task;
}


long CDM_ProductManagementInterface_Impl::onComplete(const std::string & Key,const std::string & Action)
{
	return CData_Provider::onComplete(Key,Action);
}

void CDM_ProductManagementInterface_Impl::onIndicate(const std::string & Key)
{
	CData_Provider::onIndicate(Key);
}



void CDM_ProductManagementInterface_Impl::afterDataAccess(const std::string & Key,const std::string & Name)
{
	CData_Provider::afterDataAccess(Key,Name);
}

void CDM_ProductManagementInterface_Impl::beforeDataAccess(const std::string & Key,const std::string & Name)
{
  CData_Provider::beforeDataAccess(Key,Name);
}

void CDM_ProductManagementInterface_Impl::onDeleteDataKey(const std::string & Key)
{
  log("INFO: DataKey from ProductManagementInterface removed: " + Key,3);
  if (m_pDM_Task)
  {
    m_pDM_Task->doOnDeleteProductFromInterface(Key);
  }
	
}

::CORBA::Boolean CDM_ProductManagementInterface_Impl::setProductFromTreatmentPos(const char* TreatmentPosition, ::sEventData_out EventData)
{
  return false;
}
// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDDBMANAGERTASK_INCLUDED
#define _INC_CDM_HMDDBMANAGERTASK_INCLUDED

#include "CDM_HMDDBManager.h"
#include "CDM_DBManagerTask.h"

class CDM_HMDDBManagerTask 
: public CDM_DBManagerTask
{
private:
  static CDM_HMDDBManagerTask* m_Instance;
public:
  static  CDM_HMDDBManagerTask* getInstance();

  CDM_HMDDBManager* getDBManager();

	cCBS_StdConnection* getStdConnection();

  CDM_DataInterface_Impl* getpDataInterface();

  CDM_ProductManagementInterface_Impl* getpProductManagementInterface();

  CDM_PlantManagementInterface_Impl* getpPlantManagementInterface();

  void handleDBConnectionError();

  CDM_HMDDBManagerTask();
  virtual ~CDM_HMDDBManagerTask();

protected:
  CDM_HMDDBManager* m_pDM_HMDDBManager;

  bool initialize();

  void doOnTaskWorkingError();

  void ownRunDown();

  void ownStartUp();

  void getOwnStateDetails(CORBA::String_out details);

  void initDBManager();

};

#endif /* _INC_CDM_HMDDBMANAGERTASK_INCLUDED */

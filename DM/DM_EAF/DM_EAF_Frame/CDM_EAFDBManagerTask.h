// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFDBMANAGERTASK_INCLUDED
#define _INC_CDM_EAFDBMANAGERTASK_INCLUDED

#include "CDM_DBManagerTask.h"
#include "CDM_EAFDBManager.h"


class CDM_EAFDBManagerTask 
: public CDM_DBManagerTask
{
  private:
  static CDM_EAFDBManagerTask* m_Instance;
public:
  static  CDM_EAFDBManagerTask* getInstance();

   CDM_EAFDBManager* getDBManager();

  cCBS_StdConnection* getStdConnection();

  CDM_DataInterface_Impl* getpDataInterface();

  CDM_ProductManagementInterface_Impl* getpProductManagementInterface();

  CDM_PlantManagementInterface_Impl* getpPlantManagementInterface();

  void handleDBConnectionError();

  CDM_EAFDBManagerTask();
  virtual ~CDM_EAFDBManagerTask();

protected:
  CDM_EAFDBManager* m_pDM_EAFDBManager;

  bool initialize();

  void doOnTaskWorkingError();

  void ownRunDown();

  void ownStartUp();

  void initDBManager();

};

#endif /* _INC_CDM_EAFDBMANAGERTASK_INCLUDED */

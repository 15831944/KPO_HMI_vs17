// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFDBMANAGERTASK_INCLUDED
#define _INC_CDM_LFDBMANAGERTASK_INCLUDED

#include "CDM_LFDBManager.h"
#include "CDM_DBManagerTask.h"

class CDM_LFDBManagerTask 
: public CDM_DBManagerTask
{
private:
  static CDM_LFDBManagerTask* m_Instance;
public:
  static  CDM_LFDBManagerTask* getInstance();

  CDM_LFDBManager* getDBManager();

  cCBS_StdConnection* getStdConnection();

  CDM_DataInterface_Impl* getpDataInterface();

  CDM_ProductManagementInterface_Impl* getpProductManagementInterface();

  CDM_PlantManagementInterface_Impl* getpPlantManagementInterface();

  void handleDBConnectionError();

  CDM_LFDBManagerTask();
  virtual ~CDM_LFDBManagerTask();

protected:
  CDM_LFDBManager* m_pDM_LFDBManager;

  bool initialize();

  void doOnTaskWorkingError();

  void ownRunDown();

  void ownStartUp();

  void initDBManager();

};

#endif /* _INC_CDM_LFDBMANAGERTASK_INCLUDED */

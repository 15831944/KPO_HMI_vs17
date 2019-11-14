// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENDBMANAGERTASK_INCLUDED
#define _INC_CDM_GENDBMANAGERTASK_INCLUDED

#include "CDM_DBManagerTask.h"
#include "CDM_GENDBManager.h"

class CDM_ProductManagementInterface_Impl;
class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;
class CDM_EventLogHandlerAdapter;


class CDM_GENDBManagerTask 
: public CDM_DBManagerTask
{
private:
  static CDM_GENDBManagerTask* m_Instance;
public:
  static  CDM_GENDBManagerTask* getInstance();

  CDM_GENDBManager* getDBManager();

  cCBS_StdConnection* getStdConnection();

  CDM_DataInterface_Impl* getpDataInterface();

  CDM_ProductManagementInterface_Impl* getpProductManagementInterface();

  CDM_PlantManagementInterface_Impl* getpPlantManagementInterface();

  void handleDBConnectionError();

  CDM_GENDBManagerTask();
  virtual ~CDM_GENDBManagerTask();

protected:
  CDM_GENDBManager* m_pDM_GENDBManager;

  bool initialize();

  void doOnTaskWorkingError();

  void ownRunDown();

  void ownStartUp();

  void initDBManager();

};

#endif /* _INC_CDM_GENDBMANAGERTASK_INCLUDED */

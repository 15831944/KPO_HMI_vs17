// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_DBMANAGERTASK_INCLUDED
#define _INC_CDM_DBMANAGERTASK_INCLUDED

#include "CEventMessage.h"
#include "CSMC_FrameTask.h"

class CDM_ProductManagementInterface_Impl;
class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;
class CDM_EventLogHandlerAdapter;


class CDM_DBManagerTask 
: public CSMC_FrameTask
{
public:
  virtual cCBS_StdConnection* getStdConnection() = 0;

  virtual void log(const std::string& Message, long Level);

  void EventLog(CEventMessage& Event);

  virtual CDM_DataInterface_Impl* getpDataInterface() = 0;

  virtual CDM_ProductManagementInterface_Impl* getpProductManagementInterface() = 0;

  virtual CDM_PlantManagementInterface_Impl* getpPlantManagementInterface() = 0;

  CDM_DBManagerTask();
  virtual ~CDM_DBManagerTask();

protected:
  virtual bool initialize();

  virtual void doOnTaskWorkingError();

  virtual void initDBManager() = 0;

};

#endif /* _INC_CDM_DBMANAGERTASK_INCLUDED */

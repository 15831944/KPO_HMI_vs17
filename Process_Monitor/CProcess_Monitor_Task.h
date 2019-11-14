// Copyright (C) 2009 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPROCESS_MONITOR_TASK_INCLUDED
#define _INC_CPROCESS_MONITOR_TASK_INCLUDED

#include <string>
#include "iDM_Interface_s.hh"

#include "CProxyManager.h"
#include "CEventMessage.h"
#include "cCBS_StdFrame_Task.h"
class cCBS_Connection;
class CProcess_Monitor_TelcomIntf_Impl;

class CModelResults_Impl;


class CProcess_Monitor_Task 
: public cCBS_StdFrame_Task
{
private:

  static CProcess_Monitor_Task* m_pInstance;

  // pointer of corba object of data manager
  // to get current model assigned to a product
  DM::iDM_Interface_var m_pDM_Interface;

  CProcess_Monitor_TelcomIntf_Impl *m_pTelcomIntf_Impl;

  void log(const std::string& _message, long _level = 3);

public:
  // creation of a respective telegram and send even
  bool sendEvent(std::string& PlantID, std::string& ProductID);

  CProcess_Monitor_TelcomIntf_Impl* getTelcom_Interface();

  cCBS_Connection* getConnection();

  // connect to data manager by sender name from event
  virtual DM::iDM_Interface_var& getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName = "");

  // container of possible data manager interfaces
  // from ini file
  CProxyManager<DM::iDM_Interface>* m_pDMProxyManager;

  static CProcess_Monitor_Task* getInstance();

  CProcess_Monitor_Task();

  virtual ~CProcess_Monitor_Task();

protected:
  // connect to data base
  void setDBConnections();

  // create and connect proxies for DM corba objects
  // set in ini file [DataManager]
  void bindProxies();

  // data base 
  cCBS_Connection* m_pConnection;

  // reading configuration from ini file on start-up of task
  bool initialize();

  void ownStartUp();
};

#endif /* _INC_CPROCESS_MONITOR_TASK_INCLUDED */

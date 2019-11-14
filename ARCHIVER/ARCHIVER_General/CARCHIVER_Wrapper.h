// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_WRAPPER_42971F5E0068_INCLUDED
#define _INC_CARCHIVER_WRAPPER_42971F5E0068_INCLUDED

#include <string>

#include "iDM_Interface_s.hh"
#include "CGC_Plant_Container.h"
#include "DEF_GC_HEAT_STATUS.h"// namespace with heat state definitions
#include "DEF_GC_ACTION_DEF.h"   // namespace with action definition
#include "CEventMessage.h"

class CARCHIVER_Task;

class CARCHIVER_Wrapper
{
protected:
  CGC_Plant_Container* m_pGC_Plant_Container;

  // std::string m_PlantID;

  virtual void deleteDBClasses() = 0;

  virtual void initDBClasses() = 0;

  DM::iDM_Interface_var m_pDM_Interface;

  void handleDBConnectionError();

  CARCHIVER_Task* m_pArchiverTask;

  // return trace level of log task
  long getTraceLevel();

  cCBS_ODBC_DBError m_lastError;

public:
  // return calculated duration in seconds based on a sDate-type-value
  double getDurationSince(DM::iDM_Interface_var& pDM_Interface,const std::string &Key, const char* Name);

  void setTaskAndInitDBClasses(CARCHIVER_Task* value);

  void setpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName);

  void logInterfaceDataList(DM::iDM_Interface_var& pDM_Interface,const std::string &Datakey = "");

  virtual ~CARCHIVER_Wrapper();

  CARCHIVER_Wrapper();

  void log(const std::string& Message,long Level);
  // to avoid creation of string object temporary if not necessary
  void log(const char* Message, long Level);

  bool handleSampleRef( const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, long PLANTNO, long MeasType, long SampleCounter);

  void initialSampleRef(sSampleRef &pSample);
    
  bool checkDBConnection();

  bool changeHeatStatus(CEventMessage& Event, long HeatStatusNo, long TreatmentPosition,bool commit);

  cCBS_StdConnection * getStdConnection();
};

#endif /* _INC_CARCHIVER_WRAPPER_42971F5E0068_INCLUDED */

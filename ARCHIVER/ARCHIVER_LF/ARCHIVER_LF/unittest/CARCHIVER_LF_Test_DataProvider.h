// Copyright (C) 2007 SMS Demag AG

#ifndef _INC_CARCHIVER_LF_Test_DataProvider_INCLUDED
#define _INC_CARCHIVER_LF_Test_DataProvider_INCLUDED

#include "CDateTime.h"
#include "iSMC_DataDefinitions_s.hh"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CARCHIVER_Task.h"
#include "CARCHIVER_Wrapper.h"

#include "CGCL_STIRR_PHASE.h"

#include "cCBS_Time.h"

class CARCHIVER_LF_Test_DataProvider
{
public:

	CARCHIVER_LF_Test_DataProvider(cCBS_Connection* _pConnection);

	virtual ~CARCHIVER_LF_Test_DataProvider();

  void setLFModelResult(const string& ForHeatID, const string& ForTreatID);

  void setComputerMode(const string& ForHeatID, const string& ForTreatID, long ElecMode, long StirrMode, long MatMode);
  
  void setLadleCar(const string& ProductID, const string& CarId, const string& LadleId);

  void setTempAndSteelSampleReq (const string& ProductID, bool TempReq, bool SteelSampleReq);

  void setProbeType(string ProductID, long ProbeType);

  std::string TrackerName;
  std::string ServerTask;
  std::string ServerName;

  sSampleData m_SampleData;

  cCBS_Connection* pConnection;

  DM::iDM_Interface_var m_pDM_Interface;
};

#endif 

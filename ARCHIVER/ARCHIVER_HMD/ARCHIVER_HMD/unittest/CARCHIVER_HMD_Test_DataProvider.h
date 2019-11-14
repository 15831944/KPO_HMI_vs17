// Copyright (C) 2007 SMS Demag AG

#ifndef _INC_CARCHIVER_HMD_Test_DataProvider_INCLUDED
#define _INC_CARCHIVER_HMD_Test_DataProvider_INCLUDED

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

#include "CGC_Plant_Container.h"
#include "CGC_PRODPRAC_DEF.h"
#include "CGC_HEAT_STAT.h"
#include "CPD_HEATDATA.h"
#include "CPD_LADLE_DATA.h"
#include "CPD_ANL.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT_PLANT_LONG.h"
#include "CPD_HEATDATA_LIQADD.h"
#include "CPP_HEAT.h"
#include "CPP_GRADE.h"
#include "CPP_ORDER.h"
#include "CPP_GRADE_PRODPRAC.h"
#include "CGC_PRODPRAC_DEF.h"

#include "cCBS_Time.h"

class CARCHIVER_HMD_Test_DataProvider
{
public:

	CARCHIVER_HMD_Test_DataProvider(cCBS_Connection* _pConnection);

	virtual ~CARCHIVER_HMD_Test_DataProvider();

  void setHMDModelResult(const string& ProdID, long InjType);

  std::string TrackerName;
  std::string ServerTask;
  std::string ServerName;

  cCBS_Connection* pConnection;

  DM::iDM_Interface_var m_pDM_Interface;
};

#endif 

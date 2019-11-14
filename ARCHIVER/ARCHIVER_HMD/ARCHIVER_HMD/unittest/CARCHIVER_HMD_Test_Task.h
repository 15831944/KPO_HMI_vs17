// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMD_Test_Task_INCLUDED
#define _INC_CARCHIVER_HMD_Test_Task_INCLUDED

#include "CARCHIVER_Task.h"
#include "CEventMessage.h"
#include "CARCHIVER_HMD_Test_DataProvider.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"

class CARCHIVER_HMD_Test_Task : public CARCHIVER_Task
{
public:
	CARCHIVER_HMD_Test_Task();

	static CARCHIVER_HMD_Test_Task* getInstance();
	
	virtual ~CARCHIVER_HMD_Test_Task();

  void setDataProvider(CARCHIVER_HMD_Test_DataProvider * pr);

  long getLastRowFromPD_Anl(const string& HeatID, const string& TreatID, const string& Plant, cCBS_Connection* pConnection);

protected:
	virtual bool initialize();

  CARCHIVER_HMD_Test_DataProvider * pTest_DataProvider;
private:
	static CARCHIVER_HMD_Test_Task* m_Instance;
};

#endif /* _INC_CARCHIVER_HMD_Test_Task_INCLUDED */

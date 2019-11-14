// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDPRODUCTMANAGER_413DC90903A3_INCLUDED
#define _INC_CDM_HMDPRODUCTMANAGER_413DC90903A3_INCLUDED

#include <string>
#include <vector>

#include "CDM_HMDSampleManager.h"
#include "CDM_ProductManager.h"
#include "CDM_SampleManager.h"

class CEventMessage;
class CDM_ProductManagementInterface_Impl;

//==========================================
//
//Handling ProductID's at ProductManagment interface 
//regarding to incoming events
//
//==========================================
class CDM_HMDProductManager : public CDM_ProductManager
{
public:
  virtual bool findActualProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderID);

	virtual bool changeComputerModeAvailabilities(CEventMessage& Event);

	virtual bool resetComputerModeAvailabilities(CEventMessage& Event);

	virtual bool resetProductManager(CEventMessage& Event);

	//setting powder consumption for a product
	virtual bool changeInjectionData(CEventMessage& Event);

  bool resetInjectionData(CEventMessage& Event);

	virtual bool changeAnalysisInformation(CEventMessage& Event);

	//setting sample data on samples and init
	virtual bool changeSampleData(CEventMessage& Event);

	//Changing Data of ProductID at ProductManagement 
	//interface , e.g. to time for StartOfHeat
	virtual bool changeProductInformation(CEventMessage& Event);

	virtual ~CDM_HMDProductManager();

	CDM_HMDProductManager(std::string& _prefix);

  void init(CDM_Task* pDMTask);

	CDM_HMDSampleManager * m_pSampleManager;

};

#endif /* _INC_CDM_HMDPRODUCTMANAGER_413DC90903A3_INCLUDED */

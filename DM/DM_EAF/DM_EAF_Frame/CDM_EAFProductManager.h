// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFPRODUCTMANAGER_413DC90903A3_INCLUDED
#define _INC_CDM_EAFPRODUCTMANAGER_413DC90903A3_INCLUDED

#include "CDM_ProductManager.h"
#include <string>

#include <vector>

class CEventMessage;
class CDM_ProductManagementInterface_Impl;

//Handling ProductID's at ProductManagment interface 
//regarding to incoming events
class CDM_EAFProductManager : public CDM_ProductManager
{
protected:
public:

  virtual void init(CDM_Task* pDMTask);

  virtual bool changeInjectionData(CEventMessage& Event);

  virtual bool resetInjectionData(CEventMessage& Event);

  virtual bool resetElectricalData(CEventMessage& Event);

  virtual bool resetBurnerData(CEventMessage& Event);

  virtual bool resetGasLanceData(CEventMessage& Event);

  virtual bool resetMatFeedData(CEventMessage& Event);

  virtual bool resetMasses(CEventMessage& Event);

  virtual bool resetMaterialData(CEventMessage& Event);

  virtual bool changeElectricalData(CEventMessage& Event);

  virtual bool changeGasData(CEventMessage& Event);

  virtual bool changeComputerModeAvailabilities(CEventMessage& Event);

  virtual bool resetProductManager(CEventMessage& Event);

  virtual bool resetComputerModeAvailabilities(CEventMessage& Event);

  virtual bool changeStirringData(CEventMessage& Event);

  virtual bool changeTappingData(CEventMessage& Event);

  virtual bool changeBurningData(CEventMessage& Event);

  virtual bool changeAnalysisInformation(CEventMessage& Event);

  virtual bool changeSampleInformation(CEventMessage& Event);

  virtual bool changeCoolingWaterData(CEventMessage& Event);

  virtual bool changeSetpoints(CEventMessage& Event);

  virtual bool changeMaterialFeedingData(CEventMessage& Event);

  //Changing Data of ProductID at ProductManagement 
  //interface , e.g. to time for StartOfHeat
  virtual bool changeProductInformation(CEventMessage& Event);

  virtual ~CDM_EAFProductManager();

	CDM_EAFProductManager();

  virtual bool doOnPhaseStateChange(CEventMessage& Event);

};

#endif /* _INC_CDM_EAFPRODUCTMANAGER_413DC90903A3_INCLUDED */

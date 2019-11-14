// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFPRODUCTMANAGER_413DC90903A3_INCLUDED
#define _INC_CDM_LFPRODUCTMANAGER_413DC90903A3_INCLUDED

#include "CDM_ProductManager.h"
#include <string>

#include <vector>

class CEventMessage;
class CDM_ProductManagementInterface_Impl;

//Handling ProductID's at ProductManagment interface 
//regarding to incoming events
class CDM_LFProductManager : public CDM_ProductManager
{
public:

  bool setProductData(const std::string& ProductID, long TreatmentPosition);

  // method can be used to fined product depened on event or directly about other equipments
  bool findProductByEquipment(CEventMessage& Event, std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderID);

	bool changeElectricalData(CEventMessage& Event);
  
	bool writeDiffStirringData(CEventMessage& Event, const std::string& ActData, const std::string  & NewData, double Value, std::string& StirringGasType);

	bool resetElectricalData(CEventMessage& Event);

	bool resetStirringData(CEventMessage& Event);

	bool changeComputerModeAvailabilities(CEventMessage& Event);

	bool resetComputerModeAvailabilities(CEventMessage& Event);

	bool resetProductManager(CEventMessage& Event);

	bool changeStirringData(CEventMessage& Event);

	bool changeTappingData(CEventMessage& Event);

	bool changeAnalysisInformation(CEventMessage& Event);

	bool changeSampleInformation(CEventMessage& Event);

	//Changing Data of ProductID at ProductManagement 
	//interface , e.g. to time for StartOfHeat
	bool changeProductInformation(CEventMessage& Event);

	//Register ProductID at ProductManagement interface by 
	//Event data
	bool changeSetpoints(CEventMessage& Event);

	~CDM_LFProductManager();

	CDM_LFProductManager();

  bool changeHeatingData(CEventMessage& Event);

  std::string getProductAtTransferCar(const std::string& TransferCarID);

  std::string CDM_LFProductManager::getTransferCarInOperatingPostion(CEventMessage& Event);

  void init(CDM_Task* pDMTask);

  virtual bool doOnPhaseStateChange(CEventMessage& Event);

};

#endif /* _INC_CDM_LFPRODUCTMANAGER_413DC90903A3_INCLUDED */

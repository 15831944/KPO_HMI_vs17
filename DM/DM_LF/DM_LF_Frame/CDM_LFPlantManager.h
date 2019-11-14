// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFPLANTMANAGER_413580AB023E_INCLUDED
#define _INC_CDM_LFPLANTMANAGER_413580AB023E_INCLUDED

#include <string>
#include "CDM_PlantManager.h"

#include <vector>

class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;

//Handling ModelNames (e.g. LF_1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_LFDataInterface_Impl;

//Handling ModelNames (e.g. LF_1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_LFPlantManager : public CDM_PlantManager
{
public:
	void initTransferCarStirringData(const std::string& DataKey);
  void initTransferCarComputerModeData(const std::string& DataKey);
  void initCoolingWaterData(const std::string& DataKey);
  void initTransferCarData(const std::string& DataKey);

	virtual void init(CDM_Task* pDMTask);

	//! in the following order:
	//! 1-in data interface   : with DataKey
	//! 2-in product interface: with ProductID
	//! 3-in plant interface  : actual in operating position
	virtual std::string getRelevantTransferCar(CEventMessage& Event);

	virtual bool changeElectricalData(CEventMessage& Event);

	virtual void resetStirringData(CEventMessage& Event);

	virtual std::string getPlantEquipmentData(const std::string& Equipment);

	virtual bool changeCoolingWaterData(CEventMessage& Event);

	virtual bool changeWasteGasData(CEventMessage& Event);

	virtual bool changeTransferCarData(CEventMessage& Event);

	virtual void resetPlantManager(CEventMessage& Event);

	virtual void resetComputerModes(CEventMessage& Event);

  virtual void resetPlantData(CEventMessage &Event);

	virtual bool changeLadleData(CEventMessage& Event);

	virtual bool changeStirringData(CEventMessage& Event);

	virtual bool changeTappingData(CEventMessage& Event);

	virtual bool changeAvailabilities(CEventMessage& Event);

	virtual bool changeComputerModes(CEventMessage& Event);

	virtual bool changePlantInformation(CEventMessage& Event);

	virtual ~CDM_LFPlantManager();

	CDM_LFPlantManager();


	virtual std::string getProductAtPlantEquipment(const std::string& Equipment);

  virtual std::string getPlantEquipmentOfProduct(const std::string& ProductID);


private:
	std::map<std::string,std::string> m_TransferCarPlantIdList;

};

#endif /* _INC_CDM_LFPLANTMANAGER_413580AB023E_INCLUDED */

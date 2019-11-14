// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFPLANTMANAGER_413580AB023E_INCLUDED
#define _INC_CDM_EAFPLANTMANAGER_413580AB023E_INCLUDED

#include <string>
#include "CDM_PlantManager.h"

#include <vector>

class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;

//Handling ModelNames (e.g. EAF1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_EAFDataInterface_Impl;

//Handling ModelNames (e.g. EAF1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_EAFPlantManager : public CDM_PlantManager
{
public:

  bool changeHeatingData(CEventMessage& Event);

	virtual bool changeInjectionData(CEventMessage& Event);

	void initInjectionData();

	void initElectricalData();

  void initBurnerData();

  void initGasLanceData();

  void initComputerModes();

  void initCoolingWaterData();

	virtual void init(CDM_Task* pDMTask);

	virtual bool changeElectricalData(CEventMessage& Event);

	virtual bool changeWasteGasData(CEventMessage& Event);

	virtual bool changeGasData(CEventMessage& Event);

	virtual bool changeBurningStatus(CEventMessage& Event, const std::string &BurningDevice,  long BurningStatus   );

	virtual bool changeBurningData(CEventMessage& Event);

  virtual bool changeCoolingWaterData(CEventMessage& Event);

	virtual bool changeLadleData(CEventMessage& Event);

	virtual bool changeStirringData(CEventMessage& Event);

	virtual bool changeTappingData(CEventMessage& Event);

	virtual bool changeAvailabilities(CEventMessage& Event);

	virtual bool changeComputerModes(CEventMessage& Event);

	virtual bool changePlantInformation(CEventMessage& Event);

	virtual ~CDM_EAFPlantManager();

	CDM_EAFPlantManager();

  virtual void resetPlantManager(CEventMessage &Event);
  virtual void resetComputerModes(CEventMessage& Event);


private:

};

#endif /* _INC_CDM_EAFPLANTMANAGER_413580AB023E_INCLUDED */

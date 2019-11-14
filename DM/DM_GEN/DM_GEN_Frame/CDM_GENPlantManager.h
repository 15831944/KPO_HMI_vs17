// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENPLANTMANAGER_413580AB023E_INCLUDED
#define _INC_CDM_GENPLANTMANAGER_413580AB023E_INCLUDED

#include <string>
#include "CDM_PlantManager.h"

#include <vector>

class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;

//Handling ModelNames (e.g. GEN1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_GENDataInterface_Impl;

//Handling ModelNames (e.g. GEN1) and physical plant units 
//(LadleCar1) at PlantManagement Interface
class CDM_GENPlantManager : public CDM_PlantManager
{
public:
	virtual void resetPlantDataBlowing(CEventMessage& Event);

	virtual std::map<std::string,seqGasData*> getActBlowingGasDataList(  );

	virtual void resetPlantData(CEventMessage &Event);

	virtual bool changeBlowingStatus(CEventMessage& Event, const std::string &BlowingDevice,  long BlowingStatus   );

	virtual bool changeBurningData(CEventMessage& Event);

	virtual bool changeLadleData(CEventMessage& Event);

	virtual bool changeStirringData(CEventMessage& Event);

	virtual bool changeTappingData(CEventMessage& Event);

	virtual bool changeAvailabilities(CEventMessage& Event);

	virtual bool changeComputerModes(CEventMessage& Event);

	virtual bool changePlantInformation(CEventMessage& Event);

	virtual ~CDM_GENPlantManager();

	CDM_GENPlantManager();


private:

};

#endif /* _INC_CDM_GENPLANTMANAGER_413580AB023E_INCLUDED */

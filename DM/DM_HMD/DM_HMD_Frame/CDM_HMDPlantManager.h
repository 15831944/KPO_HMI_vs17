// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDPLANTMANAGER_413580AB023E_INCLUDED
#define _INC_CDM_HMDPLANTMANAGER_413580AB023E_INCLUDED

#include <string>
#include "CDM_PlantManager.h"

#include <vector>

class CDM_DataInterface_Impl;
class CDM_PlantManagementInterface_Impl;
class CDM_HMDDataInterface_Impl;

//Handling ModelNames (e.g. HMD1) and physical plant units 
//##ModelId=45139A720051
class CDM_HMDPlantManager : public CDM_PlantManager
{
public:
	//##ModelId=45139A720053
	virtual void init(CDM_Task* pDMTask);

	//##ModelId=45139A720056
  void initComputerModes();

  //! set MatHandle and Blowing as On.
  //! set other modes from m_ComputerModeList to Off
	//##ModelId=45139A72005E
	virtual void resetComputerModes(CEventMessage& Event);

  //! call initGasData and reset lance status
	//##ModelId=45139A720061
	virtual void resetBlowingData(CEventMessage& Event);

  //! set lance heigh to 100mm and reset mat flows
	//##ModelId=45C9A0C70329
	virtual void resetCyclicData(CEventMessage& Event);

  //! call resetBlowingData, resetComputerModes
	//##ModelId=45139A720065
	virtual void resetPlantManager(CEventMessage &Event);

	//##ModelId=45139A720070
	virtual bool changeInjectionData(CEventMessage& Event);

	//##ModelId=45139A72007F
	virtual bool changeComputerModes(CEventMessage& Event);

	//! change plant status depended on events
	//##ModelId=45139A720082
	virtual bool changePlantInformation(CEventMessage& Event);

	//##ModelId=45139A72008B
	virtual ~CDM_HMDPlantManager();

	//##ModelId=45139A72008D
	CDM_HMDPlantManager();

};

#endif /* _INC_CDM_HMDPLANTMANAGER_413580AB023E_INCLUDED */

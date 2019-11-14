// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "CDM_GENTask.h"
#include "CSMC_EventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"

#include "CDM_GENPlantManager.h"
#include "CDM_PlantManagementInterface_Impl.h"




CDM_GENPlantManager::~CDM_GENPlantManager()
{
}

CDM_GENPlantManager::CDM_GENPlantManager()
{
  // fill GasNames into respective container
  m_GasTypeList.push_back(DEF_GAS::Ar);
  m_GasTypeList.push_back(DEF_GAS::N2);
  m_GasTypeList.push_back(DEF_GAS::O2);
}

bool CDM_GENPlantManager::changePlantInformation(CEventMessage& Event)
{
  return CDM_PlantManager::changePlantInformation(Event);
}



bool CDM_GENPlantManager::changeComputerModes(CEventMessage& Event)
{
  return CDM_PlantManager::changeComputerModes(Event);
}





bool CDM_GENPlantManager::changeAvailabilities(CEventMessage& Event)
{
  return CDM_PlantManager::changeAvailabilities(Event);
}

bool CDM_GENPlantManager::changeBurningData(CEventMessage& Event)
{
  return CDM_PlantManager::changeBurningData(Event);
}

bool CDM_GENPlantManager::changeLadleData(CEventMessage& Event)
{
	return CDM_PlantManager::changeLadleData(Event);
}

bool CDM_GENPlantManager::changeStirringData(CEventMessage& Event)
{
  return CDM_PlantManager::changeStirringData(Event);
}

bool CDM_GENPlantManager::changeTappingData(CEventMessage& Event)
{
	return CDM_PlantManager::changeTappingData(Event);
}

bool CDM_GENPlantManager::changeBlowingStatus(CEventMessage& Event, const std::string &BlowingDevice,  long BlowingStatus   )
{
  CDM_GENTask::getInstance()->log("!!!!! CDM_GENPlantManager::changeBlowingStatus.. not implemented !", 9);
  return false;
}



void CDM_GENPlantManager::resetPlantData(CEventMessage &Event)
{
  resetPlantDataBlowing(Event);
}



void CDM_GENPlantManager::resetPlantDataBlowing(CEventMessage& Event)
{
  CDM_GENTask::getInstance()->log("!!!!! CDM_GENPlantManager::changeBlowingStatus.. not implemented !", 9);
}

std::map<std::string,seqGasData*> CDM_GENPlantManager::getActBlowingGasDataList()
{
  std::map<std::string,seqGasData*> ActBlowingGasDataList;
  std::vector<std::string> GasDataNames;
  std::vector<std::string>::iterator itGasDataNames;

  return ActBlowingGasDataList;
}


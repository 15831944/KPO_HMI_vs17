// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_PLANTMANAGER_416A9808009B_INCLUDED
#define _INC_CDM_PLANTMANAGER_416A9808009B_INCLUDED

#include <string>
#include <vector>
#include "iDH_Interface_s.hh"

#include "CDM_StatusHandler.h"
#include "CStatusHandler.h"
#include "CGasDataHandler.h"

class CDM_PlantManagementInterface_Impl;
class CEventMessage;

class CDM_DataInterface_Impl;

class CDM_Task;

class CDM_GasDataHandler;

class CDM_PlantManager 
{
protected:
  //! insert message into additional message container
  void addEventMessageToSend(std::string Message);

  void log(const std::string& Message, long Level);

  //! to handle states changes in the plant
  CDM_StatusHandler m_PlantStatusHandler;

  //to handle states changes in the plant where seqStatus is used
  CStatusHandler m_StatusHandler;

  //to handle gases data
  CGasDataHandler m_GasDataHandler;

  CDM_Task* m_pDMTask;

  //Waste gase Type List as define in DEF_WASTE_GAS_TYPE
  std::vector<std::string> m_WasteGasTypeList;

  // amounts of thees gas types will be shown in getProcessState of the Task
  std::vector<std::string> m_GasDataList;

  // possible gas devices in a plant 
  std::vector<std::string> m_GasDeviceList;

  // container for possible plant computer modes
  std::vector<std::string> m_ComputerModeList;

  std::map<std::string,std::string> m_ModelList;

  // list of possible gas types in a plant
  std::vector<std::string> m_GasTypeList;

  // container for any constant names which could contain several gas data
  std::vector<std::string> m_GasInitializationList;

  // possible Burner devices in a plant 
  std::vector<std::string> m_BurnerDeviceList;

  // possible Lance devices in a plant 
  std::vector<std::string> m_GasLanceDeviceList;

private:
  //container for additionally event messages to sent
  std::vector<std::string> m_AdditionallyMessages;

  //finding Model by ModelName at PlantManagement Interface
  bool findModel(const std::string& ModelName);
  
  bool insertModel(const std::string& ModelName, const std::string& EquipmentId, const std::string &PlantID, bool OnlineStatus);

public:
  virtual bool changeLiftGasData(CEventMessage& Event);

  virtual bool changeVacuumData(CEventMessage& Event);

  //! return container with additionaly event messages and 
  //! clear member container directly for nex use
  void getAdditionallyMessages(std::vector<std::string>& Messages);

  virtual void initWasteGasData(const std::string& Key);

  virtual bool changeInjectionData(CEventMessage& Event);

  //! found out the transfer car for recived data
  virtual std::string getRelevantTransferCar(CEventMessage& Event);

  virtual bool changeElectricalData(CEventMessage& Event);

  virtual void fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData* seqData);

  virtual void fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, std::vector<std::string>& seqData, double Value);

  virtual void fillGasDataSequence(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData);

  virtual void initGasData(const std::string& Key, const std::string& Data, double Init);

  void initStirringDataSequence(const std::string& Key, std::vector<std::string>& m_StirringDef, std::vector<std::string>& m_StirringDevices, double Init);

  void initStatusSequence(const std::string& Key, std::vector<std::string>& m_StirringDef, std::vector<std::string>& m_StirringDevices, long Init);

  virtual void resetStirringData(CEventMessage& Event);

  virtual bool changeWasteGasData(CEventMessage& Event);

  virtual bool changeCoolingWaterData(CEventMessage& Event);

  virtual bool findProduct(CEventMessage& Event);

  virtual bool changeBurningData(CEventMessage& Event);

  virtual void resetComputerModes(CEventMessage& Event);

  CDM_PlantManager( );

  virtual void resetBlowingData(CEventMessage& Event);

  virtual void resetPlantManager(CEventMessage &Event);

  virtual bool changeGasData(CEventMessage& Event   );

  CDM_DataInterface_Impl* m_pDataInterface;

  virtual bool changeTappingData(CEventMessage& Event);

  virtual bool changeStirringData(CEventMessage& Event);

  virtual bool changeBlowingData(CEventMessage& Event);

  virtual bool changeLadleData(CEventMessage& Event);

  virtual bool changeAvailabilities(CEventMessage& Event);

  virtual void init(CDM_Task *pDMTask);

  virtual ~CDM_PlantManager();

  //Assign Product by ProductID or HeatID for Model at 
  //PlantManagement Interface
  virtual bool assignProduct( CEventMessage& Event   );

  virtual std::string getAssignedModel(const std::string& ProductID);

  //checks product data against database to deassign heats from tracker 
  //that are no longer in production
  //Assigns the product to an idle Model process, because we might have multiple instances 
  //running simultaneously, so find one of them as the assigned target. 
  //Deassign Product by ProductID from Model at 
  //PlantManagement Interface
  virtual bool deassignProduct( CEventMessage& Event );
  
  virtual bool deassignProduct( const std::string& ProductID);

  std::vector<std::string> getProductsOutOfProduction( CEventMessage& Event );

  //finding Product by ProductID at PlantManagement 
  //Interface
  virtual bool findProduct(const std::string& ProductID);

  //registering Model at ModelList regarding to inifile 
  //entries, searching for [Plant] : Aggregate, if not 
  //exists, using [Model] : ServerName
  virtual void registerModel();

  virtual bool changePlantInformation(CEventMessage& Event);

  virtual bool changeComputerModes(CEventMessage& Event);

  CDM_PlantManagementInterface_Impl* m_pPlantManagementInterface;

  virtual std::string getPlantEquipmentData(const std::string& Equipment);

  virtual std::string getProductAtPlantEquipment(const std::string& Equipment);

  virtual std::string getPlantEquipmentOfProduct(const std::string& ProductID);

  virtual bool changeTapLadleStirringData(CEventMessage& Event);

  virtual bool changeConverterPosition(CEventMessage& Event);

  virtual bool checkAssignement(CEventMessage& Event);
};

#endif /* _INC_CDM_PLANTMANAGER_416A9808009B_INCLUDED */

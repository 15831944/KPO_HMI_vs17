// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_PRODUCTMANAGER_416A981403E3_INCLUDED
#define _INC_CDM_PRODUCTMANAGER_416A981403E3_INCLUDED

class CDM_ProductManagementInterface_Impl;

#include "iDH_Interface_s.hh"

#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"

class CDM_Task;
class CDM_StatusHandler;
class CDM_GasDataHandler;
class CGC_Plant_Container;
class CDateTime;
class CEventMessage;

class CDM_ProductManager 
{
protected:

  CGC_Plant_Container* m_pGC_Plant_Container;

  std::vector<std::string> m_GasTypeList;

  //Adding ProductID to ProdauctManagement interface
  void addProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  //Find last treatment number at ProductManagement 
  //interface for HeatID
  long findLastTreatNo(std::string& HeatID);

  CDM_Task* m_pDMTask;

  CDM_ProductManager(const std::string& newTreatIDPrefix);

  std::vector<std::string> m_ComputerModeAvailabilityList;

  std::vector<std::string> m_GasDeviceList;

  std::vector<std::string> m_GasDataList;

  // possible Burner devices in a plant 
  std::vector<std::string> m_BurnerDeviceList;

  // possible Lance devices in a plant 
  std::vector<std::string> m_GasLanceDeviceList;

public:
  virtual bool changeGasLanceData(CEventMessage& Event);

  virtual bool changeChargingData(CEventMessage& Event);

  virtual bool changeLiftGasData(CEventMessage& Event);

  virtual bool changeWasteGasData(CEventMessage& Event);

  bool findOrder(std::string& ProductID,std::string& HeatID,std::string& TreatID,std::string& OrderId);

  bool changeOrderData(CEventMessage& Event, const std::string& OrderId);

  //Register ProductID at ProductManagement interface by 
  //ProductID or HeatID+TreatID
  bool registerProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  virtual bool changeMaterialFeedingData(CEventMessage& Event);

  virtual bool changeInjectionData(CEventMessage& Event);

  virtual bool changeEventDataInformation(CEventMessage& Event);

  virtual bool changeElectricalData(CEventMessage& Event);

  virtual bool changeGasData(CEventMessage& Event);

  virtual void initGasData(const std::string& Key, const std::string& Data, double Init);

  void initGasData(const std::string& Key, const std::string& Data, const std::string& GasDataName, double Init);

  void initStirringData(const std::string& Key, std::vector<std::string>& m_StirringDef, std::vector<std::string>& m_StirringDevices, double Init);

  bool setTreatmentPosition(const std::string& ProductID, long TreatmentPosition);

  virtual bool setProductData(const std::string& ProductID, long TreatmentPosition);

  virtual bool setProductData(const std::string& ProductID, const std::string& LadleType, long LadleNo, CDateTime& HeatAnnounceTime, CDateTime& HeatDepartTime, CDateTime& HeatStartTime  );

  //subtract GasValue from the seqData from GasValue in GasDataHandler.
  //if GasType doesn't registered -> inser into GasDataHandler with GasValue from the seqData.
  //negative result after subtraction will be multiplied by -1
  virtual void diffGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData);

  void log(const std::string& Message, long Level);

  //add GasValue from seqData to GasDataHandler GasValue
  //if GasType doesn't registered in GasDataHandler it will be inserted
  virtual void addGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData);

  //initialize GasDataHandler with 'GasType' and 'GasValue' from seqData
  virtual void fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData * seqData);

  virtual void fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData);

  //initialize GasDataHandler with 'GasType' from GasList and 'GasValue' with Value
  virtual void fillGasDataHandler(CDM_GasDataHandler& GasDataHandler, std::vector<std::string>& GasList, double Value);

  //gas data from the GasDataHandler will be inserted into the seqData
  virtual void fillGasDataSequence(CDM_GasDataHandler& GasDataHandler, seqGasData& seqData);

  virtual bool findProduct(CEventMessage& Event);

  virtual bool findHeat(CEventMessage& Event);

  virtual bool changeBurningData(CEventMessage& Event);

  //initialize StatusHandler with states from StateList and Value
  //if status doesn't registered in StatusHandler it will be inserted
  virtual void fillStatusHandler(CDM_StatusHandler& StatusHandler, std::vector<std::string>& StateList, long Value );

  //initialize StatusHandler with states and values from seqModes 
  //if status doesn't registered in StatusHandler it will be inserted
  virtual void fillStatusHandler(CDM_StatusHandler& StatusHandler, seqComputerModes * seqModes);

  virtual void fillStatusHandler(CDM_StatusHandler& StatusHandler, seqComputerModes& seqModes);

  //fill seqModes with data from StatusHandler
  virtual void fillComputerModesSequence(CDM_StatusHandler& StatusHandler, seqComputerModes& seqModes);

  virtual bool changeComputerModeAvailabilities(CEventMessage& Event);

  virtual bool resetComputerModeAvailabilities(CEventMessage& Event);

  virtual bool resetProductManager(CEventMessage& Event);

  virtual bool changeMaterialData(CEventMessage& Event);

  virtual void setAnalysisData(CEventMessage& Event, const std::string& AnalysisType);

  virtual std::string setSampleData( CEventMessage& Event,  long ActProbeType);

  virtual bool changeAnalysisInformation(CEventMessage& Event);

  virtual bool changeStirringData(CEventMessage& Event);

  virtual bool changeBlowingData(CEventMessage& Event);

  virtual bool changeTappingData(CEventMessage& Event);

  CDM_DataInterface_Impl* m_pDataInterface;

  virtual bool changeSampleInformation(CEventMessage& Event);

  virtual void init(CDM_Task *pDMTask);
  
  std::string m_TreatIDPrefix;

  virtual ~CDM_ProductManager();

  //Assign ProductID to a Model that is not treating any 
  //heat
  virtual bool changeAssignedModel(CEventMessage& Event, const std::string& AssignedModel);

  virtual bool changeAssignedModel(const std::string& ProductID, const std::string& AssignedModel);

  //Changing Data of ProductID at ProductManagement 
  //interface , e.g. to time for StartOfHeat
  virtual bool changeProductInformation(CEventMessage& Event);

  //Find PlantLocation at ProductManagement interface by 
  //ProductID or HeatID+TreatID
  virtual bool findActualPlantLocation(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId, std::string& PlantLocation);

  //Find actual ProductID at ProductManagement interface by 
  //ProductID or HeatID+TreatID
  virtual bool findActualProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  //Find ProductID at ProductManagement interface by 
  //HeatID+TreatID
  virtual bool findHeat(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  //Find ProductID at ProductManagement interface by 
  //ProductID or HeatID+TreatID
  virtual bool findProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID);

  //Find ProductID at ProductManagement interface by 
  //ProductID or HeatID+TreatID and supplement OrderId
  virtual bool findProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  virtual bool findProduct(std::string& ProductID);

  //Register ProductID at ProductManagement interface by 
  //Event data
  virtual bool registerProduct(CEventMessage& Event);

  //Remove ProductID at ProductManagement interface by 
  //ProductID or HeatID+TreatID
  virtual bool removeProduct(std::string& ProductID, std::string& HeatID, std::string& TreatID);

  virtual bool changeSetpoints(CEventMessage& Event);
  virtual bool changeCoolingWaterData(CEventMessage& Event);
  virtual bool changeHeatingData(CEventMessage& Event);

  // calculation of duration (min) since given time point for a product
  double getDurationSince(const std::string& ProductID, const char* TimePoint);

  //Calculate difference between GasData1 and GasData2 and add it to DestGasData
  //If DiffValue is set than gas types from GasData2 will be initialized with diffValue first
  virtual bool addDifferenceToGasData(CEventMessage& Event, const std::string& GasData1, const std::string& GasData2, const std::string& DestGasData, double DiffValue = DEF::Inv_Double);

  virtual bool changeVacuumData(CEventMessage& Event);

  virtual bool findProductByEquipment(CEventMessage& Event, std::string& ProductID, std::string& HeatID, std::string& TreatID, std::string& OrderId);

  CDM_ProductManagementInterface_Impl* m_pProductManagementInterface;

  bool changePhaseState(CEventMessage& Event);

  virtual bool doOnPhaseStateChange(CEventMessage& Event);
  
  void getAdditionallyMessages(std::vector<std::string>& Messages);

  void CDM_ProductManager::addEventMessageToSend(std::string Message);
private:
  //container for additionally event messages to sent
  std::vector<std::string> m_AdditionallyMessages;

};

#endif /* _INC_CDM_PRODUCTMANAGER_416A981403E3_INCLUDED */

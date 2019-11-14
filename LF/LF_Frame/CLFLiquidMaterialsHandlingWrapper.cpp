// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrameController.h"

#include "CLFModelTask.h"
#include "CLFLiquidMaterialsHandlingWrapper.h"
#include "DEF_GC_LIQADD_STATUS.h"

bool CLFLiquidMaterialsHandlingWrapper::doOnChangeOfLiquidAdditionData(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFLiquidMaterialsHandlingWrapper::doOnChangeOfLiquidAdditionData(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  //long TreatNo        = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getLong(Event.getProductID().c_str(), DATA::TreatNo );
  long TreatNo = m_pModelTask->getActTreatNo(Event);

  try 
  { 
    pIntfLF->indicateChgLiqAddData(); 

    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
    {
      for (int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); i++)
      {
        std::string LadleType = m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(i);
        long LadleNo          = m_pPD_HEAT_DATA_LIQADD->getLADLENO(i);
        long SampleRef        = m_pPD_HEAT_DATA_LIQADD->getSAMPLE_REF(i);
        double SteelWeight    = m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(i);
        double SlagWeight     = m_pPD_HEAT_DATA_LIQADD->getSLAGWEIGHT(i);

        if (!sequence_set_liquid_material_data(HeatID, TreatID, ActPlant, TreatNo, LadleType, LadleNo, SampleRef, SteelWeight, SlagWeight))
        {
          std::string SearchKey = HeatID + " " + TreatID;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_liquid_material_data",SearchKey.c_str());
        }
      }
    }
    else
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_LIQADD");
    }

    pIntfLF->hndlEvent();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFLiquidMaterialsHandlingWrapper::doOnChangeOfLiquidAdditionData()", ""  );    

  }

  return RetValue;
}

bool CLFLiquidMaterialsHandlingWrapper::doOnLiquidAdditionCharged(CEventMessage& Event)
{
	bool RetValue = false;
   
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFLiquidMaterialsHandlingWrapper::doOnLiquidAdditionCharged(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  long TreatNo = m_pModelTask->getActTreatNo(Event);

  try
  {
    long LiqAddNo = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getDataKey().c_str(), DATA::LiqAddNo);

    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, LiqAddNo))
    {            
      if (m_pPD_HEAT_DATA_LIQADD->getSTATUS(1) == DEF_GC_LIQADD_STATUS::ASSIGNED)
      {
        pIntfLF->indicateLiqAddCharged( ); 

        std::string LadleType = m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(1);
        long LadleNo          = m_pPD_HEAT_DATA_LIQADD->getLADLENO(1);
        long SampleRef        = m_pPD_HEAT_DATA_LIQADD->getSAMPLE_REF(1);
        double SteelWeight    = m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(1);
        double SlagWeight     = m_pPD_HEAT_DATA_LIQADD->getSLAGWEIGHT(1);

        if (!sequence_set_liquid_material_data(HeatID, TreatID, ActPlant, TreatNo, LadleType, LadleNo, SampleRef, SteelWeight, SlagWeight))
        {
          std::string SearchKey = HeatID + " " + TreatID;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_liquid_material_data",SearchKey.c_str());
        }

        pIntfLF->hndlEvent();

        // Sequence Diagram: get model results / Call Sequence
        RetValue = doModelResult(Event);
      }
    }
    else
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_LIQADD");
    }
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFLiquidMaterialsHandlingWrapper::doOnLiquidAdditionCharged()", ""  );    

  } 

  return RetValue;
}

bool CLFLiquidMaterialsHandlingWrapper::doOnRemoveLiquidSteelData(CEventMessage& Event)
{
  bool RetValue = false;
  
 
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFLiquidMaterialsHandlingWrapper::doOnRemoveLiquidSteelData(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();

  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  //long TreatNo        = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(Event.getProductID().c_str(), DATA::TreatNo );
  long TreatNo = m_pModelTask->getActTreatNo(Event);

  try 
  {
    if (m_pPD_HEAT_DATA_LIQADD && m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
    {            
      pIntfLF->indicateLiqAddDataRemove( ); 

      for (int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); i++)
      {
        if (m_pPD_HEAT_DATA_LIQADD->getSTATUS(i) == DEF_GC_LIQADD_STATUS::ASSIGNED)
        {
          pIntfLF->focusOnLiqAddHotMetal(HeatID, TreatNo, m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i));
          pIntfLF->hndlEvent();
        } 
      } 

      pIntfLF->indicateChgLiqAddData(); 
      for (int i = 1; i <= m_pPD_HEAT_DATA_LIQADD->getLastRow(); i++)
      {
        if (m_pPD_HEAT_DATA_LIQADD->getSTATUS(i) == DEF_GC_LIQADD_STATUS::ASSIGNED)
        {
          std::string LadleType = m_pPD_HEAT_DATA_LIQADD->getLADLETYPE(i);
          long LadleNo          = m_pPD_HEAT_DATA_LIQADD->getLADLENO(i);
          long SampleRef        = m_pPD_HEAT_DATA_LIQADD->getSAMPLE_REF(i);
          double SteelWeight    = m_pPD_HEAT_DATA_LIQADD->getSTEELWEIGHT(i);
          double SlagWeight     = m_pPD_HEAT_DATA_LIQADD->getSLAGWEIGHT(i);

          if (!sequence_set_liquid_material_data(HeatID, TreatID, ActPlant, TreatNo, LadleType, LadleNo, SampleRef, SteelWeight, SlagWeight))
          {
            std::string SearchKey = HeatID + " " + TreatID;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_liquid_material_data",SearchKey.c_str());
          }
        } 
      } //for(...)


    }
    else
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_LIQADD");
    }

    pIntfLF->hndlEvent();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFLiquidMaterialsHandlingWrapper::doOnRemoveLiquidSteelData()", ""  );    

  } 

  return RetValue;
}

bool CLFLiquidMaterialsHandlingWrapper::doSetLiquidMaterialData(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF && m_pModelTask ) 
  {       
    try
    {
      // TO DO

      RetValue = doModelResult(Event);
    }
    catch (...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"",
        "CLFLiquidMaterialsHandlingWrapper::doSetLiquidMaterialData",        
        "");    
    }
  }
  else
  {
    log("error CLFLiquidMaterialsHandlingWrapper::doSetLiquidMaterialData, (pIntfLF && m_pModelTask ) == false", 1);
  }
  return RetValue;
}

bool CLFLiquidMaterialsHandlingWrapper::doSetLiquidSteelData(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (pIntfLF && m_pModelTask ) 
  {       
    try
    {
      // TO DO

      RetValue = doModelResult(Event);
    }
    catch (...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CLFLiquidMaterialsHandlingWrapper::doSetLiquidSteelData",        
        "");    
    }
  }
  else
  {
    log("error CLFLiquidMaterialsHandlingWrapper::doSetLiquidSteelData, (pIntfLF && m_pModelTask ) == false", 1);
  }
  return RetValue;
}
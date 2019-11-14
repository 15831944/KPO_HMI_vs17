// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"
#include "CSMC_EventLogFrameController.h"

#include "CLFTreatmentManagerDataWrapper.h"
#include "CLFModelTask.h"
#include "iEventMessages_s.hh"
#include "CStirrPhaseCodesLF.h"
#include "CInv.h"
#include "CRS.h"
#include "DEF_GC_PRODPRAC_DEF.h"
#include "CDataConversion.h"

//##ModelId=42A06E2A01CB
bool CLFTreatmentManagerDataWrapper::doOnHeatStart(CEventMessage& Event)
{
  bool RetValue = false; 

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnHeatStart(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlStartOfHeat();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnHeatStart",  "");    
  }

  return RetValue;
}

//##ModelId=411893AA0367
bool CLFTreatmentManagerDataWrapper::doOnHeatDeparture(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnHeatDeparture(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlHeatDepart();

    // Sequence Diagram: get model results / Call Sequence
    //RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnHeatDeparture",  "");    
  }
  return RetValue;
}

//##ModelId=411893C60000
bool CLFTreatmentManagerDataWrapper::doOnHeatCancellation(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnHeatCancellation(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->hndlHeatCanc();

    // Sequence Diagram: get model results / Call Sequence
    //RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CCLFTreatmentManagerDataWrapper::doOnHeatCancellation()",   "");    
  }
  return RetValue;
}

//##ModelId=411893E0017A
bool CLFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Message = Event.getMessage();
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string PlantID = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
 
  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask || !checkDBConnection()) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement(), (pIntfLF && m_pModelTask && checkDBConnection()) == false", 1);
    return RetValue;
  }

  try
  {
    std::string LadleTransferCarId;

    long TreatNo = m_pModelTask->getActTreatNo(Event);

    // store Heat Announcement Time
    m_pModelTask->setActHeatAnnouncementTime(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getDate(Event.getProductID().c_str(),DATA::HeatAnnounceTime));

    // store LadleID and respectve Plant datakey 
    LadleTransferCarId = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getString(Event.getProductID().c_str(),DATA::LadleTransferCarId));

    std::string TransferCarPlantId = m_pModelTask->getPlantEquipment(LadleTransferCarId);

    m_pModelTask->setActProcessData(DATA::LadleTransferCarId,TransferCarPlantId);

    long PracParamPt      = getProdPracticePointer( HeatID, TreatID, ActPlant, DEF_GC_PRODPRAC_DEF::Parameter);

    pIntfLF->indicateHeatAnnouncement(HeatID, TreatID, PracParamPt);


    // MODEL: perform Sequence Diagram: set hot metal data / Call Sequence
    if (m_pPD_HEAT_DATA_LIQADD->select( HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
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
          std::stringstream SearchKey;
          SearchKey << HeatID << " " << TreatID << " " ;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_liquid_material_data",SearchKey.str().c_str());
        }
      }
    }

    // do not set aim dep. time for offline -announcement
    bool OnlineAnnouncement = (LF_EvMsg::evLFHeatAnnouncementOffline != Message);

    // MODEL: perform Sequence Diagram: set aim data / Call Sequence
    if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo, OnlineAnnouncement))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
    }

    // MODEL: perform Sequence Diagram: set production practice data electric / Call Sequence
    if (!sequence_set_production_practice_data_electric(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_electric",SearchKey.str().c_str());
    }

    // MODEL: perform Sequence Diagram: set production practice data recipe control / Call Sequence
    if (!sequence_set_production_practice_data_recipe_ctrl(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_recipe_ctrl",SearchKey.str().c_str());
    }

    if (!sequence_set_production_practice_data_stirring(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_stirring",SearchKey.str().c_str());
    }

    long Ret = pIntfLF->hndlEvent();

    RetValue = (CRS::OK == Ret);

    // Sequence Diagram: get model results / Call Sequence
    doModelResult(Event);

    // mrut 2008-01-14 : heat starts only at online-announcement
    //if (LF_EvMsg::evLFHeatAnnouncementOffline != Message)
    //{
    //  pIntfLF->hndlStartOfHeat();
    //}

  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement()", ""  );    
  }

  return RetValue;
}

//##ModelId=42A06E2A01E9
bool CLFTreatmentManagerDataWrapper::doOnChangeLiquidSteelData(CEventMessage& Event)
{
  bool RetValue = false;

  /****
  //JOGE will allready treated in liquid material wrapper
  *****/


  return RetValue;
}

//##ModelId=411894030224
bool CLFTreatmentManagerDataWrapper::doOnChangeProdPracStirring(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnChangeProdPracStirring(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    // MODEL: perform Sequence Diagram: set production practice data electric / Call Sequence
    if (!sequence_set_production_practice_data_stirring(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_stirring",SearchKey.str().c_str());
    }
    else
    {
      long Ret = pIntfLF->hndlEvent();

      RetValue = (CRS::OK == Ret);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = RetValue && doModelResult(Event);

  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnChangeProdPracStirring()",  "");    
  }

  return RetValue;
}

//##ModelId=4118942302FD
bool CLFTreatmentManagerDataWrapper::doOnChangeProdPracElectric(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnChangeProdPracElectric(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    // MODEL: perform Sequence Diagram: set production practice data electric / Call Sequence
    if (!sequence_set_production_practice_data_electric(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_electric",SearchKey.str().c_str());
    }
    else
    {
      long Ret = pIntfLF->hndlEvent();

      RetValue = (CRS::OK == Ret);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = RetValue && doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnChangeProdPracElectric()", "");    
  }

  return RetValue;
}

//##ModelId=42A06E2A01FD
bool CLFTreatmentManagerDataWrapper::doOnChangeProdPracRestriction(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnChangeProdPracRestriction(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    pIntfLF->indicateChgProdPracRecipeCtrl();        
    
    // MODEL: perform Sequence Diagram: set production practice data recipe control / Call Sequence
    if (!sequence_set_production_practice_data_recipe_ctrl(Event))
    {
      std::stringstream SearchKey;
      SearchKey << "ProdPracPt " ;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_recipe_ctrl",SearchKey.str().c_str());
    }
    else
    {
      long Ret = pIntfLF->hndlEvent();

      RetValue = (CRS::OK == Ret);
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = RetValue && doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CLFTreatmentManagerDataWrapper::doOnChangeProdPracRestriction()",  "");    
  }

  return RetValue;
}


bool CLFTreatmentManagerDataWrapper::doOnChangeProdPracParameter(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Message   = Event.getMessage();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnChangeProdPracParameter(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    // set default = 0 !
    long ProdPrac = getProdPracticePointer(HeatID, TreatID, ActPlant, DEF_GC_PRODPRAC_DEF::Parameter);

    pIntfLF->setParamPracPt(ProdPrac);

  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnChangeProdPracParameter()",   "");    
  }

  return RetValue;
}


//##ModelId=4165575903B1
bool CLFTreatmentManagerDataWrapper::doOnChangeAimData(CEventMessage& Event)
{
  bool RetValue = false;
  log (" doOnChangeAimTemp", 3);

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnChangeAimData(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try // common catch
  {
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
    
    pIntfLF->indicateChgAimData();       

    // MODEL: perform Sequence Diagram: set aim data / Call Sequence
    if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
    }
    else
    {
      long Ret = pIntfLF->hndlEvent();

      RetValue = (CRS::OK == Ret);
    }

    // Sequence Diagram: get model results / Call Sequence
    // Call model results also in unsuccessful case, could be some detail information is returned.
    RetValue = RetValue && doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnChangeAimData()",  "");    
  }

  return RetValue;
}
bool CLFTreatmentManagerDataWrapper::doOnUpdateAimDepartureTime(CEventMessage& Event)
{
  bool RetValue = false;
  std::string Function = "CLFTreatmentManagerDataWrapper::doOnUpdateAimDepartureTime" ;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
     log("Error " +  Function + ", (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  else
  {
    log(Function, 3);
  }

  try // common catch
  {
    std::string HeatID  = Event.getHeatID();
    std::string TreatID = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    pIntfLF->indicateChgAimData();       

    if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
    }
    // end GEPA 20100406

    
      CDateTime    TreatEndTime;
      CDateTime    TreatStartTime;
      CDeltaTime   DurAimTreatmentTime;


    TreatEndTime.SetTime ( m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)
                           ->getDate(Event.getDataKey().c_str(), DATA::TreatEndAim) );

    // store Heat start Time
    TreatStartTime.SetTime(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)
                           ->getDate(Event.getProductID().c_str(),DATA::HeatStartTime));


    DurAimTreatmentTime  = CDateTime::subTimes(TreatEndTime, TreatStartTime);

    double DurAimTreatmentTime_Tmp = DurAimTreatmentTime.asSeconds();
    // do not set aim dep. time if less than 10 seconds
    if ( DurAimTreatmentTime_Tmp < 10.)
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"UpdateAimDepartureTime; dt < 10 sec. ",SearchKey.c_str());
      return true;       // return true anyway
    }
    else
      DurAimTreatmentTime_Tmp /= 60;                          // minutes


    if ( CRS::OK == pIntfLF->setAimDepartTime(DurAimTreatmentTime_Tmp) )
    {
      if ( CRS::OK == pIntfLF->hndlEvent() )
      {
        RetValue = true;
      }
    }
    // Sequence Diagram: get model results / Call Sequence
    // Call model results also in unsuccessful case, could be some detail information is returned.

    RetValue = RetValue && doModelResult(Event);

  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnUpdateAimDepartureTime()", "");    
  }

  return RetValue;
}

bool  CLFTreatmentManagerDataWrapper::doOnUpdateAimTemperature  (CEventMessage& Event)
{
  bool RetValue = false;
  log (" doOnUpdateAimTemp", 3);

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnUpdateAimTemperature(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try // common catch
  {
    std::string HeatID  = Event.getHeatID();
    std::string TreatID = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    pIntfLF->indicateChgAimData();       

    if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
    }
    // end GEPA 20100406


    double AimDepartureTemp = (m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)
                             ->getDouble(Event.getDataKey().c_str(), DATA::TempAim) );


    if ( AimDepartureTemp <= 0. || DEF::Inv_Double == AimDepartureTemp)
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"doOnUpdateAimTemperature; dt < 10 sec. ",SearchKey.c_str());

      return false;
    }

    if ( CRS::OK == pIntfLF->setAimTemp(AimDepartureTemp) )
    {
      if ( CRS::OK == pIntfLF->hndlEvent() )
      {
        RetValue = true;
      }
    }

    // Sequence Diagram: get model results / Call Sequence
    // Call model results also in unsuccessful case, could be some detail information is returned.
    RetValue = RetValue && doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnUpdateAimDepartureTime()", "");    
  }

  return RetValue;
}

//##ModelId=42A06E2A0211
bool CLFTreatmentManagerDataWrapper::doOnSwitchEvent(CEventMessage& Event)
{
  long ReturnL = 1;
  bool RetValue = false;
  string stirrPhaseCodeLF;

  long Indensity = CInv::InvalidLong;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnSwitchEvent(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  //mrut 2006-07-20 : try to catch added
  try // common catch (?)
  {


    std::string Message = Event.getMessage();
    if (Message == LF_EvMsg::evLFFinalHeating)
        stirrPhaseCodeLF = CStirrPhaseCodesLF::FinalHeating;
    else if (Message == LF_EvMsg::evLFInitialHeating)
        stirrPhaseCodeLF = CStirrPhaseCodesLF::InitialHeating;
    else if (Message == LF_EvMsg::evLFMainHeating)
        stirrPhaseCodeLF = CStirrPhaseCodesLF::MainHeating;
    else if (Message == LF_EvMsg::evLFSoftStirring)
        stirrPhaseCodeLF = CStirrPhaseCodesLF::SoftStirring;
    else if (Message == LF_EvMsg::evLFCleanlinessStirring)
        stirrPhaseCodeLF = CStirrPhaseCodesLF::CleanStirring;
    else if (Message == LF_EvMsg::evLFCooling)
      stirrPhaseCodeLF = CStirrPhaseCodesLF::CoolingStirring;
//    else if (Message == LF_EvMsg::evLFChangeStirringIntensity)
//    {
//      // "we" expect the intensity
//	    Indensity = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
//       Event.getDataKey().c_str(), DATA::StirrIntensity);
//    }
    else 
      return false;

    if (!stirrPhaseCodeLF.empty())
    {
      ReturnL = pIntfLF->hndlStartNextTreatmentStep(stirrPhaseCodeLF);
      if (ReturnL != 0)
        log("function hndlStartNextTreatmentStep failed", 1);
    }
    else
    {
      // "we" have to translade the indensity number do an indensity string!
      if (m_pGCL_STIRR_INT->select(Indensity))
		  {
        string StirrIndensityCode = m_pGCL_STIRR_INT->getINTCODEMODEL(1);
        ReturnL = pIntfLF->hndlNewStirringIntensity(StirrIndensityCode);
        if (ReturnL != 0)
          log("function hndlNewStirringIntensity failed", 1);
      }
    }

    if (ReturnL == 0)
        RetValue = doModelResult(Event);

  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"", "CLFTreatmentManagerDataWrapper::doOnSwitchEvent()", "");    
  }
 

 return RetValue;
}

bool CLFTreatmentManagerDataWrapper::doOnLadleDataChanged(CEventMessage& Event)
{
  bool RetValue = false;

  std::string PlantID = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFTreatmentManagerDataWrapper::doOnLadleDataChanged(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try // common catch
  {
    std::string HeatID  = Event.getHeatID();
    std::string TreatID = Event.getTreatID();

    pIntfLF->indicateChgTapLdlData();

    if (!sequence_set_ladle_data(HeatID, TreatID, ActPlant))
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_ladle_data","");
    }
    else
    {
      long Ret = pIntfLF->hndlEvent();

      RetValue = (CRS::OK == Ret);
    }

    RetValue = RetValue && doModelResult(Event);

  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CLFTreatmentManagerDataWrapper::doOnLadleDataChanged()", "");    
  }

  return RetValue;
}


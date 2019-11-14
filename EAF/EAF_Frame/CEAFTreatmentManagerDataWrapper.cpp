// Copyright (C) 2004 SMS Demag AG

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "iSMC_DataDefinitions_s.hh"

#include "CSMC_EventLogFrameController.h"
#include "CDataConversion.h"

#include "CIntfEAF.h"
#include "CCfgEAF.h"
#include "CInv.h"

#include "DEF_GC_LIQADD_TYPE.h"
#include "DEF_GC_PRODPRAC_DEF.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"

#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPP_ORDER_SINGLE_AIMS.h"

#include "CEAFTreatmentManagerDataWrapper.h"



//##ModelId=411891F30153
bool CEAFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement(CEventMessage &Event)
{
  bool RetValue    = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("error CEAFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement(), (pIntfEAF) == false", 1);
    return RetValue;
  }

  try 
  {
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
    //long TreatNo        = m_pModelTask->getActTreatNo(Event);

    //********************************//
    // PARAMETER SET
    //********************************//
    long PracParamPt      = getProdPracticePointer( HeatID, TreatID, ActPlant, DEF_GC_PRODPRAC_DEF::Parameter);
    long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, ActPlant);

    // store Heat Announcement Time
    m_pModelTask->setActHeatAnnouncementTime(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getDate(Event.getProductID().c_str(),DATA::HeatAnnounceTime));
   
    if (!doIndicateHeatAnnouncement(HeatID, TreatID, PracParamPt)) 
    {
      return RetValue;
    }
          

    //********************************//
    // TREATMENT MAP SET
    //********************************//
    TreatmentModeNo = 0;
    if (m_pPP_ORDER_SINGLE_AIMS->select(Event.getOrderID(), ActPlant, 1,DEF_GC_PP_ORDER_SINGLE_AIMS::TREATMENTMODE)) 
    {
      std::stringstream ss;
      ss << m_pPP_ORDER_SINGLE_AIMS->getVALUE(1); ss >> TreatmentModeNo;
    }

    if (!sequence_set_treatmentmap_data(HeatID, TreatID, ActPlant, TreatmentModeNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_treatmentmap_data",SearchKey.c_str());
    }
    

    //********************************//
    // SET AIM DATA
    //********************************//
    if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
    }

    //********************************//
    //    HOT HEEL DATA
    //********************************//
    sequence_set_hot_heel_data(HeatID, TreatID, ActPlant, ActPlantNo);

    //********************************//
    // BASKET DATA
    //********************************//      
    if (!sequence_set_basket_data(HeatID, TreatID, Event))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_basket_data",SearchKey.c_str());
    }


    // Sequence Diagram: set liquid steel data / Call Sequence
    long TreatNo = CDataConversion::StringToLong(TreatID);
    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
    {
      for (long i=1; i<=m_pPD_HEAT_DATA_LIQADD->getLastRow(); ++i)
      {
        pIntfEAF->focusOnLiqAddHotMetal(HeatID, TreatNo, m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i));

        if (!sequence_set_liquid_material_data(HeatID, TreatID, TreatNo, i, ActPlant))
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
      std::string SearchKey = HeatID + " " + TreatID + " " + ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_LIQADD");
    }


    //********************************//
    //    PRODUCTION PRACTICE DATA
    //********************************//
    if (!sequence_set_all_heat_related_production_practice_data(HeatID, TreatID, ActPlant, ActPlantNo))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_all_heat_related_production_practice_data",SearchKey.c_str());
    }

    //********************************//
    // TAPPING LADLE DATA
    //********************************//      
    if (!sequence_set_tap_ladle_data(HeatID, TreatID, ActPlant))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_tap_ladle_data",SearchKey.c_str());
    }


    //mrut doHandleEvent(); //zhpf, invoke before hndlTapChgStart. 

    //********************************//
    // PLANT STATUS
    //********************************//
    //DM::iDM_Interface_var& pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);
    //std::string DataKey ( Event.getDataKey() );
   
    DM::iDM_Interface_var& pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT);
    std::string DataKey ( DEF_PLANT::Furnace );

    if (!sequence_set_plant_status(HeatID, TreatID, pDM_Interface, DataKey) )
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_plant_status",SearchKey.c_str());
    }

    RetValue = doHandleEvent();

    // Sequence Diagram: get model results / Call Sequence
    RetValue &= doModelResult(Event);
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement()", ""  );    
  } 
 
	return RetValue;
}

bool CEAFTreatmentManagerDataWrapper::doOnChangeTreatmentMode(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF) 
  {
    log("error CEAFTreatmentManagerDataWrapper::doOnHandleHeatAnnouncement(), (pIntfEAF) == false", 1);
    return RetValue;
  }


  try 
  {
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    long TreatmentModeNo  = getTreatmentModeNo(HeatID, TreatID, ActPlant);


    //********************************//
    //        TREATMENT MAP 
    //********************************//

    RetValue = doIndicateChgTreatmentMode();       

    if ( !RetValue || 
        !(RetValue = sequence_set_treatmentmap_data(HeatID, TreatID, ActPlant, TreatmentModeNo)))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_treatmentmap_data",SearchKey.c_str());

      return RetValue;                  // Ende im Gelände
    }
  

    //********************************//
    //        BASKET DATA
    //********************************//      
    if (!(RetValue = sequence_set_basket_data(HeatID, TreatID, Event)) )
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_basket_data",SearchKey.c_str());
    
      return RetValue;                  // Ende im Gelände
    }

    //********************************//
    //        LIQUID CHARGE DATA
    //********************************//      

    long TreatNo = CDataConversion::StringToLong(TreatID);

    if (m_pPD_HEAT_DATA_LIQADD->select(HeatID, TreatID, ActPlant, CSMC_DBData::unspecLong))
    {
      for (long i=1; i<=m_pPD_HEAT_DATA_LIQADD->getLastRow(); ++i)
      {
        if (m_pPD_HEAT_DATA_LIQADD->getLIQADDTYPE(i) == DEF_GC_LIQADD_TYPE::FeCr)
        {
          pIntfEAF->focusOnLiqAddFeCr(HeatID, TreatNo, m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i));
        }
        else
        {
          pIntfEAF->focusOnLiqAddHotMetal(HeatID, TreatNo, m_pPD_HEAT_DATA_LIQADD->getLIQADDNO(i));
        }

        if (!(RetValue = sequence_set_liquid_material_data(HeatID, TreatID, TreatNo, i, ActPlant)))
        {
          std::string SearchKey = HeatID + " " + TreatID;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_liquid_material_data",SearchKey.c_str());
    
          return RetValue;              // Ende im Gelände
        }
      } 
    } 
    else
    {
      // it is not necessarily an error!

      std::string SearchKey = HeatID + " " + TreatID + " " + ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_LIQADD");
    }

    //********************************//
    //    PRODUCTION PRACTICE DATA
    //********************************//
    if (!(RetValue = sequence_set_all_heat_related_production_practice_data(HeatID, TreatID, ActPlant, ActPlantNo)))
    {
      std::string SearchKey = HeatID + " " + TreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_all_heat_related_production_practice_data",SearchKey.c_str());
    
      return RetValue;              // Ende im Gelände
    }


    RetValue = doHandleEvent();
    
    RetValue &= doModelResult(Event);

  } // end try
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,  "", "CEAFTreatmentManagerDataWrapper::doOnChangeAimData()", "" );    

    RetValue = false;
  } 

  return RetValue;
}

//##ModelId=41592F1A0070
bool CEAFTreatmentManagerDataWrapper::doOnChangeAimData(CEventMessage &Event)
{
  bool RetValue = false;

  if (getpModelIntf())
  {  
    try 
    {
      std::string HeatID    = Event.getHeatID();
      std::string TreatID   = Event.getTreatID();
      std::string PlantID   = Event.getPlantID();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

      doIndicateChgAimData();       
      
      if (!sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo))
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
      }


      RetValue = doHandleEvent();
      
      RetValue &= doModelResult(Event);
	  } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,  "", "CEAFTreatmentManagerDataWrapper::doOnChangeAimData()", "" );    
    } 
  }

  return RetValue;
}

bool CEAFTreatmentManagerDataWrapper::doOnChangeSteelGrade(CEventMessage &Event)
{
  bool RetValue = false;

  if (getpModelIntf())
  {  
    try 
    {
      std::string HeatID    = Event.getHeatID();
      std::string TreatID   = Event.getTreatID();
      std::string PlantID   = Event.getPlantID();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

      //******************************************
      doIndicateChgAimData();
      if ( !(RetValue = sequence_set_aim_data(HeatID, TreatID, ActPlant, ActPlantNo) ))
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_aim_data",SearchKey.c_str());
      
        return RetValue;              // Ende im Gelände
      }

      //********************************//
      //    PRODUCTION PRACTICE DATA
      //********************************//
      if (!(RetValue = sequence_set_all_heat_related_production_practice_data(HeatID, TreatID, ActPlant, ActPlantNo)))
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_all_heat_related_production_practice_data",SearchKey.c_str());
      
        return RetValue;              // Ende im Gelände
      }


      RetValue = doHandleEvent();
      
      RetValue &= doModelResult(Event);

      RetValue = true;
	  } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,  "", "CEAFTreatmentManagerDataWrapper::doOnChangeSteelGrade()", "" );    
    } 
  }

  return RetValue;
}



//##ModelId=4118A122008A
bool CEAFTreatmentManagerDataWrapper::doOnChangeTapLadleData(CEventMessage &Event)
{
  bool RetValue = false;

  if (getpModelIntf())
  {  
    try 
    {
      std::string HeatID    = Event.getHeatID();
      std::string TreatID   = Event.getTreatID();
      std::string PlantID   = Event.getPlantID();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
      
      doIndicateChgTapLdlData();       
      
      if (!sequence_set_tap_ladle_data(HeatID, TreatID,ActPlant))
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_tap_ladle_data",SearchKey.c_str());
      }

      RetValue = doHandleEvent();
      
      RetValue &= doModelResult(Event);
	  } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "","CEAFTreatmentManagerDataWrapper::doOnChangeTapLadleData()","" );    
    } 

  }
	return RetValue;
}


//##ModelId=4118A065025F
bool CEAFTreatmentManagerDataWrapper::doOnChangeHotHeelData(CEventMessage &Event)
{
  bool RetValue = false;

  if (getpModelIntf())
  {  
    try 
    {
      std::string HeatID    = Event.getHeatID();
      std::string TreatID   = Event.getTreatID();
      std::string PlantID   = Event.getPlantID();
      std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
      long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
      
      doIndicateChgHotHeelData();       

      if (!sequence_set_hot_heel_data(HeatID, TreatID, ActPlant, ActPlantNo))
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_hot_heel_data",SearchKey.c_str());
      }

      RetValue = doHandleEvent();

      
      RetValue &= doModelResult(Event);
	  } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFTreatmentManagerDataWrapper::doOnChangeHotHeelData()",  "" );    
    } 
  }
	return RetValue;
}


//##ModelId=4118A0F901DF
bool CEAFTreatmentManagerDataWrapper::doOnHeatCancellation(CEventMessage &Event)
{
  bool RetValue = false;

  if (getpModelIntf())
  {  
    try 
    {
      RetValue = doHndlHeatCanc();

      RetValue &= doModelResult(Event);
	  } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "","CEAFTreatmentManagerDataWrapper::doOnHeatCancellation()",  "" );    
    } 

  }
	return RetValue;
}


//##ModelId=411891B10071
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracBurner(CEventMessage &Event)
{
  bool RetValue = true;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (getpModelIntf())
  {  
    try 
    {
      
      std::string SearchKey =  (HeatID + " " + TreatID);
      std::stringstream SearchTxt; SearchTxt<<SearchKey;

      //does model support burner?
      if( isModelDevice(CCtrlSystemCodesEAF::Burner) )
      {
        doIndicateChgProdPracBurner();       

        if (!sequence_set_production_practice_data_burner(HeatID, TreatID, ActPlant, ActPlantNo))
        {
          RetValue = false;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_burner",SearchTxt.str().c_str());
        }      
        else
        {
          RetValue = doHandleEvent();
        }
      }

      RetValue &= doModelResult(Event);
        
	  } // try
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CEAFTreatmentManagerDataWrapper::doOnChangeProdPracBurner()",
        "");    
    } 
  }

	return RetValue;
}


//##ModelId=41189137017A
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracJetMod(CEventMessage &Event, bool GetResults)
 // 2nd Argument is Krücke due to connected data injection : 2 jet modules, 2 lances for proc pattern
 // to be solved by generalised event chgProdPrac ...
{
  bool RetValue = true;

  #if defined(EAF_JET_MODULES)

    RetValue = false;

    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    if (getpModelIntf())
    {  
      try 
      {
        std::string SearchKey = (HeatID + " " + TreatID);
        std::stringstream SearchTxt; SearchTxt<<SearchKey;

        doIndicateChgProdPracJetModule();       

        if (!sequence_set_production_practice_data_jet_module(HeatID, TreatID, ActPlant, ActPlantNo))
        {
          RetValue = false;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_jet_module",SearchTxt.str().c_str());
        }
        else
        {
          RetValue = doHandleEvent();
        }

        if (GetResults) // kricket: we cannot retrieve the jet-model results for event chg of injection dada for bhushan
          RetValue &= doModelResult(Event);
        
	    } // try
	    catch(...) 
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, "","CEAFTreatmentManagerDataWrapper::sequence_set_production_practice_data_jet_module()", "");    
      } // catch
    }
  #endif

	return RetValue;
}

//##ModelId=4118A0A203C5
bool CEAFTreatmentManagerDataWrapper::doOnChangeManipGasLance(CEventMessage &Event)
{
  bool RetValue = false;
/* not used for JISCO

*/
	return RetValue;
}


//##ModelId=4118918C032B
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracElectric(CEventMessage &Event)
{
  bool RetValue = false;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (getpModelIntf())
  {  
    try 
    {

      std::string SearchKey = (HeatID + " " + TreatID);
      std::stringstream SearchTxt; SearchTxt<<SearchKey;

	    doIndicateChgProdPracElec();

      if (!sequence_set_production_practice_data_electric(HeatID, TreatID, ActPlant))
      {
        RetValue = false;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_electric",SearchKey.c_str());
      }      
      else
      {
        RetValue = doHandleEvent();
      }

      RetValue &= doModelResult(Event);

    } 
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFTreatmentManagerDataWrapper::doOnChangeProdPracElectric()",  ""  );    
    } 
  }
	return RetValue;
}


//##ModelId=4118A18D012E
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracRecipeControl(CEventMessage &Event)
{
  bool RetValue = false;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (getpModelIntf())
  {  
    try 
    {

      std::string SearchKey = (HeatID + " " + TreatID);
      std::stringstream SearchTxt; SearchTxt<<SearchKey;

      doIndicateChgProdPracRecipeCtrl();       
      
      if (!sequence_set_production_practice_data_recipe_ctrl(HeatID, TreatID, ActPlant, ActPlantNo))
      {
        RetValue = false;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_recipe_ctrl",SearchKey.c_str());
      }      
      else
      {
        RetValue = doHandleEvent();
      }

      RetValue &= doModelResult(Event);
    }
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CEAFTreatmentManagerDataWrapper::doOnChangeProdPracRecipeControl()",
        ""
      );    
    } 
  }
	return RetValue;
}


//##ModelId=429F142D01B1
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracOxygen(CEventMessage &Event)
{
  bool RetValue = false;

  #if defined (EAF_GAS_LANCES)

    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    if (getpModelIntf())
    {  
      try 
      {
        std::string SearchKey = (HeatID + " " + TreatID);
        std::stringstream SearchTxt; SearchTxt<<SearchKey;

        doIndicateChgProdPracManipGasLance();     

        if (!sequence_set_production_practice_data_manipulator_gas_lance(HeatID, TreatID, ActPlant))
        {
          RetValue = false;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_manipulator_gas_lance",SearchKey.c_str());
        }      
        else
        {
          RetValue = doHandleEvent();
        }

        RetValue &= doModelResult(Event);

      }
	    catch(...) 
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, "",     "CEAFTreatmentManagerDataWrapper::doOnChangeProdPracOxygen()",  "" );    
      } 
    }

  #endif

	return RetValue;
}

//##ModelId=429F142D01E3
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracParameter(CEventMessage &Event)
{
  bool RetValue = true;
	return RetValue;
}

//##ModelId=429F142D0189
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracInjection(CEventMessage &Event)
{

  bool RetValue = false;

  #if defined (EAF_INJECTION_LANCES) 
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);


     if (getpModelIntf())
    {  
      try 
      {

        std::string SearchKey = (HeatID + " " + TreatID);
        std::stringstream SearchTxt; SearchTxt<<SearchKey;

        doIndicateChgProcPat();    // welly, this use-case seems to be most matchy here...
   
        RetValue = sequence_set_production_practice_data_injection(HeatID, TreatID, ActPlant, ActPlantNo);

        if (!RetValue)
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"ChangeProdPracInjection",SearchTxt.str().c_str());
        }
        else 
        {
          RetValue = doHandleEvent();
          
          bool ModelResults = doModelResult(Event);

          RetValue &= ModelResults;
        }
      }
	    catch(...) 
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ExceptionCaught(sMessage, "","CEAFTreatmentManagerDataWrapper::doOnChangeProdPracInjection()",  "" );    
      } 
    }
#endif

	return RetValue;
}
//##ModelId=45EBDA3A0379
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracPatternFeeding(CEventMessage &Event)
{
 
  bool RetValue = true;

#if defined(EAF_PATTERN_FEEDING)

  RetValue = doOnChangeProcPattern(Event);

#endif

	return RetValue;
}


//##ModelId=411891CC01ED
bool CEAFTreatmentManagerDataWrapper::doOnChangeProcPattern(CEventMessage &Event)
{
  bool RetValue = true;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (getpModelIntf())
  {  
    try 
    {
      const CCfgEAF * pCfgEAF =  getpCfgEAF();
      const map<string, long> & CtrlSystemMap = pCfgEAF->getCtrlSystemSetptTyp();
      map<string, long>::const_iterator   CtrlSystemItEnd (CtrlSystemMap.end());

      std::string SearchKey = (HeatID + " " + TreatID);

      // we need just one indicate for one combined change of practice data
      // it must be doIndicateChgProdPracElec, otherwise it does not work!!!!
      if ( doIndicateChgProdPracElec() )
      {
        if( !sequence_set_production_practice_data_electric(HeatID, TreatID, ActPlant ) )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_electric",SearchKey.c_str());

          RetValue = false;
        }

        if (CtrlSystemMap.find (CCtrlSystemCodesEAF::BinMatPatternFeed) != CtrlSystemItEnd)
        {
          if( !sequence_set_production_practice_data_pattern_feeding(HeatID, TreatID, ActPlant) )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_pattern_feeding",SearchKey.c_str());

            RetValue = false;
          }
        }

        if ( isModelDevice(CCtrlSystemCodesEAF::ManipOxygenLance) )
        {
          if( !sequence_set_production_practice_data_manipulator_gas_lance(HeatID, TreatID, ActPlant) )
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_manipulator_gas_lance",SearchKey.c_str());

            RetValue = false;
          }
        }

        RetValue = RetValue && doHandleEvent();        
        RetValue = RetValue && doModelResult(Event);
      }
    }
    catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CEAFTreatmentManagerDataWrapper::doOnChangeProcPattern()",   "" );    
    }
  }

  return RetValue;

}

//##ModelId=45EBDA3A0398
bool CEAFTreatmentManagerDataWrapper::doOnChangeProdPracBottomStirring(CEventMessage &Event)
{

  bool RetValue = false;

#if defined (EAF_BOTTOM_STIRRING)

  if (getpModelIntf())
  {
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string PlantID   = Event.getPlantID();
    std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
    long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

    try // common catch
    {

      std::string SearchKey = (HeatID + " " + TreatID);
      std::stringstream SearchTxt; SearchTxt<<SearchKey;

      doIndicateChgProdPracBottomStirring();       

      bool PracticeDataPassed = sequence_set_production_practice_data_bottom_stirring(HeatID, TreatID, ActPlant);
      if (!PracticeDataPassed)
      {
        RetValue = false;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_production_practice_data_recipe_ctrl",SearchTxt.str().c_str());
      }      
      else
      {
        RetValue = doHandleEvent();
      }

      RetValue &= doModelResult(Event);
    }
    catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CEAFTreatmentManagerDataWrapper::doOnChangeProdPracBottomStirring()", "");    
    } // catch
  }

#endif

	return RetValue;
}

bool CEAFTreatmentManagerDataWrapper::doOnChangePlantStatus(CEventMessage &Event)
{
  bool RetValue = false;

  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  if (getpModelIntf())
  {  
    try 
    {
      DM::iDM_Interface_var& pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT);
      std::string DataKey ( DEF_PLANT::Furnace );

      // sequence_set_plant_status is calling pIntfEAF->indicatePlantStatus() and pIntfEAF->hndlPlantStatus()
      if (sequence_set_plant_status(HeatID, TreatID, pDM_Interface, DataKey) )
      {
        RetValue = doModelResult(Event);  
      }
      else
      {
        std::string SearchKey = HeatID + " " + TreatID;
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(sMessage,"sequence_set_plant_status",SearchKey.c_str());
      }
    }
	  catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
        "CEAFTreatmentManagerDataWrapper::doOnChangePlantStatus()",   "" );    
    }
  }

	return RetValue;

}

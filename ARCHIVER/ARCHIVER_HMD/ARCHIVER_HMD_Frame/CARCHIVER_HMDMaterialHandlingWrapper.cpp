// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"

#include "DEF_GC_RECIPE_STATUS.h"

#include "CARCHIVER_HMDMaterialHandlingWrapper.h"
#include "CPDH_HM_DATA.h"



//##ModelId=45D5A7D90347
CARCHIVER_HMDMaterialHandlingWrapper::CARCHIVER_HMDMaterialHandlingWrapper()
{
}

//##ModelId=45D5A7DA0110
CARCHIVER_HMDMaterialHandlingWrapper::~CARCHIVER_HMDMaterialHandlingWrapper()
{
}

//##ModelId=45D5A7DC03D7
void CARCHIVER_HMDMaterialHandlingWrapper::deleteDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::deleteDBClasses();
}

//##ModelId=45D5A7DD02B7
void CARCHIVER_HMDMaterialHandlingWrapper::initDBClasses()
{
  CARCHIVER_MaterialHandlingWrapper::initDBClasses();
}

//##ModelId=45D5B754013B
bool CARCHIVER_HMDMaterialHandlingWrapper::doOnPowderBlowing(CEventMessage& Event, bool start)
{
  bool RetValue = false;
   ///  DUTM 
////  std::string ProductID = Event.getProductID();
////  std::string HeatID    = Event.getHeatID();
////  std::string TreatID   = Event.getTreatID();
////  std::string DataKey   = Event.getDataKey();
////  std::string PlantID   = Event.getPlantID();
////  std::string ActPlant  = m_pPlantID_Interpreter->getPlant(PlantID);
////
////  // Unified exception handling *******************************************************
////  std::string Scope("CARCHIVER_HMDMaterialHandlingReportWrapper::doOnPowderBlowing");
////  std::stringstream ExceptionMsg;
////  ExceptionMsg << "Handling event: " << Event.getSender()
////               << ", " << ProductID << ", " << HeatID
////               << ", " << TreatID   << ", " << DataKey;
////  //***********************************************************************************
////  
////  try
////  {
////    if (!m_pConnection)
////    {
////      handleDBConnectionError();
////      if (!m_pConnection) return false;
////    }
////    CPDH_LANCE_DATA PDH_Lance_Data(m_pConnection);
//////    CPDH_HEAT_DATA PDH_Heat_Data(m_pConnection);
////
////    setpDM_Interface(Event.getSender(),DM::PRODUCT);
////
////    CDateTime now;
//////SS     NonSeqInfo NonSeqRecipeInfo;// to write into table
////    std::string RecStat = "Discharge_Start";// for logging only
////
////    //get info from PRODUCTION_MANAGEMENT_INTERFACE
////    double dDurHeatAnnouce    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
////    double dDurSinceHeatStart = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
////    seqGasData SeqGasData;
////    seqBatch   SeqRecipeContent;
////    long LanceCount = 0;
////
////    setpDM_Interface(Event.getSender(),DM::PLANT);
////    long LanceNo = m_pDM_Interface->getLong(DEF_PLANT::Furnace,DATA::LanceId);
////
//////SS     NonSeqRecipeInfo.DurSinceHeatAnnounce = dDurHeatAnnouce;
//////SS     NonSeqRecipeInfo.DurSinceHeatStart    = dDurSinceHeatStart;
////
////    if ( start )
////    {
////      // write first charging time if it is empty
////      if (PDH_Heat_Data.select(ActPlant, HeatID, TreatID ))
////      {
////        if (PDH_Heat_Data.isNull("INJECT_START_TIME",1))
////        {
////          PDH_Heat_Data.setINJECT_START_TIME(now);
////          if (PDH_Heat_Data.update())
////            PDH_Heat_Data.commit();
////        }
////      }
////      else
////      {
////        std::string SearchKey = HeatID + " " + TreatID + " " + ActPlant;
////        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
////        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////        pEventLog->EL_ErrorSearchingData(sMessage, SearchKey.c_str(),"PDH_Heat_Data");
////      }
////      
////      if (PDH_Lance_Data.select(ActPlant, HeatID, TreatID, LanceNo))
////      {
////        LanceCount = PDH_Lance_Data.getLANCE_IN_USE_HEAT(1);
////        LanceCount++;
////        PDH_Lance_Data.setLANCE_IN_USE_HEAT(LanceCount);
////        PDH_Lance_Data.setLANCE_IN_USE_TOTAL(LanceCount);
////
////        if (PDH_Lance_Data.update())
////          PDH_Lance_Data.commit();
////        else
////          PDH_Lance_Data.rollback();
////      }
////      else
////      {
////        PDH_Lance_Data.setHM_ID(HeatID);
////        PDH_Lance_Data.setTREATID(TreatID);
////        PDH_Lance_Data.setPLANT(ActPlant);
////        PDH_Lance_Data.setLANCE_NO(LanceNo);
////        PDH_Lance_Data.setLANCE_IN_USE_HEAT(1);
////        PDH_Lance_Data.setLANCE_IN_USE_TOTAL(1);
////
////        if (PDH_Lance_Data.insert())
////          PDH_Lance_Data.commit();
////        else
////          PDH_Lance_Data.rollback();
////      }
////
//////SS       NonSeqRecipeInfo.RecipeStatus = DEF_RECIPE_STATUS::Discharge_Start;
////    }
////    else
////    {
////      if (PDH_Heat_Data.select(ActPlant, HeatID, TreatID ))
////      {
////          PDH_Heat_Data.setINJECT_END_TIME(now);
////          if (PDH_Heat_Data.update())
////            PDH_Heat_Data.commit();       
////      }
////      else
////      {
////        std::string SearchKey = HeatID + " " + TreatID + " " + ActPlant;
////        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
////        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////        pEventLog->EL_ErrorSearchingData(sMessage, SearchKey.c_str(),"PDH_Heat_Data");
////      }
////    }
////  }
////  catch (cCBS_DBExc &e)
////  {
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
////      Scope.c_str(), ExceptionMsg.str().c_str()); 
////    RetValue = false;
////    handleDBConnectionError();
////  }
////  catch(CORBA::SystemException& sExc) 
////  {
////	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
////      Scope.c_str(), ExceptionMsg.str().c_str());
////    RetValue = false;
////  }
////  catch(CORBA::Exception& cExc) 
////  {
////	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
////      Scope.c_str(), ExceptionMsg.str().c_str());
////    RetValue = false;
////  }
////  catch(...)
////  {
////    std::string Msg("Unknown exception:");
////    Msg += ExceptionMsg.str();
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////      pEventLog->EL_ExceptionCaught(sMessage, "",
////      Scope.c_str(), Msg.c_str()); 
////    RetValue = false;
////  }
  return RetValue;
}

bool CARCHIVER_HMDMaterialHandlingWrapper::doOnMaterialAvailability(CEventMessage& Event)
{
  bool RetValue = false;

  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_HMDMaterialHandlingReportWrapper::doOnMaterialAvailability");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender() << DataKey;
  //***********************************************************************************

  try
  {
    seqMaterials SeqMaterials;

    setpDM_Interface(Event.getSender(),DM::EVENT);

    SeqMaterials = CIntfData::ToCORBAType(m_pDM_Interface->getMaterials(DataKey.c_str(), DATA::MatAvailable));

    // update PD_BIN
    handleMaterialAvailability(Event, SeqMaterials);
  }
  catch (cCBS_DBExc &e)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      Scope.c_str(), ExceptionMsg.str().c_str()); 
    RetValue = false;
    handleDBConnectionError();
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      Scope.c_str(), ExceptionMsg.str().c_str());
    RetValue = false;
  }
  catch(...)
  {
    std::string Msg("Unknown exception:");
    Msg += ExceptionMsg.str();
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",
      Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include "CGasDataHandler.h"

#include "CARCHIVER_Task.h"
#include "CARCHIVER_TreatmentWrapper.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "CDataConversion.h"
#include "DEF_GC_PP_ORDER_SINGLE_AIMS.h"
#include "DEF_GC_ACTION_DEF.h"


//##ModelId=45D56F190052
CARCHIVER_TreatmentWrapper::CARCHIVER_TreatmentWrapper()
:m_pEquipmentData(0)
,m_pHeatStatusContainer(0)
,m_pPD_DELAYS(0)
,m_pGT_MAT_PURP(0)
,m_pPD_LADLE(0)
,m_pPD_PRETREATDATA(0)
,m_pPD_HEAT_YIELDS(0)
,m_pPP_ORDER(0)
,m_pPD_HEAT_DATA_LIQADD(0)
,m_pPD_HEAT_DATA_PRODPRAC(0)
,m_pPP_HEAT(0)
,m_pPP_HEAT_PLANT(0)
,m_pPD_HEAT_DATA(0)
,m_pPD_ACTION(0)
,m_pGC_PLANTGROUP(0)
,m_pGC_Plant_Container(0)
,m_pPD_HEAT_REF(0)
,m_pGT_GRADE_PRODPRAC(0)
,m_pPD_HEAT_PLANT_REF(0)
,m_pPD_PLANTSTATUS(0)
,m_pHD_GRADE(0)
,m_pPP_SHIFT_CREW_ASSIGNMENT(0)
,m_pPD_SAMPLE(0)
,m_pHD_COOLWATER(0)
,m_pHD_LADLE_LIFE_DATA(0)
,m_pHD_PHASE_RES(0)
,m_pHD_PHASE_RES_ANL(0)
,m_pHD_PHASE_RES_PLANT(0)
,m_pHD_WASTEGAS_CYCL_MEAS_DATA(0)
,m_pPD_ELEC_SYSTEM(0)
,m_pGC_PHASE(0)
,m_pPD_PHASE_RES(0)
,m_pPD_SAMPLE_ENTRY(0)
,m_pPP_ORDER_SINGLE_AIMS(0)
,m_pPD_PHASE_RES_ANL(0)
,m_pGC_HEAT_STATUS(0)
,m_pPD_SCRAP_CONTAINER_ORDER(0)
,m_pPD_HOT_METAL(0)
,m_pPD_HOT_METAL_ORDER(0)
{
}

//##ModelId=45D56F190215
CARCHIVER_TreatmentWrapper::~CARCHIVER_TreatmentWrapper()
{
  deleteDBClasses();
}

//##ModelId=45D56FC40163
bool CARCHIVER_TreatmentWrapper::handleHeatAnnounceStatus(CEventMessage& Event, double AimTapWeightCalc)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleHeatAnnounceStatus");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    RetValue = true;

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


//##ModelId=45D56FC401A9
bool CARCHIVER_TreatmentWrapper::handleHeatStart(CEventMessage& Event)
{
  bool RetValue = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string CustHeatID;
  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleHeatStart");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if( RetValue )
    {
      CDateTime Now;

      if(m_pPD_HEAT_DATA->select(HeatID,TreatID,ActPlant))
      {
        m_pPD_HEAT_DATA->setTREATSTART_ACT(Now);

        RetValue = RetValue && m_pPD_HEAT_DATA->update();
      }
    }// if( RetValue )
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



//##ModelId=45F517D901E2
bool CARCHIVER_TreatmentWrapper::handleUpdateAimDepartureTime(CEventMessage& Event, CDateTime& depTime)
{	
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleUpdateAimDepartureTime");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant))
    {

      if (m_pPD_HEAT_DATA->getLastRow() > 0)
      {
        m_pPD_HEAT_DATA->setTREATEND_MOD(depTime);

        if (m_pPD_HEAT_DATA->update())
          m_pPD_HEAT_DATA->commit();
        else
        {
          log("WARNING: Cannot update m_pPD_HEAT_DATA->setTREATEND_MOD",2);
          m_pPD_HEAT_DATA->rollback();
        }
      }
      else
      {
        log("ERROR: m_pPD_HEAT_DATA->getLastRow(): Row number is 0!", 1);
      }
    }
    else
    {
      std::string key = HeatID + " " + TreatID + " " + ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,key.c_str(),"PD_HEATDATA");
    }
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

//##ModelId=45F518030101
bool CARCHIVER_TreatmentWrapper::handleUpdateAimTemperature(CEventMessage& Event, double temp)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleUpdateAimTemperature");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant))
    {
      long row = 0;
      if ((row = m_pPD_HEAT_DATA->getLastRow())>0)
      {
        m_pPD_HEAT_DATA->setAIMTEMP_MOD((long)temp);

        if (m_pPD_HEAT_DATA->update())
          m_pPD_HEAT_DATA->commit();
        else
        {
          log("WARNING: Cannot update m_pPD_HEAT_DATA->setAIMTEMP_MOD",2);
          m_pPD_HEAT_DATA->rollback();
        }
      }
      else
      {
        log("ERROR: m_pPD_HEAT_DATA->getLastRow(): Row number is 0!",1);
      }
    }
    else
    {
      std::string key = HeatID + " " + TreatID + " " + ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,key.c_str(),"PD_HEATDATA");
    }
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

//##ModelId=467F89EA0048
bool CARCHIVER_TreatmentWrapper::handleTappingStart(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleTappingStart");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);
    double Elecons              = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    seqGasData SeqGasData       = CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::TotalMetAmount));
    sGasData sGasData;

    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    if ( CIntfData::getLength(SeqGasData) > 0 )
    {
      CGasDataHandler GasDataHandler(SeqGasData);
      m_pPD_ACTION->m_Row.O2_MOMENT = GasDataHandler.getGasData(DEF_GAS::O2);
      m_pPD_ACTION->m_Row.AR_MOMENT = GasDataHandler.getGasData(DEF_GAS::Ar);
      m_pPD_ACTION->m_Row.N2_MOMENT = GasDataHandler.getGasData(DEF_GAS::N2);
    }

    m_pPD_ACTION->m_Row.ACTIONUNIT = "min";
    m_pPD_ACTION->m_Row.ACTIONVALUE = "0";
    m_pPD_ACTION->m_Row.ACTIONSTATUS = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = DurSinceHeatStart;
    m_pPD_ACTION->m_Row.ELECEGY = Elecons;
    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::TappingStart, true))
    {
      std::stringstream Msg;
      Msg << "ERROR: insert acrion '" << DEF_GC_ACTION_DEF::TappingStart << "' failed!";
      log(Msg.str(),1);
      m_pPD_ACTION->rollback();
    }

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

//##ModelId=467F92670341
bool CARCHIVER_TreatmentWrapper::handleUpdateAimSteelWeight(CEventMessage& Event, double Weight)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_TreatmentWrapper::handleUpdateAimSteelWeight");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Sender
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant))
    {
      long row = 0;
      if ((row = m_pPD_HEAT_DATA->getLastRow())>0)
      {
        m_pPD_HEAT_DATA->setAIMSTEELWGT_MOD(Weight);

        if (m_pPD_HEAT_DATA->update())
        {
          m_pPD_HEAT_DATA->commit();
          RetValue = true;
        }
        else
        {
          log("WARNING: Cannot update m_pPD_HEAT_DATA->setAIMSTEELWGT_MOD",2);
          m_pPD_HEAT_DATA->rollback();
        }
      }
      else
      {
        log("ERROR: m_pPD_HEAT_DATA->getLastRow(): Row number is 0!", 1);
      }
    }
    else
    {
      std::string key = HeatID + " " + TreatID + " " + ActPlant;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,key.c_str(),"PD_HEATDATA");
    }
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




//##ModelId=45D5722303CB
void CARCHIVER_TreatmentWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPD_DELAYS              = new CPD_DELAYS(pConnection);
  m_pGT_MAT_PURP            = new CGT_MAT_PURP(pConnection);
  m_pPD_LADLE               = new CPD_LADLE(pConnection);
  m_pPD_PRETREATDATA        = new CPD_PRETREATDATA(pConnection);
  m_pPD_HEAT_YIELDS         = new CPD_HEAT_YIELDS(pConnection);
  m_pPP_ORDER               = new CPP_ORDER(pConnection);
  m_pPD_HEAT_DATA_LIQADD    = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPD_HEAT_DATA_PRODPRAC  = new CPD_HEAT_DATA_PRODPRAC(pConnection);
  m_pPP_HEAT                = new CPP_HEAT(pConnection);
  m_pPP_HEAT_PLANT          = new CPP_HEAT_PLANT(pConnection);
  m_pPD_HEAT_DATA           = new CPD_HEAT_DATA(pConnection);
  m_pPD_ACTION              = new CPD_ACTION(pConnection);
  m_pGC_PLANTGROUP          = new CGC_PLANTGROUP(pConnection);
  m_pGC_Plant_Container     = new CGC_Plant_Container(pConnection);
  m_pHeatStatusContainer    = new CHeatStatusContainer(pConnection);
  m_pEquipmentData          = new CEquipmentData(pConnection);
  m_pPD_HEAT_REF            = new CPD_HEAT_REF(pConnection);
  m_pGT_GRADE_PRODPRAC      = new CGT_GRADE_PRODPRAC(pConnection);
  m_pPD_HEAT_PLANT_REF          = new CPD_HEAT_PLANT_REF(pConnection);
  m_pPD_PLANTSTATUS             = new CPD_PLANTSTATUS(pConnection);
  m_pHD_GRADE                   = new CHD_GRADE(pConnection);
  m_pPP_SHIFT_CREW_ASSIGNMENT   = new CPP_SHIFT_CREW_ASSIGNMENT(pConnection);
  m_pPD_SAMPLE                  = new CPD_SAMPLE(pConnection);
  m_pHD_COOLWATER               = new CHD_COOLWATER(pConnection);
  m_pHD_LADLE_LIFE_DATA         = new CHD_LADLE_LIFE_DATA(pConnection);
  m_pHD_PHASE_RES               = new CHD_PHASE_RES(pConnection);
  m_pHD_PHASE_RES_ANL           = new CHD_PHASE_RES_ANL(pConnection);
  m_pHD_PHASE_RES_PLANT         = new CHD_PHASE_RES_PLANT(pConnection);
  m_pHD_WASTEGAS_CYCL_MEAS_DATA = new CHD_WASTEGAS_CYCL_MEAS_DATA(pConnection);
  m_pPD_ELEC_SYSTEM             = new CPD_ELEC_SYSTEM(pConnection);
  m_pGC_PHASE                   = new CGC_PHASE(pConnection);
  m_pPD_PHASE_RES               = new CPD_PHASE_RES(pConnection);
  m_pPD_SAMPLE_ENTRY            = new CPD_SAMPLE_ENTRY(pConnection);
  m_pPP_ORDER_SINGLE_AIMS       = new CPP_ORDER_SINGLE_AIMS(pConnection);
  m_pPD_PHASE_RES_ANL           = new CPD_PHASE_RES_ANL(pConnection);
  m_pGC_HEAT_STATUS               = new CGC_HEAT_STATUS(pConnection);
  m_pPD_SCRAP_CONTAINER_ORDER   = new CPD_SCRAP_CONTAINER_ORDER(pConnection);
  m_pPD_HOT_METAL               = new CPD_HOT_METAL(pConnection);
  m_pPD_HOT_METAL_ORDER         = new CPD_HOT_METAL_ORDER(pConnection);
}

//##ModelId=45D5722402A2
void CARCHIVER_TreatmentWrapper::deleteDBClasses()
{
  if (m_pEquipmentData)             {delete m_pEquipmentData; m_pEquipmentData = 0;}
  if (m_pHeatStatusContainer)       {delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}
  if (m_pPD_DELAYS)                 {delete m_pPD_DELAYS; m_pPD_DELAYS = 0;}
  if (m_pGT_MAT_PURP)               {delete m_pGT_MAT_PURP; m_pGT_MAT_PURP = 0;}
  if (m_pPD_LADLE)                  {delete m_pPD_LADLE; m_pPD_LADLE = 0;}
  if (m_pPD_PRETREATDATA)           {delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0;}
  if (m_pPD_HEAT_YIELDS)            {delete m_pPD_HEAT_YIELDS; m_pPD_HEAT_YIELDS = 0;}
  if (m_pPP_ORDER)                  {delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPD_HEAT_DATA_LIQADD)       {delete m_pPD_HEAT_DATA_LIQADD; m_pPD_HEAT_DATA_LIQADD = 0;}
  if (m_pPD_HEAT_DATA_PRODPRAC)     {delete m_pPD_HEAT_DATA_PRODPRAC; m_pPD_HEAT_DATA_PRODPRAC = 0;}
  if (m_pPP_HEAT)                   {delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT)             {delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPD_HEAT_DATA)              {delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}
  if (m_pPD_ACTION)                 {delete m_pPD_ACTION; m_pPD_ACTION= 0;}
  if (m_pGC_PLANTGROUP)             {delete m_pGC_PLANTGROUP; m_pGC_PLANTGROUP = 0; }
  if (m_pGC_Plant_Container)        {delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
  if(m_pPD_HEAT_REF)                {delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0;}
  if(m_pGT_GRADE_PRODPRAC)          {delete m_pGT_GRADE_PRODPRAC; m_pGT_GRADE_PRODPRAC = 0;}
  if(m_pPD_HEAT_PLANT_REF)          {delete m_pPD_HEAT_PLANT_REF; m_pPD_HEAT_PLANT_REF = 0;}
  if(m_pPD_PLANTSTATUS)             {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
  if(m_pHD_GRADE)                   {delete m_pHD_GRADE; m_pHD_GRADE = 0;}
  if(m_pPP_SHIFT_CREW_ASSIGNMENT)   {delete m_pPP_SHIFT_CREW_ASSIGNMENT; m_pPP_SHIFT_CREW_ASSIGNMENT = 0;}
  if(m_pPD_SAMPLE)                  {delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0;}
  if(m_pHD_COOLWATER)               {delete m_pHD_COOLWATER; m_pHD_COOLWATER = 0;}
  if(m_pHD_LADLE_LIFE_DATA)         {delete m_pHD_LADLE_LIFE_DATA; m_pHD_LADLE_LIFE_DATA = 0;}
  if(m_pHD_PHASE_RES)               {delete m_pHD_PHASE_RES; m_pHD_PHASE_RES = 0;}
  if(m_pHD_PHASE_RES_ANL)           {delete m_pHD_PHASE_RES_ANL; m_pHD_PHASE_RES_ANL = 0;}
  if(m_pHD_PHASE_RES_PLANT)         {delete m_pHD_PHASE_RES_PLANT; m_pHD_PHASE_RES_PLANT = 0;}
  if(m_pHD_WASTEGAS_CYCL_MEAS_DATA) {delete m_pHD_WASTEGAS_CYCL_MEAS_DATA; m_pHD_WASTEGAS_CYCL_MEAS_DATA = 0;}  
  if(m_pPD_ELEC_SYSTEM)             {delete m_pPD_ELEC_SYSTEM; m_pPD_ELEC_SYSTEM = 0;} 
  if(m_pGC_PHASE)                   {delete m_pGC_PHASE; m_pGC_PHASE = 0;} 
  if(m_pPD_PHASE_RES)               {delete m_pPD_PHASE_RES; m_pPD_PHASE_RES = 0;} 
  if(m_pPD_SAMPLE_ENTRY)            {delete m_pPD_SAMPLE_ENTRY; m_pPD_SAMPLE_ENTRY = 0;} 
  if(m_pPP_ORDER_SINGLE_AIMS)       {delete m_pPP_ORDER_SINGLE_AIMS;m_pPP_ORDER_SINGLE_AIMS = 0;}
  if(m_pPD_PHASE_RES_ANL)           {delete m_pPD_PHASE_RES_ANL;m_pPD_PHASE_RES_ANL = 0;}
  if(m_pGC_HEAT_STATUS)               {delete m_pGC_HEAT_STATUS;m_pGC_HEAT_STATUS = 0;}
  if(m_pPD_SCRAP_CONTAINER_ORDER)   {delete m_pPD_SCRAP_CONTAINER_ORDER; m_pPD_SCRAP_CONTAINER_ORDER = 0;} 
  if(m_pPD_HOT_METAL)               {delete m_pPD_HOT_METAL; m_pPD_HOT_METAL = 0;} 
  if(m_pPD_HOT_METAL_ORDER)         {delete m_pPD_HOT_METAL_ORDER; m_pPD_HOT_METAL_ORDER = 0;} 

}
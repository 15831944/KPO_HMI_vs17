// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogLFController.h"
#include "CIntfData.h"
#include "CStirringDataHandler.h"
#include "CEventMessage.h"
#include "CGasDataHandler.h"

#include "CPDL_CYCL_MEAS_DATA.h"
#include "CPDL_HEAT_DATA.h"
#include "CPD_HEAT_DATA_STIRR.h"
#include "CPD_HEAT_DATA_STIRR.h"
#include "CPDL_HEAT_DATA_MELT.h"
#include "CPD_HEAT_DATA.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_STIRR_GAS_TYPE.h"
#include "DEF_GC_STIRR_DEVICE.h"

#include "CARCHIVER_LFTask.h"
#include "CARCHIVER_LFSignalsAndMeasurementWrapper.h"

//##ModelId=41DACB3301EA
CARCHIVER_LFSignalsAndMeasurementWrapper::CARCHIVER_LFSignalsAndMeasurementWrapper()
:m_pPDL_CYCL_MEAS_DATA(0)  
,m_pPDL_HEAT_DATA(0)
,m_pPD_HEAT_DATA_STIRR(0)
,m_pPDL_HEAT_DATA_MELT(0)
,m_pPD_HEAT_DATA(0)
{
}

//##ModelId=41DACB330348
CARCHIVER_LFSignalsAndMeasurementWrapper::~CARCHIVER_LFSignalsAndMeasurementWrapper()
{
  deleteDBClasses();
}

//##ModelId=41DACB3602F2
void CARCHIVER_LFSignalsAndMeasurementWrapper::initDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPDL_CYCL_MEAS_DATA         = new CPDL_CYCL_MEAS_DATA(pConnection);
  m_pPDL_HEAT_DATA              = new CPDL_HEAT_DATA(pConnection);  
  m_pPD_HEAT_DATA_STIRR         = new CPD_HEAT_DATA_STIRR(pConnection);
  m_pPDL_HEAT_DATA_MELT         = new CPDL_HEAT_DATA_MELT(pConnection);
  m_pPD_HEAT_DATA               = new CPD_HEAT_DATA(pConnection);
}


//##ModelId=41DACB360035
void CARCHIVER_LFSignalsAndMeasurementWrapper::deleteDBClasses()
{
  CARCHIVER_SignalsAndMeasurementWrapper::deleteDBClasses();

  if (m_pPDL_CYCL_MEAS_DATA)    { delete m_pPDL_CYCL_MEAS_DATA; m_pPDL_CYCL_MEAS_DATA = 0; } 
  if (m_pPDL_HEAT_DATA)         { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0; } 
  if (m_pPD_HEAT_DATA_STIRR)    { delete m_pPD_HEAT_DATA_STIRR; m_pPD_HEAT_DATA_STIRR = 0; }
  if (m_pPDL_HEAT_DATA_MELT)    { delete m_pPDL_HEAT_DATA_MELT; m_pPDL_HEAT_DATA_MELT = 0; }
  if (m_pPD_HEAT_DATA)          { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;}

}


//##ModelId=41DACB5B027E
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnCyclicMeasurement(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnCyclicMeasurement");
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

    // base class methods
    handleCoolingWater(Event);

    // LF specific methods
    handleCyclicData(Event);

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


bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnStirringStartEnd(CEventMessage& Event, long Status)
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
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnStirringStartEnd");
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

    long OtherPlugStart = 0;
    CDateTime now;

    CStirringDataHandler StirringAmountHandler;
    CStirringDataHandler StirringLastStartEndAmountHandler;
    CStirringDataHandler StirringDurationHandler;
    CStirringDataHandler StirringPressHandler;
    
    // *******************************************
    // ********doOnStirringStartEnd start*********
    // *******************************************
    setpDM_Interface(Sender,DM::PRODUCT);
    double ElecCons                 = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    long TreatmentPosition          = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);
    seqStirringData StirringAmount  = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringAmount));

    CStirringDataHandler StirringDataHandler(StirringAmount);

    log( CIntfData::getContent(CIntfData::ToAny(StirringAmount) ),2 );

    if ( Status == DEF_GEN_STATES::On )
    {
      log("******** doOnStirringStartEnd 'START' *********", 3);

      handleBottomStirringStart(Event, StirringDataHandler.getAccumulatedGasDataSeq(), ElecCons);

      for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
      {
        sStirringData StirringData;
        CIntfData::getAt(StirringData,StirringAmount,i);

        std::string Device      = StirringData.Device;
        seqGasData  SeqGasData  = StirringData.GasData;   // we expect only one entry here per device !

        sGasData      GasData;
        CIntfData::getAt(GasData,SeqGasData,0);

        std::string GasType   = GasData.GasType;
        double      GasValue  = GasData.GasValue;

        m_pPD_HEAT_DATA_STIRR->setHEATID(HeatID);
        m_pPD_HEAT_DATA_STIRR->setTREATID(TreatID);
        m_pPD_HEAT_DATA_STIRR->setPLANT(ActPlant);
        m_pPD_HEAT_DATA_STIRR->setDEVICENAME(Device);
        m_pPD_HEAT_DATA_STIRR->setSTIRRGASTYPE(GasType);
            
        m_pPD_HEAT_DATA_STIRR->setSTARTTIME(now);

		m_pPD_HEAT_DATA_STIRR->setIS_BYPASS(DEF_GEN_STATES::Off);  //U153 20121002 added
      
		if (m_pPD_HEAT_DATA_STIRR->insert())
        {
          m_pPD_HEAT_DATA_STIRR->commit();
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage, "", "PD_HEAT_DATA_STIRR", Scope.c_str());

          m_pPD_HEAT_DATA_STIRR->rollback();
        }

        // *************************
        // update heat specific data
        // *************************
        if (m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant))
        {
          bool update = false;
          if (m_pPDL_HEAT_DATA->isNull(CPDL_HEAT_DATA::STIRR_START, 1))
          {
            update = true;
            m_pPDL_HEAT_DATA->setSTIRR_START(now);
          }

          if (update)
          {
            if (m_pPDL_HEAT_DATA->update())
              m_pPDL_HEAT_DATA->commit();
            else
            {
              log("ERROR: update PDL_HEAT_DATA failed!",2);
              m_pPDL_HEAT_DATA->rollback();
            }
          }
        }
        else
        {
          std::string SearchKey  = HeatID + " " + TreatID;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PDL_HEAT_DATA");
        } // if (m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant))
      } // for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
    } 
    // ******************************************
    // ********doOnStirringStartEnd end *********
    // ******************************************
    else
    {
      log("******** doOnStirringStartEnd 'END' *********", 3);

      handleBottomStirringEnd(Event, StirringDataHandler.getAccumulatedGasDataSeq(), ElecCons);


      for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
      {
        sStirringData StirringData;
        CIntfData::getAt(StirringData,StirringAmount,i);

        std::string Device      = StirringData.Device;
        seqGasData  SeqGasData  = StirringData.GasData;   // we expect only one entry here per device !

        sGasData      GasData;
        CIntfData::getAt(GasData,SeqGasData,0);

        std::string GasType   = GasData.GasType;
        double      GasValue  = GasData.GasValue;

        CDeltaTime  PhaseTime;
        double      PhaseDur    = 0.;         
        long        isBypass    = 0;

        // ****************************************
        // look for opened stirring end on the plug
        // ****************************************
        if ( m_pPD_HEAT_DATA_STIRR->selectOpenStirringPhase( HeatID, TreatID, ActPlant, TreatmentPosition, Device, isBypass, GasType) )
        {
          // calculate duration

          PhaseTime = CDateTime::subTimes(now,m_pPD_HEAT_DATA_STIRR->getSTARTTIME(1));
          PhaseDur  = PhaseTime.asSeconds() / 3600. ;         // seconds -> hours

          PhaseDur  = CDataConversion::SetInvalidToDefault(PhaseDur,1,0); // prevent division by 0

          m_pPD_HEAT_DATA_STIRR->setCONS(GasValue);
          m_pPD_HEAT_DATA_STIRR->setENDTIME(now);

          if ( m_pPD_HEAT_DATA_STIRR->update() )
          {
            m_pPD_HEAT_DATA_STIRR->commit();
          }
          else
          {
            m_pPD_HEAT_DATA_STIRR->rollback();
          }

          // ****************************************
          // update PDL_HEAT_DATA
          // ****************************************
          if (m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant))
          {
            // the last event indicates the (most actual) stirring end time
            m_pPDL_HEAT_DATA->setSTIRR_END(now);

            if (GasType == DEF_GC_STIRR_GAS_TYPE::Ar)
            {
              m_pPDL_HEAT_DATA->setSTIRR_AR_CONS(StirringDataHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::Ar));
              m_pPDL_HEAT_DATA->setSTIRR_AR_DUR(PhaseDur);
            }
            else
            {
              m_pPDL_HEAT_DATA->setSTIRR_N2_CONS(StirringDataHandler.getAccumulatedGasValue(DEF_GC_STIRR_GAS_TYPE::N2));
              m_pPDL_HEAT_DATA->setSTIRR_N2_DUR(PhaseDur);
            }

            // handle special end time for CLEANLENESS STIRRING if CLEANLINESS_START was set before
            if (!m_pPDL_HEAT_DATA->isNull(CPDL_HEAT_DATA::CLEANLINESS_START,1))
            {
              m_pPDL_HEAT_DATA->setCLEANLINESS_END(now);
            }

            if (m_pPDL_HEAT_DATA->update())
            {
              m_pPDL_HEAT_DATA->commit();
            }
            else
            {
              log("ERROR: update PDL_HEAT_DATA failed!",2);
              m_pPDL_HEAT_DATA->rollback();
            }
          } 
          else
          {
            std::string SearchKey  = HeatID + " " + TreatID;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PDL_HEAT_DATA");
          }
        } // if ( m_pPD_HEAT_DATA_STIRR->selectOpenStirringPhase(HeatID, TreatID, ActPlant, Device, GasType) )

      } // for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)

    } // if ( Status == DEF_GEN_STATES::On )

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

//##ModelId=41F7706E02FA
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnStirringBypassOnOff(CEventMessage& Event, long Status)
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
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnStirringBypassOnOff");
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

    CDateTime now;

    CStirringDataHandler  StirringLastStartEndAmountHandler;
    CStirringDataHandler  StirringAmountHandler;

    setpDM_Interface(Sender,DM::PRODUCT);
    long TreatmentPosition              = m_pDM_Interface->getLong(ProductID.c_str(), DATA::TreatmentPosition);
    seqStirringData StirringAmount      = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringAmount));

    StirringAmountHandler.fill(StirringAmount);

    if ( Status == DEF_GEN_STATES::On )
    {
      log("********doOnStirringBypassOnOff start*********", 3);

      for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
      {
        sStirringData StirringData;
        CIntfData::getAt(StirringData,StirringAmount,i);

        std::string Device      = StirringData.Device;
        seqGasData  SeqGasData  = StirringData.GasData;   // we expect only one entry here per device !

        sGasData      GasData;
        CIntfData::getAt(GasData,SeqGasData,0);

        std::string GasType   = GasData.GasType;
        double      GasValue  = GasData.GasValue;

        m_pPD_HEAT_DATA_STIRR->setHEATID(HeatID);
        m_pPD_HEAT_DATA_STIRR->setTREATID(TreatID);
        m_pPD_HEAT_DATA_STIRR->setPLANT(ActPlant);
        m_pPD_HEAT_DATA_STIRR->setDEVICENAME(Device);
        m_pPD_HEAT_DATA_STIRR->setSTIRRGASTYPE(GasType);

        m_pPD_HEAT_DATA_STIRR->setIS_BYPASS(Status);  //GEPA 20120820 added

        m_pPD_HEAT_DATA_STIRR->setSTARTTIME(now);

        if (m_pPD_HEAT_DATA_STIRR->insert())
        {
          m_pPD_HEAT_DATA_STIRR->commit();
        }
        else
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage, "", "PD_HEAT_DATA_STIRR", Scope.c_str());

          m_pPD_HEAT_DATA_STIRR->rollback();
        }
      } // for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
    }
    else
    {
      log("********doOnStirringBypassOnOff end*********", 3);

      for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)
      {
        sStirringData StirringData;
        CIntfData::getAt(StirringData,StirringAmount,i);

        std::string Device      = StirringData.Device;
        seqGasData  SeqGasData  = StirringData.GasData;   // we expect only one entry here per device !

        sGasData      GasData;
        CIntfData::getAt(GasData,SeqGasData,0);

        std::string GasType   = GasData.GasType;
        double      GasValue  = GasData.GasValue;

        CDeltaTime  PhaseTime ;
        double      PhaseDur  = 0.;         
        long        isBypass  = 1;

        // ****************************************
        // look for opened stirring end on the plug
        // ****************************************
        if ( m_pPD_HEAT_DATA_STIRR->selectOpenStirringPhase( HeatID, TreatID, ActPlant, TreatmentPosition, Device, isBypass, GasType) )
        {
          // calculate duration

          PhaseTime = CDateTime::subTimes(now,m_pPD_HEAT_DATA_STIRR->getSTARTTIME(1));
          PhaseDur  = PhaseTime.asSeconds() / 3600. ;         // seconds -> hours

          PhaseDur  = CDataConversion::SetInvalidToDefault(PhaseDur,1,0); // prevent division by 0

          m_pPD_HEAT_DATA_STIRR->setCONS(GasValue);
          m_pPD_HEAT_DATA_STIRR->setENDTIME(now);
          m_pPD_HEAT_DATA_STIRR->setIS_BYPASS(Status); // set last actual bypass status

          if ( m_pPD_HEAT_DATA_STIRR->update() )
          {
            m_pPD_HEAT_DATA_STIRR->commit();
          }
          else
          {
            m_pPD_HEAT_DATA_STIRR->rollback();
          }

        } // if ( m_pPD_HEAT_DATA_STIRR->selectOpenStirringPhase(HeatID, TreatID, ActPlant, Device, GasType) )

      } // for( long i = 0; i < CIntfData::getLength(StirringAmount); ++i)

    } // if ( Status == DEF_GEN_STATES::On )

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

bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnHeating(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string Message   = Event.getMessage();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnHeating");
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

    // precheck contraint
    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant))
    {
      double PowerOnDur = 0.0;

      setpDM_Interface(Sender,DM::PLANT);

      long VoltTap = m_pDM_Interface->getLong(ProductID.c_str(),DATA::VoltTapNo);

      if (VoltTap != DEF::Inv_Long)
      {
        if (m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant))
        {
          if (VoltTap != DEF::Inv_Long)
          {
            m_pPDL_HEAT_DATA->setLASTTRAFOTAP(VoltTap);

            if (m_pPDL_HEAT_DATA->update())
            {
              m_pPDL_HEAT_DATA->commit();
            }
            else
            {
              m_pPDL_HEAT_DATA->rollback();
            }
          }
        }
      }// if (VoltTap != DEF::Inv_Long)
    }// if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant))
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

//##ModelId=44C5C727038E
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnEmergencyLanceStirring(CEventMessage& Event, long status)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string Sender    = Event.getSender();
  std::string Message   = Event.getMessage();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnEmergencyLanceStirring");
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

    // precheck contraint
    if (m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) && m_pPDL_HEAT_DATA->select(HeatID, TreatID,ActPlant))
    {
      double ARCons = 0;
      double N2Cons = 0;
      CDateTime StirrStSt;  // start stop time

      setpDM_Interface(Sender,DM::EVENT);      

      StirrStSt.SetTime(m_pDM_Interface->getDate(DataKey.c_str(),DATA::DateTime));

      if (status)// start of stirring
      {
        m_pPDL_HEAT_DATA->setSTIRR_START_EMRGNCY(StirrStSt);
      }
      else // end of stirring
      {
        m_pPDL_HEAT_DATA->setSTIRR_END_EMRGNCY(StirrStSt);

        setpDM_Interface(Sender,DM::PRODUCT);
        seqGasData StirringAmount ;//= CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::StirrAmountEmergLance));

        // must be one element in the sequence
        if (CIntfData::getLength(StirringAmount) > 0)
        {
          // read gas consumption per lance
          // and safe into PDL_HEAT_DATA
          sGasData StirrData;
          //CIntfData::getAt(StirrData, StirringAmount, 1);//Djx: Why use 1 to get data?
          CIntfData::getAt(StirrData, StirringAmount, 0);

          std::string Gas = StirrData.GasType;  
          if (Gas == DEF_GC_STIRR_GAS_TYPE::Ar) 
          {
            ARCons = StirrData.GasValue;
            m_pPDL_HEAT_DATA->setSTIRR_AR_CONS_EMRGNCY(ARCons);            
          }
          if (Gas == DEF_GC_STIRR_GAS_TYPE::N2) 
          {
            N2Cons = StirrData.GasValue;
            m_pPDL_HEAT_DATA->setSTIRR_N2_CONS_EMRGNCY(N2Cons);
          }
        }
      }// else

      if (m_pPDL_HEAT_DATA->update())
      {
        m_pPDL_HEAT_DATA->commit();
      }
      else
      {
        log("ERROR: update emergency lance data failed!",1);
        m_pPDL_HEAT_DATA->rollback();
      }


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


//##ModelId=44B4F03801E2
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnTempMeasurement(CEventMessage& Event)
{
  bool RetValue = false;
    
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string OrderID   = Event.getOrderID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);
  
  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnTempMeasurement");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************
  
  try
  {
    if (! checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    long TreatmentPosition = DEF_GC_TRETMENTPOSITION::TransferCar1;

    if( m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
    {
      TreatmentPosition = m_pPDL_HEAT_DATA->getCARNO(1);
    }

    RetValue = handleTempOxyMeasurement(Event, TreatmentPosition);
    
    if(RetValue)
    {
      setpDM_Interface(Event.getSender(),DM::EVENT);

      double MeasTemp  = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasTemp);

      CDateTime Now;

      RetValue = m_pPD_PLANTSTATUS->updateTempTaken(ActPlant, ActPlantNo, MeasTemp, Now, TreatmentPosition , true , m_lastError);
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


//##ModelId=462F67730255
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnElectrodesInOperatingPosition(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  //std::string PlantID   = Event.getPlantID();
  //std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnElectrodesInOperatingPosition");
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

    setpDM_Interface(Event.getSender(),DM::EVENT);    
    long status = m_pDM_Interface->getLong(DataKey.c_str(), DATA::ElecPosUp);    

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double elecegy   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

    handleElectrodesInOperatingPosition(Event, elecegy, status);
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



//##ModelId=462F677302A5
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnFurnaceBreaker(CEventMessage& Event, long status)
{
  bool RetValue = false;

  RetValue =  handleFurnaceBreaker(Event,status);

  return RetValue;
}


//##ModelId=462F677302EB
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnPower(CEventMessage& Event, long status)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnPower");
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

    CDateTime Now;

    //Change back when DH_IN is ready. 
    setpDM_Interface(Event.getSender(),DM::EVENT);
    //setpDM_Interface(Event.getSender(),DM::PRODUCT);
    long status = m_pDM_Interface->getLong(DataKey.c_str(), DATA::PowerOn);   

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    CDateTime HeatAnnounceTime         ( m_pDM_Interface->getDate  (ProductID.c_str(), DATA::HeatAnnounceTime));
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

    double ElecCons             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    std::string PhaseAct        = m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseProcess);
    long PhaseNoAct             = m_pDM_Interface->getLong  (ProductID.c_str(), DATA::PhaseNoProcess);
    std::string HeatingStepCode = m_pDM_Interface->getString(ProductID.c_str(), DATA::ElecPhaseName);

    //setpDM_Interface(Event.getSender(),DM::PLANT);
    //ElecCons             = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    /********************************************************/

    // check and convert data 
    HeatingStepCode = CDataConversion::SetInvalidToDefault(PhaseAct,DEF_LF_PHASES::HeatingInitial);

    std::string Phase = HeatingStepCode;

    if ( PhaseNoAct > 0 )
    {
      Phase += " " + CDataConversion::LongToString(PhaseNoAct); 
    }

    if ( m_pPDL_HEAT_DATA_MELT )
    {
      if ( status == DEF_GEN_STATES::On )
      {
        m_pPDL_HEAT_DATA_MELT->writeDataOnPhaseStart(HeatID, TreatID, ActPlant, Phase, ElecCons);
      }
      else if ( status == DEF_GEN_STATES::Off )
      {
        m_pPDL_HEAT_DATA_MELT->writeDataOnPhaseEnd(HeatID, TreatID, ActPlant, CSMC_DBData::unspecString, ElecCons);
      }
    }

    // get power-on time and calculate power-off time
    double PowerOnDur   = max( m_pPDL_HEAT_DATA_MELT->getPowerOnDur(HeatID, TreatID, ActPlant, HeatAnnounceTime, Now), 0.0 );
    //double PowerOffDur  = DurSinceHeatAnnounce - PowerOnDur;

    //for insert PowerOffDur and PowerOnDur in table pdl_heat_data
    /********************************************************/

    //for insert PowerOffDur and PowerOnDur in table PDL_HEAT_DATA
    if (m_pPDL_HEAT_DATA && m_pPDL_HEAT_DATA->select(HeatID, TreatID,ActPlant))
    {
      m_pPDL_HEAT_DATA->setPOWER_ON_DUR(PowerOnDur);

      if( Event.getMessage() == LF_EvMsg::evLFPowerOn )    //When get rise edge set power off duration.
      {        
        if ( m_pPDL_HEAT_DATA->getFIRST_POWER_ON(1) == CSMC_DBData::unspecDate )
        {
          m_pPDL_HEAT_DATA->setFIRST_POWER_ON(Now);//only when the time is null then set first power on time. 
        }
      }
      else if ( Event.getMessage() == LF_EvMsg::evLFPowerOff ) //When get down edge set power on duration.
      {
        m_pPDL_HEAT_DATA->setLAST_POWER_OFF(Now);       //set Last Power off time as now.
        m_pPDL_HEAT_DATA->setELEC_CONS(ElecCons); //set Last Power consumption
      }

      if (m_pPDL_HEAT_DATA->update())
      {
        RetValue = true;
        m_pPDL_HEAT_DATA->commit();
      }
      else
      {
        m_pPDL_HEAT_DATA->rollback();

        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PDE_HEAT_DATA", Scope.c_str());
      }
    }

    //set new duration, electric energy info to PD_ELEC_SYSTEM
    RetValue = handlePower(Event,status,ElecCons);
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

//##ModelId=462F6773033B
bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnTapChange(CEventMessage& Event, long TapChangStatus)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  //long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnTapChange");
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

    setpDM_Interface(Event.getSender(),DM::PLANT);
    long VoltTapNo      = m_pDM_Interface->getLong  (DEF_PLANT::Furnace, DATA::VoltTapNo);

    //set new voltap, impcurve, duration and eletric energy info to PD_Elec_Tapch
    if(!handleTapChange(Event, TapChangStatus))
    {
      log("failed to write data to database.CPD_ELEC_TAPCH", 1);
    }
    else
    {
      RetValue = true;
    }

    //== update last trafo tap ==============================================
    if ( RetValue )
    {
      if (m_pPDL_HEAT_DATA->select(HeatID, TreatID, ActPlant))
      {
        m_pPDL_HEAT_DATA->setLASTTRAFOTAP(VoltTapNo);
        if (m_pPDL_HEAT_DATA->update())
          m_pPDL_HEAT_DATA->commit();
        else
          m_pPDL_HEAT_DATA->rollback();
      }
      else
      {
        log("ERROR: could not select to set LASTTRAFOTAP in PDL_HEAT_DATA!",1);
      }
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

bool CARCHIVER_LFSignalsAndMeasurementWrapper::handleCyclicData(CEventMessage& Event)
{
  std::string HeatID  = Event.getHeatID();
  std::string TreatID = Event.getTreatID();
  std::string PlantID = Event.getPlantID();
  std::string Sender  = Event.getSender();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  CDateTime nowTime;

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::handleCyclicData");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;
  //***********************************************************************************


  setpDM_Interface(Sender,DM::PRODUCT);
  double DurSinceHeatAnnounce       = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart          = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);

  std::string PhaseAct              = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseAct));
  long PhaseNo                      = m_pDM_Interface->getLong(ProductID.c_str(), DATA::PhaseNoAct);

  std::string LadleTransferCarId    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(), DATA::LadleTransferCarId));

  double ElecCons                   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

  seqStirringData StirringAmount    = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringAmount));
  seqStirringData StirringFlow      = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringFlow));
  seqStirringData StirringIntensity = CIntfData::ToCORBAType(m_pDM_Interface->getStirringData(ProductID.c_str(), DATA::StirringIntensity));

  setpDM_Interface(Sender,DM::PLANT);
  long VoltTapNo                    = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::VoltTapNo);
  long PowerOn                      = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::PowerOn);
  long EltrdRegCurve                = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ElectrodRegCurve);
  long ElecPosUp                    = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ElecPosUp);
  long FurnBreakOn                  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnBreakOn);
  long FurnTapChangOn               = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnTapChangOn);
  long GantryPosIn                  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::GantryPosIn); 

  if (LadleTransferCarId == "2")
  {
    LadleTransferCarId = DEF_PLANT::TransferCar2;
  }
  else if (LadleTransferCarId == "1")
  {
    LadleTransferCarId = DEF_PLANT::TransferCar1;
  }
  else
  {
    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorTransferCarIdentification(sMessage,LadleTransferCarId.c_str());
  }

  seqComputerModes LFComputerModes  = CIntfData::ToCORBAType(m_pDM_Interface->getComputerModes(LadleTransferCarId.c_str(), DATA::ComputerModes)); 

  long RoofPosUp                    = m_pDM_Interface->getLong(LadleTransferCarId.c_str(), DATA::RoofPosUp);
  long LadleCarPosition             = m_pDM_Interface->getLong(LadleTransferCarId.c_str(), DATA::LadleCarPosition);
  
  CStirringDataHandler StirringDataHandlerFlow(StirringFlow);
  CStirringDataHandler StirringDataHandlerAmount(StirringAmount);
  CStirringDataHandler StirringDataHandlerIntensity(StirringIntensity);

  // ******************************************************************
  // data conversion
  // ******************************************************************
  if (m_pGC_PHASE->selectByPhase(ActPlant, PhaseAct, PhaseNo, CSMC_DBData::unspecLong))
  {
    PhaseNo = m_pGC_PHASE->getL1_PHASE_NO(1);
  }

  // ******************************************************************
  // check validity
  // ******************************************************************
  LadleCarPosition = CDataConversion::SetInvalidToDefault(LadleCarPosition,DEF_CARPOSITION::OutOfOperatingPosition);


  // ******************************************************************
  // write data to DB
  // ******************************************************************

  if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
  {
    CDateTime   now;

    m_pPDL_CYCL_MEAS_DATA->setHEATID(HeatID);
    m_pPDL_CYCL_MEAS_DATA->setTREATID(TreatID);
    m_pPDL_CYCL_MEAS_DATA->setPLANT(ActPlant);
    m_pPDL_CYCL_MEAS_DATA->setREVTIME(now);
    m_pPDL_CYCL_MEAS_DATA->setDURSINCEHEATANNOUNCE(DurSinceHeatAnnounce);
    m_pPDL_CYCL_MEAS_DATA->setDURSINCESTARTOFHEAT(DurSinceHeatStart);
    m_pPDL_CYCL_MEAS_DATA->setELEC_CONS(ElecCons);
    m_pPDL_CYCL_MEAS_DATA->setVOLTTAP(VoltTapNo);
    m_pPDL_CYCL_MEAS_DATA->setIMPCURVE(EltrdRegCurve);
    m_pPDL_CYCL_MEAS_DATA->setELECTRODEPOS(ElecPosUp);
    m_pPDL_CYCL_MEAS_DATA->setFURNACEBRAKERSTATUS(FurnBreakOn);
    m_pPDL_CYCL_MEAS_DATA->setTAPCHANGERSTATUS(FurnTapChangOn);
    m_pPDL_CYCL_MEAS_DATA->setPOWERSTATUS(PowerOn);
    m_pPDL_CYCL_MEAS_DATA->setROOFPOS(RoofPosUp);
    m_pPDL_CYCL_MEAS_DATA->setGANTRYPOS(GantryPosIn);
    m_pPDL_CYCL_MEAS_DATA->setCURPHASE_L1(PhaseNo);
    //m_pPDL_CYCL_MEAS_DATA->setACTIVITYNAME(ActPhase);

    double STIRR_N2_FLOW = StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::N2);
    double STIRR_N2_CONS = StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::N2);

    m_pPDL_CYCL_MEAS_DATA->setSTIRR_N2_FLOW(STIRR_N2_FLOW);
    m_pPDL_CYCL_MEAS_DATA->setSTIRR_N2_CONS(STIRR_N2_CONS);

    double STIRR_AR_FLOW = StirringDataHandlerFlow.getAccumulatedGasValue(DEF_GAS::Ar);
    double STIRR_AR_CONS = StirringDataHandlerAmount.getAccumulatedGasValue(DEF_GAS::Ar);

    m_pPDL_CYCL_MEAS_DATA->setSTIRR_AR_FLOW(STIRR_AR_FLOW);
    m_pPDL_CYCL_MEAS_DATA->setSTIRR_AR_CONS(STIRR_AR_CONS);      

    if ( STIRR_N2_FLOW != DEF::Inv_Double && STIRR_N2_CONS != DEF::Inv_Double)
    {
      long Stirr_Int = (long) StirringDataHandlerIntensity.getMaxGasDataValue(DEF_GAS::N2);
      m_pPDL_CYCL_MEAS_DATA->setSTIRR_INT(Stirr_Int);

      m_pPDL_CYCL_MEAS_DATA->setSTIRRGASTYPE(DEF_GAS::N2);
    }

    if ( STIRR_AR_FLOW != DEF::Inv_Double && STIRR_AR_CONS != DEF::Inv_Double)
    {
      long Stirr_Int = (long) StirringDataHandlerIntensity.getMaxGasDataValue(DEF_GAS::Ar);
      m_pPDL_CYCL_MEAS_DATA->setSTIRR_INT(Stirr_Int);

      m_pPDL_CYCL_MEAS_DATA->setSTIRRGASTYPE(DEF_GAS::Ar);
    }


    for ( long i = 0 ; i < CIntfData::getLength(LFComputerModes) ; ++i)
    {
      sComputerMode ComputerMode;
      CIntfData::getAt(ComputerMode, LFComputerModes, i);

      std::string Device = ComputerMode.Device;

      if ( Device == DEF_COMP_MODES::MatHandle )
      {
        m_pPDL_CYCL_MEAS_DATA->setCOMPMODE_MAT(ComputerMode.Status);
      }
      else if ( Device == DEF_COMP_MODES::Electric )
      {
        m_pPDL_CYCL_MEAS_DATA->setCOMPMODE_ELEC(ComputerMode.Status);
      }
      else if ( Device == DEF_COMP_MODES::Stirring )
      {
        m_pPDL_CYCL_MEAS_DATA->setCOMPMODE_STIRR(ComputerMode.Status);
      }
    }

    if(m_pPDL_CYCL_MEAS_DATA->insert())
    {
      m_pPDL_CYCL_MEAS_DATA->commit();
    }
    else
    {
      m_pPDL_CYCL_MEAS_DATA->rollback();
    }
  }// if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage, "", "PP_HEAT_PLANT", Scope.c_str());
  }

  return true;
}

bool CARCHIVER_LFSignalsAndMeasurementWrapper::handleCoolingWater(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::handleCoolingWater");
  std::stringstream ExceptionMsg;
  //***********************************************************************************

  try
  {   
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    setpDM_Interface(Sender,DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
    double MomentElec           = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons); 
    double MomentO2             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::MomentO2);

    std::string LadleTransferCarId    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(), DATA::LadleTransferCarId));


    seqGasData TotalMetAmountSeq = CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::TotalMetAmount));

    if (LadleTransferCarId == "2")
    {
      LadleTransferCarId = DEF_PLANT::TransferCar2;
    }
    else if (LadleTransferCarId == "1")
    {
      LadleTransferCarId = DEF_PLANT::TransferCar1;
    }
    else
    {
      CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorTransferCarIdentification(sMessage,LadleTransferCarId.c_str());
    }

    setpDM_Interface(Sender,DM::PLANT);
    seqCoolWaterData MeasCoolWaterData = CIntfData::ToCORBAType(m_pDM_Interface->getCoolWaterData(LadleTransferCarId.c_str(),DATA::CoolingWaterData)); 


    if (0 == CIntfData::getLength(MeasCoolWaterData))
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingCyclicData(sMessage, DEF_CYCLIC_MEASUREMENT_TYPES::CoolingWater, Scope.c_str(), "seqCoolWaterData empty");
    }

    CDateTime now;
    for ( long i = 0 ; i < CIntfData::getLength(MeasCoolWaterData) ; ++ i )
    {
      // read all CoolWaterDevices
      sCoolWaterDevice CoolWaterDevice;
      CIntfData::getAt(CoolWaterDevice,&MeasCoolWaterData,i);

      // read CoolWaterData from CoolWaterDevice
      sCoolWater CoolWater = CoolWaterDevice.CoolWaterData;

      // e.g. if car is out of Operating Position temperatures and the flow are set to 0.0 by Tracker. 
      if ( CoolWater.WaterFlow > 0.0 || CoolWater.InletTemp > 0.0 || CoolWater.OutletTemp > 0.0 )
      {
        // **********************************************
        // write process state information, if available
        // may be of type "MomentXX" or seqGasData
        if ( CIntfData::getLength(TotalMetAmountSeq) > 0 )
        {
          CGasDataHandler GasDataHandler(TotalMetAmountSeq);
          m_pPD_COOLWATER->setO2_MOMENT(GasDataHandler.getGasData(DEF_GAS::O2));
          m_pPD_COOLWATER->setAR_MOMENT(GasDataHandler.getGasData(DEF_GAS::Ar));
          m_pPD_COOLWATER->setN2_MOMENT(GasDataHandler.getGasData(DEF_GAS::N2));
        }

        if ( MomentElec != DEF::Inv_Double )
        {
          m_pPD_COOLWATER->setELEC_EGYTOT(MomentElec);
        }

        if ( MomentO2 != DEF::Inv_Double )
        {
          m_pPD_COOLWATER->setO2_MOMENT(MomentO2);
        }
        // **********************************************


        m_pPD_COOLWATER->setPLANT(ActPlant);
        m_pPD_COOLWATER->setHEATID(HeatID);
        m_pPD_COOLWATER->setTREATID(TreatID);
        m_pPD_COOLWATER->setDURSINCEHEATANNOUNCEMENT(DurSinceHeatAnnounce);
        m_pPD_COOLWATER->setDURSINCESTARTOFHEAT(DurSinceHeatStart);
        m_pPD_COOLWATER->setREVTIME(now);

        m_pPD_COOLWATER->setCOOL_EQUIP(std::string(CoolWaterDevice.CoolWaterDevice));
        m_pPD_COOLWATER->setCOOL_LOOP_NO(CoolWaterDevice.CoolWaterDeviceNo);
        m_pPD_COOLWATER->setCW_FLOW(CoolWater.WaterFlow);
        m_pPD_COOLWATER->setCW_TEMP_IN(CoolWater.InletTemp);
        m_pPD_COOLWATER->setCW_TEMP_OUT(CoolWater.OutletTemp);

        if ( m_pPD_COOLWATER->insert() )
        {
          m_pPD_COOLWATER->commit();
          RetValue = true;
        }
        else
        {
          m_pPD_COOLWATER->rollback();

          cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DBWriteError(sMessage,"", "PD_COOLWATER", Scope.c_str());

          RetValue = false;
          break;
        } // if ( m_pPD_COOLWATER->insert() )
      } // if (CoolWater.WaterFlow != 0.0)
    } // for ( long i = 0 ; i < CIntfData::getLength(MeasCoolWaterData) ; ++ i )
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

bool CARCHIVER_LFSignalsAndMeasurementWrapper::doOnMechanicalSystem(CEventMessage& Event)
{
  bool RetValue = false;

  std::string Message   = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_LFSignalsAndMeasurementWrapper::doOnMechanicalSystem");
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

    setpDM_Interface(Event.getSender(),DM::PLANT);
    double ElecCons     = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);

    seqGasData SeqGasData; 

    long ActionNo       = CSMC_DBData::unspecLong; 

    if (Message == LF_EvMsg::evLFRoofArrivesInUpPosition)
    {
      ActionNo = DEF_GC_ACTION_DEF::RoofUp;
    }
    else if (Message == LF_EvMsg::evLFRoofArrivesInDownPosition)
    {
      ActionNo = DEF_GC_ACTION_DEF::RoofDown;
    }
    else if (Message == LF_EvMsg::evLFGantrySwungIn)
    {
      ActionNo = DEF_GC_ACTION_DEF::GantrySwungIn;
    }
    else if (Message == LF_EvMsg::evLFGantrySwungOut)
    {
      ActionNo = DEF_GC_ACTION_DEF::GantrySwungOut;
    }

    RetValue = handleMechanicalSystem(Event, SeqGasData, ElecCons, ActionNo);
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

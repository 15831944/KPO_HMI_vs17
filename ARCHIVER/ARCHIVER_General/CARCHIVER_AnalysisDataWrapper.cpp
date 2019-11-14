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
#include "CDataConversion.h"

#include "CPD_PRETREATDATA.h"
#include "CPD_LADLE.h"
#include "CPD_HEAT_DATA_LIQADD.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_REF.h"
#include "CPD_HOT_METAL.h"
#include "CPD_HOT_METAL_ORDER.h"
#include "CGC_PHASE.h"
#include "CPD_ACTION.h"
#include "CHD_SAMPLE.h"
#include "CHD_SAMPLE_ENTRY.h"
#include "CPD_PLANTSTATUS.h"

#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_MEASUREMENT_ORIGIN.h"
#include "DEF_GC_SAMPLEUSABLE.h"


#include "CARCHIVER_AnalysisDataWrapper.h"


//##ModelId=45D3032F0369
CARCHIVER_AnalysisDataWrapper::CARCHIVER_AnalysisDataWrapper() 
{
}

//##ModelId=45D303300310
CARCHIVER_AnalysisDataWrapper::~CARCHIVER_AnalysisDataWrapper()
{
  deleteDBClasses();
}


//##ModelId=45D4132C0293
bool CARCHIVER_AnalysisDataWrapper::writeAnalysis(CEventMessage& Event, seqAnalysisData& SeqAnalysisData)
{
  bool RetValue = false;

  std::string ProductID   = Event.getProductID();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string DataKey     = Event.getDataKey();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::writeAnalysis");
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

    CDateTime SampleTime;
    CDateTime RecTime;
    CDateTime RecTimeLab;

    std::string SampleId;
    std::string ProcessStage;
    std::string CustHeatID;
    std::string UserCode;
    std::string SampleLocation;

    long SampleNo         = CSMC_DBData::unspecLong;
    long SampleUsable    = 1;
    long SampleMode       = CSMC_DBData::unspecLong;
    long SampleType       = CSMC_DBData::unspecLong;
    long SampleOrigin     = DEF_GC_MEASUREMENT_ORIGIN::Measured;
    long DBSampleCounter  = CSMC_DBData::unspecLong;
    long DBSampleRef      = CSMC_DBData::unspecLong;
    double DurSinceHeatAnnounce      = 0.0;
    double DurSinceHeatStart      = 0.0;

    seqAnalysis      SeqAnalysis;
    sAnalysisData    AnalysisStruct;

    cCBS_ODBC_DBError CBS_ODBC_DBError;


    if (CIntfData::getAt(AnalysisStruct, SeqAnalysisData, 0))
    {
      SampleTime.SetTime(AnalysisStruct.SampleData.SampleTime);
      SampleId        = AnalysisStruct.SampleData.SampleId;
      SampleNo        = AnalysisStruct.SampleData.SampleNo;
      SampleType      = AnalysisStruct.SampleData.SampleType;
      ProcessStage    = AnalysisStruct.SampleData.ProcessStage;
      SampleLocation  = AnalysisStruct.SampleData.SampleLocation;
      SampleMode      = AnalysisStruct.SampleData.SampleMode;
      SampleUsable   = AnalysisStruct.SampleData.SampleUsable;
      SeqAnalysis     = AnalysisStruct.Analysis;

      // collect data from event data interface
      setpDM_Interface(Event.getSender(),DM::EVENT);
      UserCode        = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::UserCode));

      // collect data from product data interface
      setpDM_Interface(Event.getSender(),DM::PRODUCT);
      DurSinceHeatAnnounce  = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
      DurSinceHeatStart     = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

      // check and log data
      if (SampleUsable == DEF::Inv_Long)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HandlingNotUsableAnalysis(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(), SampleId.c_str());
      }

      // if analysis was manual, RECLABTIME is unspecified
      if ( SampleOrigin = DEF_GC_MEASUREMENT_ORIGIN::Manual )
      {
        RecTimeLab   = CSMC_DBData::unspecDate;
      }

      // check for existing sample reference, insert nwe one if required and update PD_HEAT_DATA
      if ( m_pPD_HEAT_DATA && m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
      {
        // determine existing or new SAMPLE_REF
        DBSampleRef = m_pPD_HEAT_DATA->getSAMPLE_REF(1);

        if ( m_pPD_SAMPLE_REF && DBSampleRef == CSMC_DBData::unspecLong )
        {
          DBSampleRef = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF();
          m_pPD_HEAT_DATA->setSAMPLE_REF(DBSampleRef);

          RetValue = m_pPD_HEAT_DATA->update();
        
          if (RetValue)
          {
            m_pPD_HEAT_DATA->commit();
          }
          else
          {
            m_pPD_HEAT_DATA->rollback();
          }
        }
      }

      // try to identify existing Sample data first
      if ( m_pPD_SAMPLE->selectHeatSample(HeatID, TreatID, ActPlant, ActPlantNo, SampleType, SampleNo) )
      {
        DBSampleCounter = m_pPD_SAMPLE->getSAMPLE_COUNTER(1);
      }

      if ( DBSampleCounter == CSMC_DBData::unspecLong )
      {
        // receive next Sample_Counter fur further use.
        DBSampleCounter = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, ActPlant, ActPlantNo, SampleOrigin, SampleType, SampleNo, SeqAnalysis, true, CBS_ODBC_DBError);
        
        SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithoutsampletaken; // 2
      }

      if ( DBSampleCounter != CSMC_DBData::unspecLong )
      {

        // update methods do not perform commit statement !
        if ( m_pPD_SAMPLE->updateSampleDetails(DBSampleCounter,ProdOrderID,SampleMode,SampleLocation,SampleUsable,UserCode,SampleId,SampleOrigin)  && 
             m_pPD_SAMPLE->updateSampleTimes(DBSampleCounter,SampleTime,RecTime,RecTimeLab,DurSinceHeatAnnounce,DurSinceHeatStart, false)     )
        {
          // now update references in PD_SAMPLE_REF
          // for Steel Sample, update PD_SAMPLE_REF.STEEL, 
          RetValue = m_pPD_SAMPLE_REF->updateSAMPLE_REF(DBSampleRef,DBSampleCounter,SampleType);
        }
      }

      // updating pretreatment data
      RetValue = RetValue && updatePretreatSampleRef( Event, DBSampleRef );

      // updating liquid addition data
      //zhpf, here should NOT update pd_heat_data_Liqadd for that sample_ref
      //means added liq sample_ref instead of current heat
      //RetValue = RetValue && updateLiqAddSampleRef( Event, DBSampleRef );


      setpDM_Interface(Event.getSender(),DM::PRODUCT);

      double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
      double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

      CPD_ACTION::ActionRow pdActionRow;
      pdActionRow.HEATID                    = HeatID;
      pdActionRow.TREATID                   = TreatID;
      pdActionRow.PLANT                     = ActPlant;
      pdActionRow.ACTIONNO                  = DEF_GC_ACTION_DEF::AnalysisReceived;
      pdActionRow.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
      pdActionRow.DURSINCESTARTOFHEAT       = DurSinceHeatStart;

      RetValue = m_pPD_ACTION->write(pdActionRow );
      if (!RetValue)
      {
        std::stringstream Msg;
        Msg << "ERROR: insert action '" << DEF_GC_ACTION_DEF::AnalysisReceived << "' failed!";
        log(Msg.str(),1);
        m_pPD_ACTION->rollback();
      }


    } // if (CIntfData::getAt(AnalysisStruct, SeqAnalysisData, 0))
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingAnalysis(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(),"empty analysis sequence received");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=45D417B603CE
bool CARCHIVER_AnalysisDataWrapper::writeSample(CEventMessage& Event,long TreatmentPosition )
{
  bool RetValue = true;

  std::string ProductID   = Event.getProductID();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string DataKey     = Event.getDataKey();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::writeSample");
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

    CDateTime SampleTime;
    CDateTime RecTime;
    CDateTime RecTimeLab;

    std::string SampleId;
    std::string ProcessStage;
    std::string CustHeatID;
    std::string UserCode;
    std::string SampleLocation;

    long SampleNo         = CSMC_DBData::unspecLong;
    long SampleUsable    = 1;
    long SampleMode       = CSMC_DBData::unspecLong;
    long SampleType       = CSMC_DBData::unspecLong;
    long SampleOrigin     = DEF_GC_MEASUREMENT_ORIGIN::Measured;
    long DBSampleCounter  = CSMC_DBData::unspecLong;
    long DBSampleRef      = CSMC_DBData::unspecLong;
    double DurSinceHeatAnnounce      = 0.0;
    double DurSinceHeatStart      = 0.0;

    seqSampleData SeqSampleData;
    sSampleData   sSampleData;
    seqSample     SeqSample; // empty sequence!

    cCBS_ODBC_DBError CBS_ODBC_DBError;

    // collect data from event data interface
    setpDM_Interface(Event.getSender(),DM::EVENT);
    SeqSampleData   = CIntfData::ToCORBAType(m_pDM_Interface->getSampleData(DataKey.c_str(), DATA::SampleData));
    UserCode        = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::UserCode));

    if (CIntfData::getAt(sSampleData, SeqSampleData, 0))
    {
      SampleTime.SetTime(sSampleData.SampleTime);
      SampleId        = sSampleData.SampleId;
      SampleNo        = sSampleData.SampleNo;
      SampleType      = sSampleData.SampleType;
      ProcessStage    = sSampleData.ProcessStage;
      SampleMode      = sSampleData.SampleMode;
      SampleLocation  = sSampleData.SampleLocation;
      SampleUsable   = sSampleData.SampleUsable;

      // ***********************************************************************************************
      // now set all previous samples (for identical sample type) without analysis to "SAMPLEUSABLE" = 0
      // ***********************************************************************************************

      if ( m_pPD_SAMPLE->selectLastSampleWithoutAnalysis(HeatID,TreatID,ActPlant,ActPlantNo,SampleType) )
      {
        m_pPD_SAMPLE->setSAMPLEUSABLE(0);

        RetValue = RetValue && m_pPD_SAMPLE->update();

        if (!RetValue)
        {
          m_lastError = m_pPD_SAMPLE->getLastError();
        }
      } // if ( m_pPD_SAMPLE->selectLastSampleWithoutAnalysis(HeatID,TreatID,ActPlant,ActPlantNo,SampleType) )


      // collect data from product data interface
      setpDM_Interface(Event.getSender(),DM::PRODUCT);

      double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
      double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

      if (SampleType <= 0 || SampleType == DEF::Inv_Long)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingSample(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(), SampleId.c_str());
      }

      // receive next Sample_Counter fur further use.
      DBSampleCounter = m_pPD_SAMPLE->insertSample(HeatID, TreatID, ActPlant, ActPlantNo, SampleOrigin, SampleType, SampleNo, SeqSample, true, CBS_ODBC_DBError);

      if ( DBSampleCounter != CSMC_DBData::unspecLong )
      {
        // update methods do not perform commit statement !
        if ( m_pPD_SAMPLE->updateSampleDetails(DBSampleCounter,ProdOrderID,SampleMode,SampleLocation,SampleUsable,UserCode,SampleId,SampleOrigin)  && 
             m_pPD_SAMPLE->updateSampleTimes(DBSampleCounter,SampleTime,RecTime,CSMC_DBData::unspecDate,DurSinceHeatAnnounce,DurSinceHeatStart, false)     )
        {
          // now update references in PD_SAMPLE_REF
          // for Steel Sample, update PD_SAMPLE_REF.STEEL, ...
          // creating new Sample_Ref if required
          handleSampleRef(HeatID,TreatID,ActPlant,ActPlantNo,SampleType, DBSampleCounter);
        }
      }

      sMetTimeStamp MetTimeStamp;

      MetTimeStamp.DurSinceHeatAnnouncement = DurSinceHeatAnnounce;
      MetTimeStamp.DurSinceStartOfHeat      = DurSinceHeatStart;

      RetValue = RetValue && m_pPD_ACTION->UpdateOrInsertAction(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::SampleTaken, "", CDataConversion::LongToString(SampleNo), 1, MetTimeStamp, false, true, m_lastError);

      //update PD_PlantStatus
      RetValue = RetValue && m_pPD_PLANTSTATUS->updateSampleCounter(ActPlant, ActPlantNo, HeatID, TreatID, DBSampleCounter, TreatmentPosition, true, m_lastError);

      //copy to HD tables
      RetValue = RetValue && m_pHD_SAMPLE->copy(HeatID, TreatID, ActPlant, ActPlantNo, DBSampleCounter, true, m_lastError);
      RetValue = RetValue && m_pHD_SAMPLE_ENTRY->copy(DBSampleCounter, true, m_lastError);

      if ( !RetValue)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorHandlingAnalysis(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(),m_lastError.m_MessageText.c_str());
      }

    } // if (CIntfData::getAt(AnalysisStruct, SeqAnalysisData, 0))
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingAnalysis(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(),"empty analysis sequence received");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}
//##ModelId=45D30D09016E
bool CARCHIVER_AnalysisDataWrapper::writeHMAnalysis(CEventMessage& Event, seqAnalysisData &SeqAnalysisData)
{
  bool RetValue = false;

  std::string ProductID   = Event.getProductID();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string DataKey     = Event.getDataKey();
  std::string ProdOrderID = Event.getOrderID();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(PlantID);;

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::writeHMAnalysis");
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

    CDateTime SampleTime;
    CDateTime RecTime;
    CDateTime RecTimeLab;

    std::string SampleId;
    std::string ProcessStage;
    std::string CustHeatID;
    std::string UserCode;
    std::string SampleLocation;

    long SampleNo         = CSMC_DBData::unspecLong;
    long SampleUsable    = 1;
    long SampleMode       = CSMC_DBData::unspecLong;
    long SampleType       = CSMC_DBData::unspecLong;
    long SampleOrigin     = DEF_GC_MEASUREMENT_ORIGIN::Measured;
    long DBSampleCounter  = CSMC_DBData::unspecLong;
    long DBSampleRef      = CSMC_DBData::unspecLong;
    long HotMetalCounter  = CSMC_DBData::unspecLong;
    double DurSinceHeatAnnounce      = 0.0;
    double DurSinceHeatStart      = 0.0;

    seqAnalysis      SeqAnalysis;
    sAnalysisData    AnalysisStruct;

    cCBS_ODBC_DBError CBS_ODBC_DBError;

    if (CIntfData::getAt(AnalysisStruct, SeqAnalysisData, 0))
    {
      SampleTime.SetTime(AnalysisStruct.SampleData.SampleTime);
      SampleId      = AnalysisStruct.SampleData.SampleId;
      SampleNo      = AnalysisStruct.SampleData.SampleNo;
      SampleType    = AnalysisStruct.SampleData.SampleType;
      SampleMode    = AnalysisStruct.SampleData.SampleMode;
      SampleUsable = AnalysisStruct.SampleData.SampleUsable;
      ProcessStage  = AnalysisStruct.SampleData.ProcessStage;
      SeqAnalysis   = AnalysisStruct.Analysis;

      // read CORBA data

      // collect data from event data interface

      // collect data from product data interface
      setpDM_Interface(Event.getSender(),DM::PRODUCT);
      DurSinceHeatAnnounce  = getDurationSince(m_pDM_Interface, ProductID,DATA::HeatAnnounceTime);
      DurSinceHeatStart     = getDurationSince(m_pDM_Interface, ProductID,DATA::HeatStartTime);

      // check data
      // if analysis was manual, RECLABTIME is unspecified
      if ( SampleOrigin = DEF_GC_MEASUREMENT_ORIGIN::Manual )
      {
        RecTimeLab   = CSMC_DBData::unspecDate;
      }

      // creating new Sample_Ref if required
      if ( m_pPD_HOT_METAL_ORDER->select(ActPlant,ProdOrderID,CSMC_DBData::unspecLong) )
      {
        HotMetalCounter = m_pPD_HOT_METAL_ORDER->getHOTMETAL_COUNTER(1);

        if ( HotMetalCounter != CSMC_DBData::unspecLong )
        {
          if ( m_pPD_HOT_METAL->select(HotMetalCounter) )
          {
            DBSampleRef = m_pPD_HOT_METAL->getSAMPLE_REF(1);
          }
        }
      }

      if ( DBSampleRef == CSMC_DBData::unspecLong )
      {
        if ( m_pPD_SAMPLE_REF )
        {
          DBSampleRef = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF(false, CBS_ODBC_DBError);
        }
      }

      // try to identify existing Sample data first
      if ( m_pPD_SAMPLE->selectHeatSample(HeatID, TreatID, ActPlant, ActPlantNo, SampleType, SampleNo) )
      {
        DBSampleCounter = m_pPD_SAMPLE->getSAMPLE_COUNTER(1);
      }

      if ( DBSampleCounter == CSMC_DBData::unspecLong )
      {
        // receive next Sample_Counter fur further use.
        DBSampleCounter = m_pPD_SAMPLE->insertAnalysis(HeatID, TreatID, ActPlant, ActPlantNo, SampleOrigin,
          SampleType, SampleNo, SeqAnalysis, true, CBS_ODBC_DBError);

        SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithoutsampletaken; // 2
      }

      if ( DBSampleCounter != CSMC_DBData::unspecLong )
      {

        // update methods do not perform commit statement !
        if ( m_pPD_SAMPLE->updateSampleDetails(DBSampleCounter,ProdOrderID,SampleMode,SampleLocation,SampleUsable,UserCode,SampleId,SampleOrigin)  && 
             m_pPD_SAMPLE->updateSampleTimes(DBSampleCounter,SampleTime,RecTime,RecTimeLab,DurSinceHeatAnnounce,DurSinceHeatStart, false)     )
        {
          // now update references in PD_SAMPLE_REF
          // for Steel Sample, update PD_SAMPLE_REF.STEEL, ...
          RetValue = m_pPD_SAMPLE_REF->updateSAMPLE_REF(DBSampleRef,DBSampleCounter,SampleType);
        }
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage, "" , "PD_SAMPLE", "insert failure");

        m_pPD_SAMPLE->rollback();
      }

      // update hot metal data
      // hot metal is related to ProdOrdeId or ladle data
      updateHotMetalSampleRef(Event,DBSampleCounter);

    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingAnalysis(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(),"empty analysis sequence received");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=45D30D0901AA
bool CARCHIVER_AnalysisDataWrapper::writeHMSample(CEventMessage& Event)
{
  bool RetValue = false;

  std::string ProductID   = Event.getProductID();
  std::string HeatID      = Event.getHeatID();
  std::string TreatID     = Event.getTreatID();
  std::string DataKey     = Event.getDataKey();
  std::string ProdOrderID = Event.getOrderID();
  std::string PlantID     = Event.getPlantID();
  std::string ActPlant    = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo         = m_pGC_Plant_Container->getPlantNo(PlantID);;

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::writeHMSample");
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

    CDateTime SampleTime;
    CDateTime RecTime;
    CDateTime RecTimeLab;

    std::string SampleId;
    std::string ProcessStage;
    std::string CustHeatID;
    std::string UserCode;
    std::string SampleLocation;

    long SampleNo         = CSMC_DBData::unspecLong;
    long SampleUsable    = 1;
    long SampleMode       = CSMC_DBData::unspecLong;
    long SampleType       = CSMC_DBData::unspecLong;
    long SampleOrigin     = DEF_GC_MEASUREMENT_ORIGIN::Measured;
    long DBSampleCounter  = CSMC_DBData::unspecLong;
    long DBSampleRef      = CSMC_DBData::unspecLong;
    long HotMetalCounter  = CSMC_DBData::unspecLong;
    double DurSinceHeatAnnounce      = 0.0;
    double DurSinceHeatStart      = 0.0;

    double MeasTemp       = 0.0;

    seqSampleData SeqSampleData;
    sSampleData   sSampleData;
    seqSample     SeqSample; // empty sequence!

    cCBS_ODBC_DBError CBS_ODBC_DBError;

    // collect data from event data interface
    setpDM_Interface(Event.getSender(),DM::EVENT);
    SeqSampleData   = CIntfData::ToCORBAType(m_pDM_Interface->getSampleData(DataKey.c_str(), DATA::SampleData));
    UserCode        = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::UserCode));

    // additional values, if measured
    MeasTemp        = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::MeasTemp);

    if (CIntfData::getAt(sSampleData, SeqSampleData, 0))
    {
      SampleTime.SetTime(sSampleData.SampleTime);
      SampleId      = sSampleData.SampleId;
      SampleNo      = sSampleData.SampleNo;
      SampleType    = sSampleData.SampleType;
      ProcessStage  = sSampleData.ProcessStage;
      SampleMode    = sSampleData.SampleMode;
      SampleUsable = sSampleData.SampleUsable;

      // collect data from product data interface
      setpDM_Interface(Event.getSender(),DM::PRODUCT);
      DurSinceHeatAnnounce  = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
      DurSinceHeatStart     = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

      // check and log data
      std::stringstream sc;
      sc << "SampleID is: " << SampleId << ", SampleNo is: " << SampleNo;
      sc << ", SampleType is:" << SampleType << ", SampleMode is: " << SampleMode;
      log(sc.str(),3);

      // creating new Sample_Ref if required
      if ( m_pPD_HOT_METAL_ORDER->select(ActPlant,ProdOrderID,CSMC_DBData::unspecLong) )
      {
        HotMetalCounter = m_pPD_HOT_METAL_ORDER->getHOTMETAL_COUNTER(1);

        if ( HotMetalCounter != CSMC_DBData::unspecLong )
        {
          if ( m_pPD_HOT_METAL->select(HotMetalCounter) )
          {
            DBSampleRef = m_pPD_HOT_METAL->getSAMPLE_REF(1);
          }
        }
      }

      if ( DBSampleRef == CSMC_DBData::unspecLong )
      {
        if ( m_pPD_SAMPLE_REF )
        {
          DBSampleRef = m_pPD_SAMPLE_REF->insertNewSAMPLE_REF(false, CBS_ODBC_DBError);
        }
      }

      // receive next Sample_Counter fur further use.
      DBSampleCounter = m_pPD_SAMPLE->insertSample(HeatID, TreatID, ActPlant, ActPlantNo, SampleOrigin,
        SampleType, SampleNo, SeqSample, true, CBS_ODBC_DBError);


      if ( DBSampleCounter != CSMC_DBData::unspecLong )
      {
        // update methods do not perform commit statement !
        if ( m_pPD_SAMPLE->updateSampleDetails(DBSampleCounter,ProdOrderID,SampleMode,SampleLocation,SampleUsable,UserCode,SampleId,SampleOrigin) 
          && m_pPD_SAMPLE->updateSampleTimes(DBSampleCounter,SampleTime,RecTime,CSMC_DBData::unspecDate,DurSinceHeatAnnounce,DurSinceHeatStart, false))
        {
          // now update references in PD_SAMPLE_REF
          // for HM Sample, update PD_SAMPLE_REF.STEEL, 
          RetValue = m_pPD_SAMPLE_REF->updateSAMPLE_REF(DBSampleRef,DBSampleCounter,SampleType);
        }
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage, "" , "PD_SAMPLE", "insert failure");

        m_pPD_SAMPLE->rollback();
      }

      // update hot metal data
      // hot metal is related to ProdOrdeId or ladle data
      updateHotMetalSampleRef(Event,DBSampleCounter);

    } // if (CIntfData::getAt(sSampleData, SeqSampleData, 0))
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingSample(sMessage, HeatID.c_str(), TreatID.c_str(), ActPlant.c_str(),"");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

//##ModelId=45D3036C01DD
void CARCHIVER_AnalysisDataWrapper::deleteDBClasses()
{
  if (m_pPD_SAMPLE) { delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0; }
  if (m_pPD_SAMPLE_REF) { delete m_pPD_SAMPLE_REF; m_pPD_SAMPLE_REF = 0; }
  if (m_pPD_HOT_METAL) { delete m_pPD_HOT_METAL; m_pPD_HOT_METAL = 0; }
  if (m_pPD_HOT_METAL_ORDER) { delete m_pPD_HOT_METAL_ORDER; m_pPD_HOT_METAL_ORDER = 0; }
  if (m_pPD_PRETREATDATA) { delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0; }
  if (m_pPD_LADLE) { delete m_pPD_LADLE; m_pPD_LADLE = 0; }
  if (m_pPD_HEAT_DATA_LIQADD) { delete m_pPD_HEAT_DATA_LIQADD; m_pPD_HEAT_DATA_LIQADD = 0; }
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0; }
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0; }
  if (m_pGC_PHASE) { delete m_pGC_PHASE; m_pGC_PHASE = 0; }
  if (m_pPD_HEAT_DATA) { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0; }
  if (m_pPD_ACTION) {delete m_pPD_ACTION; m_pPD_ACTION =0;}
  if (m_pHD_SAMPLE) {delete m_pHD_SAMPLE; m_pHD_SAMPLE = 0;}
  if (m_pHD_SAMPLE_ENTRY) {delete m_pHD_SAMPLE_ENTRY; m_pHD_SAMPLE_ENTRY = 0;}
  if (m_pGC_Plant_Container) { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
  if (m_pPD_PLANTSTATUS) {delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
}

//##ModelId=45D3036D022E
void CARCHIVER_AnalysisDataWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPD_SAMPLE            = new CPD_SAMPLE(pConnection);
  m_pPD_SAMPLE_REF        = new CPD_SAMPLE_REF(pConnection);
  m_pPD_HOT_METAL         = new CPD_HOT_METAL(pConnection);
  m_pPD_HOT_METAL_ORDER   = new CPD_HOT_METAL_ORDER(pConnection);
  m_pPD_PRETREATDATA      = new CPD_PRETREATDATA(pConnection);
  m_pPD_LADLE             = new CPD_LADLE(pConnection);
  m_pPD_HEAT_DATA_LIQADD  = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPP_HEAT              = new CPP_HEAT(pConnection);
  m_pPP_HEAT_PLANT        = new CPP_HEAT_PLANT(pConnection);
  m_pGC_PHASE             = new CGC_PHASE(pConnection);
  m_pPD_HEAT_DATA         = new CPD_HEAT_DATA(pConnection);
  m_pPD_ACTION            = new CPD_ACTION(pConnection);
  m_pHD_SAMPLE            = new CHD_SAMPLE(pConnection);
  m_pHD_SAMPLE_ENTRY      = new CHD_SAMPLE_ENTRY(pConnection);
  m_pPD_PLANTSTATUS       = new CPD_PLANTSTATUS(pConnection);

  m_pGC_Plant_Container   = new CGC_Plant_Container(pConnection);
}


bool CARCHIVER_AnalysisDataWrapper::updatePretreatSampleRef(CEventMessage& Event, long SampleRef )
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
  std::string Scope("CARCHIVER_AnalysisDataWrapper::updatePretreatSampleRef");
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

    if ( SampleRef != CSMC_DBData::unspecLong && m_pPD_PRETREATDATA->selectValidDataByHeat(HeatID,TreatID) )
    {
      m_pPD_PRETREATDATA->setSAMPLE_REF(SampleRef);

      if ( m_pPD_PRETREATDATA->update() )
      {
        m_pPD_PRETREATDATA->commit();
      }
      else
      {
        m_pPD_PRETREATDATA->rollback();
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage, HeatID.c_str(), "PD_PRETREATDATA");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}



bool CARCHIVER_AnalysisDataWrapper::updateHotMetalSampleRef(CEventMessage& Event, long SampleRef)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::updateHotMetalSampleRef");
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

    std::string LadleType;
    long LadleNo          = CSMC_DBData::unspecLong;
    long Hotmetal_Counter = CSMC_DBData::unspecLong;

    // collect data from event data interface
    setpDM_Interface(Event.getSender(),DM::EVENT);
    LadleType       = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleType));
    LadleNo         = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LadleNo);

    // first check if data are available at PD_HOT_METAL_ORDER
    if ( ProdOrderID != DEF::Inv_String && m_pPD_HOT_METAL_ORDER->select(ActPlant,ProdOrderID,CSMC_DBData::unspecLong) )
    {
      Hotmetal_Counter = m_pPD_HOT_METAL_ORDER->getHOTMETAL_COUNTER(1);
    }

    // if not, try to find hot metal data by ladle information
    if ( Hotmetal_Counter == CSMC_DBData::unspecLong )
    {
      // now check if update of ladle data is possible
      if ( LadleNo != DEF::Inv_Long && 
        LadleType != DEF::Inv_String && 
        m_pPD_LADLE->select(LadleNo,LadleType) )
      {
        Hotmetal_Counter = m_pPD_LADLE->getHOTMETAL_CNT_ACT(1);
      }
    }

    // if HOTMETAL_COUNTER has been found update SAMPLE_REF
    if ( Hotmetal_Counter != CSMC_DBData::unspecLong && m_pPD_HOT_METAL->select(Hotmetal_Counter) )
    {
      m_pPD_HOT_METAL->setSAMPLE_REF(SampleRef);

      if ( m_pPD_HOT_METAL->update() )
      {
        m_pPD_HOT_METAL->commit();
      }
      else
      {
        m_pPD_HOT_METAL->rollback();
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage, HeatID.c_str(), "PD_HOTMETAL");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}

bool CARCHIVER_AnalysisDataWrapper::updateLiqAddSampleRef(CEventMessage& Event, long SampleRef)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string ProdOrderID = Event.getOrderID();

  if(ProdOrderID.empty())
  {
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    ProdOrderID    = CIntfData::ToStdString(m_pDM_Interface->getString(ProductID.c_str(),DATA::OrderId));
  }
  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_AnalysisDataWrapper::updateLiqAddSampleRef");
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

    std::string LadleType;
    long LadleNo          = CSMC_DBData::unspecLong;

    // collect data from event data interface
    setpDM_Interface(Event.getSender(),DM::EVENT);
    LadleType       = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleType));
    LadleNo         = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LadleNo);

    // now check if update of ladel data is possible
    if ( LadleNo != DEF::Inv_Long && 
      LadleType != DEF::Inv_String && 
      m_pPD_HEAT_DATA_LIQADD->selectHeatByLadle(HeatID,TreatID,ActPlant,LadleType,LadleNo, CSMC_DBData::unspecString) )
    {
      m_pPD_HEAT_DATA_LIQADD->setSAMPLE_REF(SampleRef);

      if ( ! m_pPD_HEAT_DATA_LIQADD->update() )
      {
        m_pPD_HEAT_DATA_LIQADD->commit();
      }
      else
      {
        m_pPD_HEAT_DATA_LIQADD->rollback();
      }
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage, HeatID.c_str(), "PD_HEAT_DATA_LIQADD");
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
    pEventLog->EL_ExceptionCaught(sMessage, "", Scope.c_str(), Msg.c_str()); 
    RetValue = false;
  }
  return RetValue;
}
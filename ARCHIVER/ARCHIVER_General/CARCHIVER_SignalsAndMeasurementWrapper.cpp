// Copyright (C) 2009 SMS Siemag AG, Germany

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
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
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_ELEC_SYSTEM.h"
#include "DEF_GC_SAMPLEUSABLE.h"

#include "CARCHIVER_SignalsAndMeasurementWrapper.h"



CARCHIVER_SignalsAndMeasurementWrapper::CARCHIVER_SignalsAndMeasurementWrapper() 
:m_pPP_HEAT_PLANT(0)
,m_pPP_HEAT(0)
,m_pGC_PHASE(0)
,m_pPD_SAMPLE(0)
,m_pPD_SAMPLE_ENTRY(0)
,m_pPD_ACTION(0)
,m_pPD_LADLE(0)
,m_pPD_LADLE_LIFE_DATA(0)
,m_pPD_ELEC_SYSTEM(0)
,m_pPD_TAPCH_DATA(0)
,m_pPD_COOLWATER(0)
,m_pPD_PHASE_RES(0)
,m_pPD_PHASE_RES_ANL(0)
,m_pEquipmentData(0)
,m_pHeatStatusContainer(0)
,m_pPD_PRETREATDATA(0)
,m_pPD_HEAT_REF(0)
,m_pPD_PLANTSTATUS(0)
,m_pPD_WASTEGAS_CYCL_MEAS_DATA(0)
,m_pPD_HEAT_DATA(0)
,m_pPP_ORDER(0)
,m_pPD_SAMPLE_REF(0)
,m_pGC_SAMPLELOC(0)
,m_pHD_SAMPLE(0)
,m_pHD_SAMPLE_ENTRY(0)
,m_pGC_HEAT_STATUS(0)
,m_pPD_RECIPE(0)
,m_pPD_RECIPE_ENTRY(0)
{
}

CARCHIVER_SignalsAndMeasurementWrapper::~CARCHIVER_SignalsAndMeasurementWrapper()
{
  deleteDBClasses();
}
bool CARCHIVER_SignalsAndMeasurementWrapper::handleTempOxyMeasurement(CEventMessage& Event,long TreatmentPosition)
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
  std::string MessageName = Event.getMessage();


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleTempOxyMeasurement");
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

    long DBSampleCounter  = CSMC_DBData::unspecLong;
    long DBSampleRef      = CSMC_DBData::unspecLong;
    std::string SampleId;	
    std::string SampleLocation;
    std::string ProcessStage;
    long SampleNo     = CSMC_DBData::unspecLong;;
    long MeasType     = CSMC_DBData::unspecLong;;
    long SampleMode   = CSMC_DBData::unspecLong;;   
    long SampleUsable = DEF_GC_SAMPLEUSABLE::usablewithsampletaken; // 1;   
    long SampleOrigin = CSMC_DBData::unspecLong;;   
    CDateTime   SampleTime;
    CDateTime   RecTime;

    seqSample   SeqSample;
    sSample     Sample;

    cCBS_ODBC_DBError CBS_ODBC_DBError;

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);
    double Elecons              = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

    // collect data from event data interface
    setpDM_Interface(Event.getSender(),DM::EVENT);
    seqSampleData SeqSampleData = CIntfData::ToCORBAType(m_pDM_Interface->getSampleData(DataKey.c_str(), DATA::SampleData));
    double MeasTemp             = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasTemp);
    double MeasO2Conc           = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasO2Conc);
    double MeasCarbonConc       = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasCarbonConc);
    double MeasAlConc           = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasAlConc);
    double MeasFeOConc          = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasFeOConc);
    double MeasMnOConc          = m_pDM_Interface->getDouble(DataKey.c_str(), DATA::MeasMnOConc);
    long SampleType             = m_pDM_Interface->getLong  (DataKey.c_str(), DATA::SampleType);
    std::string UserCode        = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::UserCode));

    CDateTime TempMeasTime(m_pDM_Interface->getDate  (DataKey.c_str(), DATA::TempMeasTime) );

    if ( TempMeasTime != CDateTime::InvalidDateTime() )
    {
      SampleTime = TempMeasTime;
    }

    if ( CIntfData::getLength(SeqSampleData) > 0)
    {
      sSampleData sSampleData;

      // get data from last entry in sequence
      if (CIntfData::getAt(sSampleData, SeqSampleData, CIntfData::getLength(SeqSampleData) - 1))
      {
        SampleTime.SetTime(sSampleData.SampleTime);
        SampleId        = sSampleData.SampleId;
        SampleNo        = sSampleData.SampleNo;
        ProcessStage    = sSampleData.ProcessStage;         
        SampleMode      = sSampleData.SampleMode;
        SampleLocation  = sSampleData.SampleLocation;
        MeasType        = sSampleData.SampleType;
        SampleUsable    = sSampleData.SampleUsable;
        SampleOrigin    = sSampleData.SampleOrigin;
      }
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
      
    // fill SeqSample if measured values are avaiable
    if ( MeasTemp != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Temp.c_str();
      Sample.MeasValue = MeasTemp;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Temp;
    }
    //if ( MeasFreeboard != DEF::Inv_Double )
    //{
    //  Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Freeboard.c_str(); 
    //  Sample.MeasValue = MeasFreeboard;
    //  CIntfData::insert(SeqSample,Sample);
    //  SampleType       = DEF_GC_MEASUREMENT_TYPE::Temp;
    //}
    //if ( MeasHydrisConc != DEF::Inv_Double )                  // forwarding Hydris to EMF
    //{
    //  //Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::H.c_str(); 
    //  Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::EMF.c_str(); 
    //  Sample.MeasValue = MeasHydrisConc;
    //  CIntfData::insert(SeqSample,Sample);
    //  SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox;
    //}
    if ( MeasO2Conc != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::O2.c_str(); 
      Sample.MeasValue = MeasO2Conc;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox;
    }
    if ( MeasCarbonConc != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::C.c_str(); 
      Sample.MeasValue = MeasCarbonConc;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox;
    }
    if ( MeasAlConc != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::Al.c_str(); 
      Sample.MeasValue = MeasAlConc;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox;
    }
    //if ( MeasEMF != DEF::Inv_Double )
    //{
    //  Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::EMF.c_str(); 
    //  Sample.MeasValue = MeasEMF;
    //  CIntfData::insert(SeqSample,Sample);
    //  SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox;
    //}
    if ( MeasFeOConc != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::FeO.c_str(); 
      Sample.MeasValue = MeasFeOConc;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox_Slag;
    }
    if ( MeasMnOConc != DEF::Inv_Double )
    {
      Sample.MeasName  = DEF_GC_MEASUREMENT_NAME::MnO.c_str(); 
      Sample.MeasValue = MeasMnOConc;
      CIntfData::insert(SeqSample,Sample);
      SampleType       = DEF_GC_MEASUREMENT_TYPE::Celox_Slag;
    }

    if ( SampleNo == DEF::Inv_Long )
    {
      SampleNo = 1 + m_pPD_SAMPLE->getLastSampleNo(HeatID, TreatID, ActPlant, ActPlantNo, SampleType );
    }

    // receive next Sample_Counter fur further use.
    DBSampleCounter = m_pPD_SAMPLE->insertSample(HeatID, TreatID, ActPlant, ActPlantNo, SampleOrigin, 
                                                 SampleType, SampleNo, SeqSample, true, CBS_ODBC_DBError);

    if ( DBSampleCounter != CSMC_DBData::unspecLong )
    {
      // update methods do not perform commit statement !
      if ( m_pPD_SAMPLE->updateSampleDetails(DBSampleCounter,OrderID,SampleMode,SampleLocation,SampleUsable,UserCode,SampleId,SampleOrigin)  && 
           m_pPD_SAMPLE->updateSampleTimes(DBSampleCounter,SampleTime,RecTime,CSMC_DBData::unspecDate,DurSinceHeatAnnounce,DurSinceHeatStart, true)     )
      {
        m_pPD_SAMPLE_REF->writeSAMPLE_REF(DBSampleRef,DBSampleCounter,SampleType);

        RetValue = true;
      }
    }

    if ( RetValue )
    {
      m_pPD_SAMPLE->commit();
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_SAMPLE-", "" );

      m_pPD_SAMPLE->rollback();
    }

    // insert additional measurements
    if ( DBSampleCounter != CSMC_DBData::unspecLong )  
    {
      m_pPD_SAMPLE->insertSampleDetail(DBSampleCounter,DEF_GC_MEASUREMENT_NAME::ElecEgy,Elecons);
      //addSampleDetails(DBSampleCounter,HeatID, TreatID, ActPlant, ActPlantNo);
    }

    if ( RetValue )
    {
      // updating heat data or pretreatment data
      if ( !m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
      {
        updatePretreatSampleRef( Event, DBSampleRef );
      }
      else
      {
        updateHeatDataSampleRef( Event, DBSampleRef );

        if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
        {
          //double TEMP_START = m_pPD_HEAT_DATA->getTEMP_START(1);

          if ( MeasTemp != DEF::Inv_Double )
          {
            m_pPD_HEAT_DATA->setFINALTEMP(MeasTemp);

            //if ( TEMP_START == CSMC_DBData::unspecDouble )
            //{
            //  m_pPD_HEAT_DATA->setTEMP_START(MeasTemp);              
            //}

            if ( m_pPD_HEAT_DATA->update() )
            {
              m_pPD_HEAT_DATA->commit();
            }
            else
            {
              cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DBWriteError(sMessage,"", "PD_HEAT_DATA-", "" );

              m_pPD_HEAT_DATA->rollback();
            }
          }
        }
      }
    } // if ( RetValue )

    //update PD_PlantStatus
    m_pPD_PLANTSTATUS->updateSampleCounter(ActPlant, ActPlantNo, HeatID, TreatID, DBSampleCounter, TreatmentPosition, true, m_lastError);

    //copy to HD
    RetValue = RetValue && m_pHD_SAMPLE->copy(HeatID, TreatID, ActPlant, ActPlantNo, DBSampleCounter, true, m_lastError);
    RetValue = RetValue && m_pHD_SAMPLE_ENTRY->copy(DBSampleCounter, true, m_lastError);

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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleElectrodesInOperatingPosition(CEventMessage& Event, double elecegy, long status)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleElectrodesInOperatingPosition");
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

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);


    /*CPD_ELEC_SYSTEM:: bool write(
    const std::string& HeatID, const std::string& TreatID, const std::string& SystemCode, 
    const std::string& Plant, long Status,
    double DurSinceHeatAnnounce, double DurSinceHeatStart, double ElecEgy
    );*/
    RetValue = m_pPD_ELEC_SYSTEM->write(HeatID, TreatID, DEF_GC_ELEC_SYSTEM::ELECTRODEPOS, ActPlant, status,
                                        DurSinceHeatAnnounce, DurSinceHeatStart, elecegy );

    if(!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ELEC_SYSTEM", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleFurnaceBreaker(CEventMessage& Event, long  status)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleFurnaceBreaker");
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

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);
    double ElecCons             = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
    std::string UserCode        = m_pDM_Interface->getString(ProductID.c_str(), DATA::UserCode);

    if ( status == DEF_GEN_STATES::On && m_pPD_HEAT_REF && m_pHeatStatusContainer )
    {
      if ( m_pPD_HEAT_REF->switchHeatStatusNo(HeatID,m_pHeatStatusContainer->getHeatStatus(ActPlant, DEF_GC_HEAT_STATUS::Melting), UserCode, false, m_lastError) )
      {
        if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, ActPlant) )
        {
          if ( m_pPD_HEAT_DATA->getTREATSTART_ACT(1) == CSMC_DBData::unspecDate )
          {
            CDateTime Now;
            m_pPD_HEAT_DATA->setTREATSTART_MOD(Now);

            if (m_pPD_HEAT_DATA->update())
            {
              m_pPD_HEAT_DATA->commit();

              cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DBWriteWarning(sMessage, "", "PD_HEAT_DATA", "CARCHIVER_SignalsAndMeasurementWrapper::::handlePower::HeatStart");
            }
            else
            {
              m_pPD_HEAT_DATA->rollback();
              cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DBWriteError(sMessage, "", "PD_HEAT_DATA", "CARCHIVER_SignalsAndMeasurementWrapper::handlePower");
            }
          }
        }
        else
        {
          std::string SearchKey = HeatID + ", " + TreatID + ", " + ActPlant;
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA");
        }
      }
    }

    RetValue = m_pPD_ELEC_SYSTEM->write(HeatID, TreatID, DEF_GC_ELEC_SYSTEM::FURNACEBRAKER, ActPlant, status,
                                        DurSinceHeatAnnounce, DurSinceHeatStart, ElecCons );
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
    m_pPD_ELEC_SYSTEM->rollback();
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


bool CARCHIVER_SignalsAndMeasurementWrapper::handlePower(CEventMessage& Event, long  status, double elecegy)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handlePower");
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

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);


    RetValue = m_pPD_ELEC_SYSTEM->write(HeatID, TreatID, DEF_GC_ELEC_SYSTEM::POWER,
                                        ActPlant, status, DurSinceHeatAnnounce, DurSinceHeatStart, elecegy );

    if(!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ELEC_SYSTEM", Scope.c_str());
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


bool CARCHIVER_SignalsAndMeasurementWrapper::handleTapChange(CEventMessage& Event, long TapChangStatus)
{
  bool RetValue = false;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo = m_pGC_Plant_Container->getPlantNo(PlantID);

  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleTapChange");
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
    << ", " << ProductID << ", " << HeatID
    << ", " << TreatID   << ", " << DataKey;

  try
  {
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    //like Tap change, but L1 maybe don't send tap change, so fill in cyclic
    setpDM_Interface(Sender,DM::PRODUCT);
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);
    

    setpDM_Interface(Sender,DM::PLANT);
    double ElecCons     = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::ElecCons);
    long VoltTapNo      = m_pDM_Interface->getLong  (DEF_PLANT::Furnace, DATA::VoltTapNo);
    long EltrdRegCurve  = m_pDM_Interface->getLong  (DEF_PLANT::Furnace, DATA::ElectrodRegCurve);
    long PowerStatus    = m_pDM_Interface->getLong  (DEF_PLANT::Furnace, DATA::PowerOn);

    if (TapChangStatus == DEF_GEN_STATES::Off)
    {
      RetValue = m_pPD_TAPCH_DATA->handleTapChange(HeatID, TreatID, ActPlant, VoltTapNo, EltrdRegCurve, ElecCons, TapChangStatus, true, cCBS_ODBC_DBError());
      
      if(!RetValue)
      {
        cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_TAPCH_DATA", Scope.c_str());
      }
    }

    RetValue = m_pPD_ELEC_TAPCH->handleTapChange(HeatID, TreatID, ActPlant, VoltTapNo, EltrdRegCurve, ElecCons, TapChangStatus, DurSinceHeatAnnounce, DurSinceHeatStart, true, cCBS_ODBC_DBError());

    if(!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"HEATID - TREATID", "PD_ELEC_TAPCH", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleDeslagging(CEventMessage& Event, long status)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleDeslagging");
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

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,Event.getDataKey());

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);

    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = DurSinceHeatStart;

    long ActionID = DEF_GC_ACTION_DEF::DeslaggingStart;
    if(status == DEF_GEN_STATES::Stop)
    {
      m_pPD_ACTION->m_Row.ACTIONSTATUS = 0;
      ActionID = DEF_GC_ACTION_DEF::DeslaggingEnd;
    }
    else
    {
      m_pPD_ACTION->m_Row.ACTIONSTATUS = 1;
    }

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, ActionID, true);
    //copy to HD table
    RetValue = RetValue && m_pHD_ACTION->copy(HeatID, TreatID, ActPlant,true,m_lastError);
    
    if (!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_ACTION", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleTappingLadleStirring(CEventMessage& Event, long status)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleTappingLadleStirring");
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

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,Event.getDataKey());

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);

    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = DurSinceHeatStart;

    long ActionID = DEF_GC_ACTION_DEF::LadleStirringStart;
    if(status == DEF_GEN_STATES::Stop)
    {
      m_pPD_ACTION->m_Row.ACTIONSTATUS = 0;
      ActionID = DEF_GC_ACTION_DEF::LadleStirringEnd;
    }
    else
      m_pPD_ACTION->m_Row.ACTIONSTATUS = 1;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, ActionID, true);
    //copy to HD table
    RetValue = RetValue && m_pHD_ACTION->copy(HeatID, TreatID, ActPlant,true,m_lastError);
    
    if (!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_ACTION", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleBottomStirringStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleBottomStirringStart");
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

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    m_pPD_ACTION->m_Row.ELECEGY                   = ECon;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::BottomStirringStart, true);
    //copy to HD table
    RetValue = RetValue && m_pHD_ACTION->copy(HeatID, TreatID, ActPlant,true,m_lastError);
    
    if (!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_ACTION", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleBottomStirringEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleBottomStirringEnd");
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

    //Calc duration since Heat Announcement and Heat Start
    double DurSinceHeatAnnounce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double DurSinceHeatStart    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }

    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceHeatAnnounce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceHeatStart;
    m_pPD_ACTION->m_Row.ELECEGY                   = ECon;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::BottomStirringEnd, true);
    //copy to HD table
    RetValue = RetValue && m_pHD_ACTION->copy(HeatID, TreatID, ActPlant,true,m_lastError);
    
    if (!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_ACTION", Scope.c_str());
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleTopLanceBlowingStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleTopLanceBlowingStart");
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

    //Calc duration since Heat Announcement and Heat Start
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double dDurSinceHeatAnnouce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart   = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }

    std::string ActionName;
    if ( m_pPD_ACTION->isActionDefined(DEF_GC_ACTION_DEF::BlowingStart))
    {
      ActionName = m_pPD_ACTION->getActionDefName(DEF_GC_ACTION_DEF::BlowingStart);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
    }

    m_pPD_ACTION->m_Row.ACTIONNAME = ActionName;

    m_pPD_ACTION->m_Row.ELECEGY = ECon;
    m_pPD_ACTION->m_Row.ACTIONSTATUS = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = dDurSinceHeatAnnouce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = dDurSinceHeatStart;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::BlowingStart, true);
    if (!RetValue)
    {
      std::stringstream Msg;
      Msg << "ERROR: insert action '" << DEF_GC_ACTION_DEF::BlowingStart << "' failed! ";
      Msg << __LINE__;
      log(Msg.str(),2);
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleCoolingWater(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string Sender    = Event.getSender();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);

  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleCoolingWater");
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

    seqGasData TotalMetAmountSeq = CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::TotalMetAmount));

    setpDM_Interface(Sender,DM::PLANT);
    seqCoolWaterData MeasCoolWaterData = CIntfData::ToCORBAType(m_pDM_Interface->getCoolWaterData(DEF_PLANT::Furnace,DATA::CoolingWaterData)); 

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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleOnBlowingStart(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleOnBlowingStart");
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

    //Calc duration since Heat Announcement and Heat Start
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double dDurSinceHeatAnnouce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart   = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }

    std::string ActionName;
    if ( m_pPD_ACTION->isActionDefined(DEF_GC_ACTION_DEF::BlowingStart))
    {
      ActionName = m_pPD_ACTION->getActionDefName(DEF_GC_ACTION_DEF::BlowingStart);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
    }

    m_pPD_ACTION->m_Row.ACTIONNAME = ActionName;

    m_pPD_ACTION->m_Row.ELECEGY = ECon;
    m_pPD_ACTION->m_Row.ACTIONSTATUS = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = dDurSinceHeatAnnouce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = dDurSinceHeatStart;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::BlowingStart, true);
    if (!RetValue)
    {
      std::stringstream Msg;
      Msg << "ERROR: insert action '" << DEF_GC_ACTION_DEF::BlowingStart << "' failed! ";
      Msg << __LINE__;
      log(Msg.str(),2);
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleOnBlowingEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleOnBlowingEnd");
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

    //Calc duration since Heat Announcement and Heat Start
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double dDurSinceHeatAnnouce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart   = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    sDate StartTime = m_pDM_Interface->getDate(ProductID.c_str(),DATA::BlowingOnTime); 
    sDate EndTime = m_pDM_Interface->getDate(ProductID.c_str(),DATA::BlowingOffTime);
    CDateTime BlowStartTime;
    CDateTime BlowEndTime;
    BlowStartTime.SetTime(StartTime);
    BlowEndTime.SetTime(EndTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }

    std::string ActionName;
    if ( m_pPD_ACTION->isActionDefined(DEF_GC_ACTION_DEF::BlowingEnd))
    {
      ActionName = m_pPD_ACTION->getActionDefName(DEF_GC_ACTION_DEF::BlowingEnd);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
    }

    m_pPD_ACTION->m_Row.ACTIONNAME = ActionName;

    m_pPD_ACTION->m_Row.ELECEGY = ECon;
    m_pPD_ACTION->m_Row.ACTIONSTATUS = 0;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = dDurSinceHeatAnnouce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = dDurSinceHeatStart;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, DEF_GC_ACTION_DEF::BlowingEnd, true);
    if (!RetValue)
    {
      std::stringstream Msg;
      Msg << "ERROR: insert action '" << DEF_GC_ACTION_DEF::BlowingEnd << "' failed! ";
      Msg << __LINE__;
      log(Msg.str(),2);
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleWasteGas(CEventMessage& Event)
{

  bool RetValue = false;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);
  long ActPlantNo       = m_pGC_Plant_Container->getPlantNo(PlantID);
  std::string Sender    = Event.getSender();

  setpDM_Interface(Sender,DM::PRODUCT);
  double DurSinceHeatAnnounce   = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double DurSinceHeatStart      = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  double MomentElec               = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons); 
  double MomentO2                 = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::MomentO2);
  seqGasData TotalMetAmountSeq  = CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::TotalMetAmount));


  setpDM_Interface(Sender,DM::PLANT);

  double            WasteGasTemp = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::WasteGasTemp);
  double            WasteGasFlow = m_pDM_Interface->getDouble(DEF_PLANT::Furnace, DATA::WasteGasFlow);
  seqWasteGas       WasteGasConc = CIntfData::ToCORBAType(m_pDM_Interface->getWasteGas(DEF_PLANT::Furnace, DATA::WasteGasConc));


  // Unified exception handling *******************************************************
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleWasteGas");
  std::stringstream ExceptionMsg;
  //***********************************************************************************

  try
  {   
    if (!checkDBConnection())
    {
      log("Error: " + Scope + " , (checkDBConnection()) == false", 1);
      return false;
    }

    if (0 == CIntfData::getLength(WasteGasConc))
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorHandlingCyclicData(sMessage, DEF_CYCLIC_MEASUREMENT_TYPES::WasteGas, Scope.c_str(), "seqWasteGas empty");
    }

    CDateTime now;
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setHEATID(HeatID);
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setTREATID(TreatID);
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setPLANT(ActPlant);

    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setREVTIME(now);
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setDURSINCEHEATANNOUNCE(DurSinceHeatAnnounce);
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setDURSINCESTARTOFHEAT(DurSinceHeatStart);

    // **********************************************
    // write process state information, if available
    // may be of type "MomentXX" or seqGasData
    if ( CIntfData::getLength(TotalMetAmountSeq) > 0 )
    {
      CGasDataHandler GasDataHandler(TotalMetAmountSeq);
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->setO2_MOMENT(GasDataHandler.getGasData(DEF_GAS::O2));
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->setAR_MOMENT(GasDataHandler.getGasData(DEF_GAS::Ar));
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->setN2_MOMENT(GasDataHandler.getGasData(DEF_GAS::N2));
    }

    if ( MomentElec != DEF::Inv_Double )
    {
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->setELEC_EGYTOT(MomentElec);
    }

    if ( MomentO2 != DEF::Inv_Double )
    {
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->setO2_MOMENT(MomentO2);
    }
    // **********************************************

    for (long i = 0; i < CIntfData::getLength(WasteGasConc); i++)
    {
      sWasteGas sWasteGasData;
      CIntfData::getAt(sWasteGasData,WasteGasConc,i);
      
      std::string GasType = sWasteGasData.WasteGasType;
      double GasConc = sWasteGasData.WasteGasConc;
      
      if (DEF_GAS::CO == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_CO(GasConc);
      else if (DEF_GAS::CO2 == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_CO2(GasConc);
      else if (DEF_GAS::O2 == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_O2(GasConc);
      else if (DEF_GAS::He == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_HE(GasConc);
      else if (DEF_GAS::Ar == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_AR(GasConc);
      else if(DEF_GAS::N2 == GasType )
        m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_N2(GasConc);
    }

    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_TEMP(WasteGasTemp);
    m_pPD_WASTEGAS_CYCL_MEAS_DATA->setWASTEGAS_FLOW(WasteGasFlow);

    if (m_pPD_WASTEGAS_CYCL_MEAS_DATA->insert())
    {
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->commit();
      RetValue = true;
    }
    else
    {
      m_pPD_WASTEGAS_CYCL_MEAS_DATA->rollback();
    }

    if(!RetValue)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage,"", "PD_WASTEGAS_CYCL_MEAS_DATA", Scope.c_str());
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


void CARCHIVER_SignalsAndMeasurementWrapper::deleteDBClasses()
{
  if(m_pPP_HEAT_PLANT)      { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if(m_pPP_HEAT)            { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if(m_pGC_PHASE)           { delete m_pGC_PHASE; m_pGC_PHASE = 0;}
  if(m_pPD_SAMPLE)          { delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0;}
  if(m_pPD_SAMPLE_ENTRY)    { delete m_pPD_SAMPLE_ENTRY; m_pPD_SAMPLE = 0;}
  if(m_pPD_ACTION)          { delete m_pPD_ACTION; m_pPD_ACTION = 0;}
  if(m_pHD_ACTION)          { delete m_pHD_ACTION; m_pHD_ACTION = 0;}
  if(m_pPD_LADLE)           { delete m_pPD_LADLE; m_pPD_LADLE = 0;}
  if(m_pPD_LADLE_LIFE_DATA) { delete m_pPD_LADLE_LIFE_DATA; m_pPD_LADLE_LIFE_DATA = 0;}
  if(m_pGC_Plant_Container) { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0;}
  if(m_pPD_ELEC_SYSTEM)     { delete m_pPD_ELEC_SYSTEM; m_pPD_ELEC_SYSTEM = 0;}
  if(m_pPD_ELEC_TAPCH)      { delete m_pPD_ELEC_TAPCH;  m_pPD_ELEC_TAPCH = 0;}
  if(m_pPD_TAPCH_DATA)      { delete m_pPD_TAPCH_DATA;m_pPD_TAPCH_DATA = 0;}
  if(m_pPD_COOLWATER)       { delete m_pPD_COOLWATER;  m_pPD_COOLWATER = 0;}
  if(m_pPD_PHASE_RES_ANL)   { delete m_pPD_PHASE_RES_ANL; m_pPD_PHASE_RES_ANL = 0;}
  if(m_pPD_PHASE_RES)       { delete m_pPD_PHASE_RES; m_pPD_PHASE_RES = 0;}
  if(m_pEquipmentData)      { delete m_pEquipmentData; m_pEquipmentData = 0;}
  if(m_pHeatStatusContainer){ delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}
  if(m_pPD_PRETREATDATA)    { delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0;}
  if(m_pPD_HEAT_REF)        { delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0;}
  if(m_pPD_PLANTSTATUS)     { delete m_pPD_PLANTSTATUS; m_pPD_PLANTSTATUS = 0;}
  if(m_pPD_HEAT_DATA)       { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0;  }
  if(m_pPP_ORDER)           { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if(m_pPD_SAMPLE_REF)      { delete m_pPD_SAMPLE_REF; m_pPD_SAMPLE_REF = 0;}
  if(m_pGC_SAMPLELOC)       { delete m_pGC_SAMPLELOC; m_pGC_SAMPLELOC = 0;}
  if(m_pHD_SAMPLE)          { delete m_pHD_SAMPLE; m_pHD_SAMPLE = 0;}
  if(m_pHD_SAMPLE_ENTRY)    { delete m_pHD_SAMPLE_ENTRY; m_pHD_SAMPLE_ENTRY = 0;}
  if(m_pPD_HEAT_DATA_LIQADD)        { delete m_pPD_HEAT_DATA_LIQADD; m_pPD_HEAT_DATA_LIQADD = 0;}
  if(m_pPD_RECIPE)                  { delete m_pPD_RECIPE; m_pPD_RECIPE = 0;}
  if(m_pPD_RECIPE_ENTRY)            { delete m_pPD_RECIPE_ENTRY; m_pPD_RECIPE_ENTRY = 0;}
  if(m_pGC_HEAT_STATUS)               { delete m_pGC_HEAT_STATUS; m_pGC_HEAT_STATUS = 0;}
  if(m_pPD_MAT_FEED_CYCL_MEAS_DATA) { delete m_pPD_MAT_FEED_CYCL_MEAS_DATA;m_pPD_MAT_FEED_CYCL_MEAS_DATA = 0;}
  if(m_pPD_WASTEGAS_CYCL_MEAS_DATA) { delete m_pPD_WASTEGAS_CYCL_MEAS_DATA; m_pPD_WASTEGAS_CYCL_MEAS_DATA = 0;  }
  

}

void CARCHIVER_SignalsAndMeasurementWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pPP_HEAT_PLANT              = new CPP_HEAT_PLANT(pConnection);
  m_pPP_HEAT                    = new CPP_HEAT(pConnection);
  m_pGC_PHASE                   = new CGC_PHASE(pConnection);
  m_pPD_SAMPLE                  = new CPD_SAMPLE(pConnection);
  m_pPD_SAMPLE_ENTRY            = new CPD_SAMPLE_ENTRY(pConnection);
  m_pPD_ACTION                  = new CPD_ACTION(pConnection);
  m_pHD_ACTION                  = new CHD_ACTION(pConnection);
  m_pPD_LADLE                   = new CPD_LADLE(pConnection);
  m_pPD_LADLE_LIFE_DATA         = new CPD_LADLE_LIFE_DATA(pConnection);
  m_pGC_Plant_Container         = new CGC_Plant_Container(pConnection);
  m_pPD_ELEC_SYSTEM             = new CPD_ELEC_SYSTEM(pConnection);
  m_pPD_ELEC_TAPCH              = new CPD_ELEC_TAPCH(pConnection);
  m_pPD_TAPCH_DATA              = new CPD_TAPCH_DATA(pConnection);
  m_pPD_COOLWATER               = new CPD_COOLWATER(pConnection);
  m_pPD_PHASE_RES_ANL           = new CPD_PHASE_RES_ANL(pConnection);
  m_pPD_PHASE_RES               = new CPD_PHASE_RES(pConnection);
  m_pEquipmentData              = new CEquipmentData(pConnection);
  m_pHeatStatusContainer        = new CHeatStatusContainer(pConnection);
  m_pPD_PRETREATDATA            = new CPD_PRETREATDATA(pConnection);
  m_pPD_HEAT_REF                = new CPD_HEAT_REF(pConnection);
  m_pPD_PLANTSTATUS             = new CPD_PLANTSTATUS(pConnection);	
  m_pPD_WASTEGAS_CYCL_MEAS_DATA = new CPD_WASTEGAS_CYCL_MEAS_DATA(pConnection);
  m_pPD_HEAT_DATA               = new CPD_HEAT_DATA(pConnection);
  m_pPP_ORDER                   = new CPP_ORDER(pConnection);
  m_pPD_SAMPLE_REF              = new CPD_SAMPLE_REF(pConnection);
  m_pGC_SAMPLELOC               = new CGC_SAMPLELOC(pConnection);
  m_pHD_SAMPLE                  = new CHD_SAMPLE(pConnection);
  m_pHD_SAMPLE_ENTRY            = new CHD_SAMPLE_ENTRY(pConnection);
  m_pPD_HEAT_DATA_LIQADD        = new CPD_HEAT_DATA_LIQADD(pConnection);
  m_pPD_RECIPE                  = new CPD_RECIPE(pConnection);
  m_pPD_RECIPE_ENTRY            = new CPD_RECIPE_ENTRY(pConnection);
  m_pGC_HEAT_STATUS               = new CGC_HEAT_STATUS(pConnection);
  m_pPD_MAT_FEED_CYCL_MEAS_DATA = new CPD_MAT_FEED_CYCL_MEAS_DATA(pConnection) ;
  
}

bool CARCHIVER_SignalsAndMeasurementWrapper::updatePretreatSampleRef(CEventMessage& Event, long SampleRef )
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::updatePretreatSampleRef");
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
      if ( m_pPD_SAMPLE_REF->select(SampleRef) )
      {
        m_pPD_PRETREATDATA->setSAMPLE_REF(SampleRef);

        RetValue = m_pPD_PRETREATDATA->update();

        if ( RetValue )
        {
          m_pPD_PRETREATDATA->commit();
        }
        else
        {
          m_pPD_PRETREATDATA->rollback();
        }
      }
    }
    else
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBReadError(sMessage,"", "PD_PRETREATDATA", "" );
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

bool CARCHIVER_SignalsAndMeasurementWrapper::updateHeatDataSampleRef(CEventMessage& Event, long SampleRef)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::updateHeatDataSampleRef");
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

    // now check if update of ladel data is possible
    if ( m_pPD_HEAT_DATA->select(HeatID,TreatID,ActPlant) )
    {
      if ( m_pPD_SAMPLE_REF->select(SampleRef) )
      {
        m_pPD_HEAT_DATA->setSAMPLE_REF(SampleRef);

        RetValue = m_pPD_HEAT_DATA->update();

        if ( RetValue  )
        {
          m_pPD_HEAT_DATA->commit();
        }
        else
        {
          m_pPD_HEAT_DATA->rollback();
        }
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

bool CARCHIVER_SignalsAndMeasurementWrapper::addSampleDetails(long SAMLPE_COUNTER, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO)
{
  return false;
}

// writing PC_ACTION depending on Actoin as DEF_GC_ACTION_DEF::DeslaggingStart or DEF_GC_ACTION_DEF::DeslaggingEnd
bool CARCHIVER_SignalsAndMeasurementWrapper::handleOnDeslagging(CEventMessage& Event, long Action )
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleOnDeslagging");
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

    // fill PD_ACTION
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double DurSinceA = 0.0;
    double DurSinceS = 0.0;
    double Elecons = 0.0;
    DurSinceA = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::DurSinceHeatAnnounce);
    DurSinceS = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::DurSinceHeatStart);
    Elecons   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);

    std::string ActionName =  m_pPD_ACTION->getActionDefName(Action);
    
    if (!ActionName.empty())
    {
      m_pPD_ACTION->m_Row.ACTIONNAME                = ActionName;
      m_pPD_ACTION->m_Row.ACTIONUNIT                = "min";
      m_pPD_ACTION->m_Row.ACTIONVALUE               = "0";
      m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
      m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = DurSinceA;
      m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = DurSinceS;
      m_pPD_ACTION->m_Row.N2_MOMENT                 = 0;
      m_pPD_ACTION->m_Row.AR_MOMENT                 = 0;
      m_pPD_ACTION->m_Row.O2_MOMENT                 = 0;
      m_pPD_ACTION->m_Row.ELECEGY                   = Elecons;

      RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, Action,true);

      //copy to HD table
      m_pHD_ACTION->copy(HeatID, TreatID, ActPlant,true,m_lastError);

      if (!RetValue)
      {
        log("ERROR: insert action 'Heat Deslagging' failed!",2);
      }
    }
    else
    {
      std::stringstream mes;
      mes << "WARNING: Action " << Action << "not defined in GC_ACTION_DEF!";
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

bool CARCHIVER_SignalsAndMeasurementWrapper::IncreaseLadleLifeDate(long LadleNo,std::string LadleType,bool Commit)
{
  bool RetVal = true;
  //Increase Ladle Life data.
  m_pPD_LADLE_LIFE_DATA->incrLife(LadleNo, LadleType, CSMC_DBData::unspecString, Commit);
  {
    if(Commit)
    {
      m_pPD_LADLE_LIFE_DATA->commit();
    }
  }
  return RetVal;
}

bool CARCHIVER_SignalsAndMeasurementWrapper::SetAction(CEventMessage& Event, long ActionNo, const std::string& ActionValue, long ActionStatus, const std::string& ActionUnit, double ElecEgy, bool Commit)
{
  bool Retval = true;

  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string DataKey   = Event.getDataKey();
  std::string PlantID   = Event.getPlantID();
  std::string ActPlant  = m_pGC_Plant_Container->getPlant(PlantID);


  //Update PD_Action
  std::string ActionName;
  if (m_pPD_ACTION->isActionDefined(ActionNo))
  {
    ActionName = m_pPD_ACTION->getActionDefName(ActionNo);
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    logInterfaceDataList(m_pDM_Interface,ProductID);

    double dDurHeatAnnouce    = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);
    seqGasData SeqGasDataTot;
    sGasData GasData;

    SeqGasDataTot = CIntfData::ToCORBAType(m_pDM_Interface->getGasData(ProductID.c_str(), DATA::TotalMetAmount));

    setpDM_Interface(Event.getSender(),DM::EVENT);
    logInterfaceDataList(m_pDM_Interface,DataKey);
    std::string ChuteID = CIntfData::ToStdString(m_pDM_Interface->getString(DataKey.c_str(), DATA::ScrapChuteId));

    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    if ( CIntfData::getLength(SeqGasDataTot) > 0 )
    {
      CGasDataHandler GasDataHandler(SeqGasDataTot);
      m_pPD_ACTION->m_Row.O2_MOMENT = GasDataHandler.getGasData(DEF_GAS::O2);
      m_pPD_ACTION->m_Row.AR_MOMENT = GasDataHandler.getGasData(DEF_GAS::Ar);
      m_pPD_ACTION->m_Row.N2_MOMENT = GasDataHandler.getGasData(DEF_GAS::N2);
    }

    if(CSMC_DBData::unspecString != ActionUnit)
    {
      m_pPD_ACTION->m_Row.ACTIONUNIT = ActionUnit;
    }   
    if((!ActionValue.empty()) && (ActionValue != CSMC_DBData::unspecString))
    {
      m_pPD_ACTION->m_Row.ACTIONVALUE = ActionValue;
    }    
    m_pPD_ACTION->m_Row.ACTIONSTATUS = ActionStatus;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT = dDurHeatAnnouce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT = dDurSinceHeatStart;
    if(ElecEgy != DEF::Inv_Double)
    {
      m_pPD_ACTION->m_Row.ELECEGY = ElecEgy;
    }

    if (!m_pPD_ACTION->write(HeatID, TreatID, ActPlant, ActionNo,Commit))
    {
      Retval = false;
      std::stringstream Msg;
      Msg << "ERROR: insert action '" << ActionName << "' failed! ";
      Msg << __LINE__;
      log(Msg.str(),1);
    }

  }
  else
  {
    std::stringstream mes;
    mes << "WARNING: Action " << ActionName << "not defined in GC_ACTION_DEF!";
    log(mes.str(),2);
  }
  return Retval;
};

bool CARCHIVER_SignalsAndMeasurementWrapper::handleTopLanceBlowingEnd(CEventMessage& Event, seqGasData& SeqGasData, double ECon)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleTopLanceBlowingEnd");
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

    //Calc duration since Heat Announcement and Heat Start
    double dDurSinceHeatAnnouce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart   = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    sDate StartTime = m_pDM_Interface->getDate(ProductID.c_str(),DATA::BlowingOnTime); 
    sDate EndTime = m_pDM_Interface->getDate(ProductID.c_str(),DATA::BlowingOffTime);
    CDateTime BlowStartTime;
    CDateTime BlowEndTime;
    BlowStartTime.SetTime(StartTime);
    BlowEndTime.SetTime(EndTime);

    //Write the Actions
    long Action = DEF_GC_ACTION_DEF::BlowingEnd;
    long ActionStatus = 0;

    if(!SetAction(Event,Action,CSMC_DBData::unspecString,ActionStatus,CSMC_DBData::unspecString,ECon,true))
    {
      std::stringstream mes;
      mes << "ERROR: insert action '" << Action << "' failed!";
      log(mes.str(),2);       
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

bool CARCHIVER_SignalsAndMeasurementWrapper::handleMechanicalSystem(CEventMessage& Event, seqGasData& SeqGasData, double ElecCons, long ActionNo)
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
  std::string Scope("CARCHIVER_SignalsAndMeasurementWrapper::handleMechanicalSystem");
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

    //Calc duration since Heat Announcement and Heat Start
    setpDM_Interface(Event.getSender(),DM::PRODUCT);
    double dDurSinceHeatAnnouce = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatAnnounceTime);
    double dDurSinceHeatStart   = getDurationSince(m_pDM_Interface, ProductID, DATA::HeatStartTime);

    long seqLength = 0;
    seqLength = CIntfData::getLength(SeqGasData);
    sGasData sData;
    m_pPD_ACTION->m_Row.AR_MOMENT = 0;
    m_pPD_ACTION->m_Row.O2_MOMENT = 0;
    m_pPD_ACTION->m_Row.N2_MOMENT = 0;

    for (int i = 0 ; i < seqLength ; ++i)
    {
      CIntfData::getAt(sData,&SeqGasData,i);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::O2)
        m_pPD_ACTION->m_Row.O2_MOMENT = sData.GasValue;
      if (strGasType == DEF_GAS::Ar)
        m_pPD_ACTION->m_Row.AR_MOMENT = sData.GasValue;
      if (strGasType== DEF_GAS::N2)
        m_pPD_ACTION->m_Row.N2_MOMENT = sData.GasValue;
    }

    std::string ActionName;
    if ( m_pPD_ACTION->isActionDefined(ActionNo))
    {
      ActionName = m_pPD_ACTION->getActionDefName(ActionNo);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,"ACTIONNO","GC_ACTION_DEF");
    }

    m_pPD_ACTION->m_Row.ACTIONNAME                = ActionName;
    m_pPD_ACTION->m_Row.ELECEGY                   = ElecCons;
    m_pPD_ACTION->m_Row.ACTIONSTATUS              = 1;
    m_pPD_ACTION->m_Row.DURSINCEHEATANNOUNCEMENT  = dDurSinceHeatAnnouce;
    m_pPD_ACTION->m_Row.DURSINCESTARTOFHEAT       = dDurSinceHeatStart;

    RetValue = m_pPD_ACTION->write(HeatID, TreatID, ActPlant, ActionNo, true);
    if (!RetValue)
    {
      std::stringstream Msg;
      Msg << "ERROR: insert action '" << DEF_GC_ACTION_DEF::BlowingStart << "' failed! ";
      Msg << __LINE__;
      log(Msg.str(),2);
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

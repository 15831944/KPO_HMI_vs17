// Copyright (C) 2013 SMS Demag AG

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

#include "CHDH_HM_DATA.h"
#include "CHDH_ACTION.h"
#include "CHDH_HM_DATA_PHASE.h"
#include "CHDH_CYCL_MEAS_DATA.h"

#include "CARCHIVER_HMDTreatmentWrapper.h"



CARCHIVER_HMDTreatmentWrapper::CARCHIVER_HMDTreatmentWrapper()
{
}

CARCHIVER_HMDTreatmentWrapper::~CARCHIVER_HMDTreatmentWrapper()
{
}

void CARCHIVER_HMDTreatmentWrapper::deleteDBClasses()
{
  CARCHIVER_TreatmentWrapper::deleteDBClasses();
}

void CARCHIVER_HMDTreatmentWrapper::initDBClasses()
{
  CARCHIVER_TreatmentWrapper::initDBClasses();
}

bool CARCHIVER_HMDTreatmentWrapper::doOnHeatDeparture(CEventMessage& Event)
{
  bool RetValue = true;

  // Copying of PD tables into HD tables should be done by archiver HMD,
  // currently it is still activated and done in Tracking_HMD and the Archiver_HMD call is deactivated.
  // But when Archiver_HMD has to do it, then a TSM ruleset (TSM_HMD_RuleSet.asc) has to be provided.
  // Reason: The ReportServer has to be triggered after heat departure "RDY" event, and not earlier
  // because only then the HD tables are filled with current data copied from PD tables.
  //log("++++++ CARCHIVER_HMDTreatmentWrapper::doOnHeatDeparture",3);

  //// First copy the parent table with take care of any error and with no explicit commit
  //RetValue = copyHDH_HMData(Event, false);

  //// now copy the PDH tables with only a few records per heat+treat+plant and also without any explicit commit till the last one
  //// General tables
  //// ToDo: Clarification which tables have to be copied

  //// HMD tables
  //// Not copied, because already done at heat announcement or during treatment:
  //// HDH_GRADE, HDH_GRADE_ANL, HDH_HM_DATA_PRODPRAC, HDH_PARAM, HDH_PARAM_MATRIX
  //// HDH_PP_BASE_VAL, HDH_PP_BASE_VAL_STEP, HDH_PP_BLOWING, HDH_PP_INJECTION, HDH_PP_TEMP_CORR
  ////
  //// ToDo: One unclear table PDH_LANCE_DATA, which has no HD table counterpart
  //RetValue = RetValue && copyHDH_Action(Event, false);
  //RetValue = RetValue && copyHDH_HMPhaseData(Event, false);

  //if ( RetValue )
  //{
  //  // now commit the current transaction, which contains all the upper copy tasks
  //  getStdConnection()->commit();

  //  // now copy the PD tables with an expected huge amount of rows per hm_id+treat+plant
  //  // with always explicit commit and without taken care of returned value
  //  // General tables: ToDo: Currently no tables found, okay?

  //  // HMD tables
  //  copyHDH_CyclMeasData(Event, true);
  //  // ToDo: Following model tables have to be copied
  //  //HDH_ACT_EVENT_RES
  //  //HDH_HM_PHASE_RES
  //  //HDH_HM_RES
  //  //copyHDH_ModelData(Event, true);
  //}
  //else
  //{
  //  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_DBWriteError(sMessage, "", "", "CARCHIVER_HMDTreatmentWrapper::doOnHeatDeparture");

  //  getStdConnection()->rollback();
  //}

  return RetValue;
}

bool CARCHIVER_HMDTreatmentWrapper::copyHDH_HMData(CEventMessage& Event, bool Commit)
{
  log("++++++ CARCHIVER_HMDTreatmentWrapper::copyHDH_HMData",3);

  bool RetValue = false;

  //cCBS_StdConnection *pConnection = getStdConnection();
  //if (pConnection)
  //{
  //  std::string HeatID  = Event.getHeatID();
  //  std::string TreatID = Event.getTreatID();
  //  std::string PlantID = Event.getPlantID();
  //  std::string Plant   = m_pGC_Plant_Container->getPlant(PlantID);

  //  CHDH_HM_DATA HDH_HM_DATA(pConnection);

  //  RetValue = HDH_HM_DATA.copy(HeatID, TreatID, Plant, Commit, m_lastError);
  //  if ( !RetValue )
  //  {
  //    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //    pEventLog->EL_DBWriteError(sMessage, "", "HDH_HM_DATA", m_lastError.m_MessageText.c_str());
  //  }
  //}
  return RetValue;
}//bool CARCHIVER_HMDTreatmentWrapper::copyHDH_HMData(CEventMessage& Event, bool Commit)

bool CARCHIVER_HMDTreatmentWrapper::copyHDH_Action(CEventMessage& Event, bool Commit)
{
  log("++++++ CARCHIVER_HMDTreatmentWrapper::copyHDH_Action",3);

  bool RetValue = false;

  //cCBS_StdConnection *pConnection = getStdConnection();
  //if (pConnection)
  //{
  //  std::string HeatID  = Event.getHeatID();
  //  std::string TreatID = Event.getTreatID();
  //  std::string PlantID = Event.getPlantID();
  //  std::string Plant   = m_pGC_Plant_Container->getPlant(PlantID);

  //  CHDH_ACTION HDH_ACTION(pConnection);

  //  RetValue = HDH_ACTION.copy(HeatID, TreatID, Plant, Commit, m_lastError);
  //  if ( !RetValue )
  //  {
  //    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //    pEventLog->EL_DBWriteError(sMessage, "", "HDH_ACTION", m_lastError.m_MessageText.c_str());
  //  }
  //}
  return RetValue;
}//bool CARCHIVER_HMDTreatmentWrapper::copyHDH_Action(CEventMessage& Event, bool Commit)

bool CARCHIVER_HMDTreatmentWrapper::copyHDH_HMPhaseData(CEventMessage& Event, bool Commit)
{
  log("++++++ CARCHIVER_HMDTreatmentWrapper::copyHDH_HMPhaseData",3);

  bool RetValue = false;

 /* cCBS_StdConnection *pConnection = getStdConnection();
  if (pConnection)
  {
    std::string HeatID  = Event.getHeatID();
    std::string TreatID = Event.getTreatID();
    std::string PlantID = Event.getPlantID();
    std::string Plant   = m_pGC_Plant_Container->getPlant(PlantID);

    CHDH_HM_DATA_PHASE HDH_HM_DATA_PHASE(pConnection);

    RetValue = HDH_HM_DATA_PHASE.copy(HeatID, TreatID, Plant, Commit, m_lastError);
    if ( !RetValue )
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage, "", "HDH_HM_DATA_PHASE", m_lastError.m_MessageText.c_str());
    }
  }*/
  return RetValue;
}//bool CARCHIVER_HMDTreatmentWrapper::copyHDH_HMPhaseData(CEventMessage& Event, bool Commit)

bool CARCHIVER_HMDTreatmentWrapper::copyHDH_CyclMeasData(CEventMessage& Event, bool Commit)
{
  log("++++++ CARCHIVER_HMDTreatmentWrapper::copyHDH_CyclMeasData",3);

  bool RetValue = false;

  cCBS_StdConnection *pConnection = getStdConnection();
  if (pConnection)
  {
    std::string HeatID  = Event.getHeatID();
    std::string TreatID = Event.getTreatID();
    std::string PlantID = Event.getPlantID();
    std::string Plant   = m_pGC_Plant_Container->getPlant(PlantID);

    CHDH_CYCL_MEAS_DATA HDH_CYCL_MEAS_DATA(pConnection);

    RetValue = HDH_CYCL_MEAS_DATA.copy(HeatID, TreatID, Plant, Commit, m_lastError);
    if ( !RetValue )
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteError(sMessage, "", "HDH_CYCL_MEAS_DATA", m_lastError.m_MessageText.c_str());
    }
  }
  return RetValue;
}//bool CARCHIVER_HMDTreatmentWrapper::copyHDH_CyclMeasData(CEventMessage& Event, bool Commit)

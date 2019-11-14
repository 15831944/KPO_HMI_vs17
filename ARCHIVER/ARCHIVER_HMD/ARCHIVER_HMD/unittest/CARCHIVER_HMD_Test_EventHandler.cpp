
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_EventHandler.h"
#include "CARCHIVER_HMD_Test_Task.h"


#include "CGCF_PHASE.h"
#include "CGC_PHASE.h"
#include "CGC_Plant.h"
#include "DEF_GC_ACTION.h"
#include "CPD_COMP_DATA.h"
#include "CPDF_HEAT_PHASE_DATA.h"
#include "CPDF_HEAT_DATA.h"
#include "CPDB_HEAT_DATA.h"
#include "CPDE_HEAT_DATA.h"
#include "CPDC_BASKET_HEAT.h"
#include "CPDC_BASKET_ENTRY_HEAT.h"
#include "CPD_ANL.h"
#include "CPD_ANL_ENTRY.h"
#include "CPD_RECIPE.h"
#include "CPD_REPORT.h"
#include "CPD_PRETREAT_ANL.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_ACTION.h"
#include "CPD_HEATDATA.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CPP_ORDER.h"
#include "CPD_LADLE.h"
#include "CPD_HEATDATA_LIQADD_ANL.h"
#include "CPD_LADLE_LIFE_DATA.h"


CARCHIVER_HMD_Test_EventHandler::~CARCHIVER_HMD_Test_EventHandler()
{
  if (m_pARCHIVER_MaterialHandling) { delete m_pARCHIVER_MaterialHandling; m_pARCHIVER_MaterialHandling = 0;}
  if (m_pARCHIVER_TreatmentHandling) { delete m_pARCHIVER_TreatmentHandling; m_pARCHIVER_TreatmentHandling = 0;}
  if (m_pARCHIVER_AnalysisHandling) { delete m_pARCHIVER_AnalysisHandling; m_pARCHIVER_AnalysisHandling = 0;}
  if (m_pARCHIVER_PhaseReportingHandling) { delete m_pARCHIVER_PhaseReportingHandling; m_pARCHIVER_PhaseReportingHandling = 0;}
  if (m_pARCHIVER_ComputerModesHandling) { delete m_pARCHIVER_ComputerModesHandling; m_pARCHIVER_ComputerModesHandling = 0;}
  if (m_pARCHIVER_SignalsAndMeasurementsHandling) { delete m_pARCHIVER_SignalsAndMeasurementsHandling; m_pARCHIVER_SignalsAndMeasurementsHandling = 0;}
  if (m_pARCHIVER_ModelResultHandling){delete m_pARCHIVER_ModelResultHandling;m_pARCHIVER_ModelResultHandling = 0;}
}

CARCHIVER_HMD_Test_EventHandler::CARCHIVER_HMD_Test_EventHandler(CARCHIVER_Task *Task)
: CARCHIVER_EventHandler(Task)
, m_pARCHIVER_Task(Task)
{
  m_pARCHIVER_MaterialHandling = new CARCHIVER_HMD_Test_MaterialHandling(Task);
  m_pARCHIVER_MaterialHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_ModelResultHandling = new CARCHIVER_HMD_Test_ModelResultHandling(Task);
  m_pARCHIVER_ModelResultHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_TreatmentHandling = new CARCHIVER_HMD_Test_TreatmentHandling(Task);
  m_pARCHIVER_TreatmentHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_AnalysisHandling = new CARCHIVER_HMD_Test_AnalysisHandling(Task);
  m_pARCHIVER_AnalysisHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_PhaseReportingHandling = new CARCHIVER_HMD_Test_PhaseReportingHandling(Task);
  m_pARCHIVER_PhaseReportingHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_ComputerModesHandling = new CARCHIVER_HMD_Test_ComputerModesHandling(Task);
  m_pARCHIVER_ComputerModesHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  m_pARCHIVER_SignalsAndMeasurementsHandling = new CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling(Task);
  m_pARCHIVER_SignalsAndMeasurementsHandling->setpArchiverTask(CARCHIVER_HMD_Test_Task::getInstance());
  setpTask(Task);
}

bool CARCHIVER_HMD_Test_EventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = false;
  try
	{
	  // The default implementation for this operation is that chek the receiver, then invoke the hook operation
	  // doEventHandlingHook
	  CEventMessage Event(Event);

    CSMC_RuntimeController Controller("CARCHIVER_EventHandler::handleEvent");

    std::string Message   = Event.getMessage();

    log("");
    log("----------------------------------- New Event -----------------------------------");
    log("Handling Event : " + Event.getContent(),1);

    RetValue = handleEvent(Event);

	  if (RetValue)
	  {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_EventHandled(sMessage,Event.getSender().c_str(),Event.getReceiver().c_str(),Message.c_str());
    }
    log("");
    log("----------------------------------------------------------------------------");
	}
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Handling Event",
	    "CDM_EventHandler::handleEvent","HANDLE_EVENT");
	}
	return RetValue;
}

bool CARCHIVER_HMD_Test_EventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = false;
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();
  cout << "-------START------------" << endl;
  if (checkReceiver(Event))
  {
    std::string ActMessage = Event.getMessage();
    std::string MsgRDY(".RDY");
    if ( (ActMessage == (HMD_EvMsg::evHMDHeatAnnouncement + MsgRDY))
      || (ActMessage == (HMD_EvMsg::evHMDHeatAnnouncementOffline + MsgRDY)) )
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleHMDHeatAnnouncementRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDHeatStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleHMDHeatStartRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDHeatEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleHMDHeatEndRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDSetComputerModeOn + MsgRDY))
    {
      RetValue = m_pARCHIVER_ComputerModesHandling->handleHMDSetComputerModeRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDSetComputerModeOff + MsgRDY))
    {
      RetValue = m_pARCHIVER_ComputerModesHandling->handleHMDSetComputerModeRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDHeatCancellation+ MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleHMDHeatCancellationRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDHeatDeparture + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleHMDHeatDepartureRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDPowderBlowingStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleHMDPowderBlowingRDY(Event, true);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDPowderBlowingEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleHMDPowderBlowingRDY(Event, false);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDTempMeasurement + MsgRDY))        
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleHMDTempMeasurementRDY(Event);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDHotMetalSampleTaken + MsgRDY))         
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleHMDHotMetalSampleTakenRDY(Event, true);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDSlagSampleTaken + MsgRDY))
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleHMDHotMetalSampleTakenRDY(Event, false);
    }
    else if (ActMessage == (HMD_EvMsg::evHMDCyclicMeasurement + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleHMDCyclicMeasurementRDY(Event);
    }
    else if (ActMessage ==  HMD_EvMsg::evHMDModelResult + MsgRDY ||
              ActMessage ==  HMD_EvMsg::evHMDModelResultOffline + MsgRDY )
    {
      RetValue = m_pARCHIVER_ModelResultHandling->handleHMDModelResultRDY(Event);
    }
    else if (ActMessage == HMD_EvMsg::evHMDPhasePreparation                + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseMonoInjectionLimeStart     + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideStart  + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseMonoInjectionContinued     + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseMonoInjectionLimeEnd       + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseMonoInjectionCarbideEnd    + MsgRDY||
            ActMessage == HMD_EvMsg::evHMDPhaseDeslagging + MsgRDY)
    {
      RetValue = m_pARCHIVER_PhaseReportingHandling->handleHMDPhaseReportRDY(Event);
    }

  }//if (checkReceiver(Event))
	return RetValue;
}


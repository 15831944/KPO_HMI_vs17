#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_EventHandler.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_EventHandler::~CARCHIVER_LF_Test_EventHandler()
{
  if (m_pARCHIVER_MaterialHandling) { delete m_pARCHIVER_MaterialHandling; m_pARCHIVER_MaterialHandling = 0;}
  if (m_pARCHIVER_TreatmentHandling) { delete m_pARCHIVER_TreatmentHandling; m_pARCHIVER_TreatmentHandling = 0;}
  if (m_pARCHIVER_DelayHandling) { delete m_pARCHIVER_DelayHandling; m_pARCHIVER_DelayHandling = 0;}
  if (m_pARCHIVER_ModelResultHandling) { delete m_pARCHIVER_ModelResultHandling; m_pARCHIVER_ModelResultHandling = 0;}
  if (m_pARCHIVER_AnalysisHandling) { delete m_pARCHIVER_AnalysisHandling; m_pARCHIVER_AnalysisHandling = 0;}
  if (m_pARCHIVER_ComputerModesHandling) { delete m_pARCHIVER_ComputerModesHandling; m_pARCHIVER_ComputerModesHandling = 0;}
  if (m_pARCHIVER_SignalsAndMeasurementsHandling) { delete m_pARCHIVER_SignalsAndMeasurementsHandling; m_pARCHIVER_SignalsAndMeasurementsHandling = 0;}
}

CARCHIVER_LF_Test_EventHandler::CARCHIVER_LF_Test_EventHandler(CARCHIVER_Task *Task): CARCHIVER_EventHandler(Task), m_pARCHIVER_Task(Task)
{
  m_pARCHIVER_MaterialHandling = new CARCHIVER_LF_Test_MaterialHandling(Task);
  m_pARCHIVER_MaterialHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
  m_pARCHIVER_ModelResultHandling = new CARCHIVER_LF_Test_ModelResultHandling(Task);
  m_pARCHIVER_ModelResultHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
  m_pARCHIVER_TreatmentHandling = new CARCHIVER_LF_Test_TreatmentHandling(Task);
  m_pARCHIVER_TreatmentHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
 
  m_pARCHIVER_DelayHandling = new CARCHIVER_LF_Test_DelayHandling(Task);
  m_pARCHIVER_DelayHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());

  m_pARCHIVER_AnalysisHandling = new CARCHIVER_LF_Test_AnalysisHandling(Task);
  m_pARCHIVER_AnalysisHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
  m_pARCHIVER_ComputerModesHandling = new CARCHIVER_LF_Test_ComputerModesHandling(Task);
  m_pARCHIVER_ComputerModesHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
  m_pARCHIVER_SignalsAndMeasurementsHandling = new CARCHIVER_LF_Test_SignalsAndMeasurementsHandling(Task);
  m_pARCHIVER_SignalsAndMeasurementsHandling->setpArchiverTask(CARCHIVER_LF_Test_Task::getInstance());
  setpTask(Task);
}

bool CARCHIVER_LF_Test_EventHandler::handleEvent(const FRIESEvent& Event)
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

bool CARCHIVER_LF_Test_EventHandler::handleEvent(CEventMessage& Event)
{
  bool RetValue = false;
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cout << "-------START------------" << endl;
  if (checkReceiver(Event))
  {
    std::string ActMessage = Event.getMessage();
    std::string MsgRDY(".RDY");
    
    
    //AnalysisHandling
    if (ActMessage == (LF_EvMsg::evLFSteelAnalysisReceived + MsgRDY))
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleLFAnalysisReceivedRDY(Event, true);
    }
    else if (ActMessage == (LF_EvMsg::evLFSlagAnalysisReceived + MsgRDY))
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleLFAnalysisReceivedRDY(Event, false);
    }
    else if (ActMessage == (LF_EvMsg::evLFSteelSampleTaken + MsgRDY))
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleLFSampleTakenRDY(Event, true);
    }
    else if (ActMessage == (LF_EvMsg::evLFSlagSampleTaken + MsgRDY))
    {
      RetValue = m_pARCHIVER_AnalysisHandling->handleLFSampleTakenRDY(Event, false);
    }

    
    //ComputerModeshandling
    else if (ActMessage == (LF_EvMsg::evLFSetComputerMode + MsgRDY))
    {
      RetValue = m_pARCHIVER_ComputerModesHandling->handleLFSetComputerModeRDY(Event);
    }

    //TreatmentHandling
    else if ( (ActMessage == (LF_EvMsg::evLFHeatAnnouncement + MsgRDY))|| (ActMessage == (LF_EvMsg::evLFHeatAnnouncementOffline + MsgRDY)) )
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFHeatAnnouncementRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFHeatStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFHeatStartRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFHeatEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFHeatEndRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFHeatCancellation + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFHeatCancelRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFHeatDeparture + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFHeatDepartureRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFUpdateAimDepartureTime + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFUpdateAimDepartureTimeRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFUpdateAimTemperature + MsgRDY))
    {
      RetValue = m_pARCHIVER_TreatmentHandling->handleLFUpdateAimTemperatureRDY(Event);
    }    

    //MaterialHandling
    else if (ActMessage == (LF_EvMsg::evLFMaterialHandlingReport + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleLFMaterialHandlingReportRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFLiqMatHandlReport + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleLFLiqMatHandlingReportRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFWireFeedingEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleLFMaterialHandlingReportRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFWireFeedingStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_MaterialHandling->handleLFMaterialHandlingReportRDY(Event);
    }
    
    //SignalsAndMeasurementsHandling
    else if (ActMessage == (LF_EvMsg::evLFCyclicMeasurement + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFCyclicMeasurementRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFBottomStirringStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFStirringStartEndRDY(Event, 1);
    }
    else if (ActMessage == (LF_EvMsg::evLFBottomStirringEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFStirringStartEndRDY(Event, 2);
    }
    
    else if (ActMessage == (LF_EvMsg::evLFBottomStirringByPassOn + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFStirringBypassOnOffRDY(Event, 1);
    }
    else if (ActMessage == (LF_EvMsg::evLFBottomStirringByPassOff + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFStirringBypassOnOffRDY(Event, 2);
    }
    else if (ActMessage == (LF_EvMsg::evLFEmergencyLanceStirringStart  + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFEmergencyLanceStirringRDY(Event,true);
    }
    else if (ActMessage == (LF_EvMsg::evLFEmergencyLanceStirringEnd + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFEmergencyLanceStirringRDY(Event,false);
    }
    else if (ActMessage == (LF_EvMsg::evLFTapChangeStart + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFTapChangeRDY(Event,DEF_GEN_STATES::On);
    }
    else if (ActMessage == (LF_EvMsg::evLFTapChangeFinished + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFTapChangeRDY(Event,DEF_GEN_STATES::Off);
    }
    else if (ActMessage == (LF_EvMsg::evLFTempMeasurement + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFTempMeasurementRDY(Event);
    }
    else if (ActMessage == (LF_EvMsg::evLFCeloxMeasurement + MsgRDY))
    {
      RetValue = m_pARCHIVER_SignalsAndMeasurementsHandling->handleLFTempMeasurementRDY(Event);
    }


    //ModelResultHandling
    //else if (ActMessage == (LF_EvMsg::evLFModelResult + MsgRDY))
    //{
    //  RetValue = m_pARCHIVER_ModelResultHandling->handleLFModelResultRDY(Event);
    //}



  }//if (checkReceiver(Event))
	return RetValue;
}

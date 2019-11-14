// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EAFTask.h"
#include "CDM_EAFModelResultEventHandler.h"


CDM_EAFModelResultEventHandler::CDM_EAFModelResultEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_EAFModelResultEventHandler::~CDM_EAFModelResultEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

bool CDM_EAFModelResultEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(EAFModelResultCode);
	HANDLE_EVENT(EAFModelResultActualSetpoints);
	HANDLE_EVENT(EAFModelResultRecipeSetpoints);
	HANDLE_EVENT(EAFHeatAnnounceStatus);
	return false;
}

bool CDM_EAFModelResultEventHandler::doEAFModelResultActualSetpoints(CEventMessage& Event)
{
	doEAFModelResult(Event);
	return true;
}

bool CDM_EAFModelResultEventHandler::doEAFModelResultCode( CEventMessage& Event)
{
	doEAFModelResult(Event);
	return true;
}

bool CDM_EAFModelResultEventHandler::doEAFModelResultRecipeSetpoints( CEventMessage& Event)
{
	doEAFModelResult(Event);
	return true;
}

bool CDM_EAFModelResultEventHandler::doEAFModelResult(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      // copy data from DH to DM_DataInterface
      if ( copyModelEventData(Event) )
      {
        if ( m_pDMTask->getpPlantManager()  && 
             m_pDMTask->getpProductManager()   ) 
        {
          m_pDMTask->getpPlantManager()->changePlantInformation(Event);

          m_pDMTask->getpProductManager()->changeSetpoints(Event);

          // check errors end set comp modes
          m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event);

          // do not send evGenSystemStatusReport when ActualSetPoints are received
          CEventMessage ResetEvent(Event);
          ResetEvent.setMessage(GEN_EvMsg::evGenSystemStatusReport);
          resetCyclicTriggerCall(ResetEvent);

          // send event to respective destinations
          dispatchEvent(Event);

          // sendAdditionalEvents called at "afterDispatchEvent"
        
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFModelResultEventHandler::doEAFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFModelResultEventHandler::doEAFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFModelResultEventHandler::doEAFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_EAFModelResultEventHandler::doEAFHeatAnnounceStatus(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    // try to update Event with assigend data (ProductID...)
    if ( checkEventAssignment(Event) )
    {
      // copy data from DH to DM_DataInterface
      if ( copyModelEventData(Event) )
      {
	      std::string HeatID = Event.getHeatID();
	
 	      // change respective data ata manager classes 
	      if (m_pDMTask->getpPlantManager() )
	      {
          m_pDMTask->getpPlantManager()->changePlantInformation(Event);
        }

        if (m_pDMTask->getpProductManager()) 
        {
          m_pDMTask->getpProductManager()->changeProductInformation(Event);
        }

        // send event to respective destinations
        dispatchEvent(Event);

      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EAFModelResultEventHandler::doEAFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EAFModelResultEventHandler::doEAFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EAFModelResultEventHandler::doEAFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}


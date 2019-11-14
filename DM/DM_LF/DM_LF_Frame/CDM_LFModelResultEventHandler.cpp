// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_LFTask.h"
#include "CDM_LFModelResultEventHandler.h"
#include "CStatusHandler.h"

CDM_LFModelResultEventHandler::CDM_LFModelResultEventHandler()
{
}

CDM_LFModelResultEventHandler::~CDM_LFModelResultEventHandler()
{
}

bool CDM_LFModelResultEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(LFModelResultCode);
	HANDLE_EVENT(LFModelResultActualSetpoints);
	HANDLE_EVENT(LFModelResultRecipeSetpoints);
	HANDLE_EVENT(LFHeatAnnounceStatus);

  // Offline events
	HANDLE_EVENT(LFModelResultActualSetpointsOffline);
	HANDLE_EVENT(LFModelResultCodeOffline);
	HANDLE_EVENT(LFModelResultRecipeSetpointsOffline);
	HANDLE_EVENT(LFHeatAnnounceStatusOffline);

	return false;
}

bool CDM_LFModelResultEventHandler::doLFModelResultActualSetpoints(CEventMessage& Event)
{
	doLFModelResult(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultCode( CEventMessage& Event)
{
	doLFModelResult(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultRecipeSetpoints( CEventMessage& Event)
{
	doLFModelResult(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResult(CEventMessage& Event)
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
      // copy data from MOdel to DataInterface and ProductInterface
      if ( copyModelEventData(Event) )
      {
        if ( m_pDMTask->getpPlantManager()  && 
             m_pDMTask->getpProductManager()   ) 
        {
          m_pDMTask->getpPlantManager()->changePlantInformation(Event);

          m_pDMTask->getpProductManager()->changeSetpoints(Event);


          m_pDMTask->getpProductManager()->changeProductInformation(Event);

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
                                         "CDM_LFModelResultEventHandler::doLFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFModelResultEventHandler::doLFModelResult()",
                                         ExceptionMsg.str().c_str());
  }
	return true;
}


bool CDM_LFModelResultEventHandler::doLFHeatAnnounceStatus(CEventMessage& Event)
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
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultActualSetpointsOffline(CEventMessage& Event)
{
	doLFModelResultOffline(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultCodeOffline(CEventMessage& Event)
{
	doLFModelResultOffline(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultRecipeSetpointsOffline(CEventMessage& Event)
{
	doLFModelResultOffline(Event);
	return true;
}

bool CDM_LFModelResultEventHandler::doLFHeatAnnounceStatusOffline(CEventMessage& Event)
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

        // We use the ProductManagementInterface with ProductID 
        // as the internally managed data key.
        Event.setDataKey(Event.getProductID());

        // send event to respective destinations
        dispatchEvent(Event);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFModelResultEventHandler::doLFHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

bool CDM_LFModelResultEventHandler::doLFModelResultOffline(CEventMessage& Event)
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
      // copy data from model interface to DM_DataInterface
      // and from DM_DataInterface to DM_ProductInterface
      if ( copyModelEventData(Event) )
      {
        dispatchEvent(Event);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_LFModelResultEventHandler::doLFModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_LFModelResultEventHandler::doLFModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
	return true;
}


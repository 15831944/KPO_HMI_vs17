// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_EventHandler.h"
#include "CDM_Task.h"
#include "CEventMessage.h"
#include "CDM_AnalysisEventHandler.h"

bool CDM_AnalysisEventHandler::doSteelAnalysisReceived(CEventMessage& Event)
{
  doOnAnalysisEvent( Event );
  return true;
}

bool CDM_AnalysisEventHandler::doSlagAnalysisReceived(CEventMessage& Event)
{
  doOnAnalysisEvent( Event );
  return true;
}

bool CDM_AnalysisEventHandler::doSteelSampleTaken(CEventMessage& Event)
{
  doOnSampleEvent( Event );
  return true;
}

bool CDM_AnalysisEventHandler::doSlagSampleTaken(CEventMessage& Event)
{
  doOnSampleEvent( Event );
  return true;
}

bool CDM_AnalysisEventHandler::doOnAnalysisEvent(CEventMessage& Event)
{
  try
  {
    // try to find respective ProductID
    if ( checkEventAssignment(Event) )
    {
      // try to update Sample data at the Product Management interface 
      if (m_pDMTask->getpProductManager()) 
      {
        m_pDMTask->getpProductManager()->changeAnalysisInformation(Event);
        
        m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event);
      }

      //  Send the event to respective,possibly several in the case of DataManager,
      //  destinations.
      dispatchEvent(Event);
    }
    // send event with unknown ProductID to subsystems
    // e.g. TSM will not handle the event but ARCHIVER will!
    else
    {
      // copy/fetch data form DH interface
      // HMI or Laboratory are possible !!
      if ( copyDataEventData( Event ))
      {
        dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_AnalysisEventHandler::doOnAnalysisEvent()",
                                         "");
  }
  return true;
}

CDM_AnalysisEventHandler::~CDM_AnalysisEventHandler()
{
}

CDM_AnalysisEventHandler::CDM_AnalysisEventHandler(CDM_Task* pDMTask)
:CDM_EventHandler( pDMTask )
{
}

bool CDM_AnalysisEventHandler::doOnSampleEvent(CEventMessage& Event)
{
  try
  {
    // try to find respective ProductID
    if ( checkEventAssignment(Event) )
    {
      // copy/fetch data from DH, HMI are possible !!
      if (copyProductEventData( Event ))
      {
        // try to update Sample data at Product Management interface 
        // will be called at "beforeDispatchEvent(CEventMessage& Event)"
        if (m_pDMTask->getpProductManager()) 
          m_pDMTask->getpProductManager()->changeSampleInformation(Event);

        //  Send the event to respective,possibly several in the case of DataManager,
        //  destinations.
        dispatchEvent(Event);
      }
    }
    // send event with unknown ProductID to subsystems
    // e.g. TSM will not handle the event but ARCHIVER will!
    else
    {
      // copy/fetch data form DH interface
      // HMI or Laboratory are possible !!
      if ( copyDataEventData( Event ))
      {
        dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_AnalysisEventHandler::doOnSampleEvent()",
                                         "");
  }
  return true;
}

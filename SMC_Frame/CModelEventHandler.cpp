// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"

#include "CModelTask.h"
#include "CSMC_Mutex.h"

#include "CModelEventHandler.h"


std::string CModelEventHandler::m_ActEventMessage;

CModelEventHandler::~CModelEventHandler()
{
}

CModelEventHandler::CModelEventHandler(CModelTask* pModelTask)
: m_pModelTask(pModelTask)
{
  // this will call initCommunication(..) method
  // communication values from [EventMessage] like ReceiverName, DestinationList a.o. will be overwritten by
  // inifile entry of [TaskName]

  setpTask(pModelTask);
}

bool CModelEventHandler::checkProductAcceptance(CEventMessage& Event)
{
  bool RetValue = false;

  // check if product is allready assigned at model task !
  if ( isAssignedProductID(Event.getProductID()) )
  {
    RetValue = true;
  }

  return RetValue;
}

bool CModelEventHandler::checkAnnouncement( CEventMessage & EventMessage, bool OfflineCalculationStatus)
{
  bool RetValue = true;
  std::string ProductID = EventMessage.getProductID();
  std::string HeatID    = EventMessage.getHeatID();
  std::string TreatID   = EventMessage.getTreatID();

  std::string ProcessID = cCBS_StdInitBase::getInstance()->m_ServerName;

  cCBS_StdInitBase::getInstance()->replaceWithEntry(m_pModelTask->getTaskName(), 
                                                    "ServerName", 
                                                    ProcessID);

  if ( m_pModelTask->checkProductAssignment(EventMessage,OfflineCalculationStatus) )
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_HeatAssignedToModel(sMessage,HeatID.c_str(),TreatID.c_str(),ProcessID.c_str());
  }
  else
  {
    RetValue = false;
  }

  return RetValue;
}


bool CModelEventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = false;

  CEventMessage evMessage(Event);

  cCBS_StdEvent_Task::getInstance()->setStateDetails("Actual Event Message", evMessage.getMessage(), 0);


  try
  {
    if (checkReceiver(evMessage)) // inserted for usage at offline system
    {
      // log incoming event only once !!!
      if ( getActEventMessage() != evMessage.getMessage() )
      {
        log("",3);
        log("----------------------------------- New Event -----------------------------------",3);
        log( evMessage,3 );
      }

      setActEventMessage(evMessage.getMessage());
      
      //TODO: is this needed and if yes make it thread safe
      // set static value
      m_ActEvent = evMessage;

      // Invokes on the actual event handling hook.
      // The actual event handling would be performed here, so this pure virtual hook operation
      // must be implement before instantiation
      RetValue = this->handleEvent( evMessage );

      if (RetValue)
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_EventSuccessfullyExecuted(sMessage, evMessage.getMessage().c_str());

        //ok we should not be called after one handled the event so reset the m_ActEventMessage
        m_ActEventMessage.clear();

        log("----------------------------------------------------------------------------",3);
      }
    }
  }
  catch(...)
  {
    m_ActEventMessage.clear();

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"Handling Event",
      "CModelEventHandler::handleEvent(const FRIESEvent& Event)", evMessage.getMessage().c_str());
  }
  return RetValue;
}

void CModelEventHandler::setOfflineCalculationStatus(bool value)
{
  m_pModelTask->setOfflineCalculationStatus(value);
}

bool CModelEventHandler::isAssignedProductID(const std::string& ProductID)
{
  return m_pModelTask->isAssignedProductID(ProductID);
}

void CModelEventHandler::cleanProductData()
{
  m_pModelTask->cleanProductData();
}

void CModelEventHandler::setActEventMessage(const std::string& ActEventMessage)
{
  CSMC_Mutex Mutex("m_ActEventMessage");
  m_ActEventMessage = ActEventMessage;
}

std::string CModelEventHandler::getActEventMessage() const
{
  CSMC_Mutex Mutex("m_ActEventMessage");
  return m_ActEventMessage;
}
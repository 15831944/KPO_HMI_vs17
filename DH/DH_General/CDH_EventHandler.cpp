// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CIntfData.h"
#include "CInterfaceAccess_Task.h"
#include "CEventMessage.h"

#include "CSMC_EventLogFrameController.h"
#include "CSMC_DataProvider_Impl.h"

#include "CDH_Task.h"


#include "CDH_EventHandler.h"

CDH_EventHandler::CDH_EventHandler()
: m_pDHTask(0)
, m_pHeatDataConverter(0)
, m_pGC_Plant_Container(0)
{
}

CDH_EventHandler::~CDH_EventHandler()
{
}

CDH_EventHandler::CDH_EventHandler(CInterfaceAccess_Task *pIntAccess) 
: m_pDHTask(pIntAccess)
{
}

bool CDH_EventHandler::afterHandleEvent(const FRIESEvent& Event)
{
  return true;
}

bool CDH_EventHandler::beforeHandleEvent(const FRIESEvent& Event)
{
  return true;
}


bool CDH_EventHandler::dispatchEvent(const std::string& SenderName, const std::string & DestinationName, CEventMessage& Event)
{
  //bool RetValue = false;

  //std::string ActSenderName = SenderName;

  //try
  //{
  //  // call additional internal functions to be called on each event !
  //  beforeDispatchEvent(Event);

  //  std::vector<std::string> DestinationList;
  //  DestinationList = CEventMessage::getDestinationList(DestinationName);

  //  if ( m_pDHTask )
  //  {
  //    if (ActSenderName.empty())
  //    {
  //      ActSenderName = m_SenderName;
  //    }

  //    std::string TaskName = m_pDHTask->getTaskName();
  //    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",ActSenderName);
  //    cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName",DestinationList);
  //  }

  //  RetValue = CEventHandler::dispatchEvent(ActSenderName, DestinationList, Event);

  //  // call additional internal functions to be called on each event !
  //  afterDispatchEvent(Event);
  //}
  //catch(...)
  //{
	 // cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,"",
  //                                       "CDH_EventHandler::dispatchEvent()",
  //                                       "");
  //}
  //return RetValue;
  
  bool RetValue = false;

  std::string ActSenderName;
  std::vector<std::string> ActDestinationList;

  try
  {
    // call additional internal functions to be called on each event !
    beforeDispatchEvent(Event);

    // we will take CEventHandler members set by initCommunication if no arguments are set
    if (SenderName.empty())
    {
      ActSenderName = m_SenderName;
    }
    else
    {
      ActSenderName = SenderName;
    }

    if (DestinationName.empty())
    {
      ActDestinationList = m_DestinationList;
    }
    else
    {
      ActDestinationList.push_back(DestinationName);
    }

    RetValue = CEventHandler::dispatchEvent(ActSenderName, ActDestinationList, Event);

    // call additional internal functions to be called on each event !
    afterDispatchEvent(Event);
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDH_EventHandler::dispatchEvent()",
                                         "");
  }
  return RetValue;
}


bool CDH_EventHandler::handleEvent(const FRIESEvent& Event)
{
  bool RetValue = true;
  try
	{
	  // The default implementation for this operation is that chek the receiver, then invoke the hook operation
	  // doEventHandlingHook
	  CEventMessage Event(Event);

	  if (checkReceiver(Event))
	  {
      cCBS_StdEvent_Task::getInstance()->setStateDetails("Actual Event Message", Event.getContent(), 0);

      std::string Message   = Event.getMessage();
      std::string ProductID = Event.getProductID();
      std::string Content   = Event.getContent();

      // log incoming event only once !!!
      if ( m_ActEvent.getContent() != Content )
      {
        log("",3);
        log("----------------------------------- New Event -----------------------------------",3);
        log( Event,3 );
      }

      // set static value
      m_ActEvent = Event;

	    // Invokes on the actual event handling hook.
	    // The actual event handling would be performed here, so this pure virtual hook operation
	    // must be implement before instantiation
	    RetValue = handleEvent( Event );

	    if (RetValue)
	    {

        log("",3);
        log("----------------------------------------------------------------------------",3);
	    }
	  }	// if (checkReceiver(Event))
    else
      RetValue = false;
	}
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDH_EventHandler::handleEvent()",
                                         "");
	}
	return RetValue;
}


bool CDH_EventHandler::beforeDispatchEvent(CEventMessage& Event)
{
  bool RetValue = false;

	return RetValue;
}


bool CDH_EventHandler::afterDispatchEvent(CEventMessage& Event)
{
	return false;
}


bool CDH_EventHandler::sendAdditionalEvents(CEventMessage& Event)
{
	return false;
}


std::string CDH_EventHandler::generateDataKey(CEventMessage& Event, const std::string &ActKey)
{
  return generateDataKey(Event.getProductID(), ActKey, Event.getMessage());
}

std::string CDH_EventHandler::generateDataKey(const std::string& DataKey, const std::string& ActKey, const std::string &Message)
{
  std::string generatedDataKey = ActKey;

  CSMC_DataProvider_Impl* pDH_Interface = m_pDHTask->getpInterface_OUT();
  if (pDH_Interface)
  {
    if (ActKey.empty())
    {
      generatedDataKey = pDH_Interface->generateDataKey(DataKey);
    }
  }

  std::stringstream LogMessage;
  LogMessage << "New data key : " 
          << generatedDataKey
          << " generated for Event : "
          << Message;

  log(LogMessage.str(),3);

  return generatedDataKey;
}


void CDH_EventHandler::setpDHTask(CInterfaceAccess_Task* value)
{
	m_pDHTask = value;

  // try to find special values for sender and receiver at ini file for given task name
  if ( m_pDHTask )
  {
    // use SenderName specific inifile entries
    initCommunication(m_SenderName);
  }

	return;
}


bool CDH_EventHandler::checkInternalData(const std::string& TlgName, std::string& HeatId, std::string& TreatId, std::string Plant, std::string& CustHeatId, std::string& CustTreatId)
{
  bool RetValue = true;

  std::stringstream strFunction;
  std::stringstream strAction;
  std::stringstream strMsg;

  strFunction << "CDH_EventHandler::checkInternalData: " << TlgName ;

  strAction << " Plant:" << Plant << ","
            << " HeatId:" << HeatId << ","
            << " TreatId:" << TreatId;

  try
  {  
    if ( !HeatId.empty() && HeatId != DEF::Inv_String )
    {
      if( m_pHeatDataConverter )
      {
        if ( m_pHeatDataConverter->getCustHeatData(HeatId,TreatId,CustHeatId,CustTreatId,Plant) )
        {
          CustHeatId    = CDataConversion::Trim(CustHeatId);
          CustTreatId   = CDataConversion::Trim(CustTreatId); 
        }
      }// if( m_pHeatDataConverter )
      else
      {
        strMsg << " No connection to database!: " << TlgName
               << " InternalHeatId:" << HeatId  << " InternalTreatId:" << TreatId;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage, "","HeatDataConverter",strMsg.str().c_str());

        RetValue = false;
      }

      // don't send something like "Inva"
      CustHeatId  = CDataConversion::SetInvalidToDefault(CustHeatId,"");
      CustTreatId = CDataConversion::SetInvalidToDefault(CustTreatId,"");

      if ( CustHeatId.empty() || CustTreatId.empty() )
      {
        strMsg << CustHeatId << " and " << CustTreatId << " are unknown";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID and TreatID",strMsg.str().c_str());

        RetValue = false;
      }
    }// if ( !HeatId.empty() && HeatId != DEF::Inv_String )
    else
    { 
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown", strFunction.str().c_str(),strAction.str().c_str()); 
  }

  return RetValue;
}

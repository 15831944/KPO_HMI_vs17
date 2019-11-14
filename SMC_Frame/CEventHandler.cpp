// Copyright (C) 2004 SMS Demag AG

#include <sstream>

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "CEventMessage.h"
#include "CProductID.h"

#include "CEventHandler.h"

//##ModelId=42395C000298
CEventMessage CEventHandler::m_ActEvent;

//##ModelId=410E076500D8
CEventHandler::CEventHandler()
{
  // set event values to default
  m_SenderName = cCBS_StdInitBase::getInstance()->m_ServerName;
  m_ReceiverName = cCBS_StdInitBase::getInstance()->m_ServerName;

  // use general inifile entries
  initCommunication("EventMessage");
}

//##ModelId=410E076B0287
CEventHandler::~CEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=410E3DC9024D
bool CEventHandler::handleEvent(const FRIESEvent& Event)
{
  try
  {
    if (getTraceLevel() > 1)
    {
      CEventMessage EventMessage(Event);
      
      std::string Message;

      Message =  "Event received but not handled : ";
      Message += EventMessage.getContent();

	    log(Message, 2);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventHandler::handleEvent()","Handling Event");
  }

  return false;
}

//##ModelId=412E18350387
void CEventHandler::log(const std::string& Message, long Level)
{
  cCBS_StdEvent_Task::getInstance()->log(Message,Level);
}

//##ModelId=412F247502D3
const std::string& CEventHandler::getReceiverName() const
{
	return m_ReceiverName;
}

// to be backward compatible !
//##ModelId=413EC4A30084
bool CEventHandler::dispatchEvent(const std::string& SenderName, const std::string& Destination, CEventMessage &Event)
{
  std::vector<std::string> DestinationList;

  if ( !Destination.empty() )
  {
    DestinationList.push_back(Destination);
  }

  return dispatchEvent(SenderName, DestinationList, Event);

}




//##ModelId=471C725F0039
bool CEventHandler::dispatchEvent(const std::string& SenderName, std::vector<std::string> & DestinationList, CEventMessage &Event, bool External)
{
  return Event.dispatch(SenderName,DestinationList, External);
}

//##ModelId=471C725E0254
bool CEventHandler::dispatchEvent(const std::string& SenderName, std::vector<std::string> & DestinationList, CEventMessage &Event)
{
  return Event.dispatch(SenderName,DestinationList,true);
}


//##ModelId=41405A4C00C1
void CEventHandler::log(CEventMessage& Event, long Level)
{
  if (getTraceLevel() >= Level)
  {
    log("Handling Event : " + Event.getContent(),Level);
  }
}



//##ModelId=416CF0F5026E
bool CEventHandler::checkReceiver(CEventMessage& Event)
{
  // check if reciever is set at inifile
  return Event.getReceiver() == m_ReceiverName ;
}

// check if received PLantId is valid for further event handling
//##ModelId=44FE9C2F0271
bool CEventHandler::checkPlantId(CEventMessage& Event)
{
  bool RetValue = false;

  std::vector<std::string>::iterator it;

  // check if PlantId check is used by respective inifile entry
  if ( m_PlantIdList.empty() )
  {
    RetValue = true;
  }
  else
  {
    for ( it = m_PlantIdList.begin() ; it != m_PlantIdList.end() ; ++it)
    {
      if ( Event.getPlantID() == (*it) )
      {
        RetValue = true;
        break;
      }
    }
  }

  return RetValue;
}

// check if received EventSender corrospondates with entry of m_TransmitterList
//##ModelId=44FE9C2F028F
bool CEventHandler::checkTransmitter(CEventMessage& Event)
{
  bool RetValue = false;

  std::vector<std::string>::iterator it;

  // check if m_TransmitterList is used by respective inifile entry
  for ( it = m_TransmitterList.begin() ; it != m_TransmitterList.end() ; ++it)
  {
    if ( Event.getSender() == (*it) )
    {
      RetValue = true;
      break;
    }
  }

  return RetValue;
}

bool CEventHandler::checkMessage(CEventMessage& Event)
{
  bool RetValue = false;

  std::vector<std::string>::iterator it;

  // check if m_TransmitterList is used by respective inifile entry
  if ( m_MessageList.empty() )
  {
    RetValue = true;
  }
  else
  {
    for ( it = m_MessageList.begin() ; it != m_MessageList.end() ; ++it)
    {
      if ( Event.getMessage() == (*it) )
      {
        RetValue = true;
        break;
      }
    }
  }

  return RetValue;
}


// check if avent could be accepted by
// - correct receiver     : receiver of event corrospondates to receiver of event handler
// - correct transmitter  : sender of event corrospondates to transmitter list of event handler
// - correct PlantID      : PlantID of event corrospondates to PlantID of event handler

//##ModelId=42B812960221
bool CEventHandler::checkEventAcceptance(const FRIESEvent& Event)
{
  bool RetValue = false;

  try
  {
    CEventMessage EventMessage(Event);

    // different versions to be checked
    // - receiver is set at inifile     && plantID && MessageID is ok
    // - transmitter is set at inifile  && plantID && MessageID is ok 
    // one of these setting MUST be available at inifile !!!!!!!!

    if ( (checkTransmitter(EventMessage) || checkReceiver(EventMessage)) && 
          checkPlantId(EventMessage) && 
          checkMessage(EventMessage))  
    {
      RetValue = true;
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventHandler::checkEventAcceptance()","Checking Event");
  }

  return RetValue;
}

bool CEventHandler::checkReplaceEvent(const FRIESEvent& FirstEvent, const FRIESEvent& NewEvent)
{
  bool RetValue = false;

  try
  {
    CEventMessage EventMessageFirst(FirstEvent);
    CEventMessage EventMessageNew(NewEvent);

    std::vector<std::string> EventList;
    std::vector<std::string>::iterator it; 

    if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("REPLACEEVENT","EventList",EventList) )
    {
      for ( it = EventList.begin(); it != EventList.end(); ++it )
      {
        if ( EventMessageFirst.getMessage() == (*it) &&
             EventMessageFirst.getMessage() == EventMessageNew.getMessage() )
        {
          RetValue = true;
          break;
        }
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventHandler::checkEventAcceptance()","Checking Event");
  }

  return RetValue;
}




//##ModelId=42397ADA017E
bool CEventHandler::checkDataIntegrity(CEventMessage& Event)
{
  bool RetValue = true;

  if (!Event.isPlantEvent())
  {
    std::string ProductID = Event.getProductID();
    std::string HeatID    = Event.getHeatID();
    std::string TreatID   = Event.getTreatID();
    std::string Message   = Event.getMessage();
    std::string PlantID   = Event.getPlantID();
    
    // valid for SMC 
    CProductID ID;

    if ( ID.getProductID(HeatID,TreatID) != ProductID )
    {
      if (getTraceLevel() > 1)
      {
        std::stringstream LogMessage;
        LogMessage << "Invalid Event Data detected !" ;
        LogMessage << " Event: " << Message;
        LogMessage << " ProductID: " << ProductID;
        LogMessage << " HeatID: " << HeatID;
        LogMessage << " TreatID: " << TreatID;
        LogMessage << " PlantID: " << PlantID;

        log(LogMessage.str(), 2);
      }
      RetValue = false;
    }
  }

  return RetValue;

}


//##ModelId=42C291EC0266
bool CEventHandler::doOnEventHandlingError(const FRIESEvent& Event)
{
  bool RetValue = true;

  try
  {
    if (getTraceLevel() > 0)
    {
      CEventMessage EventMessage(Event);

      std::stringstream Message;

      Message << "Event not handled! "
              <<  EventMessage.getSender()    << " -> "
              <<  EventMessage.getReceiver()  << " "
              <<  EventMessage.getMessage()   << " for ProductID : "
              <<  EventMessage.getProductID();

      log(Message.str(), 1);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventHandler::doOnEventHandlingError()","Handling event error");
  }

  return RetValue;

}

//##ModelId=433BAE830372
void CEventHandler::setpTask(cCBS_StdFrame_Task* value)
{
  // set communcation values for task
  cCBS_StdEventHandler::setpTask(value);

  // try to find special values for sender and receiver at ini file for given task name
  if ( m_pTask )
  {
    std::string TaskName = m_pTask->getTaskName();
    
    // use task specific inifile entries
    initCommunication(TaskName);
  }
}

//##ModelId=434CD60C0145
void CEventHandler::initCommunication(const std::string& Group)
{
  // take definition from inifile
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"ReceiverName",m_ReceiverName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"SenderName",m_SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"DestinationName", m_DestinationList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"TransmitterName", m_TransmitterList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"MessageName", m_MessageList);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(Group,"PlantId", m_PlantIdList);
}

bool CEventHandler::afterHandleEvent(const FRIESEvent& Event)
{
  return true;
}

bool CEventHandler::beforeHandleEvent(const FRIESEvent& Event)
{
  return true;
}
// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "iSMC_DataDefinitions_s.hh"
#include "iEventData_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdEvent_Task.h"

#include "CIntfData.h"

#include "CSMC_Mutex.h"

//##ModelId=41239E5201B6
#include "CEventMessage.h"



//##ModelId=41239E5201B6
CEventMessage::CEventMessage() 
:m_isPlantEvent(false)
,m_EventId(0)
,m_EventType(0)
{
//This default constructor is used for the static member 
//of CEventMessageCtrl.
}

//##ModelId=4109002502EF
CEventMessage::CEventMessage(const std::string& sender,
                             const std::string& receiver,
                             const std::string& message, 
                             const std::string& productID, 
                             const std::string& relatedInformation, 
                             bool isPlantEvent)
:m_Sender(sender)
,m_Receiver(receiver)
,m_Message(message)
,m_ProductID(productID)
,m_RelatedInformation(relatedInformation)
,m_isPlantEvent(isPlantEvent)
,m_EventId(0)
,m_EventType(0)
{
}

//##ModelId=413320B6026F
CEventMessage::CEventMessage(const std::string& sender, 
                             const std::string& receiver, 
                             const std::string& message, 
                             const std::string& productID, 
                             const std::string& relatedInformation,  
                             bool isPlantEvent, 
                             const std::string&HeatID, 
                             const std::string&TreatID, 
                             const std::string&DataKey)
:m_Sender(sender)
,m_Receiver(receiver)
,m_Message(message)
,m_ProductID(productID)
,m_RelatedInformation(relatedInformation)
,m_isPlantEvent(isPlantEvent)
,m_HeatID(HeatID)
,m_TreatID(TreatID)
,m_DataKey(DataKey)
,m_EventId(0)
,m_EventType(0)
{
}

//##ModelId=430C484A02C7
CEventMessage::CEventMessage(const std::string& sender, 
                             const std::string& receiver, 
                             const std::string& message, 
                             const std::string& plantID, 
                             const std::string& productID, 
                             const std::string& relatedInformation, 
                             bool isPlantEvent, 
                             const std::string& HeatID, 
                             const std::string& TreatID, 
                             const std::string& DataKey)
:m_Sender(sender)
,m_Receiver(receiver)
,m_Message(message)
,m_PlantID(plantID)
,m_ProductID(productID)
,m_RelatedInformation(relatedInformation)
,m_isPlantEvent(isPlantEvent)
,m_HeatID(HeatID)
,m_TreatID(TreatID)
,m_DataKey(DataKey)
,m_EventId(0)
,m_EventType(0)
{
}

CEventMessage::CEventMessage(const std::string& sender, 
                             const std::string& receiver, 
                             const std::string& message, 
                             const std::string& plantID, 
                             const std::string& plantLocation, 
                             const std::string& productID, 
                             const std::string& relatedInformation, 
                             bool isPlantEvent, 
                             const std::string& HeatID, 
                             const std::string& TreatID, 
                             const std::string& DataKey)
:m_Sender(sender)
,m_Receiver(receiver)
,m_Message(message)
,m_PlantID(plantID)
,m_PlantLocation(plantLocation)
,m_ProductID(productID)
,m_RelatedInformation(relatedInformation)
,m_isPlantEvent(isPlantEvent)
,m_HeatID(HeatID)
,m_TreatID(TreatID)
,m_DataKey(DataKey)
,m_EventId(0)
,m_EventType(0)
{
}


//##ModelId=4109002502EE
CEventMessage::~CEventMessage()
{
}

//##ModelId=410900250305
std::string CEventMessage::getContent()
{
  std::string RetValue;

  std::stringstream MessageStream;

  if ( m_EventId    != 0 || 
       m_EventType  != 0 )
  {
    MessageStream << "Id: " << m_EventId  << ", Type: " << m_EventType << ", ";
  }

  RetValue = MessageStream.str();
  RetValue +=  m_isPlantEvent ? "PlantEvent: " : "ProductEvent: ";
  RetValue +=  m_Sender + " -> " + m_Receiver + " : " + m_Message;
  RetValue +=  ", PlantID: " + m_PlantID;
  RetValue +=  ", PlantLocation: " + m_PlantLocation;
  RetValue +=  ", ProductID: " + m_ProductID;
  RetValue +=  ", RelatedInformation: " + m_RelatedInformation;
  RetValue +=  ", HeatID: " + m_HeatID;
  RetValue +=  ", TreatID: " + m_TreatID;
  RetValue +=  ", OrderID: " + m_OrderID;
  RetValue +=  ", DataKey: " + m_DataKey;

  return RetValue;
}

//##ModelId=4109FFFF0099
CEventMessage::CEventMessage(const FRIESEvent& Event)
:m_isPlantEvent(false)
,m_EventId(0)
,m_EventType(0)
{
  try
  {
    // fill attributes with Data coming from (FRIESEvent p_FriesEvent)
    sEventData* EventData = 0;

    m_EventId   = Event.id;
    m_EventType = Event.type;

    Event.eventData >>= EventData;

    if (EventData)
    {
	    m_Sender              = EventData->m_Sender;
	    m_Receiver            = EventData->m_Receiver;
	    m_Message             = EventData->m_Message;
      m_PlantID             = EventData->m_PlantID;
      m_PlantLocation       = EventData->m_PlantLocation;
	    m_ProductID           = EventData->m_ProductID;
      m_RelatedInformation  = EventData->m_RelatedInformation;
	    m_isPlantEvent        = EventData->m_isPlantEvent;
      m_HeatID              = EventData->m_HeatID;
      m_TreatID             = EventData->m_TreatID;
      m_OrderID             = EventData->m_OrderID;
      m_DataKey             = EventData->m_DataKey;
    }
    //else
    //{
    //  cCBS_StdEvent_Task::getInstance()->log("ERROR: structure of EventData, sent with the event, could not be converted/shifted to sEventData structure!", 3);
    //}
  }

  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventMessage::CEventMessage(const FRIESEvent& Event)","fatal error on converting Event, process stopped");
    exit(EXIT_FAILURE);
  }
}

//##ModelId=410A012D0288
bool CEventMessage::send()
{
  return send(true);
}

//##ModelId=471C725D025D
bool CEventMessage::send(bool sendExternal)
{
  bool RetValue = false;

  FRIESEvent FriesEvent;
  sEventData EventData;
  FriesEvent.id = m_EventId;
  FriesEvent.type = m_EventType;

  // convert Event to EventChannel data type
  EventData.m_Sender              = m_Sender.c_str();
  EventData.m_Receiver            = m_Receiver.c_str();
  EventData.m_Message             = m_Message.c_str();
  EventData.m_PlantID             = m_PlantID.c_str();
  EventData.m_PlantLocation       = m_PlantLocation.c_str();
  EventData.m_ProductID           = m_ProductID.c_str();
  EventData.m_RelatedInformation  = m_RelatedInformation.c_str();
  EventData.m_isPlantEvent        = m_isPlantEvent;
  EventData.m_HeatID              = m_HeatID.c_str();
  EventData.m_TreatID             = m_TreatID.c_str();
  EventData.m_OrderID             = m_OrderID.c_str();
  EventData.m_DataKey             = m_DataKey.c_str();

  FriesEvent.eventData <<= EventData;

  // Send FRIES event via event channel
  if (sendExternal) 
  {
    RetValue = cCBS_StdEvent_Task::getInstance()->sendEvent(FriesEvent, true);
  }
  else
  {
    RetValue = cCBS_StdEvent_Task::getInstance()->sendEvent(FriesEvent, false);
  }

  if ( RetValue )
  {
    cCBS_StdEvent_Task::getInstance()->log("Sending Event : " + this->getContent(),3);
  }

  return RetValue;
}

//##ModelId=4123982502D5
const std::string& CEventMessage::getDataKey() const 
{
	return m_DataKey;
}

//##ModelId=4123982701AE
const std::string& CEventMessage::getHeatID() const 
{
	return m_HeatID;
}

//##ModelId=412398290052
 bool CEventMessage::isPlantEvent() const 
{
	return m_isPlantEvent;
}

//##ModelId=4123982A02F1
const std::string& CEventMessage::getMessage() const 
{
	return m_Message;
}

//##ModelId=4123982C0146
const std::string& CEventMessage::getOrderID() const 
{
	return m_OrderID;
}

//##ModelId=4123982F019D
const std::string& CEventMessage::getReceiver() const 
{
	return m_Receiver;
}

//##ModelId=412398300393
const std::string& CEventMessage::getProductID() const 
{
	return m_ProductID;
}

//##ModelId=412398310113
void CEventMessage::setProductID(const std::string& value)
{
	m_ProductID = value;
}

//##ModelId=41239832034E
const std::string& CEventMessage::getSender() const 
{
	return m_Sender;
}

//##ModelId=4123983603A4
const std::string& CEventMessage::getTreatID() const 
{
	return m_TreatID;
}

long CEventMessage::getEventId() const 
{
	return m_EventId;
}

long CEventMessage::getEventType() const 
{
	return m_EventType;
}

//##ModelId=41239A280011
void CEventMessage::setDataKey(const std::string& value)
{
	m_DataKey = value;
}

//##ModelId=41239A2A01B8
void CEventMessage::setHeatID(const std::string& value)
{
	m_HeatID = value;
}

//##ModelId=41239A2D0267
void CEventMessage::setOrderID(const std::string& value)
{
	m_OrderID = value;
}

//##ModelId=41239A310169
void CEventMessage::setTreatID(const std::string& value)
{
	m_TreatID = value;
}

//##ModelId=413D85BC0394
const std::string& CEventMessage::getRelatedInformation() const
{
	return m_RelatedInformation;
}

//##ModelId=413D85BE0076
void CEventMessage::setRelatedInformation(const std::string& value)
{
	m_RelatedInformation = value;
}

//##ModelId=413DFD6802BD
void CEventMessage::setPlantEvent(bool value)
{
	m_isPlantEvent = value;
}

//##ModelId=413DFD7500A0
void CEventMessage::setMessage(const std::string& value)
{
	m_Message = value;
}

//##ModelId=413DFD9202CE
void CEventMessage::setReceiver(const std::string& value)
{
	m_Receiver = value;
}

//##ModelId=413DFDA20029
void CEventMessage::setSender(const std::string& value)
{
	m_Sender = value;
}

void CEventMessage::setEventId(long value)
{
	m_EventId = value;
}

void CEventMessage::setEventType(long value)
{
	m_EventType = value;
}


//sending event from "SenderName" to "DestinationName". 
//If inifile contains an entry for "DestinationName" at 
//[EventMessage] block, event will be send to this 
//destination. A comma seperated list is possible like 
//DestinationName = A,B,C
//##ModelId=42660C6400F4
bool CEventMessage::dispatch(const std::string& SenderName, const std::string& DestinationName, bool sendExternal /* = true */)
{
  std::vector<std::string> DestinationList;

  if (!DestinationName.empty())
  {
    DestinationList.push_back(DestinationName);
  }

  return dispatch(SenderName, DestinationList, sendExternal);
}


//##ModelId=44FE9C2F0196
bool CEventMessage::dispatch(const std::string& SenderName, std::vector<std::string>& DestinationList, bool sendExternal /* = true */)
{
  bool RetValue = false;

  try
  {
    // check if SenderName must be taken from inifile entry at [EventMessage]
    std::string ActSenderName = SenderName;

    if (ActSenderName.empty())
    {
      ActSenderName = CEventMessage::getSenderName("");
    }

    // check if DestinationName must be taken from inifile entry at [EventMessage]
    if (DestinationList.empty())
    {
      DestinationList = CEventMessage::getDestinationList(ActSenderName);
    }

    std::vector<std::string>::iterator it;
    for ( it = DestinationList.begin(); it != DestinationList.end(); ++it)
    {
      RetValue = doDispatch(ActSenderName,(*it),sendExternal);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventMessage::dispatch()","Dispatching Event");
  }

  return RetValue;
}


//##ModelId=471C725D03D0
bool CEventMessage::doDispatch(const std::string& SenderName, const std::string& DestinationName, bool sendExternal)
{
  CSMC_Mutex Mutex("CEventMessage::dispatch");

  bool RetValue = false;

  try
  {
    // set communication data
    setSender(SenderName);
    setReceiver(DestinationName);

    if (sendExternal)
    {
      RetValue = send();
    }
    else
    {
      RetValue = send(false);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CEventMessage::dispatch()","Dispatching Event");
  }

  return RetValue;
}


//##ModelId=4309CD4D02CE
void CEventMessage::setPlantID(const std::string& value)
{
	m_PlantID = value;
}

//##ModelId=4309CD1A0008
const std::string& CEventMessage::getPlantID() const
{
	return m_PlantID;
}

void CEventMessage::setPlantLocation(const std::string& value)
{
	m_PlantLocation = value;
}

const std::string& CEventMessage::getPlantLocation() const
{
	return m_PlantLocation;
}


//##ModelId=434D20C70243
std::string CEventMessage::getExtendedProductID(const std::string& productID, const std::string& extension)
{
  std::string RetValue(productID);
  RetValue += "$$";
  RetValue += extension;
  return RetValue;
}

//##ModelId=434D21750339
std::string CEventMessage::getOriginalProductID(const std::string& extendedProductID)
{
  return extendedProductID.substr(0, extendedProductID.find_first_of("$"));
}




//##ModelId=471C725C027A
std::string CEventMessage::getSenderName(const std::string& SenderName)
{
  // try to find general entry first, then special one
  std::string RetValue  = SenderName;

  // overwrite if exists by inifile entry for EventMessage
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",RetValue);

  // overwrite if exists by inifile entry for SenderName, e.g. TaskName
  cCBS_StdInitBase::getInstance()->replaceWithEntry(SenderName,"SenderName",RetValue);

  // check if previous found values must be overwritten by entry 
  std::vector<std::string> List;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","Reconfiguration",List);

  std::vector<std::string>::iterator it;
  for ( it = List.begin(); it != List.end(); ++it)
  {
    if ( (*it) == SenderName )
    {
      // overwrite if necessary by inifile entry for special group, typically TaskName
      cCBS_StdInitBase::getInstance()->replaceWithEntry(SenderName,"SenderName",RetValue);
    }
  }

  return RetValue;
}

//##ModelId=471C725C0306
std::vector<std::string> CEventMessage::getDestinationList(const std::string& SenderName)
{
  // try to find special entry first, then general one
  std::vector<std::string> RetValueList;
  std::vector<std::string> List;

  // check if reconfiguration has been defined for SenderName at [EventMessage]
  if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","Reconfiguration",List) )
  {
    std::vector<std::string>::iterator it;
    for ( it = List.begin(); it != List.end(); ++it)
    {
      if ( SenderName == (*it) )
      {
        cCBS_StdInitBase::getInstance()->replaceWithEntry(SenderName,"DestinationName",RetValueList);
      }
    }
  }

  // if nothing found, use SenderName entries
  if (RetValueList.empty())
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry(SenderName,"DestinationName",RetValueList);
  }

  // if nothing found, use [EventMessage] entries
  if (RetValueList.empty())
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","DestinationName",RetValueList);
  }

  // if nothing found, use Undefined
  if (RetValueList.empty())
  {
    RetValueList.push_back(DEF::Undefined);
  }

  return RetValueList;

}

bool CEventMessage::isAsCORBAAny( CORBA::Any seqAny )
{
  bool RetValue = false;
  sEventData *EventData = 0;
    
  if( seqAny >>= EventData )
  {
    RetValue = true;
  }

  return RetValue;
}

CEventMessage::CEventMessage( CORBA::Any seqAny )
:m_EventId(0)
,m_EventType(0)
{
  sEventData *EventData = 0;
    
  if( seqAny >>= EventData )
  {
    m_Sender              = EventData->m_Sender;
    m_Receiver            = EventData->m_Receiver;
    m_Message             = EventData->m_Message;
    m_PlantID             = EventData->m_PlantID;
    m_PlantLocation       = EventData->m_PlantLocation;
    m_ProductID           = EventData->m_ProductID;
    m_RelatedInformation  = EventData->m_RelatedInformation;
    m_isPlantEvent        = EventData->m_isPlantEvent;
    m_HeatID              = EventData->m_HeatID;
    m_TreatID             = EventData->m_TreatID;
    m_OrderID             = EventData->m_OrderID;
    m_DataKey             = EventData->m_DataKey;
  }
}

CORBA::Any CEventMessage::asCORBAAny()
{
  sEventData EventData;

  // convert Event to EventChannel data type
  EventData.m_Sender              = m_Sender.c_str();
  EventData.m_Receiver            = m_Receiver.c_str();
  EventData.m_Message             = m_Message.c_str();
  EventData.m_PlantID             = m_PlantID.c_str();
  EventData.m_PlantLocation       = m_PlantLocation.c_str();
  EventData.m_ProductID           = m_ProductID.c_str();
  EventData.m_RelatedInformation  = m_RelatedInformation.c_str();
  EventData.m_isPlantEvent        = m_isPlantEvent;
  EventData.m_HeatID              = m_HeatID.c_str();
  EventData.m_TreatID             = m_TreatID.c_str();
  EventData.m_OrderID             = m_OrderID.c_str();
  EventData.m_DataKey             = m_DataKey.c_str();

  CORBA::Any seqAny;
  seqAny <<= EventData;

  return seqAny;
}

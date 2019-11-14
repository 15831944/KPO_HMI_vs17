// Copyright (C) 2004 SMS Demag AG

#include "CDM_Task.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"

#include "CDateTime.h"

#include "CCyclicTriggerCall.h"
#include "CDM_CyclicTriggerCallProfile.h"



CDM_CyclicTriggerCallProfile::~CDM_CyclicTriggerCallProfile()
{
	delete m_pTrigger;
}

CDM_CyclicTriggerCallProfile::CDM_CyclicTriggerCallProfile(CEventMessage& Event , CDM_Task* pDM_Task )
{
  m_DataKey     = Event.getDataKey();
  m_Message     = Event.getMessage();
  m_ProductID   = Event.getProductID();
  m_HeatID      = Event.getHeatID();
  m_TreatID     = Event.getTreatID();
  m_PlantID     = Event.getPlantID();

  long CycleTime = 10000; // default is 10 seconds, can be overwritten for each event at ini file
  long MaxLifetime = -1; // in seconds, -1 means unlimited lifetime !

  std::vector<std::string> MessageList;
  std::vector<std::string>::iterator it;

  // initialize with general data
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CyclicTrigger","CycleTime",CycleTime);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CyclicTrigger","MaxLifetime",MaxLifetime);

  // reading all possible messages for trigger initialization
  cCBS_StdInitBase::getInstance()->getEntryList("CyclicTrigger","Message",MessageList);

  // find special configuration for trigger of this message
  for ( it = MessageList.begin() ; it != MessageList.end() ; ++it)
  {
    if ( (*it) == m_Message )
    {
      cCBS_StdInitBase::getInstance()->replaceWithEntry(m_Message,"CycleTime",CycleTime);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(m_Message,"MaxLifetime",MaxLifetime);
      break;
    }
  }

  std::string SenderName;
  std::string ReceiverName;

  std::vector<std::string>::iterator It;

  // general initialization for event message
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","SenderName",SenderName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("EventMessage","DestinationName",ReceiverName);

  // overwrite with new configuration for DM_Task
  if ( pDM_Task )
  {
    std::string TaskName = pDM_Task->getTaskName() ;
    cCBS_StdInitBase::getInstance()->getEntry(TaskName,"SenderName",SenderName);
    cCBS_StdInitBase::getInstance()->getEntry(TaskName,"DestinationName",ReceiverName);
  }

  Event.setSender(SenderName);// to send as DM
  // reset receiver to force CCyclicTrig to replace destination
  Event.setReceiver(ReceiverName); // sent 
  m_pTrigger  = new CCyclicTriggerCall(Event,CycleTime);
  m_pTrigger->setLifeTime(MaxLifetime);

}

std::string& CDM_CyclicTriggerCallProfile::getMessage()
{
	return m_Message;
}

std::string& CDM_CyclicTriggerCallProfile::getProductID()
{
	return m_ProductID;
}

std::string& CDM_CyclicTriggerCallProfile::getHeatID()
{
	return m_HeatID;
}

std::string& CDM_CyclicTriggerCallProfile::getTreatID()
{
	return m_TreatID;
}

std::string& CDM_CyclicTriggerCallProfile::getPlantID()
{
	return m_PlantID;
}


void CDM_CyclicTriggerCallProfile::update(CEventMessage& Event)
{
  CDateTime now;

  m_DataKey     = Event.getDataKey();
  m_LastUpdate  = now;

  m_pTrigger->updateActionTime(m_LastUpdate);

}

void CDM_CyclicTriggerCallProfile::reset()
{
  m_pTrigger->reset();

}


bool CDM_CyclicTriggerCallProfile::isUsed()
{
  bool RetValue = true;

  if (m_pTrigger->isTerminated()) // return true if thread does'n work
  {
    RetValue = false;
  }

  return RetValue;
}

void CDM_CyclicTriggerCallProfile::send()
{
  m_pTrigger->send();
}

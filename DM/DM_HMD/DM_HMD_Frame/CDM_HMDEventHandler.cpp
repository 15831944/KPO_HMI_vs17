// Copyright (C) 2007 SMS Demag AG

#include <string>
#include "CDM_HMDTask.h"
#include "CDM_HMDEventHandler.h"


//##ModelId=45139A72016B
CDM_HMDEventHandler::CDM_HMDEventHandler()
:CDM_EventHandler(CDM_HMDTask::getInstance())
{
}

//##ModelId=45139A72016C
CDM_HMDEventHandler::~CDM_HMDEventHandler()
{
}

bool CDM_HMDEventHandler::beforeDispatchEvent(CEventMessage& Event)
{
  bool RetValue = false;

  if ( m_pDMTask )
  {
    m_pDMTask->EventLog(Event);
  }

  if ( m_pDMTask && m_pDMTask->getpProductManager() )
  {
    // Copy DATA::DurSinceHeatAnnounce form product to event interface!
    RetValue = m_pDMTask->getpProductManager()->changeEventDataInformation(Event);
  }
	return RetValue;
}


bool CDM_HMDEventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  return false;
}




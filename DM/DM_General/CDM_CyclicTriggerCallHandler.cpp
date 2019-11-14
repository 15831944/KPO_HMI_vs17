// Copyright (C) 2004 SMS Demag AG


#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CEventMessage.h"
#include "CDateTime.h"
#include "CDM_Task.h"

#include "CDM_CyclicTriggerCallProfile.h"
#include "CDM_CyclicTriggerCallHandler.h"


CDM_CyclicTriggerCallHandler* CDM_CyclicTriggerCallHandler::m_Instance = 0;

CDM_CyclicTriggerCallHandler* CDM_CyclicTriggerCallHandler::getInstance()
{
	if (!m_Instance )
  {
    m_Instance = new CDM_CyclicTriggerCallHandler();
  }

  return m_Instance;
}

CDM_CyclicTriggerCallHandler::CDM_CyclicTriggerCallHandler()
{
}

CDM_CyclicTriggerCallHandler::~CDM_CyclicTriggerCallHandler()
{
  std::vector<CDM_CyclicTriggerCallProfile*>::iterator it;

  for ( it = m_ProfileList.begin(); it != m_ProfileList.end(); ++it)
  {
    delete (*it);
  }

  m_ProfileList.erase(m_ProfileList.begin(),m_ProfileList.end());
	
}


void CDM_CyclicTriggerCallHandler::call(CEventMessage& Event , CDM_Task* pDM_Task )
{
  std::vector<CDM_CyclicTriggerCallProfile*>::iterator it;

  std::string Message   = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string PlantID   = Event.getPlantID();
  bool isExisting       = false;

  try
  {
    it = m_ProfileList.begin();

    // try to remove elements with invalid lifetime !
    while(it != m_ProfileList.end())
    {
      if (! (*it)->isUsed() )
      {
        std::string Message;
        Message = "Erasing disused trigger profile. Message: " + (*it)->getMessage();
        Message += ", Product: " + (*it)->getProductID();
        cCBS_StdLog_Task::getInstance()->log(Message,1);
        delete (*it);
        m_ProfileList.erase(it);
        it =  m_ProfileList.begin();
      }
      else
      {
        ++it;
      }
    } // while(it != m_ProfileList.end())

    // try to find an event with same Message and ProductID
    for ( it = m_ProfileList.begin(); it != m_ProfileList.end(); ++it)
    {
      if ( (*it)->getMessage()   == Message    &&
           (*it)->getProductID() == ProductID  &&
           (*it)->getPlantID()   == PlantID )
      {
        (*it)->update(Event);
        isExisting = true;
        break;
      }
    }

    // if the event does not exist, it must be insertet into the profile list
    if (!isExisting )
    {
      CDM_CyclicTriggerCallProfile * Profile = new CDM_CyclicTriggerCallProfile(Event , pDM_Task);
      m_ProfileList.push_back(Profile);
    }

  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_CyclicTriggerCallHandler::remove()",
                                         "removing trigger");
  }

}

void CDM_CyclicTriggerCallHandler::reset(CEventMessage& Event , CDM_Task* pDM_Task )
{
  std::vector<CDM_CyclicTriggerCallProfile*>::iterator it;

  std::string Message   = Event.getMessage();
  std::string ProductID = Event.getProductID();
  std::string PlantID   = Event.getPlantID();
  bool isExisting       = false;

  try
  {
    // try to find an event with same Message and ProductID
    for ( it = m_ProfileList.begin(); it != m_ProfileList.end(); ++it)
    {
      if ( (*it)->getMessage()   == Message    &&
           (*it)->getProductID() == ProductID  &&
           (*it)->getPlantID()   == PlantID )
      {
        (*it)->reset();
        break;
      }
    }
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_CyclicTriggerCallHandler::remove()",
                                         "removing trigger");
  }

}


void CDM_CyclicTriggerCallHandler::remove(CEventMessage& Event, bool RemoveAllTriggers /* = false */)
{
  removeHeat(Event.getHeatID(), Event.getMessage(), RemoveAllTriggers);
}

void CDM_CyclicTriggerCallHandler::removeHeat(const std::string& HeatID, const std::string& Message, bool RemoveAllTriggers /* = false */)
{
  std::vector<CDM_CyclicTriggerCallProfile*>::iterator it;

  try
  {
    it = m_ProfileList.begin();

    // try to find an event with same Message and HeatID
    while(it != m_ProfileList.end())
    {
      // if the event exist, it must be deleted from the profile list and the
      // call profile must be deleted
      if ( ( (*it)->getHeatID() == HeatID && (*it)->getMessage() == Message ) ||
           ( (*it)->getHeatID() == HeatID && RemoveAllTriggers == true      ) )
      {

        // forcing to send cyclic trigger last time
        (*it)->send();

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TerminatingCyclicTrigger(sMessage,(*it)->getMessage().c_str(),(*it)->getHeatID().c_str(),(*it)->getTreatID().c_str());

        delete (*it);
        m_ProfileList.erase(it);
        it =  m_ProfileList.begin();
      }
      else
      {
        ++it;
      }
    } // while(it != m_ProfileList.end())
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_CyclicTriggerCallHandler::remove()",
                                         "removing trigger");
  }

}

void CDM_CyclicTriggerCallHandler::removeProduct(const std::string& ProductID, const std::string& Message, bool RemoveAllTriggers /* = false */)
{
  std::vector<CDM_CyclicTriggerCallProfile*>::iterator it;

  try
  {
    it = m_ProfileList.begin();

    // try to find an event with same Message and ProductID
    while(it != m_ProfileList.end())
    {
      // if the event exist, it must be deleted from the profile list and the
      // call profile must be deleted
      if ( ( (*it)->getProductID() == ProductID && (*it)->getMessage() == Message ) ||
           ( (*it)->getProductID() == ProductID && RemoveAllTriggers == true      ) )
      {

        // forcing to send cyclic trigger last time
        (*it)->send();

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_TerminatingCyclicTrigger(sMessage,(*it)->getMessage().c_str(),(*it)->getHeatID().c_str(),(*it)->getTreatID().c_str());

        delete (*it);
        m_ProfileList.erase(it);
        it =  m_ProfileList.begin();
      }
      else
      {
        ++it;
      }
    } // while(it != m_ProfileList.end())
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_CyclicTriggerCallHandler::remove()",
                                         "removing trigger");
  }

}





// Copyright (C) 2007 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_Task.h"
#include "CIntfData.h"
#include "CDM_HMDTask.h"

#include "CDM_HMDMaterialEventHandler.h"


//##ModelId=45139A7200EE
CDM_HMDMaterialEventHandler::~CDM_HMDMaterialEventHandler()
{
}

CDM_HMDMaterialEventHandler::CDM_HMDMaterialEventHandler()
{
}


bool CDM_HMDMaterialEventHandler::handleEvent(CEventMessage& evMessage)
{
	// change injection data and status im plant
	HANDLE_EVENT(HMDPowderBlowingStart);
  HANDLE_EVENT(HMDPowderBlowingEnd);

  HANDLE_EVENT(HMDHMIMaterialDischarged);

  HANDLE_EVENT_DATA(HMDChangePhysicalMatAvailibility);
	return false;
}

bool CDM_HMDMaterialEventHandler::doHMDHMIMaterialDischarged(CEventMessage& Event)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();

  try
  {
    if ( checkEventAssignment(Event) )
    {
      // copy data form DH interface
	    if ( copyDataEventData(Event) )
      {
        // try to read recipe anme from received data
        if (m_pDataInterface)
        {
          std::string RecipeName = m_pDataInterface->getString(Event.getDataKey(),
                                                               DATA::RecipeName);
          
          seqBatch RecipeBatch   = CIntfData::ToCORBAType(m_pDataInterface->getBatch(Event.getDataKey().c_str(),
                                                              DATA::RecipeContent));
          
          if (CIntfData::getLength(RecipeBatch) < 0)
          {
            log("ERORR: Event evHMDHMIMaterialDischarged: Empty batch received !",3);
          }

          // recipe name not send, set recipe name to "High Priority Batch"
          if ( RecipeName == DEF::Inv_String )
          {
            RecipeName = "HighPrioBatch";
            m_pDataInterface->setString(Event.getDataKey(),
                                        DATA::RecipeName,
                                        RecipeName);
            
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorHandlingRecipe(sMessage,"",RecipeName.c_str());
          }
          
          dispatchEvent(Event);

        } // if (m_pDataInterface)
      } // if ( copyDataEventData(Event) )
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDMaterialEventHandler::doHMDHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDMaterialEventHandler::doHMDHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDMaterialEventHandler::doHMDHMIMaterialDischarged()",
                                         ExceptionMsg.str().c_str());
  }

  return true;
}

bool CDM_HMDMaterialEventHandler::doHMDPowderBlowingStart(CEventMessage& Event)
{
  // copy data form DH interface
	if ( copyDataEventData(Event) )
  {
    if ( checkEventAssignment(Event) )
    {
	    // update Powder data at Plant Management interface 
      if (m_pDMTask->getpPlantManager()) 
        m_pDMTask->getpPlantManager()->changeInjectionData(Event);

      // update Powder data at Product Management interface
      if (m_pDMTask->getpProductManager()) 
        m_pDMTask->getpProductManager()->changeInjectionData(Event);

      dispatchEvent(Event);

			CDM_HMDDBManagerTask::getInstance()->getDBManager()->doOnPowerBlowing(Event,true);
    }
  }
  return true;
}

bool CDM_HMDMaterialEventHandler::doHMDPowderBlowingEnd(CEventMessage& Event)
{
  if ( checkEventAssignment(Event) )
  {
    // copy data form DH interface
	  if ( copyDataEventData(Event) )
    {
	    // update Powder data at Plant Management interface
      if (m_pDMTask->getpPlantManager()) 
        m_pDMTask->getpPlantManager()->changeInjectionData(Event);

	    // update Powder data at Product Management interface
      if (m_pDMTask->getpProductManager()) 
        m_pDMTask->getpProductManager()->changeInjectionData(Event);

      dispatchEvent(Event);

			CDM_HMDDBManagerTask::getInstance()->getDBManager()->doOnPowerBlowing(Event,false);
    }
  }
  return true;
}


// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_HMDModelResultEventHandler.h"
#include "CDM_ProductManagementInterface_Impl.h"


//##ModelId=45139A7200CF
CDM_HMDModelResultEventHandler::CDM_HMDModelResultEventHandler()
{
}

//##ModelId=45139A7200D0
CDM_HMDModelResultEventHandler::~CDM_HMDModelResultEventHandler()
{
}

//##ModelId=45139A7200D2
bool CDM_HMDModelResultEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(HMDModelResult);
	HANDLE_EVENT(HMDModelResultCode);
	HANDLE_EVENT(HMDHeatAnnounceStatus);
  
  // Offline events
	HANDLE_EVENT(HMDModelResultOffline);
	HANDLE_EVENT(HMDModelResultCodeOffline);
	HANDLE_EVENT(HMDHeatAnnounceStatusOffline);

	return false;
}

//##ModelId=45139A7200D9
bool CDM_HMDModelResultEventHandler::doHMDModelResultCode( CEventMessage& Event)
{
	doHMDModelResult(Event);
	return true;
}

//##ModelId=45139A7200D5
bool CDM_HMDModelResultEventHandler::doHMDModelResult(CEventMessage& Event)
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
      seqComputerModes StatusSeq;
      //safe previous comp mode avails
      if (m_pDMTask->getpProductManager())
      {
        StatusSeq = CIntfData::ToCORBAType(CDM_HMDTask::getInstance()->getpProductManagementInterface()->getComputerModes(Event.getProductID().c_str(),DATA::ComputerModeAvail));
      }

	  //Sankar to store model result as below function copyModelEventData() is not working
	  seqHMDModelResult seqModelPredResult;
      seqModelPredResult = CIntfData::ToCORBAType(CDM_HMDTask::getInstance()->m_pProductManagementInterface->getHMDModelResult(Event.getDataKey().c_str(),DATA::HMDPredRes));

	  //seqHMDModelResult seqModelCompModeResult;
      //seqModelCompModeResult = CIntfData::ToCORBAType(CDM_HMDTask::getInstance()->m_pProductManagementInterface->getHMDModelResult(Event.getDataKey().c_str(),DATA::ComputerModeAvail));

      seqComputerModes seqComputer = CIntfData::ToCORBAType(CDM_HMDTask::getInstance()->m_pProductManagementInterface->getComputerModes(Event.getDataKey().c_str(),DATA::ComputerModeAvail));
	  //log("SAN12",3);
	  //log(CIntfData::getContent(CIntfData::ToAny(seqModelCompModeResult)),3);
	  //log("SAN14",3);
	  //log(CIntfData::getContent(CIntfData::ToAny(seqComputer)),3);

      // copy data from MOdel to DataInterface and ProductInterface
      if ( copyModelEventData(Event) )
      {
        if (m_pDMTask->getpProductManager())
        {
          if (CIntfData::getLength(StatusSeq) > 0)
            CDM_HMDTask::getInstance()->m_pProductManagementInterface->setComputerModes(Event.getProductID().c_str(),DATA::ComputerModeAvail,StatusSeq);

          // check errors end set comp modes. Set reblow reason from modelresult
          m_pDMTask->getpProductManager()->changeComputerModeAvailabilities(Event);
       
		  //SANKAR
		  //CDM_HMDTask::getInstance()->m_pProductManagementInterface->setHMDModelResult(Event.getProductID().c_str(),DATA::HMDPredRes,seqModelPredResult); //it's required because above function copyModelEventData() is not working
		  //CDM_HMDTask::getInstance()->m_pProductManagementInterface->setComputerModes(Event.getProductID().c_str(),DATA::ComputerModeAvail,seqComputer); //it's required because above function copyModelEventData() is not working
		  CDM_HMDDBManagerTask::getInstance()->getDBManager()->doModelResult(Event);


          // send event to respective destinations
          dispatchEvent(Event);
					//CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHMDModelResult(Event,true); //monoj dutta
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDModelResult()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDModelResultEventHandler::doHMDModelResult()",
                                         ExceptionMsg.str().c_str());
  }
	return true;
}

//##ModelId=45139A7200DD
bool CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatus(CEventMessage& Event)
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
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatus()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}


//##ModelId=45139A7200C4
bool CDM_HMDModelResultEventHandler::doHMDModelResultCodeOffline(CEventMessage& Event)
{
	doHMDModelResultOffline(Event);
	return true;
}

//##ModelId=45139A7200CD
bool CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatusOffline(CEventMessage& Event)
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
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDModelResultEventHandler::doHMDHeatAnnounceStatusOffline()",
                                         ExceptionMsg.str().c_str());
  }
  return true;
}

//##ModelId=45139A7200CB
bool CDM_HMDModelResultEventHandler::doHMDModelResultOffline(CEventMessage& Event)
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
        dispatchEvent(Event);
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_HMDModelResultEventHandler::doHMDModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_HMDModelResultEventHandler::doHMDModelResultOffline()",
                                         ExceptionMsg.str().c_str());
  }
	return true;
}

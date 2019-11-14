// Copyright (C) 2007 SMS Demag AG

#include "CDM_HMDTask.h"
#include "CDM_HMDEventHandler.h"
#include "CDM_HMDAnalysisEventHandler.h"


//##ModelId=45139A72017B
CDM_HMDAnalysisEventHandler::~CDM_HMDAnalysisEventHandler()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45139A72017D
CDM_HMDAnalysisEventHandler::CDM_HMDAnalysisEventHandler()
: CDM_AnalysisEventHandler(CDM_HMDTask::getInstance())
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45139A720171
bool CDM_HMDAnalysisEventHandler::handleEvent(CEventMessage& evMessage)
{
	HANDLE_EVENT(HMDSlagAnalysisReceived);
	HANDLE_EVENT(HMDSlagSampleTaken);
	HANDLE_EVENT(HMDHotMetalSampleTaken);
	HANDLE_EVENT(HMDHotMetalAnalysisReceived);
	
	return false;
}

//##ModelId=45139A720180
bool CDM_HMDAnalysisEventHandler::doHMDSlagAnalysisReceived(CEventMessage& Event)
{
  bool RetValue = false;
	copyDataEventData(Event);
	if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evSlagAnalysisReceived(Event))
		RetValue=doOnAnalysisEvent(Event);
	return RetValue;
}

//##ModelId=45139A720184
bool CDM_HMDAnalysisEventHandler::doHMDSlagSampleTaken(CEventMessage& Event)
{
	
	bool RetValue = false;
	copyDataEventData(Event);
	if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evSlagSampleTaken(Event))
		RetValue=doOnSampleEvent(Event);
	return RetValue;
	//try
	//{
	//  // copy data from DH to event interface
	//  if ( copyDataEventData(Event) )
	//  {
	//    // try to find respective ProductID
	//    if ( checkEventAssignment(Event) )
	//    {
	//      // update Sample data at Product Management interface 
 //       if (m_pDMTask->getpProductManager()) 
 //         m_pDMTask->getpProductManager()->changeSampleData(Event);

	//			//  Send the event to respective,possibly several in the case of DataManager,
	//			//  destinations.
	//      dispatchEvent(Event);
	//    }
	//    // send event with unknown ProductID to subsystems
	//    // e.g. TSM will not handle the event but ARCHIVER will!
	//    else
	//    {
	//      dispatchEvent(Event);
	//    }
 //   }
	//}
	//catch(...)
	//{
 //   cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
 //   sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
 //   pEventLog->EL_ExceptionCaught(sMessage,"",
 //                                        "CDM_HMDAnalysisEventHandler::doHMDSlagSampleTaken()",
 //                                        "");
	//}
	//return true;
}



//##ModelId=45139A720186
bool CDM_HMDAnalysisEventHandler::doHMDHotMetalSampleTaken(CEventMessage& Event)
{

	bool RetValue = false;
	copyDataEventData(Event);
	if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHotMetalSampleTaken(Event))
		RetValue=doOnSampleEvent(Event);
	return RetValue;

	//try
	//{
	//  // try to find respective ProductID
	//  if ( checkEventAssignment(Event) )
	//  {
	//    // copy data from DH to event interface
	//    if ( copyDataEventData(Event) )
	//    {
	//      // update Sample data at Product Management interface 
 //       if (m_pDMTask->getpProductManager()) 
 //         m_pDMTask->getpProductManager()->changeSampleData(Event);

	//			//  Send the event to respective,possibly several in the case of DataManager,
	//			//  destinations.
	//      dispatchEvent(Event);
	//    }
	//  }
	//  // send event with unknown ProductID to subsystems
	//  // e.g. TSM will not handle the event but ARCHIVER will!
	//  else
	//  {
	//    // copy/fetch data form DH interface
 //     // HMI or Laboratory are possible !!
	//    if ( copyDataEventData( Event ))
	//    {
	//      dispatchEvent(Event);
	//    }
	//  }
	//}
	//catch(...)
	//{
 //   cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
 //   sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,"",m_pDMTask->getProcessState(Event.getProductID()),Event.getProductID());
 //   pEventLog->EL_ExceptionCaught(sMessage,"",
 //                                        "CDM_HMDAnalysisEventHandler::doHMDHotMetalSampleTaken()",
 //                                        "");
	//}
	//return true;
}

//##ModelId=45139A720188
bool CDM_HMDAnalysisEventHandler::doHMDHotMetalAnalysisReceived(CEventMessage& Event)
{
  bool RetValue = false;
	copyDataEventData(Event);
	if(CDM_HMDDBManagerTask::getInstance()->getDBManager()->evHotMetalAnalysisReceived(Event))
		RetValue=doOnAnalysisEvent(Event);
	return RetValue;
	
}

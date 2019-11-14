// Copyright (C) 2011 SMS Siemag AG

#include <iomanip>
#include <algorithm>


#include "CEventMessage.h"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDM_GENTask.h"
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "CSMC_EventLogFrameController.h"

#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_GENProductManager.h"

CDM_GENProductManager::~CDM_GENProductManager()
{
}

CDM_GENProductManager::CDM_GENProductManager()
: CDM_ProductManager(" ")
{
}

bool CDM_GENProductManager::changeSampleInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();
  std::string HeatID     = Event.getHeatID();
  std::string TreatID    = Event.getTreatID();
  std::string Message    = Event.getMessage();
  std::string PlantID    = Event.getPlantID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;

  return RetValue;
}

bool CDM_GENProductManager::changeAnalysisInformation(CEventMessage& Event)
{
  bool RetValue = false;
  std::string ProductID  = Event.getProductID();
  std::string DataKey    = Event.getDataKey();
  std::string HeatID     = Event.getHeatID();
  std::string TreatID    = Event.getTreatID();

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << ProductID << ", " << HeatID
               << ", " << TreatID << ", " << DataKey;


  //try
  //{
  //  if ( findProduct(ProductID, HeatID, TreatID) )
  //  {
  //    if (m_pDataInterface && 
  //        m_pProductManagementInterface)
  //    {
  //      if ( Event.getMessage() == HMP_EvMsg::evHMPAnalysisReceived)
  //      {
  //        setAnalysisData(Event, DATA::HMMeasAnalysis);
  //        RetValue = true;
  //      }
  //    }
  //  }
  //}
  //catch(CORBA::SystemException& sExc) 
  //{
	 // cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
  //                                       "CDM_GENProductManager::changeAnalysisInformation()",
  //                                       ExceptionMsg.str().c_str());
  //}
  //catch(CORBA::Exception& cExc) 
  //{
	 // cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
  //                                       "CDM_GENProductManager::changeAnalysisInformation()",
  //                                       ExceptionMsg.str().c_str());
  //}
  //catch(...) 
  //{
	 // cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  //  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  //  pEventLog->EL_ExceptionCaught(sMessage,"",
  //                                       "CDM_GENProductManager::changeAnalysisInformation()",
  //                                       ExceptionMsg.str().c_str());
  //}
  return RetValue;
}


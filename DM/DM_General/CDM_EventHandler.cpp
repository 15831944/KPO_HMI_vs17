// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "CIntfData.h"
#include "CSMC_DBData.h"
#include "CEventMessage.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdEvent_Task.h"
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CDM_Task.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_EventLogHandler.h"
#include "CDM_CyclicTriggerCallHandler.h"
#include "CDM_EventHandler.h"
#include "cCBS_ORB.h"// ffra:11/10/2018 added according to hadeed project

CDM_EventHandler::~CDM_EventHandler()
{
}

CDM_EventHandler::CDM_EventHandler(CDM_Task *pDM_Task) 
: m_pDataInterface(0)
, m_pProductManagementInterface(0)
, m_pPlantManagementInterface(0)
, m_pDMTask(pDM_Task)
, m_pModelResultInterface(0)
{

  // set communcation values for task
  setpTask(pDM_Task);

  // set interfaces
  init();

  //CORBA::Object_var dynObj = CBS::getORB()->resolve_initial_references("DynAnyFactory");// ffra : 11/10/2017 Changed according to hadeed project.
  CORBA::Object_var dynObj = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");
  m_DynAnyFact             = DynamicAny::DynAnyFactory::_narrow(dynObj);

}

bool CDM_EventHandler::checkEventAssignment(CEventMessage& Event  )
{
  bool RetValue = true;

  try
  {
    // check if event could be assigned to existing Product, Heat or PlantLocation
    std::string ProductID         = Event.getProductID();
    std::string HeatID            = Event.getHeatID();
    std::string TreatID           = Event.getTreatID();
    std::string PlantLocation     = Event.getPlantLocation();
    std::string Content           = Event.getContent();
    std::string OrderID           = Event.getOrderID();
    std::string PlantID           = Event.getPlantID();
    std::string ExternalHeatID;
    std::string ProcessStage;

    sEventLogMessage sMessage;

    if ( m_pDMTask->getpProductManager() )
    {
      // check if event is of type plantevent !
      if (!Event.isPlantEvent())
      {
        if (!m_pDMTask->getpProductManager()->findProduct(ProductID,HeatID,TreatID,OrderID) && 
            !m_pDMTask->getpProductManager()->findHeat(ProductID,HeatID,TreatID,OrderID)    &&
            !m_pDMTask->getpProductManager()->findOrder(ProductID,HeatID,TreatID,OrderID)    &&
            !m_pDMTask->getpProductManager()->findProductByEquipment(Event,ProductID,HeatID,TreatID,OrderID) &&
            !m_pDMTask->getpProductManager()->findActualPlantLocation(ProductID,HeatID,TreatID,OrderID,PlantLocation)&&
            !m_pDMTask->getpProductManager()->findActualProduct(ProductID,HeatID,TreatID,OrderID) )
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,m_pDMTask->getProcessState(ProductID),ProductID,m_pDMTask->getExternalHeatID(ProductID));
          pEventLog->EL_ErrorDetectingHeat(sMessage,HeatID.c_str(),TreatID.c_str(),Event.getMessage().c_str());

          // product unknown
          // try to detect data in database
          // product can be added to TSM when calling handleUnknownProduct !
          RetValue = handleUnknownProduct(Event);

          // if product has been found, use data of actual avent for further use
          if (RetValue)
          {
            ProductID = Event.getProductID();
            HeatID    = Event.getHeatID();
            TreatID   = Event.getTreatID();
            OrderID   = Event.getOrderID();
          }
        }

        // change event data in case of recognition of heat or product
        if (RetValue)
        {
          Event.setProductID(ProductID);
          Event.setHeatID(HeatID);
          Event.setTreatID(TreatID);
          Event.setOrderID(OrderID);
        }

        ExternalHeatID  = m_pDMTask->getExternalHeatID(ProductID);
        ProcessStage    = m_pDMTask->getProcessState(ProductID);
      }
    }
    
    Content = Event.getContent(); // read final event content

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,ProcessStage.c_str(),ProductID,ExternalHeatID);
    pEventLog->EL_EventReceived(sMessage,"","",Content.c_str());

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::checkEventAssignment()",
                                         "");
  }
  return RetValue;
}

bool CDM_EventHandler::dispatchEvents(CEventMessage& Event, std::vector<std::string>& Messages)
{
  bool RetValue = false;

  RetValue = dispatchEvent(Event);

  std::vector<std::string>::size_type pos = 0;

  while ( pos < Messages.size() )
  {
    Event.setMessage(Messages.at(pos));
    RetValue = RetValue & dispatchEvent(Event);
    pos++;
  }
  return RetValue;
}

bool CDM_EventHandler::dispatchEvent(CEventMessage& Event)
{
  bool RetValue = false;

  try
  {
    // call additional internal functions to be called on each event !
    beforeDispatchEvent(Event);

    // already set by CEventHandler class
    /*
    if ( m_pTask )
    {
      std::string TaskName = m_pTask->getTaskName();
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"SenderName",m_SenderName);
      cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"DestinationName",m_DestinationList);
    }

    */


    // using internal communication
    // beeing used for combined Tracking process including DM and TSM
    RetValue = CEventHandler::dispatchEvent(m_SenderName,m_DestinationList,Event, false);

    // call additional internal functions to be called on each event !
    afterDispatchEvent(Event);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::dispatchEvent()",
                                         "");
  }
  return RetValue;
}

bool CDM_EventHandler::handleEvent(const FRIESEvent& Event)
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
        log(Event, 3);
      }

      // set static value
      m_ActEvent = Event;

      // Invokes on the actual event handling hook.
      // The actual event handling would be performed here, so this pure virtual hook operation
      // must be implement before instantiation
      RetValue = handleEvent( Event );

      if (RetValue)
      {
        if ( ProductID.empty() ) // the product id is set in tracking
          ProductID = Event.getProductID();

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage;
        if ( ProductID.empty() )
        {
          sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        }
        else
        {
          sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,m_pDMTask->getProcessState(ProductID),ProductID,m_pDMTask->getExternalHeatID(ProductID));
        }
        pEventLog->EL_EventHandled(sMessage,Event.getSender().c_str(),Event.getReceiver().c_str(),Message.c_str());

        log("----------------------------------------------------------------------------",3);
      }
    }  // if (checkReceiver(Event))
    else
      RetValue = false;
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::handleEvent()",
                                         "");
  }
  return RetValue;
}

void CDM_EventHandler::init()
{
  if ( m_pDMTask )
  {
    m_pDataInterface = m_pDMTask->getpDataInterface();
    m_pProductManagementInterface = m_pDMTask->getpProductManagementInterface();
    m_pPlantManagementInterface = m_pDMTask->getpPlantManagementInterface();
  }
}

bool CDM_EventHandler::doDataEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key  )
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyDataEventData(Event, NameList,Key ))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDataEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::doDataEvent(CEventMessage& Event, const std::string& Name, const std::string& Key  )
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyDataEventData(Event, Name, Key))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDataEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::doPlantEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key  )
{
  bool RetValue = true;

  try
  {
    if (copyPlantEventData(Event, NameList, Key))
    {      
      if (Event.isPlantEvent() == false ) 
      {
        RetValue = RetValue && checkEventAssignment(Event);
      }
    }
    else
    {
      RetValue = false;
    }

    if ( RetValue ) 
      this->dispatchEvent(Event);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EventHandler::doPlantEvent()",
      "");
  }
  return RetValue;
}

bool CDM_EventHandler::doPlantEvent(CEventMessage& Event, const std::string& Name, const std::string& Key  )
{
  bool RetValue = true;

  try
  {
    if (copyPlantEventData(Event, Name, Key))
    {      
      if (Event.isPlantEvent() == false ) 
      {
        RetValue = RetValue && checkEventAssignment(Event);
      }
    }
    else
    { 
      RetValue = false;
    }

    if ( RetValue ) 
      this->dispatchEvent(Event);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
      "CDM_EventHandler::doPlantEvent()",
      "");
  }
  return RetValue;
}

bool CDM_EventHandler::doProductEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key  )
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyProductEventData(Event, NameList, Key))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doProductEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::doProductEvent(CEventMessage& Event, const std::string& Name, const std::string& Key  )
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyProductEventData(Event, Name, Key))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doProductEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::copyDataEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  bool RetValue = false;

  std::string NewDataKey = generateDataKey(Event,Key);

  std::string DataKey = Event.getDataKey();
  std::vector<std::string>::iterator itNames;

  for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
  {
    if (!(*itNames).empty()) 
    {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      // store data always under the same datakey !
      RetValue = copyDataEventData(Event,(*itNames),NewDataKey);
      if ( RetValue == false )
      {
        break;
      }
    }
  }
  return RetValue;
}

bool CDM_EventHandler::copyDataEventData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  bool RetValue = false;

  std::string Action = "Copy event data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action +=  " to ";

  try
  {
    std::string ProductID        = Event.getProductID();
    std::string DataKey          = Event.getDataKey();
    std::string ServerName       = Event.getSender();

    // read cyclic data from DH interface
    if( m_pDMTask)
    { 
      DH::iDH_Interface_var DH_Interface = m_pDMTask->getpDH_Interface(ServerName);

      if ( DH_Interface && m_pDataInterface)
      {
        std::string NewDataKey = generateDataKey(Event,Key);

        Action +=  NewDataKey;
        Action +=  " - ";
        Action +=  Name;

        log("*******************************************************************************",3);
        log(Action, 3);

        CIntfData::copyIntfData<DH::iDH_Interface_var>
          (DH_Interface,m_pDataInterface,DataKey,NewDataKey,Name);

        // JOGE is not used validateDataInterfaceData(Event, NewDataKey);

        log("*******************************************************************************",3);

        m_pDataInterface->showContent(NewDataKey,5);

        Event.setDataKey(NewDataKey);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CDM_EventHandler::copyDataEventData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CDM_EventHandler::copyDataEventData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CDM_EventHandler::copyDataEventData",
                                                     Action);
  }
  return RetValue;
}

bool CDM_EventHandler::copyPlantEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  bool RetValue = false;

  std::string NewDataKey = generateDataKey(Event,Key);

  std::string DataKey = Event.getDataKey();
  std::vector<std::string>::iterator itNames;

  for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
  {
    if (!(*itNames).empty()) 
    {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      // store data always under the same datakey !
      RetValue = copyPlantEventData(Event,(*itNames),NewDataKey);
      if ( RetValue == false )
      {
        break;
      }
    }
  }
  return RetValue;
}

bool CDM_EventHandler::copyPlantEventData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  bool RetValue = false;
  std::string Action = "Copy DH interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getDataKey();

  try
  {
    std::string DataKey          = Event.getDataKey();
    std::string ServerName       = Event.getSender();

    // read cyclic data from DH interface
    if ( m_pDMTask )
    {
      DH::iDH_Interface_var DH_Interface = m_pDMTask->getpDH_Interface(ServerName);

      if (DH_Interface && m_pPlantManagementInterface && m_pDataInterface )
      {
        std::string NewDataKey = generateDataKey(Event,Key);

        std::string NewDataKeyPlant = Key;

        if (NewDataKeyPlant.empty())
        {
          NewDataKeyPlant = DEF_PLANT::Furnace;
        }

        Action +=  " - ";
        Action +=  NewDataKey;
        Action +=  " and ";
        Action +=  NewDataKeyPlant;
        Action +=  " - ";
        Action +=  Name;

        // copy data from external interface to DataInterface
        CIntfData::copyIntfData<DH::iDH_Interface_var>
          (DH_Interface,m_pDataInterface,DataKey,NewDataKey,Name);

        // copy data from DataInterface to PlantManagementInterface
        CSMC_DataProvider_Impl::copyIntfData
          (m_pDataInterface,m_pPlantManagementInterface,NewDataKey,NewDataKeyPlant,Name);

        log(Action,3);

        Event.setDataKey(NewDataKey);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CDM_EventHandler::copyPlantEventData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,"CDM_EventHandler::copyPlantEventData",Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CDM_EventHandler::copyPlantEventData",Action);
  }

  return RetValue;
}

bool CDM_EventHandler::copyProductEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  bool RetValue = false;

  std::string DataKey = Event.getDataKey();
  std::vector<std::string>::iterator itNames;

  for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
  {
    if (!(*itNames).empty()) 
    {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      // store data always unde the same datakey !
      RetValue = copyProductEventData(Event,(*itNames),Key);
      if ( RetValue == false )
      {
        break;
      }
    }
  }
  return RetValue;
}

bool CDM_EventHandler::copyProductEventData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  bool RetValue = false;
  std::string Action = "Reading DH interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action +=  " - ";
  Action +=  Key;
  Action +=  " - ";
  Action +=  Name;

  try
  {
    std::string ProductID        = Event.getProductID();
    std::string DataKey          = Event.getDataKey();
    std::string ServerName       = Event.getSender();

    // read cyclic data from DH interface
    if( m_pDMTask )
    {
      DH::iDH_Interface_var DH_Interface = m_pDMTask->getpDH_Interface(ServerName);

      if (DH_Interface && m_pProductManagementInterface && m_pDataInterface )
      {
        std::string NewDataKey = generateDataKey(Event,Key);

        std::string NewDataKeyProduct = Key;
        if (NewDataKeyProduct.empty())
        {
          NewDataKeyProduct = ProductID;
        }

        // copy data from external interface to DataInterface
        CIntfData::copyIntfData<DH::iDH_Interface_var>
          (DH_Interface,m_pDataInterface,DataKey,NewDataKey,Name);

        // copy data from DataInterface to ProductManagementInterface
        CSMC_DataProvider_Impl::copyIntfData
          (m_pDataInterface,m_pProductManagementInterface,NewDataKey,NewDataKeyProduct,Name);

        log("*****************************",3);
        log(Action,3);

        m_pPlantManagementInterface->showContent(NewDataKey,5);

        log("*****************************",3);

        m_pProductManagementInterface->showContent(NewDataKeyProduct,5);

        Event.setDataKey(NewDataKey);
        RetValue = true;
      }
    }
  }

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CDM_EventHandler::copyProductEventData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CDM_EventHandler::copyProductEventData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CDM_EventHandler::copyProductEventData",
                                                     Action);
  }

  return RetValue;
}

bool CDM_EventHandler::beforeDispatchEvent(CEventMessage& Event)
{
  bool RetValue = false;

  if (!Event.isPlantEvent())
  {
    if ( m_pDMTask && m_pDMTask->getpProductManager() )
    {
      // Update Event Data with DATA::DurSinceHeatAnnounce form actual product data !
      RetValue = m_pDMTask->getpProductManager()->changeEventDataInformation(Event);

      // change phase state
      RetValue = m_pDMTask->getpProductManager()->changePhaseState(Event);
    }
  }

  if ( m_pDMTask )
  {
    m_pDMTask->EventLog(Event);
  }

  return RetValue;
}

bool CDM_EventHandler::afterDispatchEvent(CEventMessage& Event)
{
  bool RetValue = true;
 
  RetValue = sendAdditionalEvents(Event);

  return RetValue;
}

bool CDM_EventHandler::startCyclicTriggerCalls(CEventMessage& Event)
{
  // send additional events cyclically to DH_HMI
  CEventMessage HMIMessage(Event);
  HMIMessage.setMessage(HMI_EvMsg::evHMIUpdateDialogueData);
  HMIMessage.setDataKey(Event.getProductID());
  HMIMessage.setPlantID(Event.getPlantID());

  handleCyclicTriggerCall(HMIMessage);

  // send additional events cyclically to DH_OUT to send system status to Level 1
  bool SendGenSystemStatusReport = false;

  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();
  pStdInitBase->replaceWithEntry("ProcessControl", "SendGenSystemStatusReport", SendGenSystemStatusReport);

  if ( SendGenSystemStatusReport )
  {
    CEventMessage L1Message(Event);
    L1Message.setMessage(GEN_EvMsg::evGenSystemStatusReport);
    L1Message.setDataKey(Event.getProductID());
    L1Message.setPlantID(Event.getPlantID());

    handleCyclicTriggerCall(L1Message);
  }

  return true;
}



bool CDM_EventHandler::handleCyclicTriggerCall(CEventMessage& Event)
{

  try
  {
    // check if the ProductID is assigned to a model !
    if ( m_pDMTask->getpProductManagementInterface() )
    {
      // call additional internal functions to be called on each event !
      beforeDispatchEvent(Event);

	  CDateTime Departed = m_pDMTask->getpProductManagementInterface()->getDate(Event.getProductID().c_str(), DATA::HeatDepartureTime);
      // if a product is not in treatment (depart time not set), remove trigger call

      if (Departed == CDateTime::InvalidDate())
      {
        CDM_CyclicTriggerCallHandler::getInstance()->call(Event,m_pDMTask);
      }
      else
      {
        cCBS_StdLog_Task::getInstance()->log("Product is not in treatment. Removing cyclic trigger.",2);
        CDM_CyclicTriggerCallHandler::getInstance()->remove(Event);
      }

      // call additional internal functions to be called on each event !
      afterDispatchEvent(Event);

    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::handleCyclicTriggerCall()",
                                         "");
  }
  
  return true;
}

bool CDM_EventHandler::resetCyclicTriggerCall(CEventMessage& Event)
{

  try
  {
    // check if the ProductID is assigned to a model !
    if ( m_pDMTask->getpProductManagementInterface() )
    {
      // call additional internal functions to be called on each event !
      beforeDispatchEvent(Event);

      CDM_CyclicTriggerCallHandler::getInstance()->reset(Event,m_pDMTask);

      // call additional internal functions to be called on each event !
      afterDispatchEvent(Event);

    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::resetCyclicTriggerCall()",
                                         "");
  }
  
  return true;
}




bool CDM_EventHandler::removeAllCyclicTriggerCalls(CEventMessage& Event)
{
  try
  {
    // removing all trigger class for this Heat
    CDM_CyclicTriggerCallHandler::getInstance()->remove(Event,true);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::removeAllCyclicTriggerCalls()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::removeAllCyclicTriggerCalls(const std::string& ProductID)
{
  try
  {
    // removing all trigger class for this ProductID
    CDM_CyclicTriggerCallHandler::getInstance()->removeProduct(ProductID,"",true);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::removeAllCyclicTriggerCalls()",
                                         "");
  }
  return true;
}




bool CDM_EventHandler::validateProductInterfaceData(CEventMessage& Event, const std::string& Key)
{
  // TODO: Add your specialized code here.
  return (bool)0;
}

bool CDM_EventHandler::validatePlantInterfaceData(CEventMessage& Event, const std::string& Key)
{
  // TODO: Add your specialized code here.
  return (bool)0;
}

bool CDM_EventHandler::validateDataInterfaceData(CEventMessage& Event, const std::string& Key)
{
  bool RetValue = false;

  std::string Action = "Validating interface data for ";
  Action +=  Event.getMessage();
  Action +=  " - ";
  Action +=  Key;

  try
  {
    std::string Sender           = Event.getSender();
    std::string Message          = Event.getMessage();
    std::string ProductID        = Event.getProductID();

    if ( m_pDMTask && m_pDataInterface )
    {
      // get validation list form interface
      std::set<std::string>::iterator it;
      std::map<std::string,std::string>::iterator itTypeList;

      std::set<std::string> RuleSetNames = m_pDMTask->getRuleSetNames(Message);

      std::map<std::string,std::string> IntfDataTypeList;
      seqIntfDataList SeqIntfDataList = m_pDataInterface->getIntfDataList(Key);
      sIntfDataList IntfDataList;
      std::stringstream LogMessage;
      long Length = SeqIntfDataList.length();
      for(long I = 0; I < Length; I++)
      {
        if (CIntfData::getAt(IntfDataList,SeqIntfDataList,I))
        {
          IntfDataTypeList.insert(std::pair<std::string,std::string>(std::string(IntfDataList.Name),std::string(IntfDataList.Type)));

          if (getTraceLevel() > 3)
          {
            LogMessage << IntfDataList.Name << " - " << IntfDataList.Type 
                    << " copied from " << Sender << " with new Key :" << Key;

            if (I < Length)
            {
              LogMessage  << "\n";
            }
          }
        }
      }
      if ( getTraceLevel() > 3 && !LogMessage.str().empty() )
      {
        log(LogMessage.str(),4);
      }

      // if member of RuleSet is NOT member of DataTypeList
      // data transfer was incomplete
      for ( it = RuleSetNames.begin() ; it != RuleSetNames.end() ; ++ it)
      {
        std::string ActName = *it;

        if ( IntfDataTypeList.find(ActName) == IntfDataTypeList.end() )
        {
          std::stringstream LogMessage;
          LogMessage << m_pDataInterface->getProviderName()
                     << " - Missing Data for "
                     << ActName
                     << " after receiving event "
                     << Message
                     << " from "
                     << Sender 
                     << " with key "
                     << Event.getDataKey();

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DataProviderValidation(sMessage,LogMessage.str().c_str());
        }
      }// for ( it = RuleSetNames.begin() ; it != RuleSetNames.end() ; ++ it)

      // if data have invalid content write eventlog
      for ( itTypeList = IntfDataTypeList.begin() ; itTypeList != IntfDataTypeList.end() ; ++itTypeList)
      {
        std::string ActName = itTypeList->first;
        std::string ActType = itTypeList->second;

        if ( ActType == CIntfData::String )
        {
          std::string Name = m_pDataInterface->getString(Key,ActName);

          if ( Name == DEF::Inv_String )
          {
            std::stringstream LogMessage;
            LogMessage << m_pDataInterface->getProviderName()
                      << " - Empty Data received for "
                      << ActName
                      << " "
                      << ActType
                      << " after receiving event "
                      << Message
                      << " from "
                      << Sender
                      << " with key "
                      << Event.getDataKey();

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DataProviderValidation(sMessage,LogMessage.str().c_str());
            
          }
        }
        else if ( ActType == CIntfData::Double )
        {
          if ( DEF::Inv_Double == m_pDataInterface->getDouble(Key.c_str(),ActName.c_str()) )
          {
            std::stringstream LogMessage;
            LogMessage << m_pDataInterface->getProviderName()
                      << " - Empty Data received for "
                      << ActName
                      << " "
                      << ActType
                      << " after receiving event "
                      << Message
                      << " from "
                      << Sender
                      << " with key "
                      << Event.getDataKey();


          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_DataProviderValidation(sMessage,LogMessage.str().c_str());
            
          }
        }
        else if ( ActType == CIntfData::Long )
        {
          if ( DEF::Inv_Long == m_pDataInterface->getLong(Key.c_str(),ActName.c_str()) )
          {
            std::stringstream LogMessage;
            LogMessage << m_pDataInterface->getProviderName()
                      << " - Empty Data received for "
                      << ActName
                      << " "
                      << ActType
                      << " after receiving event "
                      << Message
                      << " from "
                      << Sender
                      << " with key "
                      << Event.getDataKey();

            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_DataProviderValidation(sMessage,LogMessage.str().c_str());
            
          }
        }
        else if ( ActType == CIntfData::Any )
        {
          // check for "empty sequence" of any content !
          CORBA::Any pActAny = m_pDataInterface->getAny(Key.c_str(),ActName.c_str());

          DynamicAny::DynAny_var da = m_DynAnyFact->create_dyn_any(pActAny);

          CORBA::TypeCode_var tc(da->type());
          while (tc->kind() == CORBA::tk_alias)
          {
            tc = tc->content_type();
          }

          if (tc->kind() == CORBA::tk_sequence)
          {
            DynamicAny::DynSequence_var ds = DynamicAny::DynSequence::_narrow(da);
            if (ds->get_length() <=0)         
            {
              std::stringstream LogMessage;
              LogMessage << m_pDataInterface->getProviderName()
                        << " - Empty Data received for "
                        << ActName
                        << " "
                        << ActType
                        << " after receiving event "
                        << Message
                        << " from "
                        << Sender
                        << " with key "
                        << Event.getDataKey();

              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_DataProviderValidation(sMessage,LogMessage.str().c_str());
            } // if   (ds->get_length() <=0)                           // empty sequence ?
          }// if (tc->kind() == CORBA::tk_sequence)

        }
      }// for ( it = RuleSetNames.begin() ; it != RuleSetNames.end() ; ++ it)
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CDM_EventHandler::validateDataInterfaceData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CDM_EventHandler::validateDataInterfaceData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CDM_EventHandler::validateDataInterfaceData",
                                                     Action);
  }


  return RetValue;
}



bool CDM_EventHandler::sendAdditionalEvents(CEventMessage& Event)
{
  // send additional events if defined at PlantManager or ProductManager
  std::vector<std::string> vMessages;

  // getAdditionallyMessages cleares list of events internally
  m_pDMTask->getpPlantManager()->getAdditionallyMessages(vMessages);

  for (long i = 0 ; i < (long)vMessages.size(); i++)
  {
    Event.setMessage(vMessages.at(i));
    dispatchEvent(Event);
  }

  // getAdditionallyMessages cleares list of events internally
  m_pDMTask->getpProductManager()->getAdditionallyMessages(vMessages);

  for (long i = 0 ; i < (long)vMessages.size(); i++)
  {
    Event.setMessage(vMessages.at(i));
    dispatchEvent(Event);
  }

  return true;
}



std::string CDM_EventHandler::generateDataKey(CEventMessage& Event, const std::string &ActKey)
{
  return generateDataKey(Event.getProductID(), ActKey, Event.getMessage());
}



std::string CDM_EventHandler::generateDataKey(const std::string& DataKey, const std::string& ActKey, const std::string &Message)
{
  std::string generatedDataKey = ActKey;

  if (m_pDataInterface)
  {
    if (ActKey.empty())
    {
      generatedDataKey = m_pDataInterface->generateDataKey(DataKey);
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





bool CDM_EventHandler::doDataEventForward(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  try
  {
    if (copyDataEventData(Event, NameList,Key ))
    {
      this->dispatchEvent(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDataEventForward()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::doDataEventForward(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  try
  {
    if (copyDataEventData(Event, Name, Key))
    {
      this->dispatchEvent(Event);
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDataEventForward()",
                                         "");
  }
  return true;
}


bool CDM_EventHandler::setpModelResultInterface(CEventMessage& Event)
{
  bool RetValue = false;

  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " << Event.getSender()
               << ", " << Event.getProductID() << ", " << Event.getHeatID()
               << ", " << Event.getTreatID() << ", " << Event.getDataKey();


  try
  {
    if (m_pProductManagementInterface && m_pDMTask ) 
    {
      // find assined model of Product ID at DM

      m_pModelResultInterface = m_pDMTask->getpModelResultInterface(Event.getSender());

      if (m_pModelResultInterface)
      {
        RetValue = true;
      } 
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorDetectingProxy(sMessage,Event.getSender().c_str(),
              "CDM_EventHandler::setpModelResultInterface()");
      }
    } // if (m_pProductManagementInterface) 
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EventHandler::setpModelResultInterface()",
                                         ExceptionMsg.str().c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EventHandler::setpModelResultInterface()",
                                         ExceptionMsg.str().c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::setpModelResultInterface()",
                                         ExceptionMsg.str().c_str());
  }

  return RetValue;

}

bool CDM_EventHandler::copyModelEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  bool RetValue = false;

  std::string DataKey = Event.getDataKey();
  std::vector<std::string>::iterator itNames;

  for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
  {
    if (!(*itNames).empty()) 
    {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      RetValue = copyModelEventData(Event,(*itNames),Key);
      if ( RetValue == false )
      {
        break;
      }
    }
  }
  return RetValue;
}



bool CDM_EventHandler::copyModelEventData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  bool RetValue = false;

  std::string Action = "Reading DH interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action +=  " - ";
  Action +=  Key;
  Action +=  " - ";
  Action +=  Name;


  try
  {
    if ( setpModelResultInterface(Event) )
    {
      std::string ProductID        = Event.getProductID();
      std::string DataKey          = Event.getDataKey();

      // read cyclic data from DH interface
      if (m_pModelResultInterface && m_pProductManagementInterface && m_pDataInterface )
      {

        std::string NewDataKey = Key;
        if (Key.empty())
        {
          NewDataKey = m_pDataInterface->generateDataKey(ProductID);
        }

        log("*****************************",3);
        log(Action,3);

        // copy data from external interface to DataInterface
        CIntfData::copyIntfData<iModelResults_var>
          (m_pModelResultInterface,m_pDataInterface,DataKey,NewDataKey,Name);

        m_pProductManagementInterface->showContent(NewDataKey,5);

        log("*****************************",3);

        // copy data from DataInterface to ProductManagementInterface
        CSMC_DataProvider_Impl::copyIntfData
          (m_pDataInterface,m_pProductManagementInterface,NewDataKey,ProductID,Name);

        m_pProductManagementInterface->showContent(ProductID,5);

        Event.setDataKey(NewDataKey);
        RetValue = true;
      }
    }
  }

  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                         "CDM_EventHandler::copyModelEventData()",
                                         Action.c_str());
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                         "CDM_EventHandler::copyModelEventData()",
                                         Action.c_str());
  }
  catch(...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLogFrame::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::copyModelEventData()",
                                         Action.c_str());
  }
  return RetValue;
}

bool CDM_EventHandler::doModelEvent(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  if ( checkEventAssignment(Event) )
  {
    if (copyModelEventData(Event, Key, Name))
    {
      dispatchEvent(Event);
    }
  }
  return true;
}

bool CDM_EventHandler::doModelEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  if ( checkEventAssignment(Event) )
  {
    if (copyModelEventData(Event, NameList, Key))
    {
      dispatchEvent(Event);
    }
  }
  return true;
}



bool CDM_EventHandler::doOnUnknownProduct(CEventMessage& Event)
{
  log("doOnUnknownProduct not implemented",2);
  return false;
}

bool CDM_EventHandler::handleUnknownProduct(CEventMessage& Event)
{
  bool RetValue = false;
  // inserts default dataset to database for data aquisition only.
  if ( Event.getHeatID() == CSMC_DBData::Default)
  {
    log("ERROR: Handle Unknown (not announced) heat!",2);
    // create a copy of event Message, copyDataEventData will change DataKey !
    CEventMessage ActEvent(Event);

    std::vector<std::string> NameList;
    NameList.push_back(DATA::CustHeatID);
    NameList.push_back(DATA::CustTreatID);

    copyDataEventData(ActEvent, NameList, ActEvent.getDataKey());

    // read customer data and call task method
    std::string CustHeatID = DEF::Inv_String;
    std::string CustTreatID = DEF::Inv_String;

    if ( m_pDataInterface)
    {
      CustHeatID  = m_pDataInterface->getString(ActEvent.getDataKey(),DATA::CustHeatID);
      CustTreatID = m_pDataInterface->getString(ActEvent.getDataKey(),DATA::CustTreatID);
    }

    if (CustHeatID != DEF::Inv_String &&
        CustTreatID != DEF::Inv_String)
    {
      m_pDMTask->handleUnknownProduct(Event,CustHeatID,CustTreatID,Event.getPlantID());
    }
  }

  // check if incoming HeatID has been added to database
  if (!Event.getHeatID().empty() && !Event.getTreatID().empty())
  {
    std::string ProdOrderID;

    if ( m_pDMTask->isProductInProduction(Event.getHeatID(),Event.getTreatID(),Event.getPlantID(), ProdOrderID) )
    {
      Event.setOrderID(ProdOrderID);

      if ( m_pDMTask->getpProductManager() )
      {
        // product will be registered
        // and sample manager initialized

        m_pDMTask->getpProductManager()->registerProduct(Event);

        // set some times from PD_ACTION
        m_pDMTask->setProductData(Event);

        m_pDMTask->getpProductManager()->changeProductInformation(Event);

        // calling unit specific implementations, e.g. sending event to TSM
        RetValue = doOnUnknownProduct(Event);
      }
    }
  }
  return RetValue;
}

bool CDM_EventHandler::doDMDataEvent(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyDMDataEventData(Event, Name, Key))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDMDataEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::doDMDataEvent(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  try
  {
    if ( checkEventAssignment(Event) )
    {
      if (copyDMDataEventData(Event, NameList,Key ))
      {
        this->dispatchEvent(Event);
      }
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                         "CDM_EventHandler::doDMDataEvent()",
                                         "");
  }
  return true;
}

bool CDM_EventHandler::copyDMDataEventData(CEventMessage& Event, std::vector<std::string>& NameList, const std::string& Key)
{
  bool RetValue = false;

  std::string NewDataKey = generateDataKey(Event,Key);

  std::string DataKey = Event.getDataKey();
  std::vector<std::string>::iterator itNames;

  for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
  {
    if (!(*itNames).empty()) 
    {
      // copy data always for the same datakey !
      Event.setDataKey(DataKey);
      // store data always under the same datakey !
      RetValue = copyDMDataEventData(Event,(*itNames),NewDataKey);
      if ( RetValue == false )
      {
        break;
      }
    }
  }
  return RetValue;
}

bool CDM_EventHandler::copyDMDataEventData(CEventMessage& Event, const std::string& Name, const std::string& Key)
{
  bool RetValue = false;

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  Event.getProductID();
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action +=  " - ";
  Action +=  Key;
  Action +=  " - ";
  Action +=  Name;


  try
  {
    std::string ProductID        = Event.getProductID();
    std::string DataKey          = Event.getDataKey();
    std::string ServerName       = Event.getSender();

    // read cyclic data from DH interface
    if( m_pDMTask)
    { 
      DM::iDM_Interface_var DM_Interface = m_pDMTask->getpDM_Interface(ServerName,DM::EVENT);

      if ( DM_Interface && m_pDataInterface)
      {
        std::string NewDataKey = generateDataKey(Event,Key);
        
        CIntfData::copyIntfData<DM::iDM_Interface_var>
          (DM_Interface,m_pDataInterface,DataKey,NewDataKey,Name);

        //JOGE 
        // validateDataInterfaceData(Event, NewDataKey);

        log("*****************************************************************************************",3);
        log(Action,3);

        m_pDataInterface->showContent(NewDataKey,5);

        log("*****************************************************************************************",3);

        Event.setDataKey(NewDataKey);
        RetValue = true;
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CDM_EventHandler::copyDMDataEventData",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CDM_EventHandler::copyDMDataEventData",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CDM_EventHandler::copyDataEventData",
                                                     Action);
  }
  return RetValue;
}

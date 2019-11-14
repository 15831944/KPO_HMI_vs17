// Copyright (C) 2004 SMS Demag AG
#include <assert.h>
#include <sstream>

#include "iDH_Interface_s.hh"
#include "iEventMessages_s.hh"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "CIntfData.h"
#include "CProductID.h"
   
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_EventLogHandlerAdapter.h"
#include "CDM_EventLogHandler.h"

#include "CPD_HEAT_DATA.h"
#include "CGC_Plant_Container.h"
#include "DEF_GC_ACTION_DEF.h"
#include "CPD_ACTION.h"
#include "CPD_HEAT_REF.h"
#include "CPD_HEAT_PLANT_REF.h"
#include "CGC_STATUS.h"

#include "CDM_Task.h"


CDM_Task::~CDM_Task()
{
	if(m_pDataInterface)
		delete m_pDataInterface;
	if(m_pProductManagementInterface)
		delete m_pProductManagementInterface;
	if(m_pPlantManagementInterface)
		delete m_pPlantManagementInterface;
  if(m_pEventLogHandlerAdapter)
		delete m_pEventLogHandlerAdapter;
  
  if ( m_pDHProxyManager )
    delete m_pDHProxyManager;

  if ( m_pModelResultsProxyManager )
    delete m_pModelResultsProxyManager;

  if ( m_pDMProxyManager )
    delete m_pDMProxyManager;

  if (m_pProductManager) delete m_pProductManager;
  if (m_pPlantManager)   delete m_pPlantManager;

  deleteDBClasses();
  
	// also here we should unbound the CORBA connections already established!!!

  // And how about the event handler objects already registered? Who is responsible for
	// their elimination? Otherwise memory leaks would definitely occur.

}

CDM_Task::CDM_Task()
: m_pDataInterface(0)
, m_pProductManagementInterface(0)
, m_pPlantManagementInterface(0)
, m_pPlantManager(0)
, m_pProductManager(0)
, m_pDHProxyManager(0)
, m_pDMProxyManager(0)
, m_pModelResultInterface(0)
, m_pModelResultsProxyManager(0)
, m_pDH_Interface(0)
, m_pEventLogHandlerAdapter(0)
, m_pPD_HEAT_DATA(0)
, m_pPD_HEAT_REF(0)
, m_pPD_HEAT_PLANT_REF(0)
, m_pGC_STATUS(0)
, m_pGC_Plant_Container(0)
{

  m_pDHProxyManager = new CProxyManager<DH::iDH_Interface>();

  m_pModelResultsProxyManager = new CProxyManager<iModelResults>();

  m_pDMProxyManager = new CProxyManager<DM::iDM_Interface>();

  // These are the three data providers we used for three different data 
	// access interfaces.
	m_pDataInterface = new CDM_DataInterface_Impl();
  m_pProductManagementInterface = new CDM_ProductManagementInterface_Impl();
  m_pPlantManagementInterface = new CDM_PlantManagementInterface_Impl();


  m_pEventLogHandlerAdapter = new CDM_EventLogHandlerAdapter();


  long BufferSize = 500;
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DATAPROVIDER","BufferSize",BufferSize);

  m_pDataInterface->setBufferSize(BufferSize);
  m_pProductManagementInterface->setBufferSize(BufferSize);
  m_pPlantManagementInterface->setBufferSize(BufferSize);

}

CDM_DataInterface_Impl* CDM_Task::getpDataInterface()
{
	return m_pDataInterface;
}

CDM_ProductManagementInterface_Impl* CDM_Task::getpProductManagementInterface()
{
	return m_pProductManagementInterface;
}

CDM_PlantManagementInterface_Impl* CDM_Task::getpPlantManagementInterface()
{
	return m_pPlantManagementInterface;
}

void CDM_Task::initManager()
{
	// init Product Manager
  if (m_pProductManager) m_pProductManager->init(this);

	// init Plant Manager
  if (m_pPlantManager) m_pPlantManager->init(this);

  // register model(s)
  if (m_pPlantManager) m_pPlantManager->registerModel();

}

void CDM_Task::ownStartUp()
{
  try
  {
    //Registering specific event handlers
	  registerEventHandlers();
    //Registering specific eventLog handlers
    registerEventLogHandlers();

    cCBS_StdFrame_Task::ownStartUp();
  }
  catch(...) 
  {
    std::cout << "exception caught in CDM_Task::ownStartUp()" << std::endl;
  }
}


//
// The proxy should already be registered when we call registerProxy inside ownStartup().
// So just bind it and return the object reference.
//
DH::iDH_Interface_var& CDM_Task::getpDH_Interface(const std::string& ServerName)
{
  try
  {
    m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName (ServerName);

    if (!m_pDH_Interface)
    {
      m_pDHProxyManager->handleConnectionErrorByServerName(ServerName);
      m_pDH_Interface = m_pDHProxyManager->getObjRefByServerName(ServerName);
    }
  }
  catch(...)
  {

	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CDM_Task::getpDH_Interface()",
                                        "getObjRefByServerName");

    m_pDH_Interface = 0;

  }

  if ( m_pDH_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }


  return m_pDH_Interface;
}

iModelResults_var& CDM_Task::getpModelResultInterface(const std::string &ServerName)
{
  try
  {
    m_pModelResultInterface = m_pModelResultsProxyManager->getObjRefByServerName(ServerName);

    if (!m_pModelResultInterface)
    {
      m_pModelResultsProxyManager->handleConnectionErrorByServerName(ServerName);
      m_pModelResultInterface = m_pModelResultsProxyManager->getObjRefByServerName(ServerName);
    }
  }
  catch(...)
  {

	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CDM_Task::getpModelResultInterface()",
                                        "getObjRefByServerName");

    m_pModelResultInterface = 0;

  }

  if ( m_pModelResultInterface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }


  return m_pModelResultInterface;

}

DM::iDM_Interface_var& CDM_Task::getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  try
  {
    m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName (ServerName,InterfaceTypeName);

    if (!m_pDM_Interface)
    {
      m_pDMProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
      m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
    }
  }
  catch(...)
  {

	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CDM_Task::getpDM_Interface()",
                                        "getObjRefByServerName");

    m_pDM_Interface = 0;

  }

  if ( m_pDM_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }

  return m_pDM_Interface;
}

//
// This helper member operation registers the local CORBA servants.
//
void CDM_Task::initCORBAInterfaces()
{
  //
  // register proxies 
  //
  m_pDHProxyManager->registerProxies("DataHandler");
  m_pDMProxyManager->registerProxies("DM");

  std::string ModelEntry  = "Model";
  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(),"Model", ModelEntry);

  m_pModelResultsProxyManager->registerProxies(ModelEntry);


	//
  // register local CORBA servant
	//
  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();
	if (pCORBA_Task)
  {
    std::string ServerName = cCBS_StdInitBase::getInstance()->m_ServerName;

    std::string ServantName    = ServerName + "DataInterface";
    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "DataInterface", ServantName);
    pCORBA_Task->registerServant(m_pDataInterface,ServantName);
    m_pDataInterface->setProviderName(ServantName);

    ServantName    = ServerName + "ProductManagementInterface";
    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "ProductManagementInterface", ServantName);
    pCORBA_Task->registerServant(m_pProductManagementInterface,ServantName);
    m_pProductManagementInterface->setProviderName(ServantName);

    ServantName    = ServerName + "PlantManagementInterface";
    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "PlantManagementInterface", ServantName);
    pCORBA_Task->registerServant(m_pPlantManagementInterface,ServantName);
    m_pPlantManagementInterface->setProviderName(ServantName);

  }

}


CDM_PlantManager* CDM_Task::getpPlantManager()
{
	return m_pPlantManager;
}

void CDM_Task::setpPlantManager(CDM_PlantManager* value)
{
	m_pPlantManager = value;
	return;
}

CDM_ProductManager* CDM_Task::getpProductManager()
{
	return m_pProductManager;
}

void CDM_Task::setpProductManager(CDM_ProductManager* value)
{
	m_pProductManager = value;
	return;
}


void CDM_Task::registerEventLogHandler(CDM_EventLogHandler *EventLogHandler)
{
  if (m_pEventLogHandlerAdapter)
  {
    m_pEventLogHandlerAdapter->registerEventLogHandler(EventLogHandler);	
  }
}



void CDM_Task::EventLog(CEventMessage& Event)
{
  if (m_pEventLogHandlerAdapter)
  {
    m_pEventLogHandlerAdapter->EventLog(Event);	
  }
	
}



void CDM_Task::copyDataFromProductToPlantInterface(const std::string& SourceKey, const std::string& DestKey, std::vector<std::string> DataList)
{
  std::stringstream ExceptionMsg;
  ExceptionMsg << "Handling event: " ;

  if ( m_pPlantManagementInterface && m_pProductManagementInterface )
  {
    try
    {
      CSMC_DataProvider_Impl::copyIntfData(m_pProductManagementInterface,
                                           m_pPlantManagementInterface,
                                           SourceKey,
                                           DestKey,
                                           DataList);

      m_pPlantManagementInterface->showContent(DestKey,4);
    }
    catch(CORBA::SystemException& sExc) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
                                           "CDM_Task::copyDataFromProductToPlantInterface",
                                            ExceptionMsg.str().c_str());
    }
    catch(CORBA::Exception& cExc) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
                                           "CDM_Task::copyDataFromProductToPlantInterface",
                                            ExceptionMsg.str().c_str());
    }
    catch(...) 
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,"",
                                           "CDM_Task::copyDataFromProductToPlantInterface",
                                            ExceptionMsg.str().c_str());
    }
  }
}


std::set<std::string> CDM_Task::getRuleSetNames(const std::string& Key)
{
  return m_Validator.getRuleSetNames(Key);
}

void CDM_Task::log(const std::string& Message, long Level)
{
  cCBS_StdFrame_Task::log(Message, Level);
}



void CDM_Task::sendInitialEvents()
{
}



bool CDM_Task::initialize()
{
	bool RetCode = CSMC_FrameTask::initialize();

	// initiliazes the DB interfaces
  initDBClasses();

	// initiliazes the external CORBA interfaces
  initCORBAInterfaces( );

  return RetCode;
}



void CDM_Task::doOnTaskWorkingError()
{

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ErrorTaskWorkingState(sMessage);
  
  setWorking(false);
}

void CDM_Task::doOnComponentStartup()
{
  sendInitialEvents();
}

// read customer data from database
bool CDM_Task::getCustData(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, std::string& HEATID_CUST, std::string& TREATID_CUST)
{
  bool RetValue = false;

  if ( m_pPD_HEAT_PLANT_REF )
  {
    RetValue = m_pPD_HEAT_PLANT_REF->getCustData(HEATID, TREATID, PLANT, HEATID_CUST, TREATID_CUST);
  }

  return RetValue;
}

std::string CDM_Task::getExternalHeatID(const std::string& ID)
{
  std::string RetValue;

  if ( m_pProductManagementInterface )
  {
    RetValue = m_pProductManagementInterface->getString(ID,DATA::CustHeatID);

    // do not return invalid!
    if (RetValue == DEF::Inv_String)
    {
      RetValue = "";
    }
  }

  return RetValue;
}

std::string CDM_Task::getExternalTreatID(const std::string& ID)
{
  std::string RetValue;

  if ( m_pProductManagementInterface )
  {
    RetValue = m_pProductManagementInterface->getString(ID,DATA::CustTreatID);

    // do not return invalid!
    if (RetValue == DEF::Inv_String)
    {
      RetValue = "";
    }
  }

  return RetValue;
}

sEventLogMessage CDM_Task::initEventLogMessage(const std::string& File, long Line, const std::string& ID)
{
  return cCBS_StdEventLog::initMessage(File,Line,getProcessState(ID),ID,getExternalHeatID(ID),getEventLogDestination(ID));
}

sEventLogMessage CDM_Task::initEventLogMessage(const std::string& File, long Line)
{
  return cCBS_StdEventLog::initMessage(File,Line);
}

long CDM_Task::getEventLogDestination(const std::string& ID)
{
  long RetValue = -1; // cCBS_StdEventLog is checking by > 0 

  if ( m_pProductManagementInterface )
  {
    // DATA::TreatmentPosition stored as long
    // using string only to select data from ini-file
    std::string TreatmentPosition = m_pProductManagementInterface->getString(ID,DATA::TreatmentPosition);

    // do not return invalid!
    if (TreatmentPosition != DEF::Inv_String)
    {
      long Destination = -1;
      if ( cCBS_StdInitBase::getInstance()->getValueOfListEntry("EVENTLOG","DestinationTreatPosList",TreatmentPosition,Destination) )
      {
        RetValue = Destination;
      }
    }
  }

  return RetValue;
}

// *****************************************************
// method may be overwritten in specialized task classes
// *****************************************************
bool CDM_Task::isProductInProduction(const std::string& HeatID, const std::string& TreatID, const std::string& PlantID, std::string& OrderId)
{
  log("++++++ CDM_Task::isProductInProduction",3);

  bool RetValue = false;

  if (m_pPD_HEAT_DATA && m_pPD_HEAT_REF && m_pGC_Plant_Container)
  {
    // first seperate Plant and PlantNo from PlantID
    std::string Plant = m_pGC_Plant_Container->getPlant(PlantID);
    long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantID);

    std::string Message;

    Message += "CDM_Task::isProductInProduction";
    Message += " checking " + HeatID + " " + TreatID + " " + PlantID;

    log(Message,3);

    //The row in PD_HEAT_DATA allows storing received data.
    //Therefore a product in tracking will be created.
    if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
    {
      for (int i = 1; i<=m_pPD_HEAT_DATA->getLastRow(); i++)
      {
        if ( m_pPD_HEAT_DATA->isNull(CPD_HEAT_DATA::HEATDEPARTURE_ACT, i) )
        {
          log("Heat " + m_pPD_HEAT_DATA->getHEATID(i) + " is still in production ",3);

          OrderId = m_pPD_HEAT_DATA->getPRODORDERID_ACT(i);

          RetValue = true;
          break;
        }
        else
        {
          log("Heat " + m_pPD_HEAT_DATA->getHEATID(i) + " is NOT longer in production ",2);
        }
      }

      if ( !RetValue )
      {
        std::string HeatID_Cust;
        std::string TreatID_Cust;

        getCustData(HeatID, TreatID, Plant, HeatID_Cust, TreatID_Cust);

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_HeatNotInProduction(sMessage,HeatID_Cust.c_str(),TreatID_Cust.c_str(),Plant.c_str());
      }
    }
    else
    {
      log("Heat not selected at database, heat is out of production or not known! ",2);
    }
  }
  else
  {
    log("DB classes not initialized!",1);
  }
  
  return RetValue;
}

bool CDM_Task::deleteDBClasses()
{
  bool RetValue = true;

  if ( m_pPD_HEAT_DATA )        { delete m_pPD_HEAT_DATA; m_pPD_HEAT_DATA = 0; }
  if ( m_pPD_HEAT_REF )         { delete m_pPD_HEAT_REF; m_pPD_HEAT_REF = 0; }
  if ( m_pPD_HEAT_PLANT_REF )   { delete m_pPD_HEAT_PLANT_REF; m_pPD_HEAT_PLANT_REF = 0; }
  if ( m_pGC_STATUS )           { delete m_pGC_STATUS; m_pGC_STATUS = 0; }
  if ( m_pGC_Plant_Container )  { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }

  return RetValue;
}

bool CDM_Task::initDBClasses()
{
  bool RetValue = false;

  cCBS_StdConnection * pConnection = getStdConnection();

  if ( pConnection )
  {
    m_pPD_HEAT_DATA         = new CPD_HEAT_DATA(pConnection);
    m_pPD_HEAT_REF          = new CPD_HEAT_REF(pConnection);
    m_pPD_HEAT_PLANT_REF    = new CPD_HEAT_PLANT_REF(pConnection);
    m_pGC_STATUS            = new CGC_STATUS(pConnection);
    m_pGC_Plant_Container   = new CGC_Plant_Container(pConnection);

    RetValue = true;
  }

  return RetValue;
}

bool CDM_Task::handleUnknownProduct(CEventMessage& Event, const std::string& CustHeatID, const std::string& CustTreatID, const std::string& PlantID)
{
  bool RetValue = false;

  return RetValue;
}


// method will be called by CDM_ProductManagementInterface (via virtual function calls in data provider)
// when ProcuctID == to datakey that will be deleted!
// This method has to be implemented in specific tasks
bool CDM_Task::doOnDeleteProductFromInterface(const std::string& ProductID)
{
  log("INFO: doOnDeleteProductFromInterface" + ProductID,1);
  bool RetValue = false;

  CEventMessage Message;

  std::string SenderName  = CEventMessage::getSenderName(getTaskName());

  Message.setProductID(ProductID);
  Message.setMessage(GEN_EvMsg::evGenRemoveTrackedProduct);
  Message.dispatch(SenderName,"");

  return RetValue;
}

bool CDM_Task::setProductData(CEventMessage& Event)
{
  bool RetValue = true;
  std::string ProductID = Event.getProductID();
  std::string HeatID    = Event.getHeatID();
  std::string TreatID   = Event.getTreatID();
  std::string PlantID   = Event.getPlantID();

  if ( m_pGC_Plant_Container )
  {
    cCBS_StdConnection * pConnection = getStdConnection();

    if ( pConnection )
    {
      // first seperate Plant and PlantNo from PlantID
      std::string Plant = m_pGC_Plant_Container->getPlant(PlantID);
      long PlantNo      = m_pGC_Plant_Container->getPlantNo(PlantID);

      // set external heat data
      if ( m_pPD_HEAT_PLANT_REF->select(HeatID, TreatID, Plant) )
      {
        m_pProductManagementInterface->setString(ProductID.c_str(), DATA::CustHeatID, m_pPD_HEAT_PLANT_REF->getHEATID_CUST(1));
        m_pProductManagementInterface->setString(ProductID.c_str(), DATA::CustTreatID, m_pPD_HEAT_PLANT_REF->getTREATID_CUST(1));
      }

      if ( m_pPD_HEAT_DATA->select(HeatID, TreatID, Plant) )
      {
        std::string Message;
        Message += "CDM_Task::setProductData";
        Message += " set data from data base for " + HeatID + " " + TreatID + " " + PlantID;
        log(Message,3);

        CDateTime HEATANNOUNCE  = m_pPD_HEAT_DATA->getHEATANNOUNCE_ACT(1);
        CDateTime TREATSTART    = m_pPD_HEAT_DATA->getTREATSTART_ACT(1);
        CDateTime HEATDEPARTURE = m_pPD_HEAT_DATA->getHEATDEPARTURE_ACT(1);
        std::string LadleType   = m_pPD_HEAT_DATA->getLADLETYPE(1);
        long LadleNo            = m_pPD_HEAT_DATA->getLADLENO(1);

        if ( m_pProductManager )
        {
          RetValue = m_pProductManager->setProductData(ProductID, LadleType, LadleNo, HEATANNOUNCE, HEATDEPARTURE, TREATSTART);
        }
      }

      /*****************************************************************************************************
      // for future use 
      CPD_ACTION    PD_ACTION (pConnection);
			if ( PD_ACTION.select(HeatID, TreatID, Plant, CSMC_DBData::unspecLong, CSMC_DBData::unspecDate) )
      {
        long R = PD_ACTION.getLastRow();

        for (int i = 1; i <= R; i++)
        {
          bool logMessage = true;
          long ActionNo = PD_ACTION.getACTIONNO(i);
          CDateTime RevTime = PD_ACTION.getREVTIME(i);

          CDateTime Now;
          Now.setDay(RevTime.getYear());
          Now.setMonth(RevTime.getMonth());
          Now.setDay(RevTime.getDay());
          Now.setHour(RevTime.getHour());
          Now.setMinute(RevTime.getMinute());
          Now.setSecond(RevTime.getSecond());
          Now.setMilliSecond(RevTime.getMilliSecond());
          
          Message = "Set data for " + ProductID + " ";

          if (logMessage)
          {
            Message += " " + Now.asString();
            log(Message,3);
          }
        }
      }
      else
      {
        log("No stored actions for selected heat!",2);
      }
      *****************************************************************************************************/

    }
    else
      log("No connection available",1);
  }
  
  return RetValue;
}

bool CDM_Task::setProductionPractice(CEventMessage& Event, std::string& Grade)
{
  log("CDM_Task::setProductionPractice: No implementation",2);
  return false;
}


std::string CDM_Task::getPlantFromEventMessage(CEventMessage& Event)
{
  std::string Plant = DEF::Inv_String;

  if ( m_pGC_Plant_Container )
  {
    Plant    = m_pGC_Plant_Container->getPlant(Event.getPlantID());
  }

  return Plant;
}

long CDM_Task::getPlantNoFromEventMessage(CEventMessage& Event)
{
  long PlantNo = DEF::Inv_Long;

  if ( m_pGC_Plant_Container )
  {
    PlantNo    = m_pGC_Plant_Container->getPlantNo(Event.getPlantID());
  }

  return PlantNo;
}

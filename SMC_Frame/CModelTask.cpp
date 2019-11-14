// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"

#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_Mutex.h"


#include "CEventMessage.h"
#include "CTreatID.h"
#include "CModelTask.h"


CModelTask::CModelTask() 
: m_ActTreatNo(0)
, m_pDM_Interface(0)
, m_pModelResults(0)
, m_pDMProxyManager(0)
, m_OfflineCalculationStatus(false)
{
}


CModelTask::~CModelTask()
{
}

DM::iDM_Interface_var& CModelTask::getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  try
  {
    m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);

    if (!m_pDM_Interface)
    {
      m_pDMProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
      m_pDM_Interface = m_pDMProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
    }
  }
  catch(...)
  {
    m_pDM_Interface = 0;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,
      "Getting CORBA Object ",
      "CModelTask::getpDM_Interface()",
      "getObjRefByServerName()");
  }

  if ( m_pDM_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }

  return m_pDM_Interface;
}

void CModelTask::initCORBAInterfaces()
{
  // Proxy names under "DataManager" in ini-file will be read 
  //and all object references to this proxies will be holed 
  //from nameservice.
  m_pDMProxyManager->registerProxies("DataManager");

  cCBS_StdCORBA_Task* pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

  // register CORBA interface
  if (pCORBA_Task)
  { 
    std::string ServantName = cCBS_StdInitBase::getInstance()->m_ServerName;
    ServantName += "ModelResultInterface";

    cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), "ServantName", ServantName);

    pCORBA_Task->registerServant(m_pModelResults,ServantName);
  }
}

const CDateTime& CModelTask::getActHeatAnnouncementTime(CEventMessage & Event) const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActHeatAnnouncementTime;
}

void CModelTask::setActHeatAnnouncementTime(sDate& value)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
 	m_ActHeatAnnouncementTime.SetTime(value);
}

const std::string& CModelTask::getActHeatID() const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActHeatID;
}

const std::string& CModelTask::getActHeatIDCust() const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActHeatIDCust;
}

const std::string& CModelTask::getActProductID() const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActProductID;
}

const std::string& CModelTask::getActTreatID() const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActTreatID;
}

const std::string& CModelTask::getActTreatIDCust() const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActTreatIDCust;
}

const long CModelTask::getActTreatNo(CEventMessage & Event) const
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_ActTreatNo;
}

bool CModelTask::initialize()
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");

  bool RetCode = CSMC_FrameTask::initialize();

  m_pDMProxyManager = new CProxyManager<DM::iDM_Interface>();

  //  init frame classes
  m_pModelResults = new CModelResults_Impl();

  initCORBAInterfaces();

  m_ProcessID = cCBS_StdInitBase::getInstance()->m_ServerName;

  std::string TaskName = getTaskName();

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "ServerName", m_ProcessID);

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ModelAvailable(sMessage,m_ProcessID.c_str());

  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "Plant", m_ActPlant);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "PlantNo", m_ActPlantNo);

  // overwrite by task entries
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "Plant", m_ActPlant);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName, "PlantNo", m_ActPlantNo);

  return RetCode;
}


bool CModelTask::getOfflineCalculationStatus(const std::string& ProductID )
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
	return m_OfflineCalculationStatus;
}

void CModelTask::setOfflineCalculationStatus(bool value)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  m_OfflineCalculationStatus = value;
}

CModelResults_Impl* CModelTask::getpModelResults()
{
  return m_pModelResults;
}

bool CModelTask::isAssignedProductID(const std::string& ProductID)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  bool RetValue = false;

  if ( !m_ActProductID.empty() && ProductID == m_ActProductID )
  {
    RetValue = true;
  }
  else
  {
    log(ProductID + " is not assigned to ProductID " + m_ActProductID,2);
  }

  return RetValue;
}

bool CModelTask::checkProductAssignment(CEventMessage& Event, bool OfflineCalculationStatus)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  bool RetValue = false;
  std::string AssignedData;
  std::string ProductID = Event.getProductID();

  std::string ProcessID = cCBS_StdInitBase::getInstance()->m_ServerName;

  cCBS_StdInitBase::getInstance()->replaceWithEntry(getTaskName(), 
                                                    "ServerName", 
                                                    ProcessID);

  std::string Action = "Reading DM interface data from ";
  Action +=  Event.getSender();
  Action +=  " - ";
  Action +=  ProductID;
  Action +=  " - ";
  Action +=  Event.getDataKey();
  Action += " - ";
  Action += ProcessID;

  try 
  {
    DM::iDM_Interface_var pDM_Interface;
    pDM_Interface = getpDM_Interface(Event.getSender(),CModelTask::PLANT);

    if (pDM_Interface)
    {
      // check if Event.ProductID of incoming event is equal to DATA::ProductID at DM
      // for actual ProcessID!

      AssignedData = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::ProductID));
      
      // valid data at DM found
      if ( AssignedData != DEF::Inv_String && 
           !AssignedData.empty() && 
           AssignedData == ProductID )
      {
        m_ActProductID              = ProductID;
        m_ActHeatID                 = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::HeatID));
        m_ActTreatID                = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::TreatID));
        m_ActTreatNo                = pDM_Interface->getLong(ProcessID.c_str(),DATA::TreatNo);

        if ( m_ActTreatNo == DEF::Inv_Long )
        {
          CTreatID NewTreatID;
          m_ActTreatNo = NewTreatID.getCounter(m_ActTreatID);
        }

        m_ActOrderID                = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::OrderId));
        m_OfflineCalculationStatus  = OfflineCalculationStatus;
        
        m_ActHeatIDCust             = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::CustHeatID));
        m_ActTreatIDCust            = CIntfData::ToStdString(pDM_Interface->getString(ProcessID.c_str(),DATA::CustTreatID)); 

        RetValue = true;
      }
      else if ( AssignedData == "" || AssignedData == DEF::Inv_String )
      {
        // deassign Product 
        m_ActProductID              = "";
        m_ActHeatID                 = "";
        m_ActTreatID                = "";
        m_ActTreatNo                = DEF::Inv_Long;
        m_ActOrderID                = "";

        m_OfflineCalculationStatus  = OfflineCalculationStatus;
        
        m_ActHeatIDCust             = "";
        m_ActTreatIDCust            = "";
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaSystemException(sExc,
                                                                "CModelTask::checkProductAssignment",
                                                                Action);
  }
  catch(CORBA::Exception& cExc) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnCorbaException(cExc,
                                                          "CModelTask::checkProductAssignment",
                                                          Action);
  }
  catch(...) 
  {
    cCBS_StdCORBA_Task::getInstance()->doOnException("CModelTask::checkProductAssignment",
                                                     Action);
  }

  return RetValue;
}

std::string CModelTask::getActProcessData(const std::string& ID)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");

  std::string RetValue = DEF::Inv_String;
  std::map<std::string,std::string>::iterator it;

  it = ActProcessDataList.find(ID);

  if ( it != ActProcessDataList.end() )
  {
    RetValue = it->second;
  }

  return RetValue;
}

void CModelTask::setActProcessData(const std::string& ID, const std::string& Value)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");

  std::string RetValue = DEF::Inv_String;
  std::map<std::string,std::string>::iterator it;

  it = ActProcessDataList.find(ID);

  if ( it != ActProcessDataList.end() )
  {
    it->second = Value;
  }
  else
  {
    ActProcessDataList.insert(std::pair<std::string,std::string>(ID,Value));
  }
}

std::string CModelTask::getPlantEquipment(const std::string& Value)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");

  std::string RetValue = DEF::Inv_String;
  std::map<std::string,std::string>::iterator it;

  for ( it = PlantEquipmentList.begin() ; it != PlantEquipmentList.end() ; ++it)
  {
    if ( it->second == Value ) 
    {
      RetValue = it->first;
      break;
    }
  }

  return RetValue;
}

void CModelTask::setPlantEquipment(const std::string& Equipment, const std::string& Value)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  PlantEquipmentList.insert(std::pair<std::string,std::string>(Equipment,Value));
}

const std::string& CModelTask::getActOrderID()
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  return m_ActOrderID;
}

void CModelTask::cleanProductData()
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");

  std::cout << "Clean product data." << __FILE__ << __LINE__ << std::endl;

  m_ActProductID.clear();
  m_ActHeatID.clear();
  m_ActTreatID.clear();
  m_ActHeatIDCust.clear();
  m_ActTreatIDCust.clear();
  m_ActOrderID.clear();
  m_ActTreatNo = -1;
}

const std::string& CModelTask::getActPlant()
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  return m_ActPlant;
}

long CModelTask::getActPlantNo()
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  return m_ActPlantNo;
}

void CModelTask::log(const std::string& Message, long Level)
{
	cCBS_StdFrame_Task::log(Message, Level);
}



void CModelTask::setActHeatIDCust(const std::string& ActHeatIDCust)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  m_ActHeatIDCust = ActHeatIDCust;
}

void CModelTask::setActTreatIDCust(const std::string& ActTreatIDCust)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  m_ActTreatIDCust = ActTreatIDCust;
}

void CModelTask::setActOrderID(const std::string& ActOrderID)
{
  CSMC_Mutex Mutex("CModelTask::CModelTask");
  m_ActOrderID = ActOrderID;
}

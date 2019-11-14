// Copyright (C) 2004 SMS Demag AG

#include "CEventMessage.h"
#include "CTsmBaseApplication.h"
#include "CMsg.h"
#include "cCBS_StdLogMsgPort.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdLog_Task.h"
#include "CTSM_Task.h"

CTSM_Task::CTSM_Task()
: m_pDM_Interface(0)
, m_pEventTask(0)
, m_pTsmApplication(0)
{
}

CTSM_Task::~CTSM_Task()
{
  delete m_pDM_ProxyManager;
}

void CTSM_Task::log(const std::string& Message, long Level)
{
	cCBS_StdFrame_Task::log(Message, Level);
}

DM::iDM_Interface_var& CTSM_Task::getpDM_Interface(const std::string& ServerName, const std::string& InterfaceTypeName)
{
  m_pDM_Interface = 0;

  if (m_pDM_ProxyManager)
  {
    try
    {
      m_pDM_Interface = m_pDM_ProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);

      if (!m_pDM_Interface)
      {
        m_pDM_ProxyManager->handleConnectionErrorByServerName(ServerName,InterfaceTypeName);
        m_pDM_Interface = m_pDM_ProxyManager->getObjRefByServerName(ServerName,InterfaceTypeName);
      }
    }
    catch(...)
    {
      m_pDM_Interface = 0;

      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage,
        "Getting CORBA Object ",
        "CTSM_Task::getpDM_Interface()",
        "getObjRef()");
    }
  } // if (m_pDM_ProxyManager)

  if ( m_pDM_Interface == 0 )
  {
    throw CORBA::INV_OBJREF ();
  }

  return m_pDM_Interface;
}

bool CTSM_Task::initialize()
{
	bool RetCode = CSMC_FrameTask::initialize();

  CMsg::addMsgPort("CBS_StdLogMsgPort",new cCBS_StdLogMsgPort);

  m_pDM_ProxyManager = new CProxyManager<DM::iDM_Interface>();
  m_pDM_ProxyManager->registerProxies("DataManager");

  m_pEventTask = cCBS_StdEvent_Task::getInstance();

  return RetCode;
}
CTsmBaseApplication* CTSM_Task::getpTsmApplication() const
{
  return m_pTsmApplication.get();
}


void CTSM_Task::getEventReceiverNames(std::vector<std::string>& EventReceiverNames, const std::string & EventReceiverName)
{
  std::vector<std::string> ReceiverNames;

  // inifile may be of content
  // [NAMECONVERSION]
  // ReceiverNames = MODEL, TSM
  // MODEL = MODEL_11, MODEL_12
  // TSM = TSM_1

  // try to find entry for ReceiverName defintions at inifile
  if ( cCBS_StdInitBase::getInstance()->getEntryList("NAMECONVERSION","ReceiverNames",ReceiverNames) )
  {
    std::vector<std::string>::iterator it;

    // try to detect EventReceiverName at entry list
    for ( it = ReceiverNames.begin(); it != ReceiverNames.end(); ++it)
    {
      // does list entry fit to event.Receiver ??
      if ( EventReceiverName == (*it) )
      {
        std::vector<std::string> NewReceiverNames;

        // is NewReceiverName defined at inifile ?
        if ( cCBS_StdInitBase::getInstance()->getEntryList("NAMECONVERSION", EventReceiverName, EventReceiverNames) )
        {
          std::stringstream Message;
          Message << "Using new EventReceiverName(s) for " << EventReceiverName ;
          cCBS_StdLog_Task::getInstance()->log(Message.str(),2);

          break;
        }
      }
    } // for ( it = ReceiverNames.begin(); it != ReceiverNames.end(); ++it)

    // insert the original value, if nothing else have been found
    if (EventReceiverNames.empty())
    {
      EventReceiverNames.push_back(EventReceiverName);
    }

  } // if ( cCBS_StdInitBase::getInstance()->getEntryList("TSM","ReceiverName",ReceiverNames) )
  else
  {
    EventReceiverNames.push_back(EventReceiverName);
  }
}


void CTSM_Task::changeEventTransmitterName(CEventMessage& evMessage)
{
  std::vector<std::string> TransmitterNames;

  // try to find entry for TransmitterName defintions at inifile
  if ( cCBS_StdInitBase::getInstance()->getEntryList("NAMECONVERSION","TransmitterNames",TransmitterNames) )
  {
    std::string TransmitterName = evMessage.getSender();
    std::vector<std::string>::iterator it;

    // try to detect TransmitterName at entry list
    for ( it = TransmitterNames.begin(); it != TransmitterNames.end(); ++it)
    {
      // does list entry fit to event.sender ??
      if ( TransmitterName == (*it) )
      {
        // is new TransmitterName defined at inifile ?
        if ( cCBS_StdInitBase::getInstance()->replaceWithEntry("NAMECONVERSION", (*it), TransmitterName) )
        {
          std::string OldTransmitterName;
          OldTransmitterName = evMessage.getSender();

          // set new TransmitterName for internal use at TSM 
          evMessage.setSender(TransmitterName);

          std::stringstream Message;
          Message << "Using new EventTransmitterName for internal use in TSM ";
          Message << "Changed from " << OldTransmitterName << " to "<< TransmitterName;
          cCBS_StdLog_Task::getInstance()->log(Message.str(),2);

          break;
        }
      }
    } // for ( it = TransmitterNames.begin(); it != TransmitterNames.end(); ++it)
  } // if ( cCBS_StdInitBase::getInstance()->getEntryList("TSM","TransmitterName",SenderNameList) )
}


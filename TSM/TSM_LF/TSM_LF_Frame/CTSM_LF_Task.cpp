// Copyright (C) 2004 SMS Demag AG

#include "CTSM_LF_StateMachineConstructCtrl.h"
#include "CEmptyPlantConstructCtrl.h"
#include "CTsmFileLoggingDatabase.h"
#include "CTsmObjectCreator.h"
#include "CTsmBaseApplication.h"
#include "CTSM_LF_EventHandler.h"

#include "CTSM_LF_Task.h"

CTSM_LF_Task* CTSM_LF_Task::Instance = 0;

CTSM_LF_Task::CTSM_LF_Task()
: m_pEventHandler(0)
{
}

CTSM_LF_Task::~CTSM_LF_Task()
{
 delete m_pEventHandler;
}

CTSM_LF_Task* CTSM_LF_Task::getInstance()
{
	if ( Instance == 0 )
	{
		Instance = new CTSM_LF_Task();
	}
  return Instance;
}

bool CTSM_LF_Task::initialize()
{
  CTSM_Task::initialize();

  m_pEventHandler = new CTSM_LF_EventHandler();
  //setting task pointer and call initCommunication() to read 
  //SenderName
  //ReceiverName
  //DestinationName
  m_pEventHandler->setpTask(this);

  m_pEventTask->registerEventHandler(m_pEventHandler);

  std::string receiverName(m_pEventHandler->getReceiverName());

  std::auto_ptr<CTsmBaseApplication> t(new CTsmBaseApplication(new CTsmFileLoggingDatabase(this->getTaskName()),
                                              new CTSM_LF_StateMachineConstructCtrl, 
                                              new CEmptyPlantConstructCtrl, 
                                              new CTsmObjectCreator,
                                              receiverName));

  m_pTsmApplication = t;
  m_pEventHandler->connectToTsmApplication(m_pTsmApplication.get());

  // Create devices
  std::vector<std::string> v;
  std::vector<std::string>::const_iterator vi;
  cCBS_StdInitBase::getInstance()->getEntryList("DEVICE", "DeviceName", v);
  for (vi = v.begin(); vi != v.end(); ++vi)
  {
    std::string msg("LF_CREATE_DEVICE_" + *vi);
    CEventMessage ev(receiverName, receiverName, msg, *vi, "", false);
    m_pTsmApplication->doAddProduct(ev);
    m_pTsmApplication->doHandleProductEvent(ev);
  }
  return true;
}

CTSM_LF_EventHandler* CTSM_LF_Task::getEventHandler()
{
  return m_pEventHandler;
}

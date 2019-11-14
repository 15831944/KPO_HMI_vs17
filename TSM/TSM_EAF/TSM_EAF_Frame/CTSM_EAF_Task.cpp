// Copyright (C) 2004 SMS Demag AG

#include "CTSM_EAF_StateMachineConstructCtrl.h"
#include "CEmptyPlantConstructCtrl.h"
#include "CTsmFileLoggingDatabase.h"
#include "CTsmObjectCreator.h"
#include "CTsmBaseApplication.h"
#include "CTSM_EAF_EventHandler.h"

#include "CTSM_EAF_Task.h"

CTSM_EAF_Task* CTSM_EAF_Task::Instance = 0;

CTSM_EAF_Task::CTSM_EAF_Task()
: m_pEventHandler(0)
{
}

CTSM_EAF_Task::~CTSM_EAF_Task()
{
 delete m_pEventHandler;
}

CTSM_EAF_Task* CTSM_EAF_Task::getInstance()
{
	if ( Instance == 0 )
	{
		Instance = new CTSM_EAF_Task();
	}
  return Instance;
}

bool CTSM_EAF_Task::initialize()
{
  CTSM_Task::initialize();

  m_pEventHandler = new CTSM_EAF_EventHandler();
  m_pEventHandler->setpTask(this);

  m_pEventTask->registerEventHandler(m_pEventHandler);

  std::string receiverName(m_pEventHandler->getReceiverName());

	std::auto_ptr<CTsmBaseApplication> t(new CTsmBaseApplication(new CTsmFileLoggingDatabase(this->getTaskName()),
                                              new CTSM_EAF_StateMachineConstructCtrl, 
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
    std::string msg("EAF_CREATE_DEVICE_" + *vi);
    CEventMessage ev(receiverName, receiverName, msg, *vi, "", false);
    m_pTsmApplication->doAddProduct(ev);
    m_pTsmApplication->doHandleProductEvent(ev);
  }
  return true;
}
  
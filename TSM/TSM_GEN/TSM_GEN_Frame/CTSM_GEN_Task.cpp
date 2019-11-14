// Copyright (C) 2004 SMS Demag AG

#include "CTSM_GEN_StateMachineConstructCtrl.h"
#include "CEmptyPlantConstructCtrl.h"
#include "CTsmFileLoggingDatabase.h"
#include "CTsmObjectCreator.h"
#include "CTsmBaseApplication.h"
#include "CTSM_GEN_EventHandler.h"

#include "CTSM_GEN_Task.h"

CTSM_GEN_Task* CTSM_GEN_Task::Instance = 0;

CTSM_GEN_Task::CTSM_GEN_Task()
: m_pEventHandler(0)
{
}

CTSM_GEN_Task::~CTSM_GEN_Task()
{
 delete m_pEventHandler;
}

CTSM_GEN_Task* CTSM_GEN_Task::getInstance()
{
	if ( Instance == 0 )
	{
		Instance = new CTSM_GEN_Task();
	}
  return Instance;
}

bool CTSM_GEN_Task::initialize()
{
  CTSM_Task::initialize();
	
  m_pEventHandler = new CTSM_GEN_EventHandler();
  m_pEventHandler->setpTask(this);

  m_pEventTask->registerEventHandler(m_pEventHandler);


  std::string receiverName(m_pEventHandler->getReceiverName());

  std::auto_ptr<CTsmBaseApplication> t(new CTsmBaseApplication(new CTsmFileLoggingDatabase,
                                            new CTSM_GEN_StateMachineConstructCtrl, 
                                            new CEmptyPlantConstructCtrl, 
                                            new CTsmObjectCreator,
                                            receiverName));

  m_pTsmApplication = t;
  m_pEventHandler->connectToTsmApplication(m_pTsmApplication.get());


  // The idea of the following code is to use TSM for tracking of 
  // different plants. In this case plants are used as persistent products.
  // This is experimental step.
  CEventMessage evMessage;

  std::vector<std::string> plants;
  std::vector<std::string>::iterator it;
  cCBS_StdInitBase::getInstance()->getEntryList("TSM_PLANTS", "Plants", plants);

  for ( it = plants.begin(); it != plants.end(); ++it )
  {
    evMessage.setProductID(*it);
    m_pTsmApplication->doAddProduct(evMessage);
  }

  return true;
}

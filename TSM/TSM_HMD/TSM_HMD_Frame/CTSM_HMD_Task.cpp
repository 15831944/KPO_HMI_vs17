// Copyright (C) 2007 SMS Demag AG

#include "CTSM_HMD_StateMachineConstructCtrl.h"
#include "CEmptyPlantConstructCtrl.h"
#include "CTsmFileLoggingDatabase.h"
#include "CTsmObjectCreator.h"
#include "CTsmBaseApplication.h"
#include "CTSM_HMD_EventHandler.h"

#include "CTSM_HMD_Task.h"

//##ModelId=45A21EBB0220
CTSM_HMD_Task* CTSM_HMD_Task::Instance  ;

//##ModelId=45A21E8D028E
CTSM_HMD_Task::CTSM_HMD_Task()
: m_pEventHandler(0)
{
}

//##ModelId=45A21E8D020B
CTSM_HMD_Task::~CTSM_HMD_Task()
{
 delete m_pEventHandler;
}

//##ModelId=45A21E8D0180
void CTSM_HMD_Task::getOwnStateDetails(CORBA::String_out details)
{
  details = CORBA::string_dup("CTSM_HMD_Task!");
}

//##ModelId=45A21E8D023E
CTSM_HMD_Task* CTSM_HMD_Task::getInstance()
{
	if ( Instance == 0 )
	{
		Instance = new CTSM_HMD_Task();
	}
  return Instance;
}

//##ModelId=45A21E8D027A
bool CTSM_HMD_Task::initialize()
{
  CTSM_Task::initialize();

  m_pEventHandler = new CTSM_HMD_EventHandler();
  //setting task pointer and call initCommunication() to read 
  //SenderName
  //ReceiverName
  //DestinationName
  m_pEventHandler->setpTask(this);

  m_pEventTask->registerEventHandler(m_pEventHandler);

  std::string receiverName(m_pEventHandler->getReceiverName());

	std::auto_ptr<CTsmBaseApplication> t(new CTsmBaseApplication(new CTsmFileLoggingDatabase,
                                              new CTSM_HMD_StateMachineConstructCtrl, 
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
    std::string msg("HMD_CREATE_DEVICE_" + *vi);
    CEventMessage ev(receiverName, receiverName, msg, *vi, "", false);
    m_pTsmApplication->doAddProduct(ev);
    m_pTsmApplication->doHandleProductEvent(ev);
  }
  return true;
}

CTSM_HMD_EventHandler* CTSM_HMD_Task::getEventHandler()
{
  return m_pEventHandler;
}

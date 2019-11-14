// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_ORB.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "cCBS_StdInitBase.h"
#include <sstream>

#include "cCBS_StdCORBA_Task.h"

cCBS_StdCORBA_Task::~cCBS_StdCORBA_Task()
{
}

cCBS_StdCORBA_Task::cCBS_StdCORBA_Task()
: m_pCBS_StdCORBA_ServerTask(0), m_pCBS_StdCORBA_ClientTask(0)
{
  // instantiation of CBS Tasks
  m_pCBS_StdCORBA_ServerTask = new cCBS_StdCORBA_ServerTask();

  m_pCBS_StdCORBA_ClientTask = new cCBS_StdCORBA_ClientTask();

}

bool cCBS_StdCORBA_Task::initialize()
{
  std::string TaskName = std::string(getTaskName()) + "CorbaServerTask";

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"TaskName",TaskName);

  registerSubTask(m_pCBS_StdCORBA_ServerTask, TaskName);


  TaskName = std::string(getTaskName()) + "CorbaClientTask";

  cCBS_StdInitBase::getInstance()->replaceWithEntry(TaskName,"TaskName",TaskName);

  registerSubTask(m_pCBS_StdCORBA_ClientTask, TaskName);


  return cCBS_StdFrame_Task::initialize();
}


cCBS_CorbaServant* cCBS_StdCORBA_Task::registerServant(PortableServer::ServantBase* pServant, const std::string  &ServantName )
{
  cCBS_CorbaServant* pCorbaServant = 0;

  try
  {
    pCorbaServant = m_pCBS_StdCORBA_ServerTask->registerServant(pServant,ServantName.c_str());
  }
  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_Task::registerServant()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_Task::registerServant()","");
  }
  catch (const cCBS_Exception &e)
	{
    std::stringstream Message;
    Message << e;

    doOnException("cCBS_StdCORBA_Task::registerServant()",Message.str());
  }
  catch(...) 
  {
    doOnException("cCBS_StdCORBA_Task::registerServant()","");
  }

  return pCorbaServant;
}

void cCBS_StdCORBA_Task::afterSubtaskStart()
{
  if ( m_pCBS_StdCORBA_ServerTask )
  {
    m_pCBS_StdCORBA_ServerTask->activateAllServants();
  }
  if ( m_pCBS_StdCORBA_ClientTask )
  {
    m_pCBS_StdCORBA_ClientTask->connectAllProxies();
  }
}

//##ModelId=426632CD0166
void cCBS_StdCORBA_Task::beforeSubtaskEnd()
{
  if ( m_pCBS_StdCORBA_ServerTask )
  {
    m_pCBS_StdCORBA_ServerTask->deactivateAllServants();
  }
  if ( m_pCBS_StdCORBA_ClientTask )
  {
    m_pCBS_StdCORBA_ClientTask->disconnectAllProxies();
  }
}


void cCBS_StdCORBA_Task::registerProxy(cCBS_ProxyBase* pCBS_ProxyBase, const std::string  &ServantName, const std::string  &ServerTask, const std::string  &ServerTaskPOA)
{
  log("cCBS_StdCORBA_Task: registerProxy()",3);

  if ( m_pCBS_StdCORBA_ClientTask )
  {
    m_pCBS_StdCORBA_ClientTask->registerProxy(pCBS_ProxyBase, ServantName, ServerTask, ServerTaskPOA);
    
    //m_pCBS_StdCORBA_ClientTask->connectProxy(ServantName, true);
  }
}

//##ModelId=40EAA09301ED
cCBS_StdCORBA_Task* cCBS_StdCORBA_Task::m_Instance = 0;

 cCBS_StdCORBA_Task* cCBS_StdCORBA_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new cCBS_StdCORBA_Task( );
	}

	return m_Instance;
}



cCBS_ProxyBase* cCBS_StdCORBA_Task::getCorbaProxy(const std::string & proxyName)
{
  cCBS_ProxyBase* pCBS_ProxyBase = 0;

  pCBS_ProxyBase = m_pCBS_StdCORBA_ClientTask->getCorbaProxy(proxyName.c_str());

  return pCBS_ProxyBase;
} // getProxy


void cCBS_StdCORBA_Task::log(const std::string & Message, long Level)
{
  cCBS_StdFrame_Task::log(Message, Level);
}



void cCBS_StdCORBA_Task::doOnCorbaException(CORBA::Exception& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}

void cCBS_StdCORBA_Task::doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}


void cCBS_StdCORBA_Task::connectProxy(const std::string& ServantName, bool reconnect  )
{
  log("cCBS_StdCORBA_Task: connectProxy()",3);

  if ( m_pCBS_StdCORBA_ClientTask )
  {
    m_pCBS_StdCORBA_ClientTask->connectProxy(ServantName, reconnect);
  }
}

void cCBS_StdCORBA_Task::doOnThreadControlError()
{
	cCBS_StdFrame_Task::doOnThreadControlError();
}

cCBS_Corba cCBS_StdCORBA_Task::getClientCorbaSettings()
{
  cCBS_Corba CorbaSettings;

  if ( m_pCBS_StdCORBA_ClientTask )
  {
    CorbaSettings = m_pCBS_StdCORBA_ClientTask->getCorbaSettings();
  }

  return CorbaSettings;
}

cCBS_Corba cCBS_StdCORBA_Task::getServerCorbaSettings()
{
  cCBS_Corba CorbaSettings;

  if ( m_pCBS_StdCORBA_ServerTask )
  {
    CorbaSettings = m_pCBS_StdCORBA_ServerTask->getCorbaSettings();
  }

  return CorbaSettings;
}

iCBS_Component_var cCBS_StdCORBA_Task::getComponent(const std::string& componentName)
{
  iCBS_Component_var comp;
  try
  {          
    std::string ProjectName;
    cCBS_StdInitBase::getInstance()->replaceWithEntry("PROJECT","Name",ProjectName);

    CORBA::Object_var obj = cCBS_ORB::getObjectReference(ProjectName.c_str(),
                                                         componentName.c_str(),
                                                         "CBS_Component");
    comp = iCBS_Component::_narrow(obj);
  }
  catch(...)
  {
  }
  return comp;
}



iCBS_Task_var cCBS_StdCORBA_Task::getTask(const std::string& taskName)
{
  iCBS_Task_var task;
  try
  {
    std::string ProjectName;
    cCBS_StdInitBase::getInstance()->replaceWithEntry("PROJECT","Name",ProjectName);

    CORBA::Object_var obj = cCBS_ORB::getObjectReference(ProjectName.c_str(),
                                                         taskName.c_str(),
                                                         "CBS_Task");
    task = iCBS_Task::_narrow(obj);
  }
  catch(...)
  {
  }
  return task;
}

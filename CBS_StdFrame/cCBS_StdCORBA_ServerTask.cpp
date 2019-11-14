// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdFrame_Component.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"

#include "cCBS_StdInitBase.h"
#include <sstream>

#include "cCBS_StdCORBA_ServerTask.h"

cCBS_StdCORBA_ServerTask::~cCBS_StdCORBA_ServerTask()
{
}

cCBS_StdCORBA_ServerTask::cCBS_StdCORBA_ServerTask()
{
  // setting standard names for communication
  m_CorbaServerTaskName     = cCBS_StdInitBase::getInstance()->m_ServerName;
  m_CorbaServerTaskPOA      = cCBS_StdInitBase::getInstance()->m_ProjectName;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("CORBA", "ServerTask", m_CorbaServerTaskName);

  bool UseProjectPOA = true;
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry("CORBA", "UseProjectPOA", UseProjectPOA);

  if ( !UseProjectPOA )
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry("CORBA", "ServerTaskPOA", m_CorbaServerTaskPOA);
  }

  // get CORBA options
  cCBS_Corba corbaModifier = getCorbaOptions();

  // create a portable object adapter
  m_corbaApplServer.newPOA(m_CorbaServerTaskPOA.c_str(), corbaModifier);

  // setting members
  m_pCorbaServer = &m_corbaApplServer;
}

bool cCBS_StdCORBA_ServerTask::initialize()
{
  return cCBS_StdCorbaServerTask::initialize();
}


cCBS_CorbaServant* cCBS_StdCORBA_ServerTask::registerServant(PortableServer::ServantBase* pServant, const std::string  &ServantName )
{
  cCBS_CorbaServant * pCBS_CorbaServant = 0;

  if ( m_pCorbaServer )
  {
    std::string Message("cCBS_StdCORBA_ServerTask::registerServant() :");
    Message += ServantName;
    Message += " at " ;
    Message += getCorbaServerTaskName();
    Message += "-" ;
    Message += getCorbaServerTaskPOA();
    log(Message,3);

    // calling base class function
    pCBS_CorbaServant = cCBS_StdCorbaServerTask::registerServant(ServantName.c_str(), pServant, m_CorbaServerTaskPOA.c_str());
  }

  return pCBS_CorbaServant;
}



void cCBS_StdCORBA_ServerTask::activateAllServants()
{
  log("cCBS_StdCORBA_ServerTask: activateAllServants()",3);
 
  try
  {
    // activate POA -> servant is ready
    if ( m_pCorbaServer )
    {
      m_pCorbaServer->activateAllPOAs();
    }
  }

  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_ServerTask::activateAllServants()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_ServerTask::activateAllServants()","");
  }

  catch(...) 
  {
    doOnException("cCBS_StdCORBA_ServerTask::activateAllServants()","");
  }
}

cCBS_Corba cCBS_StdCORBA_ServerTask::getCorbaOptions()
{
	cCBS_Corba corbaModifier(cCBS_Corba::CATCH_CORBA_SYSTEM_EXCEPTIONS |
		    					          cCBS_Corba::USE_CORBA_NAME_SERVICE |
			    				          cCBS_Corba::AUTO_REBIND);

  return corbaModifier;
}



void cCBS_StdCORBA_ServerTask::log(const std::string & Message, long Level)
{
  cCBS_StdCORBA_Task::getInstance()->log(Message, Level);
}



void cCBS_StdCORBA_ServerTask::doOnCorbaException(CORBA::Exception& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}

void cCBS_StdCORBA_ServerTask::doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}

void cCBS_StdCORBA_ServerTask::doOnException(const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,"",Function.c_str(),Action.c_str());
}



void cCBS_StdCORBA_ServerTask::deactivateAllServants()
{
  log("cCBS_StdCORBA_ServerTask: deactivateAllServants()",3);
 
  try
  {
    // deactivate POA -> servant is ready
    if ( m_pCorbaServer )
    {
      m_pCorbaServer->deactivateAllPOAs();
    }
  }

  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_ServerTask::deactivateAllServants()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_ServerTask::deactivateAllServants()","");
  }

  catch(...) 
  {
    doOnException("cCBS_StdCORBA_ServerTask::deactivateAllServants()","");
  }
	
}

std::string cCBS_StdCORBA_ServerTask::getCorbaServerTaskName()
{
	return m_CorbaServerTaskName;
}

std::string cCBS_StdCORBA_ServerTask::getCorbaServerTaskPOA()
{
	return m_CorbaServerTaskPOA;
}

cCBS_Corba cCBS_StdCORBA_ServerTask::getCorbaSettings()
{
  return m_CorbaModifier;
}

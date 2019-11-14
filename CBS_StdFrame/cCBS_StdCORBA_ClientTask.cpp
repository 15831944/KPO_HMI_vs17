// Copyright (C) 2011 SMS Siemag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdCORBA_ClientTask.h"

//##ModelId=40EAA09301D2
cCBS_StdCORBA_ClientTask::~cCBS_StdCORBA_ClientTask()
{
}

//##ModelId=40EAA09301D5
cCBS_StdCORBA_ClientTask::cCBS_StdCORBA_ClientTask()
{
}

bool cCBS_StdCORBA_ClientTask::initialize()
{
  return cCBS_StdCorbaClientTask::initialize();
}


//##ModelId=40EAA09301E2
void cCBS_StdCORBA_ClientTask::registerProxy(cCBS_ProxyBase* pCBS_ProxyBase, const std::string  &ServantName, const std::string  &ServerTask, const std::string  &ServerTaskPOA)
{
  log("cCBS_StdCORBA_ClientTask: registerProxy()",3);

  if ( pCBS_ProxyBase )
  {
    // Takes over the proxies
    std::map<std::string, cCBS_ProxyBase*>::iterator it;

    it = m_ProxyList.find(ServantName);

    if ( it == m_ProxyList.end() )
    {
      pCBS_ProxyBase->setModifier(m_CorbaModifier);

      m_ProxyList.insert( std::pair<std::string,cCBS_ProxyBase*>(ServantName,pCBS_ProxyBase));
    }
  }
}



//##ModelId=40EAA09301E8
void cCBS_StdCORBA_ClientTask::connectAllProxies()
{
  log("cCBS_StdCORBA_ClientTask: connectAllProxies()",3);

  try
  {
    std::map<std::string, cCBS_ProxyBase*>::iterator it;

    for ( it = m_ProxyList.end(); it != m_ProxyList.end(); ++it )
    {
      cCBS_ProxyBase* pCBS_ProxyBase = it->second;
    
      // Binds the proxy
      if ( pCBS_ProxyBase )
      {
        if ( !pCBS_ProxyBase->isBound() )
        {
          pCBS_ProxyBase->bind();
        }
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_ClientTask::connectAllProxies()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_ClientTask::connectAllProxies()","");
  }

  catch(...) 
  {
    doOnException("cCBS_StdCORBA_ClientTask::connectAllProxies()","");
  }
  
}

// getProxy from internal list
cCBS_ProxyBase* cCBS_StdCORBA_ClientTask::getCorbaProxy(const std::string & proxyName)
{
  cCBS_ProxyBase* pCBS_ProxyBase = 0;

  std::map<std::string, cCBS_ProxyBase*>::iterator it;

  it = m_ProxyList.find(proxyName);

  if ( it != m_ProxyList.end() )
  {
    pCBS_ProxyBase = it->second;
  }

  return pCBS_ProxyBase;
} 

//##ModelId=41499C9801D4
void cCBS_StdCORBA_ClientTask::log(const std::string & Message, long Level)
{
  cCBS_StdCORBA_Task::getInstance()->log(Message, Level);
}

//##ModelId=41E28CE40316
void cCBS_StdCORBA_ClientTask::connectProxy(const std::string& ServantName, bool reconnect  )
{
  log("cCBS_StdCORBA_ClientTask: connectProxy()",3);

  try
  {
    cCBS_ProxyBase* pCBS_ProxyBase = getCorbaProxy(ServantName);
    
    // Binds the proxy
    if ( pCBS_ProxyBase )
    {
      if ( pCBS_ProxyBase->isBound() )
      {
        if(reconnect)
        {
          pCBS_ProxyBase->resetProxy();
          pCBS_ProxyBase->bind();
        }
      }
      else
      {
        pCBS_ProxyBase->bind();
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_ClientTask::connectProxy()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_ClientTask::connectProxy()","");
  }
  catch (cCBS_App_ExcCorbaSystem& cExc)
  {
    cCBS_ExceptionInfo anInfo;
    cExc.getInfo(anInfo, 0);
    doOnException(anInfo.getModuleName(), anInfo.getExcMessage());
  }
  catch(...) 
  {
    doOnException("cCBS_StdCORBA_ClientTask::connectProxy()","");
  }
  
}

//##ModelId=426638ED0355
void cCBS_StdCORBA_ClientTask::disconnectAllProxies()
{
  log("cCBS_StdCORBA_ClientTask: disconnectAllProxies()",3);

  try
  {
    std::map<std::string, cCBS_ProxyBase*>::iterator it;

    for ( it = m_ProxyList.end(); it != m_ProxyList.end(); ++it )
    {
      cCBS_ProxyBase* pCBS_ProxyBase = it->second;
    
      // Binds the proxy
      if ( pCBS_ProxyBase )
      {
        pCBS_ProxyBase->stop();
      }
    }
  }
  catch(CORBA::SystemException& sExc) 
  {
    doOnCorbaSystemException(sExc,"cCBS_StdCORBA_ClientTask::disconnectAllProxies()","");
  }

  catch(CORBA::Exception& cExc) 
  {
    doOnCorbaException(cExc,"cCBS_StdCORBA_ClientTask::disconnectAllProxies()","");
  }

  catch(...) 
  {
    doOnException("cCBS_StdCORBA_ClientTask::disconnectAllProxies()","");
  }
}

cCBS_Corba cCBS_StdCORBA_ClientTask::getCorbaSettings()
{
  return m_CorbaModifier;
}

void cCBS_StdCORBA_ClientTask::doOnCorbaException(CORBA::Exception& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}

//##ModelId=4253E8A0030D
void cCBS_StdCORBA_ClientTask::doOnCorbaSystemException(CORBA::SystemException& Exc, const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,Exc._name(),Function.c_str(),Action.c_str());
}

void cCBS_StdCORBA_ClientTask::doOnException(const std::string &Function, const std::string &Action, const std::string  & File, long Line)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(Message,"",Function.c_str(),Action.c_str());
}

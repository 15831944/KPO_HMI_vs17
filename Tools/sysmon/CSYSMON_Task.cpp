// Copyright (C) 2004 SMS Demag AG


#include "cCBS_StdCORBA_Task.h"

#include "cCBS_StdInitBase.h"

#include "CIntfData.h"

#include "IntrfImpl.h"

#include "CDateTime.h"
#include "CSMC_Mutex.h"

#include "CSYSMON_Task.h"


CSYSMON_Task::CSYSMON_Task()
: m_ScanInterval(3000)
{ 

  cCBS_StdInitBase::getInstance()->replaceWithEntry("SystemMonitoring", "ScanInterval", m_ScanInterval);

  m_pThread = new CSYSMON_Task::CSYSMON_TaskThread(m_ScanInterval, this);
  m_pThread->setFreeOnTerminate(true);
  m_pThread->run();

}

//-------------------------------------------------------------------------------------------------
CSYSMON_Task::~CSYSMON_Task()
{
}
//-------------------------------------------------------------------------------------------------
void CSYSMON_Task::performWorkingStep()
{
  //char time[20];
  //std::vector<s_Components>::iterator iter_Pro;
  //CBS_LocalTime Now;
  //cCBS_Time::localTime(Now);
  //cCBS_Time::toString(Now,time,19);
  //time[19] = '\0';
  //std::string tmpTime = time;

  //for(iter_Proxies = m_CorbaClient->m_CorbaProxies.begin();iter_Proxies != m_CorbaClient->m_CorbaProxies.end(); iter_Proxies++)
  //{
  //  try
  //    {
  //      CORBA::String_var taskDetails;
  //      CBS_TaskState compState = (*iter_Proxies).CBSProxy->getServantPtr()->ping(taskDetails);

  //      if(compState.workState == CBS_Working)
  //      {
  //        m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),true);
  //        m_CorbaInterface->setLastResponse((*iter_Proxies).CompName.c_str(),tmpTime);
  //      }
  //      else
  //      {
  //        m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),false);
  //      }
  //    }
  //    catch(...)
  //    {
  //      m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),false);
  //      (*iter_Proxies).CBSProxy->resetProxy();
  //    }
  //}

  ////wait until the interval passes
  //Sleep(m_ScanInterval);
}
////-------------------------------------------------------------------------------------------------
void CSYSMON_Task::getOwnStateDetails(CORBA::String_out details)
{
  CSMC_Mutex Mutex("CSYSMON_Task::StateDetails");

  // check whether our thread is running and post according message 
  if (CBS_Working == getOwnWorkState())
  {
    details = CORBA::string_dup("Task is Running\n");      
  }
  else
  {
    details = CORBA::string_dup("Task is not Running\n");
  }

  cCBS_StdFrame_Task::getOwnStateDetails(details);
}

//******************************************************************************************
//******************************************************************************************
// Thread handling !!!!
//******************************************************************************************
//******************************************************************************************


//##ModelId=48AD61FE00D2
CSYSMON_Task::CSYSMON_TaskThread::CSYSMON_TaskThread(	long ControlTime, CSYSMON_Task* Parent )
: m_ControlTime(ControlTime)
, m_pParent(Parent)
, m_DateTimeFormat("%d-%m-%Y %H:%M:%S.***")//CDateTimeFormat::m_DefaultFormatString)
{
  cCBS_StdInitBase::getInstance()->replaceWithEntry("SystemMonitoring", "DateTimeFormat", m_DateTimeFormat);

  m_pIntrfImpl = new IntrfImpl();

  m_pCBS_ProxyManager = new CProxyManager<iCBS_Task>();

  setCORBAConnections();

  m_ProxyList = m_pCBS_ProxyManager->getProxyList();

}

//##ModelId=48AD61FE00D5
CSYSMON_Task::CSYSMON_TaskThread::~CSYSMON_TaskThread()
{
}

//##ModelId=48AD61FE00D6
void CSYSMON_Task::CSYSMON_TaskThread::work()
{
  try
  {
    while( !getTerminateThread() )
    {
      performWorkingStep();
    }
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CSYSMON_Task::CSYSMON_TaskThread::work()","performing Working Step");
  }
}



//##ModelId=48AD61FE00D7
void CSYSMON_Task::CSYSMON_TaskThread::terminate()
{
  setTerminateThread();
}

//##ModelId=48AD61FE00D8
void CSYSMON_Task::CSYSMON_TaskThread::performWorkingStep()
{
  try
  {
    if ( !getTerminateThread() && m_pIntrfImpl )
    {
      CDateTime Now;

      std::map <std::string,std::string>::iterator it;

      for(it = m_ProxyList.begin(); it != m_ProxyList.end(); it++)
      {
        std::string ServerName    = it->first;
        std::string ComponentName = it->second;

        try
        {
          iCBS_Component_var pCBS_Component = CBS::getComponent(ComponentName.c_str(), false);

          if ( pCBS_Component )
          {
            CORBA::String_var taskDetails;
            CBS_TaskState compState = pCBS_Component->ping(taskDetails);

            if(compState.workState == CBS_Working)
            {
              m_pIntrfImpl->setStatus(ServerName.c_str(),true);
              m_pIntrfImpl->setLastResponse(ServerName.c_str(),Now.asString(m_DateTimeFormat));
              m_pParent->setStateDetailsThreadSave(ServerName, Now.asString(m_DateTimeFormat));              
            }
            else
            {
              m_pIntrfImpl->setStatus(ServerName.c_str(),false);
            }
          }
        }
        catch(...)
        {
          m_pIntrfImpl->setStatus(ServerName.c_str(),false);
        }
      }

      
    }
  
    sleep(m_ControlTime);

  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"","CCyclicedTriggerCall::CCyclicTrig::performWorkingStep()","");
  }
}

void CSYSMON_Task::CSYSMON_TaskThread::setCORBAConnections()
{
  // find multiple interfaces in ini file
  cCBS_StdCORBA_Task * pCORBA_Task = cCBS_StdCORBA_Task::getInstance();

  if (m_pCBS_ProxyManager)
  {
    // Proxy names under "SystemMonitoring" in ini-file will be read 
    //and all object references to this proxies will be fetched 
    //from nameservice.
    m_pCBS_ProxyManager->registerProxies("SystemMonitoring");
  }

  if (pCORBA_Task && m_pIntrfImpl)
  {
    std::string SMONIntrf = "SMONIntrf";

    cCBS_StdInitBase::getInstance()->replaceWithEntry("SystemMonitoring", "SMONIntrf", SMONIntrf);

    pCORBA_Task->registerServant(m_pIntrfImpl,SMONIntrf);
  }

}

void CSYSMON_Task::setStateDetailsThreadSave(const std::string &item, const std::string &value)
{
  CSMC_Mutex Mutex("CSYSMON_Task::StateDetails");
  
  setStateDetails(item, value);
}
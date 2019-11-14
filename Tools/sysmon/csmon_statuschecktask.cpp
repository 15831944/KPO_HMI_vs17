#include "cSMON_StatusCheckTask.h"
#include "cSMON_CorbaClientTask.h"
#include "IntrfImpl.h"
#define _CLOG9
#include "CBS_Clog.h"
#include "omniORB.h"

cSMON_StatusCheckTask::cSMON_StatusCheckTask(IntrfImpl *Interface) 
{
  m_CorbaInterface = Interface;

  cCBS_ConfigBase* configBase = cCBS_ConfigBase::getConfigBase();

  if (!(configBase->getActGrpEle("SystemMonitoring", "ScanInterval", iScanInterval)))
    iScanInterval = 3000; //reading failed -> set 3000 as default value

  if (!(configBase->getActGrpEle("SystemMonitoring", "ORBPingTimeOut", m_ORBPingTimeOut)))
    m_ORBPingTimeOut = 3000; //reading failed -> set 3000 as default value


  CLOG6 (<< "Constructor finished!" << std::endl);
}
//-------------------------------------------------------------------------------------------------
cSMON_StatusCheckTask::~cSMON_StatusCheckTask()
{
}
//-------------------------------------------------------------------------------------------------
void cSMON_StatusCheckTask::ownRunDown()
{
  this->terminate();
  CLOG6(<< "ownRunDown says:Bye bye!!!" << std::endl);
}
//-------------------------------------------------------------------------------------------------
void cSMON_StatusCheckTask::performWorkingStep()
{
  char time[20];
  std::vector<s_Components>::iterator iter_Proxies;
  CBS_LocalTime Now;
  cCBS_Time::localTime(Now);
  cCBS_Time::toString(Now,time,19);
  time[19] = '\0';
  std::string tmpTime = time;
  bool foundOneNotWorking = false;
  for(iter_Proxies = m_CorbaClient->m_CorbaProxies.begin();iter_Proxies != m_CorbaClient->m_CorbaProxies.end(); iter_Proxies++)
  {
    // set this task's workstate according to the workstate of all tasks and components that are monitored
    try
    {
      CORBA::String_var taskDetails;
      //CBS_TaskState compState = (*iter_Proxies).CBSProxy->getServantPtr()->ping(taskDetails);

	    iCBS_Component_var l_component = CBS::getComponent((*iter_Proxies).CorbaName.c_str());
      omniORB::setClientCallTimeout(l_component, m_ORBPingTimeOut);
	    CBS_TaskState compState = l_component->ping(taskDetails);

      if (compState.runState == CBS_Running && (compState.workState == CBS_Working || compState.workState == CBS_PartiallyWorking) )
      {
        m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),true);
        m_CorbaInterface->setLastResponse((*iter_Proxies).CompName.c_str(),tmpTime);
      }
      else
      {
        m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),false);
        foundOneNotWorking = true;
      }
    }
    catch(...)
    {
      m_CorbaInterface->setStatus((*iter_Proxies).CompName.c_str(),false);
      (*iter_Proxies).CBSProxy->resetProxy();
      foundOneNotWorking = true;

      std::cout << (*iter_Proxies).CompName.c_str() << " not reachable!" << std::endl;
    }
  }

  //wait until the interval passes
  Sleep(iScanInterval);
}
//-------------------------------------------------------------------------------------------------
void cSMON_StatusCheckTask::getOwnStateDetails(CORBA::String_out details)
{
  // check whether our thread is running and post according message 
  if (running())
  {
    if (CBS_Working == getOwnWorkState())
    {
      details = CORBA::string_dup("Task is Running\n");      
    }
    else
    {
      details = CORBA::string_dup("Task is not Running\n");
    }
  }
}
//-------------------------------------------------------------------------------------------------
void cSMON_StatusCheckTask::ownStartUp()
{
  cCBS_StdWorkerTask::ownStartUp();               // always call base class method!
  CLOG6(<< "ownStartUp invoked" << std::endl);

  if(getTraceLevel() > 0)                         // for debug only
  {
    CLOG6(<< "ownStartUp:method getTraceLevel() of " << getTaskName() << " returns "
      << getTraceLevel() << std::endl);
  }

  //if(successful_application_work) // everything done before was successful?
  //{
  //  setWorking(true);
  //  CLOG6(<< "ownStartUp: everything ok, set working 'true'." << std::endl);
  //}
  //else
  //{
  //  CLOG2(<<"ownStartUp: could not start up sub-tasks!"<<std::endl);
  //}

}

void cSMON_StatusCheckTask::createSubtasks()
{
  CBS_TaskData taskData;
  taskData.critical     = true;
  taskData.autoRecovery = true;
  taskData.priority     = MCBS::MCBS_PrioNormal;

cCBS_Corba corbaMode ( cCBS_Corba::CATCH_CORBA_SYSTEM_EXCEPTIONS | 
                              cCBS_Corba::RETHROW_CORBA_SYSTEM_AS_CBS_EXCEPTION |
								              cCBS_Corba::USE_CORBA_NAME_SERVICE |
								              cCBS_Corba::AUTO_REBIND );

m_CorbaClient = new cSMON_CorbaClientTask(corbaMode);

  m_CorbaClient->activate(m_componentPOA,"SysMon_CorbaClientTask");
  addSubtask(m_CorbaClient->getTaskName(),m_CorbaClient->getReference(),taskData);
  CLOG1(<<"SysMon_CorbaClientTask created"<<std::endl);
}
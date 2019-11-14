//-------------------------------------------------------------------------------------------------
// 
//                           S M S  D e m a g  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : CastingOpt 
// filename      : cSMON_CorbaClientTask.h 
// author        : Michael Pander
// department    : EAM1
// creation date : 18-Oct-2004 
// description   : Task for Corba connection to Level 1 and tracking.
// 
//-------------------------------------------------------------------------------------------------
// 
// change notes: 
// 
// version  dd-mm-yyyy    author   remarks 
//  1.01     17-Jul-2005   mipa     added tundish proxy for correct obtainment of tundish temperature
//  1.00     12-Dec-2004   mipa     final version; final check and reworked comments
//  0.96     18-Oct-2004   mipa     original edit
//-------------------------------------------------------------------------------------------------

#include "cSMON_CorbaClientTask.h"
#include <iostream>
// compile test log levels up to #9 
#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"

//##Begin Model Documentation
//
//##End Model Documentation
cSMON_CorbaClientTask::cSMON_CorbaClientTask(cCBS_Corba & corbaMode)
: cCBS_StdCorbaClientTask(corbaMode)
{                                                     
  s_Components tmp;

  cCBS_ConfigBase* configBase = cCBS_ConfigBase::getConfigBase();

  int iNoSystems = 0;
  if (configBase->getActGrpEle("SystemMonitoring", "NoOfSystems", iNoSystems))
  {
    for (int i = 1; i <= iNoSystems; i++)
    {
      std::string sComponentName;
      std::string sCorbaName;
      std::stringstream sConfigGrpName;

      sConfigGrpName << "SysMonProcess_" << i << '\0';

      CLOG1(<< "reading configuration for Component #" << i << std::endl);
      if ( configBase->getActGrpEle(sConfigGrpName.str().c_str(), "CorbaName", sCorbaName)
        && configBase->getActGrpEle(sConfigGrpName.str().c_str(), "ComponentName", sComponentName))
      {
        //now that i have a CorbaName and a ComponentName, add it to the list
        tmp.CompName = sComponentName;
        tmp.CorbaName = sCorbaName;
        tmp.CBSProxy = new cCBS_CorbaProxy<iCBS_Task>(tmp.CorbaName.c_str(),corbaMode);
        m_CorbaProxies.push_back(tmp);
      }
      else
      {
        CLOG1(<< "Configuration not complete for Component #" << i << std::endl);
        CLOG1("I need \"CorbaName\" and \"ComponentName\"!" << std::endl);
      }
    }
  }
  else //if (configBase->getActGrpEle("SystemMonitoring", "NoOfSystems", iNoSystems))
  {
    CLOG6(<< "Could not read number of Systems to monitor from iniFile -> [SystemMonitoring], NoOfSystems" << std::endl);
  }

  CLOG1("Constructor finished.");
}

void cSMON_CorbaClientTask::getOwnStateDetails(CORBA::String_out details)
{
  // check whether our thread is running and post according message 
  if (CBS_Working == getOwnWorkState())
  {
    std::stringstream sStatus;

    sStatus << "Task is Running" << std::endl;
    sStatus << "I am monitoring " << m_CorbaProxies.size() << " Components" << std::endl;

    std::vector<s_Components>::const_iterator proxyIter;
    for (proxyIter = m_CorbaProxies.begin(); proxyIter < m_CorbaProxies.end(); proxyIter++)
    {
      sStatus << "--> Component " << (*proxyIter).CompName << " with CorbaName " << (*proxyIter).CorbaName << std::endl;
    }

    details = CORBA::string_dup(sStatus.str().c_str());
  }
  else
  {
    details = CORBA::string_dup("Task is not Running\n");
  }
}

//-------------------------------------------------------------------------------------------------
cSMON_CorbaClientTask::~cSMON_CorbaClientTask()
{                                                     
	
}

//-------------------------------------------------------------------------------------------------
//##Begin Model Documentation
//Virtual task start up method. Called by the 
//runtimeStartUp method after starting up the subtasks. 
//The default implementation sets only the state of the 
//task to Running. Note that the work state is not set.
//
//This method may be redefined if the task represents for 
//example a thread or a process. In this case, the method 
//redefinition would start thread execution.
//##End Model Documentation
void cSMON_CorbaClientTask::ownStartUp()
{
  
    cCBS_StdCorbaClientTask::ownStartUp();              // always call base class method!
    // we need to bind the objects..
    std::vector<s_Components>::iterator iter_Proxies;

    for(iter_Proxies = m_CorbaProxies.begin(); iter_Proxies != m_CorbaProxies.end(); iter_Proxies++)
    {
      try
      {
        (*iter_Proxies).CBSProxy->bind();
      }
      catch (...)
      {
        CLOG1(<<(*iter_Proxies).CompName.c_str()<< ": bind() method failed!" << std::endl);
      }
    }

    CLOG6(<< "all proxies bound, ownStartup performed." << std::endl);
    setWorking(true);
}
// end of file cSMON_CorbaClientTask.cpp

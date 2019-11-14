#include "iProcess_Monitor_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrame.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CProcess_Monitor_Task.h"
#include "CProcess_Monitor_TelcomIntf_Impl.h"
#include "CProcess_Monitor_Check_Task.h"

CProcess_Monitor_Check_Task* CProcess_Monitor_Check_Task::m_pInstance = 0;

CProcess_Monitor_Check_Task* CProcess_Monitor_Check_Task::getInstance()
{
  if( m_pInstance == 0 )
    m_pInstance = new CProcess_Monitor_Check_Task();

  return m_pInstance;
}

CProcess_Monitor_Check_Task::CProcess_Monitor_Check_Task() 
: m_iScanInterval(30000)
{
}


CProcess_Monitor_Check_Task::~CProcess_Monitor_Check_Task()
{
  ownRunDown();
}


void CProcess_Monitor_Check_Task::performWorkingStep()
{
  bool WorkingState = false;

  if (CProcess_Monitor_Task::getInstance()->getOwnWorkState() == CBS_Working)
  {
    CProcess_Monitor_TelcomIntf_Impl *pTelcomIntf;
    pTelcomIntf = CProcess_Monitor_Task::getInstance()->getTelcom_Interface();

    log("----------- Start Control Loop -----------", 3);

    std::map< std::string, std::set<std::string> > MonitorList;
    std::map< std::string, std::set<std::string> >::const_iterator itMonitorList;
    MonitorList = pTelcomIntf->getMonitorList(); // get list of monitored items (plants)
    for (itMonitorList = MonitorList.begin(); itMonitorList != MonitorList.end(); itMonitorList ++)
    {
      std::string ActPlantID = itMonitorList->first;

      bool doControl = true;
      doControl = pTelcomIntf->getBoolean(ActPlantID, PM::Control);
      if (doControl == true)
      {
        WorkingState = true; // if one should be controled

        bool SwitchOffComputerMode = false;

        std::set<std::string>::const_iterator iter_Procs;
        bool go_on = true;
        for(iter_Procs = itMonitorList->second.begin(); iter_Procs != itMonitorList->second.end(); ++iter_Procs)
        {

          SwitchOffComputerMode = true;
          if (go_on == false)
            break;

          std::string ActProcess = *iter_Procs;

          if (getTraceLevel() >= PM::INFO_LEVEL)
          {
            std::stringstream Message;
            Message << "Check " << ActPlantID << "->" << ActProcess;
            log(Message.str(),PM::INFO_LEVEL);
          }

          std::string ComponentName = ActProcess;
          cCBS_StdInitBase::getInstance()->replaceWithEntry("ComponentName", ActProcess, ComponentName);
          try
          {
            iCBS_Component_var comp = CBS::getComponent(ComponentName.c_str(), false);
            if ( CBS_Running == comp->getOwnRunState())
            {
              if ( CBS_Working == comp->getOwnWorkState())
              {
                SwitchOffComputerMode = false;
                if (getTraceLevel() >= PM::INFO_LEVEL)
                  log("Process is available " + ActPlantID + "->" + ActProcess, PM::INFO_LEVEL);
              }
              else
              {
                // if you set your flag and continue, you may clear it again in the next loop cycle
                // and you won't get what you like.

                go_on = false;
                if (getTraceLevel() >= PM::INFO_LEVEL)
                  log("Process is available  but not working " + ActPlantID + "->" + ActProcess, PM::INFO_LEVEL);
              }
            }
            else
            {
              if (getTraceLevel() >= PM::WARNING_LEVEL)
                log("Component is not running but available " + ActPlantID + "->" + ComponentName, PM::WARNING_LEVEL);

                go_on = false;
            }
          }
          catch(CORBA::SystemException &e)
          {
            std::string TRANSIENT = "TRANSIENT";
            if (TRANSIENT == std::string(e._name()))
            {
              if (getTraceLevel() >= PM::ERROR_LEVEL)
                log("Process not available " + ActPlantID + "->" + (ActProcess), PM::ERROR_LEVEL);

              cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
              sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              pEventLog->EL_ProcessStatusError(sMessage, ActProcess.c_str(), ActPlantID.c_str());
            }
            else
            {
              if (getTraceLevel() >= PM::ERROR_LEVEL)
                log(ActPlantID + " : " + ComponentName + " CORBA System exception " + e._name(), PM::ERROR_LEVEL);
            }
            go_on = false;
          }
          catch (...)
          {
            log(ActPlantID + " : " + ComponentName + " exception!", PM::ERROR_LEVEL);
            go_on = false;
          }
          
        }

        if (!itMonitorList->second.empty())// if no processes are registered for a plant
        {
          if ( SwitchOffComputerMode == true )
          {
            ////////if  ( (AvailabilityForPlant.find(ActPlantID) == AvailabilityForPlant.end()) ||
            ////////       AvailabilityForPlant     [ActPlantID] == true)
            {
              long ActErrorNo = pTelcomIntf->getLong(ActPlantID, PM::ErrorCount);
              ActErrorNo = ActErrorNo + 1;
              pTelcomIntf->setLong(ActPlantID, PM::ErrorCount, ActErrorNo);

              std::string ProductID = CProcess_Monitor_Task::getInstance()->getTelcom_Interface()
                                          ->getString(ActPlantID, PM::ProductID);

              CProcess_Monitor_Task::getInstance()->sendEvent((const std::string)ActPlantID, ProductID);

              sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
              CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
              pEventLog->EL_ProcessMonitorSwitchOffCompMode(Message, ProductID.c_str(), ActPlantID.c_str());              
            }
          }
          else
              pTelcomIntf->setLong(ActPlantID, PM::ErrorCount, 0);    // reset errorcount


          AvailabilityForPlant[ActPlantID] = !SwitchOffComputerMode;
        }
      }//if (doControl == true)
    }// for (itMonitorList = MonitorList.begin()....

    log("----------- End Control Loop -----------", 3);
  }
  else
  {
    log("CProcess_Monitor_Task doesn't have work state. No control for any plant!", PM::WARNING_LEVEL);
  }
  //not yet viable to reset status  setWorking(WorkingState);

  sleep(m_iScanInterval);
}


void CProcess_Monitor_Check_Task::getOwnStateDetails(CORBA::String_out details)
{
  // check whether our thread is running and post according message 
  if (running())
  {
    std::string MonitorDetails = "Following plants and processes are monitored\n";

    CProcess_Monitor_TelcomIntf_Impl *pTelcomIntf;
    pTelcomIntf = CProcess_Monitor_Task::getInstance()->getTelcom_Interface();

    // prepare output which plant and processes are monitored
    std::map< std::string, std::set<std::string> > MonitorList;
    std::map< std::string, std::set<std::string> >::const_iterator itMonitorList;
    MonitorList = pTelcomIntf->getMonitorList();
    for (itMonitorList = MonitorList.begin(); itMonitorList != MonitorList.end(); itMonitorList ++)
    {
      std::string ActPlantID = itMonitorList->first;
      MonitorDetails += ActPlantID;

      bool doControl = pTelcomIntf->getBoolean(ActPlantID, PM::Control);
      if (doControl == true)
      {
        MonitorDetails += " monitoring active for processes: ";

        std::set<std::string>::const_iterator iter_Procs;
        for(iter_Procs = itMonitorList->second.begin(); iter_Procs != itMonitorList->second.end(); ++iter_Procs)
        {
          MonitorDetails += *iter_Procs + " ";
        }
      }
      else
      {
        MonitorDetails += " monitoring is currently NOT active. Waiting for next heat announcement.";
      }

      MonitorDetails += "\n";
    }
    details = CORBA::string_dup(/*"Task is Running\n" + */MonitorDetails.c_str());
  }
  else
  {
    details = CORBA::string_dup("Task is not Running\n");
  }
}

void CProcess_Monitor_Check_Task::ownStartUp()
{
  cCBS_StdFrame_Task::ownStartUp();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("TaskData", "CheckInterval", m_iScanInterval);

  if (!running())
  {
    run();
    setWorking(true);
  }
}

void CProcess_Monitor_Check_Task::ownRunDown()
{
  log("CProcess_Monitor_Check_Task::ownRunDown",3);
  if (running())
  {
    log("CProcess_Monitor_Check_Task::ownRunDown: terminate thread",3);
    setTerminateThread();
    waitForExit();
    log("CProcess_Monitor_Check_Task::ownRunDown: terminated",3);
  }
}

//void CProcess_Monitor_Check_Task::log(const std::string& _message, long _level)
//{
//  cCBS_StdLog_Task::getInstance()->log(_message, _level);
//}


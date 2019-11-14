#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_DelayHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_DelayHandling::~CARCHIVER_LF_Test_DelayHandling()
{
}

CARCHIVER_LF_Test_DelayHandling::CARCHIVER_LF_Test_DelayHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}


bool CARCHIVER_LF_Test_DelayHandling::HandleLFDelayStatusRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;  

  //Initialise database objects
  CPD_REPORT* m_pPD_Report = 0;
  

  if (pConnection)
  {
    m_pPD_Report = new CPD_REPORT(pConnection);
   
  }

  
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
  {
    cCBS_StdLog_Task::getInstance()->log("Test Handle Delay Status use case was successful",1);
  }
  else
  {
     cCBS_StdLog_Task::getInstance()->log("Test Handle Delay Status use case failed",1);
  }

  RetValue = true;

  return RetValue;
}




void CARCHIVER_LF_Test_DelayHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_DelayHandling::deleteDBClasses()
{
}


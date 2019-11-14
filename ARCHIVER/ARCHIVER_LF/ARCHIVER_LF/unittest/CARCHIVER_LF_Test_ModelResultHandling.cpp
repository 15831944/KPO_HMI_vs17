#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_ModelResultHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_ModelResultHandling::~CARCHIVER_LF_Test_ModelResultHandling()
{
}

CARCHIVER_LF_Test_ModelResultHandling::CARCHIVER_LF_Test_ModelResultHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);

}

bool CARCHIVER_LF_Test_ModelResultHandling::handleLFRecipeSetpointsRDY(CEventMessage& Event)
{
  bool RetValue = false;

  return RetValue;
}

bool CARCHIVER_LF_Test_ModelResultHandling::handleLFActualSetpointsRDY(CEventMessage& Event)
{
   bool RetValue = false;

   return RetValue;
}
void CARCHIVER_LF_Test_ModelResultHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_ModelResultHandling::deleteDBClasses()
{
}

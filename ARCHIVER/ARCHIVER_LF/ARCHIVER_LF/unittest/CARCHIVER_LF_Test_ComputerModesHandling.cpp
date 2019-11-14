#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_ComputerModesHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_ComputerModesHandling::~CARCHIVER_LF_Test_ComputerModesHandling()
{
}

CARCHIVER_LF_Test_ComputerModesHandling::CARCHIVER_LF_Test_ComputerModesHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}


bool CARCHIVER_LF_Test_ComputerModesHandling::handleLFSetComputerModeRDY(CEventMessage& Event)//Dipesh-------
{ bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string DataKey = Event.getDataKey();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
 

  bool TestCode = false;

  //Declare Pointers of DB Classes
  
  CPD_COMP_DATA* pPD_COMP_DATA = 0;

  //Initialise database objects
  if (pConnection)
     pPD_COMP_DATA = new CPD_COMP_DATA(pConnection);
    

  seqComputerModes SeqComputerModes;
  long          ComputerModesStatus;
  long          ChangedComputerModesStatus;
  long          GetAtValue;
  sComputerMode Mode;
  string        Device;

  setpDM_Interface(ServerTask,DM::PLANT);
  SeqComputerModes = *m_pDM_Interface->getComputerModes(DataKey.c_str(), DATA::ComputerModes);
  
  Message << "\nPD_COMP_DATA" << endl;
  long SeqLength = CIntfData::getLength(SeqComputerModes);
  for (int x = 0; x < SeqLength; x++) 
  {
    GetAtValue  = CIntfData::getAt(Mode, SeqComputerModes, x);
    Device      = Mode.Device;

    ComputerModesStatus = Mode.Status;

    ChangedComputerModesStatus = pPD_COMP_DATA->getActStatus(RecHeatID, RecTreatID, RecPlant, Device);

    if( ComputerModesStatus != ChangedComputerModesStatus )
    {
      Message << "ERROR:\n  ComputerModesStatus for Device " << Device << " is not set in PD_COMP_DATA" << endl;
      TestCode = false;
    }
    else
    {
      Message << "ComputerModesStatus for Device " << Device << " (" << ComputerModesStatus << ") = " << ChangedComputerModesStatus << endl;
    }
  }
  

  //delete databse objects
  if (pPD_COMP_DATA) { delete pPD_COMP_DATA; pPD_COMP_DATA = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}
void CARCHIVER_LF_Test_ComputerModesHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_ComputerModesHandling::deleteDBClasses()
{
}


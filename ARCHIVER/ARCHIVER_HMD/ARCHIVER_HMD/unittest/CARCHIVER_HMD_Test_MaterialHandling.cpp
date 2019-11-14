#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_MaterialHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"


CARCHIVER_HMD_Test_MaterialHandling::~CARCHIVER_HMD_Test_MaterialHandling()
{
}

CARCHIVER_HMD_Test_MaterialHandling::CARCHIVER_HMD_Test_MaterialHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}


bool CARCHIVER_HMD_Test_MaterialHandling::handleHMDPowderBlowingRDY(CEventMessage& Event, bool BlowingStart)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;
 


  //Initialise database objects
  CPDH_HEAT_DATA* m_pPDH_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDH_Heat_Data = new CPDH_HEAT_DATA(pConnection);    
  }
    
    Message << "\nPDH_HEAT_DATA" <<endl;

    if (m_pPDH_Heat_Data->select(RecPlant, RecHeatID, RecTreatID ))
    {
        if(BlowingStart)
        {
        if(!m_pPDH_Heat_Data->isNull("INJECT_START_TIME",1))
        Message <<"INJECT_START_TIME = " << m_pPDH_Heat_Data->getINJECT_START_TIME(1) <<endl;
        else
	        {      
                Message << "ERROR:\n  INJECT_START_TIME is not set in PDH_HEAT_DATA" << endl;
			          TestCode = false;
		      }
        }
        else
        {     
        if(!m_pPDH_Heat_Data->isNull("INJECT_END_TIME",1))
        Message <<"INJECT_END_TIME = " << m_pPDH_Heat_Data->getINJECT_END_TIME(1) <<endl;
       else
	        {      
                Message << "INJECT_END_TIME is not set in PDH_HEAT_DATA" << endl;
			          TestCode = false;
		      }
        }
    }
    else
    {
        Message << "The selection from PDH_Heat_Data was not successful" << endl;
        TestCode = false;
    }
   

  if (m_pPDH_Heat_Data) { delete m_pPDH_Heat_Data; m_pPDH_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  

  RetValue = true;

  return RetValue;
}

void CARCHIVER_HMD_Test_MaterialHandling::initDBClasses()
{
}

void CARCHIVER_HMD_Test_MaterialHandling::deleteDBClasses()
{
}

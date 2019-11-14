#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CDH_IN_Test_Task.h"	
#include "CDateTime.h"
#include "CIntfData.h"

#include "CDH_IN_Test_DataProvider.h"
#include "CDH_IN_Test_EventHandler.h"	


CDH_IN_Test_EventHandler::CDH_IN_Test_EventHandler()
{
}

CDH_IN_Test_EventHandler::~CDH_IN_Test_EventHandler()
{
}

bool CDH_IN_Test_EventHandler::handleEvent(CEventMessage &evMessage)
{
  bool RetValue = true;
  
  if (checkReceiver(evMessage))
  {
    DH::iDH_Interface_var DH_Interface = CDH_IN_Test_Task::getInstance()->getDHInterface();
    if (DH_Interface)
    { 
      std::cout << "Event received: " << evMessage.getMessage() <<".\n\n";
   
      if (CDH_IN_Test_Task::getInstance()->MatchTelegram(evMessage.getMessage()))
      {
        CDH_IN_Test_Task::getInstance()->TestMain(evMessage);
      }
    }
    else
    {
      std::cout << "No DH interface.\n";
    } //DH_Interface
  } //(checkReceiver(evMessage))
 
  return RetValue;  
}

// Copyright (C) 2006 SMS Demag AG Germany

#include "CEventHandlerFactory.h"
//#include "CAOD_EventHandler.h"
//#include "CEAF_EventHandler.h"
#include "CLF_EventHandler.h"
//#include "CL3_EventHandler.h"
//#include "CLab_EventHandler.h"
//#include "CCCS_EventHandler.h"
//#include "CHMD_EventHandler.h"

//#include "CIPQS_EventHandler.h"



//##ModelId=4582B990019C
CEventHandlerFactory::CEventHandlerFactory()
{
  //DH_ServerName_AOD   = "DH_L1_AOD_1_OUT";
  //DH_ServerName_EAF   = "DH_L1_EAF_1_OUT";
  DH_ServerName_LF    = "DH_L1_LF_1_OUT";
  //DH_ServerName_LAB   = "DH_LAB_OUT";
  //DH_ServerName_L3    = "DH_L3_OUT";
  //DH_ServerName_CCS   = "DH_CCS_OUT";
  //DH_ServerName_IPQS  = "DH_IPQS_OUT";
	//DH_ServerName_HMD_1 =  "DH_L1_HMD_1_OUT";
	//DH_ServerName_HMD_2 =  "DH_L1_HMD_2_OUT";

}

//##ModelId=4582B99303D2
CEventHandlerFactory::~CEventHandlerFactory()
{
}

//##ModelId=4582BD5302F6
CDH_EventHandler* CEventHandlerFactory::createEventHandler(std::string& ServerName)
{

  ///*if ( DH_ServerName_AOD    ==  ServerName )
  //  return new CAOD_EventHandler();

  //else if ( DH_ServerName_EAF    ==  ServerName )
  //  return new CEAF_EventHandler();
    
  //else
  if ( DH_ServerName_LF     ==  ServerName ) 
    return new CLF_EventHandler();

  //else if ( DH_ServerName_LAB    ==  ServerName )
  //  return new CLab_EventHandler();

  //else if ( DH_ServerName_L3    ==  ServerName )
  //  return new CL3_EventHandler();

  //else if ( DH_ServerName_CCS    ==  ServerName )
  //  return new CCCS_EventHandler();

  //else if (( DH_ServerName_HMD_1    ==  ServerName ) || ( DH_ServerName_HMD_2    ==  ServerName ))
  //  return new CHMD_EventHandler();

	//else if ( DH_ServerName_IPQS   ==  ServerName )
  //  return new CIPQS_EventHandler();

  else 
    std::cout << "CEventHandlerFactory::createEventHandler: No event handler created, return (0)" << std::endl;
 
  return static_cast <CDH_EventHandler*> (0);
 }


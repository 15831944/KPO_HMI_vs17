// Copyright (C) 2006 SMS Demag AG

#include "CTlgHandlerFactory.h"
//#include "CAOD_TelegramHandler.h"
//#include "CEAF_TelegramHandler.h"
#include "CLF_TelegramHandler.h"
//#include "CLab_TelegramHandler.h"
//#include "CCCS_TelegramHandler.h"
//#include "CL3_TelegramHandler.h"
//#include "CHMD_TelegramHandler.h"

//##ModelId=4582C55C027A
CTelegram_Handler *  CTlgHandlerFactory::createTlgHandler(std::string& ServerName)
{
 /* if ( ServerName == DH_ServerName_AOD )
    return new CAOD_TelegramHandler( );

  else*/ 
	//if ( ServerName == DH_ServerName_EAF )
 //   return new CEAF_TelegramHandler( );

 // else 
	  if ( ServerName == DH_ServerName_LF )
    return new CLF_TelegramHandler( );

  /*else if ( ServerName == DH_ServerName_LAB )
    return new CLab_TelegramHandler( );
  */
  //else if ( ServerName == DH_ServerName_CCS )
  //  return new CCCS_TelegramHandler( );

  //else if ( (ServerName == DH_ServerName_HMD_1 ) || (ServerName == DH_ServerName_HMD_2))
  //  return new CHMD_TelegramHandler( );

  //else if ( ServerName == DH_ServerName_L3 )
  //  return new CL3_TelegramHandler( );

  else 
  {
    std::cout << "CTlgHandlerFactory::createTlgHandler: No telegram handler created, return (0)" << std::endl;
    return static_cast<CTelegram_Handler*>(0);
  }
}

//##ModelId=4582C5FF0304
CTlgHandlerFactory::CTlgHandlerFactory()
{
  //DH_ServerName_AOD    = "DH_L1_AOD_1_IN";
  //DH_ServerName_EAF    = "DH_L1_EAF_1_IN";
  DH_ServerName_LF     = "DH_L1_LF_1_IN";
 // DH_ServerName_LAB    = "DH_LAB_IN";
 // DH_ServerName_CCS    = "DH_CCS_IN";
 // DH_ServerName_L3     = "DH_L3_IN";
	//DH_ServerName_HMD_1    = "DH_L1_HMD_1_IN";
	//DH_ServerName_HMD_2    = "DH_L1_HMD_2_IN";
}

//##ModelId=4582C6000176
CTlgHandlerFactory::~CTlgHandlerFactory()
{
}


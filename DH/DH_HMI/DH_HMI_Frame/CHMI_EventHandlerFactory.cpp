// Copyright (C) 2006 SMS Demag AG

#include "CHMI_EventHandlerFactory.h"
#include "CHMI_LF_EventHandler.h"
#include "CHMI_EAF_EventHandler.h"
#include "CHMI_GEN_EventHandler.h"
#include "CHMI_HMD_EventHandler.h"

CHMI_EventHandlerFactory::CHMI_EventHandlerFactory()
{
  DH_ServerName_EAF    = "DH_HMI_EAF";
  DH_ServerName_LF     = "DH_HMI_LF";
  DH_ServerName_GEN    = "DH_HMI_GEN";
  DH_ServerName_AOD    = "DH_HMI_AOD";
	DH_ServerName_HMD    = "DH_HMI_HMD";
}

CHMI_EventHandlerFactory::~CHMI_EventHandlerFactory()
{
}

CDH_EventHandler* CHMI_EventHandlerFactory::createEventHandler(std::string& ServerName)
{
  if ( ServerName == DH_ServerName_LF )
    return new CHMI_LF_EventHandler(ServerName);

  if ( ServerName == DH_ServerName_EAF )
    return new CHMI_EAF_EventHandler(ServerName);

  if ( ServerName == DH_ServerName_GEN )
    return new CHMI_GEN_EventHandler(ServerName);

 if ( ServerName == DH_ServerName_HMD )
    return new CHMI_HMD_EventHandler(ServerName);

	return static_cast <CDH_EventHandler*>(0);
}


// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED
#define _INC_CDM_LFMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED

#include "CDM_EventHandler.h"
#include "CDM_LFEventHandler.h"

class CDM_LFModesAndAvailabilitiesEventHandler 
: public CDM_LFEventHandler
{
public:
  CDM_LFModesAndAvailabilitiesEventHandler();

  virtual ~CDM_LFModesAndAvailabilitiesEventHandler();

  virtual bool handleEvent(CEventMessage& evMessage);

  bool doLFSetComputerMode(CEventMessage& Event);

  // reset comp. mode vailability for a product
  bool doLFResetComputerModeAvailability(CEventMessage& Event);

};

#endif /* _INC_CDM_LFMODESANDAVAILABILITIESEVENTHANDLER_412F158503B0_INCLUDED */

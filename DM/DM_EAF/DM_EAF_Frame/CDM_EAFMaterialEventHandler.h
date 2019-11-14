// Copyright (C) SMS-SIEMAG AG 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_EAFMATERIALEVENTHANDLER_412F156103AA_INCLUDED
#define _INC_CDM_EAFMATERIALEVENTHANDLER_412F156103AA_INCLUDED

#include "CDM_EAFEventHandler.h"

class CDM_EAFMaterialEventHandler 
  : public CDM_EAFEventHandler
{
public:

  virtual ~CDM_EAFMaterialEventHandler();

  CDM_EAFMaterialEventHandler();

  //This hook operation is called by adapter
  virtual bool handleEvent(CEventMessage& evMessage);

  bool doEAFHMIMaterialDischarged(CEventMessage& Event);

  bool doEAFMaterialHandlingReport( CEventMessage& Event);  

  bool doEAFChangeLiquidAdditionData(CEventMessage& Event);

  bool doEAFMatFeedingStart(CEventMessage& Event);

  bool doEAFMatFeedingStop(CEventMessage& Event);

  bool doEAFHandleBasketDischarged(CEventMessage& Event);

  bool doEAFHandleBasketAssignedToHeat(CEventMessage& Event);

  bool doEAFHandleBasketDeAssignedFromHeat(CEventMessage& Event);

  bool doEAFHandleSetBasketData(CEventMessage& Event);

  bool doEAFChargedHotMetal(CEventMessage& Event);

  bool doEAFHotMetalAssigned(CEventMessage& Event);

  bool doEAFHotMetalLadleData(CEventMessage& Event);

  bool doEAFRemoveHotMetalData(CEventMessage& Event);

  bool doEAFScrapMaterialAvail(CEventMessage& Event);
};

#endif /* _INC_CDM_EAFMATERIALEVENTHANDLER_412F156103AA_INCLUDED */

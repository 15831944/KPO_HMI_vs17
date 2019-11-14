
#ifndef __DM_DEFINTIONS_H_INCLUDED__
#define __DM_DEFINTIONS_H_INCLUDED__

// These header files might always be used by event handling classes
#include "CEventMessage.h"
#include "iDH_Interface_s.hh"
#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CDM_ProductManagementInterface_Impl.h"


#if defined (LF_MODEL)
	#include "iLF_Interface_s.hh"
	#define EVENT_MESSAGE_SCOPE  LF_EvMsg  
#elif defined (EAF_MODEL)
	#include "iEAF_Interface_s.hh"
	#define EVENT_MESSAGE_SCOPE  EAF_EvMsg
#elif defined (BOF_MODEL)
	#include "iBOF_Interface_s.hh"
	#define EVENT_MESSAGE_SCOPE  BOF_EvMsg
#elif defined (AOD_MODEL)
	#include "iAOD_Interface_s.hh"
	#define EVENT_MESSAGE_SCOPE  AOD_EvMsg
#elif defined (L3_EvMsg)
	#define EVENT_MESSAGE_SCOPE  L3_EvMsg
#elif defined (HMI_EvMsg)
	#define EVENT_MESSAGE_SCOPE  HMI_EvMsg
#elif defined (GEN_EvMsg)
	#define EVENT_MESSAGE_SCOPE  GEN_EvMsg
#elif defined (HMD_EvMsg)
	#define EVENT_MESSAGE_SCOPE  HMD_EvMsg
#elif defined (RH_EvMsg)
	#define EVENT_MESSAGE_SCOPE  RH_EvMsg
#else
	#error  One of these macros must be defined before includeing "DM_Defintions.h": \
          LF_MODEL, EAF_MODEL, AOD_MODEL,L3_EvMsg,HMI_EvMsg, or GEN_EvMsg.
#endif



// These macros are defined to facilitate the event handling codings
#if defined (HANDLE_EVENT)
  #undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
           return do##action(evMessage);

#if defined (HANDLE_EVENT_PLANT)
  #undef HANDLE_EVENT_PLANT
#endif
#define HANDLE_EVENT_PLANT(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
			     return doPlantEvent(evMessage);

#if defined (HANDLE_EVENT_PRODUCT)
#undef HANDLE_EVENT_PRODUCT
#endif
#define HANDLE_EVENT_PRODUCT(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
			     return doProductEvent(evMessage);

#if defined (HANDLE_EVENT_DATA)
 #undef HANDLE_EVENT_DATA
#endif
#define HANDLE_EVENT_DATA(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
			     return doDataEvent(evMessage);


#endif // __DM_DEFINTIONS_H_INCLUDED__

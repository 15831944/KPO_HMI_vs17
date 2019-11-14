// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_LFEVENTHANDLER_412F163F0078_INCLUDED
#define _INC_CDM_LFEVENTHANDLER_412F163F0078_INCLUDED

#if defined (EVENT_MESSAGE_SCOPE)
  #undef EVENT_MESSAGE_SCOPE
#endif

#define EVENT_MESSAGE_SCOPE  LF_EvMsg  

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

#if defined (HANDLE_EVENT_DATA_FORWARD)
 #undef HANDLE_EVENT_DATA_FORWARD
#endif
#define HANDLE_EVENT_DATA_FORWARD(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
			     return doDataEventForward(evMessage);



#include "CDM_EventHandler.h"

class CDM_LFEventHandler : public CDM_EventHandler
{
public:

	CDM_LFEventHandler();

	virtual ~CDM_LFEventHandler();

  virtual bool doOnUnknownProduct(CEventMessage& Event);

};

#endif /* _INC_CDM_LFEVENTHANDLER_412F163F0078_INCLUDED */

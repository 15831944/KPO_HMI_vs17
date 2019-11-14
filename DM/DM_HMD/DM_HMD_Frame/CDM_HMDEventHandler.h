// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDEVENTHANDLER_412F163F0078_INCLUDED
#define _INC_CDM_HMDEVENTHANDLER_412F163F0078_INCLUDED

#if defined (EVENT_MESSAGE_SCOPE)
  #undef EVENT_MESSAGE_SCOPE
#endif
#define EVENT_MESSAGE_SCOPE  HMD_EvMsg  

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


#include "CDM_EventHandler.h"


//##ModelId=45139A720146
class CDM_HMDEventHandler 
: public CDM_EventHandler
{
protected:

  virtual bool beforeDispatchEvent(CEventMessage& Event);

public:
	CDM_HMDEventHandler();
	virtual ~CDM_HMDEventHandler();

  virtual bool doOnUnknownProduct(CEventMessage& Event);


};

#endif /* _INC_CDM_HMDEVENTHANDLER_412F163F0078_INCLUDED */

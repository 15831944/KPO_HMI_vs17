// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_GENEVENTHANDLER_412F163F0078_INCLUDED
#define _INC_CDM_GENEVENTHANDLER_412F163F0078_INCLUDED

#if defined (EVENT_MESSAGE_SCOPE)
  #undef EVENT_MESSAGE_SCOPE
#endif
#define EVENT_MESSAGE_SCOPE  GEN_EvMsg

#if defined (HANDLE_EVENT)
  #undef HANDLE_EVENT
#endif
#define HANDLE_EVENT(action) \
	if (EVENT_MESSAGE_SCOPE##::ev##action == evMessage.getMessage()) \
           return do##action(evMessage);

#include "CDM_EventHandler.h"



class CDM_GENEventHandler : public CDM_EventHandler
  
{
protected:
  
public:
	virtual bool checkEventAssignment(CEventMessage& Event);


	CDM_GENEventHandler();

	virtual ~CDM_GENEventHandler();

  virtual bool doOnUnknownProduct(CEventMessage& Event);


};

#endif /* _INC_CDM_GENEVENTHANDLER_412F163F0078_INCLUDED */

// Copyright (C) 2006 SMS Demag AG
// 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMI_EAF_EVENTHANDLER_45882EAB003E_INCLUDED
#define _INC_CHMI_EAF_EVENTHANDLER_45882EAB003E_INCLUDED

#include "CHMI_EventHandler.h"

//##ModelId=45882EAB003E
class CHMI_EAF_EventHandler 
  : public CHMI_EventHandler
{
public:
  //This hook operation would be called automatically by 
  //handleEvent( FRISEVENT &event) 
  //when an event is received. And this operation must be 
  //implemented by the user or client
  //in order to use it.
  //##ModelId=45883018018A
  virtual bool handleEvent(CEventMessage& evMessage);

  //##ModelId=4588301C013F
  CHMI_EAF_EventHandler(std::string& ServerName);

  //##ModelId=45883020005E
  virtual ~CHMI_EAF_EventHandler();

};

#endif /* _INC_CHMI_EAF_EVENTHANDLER_45882EAB003E_INCLUDED */

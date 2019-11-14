// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELEGRAM_EVENTHANDLER_4264F02C00E4_INCLUDED
#define _INC_CTELEGRAM_EVENTHANDLER_4264F02C00E4_INCLUDED

#include "CEventHandler.h"

//##ModelId=4264F02C00E4
class CTelegram_EventHandler 
: public CEventHandler
{
public:

  bool dispatchEvent(const std::string& SenderName, const std::string & DestinationName, CEventMessage& Event);

};

#endif /* _INC_CTELEGRAM_EVENTHANDLER_4264F02C00E4_INCLUDED */

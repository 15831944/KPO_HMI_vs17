// Copyright (C) 2009 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDELAYEDTRIGGERCALL_4110EE2F001F_INCLUDED
#define _INC_CDELAYEDTRIGGERCALL_4110EE2F001F_INCLUDED

#include "CEventMessage.h"

//Provides a delayed trigger. The trigger is executed after 
//the specified delay time and then self-destroyed. This 
//class use the protected nested class CTrig to prevent 
//problems in destroying automaticlly and dynamically 
//instantiated objects.
class CDelayedTriggerCall 
{
protected:
  //Provides delayed trigger based on the CBS_Thread class.
  //Attributes are filled from enclosed class CDelayedTrigger.
  class CDelayTrig 
  : public cCBS_Thread
  {
  public:
    //Expects the delay in ms the new trigger should be 
    //delayed and the trigger specified as CCbsEventMessage.
    CDelayTrig(CEventMessage& arg, long msec);

  protected:
    long m_delayTime;

    CEventMessage m_eventMessage;

    virtual ~CDelayTrig();

    //Virtual work method. Sleeps for the specified delay 
    //time and fires the trigger.
    virtual void work();

  };

public:
  virtual ~CDelayedTriggerCall();

  //Expects the delay in milli seconds for the message to be sent.
  CDelayedTriggerCall(CEventMessage& arg, long msec);

};

#endif /* _INC_CDELAYEDTRIGGERCALL_4110EE2F001F_INCLUDED */

// Copyright (C) 2012 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CEVENTLOGCYCLICREMINDER_40EE9AC8030E_INCLUDED
#define _INC_CEVENTLOGCYCLICREMINDER_40EE9AC8030E_INCLUDED

#include <map>
#include "cCBS_Thread.h"
#include "cCBS_EventLogMessage.h"

class cCBS_StdEventLogCyclicReminder 
{
public:
  class CCyclicTrig 
  : public cCBS_Thread
  {
    friend class cCBS_StdEventLogCyclicReminder;

  private:

    cCBS_StdEventLogCyclicReminder* m_Parent;

    bool m_isRecalled;

  public:
    //recall trigger cycle for sending event immediately
    void recall();

    virtual ~CCyclicTrig();

    CCyclicTrig(cCBS_StdEventLogCyclicReminder* parent, sEventLogMessage& EventLog, long RemindTime);

    std::string getCurrentThreadId();

    void terminate();

    sEventLogMessage getEventLog();

    void log(const std::string & Message, long Level);

  protected:
    //Work function called in a loop by the thread (via the 
    //work method). Can be redefined by subclasses. 
    //
    //The default implementation does nothing (except 
    //sleeping for 1 second). This method could have been 
    //declared abstract. Anyway, in order to allow instances 
    //of cCBS_Thread to be created (in the case where a 
    //thread function has been specified for execution), it 
    //has been implemented doing nothing.
    virtual void performWorkingStep();

    //Virtual work method. Sleeps for the specified 
    //ControlTime and checks status 
    //will run down task and component in case of errors
    virtual void work();


    //RemindTime in mseconds
    long m_RemindTime;

    sEventLogMessage m_EventLog;
  };

  virtual ~cCBS_StdEventLogCyclicReminder();

  cCBS_StdEventLogCyclicReminder();

  void addEventLog(sEventLogMessage& EventLog, long msec );

  void removeEventLog(sEventLogMessage& EventLog);

  void sendMessage(sEventLogMessage& EventLog, long msec = 20000 );

  void log(const std::string & Message, long Level);

protected:

  std::map<long,cCBS_StdEventLogCyclicReminder::CCyclicTrig*> m_EventLogList;
  cCBS_StdEventLogCyclicReminder::CCyclicTrig* findTrigger(sEventLogMessage& EventLog);

public:

  void recall(sEventLogMessage& EventLog);
};

#endif /* _INC_CEVENTLOGCYCLICREMINDER_40EE9AC8030E_INCLUDED */

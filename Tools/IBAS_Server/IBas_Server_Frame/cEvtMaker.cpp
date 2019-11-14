#include "BasTelegrams_EventMap.h"

// some CBS Includes to make compiler happy (need only cCBS_StdEventSenderTask but that requires more)



#pragma warning (disable: 4311 4312 4267)
#include "iStdEventData_s.h"
#pragma warning (default: 4311 4312 4267)
#include "cCBS_StdTask.h"
#include "cCBS_EvChannelSender.h"
#include "cCBS_StdEventSenderTask.h"


extern cCBS_StdEventSenderTask * pCBS_StdEventSenderTask;

#include "cevtmaker.h"





cEvtMaker::cEvtMaker(void)
{
  theEvtMap = new BasTelegrams_EventMap;
}

cEvtMaker::~cEvtMaker(void)
{
}

// Actually, this does not longer SEND the events, rather
// it queues them up for later sending.

void cEvtMaker::checkAndSend (const char *tag, long oldValue, long newValue)
{
  long EvtValue;
  if   (tag[2] == '.') tag+=3;      // skip "fb." and such
  if   (theEvtMap->getEventToSend (tag, oldValue, newValue, EvtValue))
  {
    if   (pCBS_StdEventSenderTask)
    {
      FRIESEvent event;             // the Send Event containing the data as ANY
      sStdEventData pData ;         // the used Data

      pData.i1 = newValue;          // new Flag value as 1st Integer value
      CORBA::Any tmp;               // using a temporary object to avoid trouble
      tmp <<= pData; 

      // complete and send the Event
      event.id   = 10 ;             // unused, actually...
      event.type = EvtValue;        // what the Event Map told us to send...
      event.eventData = tmp;

//      pCBS_StdEventSenderTask->send(event);
      eventQueue.push (event);
    }
  }
}

void cEvtMaker::abortAccumulatedEvents()
{
  // just pop until queue is empty
  while (!eventQueue.empty())
  {
    eventQueue.pop();
  }
}

void cEvtMaker::sendAccumulatedEvents()
{
  // send next event and pop until empty.
  while (!eventQueue.empty())
  {
    pCBS_StdEventSenderTask->send (eventQueue.front());
    eventQueue.pop();
  }
}
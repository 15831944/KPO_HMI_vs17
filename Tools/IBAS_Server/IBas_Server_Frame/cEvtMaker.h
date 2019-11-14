#ifndef CEVTMAKER_H
#define CEVTMAKER_H

#include <queue>

class BasTelegrams_EventMap;
class cEvtMaker
{
public:
  cEvtMaker(void);
  ~cEvtMaker(void);
  // the name is a little confusing. does not really send.
  void checkAndSend (const char* tag, long oldVal, long newVal);
  void sendAccumulatedEvents  ();
  void abortAccumulatedEvents ();
protected:
  // the generated list of Event Channel Events we need to emit upon receipt of
  // a new Flag Value
  BasTelegrams_EventMap *theEvtMap;

  std::queue<FRIESEvent>  eventQueue;

};

#endif // CEVTMAKER_H
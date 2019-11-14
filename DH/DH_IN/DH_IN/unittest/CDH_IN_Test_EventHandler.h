#ifndef _INC_CDH_IN_EventHandler_INCLUDED
#define _INC_CDH_IN_EventHandler_INCLUDED

#include "CDH_EventHandler.h"
#include "CDH_IN_Test_DataProvider.h"

class CDH_IN_Test_EventHandler 
: public CDH_EventHandler 
{
public:
  CDH_IN_Test_EventHandler();

  ~CDH_IN_Test_EventHandler();
  
  virtual bool handleEvent(CEventMessage &evMessage);

//private:
//  CPP_HEAT_PLANT* m_pPP_Heat_Plant;

};

#endif //_INC_CDH_IN_EventHandler_INCLUDED
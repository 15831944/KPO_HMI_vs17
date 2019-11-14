#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_AODEVENTHANDLER_414018470156_INCLUDED
#define _INC_CARCHIVER_AODEVENTHANDLER_414018470156_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "CARCHIVER_SRVWrapper.h"

//##ModelId=41DD3EDC0320
class CARCHIVER_SRVEventHandler : public CARCHIVER_EventHandler
  
{
protected:
	//##ModelId=41DD3EFA0284
	CARCHIVER_SRVWrapper Wrapper;

public:
	//##ModelId=42EA38FD023B
	virtual bool handleEvent(CEventMessage& Event);

  virtual bool handleEvent(const FRIESEvent& Event);


	//##ModelId=41DD3EFA02CA
	virtual ~CARCHIVER_SRVEventHandler();

	//##ModelId=41DD3EFA02CC
	CARCHIVER_SRVEventHandler(CARCHIVER_Task *Task);	

};

#endif /* _INC_CARCHIVER_AODEVENTHANDLER_414018470156_INCLUDED */

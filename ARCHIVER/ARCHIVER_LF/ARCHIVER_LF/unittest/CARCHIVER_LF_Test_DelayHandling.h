#ifndef _INC_CARCHIVER_LF_Test_DelayHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_DelayHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CARCHIVER_Wrapper.h"


#include "CPD_REPORT.h"

class CEventMessage;

class CARCHIVER_LF_Test_DelayHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_DelayHandling();
	CARCHIVER_LF_Test_DelayHandling(CARCHIVER_Task *Task);
  
  bool HandleLFDelayStatusRDY(CEventMessage& Event);
    
	void initDBClasses();
	void deleteDBClasses();
};

#endif /* _INC_CARCHIVER_LF_Test_DelayHandling_INCLUDED */


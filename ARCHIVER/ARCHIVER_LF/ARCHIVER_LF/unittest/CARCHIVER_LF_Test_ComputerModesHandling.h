
//Dipesh-----------
#ifndef _INC_CARCHIVER_LF_Test_ComputerModesHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_ComputerModesHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"


#include "CPD_COMP_DATA.h"
#include "CARCHIVER_Wrapper.h"




class CEventMessage;

class CARCHIVER_LF_Test_ComputerModesHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_ComputerModesHandling();

	CARCHIVER_LF_Test_ComputerModesHandling(CARCHIVER_Task *Task);

  bool handleLFSetComputerModeRDY(CEventMessage& Event);

  void initDBClasses();
	
  void deleteDBClasses();
};

#endif /* _INC_CARCHIVER_LF_Test_ComputerModesHandling_INCLUDED */
#ifndef _INC_CARCHIVER_HMD_Test_ModelResultHandling_INCLUDED
#define _INC_CARCHIVER_HMD_Test_ModelResultHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"

#include "CDM_ProductManagementInterface_Impl.h"
#include "CARCHIVER_Wrapper.h"
#include "CPDH_ACTUAL_RES.h"

class CEventMessage;

class CARCHIVER_HMD_Test_ModelResultHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_HMD_Test_ModelResultHandling();

	CARCHIVER_HMD_Test_ModelResultHandling(CARCHIVER_Task *Task);

  bool handleHMDModelResultRDY(CEventMessage& Event);
  
  void initDBClasses();

	void deleteDBClasses();


};

#endif /* _INC_CARCHIVER_HMD_Test_ModelResultHandling_INCLUDED */

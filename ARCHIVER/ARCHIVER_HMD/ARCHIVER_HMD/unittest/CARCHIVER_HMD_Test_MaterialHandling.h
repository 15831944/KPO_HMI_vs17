#ifndef _INC_CARCHIVER_HMD_Test_MaterialHandling_INCLUDED
#define _INC_CARCHIVER_HMD_Test_MaterialHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"


#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_REPORT.h"
#include "CPDR_POWDER_ADD.h"
#include "CPDH_HEAT_DATA.h"

#include "CDM_DataInterface_Impl.h"
#include "CARCHIVER_Wrapper.h"

class CEventMessage;

class CARCHIVER_HMD_Test_MaterialHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;



public:

	~CARCHIVER_HMD_Test_MaterialHandling();
	CARCHIVER_HMD_Test_MaterialHandling(CARCHIVER_Task *Task);
  
  bool handleHMDPowderBlowingRDY(CEventMessage& Event, bool start);
	void initDBClasses();
	void deleteDBClasses();
  
};

#endif /* _INC_CARCHIVER_HMD_Test_MaterialHandling_INCLUDED */

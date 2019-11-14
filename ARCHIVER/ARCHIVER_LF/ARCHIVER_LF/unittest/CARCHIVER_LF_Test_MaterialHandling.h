#ifndef _INC_CARCHIVER_LF_Test_MaterialHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_MaterialHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"


#include "CPD_RECIPE.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CPD_REPORT.h"
#include "CPDL_WIRE_ADD.h"
#include "CGT_MAT.h"
#include "CPD_LADLE.h"

#include "CDM_DataInterface_Impl.h"
#include "CARCHIVER_Wrapper.h"

class CEventMessage;

class CARCHIVER_LF_Test_MaterialHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_MaterialHandling();
	CARCHIVER_LF_Test_MaterialHandling(CARCHIVER_Task *Task);
  
  bool handleLFMaterialHandlingReportRDY(CEventMessage& Event);
  bool handleLFWireFeedingStartRDY(CEventMessage& Event);
  bool handleLFWireFeedingEndRDY(CEventMessage& Event);
  bool handleLFLiqMatHandlingReportRDY(CEventMessage& Event);


	void initDBClasses();
	void deleteDBClasses();
};

#endif /* _INC_CARCHIVER_LF_Test_MaterialHandling_INCLUDED */

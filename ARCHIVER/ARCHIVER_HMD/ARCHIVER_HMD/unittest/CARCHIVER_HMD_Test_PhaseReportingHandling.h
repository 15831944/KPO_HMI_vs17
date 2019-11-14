#ifndef _INC_CARCHIVER_HMD_Test_PhaseReportingHandling_INCLUDED
#define _INC_CARCHIVER_HMD_Test_PhaseReportingHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"

#include "CGCF_PHASE.h"
#include "CGC_PHASE.h"
#include "CGC_Plant.h"
#include "DEF_GC_ACTION.h"
#include "CPDH_Heat_Data_Phase.h"
#include "CGC_Phase.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CHeatStatusContainer.h"

#include "CARCHIVER_Wrapper.h"

class CEventMessage;

class CARCHIVER_HMD_Test_PhaseReportingHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;
  
  CHeatStatusContainer* m_pHeatStatusContainer;

public:

	~CARCHIVER_HMD_Test_PhaseReportingHandling();

	CARCHIVER_HMD_Test_PhaseReportingHandling(CARCHIVER_Task *Task);

  bool handleHMDPhaseReportRDY(CEventMessage& Event);

  void initDBClasses();
	
  void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_HMD_Test_PhaseReportingHandling_INCLUDED */
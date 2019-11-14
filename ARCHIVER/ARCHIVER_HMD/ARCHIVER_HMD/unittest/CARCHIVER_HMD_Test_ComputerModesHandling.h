#ifndef _INC_CARCHIVER_HMD_Test_ComputerModesHandling_INCLUDED
#define _INC_CARCHIVER_HMD_Test_ComputerModesHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"

#include "CGCF_PHASE.h"
#include "CGC_PHASE.h"
#include "CGC_Plant.h"
#include "DEF_GC_ACTION.h"
#include "CPD_COMP_DATA.h"
#include "CPDF_HEAT_PHASE_DATA.h"
#include "CPDF_HEAT_DATA.h"
#include "CPDB_HEAT_DATA.h"
#include "CPDE_HEAT_DATA.h"
#include "CPDC_BASKET_HEAT.h"
#include "CPDC_BASKET_ENTRY_HEAT.h"
#include "CPD_ANL.h"
#include "CPD_ANL_ENTRY.h"
#include "CPD_RECIPE.h"
#include "CPD_REPORT.h"
#include "CPD_PRETREAT_ANL.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_ACTION.h"
#include "CPD_HEATDATA.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_HEAT.h"
#include "CPP_ORDER.h"
#include "CPD_LADLE.h"
#include "CPD_HEATDATA_LIQADD_ANL.h"
#include "CPD_LADLE_LIFE_DATA.h"
#include "CARCHIVER_Wrapper.h"

class CEventMessage;

class CARCHIVER_HMD_Test_ComputerModesHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_HMD_Test_ComputerModesHandling();

	CARCHIVER_HMD_Test_ComputerModesHandling(CARCHIVER_Task *Task);

  bool handleHMDSetComputerModeRDY(CEventMessage& Event);

  void initDBClasses();
	
  void deleteDBClasses();
};

#endif /* _INC_CARCHIVER_HMD_Test_ComputerModesHandling_INCLUDED */
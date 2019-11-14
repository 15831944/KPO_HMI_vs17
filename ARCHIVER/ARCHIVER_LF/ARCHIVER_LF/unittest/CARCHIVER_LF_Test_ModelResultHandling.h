#ifndef _INC_CARCHIVER_LF_Test_ModelResultHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_ModelResultHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"

#include "CGC_Plant_Container.h"

#include "CGCF_PHASE.h"
#include "CGC_PHASE.h"
#include "CGC_Plant.h"
#include "DEF_GC_ACTION.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES_ANL.h"
#include "CPD_RECIPE_AIM_ENTRY.h"
#include "CHD_RECIPE_AIM.h"
#include "CPD_RECIPE_ENTRY.h"
#include "CARCHIVER_Wrapper.h"
#include "CVPD_RECIPE_CURR_STATUS.h"
#include "CPD_RECIPE.h"

class CEventMessage;

class CARCHIVER_LF_Test_ModelResultHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_ModelResultHandling();

	CARCHIVER_LF_Test_ModelResultHandling(CARCHIVER_Task *Task);

  //bool handleLFModelResultRDY(CEventMessage& Event);

  bool handleLFActualSetpointsRDY(CEventMessage& Event);  
  bool handleLFRecipeSetpointsRDY(CEventMessage& Event);
  void initDBClasses();
	void deleteDBClasses();


};

#endif /* _INC_CARCHIVER_LF_Test_ModelResultHandling_INCLUDED */

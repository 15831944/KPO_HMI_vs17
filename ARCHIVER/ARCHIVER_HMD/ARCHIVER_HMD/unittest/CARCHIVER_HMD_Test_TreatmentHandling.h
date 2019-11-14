#ifndef _INC_CARCHIVER_HMD_Test_TreatmentHandling_INCLUDED
#define _INC_CARCHIVER_HMD_Test_TreatmentHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"

#include "CGCF_PHASE.h"
#include "CGC_PHASE.h"
#include "CGC_Plant.h"
#include "DEF_GC_ACTION.h"
#include "CPD_REPORT.h"
#include "CPD_PRETREATDATA.h"
#include "CPD_ACTION.h"
#include "CPDH_HEAT_DATA.h"
#include "CARCHIVER_Wrapper.h"
#include "CHeatStatusContainer.h"
#include "CPD_HEATDATA.h"
#include "CPD_LADLE_LIFE_DATA.h"
#include "CARCHIVER_Wrapper.h"
#include "CGC_PRD_STAT.h"



class CEventMessage;

class CARCHIVER_HMD_Test_TreatmentHandling : public CARCHIVER_Wrapper
{
private:

  std::vector<std::string> m_LadlePartCode;

protected:

  CARCHIVER_Task* m_pARCHIVER_Task;
  cCBS_Connection* pConnection;
  std::string TrackerName;
  std::string ServerTask;
  CHeatStatusContainer* m_pHeatStatusContainer;

public:

  ~CARCHIVER_HMD_Test_TreatmentHandling();
  CARCHIVER_HMD_Test_TreatmentHandling(CARCHIVER_Task *Task);
  bool handleHMDHeatAnnouncementRDY(CEventMessage& Event);
  bool handleHMDHeatStartRDY(CEventMessage& Event);
  bool handleHMDHeatEndRDY(CEventMessage& Event);
  bool handleHMDHeatCancellationRDY(CEventMessage& Event);
  bool handleHMDHeatDepartureRDY(CEventMessage& Event);  
  void initDBClasses();
	void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_HMD_Test_TreatmentHandling_INCLUDED */

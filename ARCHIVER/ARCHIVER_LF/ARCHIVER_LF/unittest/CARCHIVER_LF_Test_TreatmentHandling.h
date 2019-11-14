
//Dipesh----------------

#ifndef _INC_CARCHIVER_LF_Test_TreatmentHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_TreatmentHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CARCHIVER_Wrapper.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"
#include "CPP_ORDER.h"
#include "CPP_GRADE_PRODPRAC.h"
#include "CPD_HEATDATA.h"
#include "CPD_REPORT.h"
#include "CPP_GRADE_PRODPRAC.h"
#include "CPD_ACTION.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"
#include "CPD_PRETREATDATA.h"
#include "CGC_HEAT_STAT.h"
#include "CPDL_HEAT_DATA.h"
#include "CPDL_CYCL_MEAS_DATA.h"
#include "CPD_LADLE_LIFE_DATA.h"

class CEventMessage;

class CARCHIVER_LF_Test_TreatmentHandling : public CARCHIVER_Wrapper
{
private:
  std::vector<std::string> m_LadlePartCode;
      
protected:

  cCBS_Connection* pConnection;
  std::string TrackerName;
  std::string ServerTask;

public:

  ~CARCHIVER_LF_Test_TreatmentHandling();
  CARCHIVER_LF_Test_TreatmentHandling(CARCHIVER_Task *Task);
  bool handleLFHeatAnnouncementRDY(CEventMessage& Event);
  bool handleLFHeatStartRDY(CEventMessage& Event);
  bool handleLFHeatEndRDY(CEventMessage& Event);
  bool handleLFHeatCancelRDY(CEventMessage& Event);
  bool handleLFUpdateAimDepartureTimeRDY(CEventMessage& Event);
  bool handleLFUpdateAimTemperatureRDY(CEventMessage& Event);
  bool handleLFHeatDepartureRDY(CEventMessage& event);
  void initDBClasses();
	void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_LF_Test_TreatmentHandling_INCLUDED */

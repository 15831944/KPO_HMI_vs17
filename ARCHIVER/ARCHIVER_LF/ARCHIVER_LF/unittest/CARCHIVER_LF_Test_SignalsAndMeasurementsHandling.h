#ifndef _INC_CARCHIVER_LF_Test_SignalsAndMeasurementsHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_SignalsAndMeasurementsHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"


#include "CPDL_HEAT_DATA.h"
#include "CPD_ELEC_SYSTEM.h"
#include "CPDL_HEAT_DATA_MELT.h"
#include "CPDL_CYCL_MEAS_DATA.h"
#include "CPD_COOLWATER.h"
#include "CDM_ProductManagementInterface_Impl.h"
#include "CDM_DataInterface_Impl.h"
#include "CDM_PlantManagementInterface_Impl.h"
#include "CARCHIVER_Wrapper.h"


#include "CPD_ANL.h"
#include "CPD_REPORT.h"
#include "CPD_LADLE_DATA.h"
#include "CGC_Phase.h"
#include "CPDL_STIRR_DATA.h"
#include "CPDL_STIRR_BYPASS_DATA.h"
#include "CPDL_HEAT_DATA.h"
#include "CPD_ELEC_TAPCH.h"

class CEventMessage;

class CARCHIVER_LF_Test_SignalsAndMeasurementsHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;
  cCBS_Connection* pConnection;
  std::string TrackerName;
  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_SignalsAndMeasurementsHandling();
	CARCHIVER_LF_Test_SignalsAndMeasurementsHandling(CARCHIVER_Task *Task);
  bool handleLFCyclicMeasurementRDY(CEventMessage& Event);
  bool handleLFStirringBypassOnOffRDY(CEventMessage& Event, long status);
  bool handleLFHeatingRDY(CEventMessage& Event);
  bool handleLFEmergencyLanceStirringRDY(CEventMessage& Event, bool status);
  bool handleLFStirringStartEndRDY(CEventMessage& Event, long status);
  bool handleLFTempMeasurementRDY(CEventMessage& Event);

  //  bool handleLFElectrodesInOperatingPositionRDY(CEventMessage& Event);
  //  bool handleLFFurnaceBreakerRDY(CEventMessage& Event, long status);
  // These 2 functions are replaced by one fun given below...

  bool handleLFElectrodesInOperatingPositionFurnanceBreakerRDY(CEventMessage& Event,long Status);
  bool handleLFPowerRDY(CEventMessage& Event, long status);
  bool handleLFTapChangeRDY(CEventMessage& Event, long status);
  void initDBClasses();
	void deleteDBClasses();
};

#endif /* _INC_CARCHIVER_LF_Test_SignalsAndMeasurementsHandling_INCLUDED */
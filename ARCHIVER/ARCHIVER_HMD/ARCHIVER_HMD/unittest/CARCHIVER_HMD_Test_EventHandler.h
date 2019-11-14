#ifndef _INC_CARCHIVER_HMD_Test_EventHandler_INCLUDED
#define _INC_CARCHIVER_HMD_Test_EventHandler_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"
#include "CGC_Plant_Container.h"

#include "CARCHIVER_HMD_Test_MaterialHandling.h"
#include "CARCHIVER_HMD_Test_ModelResultHandling.h"
#include "CARCHIVER_HMD_Test_TreatmentHandling.h"
#include "CARCHIVER_HMD_Test_AnalysisHandling.h"
#include "CARCHIVER_HMD_Test_PhaseReportingHandling.h"
#include "CARCHIVER_HMD_Test_ComputerModesHandling.h"
#include "CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling.h"

class CEventMessage;

class CARCHIVER_HMD_Test_EventHandler
: public CARCHIVER_EventHandler
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  CARCHIVER_HMD_Test_MaterialHandling* m_pARCHIVER_MaterialHandling;
  CARCHIVER_HMD_Test_ModelResultHandling* m_pARCHIVER_ModelResultHandling;
  CARCHIVER_HMD_Test_TreatmentHandling* m_pARCHIVER_TreatmentHandling;
  CARCHIVER_HMD_Test_AnalysisHandling* m_pARCHIVER_AnalysisHandling;
  CARCHIVER_HMD_Test_PhaseReportingHandling* m_pARCHIVER_PhaseReportingHandling;
  CARCHIVER_HMD_Test_ComputerModesHandling* m_pARCHIVER_ComputerModesHandling;
  CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling* m_pARCHIVER_SignalsAndMeasurementsHandling ;

  cCBS_Connection* pConnection;

public:

	~CARCHIVER_HMD_Test_EventHandler();

	CARCHIVER_HMD_Test_EventHandler(CARCHIVER_Task *Task);

	virtual bool handleEvent(const FRIESEvent& Event);

	virtual bool handleEvent(CEventMessage& Event);

};

#endif /* _INC_CARCHIVER_HMD_Test_EventHandler_INCLUDED */

#ifndef _INC_CARCHIVER_LF_Test_AnalysisHandling_INCLUDED
#define _INC_CARCHIVER_LF_Test_AnalysisHandling_INCLUDED

#include "CARCHIVER_EventHandler.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CARCHIVER_Task.h"

#include "CGC_PHASE.h"
#include "CPD_ANL.h"
#include "CPD_ANL_ENTRY.h"
#include "CARCHIVER_Wrapper.h"

#include "CPD_REPORT.h"
#include "CPD_LADLE_DATA.h"


class CEventMessage;

class CARCHIVER_LF_Test_AnalysisHandling : public CARCHIVER_Wrapper
{
protected:

	CARCHIVER_Task* m_pARCHIVER_Task;

  cCBS_Connection* pConnection;

  std::string TrackerName;

  std::string ServerTask;

public:

	~CARCHIVER_LF_Test_AnalysisHandling();

	CARCHIVER_LF_Test_AnalysisHandling(CARCHIVER_Task *Task);

  bool handleLFSampleTakenRDY(CEventMessage& Event, bool Steel);

  bool handleLFAnalysisReceivedRDY(CEventMessage& Event, bool Steel);
  
  void initDBClasses();

	void deleteDBClasses();


};

#endif /* _INC_CARCHIVER_LF_Test_AnalysisHandling_INCLUDED */

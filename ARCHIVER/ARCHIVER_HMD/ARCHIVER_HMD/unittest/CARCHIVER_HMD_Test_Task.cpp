// Copyright (C) 2007 SMS Demag AG

#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_StdInitBase.h"
 
#include "CARCHIVER_HMD_Test_EventHandler.h"
#include "CARCHIVER_HMD_Test_Task.h"
//#include "CARCHIVER_HMD_Test_MaterialHandling.h"


CARCHIVER_HMD_Test_Task* CARCHIVER_HMD_Test_Task::m_Instance = 0;

CARCHIVER_HMD_Test_Task::CARCHIVER_HMD_Test_Task()
{
}

CARCHIVER_HMD_Test_Task::~CARCHIVER_HMD_Test_Task()
{
}

bool CARCHIVER_HMD_Test_Task::initialize()
{
  bool RetCode = true;
  try
  {
    RetCode = cCBS_Task::initialize();
    
    cCBS_StdEvent_Task *pEventTask = cCBS_StdEvent_Task::getInstance();

    // registering event handler
    CARCHIVER_HMD_Test_EventHandler * pEventHandler = new CARCHIVER_HMD_Test_EventHandler(this);
    
    if (pEventTask)
    {
      pEventTask->registerEventHandler(pEventHandler);
    }
  }
  catch (...)
  {
    log("EXCEPTION: CARCHIVER_HMD_Test_Task::initialize!");
  }
  return RetCode;
}

CARCHIVER_HMD_Test_Task* CARCHIVER_HMD_Test_Task::getInstance()
{
	if ( m_Instance == 0 )
	{
		m_Instance = new CARCHIVER_HMD_Test_Task();
	}
	return m_Instance;
}

void CARCHIVER_HMD_Test_Task::setDataProvider(CARCHIVER_HMD_Test_DataProvider * pr)
{
  pTest_DataProvider = pr;
}

long CARCHIVER_HMD_Test_Task::getLastRowFromPD_Anl(const string& HeatID, const string& TreatID, const string& Plant, cCBS_Connection* pConnection)
{
  bool RetValue = false;
  std::string ActPlant;
  long RowAmount = 0;
  long MaxCounterRow = -1;
  long ActualCounter = 0;
  long MaxCounter = 0;

  CPD_ANL* m_pPD_Anl = 0;

  if (!pConnection)
    return -1;

  m_pPD_Anl = new CPD_ANL(pConnection);


  if (m_pPD_Anl->select(HeatID, TreatID, Plant))
  {
    RowAmount = m_pPD_Anl->getLastRow();
    for ( int i = 1; i <= RowAmount; ++i)
    {
      ActualCounter = m_pPD_Anl->getANL_COUNTER(i);
      if (MaxCounter < ActualCounter)
      {
        MaxCounter = ActualCounter;
        MaxCounterRow = i;
      }
    }
  }

  if (m_pPD_Anl)              { delete m_pPD_Anl; m_pPD_Anl = 0;}

  return MaxCounterRow;
}

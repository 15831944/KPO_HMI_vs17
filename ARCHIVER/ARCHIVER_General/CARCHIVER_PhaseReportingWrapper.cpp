// Copyright (C) 2007 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"
#include "cCBS_StdCORBA_Task.h"
#include "CEventMessage.h"

#include "CARCHIVER_Task.h"
#include "CARCHIVER_PhaseReportingWrapper.h"



//##ModelId=45E56E2B0216
CARCHIVER_PhaseReportingWrapper::CARCHIVER_PhaseReportingWrapper() 
{
}

//##ModelId=45E56E2C00ED
CARCHIVER_PhaseReportingWrapper::~CARCHIVER_PhaseReportingWrapper()
{
  deleteDBClasses();
}

//##ModelId=45E56E350011
bool CARCHIVER_PhaseReportingWrapper::handleHeatProductionPhaseReport(CEventMessage &Event)
{
	return true;
}

//##ModelId=45E56E2E0249
void CARCHIVER_PhaseReportingWrapper::initDBClasses()
{
  cCBS_StdConnection *pConnection = getStdConnection();

  m_pGC_Plant_Container  = new CGC_Plant_Container(pConnection);
  m_pGC_PHASE            = new CGC_PHASE(pConnection);
  m_pPD_SAMPLE           = new CPD_SAMPLE(pConnection);
  m_pPD_SAMPLE_ENTRY     = new CPD_SAMPLE_ENTRY(pConnection);
  m_pPD_ACTION           = new CPD_ACTION(pConnection);
  m_pPP_HEAT_PLANT       = new CPP_HEAT_PLANT(pConnection);
  m_pPP_HEAT             = new CPP_HEAT(pConnection);
  m_pGC_HEAT_STATUS        = new CGC_HEAT_STATUS(pConnection);
}

//##ModelId=45E56E2F017A
void CARCHIVER_PhaseReportingWrapper::deleteDBClasses()
{
  if (m_pGC_Plant_Container) { delete m_pGC_Plant_Container; m_pGC_Plant_Container = 0; }
  if (m_pGC_PHASE)            {delete m_pGC_PHASE; m_pGC_PHASE = 0;}
  if (m_pPD_SAMPLE)              {delete m_pPD_SAMPLE; m_pPD_SAMPLE = 0;}
  if (m_pPD_SAMPLE_ENTRY)        {delete m_pPD_SAMPLE_ENTRY; m_pPD_SAMPLE_ENTRY = 0;}
  if (m_pPD_ACTION)           {delete m_pPD_ACTION; m_pPD_ACTION = 0;}
  if (m_pPP_HEAT_PLANT)       {delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_HEAT)             {delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pGC_HEAT_STATUS)        {delete m_pGC_HEAT_STATUS; m_pGC_HEAT_STATUS = 0;}
}


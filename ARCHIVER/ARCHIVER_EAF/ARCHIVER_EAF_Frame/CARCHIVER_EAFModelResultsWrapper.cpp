// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"

#include "CSMC_DataProvider_Impl.h"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_DBExc.h"

#include "CIntfData.h"
#include "CDataConversion.h"
#include "CSMC_EventLogFrameController.h"

#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_RECIPE_SOURCE.h"
#include "DEF_GC_RECIPE_STATUS.h"
#include "DEF_GC_PHASE.h"

#include "CGC_PhaseContainer.h"

#include "CARCHIVER_Task.h"
#include "CARCHIVER_EAFModelResultsWrapper.h"


//##ModelId=41A367AF0134
CARCHIVER_EAFModelResultsWrapper::CARCHIVER_EAFModelResultsWrapper()
:CARCHIVER_ModelResultWrapper()
,m_pGC_PhaseContainer(0)
{
}

//##ModelId=419CC21300A0
CARCHIVER_EAFModelResultsWrapper::~CARCHIVER_EAFModelResultsWrapper()
{
  deleteDBClasses();
}

//##ModelId=415299D10072
bool CARCHIVER_EAFModelResultsWrapper::doOnActualSetpoints(CEventMessage& Event)
{
  bool RetValue = true;
  // Handling of actual setpoints and recipe setpoints moved to ModelResultWrapper
  return RetValue;
}

//##ModelId=41ADE222018C
void CARCHIVER_EAFModelResultsWrapper::deleteDBClasses()
{
  CARCHIVER_ModelResultWrapper::deleteDBClasses();

  if (m_pGC_PhaseContainer)     {delete m_pGC_PhaseContainer; m_pGC_PhaseContainer = 0;}
}

//##ModelId=41ADE23002EB
void CARCHIVER_EAFModelResultsWrapper::initDBClasses()
{
  std::string Plant = DEF_GC_PLANT_DEF::EAF;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("PLANT", "Plant", Plant);
  
  if ( m_pArchiverTask )
  {
    cCBS_StdInitBase::getInstance()->replaceWithEntry(m_pArchiverTask->getTaskName(),"Plant",Plant);
  }

  CARCHIVER_ModelResultWrapper::initDBClasses();

  cCBS_StdConnection *pConnection = getStdConnection();

  m_pGC_PhaseContainer      = new CGC_PhaseContainer(pConnection, Plant);
}  

bool CARCHIVER_EAFModelResultsWrapper::doOnRecipeSetpoints(CEventMessage& Event)
{
  bool RetValue = true;
  // Handling of actual setpoints and recipe setpoints moved to ModelResultWrapper
  return RetValue;
}

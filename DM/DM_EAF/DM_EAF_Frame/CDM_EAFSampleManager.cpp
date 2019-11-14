// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CEventMessage.h"
#include "CSMC_EventLogFrameController.h"
#include "CDM_EAFSampleManager.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_PLANT_DEF.h"

CDM_EAFSampleManager::~CDM_EAFSampleManager()
{
	// ToDo: Add your specialized code here and/or call the base class
}

CDM_EAFSampleManager::CDM_EAFSampleManager() 
{
  setDefaultProcessStage(std::string(DEF_PROCESS_STAGE::InProcess));

  insertProcessStage( EAF_EvMsg::evEAFHeatAnnouncement,DEF_PROCESS_STAGE::BeforeProcess);
  insertProcessStage( EAF_EvMsg::evEAFHeatStart,DEF_PROCESS_STAGE::InProcess);
  insertProcessStage( EAF_EvMsg::evEAFHeatEnd,DEF_PROCESS_STAGE::AfterProcess);
   
  insertType(EAF_EvMsg::evEAFSteelSampleTaken,DEF_GC_MEASUREMENT_TYPE::Steel);
  insertType(EAF_EvMsg::evEAFSlagSampleTaken,DEF_GC_MEASUREMENT_TYPE::Slag);
  insertType(EAF_EvMsg::evEAFTempMeasurement,DEF_GC_MEASUREMENT_TYPE::Temp);

  init();
}

std::string CDM_EAFSampleManager::createSampleCodeFromScratch(std::string& ProductID, long ActSampleType, const std::string ActPlant, const std::string ActProcessStage, long ActSampleNo)
{
  std::string NewSampleCode;
  std::string Plant         = ActPlant;
  std::string ProcessStage  = ActProcessStage;
  long SampleNo             = ActSampleNo;
  long SampleType           = ActSampleType;  

  if (Plant == DEF_GC_PLANT_DEF::EAF)
      Plant = "E1";
  //if (Plant == DEF_GC_PLANT_DEF::EAFCr)
  //    Plant = "F1";
  
  // get information according to actual product state
  std::string ActSampleCode = getActSampleCode(ProductID,SampleType);
  if ( SampleNo == DEF::Inv_Long )
  {
    SampleNo = getSampleNo(ActSampleCode);
  }
  if ( SampleType == DEF::Inv_Long )
  {
    SampleType = getSampleType(ActSampleCode);
  }
  if ( Plant == DEF::Inv_String )
  {
    Plant = getPlantId(ActSampleCode);
  }
  if ( ProcessStage == DEF::Inv_String )
  {
    ProcessStage = getProcessStage(ActSampleCode);
  }

  if ( SampleNo      != DEF::Inv_Long   && 
       Plant         != DEF::Inv_String && 
       SampleType    != DEF::Inv_Long   && 
       ProcessStage  != DEF::Inv_String   )
  {
    NewSampleCode = getSampleCode(SampleType, Plant, ProcessStage, SampleNo);
  }
  else
  {
    std::string DefaultSampleCode = getActSampleCode(ProductID,ActSampleType);

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_UsingDefaultSample(sMessage,"",DefaultSampleCode.c_str());

    NewSampleCode = DefaultSampleCode;
  }
  return NewSampleCode;
}

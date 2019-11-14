// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CEventMessage.h"
#include "CSMC_EventLogFrameController.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "CDM_LFSampleManager.h"
#include "DEF_GC_PLANT_DEF.h"
#include "DEF_GC_PLANT_DEF.h"

CDM_LFSampleManager::~CDM_LFSampleManager()
{
}

CDM_LFSampleManager::CDM_LFSampleManager() 
{
  setDefaultProcessStage(std::string(DEF_PROCESS_STAGE::InProcess));

  insertProcessStage( LF_EvMsg::evLFHeatAnnouncement,DEF_PROCESS_STAGE::BeforeProcess);
  insertProcessStage( LF_EvMsg::evLFHeatStart,DEF_PROCESS_STAGE::InProcess);
  insertProcessStage( LF_EvMsg::evLFHeatEnd,DEF_PROCESS_STAGE::AfterProcess);
   
  insertType(LF_EvMsg::evLFSteelSampleTaken,DEF_GC_MEASUREMENT_TYPE::Steel);
  insertType(LF_EvMsg::evLFSlagSampleTaken,DEF_GC_MEASUREMENT_TYPE::Slag);
  insertType(LF_EvMsg::evLFTempMeasurement,DEF_GC_MEASUREMENT_TYPE::Temp);

  init();
}

std::string CDM_LFSampleManager::createSampleCodeFromScratch(std::string& ProductID, long ActSampleType, const std::string ActPlantID, const std::string ActProcessStage, long ActSampleNo)
{
  std::string NewSampleCode;
  std::string PlantID         = ActPlantID;
  std::string ProcessStage    = ActProcessStage;
  long SampleNo               = ActSampleNo;
  long SampleType             = ActSampleType;  

  if (PlantID == std::string(DEF_GC_PLANT_DEF::LF))
      PlantID = "L1";  

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
  if ( PlantID == DEF::Inv_String )
  {
    PlantID = getPlantId(ActSampleCode);
  }
  if ( ProcessStage == DEF::Inv_String )
  {
    ProcessStage = getProcessStage(ActSampleCode);
  }

  if ( SampleNo      != DEF::Inv_Long   && 
       PlantID       != DEF::Inv_String && 
       SampleType    != DEF::Inv_Long   && 
       ProcessStage  != DEF::Inv_String   )
  {
    NewSampleCode = getSampleCode(SampleType, PlantID, ProcessStage, SampleNo);
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

void CDM_LFSampleManager::initProductSampleInformation(const std::string& ProductID, const std::string& Plant)
{
  std::vector<long>::iterator it;
  std::string PlantID = Plant;
  if (PlantID == std::string(DEF_GC_PLANT_DEF::LF))
      PlantID = "L1";  

  for( it = m_SampleTypeList.begin(); it != m_SampleTypeList.end() ; ++ it )
  {
    sSampleInformationData SampleInformationData;

    SampleInformationData.SampleType    = (*it);
    SampleInformationData.SampleNo = 1 ;
    SampleInformationData.ProcessStage  = m_DefaultProcessStage;
    SampleInformationData.Plant         = PlantID;

    //std::multimap<std::string,sSampleInformationData> m_ProductSampleInformationList;
    m_ProductSampleInformationList.insert(std::pair <std::string,sSampleInformationData>(ProductID,SampleInformationData));
  }

  log("CDM_SampleManager::initProductSampleInformation",2);
  showContent(ProductID);
}
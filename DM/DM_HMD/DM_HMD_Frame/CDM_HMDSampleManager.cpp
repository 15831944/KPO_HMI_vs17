// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CSMC_EventLogFrameController.h"

#include "CEventMessage.h"
//#include "DEF_GC_PROBETYPE.h"
#include "DEF_GC_MEASUREMENT_TYPE.h"
#include "DEF_GC_PLANT.h"
#include "cCBS_StdLog_Task.h"
#include "CDM_HMDSampleManager.h"


//##ModelId=45139A71038B
CDM_HMDSampleManager::~CDM_HMDSampleManager()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=45139A71038D
CDM_HMDSampleManager::CDM_HMDSampleManager() 
{
	setDefaultProcessStage(std::string(DEF_PROCESS_STAGE::InProcess));

	insertProcessStage( HMD_EvMsg::evHMDHeatAnnouncement,std::string(DEF_PROCESS_STAGE::BeforeProcess));
	insertProcessStage( HMD_EvMsg::evHMDHeatStart,std::string(DEF_PROCESS_STAGE::InProcess));
	insertProcessStage( HMD_EvMsg::evHMDHeatEnd,std::string(DEF_PROCESS_STAGE::AfterProcess));
   
  insertType(HMD_EvMsg::evHMDHotMetalSampleTaken,DEF_GC_MEASUREMENT_TYPE::HM);
  insertType(HMD_EvMsg::evHMDTempMeasurement,DEF_GC_MEASUREMENT_TYPE::Temp);

  init();
}

//##ModelId=45139A71038E
std::string CDM_HMDSampleManager::createSampleCodeFromScratch(std::string& ProductID, long ActProbeType, const std::string ActPlantID, const std::string ActProcessStage, long ActSampleCounter)
{
  std::string NewSampleCode;
  std::string PlantID         = ActPlantID;
  std::string ProcessStage    = ActProcessStage;
  long SampleCounter          = ActSampleCounter;
  long ProbeType              = ActProbeType;  

  //if (PlantID == std::string(DEF_GC_PLANT::HMD_1))
  //    PlantID = "HMD1";
  //else if (PlantID == std::string(DEF_GC_PLANT::HMD_2))
  //    PlantID = "HMD2";
	//else
  //  PlantID = DEF_DB_PLANT::HMD;


  // get information according to actual product state
  std::string ActSampleCode = getActSampleCode(ProductID,ProbeType);
  if ( SampleCounter == DEF::Inv_Long )
  {
//    SampleCounter = getSampleCounter(ActSampleCode);
  }
  if ( ProbeType == DEF::Inv_Long )
  {
//    ProbeType = getProbeType(ActSampleCode);
  }
  if ( PlantID == DEF::Inv_String )
  {
    PlantID = getPlantId(ActSampleCode);
  }
  if ( ProcessStage == DEF::Inv_String )
  {
    ProcessStage = getProcessStage(ActSampleCode);
  }

  if ( SampleCounter != DEF::Inv_Long   && 
       PlantID       != DEF::Inv_String && 
       ProbeType     != DEF::Inv_Long   && 
       ProcessStage  != DEF::Inv_String   )
  {
    NewSampleCode = getSampleCode(ProbeType, PlantID, ProcessStage, SampleCounter);
  }
  else
  {
    std::string DefaultSampleCode = getActSampleCode(ProductID,ActProbeType);

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorHandlingSample(sMessage, "", "", PlantID.c_str(), DefaultSampleCode.c_str());

    NewSampleCode = DefaultSampleCode;
  }
  return NewSampleCode;
}

//##ModelId=45139A710394
void CDM_HMDSampleManager::initProductSampleInformation(const std::string& ProductID, const std::string& Plant)
{
  //std::vector<long>::iterator it;
  //std::string PlantID = Plant;
  //  
  ////if (PlantID == std::string(DEF_GC_PLANT::HMD_1))
  ////  PlantID = "HMD1";
  ////else if (PlantID == std::string(DEF_GC_PLANT::HMD_2))
  ////  PlantID = "HMD2";
  ////else
  ////  PlantID = DEF_DB_PLANT::HMD;

  ////for( it = m_ProbeTypeList.begin(); it != m_ProbeTypeList.end() ; ++ it )
  ////{
  ////  sSampleInformationData SampleInformationData;

  ////  SampleInformationData.SampleType    = (*it);
  ////  SampleInformationData.SampleCounter = 1 ;
  ////  SampleInformationData.ProcessStage  = m_DefaultProcessStage;
  ////  SampleInformationData.Plant         = PlantID;

  ////  //std::multimap<std::string,sSampleInformationData> m_ProductSampleInformationList;
  ////  m_ProductSampleInformationList.insert(std::pair <std::string,sSampleInformationData>(ProductID,SampleInformationData));
  ////}

  //log("CDM_HMDSampleManager::initProductSampleInformation",2);
  //showContent(ProductID);

  deleteProductSampleInformation(ProductID);

  log("CDM_SampleManager::initProductSampleInformation",3);
  std::vector<long>::iterator it;

  for( it = m_SampleTypeList.begin(); it != m_SampleTypeList.end() ; ++ it )
  {
    sSampleInformationData SampleInformationData;

    SampleInformationData.SampleType    = (*it);
    SampleInformationData.SampleNo      = 1 ;
    SampleInformationData.ProcessStage  = m_DefaultProcessStage;
    SampleInformationData.Plant         = Plant;

    //std::multimap<std::string,sSampleInformationData> m_ProductSampleInformationList;
    m_ProductSampleInformationList.insert(std::pair <std::string,sSampleInformationData>(ProductID,SampleInformationData));
  }
  showContent(ProductID);

}

void CDM_HMDSampleManager::setDefaultProcessStage(const std::string& value)
{
	m_DefaultProcessStage = value;
}

void CDM_HMDSampleManager::insertProcessStage(const std::string& EventMessage, const std::string& Stage)
{
  m_ProcessStageEventList.insert( std::pair<std::string,std::string>(EventMessage,Stage) );
}

void CDM_HMDSampleManager::insertType(const std::string& EventMessage,  long Type)
{
  m_SampleTypeEventList.insert( std::pair <std::string,long>(EventMessage,Type) );
}

std::string CDM_HMDSampleManager::getActSampleCode(const std::string& ProductID,  long SampleType)
{
  std::string PlantId              = getPlant(ProductID,SampleType);
  std::string ProductProcessStage  = getProductProcessStage(ProductID);
  long ProductSampleNo        = getProductSampleNo(ProductID,SampleType);

  std::string Value = m_FormattedSampleCode.getSampleCode(SampleType,PlantId,ProductProcessStage,ProductSampleNo);

  return Value;
}

std::string CDM_HMDSampleManager::getPlant(const std::string& ProductID, long Type)
{
  std::string Plant;

  std::multimap<std::string,sSampleInformationData>::iterator it;

  for( it = m_ProductSampleInformationList.begin(); it != m_ProductSampleInformationList.end() ; ++ it )
  {
    if ( it->first == ProductID && it->second.SampleType == Type ) // one entry for product and type
    {
      Plant = it->second.Plant;
      break;
    }
  }

  return Plant;
}

std::string CDM_HMDSampleManager::getProductProcessStage(const std::string& ProductID)
{
  std::string ProcessStage = m_DefaultProcessStage;

  std::multimap<std::string,sSampleInformationData>::iterator it;

  // all stages for product are identical
  it = m_ProductSampleInformationList.find(ProductID);
  if ( it != m_ProductSampleInformationList.end() )
  {
    ProcessStage = it->second.ProcessStage;
  }

  return ProcessStage;
}

long CDM_HMDSampleManager::getProductSampleNo(const std::string& ProductID, long Type)
{
  long ProductSampleNo = 0;

  std::multimap<std::string,sSampleInformationData>::iterator it;

  for( it = m_ProductSampleInformationList.begin(); it != m_ProductSampleInformationList.end() ; ++ it )
  {
    if ( it->first == ProductID && it->second.SampleType == Type ) // one entry for product and type
    {
      ProductSampleNo = it->second.SampleNo;
      break;
    }
  }

  return ProductSampleNo;
}

std::string CDM_HMDSampleManager::getProcessStage(const std::string& SampleCode)
{
  return this->m_FormattedSampleCode.getProcessStage(SampleCode);
}

std::string CDM_HMDSampleManager::getSampleCode( long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long SampleNo)
{
  return this->m_FormattedSampleCode.getSampleCode(SampleType,PlantID, PlantNo, ProcessStage,SampleNo);
}

//##ModelId=43848BF4023E
std::string CDM_HMDSampleManager::getSampleCode( long SampleType, const std::string PlantID, const std::string ProcessStage, long SampleNo)
{
  return this->m_FormattedSampleCode.getSampleCode(SampleType,PlantID,ProcessStage,SampleNo);
}

//##
std::string CDM_HMDSampleManager::getSampleCode( long SampleType, const std::string Location, long SampleNo )
{
  return this->m_FormattedSampleCode.getSampleCode(SampleType, SampleNo, Location);
}

void CDM_HMDSampleManager::init()
{
  m_MaxSampleNo = m_FormattedSampleCode.getMaxCounter();
}

void CDM_HMDSampleManager::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);

}

void CDM_HMDSampleManager::showContent(const std::string& ProductID)
{
  std::multimap<std::string,sSampleInformationData>::iterator it;

  std::stringstream Content;

  Content << "Content of actual Sample information : for Product " << ProductID << std::endl;
  Content << " Plant |Type |Stage |SampleNo \n";

  for( it = m_ProductSampleInformationList.begin(); it != m_ProductSampleInformationList.end() ; ++ it )
  {
    if ( it->first == ProductID )
    {
      Content << " " << it->second.Plant;
      Content << "    |" << it->second.SampleType;
      Content << "     |" << it->second.ProcessStage;
      Content << "     |" << it->second.SampleNo;
      Content << std::endl ;
    }
  }

  log(Content.str(),3);
}

void CDM_HMDSampleManager::removeProcessStages(const std::string& ProductID)
{
  std::multimap<std::string,sSampleInformationData>::iterator it;
  it = m_ProductSampleInformationList.begin();

  while (it != m_ProductSampleInformationList.end())
  {
    if ( it->first == ProductID)
    {
      m_ProductSampleInformationList.erase(it);
      it = m_ProductSampleInformationList.begin();
    }
    else
    {
      ++it;
    }
  }
}

void CDM_HMDSampleManager::deleteProductSampleInformation(const std::string& ProductID)
{
  log("CDM_SampleManager::deleteProductSampleInformation",3);

  std::multimap<std::string,sSampleInformationData>::iterator it;

  std::stringstream ContentDeleted;

  ContentDeleted << "INFO: Delete Sample information : for Product " << ProductID << std::endl;
  ContentDeleted << " Plant Type Stage SampleNo \n";

  for( it = m_ProductSampleInformationList.begin(); it != m_ProductSampleInformationList.end() ; ++ it )
  {
    if ( it->first == ProductID )
    {
      ContentDeleted << " " << it->second.Plant;
      ContentDeleted << " " << it->second.SampleType;
      ContentDeleted << " " << it->second.ProcessStage;
      ContentDeleted << " " << it->second.SampleNo;
      ContentDeleted << std::endl ;
    }
  }
  m_ProductSampleInformationList.erase(ProductID);

  log(ContentDeleted.str(),3);
}
std::string CDM_HMDSampleManager::getPlantId(const std::string& SampleCode)
{
  return this->m_FormattedSampleCode.getPlantId(SampleCode);
}
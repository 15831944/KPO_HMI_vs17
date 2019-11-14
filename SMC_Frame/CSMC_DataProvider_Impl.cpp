// Copyright (C) 2011 SMS Diemag AG
#include <fstream>
#include <sstream>
#include "CDataConversion.h"
#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_RuntimeController.h"

#include "CSMC_DataProvider_Impl.h"

// **********************************************************************************************
// ***** following functions are helpers on CORBA Data
// **********************************************************************************************
sAnalysis CSMC_DataProvider_Impl::getsAnalysis(seqAnalysis & SeqAnalysis, const std::string Element)
{
  sAnalysis Analysis;
  // preset
  Analysis.Concentration  = -1.;
  Analysis.Element        = Element.c_str();

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  {
    sAnalysis ActAnalysis;
    CIntfData::getAt(ActAnalysis,SeqAnalysis,i);
    if ( std::string(ActAnalysis.Element) == Element )
    {
      Analysis.Concentration  = ActAnalysis.Concentration;
      Analysis.Element        = ActAnalysis.Element;
    }
  }

  return Analysis;
}

sAnalysisString CSMC_DataProvider_Impl::getsAnalysisString(seqAnalysis & SeqAnalysis, const std::string Element)
{
  sAnalysisString Analysis;
  // preset
  Analysis.Concentration  = "-";
  Analysis.Element        = Element.c_str();

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  {
    sAnalysis ActAnalysis;
    CIntfData::getAt(ActAnalysis,SeqAnalysis,i);
    
    if ( std::string(ActAnalysis.Element) == Element )
    {
      Analysis.Concentration  = CDataConversion::DoubleToString( CDataConversion::RoundToDecimals(ActAnalysis.Concentration,4) ).c_str();
      Analysis.Element        = ActAnalysis.Element;
    }
  }

  return Analysis;
}


bool CSMC_DataProvider_Impl::updateAnalysisValue(seqAnalysis & SeqAnalysis, const std::string Element, double Concentration)
{
  bool RetValue = false;

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  {
    sAnalysis ActAnalysis;
    CIntfData::getAt(ActAnalysis,SeqAnalysis,i);

    if ( std::string(ActAnalysis.Element) == Element )
    {
      ActAnalysis.Concentration = Concentration;

      CIntfData::setAt(SeqAnalysis,ActAnalysis,i);

      RetValue = true;
    }
  }

  return RetValue;
}


bool CSMC_DataProvider_Impl::insertSeqAnalysis(seqAnalysis & SeqActAnalysis, const seqAnalysis SeqAnalysis)
{
  bool RetValue = false;

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  {
    sAnalysis ActAnalysis;
    sAnalysis Analysis;
    CIntfData::getAt(Analysis,SeqAnalysis,i);

    ActAnalysis.Element       = Analysis.Element;
    ActAnalysis.Concentration = Analysis.Concentration;

    CIntfData::insert(SeqActAnalysis,ActAnalysis);

    RetValue = true;
  }

  return RetValue;
}

bool CSMC_DataProvider_Impl::insertSeqSample(seqSample & SeqActSample, const seqSample SeqSample)
{
  bool RetValue = false;

  for( long i = 0 ; i < CIntfData::getLength(SeqSample); ++i )
  {
    sSample ActSample;
    sSample Sample;
    CIntfData::getAt(Sample,SeqSample,i);

    ActSample.MeasName   = Sample.MeasName;
    ActSample.MeasValue  = Sample.MeasValue;

    CIntfData::insert(SeqActSample,ActSample);

    RetValue = true;
  }

  return RetValue;
}

bool CSMC_DataProvider_Impl::removeAnalysisEntry(seqAnalysis & SeqAnalysis, const std::string Element)
{
  bool RetValue = false;

  seqAnalysis NewSeqAnalysis;

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  {
    sAnalysis ActAnalysis;
    CIntfData::getAt(ActAnalysis,SeqAnalysis,i);

    if ( std::string(ActAnalysis.Element) == Element )
    {
      RetValue = true;
    }
    else
    {
      CIntfData::insert(NewSeqAnalysis,ActAnalysis);
    }
  }

  if ( RetValue ) 
  {
    SeqAnalysis = NewSeqAnalysis;
  }

  return RetValue;
}

bool CSMC_DataProvider_Impl::removeSampleEntry(seqSample & SeqSample, const std::string MeasName)
{
  bool RetValue = false;

  seqSample NewSeqSample;

  for( long i = 0 ; i < CIntfData::getLength(SeqSample); ++i )
  {
    sSample ActSample;
    CIntfData::getAt(ActSample,SeqSample,i);

    if ( std::string(ActSample.MeasName) == MeasName )
    {
      RetValue = true;
    }
    else
    {
      CIntfData::insert(NewSeqSample,ActSample);
    }
  }

  if ( RetValue ) 
  {
    SeqSample = NewSeqSample;
  }

  return RetValue;
}



bool CSMC_DataProvider_Impl::updateSampleValue(seqSample & SeqSample, const std::string MeasName, double MeasValue)
{
  bool RetValue = false;

  for( long i = 0 ; i < CIntfData::getLength(SeqSample); ++i )
  {
    sSample ActSample;
    CIntfData::getAt(ActSample,SeqSample,i);

    if ( std::string(ActSample.MeasName) == MeasName )
    {
      ActSample.MeasValue = MeasValue;

      CIntfData::setAt(SeqSample,ActSample,i);

      RetValue = true;
    }
  }

  return RetValue;
}

void CSMC_DataProvider_Impl::insertSampleValue(seqSample & SeqSample, const std::string MeasName, double MeasValue)
{
  sSample ActSample;
  ActSample.MeasName  = MeasName.c_str();
  ActSample.MeasValue = MeasValue;

  CIntfData::insert(SeqSample,ActSample);
}

void CSMC_DataProvider_Impl::insertAnalysisValue(seqAnalysis & SeqAnalysis, const std::string Element, double Concentration)
{
  sAnalysis ActAnalysis;

  ActAnalysis.Element       = Element.c_str();
  ActAnalysis.Concentration = Concentration;

  CIntfData::insert(SeqAnalysis,ActAnalysis);
}


sSample CSMC_DataProvider_Impl::getsSample(seqSample & SeqSample, const std::string MeasName)
{
  sSample Sample;
  // preset
  Sample.MeasValue  = DEF::Inv_Double;
  Sample.MeasName   = MeasName.c_str();

  for( long i = 0 ; i < CIntfData::getLength(SeqSample); ++i )
  {
    sSample ActSample;
    CIntfData::getAt(ActSample,SeqSample,i);
    if ( std::string(ActSample.MeasName) == MeasName )
    {
      Sample.MeasValue  = ActSample.MeasValue;
      Sample.MeasName   = ActSample.MeasName;
    }
  }

  return Sample;
}

double CSMC_DataProvider_Impl::getAnalysisValue(seqAnalysis & SeqAnalysis, const std::string MeasName)
{
  sAnalysis Analysis = CSMC_DataProvider_Impl::getsAnalysis(SeqAnalysis, MeasName);

  return Analysis.Concentration;
}


double CSMC_DataProvider_Impl::getSampleValue(seqSample & SeqSample, const std::string MeasName)
{
  sSample Sample = CSMC_DataProvider_Impl::getsSample(SeqSample, MeasName);

  return Sample.MeasValue;
}

bool CSMC_DataProvider_Impl::addBatch(seqBatch & SeqBatch, sBatch NewBatch)
{
  bool RetValue = false;

  for( long i = 0 ; i < CIntfData::getLength(SeqBatch); ++i )
  {
    sBatch ActBatch;
    CIntfData::getAt(ActBatch,SeqBatch,i);

    // we accept only valid materials
    if ( std::string(NewBatch.MatCode).empty() )
    {
      continue;
    }

    // we accept only valid masses
    if ( std::string(ActBatch.MatCode) == std::string(NewBatch.MatCode) )
    {
      if ( NewBatch.Mass > 0. )
      {
        ActBatch.Mass += NewBatch.Mass;

        CIntfData::setAt(SeqBatch,ActBatch,i);

        RetValue = true;
      }
    }
  }

  // not yet handled, check if NewBatch can be inserted
  if ( !RetValue )
  {
    if ( NewBatch.Mass > 0. && !std::string(NewBatch.MatCode).empty() )
    {
      CIntfData::insert(SeqBatch,NewBatch);
      RetValue = true;
    }
  }

  return RetValue;
}




/////////////////////////////////////////////////////////////////
//
// We let our base class store and retrieve the compound data 
// types as Corba-Any. Here only trivial interfacing
//
/////////////////////////////////////////////////////////////////

CSMC_DataProvider_Impl::CSMC_DataProvider_Impl()
:m_pCorbaTask(0)
{
  m_pCorbaTask = cCBS_StdCORBA_Task::getInstance();
  loadRules();
  loadEvaluationList();

}

CSMC_DataProvider_Impl::~CSMC_DataProvider_Impl()
{
}

void CSMC_DataProvider_Impl::loadEvaluationList()
{
  std::vector<std::string> EvaluationList;
  std::vector<std::string>::iterator it;

  cCBS_StdInitBase::getInstance()->getEntryList("DATAPROVIDER", "EvaluationList", EvaluationList);

  for ( it = EvaluationList.begin(); it != EvaluationList.end(); it++)
  {
    m_EvaluationList.insert( (*it) );
  }

}


void CSMC_DataProvider_Impl::log(const std::string& Message, long Level)
{
  CSMC_RuntimeController RuntimeController("CSMC_DataProvider_Impl::log");

  if (m_pCorbaTask)
  {
    if ( getTraceLevel() >= Level )
    {
      m_pCorbaTask->log(Message,Level);
    }
  }
}

void CSMC_DataProvider_Impl::EventLogExc(const std::string & Message, const std::string& Function, const std::string& Action)
{
  std::string ActMessage;
  ActMessage = m_ProviderName + " " + Message;

  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage,ActMessage.c_str(), Function.c_str(), Action.c_str());
}

void CSMC_DataProvider_Impl::EventLogReadFailure(const std::string& Message)
{

  std::string ActMessage("System cannot provide data for ");
  ActMessage += m_ProviderName + " " + Message;

  log(ActMessage,5);
}

void CSMC_DataProvider_Impl::EventLogValidationFailure(const std::string& Message)
{
  CSMC_RuntimeController RuntimeController("CSMC_DataProvider_Impl::EventLogValidationFailure");

  std::string ActMessage;
  ActMessage = m_ProviderName + " " + Message;

  CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_DataProviderValidation(sMessage,ActMessage.c_str());

}

void CSMC_DataProvider_Impl::loadRules()
{
  cCBS_StdInitBase *pInitBase = cCBS_StdInitBase::getInstance();
  
  std::string DataProviderRuleSet;

  pInitBase->replaceWithEntry("PATH", "DataProviderRuleSet", DataProviderRuleSet);

  if (!DataProviderRuleSet.empty())
  {
    DataProviderRuleSet =  pInitBase->getXPACT_SMC() + DataProviderRuleSet;

    std::ifstream in(DataProviderRuleSet.c_str());
    std::string lineBuffer;
    std::string Key;

    // read line of RuleSet file
    while (getline(in, lineBuffer))
    {
      std::string Name;
      std::string Type;
      std::string Comp;

      std::istringstream istr(lineBuffer);

      // processing empty and comment lines
      if(lineBuffer.empty() || lineBuffer.substr(0,2) == "//")
      {
        continue;
      }

      // processing [Block], will be used as "key" later on
      if(lineBuffer.substr(0,1) == "[")
      {
        // key is value inbetween "[" and "]"
        if( istr >> Key )
        {
          Key = Key.substr(1,Key.length()-2);
        }
        else
        {
          Key.erase();
        }
      }

      // processing rules
      if( istr >> Name >> Comp)
      {

        std::string Value;
        std::string Default;

        if( istr >> Value )
        {
          if( !(istr >> Default) )
          {
            Default = DEF::Inv_String;
          }

          Validator.loadRule(Name,Key,Comp,Value,Default);

        }
      }
    }

    in.close();
  }
  
}

bool CSMC_DataProvider_Impl::isLoggingOn()
{
  bool RetValue = false;

  if (m_pCorbaTask)
  {
    RetValue = m_pCorbaTask->isLoggingOn();
  }

  return RetValue;

}

long CSMC_DataProvider_Impl::getTraceLevel()
{
  if (m_pCorbaTask)
  {
    return m_pCorbaTask->getTraceLevel();
  }
  else
  {
    return 0;
  }
}


seqRecipeList* CSMC_DataProvider_Impl::getRecipeList(const char* Key,
                                                     const char* Name)
{
  
  return AnyToSeq<seqRecipeList>(Key, Name,"CSMC_DataProvider_Impl::getRecipeList");
}

sDate CSMC_DataProvider_Impl::getDate(const char * Key, 
                                         const char * Name)
{
  sDate RetValue;
  RetValue = CDateTime::InvalidDate();
  AnyToStruct(RetValue,Key, Name);
  return RetValue;
    
}

seqAODBlowPredRes* CSMC_DataProvider_Impl::getAODBlowPredRes (const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqAODBlowPredRes>(Key, Name, "CSMC_DataProvider_Impl::getAODBlowPredRes");
}


seqEAFBurnerPredRes* CSMC_DataProvider_Impl::getEAFBurnerPredRes(const char* Key, 
                                                                const char* Name)
{
  
  return AnyToSeq<seqEAFBurnerPredRes>(Key, Name, "CSMC_DataProvider_Impl::getEAFBurnerPredRes");
}

void CSMC_DataProvider_Impl::setAnalysis(const char* Key, const char * Name, 
                                         const seqAnalysis& NewData)
{
  
  SeqToAny<seqAnalysis>(Key, Name, NewData);
}

seqAnalysis* CSMC_DataProvider_Impl::getAnalysis(const char* Key, 
                                                 const char* Name)
{
  return AnyToSeq<seqAnalysis>(Key, Name, "CSMC_DataProvider_Impl::getAnalysis");
}


void CSMC_DataProvider_Impl::setDate(const char* Key, const char * Name, 
                                     const sDate& NewData)
{
  
  StructToAny<sDate>(Key, Name, NewData);
}


void CSMC_DataProvider_Impl::setAODBlowPredRes(const char* Key, const char* Name, 
                                               const seqAODBlowPredRes& NewData)
{
  
  SeqToAny<seqAODBlowPredRes>(Key, Name, NewData);
}


void CSMC_DataProvider_Impl::setEAFBurnerPredRes(const char* Key,const char* Name, 
                                                 const seqEAFBurnerPredRes& NewData)
{
  
  SeqToAny<seqEAFBurnerPredRes>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setRecipeList(const char* Key, const char * Name, 
                                           const seqRecipeList& NewData)
{
  
  SeqToAny<seqRecipeList>(Key, Name, NewData);
}

seqAODGlobalSetpoints* CSMC_DataProvider_Impl::getAODGlobalSetpoints(const char* Key, 
                                                                             const char* Name)
{
  
  return AnyToSeq<seqAODGlobalSetpoints>(Key, Name, "CSMC_DataProvider_Impl::getAODGlobalSetpoints");
}

void CSMC_DataProvider_Impl::setAODGlobalSetpoints(const char* Key, const char* Name, 
                                                        const seqAODGlobalSetpoints& NewData)
{
  
  SeqToAny<seqAODGlobalSetpoints>(Key, Name, NewData);
}

seqPredRes* CSMC_DataProvider_Impl::getPredRes(const char* Key, 
                                               const char* Name)
{
  
  return AnyToSeq<seqPredRes>(Key, Name, "CSMC_DataProvider_Impl::getPredRes");
}

void CSMC_DataProvider_Impl::setPredRes(const char* Key, const char* Name, 
                                        const seqPredRes& NewData)
{
  
  SeqToAny<seqPredRes>(Key, Name, NewData);
}

seqBatch* CSMC_DataProvider_Impl::getBatch(const char* Key, 
                                           const char* Name)
{
  
  return AnyToSeq<seqBatch>(Key, Name, "CSMC_DataProvider_Impl::getBatch");
}

void CSMC_DataProvider_Impl::setBatch(const char* Key, const char * Name, 
                                      const seqBatch& NewData)
{
  
  SeqToAny<seqBatch>(Key, Name, NewData);
}


void CSMC_DataProvider_Impl::setProductIdentification(const char* Key, const char * Name, 
                                                      const seqProductIdentification& NewData)
{
  
  SeqToAny<seqProductIdentification>(Key, Name, NewData);
}

seqProductIdentification* CSMC_DataProvider_Impl::getProductIdentification(const char* Key, 
                                                                           const char* Name)
{
  
  return AnyToSeq<seqProductIdentification>(Key, Name, "CSMC_DataProvider_Impl::getProductIdentification");
}

void CSMC_DataProvider_Impl::setLFElecPredRes(const char* Key, const char * Name, 
                                              const seqLFElecPredRes& NewData)
{
  
  SeqToAny<seqLFElecPredRes>(Key, Name, NewData);
}

seqLFElecPredRes* CSMC_DataProvider_Impl::getLFElecPredRes(const char* Key, 
                                                           const char* Name)
{
  
  return AnyToSeq<seqLFElecPredRes>(Key, Name, "CSMC_DataProvider_Impl::getLFElecPredRes");
}

void CSMC_DataProvider_Impl::setLFStirrPredRes(const char* Key, const char * Name, 
                                               const seqLFStirrPredRes& NewData)
{
  
  SeqToAny<seqLFStirrPredRes>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setRHModelResult(const char* Key, const char * Name, 
                                                const seqRHModelResult & NewData)
{
  
  SeqToAny<seqRHModelResult>(Key, Name, NewData);
}

seqLFStirrPredRes* CSMC_DataProvider_Impl::getLFStirrPredRes(const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqLFStirrPredRes>(Key, Name, "CSMC_DataProvider_Impl::getLFStirrPredRes");
}

seqRHModelResult *  CSMC_DataProvider_Impl::getRHModelResult(const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqRHModelResult>(Key, Name, "CSMC_DataProvider_Impl::getRHModelResult");
}

void CSMC_DataProvider_Impl::setEAFInjectLance(const char* Key, const char * Name, 
                                               const seqEAFInjectLance& NewData)
{
  
  SeqToAny<seqEAFInjectLance>(Key, Name, NewData);
}

seqEAFInjectLance* CSMC_DataProvider_Impl::getEAFInjectLance(const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqEAFInjectLance>(Key, Name, "CSMC_DataProvider_Impl::getEAFInjectLance");
}



void CSMC_DataProvider_Impl::setEAFMatFeed(const char* Key, const char * Name, 
                                           const seqEAFMatFeed& NewData)
{
  
  SeqToAny<seqEAFMatFeed>(Key, Name, NewData);
}

seqEAFMatFeed* CSMC_DataProvider_Impl::getEAFMatFeed(const char* Key, 
                                                     const char* Name)
{
  
  return AnyToSeq<seqEAFMatFeed>(Key, Name, "CSMC_DataProvider_Impl::getEAFMatFeed");
}

void CSMC_DataProvider_Impl::setEAFGasLancePredRes(const char* Key, const char * Name, 
                                                   const seqEAFGasLancePredRes& NewData)
{
  
  SeqToAny<seqEAFGasLancePredRes>(Key, Name, NewData);
}

seqEAFGasLancePredRes* CSMC_DataProvider_Impl::getEAFGasLancePredRes(const char* Key, 
                                                                     const char* Name)
{
  
  return AnyToSeq<seqEAFGasLancePredRes>(Key, Name, "CSMC_DataProvider_Impl::getEAFGasLancePredRes");
}

//void CSMC_DataProvider_Impl::setEAFElecPredRes(const char* Key, const char * Name, 
//                                               const seqEAFElecPredRes& NewData)
//{
//  
//  SeqToAny<seqEAFElecPredRes>(Key, Name, NewData);
//}
//
//seqEAFElecPredRes* CSMC_DataProvider_Impl::getEAFElecPredRes(const char* Key, 
//                                                             const char* Name)
//{
//  
//  return AnyToSeq<seqEAFElecPredRes>(Key, Name, "CSMC_DataProvider_Impl::getEAFElecPredRes");
//}

void CSMC_DataProvider_Impl::setEAFProcessPredRes(const char* Key, const char * Name, 
                                               const seqEAFProcessPredRes& NewData)
{
  
  SeqToAny<seqEAFProcessPredRes>(Key, Name, NewData);
}
seqEAFProcessPredRes* CSMC_DataProvider_Impl::getEAFProcessPredRes(const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqEAFProcessPredRes>(Key, Name, "CSMC_DataProvider_Impl::getEAFProcessPredRes");
}

seqGasAvail* CSMC_DataProvider_Impl::getGasAvail(const char* Key, 
                                                  const char* Name)
{
  
  return AnyToSeq<seqGasAvail>(Key, Name, "CSMC_DataProvider_Impl::getGasAvail");
}
  
void CSMC_DataProvider_Impl::setGasAvail (const char* Key, const char* Name, 
                                           const seqGasAvail& NewData)
{
  
  SeqToAny<seqGasAvail>(Key, Name, NewData);
}
  
seqWasteGas* CSMC_DataProvider_Impl::getWasteGas(const char* Key, 
                                                  const char* Name)
{
  
  return AnyToSeq<seqWasteGas>(Key, Name, "CSMC_DataProvider_Impl::getWasteGas");
}
  
void CSMC_DataProvider_Impl::setWasteGas(const char* Key, const char* Name, 
                                          const seqWasteGas& NewData)
{
  
  SeqToAny<seqWasteGas>(Key, Name, NewData);
}
  
seqWireFeeder* CSMC_DataProvider_Impl::getWireFeeder (const char* Key, 
                                                      const char* Name)
{
  
  return AnyToSeq<seqWireFeeder>(Key, Name, "CSMC_DataProvider_Impl::getWireFeeder");
}

void CSMC_DataProvider_Impl::setWireFeeder (const char* Key, const char* Name, 
                                            const seqWireFeeder& NewData)
{
  
  SeqToAny<seqWireFeeder>(Key, Name, NewData);
}
  
seqCoolWaterData* CSMC_DataProvider_Impl::getCoolWaterData (const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqCoolWaterData>(Key, Name, "CSMC_DataProvider_Impl::getCoolWaterData");
}

void CSMC_DataProvider_Impl::setCoolWaterData(const char* Key, const char* Name, 
                                              const seqCoolWaterData& NewData)
{
 
  SeqToAny<seqCoolWaterData>(Key, Name, NewData);
}
  
seqComputerModes *CSMC_DataProvider_Impl::getComputerModes (const char* Key, 
                                                             const char* Name)
{
  
  return AnyToSeq<seqComputerModes>(Key, Name, "CSMC_DataProvider_Impl::getComputerModes");
}

void CSMC_DataProvider_Impl::setComputerModes(const char* Key, const char* Name, 
                                              const seqComputerModes& NewData)
{
  
  SeqToAny<seqComputerModes>(Key, Name, NewData);
}

seqGasData * CSMC_DataProvider_Impl::getGasData (const char* Key, 
                                                 const char* Name)
{
  
  return AnyToSeq<seqGasData>(Key, Name, "CSMC_DataProvider_Impl::getGasData");
}

void CSMC_DataProvider_Impl::setGasData (const char* Key, const char* Name, 
                                         const seqGasData& NewData)
{
  
  SeqToAny<seqGasData>(Key, Name, NewData);
}

seqBlowStatus *CSMC_DataProvider_Impl::getBlowStatus (const char* Key, 
                                                       const char* Name)
{
  
  return AnyToSeq<seqBlowStatus>(Key, Name, "CSMC_DataProvider_Impl::getBlowStatus");
}

void CSMC_DataProvider_Impl::setBlowStatus (const char* Key, const char* Name, 
                                            const seqBlowStatus& NewData)
{
  
  SeqToAny<seqBlowStatus>(Key, Name, NewData);
}

seqPhaseStatus *CSMC_DataProvider_Impl::getPhaseStatus (const char* Key, 
                                                         const char* Name)
{
  
  return AnyToSeq<seqPhaseStatus>(Key, Name, "CSMC_DataProvider_Impl::getPhaseStatus");
}

void CSMC_DataProvider_Impl::setPhaseStatus (const char* Key, const char* Name, 
                                             const seqPhaseStatus& NewData)
{
  
  SeqToAny<seqPhaseStatus>(Key, Name, NewData);
}

seqStringList* CSMC_DataProvider_Impl::getStringList(const char* Key, 
                                                     const char* Name)
{
 
  return AnyToSeq<seqStringList>(Key, Name, "CSMC_DataProvider_Impl::getStringList");
}

void CSMC_DataProvider_Impl::setStringList(const char* Key, const char* Name, 
                                           const seqStringList& NewData)
{
  
  SeqToAny<seqStringList>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setGasLanceData(const char* Key, const char* Name, 
                                             const seqGasLanceData& NewData)
{
  
  SeqToAny<seqGasLanceData>(Key, Name, NewData);
}

seqGasLanceData* CSMC_DataProvider_Impl::getGasLanceData(const char* Key, 
                                                         const char* Name)
{
  
  return AnyToSeq<seqGasLanceData>(Key, Name, "CSMC_DataProvider_Impl::getGasLanceData");
}

void CSMC_DataProvider_Impl::setInjectLanceData(const char* Key, const char* Name, 
                                                const seqInjectLanceData& NewData)
{
  
  SeqToAny<seqInjectLanceData>(Key, Name, NewData);
}

seqInjectLanceData* CSMC_DataProvider_Impl::getInjectLanceData(const char* Key, 
                                                               const char* Name)
{
  
  return AnyToSeq<seqInjectLanceData>(Key, Name, "CSMC_DataProvider_Impl::getInjectLanceData");
}

void CSMC_DataProvider_Impl::setSampleData(const char* Key, const char* Name, const seqSampleData& NewData)
{
  
  SeqToAny<seqSampleData>(Key, Name, NewData);
}

seqSampleData* CSMC_DataProvider_Impl::getSampleData(const char* Key, const char* Name)
{
  
  return AnyToSeq<seqSampleData>(Key, Name, "CSMC_DataProvider_Impl::getSampleData");
}

void CSMC_DataProvider_Impl::setAnalysisData(const char* Key, const char* Name, const seqAnalysisData& NewData)
{
  
  SeqToAny<seqAnalysisData>(Key, Name, NewData);
}

seqAnalysisData* CSMC_DataProvider_Impl::getAnalysisData(const char* Key, const char* Name)
{
  
  return AnyToSeq<seqAnalysisData>(Key, Name, "CSMC_DataProvider_Impl::getAnalysisData");
}

void CSMC_DataProvider_Impl::setStatus(const char* Key, const char* Name, const seqStatus& NewData)
{
  
  SeqToAny<seqStatus>(Key, Name, NewData);
}

seqStatus* CSMC_DataProvider_Impl::getStatus(const char* Key, const char* Name)
{
  
  return AnyToSeq<seqStatus>(Key, Name, "CSMC_DataProvider_Impl::getStatus");
}

seqHeatSchedule* CSMC_DataProvider_Impl::getHeatSchedule (const char* Key, const char* Name)
{
  
  return AnyToSeq<seqHeatSchedule>(Key, Name, "CSMC_DataProvider_Impl::getHeatSchedule");
}

void CSMC_DataProvider_Impl::setHeatSchedule(const char* Key, const char* Name, 
                               const seqHeatSchedule& NewData)
{
  
  SeqToAny<seqHeatSchedule>(Key, Name, NewData);
}

seqHeatSchedulePlant * CSMC_DataProvider_Impl::getHeatSchedulePlant (const char* Key, 
                                                                     const char* Name)
{
  
  return AnyToSeq<seqHeatSchedulePlant>(Key, Name, "CSMC_DataProvider_Impl::getHeatSchedulePlant");
}

void CSMC_DataProvider_Impl::setHeatSchedulePlant(const char* Key, const char* Name, 
                                    const seqHeatSchedulePlant& NewData)
{
  
  SeqToAny<seqHeatSchedulePlant>(Key, Name, NewData);
}

seqOrderData* CSMC_DataProvider_Impl::getOrderData(const char* Key, const char* Name)
{
  
  return AnyToSeq<seqOrderData>(Key, Name, "CSMC_DataProvider_Impl::getOrderData");
}

void CSMC_DataProvider_Impl::setOrderData(const char* Key, const char* Name, const seqOrderData& NewData)
{
  
  SeqToAny<seqOrderData>(Key, Name, NewData);
}

seqHeatData* CSMC_DataProvider_Impl::getHeatData(const char* Key, const char* Name)
{
  return AnyToSeq<seqHeatData>(Key, Name, "CSMC_DataProvider_Impl::getHeatData");
}

void CSMC_DataProvider_Impl::setHeatData(const char* Key, const char* Name, const seqHeatData& NewData)
{
  SeqToAny<seqHeatData>(Key, Name, NewData);
}

seqLiqMatReport* CSMC_DataProvider_Impl::getLiqMatReport(const char* Key, const char* Name)
{
  return AnyToSeq<seqLiqMatReport>(Key, Name, "CSMC_DataProvider_Impl::getLiqMatReport");
}

void CSMC_DataProvider_Impl::setLiqMatReport(const char* Key, const char* Name, const seqLiqMatReport& NewData)
{
  SeqToAny<seqLiqMatReport>(Key, Name, NewData);
}


seqGasLanceGasAvail* CSMC_DataProvider_Impl::getGasLanceGasAvail(const char* Key, const char* Name)
{
  return AnyToSeq<seqGasLanceGasAvail>(Key, Name, "CSMC_DataProvider_Impl::getGasLanceGasAvail");
}

void CSMC_DataProvider_Impl::setGasLanceGasAvail(const char* Key, const char* Name, const seqGasLanceGasAvail& NewData)
{
  SeqToAny<seqGasLanceGasAvail>(Key, Name, NewData);
}

seqBOFBlowPredRes* CSMC_DataProvider_Impl::getBOFBlowPredRes(const char* Key, const char* Name)
{
  return AnyToSeq<seqBOFBlowPredRes>(Key, Name, "CSMC_DataProvider_Impl::getBOFBlowPredRes");
}

seqBOFGlobalSetpoints* CSMC_DataProvider_Impl::getBOFGlobalSetpoints(const char* Key, const char* Name)
{
  return AnyToSeq<seqBOFGlobalSetpoints>(Key, Name, "CSMC_DataProvider_Impl::getBOFGlobalSetpoints");
}

seqConArcGlobalSetpoints* CSMC_DataProvider_Impl::getConArcGlobalSetpoints(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcGlobalSetpoints>(Key, Name, "CSMC_DataProvider_Impl::getConArcGlobalSetpoints");
}

void CSMC_DataProvider_Impl::setBOFBlowPredRes(const char* Key, const char* Name, const seqBOFBlowPredRes& NewData)
{
  SeqToAny<seqBOFBlowPredRes>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setBOFGlobalSetpoints(const char* Key, const char* Name, const seqBOFGlobalSetpoints& NewData)
{
  SeqToAny<seqBOFGlobalSetpoints>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setConArcGlobalSetpoints(const char* Key, const char* Name, const seqConArcGlobalSetpoints& NewData)
{
  SeqToAny<seqConArcGlobalSetpoints>(Key, Name, NewData);
}


seqElecPhaseData* CSMC_DataProvider_Impl::getElecPhaseData(const char* Key, const char* Name)
{
  return AnyToSeq<seqElecPhaseData>(Key, Name, "CSMC_DataProvider_Impl::getElecPhaseData");
}

void CSMC_DataProvider_Impl::setElecPhaseData(const char* Key, const char* Name, const seqElecPhaseData& NewData)
{
  SeqToAny<seqElecPhaseData>(Key, Name, NewData);
}


// **********************************************************************************************
// ***** following functions will allow access to data provider directly                    *****
// ***** CORBA functionalities like string_dup will not be called to prevent memory leakage *****
// **********************************************************************************************

CORBA::Any CSMC_DataProvider_Impl::getAny(const std::string& Key, const std::string& Name)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getAny"))
  {
    CORBA::Any t;
    return t;
  }
  
  CORBA::Any &ActAny = CData_Provider::getAny(Key, Name);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getAny");

  return ActAny;
}

CORBA::Boolean CSMC_DataProvider_Impl::getBoolean(const std::string& Key, const std::string& Name)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getBoolean"))
  {
    return false;
  }

  bool RetValue = CData_Provider::getBoolean(Key, Name);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getBoolean");

  return RetValue;
}

CORBA::Double CSMC_DataProvider_Impl::getDouble(const std::string& Key, const std::string& Name)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getDouble"))
  {
    return DEF::Inv_Double;
  }

  double RetValue = CData_Provider::getDouble(Key, Name);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getDouble");

  return RetValue;
}

//Jiantao 26.11 2009 , this function changed due to  performance problem
//CIntfData::insert() function increase the sequence lenth by 1 everytime,
//them memory used by this sequence need to be deallocated and reallocated again,
//this operation consume lots of CPU times, it's not suppose to be used here.
seqIntfDataList CSMC_DataProvider_Impl::getIntfDataList(const std::string& Key)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getIntfDataList"))
  {
    seqIntfDataList t;
    return t;
  }

  seqIntfDataList ret;

  try
  {
    std::map<std::string,std::string> IntfDataNameList = getIntfDataTypeList(Key);

    if ( !IntfDataNameList.empty() )
    {
      int mapSize =  IntfDataNameList.size();
      std::map<std::string,std::string>::iterator it;

      ret.length(mapSize);

      int pos = 0;

      for ( it = IntfDataNameList.begin(); it != IntfDataNameList.end() ; ++ it )
      {
        sIntfDataList IntfDataList;
        IntfDataList.Name = it->first.c_str();
        IntfDataList.Type = it->second.c_str();

        CIntfData::setAt(ret,IntfDataList,pos);

        pos++;
      }
    }
    else
    {
      ret.length(0);
    }
  }
  catch(...)
  {
    EventLogExc("Unknown","CData_Provider_Impl::getIntfDataList","");
  }

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getIntfDataList");

  return ret;
}

long CSMC_DataProvider_Impl::getLong(const std::string& Key, const std::string& Name)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getLong"))
  {
    return DEF::Inv_Long;
  }

  long RetValue = CData_Provider::getLong(Key, Name);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getLong");

  return RetValue;
}

std::string CSMC_DataProvider_Impl::getString(const std::string& Key, const std::string& Name)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getString"))
  {
    return DEF::Inv_String;
  }

  std::string RetValue = CData_Provider::getString(Key, Name);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getString");

  return RetValue;

}

void CSMC_DataProvider_Impl::setAny(const std::string& Key, const std::string& Name, CORBA::Any& NewAny)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::setAny"))
  {
    return;
  }

  CData_Provider::setAny(Key, Name, NewAny);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::setAny");
}

void CSMC_DataProvider_Impl::setBoolean(const std::string& Key, const std::string& Name, bool value)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::setBoolean"))
  {
    return;
  }

  CData_Provider::setBoolean(Key, Name, value);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::setBoolean");
}

void CSMC_DataProvider_Impl::setDouble(const std::string& Key, const std::string& Name, double value)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::setDouble"))
  {
    return;
  }

  CData_Provider::setDouble(Key, Name, value);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::setDouble");
}

void CSMC_DataProvider_Impl::setLong(const std::string& Key, const std::string& Name, long value)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::setLong"))
  {
    return;
  }

  CData_Provider::setLong(Key, Name, value);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::setLong");
}

void CSMC_DataProvider_Impl::setString(const std::string& Key, const std::string& Name, const std::string& value)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::setString"))
  {
    return;
  }

  CData_Provider::setString(Key, Name, value);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::setString");

}


std::string CSMC_DataProvider_Impl::generateDataKey(const std::string& Value)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::generateDataKey"))
  {
    return CORBA::string_dup(DEF::Inv_String);
  }

  std::string Key = CData_Provider::generateDataKey(Value);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::generateDataKey");

  return Key;

}

std::set<std::string> CSMC_DataProvider_Impl::getIntfReqList(const std::string& Key)
{
  if (! m_Critical_Section.lock("CSMC_DataProvider_Impl::getIntfReqList"))
  {
    std::set<std::string> t;
    return t;
  }

  std::set<std::string> &RetValue = CData_Provider::getIntfReqList(Key);

  m_Critical_Section.unlock("CSMC_DataProvider_Impl::getIntfReqList");

  return RetValue;
}

seqHMDModelResult *  CSMC_DataProvider_Impl::getHMDModelResult(const char* Key, const char* Name)
{
  return AnyToSeq<seqHMDModelResult>(Key, Name, "CSMC_DataProvider_Impl::getHMDModelResult");
}

void CSMC_DataProvider_Impl::setHMDModelResult(const char* Key, const char* Name, const seqHMDModelResult& NewData)
{
  SeqToAny<seqHMDModelResult>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setConArcElecData(const char* Key, const char* Name, const seqConArcElecData& NewData)
{
  SeqToAny<seqConArcElecData>(Key, Name, NewData);
}

seqConArcElecData* CSMC_DataProvider_Impl::getConArcElecData(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcElecData>(Key, Name, "CSMC_DataProvider_Impl::getConArcElecData");
}

void CSMC_DataProvider_Impl::setConArcMediaData(const char* Key, const char* Name, const seqConArcMediaData& NewData)
{
  SeqToAny<seqConArcMediaData>(Key, Name, NewData);
}

seqConArcMediaData* CSMC_DataProvider_Impl::getConArcMediaData(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcMediaData>(Key, Name, "CSMC_DataProvider_Impl::getConArcMediaData");
}

void CSMC_DataProvider_Impl::setConArcSetptData(const char* Key, const char* Name, const seqConArcSetptData& NewData)
{
  SeqToAny<seqConArcSetptData>(Key, Name, NewData);
}

seqConArcSetptData* CSMC_DataProvider_Impl::getConArcSetptData(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcSetptData>(Key, Name, "CSMC_DataProvider_Impl::getConArcSetptData");
}

void CSMC_DataProvider_Impl::setConArcMeasData(const char* Key, const char* Name, const seqConArcMeasData& NewData)
{
  SeqToAny<seqConArcMeasData>(Key, Name, NewData);
}

seqConArcMeasData* CSMC_DataProvider_Impl::getConArcMeasData(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcMeasData>(Key, Name, "CSMC_DataProvider_Impl::getConArcMeasData");

}

seqEAFMatFeedPredRes* CSMC_DataProvider_Impl::getEAFMatFeedPredRes(const char *Key, const char *Name)
{
  return AnyToSeq<seqEAFMatFeedPredRes>(Key, Name, "CSMC_DataProvider_Impl::getEAFMatFeedPredRes");
}

void CSMC_DataProvider_Impl::setEAFMatFeedPredRes(const char* Key, const char* Name, const seqEAFMatFeedPredRes& NewData)
{
  SeqToAny<seqEAFMatFeedPredRes>(Key, Name, NewData);
}

seqMaterials* CSMC_DataProvider_Impl::getMaterials(const char* Key, const char* Name)
{
  return AnyToSeq<seqMaterials>(Key, Name, "CSMC_DataProvider_Impl::getMaterials");
}

void CSMC_DataProvider_Impl::setMaterials(const char* Key, const char* Name, const seqMaterials& NewData)
{
  SeqToAny<seqMaterials>(Key, Name, NewData);
}
//
seqStirringData* CSMC_DataProvider_Impl::getStirringData(const char* Key, const char* Name)
{
  return AnyToSeq<seqStirringData>(Key, Name, "CSMC_DataProvider_Impl::getStirringData");
}

void CSMC_DataProvider_Impl::setStirringData(const char* Key, const char* Name, const seqStirringData& NewData)
{
  SeqToAny<seqStirringData>(Key, Name, NewData);
}

seqInjectData* CSMC_DataProvider_Impl::getInjectData(const char* Key, const char* Name)
{
  return AnyToSeq<seqInjectData>(Key, Name, "CSMC_DataProvider_Impl::getInjectData");
}

void CSMC_DataProvider_Impl::setInjectData(const char* Key, const char* Name, const seqInjectData& NewData)
{
  SeqToAny<seqInjectData>(Key, Name, NewData);
}

seqVDModelResult* CSMC_DataProvider_Impl::getVDModelResult(const char* Key, const char* Name)
{
  return AnyToSeq<seqVDModelResult>(Key, Name, "CSMC_DataProvider_Impl::getVDModelResult");
}

void CSMC_DataProvider_Impl::setVDModelResult(const char* Key, const char* Name, const seqVDModelResult& NewData)
{
  SeqToAny<seqVDModelResult>(Key, Name, NewData);
}

seqConArcModelResult* CSMC_DataProvider_Impl::getConArcModelResult(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcModelResult>(Key, Name, "CSMC_DataProvider_Impl::getConArcModelResult");
}

void CSMC_DataProvider_Impl::setConArcModelResult(const char* Key, const char* Name, const seqConArcModelResult& NewData)
{
  SeqToAny<seqConArcModelResult>(Key, Name, NewData);
}

seqLTSStirrPredRes* CSMC_DataProvider_Impl::getLTSStirrPredRes(const char* Key, const char* Name)
{
  return AnyToSeq<seqLTSStirrPredRes>(Key, Name, "CSMC_DataProvider_Impl::getLTSStirrPredRes");
}

void CSMC_DataProvider_Impl::setLTSStirrPredRes(const char* Key, const char* Name, const seqLTSStirrPredRes& NewData)
{
  SeqToAny<seqLTSStirrPredRes>(Key, Name, NewData);
}

seqConArcBlowData* CSMC_DataProvider_Impl::getConArcBlowData(const char* Key, const char* Name)
{
  return AnyToSeq<seqConArcBlowData>(Key, Name, "CSMC_DataProvider_Impl::getConArcBlowData");
}

void CSMC_DataProvider_Impl::setConArcBlowData(const char* Key, const char* Name, const seqConArcBlowData& NewData)
{
  SeqToAny<seqConArcBlowData>(Key, Name, NewData);
}

void CSMC_DataProvider_Impl::setSample(const char* Key, const char * Name, const seqSample& NewData)
{
  SeqToAny<seqSample>(Key, Name, NewData);
}

seqSample* CSMC_DataProvider_Impl::getSample(const char* Key, const char* Name)
{
  return AnyToSeq<seqSample>(Key, Name, "CSMC_DataProvider_Impl::getSample");
}

void CSMC_DataProvider_Impl::setPhaseDataReport(const char* Key, const char * Name, const seqPhaseDataReport& NewData)
{
  SeqToAny<seqPhaseDataReport>(Key, Name, NewData);
}

seqPhaseDataReport* CSMC_DataProvider_Impl::getPhaseDataReport(const char* Key, const char* Name)
{
  return AnyToSeq<seqPhaseDataReport>(Key, Name, "CSMC_DataProvider_Impl::getPhaseDataReport");
}

void CSMC_DataProvider_Impl::setTorpedoData(const char* Key, const char * Name, const seqTorpedoData& NewData)
{
  SeqToAny<seqTorpedoData>(Key, Name, NewData);
}

seqTorpedoData* CSMC_DataProvider_Impl::getTorpedoData(const char* Key, const char* Name)
{
  return AnyToSeq<seqTorpedoData>(Key, Name, "CSMC_DataProvider_Impl::getTorpedoData");
}

void CSMC_DataProvider_Impl::setEquipmentLifeData(const char* Key, const char * Name, const seqEquipmentLifeData& NewData)
{
  SeqToAny<seqEquipmentLifeData>(Key, Name, NewData);
}

seqEquipmentLifeData* CSMC_DataProvider_Impl::getEquipmentLifeData(const char* Key, const char* Name)
{
  return AnyToSeq<seqEquipmentLifeData>(Key, Name,"CSMC_DataProvider_Impl::getEquipmentLifeData");
}

void CSMC_DataProvider_Impl::setPPRestriction(const char* Key, const char * Name, const seqPPRestriction& NewData)
{
  SeqToAny<seqPPRestriction>(Key, Name, NewData);
}

seqPPRestriction* CSMC_DataProvider_Impl::getPPRestriction(const char* Key, const char* Name)
{
  return AnyToSeq<seqPPRestriction>(Key, Name,"CSMC_DataProvider_Impl::getPPRestriction");
}

void CSMC_DataProvider_Impl::setHeatStack(const char* Key, const char * Name, const seqHeatStack& NewData)
{
  SeqToAny<seqHeatStack>(Key, Name, NewData);
}

seqHeatStack* CSMC_DataProvider_Impl::getHeatStack(const char* Key, const char* Name)
{
  return AnyToSeq<seqHeatStack>(Key, Name,"CSMC_DataProvider_Impl::getHeatStack");
}

seqMediaConsumed* CSMC_DataProvider_Impl::getMediaConsumed(const char* Key, const char* Name)
{
  return AnyToSeq<seqMediaConsumed>(Key, Name, "CSMC_DataProvider_Impl::getMediaConsumed");
}

void CSMC_DataProvider_Impl::setMediaConsumed(const char* Key, const char * Name, const seqMediaConsumed& NewData)
{
  SeqToAny<seqMediaConsumed>(Key, Name, NewData);
}

seqEnergyConsumed* CSMC_DataProvider_Impl::getEnergyConsumed(const char* Key, const char* Name)
{
  return AnyToSeq<seqEnergyConsumed>(Key, Name, "CSMC_DataProvider_Impl::getEnergyConsumed");
}

void CSMC_DataProvider_Impl::setEnergyConsumed(const char* Key, const char * Name, const seqEnergyConsumed& NewData)
{
  SeqToAny<seqEnergyConsumed>(Key, Name, NewData);
}

seqSAF_Bin* CSMC_DataProvider_Impl::getSAFBinData(const char* Key, const char* Name)
{
  return AnyToSeq<seqSAF_Bin>(Key, Name, "CSMC_DataProvider_Impl::getSAFBinData");
}

void CSMC_DataProvider_Impl::setSAFBinData(const char* Key, const char * Name, const seqSAF_Bin& NewData)
{
  SeqToAny<seqSAF_Bin>(Key, Name, NewData);
}

seqHarmonics* CSMC_DataProvider_Impl::getHarmonics(const char* Key, const char* Name)
{
  return AnyToSeq<seqHarmonics>(Key, Name, "CSMC_DataProvider_Impl::getHarmonics");
}

void CSMC_DataProvider_Impl::setHarmonics(const char* Key, const char * Name, const seqHarmonics& NewData)
{
  SeqToAny<seqHarmonics>(Key, Name, NewData);
}

seqWallTemp* CSMC_DataProvider_Impl::getWallTemp(const char* Key, const char* Name)
{
  return AnyToSeq<seqWallTemp>(Key, Name, "CSMC_DataProvider_Impl::getWallTemp");
}

void CSMC_DataProvider_Impl::setWallTemp(const char* Key, const char * Name, const seqWallTemp& NewData)
{
  SeqToAny<seqWallTemp>(Key, Name, NewData);
}

seqHMPouringData* CSMC_DataProvider_Impl::getHMPouringData(const char* Key, const char* Name)
{
  return AnyToSeq<seqHMPouringData>(Key, Name, "CSMC_DataProvider_Impl::getHMPouringData");
}

void CSMC_DataProvider_Impl::setHMPouringData(const char* Key, const char * Name, const seqHMPouringData& NewData)
{
  SeqToAny<seqHMPouringData>(Key, Name, NewData);
}

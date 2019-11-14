// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

// Note: The file CIntfLF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfLF.h"
#include "CSmplCode.h"
#include "CSmplLoc.h"

#include "CIntfData.h"

#include "cCBS_StdEventLogFrameController.h"

#include "CLFModelTask.h"
#include "CLFAnalysisHandlingWrapper.h"

//##ModelId=41650A3A0065
bool CLFAnalysisHandlingWrapper::doOnSlagSampleTaken( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask ) 
  {
    log("error CLFAnalysisHandlingWrapper::doOnSlagSampleTaken(), (pIntfLF && m_pModelTask ) == false", 1);
    return RetValue;
  }

  try 
  {
    string        MeasSampleCode;
    seqSampleData seqSampleData;
    sSampleData   sSampleData;

    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);
    seqSampleData = CIntfData::ToCORBAType(pDM_Interface->getSampleData(Event.getDataKey().c_str(), DATA::SampleData));
    if (CIntfData::getAt(sSampleData, seqSampleData, 0))
    {
      MeasSampleCode = sSampleData.SampleCode;
    }
    else
    {
      log("error CLFAnalysisHandlingWrapper::doOnSlagSampleTaken(), empty sequence seqSampleData", 1);
      return RetValue;
    }

    // Sequence Diagram: get model results / Call Sequence 
    pIntfLF->hndlSlagSmplTaken(MeasSampleCode); 
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFAnalysisHandlingWrapper::doOnSlagSampleTaken()","");    
  }

  return RetValue;
}

//##ModelId=41650A3A0098
bool CLFAnalysisHandlingWrapper::doOnSteelSampleTaken( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask ) 
  {
    log("error CLFAnalysisHandlingWrapper::doOnSteelSampleTaken(), (pIntfLF && m_pModelTask ) == false", 1);
    return RetValue;
  }

  try
  {
    string        MeasSampleCode;
    seqSampleData seqSampleData;
    sSampleData   sSampleData;

    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);
    seqSampleData = CIntfData::ToCORBAType(pDM_Interface->getSampleData(Event.getDataKey().c_str(), DATA::SampleData));
    if (CIntfData::getAt(sSampleData, seqSampleData, 0))
    {
      MeasSampleCode = sSampleData.SampleCode;
    }
    else
    {
      log("error CLFAnalysisHandlingWrapper::doOnSteelSampleTaken(), empty sequence seqSampleData", 1);
      return RetValue;
    }

    // Sequence Diagram: get model results / Call Sequence
    pIntfLF->hndlSteelSmplTaken(MeasSampleCode); //satk 04062018
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFAnalysisHandlingWrapper::doOnSteelSampleTaken()", "");    
  }

  return RetValue;

}

//##ModelId=41650A3A00C0
bool CLFAnalysisHandlingWrapper::doOnSteelAnalysisReceived( CEventMessage &Event ) 
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask ) 
  {
    log("error CLFAnalysisHandlingWrapper::doOnSteelAnalysisReceived(), (pIntfLF && m_pModelTask ) == false", 1);
    return RetValue;
  }

  try 
  {
    CDeltaTime   DurSampleTime;
    CDateTime    MeasSampleTime;
    string       MeasSampleCode;
    long         MeasSampleNo = 0; 
    seqAnalysisData seqAnalysisData;
    sAnalysisData   sAnalysisData;
    seqAnalysis     MeasAnalysis;

    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);
    seqAnalysisData = CIntfData::ToCORBAType(pDM_Interface->getAnalysisData(Event.getDataKey().c_str(), DATA::SteelMeasAnalysis));

    if (CIntfData::getAt(sAnalysisData, seqAnalysisData, 0))
    {
      MeasSampleCode = sAnalysisData.SampleData.SampleCode;
      MeasSampleNo   = sAnalysisData.SampleData.SampleNo;
      MeasAnalysis   = sAnalysisData.Analysis;
      MeasSampleTime.SetTime(sAnalysisData.SampleData.SampleTime);

    }
    else
    {
      log("error CLFAnalysisHandlingWrapper::doOnSteelAnalysisReceived(), empty sequence seqSampleData", 1);
      return RetValue;
    }

    DurSampleTime  = CDateTime::subTimes(MeasSampleTime, m_pModelTask->getActHeatAnnouncementTime(Event));
    std::stringstream Message1 ;
    Message1 << "###Sample taken time " << MeasSampleTime << " calc Dur " <<DurSampleTime;
    log(Message1.str(),2);

    // Sequence Diagram: handle received steel analysis / Call Sequence
    pIntfLF->indicateSteelAnlMeas();
    pIntfLF->setMeasSmplType(CSmplCode::Steel); 
    pIntfLF->setMeasSmplTime(max(0,DurSampleTime.asSeconds()/60)); // HeatAnnonceTime may < 0 until no heat is announced
    pIntfLF->setMeasSmplLoc(CSmplLoc::LadleStirringStation);
    pIntfLF->setMeasSmplNo(MeasSampleNo);
    pIntfLF->setMeasSmplCode(MeasSampleCode);                      

    // repeat for all measured elements as defined in CVE
    long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
    for (int x = 0; x<LengthMeasAnalysis; x++) 
    {
      sAnalysis strAnalysis;
      CIntfData::getAt(strAnalysis, MeasAnalysis, x);

      std::stringstream Message ;
      Message << "pIntfLF->setMeasAnl " << strAnalysis.Element << " : " << strAnalysis.Concentration;
      log(Message.str(),2);
      
      pIntfLF->setMeasAnl(std::string(strAnalysis.Element), strAnalysis.Concentration);                    
    }

    pIntfLF->hndlEvent();

    RetValue = doModelResult(Event);
  }
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFAnalysisHandlingWrapper::doOnSteelAnalysisReceived()","");    
  } 
 
  return RetValue;
}

//##ModelId=41650A3A00E8
bool CLFAnalysisHandlingWrapper::doOnSlagAnalysisReceived( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask ) 
  {
    log("error CLFAnalysisHandlingWrapper::doOnSlagAnalysisReceived(), (pIntfLF && m_pModelTask ) == false", 1);
    return RetValue;
  }

  try  
  {
    CDeltaTime   DurSampleTime;
    CDateTime    MeasSampleTime;
    string       MeasSampleCode;
    long         MeasSampleNo = 0; 
    seqAnalysisData seqAnalysisData;
    sAnalysisData   sAnalysisData;
    seqAnalysis     MeasAnalysis;

    DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);
    seqAnalysisData = CIntfData::ToCORBAType(pDM_Interface->getAnalysisData(Event.getDataKey().c_str(), DATA::SlagMeasAnalysis));

    //MeasSampleTime.SetTime(pDM_Interface->getDate(Event.getDataKey().c_str(),DATA::SlagSampleTime));

    if (CIntfData::getAt(sAnalysisData, seqAnalysisData, 0))
    {
      MeasSampleCode = sAnalysisData.SampleData.SampleCode;
      MeasSampleNo   = sAnalysisData.SampleData.SampleNo;
      MeasAnalysis   = sAnalysisData.Analysis;
      MeasSampleTime.SetTime(sAnalysisData.SampleData.SampleTime);
    }
    else
    {
      log("error CLFAnalysisHandlingWrapper::doOnSlagAnalysisReceived(), empty sequence seqSampleData", 1);
      return RetValue;
    }

    DurSampleTime  = CDateTime::subTimes(MeasSampleTime, m_pModelTask->getActHeatAnnouncementTime(Event));

    // Sequence Diagram: handle received Slag analysis / Call Sequence
    pIntfLF->indicateSlagAnlMeas();
    pIntfLF->setMeasSmplType(CSmplCode::Slag); 
    pIntfLF->setMeasSmplTime(max(0,DurSampleTime.asSeconds()/60)); // HeatAnnonceTime may < 0 until no heat is announced
    pIntfLF->setMeasSmplLoc(CSmplLoc::LadleStirringStation);
    pIntfLF->setMeasSmplNo(MeasSampleNo);
    pIntfLF->setMeasSmplCode(MeasSampleCode);                      

    // repeat for all measured elements as defined in CVE
    long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
    for (int x = 0; x<LengthMeasAnalysis; x++) 
    {
      sAnalysis strAnalysis;
      CIntfData::getAt(strAnalysis, MeasAnalysis, x);

      std::stringstream Message ;
      
      Message << "pIntfLF->setMeasAnl " << strAnalysis.Element << " : " << strAnalysis.Concentration;
      log(Message.str(),2);
      
      pIntfLF->setMeasAnl(std::string(strAnalysis.Element), strAnalysis.Concentration);                    
    }

    pIntfLF->hndlEvent();

    RetValue = doModelResult(Event);
  } 
  catch(...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "","CLFAnalysisHandlingWrapper::doOnSlagAnalysisReceived()","");    
  }

  return RetValue;
}

// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CSmplCode.h"
#include "CSmplLoc.h"

#include "CIntfData.h"
#include "CEAFAnalysisHandlingWrapper.h"

//##ModelId=41513374013D
bool CEAFAnalysisHandlingWrapper::doOnSlagAnalysisReceived( CEventMessage &Event )
{
  bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFAnalysisHandlingWrapper::doOnSlagAnalysisReceived(), ( pIntfEAF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try  
	{
	  CDeltaTime   DurSampleTime;
	  CDateTime    MeasSampleTime;
	  string       MeasSampleCode;
	  long         MeasSampleNo = 0; 
	  seqAnalysisData seqAnalysisData;
	  sAnalysisData sAnalysisData;
	  seqAnalysis MeasAnalysis;

	  DM::iDM_Interface_var pDM_Interface = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT);

	  seqAnalysisData = CIntfData::ToCORBAType(pDM_Interface->getAnalysisData(Event.getDataKey().c_str(), DATA::SlagMeasAnalysis));
	  if (CIntfData::getAt(sAnalysisData, seqAnalysisData, 0))
	  {
      MeasSampleCode = sAnalysisData.SampleData.SampleCode;
      MeasSampleNo   = sAnalysisData.SampleData.SampleNo;
      MeasAnalysis   = sAnalysisData.Analysis;		    
      MeasSampleTime.SetTime(sAnalysisData.SampleData.SampleTime);
	  }
	  else
	  {
		  log("error CEAFAnalysisHandlingWrapper::doOnSlagAnalysisReceived(), empty sequence seqSampleData", 1);
		  return RetValue;
	  }


	  DurSampleTime  = CDateTime::subTimes(MeasSampleTime, m_pModelTask->getActHeatAnnouncementTime(Event));


	  // Sequence Diagram: handle received Slag analysis / Call Sequence
	  pIntfEAF->indicateSlagAnlMeas();
	  pIntfEAF->setMeasSmplType(CSmplCode::Slag); 
	  pIntfEAF->setMeasSmplTime(max(0,DurSampleTime.asSeconds()/60)); // HeatAnnonceTime may < 0 until no heat is announced
	  pIntfEAF->setMeasSmplLoc(CSmplLoc::Furnace);
	  pIntfEAF->setMeasSmplNo(MeasSampleNo);
	  pIntfEAF->setMeasSmplCode(MeasSampleCode);                      

	  // repeat for all measured elements as defined in CVE
	  long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
	  for (int x = 0; x<LengthMeasAnalysis; x++) 
	  {
		  sAnalysis strAnalysis;
		  CIntfData::getAt(strAnalysis, MeasAnalysis, x);
	    
		  pIntfEAF->setMeasAnl(std::string( strAnalysis.Element ), strAnalysis.Concentration);                    
	  }

	  pIntfEAF->hndlEvent();
	  RetValue = doModelResult(Event);
	} 
	catch(...)
	{
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
	  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
	  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFAnalysisHandlingWrapper::doOnSteelAnalysisReceived()","");    
	}
	

	return RetValue;
}

//##ModelId=4151336E0287
bool CEAFAnalysisHandlingWrapper::doOnSlagSampleTaken( CEventMessage &Event )
{
	bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFAnalysisHandlingWrapper::doOnSlagSampleTaken(), ( pIntfEAF && m_pModelTask) == false", 1);
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
			log("error CEAFAnalysisHandlingWrapper::doOnSlagSampleTaken(), empty sequence seqSampleData", 1);
			return RetValue;
		}

		// Sequence Diagram: get model results / Call Sequence
		pIntfEAF->hndlSlagSmplTaken(MeasSampleCode);   
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		pEventLog->EL_ExceptionCaught(sMessage, "","CEAFAnalysisHandlingWrapper::doOnSlagSampleTaken()","");    
	} 
	
 	return RetValue;
}

//##ModelId=4151336F0171
bool CEAFAnalysisHandlingWrapper::doOnSteelAnalysisReceived( CEventMessage &Event )
{
	bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFAnalysisHandlingWrapper::doOnSteelAnalysisReceived(), ( pIntfEAF && m_pModelTask) == false", 1);
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
			  log("error CEAFAnalysisHandlingWrapper::doOnSteelAnalysisReceived(), empty sequence seqSampleData", 1);
			  return RetValue;
		  }


		  DurSampleTime  = CDateTime::subTimes(MeasSampleTime, m_pModelTask->getActHeatAnnouncementTime(Event));

		  // Sequence Diagram: handle received steel analysis / Call Sequence
		  pIntfEAF->indicateSteelAnlMeas();
		  pIntfEAF->setMeasSmplType(CSmplCode::Steel); 
		  pIntfEAF->setMeasSmplTime(max(0,DurSampleTime.asSeconds()/60)); // HeatAnnonceTime may < 0 until no heat is announced
		  pIntfEAF->setMeasSmplLoc(CSmplLoc::Furnace);
		  pIntfEAF->setMeasSmplNo(MeasSampleNo);
		  pIntfEAF->setMeasSmplCode(MeasSampleCode);                      

		  // repeat for all measured elements as defined in CVE
		  long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
		  for (int x = 0; x<LengthMeasAnalysis; x++) 
		  {
			  sAnalysis strAnalysis;
			  CIntfData::getAt(strAnalysis, MeasAnalysis, x);

			  pIntfEAF->setMeasAnl(std::string(strAnalysis.Element), strAnalysis.Concentration);                    
		  }

		  pIntfEAF->hndlEvent();
		  RetValue = doModelResult(Event);
	}
	catch(...)
	{
		  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFAnalysisHandlingWrapper::doOnSteelAnalysisReceived()","");    
	} 
	
	return RetValue;
}

//##ModelId=4151336F03A2
bool CEAFAnalysisHandlingWrapper::doOnSteelSampleTaken( CEventMessage &Event )
{
	bool RetValue = false;
	CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF || !m_pModelTask) 
  {
    log("error CEAFAnalysisHandlingWrapper::doOnSteelSampleTaken(), ( pIntfEAF && m_pModelTask) == false", 1);
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
				log("error CEAFAnalysisHandlingWrapper::doOnSteelSampleTaken(), empty sequence seqSampleData", 1);
				return RetValue;
		  }

		  // Sequence Diagram: Collect analysis data / Call Sequence
		  pIntfEAF->hndlSteelSmplTaken(MeasSampleCode);			   
		  RetValue = doModelResult(Event);

	}
	catch (...) 
	{
		  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		  pEventLog->EL_ExceptionCaught(sMessage, "","CEAFAnalysisHandlingWrapper::doOnSteelSampleTaken()","");    
	}
	
	return RetValue;
}


// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"
#include "CCfgEAF.h"

#include "DEF_GC_COMP_STATUS.h"

#include "CEAFComputerModeWrapper.h"
#include "CIntfData.h"
#include "CCtrlSystemCodesEAF.h"

//##ModelId=411277130175
bool CEAFComputerModeWrapper::doOnSetComputerMode( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFComputerModeWrapper::doOnSetComputerMode(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try
  {
    seqComputerModes  SeqComputerModes  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->
                                    getComputerModes(DEF_PLANT::Furnace, DATA::ComputerModes));

    const CCfgEAF * pCfgEAF =  getpCfgEAF();
    const map<std::string, long> & CtrlSystemMap = pCfgEAF->getCtrlSystemSetptTyp();
    map<std::string, long>::const_iterator  CtrlSystemItEnd (CtrlSystemMap.end());
    map<std::string, long>::const_iterator  CtrlSystemIt    (CtrlSystemItEnd);

    for (int x = 0; x < CIntfData::getLength(SeqComputerModes); x++) 
    {
      sComputerMode  ComputerMode;

      CIntfData::getAt(ComputerMode, SeqComputerModes, x);

      bool Status         = ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode;
      std::string Device  = ComputerMode.Device;
      std::string CtrlSystemCode;
    
      if (Device == DEF_COMP_MODES::Electric )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::Elec;
        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::GasLance )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::ManipGasLance;
        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::DynamicFeed )
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BinMatDynFeed;
        Status          = (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode) || (ComputerMode.Status == DEF_GC_COMP_STATUS::ComputerPatternMode);
      }
      else if (Device == DEF_COMP_MODES::PatternFeed)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BinMatPatternFeed;
      }
      else if (Device == DEF_COMP_MODES::TappingBatch)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BatchMatHndlg;
      }
      else if (Device == DEF_COMP_MODES::Burner)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::Burner;
      }
      else if (Device == DEF_COMP_MODES::MatHandle)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BatchMatHndlg;
      }
      else if (Device == DEF_COMP_MODES::Injection)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::CarbonLance;
      }
      else if (Device == DEF_COMP_MODES::Stirring)
      {
        CtrlSystemCode  = CCtrlSystemCodesEAF::BottomStirringDevice;
      }
      else
        continue;

      if ( !CtrlSystemCode.empty() )
      {
        CtrlSystemIt = CtrlSystemMap.find (CtrlSystemCode);
        if (CtrlSystemIt != CtrlSystemItEnd && CtrlSystemIt->second > 0)
        {
          pIntfEAF->setCompuModeOnOrOff(CtrlSystemCode, Status);
        }
      }
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFComputerModeWrapper::doOnSetComputerMode", ""  );          
  }
  

  return RetValue;
}

//##ModelId=4112777D0379
bool CEAFComputerModeWrapper::doOnSetEAFMaintenanceMode( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFComputerModeWrapper::doOnSetEAFMaintenanceMode(), (m_pModelTask) == false", 1);
    return false;
  }

  if (!pIntfEAF ) return false;
 
  try
  {
    pIntfEAF->setMaintMode(true);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFComputerModeWrapper::doOnSetEAFMaintenanceMode()", "" );          
  }


  return RetValue;
}

//##ModelId=429F1E93002E
bool CEAFComputerModeWrapper::doOnActivateWTC( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFComputerModeWrapper::doOnActivateWTC(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->actvWallTempCtrl();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFComputerModeWrapper::doOnActivateWTC()",   ""  );          
  }
  

  return RetValue;
}

//##ModelId=429F1E93004C
bool CEAFComputerModeWrapper::doOnDeactivateWTC( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!m_pModelTask) 
  {
    log("error CEAFComputerModeWrapper::doOnDeactivateWTC(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try
  {
    pIntfEAF->deactvWallTempCtrl();

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFComputerModeWrapper::doOnDeactivateWTC()",    ""  );          
  }
  

  return RetValue;
}


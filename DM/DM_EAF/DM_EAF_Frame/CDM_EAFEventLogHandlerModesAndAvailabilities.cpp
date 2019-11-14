// Copyright (C) 2005 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDM_EAFTask.h"
#include "CSMC_EventLogEAFController.h"
#include "DEF_GC_COMP_STATUS.h"
#include "CDM_EAFEventLogHandlerModesAndAvailabilities.h"

bool CDM_EAFEventLogHandlerModesAndAvailabilities::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {
    CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();

    if( Message == EAF_EvMsg::evEAFSetComputerMode )
    {
      seqComputerModes ActSeq; 
      sComputerMode ActStruct ; 
      ActSeq = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModes));

      long seqLength = CIntfData::getLength(ActSeq);

      for(int i=0;i<seqLength;i++)
      {
        CIntfData::getAt(ActStruct, ActSeq,i);
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));

        if ( ActStruct.Status == DEF_GC_COMP_STATUS::AutoMode )
        {
          pEventLog->EL_SetComputerModeAutomatic(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode )
        {
          pEventLog->EL_SetComputerModeDynamic(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerPatternMode )
        {
          pEventLog->EL_SetComputerModePattern(sMessage,ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ManualMode )
        {
          pEventLog->EL_SetComputerModeManual(sMessage,ActStruct.Device);
        }
      }

    }
    else if ( Message == EAF_EvMsg::evEAFActivateWallTempCtrl )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_ActivateWallTempCtrl(sMessage);
    } 
    else if ( Message == EAF_EvMsg::evEAFDeactivateWallTempCtrl )
    {      
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_DeactivateWallTempCtrl(sMessage);
    } 
    else
      RetValue = false;
  }

  return RetValue;
}


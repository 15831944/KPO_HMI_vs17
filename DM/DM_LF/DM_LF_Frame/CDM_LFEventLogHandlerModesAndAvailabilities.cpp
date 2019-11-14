// Copyright (C) 2004 SMS Demag AG, Germany

#include "iEventMessages_s.hh"
#include "CIntfData.h"
#include "CDateTime.h"
#include "CDM_LFTask.h"
#include "CSMC_EventLogLFController.h"
#include "DEF_GC_COMP_STATUS.h"
#include "CDM_LFEventLogHandlerModesAndAvailabilities.h"

bool CDM_LFEventLogHandlerModesAndAvailabilities::EventLog(CEventMessage& Event)
{
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  bool retValue  =false;

  if (m_pDataInterface)
  {
    CSMC_EventLogLF *pEventLog = CSMC_EventLogLFController::getInstance()->getpEventLog();

    if ( Message == LF_EvMsg::evLFSetComputerMode )
    {
      seqComputerModes ActSeq         = CIntfData::ToCORBAType(m_pDataInterface->getComputerModes(DataKey.c_str(),DATA::ComputerModes)); 
      std::string LadleTransferCarId  = m_pProductManagementInterface->getString(ProductID,DATA::LadleTransferCarId);
      sComputerMode ActStruct ; 

      long seqLength = CIntfData::getLength(ActSeq);

      for(int i=0;i<seqLength;i++)
      {
        CIntfData::getAt(ActStruct, ActSeq,i);

        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));

        if ( ActStruct.Status == DEF_GC_COMP_STATUS::AutoMode )
        {
          pEventLog->EL_SetComputerModeAutomatic(sMessage,LadleTransferCarId.c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode )
        {
          pEventLog->EL_SetComputerModeDynamic(sMessage,LadleTransferCarId.c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ComputerPatternMode )
        {
          pEventLog->EL_SetComputerModePattern(sMessage,LadleTransferCarId.c_str(),ActStruct.Device);
        }
        else if ( ActStruct.Status == DEF_GC_COMP_STATUS::ManualMode )
        {
          pEventLog->EL_SetComputerModeManual(sMessage,LadleTransferCarId.c_str(),ActStruct.Device);
        }
      }

      retValue = true;

    }
  }
  return retValue;
}


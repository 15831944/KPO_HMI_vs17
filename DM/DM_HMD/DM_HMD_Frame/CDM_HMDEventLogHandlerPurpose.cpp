// Copyright (C) 2007 SMS Demag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerPurpose.h"



//##ModelId=45139A72010A
bool CDM_HMDEventLogHandlerPurpose::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();

  if (m_pDataInterface)
  {//JOGE
    if ( Event.getMessage() == "test") //HMD_EvMsg::evHMDSteelAnalysisReceived )
    {
    }//JOGE
    else if ( Event.getMessage() == "test") //HMD_EvMsg::evHMDSteelAnalysisReceived )
    {
    }
    else
      RetValue = false;
  }
  else
    RetValue = false;

  return RetValue;
}


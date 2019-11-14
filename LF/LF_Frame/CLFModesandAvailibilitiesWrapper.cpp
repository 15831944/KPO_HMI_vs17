// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "DEF_GC_COMP_STATUS.h"

#include "CLFModelTask.h"
#include "CLFModesandAvailibilitiesWrapper.h"

//##ModelId=411388FB005C
bool CLFModesAndAvailibilitiesWrapper::doOnSetComputerMode(CEventMessage &Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFModesAndAvailibilitiesWrapper::doOnSetComputerMode(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }

  try
  {
    long              SeqLength;
    long              GetAtValue;
    seqComputerModes  SeqComputerModes;
    sComputerMode     CompModes;
    std::string       Device;

    SeqComputerModes  = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->
                                    getComputerModes(DEF_PLANT::Furnace, DATA::ComputerModes));

    SeqLength = CIntfData::getLength(SeqComputerModes);
    for (int x = 0; x < SeqLength; x++) 
    {
      GetAtValue  = CIntfData::getAt(CompModes, SeqComputerModes, x);
      Device      = CompModes.Device;
     pIntfLF->setCompuModeOnOrOff(Device, CompModes.Status == DEF_GC_COMP_STATUS::ComputerDynamicMode);//satk 04062018
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);	  
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFModesAndAvailibilitiesWrapper::doOnSetComputerMode()", ""  );    
  }


  return RetValue;
}


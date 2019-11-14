// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFModelTask.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CEAFBurnerWrapper.h"

//##ModelId=4112211402BE
bool CEAFBurnerWrapper::doOnBurnerStart( CEventMessage &Event )
{
	bool RetValue = false;

  #if defined EAF_BURNER
	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

  if (!m_pModelTask) 
	{
		log("error CEAFBurnerWrapper::doOnBurnerStart(), (m_pModelTask) == false", 1);
		return false;
	}

	try
	{
		long BurnerNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
								 Event.getDataKey().c_str(), DATA::BurnerNo);

		/*long BurnerNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getLong(
								 DEF_PLANT::Furnace, DATA::BurnerNo);*/

		pIntfEAF->hndlBurnerStart(BurnerNo);

		// Sequence Diagram: get model results / Call Sequence
		RetValue = doModelResult(Event);
	}
	catch (...) 
	{
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFBurnerWrapper::doOnBurnerStart()",  ""  );          
	}
  #endif

	return RetValue;
}

//##ModelId=41122128007A
bool CEAFBurnerWrapper::doOnBurnerEnd( CEventMessage &Event )
{
	bool RetValue = false;

  #if defined EAF_BURNER
	CIntfEAF *pIntfEAF = getpModelIntf();
	if (!pIntfEAF ) return false;

	if (!m_pModelTask) 
	{
		log("error CEAFBurnerWrapper::doOnBurnerEnd(), (m_pModelTask) == false", 1);
		return false;
	}

	try
	{
			seqGasLanceData seqLance     = CIntfData::ToCORBAType(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getGasLanceData(
								 Event.getDataKey().c_str(), DATA::BurnerAmount));

		  long BurnerNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getLong(
								 Event.getDataKey().c_str(), DATA::BurnerNo);

		  /*long BurnerNo     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PLANT)->getLong(
								 DEF_PLANT::Furnace, DATA::BurnerNo);*/

      /*if(CIntfData::getLength(seqLance)>0)
      {
        seqGasData seqGas = seqLance[0].LanceData;
        if(CIntfData::getLength(seqGas)== 2)
        {          
          pIntfEAF->hndlBurnerStop(seqGas[0].GasValue,seqGas[1].GasValue);

		      // Sequence Diagram: get model results / Call Sequence
		      RetValue = doModelResult(Event);
        }
      }*/
  
		  pIntfEAF->hndlBurnerStop(BurnerNo);

		  // Sequence Diagram: get model results / Call Sequence
		  RetValue = doModelResult(Event);
  

	}
	catch (...) 
	{
		cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
		sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
		pEventLog->EL_ExceptionCaught(sMessage, "","CEAFBurnerWrapper::doOnBurnerEnd()",   ""  );          
	}

  #endif

	return RetValue;
}


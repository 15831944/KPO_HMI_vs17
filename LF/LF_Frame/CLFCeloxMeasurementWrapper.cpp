// Copyright (C) 2011 SMS Siemag AG

#include "CIntfData.h"
#include "CIntfLF.h"
#include "cCBS_StdEventLogFrameController.h"
#include "iSMC_DataDefinitions_s.hh"

#include "CLFModelTask.h"
#include "CLFCeloxMeasurementWrapper.h"

//##ModelId=4166585002DD
bool CLFCeloxMeasurementWrapper::doOnCeloxMeasurement(CEventMessage& Event)
{
  bool RetValue = false;

  CIntfLF *pIntfLF = getpModelIntf();

  if (!pIntfLF || !m_pModelTask) 
  {
    log("error CLFCeloxMeasurementWrapper::doOnCeloxMeasurement(), (pIntfLF && m_pModelTask) == false", 1);
    return RetValue;
  }
  try
  {
    double Temp     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(Event.getDataKey().c_str(), DATA::MeasTemp);
    double ActyO2   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(Event.getDataKey().c_str(), DATA::MeasO2Conc);
    double ActyAl   = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getDouble(Event.getDataKey().c_str(), DATA::MeasAlConc);

    std::stringstream Message ;

    if (Temp <= 0.0)
    {
      Message << "ERROR: invalid Temperature: " << Temp << ", it will be ignored!\n";
      Temp = DEF::Inv_Double;
    }
    if (ActyO2 <= 0.0)
    {
      Message << "ERROR: invalid Oxygen Concentration: " << ActyO2 << ", it will be ignored!\n";
      ActyO2 = DEF::Inv_Double;
    }
    if (ActyAl<= 0.0)
    {
      Message << "ERROR: invalid Aluminium Concentration: " << ActyAl << ", it will be ignored!\n";
      ActyAl = DEF::Inv_Double;
    }

    Message << "Set pIntfLF->hndlCeloxMeas " << Temp << ", " << ActyO2 << ", " << ActyAl << ", true";
    log(Message.str(),3);

    pIntfLF->hndlCeloxMeas(Temp, ActyO2, ActyAl, true);

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "", "CLFCeloxMeasurementWrapper::doOnCeloxMeasurement()", ""  );    
  }

  return RetValue;
}
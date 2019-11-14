// Copyright (C) 2011 SMS Siemag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "CIntfEAF.h"

#include "CEAFTappedWeightWrapper.h"
#include "CDataConversion.h"

//##ModelId=41123B65009C
bool CEAFTappedWeightWrapper::doOnSetTappedWeight( CEventMessage &Event )
{
  bool RetValue = false;
  std::string ProductID = Event.getProductID();

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF )return false;
  
  try
  {
    double TappingMass    = m_pModelTask->getpDM_Interface(Event.getSender(),DM::PRODUCT)->getDouble(ProductID.c_str(), DATA::TappingMass);
    long ladleNo    = m_pModelTask->getpDM_Interface(Event.getSender(),DM::PRODUCT)->getLong(ProductID.c_str(), DATA::LadleNo);

    pIntfEAF->setTappedWgt(CDataConversion::LongToString(ladleNo), TappingMass); 

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...) 
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappedWeightWrapper::doOnSetTappedWeight()",  "" );          
  }
  

  return RetValue;
}


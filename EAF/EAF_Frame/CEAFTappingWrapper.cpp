// Copyright (C) 2004 SMS Demag AG

#include "iSMC_DataDefinitions_s.hh"

// Note: The file CIntfEAF.h includes Config.h with definitions which can be used within the Wrapper
#include "Config.h"
#include "CIntfEAF.h"
#include "CIntfData.h"
#include "CEAFTappingWrapper.h"
#include "CTreatStatCodesEAF.h"


//##ModelId=411239F903C1
bool CEAFTappingWrapper::doOnTappingStart( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    pIntfEAF->hndlTapStart();   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingWrapper::doOnTappingStart()",    ""   );    
  }
  

  return RetValue;
}



//##ModelId=411239E901F9
bool CEAFTappingWrapper::doOnTappingEnd( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

  if (!pIntfEAF ) return false;
  
  try 
  {
    std::string HiD(Event.getHeatID()  );
    std::string TiD(Event.getTreatID() );

    //2006-01-09 mrut get tapped weight from interface.
    double TappedMass     = m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::PRODUCT)->getDouble(
                                  Event.getProductID().c_str(), DATA::TappingMass);

    if ( (DEF::Inv_Double != TappedMass) && (TappedMass > 0.0) )
    {
      pIntfEAF->hndlTapEnd(TappedMass); 
    }
    else
    {
      pIntfEAF->hndlTapEnd();   
    }

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);



    ////////////////////////////////////////////////////////////////////////////////////////
    //mrut 2006-03-01 code -predator
    // update hot heel
    ////////////////////////////////////////////////////////////////////////////////////////
    /*try 
    {
      seqPredRes pPredRes = CIntfData::ToCORBAType(m_pModelResults->getPredRes(CEAFModelWrapper::m_PrevSetpointsKey.c_str(), DATA::EAFPredRes));

      if ( CIntfData::getLength(pPredRes) > 0 )
      {
        seqPredRes & PredRes  = pPredRes;

        double HHMSteel=0.;
        double HHTSteel=0.;
        double HHMSlag =0.;
        long SeqLen = CIntfData::getLength(PredRes);
        double DurationOfPrepPhase = 0;
        for (long i = 0; i < SeqLen; ++i)
        {
          sPredRes strPredRes;
          CIntfData::getAt(strPredRes, PredRes, i);
          if (std::string(strPredRes.Phase) == CTreatStatCodesEAF::HotHeel)
          {
            HHMSteel = strPredRes.GenRes.SteelWeight;
            HHMSlag  = strPredRes.GenRes.SlagWeight;
            HHTSteel = strPredRes.GenRes.Temp;
            break;
          }
        }

        if (!this->sequence_update_hot_heel_data(HiD, TiD,  HHMSteel, HHMSlag, HHTSteel))
        {
            std::string SearchKey = HiD + " " + TiD;
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ErrorProcessingData(sMessage,"sequence_update_hot_heel_data",SearchKey.c_str());
        }
      } //end if (pPredRes)
    }// end try
    catch (...)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", "CEAFTappingWrapper::doOnTappingEnd(),update hot heel",  "" );    
    }*/
    




  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingWrapper::doOnTappingEnd()", ""  );    
  }
  

  return RetValue;
}

//##ModelId=41123A380198
bool CEAFTappingWrapper::doOnTapLadleData( CEventMessage &Event )
{
  bool RetValue = false;

  CIntfEAF *pIntfEAF = getpModelIntf();

 if (!m_pModelTask) 
  {
    log("error CEAFTappingWrapper::doOnTapLadleData(), (m_pModelTask) == false", 1);
    return false;
  }
  if (!pIntfEAF ) return false;
  
  try 
  {
    string LadleId     = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
	                                    Event.getDataKey().c_str(), DATA::LadleNo));
    string LadleStat   = CIntfData::ToStdString(m_pModelTask->getpDM_Interface(Event.getSender(),CModelTask::EVENT)->getString(
	                                    Event.getDataKey().c_str(), DATA::TapLadleStatus));

    pIntfEAF->hndlTapLadleData(LadleId, LadleStat);   

    // Sequence Diagram: get model results / Call Sequence
    RetValue = doModelResult(Event);
  }
  catch (...)
  {
    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "",
      "CEAFTappingWrapper::doOnTapLadleData()",  "" );    
  }

  return RetValue;
}


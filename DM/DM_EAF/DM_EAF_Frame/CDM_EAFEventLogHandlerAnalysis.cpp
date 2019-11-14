// Copyright (C) 2011 SMS Siemag AG

#include "iEventMessages_s.hh"
#include "CDateTime.h"
#include "CDM_EAFTask.h"
#include "CIntfData.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogEAFController.h"
#include "CDataConversion.h"
#include "DEF_GC_MEASUREMENT_NAME.h"

#include "CDM_EAFEventLogHandlerAnalysis.h"

bool CDM_EAFEventLogHandlerAnalysis::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();
  CDateTime Now;

  if (m_pDataInterface)
  {

    CSMC_EventLogEAF *pEventLog = CSMC_EventLogEAFController::getInstance()->getpEventLog();

    if ( Message == EAF_EvMsg::evEAFSteelAnalysisReceived )
    {
      CDateTime SampleTime;
      SampleTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::SteelSampleTime);

      CDataConversion::SetInvalidToDefault(SampleTime,Now);

      sEventLogMessage sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_SteelAnalysisReceived(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleId),"-").c_str(),
        SampleTime.asString().c_str());

      seqAnalysisData SeqAnalysisData = CIntfData::ToCORBAType(m_pDataInterface->getAnalysisData(DataKey.c_str(), DATA::SteelMeasAnalysis));
      sAnalysisData AnalysisData; 

      CIntfData::getAt(AnalysisData, SeqAnalysisData, 0);
      seqAnalysis SeqAnalysis = AnalysisData.Analysis;

      // *************************************************************************************************

      sAnalysisString Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::C);
      sAnalysisString Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Mn);
      sAnalysisString Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::P);
      sAnalysisString Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::S);
      sAnalysisString Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Si);

      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration );

      // *************************************************************************************************

      Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::N2);
      Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Al);
      Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Al_S);
      Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Cu);
      Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Sn);

      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration );

      // *************************************************************************************************

      Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Cr);
      Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Ni);
      Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Mo);
      Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::V);
      Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::B);

      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration );

      // *************************************************************************************************

      Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Ti);
      Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Ca);
      Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::H2);
      Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::O2);
      Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, "");


      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration );

      // *************************************************************************************************

    }
    else if ( Message == EAF_EvMsg::evEAFSlagAnalysisReceived )
    {
      CDateTime SampleTime;
      SampleTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::SlagSampleTime);

      CDataConversion::SetInvalidToDefault(SampleTime,Now); 

      sEventLogMessage sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_SlagAnalysisReceived(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleId),"-").c_str(),
        SampleTime.asString().c_str());

      seqAnalysisData SeqAnalysisData = CIntfData::ToCORBAType(m_pDataInterface->getAnalysisData(DataKey.c_str(), DATA::SlagMeasAnalysis));
      sAnalysisData AnalysisData; 

      CIntfData::getAt(AnalysisData, SeqAnalysisData, 0);
      seqAnalysis SeqAnalysis = AnalysisData.Analysis;

      // *************************************************************************************************

      sAnalysisString Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::CaO);
      sAnalysisString Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Al2O3);
      sAnalysisString Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::SiO2);
      sAnalysisString Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::FeO);
      sAnalysisString Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::MnO);

      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration);

      // *************************************************************************************************

      Analysis1 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::MgO);
      Analysis2 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::TiO2);
      Analysis3 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::P2O5);
      Analysis4 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::V2O5);
      Analysis5 = CSMC_DataProvider_Impl::getsAnalysisString(SeqAnalysis, DEF_GC_MEASUREMENT_NAME::Cr2O3);

      sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_Analysis(sMessage, 
                                      Analysis1.Element ,Analysis1.Concentration,
                                      Analysis2.Element ,Analysis2.Concentration,
                                      Analysis3.Element ,Analysis3.Concentration,
                                      Analysis4.Element ,Analysis4.Concentration,
                                      Analysis5.Element ,Analysis5.Concentration);

      // *************************************************************************************************

    }
    else if ( Message == EAF_EvMsg::evEAFSteelSampleTaken )
    {
      sEventLogMessage sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_SteelSampleTaken(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleId),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleNo),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleLocation),"-").c_str());
    }
    else if ( Message == EAF_EvMsg::evEAFSlagSampleTaken )
    {
      sEventLogMessage sMessage = initEventLogMessage(__FILE__,__LINE__,ProductID);
      pEventLog->EL_SlagSampleTaken(sMessage,
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleId),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleNo),"-").c_str(),
        CDataConversion::SetInvalidToDefault(m_pDataInterface->getString(DataKey,DATA::SampleLocation),"-").c_str());
    }
    else
    {
      RetValue = false; // The event is for this handler, but the handler doesn't have a do-method
    }
  }
  return RetValue;
}

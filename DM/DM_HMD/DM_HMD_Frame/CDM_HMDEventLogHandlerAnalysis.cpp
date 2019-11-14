// Copyright (C) 2007 SMS Demag AG

#include "CDateTime.h"
#include "CDM_HMDTask.h"
#include "iEventMessages_s.hh"
#include "CIntfData.h"
#include "CSMC_EventLogFrameController.h"
#include "CSMC_EventLogHMDController.h"
#include "CDM_HMDEventLogHandlerAnalysis.h"




//##ModelId=45139A720132
bool CDM_HMDEventLogHandlerAnalysis::EventLog(CEventMessage& Event)
{
  bool RetValue = true;
  std::string Message = Event.getMessage();
  std::string DataKey = Event.getDataKey();
  std::string ProductID = Event.getProductID();

  if (m_pDataInterface)
  {

    CSMC_EventLogHMD *pEventLog = CSMC_EventLogHMDController::getInstance()->getpEventLog();

    if ( Message == HMD_EvMsg::evHMDHotMetalAnalysisReceived )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HotMetalAnalysisReceived(sMessage,
        m_pDataInterface->getString(DataKey,DATA::SampleCode).c_str(),
		m_pDataInterface->getLong(DataKey,DATA::SampleId));
      seqAnalysis MeasAnalysis = CIntfData::ToCORBAType(m_pDataInterface->getAnalysis(DataKey.c_str(), DATA::SteelMeasAnalysis));
      long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
      string Code1 = "C";
      string Code2 = "Cr";
      string Code3 = "Mn";
      string Code4 = "Ni";
      string Code5 = "S";
      double  Val1  = 0.;
      double  Val2  = 0.;
      double  Val3  = 0.;
      double  Val4  = 0.;
      double  Val5  = 0.;

      for (int x = 0; x<LengthMeasAnalysis; x++) 
      {
        sAnalysis strAnalysis;
        string Element;
        long GetAtValue = CIntfData::getAt(strAnalysis, MeasAnalysis, x);
        Element = strAnalysis.Element;
        if (Element == Code1) Val1 = strAnalysis.Concentration;
        else if (Element == Code2) Val2 = strAnalysis.Concentration;
        else if (Element == Code3) Val3 = strAnalysis.Concentration;
        else if (Element == Code4) Val4 = strAnalysis.Concentration;
        else if (Element == Code5) Val5 = strAnalysis.Concentration;
      }

      sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_Analysis(sMessage,
        Code1.c_str(),Val1,Code2.c_str(),Val2,Code3.c_str(),Val3,Code4.c_str(),Val4,Code5.c_str(),Val5);

    }
    else if ( Message == HMD_EvMsg::evHMDSlagAnalysisReceived )
    {
      CDateTime SampleTime;
      SampleTime << m_pDataInterface->getDate(DataKey.c_str(),DATA::SlagSampleTime);

      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SlagAnalysisReceived(sMessage,
        m_pDataInterface->getString(DataKey,DATA::SampleCode).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::SampleId));
      seqAnalysis MeasAnalysis = CIntfData::ToCORBAType(m_pDataInterface->getAnalysis(Event.getDataKey().c_str(), DATA::SlagMeasAnalysis));
      long LengthMeasAnalysis = CIntfData::getLength(MeasAnalysis);
      string Code1 = "CaO";
      string Code2 = "SiO2";
      string Code3 = "Cr2O3";
      string Code4 = "MgO";
      string Code5 = "MnO";
      double  Val1  = 0.;
      double  Val2  = 0.;
      double  Val3  = 0.;
      double  Val4  = 0.;
      double  Val5  = 0.;
      for (int x = 0; x<LengthMeasAnalysis; x++) 
      {
        sAnalysis strAnalysis;
        string Element;
        long GetAtValue = CIntfData::getAt(strAnalysis, MeasAnalysis, x);
        Element = strAnalysis.Element;
        if (Element == Code1) Val1 = strAnalysis.Concentration;
        else if (Element == Code2) Val2 = strAnalysis.Concentration;
        else if (Element == Code3) Val3 = strAnalysis.Concentration;
        else if (Element == Code4) Val4 = strAnalysis.Concentration;
        else if (Element == Code5) Val5 = strAnalysis.Concentration;
      }

      sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_Analysis(sMessage,
        Code1.c_str(),Val1,Code2.c_str(),Val2,Code3.c_str(),Val3,Code4.c_str(),Val4,Code5.c_str(),Val5);

    }
    else if ( Message == HMD_EvMsg::evHMDHotMetalSampleTaken )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_HotMetalSampleTaken(sMessage,
        m_pDataInterface->getString(DataKey,DATA::SampleId).c_str(),
        m_pDataInterface->getLong(DataKey,DATA::SampleId),
        m_pDataInterface->getString(DataKey,DATA::SampleLocation).c_str());
    }
    else if ( Event.getMessage() == HMD_EvMsg::evHMDSlagSampleTaken )
    {
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__,getProcessState(ProductID),ProductID,getExternalHeatID(ProductID));
      pEventLog->EL_SlagSampleTaken(sMessage,
        m_pDataInterface->getString(DataKey,DATA::SampleCode).c_str(),
		m_pDataInterface->getLong(DataKey,DATA::SampleId),
        m_pDataInterface->getString(DataKey,DATA::SampleLocation).c_str());
    }
    else
      RetValue = false;
  }
  else
    RetValue = false;

  return RetValue;
}

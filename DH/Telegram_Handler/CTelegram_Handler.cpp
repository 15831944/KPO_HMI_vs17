// Copyright (C) 2011 SMS Siemag AG
#if defined(WIN32) || defined(_WIN32)
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <string>
#include <vector>

#include "iSMC_DataDefinitions_s.hh"

#include "CSMC_DataProvider_Impl.h"
#include "CSMC_EventLogFrameController.h"
#include "CTelegram_Handler.h"
#include "cCBS_StdLog_Task.h"
#include "cCBS_StdInitBase.h"
#include "CTelegram_Adapter.h"
#include "CDataConversion.h"
#include "CSMC_DBData.h"

CTelegram_Handler::~CTelegram_Handler()
{
}

CTelegram_Handler::CTelegram_Handler()
:m_pTelegram_Adapter (0), m_pGC_Plant_Container(0), m_pHeatDataConverter(0)
{
}

void CTelegram_Handler::log(const std::string& message, long Level)
{
  if (m_pTelegram_Adapter && m_pTelegram_Adapter->m_pEvent_Task)
  {
    m_pTelegram_Adapter->m_pEvent_Task->log(message, Level);
  }
}

std::string CTelegram_Handler::generateDataKey(const std::string & Value)
{
  std::string ActValue = Value;
  if (m_pTelegram_Adapter->m_pIntf_OUT)
  {
    ActValue = m_pTelegram_Adapter->m_pIntf_OUT->generateDataKey(Value);
  }

  return ActValue;

}

void CTelegram_Handler::assignTelegramAdapter(CTelegram_Adapter* newAdapter)
{
	m_pTelegram_Adapter = newAdapter;
}

bool CTelegram_Handler::checkInternalData(const std::string& TlgName, std::string& HeatId, std::string& TreatId, std::string Plant, std::string& CustHeatId, std::string& CustTreatId)
{
  bool RetValue = true;

  std::stringstream strFunction;
  std::stringstream strAction;
  std::stringstream strMsg;

  strFunction << "CTelegram_Handler::checkInternalData: " << TlgName ;

  strAction << " Plant:" << Plant << ","
            << " HeatId:" << HeatId << ","
            << " TreatId:" << TreatId;

  try
  {
    HeatId        = CDataConversion::Trim(HeatId);
    TreatId       = CDataConversion::Trim(TreatId);

    if ( !HeatId.empty() && HeatId != DEF::Inv_String )
    {
      if( m_pHeatDataConverter )
      {
        if ( m_pHeatDataConverter->getCustHeatData(HeatId,TreatId,CustHeatId,CustTreatId,Plant) )
        {
          CustHeatId    = CDataConversion::Trim(CustHeatId);
          CustTreatId   = CDataConversion::Trim(CustTreatId); 
        }
      }// if( m_pHeatDataConverter )
      else
      {
        strMsg << " No connection to database!: " << TlgName
               << " InternalHeatId:" << HeatId  << " InternalTreatId:" << TreatId;

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage, "","HeatDataConverter",strMsg.str().c_str());

        RetValue = false;
      }

      // don't send something like "Inva"
      CustHeatId  = CDataConversion::SetInvalidToDefault(CustHeatId,"");
      CustTreatId = CDataConversion::SetInvalidToDefault(CustTreatId,"");

      if ( CustHeatId.empty() || CustTreatId.empty() )
      {
        strMsg << CustHeatId << " and " << CustTreatId << " are unknown";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID and TreatID",strMsg.str().c_str());

        RetValue = false;
      }
    }// if ( !HeatId.empty() && HeatId != DEF::Inv_String )
    else
    { 
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown", strFunction.str().c_str(),strAction.str().c_str()); 
  }

  return RetValue;
}

bool CTelegram_Handler::CheckCustomerData(const std::string& TlgName, std::string& CustHeatId, std::string& CustTreatId, std::string& HeatId, std::string& TreatId, std::string Plant)
{
  bool RetValue = true;

  std::stringstream strFunction;
  std::stringstream strAction;
  std::stringstream strMsg;

  strFunction << "CTelegram_Handler::CheckCustomerData: " << TlgName ;

  strAction << " Plant:" << Plant << ","
            << " CustHeatId:" << CustHeatId << ","
            << " CustTreatId:" << CustTreatId;

  CustHeatId    = CDataConversion::Trim(CustHeatId);
  CustTreatId   = CDataConversion::Trim(CustTreatId); 

  try
  {  
    if ( !CustHeatId.empty() && CustHeatId != DEF::Inv_String )
    {
      if( m_pHeatDataConverter )
      {
        m_pHeatDataConverter->getInternalHeatData(CustHeatId,CustTreatId,HeatId,TreatId,Plant);

        // don't use something like "Inva"
        HeatId  = CDataConversion::SetInvalidToDefault(HeatId,"");
        TreatId = CDataConversion::SetInvalidToDefault(TreatId,"");

        if ( HeatId.empty() || TreatId.empty() )
        {
          strMsg << CustHeatId << " or " << CustTreatId << " are unknown";

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatId or TreatId",strMsg.str().c_str());

          RetValue = false;
        }
      }// if( m_pHeatDataConverter )
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorPointerHandling(sMessage, strFunction.str().c_str(),"m_pHeatDataConverter not instatiated !");

        RetValue = false;
      }
    }// if ( !CustHeatID.empty() && CustHeatID != DEF::Inv_String )
    else
    { 
      RetValue = false;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TlgName.c_str(),"HeatID","empty");  
    }
  }
  catch (cCBS_DBExc &e)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
      strFunction.str().c_str(), strAction.str().c_str()); 
  }
  catch(CORBA::Exception& cExc) 
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
      strFunction.str().c_str(), strAction.str().c_str());
  }
  catch(...)
  {
    RetValue = false;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage, "Unknown",
      strFunction.str().c_str(),strAction.str().c_str()); 
  }

  return RetValue;
}


bool CTelegram_Handler::handleErrorCode(const std::string& Key, long ErrorCode)
{
  bool RetValue = true;

  try
  {
    if (m_pTelegram_Adapter && m_pTelegram_Adapter->m_pIntf_IN)
    {
      // we want to forward the first known ErrorCode
      // if a ErrorCode is still avaialable, we will not overwrite it !
      if ( m_pTelegram_Adapter->m_pIntf_IN->getLong(Key, DATA::ErrorCode) == DEF::Inv_Long )
      {
        m_pTelegram_Adapter->m_pIntf_IN->setLong(Key, DATA::ErrorCode, ErrorCode);
      }
    }
    else
    {
      RetValue = false;
    }
  }
  catch(...)
  {
    RetValue = false;
  }

  return RetValue;
}

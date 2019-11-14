// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELEGRAM_HANDLER_40F7CE8E0138_INCLUDED
#define _INC_CTELEGRAM_HANDLER_40F7CE8E0138_INCLUDED

#include <string>

#include "CTelegram_EventHandler.h"
#include "CTelegram_Adapter.h"
#include "CGC_Plant_Container.h"
#include "CHeatDataConverter.h"
#include "CDateTime.h"
#include "CStatusHandler.h"
#include "CSMC_EventLogFrameController.h"

using namespace std;

class CTelegram_DataProfile;
class CPlantID;

class CTelegram_Handler 
{
public:
  bool handleErrorCode(const std::string& Key, long ErrorCode);

  virtual bool doOnComplete(const std::string& Key, const std::string& TlgName) = 0;

  void assignTelegramAdapter(CTelegram_Adapter* newAdapter);

  std::string generateDataKey(const std::string & Value);

  void log(const std::string& message, long Level);

  virtual ~CTelegram_Handler();

  CTelegram_Handler();

private:

protected:
  // returns true if Min >= Value <= Max for each element of sequence
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, DEF::seqLong Seq, long Min, long Max)
  {
    bool RetValue = true;
    for ( long i = 0 ; i < CIntfData::getLength(Seq); ++i )
    {
      long Value = -1;
      CIntfData::getAt(Value,Seq,i);

      if ( !checkValidity(TelegramName, ValueName, Value, Min, Max ) )
      {
        std::stringstream Message;
        Message << ValueName << " [" << i << "]";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),Message.str().c_str(),Value,Min,Max);

        RetValue = false;
      }
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, DEF::seqLong Seq, long Min, long Max)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Seq, Min, Max);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Min >= Value <= Max for each element of sequence
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, DEF::seqDouble Seq, double Min, double Max)
  {
    bool RetValue = true;
    for ( long i = 0 ; i < CIntfData::getLength(Seq); ++i )
    {
      double Value = -1;
      CIntfData::getAt(Value,Seq,i);

      if ( !checkValidity(TelegramName, ValueName, Value, Min, Max ) )
      {
        std::stringstream Message;
        Message << ValueName << " [" << i << "]";

        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),Message.str().c_str(),Value,Min,Max);

        RetValue = false;
      }
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, DEF::seqDouble Seq, double Min, double Max)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Seq, Min, Max);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Min >= Value <= Max
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, long Value, long Min, long Max)
  {
    bool RetValue = true;

    if ( Value < Min || Value > Max )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),Value,Min,Max);

      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, long Value, long Min, long Max)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Min, Max);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  inline bool checkValidityToDefault(const std::string & TelegramName, const std::string & ValueName, long &Value, long Min, long Max, long Default)
  {
    bool RetValue = true;

    if ( Value < Min || Value > Max )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgDataToDefault(sMessage,TelegramName.c_str(),ValueName.c_str(),Value,Min,Max,Default);

      Value = Default;

      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidationToDefault(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, long &Value, long Min, long Max, long Default)
  {
    bool RetValue = checkValidityToDefault(TelegramName, ValueName, Value, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Min >= Value <= Max
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, double Value, double Min, double Max)
  {
    bool RetValue = true;

    if ( Value < Min || Value > Max )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),Value,Min,Max);

      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, double Value, double Min, double Max)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Min, Max);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  inline bool checkValidityToDefault(const std::string & TelegramName, const std::string & ValueName, double &Value, double Min, double Max, double Default)
  {
    bool RetValue = true;

    if ( Value < Min || Value > Max )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgDataToDefault(sMessage,TelegramName.c_str(),ValueName.c_str(),Value,Min,Max,Default);

      Value = Default;

      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidationToDefault(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, double &Value, double Min, double Max, double Default)
  {
    bool RetValue = checkValidityToDefault(TelegramName, ValueName, Value, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Min >= Value <= Max && Value != Default for each element of sequence
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, DEF::seqLong Seq, long Min, long Max, long Default)
  {
    bool RetValue = true;
    for ( long i = 0 ; i < CIntfData::getLength(Seq); ++i )
    {
      long Value = -1;
      CIntfData::getAt(Value,Seq,i);

      if ( Value != Default )
      {
        if ( !checkValidity(TelegramName, ValueName, Value, Min, Max ) )
        {
          std::stringstream Message;
          Message << ValueName << " [" << i << "]";

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),Message.str().c_str(),Value,Min,Max);

          RetValue = false;
        }
      }
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, DEF::seqLong Seq, long Min, long Max, long Default)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Seq, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  // returns true if Min >= Value <= Max && Value != Default for each element of sequence
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, DEF::seqDouble Seq, double Min, double Max, double Default)
  {
    bool RetValue = true;
    for ( long i = 0 ; i < CIntfData::getLength(Seq); ++i )
    {
      double Value = -1;
      CIntfData::getAt(Value,Seq,i);

      if ( Value != Default )
      {
        if ( !checkValidity(TelegramName, ValueName, Value, Min, Max ) )
        {
          std::stringstream Message;
          Message << ValueName << " [" << i << "]";

          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),Message.str().c_str(),Value,Min,Max);

          RetValue = false;
        }
      }
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, DEF::seqDouble Seq, double Min, double Max, double Default)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Seq, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Min >= Value <= Max && Value != Default
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, long Value, long Min, long Max, long Default)
  {
    bool RetValue = true;
    if ( Value != Default )
    {
      RetValue = checkValidity(TelegramName,ValueName,Value,Min,Max);
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, long Value, long Min, long Max, long Default)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  // returns true if Min >= Value <= Max && Value != Default
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, double Value, double Min, double Max, double Default)
  {
    bool RetValue = true;

    if ( Value != Default )
    {
      RetValue = checkValidity(TelegramName,ValueName,Value,Min,Max);
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, double Value, double Min, double Max, double Default)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Min, Max, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  // returns true if Value != DEF::InvalidString
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, const std::string & Value)
  {
    bool RetValue = true;

    if ( Value == DEF::Inv_String )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

      std::string ActValue = "<" + Value + ">";

      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),ActValue.c_str());
      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, const std::string & Value)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  // returns true if Value != CDateTime::InvalidDate
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, const CDateTime & Value)
  {
    bool RetValue = true;

    if ( Value == CDateTime::InvalidDateTime() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),Value.asString().c_str());
      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, const CDateTime & Value)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Value != DEF::InvalidString
  inline bool checkValidityOrEmpty(const std::string & TelegramName, const std::string & ValueName, const std::string & Value)
  {
    bool RetValue = true;

    if ( Value == DEF::Inv_String || Value.empty() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

      std::string ActValue = "<" + Value + ">";

      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),ActValue.c_str());
      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidationOrEmpty(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, const std::string & Value)
  {
    bool RetValue = checkValidityOrEmpty(TelegramName, ValueName, Value);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }


  // returns true if Value == Validator
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, const std::string & Value, const std::string & Validator)
  {
    bool RetValue = true;

    if ( Value != Validator )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

      std::string ActValue = "<" + Value + ">";

      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),ValueName.c_str(),ActValue.c_str());
      RetValue = false;
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, const std::string & Value, const std::string & Validator)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Validator);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  // checks if Value is in sequence of Validator or equals Default
  // otherwise returns false
  inline bool checkValidity(const std::string & TelegramName, const std::string & ValueName, const std::string & Value, DEF::seqString Validator, std::string Default)
  {
    bool RetValue = false;

    for ( long i = 0 ; i < CIntfData::getLength(Validator); ++i )
    {
      std::string ValidatorValue;
      CIntfData::getAt(ValidatorValue,Validator,i);

      if ( ValidatorValue == Default )
      {
        RetValue = true;
        break;
      }

      if ( Value == ValidatorValue )
      {
        RetValue = true;
        break;
      }
      else
      {
        RetValue = false;
      }
    }

    if ( !RetValue )
    {
      std::stringstream Message;
      Message << ValueName ;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);

      std::string ActValue = "<" + Value + ">";
      pEventLog->EL_InvalidTlgData(sMessage,TelegramName.c_str(),Message.str().c_str(),ActValue.c_str());
    }

    return RetValue;
  }
  inline bool setErrorOnValidation(const std::string& Key, long ErrorCode, const std::string & TelegramName, const std::string & ValueName, const std::string & Value, DEF::seqString Validator, std::string Default)
  {
    bool RetValue = checkValidity(TelegramName, ValueName, Value, Validator, Default);

    if ( !RetValue )
    {
      handleErrorCode(Key, ErrorCode);
    }

    return RetValue;
  }

  bool checkInternalData(const std::string& TlgName, std::string& HeatId, std::string& TreatId, std::string Plant, std::string& CustHeatId, std::string& CustTreatId);

  bool CheckCustomerData(const std::string& TlgName, std::string& CustHeatId, std::string& CustTreatId, std::string& HeatId, std::string& TreatId, std::string Plant);

  
	CHeatDataConverter* m_pHeatDataConverter;

	//PlantID converter between L1<-->L2
	CGC_Plant_Container* m_pGC_Plant_Container;

	std::vector <std::string> EventMessageVector;

	CTelegram_EventHandler m_EventHandler;

	CTelegram_Adapter* m_pTelegram_Adapter;

  CStatusHandler m_StatusHandler;

};

#endif /* _INC_CTELEGRAM_HANDLER_40F7CE8E0138_INCLUDED */

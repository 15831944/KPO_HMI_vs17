// Copyright (C) 2004 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDATACONVERSION_439ECDDE03BE_INCLUDED
#define _INC_CDATACONVERSION_439ECDDE03BE_INCLUDED

#include <sstream>
#include <string>
#include <iomanip>
#include <complex>

#include "iData_Provider_s.hh"

#include "CDateTime.h"
#include "CSMC_EventLogFrameController.h"

// class is containing Data Conversion methods as static members beeing defined at header file only 

class CDataConversion 
{

public:

  static inline std::string LongToString(const long Value)
  {
    std::string ret(DEF::Inv_String);

    if ( Value == Value ) // check for NaN
    {
      std::ostringstream os;
      os<<Value;

      if (!os.fail()) //includes bad
      {
        ret = os.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongToString","-");
      }
    }//if ( Value == Value ...
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongToString","Value is not a number");
    }

    return ret;
  }

  static inline long StringToLong(const std::string& value)
  {
    long temp_convert = DEF::Inv_Long;

    std::stringstream stream;		
    stream << value;
    stream >> temp_convert;

    if ( stream.fail() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::StringToLong",value.c_str());

      temp_convert = DEF::Inv_Long;
    }

    return temp_convert;
  }


  static inline long StringToLong(const std::string& value, long Default)
  {
    return SetInvalidToDefault(StringToLong(value),Default);
  }

  static inline std::string LongToString(const long value, const std::string& Default)
  {
    return SetInvalidToDefault(LongToString(value),Default);
  }

  // ******************************************
  static inline std::string LongLongToString(const long long Value)
  {
    std::string ret(DEF::Inv_String);

    if ( Value == Value ) // check for NaN
    {
      std::ostringstream os;
      os<<Value;

      if (!os.fail())
      {
        ret = os.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongLongToString","-");
      }
    }//if ( Value == Value )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongLongToString","Value is not a number");
    }

    return ret;
  }

  static inline long long StringToLongLong(const std::string& value)
  {
    long long temp_convert = DEF::Inv_LongLong; 

    std::stringstream stream;		
    stream << value;
    stream >> temp_convert;

    if ( stream.fail() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::StringToLongLong",value.c_str());

      temp_convert = DEF::Inv_LongLong;
    }

    return temp_convert;
  }


  static inline long long StringToLongLong(const std::string& value, long long Default)
  {
    return SetInvalidToDefault(StringToLongLong(value),Default);
  }

  static inline std::string LongLongToString(const long long value, const std::string& Default)
  {
    return SetInvalidToDefault(LongLongToString(value),Default);
  }


  static inline std::string  IntToString(const int Value)
  {
    std::string ret(DEF::Inv_String);

    if ( Value == Value ) // check for NaN
    {
      std::ostringstream os;
      os<<Value;

      if (!os.fail())
      {
        ret = os.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::IntToString","-");
      }
    }//if ( Value == Value )
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::IntToString","Value is not a number");
    }

    return ret;
  }

  static inline int StringToInt(const std::string& value)
  {
    int temp_convert = -1;
    
    std::stringstream stream;		
    stream << value;
    stream >> temp_convert;

    if ( stream.fail() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::StringToInt",value.c_str());

      temp_convert = -1;
    }

    return temp_convert;
  }

  static inline double StringToDouble(const std::string& value, double Default)
  {
    return SetInvalidToDefault(StringToDouble(value),Default);
  }

  static inline double StringToDouble(const std::string& value)
  {
    double doubleNum = DEF::Inv_Double;
    
    std::stringstream temp;
    temp << value;
    temp >> doubleNum;

    if ( temp.fail() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::StringToDouble",value.c_str());

      doubleNum = DEF::Inv_Double;
    }

    return doubleNum;
  }

  static inline std::string DoubleToString(double Value)
  {
    std::string stringVal(DEF::Inv_String);
        
    if ( Value == Value ) // check for NaN
    {
      std::stringstream temp;
      temp << Value;
            
      if (!temp.fail())
      {
        stringVal = temp.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::DoubleToString","-");
      }
    }//if ( Value == Value ...
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::DoubleToString","Value is not a number");
    }

    return stringVal;
  }

  static inline std::string DoubleToString(double Value, int ValWide, char FillSign = '0')
  {
    std::string stringVal(DEF::Inv_String);

    if ( Value == Value ) // check for NaN
    {
      std::stringstream temp;
      temp << std::setw(ValWide) << std::setfill(FillSign) << Value;

      if (!temp.fail())
      {
        stringVal = temp.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::DoubleToString","-");
      }
    }//if ( Value == Value ...
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::DoubleToString","Value is not a number");
    }

    return stringVal;
  }

  static inline std::wstring StringToWstring(const std::string & value)
  {
    std::wstring temp( value.begin(), value.end() );
    return temp;
  }


  static inline std::string LongToString(long Value, int ValWide, char FillSign = '0')
  {
    std::string stringVal(DEF::Inv_String);

    if ( Value == Value ) // check for NaN
    {
      std::stringstream temp;
      temp << std::setw(ValWide) << std::setfill(FillSign) << Value;

      if (!temp.fail())
      {
        stringVal = temp.str();
      }
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongToString","-");
      }
    }//if ( Value == Value ...
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongToString","Value is not a number");
    }

    return stringVal;
  }

  static inline std::string TruncateDoubleToString(double Value, int ValWide, char FillSign = '0', bool RightJustified = true)
  {
    std::string stringVal = DoubleToString(Value, ValWide, FillSign);
    stringVal = Truncate(stringVal, ValWide, RightJustified);

    return stringVal;
  }

  static inline std::string TruncateLongToString(long Value, int ValWide, char FillSign = '0', bool RightJustified = true)
  {
    std::string stringVal = LongToString(Value, ValWide, FillSign);
    stringVal = Truncate(stringVal, ValWide, RightJustified);

    return stringVal;
  }

  static inline std::string Trim(const std::string& Value, const std::string& Sign = " ")
  {
    std::string RetValue;

    if ( Value.length() > 0 )
    {
      RetValue = Value.substr(Value.find_first_not_of(Sign),Value.length());
      RetValue = RetValue.substr(0,RetValue.find_first_of(Sign));
    }

    return RetValue;
  }

  static inline std::string FillRight(const std::string& Value, long Lenght, const std::string& Sign = " ")
  {
    std::string RetValue;

    long NoOfFill = Lenght - Value.length();

    if ( NoOfFill > 0 )
    {
      RetValue.insert(0       , Value);
      RetValue.append(NoOfFill, *Sign.c_str());
    }
    else
    {
      RetValue = Value;
    }

    return RetValue;
  }

  static inline std::string FillLeft(const std::string& Value, long Lenght, const std::string& Sign = " ")
  {
    std::string RetValue;

    long NoOfFill = Lenght - Value.length();

    if ( NoOfFill > 0 )
    {
      RetValue.append(NoOfFill, *Sign.c_str());
      RetValue.insert(NoOfFill, Value);
    }
    else
    {
      RetValue = Value;
    }

    return RetValue;
  }

  static inline std::string TruncateAndSetInvalidToDefault(const std::string& Value, long Size, std::string Default, bool RightJustified = true)
  {
    return Truncate(SetInvalidToDefault(Value,Default), Size, RightJustified);
  }

  static inline std::string TruncateAndSetInvalidToDefault(long Value, long Size, std::string Default, bool RightJustified = true)
  {
    return TruncateAndSetInvalidToDefault(LongToString(Value), Size, Default, RightJustified );
  }

  static inline std::string CheckLengthAndTruncate(const std::string& Value, long Size, bool RightJustified = true)
  {
    std::string RetValue = Truncate(Value, Size, RightJustified);

    if ( (long)Value.length() != (long)RetValue.length() )
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ViolationColPrecision(Message,"CDataConversion","CheckLengthAndTruncate",Value.c_str(),RetValue.c_str());
    }

    return RetValue;
  }

  static inline std::string Truncate(const std::string& Value, long Size, bool RightJustified = true)
  {
    std::string RetValue;

    if ( (long)Value.length() > Size )
    {
      if ( RightJustified )
      {
        RetValue = Value.substr( ( Value.length() - Size) , Value.length() );
      }
      else
      {
        RetValue = Value.substr( 0 , Size );
      }
    }
    else
    {
      RetValue = Value;
    }

    return RetValue;
  }

  static long SetToRange(long value, long Default, long Min, long Max, long Validator = DEF::Inv_Long)
  {
    long RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }
    else
    {
      if ( value > Max )
      {
        RetValue = Max;
      }
      if ( value < Min )
      {
        RetValue = Min;
      }
    }

    return RetValue;
  }

  static inline double SetToRange(double value, double Default, double Min, double Max, double Validator = DEF::Inv_Double)
  {
    double RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }
    else
    {
      if ( value > Max )
      {
        RetValue = Max;
      }
      if ( value < Min )
      {
        RetValue = Min;
      }
    }

    return RetValue;
  }

  static inline std::string SetToRange(const std::string& value, std::string Default, std::string Validator = DEF::Inv_String)
  {
    std::string RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline long SetInvalidToDefault(long value, long Default, long Validator = DEF::Inv_Long)
  {
    long RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline long long SetInvalidToDefault(long long value, long long Default, long long Validator = DEF::Inv_Long)
  {
    long long RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }


  static inline long SetInvalidRangeToDefault(long value, long Default, long Min, long Max)
  {
    long RetValue = value; 

    if ( value > Max )
    {
      RetValue = Default;
    }
    if ( value < Min )
    {
      RetValue = Default;
    }

    return RetValue;
  }


  static inline double SetInvalidToDefault(double value, double Default, double Validator = DEF::Inv_Double)
  {
    double RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline double SetInvalidRangeToDefault(double value, double Default, double Min, double Max)
  {
    double RetValue = value; 

    if ( value > Max )
    {
      RetValue = Default;
    }
    if ( value < Min )
    {
      RetValue = Default;
    }

    return RetValue;
  }


  static inline std::string SetInvalidToDefault(const std::string& value, std::string Default, std::string Validator = DEF::Inv_String)
  {
    std::string RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline CDateTime SetInvalidToDefault(const CDateTime& value, CDateTime Default, CDateTime Validator = CDateTime::InvalidDateTime())
  {
    CDateTime RetValue = value; 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline std::string SetInvalidToDefault(const CDateTime& value, const std::string& Default, CDateTime Validator = CDateTime::InvalidDateTime())
  {
    std::string RetValue = value.asString(); 

    if ( value == Validator )
    {
      RetValue = Default;
    }

    return RetValue;
  }

  static inline long RoundToLong(double value)
  {
    long RetValue = DEF::Inv_Long; 

    if ( value != DEF::Inv_Double )
    {
      if ( value >= 0.0 )
      {
        // 0.5    ... 1.4999 -> 1
        // 1.5000 ... 2.4999 -> 2
        RetValue = long(value + 0.5);
      }
      else if ( value < 0.0 )
      {
        // -0.5    ... -1.4999 -> 1
        // -1.5000 ... -2.4999 -> 2
        RetValue = long(value - 0.5);
      }
    }

    return RetValue;
  }

  static inline std::string ReplaceString(const std::string &stringSearchString, const std::string &stringReplaceString, std::string stringStringToReplace) 
  { 
    std::string::size_type pos = stringStringToReplace.find(stringSearchString, 0); 
    int intLengthSearch = stringSearchString.length(); 
    int intLengthReplacment = stringReplaceString.length(); 

    while(std::string::npos != pos) 
    { 
      stringStringToReplace.replace(pos, intLengthSearch, stringReplaceString); 
      pos = stringStringToReplace.find(stringSearchString, pos + intLengthReplacment); 
    } 

    return stringStringToReplace; 
  } 


  static inline double RoundToDecimals(double value, long Decimals = 0)
  {
    double RetValue = value; 

    if ( value != DEF::Inv_Double )
    {
      if ( Decimals > 0 )
      {
        // 1.4009 round by 2 decimals -> 1.4000
        // 1.4009 round by 3 decimals -> 1.4010

        // 1.4009 round by 3 decimals 
        // 1.4009 * 10pow3 -> 1400,9 + 0.5 -> 1401,4 -> long(1401,4) -> 1401 / 10pow3 -> 1.4010
        long Intermediate = RoundToLong(value * pow(10.,Decimals));
        RetValue = double(Intermediate)/pow(10.,Decimals) ;

      }
      else
      {
        RetValue = RoundToLong(value);
      }
    }

    return RetValue;
  }

  static inline std::string FitToLength(const std::string& Value, long Lenght, const std::string& Sign = " ", bool RightJustified = true)
  {
    if ( (long)Value.size() < Lenght )
    {
      if ( RightJustified )
      {
        return FillLeft(Value,Lenght,Sign);
      }
      else
      {
        return FillRight(Value,Lenght,Sign);
      }
    }
    else if ( (long)Value.size() > Lenght )
    {
      return Truncate(Value,Lenght,RightJustified);
    }
    else
    {
      return Value;
    }
  }

  static inline double LongToDouble(const long Value)
  {
    double ret(DEF::Inv_Double);

    if ( Value == Value //check for NaN
      && DEF::Inv_Long != Value
       )
    {
      ret = (double)Value;
    }//if ( Value == Value ...
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage Message = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorProcessingData(Message,"CDataConversion::LongToDouble","Value is not a number");
    }

    return ret;
  }

  static inline bool LongToBool(const long Value)
  {
    bool RetValue = false;

    if ( Value == 1)
    {
      RetValue = true;
    }

    return RetValue;
  }

};

#endif /* _INC_CDATACONVERSION_439ECDDE03BE_INCLUDED */

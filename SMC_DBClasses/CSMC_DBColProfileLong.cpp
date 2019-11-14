// Copyright (C) 2012 SMS Siemag AG

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_DBData.h"
#include "CSMC_DBColProfileLong.h"

CSMC_DBColProfileLong::~CSMC_DBColProfileLong()
{
}

std::string CSMC_DBColProfileLong::getSQLString()
{
  std::stringstream strValue;

  if ( m_writeNullValue )
  {
    strValue << "NULL" ;
  }
  else
  {
    strValue << m_value ;
  }
	
  return strValue.str();
}

CSMC_DBColProfileLong::CSMC_DBColProfileLong(const std::string& TableName, const std::string  & ColName, long ColSize)
: CSMC_DBColProfile(TableName,SMC_DB_Long,ColName,ColSize)
{
}

 void CSMC_DBColProfileLong::setvalue(long value)
{
  try
  {
    // unfortunaltely we are using -2147483647 but not LONG_MIN
    // we have to check against both here to prohibit insertion of invalid data 
    if ( value == CSMC_DBData::unspecLong || value == LONG_MIN )
    {
      m_writeNullValue = true;
    }
    else
    {
      m_writeNullValue = false;

      if ( m_ColSize >= 0 )
      {
        //Avoid numerical problem with long in C++
        long LimitColsize = min(m_ColSize,9);
        long maximumAllowableVal = (long)pow(10., LimitColsize) - 1;

        if ( abs(value) > maximumAllowableVal )
        {
          std::stringstream Old;
          std::stringstream New;
          Old << value;

          if(value < 0)
            value = maximumAllowableVal*(-1);
          else
            value = maximumAllowableVal;

          New << value;

          if (m_ShowPrecisionTestLogs)
          {
            CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
            sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
            pEventLog->EL_ViolationColPrecision(sMessage,
                                m_TableName.c_str(),
                                m_ColName.c_str(),
                                Old.str().c_str(),
                                New.str().c_str());
          }
        }
      }

	    m_value = value;
    }
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CSMC_DBColProfileLong::setvalue",
                                        "");
  }

	return;
}


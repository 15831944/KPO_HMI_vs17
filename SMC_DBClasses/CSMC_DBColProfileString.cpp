// Copyright (C) 2012 SMS Siemag AG

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_DBData.h"
#include "CSMC_DBColProfileString.h"

CSMC_DBColProfileString::~CSMC_DBColProfileString()
{
}

std::string CSMC_DBColProfileString::getSQLString()
{
  std::stringstream strValue;

  if ( m_writeNullValue )
  {
    strValue << "NULL";
  }
  else
  {
    strValue << "'" << m_value << "'";
  }
	
  return strValue.str();
}

CSMC_DBColProfileString::CSMC_DBColProfileString(const std::string& TableName, const std::string  & ColName, long ColSize)
: CSMC_DBColProfile(TableName,SMC_DB_String,ColName,ColSize)
{
}

 void CSMC_DBColProfileString::setvalue( std::string & value)
{
  try
  { 
    if ( value == CSMC_DBData::unspecString || 
         value == CSMC_DBData::unspecDate.toDBString() )
    {
      m_writeNullValue = true;
    }
    else
    {
      m_writeNullValue = false;

      if ( m_ColSize >= 0 && (long)value.size() > m_ColSize )
      {
        std::string Old = value;
          
        value = value.substr(0,m_ColSize);

        if (m_ShowPrecisionTestLogs)
        {
          CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
          sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
          pEventLog->EL_ViolationColPrecision(sMessage,
                              m_TableName.c_str(),
                              m_ColName.c_str(),
                              Old.c_str(),
                              value.c_str());
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
                                        "CSMC_DBColProfileString::setvalue",
                                        "");
  }

	return;
}


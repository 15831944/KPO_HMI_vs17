// Copyright (C) 2004 SMS Demag AG

#include "cCBS_StdEventLogFrameController.h"
#include <iomanip>
#include "CSMC_DBData.h"
#include "CSMC_DBColProfileDate.h"


//##ModelId=4159297C0149
CSMC_DBColProfileDate::CSMC_DBColProfileDate(const std::string &TableName, const std::string &ColName)
: CSMC_DBColProfile(TableName,SMC_DB_Date,ColName)
{
}

//##ModelId=4159297C0349
CSMC_DBColProfileDate::~CSMC_DBColProfileDate()
{
}

//##ModelId=41594AE20155
DB_CLASSLIB_DATE *CSMC_DBColProfileDate::getDateTime() 
{
  return &m_value;
}

//##ModelId=41594B0503A8
void CSMC_DBColProfileDate::setDateTime(const CDateTime& value)
{
  try
  {
    if ( value == CSMC_DBData::unspecDate )
    {
      m_writeNullValue = true;
    }
    else
    {
      m_writeNullValue = false;
    }

    m_value.year    = (short int)value.getYear();
    m_value.month   = (short int)value.getMonth();
    m_value.day     = (short int)value.getDay();
    m_value.hour    = (short int)value.getHour();
    m_value.minute  = (short int)value.getMinute();
    m_value.second  = (short int)value.getSecond();

    //KLUW: This is special for the ODBC driver. There is an error with the precision.
    m_value.msecond = (int)value.getMilliSecond()*1000000;

  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CSMC_DBColProfileDate::setvalue",
                                        "");
  }

}

std::string CSMC_DBColProfileDate::getSQLString()
{
  // 'YYYY-MM-DD HH24:MI:SS.FF'
  std::stringstream strValue;

  if ( m_writeNullValue )
  {
    strValue << "NULL" ;
  }
  else
  {
    // use to_date to be independent of NLS_DATE_FORMAT
    // TO_DATE('2009-11-24 12:38:15','YYYY-MM-DD HH24:MI:SS')
    strValue.fill('0');
    strValue << "TO_DATE('"
            << std::setw(4) << m_value.year 
            << "-"
            << std::setw(2) << m_value.month
            << "-"
            << std::setw(2) << m_value.day
            << " "
            << std::setw(2) << m_value.hour
            << ":"
            << std::setw(2) << m_value.minute
            << ":"
            << std::setw(2) << m_value.second

	          << "','YYYY-MM-DD HH24:MI:SS')";
  }

  return strValue.str();
}


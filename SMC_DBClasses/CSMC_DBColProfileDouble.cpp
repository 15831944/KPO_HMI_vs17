// Copyright (C) 2012 SMS Siemag AG

#include <float.h>
#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_DBData.h"
#include "CSMC_DBColProfileDouble.h"


CSMC_DBColProfileDouble::~CSMC_DBColProfileDouble()
{
}

std::string CSMC_DBColProfileDouble::getSQLString()
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

CSMC_DBColProfileDouble::CSMC_DBColProfileDouble(const std::string& TableName, const std::string  & ColName, long ColSize)
: CSMC_DBColProfile(TableName,SMC_DB_Double,ColName,ColSize)
{
}

 void CSMC_DBColProfileDouble::setvalue(double value)
{
  try
  {
    // unfortunaltely we are using 2.2250738585072014e-308 but not DBL_MIN
    // we have to check against both here to prohibit insertion of invalid data 
    if ( value == CSMC_DBData::unspecDouble || value == DBL_MIN )
    {
      m_writeNullValue = true;
    }
    else
    {
      m_writeNullValue = false;

      if ( m_ColSize >= 0 )
      {
        //avoid problems with maximum double in C++,e.g NUMBER(20,3)
        long LimitColsize = min(m_ColSize,14);
        double maximumAllowableVal = pow(10., LimitColsize ) - 1.;

        if ( fabs(value) > maximumAllowableVal )
        {
          std::stringstream Old;
          std::stringstream New;
          Old << value;

          if(value < 0)
            value = maximumAllowableVal*(-1.);
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
                                        "CSMC_DBColProfileDouble::setvalue",
                                        "");
  }

	return;
}


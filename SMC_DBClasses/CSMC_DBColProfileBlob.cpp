// Copyright (C) 2012 SMS Siemag AG

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_DBData.h"
#include "CSMC_DBColProfileBlob.h"

CSMC_DBColProfileBlob::~CSMC_DBColProfileBlob()
{
}

std::string CSMC_DBColProfileBlob::getSQLString()
{
  std::stringstream strValue;

  if ( m_writeNullValue )
  {
    strValue << "NULL";
  }
  else
  {
    strValue << "'";

    int CharCount = -1;
    int valueSize = m_value.getSize();

    //char *chr = m_value.getBytes(0, valueSize);

    //strValue.append(reinterpret_cast<const char *>(chr), valueSize);
    while ( true )
    {          
      CharCount++;

      char CharNull = 0;
      if ( CharNull != m_value.getByte(CharCount) )
      {
        strValue << m_value.getByte(CharCount);
      }
      else
      {
        strValue << std::string("0");
      }

      if ( valueSize-1 == CharCount )
        break;
    }

    strValue << "'";
  }

  return strValue.str();
}

CSMC_DBColProfileBlob::CSMC_DBColProfileBlob(const std::string& TableName, const std::string  & ColName, long ColSize)
: CSMC_DBColProfile(TableName,SMC_DB_Blob,ColName,ColSize)
{
}

void CSMC_DBColProfileBlob::setvalue(cCBS_Blob & value)
{
  try
  { 
    if ( value.getSize() == 0 )
    {
      m_writeNullValue = true;
    }
    else
    {
      m_writeNullValue = false;

      m_value = value;
    }
  }
  catch(...)
  {
	  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ExceptionCaught(sMessage,"",
                                        "CSMC_DBColProfileBlob::setvalue",
                                        "");
  }

	return;
}


// Copyright (C) 2012 SMS Demag AG

#include "CSMC_Error.h"


CSMC_Error::~CSMC_Error()
{
}

CSMC_Error::CSMC_Error(cCBS_ODBC_DBError LastError, long OpAcknowledge )
{
  m_MessageText     = LastError.m_MessageText;
  m_NativeErrorCode = LastError.m_NativeErrorCode;
  m_SQLState        = LastError.m_SQLState;
  m_OpAcknowledge   = OpAcknowledge;
}

CSMC_Error::CSMC_Error(const std::string &ErrorMessage, long ErrCode, const std::string &SQL, long OpAcknowledge )
{
  m_MessageText     = ErrorMessage;
  m_NativeErrorCode = ErrCode;
  m_SQLState        = SQL;
  m_OpAcknowledge   = OpAcknowledge;
}

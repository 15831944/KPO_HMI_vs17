// Copyright (C) 2012 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_ERROR_42C3AE100235_INCLUDED
#define _INC_CSMC_ERROR_42C3AE100235_INCLUDED

#include <string>
#include "cCBS_ODBC_DBError.h"

class CSMC_Error 
{
public:
	virtual ~CSMC_Error();

	CSMC_Error(cCBS_ODBC_DBError LastError, long OpAcknowledge );

  CSMC_Error(const std::string &ErrorMessage, long ErrCode, const std::string &SQL, long OpAcknowledge );

  std::string m_MessageText;
  std::string m_SQLState;
  long m_NativeErrorCode;
  long m_OpAcknowledge;

private:


};

#endif /* _INC_CSMC_ERROR_42C3AE100235_INCLUDED */

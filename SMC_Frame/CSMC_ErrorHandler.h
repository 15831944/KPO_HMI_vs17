// Copyright (C) 2012 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSMC_ERRORHANDLER_42C3ADC902B5_INCLUDED
#define _INC_CSMC_ERRORHANDLER_42C3ADC902B5_INCLUDED

#include <string>
#include <vector>

#include "CSMC_Error.h"


class CSMC_ErrorHandler 
{
public:

	virtual ~CSMC_ErrorHandler();

	CSMC_ErrorHandler();

  void setError(CSMC_Error * pSMC_Error);

  void setError(cCBS_ODBC_DBError LastError, long OpAcknowledge );
  void setError(const std::string &ErrorMessage, long ErrCode, const std::string &SQL, long OpAcknowledge );

  std::vector<CSMC_Error*> getErrorList();
  
  bool isError();

  void resetErrorList();

  std::vector<CSMC_Error*> m_ErrorList;

	void log(const std::string& Message, long Level);

};

#endif /* _INC_CSMC_ERRORHANDLER_42C3ADC902B5_INCLUDED */

// Copyright (C) 2012 SMS Demag AG


#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_Error.h"
#include "CSMC_ErrorHandler.h"



CSMC_ErrorHandler::~CSMC_ErrorHandler()
{
}

CSMC_ErrorHandler::CSMC_ErrorHandler()
{
}

void CSMC_ErrorHandler::log(const std::string& Message, long Level)
{
  cCBS_StdLog_Task::getInstance()->log(Message,Level);
}

void CSMC_ErrorHandler::setError(CSMC_Error * pSMC_Error)
{
  m_ErrorList.push_back(pSMC_Error);
}

std::vector<CSMC_Error*> CSMC_ErrorHandler::getErrorList()
{
  return m_ErrorList;
}

bool CSMC_ErrorHandler::isError()
{
  bool RetValue = false;

  if ( m_ErrorList.size() > 0 )
  {
    RetValue = true;
  }

  return RetValue;
}


void CSMC_ErrorHandler::resetErrorList()
{
  std::vector<CSMC_Error*>::iterator it;

  for ( it = m_ErrorList.begin() ; it != m_ErrorList.end() ; ++it )
  {
    delete (*it);
  }

  m_ErrorList.erase(m_ErrorList.begin(),m_ErrorList.end());
}

void CSMC_ErrorHandler::setError(cCBS_ODBC_DBError LastError, long OpAcknowledge )
{
  CSMC_Error * pSMC_Error = new CSMC_Error(LastError, OpAcknowledge);

  setError(pSMC_Error);
}

void CSMC_ErrorHandler::setError(const std::string &ErrorMessage, long ErrCode, const std::string &SQL, long OpAcknowledge )
{
  CSMC_Error * pSMC_Error = new CSMC_Error(ErrorMessage, ErrCode, SQL, OpAcknowledge);

  setError(pSMC_Error);
}


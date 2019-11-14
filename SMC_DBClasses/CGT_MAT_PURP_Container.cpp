// Copyright (C) 2009 SMS Demag AG, Germany 

#include "CGT_MAT_PURP_Container.h"

CGT_MAT_PURP_Container::CGT_MAT_PURP_Container(cCBS_StdConnection *Connection)
{
  try
  {
    if (Connection)
    {
      m_pGT_MAT_PURP = new CGT_MAT_PURP(Connection);
    }
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,
                          "Can not instantiate DB class in case of NULL pointer to connection",
                          "Terminating program!");
      exit(EXIT_FAILURE);
    }

    if (m_pGT_MAT_PURP)
    {
      std::string MatCode;
      long UnitGroupNo = 0;
      std::string PurpCode;

      m_pGT_MAT_PURP->select(CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecString);
      long lRowsGot = m_pGT_MAT_PURP->getLastRow();
      for (long i = 1; i <= lRowsGot; i++)
      {
        MatCode     = m_pGT_MAT_PURP->getMAT_CODE(i);
        UnitGroupNo = m_pGT_MAT_PURP->getUNITGROUPNO(i);
        PurpCode    = m_pGT_MAT_PURP->getPURP_CODE(i);

        m_MatPurpList.insert(std::pair< std::string, std::pair<long,std::string> >(MatCode, std::pair<long,std::string>(UnitGroupNo,PurpCode)));
      }
    }
    delete m_pGT_MAT_PURP; m_pGT_MAT_PURP = 0;
  }
  catch(...)
  {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,
                          "Error during initialization!",
                          "Terminating program!");
      exit(EXIT_FAILURE);
  }
}

CGT_MAT_PURP_Container::~CGT_MAT_PURP_Container()
{
}

//returns a PurpCode from the given list which is available for the given MatCode
std::string CGT_MAT_PURP_Container::getPurpCode(std::string& MatCode, long UnitGroupNo, std::set<std::string> PurpCode)
{
  std::string strPurpCode = DEF::Inv_String;

  std::set<std::string>::iterator itPurpCode;
  std::map< std::string, std::pair<long,std::string> >::iterator itList;

  while ((itPurpCode = PurpCode.begin()) != PurpCode.end())
  {
    strPurpCode = (*itPurpCode);
    while ((itList = m_MatPurpList.find(MatCode)) != m_MatPurpList.end())
    {
      if (strPurpCode == itList->second.second)
      {
        break;
      }
      ++itList;
    }
    ++itPurpCode;
  }

  return strPurpCode;
}

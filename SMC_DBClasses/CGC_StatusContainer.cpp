// Copyright (C) 2007 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "CGC_STATUS.h"
#include "CGC_StatusContainer.h"


CGC_StatusContainer::CGC_StatusContainer(cCBS_StdConnection* Connection)
{
  CGC_STATUS  GC_STATUS   (Connection);

  if ( GC_STATUS.select(CSMC_DBData::unspecLong) )
  {
    std::string Plant;
    StatusDef sStatus;
    for ( long i=1; i <= GC_STATUS.getLastRow(); i++ )
    {
      sStatus.StatusNo     = GC_STATUS.getSTATUSNO(i);
      sStatus.StatusName   = GC_STATUS.getSTATUSNAME(i);
      sStatus.StatusDescr  = GC_STATUS.getSTATUSDESCR(i);
      Plant                = GC_STATUS.getPLANT(i);

      m_StatusTable.insert(std::pair <std::string,StatusDef>(Plant, sStatus));
    }
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage, GC_STATUS.getActStatement().c_str(), "GC_STATUS");
  }
}

CGC_StatusContainer::~CGC_StatusContainer()
{
}

long CGC_StatusContainer::getStatusNo(const std::string& PLANT, std::string STATUSNAME)
{
  long ret = -1;
  std::multimap<const std::string, StatusDef>::const_iterator it;

  for ( it = m_StatusTable.lower_bound(PLANT); it != m_StatusTable.upper_bound(PLANT); ++it )
  {
    if ( STATUSNAME == (it->second).StatusName )
    {
      ret = (it->second).StatusNo;
      break;
    }
  }
  return ret;
}

// Copyright (C) 2004, 2005 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CGC_PLANTGROUP.h"
#include "CGC_Plantgroup_Container.h"


CGC_Plantgroup_Container::CGC_Plantgroup_Container(cCBS_Connection *Connection)
{
  try
  {
    if (Connection)
      m_pCGC_PLANTGROUP = new CGC_PLANTGROUP(Connection);
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,
                          "Can not instantiate DB class (CGC_PLANTGROUP) in case of NULL pointer to connection",
                          "");
    }
    if (m_pCGC_PLANTGROUP)
    {
      UGNo UGDesc;

      m_pCGC_PLANTGROUP->select(CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong);
      long lRowsGot = m_pCGC_PLANTGROUP->getLastRow();
      for (long i = 1; i <= lRowsGot; i++)
      {
        UGDesc.Unit        = m_pCGC_PLANTGROUP->getPLANT(i);
        UGDesc.UnitNo      = m_pCGC_PLANTGROUP->getPLANTNO(i);
        UGDesc.UnitGroupNo = m_pCGC_PLANTGROUP->getUNITGROUPNO(i);

        m_UnitGroupVector.push_back(UGDesc);
      }
      delete m_pCGC_PLANTGROUP;
      m_pCGC_PLANTGROUP = 0;
    }
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

CGC_Plantgroup_Container::CGC_Plantgroup_Container(cCBS_StdConnection *Connection)
{
  try
  {
    if (Connection)
      m_pCGC_PLANTGROUP = new CGC_PLANTGROUP(Connection);
    else
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DatabaseConnectionError(sMessage,
                          "Can not instantiate DB class (CGC_PLANTGROUP) in case of NULL pointer to connection",
                          "");
    }
    if (m_pCGC_PLANTGROUP)
    {
      UGNo UGDesc;

      m_pCGC_PLANTGROUP->select(CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong);
      long lRowsGot = m_pCGC_PLANTGROUP->getLastRow();
      for (long i = 1; i <= lRowsGot; i++)
      {
        UGDesc.Unit        = m_pCGC_PLANTGROUP->getPLANT(i);
        UGDesc.UnitNo      = m_pCGC_PLANTGROUP->getPLANTNO(i);
        UGDesc.UnitGroupNo = m_pCGC_PLANTGROUP->getUNITGROUPNO(i);

        m_UnitGroupVector.push_back(UGDesc);
      }
      delete m_pCGC_PLANTGROUP;
      m_pCGC_PLANTGROUP = 0;
    }
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

CGC_Plantgroup_Container::~CGC_Plantgroup_Container()
{
}

//returns UNITGROUPNO for one Plant type
long CGC_Plantgroup_Container::getUnitGroupNo(const std::string& Plant)
{
  long RetValue = 0;

  std::vector<UGNo>::iterator it;

  for (it=m_UnitGroupVector.begin(); it!=m_UnitGroupVector.end();it++)
  {
    if ( it->Unit == Plant  )
    {
      if ( it->UnitGroupNo < 1000 ) // per definition UNITGROUPNO with highest specilazation starts with 1000
      {
        RetValue = max( it->UnitGroupNo, RetValue );
      }
    }
  }

  return RetValue;
}

//returns UNITGROUPNO for exact one Plant and PlantNo
long CGC_Plantgroup_Container::getUnitGroupNo(const std::string& Plant, long PlantNo)
{
  long RetValue = 0;

  std::vector<UGNo>::iterator it;

  // search for no with highest specialization
  for (it=m_UnitGroupVector.begin(); it!=m_UnitGroupVector.end();it++)
  {
    if ( it->Unit == Plant && it->UnitNo == PlantNo  )
    {
      RetValue = max( it->UnitGroupNo, RetValue );
    }
  }

  return RetValue;
}


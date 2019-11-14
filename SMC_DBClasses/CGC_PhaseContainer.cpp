// Copyright (C) 2009 SMS Siemag AG, Germany 

#include <sstream>
#include "CSMC_EventLogFrameController.h"
#include "CGC_PHASE.h"
#include "CGC_PhaseContainer.h"
#include "cCBS_StdDB_Task.h"


CGC_PhaseContainer::~CGC_PhaseContainer()
{
}

CGC_PhaseContainer::CGC_PhaseContainer(cCBS_Connection * Connection, const std::string & Plant)
{
  if (!Connection)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DatabaseConnectionError(sMessage,
                        "Can not instantiate DB class in case of NULL pointer to connection",
                        "No Phases from GC_PHASE will be read!");
    return;
  }

  if (Plant.empty() || Plant == CSMC_DBData::unspecString )
    cCBS_StdDB_Task::getInstance()->log("CGC_PhaseContainer::CGC_PhaseContainer: Invalid Plant: " + Plant, 0);
  else
  {
    try
    {
      CGC_PHASE GC_PHASE(Connection);

      m_PhaseNameList = GC_PHASE.getPhaseNameList(Plant);

      if(GC_PHASE.selectByPlant(Plant))
      {
        PhaseData pd;
        std::stringstream PhaseKey;
        std::string L2PhaseKey;
        
        long Rows = GC_PHASE.getLastRow();
        for (long i = 1; i <= Rows; i++)
        {
          PhaseKey << GC_PHASE.getPHASENAME(i);
          PhaseKey << "_";
          PhaseKey << GC_PHASE.getPHASENO(i);

          pd.PhaseNo    = GC_PHASE.getPHASENO(i);
          pd.PhaseName  = GC_PHASE.getPHASENAME(i);
          pd.ResPhaseNo = GC_PHASE.getRES_PHASENO(i);
          pd.L1PhaseNo  = GC_PHASE.getL1_PHASE_NO(i);
          pd.Flag       = GC_PHASE.getFLAG(i); 

          m_PhaseDataList.insert(std::pair <std::string, PhaseData>(PhaseKey.str(), pd));

          std::map<std::string,long> map_tmp;
          map_tmp.insert(std::pair<std::string, long>(pd.PhaseName,pd.PhaseNo));
          m_Phases.push_back(map_tmp);

          PhaseKey.str("");
        } // end for loop
      }// end if
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage, "", "GC_PHASE", "Select by Plant failed");
      }
    }// try block
    catch (...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", "CGC_PhaseContainer::getPhaseDataByPlant()", "Unknow Exception");
    }
  }
}

CGC_PhaseContainer::CGC_PhaseContainer(cCBS_StdConnection * Connection, const std::string & Plant)
{
  if (!Connection)
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DatabaseConnectionError(sMessage,
                        "Can not instantiate DB class in case of NULL pointer to connection",
                        "No Phases from GC_PHASE will be read!");
    return;
  }

  if (Plant.empty() || Plant == CSMC_DBData::unspecString )
    cCBS_StdDB_Task::getInstance()->log("CGC_PhaseContainer::CGC_PhaseContainer: Invalid Plant: " + Plant, 0);
  else
  {
    try
    {
      CGC_PHASE GC_PHASE(Connection);

      m_PhaseNameList = GC_PHASE.getPhaseNameList(Plant);

      if(GC_PHASE.selectByPlant(Plant))
      {
        PhaseData pd;
        std::stringstream PhaseKey;
        std::string L2PhaseKey;
        
        long Rows = GC_PHASE.getLastRow();
        for (long i = 1; i <= Rows; i++)
        {
          PhaseKey << GC_PHASE.getPHASENAME(i);
          PhaseKey << "_";
          PhaseKey << GC_PHASE.getPHASENO(i);

          pd.PhaseNo    = GC_PHASE.getPHASENO(i);
          pd.PhaseName  = GC_PHASE.getPHASENAME(i);
          pd.ResPhaseNo = GC_PHASE.getRES_PHASENO(i);
          pd.L1PhaseNo  = GC_PHASE.getL1_PHASE_NO(i);
          pd.Flag       = GC_PHASE.getFLAG(i); 

          m_PhaseDataList.insert(std::pair <std::string, PhaseData>(PhaseKey.str(), pd));

          std::map<std::string,long> map_tmp;
          map_tmp.insert(std::pair<std::string, long>(pd.PhaseName,pd.PhaseNo));
          m_Phases.push_back(map_tmp);

          PhaseKey.str("");
        } // end for loop
      }// end if
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_DBReadError(sMessage, "", "GC_PHASE", "Select by Plant failed");
      }
    }// try block
    catch (...)
    {
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "", "CGC_PhaseContainer::getPhaseDataByPlant()", "Unknow Exception");
    }
  }
}

long CGC_PhaseContainer::getL1PhaseNoByName(const std::string & PhaseName, const long & PhaseNo)
{
  long lL1PhaseNo = CSMC_DBData::unspecLong;
  std::ostringstream L2PhaseName;

  L2PhaseName << PhaseName;
  L2PhaseName << "_";
  L2PhaseName << PhaseNo;
  
  std::map<std::string,long>::iterator it;

  it = m_PhaseNameList.find(L2PhaseName.str());

  if ( it != m_PhaseNameList.end() )
  {
    lL1PhaseNo = it->second;
  }

  if ( lL1PhaseNo == CSMC_DBData::unspecLong )
  {
    std::stringstream Message;

    Message << "Failed to find the L1_PHASE_NO no for Phase :" << PhaseName << " and PhaseNo : " << PhaseNo;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GC_PHASE",Message.str().c_str());
  }

  return lL1PhaseNo;
}

long CGC_PhaseContainer::getResPhaseNo(const std::string & PhaseName, const long & PhaseNo)
{
  long ResPhaseNo = CSMC_DBData::unspecLong;
  std::stringstream L2PhaseKey;

  L2PhaseKey << PhaseName;
  L2PhaseKey << "_";
  L2PhaseKey << PhaseNo;
  
  std::map<std::string, PhaseData>::iterator it;

  it = m_PhaseDataList.find(L2PhaseKey.str());

  if(it != m_PhaseDataList.end())
  {
    ResPhaseNo = it->second.ResPhaseNo;
  }

  if ( ResPhaseNo == CSMC_DBData::unspecLong )
  {
    std::stringstream Message;

    Message << "Failed to find the RES_PHASE_NO no for Phase :" << PhaseName << " and PhaseNo : " << PhaseNo;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GC_PHASE",Message.str().c_str());
  }

  return ResPhaseNo;
}

long CGC_PhaseContainer::getMaxResPhaseNo()
{
  long ResPhaseNo = CSMC_DBData::unspecLong;

  std::map<std::string, PhaseData>::iterator it;

  for ( it = m_PhaseDataList.begin() ; it != m_PhaseDataList.end() ; ++it )
  {
    if ( it->second.Flag == 1 )
    {
      ResPhaseNo = max(ResPhaseNo, it->second.ResPhaseNo) ;
    }
  }

  return ResPhaseNo;
}


// return l2 phase name and phase number by parameter reference using L1 number
bool CGC_PhaseContainer::getPhaseDataByL1PhaseNo(std::string& PhaseName, long& PhaseNo, long lL1PhaseNo)
{
  bool RetValue = false;

  std::map<std::string, PhaseData>::iterator it;

  for (it = m_PhaseDataList.begin(); it != m_PhaseDataList.end(); ++it)
  {
    if (it->second.L1PhaseNo == lL1PhaseNo)
    {
      PhaseName = it->second.PhaseName;
      PhaseNo =  it->second.PhaseNo;

      RetValue = true;
    }
  }

  if ( !RetValue )
  {
    std::stringstream Message;

    Message << "Failed to find the Phase Data no for Phase :" << PhaseName << " PhaseNo : " << PhaseNo << " and L1PhaseNo " << lL1PhaseNo;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GC_PHASE",Message.str().c_str());
  }

  return RetValue;
}

// return l2 phase name and phase number by parameter reference using L1 number
bool CGC_PhaseContainer::getPhaseDataByResPhaseNo(std::string& PhaseName, long& PhaseNo, long ResPhaseNo)
{
  bool RetValue = false;

  std::map<std::string, PhaseData>::iterator it;

  for (it = m_PhaseDataList.begin(); it != m_PhaseDataList.end(); ++it)
  {
    if (it->second.ResPhaseNo == ResPhaseNo)
    {
      PhaseName = it->second.PhaseName;
      PhaseNo =  it->second.PhaseNo;

      RetValue = true;
    }
  }

  if ( !RetValue )
  {
    std::stringstream Message;

    Message << "Failed to find the Phase Data no for Phase :" << PhaseName << " PhaseNo : " << PhaseNo << " and ResPhaseNo " << ResPhaseNo;

    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadError(sMessage,"","GC_PHASE",Message.str().c_str());
  }

  return RetValue;
}

std::list<std::map<std::string,long> > CGC_PhaseContainer::getPhases()
{
  return m_Phases;
}

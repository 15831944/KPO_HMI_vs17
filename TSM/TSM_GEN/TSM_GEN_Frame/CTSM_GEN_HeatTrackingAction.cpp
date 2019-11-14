// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "cCBS_StdDB_Task.h"
#include "CSMC_EventLogFrame.h"
#include "CSMC_EventLogFrameController.h"
#include "CTrackingObject.h"
#include "CEventMessageCtrl.h"
#include "CGC_HEAT_STATUS.h"
#include "CTSM_GEN_Task.h"

#include "CTSM_GEN_HeatTrackingAction.h"

std::string CTSM_GEN_HeatTrackingAction::relatedEventName("TSM_GEN_TRACK_HEAT");

bool CTSM_GEN_HeatTrackingAction::isDataBaseAccess = false;

std::map<std::string,std::string> CTSM_GEN_HeatTrackingAction::PreviousStates;

std::map<std::string,std::string> CTSM_GEN_HeatTrackingAction::StateDescriptions;

void CTSM_GEN_HeatTrackingAction::execute(CTrackingObject* pObjectForAction)
{
  std::map<std::string, std::string>::const_iterator It;

  std::string actHeatState = pObjectForAction->getProcessStatus();
  std::string productID= pObjectForAction->getObjectID();
  std::string msg = CEventMessageCtrl::getEventMessage().getMessage();

  std::string previousHeatState;
  It = CTSM_GEN_HeatTrackingAction::PreviousStates.find(productID);
  if (It == CTSM_GEN_HeatTrackingAction::PreviousStates.end())
  {
    // update the container for the next change only and terminate
    CTSM_GEN_HeatTrackingAction::PreviousStates[productID] = actHeatState;
    CTSM_GEN_HeatTrackingAction::StateDescriptions[actHeatState] = actHeatState;
    return;
  }
  else
    previousHeatState = It->second;

  CTSM_GEN_HeatTrackingAction::PreviousStates[productID] = actHeatState;

  std::string actDesc("\"");
  std::string prevDesc("\"");

  // In case the data base connection was not established we use the state names
  if (CTSM_GEN_HeatTrackingAction::isDataBaseAccess)
  {
    actDesc  += CTSM_GEN_HeatTrackingAction::StateDescriptions[actHeatState];
    prevDesc += CTSM_GEN_HeatTrackingAction::StateDescriptions[previousHeatState];
  }
  else
  {
    actDesc  += actHeatState;
    prevDesc += previousHeatState;
  }
  actDesc += "\"";
  prevDesc += "\"";

	CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_StateTransition(sMessage,"Heat state",prevDesc.c_str(),actDesc.c_str(),productID.c_str(),msg.c_str());

  //std::string ServerDM = "DM_GEN";
  //// Replace DM_LF with specific DM (DM_LF_1,...) if available
  //cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", ServerDM);

  //DM::iDM_Interface_var m_pDM_Interface = CTSM_GEN_Task::getInstance()->getpDM_Interface(ServerDM, DM::PRODUCT);

  //if (m_pDM_Interface) 
  //{
  //  m_pDM_Interface->setString(productID.c_str(), DATA::PhaseAct, actPhase.c_str());
  //}
}

CTSM_GEN_HeatTrackingAction::CTSM_GEN_HeatTrackingAction()
{
  if (CTSM_GEN_HeatTrackingAction::StateDescriptions.empty())
    initialize();
}

void CTSM_GEN_HeatTrackingAction::initialize()
{
  cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();
  cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

  if (pDB_Task)
  {
    try
    {
      std::string DBName;
      std::string DBUser;
      std::string DBPassword;
      
      if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName) &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser)  &&
              pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword) ))
      {
        std::cerr << "Can not read SMC database settings from ini-file" << std::endl;
        exit(EXIT_FAILURE);
      }
       cCBS_Connection*  pConnection = pDB_Task->getConnection(DBName,DBUser, DBPassword);

      if (pConnection)
      {
        pConnection->setAutoCommit(false);
        std::stringstream toLog;
        
		CGC_HEAT_STATUS &GC_HEAT_STATUS = CGC_HEAT_STATUS(pConnection); // FFRA To Be Checked at runtime code: RUN

        if (GC_HEAT_STATUS.select(CSMC_DBData::unspecLong))
        {
          CTSM_GEN_HeatTrackingAction::isDataBaseAccess = true;
          for (int i = 1; i <= GC_HEAT_STATUS.getLastRow(); i++)
          {
            std::string HeatStatus     = GC_HEAT_STATUS.getHEATSTATUS(i);
            std::string HeatStatusDesc = GC_HEAT_STATUS.getHEATSTATUSDESCR(i);
            CTSM_GEN_HeatTrackingAction::StateDescriptions.insert(std::pair<std::string,std::string>(HeatStatus,HeatStatusDesc));
          }
        }
        toLog << "Found " << CTSM_GEN_HeatTrackingAction::StateDescriptions.size() << " heat states in table GC_HEAT_STATUS";

        CTSM_GEN_Task::getInstance()->log(toLog.str(), 2);
      }
    }
    catch (cCBS_DBExc &e)
    {
      cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
        "CTSM_GEN_HeatTrackingAction::initialize", "Reading from GC_HEAT_STATUS"); 
    }
    catch(...) 
    {
      std::cout << "exception caught in CTSM_GEN_HeatTrackingAction::initialize()" << std::endl;
    }

  }
}

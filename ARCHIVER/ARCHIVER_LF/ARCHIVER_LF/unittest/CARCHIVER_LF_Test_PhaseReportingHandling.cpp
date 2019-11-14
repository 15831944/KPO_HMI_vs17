#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_PhaseReportingHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_PhaseReportingHandling::~CARCHIVER_LF_Test_PhaseReportingHandling()
{
}

CARCHIVER_LF_Test_PhaseReportingHandling::CARCHIVER_LF_Test_PhaseReportingHandling(CARCHIVER_Task *Task)
{
  //pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();

  //cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  //cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);

}

//bool CARCHIVER_LF_Test_PhaseReportingHandling::handleLFPhaseReportRDY(CEventMessage& Event)
//{
//  bool RetValue = false;
//  std::stringstream Message;
//  std::string DataKey = Event.getDataKey();
//  std::string RecHeatID = Event.getHeatID();
//  std::string RecTreatID = Event.getTreatID();
//  std::string ProductID = Event.getProductID();
//  std::string RecPlant = DEF_DB_PLANT::LF;
//  bool TestCode = true;
//  std::string MsgRDY(".RDY");
//
//  CPDR_HEAT_DATA_PHASE* m_pPDR_Heat_Data_Phase = 0;
//  CGC_Phase* m_pGC_PHASE = 0;
//
//  long PhaseNo = -1;
//  if (pConnection)
//  {
//    m_pPDR_Heat_Data_Phase = new CPDR_HEAT_DATA_PHASE(pConnection);
//    m_pGC_PHASE = new CGC_Phase(pConnection);
//  }
//
//  setpDM_Interface(ServerTask,DM::PRODUCT);
//  std::string PhaseReportName = m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct);
//  // get the PhaseNo
//  Message << "\nGC_PHASE" << endl;
//  if (m_pGC_PHASE->select(RecPlant, PhaseReportName, CSMC_DBData::unspecLong))
//  {
//    if (!m_pGC_PHASE->isNull("L1_PHASE_NO", 1))
//    {
//      PhaseNo = m_pGC_PHASE->getL1PhaseNo(1);
//      Message << "PhaseNo("<< PhaseReportName <<") = " << PhaseNo << endl;
//    }
//    else
//    {
//      log("ERROR: L1_PHASE_NO is not set for this Phase!",0);
//      TestCode = false;
//    }
//  }
//  else
//  {
//    Message << "INFO: Actual phase is not defined for the actual plant" << endl;
//    TestCode = false;
//  }
//  // get the last Phase from DB
//  if (TestCode)
//  {
//    Message << "\nPDR_HEAT_DATA_PHASE" << endl;
//    if (m_pPDR_Heat_Data_Phase->selectLastPhase(RecPlant, RecHeatID, RecTreatID))
//    {
//      if (Event.getMessage() == (LF_EvMsg::evLFPhaseEndReport + MsgRDY))
//      {
//        if(!m_pPDR_Heat_Data_Phase->isNull("END_TIME", 1))
//		    {
//          Message << "END_TIME(now) = " << m_pPDR_Heat_Data_Phase->getEND_TIME(1) << endl;
//		    }
//		    else
//		    {      
//          Message << "ERROR:\n  END_TIME is not set in PDR_HEAT_DATA_PHASE" << endl;
//			    TestCode = false;
//		    }
//      }
//      if(!m_pPDR_Heat_Data_Phase->isNull("START_TIME", 1))
//		  {
//        Message << "START_TIME(now, except if END_TIME exists) = " << m_pPDR_Heat_Data_Phase->getSTART_TIME(1) << endl;
//		  }
//		  else
//		  {      
//        Message << "ERROR:\n  START_TIME is not set in PDR_HEAT_DATA_PHASE" << endl;
//			  TestCode = false;
//		  }
//      if(!m_pPDR_Heat_Data_Phase->isNull("PHASENO", 1))
//		  {
//        Message << "PHASENO = " << m_pPDR_Heat_Data_Phase->getPHASENO(1) << endl;
//		  }
//		  else
//		  {      
//        Message << "ERROR:\n  PHASENO is not set in PDR_HEAT_DATA_PHASE" << endl;
//			  TestCode = false;
//		  }
//    }
//    else
//    {
//      Message << "ERROR:\n  PDR_HEAT_DATA_PHASE, select for HeatID: " << RecHeatID << ", TreatID: "
//              << RecTreatID << ", PLANT: " << RecPlant << " failed!\n";
//      TestCode = false;
//    }
//  }
//
//  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);
//
//  if (m_pPDR_Heat_Data_Phase) { delete m_pPDR_Heat_Data_Phase; m_pPDR_Heat_Data_Phase = 0;}
//  if (m_pGC_PHASE) { delete m_pGC_PHASE; m_pGC_PHASE = 0;}
//
//  if (TestCode)
//    cCBS_StdLog_Task::getInstance()->log("Test Phase Report use case was successful",1);
//  else
//    cCBS_StdLog_Task::getInstance()->log("Test Phase Report use case failed",1);
//  RetValue = true;
//  return RetValue;
//}
//



void CARCHIVER_LF_Test_PhaseReportingHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_PhaseReportingHandling::deleteDBClasses()
{
}

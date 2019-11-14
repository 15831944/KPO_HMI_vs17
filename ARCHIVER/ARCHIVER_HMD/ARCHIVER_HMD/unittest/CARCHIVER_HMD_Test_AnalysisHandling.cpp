#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_AnalysisHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"


CARCHIVER_HMD_Test_AnalysisHandling::~CARCHIVER_HMD_Test_AnalysisHandling()
{
}

CARCHIVER_HMD_Test_AnalysisHandling::CARCHIVER_HMD_Test_AnalysisHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}
//------------------
bool CARCHIVER_HMD_Test_AnalysisHandling::handleHMDHotMetalSampleTakenRDY(CEventMessage& Event, bool HotMetal)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;

  std::string strLadleNo, strLadleType;
  bool TestCode = true;

  CPD_ANL* m_pPD_Anl = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CGC_Phase* m_pGC_Phase = 0;
  CPD_LADLE_DATA* m_pPD_Ladle_Data = 0;
  CARCHIVER_HMD_Test_Task* m_pTestTask = 0;

  if (pConnection)
  {
    m_pPD_Anl = new CPD_ANL(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pGC_Phase = new CGC_Phase(pConnection);
    m_pPD_Ladle_Data = new CPD_LADLE_DATA(pConnection);
    m_pTestTask = new CARCHIVER_HMD_Test_Task();
  }
  if(m_pPD_Anl)
  {
    seqSampleData SeqSampleData;
    sSampleData sSmplData;

    //SeqComputerModes = *CARCHIVER_HMD_Test_Task::getInstance()->getPlantInterf()->
    //                getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes);

    setpDM_Interface(ServerTask,DM::EVENT);
    SeqSampleData = *m_pDM_Interface->getSampleData(DataKey.c_str(), DATA::SampleData);
    
    CIntfData::getAt(sSmplData, SeqSampleData, 0);

    std::string SampleId = sSmplData.SampleId;

    setpDM_Interface(ServerTask,DM::PRODUCT);
    std::string PhaseReportName = m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct);

    long lPhaseNo = 0;
    long Res_PhaseNo = 0;
    std::stringstream ReblowCounter;
    ReblowCounter << m_pDM_Interface->getString(ProductID.c_str(),DATA::Counter);
    if(ReblowCounter.str() != DEF::Inv_String)
    {
      ReblowCounter >> lPhaseNo;
      //// in this phase we want to have number of each reblow.
      if(lPhaseNo > 0 && PhaseReportName.find("ReblowAfterBlow") != PhaseReportName.npos)
        lPhaseNo --; // decrease because in the GC_PHASE Reblow starts with 0 and end with 4
    }
    Message << "\nGC_PHASE" << endl;
    if (m_pGC_Phase->select(RecPlant, PhaseReportName,lPhaseNo))
    {
      Res_PhaseNo = m_pGC_Phase->getResPhaseNo(1);
      Message << "ResPhaseNo = "<< Res_PhaseNo << endl;
    }
    else
    {
      Message << "ERROR\n  No Phase found for the heat in gc_prase" << endl;
      TestCode = false;
    }

    Message << "\nPD_ANL" << endl;
//  if(m_pPD_Anl->select(RecHeatID, RecTreatID, SampleId, sSmplData.SampleCounter))
//  if(m_pPD_Anl->selectForPhase(RecHeatID, RecTreatID, RecPlant, Res_PhaseNo))
    if(m_pPD_Anl->select(RecHeatID, RecTreatID, RecPlant))
    {
      int row = m_pTestTask->getLastRowFromPD_Anl(RecHeatID, RecTreatID, RecPlant, pConnection);  // get the row with a maximal ANL_COUNTER
      Message << "ANL_COUNTER = " << m_pPD_Anl->getANL_COUNTER(row)
      << "\nHEATID = " << m_pPD_Anl->getHEATID(row)
      << "\nTREATID = " << m_pPD_Anl->getTREATID(row)
      << "\nPRODORDERID = " << m_pPD_Anl->getPRODORDERID(row)
      << "\nPLANT = " << m_pPD_Anl->getPLANT(row)
      << "\nPLANTNO = " << m_pPD_Anl->getPLANTNO(row)
      << "\nRECTIME = " << m_pPD_Anl->getRECTIME(row)
      << "\nELECMOMENT = " << m_pPD_Anl->getELECMOMENT(row)
      << "\nPROBETYPENO = " << m_pPD_Anl->getPROBETYPENO(row)
      << "\nSAMPLEMODENO = " << m_pPD_Anl->getSAMPLEMODENO(row)
      << "\nSTAGENO = " << m_pPD_Anl->getSTAGENO(row)
      << "\nSAMPLEID = " << m_pPD_Anl->getSAMPLEID(row)
      << "\nSMPLNO = " << m_pPD_Anl->getSMPLNO(row)
      << "\nSMPLTIME = " << m_pPD_Anl->getSMPLTIME(row)
      << "\nO2_MOMENT = " << m_pPD_Anl->getO2_MOMENT(row)
      << "\nAR_MOMENT = " << m_pPD_Anl->getAR_MOMENT(row)
      << "\nN2_MOMENT = " << m_pPD_Anl->getN2_MOMENT(row)
      << "\nDURSINCEHEATANNOUNCEMENT = " << m_pPD_Anl->getDURSINCEHEATANNOUNCEMENT(row)
      << "\nDURSINCESTARTOFHEAT = " << m_pPD_Anl->getDURSINCESTARTOFHEAT(row)
      << "\nLADLETYPE = " << m_pPD_Anl->getLADLETYPE(row)
      << "\nLADLENO = "  << m_pPD_Anl->getLADLENO(row) <<endl;

    }
    else
    {
      Message << "ERROR:\n  m_pPD_Anl, select for HeatID: " << RecHeatID << ", TreatID: "
              << RecTreatID << ", PLANT: " << RecPlant << ", failed!" << endl;
      TestCode = false;
    }
  }//if(m_pPD_Anl)

  Message << "\nPD_REPORT" << endl;
  if(m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(HotMetal)
      Message << "STEELPROBESNO = " << m_pPD_Report->getSTEELPROBESNO(1) << endl;
    else
      Message << "SLAGPROBESNO = " << m_pPD_Report->getSLAGPROBESNO(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  PD_Report, select for HeatID: " << RecHeatID << ", TreatID: "
            << RecTreatID << ", PLANT: " << RecPlant << " failed!\n";
    TestCode = false;
  }

  Message << "\nPD_LADLE_DATA" << endl;
  setpDM_Interface(ServerTask,DM::EVENT);
  strLadleType = m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleType);
  strLadleNo = m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleId);
  if(m_pPD_Ladle_Data->select(strLadleType, strLadleNo, "LAST"))
  {
    if(!m_pPD_Ladle_Data->isNull("HEATID", 1))
	  {
      Message << "HEATID = " << m_pPD_Ladle_Data->getHEATID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  HEATID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("TREATID", 1))
	  {
      Message << "TREATID = " << m_pPD_Ladle_Data->getTREATID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  TREATID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("SAMPLEID", 1))
	  {
      Message << "SAMPLEID = " << m_pPD_Ladle_Data->getSAMPLEID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  SAMPLEID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("SAMPLNO", 1))
	  {
      Message << "SAMPLNO = " << m_pPD_Ladle_Data->getSAMPLNO(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  SAMPLENO is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("LASTANLTIME", 1))
	  {
      Message << "LASTANLTIME = " << m_pPD_Ladle_Data->getLASTANLTIME(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  LASTANLTIME is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("ANLSTATUS", 1))
	  {
      Message << "ANLSTATUS = " << m_pPD_Ladle_Data->getANLSTATUS(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  ANLSTATUS is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_Ladle_Data->isNull("PRODORDERID", 1))
	  {
      Message << "PRODORDERID = " << m_pPD_Ladle_Data->getPRODORDERID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  PRODORDERID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
  }
  else
  {
    Message << "ERROR:\n  select * from PD_LADLE_DATA was not successfull" << endl;
    TestCode = false;
  }
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (m_pPD_Anl) { delete m_pPD_Anl; m_pPD_Anl = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pGC_Phase) { delete m_pGC_Phase; m_pGC_Phase = 0;}
  if (m_pPD_Ladle_Data) { delete m_pPD_Ladle_Data; m_pPD_Ladle_Data = 0;}

  if (TestCode)
  {
    if (HotMetal)
      cCBS_StdLog_Task::getInstance()->log("Test HotMetal Sample Taken use case was successful",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Slag Sample Taken use case was successful",1);
  }
  else
  {
    if (HotMetal)
      cCBS_StdLog_Task::getInstance()->log("Test HotMetal Sample Taken use case failed",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Slag Sample Taken use case failed",1);
  }
  RetValue = true;

  return RetValue;
}




void CARCHIVER_HMD_Test_AnalysisHandling::initDBClasses()
{
}

void CARCHIVER_HMD_Test_AnalysisHandling::deleteDBClasses()
{
}

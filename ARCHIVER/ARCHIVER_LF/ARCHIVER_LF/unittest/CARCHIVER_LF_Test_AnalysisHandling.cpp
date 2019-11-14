#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_AnalysisHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_AnalysisHandling::~CARCHIVER_LF_Test_AnalysisHandling()
{
}

CARCHIVER_LF_Test_AnalysisHandling::CARCHIVER_LF_Test_AnalysisHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}
//Dipesh------------
bool CARCHIVER_LF_Test_AnalysisHandling::handleLFSampleTakenRDY(CEventMessage& Event, bool Steel)//Dipesh------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::LF;
 
  std::string strLadleNo, strLadleType;
  bool TestCode = true;

  CPD_ANL* m_pPD_Anl = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CGC_Phase* m_pGC_PHASE = 0;
  CPD_LADLE_DATA* m_pPD_LADLE_Data = 0;
  CARCHIVER_LF_Test_Task* m_pTestTask = 0;

  if (pConnection)
  {
    m_pPD_Anl = new CPD_ANL(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pGC_PHASE = new CGC_Phase(pConnection);
    m_pPD_LADLE_Data = new CPD_LADLE_DATA(pConnection);
    m_pTestTask = new CARCHIVER_LF_Test_Task();
  }
  if(m_pPD_Anl)
  {
    seqSampleData SeqSampleData;
    sSampleData sSmplData;

    //SeqComputerModes = *CARCHIVER_LF_Test_Task::getInstance()->getPlantInterf()->
    //                getComputerModes(DEF_PLANT::Furnace,DATA::ComputerModes);

    setpDM_Interface(ServerTask,DM::EVENT);
    SeqSampleData = CIntfData::ToCORBAType(m_pDM_Interface->getSampleData(DataKey.c_str(), DATA::SampleData));
    
    CIntfData::getAt(sSmplData, SeqSampleData, 0);

    std::string SampleId = sSmplData.SampleId;

    setpDM_Interface(ServerTask,DM::PRODUCT);
    std::string PhaseReportName = m_pDM_Interface->getString(RecProductID.c_str(),DATA::PhaseAct);

    long lPhaseNo = 0;
    long Res_PhaseNo = 0;
    std::stringstream ReblowCounter;
    ReblowCounter << m_pDM_Interface->getString(RecProductID.c_str(),DATA::Counter);
    if(ReblowCounter.str() != DEF::Inv_String)
    {
      ReblowCounter >> lPhaseNo;
      //// in this phase we want to have number of each reblow.
      if(lPhaseNo > 0 && PhaseReportName.find("ReblowAfterBlow") != PhaseReportName.npos)
        lPhaseNo --; // decrease because in the GC_PHASE Reblow starts with 0 and end with 4
    }
    Message << "\nGC_PHASE" << endl;
    if (m_pGC_PHASE->select(RecPlant, PhaseReportName,lPhaseNo))
    {
      Res_PhaseNo = m_pGC_PHASE->getResPhaseNo(1);
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
      << "\nLADLENO = "  << m_pPD_Anl->getLADLENO(row);

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
    if(Steel)
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
  if(m_pPD_LADLE_Data->select(strLadleType, strLadleNo, "LAST"))
  {
    if(!m_pPD_LADLE_Data->isNull("HEATID", 1))
	  {
      Message << "HEATID = " << m_pPD_LADLE_Data->getHEATID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  HEATID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("TREATID", 1))
	  {
      Message << "TREATID = " << m_pPD_LADLE_Data->getTREATID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  TREATID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("SAMPLEID", 1))
	  {
      Message << "SAMPLEID = " << m_pPD_LADLE_Data->getSAMPLEID(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  SAMPLEID is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("SAMPLNO", 1))
	  {
      Message << "SAMPLNO = " << m_pPD_LADLE_Data->getSAMPLNO(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  SAMPLENO is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("LASTANLTIME", 1))
	  {
      Message << "LASTANLTIME = " << m_pPD_LADLE_Data->getLASTANLTIME(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  LASTANLTIME is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("ANLSTATUS", 1))
	  {
      Message << "ANLSTATUS = " << m_pPD_LADLE_Data->getANLSTATUS(1)<< endl;
	  }
    else
    {
      Message << "ERROR:\n  ANLSTATUS is not set in PD_LADLE_DATA" << endl;
  	  TestCode = false;      
    }
    if(!m_pPD_LADLE_Data->isNull("PRODORDERID", 1))
	  {
      Message << "PRODORDERID = " << m_pPD_LADLE_Data->getPRODORDERID(1)<< endl;
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
  if (m_pGC_PHASE) { delete m_pGC_PHASE; m_pGC_PHASE = 0;}
  if (m_pPD_LADLE_Data) { delete m_pPD_LADLE_Data; m_pPD_LADLE_Data = 0;}

  if (TestCode)
  {
    if (Steel)
      cCBS_StdLog_Task::getInstance()->log("Test Steel Sample Taken use case was successful",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Slag Sample Taken use case was successful",1);
  }
  else
  {
    if (Steel)
      cCBS_StdLog_Task::getInstance()->log("Test Steel Sample Taken use case failed",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Slag Sample Taken use case failed",1);
  }
  RetValue = true;

  return RetValue;
}

//.... Done By PAMA....
bool CARCHIVER_LF_Test_AnalysisHandling::handleLFAnalysisReceivedRDY(CEventMessage& Event, bool Steel)      
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();

  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;


  long SampleCounter;
  std::string SampleId;
  
  CPD_ANL_ENTRY*  m_pPD_Anl_Entry = 0;
  CPD_ANL* m_pPD_Anl = 0;
  CGC_Phase* m_pGC_PHASE = 0;

  if (pConnection)
  {
     m_pPD_Anl = new CPD_ANL(pConnection);
     m_pGC_PHASE = new CGC_Phase(pConnection);
     m_pPD_Anl_Entry = new CPD_ANL_ENTRY(pConnection);
  }

  seqAnalysisData SeqAnalysisData;
  sAnalysisData AnalysisStruct;
  seqGasData SeqGasData;
  CDateTime SampleTime;

  setpDM_Interface(Event.getSender(),DM::EVENT);
  if (Steel)
  {
    SeqAnalysisData = *m_pDM_Interface->getAnalysisData(DataKey.c_str(),DATA::SteelMeasAnalysis);
  }
  else
  {
    SeqAnalysisData = *m_pDM_Interface->getAnalysisData(DataKey.c_str(),DATA::SlagMeasAnalysis);
  }

   setpDM_Interface(Event.getSender(),DM::PRODUCT);
   double ElecCons = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::ElecCons);
   SampleId = AnalysisStruct.SampleData.SampleId;
   SampleCounter = AnalysisStruct.SampleData.SampleCounter;

   Message << "\nPD_ANL" << endl;
   if (m_pPD_Anl->select(RecHeatID, RecTreatID, SampleId, SampleCounter))
   {
      int row = 1;
      Message << "ANL_COUNTER: " << m_pPD_Anl->getANL_COUNTER(row)
      << "\nHEATID: " << m_pPD_Anl->getHEATID(row)
      << "\nTREATID: " << m_pPD_Anl->getTREATID(row)
      << "\nPRODORDERID: " << m_pPD_Anl->getPRODORDERID(row)
      << "\nPLANT: " << m_pPD_Anl->getPLANT(row)
      << "\nPLANTNO: " << m_pPD_Anl->getPLANTNO(row)
      << "\nRECTIME: " << m_pPD_Anl->getRECTIME(row)
      << "\nELECMOMENT: " << m_pPD_Anl->getELECMOMENT(row)
      << "\nPROBETYPENO: " << m_pPD_Anl->getPROBETYPENO(row)
      << "\nSTAGENO: " << m_pPD_Anl->getSTAGENO(row)
      << "\nSAMPLEID: " << m_pPD_Anl->getSAMPLEID(row)
      << "\nSMPLNO: " << m_pPD_Anl->getSMPLNO(row)
      << "\nSMPLTIME: " << m_pPD_Anl->getSMPLTIME(row)
      << "\nO2_MOMENT: " << m_pPD_Anl->getO2_MOMENT(row)
      << "\nAR_MOMENT: " << m_pPD_Anl->getAR_MOMENT(row)
      << "\nN2_MOMENT: " << m_pPD_Anl->getN2_MOMENT(row)
      << "\nDURSINCEHEATANNOUNCEMENT: " << m_pPD_Anl->getDURSINCEHEATANNOUNCEMENT(row)
      << "\nDURSINCESTARTOFHEAT: " << m_pPD_Anl->getDURSINCESTARTOFHEAT(row)
      << "\nLADLETYPE: " << m_pPD_Anl->getLADLETYPE(row)
      << "\nLADLENO: "  << m_pPD_Anl->getLADLENO(row)
      << "\nRECTIMELAB: "  << m_pPD_Anl->getRECTIMELAB(row)
      << "\nSMPLUSEABLE: "  << m_pPD_Anl->getSMPLUSEABLE(row) << endl;
   }
   else
  {
    Message << "ERROR:\n  Selection From PD_ANL failed!\n";
    TestCode = false;
  }

  long lAnlCounter = m_pPD_Anl->getANL_COUNTER(1);
  Message << "\nPD_ANL_ENTRY" << endl;
  if(m_pPD_Anl_Entry->select(lAnlCounter))
  {
    for(int i = 1; i <= m_pPD_Anl_Entry->getLastRow(); i++)
    {
      Message << "ENAME: " << m_pPD_Anl_Entry->getENAME(i)
              << ",\tANL: " << m_pPD_Anl_Entry->getANL(i) << endl;
    }
  }
  else
  {
    Message << "ERROR:\n  PD_Anl_Entry, select for m_pPD_Anl->getANL_COUNTER(1): " << lAnlCounter << " failed!\n";
    TestCode = false;
  }

  if (m_pPD_Anl) { delete m_pPD_Anl; m_pPD_Anl = 0;}
  if (m_pPD_Anl_Entry) { delete m_pPD_Anl_Entry; m_pPD_Anl_Entry = 0;}
  if (m_pGC_PHASE) { delete m_pGC_PHASE; m_pGC_PHASE = 0;}

  if (TestCode)
  {
    cCBS_StdLog_Task::getInstance()->log("Test Steel Analysis Received use case was successful",1);
  }
  else
  {
    cCBS_StdLog_Task::getInstance()->log("Test Steel Analysis Received use case failed",1);
  }
  RetValue = true;

  return RetValue;
}

void CARCHIVER_LF_Test_AnalysisHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_AnalysisHandling::deleteDBClasses()
{
}

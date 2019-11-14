#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"
#include "CStirringDataHandler.h"
#include "DEF_GC_PROBETYPE.h"

CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::~CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling()
{
}

CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}

bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDTopLanceBlowingStartRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  //Initialise database objects
  CPDR_HEAT_DATA* m_pPDR_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDR_Heat_Data = new CPDR_HEAT_DATA(pConnection);
  }

  Message << "\nPDR_HEAT_DATA" << endl;
  if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
  {
    // Set BLOWINGSTARTTIME in PDR_HEAT_DATA if it's NULL
    //
    if(!m_pPDR_Heat_Data->isNull("BLOWINGSTARTTIME",1))
    {
      Message << "BLOWINGSTARTTIME(the time when it is set) = " << m_pPDR_Heat_Data->getBLOWINGSTARTTIME(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  BLOWINGSTARTTIME is not set in PDR_HEAT_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PDR_HEAT_DATA was not successfull"<<endl;
    TestCode = false;
  }

  if (m_pPDR_Heat_Data) { delete m_pPDR_Heat_Data; m_pPDR_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Blowing Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Blowing Start use case failed",1);
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDTopLanceBlowingStopRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  //Initialise database objects
  CPDR_HEAT_DATA* m_pPDR_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDR_Heat_Data = new CPDR_HEAT_DATA(pConnection);
  }

  Message << "\nPDR_HEAT_DATA" << endl;
  if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
  {
    //Read TopLanceAmount from Tracker
    //
    seqGasData *pSeqGasData = 0;
    setpDM_Interface(ServerTask,DM::PRODUCT);
    pSeqGasData = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::TopLanceAmount);
    sGasData sData;
    sData.GasValue = -1;

    CIntfData::getAt(sData, pSeqGasData, 0);

    //Read BlowDur from Tracker

    // to test if the three values has been updated
    //
    if(!m_pPDR_Heat_Data->isNull("TOTAL_O2_CONS",1))
      Message << "TOTAL_O2_CONS(" << sData.GasValue << ") = " << m_pPDR_Heat_Data->getTOTAL_O2_CONS(1) << endl;
    else
    {
      Message << "ERROR:\n  TOTAL_O2_CONS is not set in PDR_HEAT_DATA"<<endl;
      TestCode = false;
    }

    if(!m_pPDR_Heat_Data->isNull("BLOWING_DUR",1))
    {
      seqGasData *pSeqGasData = 0;
      pSeqGasData = m_pDM_Interface->getGasData(RecProductID.c_str(),DATA::BlowDur);
      CIntfData::getAt(sData, pSeqGasData, 0);
      double BlowDur = sData.GasValue;
      Message << "BLOWING_DUR(" << BlowDur << ") = " << m_pPDR_Heat_Data->getBLOWING_DUR(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  BLOWING_DUR is not set in PDR_HEAT_DATA"<<endl;
      TestCode = false;
    }

    if(!m_pPDR_Heat_Data->isNull("BLOWINGENDTIME",1))
      Message << "BLOWINGENDTIME(now) = " << m_pPDR_Heat_Data->getBLOWINGENDTIME(1) << endl;
    else
    {
      Message << "ERROR:\n  BLOWINGENDTIME is not set in PDR_HEAT_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    std::string SearchKey = RecHeatID;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PDR_Heat_Data");
  }


  if (m_pPDR_Heat_Data) { delete m_pPDR_Heat_Data; m_pPDR_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Blowing Stop use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Blowing Stop use case failed",1);
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDTotalBlowingEndRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::CON;
  bool TestCode = true;

  //Initialise database objects
  CPDB_HEAT_DATA* m_pPDB_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDB_Heat_Data = new CPDB_HEAT_DATA(pConnection);
  }
  //.........

  if (m_pPDB_Heat_Data) { delete m_pPDB_Heat_Data; m_pPDB_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDStirringStartEndRDY(CEventMessage& Event, long Start)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  //Initialise database objects
  CPDR_STIRR_DATA* m_pPDR_Stirr_Data = 0;
  CPDR_HEAT_DATA* m_pPDR_Heat_Data = 0;
  CPDR_STIRR_BYPASS_DATA* m_pPDR_Stirr_Bypass_Data = 0;

  if (pConnection)
  {
    m_pPDR_Stirr_Data = new CPDR_STIRR_DATA(pConnection);
    m_pPDR_Heat_Data = new CPDR_HEAT_DATA(pConnection);
    m_pPDR_Stirr_Bypass_Data = new CPDR_STIRR_BYPASS_DATA(pConnection);

  }
  if(Start == 1) // Stirring START
  {
    setpDM_Interface(ServerTask,DM::PRODUCT);
    std::string CarID = m_pDM_Interface->getString(ProductID.c_str(), DATA::LadleTransferCarId);

    setpDM_Interface(ServerTask,DM::PLANT);
    long PlugNo = m_pDM_Interface->getLong(CarID.c_str(), DATA::LadlePlugNo);
    
    std::vector<long> PlugList;
    if (PlugNo == DEF_PLUG_NO::All)
    {
      PlugList.push_back(1);
      PlugList.push_back(2);
    }

    Message << "\nPDR_STIRR_DATA" << endl;
    if(m_pPDR_Stirr_Data->selectActual(RecHeatID, RecTreatID, RecPlant, CSMC_DBData::unspecLong))
    {
      long lRows = m_pPDR_Stirr_Data->getLastRow();
      
      for( int i = 1; i <= lRows; ++i)
      {
        Message << "PLUGNO("<<i<<") = " << m_pPDR_Stirr_Data->getPLUGNO(i) << endl;
        Message << "STIRR_START_PLUG("<<i<<") = " << m_pPDR_Stirr_Data->getSTIRR_START_PLUG(i) << endl;
      }
    }
    else
    {
      Message << "ERROR:\n  No any entry for this HeatID, TreatID & Plant in PDR_STIRR_DATA" << endl;
      TestCode = false;
    }
    Message << "\nPDR_HEAT_DATA" << endl;
    if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
    {
      if (!m_pPDR_Heat_Data->isNull("STIRRSTARTTIME", 1))
      {
        Message << "STIRRSTARTTIME = " << m_pPDR_Heat_Data->getSTIRRSTARTTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRRSTARTTIME is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_START_PLUG1", 1))
      {
        Message << "STIRR_START_PLUG1 = " << m_pPDR_Heat_Data->getSTIRR_START_PLUG1(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_START_PLUG1 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_START_PLUG2", 1))
      {
        Message << "STIRR_START_PLUG2 = " << m_pPDR_Heat_Data->getSTIRR_START_PLUG2(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_START_PLUG2 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  No any entry for this HeatID, TreatID & Plant in PDR_HEAT_DATA" << endl;
      TestCode = false;
    }
  } // Stirring START
  else if(Start == 2) // Stirring END
  {
    Message << "\nPDR_STIRR_DATA";
    if(m_pPDR_Stirr_Data->selectActual(RecHeatID, RecTreatID, RecPlant, CSMC_DBData::unspecLong))
    {
      long lRows = m_pPDR_Stirr_Data->getLastRow();
      for( int i = 1; i <= lRows; ++i)
      {
        Message << "\n" << i << ". Plug Number" << endl;
        Message << "PLUGNO = " << m_pPDR_Stirr_Data->getPLUGNO(i) << endl;
        Message << "STIRR_AR_CONS_PLUG = " << m_pPDR_Stirr_Data->getSTIRR_AR_CONS_PLUG(i) << endl;
        Message << "STIRR_AR_DUR = " << m_pPDR_Stirr_Data->getSTIRR_AR_DUR(i) << endl;
        Message << "STIRR_N2_CONS_PLUG = " << m_pPDR_Stirr_Data->getSTIRR_N2_CONS_PLUG(i) << endl;
        Message << "STIRR_N2_DUR = " << m_pPDR_Stirr_Data->getSTIRR_N2_DUR(i) << endl;
      }
    }

    Message << "\nPDR_STIRR_BYPASS_DATA";
    if(m_pPDR_Stirr_Bypass_Data->selectActual(RecHeatID, RecTreatID, RecPlant, CSMC_DBData::unspecLong))
    {
      long lRows = m_pPDR_Stirr_Bypass_Data->getLastRow();
      for( int i = 1; i <= lRows; ++i)
      {
        Message << "\n" << i << ". Plug Number" << endl;
        if(!m_pPDR_Stirr_Bypass_Data->isNull("PLUGNO", i))
		    {
          Message << "PLUGNO = " << m_pPDR_Stirr_Bypass_Data->getPLUGNO(i) << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  PLUGNO is not set in PDR_STIRR_BYPASS_DATA" << endl;
			    TestCode = false;
		    }
        if(!m_pPDR_Stirr_Bypass_Data->isNull("STIRR_BYPASS_START_PLUG", i))
		    {
          Message << "STIRR_BYPASS_START_PLUG = " << m_pPDR_Stirr_Bypass_Data->getSTIRR_BYPASS_START_PLUG(i) << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  STIRR_BYPASS_START_PLUG is not set in PDR_STIRR_BYPASS_DATA" << endl;
			    TestCode = false;
		    }
        if(!m_pPDR_Stirr_Bypass_Data->isNull("STIRR_BYPASS_END_PLUG", i))
		    {
          Message << "STIRR_BYPASS_END_PLUG = " << m_pPDR_Stirr_Bypass_Data->getSTIRR_BYPASS_END_PLUG(i) << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  STIRR_BYPASS_END_PLUG is not set in PDR_STIRR_BYPASS_DATA" << endl;
			    TestCode = false;
		    }
        if(!m_pPDR_Stirr_Bypass_Data->isNull("STIRR_AR_CONS_PLUG", i))
		    {
          Message << "STIRR_AR_CONS_PLUG = " << m_pPDR_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(i) << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not set in PDR_STIRR_BYPASS_DATA" << endl;
			    TestCode = false;
		    }
        if(!m_pPDR_Stirr_Bypass_Data->isNull("STIRR_N2_CONS_PLUG", i))
		    {
          Message << "STIRR_N2_CONS_PLUG = " << m_pPDR_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(i) << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not set in PDR_STIRR_BYPASS_DATA" << endl;
			    TestCode = false;
		    }
      }
    }
    else
    {
      Message << "ERROR:\n  The selection from PDR_STIRR_BYPASS_DATA was not successfull"<<endl;
      TestCode = false;
    }

    Message << "\nPDR_HEAT_DATA" << endl;
    if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
    {
      if (!m_pPDR_Heat_Data->isNull("STIRRENDTIME", 1))
      {
        Message << "STIRRENDTIME = " << m_pPDR_Heat_Data->getSTIRRENDTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRRENDTIME is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_GAS_AR_CONS", 1))
      {
        Message << "STIRR_GAS_AR_CONS = " << m_pPDR_Heat_Data->getSTIRR_GAS_AR_CONS(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_GAS_AR_CONS is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_AR_CONS_PLUG1", 1))
      {
        Message << "STIRR_AR_CONS_PLUG1 = " << m_pPDR_Heat_Data->getSTIRR_AR_CONS_PLUG1(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG1 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_AR_CONS_PLUG2", 1))
      {
        Message << "STIRR_AR_CONS_PLUG2 = " << m_pPDR_Heat_Data->getSTIRR_AR_CONS_PLUG2(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG2 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_AR_DUR", 1))
      {
        Message << "STIRR_AR_DUR = " << m_pPDR_Heat_Data->getSTIRR_AR_DUR(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_DUR is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_GAS_N2_CONS", 1))
      {
        Message << "STIRR_GAS_N2_CONS = " << m_pPDR_Heat_Data->getSTIRR_GAS_N2_CONS(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_GAS_N2_CONS is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_N2_CONS_PLUG1", 1))
      {
        Message << "STIRR_N2_CONS_PLUG1 = " << m_pPDR_Heat_Data->getSTIRR_N2_CONS_PLUG1(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG1 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_N2_CONS_PLUG2", 1))
      {
        Message << "STIRR_N2_CONS_PLUG2 = " << m_pPDR_Heat_Data->getSTIRR_AR_CONS_PLUG2(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG2 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_END_PLUG1", 1))
      {
        Message << "STIRR_END_PLUG1 = " << m_pPDR_Heat_Data->getSTIRR_END_PLUG1(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_END_PLUG1 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_END_PLUG2", 1))
      {
        Message << "STIRR_END_PLUG2 = " << m_pPDR_Heat_Data->getSTIRR_END_PLUG2(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_END_PLUG2 is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("STIRR_N2_DUR", 1))
      {
        Message << "STIRR_N2_DUR = " << m_pPDR_Heat_Data->getSTIRR_N2_DUR(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_DUR is not set in PDR_HEAT_DATA" << endl;
        TestCode = false;
      }

    }
    else
    {
      Message << "ERROR:\n  No any entry for this HeatID, TreatID & Plant in PDR_HEAT_DATA" << endl;
      TestCode = false;
    }
  }

  if (m_pPDR_Stirr_Data) { delete m_pPDR_Stirr_Data; m_pPDR_Stirr_Data = 0;}
  if (m_pPDR_Heat_Data) { delete m_pPDR_Heat_Data; m_pPDR_Heat_Data = 0;}
  if (m_pPDR_Stirr_Bypass_Data) { delete m_pPDR_Stirr_Bypass_Data; m_pPDR_Stirr_Bypass_Data = 0;}
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
  {
    if (Start == 1)
      cCBS_StdLog_Task::getInstance()->log("Test Stirring Start use case was successful",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Stirring Stop use case was successful",1);
  }
  else
  {
    if (Start == 1)
      cCBS_StdLog_Task::getInstance()->log("Test Stirring Start use case failed",1);
    else
      cCBS_StdLog_Task::getInstance()->log("Test Stirring Stop use case failed",1);
  }
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDCyclicMeasurementRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;
  sGasData GasData;

  long PredLength = 0;
  //Initialise database objects
  CPDH_CYCL_MEAS_DATA* m_pPDH_Cycl_Meas_Data = 0;

  if (pConnection)
  {
    m_pPDH_Cycl_Meas_Data = new CPDH_CYCL_MEAS_DATA(pConnection);
  }


  CDateTime RevTime;
  Message << "\nPDH_CYCL_MEAS_DATA" << endl;
 
 if( m_pPDH_Cycl_Meas_Data->selectMax(RecHeatID, RecTreatID, RecPlant, "REVTIME") )
  {
    RevTime = m_pPDH_Cycl_Meas_Data->getREVTIME(1);
  }
  else
  {
    Message << "ERROR:\n  Failed to select the latest REVTIME from PDH_CYCL_MEAS_DATA."<<endl;
    TestCode = false;
  }
  if( m_pPDH_Cycl_Meas_Data->select(RecHeatID, RecTreatID, RecPlant, RevTime) )
  {

  if(!m_pPDH_Cycl_Meas_Data->isNull("TREATTYPE",1))
  {
    Message << "TREATTYPE = " <<  m_pPDH_Cycl_Meas_Data->getTREATTYPE(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  TREATTYPE is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("DURSINCEHEATANNOUNCE",1))
  {
    Message << "DURSINCEHEATANNOUNCE = " <<  m_pPDH_Cycl_Meas_Data->getDURSINCEHEATANNOUNCE(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  DURSINCEHEATANNOUNCE is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("DURSINCESTARTOFHEAT",1))
  {
    Message << "DURSINCESTARTOFHEAT = " <<  m_pPDH_Cycl_Meas_Data->getDURSINCESTARTOFHEAT(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  DURSINCESTARTOFHEAT is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_FLOW_LIME",1))
  {
    Message << "POWDER_FLOW_LIME = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_FLOW_LIME(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_FLOW_LIME is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_FLOW_MAGNES",1))
  {
    Message << "POWDER_FLOW_MAGNES = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_FLOW_MAGNES(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_FLOW_MAGNES is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_FLOW_CARB",1))
  {
    Message << "POWDER_FLOW_CARB = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_FLOW_CARB(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_FLOW_CARB is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_CONS_LIME",1))
  {
    Message << "POWDER_CONS_LIME = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_CONS_LIME(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_CONS_LIME is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_CONS_MAGNES",1))
  {
    Message << "POWDER_CONS_MAGNES = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_CONS_MAGNES(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_CONS_MAGNES is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("POWDER_CONS_CARB",1))
  {
    Message << "POWDER_CONS_CARB = " <<  m_pPDH_Cycl_Meas_Data->getPOWDER_CONS_CARB(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  POWDER_CONS_CARB is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("MAT_CODE_CARB",1))
  {
    Message << "MAT_CODE_CARB = " <<  m_pPDH_Cycl_Meas_Data->getMAT_CODE_CARB(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  MAT_CODE_CARB is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("MAT_CODE_MAGN",1))
  {
    Message << "MAT_CODE_MAGN = " <<  m_pPDH_Cycl_Meas_Data->getMAT_CODE_MAGN(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  MAT_CODE_MAGN is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  if(!m_pPDH_Cycl_Meas_Data->isNull("MAT_CODE_LIME",1))
  {
    Message << "MAT_CODE_LIME = " <<  m_pPDH_Cycl_Meas_Data->getMAT_CODE_LIME(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  MAT_CODE_LIME is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
   if(!m_pPDH_Cycl_Meas_Data->isNull("LANCE_POSITION",1))
  {
    Message << "LANCE_POSITION = " <<  m_pPDH_Cycl_Meas_Data->getLANCE_POSITION(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  LANCE_POSITION is not set in the table PDH_Cycl_Meas_Data "<<endl;
    TestCode = false;
  }
  }

  else
  {
    Message << "INFO:\n  Failed to select data from PDH_CYCL_MEAS_DATA."<<endl;
  }
  if (m_pPDH_Cycl_Meas_Data) { delete m_pPDH_Cycl_Meas_Data; m_pPDH_Cycl_Meas_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Cyclic Measurement use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Cyclic Measurement use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDVacuumStartEndRDY(CEventMessage& Event, long Start)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  //Initialise database objects
  CPDR_HEAT_DATA* m_pPDR_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDR_Heat_Data = new CPDR_HEAT_DATA(pConnection);
  }


  if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
  {
    if (Start == 1)
    {
      Message << "\nPDR_HEAT_DATA"<< endl;
      if (!m_pPDR_Heat_Data->isNull("VACUUMSTARTTIME", 1))
      {
        Message << "VACUUMSTARTTIME(now) = " << m_pPDR_Heat_Data->getVACUUMSTARTTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  VACUUMSTARTTIME is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }
    }
    else
    {
      seqGasData *pSeqGasData = 0;

      setpDM_Interface(ServerTask,DM::PRODUCT);
      double SteamCon = m_pDM_Interface->getDouble(ProductID.c_str(),DATA::SteamConsumption);
      double VacuumDur= m_pDM_Interface->getDouble(ProductID.c_str(),DATA::VacuumDuration);
      Message << "\nPDR_HEAT_DATA" << endl;
      if(!m_pPDR_Heat_Data->isNull("STEAM_CONS",1))
      {
        if( (SteamCon - m_pPDR_Heat_Data->getSTEAM_CONS(1)) < 0.01 )
        {
          Message << "STEAM_CONS(" << SteamCon << ") = " << m_pPDR_Heat_Data->getSTEAM_CONS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STEAM_CONS is not equal to " << SteamCon << ". It is " << m_pPDR_Heat_Data->getSTEAM_CONS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  STEAM_CONS is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }


      if(!m_pPDR_Heat_Data->isNull("VACUUM_DUR",1))
      {
        if( (VacuumDur - m_pPDR_Heat_Data->getVACUUM_DUR(1)) < 0.01 )
        {
          Message << "VACUUM_DUR(" << VacuumDur << ") = " << m_pPDR_Heat_Data->getVACUUM_DUR(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  VACUUM_DUR is not equal to " << VacuumDur << ". It is " << m_pPDR_Heat_Data->getVACUUM_DUR(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  VACUUM_DUR is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }


      if (!m_pPDR_Heat_Data->isNull("VACUUMENDTIME", 1))
      {
        Message << "VACUUMENDTIME(now) = " << m_pPDR_Heat_Data->getVACUUMENDTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  VACUUMENDTIME is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }
    }
  }
  else
  {
    Message << "ERROR:\n  Failed to select data from PDR_HEAT_DATA"<<endl;
    TestCode = false;
  }


  if (m_pPDR_Heat_Data) { delete m_pPDR_Heat_Data; m_pPDR_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  Message.str("");
  
  Message << "Test ";
  switch(Start)
  {
  case 0:
    Message << "Vacuum End";
    break;
  case 1:
    Message << "Vacuum Start";
    break;
  case 2:
    Message << "Vacuum Interrupt";
    break;
  }
  Message << " use case ";
  std::string strTestResult;
  if (TestCode)
    Message << "succeeded";
  else
    Message << "failed";
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  RetValue = true;

  return RetValue;
}


bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDLiftGasStartEndRDY(CEventMessage& Event, long Start)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  //Initialise database objects
  CPDR_HEAT_DATA* m_pPDR_Heat_Data = 0;

  if (pConnection)
  {
    m_pPDR_Heat_Data = new CPDR_HEAT_DATA(pConnection);
  }

  Message << "\nPDR_HEAT_DATA" << endl;
  if (m_pPDR_Heat_Data->select(RecHeatID, RecTreatID, RecPlant))
  {
    if (Start == 1)
    {
      if (!m_pPDR_Heat_Data->isNull("LIFT_GAS_STARTTIME", 1))
      {
        Message << "LIFT_GAS_STARTTIME(less or equal to NOW) = " << m_pPDR_Heat_Data->getLIFT_GAS_STARTTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  LIFT_GAS_STARTTIME is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }
      if (!m_pPDR_Heat_Data->isNull("VESSEL_TEMP_START", 1))
      {
        Message << "VESSEL_TEMP_START(-1 if not set in tracker) = " << m_pPDR_Heat_Data->getVESSEL_TEMP_START(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  VESSEL_TEMP_START is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }
    }
    else
    {
      if (!m_pPDR_Heat_Data->isNull("LIFT_GAS_ENDTIME", 1))
      {
        Message << "LIFT_GAS_ENDTIME(less or equal to NOW) = " << m_pPDR_Heat_Data->getLIFT_GAS_ENDTIME(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  LIFT_GAS_ENDTIME is not set in PDR_HEAT_DATA"<<endl;
        TestCode = false;
      }
      seqGasData *pSeqGasData = 0;
      sGasData sData;
      setpDM_Interface(ServerTask,DM::PRODUCT);
      pSeqGasData = m_pDM_Interface->getGasData(ProductID.c_str(),DATA::LiftGasAmount);
      CIntfData::getAt(sData, pSeqGasData, 0);
      std::string strGasType = sData.GasType;
      if (strGasType == DEF_GAS::Ar)
      {
        if (!m_pPDR_Heat_Data->isNull("LIFT_GAS_AR_CONS", 1))
        {
          Message << "LIFT_GAS_AR_CONS("<<sData.GasValue<<") = " << m_pPDR_Heat_Data->getLIFT_GAS_AR_CONS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  LIFT_GAS_AR_CONS is not set in PDR_HEAT_DATA"<<endl;
          TestCode = false;
        }
      }
      else if (strGasType == DEF_GAS::N2)
      {
        if (!m_pPDR_Heat_Data->isNull("LIFT_GAS_N2_CONS", 1))
        {
          Message << "LIFT_GAS_N2_CONS("<<sData.GasValue<<") = " << m_pPDR_Heat_Data->getLIFT_GAS_N2_CONS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  LIFT_GAS_N2_CONS is not set in PDR_HEAT_DATA"<<endl;
          TestCode = false;
        }
      }

      pSeqGasData= m_pDM_Interface->getGasData(ProductID.c_str(),DATA::LiftGasDuration);
      long lSeqLength = CIntfData::getLength(pSeqGasData);
      for(int i = 0; i < lSeqLength; ++i)
      {
        CIntfData::getAt(sData, pSeqGasData, i);
        strGasType = sData.GasType;
        if (strGasType == DEF_GAS::Ar)
        {
          if (!m_pPDR_Heat_Data->isNull("AR_LIFT_GAS_DUR", 1))
          {
            Message << "AR_LIFT_GAS_DUR("<<sData.GasValue<<") = " << m_pPDR_Heat_Data->getAR_LIFT_GAS_DUR(1) << endl;
          }
          else
          {
            Message << "ERROR:\n  AR_LIFT_GAS_DUR is not set in PDR_HEAT_DATA"<<endl;
            TestCode = false;
          }
        }
        else if (strGasType == DEF_GAS::N2)
        {
          if (!m_pPDR_Heat_Data->isNull("N2_LIFT_GAS_DUR", 1))
          {
            Message << "N2_LIFT_GAS_DUR("<<sData.GasValue<<") = " << m_pPDR_Heat_Data->getN2_LIFT_GAS_DUR(1) << endl;
          }
          else
          {
            Message << "ERROR:\n  N2_LIFT_GAS_DUR is not set in PDR_HEAT_DATA"<<endl;
            TestCode = false;
          }        
        }
      }
    }
  }
  else
  {
    Message << "ERROR:\n  Failed to select data from PDR_HEAT_DATA"<<endl;
    TestCode = false;
  }


  if (m_pPDR_Heat_Data) { delete m_pPDR_Heat_Data; m_pPDR_Heat_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  Message.str("");
  
  Message << "Test ";
  switch(Start)
  {
  case 0:
    Message << "Vacuum End";
    break;
  case 1:
    Message << "Vacuum Start";
    break;
  case 2:
    Message << "Vacuum Interrupt";
    break;
  }
  Message << " use case ";
  std::string strTestResult;
  if (TestCode)
    Message << "succeeded";
  else
    Message << "failed";
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  RetValue = true;

  return RetValue;
}


bool CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::handleHMDTempMeasurementRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  long ProbeType = 0;
  long RowNumber = 0;
  double MeasO2Conc = 0.0;
  double MeasCarbonConc = 0.0;
  double MeasAlConc = 0.0;
  std::string LadleNo;
  std::string LadleType;
  //Initialise database objects

  CPD_ANL* m_pPD_Anl = 0;
  CPD_LADLE_DATA* m_pPD_Ladle_Data = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CARCHIVER_HMD_Test_Task* m_pTestTask = 0;

  if (pConnection)
  {
    m_pPD_Anl = new CPD_ANL(pConnection);
    m_pPD_Ladle_Data = new CPD_LADLE_DATA(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pTestTask = new CARCHIVER_HMD_Test_Task();
  }

  setpDM_Interface(ServerTask,DM::EVENT);
  ProbeType  = m_pDM_Interface->getLong(DataKey.c_str(), DATA::ProbeType);

  if (ProbeType != DEF_GC_PROBETYPE::TempCarbonOxygen)
  {
    ProbeType = DEF_GC_PROBETYPE::Temperature;
  }

  Message << "\nPD_ANL" << endl;
  if (m_pPD_Anl->select(RecHeatID, RecTreatID, RecPlant))
  {
    long Row = m_pTestTask->getLastRowFromPD_Anl(RecHeatID, RecTreatID, RecPlant, pConnection);  // get the row with a maximal ANL_COUNTER
    if (!m_pPD_Anl->isNull("ANL_COUNTER",Row))
    {
      Message << "ANL_COUNTER = " << m_pPD_Anl->getANL_COUNTER(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  ANL_COUNTER is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (ProbeType == DEF_GC_PROBETYPE::TempCarbonOxygen)
    {
      MeasO2Conc     = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::MeasO2Conc);
      MeasCarbonConc = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::MeasCarbonConc);
      MeasAlConc     = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::MeasAlConc);

      if (!m_pPD_Anl->isNull("O_SMPLSYS",Row))
      {
        if (m_pPD_Anl->getO_SMPLSYS(Row) == MeasO2Conc)
          Message << "O_SMPLSYS = " << m_pPD_Anl->getO_SMPLSYS(Row) << endl;
        else
        {
          Message << "ERROR:\n  O_SMPLSYS is not equal "<< MeasO2Conc;
          Message << " it is " << m_pPD_Anl->getO_SMPLSYS(Row) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  O_SMPLSYS is not set in PD_ANL"<<endl;
        TestCode = false;
      }
      if (!m_pPD_Anl->isNull("C_SMPLSYS",Row))
      {
        if(m_pPD_Anl->getC_SMPLSYS(Row) == MeasCarbonConc)
          Message << "C_SMPLSYS = " << m_pPD_Anl->getC_SMPLSYS(Row) << endl;
        else
        {
          Message << "ERROR:\n  C_SMPLSYS is not equal "<< MeasCarbonConc;
          Message << " it is " << m_pPD_Anl->getC_SMPLSYS(Row) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  C_SMPLSYS is not set in PD_ANL"<<endl;
        TestCode = false;
      }
      if (!m_pPD_Anl->isNull("AL_SMPLSYS",Row))
      {
        if(m_pPD_Anl->getAL_SMPLSYS(Row) == MeasAlConc)
          Message << "AL_SMPLSYS = " << m_pPD_Anl->getAL_SMPLSYS(Row) << endl;
        else
        {
          Message << "ERROR:\n  AL_SMPLSYS is not equal "<< MeasCarbonConc;
          Message << " it is " << m_pPD_Anl->getAL_SMPLSYS(Row) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  AL_SMPLSYS is not set in PD_ANL"<<endl;
        TestCode = false;
      }
    }
    {
    if (!m_pPD_Anl->isNull("PHASENO",Row))
    {
      Message << "PHASENO = " << m_pPD_Anl->getPHASENO(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  PHASENO is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("STAGENO",Row))
    {
      Message << "STAGENO = " << m_pPD_Anl->getSTAGENO(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  STAGENO is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("SAMPLEMODENO",Row))
    {
      Message << "SAMPLEMODENO = " << m_pPD_Anl->getSAMPLEMODENO(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  SAMPLEMODENO is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("SMPLUSEABLE",Row))
    {
      if (m_pPD_Anl->getSMPLUSEABLE(Row) == 1)
        Message << "SMPLUSEABLE = " << m_pPD_Anl->getSMPLUSEABLE(Row) << endl;
      else
      {
        Message << "ERROR:\n  SMPLUSEABLE is not equal 1 it is " << m_pPD_Anl->getSMPLUSEABLE(Row) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  SMPLUSEABLE is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("ELECMOMENT",Row))
    {
      Message << "ELECMOMENT = " << m_pPD_Anl->getELECMOMENT(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  ELECMOMENT is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("O2_MOMENT",Row))
    {
      Message << "O2_MOMENT = " << m_pPD_Anl->getO2_MOMENT(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  O2_MOMENT is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("AR_MOMENT",Row))
    {
      Message << "AR_MOMENT = " << m_pPD_Anl->getAR_MOMENT(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  AR_MOMENT is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("N2_MOMENT",Row))
    {
      Message << "N2_MOMENT = " << m_pPD_Anl->getN2_MOMENT(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  N2_MOMENT is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    if (!m_pPD_Anl->isNull("PRODORDERID",Row))
    {
      Message << "PRODORDERID = " << m_pPD_Anl->getPRODORDERID(Row) << endl;
    }
    else
    {
      Message << "ERROR:\n  PRODORDERID is not set in PD_ANL"<<endl;
      TestCode = false;
    }
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_ANL was not successfull"<<endl;
    TestCode = false;
  }
  LadleType = m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleType);
  LadleNo = m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleId);

  Message << "\nPD_LADLE_DATA" << endl;
  if (m_pPD_Ladle_Data->select(LadleType, LadleNo, "LAST"))
  {
    if(!m_pPD_Ladle_Data->isNull("PRODORDERID",1))
    {
      Message << "PRODORDERID = " << m_pPD_Ladle_Data->getPRODORDERID(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  PRODORDERID is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Ladle_Data->isNull("LASTTEMPTIME",1))
    {
      Message << "LASTTEMPTIME = " << m_pPD_Ladle_Data->getLASTTEMPTIME(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  LASTTEMPTIME is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Ladle_Data->isNull("LASTTEMP",1))
    {
      Message << "LASTTEMP = " << m_pPD_Ladle_Data->getLASTTEMP(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  LASTTEMP is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Ladle_Data->isNull("TMPSTATUS",1))
    {
      if (m_pPD_Ladle_Data->getTMPSTATUS(1) == 2)
        Message << "TMPSTATUS = " << m_pPD_Ladle_Data->getTMPSTATUS(1) << endl;
      else
      {
        Message << "ERROR:\n  TMPSTATUS is not equal 2";
        Message << " it is " << m_pPD_Ladle_Data->getTMPSTATUS(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TMPSTATUS is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Ladle_Data->isNull("HEATID",1))
    {
      Message << "HEATID = " << m_pPD_Ladle_Data->getHEATID(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  HEATID is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Ladle_Data->isNull("TREATID",1))
    {
      Message << "TREATID = " << m_pPD_Ladle_Data->getTREATID(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  TREATID is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_LADLE_DATA was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPD_REPORT" << endl;
  if (m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_Report->isNull("TEMPPROBESNO",1))
    {
      Message << "TEMPPROBESNO = " << m_pPD_Report->getTEMPPROBESNO(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  TEMPPROBESNO is not set in PD_REPORT"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Report->isNull("LASTTEMP",1))
    {
      Message << "LASTTEMP = " << m_pPD_Report->getLASTTEMP(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  LASTTEMP is not set in PD_REPORT"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_REPORT was not successfull"<<endl;
    TestCode = false;
  }

  if (m_pPD_Anl) { delete m_pPD_Anl; m_pPD_Anl = 0;}
  if (m_pPD_Ladle_Data) { delete m_pPD_Ladle_Data; m_pPD_Ladle_Data = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Temp/TempCarbonOxygen Measurement use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Temp/TempCarbonOxygen Measurement use case failed",1);
  RetValue = true;

  return RetValue;
}

double CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::getDurationSince(const std::string &Key, const char* Name)
{
  double Dur = DEF::Inv_Double;

  setpDM_Interface(ServerTask, DM::PRODUCT);
  if (m_pDM_Interface)
  {
    CDateTime now;
    CDateTime start;
    CDeltaTime dtTime;
    
    start.SetTime(m_pDM_Interface->getDate(Key.c_str(), Name));
    dtTime = CDateTime::subTimes(now, start);
    Dur = dtTime.asSeconds()/60;

  }
  return Dur;
}
void CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::initDBClasses()
{
}

void CARCHIVER_HMD_Test_SignalsAndMeasurementsHandling::deleteDBClasses()
{
}

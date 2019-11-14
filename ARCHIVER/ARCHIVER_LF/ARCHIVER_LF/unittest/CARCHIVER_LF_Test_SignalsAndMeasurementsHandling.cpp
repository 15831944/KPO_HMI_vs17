#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_SignalsAndMeasurementsHandling.h"
#include "CARCHIVER_LF_Test_Task.h"
#include "CStirringDataHandler.h"
#include "DEF_GC_PROBETYPE.h"

CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::~CARCHIVER_LF_Test_SignalsAndMeasurementsHandling()
{
}

CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::CARCHIVER_LF_Test_SignalsAndMeasurementsHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
}

//Dipesh--------
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFStirringStartEndRDY(CEventMessage& Event, long status)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  std::string DataKey = Event.getDataKey();


  long OtherPlugStart = 0;
  CDateTime now;
  seqGasData* StirrConsSeq;
  seqGasData* StirrDurSeq;
  sGasData    StirrData;
  string      Gas;
  long        PredLength;
  double      ARCons = 0;
  double      N2Cons = 0;
  double      ARDur  = 0;
  double      N2Dur  = 0;
  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPDL_STIRR_DATA* m_pPDL_Stirr_Data = 0;
  CPDL_HEAT_DATA* m_pPDL_HEAT_DATA = 0;
  CPDL_STIRR_BYPASS_DATA* m_pPDL_Stirr_Bypass_Data = 0;

  //Initialise database objects
  if (pConnection)
  {
    m_pPDL_Stirr_Data = new CPDL_STIRR_DATA(pConnection);
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
    m_pPDL_Stirr_Bypass_Data = new CPDL_STIRR_BYPASS_DATA(pConnection);
  }
  
  setpDM_Interface(ServerTask,DM::EVENT);
  long PlugNo = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LadlePlugNo);

  std::vector<long> PlugList;
  if (PlugNo == 0)
  {
    PlugList.push_back(1);
    PlugList.push_back(2);
  }
  else
  {
    PlugList.push_back(PlugNo);
  }

  if (Status == DEF_GEN_STATES::Start) // Stirring START
  {
    for( long i = 0; i < (long)PlugList.size(); ++i)
    {
      long PN = PlugList[i];
      Message << "\nPDL_STIRR_DATA" << endl;
      if(m_pPDL_Stirr_Data->selectActual(RecHeatID, RecTreatID, PN))
      {
        long lRows = m_pPDL_Stirr_Data->getLastRow();
        for( int i = 1; i <= lRows; ++i)
        {
          Message << "PLUGNO("<<i<<") = " << m_pPDL_Stirr_Data->getPLUGNO(i) << endl;
          Message << "STIRR_START_PLUG("<<i<<") = " << m_pPDL_Stirr_Data->getSTIRR_START_PLUG(i) << endl;
        }
      }
      else
      {
        Message << "ERROR:\n  No any entry for this RecHeatID, RecTreatID & RecPlant in PDL_STIRR_DATA" << endl;
        TestCode = false;
      }
      Message << "\nPDL_HEAT_DATA" << endl;
      if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
      {
        if (!m_pPDL_HEAT_DATA->isNull("STIRR_START", 1))
        {
          Message << "STIRR_START(now) = " << m_pPDL_HEAT_DATA->getSTIRR_START(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_START is not set in PDL_HEAT_DATA" << endl;
          TestCode = false;
        }
        if (PN == 1 && !m_pPDL_HEAT_DATA->isNull("STIRR_START_PLUG1", 1))
        {
          Message << "STIRR_START_PLUG1(now) = " << m_pPDL_HEAT_DATA->getSTIRR_START_PLUG1(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_START_PLUG1 is not set in PDL_HEAT_DATA" << endl;
          TestCode = false;
        }
        if (PN == 2 && !m_pPDL_HEAT_DATA->isNull("STIRR_START_PLUG2", 1))
        {
          Message << "STIRR_START_PLUG2(now) = " << m_pPDL_HEAT_DATA->getSTIRR_START_PLUG2(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_START_PLUG2 is not set in PDL_HEAT_DATA" << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  No any entry for this HeatID, TreatID & Plant in PDL_HEAT_DATA" << endl;
        TestCode = false;
      }
    } 
  }// Stirring START
  else
  {
    setpDM_Interface(ServerTask,DM::PRODUCT);
    for( long i = 0; i < (long)PlugList.size(); ++i)
    {
      long PN = PlugList[i];
      if ( PN == 1 )
        {
          // get stirring consumptions of the  plug
          StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrLastStartEndAmountPlug1);
          // get stirring durations of the  plug
          StirrDurSeq =  m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrLastStartEndDurPlug1);
        }
      if ( PN == 2 )
        {
          // get stirring consumptions of the  plug
          StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrLastStartEndAmountPlug2);
          // get stirring durations of the  plug
          StirrDurSeq =  m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrLastStartEndDurPlug2);
        }
        
        PredLength = CIntfData::getLength(*StirrConsSeq);
        for (int i = 0 ; i < PredLength ; ++i)
        {
          CIntfData::getAt(StirrData, StirrConsSeq, i);

          Gas = StirrData.GasType;  
          if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
          if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
        }

        PredLength = CIntfData::getLength(*StirrDurSeq);
        for (int i = 0 ; i < PredLength ; ++i)
        {
          CIntfData::getAt(StirrData, StirrDurSeq, i);

          Gas = StirrData.GasType;  
          if (Gas == DEF_GAS::Ar) ARDur = StirrData.GasValue;
          if (Gas == DEF_GAS::N2) N2Dur = StirrData.GasValue;
        }
  Message << "\nPDL_STIRR_DATA" << endl;
  if ((m_pPDL_Stirr_Data->selectActual(RecHeatID, RecTreatID, PN))
      &&(m_pPDL_Stirr_Data->isNull("STIRR_END_PLUG", 1)))
  {
    if (!m_pPDL_Stirr_Data->isNull("STIRR_AR_DUR",1))
    {
      if (m_pPDL_Stirr_Data->getSTIRR_AR_DUR(1) == ARDur)
      Message << "STIRR_AR_DUR = " << m_pPDL_Stirr_Data->getSTIRR_AR_DUR(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_AR_DUR is not equal "<< ARDur;
        Message << " it is " << m_pPDL_Stirr_Data->getSTIRR_AR_DUR(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_AR_DUR is not set in CPDL_STIRR_DATA"<<endl;
      TestCode = false;
    }

    if (!m_pPDL_Stirr_Data->isNull("STIRR_N2_DUR",1))
    {
      if (m_pPDL_Stirr_Data->getSTIRR_N2_DUR(1) == N2Dur)
      Message << "STIRR_N2_DUR = " << m_pPDL_Stirr_Data->getSTIRR_N2_DUR(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_N2_DUR is not equal "<< N2Dur;
        Message << " it is " << m_pPDL_Stirr_Data->getSTIRR_N2_DUR(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_N2_DUR is not set in CPDL_STIRR_DATA"<<endl;
      TestCode = false;
    }

    if (!m_pPDL_Stirr_Data->isNull("STIRR_AR_CONS_PLUG",1))
    {
      if (m_pPDL_Stirr_Data->getSTIRR_AR_CONS_PLUG(1) == ARCons)
      Message << "STIRR_AR_CONS_PLUG = " << m_pPDL_Stirr_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not equal "<< ARCons;
        Message << " it is " << m_pPDL_Stirr_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not set in CPDL_STIRR_DATA"<<endl;
      TestCode = false;
    }

    if (!m_pPDL_Stirr_Data->isNull("STIRR_N2_CONS_PLUG",1))
    {
      if (m_pPDL_Stirr_Data->getSTIRR_N2_CONS_PLUG(1) == N2Cons)
      Message << "STIRR_N2_CONS_PLUG = " << m_pPDL_Stirr_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not equal "<< N2Cons;
        Message << " it is " << m_pPDL_Stirr_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not set in CPDL_STIRR_DATA"<<endl;
      TestCode = false;
    }

    if(!m_pPDL_Stirr_Data->isNull("STIRR_END_PLUG",1))
    {
      Message << "STIRR_END_PLUG(now) = " << m_pPDL_Stirr_Data->getSTIRR_END_PLUG(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  STIRR_END_PLUG is not set in CPDL_STIRR_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  Selection from PDL_STIRR_DATA is not right"<<endl;
    TestCode = false;
  }

  Message << "\nPDL_STIRR_BYPASS_DATA" << endl;
  if ((m_pPDL_Stirr_Bypass_Data->selectActual(RecHeatID, RecTreatID, PN))
        &&(m_pPDL_Stirr_Bypass_Data->isNull("STIRR_BYPASS_END_PLUG", 1)))
  {
    if (PN == 1)
    {
      StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrAmountPlug1);
    }
    if (PN == 2)
    {
      StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrAmountPlug2);
    }

    PredLength = CIntfData::getLength(*StirrConsSeq);
    for (int i = 0 ; i < PredLength ; ++i)
    {
      CIntfData::getAt(StirrData, StirrConsSeq, i);
      Gas = StirrData.GasType;  
      if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
      if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
    }
    if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_AR_CONS_PLUG",1))
    {
      if (m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) == ARCons)
      Message << "STIRR_AR_CONS_PLUG = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not equal "<< ARCons;
        Message << " it is " << m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not set in CPDL_STIRR_BYPASS_DATA"<<endl;
      TestCode = false;
    }
    if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_N2_CONS_PLUG",1))
    {
      if (m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) == N2Cons)
      Message << "STIRR_N2_CONS_PLUG = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not equal "<< N2Cons;
        Message << " it is " << m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not set in CPDL_STIRR_BYPASS_DATA"<<endl;
      TestCode = false;
    }

    if(!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_BYPASS_END_PLUG",1))
    {
      Message << "STIRR_BYPASS_END_PLUG(now) = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_BYPASS_END_PLUG(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  STIRR_BYPASS_END_PLUG is not set in CPDL_STIRR_BYPASS_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  Selection from PDL_STIRR_BYPASS_DATA is not right"<<endl;
    TestCode = false;
  }

  Message << "\nPDL_HEAT_DATA" << endl;
  if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPDL_HEAT_DATA->isNull("STIRR_END",1))
    {
      Message << "STIRR_END(now) = " << m_pPDL_HEAT_DATA->getSTIRR_END(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  STIRR_END is not set in PDL_HEAT_DATA"<<endl;
      TestCode = false;
    }

    setpDM_Interface(ServerTask,DM::PRODUCT);
    StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrAmount);
    PredLength = CIntfData::getLength(*StirrConsSeq);
    for (int i = 0 ; i < PredLength ; ++i)
    {
       CIntfData::getAt(StirrData, StirrConsSeq, i);
       Gas = StirrData.GasType;  
       if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
       if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
    }

    if (!m_pPDL_HEAT_DATA->isNull("STIRR_AR_CONS",1))
    {
      if (m_pPDL_HEAT_DATA->getSTIRR_AR_CONS(1) == ARCons)
      Message << "STIRR_AR_CONS_PLUG = " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS is not equal "<< ARCons;
        Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_AR_CONS is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
    }

    if (!m_pPDL_HEAT_DATA->isNull("STIRR_N2_CONS",1))
    {
      if (m_pPDL_HEAT_DATA->getSTIRR_N2_CONS(1) == N2Cons)
      Message << "STIRR_N2_CONS_PLUG = " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS is not equal "<< N2Cons;
        Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_N2_CONS is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
    }

    StirrDurSeq =  m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrDur);

    PredLength = CIntfData::getLength(*StirrDurSeq);
    for (int i = 0 ; i < PredLength ; ++i)
    {
      CIntfData::getAt(StirrData, StirrDurSeq, i);
      Gas = StirrData.GasType;  
      if (Gas == DEF_GAS::Ar) ARDur = StirrData.GasValue;
      if (Gas == DEF_GAS::N2) N2Dur = StirrData.GasValue;
    }

    if (!m_pPDL_HEAT_DATA->isNull("STIRR_AR_DUR",1))
    {
      if (m_pPDL_HEAT_DATA->getSTIRR_AR_DUR(1) == ARDur)
      Message << "STIRR_AR_DUR = " << m_pPDL_HEAT_DATA->getSTIRR_AR_DUR(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_AR_DUR is not equal "<< ARDur;
        Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_AR_DUR(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_AR_DUR is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
    }

    if (!m_pPDL_HEAT_DATA->isNull("STIRR_N2_DUR",1))
    {
      if (m_pPDL_HEAT_DATA->getSTIRR_N2_DUR(1) == N2Dur)
      Message << "STIRR_N2_DUR = " << m_pPDL_HEAT_DATA->getSTIRR_N2_DUR(1) << endl;
      else
      {
        Message << "ERROR:\n  STIRR_N2_DUR is not equal "<< N2Dur;
        Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_N2_DUR(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STIRR_N2_DUR is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
    }

    if (PN == 1)
    {
      StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrAmountPlug1);
    }
    if (PN == 2)
    {
      StirrConsSeq = m_pDM_Interface->getGasData(RecProductID.c_str(), DATA::StirrAmountPlug2);
    }

    PredLength = CIntfData::getLength(*StirrConsSeq);
    for (int i = 0 ; i < PredLength ; ++i)
    {
      CIntfData::getAt(StirrData, StirrConsSeq, i);
      Gas = StirrData.GasType;  
      if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
      if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
    } 

    if (PN == 1)
    {
      if(!m_pPDL_HEAT_DATA->isNull("STIRR_END_PLUG1",1))
      {
        Message << "STIRR_END_PLUG1(now) = " << m_pPDL_HEAT_DATA->getSTIRR_END_PLUG1(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_END_PLUG1 is not set in PDL_HEAT_DATA"<<endl;
        TestCode = false;
      }
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_AR_CONS_PLUG1",1))
      {
        if (m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG1(1) == ARCons)
        Message << "STIRR_AR_CONS_PLUG1 = " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG1(1) << endl;
        else
        {
          Message << "ERROR:\n  STIRR_AR_CONS_PLUG1 is not equal "<< ARCons;
          Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG1(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG1 is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_N2_CONS_PLUG1",1))
      {
        if (m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG1(1) == N2Cons)
        Message << "STIRR_N2_CONS_PLUG1 = " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG1(1) << endl;
        else
        {
          Message << "ERROR:\n  STIRR_N2_CONS_PLUG1 is not equal "<< N2Cons;
          Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG1(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG1 is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    }
    if (PN == 2)
    {
      if(!m_pPDL_HEAT_DATA->isNull("STIRR_END_PLUG2",1))
      {
        Message << "STIRR_END_PLUG2(now) = " << m_pPDL_HEAT_DATA->getSTIRR_END_PLUG2(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_END_PLUG2 is not set in PDL_HEAT_DATA"<<endl;
        TestCode = false;
      }
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_AR_CONS_PLUG2",1))
      {
        if (m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG2(1) == ARCons)
        Message << "STIRR_AR_CONS_PLUG2 = " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG2(1) << endl;
        else
        {
          Message << "ERROR:\n  STIRR_AR_CONS_PLUG2 is not equal "<< ARCons;
          Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_PLUG2(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_PLUG2 is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_N2_CONS_PLUG2",1))
      {
        if (m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG1(1) == N2Cons)
        Message << "STIRR_N2_CONS_PLUG2 = " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG2(1) << endl;
        else
        {
          Message << "ERROR:\n  STIRR_N2_CONS_PLUG2 is not equal "<< N2Cons;
          Message << " it is " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_PLUG2(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_PLUG2 is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    }
  }
  else
  {
    Message << "ERROR:\n  Selection from PDL_Heat_Data is not right."<<endl;
    TestCode = false;
  }
    }
  }
  //delete databse objects
  if (m_pPDL_Stirr_Data) { delete m_pPDL_Stirr_Data; m_pPDL_Stirr_Data = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  if (m_pPDL_Stirr_Bypass_Data) { delete m_pPDL_Stirr_Bypass_Data; m_pPDL_Stirr_Bypass_Data = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}

//Dipesh-----------
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFStirringBypassOnOffRDY(CEventMessage& Event, long status)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string DataKey = Event.getDataKey();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  std::string CustHeatID;

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPDL_STIRR_BYPASS_DATA* m_pPDL_Stirr_Bypass_Data = 0;
  
  //Initialise database objects
  if (pConnection)
  {
    m_pPDL_Stirr_Bypass_Data = new CPDL_STIRR_BYPASS_DATA(pConnection); 
  }

  setpDM_Interface(ServerTask,DM::EVENT);
  long PlugNo = m_pDM_Interface->getLong(DataKey.c_str(), DATA::LadlePlugNo);
    
  // PlugNo == 0 means both plugs are stirring !!
  std::vector<long> PlugList;
  if (PlugNo == 0)
  {
    PlugList.push_back(1);
    PlugList.push_back(2);
  }
  else
  {
    PlugList.push_back(PlugNo);
  }
  if (Status == DEF_GEN_STATES::Start)
  {
    for( long i = 0; i < (long)PlugList.size(); ++i)
    {
      long PN = PlugList[i];
      if(m_pPDL_Stirr_Bypass_Data->selectActual(RecHeatID, RecTreatID, PN))
      {
        if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_BYPASS_START_PLUG", 1))
        {
          Message << "STIRR_BYPASS_START_PLUG(now) = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_BYPASS_START_PLUG(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_BYPASS_START_PLUG is not set in PDL_HEAT_DATA" << endl;
          TestCode = false;
        }
      }
    }
  }
  else
  {
    seqGasData* StirrConsSeq;
    sGasData    StirrData;
    string      Gas;
    long        PredLength;
    double      ARCons = 0;
    double      N2Cons = 0;

    setpDM_Interface(ServerTask,DM::PRODUCT);
    for( long i = 0; i < (long)PlugList.size(); ++i)
    {
      long PN = PlugList[i];

      // get stirring consumptions of the  plug
      if (PN == 1)
      {
        StirrConsSeq = m_pDM_Interface->getGasData(DataKey.c_str(), DATA::StirrAmountPlug1);
      }
      if (PN == 2)
      {
        StirrConsSeq = m_pDM_Interface->getGasData(DataKey.c_str(), DATA::StirrAmountPlug2);
      }

      PredLength = CIntfData::getLength(*StirrConsSeq);
      for (int i = 0 ; i < PredLength ; ++i)
      {
        CIntfData::getAt(StirrData, StirrConsSeq, i);
        Gas = StirrData.GasType;  
        if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
	      if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
      }

      if ((m_pPDL_Stirr_Bypass_Data->selectActual(RecHeatID, RecTreatID, PN))
        &&(m_pPDL_Stirr_Bypass_Data->isNull("STIRR_BYPASS_END_PLUG", 1)))
      {
        if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_AR_CONS_PLUG",1))
        {
          if (m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) == ARCons)
            Message << "STIRR_AR_CONS_PLUG = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
          else
          { 
            Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not equal "<< ARCons;
            Message << " it is " << m_pPDL_Stirr_Bypass_Data->getSTIRR_AR_CONS_PLUG(1) << endl;
            TestCode = false;
          }
        }
        else
        {
           Message << "ERROR:\n  STIRR_AR_CONS_PLUG is not set in PDL_STIRR_BYPASS_DATA"<<endl;
           TestCode = false;
        }

        if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_N2_CONS_PLUG",1))
        {
          if (m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) == N2Cons)
            Message << "STIRR_N2_CONS_PLUG = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
          else
          { 
            Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not equal "<< N2Cons;
            Message << " it is " << m_pPDL_Stirr_Bypass_Data->getSTIRR_N2_CONS_PLUG(1) << endl;
            TestCode = false;
          }
        }
        else
        {
           Message << "ERROR:\n  STIRR_N2_CONS_PLUG is not set in PDL_STIRR_BYPASS_DATA"<<endl;
           TestCode = false;
        }
        
        if (!m_pPDL_Stirr_Bypass_Data->isNull("STIRR_BYPASS_END_PLUG", 1))
        {
          Message << "STIRR_BYPASS_END_PLUG(now) = " << m_pPDL_Stirr_Bypass_Data->getSTIRR_BYPASS_END_PLUG(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_BYPASS_END_PLUG is not set in PDL_STIRR_BYPASS_DATA" << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  PDL_STIRR_BYPASS_DATA, select for HeatID: " << RecHeatID << ", TreatID: "
                << RecTreatID << ", PLUGNO: " << PN << " failed!\n";
        TestCode = false;
      
      }
    }
  }
  //delete databse objects
  if (m_pPDL_Stirr_Bypass_Data) { delete m_pPDL_Stirr_Bypass_Data; m_pPDL_Stirr_Bypass_Data = 0;}
  
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}


//.... Done By PAMA....
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFEmergencyLanceStirringRDY(CEventMessage& Event, bool status)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
 
  bool TestCode = false;

  double ARCons = 0;
  double N2Cons = 0;

  //declare pointers of DB Classes
  CPDL_HEAT_DATA *m_pPDL_HEAT_DATA = 0;

  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
  }

  CDateTime StirrStSt;  // start stop time

  setpDM_Interface(Event.getSender(),DM::EVENT);
 
  StirrStSt.SetTime(m_pDM_Interface->getDate(DataKey.c_str(),DATA::DateTime));
  
  Message << "\nPDL_HEAT_DATA" << endl;
  if (m_pPDL_HEAT_DATA ->select(RecHeatID ,RecTreatID ,RecPlant ))
  {
    if(status)
    {
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_START_EMRGNCY",1))
      {
        if(m_pPDL_HEAT_DATA->getSTIRR_START_EMRGNCY(1) == StirrStSt )
        {
          Message << "STIRR_START_EMRGNCY = " << m_pPDL_HEAT_DATA->getSTIRR_START_EMRGNCY(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_START_EMRGNCY is not equal to "<< StirrStSt <<" it is " << m_pPDL_HEAT_DATA->getSTIRR_START_EMRGNCY(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  STIRR_START_EMRGNCY is not set in PDL_HEAT_DATA." << endl;
        TestCode = false;
      }
    }
    else
    {
      if (!m_pPDL_HEAT_DATA->isNull("STIRR_END_EMRGNCY",1))
      {
        if(m_pPDL_HEAT_DATA->getSTIRR_END_EMRGNCY(1) == StirrStSt )
        {
          Message << "STIRR_END_EMRGNCY = " << m_pPDL_HEAT_DATA->getSTIRR_END_EMRGNCY(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_END_EMRGNCY is not equal to "<< StirrStSt <<" it is " << m_pPDL_HEAT_DATA->getSTIRR_END_EMRGNCY(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  STIRR_END_EMRGNCY is not set in PDL_HEAT_DATA." << endl;
        TestCode = false;
      }
      
      setpDM_Interface(Event.getSender(),DM::PRODUCT);
      seqGasData StirrConsSeq = *m_pDM_Interface->getGasData(ProductID.c_str(), DATA::StirrAmountEmergLance);
      // must be one element in the sequence
      if (CIntfData::getLength(StirrConsSeq) > 0)
      {
        sGasData StirrData;
        CIntfData::getAt(StirrData, StirrConsSeq, 1);

        std::string Gas = StirrData.GasType;  
        if (Gas == DEF_GAS::Ar) ARCons = StirrData.GasValue;
	      if (Gas == DEF_GAS::N2) N2Cons = StirrData.GasValue;
      }
    }//Else end
    
    if (!m_pPDL_HEAT_DATA->isNull("EMERGENCYLANCEUSED",1))
    {
      if(m_pPDL_HEAT_DATA->getEMERGENCYLANCEUSED(1) == 1 )
      {
        Message << "EMERGENCYLANCEUSED = " << m_pPDL_HEAT_DATA->getEMERGENCYLANCEUSED(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  EMERGENCYLANCEUSED is not equal to "<< 1 <<" it is " << m_pPDL_HEAT_DATA->getEMERGENCYLANCEUSED(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  EMERGENCYLANCEUSED is not set in PDL_HEAT_DATA." << endl;
      TestCode = false;
    }
    
    if (!m_pPDL_HEAT_DATA->isNull("STIRR_AR_CONS_EMRGNCY",1))
    {
      if(m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_EMRGNCY(1) == ARCons )
      {
        Message << "STIRR_AR_CONS_EMRGNCY = " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_EMRGNCY(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_AR_CONS_EMRGNCY is not equal to "<< ARCons <<" it is " << m_pPDL_HEAT_DATA->getSTIRR_AR_CONS_EMRGNCY(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  STIRR_AR_CONS_EMRGNCY is not set in PDL_HEAT_DATA." << endl;
      TestCode = false;
    }
    if (!m_pPDL_HEAT_DATA->isNull("STIRR_N2_CONS_EMRGNCY",1))
    {
      if(m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_EMRGNCY(1) == N2Cons )
      {
        Message << "STIRR_N2_CONS_EMRGNCY = " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_EMRGNCY(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  STIRR_N2_CONS_EMRGNCY is not equal to "<< N2Cons <<" it is " << m_pPDL_HEAT_DATA->getSTIRR_N2_CONS_EMRGNCY(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  STIRR_N2_CONS_EMRGNCY is not set in PDL_HEAT_DATA." << endl;
      TestCode = false;
    }
  }
    else
  {
    Message << "ERROR:\n  The selection from PDL_HEAT_DATA was not successfull"<<endl;
    TestCode = false;
  }
  
  //delete databse objects
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
 
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Emergency Lance Stirring use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Emergency Lance Stirring use case failed",1);
  RetValue = true;

    return RetValue;
}


//.... Done By PAMA....
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFCyclicMeasurementRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;
  
  std::string LadleTransferCarId;
  std::string LadleTransferCarIdFull;
  long PredLength = 0;


  //declare pointers of DB Classes
  CPDL_CYCL_MEAS_DATA *m_pPDL_CYCL_MEAS_DATA = 0;
  CPP_HEAT_PLANT *m_pPP_HEAT_PLANT = 0;
  CPD_COOLWATER *m_pPD_COOLWATER = 0;
  

  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPDL_CYCL_MEAS_DATA = new CPDL_CYCL_MEAS_DATA(pConnection);
    m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
    m_pPD_COOLWATER = new CPD_COOLWATER(pConnection);
  }
  
  //std::string GasType;
  sGasData    GasData;
  seqGasData *StirrFlow;
  seqGasData *StirrCons;
  seqComputerModes *LFComputerModes;
  sComputerMode ComputerMode;
  seqCoolWaterData *MeasCoolWaterData;
  CDateTime RevTime;

  Message << "\nPDL_CYCL_MEAS_DATA" << endl;
  if( m_pPDL_CYCL_MEAS_DATA->selectMax(RecHeatID, RecTreatID, RecPlant, "REVTIME") )
  {
    RevTime = m_pPDL_CYCL_MEAS_DATA->getREVTIME(1);
  }
  else
  {
    Message << "ERROR:\n  Failed to select the latest REVTIME from PDL_CYCL_MEAS_DATA."<<endl;
    TestCode = false;
  }

  setpDM_Interface(ServerTask,DM::PRODUCT);
  double durSA = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatAnnounceTime);
  double durSS = getDurationSince(m_pDM_Interface, ProductID.c_str(), DATA::HeatStartTime);
  std::string PhaseL1 = m_pDM_Interface->getString(ProductID.c_str(), DATA::PhaseAct);
  std::string GasType = m_pDM_Interface->getString(ProductID.c_str(), DATA::StirrGasType);

  LadleTransferCarId = m_pDM_Interface->getString(ProductID.c_str(),DATA::LadleTransferCarId);
  if ( LadleTransferCarId == DEF::Inv_String )
  {
    Message << "ERROR:\n  No LadleTransferCarId got from DM, elec and gas data may not get also" << endl;
  }
  
  if (LadleTransferCarId=="2")
  {
    LadleTransferCarIdFull = DEF_PLANT::TransferCar2;
  }
  else if (LadleTransferCarId=="1")
  {
    LadleTransferCarIdFull = DEF_PLANT::TransferCar1;
  }
  else
  {
    log("ERROR: transfer car ID is wrong from DM interface set as Transfercar1",2);
    LadleTransferCarIdFull = DEF_PLANT::TransferCar1;
  }

  setpDM_Interface(ServerTask,DM::PLANT);
  long ElecPosUp       = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::ElecPosUp);
  long FurnBreakOn     = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnBreakOn);
  long FurnTapChangOn  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::FurnTapChangOn);
  long PowerOn         = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::PowerOn);
  long RoofPosUp       = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::RoofPosUp);
  long GantryPosIn     = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::GantryPosIn);
  LFComputerModes      = m_pDM_Interface->getComputerModes(LadleTransferCarIdFull.c_str(), DATA::ComputerModes);
  long VoltTapNo       = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::VoltTapNo);
  long EltrdRegCurve   = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::EltrdRegCurve);

  long CarOpPosIn      = m_pDM_Interface->getLong(LadleTransferCarIdFull.c_str(), DATA::LadleCarPosition);
  long CarOpPosIn_Tmp  = CarOpPosIn;
  long StirrIntensity  = m_pDM_Interface->getLong(LadleTransferCarIdFull.c_str(), DATA::StirrIntensity);
  if (StirrIntensity < 0)
    StirrIntensity = 0;

  setpDM_Interface(ServerTask,DM::PRODUCT);

  double ElecCons      = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
  StirrFlow = m_pDM_Interface->getGasData(ProductID.c_str(), DATA::StirrFlow);
  StirrCons = m_pDM_Interface->getGasData(ProductID.c_str(), DATA::StirrAmount);
  MeasCoolWaterData = m_pDM_Interface->getCoolWaterData(ProductID.c_str(),DATA::CoolingWaterData);

    if ( m_pPDL_CYCL_MEAS_DATA->select(RecHeatID, RecTreatID , RecPlant , RevTime ) )
    {
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("REVTIME",1))
      {
        CDateTime now;
        Message << "REVTIME(now) = " << m_pPDL_CYCL_MEAS_DATA->getREVTIME(1) << endl;
      }
      else
      {
        Message << "INFO:\n  REVTIME is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("DURSINCEHEATANNOUNCE",1))
      {
        Message << "DURSINCEHEATANNOUNCE(" << durSA << ") = " << m_pPDL_CYCL_MEAS_DATA->getDURSINCEHEATANNOUNCE(1) << endl;
      }
      else
      {
        Message << "INFO:\n  DURSINCEHEATANNOUNCE is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("DURSINCESTARTOFHEAT",1))
      {
        Message << "DURSINCESTARTOFHEAT(" << durSS << ") = " << m_pPDL_CYCL_MEAS_DATA->getDURSINCESTARTOFHEAT(1) << endl;
      }
      else
      {
        Message << "INFO:\n  DURSINCESTARTOFHEAT is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("VOLTTAP",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getVOLTTAP(1) == VoltTapNo)
        {
          Message << "VOLTTAP = " << m_pPDL_CYCL_MEAS_DATA->getVOLTTAP(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  VOLTTAP is not equal to "<< VoltTapNo <<" it is " << m_pPDL_CYCL_MEAS_DATA->getVOLTTAP(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  VOLTTAP is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("IMPCURVE",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getIMPCURVE(1) == EltrdRegCurve)
        {
          Message << "IMPCURVE = " << m_pPDL_CYCL_MEAS_DATA->getIMPCURVE(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  IMPCURVE is not equal to "<< EltrdRegCurve <<" it is " << m_pPDL_CYCL_MEAS_DATA->getIMPCURVE(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  IMPCURVE is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("ELECTRODEPOS",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getELECTRODEPOS(1) == ElecPosUp)
        {
          Message << "ELECTRODEPOS = " << m_pPDL_CYCL_MEAS_DATA->getELECTRODEPOS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  ELECTRODEPOS is not equal to "<< ElecPosUp <<" it is " << m_pPDL_CYCL_MEAS_DATA->getELECTRODEPOS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  ELECTRODEPOS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("FURNACEBRAKERSTATUS",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getFURNACEBRAKERSTATUS(1) == FurnBreakOn)
        {
          Message << "FURNACEBRAKERSTATUS = " << m_pPDL_CYCL_MEAS_DATA->getFURNACEBRAKERSTATUS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  FURNACEBRAKERSTATUS is not equal to "<< FurnBreakOn <<" it is " << m_pPDL_CYCL_MEAS_DATA->getFURNACEBRAKERSTATUS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  FURNACEBRAKERSTATUS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("TAPCHANGERSTATUS",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getTAPCHANGERSTATUS(1) == FurnTapChangOn)
        {
          Message << "TAPCHANGERSTATUS = " << m_pPDL_CYCL_MEAS_DATA->getTAPCHANGERSTATUS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  TAPCHANGERSTATUS is not equal to "<< FurnTapChangOn <<" it is " << m_pPDL_CYCL_MEAS_DATA->getTAPCHANGERSTATUS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  TAPCHANGERSTATUS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("POWERSTATUS",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getPOWERSTATUS(1) == PowerOn)
        {
          Message << "POWERSTATUS = " << m_pPDL_CYCL_MEAS_DATA->getPOWERSTATUS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  POWERSTATUS is not equal to "<< PowerOn <<" it is " << m_pPDL_CYCL_MEAS_DATA->getPOWERSTATUS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  POWERSTATUS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("ELEC_EGYTOT",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getELEC_EGYTOT(1) == ElecCons)
        {
          Message << "ELEC_EGYTOT = " << m_pPDL_CYCL_MEAS_DATA->getELEC_EGYTOT(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  ELEC_EGYTOT is not equal to "<< ElecCons <<" it is " << m_pPDL_CYCL_MEAS_DATA->getELEC_EGYTOT(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  ELEC_EGYTOT is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      if (!m_pPDL_CYCL_MEAS_DATA->isNull("ROOFPOS",1))
      {
        Message << "ROOFPOS = " << m_pPDL_CYCL_MEAS_DATA->getROOFPOS(1) << endl;
      }
      else
      {
        Message << "INFO:\n  ROOFPOS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("GANTRYPOS",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getGANTRYPOS(1) == GantryPosIn)
        {
          Message << "GANTRYPOS = " << m_pPDL_CYCL_MEAS_DATA->getGANTRYPOS(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  GANTRYPOS is not equal to "<< GantryPosIn <<" it is " << m_pPDL_CYCL_MEAS_DATA->getGANTRYPOS(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  GANTRYPOS is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_ELEC",1))
      {
        Message << "COMPMODE_ELEC = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_ELEC(1) << endl;
      }
      else
      {
        Message << "INFO:\n  COMPMODE_ELEC is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_STIRR",1))
      {
        Message << "COMPMODE_STIRR = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_STIRR(1) << endl;
      }
      else
      {
        Message << "INFO:\n  COMPMODE_STIRR is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_MAT",1))
      {
        Message << "COMPMODE_MAT = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_MAT(1) << endl;
      }
      else
      {
        Message << "INFO:\n  COMPMODE_MAT is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRRGASTYPE",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getSTIRRGASTYPE(1) == GasType)
        {
          Message << "STIRRGASTYPE = " << m_pPDL_CYCL_MEAS_DATA->getSTIRRGASTYPE(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRRGASTYPE is not equal to "<< GasType <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRRGASTYPE(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  STIRRGASTYPE is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      //stirr flow
      PredLength = CIntfData::getLength(StirrFlow);
      if (PredLength < 1)
      {
        Message << "ERROR:\n  Empty StirrFlow sequence was receved!" << endl;
      }
      for (int i = 0 ; i < PredLength ; ++i)
      {
        CIntfData::getAt(GasData,StirrFlow,i);
        GasType = GasData.GasType;
        if (GasType  == DEF_GAS::Ar)
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRR_AR_FLOW",1))
          {
            if((m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_FLOW(1) - GasData.GasValue) < 1 )
            {
              Message << "STIRR_AR_FLOW = " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_FLOW(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_AR_FLOW is not equal to "<< GasData.GasValue <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_FLOW(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_AR_FLOW is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
        if (GasType  == DEF_GAS::N2)
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRR_N2_FLOW",1))
          {
            if((m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_FLOW(1) - GasData.GasValue) < 1 )
            {
              Message << "STIRR_N2_FLOW = " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_N2_FLOW(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_N2_FLOW is not equal to "<< GasData.GasValue <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_N2_FLOW(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_N2_FLOW is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
      }//For End

      //stirr cons
      PredLength = CIntfData::getLength(StirrCons);
      if (PredLength < 1)
      {
        Message << "ERROR:\n  Empty StirrCons sequence was receved!" << endl;
      }
      for (int i = 0 ; i < PredLength ; ++i)
      {
        CIntfData::getAt(GasData,StirrCons,i);
        GasType = GasData.GasType;
        if (GasType  == DEF_GAS::Ar)
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRR_AR_CONS",1))
          {
            if((m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_CONS(1) - GasData.GasValue) < 1 )
            {
              Message << "STIRR_AR_CONS = " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_CONS(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_AR_CONS is not equal to "<< GasData.GasValue <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_CONS(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_AR_CONS is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
        if (GasType  == DEF_GAS::N2)
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRR_N2_CONS",1))
          {
            if((m_pPDL_CYCL_MEAS_DATA->getSTIRR_AR_CONS(1) - GasData.GasValue) < 1 )
            {
              Message << "STIRR_N2_CONS = " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_N2_CONS(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_N2_CONS is not equal to "<< GasData.GasValue <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_N2_CONS(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_N2_CONS is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
      }//For End

      if (!m_pPDL_CYCL_MEAS_DATA->isNull("STIRR_INT",1))
      {
        if(m_pPDL_CYCL_MEAS_DATA->getSTIRR_INT(1) == StirrIntensity)
        {
          Message << "STIRR_INT = " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_INT(1) << endl;
        }
        else
        {
          Message << "ERROR:\n  STIRR_INT is not equal to "<< StirrIntensity <<" it is " << m_pPDL_CYCL_MEAS_DATA->getSTIRR_INT(1) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "INFO:\n  STIRR_INT is not set in PDL_CYCL_MEAS_DATA." << endl;
        TestCode = false;
      }
      long CompModeLength = CIntfData::getLength(LFComputerModes);
      if (CompModeLength < 1)
      {
        Message << "ERROR:\n  Empty ComuterModes sequence was receved!" << endl;
      }
      for ( long i = 0 ; i < CompModeLength ; ++i)
      {
        CIntfData::getAt(ComputerMode,LFComputerModes ,i);
        if (0 == strcmp(DEF_COMP_MODES::MatHandle,ComputerMode.Device))
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_MAT",1))
          {
            if(m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_MAT(1) == ComputerMode.Status)
            {
              Message << "COMPMODE_MAT = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_MAT(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  COMPMODE_MAT is not equal to "<< ComputerMode.Status <<" it is " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_MAT(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  COMPMODE_MAT is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
        else if (0 == strcmp(DEF_COMP_MODES::Stirring, ComputerMode.Device))
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_STIRR",1))
          {
            if(m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_STIRR(1) == ComputerMode.Status)
            {
              Message << "COMPMODE_STIRR = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_STIRR(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  COMPMODE_STIRR is not equal to "<< ComputerMode.Status <<" it is " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_STIRR(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  COMPMODE_STIRR is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
        else if (0 == strcmp(DEF_COMP_MODES::Electric, ComputerMode.Device))
        {
          if (!m_pPDL_CYCL_MEAS_DATA->isNull("COMPMODE_ELEC",1))
          {
            if(m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_ELEC(1) == ComputerMode.Status)
            {
              Message << "COMPMODE_ELEC = " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_ELEC(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  COMPMODE_ELEC is not equal to "<< ComputerMode.Status <<" it is " << m_pPDL_CYCL_MEAS_DATA->getCOMPMODE_ELEC(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  COMPMODE_ELEC is not set in PDL_CYCL_MEAS_DATA." << endl;
            TestCode = false;
          }
        }
      }//For Loop End
    }
    else
    {
      Message << "ERROR:\n  The selection from PDL_CYCL_MEAS_DATA was not successfull"<<endl;
      TestCode = false;
    }

    Message << "\nPD_COOLWATER" << endl;
    long seqLength = CIntfData::getLength(MeasCoolWaterData);
    seqGasData StirrConsSeq = *m_pDM_Interface->getGasData(ProductID.c_str(), DATA::StirrAmount);
    if (seqLength < 1)
    {
      Message << "ERROR:\n  Empty MeasCoolWaterData sequence was receved!" << endl;
    }
    for ( long i = 0 ; i < seqLength ; ++ i )
    {
      // read all CoolWaterDevices
      sCoolWaterDevice CoolWaterDevice;
      CIntfData::getAt(CoolWaterDevice,MeasCoolWaterData,i);

      // read CoolWaterData from CoolWaterDevice
      sCoolWater CoolWater = CoolWaterDevice.CoolWaterData;

       // if car is out of Operating Position temperatures and the flow are set to 0.0 by DM_LF. Check only the flow.
      if (CoolWater.WaterFlow != 0.0)
      {
        Message << "\nStructure No " << (i+1) << endl;
        if ( m_pPD_COOLWATER->selectActual(RecPlant, RecTreatID ,RecHeatID, CoolWaterDevice.CoolWaterDeviceNo ,std::string(CoolWaterDevice.CoolWaterDevice) ))
        {
          if (!m_pPD_COOLWATER->isNull("COOL_EQUIP",1))
          {
            if(m_pPD_COOLWATER->getCOOL_EQUIP(1) == std::string (CoolWaterDevice.CoolWaterDevice))
            {
              Message << "COOL_EQUIP = " << m_pPD_COOLWATER->getCOOL_EQUIP(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  COOL_EQUIP is not equal to "<< CoolWaterDevice.CoolWaterDevice <<" it is " << m_pPD_COOLWATER->getCOOL_EQUIP(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  COOL_EQUIP is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
          if (!m_pPD_COOLWATER->isNull("REVTIME",1))
          {
            CDateTime now;
            Message << "REVTIME(now) = " << m_pPD_COOLWATER->getREVTIME(1) << endl;
          }
          else
          {
            Message << "INFO:\n  REVTIME is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
          if (!m_pPD_COOLWATER->isNull("DURSINCEHEATANNOUNCEMENT",1))
          {
            Message << "DURSINCEHEATANNOUNCEMENT(" << durSA << ") = " << m_pPD_COOLWATER->getDURSINCEHEATANNOUNCEMENT(1) << endl;
          }
          else
          {
            Message << "INFO:\n  DURSINCEHEATANNOUNCEMENT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }


          if (!m_pPD_COOLWATER->isNull("DURSINCESTARTOFHEAT",1))
          {
            Message << "DURSINCESTARTOFHEAT(" << durSS << ") = " << m_pPD_COOLWATER->getDURSINCESTARTOFHEAT(1) << endl;
          }
          else
          {
            Message << "INFO:\n  DURSINCESTARTOFHEAT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }

          if (!m_pPD_COOLWATER->isNull("COOL_LOOP_NO",1))
          {
            if(m_pPD_COOLWATER->getCOOL_LOOP_NO(1) == CoolWaterDevice.CoolWaterDeviceNo)
            {
              Message << "COOL_LOOP_NO = " << m_pPD_COOLWATER->getCOOL_LOOP_NO(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  COOL_LOOP_NO is not equal to "<< CoolWaterDevice.CoolWaterDeviceNo <<" it is " << m_pPD_COOLWATER->getCOOL_LOOP_NO(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  COOL_LOOP_NO is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
          if (!m_pPD_COOLWATER->isNull("CW_TEMP_IN",1))
          {
            if(m_pPD_COOLWATER->getCW_TEMP_IN(1) == CoolWater.InletTemp)
            {
              Message << "CW_TEMP_IN = " << m_pPD_COOLWATER->getCW_TEMP_IN(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  CW_TEMP_IN is not equal to "<< CoolWater.InletTemp <<" it is " << m_pPD_COOLWATER->getCW_TEMP_IN(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  CW_TEMP_IN is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
          if (!m_pPD_COOLWATER->isNull("CW_TEMP_OUT",1))
          {
            if(m_pPD_COOLWATER->getCW_TEMP_OUT(1) == CoolWater.OutletTemp)
            {
              Message << "CW_TEMP_OUT = " << m_pPD_COOLWATER->getCW_TEMP_OUT(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  CW_TEMP_OUT is not equal to "<< CoolWater.OutletTemp <<" it is " << m_pPD_COOLWATER->getCW_TEMP_OUT(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  CW_TEMP_OUT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }

          if (!m_pPD_COOLWATER->isNull("ELEC_EGYTOT",1))
          {
            if(m_pPD_COOLWATER->getELEC_EGYTOT(1) == ElecCons)
            {
              Message << "ELEC_EGYTOT = " << m_pPD_COOLWATER->getELEC_EGYTOT(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  ELEC_EGYTOT is not equal to "<< ElecCons <<" it is " << m_pPD_COOLWATER->getELEC_EGYTOT(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  ELEC_EGYTOT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }

          long PredLength1 = CIntfData::getLength(StirrConsSeq);
          double AR_Moment = 0;
          double N2_Moment = 0;
          for (int i = 0 ; i < PredLength1 ; ++i)
          {
            sGasData StirrData;
            CIntfData::getAt(StirrData, StirrConsSeq, i);

            std::string Gas = StirrData.GasType;  
            if (Gas == DEF_GAS::Ar) AR_Moment = StirrData.GasValue;
	          if (Gas == DEF_GAS::N2) N2_Moment = StirrData.GasValue;
          }
          if (!m_pPD_COOLWATER->isNull("AR_MOMENT",1))
          {
            if(m_pPD_COOLWATER->getAR_MOMENT(1) == AR_Moment)
            {
              Message << "AR_MOMENT = " << m_pPD_COOLWATER->getAR_MOMENT(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  AR_MOMENT is not equal to "<< AR_Moment <<" it is " << m_pPD_COOLWATER->getAR_MOMENT(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  AR_MOMENT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
          if (!m_pPD_COOLWATER->isNull("N2_MOMENT",1))
          {
            if(m_pPD_COOLWATER->getN2_MOMENT(1) == N2_Moment)
            {
              Message << "N2_MOMENT = " << m_pPD_COOLWATER->getN2_MOMENT(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  N2_MOMENT is not equal to "<< N2_Moment <<" it is " << m_pPD_COOLWATER->getN2_MOMENT(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  N2_MOMENT is not set in PD_COOLWATER." << endl;
            TestCode = false;
          }
        }
        else
        {
          Message << "ERROR:\n  The selection from PD_COOLWATER was not successfull"<<endl;
          TestCode = false;
        }
      }
    }
        
  //delete databse objects
  if (m_pPDL_CYCL_MEAS_DATA) { delete m_pPDL_CYCL_MEAS_DATA; m_pPDL_CYCL_MEAS_DATA = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPD_COOLWATER) { delete m_pPD_COOLWATER; m_pPD_COOLWATER = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test LF Cyclic Measurement use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test LF Cyclic Measurement use case failed",1);
  RetValue = true;

   return RetValue;
}

//.... Done By PAMA....
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFHeatingRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;

  bool TestCode = false;


  std::string PhaseName ;
  double Duration = 0.0 ;
  double ElecCons = 0.0 ;
  long PhaseNo    = 0;
  long PhaseType  = 0;
  sDate StartTime;
  sDate EndTime;
  CDateTime hStartTime;
  CDateTime hEndTime;
  seqGasData StirrAmount;

  //declare pointers of DB Classes
  CPDL_HEAT_DATA_MELT *m_pPDL_HEAT_DATA_Melt = 0;
  CPDL_HEAT_DATA *m_pPDL_HEAT_DATA = 0;

  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPDL_HEAT_DATA_Melt = new CPDL_HEAT_DATA_MELT(pConnection);
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
  }
  
   setpDM_Interface(Event.getSender(),DM::PRODUCT);
   seqElecPhaseData ElecPhaseDataSeq   = *m_pDM_Interface->getElecPhaseData(ProductID.c_str(),DATA::ElecPhaseData);          
   sElecPhaseData ElecPhaseDataStruct;

   Message << "\nPDL_HEAT_DATA_MELT" << endl;
   for ( long i = 0 ; i < CIntfData::getLength(ElecPhaseDataSeq); ++i )
   {
     CIntfData::getAt(ElecPhaseDataStruct,ElecPhaseDataSeq,i);
     if ( ElecPhaseDataStruct.PhaseType == 1 )
     {
       PhaseName   = ElecPhaseDataStruct.PhaseName ;
       Duration    = ElecPhaseDataStruct.Duration  ;
       ElecCons    = ElecPhaseDataStruct.ElecCons  ;
       PhaseNo     = ElecPhaseDataStruct.PhaseNo   ;
       PhaseType   = ElecPhaseDataStruct.PhaseType ;
       StartTime   = ElecPhaseDataStruct.StartTime ;
       EndTime     = ElecPhaseDataStruct.EndTime   ;
       StirrAmount = ElecPhaseDataStruct.GasData;

       hStartTime << StartTime;
       hEndTime   << EndTime ;

      
       if ( m_pPDL_HEAT_DATA_Melt->select(RecHeatID,RecTreatID,PhaseName ,hStartTime ))
       {
         sGasData GasData;

         double Stirr_AR_Cons = 0.0;
         double Stirr_N2_Cons = 0.0;

         // extract AR and N2 amount from Stirring data
         for ( long i = 0 ; i < CIntfData::getLength(StirrAmount); ++i )
         {
           CIntfData::getAt(GasData,StirrAmount,i);
            if ( std::string(GasData.GasType) == DEF_GAS::Ar) 
            {
              Stirr_AR_Cons = GasData.GasValue;
            }
            else if ( std::string(GasData.GasType) == DEF_GAS::N2) 
            {
              Stirr_N2_Cons = GasData.GasValue;
            }
          }
          if (!m_pPDL_HEAT_DATA_Melt->isNull("END_TIME",1))
          {
            Message << "END_TIME( should be more or less " << hEndTime  << ") = " << m_pPDL_HEAT_DATA_Melt->getEND_TIME(1) << endl;
          }
          else
          {
            Message << "INFO:\n  END_TIME is not set in PDL_HEAT_DATA_MELT." << endl;
            TestCode = false;
          }
          if (!m_pPDL_HEAT_DATA_Melt->isNull("DURATION",1))
          {
            if(m_pPDL_HEAT_DATA_Melt->getDURATION(1) == Duration)
            {
              Message << "DURATION = " << m_pPDL_HEAT_DATA_Melt->getDURATION(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  DURATION is not equal to "<< Duration <<" it is " << m_pPDL_HEAT_DATA_Melt->getDURATION(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  DURATION is not set in PDL_HEAT_DATA_MELT." << endl;
            TestCode = false;
          }
          if (!m_pPDL_HEAT_DATA_Melt->isNull("ELEC_CONS",1))
          {
            if(m_pPDL_HEAT_DATA_Melt->getELEC_CONS(1) == ElecCons)
            {
              Message << "ELEC_CONS = " << m_pPDL_HEAT_DATA_Melt->getELEC_CONS(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  ELEC_CONS is not equal to "<< ElecCons <<" it is " << m_pPDL_HEAT_DATA_Melt->getELEC_CONS(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  ELEC_CONS is not set in PDL_HEAT_DATA_MELT." << endl;
            TestCode = false;
          }
          if (!m_pPDL_HEAT_DATA_Melt->isNull("STIRR_AR_CONS",1))
          {
            if(m_pPDL_HEAT_DATA_Melt->getSTIRR_AR_CONS(1) == Stirr_AR_Cons)
            {
              Message << "STIRR_AR_CONS = " << m_pPDL_HEAT_DATA_Melt->getSTIRR_AR_CONS(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_AR_CONS is not equal to "<< Stirr_AR_Cons <<" it is " << m_pPDL_HEAT_DATA_Melt->getSTIRR_AR_CONS(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_AR_CONS is not set in PDL_HEAT_DATA_MELT." << endl;
            TestCode = false;
          }
          if (!m_pPDL_HEAT_DATA_Melt->isNull("STIRR_N2_CONS",1))
          {
            if(m_pPDL_HEAT_DATA_Melt->getSTIRR_N2_CONS(1) == Stirr_N2_Cons)
            {
              Message << "STIRR_N2_CONS = " << m_pPDL_HEAT_DATA_Melt->getSTIRR_N2_CONS(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  STIRR_N2_CONS is not equal to "<< Stirr_N2_Cons <<" it is " << m_pPDL_HEAT_DATA_Melt->getSTIRR_N2_CONS(1) << endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "INFO:\n  STIRR_N2_CONS is not set in PDL_HEAT_DATA_MELT." << endl;
            TestCode = false;
          }


        }
        else
        {
          Message << "ERROR:\n  The selection from PDL_HEAT_DATA_MELT was not successfull"<<endl;
          TestCode = false;
        }
      }
   }
   
   Message << "\nPDL_HEAT_DATA" << endl;
   setpDM_Interface(Event.getSender(),DM::EVENT);
   long VoltTap = m_pDM_Interface->getLong(DataKey.c_str(),DATA::VoltTapNo);
   if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
   {
     if (VoltTap != DEF::Inv_Long)
     {
       if (!m_pPDL_HEAT_DATA->isNull("LASTTRAFOTAP",1))
       {
         if(m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) == VoltTap)
         {
           Message << "LASTTRAFOTAP = " << m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) << endl;
         }
         else
         {
           Message << "ERROR:\n  LASTTRAFOTAP is not equal to "<< VoltTap <<" it is " << m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) << endl;
           TestCode = false;
         }
       }
       else
       {
         Message << "INFO:\n  LASTTRAFOTAP is not set in PDL_HEAT_DATA." << endl;
         TestCode = false;
       }      
     }
   }
   else
   {
     Message << "ERROR:\n  The selection from PDL_HEAT_DATA was not successfull"<<endl;
     TestCode = false;
   }


  //delete databse objects
  if (m_pPDL_HEAT_DATA_Melt) { delete m_pPDL_HEAT_DATA_Melt; m_pPDL_HEAT_DATA_Melt = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heating use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heating use case failed",1);
  RetValue = true;

    return RetValue;
}

//Dipesh-------
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFTempMeasurementRDY(CEventMessage& Event)//Dipesh-------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  std::string TempSampleId;
  std::string LadleType;
  std::string LadleNo;
  std::string ProcessStage;
  std::string SampleMode;
  
  CDateTime   SampleTime;
  long SampleCounter = -1;
  long ProbeType = -1;
  double Temp = 0.0;
  double DurSinceA = 0.0;
  double DurSinceS = 0.0;
  sSampleData sSmpData;
  double MeasO2Conc = 0.0;
  double MeasCarbonConc = 0.0;
  double MeasH2Conc = 0.0;
  double MeasAlConc = 0.0;
  double ECon = 0.0;
  long pn = 0;
    
  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPD_ANL* m_pPD_Anl = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CPD_LADLE_DATA* m_pPD_LADLE_Data = 0;
  CGC_Phase* m_pGC_PHASE = 0;
  CARCHIVER_LF_Test_Task* m_pTestTask = 0;

  //Initialise database objects
  if (pConnection)
  {
     m_pPD_Anl = new CPD_ANL(pConnection);
     m_pPD_Report = new CPD_REPORT(pConnection);
     m_pPD_LADLE_Data = new CPD_LADLE_DATA(pConnection);
     m_pGC_PHASE = new CGC_Phase(pConnection);
     m_pTestTask = new CARCHIVER_LF_Test_Task();
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

    // get act phase number
    std::string PhaseReportName;
    long PhaseNo = 0;
    std::stringstream ResPhaseNo;
    PhaseReportName = m_pDM_Interface->getString(RecProductID.c_str(),DATA::PhaseAct); 

    // important
    long l1PhaseNo = 0; // take allways ziro if phase is not countable (see GC_PHASE)

    if (PhaseReportName.find("MainBlow") != PhaseReportName.npos ||
        PhaseReportName.find("DynBlowNo") != PhaseReportName.npos ||
        PhaseReportName.find("Arc") != PhaseReportName.npos)
    {
      // MainBlow, DynBlowNo. Arc are countable phases and starts with 1 (see GC_PHASE)
      // but we don't care about counter and take always '1' 
      l1PhaseNo = 1;
    }
    else if (PhaseReportName.find("ReblowAfterBlow") != PhaseReportName.npos)
    {
      // in this phase we want to have number of each reblow.
      // we get ReblowAfterBlow1, ReblowAfterBlow2, ... , ReblowAfterBlow5
      std::stringstream num;
      num << *(PhaseReportName.end()--); // get last char (1,...,5)
      num >> l1PhaseNo;
      l1PhaseNo --; // decrease because in GC_PHASE the Reblow starts with 0 and end with 4
      // delete number
      PhaseReportName.erase(PhaseReportName.end()--, PhaseReportName.end());
    }
     // m_pGC_PHASE defined in GEN_Wraper
    if (m_pGC_PHASE->select(RecPlant,PhaseReportName,PhaseNo))
    {
      if (!m_pPD_Anl->isNull("PHASENO",1))
      {
        if (m_pPD_Anl->getPHASENO(1) == m_pGC_PHASE->getResPhaseNo(1))
        {
          Message<<"m_pGC_PHASE->getResPhaseNo(1) = "<<m_pPD_Anl->getPHASENO(1)<<endl;
        } 
        else
        {
          Message<<"ERROR:\n  The PHASENO in PD_Anl was different from the one of GC_Phase."<<endl;
          TestCode = false;
        }
      } 
      else
      {
        Message<<"ERROR:\n  PHASENO was not set in PD_Anl."<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message<<"ERROR:\n  Selection from GC_PHASE was not right"<<endl;
      TestCode = false;
    }
    
    if (!m_pPD_Anl->isNull("STAGENO",Row))
    {
      if (m_pPD_Anl->getSTAGENO(Row) == ProcessStage)
      Message << "STAGENO = " << m_pPD_Anl->getSTAGENO(Row) << endl;
      else
      {
        Message << "ERROR:\n  STAGENO is not equal "<< ProcessStage;
        Message << " it is " << m_pPD_Anl->getSTAGENO(Row) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  STAGENO is not set in PD_ANL"<<endl;
      TestCode = false;
    }

    if (SampleMode == DEF_SAMPLE_MODE::Manual)
     {
      if (!m_pPD_Anl->isNull("SAMPLEMODENO",Row))
      {
        if (m_pPD_Anl->getSAMPLEMODENO(Row) == 1)
          Message << "SAMPLEMODENO = " << m_pPD_Anl->getSAMPLEMODENO(Row) << endl;
        else
        {
          Message << "ERROR:\n  SAMPLEMODENO is not equal "<< 1;
          Message << " it is " << m_pPD_Anl->getSAMPLEMODENO(Row) << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  SAMPLEMODENO is not set in PD_ANL"<<endl;
        TestCode = false;
      }
     }
    else if (!m_pPD_Anl->isNull("SAMPLEMODENO",Row))
    {
      if (m_pPD_Anl->getSAMPLEMODENO(Row) == 2)
      Message << "SAMPLEMODENO = " << m_pPD_Anl->getSAMPLEMODENO(Row) << endl;
      else
      {
        Message << "ERROR:\n  SAMPLEMODENO is not equal "<< 2;
        Message << " it is " << m_pPD_Anl->getSAMPLEMODENO(Row) << endl;
        TestCode = false;
      }
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
        Message << "ERROR:\n  SMPLUSEABLE is not equal "<< 1;
        Message << " it is " << m_pPD_Anl->getSMPLUSEABLE(Row) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  SMPLUSEABLE is not set in PD_ANL"<<endl;
      TestCode = false;
    }

    if(!m_pPD_Anl->isNull("TEMP",1))
    {
      if(m_pPD_Anl->getTEMP(1) == Temp)
      {
        double Temp = m_pPD_Anl->getTEMP(1);
        Message << "TEMP(Temp) = " << Temp << endl;
      }
      else
      {
        Message << "ERROR:\n  TEMP is not equal to " << Temp << ". It is "<<m_pPD_Anl->getTEMP(1)<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TEMP is not set in PD_Anl"<<endl;
      TestCode = false;
    }

    if (!m_pPD_Anl->isNull("ELECMOMENT",1))
    {
      if (m_pPD_Anl->getELECMOMENT(1) == ECon)
      {
        double ECon = m_pPD_Anl->getELECMOMENT(1);
        Message << "ELECMOMENT = " << m_pPD_Anl->getELECMOMENT(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  ELECMOMENT is not equal "<< ECon;
        Message << " it is " << m_pPD_Anl->getELECMOMENT(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  ELECMOMENT is not set in PD_ANL"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_ANL was not successfull"<<endl;
    TestCode = false;
  }
  LadleType = m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleType);
  LadleNo = m_pDM_Interface->getString(DataKey.c_str(),DATA::LadleId);

  Message << "\nPD_LADLE_DATA"<<endl; 
  if(m_pPD_LADLE_Data->select(LadleType, LadleNo, "LAST"))  
  {
    if(!m_pPD_LADLE_Data->isNull("LASTTEMP",1))
    {
      if (m_pPD_LADLE_Data->getLASTTEMP(1) == Temp)
        Message << "LASTTEMP = " << m_pPD_LADLE_Data->getLASTTEMP(1) << endl;
      else
      {
        Message << "ERROR:\n  LASTTEMP is not equal Temp";
        Message << " it is " << m_pPD_LADLE_Data->getLASTTEMP(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  LASTTEMP is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    
    if(!m_pPD_LADLE_Data->isNull("TMPSTATUS",1))
    {
      if (m_pPD_LADLE_Data->getTMPSTATUS(1) == 2)
        Message << "TMPSTATUS = " << m_pPD_LADLE_Data->getTMPSTATUS(1) << endl;
      else
      {
        Message << "ERROR:\n  TMPSTATUS is not equal 2";
        Message << " it is " << m_pPD_LADLE_Data->getTMPSTATUS(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TMPSTATUS is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_LADLE_Data->isNull("HEATID",1))
    {
      if (m_pPD_LADLE_Data->getHEATID(1) == RecHeatID)
        Message << "HEATID = " << m_pPD_LADLE_Data->getHEATID(1) << endl;
      else
      {
        Message << "ERROR:\n  HEATID is not equal RecHeatID";
        Message << " it is " << m_pPD_LADLE_Data->getHEATID(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  HEATID is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_LADLE_Data->isNull("TREATID",1))
    {
      if (m_pPD_LADLE_Data->getTREATID(1) == RecTreatID)
        Message << "TREATID = " << m_pPD_LADLE_Data->getTREATID(1) << endl;
      else
      {
        Message << "ERROR:\n  TREATID is not equal RecTreatID";
        Message << " it is " << m_pPD_LADLE_Data->getTREATID(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TREATID is not set in PD_LADLE_DATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  select * from PD_LADLE_DATA was not successfull" << endl;
    TestCode = false;
  }

  Message << "\nPD_REPORT" << endl;
  if (m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_Report->isNull("TEMPPROBESNO",1))
    {
      if (m_pPD_Report->getTEMPPROBESNO(1) == 1)
        Message << "TEMPPROBESNO = " << m_pPD_Report->getTEMPPROBESNO(1) << endl;
      else
      {
        
        Message << "ERROR:\n  TEMPPROBESNO is not equal 1";
        Message << " it is " << m_pPD_Report->getTEMPPROBESNO(1) << endl;
        TestCode = false;
      }
      if (m_pPD_Report->getTEMPPROBESNO(1) == pn)
         
        Message << "TEMPPROBESNO = " << m_pPD_Report->getTEMPPROBESNO(1) << endl;
      else
      {
        Message << "ERROR:\n  TEMPPROBESNO is not equal pn";
        Message << " it is " << m_pPD_Report->getTREATID(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TEMPPROBESNO is not set in PD_REPORT"<<endl;
      TestCode = false;
    }
    if(!m_pPD_Report->isNull("LASTTEMP",1))
    {
      if (m_pPD_Report->getLASTTEMP(1) == Temp)
        Message << "LASTTEMP = " << m_pPD_Report->getLASTTEMP(1) << endl;
      else
      {
        Message << "ERROR:\n  LASTTEMP is not equal Temp";
        Message << " it is " << m_pPD_Report->getLASTTEMP(1) << endl;
        TestCode = false;
      }
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


  //delete databse objects
  if (m_pPD_LADLE_Data) { delete m_pPD_LADLE_Data; m_pPD_LADLE_Data = 0;}
  if (m_pPD_Anl) { delete m_pPD_Anl; m_pPD_Anl = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pGC_PHASE) { delete m_pGC_PHASE; m_pGC_PHASE = 0;}
  if (m_pTestTask) { delete m_pTestTask; m_pTestTask = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}
//.... Done By PAMA....
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFElectrodesInOperatingPositionFurnanceBreakerRDY(CEventMessage& Event,long Status)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  
  bool TestCode = false;

  //declare pointers of DB Classes
  CPD_ELEC_SYSTEM *m_pPD_ELEC_SYSTEM = 0;
  
  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPD_ELEC_SYSTEM = new CPD_ELEC_SYSTEM(pConnection);
  }

  setpDM_Interface(Event.getSender(),DM::EVENT);
  
  setpDM_Interface(Event.getSender(),DM::PRODUCT);
  double ElecCons   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
  double DurSA = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
  double DurSS = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);


  std::string StatusString;
  if ( Status == 1 )
  {
    StatusString = DEF_ELEC_SYSTEM::ELECTRODEPOS;
  }
  else if ( Status == 2)
  {
    StatusString = DEF_ELEC_SYSTEM::FURNACEBRAKER;
  }

  Message << "\nPD_ELEC_SYSTEM" << endl;
  if (!m_pPD_ELEC_SYSTEM->selectActual(RecHeatID , RecTreatID , StatusString , RecPlant ))
  {
    if (!m_pPD_ELEC_SYSTEM->isNull("DATECHANGE",1))
    {
      CDateTime now;
      Message << "DATECHANGE( should be more or less " << now << ") = " << m_pPD_ELEC_SYSTEM->getDATECHANGE(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DATECHANGE is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }



    //What For Status...is it correct //done by PAMA
    if (!m_pPD_ELEC_SYSTEM->isNull("STATUS",1))
    {
      if(m_pPD_ELEC_SYSTEM->getSTATUS(1) == Status )
      {
        Message << "STATUS = " << m_pPD_ELEC_SYSTEM->getSTATUS(1) << endl;
      }
      else
      {
         Message << "ERROR:\n  STATUS is not equal to "<< Status <<" it is " << m_pPD_ELEC_SYSTEM->getSTATUS(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  STATUS is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }

    if (!m_pPD_ELEC_SYSTEM->isNull("ELEC_EGYTOT",1))
    {
      if(m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) == ElecCons)
      {
        Message << "ELEC_EGYTOT = " << m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) << endl;
      }
      else
      {
         Message << "ERROR:\n  ELEC_EGYTOT is not equal to "<< ElecCons <<" it is " << m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  ELEC_EGYTOT is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }
    if (!m_pPD_ELEC_SYSTEM->isNull("DURSINCEHEATANNOUNCE",1))
    {
      Message << "DURSINCEHEATANNOUNCE( should be more or less " << DurSA << ") = " << m_pPD_ELEC_SYSTEM->getDURSINCEHEATANNOUNCE(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DURSINCEHEATANNOUNCE is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }

    if (!m_pPD_ELEC_SYSTEM->isNull("DURSINCESTARTOFHEAT",1))
    {
      Message << "DURSINCESTARTOFHEAT( should be more or less " << DurSS << ") = " << m_pPD_ELEC_SYSTEM->getDURSINCESTARTOFHEAT(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DURSINCESTARTOFHEAT is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }   
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_ELEC_SYSTEM was not successfull"<<endl;
    TestCode = false;
  }





  //delete databse objects
  if (m_pPD_ELEC_SYSTEM) { delete m_pPD_ELEC_SYSTEM; m_pPD_ELEC_SYSTEM = 0;}
  
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

   return RetValue;
}

//.... Done By PAMA....
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFPowerRDY(CEventMessage& Event, long status)//.... Done By PAMA....
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  std::string DataKey   = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  
  bool TestCode = false;

  //declare pointers of DB Classes
  CPD_ELEC_SYSTEM *m_pPD_ELEC_SYSTEM = 0;
  
  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPD_ELEC_SYSTEM = new CPD_ELEC_SYSTEM(pConnection);
  }

  setpDM_Interface(Event.getSender(),DM::PRODUCT);

  double ElecCons   = m_pDM_Interface->getDouble(ProductID.c_str(), DATA::ElecCons);
  
  double DurSA = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatAnnounceTime);
  double DurSS = getDurationSince(m_pDM_Interface, ProductID.c_str(),DATA::HeatStartTime);

  Message << "\nPD_ELEC_SYSTEM" << endl;
  if (!m_pPD_ELEC_SYSTEM->selectActual(RecHeatID , RecTreatID , DEF_ELEC_SYSTEM::POWER , RecPlant ))
  {
    if (!m_pPD_ELEC_SYSTEM->isNull("DATECHANGE",1))
    {
      CDateTime now;
      Message << "DATECHANGE( should be more or less " << now << ") = " << m_pPD_ELEC_SYSTEM->getDATECHANGE(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DATECHANGE is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }



    //What For Status...is it correct //done by PAMA

    if (!m_pPD_ELEC_SYSTEM->isNull("STATUS",1))
    {
      if(m_pPD_ELEC_SYSTEM->getSTATUS(1) == status)
      {
        Message << "STATUS = " << m_pPD_ELEC_SYSTEM->getSTATUS(1) << endl;
      }
      else
      {
         Message << "ERROR:\n  STATUS is not equal to "<< status <<" it is " << m_pPD_ELEC_SYSTEM->getSTATUS(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  STATUS is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }

    if (!m_pPD_ELEC_SYSTEM->isNull("ELEC_EGYTOT",1))
    {
      if(m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) == ElecCons)
      {
        Message << "ELEC_EGYTOT = " << m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) << endl;
      }
      else
      {
         Message << "ERROR:\n  ELEC_EGYTOT is not equal to "<< ElecCons <<" it is " << m_pPD_ELEC_SYSTEM->getELEC_EGYTOT(1) << endl;
         TestCode = false;
      }
    }
    else
    {
      Message << "INFO:\n  ELEC_EGYTOT is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }
    if (!m_pPD_ELEC_SYSTEM->isNull("DURSINCEHEATANNOUNCE",1))
    {
      Message << "DURSINCEHEATANNOUNCE( should be more or less " << DurSA << ") = " << m_pPD_ELEC_SYSTEM->getDURSINCEHEATANNOUNCE(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DURSINCEHEATANNOUNCE is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }

    if (!m_pPD_ELEC_SYSTEM->isNull("DURSINCESTARTOFHEAT",1))
    {
      Message << "DURSINCESTARTOFHEAT( should be more or less " << DurSS << ") = " << m_pPD_ELEC_SYSTEM->getDURSINCESTARTOFHEAT(1) << endl;
    }
    else
    {
      Message << "INFO:\n  DURSINCESTARTOFHEAT is not set in PD_ELEC_SYSTEM." << endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_ELEC_SYSTEM was not successfull"<<endl;
    TestCode = false;
  }

  //delete databse objects
  if (m_pPD_ELEC_SYSTEM) { delete m_pPD_ELEC_SYSTEM; m_pPD_ELEC_SYSTEM = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Power use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Power use case failed",1);
  RetValue = true;

  return RetValue;
}

//Dipesh------------
bool CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::handleLFTapChangeRDY(CEventMessage& Event, long status)//Dipesh------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;


  long Status = 0;
  double durSinceA = 0.0; 
  double durSinceH = 0.0; 
  double ElecEgy = 0.0;
  CDateTime DATECHANGE;
  

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPD_ELEC_TAPCH* m_pPD_ELEC_TAPCH = 0;
  CPDL_HEAT_DATA* m_pPDL_HEAT_DATA = 0;
  

  //Initialise database objects
  if (pConnection)
  {
    m_pPD_ELEC_TAPCH = new CPD_ELEC_TAPCH(pConnection);
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
  }

  setpDM_Interface(Event.getSender(),DM::PRODUCT);
  double elecegy   = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::ElecCons);
  long volttap1     = m_pDM_Interface->getLong(RecProductID.c_str(), DATA::VoltTapNo);
    
  setpDM_Interface(Event.getSender(),DM::PRODUCT);
  double DurSinceA = getDurationSince(m_pDM_Interface, RecProductID.c_str(),DATA::HeatAnnounceTime);
  double DurSinceS = getDurationSince(m_pDM_Interface, RecProductID.c_str(),DATA::HeatStartTime);

  setpDM_Interface(Event.getSender(),DM::PLANT);
  long volttap2  = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::VoltTapNo);
  long impcurve = m_pDM_Interface->getLong(DEF_PLANT::Furnace, DATA::EltrdRegCurve);

  Message << "\nPD_ELEC_TAPCH" << endl;
  if (m_pPD_ELEC_TAPCH->select(RecPlant,DATECHANGE,RecTreatID,RecHeatID))
  {
    if (!m_pPD_ELEC_TAPCH->isNull("TAPCHANGERSTATUS",1))
    {
      if (m_pPD_ELEC_TAPCH->getTAPCHANGERSTATUS(1) == Status)
      Message << "TAPCHANGERSTATUS = " << m_pPD_ELEC_TAPCH->getTAPCHANGERSTATUS(1) << endl;
      else
      {
        Message << "ERROR:\n  TAPCHANGERSTATUS is not equal "<< Status;
        Message << " it is " << m_pPD_ELEC_TAPCH->getTAPCHANGERSTATUS(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  TAPCHANGERSTATUS is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }
    if ( volttap2 == DEF::Inv_Long )
      volttap2 = 0;
    if (!m_pPD_ELEC_TAPCH->isNull("VOLTTAP",1))
    {
      if (m_pPD_ELEC_TAPCH->getVOLTTAP(1) == volttap2)
      Message << "VOLTTAP = " << m_pPD_ELEC_TAPCH->getVOLTTAP(1) << endl;
      else
      {
        Message << "ERROR:\n  VOLTTAP is not equal "<< volttap2;
        Message << " it is " << m_pPD_ELEC_TAPCH->getVOLTTAP(1) << endl;
          TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  VOLTTAP is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }

    if (!m_pPD_ELEC_TAPCH->isNull("IMPCURVE",1))
    {
      if (m_pPD_ELEC_TAPCH->getIMPCURVE(1) == impcurve)
      Message << "IMPCURVE = " << m_pPD_ELEC_TAPCH->getIMPCURVE(1) << endl;
      else
      {
        Message << "ERROR:\n  IMPCURVE is not equal "<< impcurve;
        Message << " it is " << m_pPD_ELEC_TAPCH->getIMPCURVE(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  IMPCURVE is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }
    if (!m_pPD_ELEC_TAPCH->isNull("DURSINCEHEATANNOUNCE",1))
    {
      if (m_pPD_ELEC_TAPCH->getDURSINCEHEATANNOUNCE(1) == durSinceA)
      Message << "DURSINCEHEATANNOUNCE = " << m_pPD_ELEC_TAPCH->getDURSINCEHEATANNOUNCE(1) << endl;
      else
      {
        Message << "ERROR:\n  DURSINCEHEATANNOUNCE is not equal "<< durSinceA;
        Message << " it is " << m_pPD_ELEC_TAPCH->getDURSINCEHEATANNOUNCE(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  DURSINCEHEATANNOUNCE is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }
    if (!m_pPD_ELEC_TAPCH->isNull("DURSINCESTARTOFHEAT",1))
    {
      if (m_pPD_ELEC_TAPCH->getDURSINCESTARTOFHEAT(1) == durSinceH)
      Message << "DURSINCESTARTOFHEAT = " << m_pPD_ELEC_TAPCH->getDURSINCESTARTOFHEAT(1) << endl;
      else
      {
        Message << "ERROR:\n  DURSINCESTARTOFHEAT is not equal "<< durSinceH;
        Message << " it is " << m_pPD_ELEC_TAPCH->getDURSINCESTARTOFHEAT(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  DURSINCESTARTOFHEAT is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }
    if (!m_pPD_ELEC_TAPCH->isNull("ELEC_EGYTOT",1))
    {
      if (m_pPD_ELEC_TAPCH->getELEC_EGYTOT(1) == ElecEgy)
      Message << "ELEC_EGYTOT = " << m_pPD_ELEC_TAPCH->getELEC_EGYTOT(1) << endl;
      else
      {
        Message << "ERROR:\n  ELEC_EGYTOT is not equal "<< ElecEgy;
        Message << " it is " << m_pPD_ELEC_TAPCH->getELEC_EGYTOT(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  ELEC_EGYTOT is not set in PD_ELEC_TAPCH"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_ELEC_TAPCH was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPDL_HEAT_DATA" << endl;
  if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
  {
    if (!m_pPDL_HEAT_DATA->isNull("LASTTRAFOTAP",1))
    {
      if (m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) == volttap1)
      Message << "LASTTRAFOTAP = " << m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) << endl;
      else
      {
        Message << "ERROR:\n  LASTTRAFOTAP is not equal "<< volttap1;
        Message << " it is " << m_pPDL_HEAT_DATA->getLASTTRAFOTAP(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  LASTTRAFOTAP is not set in PDL_HEAT_DATA"<<endl;
      TestCode = false;
    }
  }
  else 
  {
    Message << "ERROR:\n  The selection from PDL_HEAT_DATA was not successfull"<<endl;
    TestCode = false;
  }

  //delete databse objects
  if (m_pPD_ELEC_TAPCH) { delete m_pPD_ELEC_TAPCH; m_pPD_ELEC_TAPCH = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}
void CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_SignalsAndMeasurementsHandling::deleteDBClasses()
{
}

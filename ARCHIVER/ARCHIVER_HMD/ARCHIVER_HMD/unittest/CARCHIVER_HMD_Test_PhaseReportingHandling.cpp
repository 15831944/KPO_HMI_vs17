#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_PhaseReportingHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"


CARCHIVER_HMD_Test_PhaseReportingHandling::~CARCHIVER_HMD_Test_PhaseReportingHandling()
{
  if (m_pHeatStatusContainer) { delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}
}

CARCHIVER_HMD_Test_PhaseReportingHandling::CARCHIVER_HMD_Test_PhaseReportingHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
  m_pHeatStatusContainer = new CHeatStatusContainer(pConnection);
}

bool CARCHIVER_HMD_Test_PhaseReportingHandling::handleHMDPhaseReportRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  std::string CustHeatID;
  double Amount;
  bool TestCode = true;
  std::string MsgRDY(".RDY");

  CPDH_HEAT_DATA_PHASE* m_pPDH_Heat_Data_Phase = 0;
  CGC_Phase* m_pGC_Phase = 0;
  CPP_HEAT_PLANT* m_pPP_Heat_Plant = 0;
  CPP_HEAT* m_pPP_Heat = 0;

  long PhaseNo = -1;
  long lRows = 0;
  if (pConnection)
  {
    m_pPDH_Heat_Data_Phase = new CPDH_HEAT_DATA_PHASE(pConnection);
    m_pGC_Phase = new CGC_Phase(pConnection);
    m_pPP_Heat_Plant = new CPP_HEAT_PLANT(pConnection);
    m_pPP_Heat = new CPP_HEAT(pConnection);
  }

  setpDM_Interface(ServerTask,DM::PRODUCT);
  std::string PhaseReportName = m_pDM_Interface->getString(ProductID.c_str(),DATA::PhaseAct);
  // get the PhaseNo
  Message << "\nGC_PHASE" << endl;
  if (m_pGC_Phase->select(RecPlant, PhaseReportName, CSMC_DBData::unspecLong))
  {
    if (!m_pGC_Phase->isNull("L1_PHASE_NO", 1))
    {
      PhaseNo = m_pGC_Phase->getL1PhaseNo(1);
      Message << "PhaseNo("<< PhaseReportName <<") = " << PhaseNo << endl;
    }
    else
    {
      log("ERROR: L1_PHASE_NO is not set for this Phase!",0);
      TestCode = false;
    }
  }
  else
  {
    Message << "INFO: Actual phase is not defined for the actual plant" << endl;
    TestCode = false;
  }
  // get the last Phase from DB
  if (TestCode)
  {
if (PhaseReportName == DEF_HMD_PHASES::StartMonoLime || PhaseReportName == DEF_HMD_PHASES::StartMonoCarb || PhaseReportName == DEF_HMD_PHASES::MainPhase)
  {
    Message << "\nPP_HEAT" <<endl;
    if(m_pPP_Heat_Plant->select(RecHeatID,RecTreatID,RecPlant))
    {
      if(!m_pPP_Heat_Plant->isNull("HEATID_CUST",1))
      CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);
      else 
      {
      Message << "ERROR:\n The CustHeatID was not set in the PP_Heat_Plant" <<endl;
      TestCode = false;
      }
      if(m_pPP_Heat->select(CustHeatID))
      {
        if (PhaseReportName == DEF_HMD_PHASES::StartMonoLime)
        {
        if (!m_pPP_Heat->isNull("HEATSTATORDER",1))
          {
            if (m_pPP_Heat->getHEATSTATORDER(1) == m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::LimeBlow))
              Message <<"HEATSTATORDER (" << m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::LimeBlow)<< ") = "<<m_pPP_Heat->getHEATSTATORDER(1)<<endl;
            else
              {
                Message <<"ERROR:\n The HEATSTATORDER in PP_HEAT is different from the value of m_pHeatStatusContainer("<< PhaseReportName <<")" <<endl;
               }
          }
        else
        {
          Message <<"ERROR:\n The HEATSTATORDER was not set in PP_HEAT" << endl;
          TestCode = false;
        }  
        }  
        else if (PhaseReportName == DEF_HMD_PHASES::StartMonoCarb)
        {
        if (!m_pPP_Heat->isNull("HEATSTATORDER",1))
          {
            if (m_pPP_Heat->getHEATSTATORDER(1) == m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::CarbideBlow))
              Message <<"HEATSTATORDER (" << m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::CarbideBlow) << ") = "<<m_pPP_Heat->getHEATSTATORDER(1)<<endl;
            else
              {
                Message <<"ERROR:\n The HEATSTATORDER in PP_HEAT is different from the value of m_pHeatStatusContainer(" << PhaseReportName << ")" <<endl;
               }
          }
        else
        {
          Message <<"ERROR:\n The HEATSTATORDER was not set in PP_HEAT" << endl;
          TestCode = false;
        }  
        }    
        else if (PhaseReportName == DEF_HMD_PHASES::MainPhase)
        {
        if (!m_pPP_Heat->isNull("HEATSTATORDER",1))
          {
            if (m_pPP_Heat->getHEATSTATORDER(1) == m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::MagnesBlow))
              Message <<"HEATSTATORDER (" << m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::MagnesBlow) << ") = "<<m_pPP_Heat->getHEATSTATORDER(1)<<endl;
            else
              {
                Message <<"ERROR:\n The HEATSTATORDER in PP_HEAT is different from the value of m_pHeatStatusContainer(" << PhaseReportName << ")" <<endl;
               }
          }
        else
        {
          Message <<"ERROR:\n The HEATSTATORDER was not set in PP_HEAT" << endl;
          TestCode = false;
        }  
        }
      }
      else
      {
      Message <<"ERROR:\n The CustHeatID was not set in PP_HEAT" <<endl;
      TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n The selection from PP_HEAT_PLANT was not successful" << endl;
      TestCode = false;
    }
  }
    Message << "\nPDH_Heat_Data_Phase" << endl;

    if (m_pPDH_Heat_Data_Phase->selectOrderByStartTime(RecPlant, RecHeatID, RecTreatID))
    {
        lRows = m_pPDH_Heat_Data_Phase->getLastRow();

       if(m_pPDH_Heat_Data_Phase->isNull("END_TIME",lRows))
		  {
        Message <<"\nActual Phase:" << endl;
        Message << "START_TIME( now ) = " << m_pPDH_Heat_Data_Phase->getSTART_TIME(lRows) << endl;
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_CARBIDE", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_CARBIDE(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_CARBIDE (0)  = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_CARBIDE (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_LIME", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_LIME(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_LIME (0) = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_LIME (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_MG", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_MG(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_MG (0) = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_MG (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("RES_PHASENO", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getRES_PHASENO(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "RES_PHASENO = " << Amount << endl;
		     }
		    else
		    {      
          Message << "ERROR:\n  RES_PHASENO is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }

        
        Message <<"\nPrevious Phase:" << endl;
        Message <<"START_TIME(less than END_TIME) = "<<m_pPDH_Heat_Data_Phase->getSTART_TIME(lRows - 1)<<endl;
        Message <<"END_TIME(now) = " <<m_pPDH_Heat_Data_Phase->getEND_TIME(lRows - 1) <<endl;
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_CARBIDE", lRows - 1))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_CARBIDE(lRows - 1);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_CARBIDE   = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_CARBIDE (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_LIME", lRows - 1))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_LIME(lRows - 1);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_LIME  = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_LIME (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_MG", lRows - 1))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_MG(lRows - 1);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_MG  = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_MG (0) is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("RES_PHASENO", lRows - 1))
		    {
           Amount = m_pPDH_Heat_Data_Phase->getRES_PHASENO(lRows - 1);
           Message << "RES_PHASENO = " << Amount << endl;
		     }
		    else
		    {      
          Message << "ERROR:\n  RES_PHASENO is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
      }
       else 
      {
          Message << "\nEND_TIME(now) = " << m_pPDH_Heat_Data_Phase->getEND_TIME(lRows) << endl;
		  
        if(!m_pPDH_Heat_Data_Phase->isNull("DURATION", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getDURATION(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "DURATION = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  DURATION is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_CARBIDE", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_CARBIDE(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_CARBIDE = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_CARBIDE is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_LIME", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_LIME(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_LIME = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_LIME is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
        if(!m_pPDH_Heat_Data_Phase->isNull("INJ_MG", lRows))
		    {
          Amount = m_pPDH_Heat_Data_Phase->getINJ_MG(lRows);
          if (Amount == DEF::Inv_Double)
           {
             Amount = 0;
           }
          Message << "INJ_MG = " << Amount << endl;
		    }
		    else
		    {      
          Message << "ERROR:\n  INJ_MG is not set in PDH_Heat_Data_Phase" << endl;
			    TestCode = false;
		    }
     
     }
    }
    else
    {
      Message << "ERROR:\n  PDH_Heat_Data_Phase, select for HeatID: " << RecHeatID << ", TreatID: "
              << RecTreatID << ", PLANT: " << RecPlant << " failed!\n";
      TestCode = false;
    }
    }
  

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (m_pPDH_Heat_Data_Phase) { delete m_pPDH_Heat_Data_Phase; m_pPDH_Heat_Data_Phase = 0;}
  if (m_pGC_Phase) { delete m_pGC_Phase; m_pGC_Phase = 0;}
  if (m_pPP_Heat_Plant) { delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
  if (m_pPP_Heat) { delete m_pPP_Heat; m_pPP_Heat = 0;}

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Phase Report use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Phase Report use case failed",1);
  RetValue = true;
  return RetValue;
}


void CARCHIVER_HMD_Test_PhaseReportingHandling::initDBClasses()
{
}

void CARCHIVER_HMD_Test_PhaseReportingHandling::deleteDBClasses()
{
}

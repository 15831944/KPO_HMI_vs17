
//Dipesh--------------
#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_LF_Test_TreatmentHandling.h"
#include "CARCHIVER_LF_Test_Task.h"


CARCHIVER_LF_Test_TreatmentHandling::~CARCHIVER_LF_Test_TreatmentHandling()
{
}

CARCHIVER_LF_Test_TreatmentHandling::CARCHIVER_LF_Test_TreatmentHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_LF_Test_Task::getInstance()->getpConnection();

  m_LadlePartCode.push_back("LB");
  m_LadlePartCode.push_back("LW");
  m_LadlePartCode.push_back("PP1");
  m_LadlePartCode.push_back("PP2");
  m_LadlePartCode.push_back("SG");
  m_LadlePartCode.push_back("BP");
  m_LadlePartCode.push_back("UN");
  m_LadlePartCode.push_back("LN");
  
  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);

}



bool CARCHIVER_LF_Test_TreatmentHandling::handleLFHeatAnnouncementRDY(CEventMessage& Event)//Dipesh--------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecProductID = Event.getProductID();
  std::string RecPlantID   = Event.getPlantID();
  std::string RecOrderID = Event.getOrderID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  bool TestCode = true;
  int ProdPrac = 0;
  int iCountOfPPData = 0;
  int iCountOfPDPPData = 0;
  long HeatStatOrder = 0;
  std::string CustHeatID;
  std::string strSteelGradeCode;
  CDateTime now;
  long ActualWeek = 0;
  long ActualMonth = 0;


  CPD_HEATDATA* m_pPD_HeatData = 0;
  CPP_ORDER* m_pPP_ORDER = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CPD_ACTION* m_pPD_ACTION = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_GRADE_PRODPRAC* m_pPP_Grade_ProdPrac = 0;
  CPP_HEAT* m_pPP_HEAT = 0;
  CPDL_HEAT_DATA* m_pPDL_HEAT_DATA = 0;
  CPD_HEAT_DATA_PRODPRAC* m_pPD_HEAT_DATA_PRODPRAC;
  CGC_Plant_Container* m_pPlantID_Interpreter;
  CPD_PRETREATDATA* m_pPD_PRETREATDATA;
  CGC_HEAT_STAT* m_pGC_HEAT_STAT = 0;

  if (pConnection)
  {
    m_pPD_HeatData = new CPD_HEATDATA(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pPP_ORDER = new CPP_ORDER(pConnection);
    m_pPD_ACTION = new CPD_ACTION(pConnection);
    m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
    m_pPP_HEAT = new CPP_HEAT(pConnection);
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
    m_pPD_HEAT_DATA_PRODPRAC = new CPD_HEAT_DATA_PRODPRAC(pConnection);
    m_pPlantID_Interpreter = new CGC_Plant_Container(pConnection);
    m_pPP_Grade_ProdPrac = new CPP_GRADE_PRODPRAC(pConnection);
    m_pPD_PRETREATDATA = new CPD_PRETREATDATA(pConnection);
    m_pGC_HEAT_STAT = new CGC_HEAT_STAT(pConnection);
  }

  std::string LadleType;
  std::string LadleNo;
  if (m_pGC_HEAT_STAT->select(RecPlant, DEF_GC_HEAT_STAT::Announced))
    HeatStatOrder = m_pGC_HEAT_STAT->getHEATSTATORDER(1);
  else
    HeatStatOrder = -1;

  Message << "\nPD_PRETREATDATA" << endl;
  if(m_pPD_PRETREATDATA->select(RecHeatID))
  {
    if(!m_pPD_PRETREATDATA->isNull("HEATSTATORDER",1))
    {
      if(m_pPD_PRETREATDATA->getHEATSTATORDER(1) == HeatStatOrder)
      {
        Message << "HEATSTATORDER(" << HeatStatOrder <<") = " << m_pPD_PRETREATDATA->getHEATSTATORDER(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  HEATSTATORDER is not equal to " << HeatStatOrder << ". It is "<<m_pPD_PRETREATDATA->getHEATSTATORDER(1)<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  HEATSTATORDER is not set in PD_HEATDATA"<<endl;
      TestCode = false;
    }
  
    if(!m_pPD_PRETREATDATA->isNull("LASTPLANT",1))
    {
      Message << "LASTPLANT = " << m_pPD_PRETREATDATA->getLASTPLANT(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  LASTPLANT is not set in PD_HEATDATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_PRETREATDATA was not successfull for HeatId = "<< RecHeatID <<endl;
    TestCode = false;
  }

  Message << "\nPD_HEATDATA" << endl;
  if(m_pPD_HeatData->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_HeatData->isNull("TREATSTART_ACT",1))
    {
      Message << "TREATSTART_ACT(now) = " << m_pPD_HeatData->getTREATSTART_ACT(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  TREATSTART_ACT is not set in PD_HEATDATA"<<endl;
      TestCode = false;
    }
  
    LadleType = m_pPD_HeatData->getLADLETYPE(1);
    LadleNo   = m_pPD_HeatData->getLADLENO(1);
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_HEATDATA was not successfull"<<endl;
    TestCode = false;
  }
  
  Message <<"\nPP_HEAT_PLANT" << endl;
  if(m_pPP_HEAT_PLANT->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPP_HEAT_PLANT->isNull("ACTTREATSTART",1))
    {
      Message << "ACTTREATSTART(now) = " << m_pPP_HEAT_PLANT->getACTTREATSTART(1) << endl;
      CustHeatID = m_pPP_HEAT_PLANT->getHEATID_CUST(1);
    }
    else
    {
      Message << "ERROR:\n  ACTTREATSTART is not set in PP_HEAT_PLANT"<<endl;
      TestCode = false;
    }
  }
  else 
  {
    Message << "ERROR:\n  The selection from PP_HEAT_PLANT was not successfull"<<endl;
    TestCode = false;
  }
  
  Message << "\nPP_HEAT" << endl;
  if(m_pPP_HEAT->select(CustHeatID))
  {
    if(!m_pPP_HEAT->isNull("HEATSTATORDER",1))
    {
      // remove ".RDY" - the special Message extension;
      std::string EventMsg = Event.getMessage();
      EventMsg = EventMsg.substr( 0, EventMsg.length()-4 );

      if(m_pPP_HEAT->getHEATSTATORDER(1) == HeatStatOrder)
      {
        Message << "HEATSTATORDER(" << HeatStatOrder <<") = " << m_pPP_HEAT->getHEATSTATORDER(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  HEATSTATORDER is not equal to " << HeatStatOrder << ". It is "<<m_pPP_HEAT->getHEATSTATORDER(1)<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  HEATSTATORDER is not set in PP_HEAT"<<endl;
      TestCode = false;
    }

    if(!m_pPP_HEAT->isNull("ROUTECODEACT",1))
    {
      Message << "ROUTECODEACT(\"L1\") = " << m_pPP_HEAT->getROUTECODEACT(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  ROUTECODEACT is not set in PP_HEAT"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PP_HEAT was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPD_ACTION" << endl;
  if(m_pPD_ACTION->select(RecHeatID, RecTreatID, RecPlant, DEF_GC_ACTION::HeatAnnounce))
  {
    if(!m_pPD_ACTION->isNull("ACTIONNAME", 1))
		{
      Message << "ACTIONNAME(Heat Announce) = " << m_pPD_ACTION->getACTIONNAME(1) << endl;
		}
    else
    {  
      Message << "ERROR:\n  ACTIONNAME is not set in PD_ACTION" << endl;
			TestCode = false;
    } 
    
    if(!m_pPD_ACTION->isNull("ACTIONSTATUS", 1))
		{
      Message << "ACTIONSTATUS(0) = " << m_pPD_ACTION->getACTIONSTATUS(1) << endl;
		}
    else
    {
      Message << "ERROR:\n  ACTIONSTATUS is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("DURSINCEHEATANNOUNCEMENT", 1))
		{
      double DurSinceAnn = m_pPD_ACTION->getDURSINCEHEATANNOUNCEMENT(1);
      Message << "DURSINCEHEATANNOUNCEMENT(0) = " << DurSinceAnn << endl;
		}
    else
    {
      Message << "ERROR:\n  DURSINCEHEATANNOUNCEMENT is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("DURSINCESTARTOFHEAT", 1))
		{
      double DurSinceStart = m_pPD_ACTION->getDURSINCESTARTOFHEAT(1);
      Message << "DURSINCESTARTOFHEAT(0) = " << DurSinceStart << endl;
		}
    else
    {
      Message << "ERROR:\n  DURSINCESTARTOFHEAT is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("ELECEGY", 1))
		{
      Message << "ELECEGY(0) = " << m_pPD_ACTION->getELECEGY(1) << endl;
		}
    else
    {
      Message << "ERROR:\n  ELECEGY is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("N2_MOMENT", 1))
    {
      double NitroMom = m_pPD_ACTION->getN2_MOMENT(1);
      Message << "N2_MOMENT(0) = " << NitroMom << endl;     
    }
    else
    {
      Message << "ERROR:\n  N2_MOMENT is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("O2_MOMENT", 1))
    {
      double OxyMom = m_pPD_ACTION->getO2_MOMENT(1);
      Message << "O2_MOMENT(0) = " << OxyMom << endl;
    }
    else
    {
      Message << "ERROR:\n  O2_MOMENT is not set in PD_ACTION" << endl;
			TestCode = false;
    }

    if(!m_pPD_ACTION->isNull("AR_MOMENT", 1))
    {
      double ArMom = m_pPD_ACTION->getAR_MOMENT(1);
      Message << "AR_MOMENT(0) = " << ArMom << endl;
    }
    else
    {
      Message << "ERROR:\n  AR_MOMENT is not set in PD_ACTION" << endl;
			TestCode = false;
    }

  }
  else
  {
    Message << "ERROR:\n  No any entry in PD_ACTION for Heat Announcement" << endl;
    TestCode = false;
  }

  Message << "\nPD_REPORT" << endl;
  if (m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_Report->isNull("ANNOUCETIME", 1))
	  {
      Message << "ANNOUCETIME(now) = " << m_pPD_Report->getANNOUCETIME(1) << endl;
      
	  }
    else
    {
      Message << "ERROR:\n  ANNOUCETIME is not set in PD_Report" << endl;
		  TestCode = false;
    }
    
    if(!m_pPD_Report->isNull("HEATASSIGNMENTDATE", 1))
	  {
      Message << "HEATASSIGNMENTDATE(now) = " << m_pPD_Report->getHEATASSIGNMENTDATE(1) << endl;
	  }
    else
    {
      Message << "ERROR:\n  HEATASSIGNMENTDATE is not set in PD_Report" << endl;
		  TestCode = false;
    }
    
    if(!m_pPD_Report->isNull("TREATSTART_ACT", 1))
	  {
      Message << "TREATSTART_ACT(now) = " << m_pPD_Report->getTREATSTART_ACT(1) << endl;
	  }
    else
    {
      Message << "ERROR:\n  TREATSTART_ACT is not set in PD_Report" << endl;
		  TestCode = false;
    }
    
    if(!m_pPD_Report->isNull("WEEKNO", 1))
	  {
      Message << "WEEKNO(ActualWeek) = " << m_pPD_Report->getWEEKNO(1) << endl;
	  }
    else
    {
      Message << "ERROR:\n  WEEKNO is not set in PD_Report" << endl;
		  TestCode = false;
    }
    
    if(!m_pPD_Report->isNull("MONTHNO", 1))
	  {
      Message << "MONTHNO(ActualMonth) = " << m_pPD_Report->getMONTHNO(1) << endl;
	  }
    else
    {
      Message << "ERROR:\n  MONTHNO is not set in PD_Report" << endl;
		  TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  No any entry in PD_REPORT for Heat Announcement" << endl;
    TestCode = false;
  }

  // test update/insert of PDL_Heat_Data
  //
  if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
  {

    std::string ActPlant  = m_pPlantID_Interpreter->getPlantName(RecPlantID);
    long ActPlantNo = m_pPlantID_Interpreter->getPlantNo(RecPlantID);

    // update/insert from PD_HEAT_DATA_PRODPRAC
    //

    if (m_pPD_HEAT_DATA_PRODPRAC->select(RecPlant, RecTreatID, RecHeatID, CSMC_DBData::unspecString))
    {
      iCountOfPDPPData = m_pPD_HEAT_DATA_PRODPRAC->getLastRow();
      if(m_pPP_ORDER->select(RecOrderID))
      {
        Message << "\nPP_ORDER"<<endl;
        if(!m_pPP_ORDER->isNull("STEELGRADECODE",1))
        {
          strSteelGradeCode = m_pPP_ORDER->getSTEELGRADECODE(1);
          Message << "STEELGRADECODE = " + strSteelGradeCode << endl;
        }
        else
        {
          Message << "ERROR:\n  STEELGRADECODE was not found in PP_HEAT for ProdID = " + RecProductID << endl;
          TestCode = false;
        }
        Message << "\nPP_GRADE_PRODPRAC"<<endl;
        if(m_pPP_Grade_ProdPrac->select(strSteelGradeCode, RecPlant, CSMC_DBData::unspecString))
        {
          iCountOfPPData = m_pPP_Grade_ProdPrac->getLastRow();
          Message << iCountOfPPData << " Rows found in PP_GRADE_PRODPRAC for Steelgradecode = " + strSteelGradeCode<<endl;
        }
        else
        {
          Message << "ERROR:\n  No any data found in PP_GRADE_PRODPRAC for SteelGradeCode = " + strSteelGradeCode<<endl;
          TestCode = false;
        }
        
        Message << "\nPD_HEAT_DATA_PRODPRAC & PDL_HEAT_DATA" << endl;
        if(iCountOfPDPPData == iCountOfPPData)
        {
          for( int i = 1; i <= iCountOfPPData; ++i)
          {
            std::string DescrPP = m_pPD_HEAT_DATA_PRODPRAC->getDESCR_PP(i);
            if (DescrPP == "Treatment") 
            {
              if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
              else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);
              /*if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_TREAT",1))
              {
                Message << "PRODPRAC_TREAT(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_TREAT(1) << endl;
              }
              else
              {
                Message << "ERROR:\n  PRODPRAC_TREAT is not set in PDL_HEAT_DATA"<<endl;
                TestCode = false;
              }*/
            }
            else if (DescrPP == "Restriction") 
            {
              if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
              else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);
              if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_RESTRI",1))
              {
                Message << "PRODPRAC_RESTRI(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_RESTRI(1) << endl;
              }
              else
              {
                Message << "ERROR:\n  PRODPRAC_RESTRI is not set in PDL_HEAT_DATA"<<endl;
                TestCode = false;
              }
            }
            else if (DescrPP == "Parameter") 
            {
              if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
              else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
                ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);
              if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_PARA",1))
              {
                Message << "PRODPRAC_PARA(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_PARA(1) << endl;
              }
              else
              {
                Message << "ERROR:\n  PRODPRAC_PARA is not set in PDL_HEAT_DATA"<<endl;
                TestCode = false;
              }
            }
          }
        }
        else
        {
          Message << "ERROR:\n  The counts of the Rows for SteelGradeCode = "+strSteelGradeCode+" in PP_GRADE_PRODPRAC ";
          Message << "& PD_HEAT_DATA_PRODPRAC are not equal" << endl;
          TestCode = false;
        }
      }
      else
      {
        Message << "ERROR:\n  No any entry for OrderID = " + RecOrderID + " was found in PP_ORDER"<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "\nPD_HEAT_DATA_DRODPRAC\nERROR:\n  No Data found for actual Heat" << endl;
      std::string SearchKey  = RecHeatID + " " + RecTreatID;
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PD_HEAT_DATA_PRODPRAC");
    }
  }

  if (m_pPD_HeatData) { delete m_pPD_HeatData; m_pPD_HeatData = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_Grade_ProdPrac) { delete m_pPP_Grade_ProdPrac; m_pPP_Grade_ProdPrac = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  if (m_pPD_HEAT_DATA_PRODPRAC) { delete m_pPD_HEAT_DATA_PRODPRAC; m_pPD_HEAT_DATA_PRODPRAC = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPlantID_Interpreter) { delete m_pPlantID_Interpreter; m_pPlantID_Interpreter = 0;}
  if (m_pPD_ACTION) { delete m_pPD_ACTION; m_pPD_ACTION = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pPD_PRETREATDATA) { delete m_pPD_PRETREATDATA; m_pPD_PRETREATDATA = 0;}
  if (m_pGC_HEAT_STAT) { delete m_pGC_HEAT_STAT; m_pGC_HEAT_STAT = 0;}


  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Annoncement use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Annoncement use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_TreatmentHandling::handleLFHeatCancelRDY(CEventMessage& Event)//Dipesh-------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;


  std::string CustHeatID;
  std::string DefRouteCode;
  std::string ActRouteCode;
  long OrdStatNo;
  long HeatStartOrder; 

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPP_HEAT* m_pPP_HEAT = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_ORDER* m_pPP_ORDER = 0;

  //Initialise database objects
  if (pConnection)
  {
    m_pPP_HEAT = new CPP_HEAT(pConnection);
    m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
    m_pPP_ORDER = new CPP_ORDER(pConnection);

  }

  Message << "\nPP_HEAT" << endl;
  if(m_pPP_HEAT->select(CustHeatID))
  {
    DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_LF_PLANTS::LF_1_1);
    ActRouteCode = m_pPP_HEAT->getROUTECODEACT(1);
    if (ActRouteCode.length() >= DefRouteCode.length())
    {
      if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
      {
        HeatStartOrder = 64;
        OrdStatNo = 11;
        ActRouteCode.clear();// to avoid the next checking
      }
    }
    DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_LF_PLANTS::LF_2_1);
    if (ActRouteCode.length() >= DefRouteCode.length())
    {
      if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
      {
        HeatStartOrder = 64;
        OrdStatNo = 11;
        ActRouteCode.clear();// to avoid the next checking
      }
    }
    if(!m_pPP_HEAT->isNull("HEATSTATORDER", 1))
    {
      HeatStartOrder = m_pPP_HEAT->getHEATSTATORDER(1);
      if(HeatStartOrder == HeatStartOrder)
      {
        Message << "HEATSTATORDER in PP_HEAT was set to " << HeatStartOrder << endl;
      }
      else
      {
        Message << "ERROR:\n  HEATSTATORDER in PP_HEAT was not set to " << HeatStartOrder << ", it is "<< HeatStartOrder << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  HEATSTATORDER is NULL" << endl;
      TestCode = false;
    }
    if(!m_pPP_HEAT->isNull("PRODORDERID", 1))
    {
      RecOrderID = m_pPP_HEAT->getPRODORDERID(1);
      if(m_pPP_ORDER->select(RecOrderID))
      {
        if(!m_pPP_ORDER->isNull("ORD_STAT_NO", 1))
        {
          OrdStatNo = m_pPP_ORDER->getORD_STAT_NO(1);
          if(OrdStatNo == OrdStatNo)
          {
            Message << "ORD_STAT_NO in PP_ORDER was set to " << OrdStatNo << endl;
          }
          else
          {
            Message << "ERROR:\n  ORD_STAT_NO in PP_ORDER was not set to " << OrdStatNo << ", it is "<< OrdStatNo << endl;
            TestCode = false;
          }
        }
        else
        {
          TestCode = false;        
          Message << "ERROR:\n  ORD_STAT_NO in PP_ORDER is NULL" << endl;
        }
      }
      else
      {
        Message << "ERROR:\n  select * from PP_ORDER where PRODORDERID=" <<RecOrderID<< " was not successfull" << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  PRODORDERID in PP_ORDER is NULL" << endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  Select was not successfull" << endl;
    TestCode = false;
  }
  






  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}
bool CARCHIVER_LF_Test_TreatmentHandling::handleLFHeatStartRDY(CEventMessage& Event)//Dipesh---------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  
  long OrdStatNo;

  std::string CustHeatID;

  bool TestCode = false;

  //declare pointers of DB Classes
  CPP_HEAT *m_pPP_HEAT = 0;
  CPP_HEAT_PLANT *m_pPP_HEAT_PLANT = 0;
  CPP_ORDER *m_pPP_ORDER = 0;

  //initialize pointers of DB Classes
  if (pConnection)
  {
    m_pPP_ORDER = new CPP_ORDER(pConnection);
    m_pPP_HEAT = new CPP_HEAT(pConnection);
    m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
  }

  //get HEATID_CUST from PP_HEAT_PLANT
  if (m_pPP_HEAT_PLANT->select(RecHeatID, RecTreatID, RecPlant))
  {
    CustHeatID = m_pPP_HEAT_PLANT->getHEATID_CUST(1);

    if (!CustHeatID.empty() && CustHeatID !=DEF::Inv_String && m_pPP_HEAT->select(CustHeatID) )
    {
      RecOrderID = m_pPP_HEAT->getPRODORDERID(1);
      if (!RecOrderID.empty() && RecOrderID !=DEF::Inv_String && m_pPP_ORDER->select(RecOrderID))
      {
        if(!m_pPP_ORDER->isNull("ORD_STAT_NO",1))
        {
          OrdStatNo = m_pPP_ORDER->getORD_STAT_NO(1);
          if (OrdStatNo == 13)
          {
            Message << "ORD_STAT_NO(13) = " << m_pPP_ORDER->getORD_STAT_NO(1) << endl;
            TestCode = true;
          }
          else
          {
            Message << "ERROR:\n  ORD_STAT_NO is Not Equal TO 13 its "  << OrdStatNo<<endl; 
          }
        }
        else
        {
          Message << "ERROR:\n  ORD_STAT_NO is not set in PP_ORDER"<<endl;
          TestCode = false;
        }
      }
    }
  }

  else
  {
    Message << "ERROR:\n  The selection from PP_HEAT_PLANT was not successfull"<<endl;
    TestCode = false;
  }


  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_TreatmentHandling::handleLFHeatEndRDY(CEventMessage& Event)//Dipesh-------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecPlantID = Event.getPlantID();
  std::string RecOrderID;


  std::string CustHeatID;
  double    ElecEgy;
  double    PowerOnDur;
  
  

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPP_HEAT* m_pPP_HEAT = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_ORDER* m_pPP_ORDER = 0;
  CPDL_HEAT_DATA* m_pPDL_HEAT_DATA = 0;
  CPD_REPORT* m_pPD_Report = 0;

  //Initialise database objects
  if (pConnection)
    {
      m_pPP_HEAT = new CPP_HEAT(pConnection);
      m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
      m_pPP_ORDER = new CPP_ORDER(pConnection);
      m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
      m_pPD_Report = new CPD_REPORT(pConnection);
    }

  setpDM_Interface(ServerTask,DM::PRODUCT);

  ElecEgy    = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::ElecCons );
  PowerOnDur = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::PowerOnDur);

   Message << "\nPDL_HEAT_DATA" << endl;
    if(!m_pPDL_HEAT_DATA->isNull("ELEC_CONS_TOTAL",1))
    {
      if(m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1) == ElecEgy)
      {
        double EleConTot = m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1);
        Message << "ELEC_CONS_TOTAL(ElecEgy) = " << EleConTot << endl;
      }
      else
      {
        Message << "ERROR:\n  ELEC_CONS_TOTAL is not equal to " << ElecEgy << ". It is "<<m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1)<<endl;
        TestCode = false;
      }
    }
     else
      {
        Message << "ERROR:\n  ELEC_CONS_TOTAL is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    

    if(!m_pPDL_HEAT_DATA->isNull("SPEC_EGY",1))
    {
      if(m_pPDL_HEAT_DATA->getSPEC_EGY(1) == ElecEgy)
      {
         double SpGy = m_pPDL_HEAT_DATA->getSPEC_EGY(1);
         Message << "SPEC_EGY(ElecEgy) = " << SpGy << endl;
      }
      else
      {
        Message << "ERROR:\n  SPEC_EGY is not equal to " << ElecEgy << ". It is "<<m_pPDL_HEAT_DATA->getSPEC_EGY(1)<<endl;
        TestCode = false;
      }
    }
      else
      {
        Message << "ERROR:\n  SPEC_EGY is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    

    if(!m_pPDL_HEAT_DATA->isNull("POWER_ON_DUR",1))
    {
      if(m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1) == PowerOnDur)
      {
      double PowDur = m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1);
      Message << "POWER_ON_DUR(PowerOnDur) = " << PowDur << endl;
     
      }
      else
      { 
      Message << "ERROR:\n  POWER_ON_DUR is not equal to " << PowerOnDur << ". It is "<<m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1)<<endl;
       TestCode = false;
      }
    }
      else
      {
      Message << "ERROR:\n  POWER_ON_DUR is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
      }

  if (m_pPDL_HEAT_DATA->select(RecHeatID,RecTreatID,RecPlantID))
    {
      Message << "RecHeatID = " << m_pPDL_HEAT_DATA->getHEATID(1)<<endl;
      Message << "RecTreatID = " << m_pPDL_HEAT_DATA->getTREATID(1)<<endl;
      Message << "RecPlant = " << m_pPDL_HEAT_DATA->getPLANT(1)<<endl;
    }
    else
    {
      Message << "ERROR:\n PDL_Heat_Data, select for HEATID: " << RecHeatID << ", TREATID: "
              << RecTreatID << ", PLANT: " << RecPlantID << " failed!\n";
      TestCode = false;
    }
    Message << "\nPD_REPORT" << endl;
  if (m_pPD_Report->select(RecHeatID,RecTreatID,RecPlantID))
   {
      if(!m_pPD_Report->isNull("TOTAL_ELEC_EGY",1))
    {
      double ElGy = m_pPD_Report->getTOTAL_ELEC_EGY(1);
      Message << "TOTAL_ELEC_EGY(ElecEgy) = " << ElGy << endl;
     
    }
    else
    {
      Message << "ERROR:\n  TOTAL_ELEC_EGY is not set in PD_Report"<<endl;
      TestCode = false;
    }
   }
    else
  {
    Message << "ERROR:\n  The selection from PD_Report was not successfull"<<endl;
    TestCode = false;
  }

  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}



bool CARCHIVER_LF_Test_TreatmentHandling::handleLFHeatDepartureRDY(CEventMessage& Event)//Dipesh---------------
{
 bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecPlantID = Event.getPlantID();
  std::string RecOrderID;


  std::string CustHeatID;
  CDateTime now;
  double    ElecEgy = 0.0;
  double    PowerOnDur = 0.0;
  std::string LadleNo;
  std::string LadleType;
  

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPP_HEAT* m_pPP_HEAT = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_ORDER* m_pPP_ORDER = 0;
  CPDL_HEAT_DATA* m_pPDL_HEAT_DATA = 0;
  CPDL_CYCL_MEAS_DATA* m_pPDL_CYCL_MEAS_DATA = 0;
  CPD_HEAT_DATA_PRODPRAC* m_pPD_HEAT_DATA_PRODPRAC = 0;
  CPD_LADLE_LIFE_DATA* m_pPD_LADLE_LIFE_DATA = 0;
  CPD_HEATDATA* m_pPD_HeatData = 0;
  CPD_REPORT* m_pPD_Report = 0;
  
  //Initialise database objects
  if (pConnection)
  {
    m_pPP_HEAT = new CPP_HEAT(pConnection);
    m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
    m_pPP_ORDER = new CPP_ORDER(pConnection);
    m_pPDL_HEAT_DATA = new CPDL_HEAT_DATA(pConnection);
    m_pPDL_CYCL_MEAS_DATA = new CPDL_CYCL_MEAS_DATA(pConnection);
    m_pPD_HEAT_DATA_PRODPRAC = new CPD_HEAT_DATA_PRODPRAC(pConnection);
    m_pPD_LADLE_LIFE_DATA = new CPD_LADLE_LIFE_DATA(pConnection);
    m_pPD_HeatData = new CPD_HEATDATA(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
  }
  setpDM_Interface(ServerTask,DM::PRODUCT);

  ElecEgy    = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::ElecCons );
  PowerOnDur = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::PowerOnDur);

    //PDL_Cycl_Meas_Data
    if (m_pPDL_CYCL_MEAS_DATA->selectMax(RecHeatID, RecTreatID, m_PlantID, "ELEC_EGYTOT"))
      ElecEgy    = m_pPDL_CYCL_MEAS_DATA->getELEC_EGYTOT(1);
    else
      ElecEgy    = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::ElecCons );
    
    PowerOnDur = m_pDM_Interface->getDouble(RecProductID.c_str(), DATA::PowerOnDur);
    
    
    Message << "\nPDL_HEAT_DATA" << endl;
  if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
   {
    if(!m_pPDL_HEAT_DATA->isNull("ELEC_CONS_TOTAL",1))
    {
      if(m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1) == ElecEgy)
      {
        double EleConTot = m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1);
        Message << "ELEC_CONS_TOTAL(ElecEgy) = " << EleConTot << endl;
      }
      else
      {
        Message << "ERROR:\n  ELEC_CONS_TOTAL is not equal to " << ElecEgy << ". It is "<<m_pPDL_HEAT_DATA->getELEC_CONS_TOTAL(1)<<endl;
        TestCode = false;
      }
    }
     else
      {
        Message << "ERROR:\n  ELEC_CONS_TOTAL is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    

    if(!m_pPDL_HEAT_DATA->isNull("SPEC_EGY",1))
    {
      if(m_pPDL_HEAT_DATA->getSPEC_EGY(1) == ElecEgy)
      {
         double SpGy = m_pPDL_HEAT_DATA->getSPEC_EGY(1);
         Message << "SPEC_EGY(ElecEgy) = " << SpGy << endl;
      }
      else
      {
        Message << "ERROR:\n  SPEC_EGY is not equal to " << ElecEgy << ". It is "<<m_pPDL_HEAT_DATA->getSPEC_EGY(1)<<endl;
        TestCode = false;
      }
    }
      else
      {
        Message << "ERROR:\n  SPEC_EGY is not set in PDL_Heat_Data"<<endl;
        TestCode = false;
      }
    

    if(!m_pPDL_HEAT_DATA->isNull("POWER_ON_DUR",1))
    {
      if(m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1) == PowerOnDur)
      {
      double PowDur = m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1);
      Message << "POWER_ON_DUR(PowerOnDur) = " << PowDur << endl;
     
      }
      else
      { 
      Message << "ERROR:\n  POWER_ON_DUR is not equal to " << PowerOnDur << ". It is "<<m_pPDL_HEAT_DATA->getPOWER_ON_DUR(1)<<endl;
       TestCode = false;
      }
    }
      else
      {
      Message << "ERROR:\n  POWER_ON_DUR is not set in PDL_Heat_Data"<<endl;
      TestCode = false;
      }
   }
  else
  {
    Message << "ERROR:\n  Failed To Select Data From PDL_HEAT_DATA"<<endl;
    TestCode = false;
  }

 
      Message << "\nPDL_HEAT_DATA" << endl;
  if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
  {
    if (m_pPD_HEAT_DATA_PRODPRAC->select(RecPlant, RecTreatID, RecHeatID, CSMC_DBData::unspecString))
    {
      long ProdPrac = -1;

      for (int i = 1; i <= m_pPD_HEAT_DATA_PRODPRAC->getLastRow(); i++)
      {
        std::string DescrPP = m_pPD_HEAT_DATA_PRODPRAC->getDESCR_PP(i);

        if (DescrPP == "Electric")
        {
          if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_ELEC",1))
          {
            if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
            else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);

            if(m_pPDL_HEAT_DATA->getPRODPRAC_ELEC(1) == ProdPrac)
            {
              Message << "PRODPRAC_ELEC(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_ELEC(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  PRODPRAC_ELEC is not equal to " << ProdPrac << ". It is " << m_pPDL_HEAT_DATA->getPRODPRAC_ELEC(1) <<endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "ERROR:\n  PRODPRAC_ELEC is not set in PDL_HEAT_DATA"<<endl;
            TestCode = false;
          }

        }
        else if (DescrPP == "Restriction") 
        {
          if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_RESTRI",1))
          {
            ProdPrac = -1;

            if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
            else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);

            if(m_pPDL_HEAT_DATA->getPRODPRAC_RESTRI(1) == ProdPrac)
            {
              Message << "PRODPRAC_RESTRI(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_RESTRI(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  PRODPRAC_RESTRI is not equal to " << ProdPrac << ". It is " << m_pPDL_HEAT_DATA->getPRODPRAC_RESTRI(1) <<endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "ERROR:\n  PRODPRAC_RESTRI is not set in PDL_HEAT_DATA"<<endl;
            TestCode = false;
          }

        }
        else if (DescrPP == "Stirring") 
        {
          if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_STIRR",1))
          {
            ProdPrac = -1;

            if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
            else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);

            if(m_pPDL_HEAT_DATA->getPRODPRAC_STIRR(1) == ProdPrac)
            {
              Message << "PRODPRAC_STIRR(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_STIRR(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  PRODPRAC_STIRR is not equal to " << ProdPrac << ". It is " << m_pPDL_HEAT_DATA->getPRODPRAC_STIRR(1) <<endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "ERROR:\n  PRODPRAC_STIRR is not set in PDL_HEAT_DATA"<<endl;
            TestCode = false;
          }

        }
        else if (DescrPP == "Parameter") 
        {
          if(!m_pPDL_HEAT_DATA->isNull("PRODPRAC_PARA",1))
          {
            ProdPrac = -1;

            if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_MOD", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_MOD(i);
            else if (!m_pPD_HEAT_DATA_PRODPRAC->isNull("PRODPRACID_PLAN", i))
              ProdPrac = m_pPD_HEAT_DATA_PRODPRAC->getPRODPRACID_PLAN(i);

            if(m_pPDL_HEAT_DATA->getPRODPRAC_PARA(1) == ProdPrac)
            {
              Message << "PRODPRAC_PARA(" << ProdPrac << ") = " << m_pPDL_HEAT_DATA->getPRODPRAC_PARA(1) << endl;
            }
            else
            {
              Message << "ERROR:\n  PRODPRAC_PARA is not equal to " << ProdPrac << ". It is " << m_pPDL_HEAT_DATA->getPRODPRAC_PARA(1) <<endl;
              TestCode = false;
            }
          }
          else
          {
            Message << "ERROR:\n  PRODPRAC_PARA is not set in PDL_HEAT_DATA"<<endl;
            TestCode = false;
          }

        }
      }
    }
    else
    {
      Message << "INFO:\n  Failed to select data from PD_Heat_Data_Prodprac."<<endl;
    }

    }
  else
    {
      Message << "ERROR:\n  Failed To Select Data From PDL_HEAT_DATA"<<endl;
      TestCode = false;
    }
   
      
  if (!m_pPDL_HEAT_DATA->isNull("LADLE_DEPARTTIME",1))
      Message << "LADLE_DEPARTTIME(now) = " << m_pPDL_HEAT_DATA->getLADLE_DEPARTTIME(1) << endl;
  else
    {
      Message << "ERROR:\n  LADLE_DEPARTTIME is not set in PDL_HEAT_DATA"<<endl;
      TestCode = false;
    }


      
  if (m_pPD_HeatData->select(RecHeatID, RecTreatID, RecPlant))
    {
      if (!m_pPDL_HEAT_DATA->isNull("CARNO",1))
      {
        if (m_pPDL_HEAT_DATA->getCARNO(1) == m_pPD_HeatData->getCARNO(1))
        {
          Message<<"CARNO ("<<m_pPD_HeatData->getCARNO(1)<<") = "<<m_pPDL_HEAT_DATA->getCARNO(1)<<endl;
        } 
        else
        {
          Message<<"ERROR:\n  The CARNO in PDL_HEAT_DATA was different from the one of PD_HeatData."<<endl;
          TestCode = false;
        }
      } 
      else
      {
        Message<<"ERROR:\n  CARNO was not set in PDL_HEAT_DATA."<<endl;
        TestCode = false;
      }
    
   /* else
    {
      Message<<"ERROR:\n  The Data selection from PD_HeatData was not correct."<<endl;
      TestCode = false;
    }*/
  
    std::vector<std::string>::iterator it;
    it = m_LadlePartCode.begin();
    if(m_pPD_HeatData->select(RecHeatID, RecTreatID, RecPlant))
    {
      LadleNo = m_pPD_HeatData->getLADLENO(1);
      LadleType = m_pPD_HeatData->getLADLETYPE(1);
    }
    for (it ; it < m_LadlePartCode.end() ; it++)
    {
      if (m_pPD_LADLE_LIFE_DATA->select(LadleType, LadleNo, *it ))
      {
        if (m_pPDL_HEAT_DATA->select(RecHeatID, RecTreatID, RecPlant))
        {
          long LadleLifeData = m_pPD_LADLE_LIFE_DATA->getLIFE(1);
          std::string LadlePart = m_pPD_LADLE_LIFE_DATA->getLADLEPARTCODE(1);
          if (LadlePart == "LW")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_WALL_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_WALL_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
              Message<<"TAPLADLE_WALL_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_WALL_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_WALL_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_WALL_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "LB")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_BOTTOM_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_BOT_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_BOTTOM_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_BOT_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_BOTTOM_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_BOTTOM_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "BP")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_BOT_PLATE_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_BOT_PLATE_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_BOT_PLATE_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_BOT_PLATE_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_BOT_PLATE_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_BOT_PLATE_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "PP1")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_POROUS_PLUG1_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_POROUS_PLUG1_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_POROUS_PLUG1_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_POROUS_PLUG1_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_POROUS_PLUG1_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_POROUS_PLUG1_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "PP2")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_POROUS_PLUG2_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_POROUS_PLUG2_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_POROUS_PLUG2_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_POROUS_PLUG2_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_POROUS_PLUG2_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_POROUS_PLUG2_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "SG")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_SLIDE_GATE_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_SLIDE_GATE_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_SLIDE_GATE_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_SLIDE_GATE_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_SLIDE_GATE_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_SLIDE_GATE_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "UN")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_UP_NOZZLE_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_UP_NOZZLE_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_UP_NOZZLE_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_UP_NOZZLE_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_UP_NOZZLE_LIFE in PDL_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_UP_NOZZLE_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
          if (LadlePart == "LN")
          {
            if (!m_pPDL_HEAT_DATA->isNull("LADLE_LOW_NOZZLE_LIFE",1))
            {
              if (m_pPDL_HEAT_DATA->getLADLE_LOW_NOZZLE_LIFE(1) == m_pPD_LADLE_LIFE_DATA->getLIFE(1))
                Message<<"LADLE_LOW_NOZZLE_LIFE ("<<LadleLifeData<<") = "<<m_pPDL_HEAT_DATA->getLADLE_LOW_NOZZLE_LIFE(1)<<endl;
              else
                Message << "ERROR:\n  The value of LADLE_LOW_NOZZLE_LIFE in PDF_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
            } 
            else
            {
              Message << "ERROR:\n  LADLE_LOW_NOZZLE_LIFE is not set in PDL_HEAT_DATA"<<endl;
              TestCode = false;
            }
          }
        }
        else
        {
          Message<<"ERROR:\n  The selection from PDL_Heat_Data was not successful."<<endl;
          TestCode = false;
        }
      }

      else
      {
        Message<<"ERROR:\n  The selection from PD_LADLE_LIFE_DATA was not successful."<<endl;
        TestCode = false;
      }
    }
    }
  else
      {
        Message<<"ERROR:\n  The selection from PD_HEATDATA was not successful"<<endl;
        TestCode = false;
      }
  
 
   
  

  
      Message << "\nPD_REPORT" << endl;
    if (m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
    {
     if(!m_pPD_Report->isNull("TOTAL_ELEC_EGY",1))
     {
      if(m_pPD_Report->getTOTAL_ELEC_EGY(1) == ElecEgy)
      {
        double EleConTot = m_pPD_Report->getTOTAL_ELEC_EGY(1);
        Message << "TOTAL_ELEC_EGY(ElecEgy) = " << EleConTot << endl;
      }
      else
      {
        Message << "ERROR:\n  TOTAL_ELEC_EGY is not equal to " << ElecEgy << ". It is "<<m_pPD_Report->getTOTAL_ELEC_EGY(1)<<endl;
        TestCode = false;
      }
    }
     else
      {
        Message << "ERROR:\n  TOTAL_ELEC_EGY is not set in PD_REPORT"<<endl;
        TestCode = false;
      }
   }
    else
      {
        Message << "ERROR:\n  Data selection from PD_REPORT is not right"<<endl;
        TestCode = false;
      }




  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPDL_HEAT_DATA) { delete m_pPDL_HEAT_DATA; m_pPDL_HEAT_DATA = 0;}
  if (m_pPDL_CYCL_MEAS_DATA) { delete m_pPDL_CYCL_MEAS_DATA; m_pPDL_CYCL_MEAS_DATA = 0;}
  if (m_pPD_LADLE_LIFE_DATA) { delete m_pPD_LADLE_LIFE_DATA; m_pPD_LADLE_LIFE_DATA = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_TreatmentHandling::handleLFUpdateAimDepartureTimeRDY(CEventMessage& Event)//Dipesh----------------
{
 bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  std::string DataKey = Event.getDataKey();


  std::string CustHeatID;

  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPP_HEAT* m_pPP_HEAT = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_ORDER* m_pPP_ORDER = 0;
  CPD_HEATDATA* m_pPD_HeatData = 0;
  CPD_REPORT* m_pPD_Report = 0;


  //Initialise database objects
  if (pConnection)
    {
      m_pPP_HEAT = new CPP_HEAT(pConnection);
      m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
      m_pPP_ORDER = new CPP_ORDER(pConnection);
      m_pPD_HeatData = new CPD_HEATDATA(pConnection);
      m_pPD_Report = new CPD_REPORT(pConnection);
  
    }

    
  setpDM_Interface(ServerTask,DM::EVENT);
  CDateTime depTime ;
  depTime.SetTime(m_pDM_Interface->getDate(DataKey.c_str(),DATA::TreatEndAim));

  Message << "\nPD_HEATDATA" << endl;
  if(m_pPD_HeatData->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_HeatData->isNull("TREATEND_MOD",1))
    {
      Message << "TREATEND_MOD("<<depTime.asString()<<") = " << m_pPD_HeatData->getTREATEND_MOD(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  TREATEND_MOD in PD_HEATDATA is NULL"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_HEATDATA was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPD_REPORT" << endl;
  if(m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_Report->isNull("TREATEND_MOD",1))
    {
      Message << "TREATEND_MOD("<<depTime.asString()<<") = " << m_pPD_Report->getTREATEND_MOD(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  TREATEND_MOD in PD_REPORT is NULL"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_REPORT was not successfull"<<endl;
    TestCode = false;
  }
  






  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPD_HeatData) { delete m_pPD_HeatData; m_pPD_HeatData = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_LF_Test_TreatmentHandling::handleLFUpdateAimTemperatureRDY(CEventMessage& Event)//Dipesh-------------
{
  bool RetValue = false;
  std::stringstream Message;
  std::string RecProductID = Event.getProductID();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecPlant = DEF_DB_PLANT::LF;
  std::string RecOrderID;
  std::string DataKey = Event.getDataKey();

  std::string CustHeatID;
  bool TestCode = false;

  //Declare Pointers of DB Classes
  CPP_HEAT* m_pPP_HEAT = 0;
  CPP_HEAT_PLANT* m_pPP_HEAT_PLANT = 0;
  CPP_ORDER* m_pPP_ORDER = 0;
  CPD_HEATDATA* m_pPD_HeatData = 0;
  CPD_REPORT* m_pPD_Report = 0;

  //Initialise database objects
  if (pConnection)
    {
      m_pPP_HEAT = new CPP_HEAT(pConnection);
      m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(pConnection);
      m_pPP_ORDER = new CPP_ORDER(pConnection);
      m_pPD_HeatData = new CPD_HEATDATA(pConnection);
      m_pPD_Report = new CPD_REPORT(pConnection);
  
    }

    setpDM_Interface(ServerTask,DM::EVENT);
  // update PD_HEATDATA
  double AimTemp = m_pDM_Interface->getDouble(DataKey.c_str(),DATA::TempAim);
  
  Message << "\nPD_HEATDATA" << endl;
  if(m_pPD_HeatData->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_HeatData->isNull("AIMTEMP_MOD",1))
    {
      if(m_pPD_HeatData->getAIMTEMP_MOD(1) == AimTemp)
      {
        Message << "AIMTEMP_MOD("<<AimTemp<<") = " << m_pPD_HeatData->getAIMTEMP_MOD(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  AIMTEMP_MOD is not equal to "<<AimTemp<<". It is " << m_pPD_HeatData->getAIMTEMP_MOD(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  AIMTEMP_MOD is not set in PD_HEATDATA"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_HEATDATA was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPD_REPORT" << endl;
  if(m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPD_Report->isNull("AIMTEMP_MOD",1))
    {
      if(m_pPD_Report->getAIMTEMP_MOD(1) == AimTemp)
      {
        Message << "AIMTEMP_MOD("<<AimTemp<<") = " << m_pPD_Report->getAIMTEMP_MOD(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  AIMTEMP_MOD is not equal to "<<AimTemp<<". It is " << m_pPD_Report->getAIMTEMP_MOD(1) << endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  AIMTEMP_MOD is not set in PD_REPORT"<<endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_REPORT was not successfull"<<endl;
    TestCode = false;
  }

  //delete databse objects
  if (m_pPP_HEAT) { delete m_pPP_HEAT; m_pPP_HEAT = 0;}
  if (m_pPP_HEAT_PLANT) { delete m_pPP_HEAT_PLANT; m_pPP_HEAT_PLANT = 0;}
  if (m_pPP_ORDER) { delete m_pPP_ORDER; m_pPP_ORDER = 0;}
  if (m_pPD_HeatData) { delete m_pPD_HeatData; m_pPD_HeatData = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}

void CARCHIVER_LF_Test_TreatmentHandling::initDBClasses()
{
}

void CARCHIVER_LF_Test_TreatmentHandling::deleteDBClasses()
{
}

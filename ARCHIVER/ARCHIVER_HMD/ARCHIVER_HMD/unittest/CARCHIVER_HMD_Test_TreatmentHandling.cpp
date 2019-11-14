#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"

#include "cCBS_StdInitBase.h"
#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdLog_Task.h"

#include "CSMC_RuntimeController.h"
#include "CEventMessageReady.h"

#include "CARCHIVER_HMD_Test_TreatmentHandling.h"
#include "CARCHIVER_HMD_Test_Task.h"



CARCHIVER_HMD_Test_TreatmentHandling::~CARCHIVER_HMD_Test_TreatmentHandling()
{
  if (m_pHeatStatusContainer) { delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}
}

CARCHIVER_HMD_Test_TreatmentHandling::CARCHIVER_HMD_Test_TreatmentHandling(CARCHIVER_Task *Task)
{
  pConnection = CARCHIVER_HMD_Test_Task::getInstance()->getpConnection();

  m_LadlePartCode.push_back("LB");
  m_LadlePartCode.push_back("LW");

  cCBS_StdInitBase::getInstance()->replaceWithEntry("DataManager", "ServerName", TrackerName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry(TrackerName, "ServerTask", ServerTask);
  m_pHeatStatusContainer = new CHeatStatusContainer(pConnection);

}

bool CARCHIVER_HMD_Test_TreatmentHandling::handleHMDHeatAnnouncementRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecProductID = Event.getProductID();
  std::string RecPlantID   = Event.getPlantID();
  std::string RecOrderID = Event.getOrderID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;
  int ProdPrac = 0;
  int iCountOfPPData = 0;
  int iCountOfPDPPData = 0;
  std::string CustHeatID;
  std::string strSteelGradeCode;

  CPD_HEATDATA* m_pPD_HeatData = 0;
  CPP_ORDER* m_pPP_Order = 0;
  CPD_REPORT* m_pPD_Report = 0;
  CPD_ACTION* m_pPD_Action = 0;
  CPP_HEAT_PLANT* m_pPP_Heat_Plant = 0;
  CPP_HEAT* m_pPP_Heat = 0;
  CPDH_HEAT_DATA* m_pPDH_Heat_Data = 0;
  CGC_Plant_Container* m_pPlantID_Interpreter;
  CPD_PRETREATDATA* m_pPD_PretreatData; 
  CPD_LADLE_LIFE_DATA* m_pPD_Ladle_Life_Data;
  

  if (pConnection)
  {
    m_pPD_HeatData = new CPD_HEATDATA(pConnection);
    m_pPD_Report = new CPD_REPORT(pConnection);
    m_pPP_Order = new CPP_ORDER(pConnection);
    m_pPD_Action = new CPD_ACTION(pConnection);
    m_pPP_Heat_Plant = new CPP_HEAT_PLANT(pConnection);
    m_pPP_Heat = new CPP_HEAT(pConnection);
    m_pPDH_Heat_Data = new CPDH_HEAT_DATA(pConnection);
    m_pPlantID_Interpreter = new CGC_Plant_Container(pConnection);
    m_pPD_PretreatData = new CPD_PRETREATDATA(pConnection);
    m_pPD_Ladle_Life_Data = new CPD_LADLE_LIFE_DATA(pConnection);
  }

  std::string LadleType;
  std::string LadleNo;

  std::string LadleTypetest;
  std::string LadleNotest;
// ARCHIVER_GENERAL Funktions
  
  Message << "\nPD_PRETREATDATA" << endl;
  if(m_pPD_PretreatData->select(RecHeatID))
  {
    if(!m_pPD_PretreatData->isNull("HEATSTATORDER",1))
    {
      Message << "HEATSTATORDER = " << m_pPD_PretreatData->getHEATSTATORDER(1) << endl;
    }
    else
    {
      Message << "ERROR:\n  HEATSTATORDER is not set in PD_HEATDATA"<<endl;
      TestCode = false;
    }
    if(!m_pPD_PretreatData->isNull("LASTPLANT",1))
    {
      Message << "LASTPLANT = " << m_pPD_PretreatData->getLASTPLANT(1) << endl;
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
    setpDM_Interface(ServerTask,DM::EVENT);
    LadleType = m_pPD_HeatData->getLADLETYPE(1);
    LadleNo   = m_pPD_HeatData->getLADLENO(1);

    LadleTypetest = m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleType);
    LadleNotest = m_pDM_Interface->getString(DataKey.c_str(), DATA::LadleId);

    if(false)//LadleType != LadleTypetest)
    {
      Message <<"ERROR:\n  LADLETYPE is not right in PD_HEATDATA" <<endl;
      TestCode = false;
    }
    else
    {
      Message << "LADLETYPE = " << m_pPD_HeatData->getLADLETYPE(1) <<endl;
    }
     if(false)//LadleNo != LadleNotest)
    {
      Message <<"ERROR:\n  LADLENO is not right in PD_HEATDATA" <<endl;
      TestCode = false;
    }
    else
    {
      Message << "LADLENO = " << m_pPD_HeatData->getLADLENO(1) <<endl;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_HEATDATA was not successfull"<<endl;
    TestCode = false;
  }
  Message <<"\nPP_HEAT_PLANT" << endl;
  if(m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
  {
    if(!m_pPP_Heat_Plant->isNull("ACTTREATSTART",1))
    {
      Message << "ACTTREATSTART(now) = " << m_pPP_Heat_Plant->getACTTREATSTART(1) << endl;
      CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);
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
  if(m_pPP_Heat->select(CustHeatID))
  {
    if(!m_pPP_Heat->isNull("HEATSTATORDER",1))
    {
      int HeatStatOrder = m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::Announced);

      // remove ".RDY" - the special Message extension;
      std::string EventMsg = Event.getMessage();
      EventMsg = EventMsg.substr( 0, EventMsg.length()-4 );

      if( EventMsg.compare(HMD_EvMsg::evHMDHeatAnnouncementOffline) == 0 )
      {
        HeatStatOrder = 64;
      }

      if(m_pPP_Heat->getHEATSTATORDER(1) == HeatStatOrder)
      {
        Message << "HEATSTATORDER(" << HeatStatOrder <<") = " << m_pPP_Heat->getHEATSTATORDER(1) << endl;
      }
      else
      {
        Message << "ERROR:\n  HEATSTATORDER is not equal to " << HeatStatOrder << ". It is "<<m_pPP_Heat->getHEATSTATORDER(1)<<endl;
        TestCode = false;
      }
    }
    else
    {
      Message << "ERROR:\n  HEATSTATORDER is not set in PP_HEAT"<<endl;
      TestCode = false;
    }
    std::string ActRouteCode = m_pPlantID_Interpreter->getRouteCodeID(RecPlantID);

    if(!m_pPP_Heat->isNull("ROUTECODEACT",1))
    {
      Message << "ROUTECODEACT(" << ActRouteCode << ") = " << m_pPP_Heat->getROUTECODEACT(1) << endl;
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
  if(m_pPD_Action->select(RecHeatID, RecTreatID, RecPlant, 1000))
  {
    if(m_pPD_Action->isNull("ACTIONNAME", 1))
		{
      Message << "ERROR:\n  ACTIONNAME is not set in PD_ACTION" << endl;
			TestCode = false;
		}else
      Message << "ACTIONNAME(Heat Announce) = " << m_pPD_Action->getACTIONNAME(1) << endl;
//--    
    if(m_pPD_Action->isNull("ACTIONSTATUS", 1))
		{
      Message << "ERROR:\n  ACTIONSTATUS is not set in PD_ACTION" << endl;
			TestCode = false;
		}else
      Message << "ACTIONSTATUS(0) = " << m_pPD_Action->getACTIONSTATUS(1) << endl;
//--
    if(m_pPD_Action->isNull("DURSINCEHEATANNOUNCEMENT", 1))
		{
      Message << "ERROR:\n  DURSINCEHEATANNOUNCEMENT is not set in PD_ACTION" << endl;
			TestCode = false;
		}
    else
    {
      double DurSinceAnn = m_pPD_Action->getDURSINCEHEATANNOUNCEMENT(1);
      Message << "DURSINCEHEATANNOUNCEMENT(0) = " << DurSinceAnn << endl;
    }
//--
    if(m_pPD_Action->isNull("DURSINCESTARTOFHEAT", 1))
		{
      Message << "ERROR:\n  DURSINCESTARTOFHEAT is not set in PD_ACTION" << endl;
			TestCode = false;
		}
    else
    {
      double DurSinceStart = m_pPD_Action->getDURSINCESTARTOFHEAT(1);
      Message << "DURSINCESTARTOFHEAT(0) = " << DurSinceStart << endl;
    }
//--
    if(m_pPD_Action->isNull("ELECEGY", 1))
		{
      Message << "ERROR:\n  ELECEGY is not set in PD_ACTION" << endl;
			TestCode = false;
		}else
      Message << "ELECEGY(0) = " << m_pPD_Action->getELECEGY(1) << endl;
  }
  else
  {
    Message << "ERROR:\n  No any entry in PD_ACTION for Heat Announcement" << endl;
    TestCode = false;
  }


  
  Message << "\nPD_REPORT" << endl;
  if(m_pPD_Report->select(RecHeatID, RecTreatID, RecPlant))
  {
    Message << "The row for HeatID, TreatID & Plant was found, ANNOUNCETIME & HEATASSIGNMENTDATE were changed" << endl;
  }
  else
  {
    Message << "The row for HeatID, TreatID & Plant was not found, check the inserted Data in DB" << endl;
  }

  
  Message << "\nPDH_HEAT_DATA" << endl;
  if (m_pPDH_Heat_Data->select( RecPlant, RecHeatID, RecTreatID))
  {
    if (!m_pPDH_Heat_Data->isNull("AIM_S_GRADE", 1))
		{
      Message << "AIM_S_GRADE = " << m_pPDH_Heat_Data->getAIM_S_GRADE(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  AIM_S_GRADE is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("AIM_S_OPER", 1))
		{
      Message << "AIM_S_OPER = " << m_pPDH_Heat_Data->getAIM_S_OPER(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  AIM_S_OPER is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("CREW_CODE", 1))
		{
      Message << "CREW_CODE = " << m_pPDH_Heat_Data->getCREW_CODE(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  CREW_CODE is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HEATID_CON", 1))
		{
      Message << "HEATID_CON = " << m_pPDH_Heat_Data->getHEATID_CON(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HEATID_CON is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HEAT_ANNOUNCE_TIME", 1))
		{
      Message << "HEAT_ANNOUNCE_TIME(now) = " << m_pPDH_Heat_Data->getHEAT_ANNOUNCE_TIME(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HEAT_ANNOUNCE_TIME is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HM_TEMP_START", 1))
		{
      Message << "HM_TEMP_START = " << m_pPDH_Heat_Data->getHM_TEMP_START(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HM_TEMP_START is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HM_WEIGHT_START", 1))
		{
      Message << "HM_WEIGHT_START = " << m_pPDH_Heat_Data->getHM_WEIGHT_START(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HM_WEIGHT_START is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HM_WEIGHT_END", 1))
		{
      Message << "HM_WEIGHT_END = " << m_pPDH_Heat_Data->getHM_WEIGHT_END(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HM_WEIGHT_END is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("HM_WEIGHTSTART_OPER", 1))
		{
      Message << "HM_WEIGHTSTART_OPER = " << m_pPDH_Heat_Data->getHM_WEIGHTSTART_OPER(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  HM_WEIGHTSTART_OPER is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("LADLE_FREEBOARD", 1))
		{
      Message << "LADLE_FREEBOARD = " << m_pPDH_Heat_Data->getLADLE_FREEBOARD(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  LADLE_FREEBOARD is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("LADLE_FREEBOARD_BF", 1))
		{
      Message << "LADLE_FREEBOARD_BF = " << m_pPDH_Heat_Data->getLADLE_FREEBOARD_BF(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  LADLE_FREEBOARD_BF is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("SHIFT_CODE", 1))
		{
      Message << "SHIFT_CODE = " << m_pPDH_Heat_Data->getSHIFT_CODE(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  SHIFT_CODE is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("TEMP_INITIAL", 1))
		{
      Message << "TEMP_INITIAL = " << m_pPDH_Heat_Data->getTEMP_INITIAL(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  TEMP_INITIAL is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
    if (!m_pPDH_Heat_Data->isNull("USER_CODE", 1))
		{
      Message << "USER_CODE = " << m_pPDH_Heat_Data->getUSER_CODE(1) << endl;
		}
		else
		{      
      Message << "ERROR:\n  USER_CODE is not set in PDH_HEAT_DATA" << endl;
			TestCode = false;
		}
  //  std::vector<std::string>::iterator it;
  //  it = m_LadlePartCode.begin();

  //  for (it ; it < m_LadlePartCode.end() ; it++)
  //{
  //   if (m_pPD_Ladle_Life_Data->select(LadleType, LadleNo, *it ))
  //    {
  //      if (m_pPDH_Heat_Data->select(RecPlant,RecHeatID,RecTreatID))
  //      {
  //      long LadleLifeData = m_pPD_Ladle_Life_Data->getLIFE(1);
  //      std::string LadlePart = m_pPD_Ladle_Life_Data->getLADLEPARTCODE(1);
  //      if(LadlePart == "LW")
  //      {
  //        if(!m_pPDH_Heat_Data->isNull("LADLE_WALL_LIFE",1))
  //        {
  //          if(m_pPDH_Heat_Data->getLADLE_WALL_LIFE(1) == m_pPD_Ladle_Life_Data->getLIFE(1))
  //            Message << "LADLE_WALL_LIFE(" << LadleLifeData << ") = " << m_pPDH_Heat_Data->getLADLE_WALL_LIFE(1) << endl;            
  //          else
  //            Message << "ERROR:\n  The value of LADLE_WALL_LIFE in PDH_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
  //        }
  //        else
  //        {
  //          Message << "ERROR:\n  LADLE_WALL_LIFE is not set in PDH_HEAT_DATA"<<endl;
  //          TestCode = false;
  //        }
  //      }
  //      else if(LadlePart == "LB")
  //      {
  //        if(!m_pPDH_Heat_Data->isNull("LADLE_BOT_LIFE",1))
  //        {
  //          if(m_pPDH_Heat_Data->getLADLE_BOT_LIFE(1) == m_pPD_Ladle_Life_Data->getLIFE(1))
  //            Message << "LADLE_BOT_LIFE(" << LadleLifeData << ") = " << m_pPDH_Heat_Data->getLADLE_BOT_LIFE(1) << endl;
  //          else
  //            Message << "ERROR:\n The value of LADLE_BOT_LIFE in PDH_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
  //        }
  //        else
  //        {
  //          Message << "ERROR:\n  LADLE_BOT_LIFE is not set in PDH_HEAT_DATA"<<endl;
  //          TestCode = false;
  //        }
  //      }
  //      }
  //      else
  //      {
  //        Message << "ERROR:\n The selection from PDH_HEAT_DATA was not successfull" <<endl;
  //        TestCode = false;
  //      }      
  //    }
  //     else
  //      {
  //        Message << "ERROR:\n The selection from PD_LADLE_LIFE_DATA was not successfull" <<endl;
  //        TestCode = false;
  //      }
  //
  //}

  }
  else
  {
    std::string SearchKey = RecHeatID;
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_ErrorSearchingData(sMessage,SearchKey.c_str(),"PDH_Heat_Data");
  }


  if (m_pPD_HeatData) { delete m_pPD_HeatData; m_pPD_HeatData = 0;}
  if (m_pPP_Heat_Plant) { delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
  if (m_pPP_Heat) { delete m_pPP_Heat; m_pPP_Heat = 0;}
  if (m_pPDH_Heat_Data) { delete m_pPDH_Heat_Data; m_pPDH_Heat_Data = 0;}
  if (m_pPP_Order) { delete m_pPP_Order; m_pPP_Order = 0;}
  if (m_pPlantID_Interpreter) { delete m_pPlantID_Interpreter; m_pPlantID_Interpreter = 0;}
  if (m_pPD_Action) { delete m_pPD_Action; m_pPD_Action = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pPD_PretreatData) { delete m_pPD_PretreatData; m_pPD_PretreatData = 0;}


  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Annoncement use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Annoncement use case failed",1);
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_TreatmentHandling::handleHMDHeatStartRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  bool TestCode = false;
  std::string RecPlant = DEF_DB_PLANT::HMD;
  std::string CustHeatID;
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();

  //Initialise database objects
  CPP_ORDER* m_pPP_Order = 0;
  CPP_HEAT* m_pPP_Heat = 0;
  CPP_HEAT_PLANT* m_pPP_Heat_Plant = 0;

  if (pConnection)
  {
    m_pPP_Order = new CPP_ORDER(pConnection);
    m_pPP_Heat = new CPP_HEAT(pConnection);
    m_pPP_Heat_Plant = new CPP_HEAT_PLANT(pConnection);
  }

//-----------SET INTERFACE
  setpDM_Interface(ServerTask,DM::PRODUCT);
  std::string RecOrder = m_pDM_Interface->getString(ProductID.c_str(), DATA::OrderId);
  int Heatstatorder = m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::TreatStart);
  
//------------------------

  Message << "\nPP_HEAT"<<endl;
if(m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
{
   CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);

 if(m_pPP_Heat->select(CustHeatID))
  {
    if(!m_pPP_Heat->isNull("HEATSTATORDER", 1))
    {
      if(m_pPP_Heat->getHEATSTATORDER(1) == Heatstatorder)
      {
        Message << "HEATSTATORDER(12) = " << m_pPP_Heat->getHEATSTATORDER(1) << endl;
        TestCode = true;
      }
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PP_Heat was not successfull"<<endl;
    TestCode = false;
  }
  if(!TestCode)
  {
    Message << "ERROR:\n  HEATSTATORDER for Heat Start(12) was not found in table PP_HEAT "<< endl;
  }
}
else
 {
    Message << "ERROR:\n  CUSTHEATID for Heat Start(12) was not found in table PP_HEAT_PLANT" << endl;
 }


  Message << "\nPP_ORDER"<<endl;
  if(m_pPP_Order->select(RecOrder))
  {
    if(!m_pPP_Order->isNull("ORD_STAT_NO", 1))
    {
      if(m_pPP_Order->getORD_STAT_NO(1) == 21)
      {
        Message << "ORD_STAT_NO(21) = " << m_pPP_Order->getORD_STAT_NO(1) << endl;
        TestCode = true;
      }
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PP_ORDER was not successfull"<<endl;
    TestCode = false;
  }
  if(!TestCode)
  {
    Message << "ERROR:\n  ORD_STAT_NO for Heat Start(21) was not found" << endl;
  }

  //delete databse objects
  if (m_pPP_Order) { delete m_pPP_Order; m_pPP_Order = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Start use case failed",1);
  RetValue = true;

  return RetValue;
}

bool CARCHIVER_HMD_Test_TreatmentHandling::handleHMDHeatEndRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string ProductID = Event.getProductID();
  bool TestCode = true;

  //Initialise database objects
  CPP_ORDER* m_pPP_Order = 0;

  if (pConnection)
  {
    m_pPP_Order = new CPP_ORDER(pConnection);
  }
//-----------SET INTERFACE
  setpDM_Interface(ServerTask,DM::PRODUCT);

  std::string RecOrder = m_pDM_Interface->getString(ProductID.c_str(), DATA::OrderId);
//------------------------

  Message << "\nPP_ORDER"<<endl;
  if(m_pPP_Order->select(RecOrder))
  {
    if(!m_pPP_Order->isNull("ORD_STAT_NO", 1))
    {
      if(m_pPP_Order->getORD_STAT_NO(1) == 22)
      {
        Message << "ORD_STAT_NO(22) = " << m_pPP_Order->getORD_STAT_NO(1) << endl;
        TestCode = true;
      }
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PP_ORDER was not successfull"<<endl;
    TestCode = false;
  }
  if(!TestCode)
  {
    Message << "ERROR:\n  ORD_STAT_NO for Heat Start(16) was not found" << endl;
  }

  //delete databse objects
  if (m_pPP_Order) { delete m_pPP_Order; m_pPP_Order = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat End use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat End use case failed",1);
  RetValue = true;

  return RetValue;
}


bool CARCHIVER_HMD_Test_TreatmentHandling::handleHMDHeatCancellationRDY(CEventMessage& Event)
{
  bool RetValue = false;
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string ProductID = Event.getProductID();
  std::string RecPlantID = Event.getPlantID();
  std::string RecPlant = DEF_DB_PLANT::HMD;
  bool TestCode = true;

  std::string CustHeatID = "-1";
  std::string CustTreatID = "-1";
  CDateTime   ExpirationDate;
  std::string ProdOrderId = "";
  long        rows = 0;
  long        HeatStartOrder = 0;
  long        OrdStatNo = 0;
  long        HeatStartOrder_Theoretic = -1;  // HMD Treatment started
  long        OrdStatNo_Theoretic = -1;       // The production started at HMD


  //Initialise database objects
  CPP_HEAT_PLANT* m_pPP_Heat_Plant = 0;
  CPP_HEAT* m_pPP_Heat = 0;
  CPP_ORDER* m_pPP_Order = 0;
  CGC_Plant_Container* m_pPlantID_Interpreter = 0;
  CGC_PRD_STAT* m_pGC_Prd_Stat = 0;
  CHeatStatusContainer* m_pHeatStatusContainer;

  if (pConnection)
  {
    m_pPP_Heat_Plant = new CPP_HEAT_PLANT(pConnection);
    m_pPP_Heat = new CPP_HEAT(pConnection);
    m_pPP_Order = new CPP_ORDER(pConnection);
    m_pPlantID_Interpreter = new CGC_Plant_Container(pConnection);
    m_pGC_Prd_Stat = new CGC_PRD_STAT(pConnection);
    m_pHeatStatusContainer= new CHeatStatusContainer(pConnection);
  }

  // read customer heatid from PP_HEAT_PLANT
  //Message << "\nPP_HEAT_PLANT" << endl;
  //if (m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
  //{
  //  CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(m_pPP_Heat_Plant->first());
  //  Message << "New VALID entry with HeatID = " << RecHeatID <<
  //                                   " TreatId = " << RecTreatID <<
  //                                   " Plant = " << RecPlant <<
  //                                   " was created" << endl;
  //}
  //else
  //{
  //  Message << "ERROR:\n  there are no any VALID entries for actual heat found" << endl;
  //  TestCode = false;
  //}
    Message << "\nPP_HEAT_PLANT" << endl;
  if (m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
  {
    CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);
    long Rows = m_pPP_Heat_Plant->getLastRow();
    Message<<"There are "<<Rows<<"lines of HEATID:"<<RecHeatID<<" and TREATID:"<<RecTreatID<<" and PLANT:"<<RecPlant<<endl;
    for (int i = 1; i <= Rows; i++)
    {
      if (!m_pPP_Heat_Plant->isNull("EXPIRATIONDATE",i))
      {
        if (m_pPP_Heat_Plant->getString("EXPIRATIONDATE",i) != "VALID")
        Message<<"The EXPIRATIONDATE was changed to"<<m_pPP_Heat_Plant->getEXPIRATIONDATE(i)<<endl;
        else
        {
          Message<<"The EXPIRATIONDATE was VALID of the new line of PP_HEAT_PLANT."<<endl;
          if (!m_pPP_Heat_Plant->isNull("TREATID",i))
          {
            Message<<"TREATID of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getTREATID(i)<<endl;
          } 
          else
          {
            Message<<"TREATID was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("HEATID",i))
          {
            Message<<"HEATID of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getHEATID(i)<<endl;
          } 
          else
          {
            Message<<"HEATID was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("HEATID_CUST",i))
          {
            Message<<"HEATID_CUST of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getHEATID_CUST(i)<<endl;
          } 
          else
          {
            Message<<"HEATID_CUST was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("TREATID_CUST",i))
          {
            Message<<"TREATID_CUST of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getTREATID_CUST(i)<<endl;
          } 
          else
          {
            Message<<"TREATID_CUST was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANT",i))
          {
            Message<<"PLANT of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANT(i)<<endl;
          } 
          else
          {
            Message<<"PLANT was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANTNO",i))
          {
            Message<<"PLANTNO of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANTNO(i)<<endl;
          } 
          else
          {
            Message<<"PLANTNO was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANLADLENO",i))
          {
            Message<<"PLANLADLENO of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANLADLENO(i)<<endl;
          } 
          else
          {
            Message<<"PLANLADLENO was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANLADLETYPE",i))
          {
            Message<<"PLANLADLETYPE of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANLADLETYPE(i)<<endl;
          } 
          else
          {
            Message<<"PLANLADLETYPE was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANTREATSTART",i))
          {
            Message<<"PLANTREATSTART of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANTREATSTART(i)<<endl;
          } 
          else
          {
            Message<<"PLANTREATSTART was not set for the new line."<<endl;
            TestCode = false;
          }
          if (!m_pPP_Heat_Plant->isNull("PLANTREATEND",i))
          {
            Message<<"PLANTREATEND of the new line of PP_HEAT_PLANT was "<<m_pPP_Heat_Plant->getPLANTREATEND(i)<<endl;
          } 
          else
          {
            Message<<"PLANTREATEND was not set for the new line."<<endl;
            TestCode = false;
          }
        }
      }
      else
      {
        Message<<"ERROR:\n  EXPIRATIONDATE is null in PP_HEAT_PLANT"<<endl;
        TestCode = false;
      }
    }
  } 
  else
  {
    Message<<"ERROR:\n  The selection from PP_HEAT_PLANT was not successful."<<endl;
    TestCode = false;
  }

  //Test HeatCancel_HMD
  //
  Message << "\nPP_HEAT" << endl;
  if (m_pPP_Heat->select(CustHeatID))
  {
    if (!m_pPP_Heat->isNull("HEATSTATORDER",1))
    {
      if (m_pPP_Heat->getHEATSTATORDER(1) == m_pHeatStatusContainer->getHeatStatus("L3", DEF_GC_HEAT_STAT::Planned ))
        Message<<"HEATSTATORDER ("<<m_pPP_Heat->getHEATSTATORDER(1)<<") = "<<m_pHeatStatusContainer->getHeatStatus("L3", DEF_GC_HEAT_STAT::Planned)<<endl;
      else
      {
        Message<<"The HEATSTATORDER of PP_HEAT was different from CHeatStatusContainer."<<endl;
        TestCode = false;
      }
    } 
    else
    {
      Message<<"ERROR:\n  HEATSTATORDER was not set in PP_HEAT."<<endl;
      TestCode = false;
    }
  } 
  else
  {
    Message<<"ERROR:\n  The selection from PP_HEAT was not successful."<<endl;
    TestCode = false;
  }
  
  Message<<"\nPP_ORDER"<<endl;
  if (m_pPP_Heat->select(CustHeatID))
  {
    std::string PRODORDERID = m_pPP_Heat->getPRODORDERID(1);
    if (m_pPP_Order->select(PRODORDERID))
    {
      if (m_pGC_Prd_Stat->select(DEF_GC_PRD_STAT::Planned))
     {
      if (m_pPP_Order->getORD_STAT_NO(1) == m_pGC_Prd_Stat->getORD_STAT_NO(1))
      {
        Message<<"ORD_STAT_NO("<<m_pGC_Prd_Stat->getORD_STAT_NO(1)<<") = "<<m_pPP_Order->getORD_STAT_NO(1)<<endl;
      } 
      else
      {
        Message<<"The ORD_STAT_NO of PP_ORDER is different from GC_PRD_STAT."<<endl;
        TestCode = false;
      }
     }
     else
     {
       Message<<"ERROR:\n  The selection from GC_PRD_STAT was not successful."<<endl;
       TestCode = false;
     }
    } 
    else
    {
      Message<<"ERROR:\n  The selection from PP_Order was not successful."<<endl;
      TestCode = false;
    }
  } 
  else
  {
    Message<<"ERROR:\n  The selection from PP_Heat was not successful."<<endl;
    TestCode = false;
  }
  //Message << "\nPP_HEAT" << endl;
  //if(m_pPP_Heat->select(CustHeatID))
  //{
  //  // find out which plant was the last and set the related status of heat and order
  //  std::string DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_CONARC_PLANTS::ConArc_1);
  //  std::string ActRouteCode = m_pPP_Heat->getROUTECODEACT(1);
  //  if (ActRouteCode.length() >= DefRouteCode.length())
  //  {
  //    if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
  //    {
  //      HeatStartOrder_Theoretic = 36;
  //      OrdStatNo_Theoretic = 11;
  //      ActRouteCode.clear(); // to avoid the next checking
  //    }
  //  }
  //  DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_CONARC_PLANTS::ConArc_2);
  //  if (ActRouteCode.length() >= DefRouteCode.length())
  //  {
  //    if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
  //    {
  //      HeatStartOrder_Theoretic = 36;
  //      OrdStatNo_Theoretic = 11;
  //      ActRouteCode.clear();// to avoid the next checking
  //    }
  //  }
  //  DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_LF_PLANTS::LF_1_1);
  //  if (ActRouteCode.length() >= DefRouteCode.length())
  //  {
  //    if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
  //    {
  //      HeatStartOrder_Theoretic = 64;
  //      OrdStatNo_Theoretic = 14;
  //      ActRouteCode.clear();// to avoid the next checking
  //    }
  //  }
  //  DefRouteCode = m_pPlantID_Interpreter->getRouteCodeID(DEF_LF_PLANTS::LF_2_1);
  //  if (ActRouteCode.length() >= DefRouteCode.length())
  //  {
  //    if(ActRouteCode.substr((ActRouteCode.length()-DefRouteCode.length()),DefRouteCode.length()) == DefRouteCode)
  //    {
  //      HeatStartOrder_Theoretic = 64;
  //      OrdStatNo_Theoretic = 14;
  //      ActRouteCode.clear();// to avoid the next checking
  //    }
  //  }
  //  if(!m_pPP_Heat->isNull("HEATSTATORDER", 1))
  //  {
  //    HeatStartOrder = m_pPP_Heat->getHEATSTATORDER(1);
  //    if(HeatStartOrder == HeatStartOrder_Theoretic)
  //    {
  //      Message << "HEATSTATORDER in PP_HEAT was set to " << HeatStartOrder_Theoretic << endl;
  //    }
  //    else
  //    {
  //      Message << "ERROR:\n  HEATSTATORDER in PP_HEAT was not set to " << HeatStartOrder_Theoretic << ", it is "<< HeatStartOrder << endl;
  //      TestCode = false;
  //    }
  //  }
  //  else
  //  {
  //    Message << "ERROR:\n  HEATSTATORDER is NULL" << endl;
  //    TestCode = false;
  //  }
  //  if(!m_pPP_Heat->isNull("PRODORDERID", 1))
  //  {
  //    ProdOrderId = m_pPP_Heat->getPRODORDERID(1);
  //    if(m_pPP_Order->select(ProdOrderId))
  //    {
  //      if(!m_pPP_Order->isNull("ORD_STAT_NO", 1))
  //      {
  //        OrdStatNo = m_pPP_Order->getORD_STAT_NO(1);
  //        if(OrdStatNo == OrdStatNo_Theoretic)
  //        {
  //          Message << "ORD_STAT_NO in PP_ORDER was set to " << OrdStatNo_Theoretic << endl;
  //        }
  //        else
  //        {
  //          Message << "ERROR:\n  ORD_STAT_NO in PP_ORDER was not set to " << OrdStatNo_Theoretic << ", it is "<< OrdStatNo << endl;
  //          TestCode = false;
  //        }
  //      }
  //      else
  //      {
  //        TestCode = false;        
  //        Message << "ERROR:\n  ORD_STAT_NO in PP_ORDER is NULL" << endl;
  //      }
  //    }
  //    else
  //    {
  //      Message << "ERROR:\n  select * from PP_ORDER where PRODORDERID=" <<ProdOrderId<< " was not successfull" << endl;
  //      TestCode = false;
  //    }
  //  }
  //  else
  //  {
  //    Message << "ERROR:\n  PRODORDERID in PP_ORDER is NULL" << endl;
  //    TestCode = false;
  //  }
  //}
  //else
  //{
  //  Message << "ERROR:\n  Select was not successfull" << endl;
  //  TestCode = false;
  //}

  //delete databse objects
  if (m_pPP_Heat_Plant) { delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
  if (m_pPP_Heat) { delete m_pPP_Heat; m_pPP_Heat = 0;}
  if (m_pPP_Order) { delete m_pPP_Order; m_pPP_Order = 0;}
  if (m_pPlantID_Interpreter) { delete m_pPlantID_Interpreter; m_pPlantID_Interpreter = 0; }
  if (m_pGC_Prd_Stat) { delete m_pGC_Prd_Stat; m_pGC_Prd_Stat = 0; }
  if (m_pHeatStatusContainer) { delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}

  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Cancel use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Cancel use case failed",1);
  RetValue = true;

  return RetValue;
}
bool CARCHIVER_HMD_Test_TreatmentHandling::handleHMDHeatDepartureRDY(CEventMessage& Event)
{
  bool RetValue = false;
  
  std::stringstream Message;
  std::string DataKey = Event.getDataKey();
  std::string RecHeatID = Event.getHeatID();
  std::string RecTreatID = Event.getTreatID();
  std::string RecProductID = Event.getProductID();
  std::string RecPlantID   = Event.getPlantID();
  std::string ProdOrderId  = "";
  std::string RecPlant = DEF_DB_PLANT::HMD;
  std::string LadleType;
  std::string LadleNo;
  std::string CustHeatID;
  bool TestCode = true;
  
  CPP_ORDER *m_pPP_Order;
  CPP_HEAT *m_pPP_Heat;
  CPD_HEATDATA *m_pPD_HeatData;
  CPDH_HEAT_DATA *m_pPDH_Heat_Data;
  CPD_REPORT *m_pPD_Report;
  CPP_HEAT_PLANT *m_pPP_Heat_Plant;
  CPD_LADLE_LIFE_DATA *m_pPD_Ladle_Life_Data;
  CHeatStatusContainer* m_pHeatStatusContainer;

  if (pConnection)
 {
    m_pPP_Order           = new CPP_ORDER(pConnection);
    m_pPP_Heat            = new CPP_HEAT(pConnection);
    m_pPD_HeatData        = new CPD_HEATDATA(pConnection);
    m_pPDH_Heat_Data      = new CPDH_HEAT_DATA(pConnection);
    m_pPD_Report          = new CPD_REPORT(pConnection);
    m_pPP_Heat_Plant      = new CPP_HEAT_PLANT(pConnection);
    m_pPD_Ladle_Life_Data = new CPD_LADLE_LIFE_DATA(pConnection);
    m_pPDH_Heat_Data      = new CPDH_HEAT_DATA(pConnection);
    m_pHeatStatusContainer= new CHeatStatusContainer(pConnection);
 }  
  
  Message << "\nPD_HEATDATA" << endl;

  if(m_pPD_HeatData->select(RecHeatID,RecTreatID,RecPlant))
  {
    
    LadleType = m_pPD_HeatData->getLADLETYPE(1);
    
    if(LadleType != DEF_LADLE_TYPES::HotMetalLadle)
    {
      Message <<"ERROR:\n  LADLETYPE is not right in PD_HEATDATA" <<endl;
      TestCode = false;
      LadleType = DEF_LADLE_TYPES::HotMetalLadle;
    }

    LadleNo   = m_pPD_HeatData->getLADLENO(1);

    if(!m_pPD_HeatData->isNull("TREATEND_ACT",1))
    {
      Message << "TREATEND_ACT = " <<m_pPD_HeatData->getTREATEND_ACT(1) <<endl;
    }
    else
    {
      Message << "ERROR:\n TREATEND_ACT is not set in PD_HEATDATA" << endl;
      TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n The selection from PD_HEATDATA was not successfull" <<endl;
    TestCode = false;
  }

  Message << "\nPP_ORDER" << endl;
   if(m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
{
  if(!m_pPP_Heat_Plant->isNull("HEATID_CUST",1))
  {
  CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);

  if(m_pPP_Heat->select(CustHeatID))
  {
  if(!m_pPP_Heat->isNull("PRODORDERID", 1))
    {
      ProdOrderId = m_pPP_Heat->getPRODORDERID(1);
      if(m_pPP_Order->select(ProdOrderId))
      {
       if(!m_pPP_Order->isNull("ORD_STAT_NO",1))
       {
         if(m_pPP_Order->getORD_STAT_NO(1) == 22)
         Message << "ORD_STAT_NO (22) = " << m_pPP_Order->getORD_STAT_NO(1) << endl;
         else
         Message <<"The value of ORD_STAT_NO is not right in table PP_ORDER" <<endl;
       }
      else
       {
        Message << "ERROR:\n  ORD_STAT_NO is not set in PP_ORDER"<<endl;
        TestCode = false;
       }
      }
    }
  else
       {
        Message << "ERROR:\n  PRODORDERID is not set in PP_HEAT"<<endl;
        TestCode = false;
       }

  }
  else
  {
    Message <<"ERROR:\n CustHeatID is not set in PP_HEAT" <<endl;
    TestCode = false;
  }
  }
  else
  {
    Message << "ERROR:\n HEATID_CUST is not set in PP_HEAT_PLANT" <<endl;
    TestCode = false;
  }
 }
  else
  {
    Message << "ERROR:\n  The selection from PP_HEAT_PLANT was not successfull"<<endl;
    TestCode = false;
  }

  Message << "\nPP_HEAT" << endl;
  if (m_pPP_Heat_Plant->select(RecHeatID, RecTreatID, RecPlant))
{
  CustHeatID = m_pPP_Heat_Plant->getHEATID_CUST(1);
  if(m_pPP_Heat->select(CustHeatID))
{
  if(!m_pPP_Heat->isNull("HEATSTATORDER", 1))
    {
        if (m_pHeatStatusContainer->getHeatStatus(RecPlant, DEF_GC_HEAT_STAT::LdlDepart) == m_pPP_Heat->getHEATSTATORDER(1))
         Message << "HEATSTATORDER = " << m_pPP_Heat->getHEATSTATORDER(1) << endl;
        else
         Message <<"ERROR:\n The HEATSTATORDER in PP_HEAT is different from the value of m_pHeatStatusContainer->getHeatStatus(ActPlant, DEF_GC_HEAT_STAT::LdlDepart)" <<endl;
    }
  else
    {
        Message << "ERROR:\n  HEATSTATORDER is not set in PP_HEAT"<<endl;
        TestCode = false;
    }
}
}
else
{
  Message <<"ERROR:\n The HEATID_CUST was not set in PP_HEAT_PLANT" <<endl;
}
 

  Message << "\nPD_REPORT" << endl;

  if(m_pPD_Report->select(RecHeatID,RecTreatID,RecPlant))
  {
   if(!m_pPD_Report->isNull("TREATDUR", 1))
    {
         Message << "TREATDUR = " << m_pPD_Report->getTREATDUR(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  TREATDUR is not set in PD_REPORT"<<endl;
        TestCode = false;
    }  
   if(!m_pPD_Report->isNull("DEPARTTIME", 1))
    {
         Message << "DEPARTTIME = " << m_pPD_Report->getDEPARTTIME(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  DEPARTTIME is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("DELAYDUR", 1))
    {
         Message << "DELAYDUR = " << m_pPD_Report->getDELAYDUR(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  DELAYDUR is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("LASTTEMP", 1))
    {
         Message << "LASTTEMP = " << m_pPD_Report->getLASTTEMP(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  LASTTEMP is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("TIMELASTTEMPBEFTAP", 1))
    {
         Message << "TIMELASTTEMPBEFTAP = " << m_pPD_Report->getTIMELASTTEMPBEFTAP(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  TIMELASTTEMPBEFTAP is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("AIMSTEELWEIGHT_MOD", 1))
    {
         Message << "AIMSTEELWEIGHT_MOD = " << m_pPD_Report->getAIMSTEELWEIGHT_MOD(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  AIMSTEELWEIGHT_MOD is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("AIMTEMP_MOD", 1))
    {
         Message << "AIMTEMP_MOD = " << m_pPD_Report->getAIMTEMP_MOD(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  AIMTEMP_MOD is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("TREATSTART_MOD", 1))
    {
         Message << "TREATSTART_MOD = " << m_pPD_Report->getTREATSTART_MOD(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  TREATSTART_MOD is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
   if(!m_pPD_Report->isNull("TREATEND_MOD", 1))
    {
         Message << "TREATEND_MOD = " << m_pPD_Report->getTREATEND_MOD(1) << endl;
    }
  else
    {
        Message << "ERROR:\n  TREATEND_MOD is not set in PD_REPORT"<<endl;
        TestCode = false;
    }
  }
  else
  {
    Message << "ERROR:\n  The selection from PD_REPORT was not successfull"<<endl;
    TestCode = false;
   }


   
  Message << "\nPDH_HEAT_DATA" << endl;

  if(m_pPDH_Heat_Data->select(RecPlant,RecHeatID,RecTreatID))
  {
    if(!m_pPDH_Heat_Data->isNull("SLAG_WEIGHT_END",1))
    {
      Message << "SLAG_WEIGHT_END = " << m_pPDH_Heat_Data->getSLAG_WEIGHT_END(1) <<endl;
    }
    else
    {
        Message << "ERROR:\n  SLAG_WEIGHT_END is not set in PDH_HEAT_DATA"<<endl;
        TestCode = false;
    }
    if(!m_pPDH_Heat_Data->isNull("HM_WEIGHT_END",1))
    {
      Message << "HM_WEIGHT_END = " << m_pPDH_Heat_Data->getHM_WEIGHT_END(1) <<endl;
    }
    else
    {
        Message << "ERROR:\n  HM_WEIGHT_END is not set in PDH_HEAT_DATA"<<endl;
        TestCode = false;
    }
    if(!m_pPDH_Heat_Data->isNull("INJECT_END_TIME",1))
    {
      Message << "INJECT_END_TIME = " << m_pPDH_Heat_Data->getINJECT_END_TIME(1) <<endl;
    }
    else
    {
        Message << "ERROR:\n  INJECT_END_TIME is not set in PDH_HEAT_DATA"<<endl;
        TestCode = false;
    }
    if(!m_pPDH_Heat_Data->isNull("LADLE_WALL_LIFE",1))
    {
      Message << "LADLE_WALL_LIFE = " << m_pPDH_Heat_Data->getLADLE_WALL_LIFE(1) <<endl;
    }
    else
    {
        Message << "ERROR:\n  LADLE_WALL_LIFE is not set in PDH_HEAT_DATA"<<endl;
        TestCode = false;
    }
    if(!m_pPDH_Heat_Data->isNull("LADLE_BOT_LIFE",1))
    {
      Message << "LADLE_BOT_LIFE = " << m_pPDH_Heat_Data->getLADLE_BOT_LIFE(1) <<endl;
    }
    else
    {
        Message << "ERROR:\n  LADLE_BOT_LIFE is not set in PDH_HEAT_DATA"<<endl;
        TestCode = false;
    }
   }
  else
  {
    Message << "The selection from PDH_HEAT_DATA was not successful" <<endl;
  }

  Message << "\nPD_LADLE_LIFE_DATA" <<endl;

  std::vector<std::string>::iterator it;
  it = m_LadlePartCode.begin();
  for (it ; it < m_LadlePartCode.end() ; it++)
  {
     if (m_pPD_Ladle_Life_Data->select(LadleType, LadleNo, *it ))
      {
        if (m_pPDH_Heat_Data->select(RecPlant,RecHeatID,RecTreatID))
        {
        long LadleLifeData = m_pPD_Ladle_Life_Data->getLIFE(1);
        std::string LadlePart = m_pPD_Ladle_Life_Data->getLADLEPARTCODE(1);
        if(LadlePart == "LW")
        {
          if(!m_pPDH_Heat_Data->isNull("LADLE_WALL_LIFE",1))
          {
            if(m_pPDH_Heat_Data->getLADLE_WALL_LIFE(1) == m_pPD_Ladle_Life_Data->getLIFE(1))
              Message << "LADLE_WALL_LIFE(" << LadleLifeData << ") = " << m_pPDH_Heat_Data->getLADLE_WALL_LIFE(1) << endl;            
            else
              Message << "ERROR:\n  The value of LADLE_WALL_LIFE in PDH_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
          }
          else
          {
            Message << "ERROR:\n  LADLE_WALL_LIFE is not set in PDH_HEAT_DATA"<<endl;
            TestCode = false;
          }
        }


        else if(LadlePart == "LB")
        {
          if(!m_pPDH_Heat_Data->isNull("LADLE_BOT_LIFE",1))
          {
            if(m_pPDH_Heat_Data->getLADLE_BOT_LIFE(1) == m_pPD_Ladle_Life_Data->getLIFE(1))
              Message << "LADLE_BOT_LIFE(" << LadleLifeData << ") = " << m_pPDH_Heat_Data->getLADLE_BOT_LIFE(1) << endl;
            else
              Message << "ERROR:\n The value of LADLE_BOT_LIFE in PDH_Heat_Data is different from the value of LIFE in PD_LADLE_LIFE_DATA " << endl;
          }
          else
          {
            Message << "ERROR:\n  LADLE_BOT_LIFE is not set in PDH_HEAT_DATA"<<endl;
            TestCode = false;
          }
        }
        }
        else
        {
          Message << "ERROR:\n The selection from PDH_HEAT_DATA was not successfull" <<endl;
          TestCode = false;
        }  
      }
     else
        {
          Message << "ERROR:\n The selection from PD_LADLE_LIFE_DATA was not successfull" <<endl;
          TestCode = false;
        }
  }
        
  if (m_pPD_HeatData) { delete m_pPD_HeatData; m_pPD_HeatData = 0;}
  if (m_pPP_Heat_Plant) { delete m_pPP_Heat_Plant; m_pPP_Heat_Plant = 0;}
  if (m_pPP_Heat) { delete m_pPP_Heat; m_pPP_Heat = 0;}
  if (m_pPDH_Heat_Data) { delete m_pPDH_Heat_Data; m_pPDH_Heat_Data = 0;}
  if (m_pPP_Order) { delete m_pPP_Order; m_pPP_Order = 0;}
  if (m_pPD_Report) { delete m_pPD_Report; m_pPD_Report = 0;}
  if (m_pPD_Ladle_Life_Data) { delete m_pPD_Ladle_Life_Data; m_pPD_Ladle_Life_Data = 0;}
  if (m_pHeatStatusContainer) { delete m_pHeatStatusContainer; m_pHeatStatusContainer = 0;}
  
  cCBS_StdLog_Task::getInstance()->log(Message.str(),1);

  if (TestCode)
    cCBS_StdLog_Task::getInstance()->log("Test Heat Departure use case was successful",1);
  else
    cCBS_StdLog_Task::getInstance()->log("Test Heat Departure use case failed",1);
  RetValue = true;

  return RetValue;
}

void CARCHIVER_HMD_Test_TreatmentHandling::initDBClasses()
{
   
}

void CARCHIVER_HMD_Test_TreatmentHandling::deleteDBClasses()
{
  
}

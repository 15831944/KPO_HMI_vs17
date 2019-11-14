#include "CARCHIVER_HMDAnnouncementPresettings.h"

CARCHIVER_HMDAnnouncementPresettings::CARCHIVER_HMDAnnouncementPresettings()
{
}

bool CARCHIVER_HMDAnnouncementPresettings::initialize(CEventMessage& Event)
{
  bool RetValue = true;

////  // Unified exception handling *******************************************************
////  std::string Scope("CARCHIVER_HMDAnnouncementPresettings::initialize");
////  std::stringstream ExceptionMsg;
////  ExceptionMsg << "Handling event: " << ", " << Event.getHeatID()
////               << ", " << Event.getTreatID()   << ", " << Event.getPlantID();
////  //***********************************************************************************
////
////  try
////  {    
////    m_pConnection = CARCHIVER_HMDTask::getInstance()->getpConnection();
////    if (!m_pConnection)
////    {
////      handleDBConnectionError();
////    }
////
////    CPP_HEAT                  PP_Heat(m_pConnection);
////    CPP_ORDER                 PP_Order(m_pConnection);
////    CPP_HEAT_PLANT            PP_Heat_Plant(m_pConnection);
////    CGC_SHIFT_CODE            GC_Shift_Code(m_pConnection);
//////SS    CPP_SHIFT_CREW_ASSIGNMENT PP_Shift_Crew_Assignement(m_pConnection);
//////SS    CPP_CREW_USER_ASSIGNMENT  PP_Crew_User_Assignement(m_pConnection);
////    CPD_LADLE                 PD_Ladle(m_pConnection);
//////SS    CPD_LADLE_DATA            PD_Ladle_Data(m_pConnection);
//////SS    CPP_GRADE_ANL             PP_Grade_Anl(m_pConnection);
////    CGC_Plant_Container       PlantID_Interpreter(m_pConnection);
////
////    CDateTime   Now;
////
////    m_HeatID    = Event.getHeatID();
////    m_TreatID   = Event.getTreatID();
////    m_PlantID   = Event.getPlantID();
////    m_Plant     = PlantID_Interpreter.getPlant(m_PlantID);
////    m_PlantNo   = PlantID_Interpreter.getPlantNo(m_PlantID);
////    m_LadleType = DEF_LADLE_TYPES::HotMetalLadle;
////    SCULLMASS   = 0.0;
////    TAREWGT     = 0.0;
////    EquipPlant  = 0;
////    HEATID_CON  = CSMC_DBData::unspecString;
////    TREATID_CON  = CSMC_DBData::unspecString;
////    ConArcCustHeatID  = CSMC_DBData::unspecString;
////
//////SS    m_UserCode  = PP_Crew_User_Assignement.getActualUserCode(m_Plant, m_PlantNo);
////
////    // get data from Interface
////    setpDM_Interface(Event.getSender(),DM::EVENT);
////    m_LadleNo   = CIntfData::ToStdString(m_pDM_Interface->getString(Event.getDataKey().c_str(), DATA::LadleNo));
//////SS    CAST_ID     = CIntfData::ToStdString(m_pDM_Interface->getString(Event.getDataKey().c_str(), DATA::BFCastID));
////    CALC_MODE   = m_pDM_Interface->getLong(Event.getDataKey().c_str(), DATA::HeatingMode);
////    TREAT_TYPE_OPER = m_pDM_Interface->getLong(Event.getDataKey().c_str(), DATA::HMDBlowType);
////    AIM_S_OPER  = m_pDM_Interface->getDouble(Event.getDataKey().c_str(), DATA::SulphurAim);
////
////    ConArcCustHeatID = CIntfData::ToStdString(m_pDM_Interface->getString(Event.getDataKey().c_str(), DATA::CustHeatID));
////    if (PP_Heat_Plant.selectByCustData(ConArcCustHeatID, CSMC_DBData::unspecString, DEF_DB_PLANT::CON) && !ConArcCustHeatID.empty())
////    {
////      HEATID_CON = PP_Heat_Plant.getHEATID(1);
////      TREATID_CON = PP_Heat_Plant.getTREATID(1);
////      PLANTREATSTART = PP_Heat_Plant.getTREATSTART_PLAN(1); //SS .getPLANTREATSTART(1);
////      PLANTREATSTART_CON = PP_Heat_Plant.getTREATSTART_PLAN(1); //SS .getPLANTREATSTART(1);
////    }
////
////    //PP_HEAT_PLANT
//////SS    if (PP_Heat_Plant.select(m_HeatID, m_TreatID, m_Plant, m_PlantNo))
////    if (PP_Heat_Plant.select(m_HeatID, m_TreatID, m_Plant)) //SS
////	{
////      // If ConArc HeatId is empty read PlanTreatEnd time for current heat.
////      if(ConArcCustHeatID.empty())
////      {
////        PLANTREATSTART = PP_Heat_Plant.getTREATEND_PLAN(1); //SS  .getPLANTREATEND(1);
////        PLANTREATSTART_CON = PP_Heat_Plant.getTREATEND_PLAN(1); //SS .getPLANTREATEND(1);
////      }
////
////      m_CustHeatID = PP_Heat_Plant.getHEATID_CUST_PLAN(1); //SS  .getHEATID_CUST(1);
////      m_CustTreatID = PP_Heat_Plant.getTREATID_CUST_PLAN(1); //SS  .getTREATID_CUST(1);
////    }
////
////    //call the general function
//////SS    CARCHIVER_AnnouncementPresettings::initialize(m_HeatID, m_TreatID, m_CustHeatID, m_CustTreatID, m_Plant, m_PlantNo, m_LadleType, m_LadleNo, m_UserCode, Now); 
////    CARCHIVER_AnnouncementPresettings::writeAll();
////
////    //PP_HEAT
////    if (PP_Heat.select(m_CustHeatID))
////    {
////      PRODORDERID  = PP_Heat.getPRODORDERID(1);
////    }
////
////    //PP_ORDER
////    if (PP_Order.select(PRODORDERID))
////    {
////      STEELGRADECODE = PP_Order.getSTEELGRADECODE(1);
////    }
////
////    //GC_SHIFT_CODE
////    //SS if (GC_Shift_Code.select(Now))
////    //SS {
////    //SS  SHIFTCODE = GC_Shift_Code.getSHIFTCODE(1);
////    //SS }
////
////    //PP_SHIFT_CREW_ASSIGNMENT
////    SHIFTSTARTDATE.fromDBString( Now.toDBString().substr(0,10) );
//////SS    if (PP_Shift_Crew_Assignement.select(SHIFTSTARTDATE, m_Plant, m_PlantNo, SHIFTCODE))
//////SS    {
//////SS      CREWCODE = PP_Shift_Crew_Assignement.getCREWCODE(1);
//////SS    }
////
////    //PD_LADLE
//////SS    if (PD_Ladle.select(m_LadleNo, m_LadleType))
////    long i=1; //SS 
////	if (PD_Ladle.select(i, m_LadleType)) //SS
////    {
////      SCULLMASS = PD_Ladle.getSCULLMASS(1);
////      TAREWGT = PD_Ladle.getTAREWEIGHT(1); //SS .getTAREWGT(1);
//////SS      REMSTEELMASS = PD_Ladle.getREMSTEELMASS(1);
//////SS      REMSLAGMASS = PD_Ladle.getREMSLAGMASS(1);
////      LADLE_FREEBOARD_BF = PD_Ladle.getFREEBOARD(1);
////
////      //
////      //Special Check in case operator forgot to update Freeboard. set to standard 300.
////      //ConArc HM Discharge set Ladle Freeboard as 999. i.e. empty
////      if(LADLE_FREEBOARD_BF == 999)
////        LADLE_FREEBOARD_BF = 300;
////    }
////
////    //PD_LADLE
////    //SS if (PD_Ladle_Data.select(m_LadleType, m_LadleNo, "LAST"))
////    //SS {
////    //SS   LASTTEMP = PD_Ladle_Data.getLASTTEMP(1);
////    //SS }
////
////    //PP_HEAT_PLANT
////    if (PP_Heat_Plant.select(m_HeatID, m_TreatID, DEF_DB_PLANT::CON))
////    {
////      PLANTREATSTART_CON = PP_Heat_Plant.getTREATSTART_PLAN(1); //SS   .getPLANTREATSTART(1);
////    }
////
////    //PP_GRADE_ANL
////    //SS if (PP_Grade_Anl.select(STEELGRADECODE, m_Plant))
////    //SS {
////    //SS   AIM_S_GRADE = PP_Grade_Anl.getANL(1); // If ANL is not set in PD_GRADE_ANL then take it from **_PARAM table.
////    //SS }
////  }
////  catch (cCBS_DBExc &e)
////  {
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(),
////    Scope.c_str(), ExceptionMsg.str().c_str()); 
////    RetValue = false;
////    handleDBConnectionError();
////  }
////  catch(CORBA::SystemException& sExc) 
////  {
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage,sExc._name(),
////    Scope.c_str(), ExceptionMsg.str().c_str());
////    RetValue = false;
////  }
////  catch(CORBA::Exception& cExc) 
////  {
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage,cExc._name(),
////    Scope.c_str(), ExceptionMsg.str().c_str());
////    RetValue = false;
////  }
////  catch(...)
////  {
////    std::string Msg("Unknown exception:");
////    Msg += ExceptionMsg.str();
////    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
////    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
////    pEventLog->EL_ExceptionCaught(sMessage, "",
////    Scope.c_str(), Msg.c_str()); 
////    RetValue = false;
////  }
  return RetValue;
}

CARCHIVER_HMDAnnouncementPresettings::~CARCHIVER_HMDAnnouncementPresettings()
{
}

bool CARCHIVER_HMDAnnouncementPresettings::writePDH_HEAT_DATA()
{
  bool RetValue = false;
////  CDateTime Now;
////  
////  CPDH_HEAT_DATA PDH_Heat_Data(m_pConnection);
////
////  PDH_Heat_Data.setHEATID(m_HeatID);
////  PDH_Heat_Data.setHEATID_CON(ConArcCustHeatID);
////  //PDH_Heat_Data.setHEATID_CON(HEATID_CON);
////  PDH_Heat_Data.setTREATID(m_TreatID);
////  PDH_Heat_Data.setPLANT(m_Plant);
////  PDH_Heat_Data.setLADLE_FREEBOARD_BF((long)LADLE_FREEBOARD_BF);
////  PDH_Heat_Data.setLADLE_FREEBOARD((long)LADLE_FREEBOARD_BF);
////  PDH_Heat_Data.setSHIFT_CODE(SHIFTCODE);
////  PDH_Heat_Data.setCREW_CODE(CREWCODE);
////  PDH_Heat_Data.setUSER_CODE(m_UserCode);
////  PDH_Heat_Data.setPRODUCTION_DATE(Now);
////  PDH_Heat_Data.setHM_WEIGHTSTART_OPER(REMSTEELMASS);
////  PDH_Heat_Data.setHEAT_ANNOUNCE_TIME(Now);
////  PDH_Heat_Data.setHM_WEIGHT_END(REMSTEELMASS);
////  PDH_Heat_Data.setSLAG_WEIGHT_START(REMSLAGMASS);
////  PDH_Heat_Data.setSLAG_WEIGHT_START_OPER(REMSLAGMASS);
////  PDH_Heat_Data.setSLAG_WEIGHT_END(REMSLAGMASS);
////  PDH_Heat_Data.setDISCHARGE_TIME_PLAN(PLANTREATSTART_CON);
////  PDH_Heat_Data.setHM_TEMP_START(LASTTEMP);
////  PDH_Heat_Data.setAIM_S_GRADE(AIM_S_GRADE);
////  PDH_Heat_Data.setAIM_S_OPER(AIM_S_OPER);
////  PDH_Heat_Data.setTEMP_INITIAL(LASTTEMP);
////  PDH_Heat_Data.setHM_WEIGHT_START(REMSTEELMASS);
////  PDH_Heat_Data.setCALC_MODE(CALC_MODE);
////  PDH_Heat_Data.setTREAT_TYPE_OPER(TREAT_TYPE_OPER);
////  PDH_Heat_Data.setTREAT_TYPE_MODEL(0);
////  PDH_Heat_Data.setLADLENO(m_LadleNo);
////  PDH_Heat_Data.setLADLETYPE(m_LadleType);
////  PDH_Heat_Data.setCAST_ID(CAST_ID);
////
////  if (PDH_Heat_Data.select(m_Plant, m_HeatID, m_TreatID))
////  {
////    RetValue = PDH_Heat_Data.update();
////    if (RetValue)
////      PDH_Heat_Data.commit();
////    else
////      PDH_Heat_Data.rollback();
////  }
////  else
////  {
////    RetValue = PDH_Heat_Data.insert();
////    if (RetValue)
////      PDH_Heat_Data.commit();
////    else
////      PDH_Heat_Data.rollback();
////  }
////
////  return RetValue;
////}
////
////bool CARCHIVER_HMDAnnouncementPresettings::writePD_HEATDATA()
////{
////  bool RetValue = false;
////  CDateTime Now;
////  CPD_HEAT_DATA PD_Heatdata(m_pConnection);
////
////  if (PD_Heatdata.select(m_HeatID, m_TreatID, m_Plant))
////  {
////    PD_Heatdata.setTREATSTART_ACT(Now);
////
////    RetValue = PD_Heatdata.update();
////    if (RetValue)
////      PD_Heatdata.commit();
////    else
////      PD_Heatdata.rollback();
////  }
////  return RetValue;
////}
////
////bool CARCHIVER_HMDAnnouncementPresettings::writePD_LADLE()
////{
////  bool RetValue = false;
////  CPD_LADLE PD_Ladle(m_pConnection);
////
//////SS  if (PD_Ladle.select(m_LadleNo, m_LadleType))
////  int i=1;
////  if (PD_Ladle.select(i, m_LadleType)) //SS
////  {
////    if (m_PlantID == DEF_HMD_PLANTS::HMD_1)
////		PD_Ladle.setLADLEPOSID(DEF_GC_LADLE_POS::DS1); //SS  ::HMLadleOnHMD1);
////            //.setLDLPOSID
////    else if (m_PlantID == DEF_HMD_PLANTS::HMD_2)
//// 		PD_Ladle.setLADLEPOSID(DEF_GC_LADLE_POS::DS2); //SS ::HMLadleOnHMD2);
////                 //SS  .setLDLPOSID  
////    RetValue = PD_Ladle.update();
////    if (RetValue)
////      PD_Ladle.commit();
////    else
////      PD_Ladle.rollback();
////  }
  return RetValue;
}

bool CARCHIVER_HMDAnnouncementPresettings::writePD_LADLE_DATA()
{
  bool RetValue = false;
  // SS CPD_LADLE_DATA PD_Ladle_Data(m_pConnection);

  // SS if (PD_Ladle_Data.select(m_LadleType, m_LadleNo, "LAST"))
  // SS {
  // SS   PD_Ladle_Data.setTAP_ID(m_HeatID);
  // SS   if (HEATID_CON != CSMC_DBData::unspecString)
  // SS   {
  // SS     PD_Ladle_Data.setHEATID(HEATID_CON);
  // SS     PD_Ladle_Data.setTREATID(TREATID_CON);
      //PD_Ladle_Data.setHEATID(m_HeatID);
      //PD_Ladle_Data.setTREATID(m_TreatID);
  // SS   }

    //SS RetValue = PD_Ladle_Data.update();
    //SS if (RetValue)
    //SS   PD_Ladle_Data.commit();
    //SS else
    //SS   PD_Ladle_Data.rollback();
  // SS }
  return RetValue;
}

bool CARCHIVER_HMDAnnouncementPresettings::writeAll()
{
  bool RetValue = true;

	if(!writePDH_HEAT_DATA())
    RetValue = false;

	if(!writePD_HEATDATA())
    RetValue = false;

	if(!writePD_LADLE())
    RetValue = false;

	if(!writePD_LADLE_DATA())
    RetValue = false;

  return RetValue;
}

void CARCHIVER_HMDAnnouncementPresettings::initDBClasses()
{
}

void CARCHIVER_HMDAnnouncementPresettings::deleteDBClasses()
{
}


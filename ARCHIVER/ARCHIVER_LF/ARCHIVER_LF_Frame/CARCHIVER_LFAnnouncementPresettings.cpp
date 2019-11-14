#include "CARCHIVER_LFAnnouncementPresettings.h"

CARCHIVER_LFAnnouncementPresettings::CARCHIVER_LFAnnouncementPresettings()
{
}

void CARCHIVER_LFAnnouncementPresettings::initialize(const std::string& HeatID, const std::string& TreatID, 
                                                        const std::string& CustHeatID, const std::string& CustTreatID, const std::string& Plant, 
                                                        long PlantNo, const std::string& LadleType, const std::string& LadleNo,
                                                        const std::string& UserCode, const CDateTime& RevTime)
{
  m_pConnection = CARCHIVER_LFTask::getInstance()->getpConnection();
  if (!m_pConnection)
  {
    handleDBConnectionError();
  }
  initDBClasses();

  CDateTime Now;

  m_HeatID = HeatID;
  m_TreatID = TreatID;
  m_CustHeatID = CustHeatID;
  m_CustTreatID = CustTreatID;
  m_Plant = Plant;;
  m_PlantNo = PlantNo;
  m_LadleNo = LadleNo;
  m_LadleType = LadleType;
  m_UserCode = "USAD";//UserCode;
  m_HEATASSIGNMENTDATE.resetTime();
  m_RevTime = RevTime;

  m_WEEKNO = 0;
  m_MONTHNO = 0;
  m_DRI_FEED_MODE_CODE = 1;
  HEATING_MODE = 0;
  AIMHOTHEEL_LF = 0;
  SHIFTCODE = 0;
  PRODPRAC_ID = 0;
  AIMTEMP = 0;
  LASTTEMP = 0;
  HEATSTATORDER = 0;
  LIQADDNO = 1;
  REMSTEELMASS = 0.0;
  REMSLAGMASS = 0.0;
  WEIGHTSTEEL = 0.0;
  WEIGHTSLAG = 0.0;
  TEMP = 0.0;
  ANL = -1.0;
  TREATID_LAST = "1";
  LASTPLANT = "HMD";

  //EQUIP DATA from GDC_EQUIP_STRUCT
  ELECTRODE1_STRUCT_ID = 4010;// + m_PlantNo*100;
  ELECTRODE2_STRUCT_ID = 4020;// + m_PlantNo*100;
  ELECTRODE3_STRUCT_ID = 4030;// + m_PlantNo*100;
  ROOF_STRUCT_ID       = 4040;// + m_PlantNo*100;

  //PP_HEAT
  if (m_pPP_HEAT->select(m_CustHeatID))
  {
    ROUTECODEACT = m_pPP_HEAT->getROUTECODEACT(1);
    PRODORDERID  = m_pPP_HEAT->getPRODORDERID(1);
    HEATSTATORDER = m_pPP_HEAT->getHEATSTATORDER(1);
  }

  //PP_HEAT_PLANT
  if (m_pPP_HEAT_PLANT->select(m_HeatID, m_TreatID, m_Plant, m_PlantNo))
  {
    PLANTREATEND = m_pPP_HEAT_PLANT->getPLANTREATEND(1);
    PLANTREATSTART = m_pPP_HEAT_PLANT->getPLANTREATSTART(1);
    std::string Date = PLANTREATSTART.toDBString().substr(0,10);
    SHIFTSTARTDATE.fromDBString(Date);
  }

  //PP_ORDER
  if (m_pPP_ORDER->select(PRODORDERID))
  {
    STEELGRADECODE = m_pPP_ORDER->getSTEELGRADECODE(1);
    HEATING_MODE = m_pPP_ORDER->getHEATING_MODE(1);
  }

  //GC_SHIFT_CODE
  if (m_pGC_SHIFT_CODE->select(Now))
  {
    SHIFTCODE = m_pGC_SHIFT_CODE->getSHIFTCODE(1);
  }

  //PP_SHIFT_CREW_ASSIGNMENT
  if (m_pPP_Shift_Crew_Assignement->select(SHIFTSTARTDATE, m_Plant, m_PlantNo, SHIFTCODE))
  {
    CREWCODE = m_pPP_Shift_Crew_Assignement->getCREWCODE(1);
  }
  //PP_GRADE
  if (m_pPP_Grade->select(STEELGRADECODE))
  {
    STEELGRADECODEDESC = m_pPP_Grade->getSTEELGRADECODEDESC(1);
    STEELGRADECODEDESC_C = m_pPP_Grade->getSTEELGRADECODEDESC_C(1);
  }
  //PP_GRADE_PRODPRAC
  if (m_pPP_Grade_ProdPrac->select(STEELGRADECODE, m_Plant, "Parameter"))
  {
    DESCR_PP = m_pPP_Grade_ProdPrac->getDESCR_PP(1);
    PRODPRAC_ID = m_pPP_Grade_ProdPrac->getPRODPRAC_ID(1);
  }
  //PP_GRADE_SINGLE_AIMS
  if (m_pPP_Grade_Single_Aims->select(STEELGRADECODE, m_Plant))
  {
    AIMTEMP = m_pPP_Grade_Single_Aims->getAIMTEMP(1);
  }

  //PD_LADLE
  if (m_pPD_LADLE->select(m_LadleNo, m_LadleType))
  {
    REMSTEELMASS = m_pPD_LADLE->getREMSTEELMASS(1);
    REMSLAGMASS = m_pPD_LADLE->getREMSLAGMASS(1);
    LADLETHERMSTATID = m_pPD_LADLE->getLADLETHERMSTATID(1);
  }
  
  //PD_LADLE_DATA
  if (m_pPD_LADLE_Data->select(m_LadleType, m_LadleNo, "LAST"))
  {
    LASTTEMPTIME = m_pPD_LADLE_Data->getLASTTEMPTIME(1);
    LASTTEMP = m_pPD_LADLE_Data->getLASTTEMP(1);
  } 

  //PDC_EQUIP_MOUNT
  {
  if (m_pPDC_Equip_Mount->selectWithSTRUCT_ID(ELECTRODE1_STRUCT_ID))
  {
    ELECTRODE1_EQUIP_ID = m_pPDC_Equip_Mount->getEQUIP_ID(1);
    ELECTRODE1_PRI_COUNTER = m_pPDC_Equip_Mount->getPRI_COUNTER(1) + 1;
  }
  if (m_pPDC_Equip_Mount->selectWithSTRUCT_ID(ELECTRODE2_STRUCT_ID))
  {
    ELECTRODE2_EQUIP_ID = m_pPDC_Equip_Mount->getEQUIP_ID(1);
    ELECTRODE2_PRI_COUNTER = m_pPDC_Equip_Mount->getPRI_COUNTER(1) + 1;
  }
  if (m_pPDC_Equip_Mount->selectWithSTRUCT_ID(ELECTRODE3_STRUCT_ID))
  {
    ELECTRODE3_EQUIP_ID = m_pPDC_Equip_Mount->getEQUIP_ID(1);
    ELECTRODE3_PRI_COUNTER = m_pPDC_Equip_Mount->getPRI_COUNTER(1) + 1;
  }
  if (m_pPDC_Equip_Mount->selectWithSTRUCT_ID(ROOF_STRUCT_ID))
  {
    ROOF_EQUIP_ID = m_pPDC_Equip_Mount->getEQUIP_ID(1);
    ROOF_PRI_COUNTER = m_pPDC_Equip_Mount->getPRI_COUNTER(1) + 1;
  }
  }
}

CARCHIVER_LFAnnouncementPresettings::~CARCHIVER_LFAnnouncementPresettings()
{
  deleteDBClasses();
}
bool CARCHIVER_LFAnnouncementPresettings::writePD_REPORT()
{
  bool RetValue = false;

  CDateTime Now;

  m_pPD_Report->setHEATID(m_HeatID);
  m_pPD_Report->setTREATID(m_TreatID);
  m_pPD_Report->setPLANT(m_Plant);
  m_pPD_Report->setPLANTNO(m_PlantNo);
  m_pPD_Report->setREVTIME(m_RevTime);
  m_pPD_Report->setCREWID(CREWCODE);
  m_pPD_Report->setSHIFT(SHIFTCODE);
  m_pPD_Report->setWEEKNO(m_WEEKNO);
  m_pPD_Report->setMONTHNO(m_MONTHNO);
  m_pPD_Report->setANNOUCETIME(Now);
  m_pPD_Report->setHEATASSIGNMENTDATE(m_HEATASSIGNMENTDATE);
  m_pPD_Report->setDELAYDUR(0.0);
  m_pPD_Report->setTREATDUR(0.0);
  m_pPD_Report->setLASTTEMPTIME(LASTTEMPTIME);
  m_pPD_Report->setLASTTEMP(LASTTEMP);
  m_pPD_Report->setSTARTSTEELWEIGHT(REMSTEELMASS);
  m_pPD_Report->setSTARTSLAGWEIGHT(REMSLAGMASS);
  m_pPD_Report->setFINALSTEEL(REMSTEELMASS);
  m_pPD_Report->setFINALSLAG(REMSLAGMASS);
  m_pPD_Report->setLADLETYPEIN(m_LadleType);
  m_pPD_Report->setLADLENO_IN(m_LadleNo);
  m_pPD_Report->setLADLETYPE_OUT(m_LadleType);
  m_pPD_Report->setLADLENO_OUT(m_LadleNo);
  m_pPD_Report->setSTEELGRADECODE(STEELGRADECODE);
  m_pPD_Report->setSTEELGRADECODEDESC(STEELGRADECODEDESC);
  m_pPD_Report->setPRODORDERID(PRODORDERID);
  m_pPD_Report->setSTEELGRADECODEDESC_C(STEELGRADECODEDESC_C);
  m_pPD_Report->setTOTAL_ELEC_EGY(0.0);
  m_pPD_Report->setTEMPPROBESNO(0);
  m_pPD_Report->setSLAGPROBESNO(0);
  m_pPD_Report->setSTEELPROBESNO(0);
  m_pPD_Report->setELECTRODE_CONSUMPTION(0);
  m_pPD_Report->setROUTECODE(ROUTECODEACT);
  m_pPD_Report->setUSERCODE(m_UserCode);
  m_pPD_Report->setPRODUCTIONORDERID_PLAN(PRODORDERID);
  m_pPD_Report->setSTEELGRADECODE_PLAN(STEELGRADECODE);
  m_pPD_Report->setSTEELGRADEDESC_PLAN(STEELGRADECODEDESC);
  m_pPD_Report->setHOTHEELWEIGHT(0.0);
  m_pPD_Report->setAIMSTEELWEIGHT_PLAN(REMSTEELMASS);
  m_pPD_Report->setAIMSTEELWEIGHT_MOD(REMSTEELMASS);
  m_pPD_Report->setFINALWEIGHT(REMSTEELMASS);
  m_pPD_Report->setTOTALCHARGEDWEIGHT(REMSTEELMASS);
  m_pPD_Report->setAIMTEMP_PLAN(AIMTEMP);
  m_pPD_Report->setAIMTEMP_MOD(AIMTEMP);
  m_pPD_Report->setFINALTEMPCALC(AIMTEMP);
  m_pPD_Report->setTREATSTART_PLAN(PLANTREATSTART);
  m_pPD_Report->setTREATSTART_MOD(PLANTREATSTART);
  m_pPD_Report->setTREATEND_PLAN(PLANTREATEND);
  m_pPD_Report->setTREATEND_MOD(PLANTREATEND);
  m_pPD_Report->setCHARGETOTAPDURATION(0.0);
  m_pPD_Report->setTAPTOTAPDURATION(0.0);
  m_pPD_Report->setTIMELASTTEMPBEFTAP(LASTTEMPTIME);

  if (m_pPD_Report->select(m_HeatID, m_TreatID, m_Plant))
  {
    RetValue = m_pPD_Report->update();
    if (RetValue)
      m_pPD_Report->commit();
    else
      m_pPD_Report->rollback();
  }
  else
  {
    RetValue = m_pPD_Report->insert();
    if (RetValue)
      m_pPD_Report->commit();
    else
      m_pPD_Report->rollback();
  }
  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_REPORT(long WEEKNO, long MONTHNO, 
                                              const CDateTime& ANNOUNCETIME, const CDateTime& HEATASSIGNMENTDATE)
{
  bool RetValue = false;

  m_ANNOUNCETIME = ANNOUNCETIME;
  m_HEATASSIGNMENTDATE = HEATASSIGNMENTDATE;
  m_WEEKNO = WEEKNO;
  m_MONTHNO = MONTHNO;
  RetValue = writePD_REPORT();

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_HEATDATA()
{
  bool RetValue = false;

  m_pPD_Heatdata->setHEATID(m_HeatID);
  m_pPD_Heatdata->setTREATID(m_TreatID);
  m_pPD_Heatdata->setPLANT(m_Plant);
  m_pPD_Heatdata->setPRODORDERID_PLAN(PRODORDERID);
  m_pPD_Heatdata->setPRODUCTIONORDERID_ACT(PRODORDERID);
  m_pPD_Heatdata->setSTEELGRADECODE_PLAN(STEELGRADECODE);
  m_pPD_Heatdata->setSTEELGRADECODE_ACT(STEELGRADECODE);
  m_pPD_Heatdata->setCREWCODE(CREWCODE);
  m_pPD_Heatdata->setSHIFTCODE(SHIFTCODE);
  m_pPD_Heatdata->setAIMSTEELWGT_PLAN(REMSTEELMASS);
  m_pPD_Heatdata->setAIMSTEELWGT_MOD(REMSTEELMASS);
  m_pPD_Heatdata->setAIMTEMP_PLAN(AIMTEMP);
  m_pPD_Heatdata->setAIMTEMP_MOD(AIMTEMP);
  m_pPD_Heatdata->setTREATSTART_PLAN(PLANTREATSTART);
  m_pPD_Heatdata->setTREATSTART_MOD(PLANTREATSTART);
  m_pPD_Heatdata->setTREATEND_PLAN(PLANTREATEND);
  m_pPD_Heatdata->setTREATEND_MOD(PLANTREATEND);
  m_pPD_Heatdata->setREVTIME(m_RevTime);
  m_pPD_Heatdata->setGUNNINGAMOUNT(0.0);
  m_pPD_Heatdata->setCARNO(1);
  m_pPD_Heatdata->setUSERCODE(m_UserCode);
  m_pPD_Heatdata->setAIMSTEELWGT_CALC(0.0);
  m_pPD_Heatdata->setUSELANCE(1);
  m_pPD_Heatdata->setTHERMFURNACESTATID(LADLETHERMSTATID);
  m_pPD_Heatdata->setPLANTNO(m_PlantNo);
  m_pPD_Heatdata->setLADLENO(m_LadleNo);
  m_pPD_Heatdata->setLADLETYPE(m_LadleType);
  
  if (m_pPD_Heatdata->select(m_HeatID, m_TreatID, m_Plant))
  {
    RetValue = m_pPD_Heatdata->update();
    if (RetValue)
      m_pPD_Heatdata->commit();
    else
      m_pPD_Heatdata->rollback();
  }
  else
  {
    RetValue = m_pPD_Heatdata->insert();
    if (RetValue)
      m_pPD_Heatdata->commit();
    else
      m_pPD_Heatdata->rollback();
  }

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_HEATDATA_LIQADD()
{
  bool RetValue = false;
  CDateTime Now;

  m_pPD_HEAT_DATA_LIQADD->setHEATID(m_HeatID);
  m_pPD_HEAT_DATA_LIQADD->setTREATID(m_TreatID);
  m_pPD_HEAT_DATA_LIQADD->setPLANT(m_Plant);
  m_pPD_HEAT_DATA_LIQADD->setLIQADDNO(1);
  m_pPD_HEAT_DATA_LIQADD->setDISCHAARGETIME(Now);
  m_pPD_HEAT_DATA_LIQADD->setSTEELWEIGHT(REMSTEELMASS);
  m_pPD_HEAT_DATA_LIQADD->setSLAGWEIGHT(REMSLAGMASS);
  m_pPD_HEAT_DATA_LIQADD->setSCULLWEIGHT(0.0);
  m_pPD_HEAT_DATA_LIQADD->setTEMPERATURE(TEMP);
  m_pPD_HEAT_DATA_LIQADD->setSOURCE("H");
  m_pPD_HEAT_DATA_LIQADD->setSTATUS("CHARGED");
  m_pPD_HEAT_DATA_LIQADD->setMANUALCHANGED(0);
  
  if (m_pPD_HEAT_DATA_LIQADD->select(m_HeatID, m_TreatID, m_Plant, LIQADDNO))
  {
    RetValue = m_pPD_HEAT_DATA_LIQADD->update();
    if (RetValue)
      m_pPD_HEAT_DATA_LIQADD->commit();
    else
      m_pPD_HEAT_DATA_LIQADD->rollback();
  }
  else
  {
    RetValue = m_pPD_HEAT_DATA_LIQADD->insert();
    if (RetValue)
      m_pPD_HEAT_DATA_LIQADD->commit();
    else
      m_pPD_HEAT_DATA_LIQADD->rollback();
  }
  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_HEATDATA_LIQADD_ANL()
{
  bool RetValue = false;
  if (m_pPD_LADLE_Anl->select(m_LadleType, m_LadleNo, "LAST", CSMC_DBData::unspecString))
  {
    for (long i = 1; i <= m_pPD_LADLE_Anl->getLastRow(); ++i)
    {
      m_pPD_HEAT_DATA_LIQADD_Anl->setHEATID(m_HeatID);
      m_pPD_HEAT_DATA_LIQADD_Anl->setTREATID(m_HeatID);
      m_pPD_HEAT_DATA_LIQADD_Anl->setPLANT(m_Plant);
      m_pPD_HEAT_DATA_LIQADD_Anl->setLIQADDNO(LIQADDNO);
      ENAME = m_pPD_LADLE_Anl->getENAME(i);
      m_pPD_HEAT_DATA_LIQADD_Anl->setENAME(ENAME);
      ANL = m_pPD_LADLE_Anl->getANL(i);
      m_pPD_HEAT_DATA_LIQADD_Anl->setANL(ANL);

      if (m_pPD_HEAT_DATA_LIQADD_Anl->select(LIQADDNO, m_TreatID, m_HeatID, ENAME, m_Plant))
      {
        RetValue = m_pPD_HEAT_DATA_LIQADD_Anl->update();
        if (RetValue)
          m_pPD_HEAT_DATA_LIQADD_Anl->commit();
        else
          m_pPD_HEAT_DATA_LIQADD_Anl->rollback();
      }
      else
      {
        RetValue = m_pPD_HEAT_DATA_LIQADD_Anl->insert();
        if (RetValue)
          m_pPD_HEAT_DATA_LIQADD_Anl->commit();
        else
          m_pPD_HEAT_DATA_LIQADD_Anl->rollback();
      }
    }
  }

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_PRETREATDATA()
{
  bool RetValue = false;
  CDateTime Now;

  m_pPD_PRETREATDATA->setHEATID(m_HeatID);
  m_pPD_PRETREATDATA->setSTEELWEIGHT(REMSTEELMASS);
  m_pPD_PRETREATDATA->setREVTIME(Now);
  m_pPD_PRETREATDATA->setSLAGWEIGHT(REMSLAGMASS);
  m_pPD_PRETREATDATA->setSCULLWEIGHT(0.0);
  m_pPD_PRETREATDATA->setTEMPERATURE(LASTTEMP);
  m_pPD_PRETREATDATA->setTEMPTIMEMEAS(LASTTEMPTIME);
  m_pPD_PRETREATDATA->setLADLETYPE(m_LadleType);
  m_pPD_PRETREATDATA->setLADLENO(m_LadleNo);
  m_pPD_PRETREATDATA->setHEATSTATORDER(HEATSTATORDER);
  m_pPD_PRETREATDATA->setUSERCODE(m_UserCode);
  m_pPD_PRETREATDATA->setTREATID_LAST(TREATID_LAST);
  m_pPD_PRETREATDATA->setSLAB_PRODUCED(0);

  if (m_pPD_PRETREATDATA->select(m_HeatID))
  {
    RetValue = m_pPD_PRETREATDATA->update();
    if (RetValue)
      m_pPD_PRETREATDATA->commit();
    else
      m_pPD_PRETREATDATA->rollback();
  }
  else
  {
    RetValue = m_pPD_PRETREATDATA->insert();
    if (RetValue)
      m_pPD_PRETREATDATA->commit();
    else
      m_pPD_PRETREATDATA->rollback();
  }

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_PRETREAT_ANL()
{
  bool RetValue = false;
  if (m_pPD_LADLE_Anl->select(m_LadleType, m_LadleNo, "LAST", CSMC_DBData::unspecString))
  {
    for (long i = 1; i <= m_pPD_LADLE_Anl->getLastRow(); ++i)
    {
      m_pPD_Pretreat_Anl->setHEATID(m_HeatID);
      m_pPD_Pretreat_Anl->setENAME(m_pPD_LADLE_Anl->getENAME(i));
      m_pPD_Pretreat_Anl->setANL(m_pPD_LADLE_Anl->getANL(i));

      if (m_pPD_Pretreat_Anl->select(m_HeatID, m_pPD_LADLE_Anl->getENAME(i)))
      {
        RetValue = m_pPD_Pretreat_Anl->update();
        if (RetValue)
          m_pPD_Pretreat_Anl->commit();
        else
          m_pPD_Pretreat_Anl->rollback();
      }
      else
      {
        RetValue = m_pPD_Pretreat_Anl->insert();
        if (RetValue)
          m_pPD_Pretreat_Anl->commit();
        else
          m_pPD_Pretreat_Anl->rollback();
      }
    }
  }

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writePD_HEAT_DATA_PRODPRAC()
{
  bool RetValue = false;

  m_pPD_HEAT_DATA_PRODPRAC->setHEATID(m_HeatID);
  m_pPD_HEAT_DATA_PRODPRAC->setTREATID(m_TreatID);
  m_pPD_HEAT_DATA_PRODPRAC->setPLANT(m_Plant);
  m_pPD_HEAT_DATA_PRODPRAC->setSTEELGRADECODE_ACT(STEELGRADECODE);
  m_pPD_HEAT_DATA_PRODPRAC->setDESCR_PP(DESCR_PP);
  m_pPD_HEAT_DATA_PRODPRAC->setPRODPRACID_PLAN(PRODPRAC_ID);
  m_pPD_HEAT_DATA_PRODPRAC->setPRODPRACID_MOD(PRODPRAC_ID);

  if (m_pPD_HEAT_DATA_PRODPRAC->select(m_Plant, m_TreatID, m_HeatID, DESCR_PP))
  {
    RetValue = m_pPD_HEAT_DATA_PRODPRAC->update();
    if (RetValue)
      m_pPD_HEAT_DATA_PRODPRAC->commit();
    else
      m_pPD_HEAT_DATA_PRODPRAC->rollback();
  }
  else
  {
    RetValue = m_pPD_HEAT_DATA_PRODPRAC->insert();
    if (RetValue)
      m_pPD_HEAT_DATA_PRODPRAC->commit();
    else
      m_pPD_HEAT_DATA_PRODPRAC->rollback();
  }
  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writeAll()
{
  bool RetValue = false;

	if(writePD_REPORT())
    RetValue = true;
  else
    RetValue = false;

  if (RetValue && writePD_HEATDATA())
    RetValue = true;
  else
    RetValue = false;

  if (RetValue && writePD_HEATDATA())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_HEATDATA_LIQADD())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_HEATDATA_LIQADD_ANL())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_PRETREATDATA())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_PRETREAT_ANL())
    RetValue = true;
  else
    RetValue = false;

  if (RetValue && writePD_HEAT_DATA_PRODPRAC())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_HEAT_DATA_PRODPRAC())
    RetValue = true;
  else
    RetValue = false;

  return RetValue;
}

bool CARCHIVER_LFAnnouncementPresettings::writeAll(long WEEKNO, long MONTHNO, const CDateTime&  ANNOUNCETIME, 
                                              const CDateTime& HEATASSIGNMENTDATE, long DRI_FEED_MODE_CODE)
{
  bool RetValue = false;
	if(writePD_REPORT(WEEKNO, MONTHNO, ANNOUNCETIME, HEATASSIGNMENTDATE))
    RetValue = true;
  else
    RetValue = false;

  if (RetValue && writePD_HEATDATA())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_HEATDATA_LIQADD())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_HEATDATA_LIQADD_ANL())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_PRETREATDATA())
    RetValue = true;
  else
    RetValue = false;

	if (RetValue && writePD_PRETREAT_ANL())
    RetValue = true;
  else
    RetValue = false;

  if (RetValue && writePD_HEAT_DATA_PRODPRAC())
    RetValue = true;
  else
    RetValue = false;

  return RetValue;
}

void CARCHIVER_LFAnnouncementPresettings::initDBClasses()
{
  m_pPP_Shift_Crew_Assignement = new CPP_SHIFT_CREW_ASSIGNMENT(m_pConnection);
  m_pPP_Grade_Single_Aims = new CPP_GRADE_SINGLE_AIMS(m_pConnection);
  m_pGC_SHIFT_CODE = new CGC_SHIFT_CODE(m_pConnection);
  m_pPD_HEAT_DATA_LIQADD_Anl = new CPD_HEATDATA_LIQADD_ANL(m_pConnection);
  m_pPD_HOTHEEL_Anl_Entry = new CPD_HOTHEEL_ANL_ENTRY(m_pConnection);
  m_pPDC_Equip_Mount = new CPDC_EQUIP_MOUNT(m_pConnection);
  m_pPD_HOTHEEL = new CPD_HOTHEEL(m_pConnection);
  m_pPD_LADLE = new CPD_LADLE(m_pConnection);
  m_pPD_LADLE_Data = new CPD_LADLE_DATA(m_pConnection);
  m_pPD_Report = new CPD_REPORT(m_pConnection);
  m_pPP_Grade = new CPP_GRADE(m_pConnection);
  m_pPP_Grade_ProdPrac = new CPP_GRADE_PRODPRAC(m_pConnection);
  m_pPP_HEAT = new CPP_HEAT(m_pConnection);
  m_pPP_HEAT_PLANT = new CPP_HEAT_PLANT(m_pConnection);
  m_pPP_ORDER = new CPP_ORDER(m_pConnection);
  m_pPD_Heatdata = new CPD_HEATDATA(m_pConnection);
  m_pPD_HEAT_DATA_LIQADD = new CPD_HEATDATA_LIQADD(m_pConnection);
  m_pPD_HEAT_DATA_PRODPRAC = new CPD_HEAT_DATA_PRODPRAC(m_pConnection);
  m_pPD_LADLE_Anl = new CPD_LADLE_ANL(m_pConnection);
  m_pPD_PRETREATDATA = new CPD_PRETREATDATA(m_pConnection);
  m_pPD_Pretreat_Anl = new CPD_PRETREAT_ANL(m_pConnection);
}

void CARCHIVER_LFAnnouncementPresettings::deleteDBClasses()
{
  if (m_pPD_HEAT_DATA_PRODPRAC) delete m_pPD_HEAT_DATA_PRODPRAC;
  if (m_pPD_LADLE_Anl) delete m_pPD_LADLE_Anl;
  if (m_pPD_PRETREATDATA) delete m_pPD_PRETREATDATA;
  if (m_pPD_Pretreat_Anl) delete m_pPD_Pretreat_Anl;
  if (m_pPD_Heatdata) delete m_pPD_Heatdata;
  if (m_pPD_HEAT_DATA_LIQADD) delete m_pPD_HEAT_DATA_LIQADD;
  if (m_pPD_HOTHEEL) delete m_pPD_HOTHEEL;
  if (m_pPD_LADLE) delete m_pPD_LADLE;
  if (m_pPD_LADLE_Data) delete m_pPD_LADLE_Data;
  if (m_pPD_Report) delete m_pPD_Report;
  if (m_pPP_Grade) delete m_pPP_Grade;
  if (m_pPP_Grade_ProdPrac) delete m_pPP_Grade_ProdPrac;
  if (m_pPP_HEAT) delete m_pPP_HEAT;
  if (m_pPP_ORDER) delete m_pPP_ORDER;
  if (m_pPP_HEAT_PLANT) delete m_pPP_HEAT_PLANT;
  if (m_pPP_Shift_Crew_Assignement) delete m_pPP_Shift_Crew_Assignement;
  if (m_pPP_Grade_Single_Aims) delete m_pPP_Grade_Single_Aims;
  if (m_pGC_SHIFT_CODE) delete m_pGC_SHIFT_CODE;
  if (m_pPD_HEAT_DATA_LIQADD_Anl) delete m_pPD_HEAT_DATA_LIQADD_Anl;
  if (m_pPD_HOTHEEL_Anl_Entry) delete m_pPD_HOTHEEL_Anl_Entry;
  if (m_pPDC_Equip_Mount) delete m_pPDC_Equip_Mount;
}

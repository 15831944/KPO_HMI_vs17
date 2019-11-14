// Copyright (C) 2008 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_ANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED
#define _INC_CARCHIVER_ANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED

#include <string>
#include <string>
#include "CARCHIVER_Task.h"
#include "iSMC_DataDefinitions_s.hh"
#include "CPP_SHIFT_CREW_ASSIGNMENT.h"
#include "CGT_GRADE_SINGLE_AIMS.h"
#include "CGC_SHIFT_CODE.h"
#include "CPD_EQUIP_MOUNT.h"
#include "CARCHIVER_Wrapper.h"
#include "CPD_HOTHEEL.h";
#include "CPD_HEAT_DATA.h";
#include "CPD_HEAT_DATA_LIQADD.h";
#include "CPD_LADLE.h";
#include "CGT_GRADE.h";
#include "CGT_GRADE_PRODPRAC.h";
#include "CPP_HEAT.h";
#include "CPP_HEAT_PLANT.h";
#include "CPP_ORDER.h";
#include "CPD_HEAT_DATA_PRODPRAC.h";
#include "CPD_PRETREATDATA.h";
// #include "CPD_PRETREAT_ANL.h";
#include "CPDE_HEAT_DATA.h";
//#include "CPDF_HEAT_DATA.h";
#include "CGT_GRADE.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CGT_GRADE_SINGLE_AIMS.h"

#define PartCode_LadleBottom "LB"
#define PartCode_Wall "LW"
#define PartCode_Plug1 "PP1"
#define PartCode_SlideGate "SG"
#define PartCode_UpNozzle "UN"
#define PartCode_Plug2 "PP2"
#define PartCode_LowZozzle "LN"
#define PartCode_BotPlate "BP"
#define PartCode_SlagZone "LSZ"
#define PartCode_SteelZone "???????"  // did not find in database table
#define PartCode_WellBlock1 "WB1"
#define PartCode_WellBlock2 "WB2"

class CARCHIVER_Task;

class CARCHIVER_AnnouncementPresettings 
: public CARCHIVER_Wrapper
{ 
public:
  CARCHIVER_AnnouncementPresettings();
  ~CARCHIVER_AnnouncementPresettings();

  //zhpf
  void initialize( const std::string& HeatID, 
                   const std::string& TreatID, 
                   const std::string& CustHeatID, 
                   const std::string& CustTreatID, 
                   const std::string& Plant, 
                   long PlantNo, 
                   const std::string& LadleType, 
                   long LadleNo,
                   const std::string& UserCode, 
                   const CDateTime& RevTime,
                   long HeatingMode );

  bool writePD_HEAT_DATA();
  bool writePD_HEATDATA_LIQADD();
  bool writePD_HEATDATA_LIQADD_ANL();
  bool writePD_PRETREATDATA();
  bool writePD_PRETREAT_ANL();
  bool writePD_HEAT_DATA_PRODPRAC();
  bool writeAll();
  bool writeAll( long WEEKNO, 
                 long MONTHNO, 
                 const CDateTime&  ANNOUNCETIME, 
                 const CDateTime& HEATASSIGNMENTDATE, 
                 long DRI_FEED_MODE_CODE);

protected:
  virtual void initDBClasses();
  virtual void deleteDBClasses();

//private:
  CPP_SHIFT_CREW_ASSIGNMENT *m_pPP_Shift_Crew_Assignement;
  CGT_GRADE_SINGLE_AIMS     *m_pPP_Grade_Single_Aims;
  CGC_SHIFT_CODE            *m_pGC_SHIFT_CODE;
  //CPD_HEAT_DATA_LIQADD_ANL   *m_pPD_HEAT_DATA_LIQADD_Anl;
  //CPD_HOTHEEL_ANL_ENTRY     *m_pPD_HOTHEEL_Anl_Entry;
  CPD_EQUIP_MOUNT           *m_pPD_Equip_Mount;
  CPD_HOTHEEL               *m_pPD_HOTHEEL;
  CPD_LADLE                 *m_pPD_LADLE;
  //CPD_LADLE_DATA            *m_pPD_LADLE_Data;
  CGT_GRADE                 *m_pPP_Grade;
  CGT_GRADE_PRODPRAC        *m_pPP_Grade_ProdPrac;
  CPP_HEAT                  *m_pPP_HEAT;
  CPP_HEAT_PLANT            *m_pPP_HEAT_PLANT;
  CPP_ORDER                 *m_pPP_ORDER;
  //zhpf,pd_heat_data
  CPD_HEAT_DATA             *m_pPD_HEAT_DATA;
  CPD_HEAT_DATA_LIQADD       *m_pPD_HEAT_DATA_LIQADD;
  CPD_HEAT_DATA_PRODPRAC    *m_pPD_HEAT_DATA_PRODPRAC;
  CPD_PRETREATDATA          *m_pPD_PRETREATDATA;
  //CPD_PRETREAT_ANL          *m_pPD_Pretreat_Anl;
  CGT_GRADE                 *m_pGT_Grade;
  CGT_GRADE_PRODPRAC        *m_pGT_Grade_ProdPrac;
  CGT_GRADE_SINGLE_AIMS     *m_pGT_Grade_Single_Aims;
  //CPD_HEAT_DATA_LIQADD_ANL   *m_pPD_HEAT_DATA_LIQADD_Anl;

  std::string m_HeatID;
  std::string m_TreatID;
  std::string m_CustHeatID;
  std::string m_CustTreatID;
  std::string m_Plant;
  long        m_PlantNo;
  std::string m_LadleType;
  //zhpf
  long m_LadleNo;
  long        m_HeatingMode;
  std::string m_UserCode;
  CDateTime   m_RevTime;
  long        m_WEEKNO;
  long        m_MONTHNO;
  long        SHIFTCODE;
  long        PRODPRAC_ID;
  long        AIMTEMP;
  long        LASTTEMP;
  long        HEATSTATORDER;
  long        LIQADDNO;
  double      REMSTEELMASS;
  double      WEIGHTSTEEL;
  double      REMSLAGMASS;
  double      WEIGHTSLAG;
  double      TEMP;
  CDateTime   TEMP_TIME;
  double      ANL;
  CDateTime   ANL_TIME;
  CDateTime   LASTANLTIME;
  std::string TREATID_LAST;
  std::string SAMPLEID;
  std::string LASTPLANT;
  CDateTime   m_ANNOUNCETIME;
  CDateTime   m_HEATASSIGNMENTDATE;

  CDateTime   PLANTREATEND;
  CDateTime   PLANTREATSTART;
  CDateTime   SHIFTSTARTDATE;
  CDateTime   LASTTEMPTIME;
  std::string LADLETHERMSTATID;
  std::string DESCR_PP;
  std::string STEELGRADECODE;
  std::string STEELGRADECODEDESC;
  std::string STEELGRADECODEDESC_C;
  std::string ROUTECODEACT;
  std::string PRODORDERID;
  std::string CREWCODE;
  std::string HEATID_PD_HOTHEEL;
  std::string TREATID_PD_HOTHEEL;
  std::string CAMPAIN_PD_HOTHEEL;
  std::string ENAME;
};

#endif /* _INC_CARCHIVER_CONARCANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED */

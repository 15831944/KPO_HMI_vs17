// Copyright (C) 2008 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED
#define _INC_CARCHIVER_LFANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED

#include <string>
#include <string>
#include "CARCHIVER_LFTask.h"
#include "CPP_SHIFT_CREW_ASSIGNMENT.h"
#include "CPP_GRADE_SINGLE_AIMS.h"
#include "CGC_SHIFT_CODE.h"
#include "CPD_HEATDATA_LIQADD_ANL.h"
#include "CPD_HOTHEEL_ANL_ENTRY.h"
#include "CPDC_EQUIP_MOUNT.h"
#include "CARCHIVER_Wrapper.h"
#include "CPD_HOTHEEL.h";
#include "CPD_HEATDATA.h";
#include "CPD_HEATDATA_LIQADD.h";
#include "CPD_LADLE.h";
#include "CPD_LADLE_DATA.h";
#include "CPD_REPORT.h";
#include "CPP_GRADE.h";
#include "CPP_GRADE_PRODPRAC.h";
#include "CPP_HEAT.h";
#include "CPP_HEAT_PLANT.h";
#include "CPP_ORDER.h";
#include "CPD_HEAT_DATA_PRODPRAC.h";
#include "CPD_LADLE_ANL.h";
#include "CPD_PRETREATDATA.h";
#include "CPD_PRETREAT_ANL.h";

class CARCHIVER_LFTask;

class CARCHIVER_LFAnnouncementPresettings
: CARCHIVER_Wrapper
{
public:
  CARCHIVER_LFAnnouncementPresettings();
  ~CARCHIVER_LFAnnouncementPresettings();

  void initialize(const std::string& HeatID, const std::string& TreatID, 
                                          const std::string& CustHeatID, const std::string& CustTreatID, const std::string& Plant, 
                                          long PlantNo, const std::string& LadleType, const std::string& LadleNo,
                                          const std::string& UserCode, const CDateTime& RevTime);
  
  bool writePD_REPORT();
  bool writePD_REPORT(long p_PD_REPORT_WEEKNO, long p_PD_REPORT_MONTHNO, 
                      const CDateTime& ANNOUNCETIME, const CDateTime& HEATASSIGNMENTDATE);
  bool writePD_HEATDATA();
  bool writePD_HEATDATA_LIQADD();
  bool writePD_HEATDATA_LIQADD_ANL();
  bool writePD_PRETREATDATA();
  bool writePD_PRETREAT_ANL();
  bool writePD_HEAT_DATA_PRODPRAC();
  bool writeAll();
  bool writeAll(long WEEKNO, long MONTHNO, const CDateTime&  ANNOUNCETIME, 
                const CDateTime& HEATASSIGNMENTDATE, long DRI_FEED_MODE_CODE);

protected:

  virtual void initDBClasses();
  virtual void deleteDBClasses();

private:
  CPP_SHIFT_CREW_ASSIGNMENT *m_pPP_Shift_Crew_Assignement;
  CPP_GRADE_SINGLE_AIMS     *m_pPP_Grade_Single_Aims;
  CGC_SHIFT_CODE            *m_pGC_SHIFT_CODE;
  CPD_HEATDATA_LIQADD_ANL   *m_pPD_HEAT_DATA_LIQADD_Anl;
  CPD_HOTHEEL_ANL_ENTRY     *m_pPD_HOTHEEL_Anl_Entry;
  CPDC_EQUIP_MOUNT          *m_pPDC_Equip_Mount;
  CPD_HOTHEEL               *m_pPD_HOTHEEL;
  CPD_LADLE                 *m_pPD_LADLE;
  CPD_LADLE_DATA            *m_pPD_LADLE_Data;
  CPD_REPORT                *m_pPD_Report;
  CPP_GRADE                 *m_pPP_Grade;
  CPP_GRADE_PRODPRAC        *m_pPP_Grade_ProdPrac;
  CPP_HEAT                  *m_pPP_HEAT;
  CPP_HEAT_PLANT            *m_pPP_HEAT_PLANT;
  CPP_ORDER                 *m_pPP_ORDER;
  CPD_HEATDATA              *m_pPD_Heatdata;
  CPD_HEATDATA_LIQADD       *m_pPD_HEAT_DATA_LIQADD;
  CPD_HEAT_DATA_PRODPRAC    *m_pPD_HEAT_DATA_PRODPRAC;
  CPD_LADLE_ANL             *m_pPD_LADLE_Anl;
  CPD_PRETREATDATA          *m_pPD_PRETREATDATA;
  CPD_PRETREAT_ANL          *m_pPD_Pretreat_Anl;

  std::string m_CustHeatID;
  std::string m_CustTreatID;
  std::string m_HeatID;
  std::string m_TreatID;
  std::string m_Plant;
  std::string m_LadleNo;
  std::string m_LadleType;
  std::string m_UserCode;
  long        m_PlantNo;
  long        m_WEEKNO;
  long        m_MONTHNO;
  long        m_DRI_FEED_MODE_CODE;
  CDateTime   m_RevTime;
  CDateTime   m_ANNOUNCETIME;
  CDateTime   m_HEATASSIGNMENTDATE;
  long        HEATING_MODE;
  long        AIMHOTHEEL_LF;
  long        SHIFTCODE;
  long        PRODPRAC_ID;
  long        AIMTEMP;
  long        LASTTEMP;
  long        HEATSTATORDER;
  long        LIQADDNO;
  long        ELECTRODE1_STRUCT_ID;
  long        ELECTRODE1_EQUIP_ID;
  long        ELECTRODE2_STRUCT_ID;
  long        ELECTRODE2_EQUIP_ID;
  long        ELECTRODE3_STRUCT_ID;
  long        ELECTRODE3_EQUIP_ID;
  long        ROOF_STRUCT_ID;
  long        ROOF_EQUIP_ID;
  long        CAMPAIN_PRI_COUNTER;
  double      REMSTEELMASS;
  double      REMSLAGMASS;
  double      WEIGHTSTEEL;
  double      WEIGHTSLAG;
  double      TEMP;
  double      ANL;
  double      ELECTRODE1_PRI_COUNTER;
  double      ELECTRODE2_PRI_COUNTER;
  double      ELECTRODE3_PRI_COUNTER;
  double      ROOF_PRI_COUNTER;
  CDateTime   PLANTREATEND;
  CDateTime   PLANTREATSTART;
  CDateTime   SHIFTSTARTDATE;
  CDateTime   LASTTEMPTIME;
  std::string TAPHOLE_EQUIP_ID_str;
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
  std::string TREATID_LAST;
  std::string LASTPLANT;

};

#endif /* _INC_CARCHIVER_LFANNOUNCEMENTPRESETTINGS_4642CF43030F_INCLUDED */

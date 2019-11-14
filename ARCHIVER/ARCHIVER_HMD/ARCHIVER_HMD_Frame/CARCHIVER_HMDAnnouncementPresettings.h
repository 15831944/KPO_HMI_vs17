// Copyright (C) 2008 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDAnnouncementPRESETTINGS_4642CF43030F_INCLUDED
#define _INC_CARCHIVER_HMDAnnouncementPRESETTINGS_4642CF43030F_INCLUDED

#include <string>

#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_S.hh"
#include "iEventMessages_s.hh"
#include "iDM_Interface_s.hh"
#include "CARCHIVER_AnnouncementPresettings.h"

#include "CARCHIVER_HMDTask.h"
#include "CARCHIVER_Wrapper.h"
//SS #include "CPP_GRADE_ANL.h";
//#include "CPDH_HEAT_DATA.h"
#include "CEquipmentData.h"
//SS #include "CPP_CREW_USER_ASSIGNMENT.h"
#include "CPD_HEAT_DATA.h"
#include "DEF_GC_LADLE_POS.h"
#include "CEventMessage.h"
#include "CIntfData.h"
#include "CGC_Plant_Container.h"

class CARCHIVER_HMDTask;

class CARCHIVER_HMDAnnouncementPresettings
: public CARCHIVER_AnnouncementPresettings
{
public:
  CARCHIVER_HMDAnnouncementPresettings();
  ~CARCHIVER_HMDAnnouncementPresettings();

  bool initialize(CEventMessage& Event);
  
  bool writeAll();
  bool writePDH_HEAT_DATA();
  bool writePD_HEATDATA();
  bool writePD_LADLE();
  bool writePD_LADLE_DATA();

protected:

  virtual void initDBClasses();
  virtual void deleteDBClasses();

private:

  std::string m_CustHeatID;
  std::string m_CustTreatID;
  std::string m_HeatID;
  std::string m_TreatID;
  std::string m_Plant;
  std::string m_PlantID;
  std::string m_LadleNo;
  std::string m_LadleType;
  CDateTime   PLANTREATSTART_CON;
  long        m_PlantNo;
  long        EquipPlant;
  long        CALC_MODE;
  long        TREAT_TYPE_OPER;
  double      SCULLMASS;
  double      TAREWGT;
  double      LADLE_FREEBOARD_BF;
  double      AIM_S_OPER;
  double      AIM_S_GRADE;
  std::string STEELGRADECODE;
  std::string PRODORDERID;
  std::string USERCODE;
  std::string CAST_ID;
  std::string HEATID_CON;
  std::string TREATID_CON;
  std::string ConArcCustHeatID;

};

#endif /* _INC_CARCHIVER_HMDAnnouncementPRESETTINGS_4642CF43030F_INCLUDED */

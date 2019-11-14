// Copyright (C) 2006 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLF_EVENTHANDLER_4582BE9C00A8_INCLUDED
#define _INC_CLF_EVENTHANDLER_4582BE9C00A8_INCLUDED

#include "CDH_EventHandler.h"

// db classes
#include "CGC_Recipe_L1Container.h"
#include "CGC_SourceContainer.h"

#include "CGT_MAT_PURP.h"
#include "CGT_MAT.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CGCL_STIRR_PHASE.h"

#include "CPD_LADLE.h"
#include "CPD_HEAT_DATA.h"
//#include "CPD_HEAT_PLANT_REF.h"
#include "CPD_RECIPE.h"
#include "CPDL_HEAT_DATA.h"

#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"

#include <map>

class CLF_EventHandler 
: public CDH_EventHandler
{
public:
  virtual bool handleEvent(CEventMessage& evMessage);
	virtual bool afterHandleEvent(const FRIESEvent& Event);
	virtual bool beforeHandleEvent(const FRIESEvent& Event);

  CLF_EventHandler();
  virtual ~CLF_EventHandler();

	

private:
  void SendEventMessage(const std::string& TlgName, const std::string& DataKey, const std::string& PlantID, const std::string& HeatID, const std::string& TreatID, const std::string& OrderID);

  bool provideData_L2LF03HeatAnnouncement(CEventMessage& Event, long UpdateFlag = 0);      
  bool provideData_L2LF06HeatCancel(CEventMessage& Event);                           
  bool provideData_L2LF07CompMode(CEventMessage& Event);                           
  bool provideData_L2LF20VoltageTap(CEventMessage& Event);                           
  bool provideData_L2LF22PullElectrodes(CEventMessage& Event);                           
  bool provideData_L2LF23ReleaseElectrodes(CEventMessage& Event);         
  bool provideData_L2LF25SampleRequest(CEventMessage& Event);                           
  bool provideData_L2LF30ProcessPatternElec(CEventMessage& Event); 
  bool provideData_L2LF31ProcessPatternStirr(CEventMessage& Event);
  bool provideData_L2LF70MatHandling(CEventMessage& Event);  
  bool provideData_L2LF71MatAvailRequest(CEventMessage& Event);
  bool provideData_L2LF72StatusRequest(CEventMessage& Event);     

  bool provideData_L2LF20_VOLTAGE_TAP(CEventMessage& Event);
  bool provideData_L2LF30_ELEC_PATT(CEventMessage& Event);
  bool provideData_L2LF31_STIRR_PATT(CEventMessage& Event);
  bool provideData_L2LF70_MAT_HANDL(CEventMessage& Event);


  // DH_OUT_LF PATTERN IMPLEMENTATION 
  bool provideData_TlgName(CEventMessage& Event);

  CGC_Recipe_L1Container* m_pGC_Recipe_L1Container;
  CGC_SourceContainer*    m_pGC_SourceContainer;

  CGT_MAT_PURP*           m_pGT_MAT_PURP;
  CGT_MAT*                m_pGT_MAT;
  CGT_GRADE_PRODPRAC*     m_pGT_GRADE_PRODPRAC;
  CGCL_STIRR_PHASE*       m_pGCL_STIRR_PHASE;

  CPD_LADLE*              m_pPD_LADLE;
  CPD_HEAT_DATA*          m_pPD_HEAT_DATA;
  CPD_RECIPE*             m_pPD_RECIPE;
  CPDL_HEAT_DATA*         m_pPDL_HEAT_DATA;

  CPP_HEAT*               m_pPP_HEAT;
  CPP_HEAT_PLANT*         m_pPP_HEAT_PLANT;

  bool ElPatternChanged; 
  long AimVoltTapPrev; 
  long AimCurveNoPrev; 
	bool UseOracleTransfer;
};

#endif /* _INC_CLF_EVENTHANDLER_4582BE9C00A8_INCLUDED */

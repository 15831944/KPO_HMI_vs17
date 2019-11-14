// Copyright (C) 2011 SMS Siemag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_EAFTreatmentManagementWrapper_41DAC61002DD_INCLUDED
#define _INC_CARCHIVER_EAFTreatmentManagementWrapper_41DAC61002DD_INCLUDED

#include "CEventMessage.h"

#include "CARCHIVER_TreatmentWrapper.h"

class CPDE_HEAT_DATA_MELT;

class CARCHIVER_EAFTreatmentManagementWrapper 
  : public CARCHIVER_TreatmentWrapper
{
public:
  bool doOnHeatStart(CEventMessage& Event);

  bool doOnTappingStart(CEventMessage& Event);

  bool doPhaseReport(CEventMessage& Event);

  virtual ~CARCHIVER_EAFTreatmentManagementWrapper();

  CARCHIVER_EAFTreatmentManagementWrapper();

protected:
  //bool AutoHeatAnnounce(CEventMessage& Event);

  CPDE_HEAT_DATA_MELT* m_pPDE_HEAT_DATA_MELT;

  virtual void deleteDBClasses();
  virtual void initDBClasses(); 

};

#endif /* _INC_CARCHIVER_EAFTreatmentManagementWrapper_41DAC61002DD_INCLUDED */

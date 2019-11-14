// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_LFMODELRESULTWRAPPER_414018DC0241_INCLUDED
#define _INC_CARCHIVER_LFMODELRESULTWRAPPER_414018DC0241_INCLUDED


#include "CEventMessage.h"

#include "CARCHIVER_ModelResultWrapper.h"

class CHD_GRADE_ANL;

class CPDL_ACTIVITY_RES;
class CPDL_ACTUAL_RES;
class CPDL_PHASE_ELEC_RES;
class CPDL_PHASE_STIRRING_RES;
class CGC_PhaseContainer;

//##ModelId=41A4A10703BD
class CARCHIVER_LFModelResultWrapper 
: public CARCHIVER_ModelResultWrapper
{
public:
	//##ModelId=41A4A37E014E
	virtual ~CARCHIVER_LFModelResultWrapper();

	//##ModelId=41A4A37E0159
	CARCHIVER_LFModelResultWrapper();

	//##ModelId=41A4A37E0180
	bool doOnActualSetpoints(CEventMessage& Event);

	//##ModelId=462F4F8803AF
	bool doOnRecipeSetpoints(CEventMessage& Event);

private:
	//##ModelId=41ADE8490398
	virtual void deleteDBClasses();

	//##ModelId=41ADE84A0098
	virtual void initDBClasses();

	//##ModelId=462F4FF40339
	CPDL_ACTUAL_RES *m_pPDL_ACTUAL_RES;
    
	//##ModelId=41B5B0B20001
  CPDL_PHASE_ELEC_RES* m_pPDL_PHASE_ELEC_RES;

  CPDL_PHASE_STIRRING_RES* m_pPDL_PHASE_STIRRING_RES;

  //##ModelId=41B6F8CB0392
	CPDL_ACTIVITY_RES* m_pPDL_ACTIVITY_RES;

  CGC_PhaseContainer* m_pGC_PhaseContainer;

};

#endif /* _INC_CARCHIVER_LFMODELRESULTWRAPPER_414018DC0241_INCLUDED */

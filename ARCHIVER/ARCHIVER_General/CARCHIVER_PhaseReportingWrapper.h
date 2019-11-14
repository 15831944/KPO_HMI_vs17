// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_PHASEREPORTINGWRAPPER_45E56DA50213_INCLUDED
#define _INC_CARCHIVER_PHASEREPORTINGWRAPPER_45E56DA50213_INCLUDED

#include "CEventHandler.h"
#include "CARCHIVER_Wrapper.h"
#include "CGC_PHASE.h"
#include "CPD_SAMPLE.h"
#include "CPD_SAMPLE_ENTRY.h"
#include "CPP_HEAT_PLANT.h" 
#include "CPP_HEAT.h" 
#include "CPD_ACTION.h"
#include "CGC_HEAT_STATUS.h"

//##ModelId=45E56DA50213
class CARCHIVER_PhaseReportingWrapper 
: public CARCHIVER_Wrapper
{
public:
	//##ModelId=45E56E2B0216
	CARCHIVER_PhaseReportingWrapper();

	//##ModelId=45E56E2C00ED
	virtual ~CARCHIVER_PhaseReportingWrapper();

protected:
	//##ModelId=4785EF7C0282
	CPD_ACTION* m_pPD_ACTION;

	//##ModelId=4785EFBB00C4
	CPP_HEAT* m_pPP_HEAT; 

	//##ModelId=4785EFCD0268
	CPP_HEAT_PLANT* m_pPP_HEAT_PLANT;

	//##ModelId=4785F0370298
	CGC_HEAT_STATUS* m_pGC_HEAT_STATUS;

	//##ModelId=46B19EBB000F
	CGC_PHASE* m_pGC_PHASE;

	//##ModelId=46B19EC80049
	CPD_SAMPLE* m_pPD_SAMPLE;

	//##ModelId=46B19ED3022E
	CPD_SAMPLE_ENTRY* m_pPD_SAMPLE_ENTRY;

	//##ModelId=45E56E350011
	bool handleHeatProductionPhaseReport(CEventMessage &Event);

	//##ModelId=45E56E2E0249
	virtual void initDBClasses();

	//##ModelId=45E56E2F017A
	virtual void deleteDBClasses();

};

#endif /* _INC_CARCHIVER_PHASEREPORTINGWRAPPER_45E56DA50213_INCLUDED */

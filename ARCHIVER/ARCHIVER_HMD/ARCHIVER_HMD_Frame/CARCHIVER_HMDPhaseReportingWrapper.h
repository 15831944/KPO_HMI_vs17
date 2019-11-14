// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDPHASEREPORTINGWRAPPER_45E56EAB0082_INCLUDED
#define _INC_CARCHIVER_HMDPHASEREPORTINGWRAPPER_45E56EAB0082_INCLUDED

#include "CARCHIVER_PhaseReportingWrapper.h"
#include "CDateTime.h"

class CHeatStatusContainer;
class CPDH_HM_DATA_PHASE;
class CGC_PHASE;


//##ModelId=45E56EAB0082
class CARCHIVER_HMDPhaseReportingWrapper 
: public CARCHIVER_PhaseReportingWrapper
{
public:
	//##ModelId=45E56EC80124
	CARCHIVER_HMDPhaseReportingWrapper();

	//##ModelId=45E56EC80350
	virtual ~CARCHIVER_HMDPhaseReportingWrapper();

	//##ModelId=45E56EDE026B
	bool doOnHeatProductionPhaseReport(CEventMessage &Event);

protected:
	//##ModelId=45E5712A0043
	CPDH_HM_DATA_PHASE* m_pPDH_HM_DATA_PHASE;
  CGC_PHASE* m_pGC_PHASE;
  CHeatStatusContainer* m_pHeatStatusContainer;

	//##ModelId=45E56ECA0201
	virtual void initDBClasses();

	//##ModelId=45E56ECB02FC
	virtual void deleteDBClasses();


	/*struct of last data of a phase*/
	//##ModelId=45F51E2002E0
	typedef struct _PhData
	{
		std::string PHASENAME;
		CDateTime PHASE_START;
		double INJ_CARBIDE;
		double INJ_LIME;
		double INJ_MG;
	}sPhData;

	//last data of a phase
	//##ModelId=45F51E2002C3
	std::map<std::string, sPhData> LastPhaseData;
};

#endif /* _INC_CARCHIVER_HMDPHASEREPORTINGWRAPPER_45E56EAB0082_INCLUDED */

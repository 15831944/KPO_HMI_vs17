// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CARCHIVER_HMDMODELRESULTWRAPPER_INCLUDED
#define _INC_CARCHIVER_HMDMODELRESULTWRAPPER_INCLUDED

#include "iDM_Interface_s.hh"
#include "CEventMessage.h"

#include "CARCHIVER_ModelResultWrapper.h"
//#include "CPDH_ACTUAL_RES.h"
#include "CPD_PHASE_RES.h"
#include "CPD_PHASE_RES.h"
//#include "CPDH_HEAT_DATA.h"
//SS #include "CPD_LADLE_ANL.h"

//##ModelId=45D58A690181
class CARCHIVER_HMDModelResultWrapper 
: public CARCHIVER_ModelResultWrapper
{
public:
	//##ModelId=45D58A9103C3
	virtual ~CARCHIVER_HMDModelResultWrapper();

	//##ModelId=45D58A91011B
	CARCHIVER_HMDModelResultWrapper();

	//##ModelId=47693EE3015F
	bool doOnModelResult(CEventMessage& Event);

protected:
	//##ModelId=47693F8400EC
	////CPDH_ACTUAL_RES* m_pPDH_Actual_Res;

 //// CPD_PHASE_RES* m_pPD_Phase_Res;

 //// CPD_PHASE_RES_ANL* m_pPD_Phase_Res_Anl;

 //// CPDH_HEAT_DATA* m_pPDH_HEAT_DATA;

//SS   CPD_LADLE_ANL* m_pPD_Ladle_Anl;


	//##ModelId=45D58A96024B
	virtual void deleteDBClasses();

	//##ModelId=45D58A970077
	virtual void initDBClasses();
};

#endif /* _INC_CARCHIVER_HMDMODELRESULTWRAPPER_INCLUDED */

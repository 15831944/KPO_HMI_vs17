// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMDMODELWRAPPER_4118CC3401F4_INCLUDED
#define _INC_CHMDMODELWRAPPER_4118CC3401F4_INCLUDED

#include "CHMDModelTask.h"
#include "CModelWrapper.h"

#include "CEventMessage.h"
#include "cCBS_Connection.h"
#include "cCBS_DBExc.h"

#include "CGT_MAT.h"
#include "CGT_MAT_PURP.h"
//#include "CGT_MAT_AVAIL.h"
#include "CGT_MAT_CHEM.h"

#include "CHDH_PP_INJECTION.h"
#include "CHDH_PP_BLOWING.h"
//#include "CHDH_PP_PARA.h"
#include "CHDH_PARAM.h"

#include "CHDH_PP_TEMP_CORR.h"
#include "CHDH_PP_BASE_VAL.h"
#include "CHDH_PP_BASE_VAL_STEP.h"

//#include "CGTH_PP_INJECTION.h"
//#include "CGTH_PP_BLOWING.h"
//#include "CGTH_PP_PARA.h"
//#include "CGTH_PP_TEMP_CORR.h"
//#include "CGTH_PP_BASE_VAL.h"
//#include "CGTH_PP_BASE_VAL_STEP.h"

//#include "CPDH_HEAT_DATA.h"
#include "CPD_HEAT_DATA.h"

#include "CPD_HOT_METAL.h"		
#include "CPD_SAMPLE_REF.h"		
#include "CPD_SAMPLE_ENTRY.h"	


#include "CHD_GRADE_ANL.h"
//#include "CPD_HEAT_DATA_LIQADD.h"
//#include "CPD_HEAT_DATA_LIQADD_ANL.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"
#include "CHD_PARAM.h"

//#include "CPD_BIN.h" //anku 25.8.2011 Bhushan
#include "CPDH_CYCL_MEAS_DATA.h"//anku 10.9.2011 Bhushan

#include "CPDH_HM_DATA.h"

//##ModelId=4118CC3401F4
class CHMDModelWrapper : public CModelWrapper
{
protected:
CPD_HEAT_DATA_PRODPRAC *m_pPD_HEAT_DATA_PRODPRAC;
CGT_MAT              *m_pGT_MAT;
CGT_MAT_PURP         *m_pGT_MAT_PURP;
//CGT_MAT_AVAIL        *m_pGT_MAT_AVAIL;
CGT_MAT_CHEM         *m_pGT_MAT_CHEM;

CHDH_PP_INJECTION    *m_pHDH_PP_INJECTION;
CHDH_PP_BLOWING      *m_pHDH_PP_BLOWING;
//CHDH_PP_PARA         *m_pHDH_PP_PARA;
CHDH_PARAM         *m_pHDH_PARAM;
CHDH_PP_TEMP_CORR    *m_pHDH_PP_TEMP_CORR;
CHDH_PP_BASE_VAL     *m_pHDH_PP_BASE_VAL;
CHDH_PP_BASE_VAL_STEP*m_pHDH_PP_BASE_VAL_STEP;

//CGTH_PP_INJECTION    *m_pGTH_PP_INJECTION;
//CGTH_PP_BLOWING      *m_pGTH_PP_BLOWING;
//CGTH_PP_PARA         *m_pGTH_PP_PARA;
//CGTH_PP_TEMP_CORR    *m_pGTH_PP_TEMP_CORR;
//CGTH_PP_BASE_VAL     *m_pGTH_PP_BASE_VAL;
//CGTH_PP_BASE_VAL_STEP*m_pGTH_PP_BASE_VAL_STEP;


CPDH_HM_DATA       *m_pPDH_HM_DATA;
CPD_HOT_METAL		*m_pPD_HOT_METAL;
CPD_SAMPLE_REF		*m_pPD_SAMPLE_REF;
CPD_SAMPLE_ENTRY	*m_pPD_SAMPLE_ENTRY;

//CPD_HEAT_DATA       *m_pPD_HEATDATA;
CHD_GRADE_ANL        *m_pHDH_GRADE_ANL;
//CPD_HEAT_DATA_LIQADD     *m_pPD_HEATDATA_LIQADD;
//CPD_HEAT_DATA_LIQADD_ANL *m_pPDH_HM_DATA_LIQADD_ANL;

CPDH_CYCL_MEAS_DATA *m_pPDH_CYCL_MEAS_DATA;

//CPD_BIN *m_pPD_BIN;//anku 25.8.2011


protected:
  std::string m_Key;

public:

  //Get Lance blow type from column USELANCE of table 
  //PD_HEATDATA.
  //##ModelId=42A72C350390
  long getLanceBlowType(const std::string & HeatID, const std::string & TreatId);


  //##ModelId=41FF4FF1010D
  virtual void initDBClasses();

  //##ModelId=41FF500E017D
  virtual void deleteDBClasses();

  //##ModelId=4124B121004D
  virtual ~CHMDModelWrapper(); 

  //##ModelId=41FF605C0229
  void handleError(const char * Function, const char * Action);

  //##ModelId=41FF605C03D7
  void handleCORBAConnectionError(const char * Function, const char * Action);

  //##ModelId=41FF605D0180
  void handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action);

  //##ModelId=41FF605D03E3
  void handleDBConnectionError();

  //##ModelId=4118CDE2024D
  virtual bool doModelResult(CEventMessage &Event);

	string m_PlantName;
	long m_PlantNo;

protected:

  //##ModelId=42A04EA80008
  DM::iDM_Interface_var   m_pDM_Interface;

  //##ModelId=41FF800401FA
	CModelResults_Impl * m_pModelResults; //lohm  changed from private to protected

  //##ModelId=4124B120022C
  CHMDModelWrapper();

  //##ModelId=412639E40176
  cCBS_StdConnection* m_pConnection;



};

#endif /* _INC_CHMDMODELWRAPPER_4118CC3401F4_INCLUDED */

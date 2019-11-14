// Copyright (C) 2004 SMS Demag AG

#include "iEventMessages_s.hh"
#include "iSMC_DataDefinitions_s.hh"

#include "CHMDModelWrapper.h"

#include "CEventMessage.h"
#include "CIntfData.h"

#include "cCBS_StdEventLogFrameController.h"
#include "cCBS_StdInitBase.h"

#include "CSMC_RecipeHandler.h"
#include "CSMC_EventLogFrameController.h"
#include "DEF_GC_PLANT_DEF.h"

//##ModelId=4124B120022C
CHMDModelWrapper::CHMDModelWrapper()
: m_pHDH_PP_BASE_VAL( 0)
, m_pPD_HEAT_DATA_PRODPRAC( 0)
, m_pHDH_PP_BASE_VAL_STEP( 0)
, m_pGT_MAT( 0)
, m_pGT_MAT_PURP( 0)
, m_pGT_MAT_CHEM( 0)
//, m_pGT_MAT_AVAIL( 0)

, m_pHDH_PP_INJECTION( 0)
, m_pHDH_PP_BLOWING( 0)
//, m_pHDH_PP_PARA( 0)
, m_pHDH_PP_TEMP_CORR( 0)

//, m_pGTH_PP_BASE_VAL( 0)
//, m_pGTH_PP_BASE_VAL_STEP( 0)
//, m_pGTH_PP_INJECTION( 0)
//, m_pGTH_PP_BLOWING( 0)
//, m_pGTH_PP_PARA( 0)
//, m_pGTH_PP_TEMP_CORR( 0)

//, m_pPDH_HEAT_DATA( 0)
, m_pPDH_HM_DATA( 0)
, m_pPD_HOT_METAL( 0)
, m_pPD_SAMPLE_REF( 0)
, m_pPD_SAMPLE_ENTRY( 0)




//, m_pPD_BIN (0)
, m_pHDH_GRADE_ANL( 0)
//, m_pPD_HEATDATA_LIQADD( 0)
//, m_pPD_HEATDATA_LIQADD_ANL( 0)

, m_pPDH_CYCL_MEAS_DATA( 0)

, m_pHDH_PARAM( 0)
{
  m_PlantName = DEF_GC_PLANT_DEF::HMD;
  m_PlantNo = 1;

  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "PlantName", m_PlantName);
  cCBS_StdInitBase::getInstance()->replaceWithEntry("PROCESS", "PlantNo", m_PlantNo);

}

//##ModelId=4124B121004D
CHMDModelWrapper::~CHMDModelWrapper()
{
  deleteDBClasses();
}


//##ModelId=41FF4FF1010D
void CHMDModelWrapper::initDBClasses()
{
  m_pConnection = m_pModelTask->getStdConnection();

  if (m_pConnection)
  {
    m_pPD_HEAT_DATA_PRODPRAC =  new CPD_HEAT_DATA_PRODPRAC( m_pConnection);
    m_pHDH_PP_BASE_VAL       =  new CHDH_PP_BASE_VAL( m_pConnection);
    m_pHDH_PP_BASE_VAL_STEP  =  new CHDH_PP_BASE_VAL_STEP( m_pConnection);
    m_pGT_MAT                =  new CGT_MAT( m_pConnection);
    m_pGT_MAT_PURP           =  new CGT_MAT_PURP( m_pConnection);
    m_pGT_MAT_CHEM           =  new CGT_MAT_CHEM( m_pConnection);

    //m_pGTH_PP_INJECTION      =  new CGTH_PP_INJECTION( m_pConnection);
    //m_pGTH_PP_BLOWING        =  new CGTH_PP_BLOWING( m_pConnection);
    //m_pGTH_PP_PARA           =  new CGTH_PP_PARA( m_pConnection);
    //m_pGTH_PP_TEMP_CORR      =  new CGTH_PP_TEMP_CORR( m_pConnection);
    //m_pGTH_PP_BASE_VAL       =  new CGTH_PP_BASE_VAL( m_pConnection);
    //m_pGTH_PP_BASE_VAL_STEP  =  new CGTH_PP_BASE_VAL_STEP( m_pConnection);

    m_pHDH_PP_INJECTION      =  new CHDH_PP_INJECTION( m_pConnection);
    m_pHDH_PP_BLOWING        =  new CHDH_PP_BLOWING( m_pConnection);
    //m_pHDH_PP_PARA           =  new CHDH_PP_PARA( m_pConnection);
    m_pHDH_PARAM           =  new CHDH_PARAM( m_pConnection);
    m_pHDH_PP_TEMP_CORR      =  new CHDH_PP_TEMP_CORR( m_pConnection);
    m_pHDH_PP_BASE_VAL       =  new CHDH_PP_BASE_VAL( m_pConnection);
    m_pHDH_PP_BASE_VAL_STEP  =  new CHDH_PP_BASE_VAL_STEP( m_pConnection);

    //m_pPDH_HEAT_DATA         =  new CPDH_HEAT_DATA( m_pConnection);
    m_pPDH_HM_DATA         =  new CPDH_HM_DATA( m_pConnection);
    m_pPD_HOT_METAL         =  new CPD_HOT_METAL	( m_pConnection);
    m_pPD_SAMPLE_REF         =  new CPD_SAMPLE_REF	( m_pConnection);
    m_pPD_SAMPLE_ENTRY         =  new CPD_SAMPLE_ENTRY( m_pConnection);

    //m_pPD_HEATDATA         =  new CPD_HEATDATA( m_pConnection);
    //m_pPD_BIN         =  new CPD_BIN( m_pConnection);
	m_pHDH_GRADE_ANL = new CHD_GRADE_ANL( m_pConnection);
    //m_pPD_HEATDATA_LIQADD = new CPD_HEATDATA_LIQADD( m_pConnection); 
    //m_pPD_HEATDATA_LIQADD_ANL = new CPD_HEATDATA_LIQADD_ANL( m_pConnection); 
	m_pPDH_CYCL_MEAS_DATA = new CPDH_CYCL_MEAS_DATA (m_pConnection);

    //m_pGT_MAT_AVAIL = new CGT_MAT_AVAIL( m_pConnection);
  }
}

//##ModelId=41FF500E017D
void CHMDModelWrapper::deleteDBClasses()
{
  delete m_pPD_HEAT_DATA_PRODPRAC; m_pPD_HEAT_DATA_PRODPRAC = 0;
  delete m_pGT_MAT               ; m_pGT_MAT               = 0;
  delete m_pGT_MAT_PURP          ; m_pGT_MAT_PURP          = 0;
  delete m_pGT_MAT_CHEM          ; m_pGT_MAT_CHEM          = 0;

  delete m_pHDH_PP_INJECTION     ; m_pHDH_PP_INJECTION     = 0;
  delete m_pHDH_PP_BLOWING       ; m_pHDH_PP_BLOWING       = 0;
  delete m_pHDH_PARAM          ; m_pHDH_PARAM          = 0;
  //delete m_pHDH_PP_PARA          ; m_pHDH_PP_PARA          = 0;
  delete m_pHDH_PP_TEMP_CORR     ; m_pHDH_PP_TEMP_CORR     = 0;
  delete m_pHDH_PP_BASE_VAL      ; m_pHDH_PP_BASE_VAL      = 0;
  delete m_pHDH_PP_BASE_VAL_STEP ; m_pHDH_PP_BASE_VAL_STEP = 0;

  //delete m_pGTH_PP_INJECTION     ; m_pGTH_PP_INJECTION     = 0;
  //delete m_pGTH_PP_BLOWING       ; m_pGTH_PP_BLOWING       = 0;
  //delete m_pGTH_PP_PARA          ; m_pGTH_PP_PARA          = 0;
  //delete m_pGTH_PP_TEMP_CORR     ; m_pGTH_PP_TEMP_CORR     = 0;
  //delete m_pGTH_PP_BASE_VAL      ; m_pGTH_PP_BASE_VAL      = 0;
  //delete m_pGTH_PP_BASE_VAL_STEP ; m_pGTH_PP_BASE_VAL_STEP = 0;

  //delete m_pPDH_HEAT_DATA;          m_pPDH_HEAT_DATA          = 0;
  delete m_pPDH_HM_DATA;            m_pPDH_HM_DATA            = 0;
  delete m_pPD_HOT_METAL    ;            m_pPD_HOT_METAL           = 0;
  delete m_pPD_SAMPLE_REF   ;            m_pPD_SAMPLE_REF          = 0;
  delete m_pPD_SAMPLE_ENTRY ;            m_pPD_SAMPLE_ENTRY        = 0;

// delete m_pPD_BIN;					m_pPD_BIN				  = 0;
  delete m_pHDH_GRADE_ANL;           m_pHDH_GRADE_ANL           = 0;
  //delete m_pPD_HEATDATA_LIQADD;     m_pPD_HEATDATA_LIQADD     = 0;
  //delete m_pPD_HEATDATA_LIQADD_ANL; m_pPD_HEATDATA_LIQADD_ANL = 0;

  delete m_pPDH_CYCL_MEAS_DATA		; m_pPDH_CYCL_MEAS_DATA = 0;
  //delete m_pGT_MAT_AVAIL;           m_pGT_MAT_AVAIL           = 0;

  delete m_pHDH_PARAM;               m_pHDH_PARAM           = 0;
}

//##ModelId=41FF605C0229
void CHMDModelWrapper::handleError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, "", Function, Action);    
}

//##ModelId=41FF605C03D7
void CHMDModelWrapper::handleCORBAConnectionError(const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
      pEventLog->EL_ExceptionCaught(sMessage, "",  Function, Action);    
}

//##ModelId=41FF605D0180
void CHMDModelWrapper::handleDBConnectionError(cCBS_DBExc &e, const char * Function, const char * Action)
{
  cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
  sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
  pEventLog->EL_ExceptionCaught(sMessage, (e.getText()).c_str(), Function, Action);    

  deleteDBClasses();
  m_pModelTask->handleDBConnectionError();
  initDBClasses();
}

//##ModelId=41FF605D03E3
void CHMDModelWrapper::handleDBConnectionError()
{
  deleteDBClasses();
  m_pModelTask->handleDBConnectionError();
  initDBClasses();
}

//##ModelId=4118CDE2024D
bool CHMDModelWrapper::doModelResult(CEventMessage &Event)
{
  bool RetValue = false;

  if (m_pModelTask)
  {
    RetValue = m_pModelTask->callModelResultWrapper(DEF_GC_PLANT_DEF::HMD,Event);
  }

  return RetValue;
}



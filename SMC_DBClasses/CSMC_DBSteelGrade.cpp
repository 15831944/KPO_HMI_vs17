// Copyright (C) 2004 SMS Demag AG, Germany 

#include "CSMC_EventLogFrameController.h"

#include "CPD_HEAT_DATA.h"

#include "CGT_GRADE.h"
#include "CGT_GRADE_ANL.h"
#include "CHD_GRADE.h"
#include "CHD_GRADE_ANL.h"


#include "CSMC_DBSteelGrade.h"



//##ModelId=41D9305A037D
CSMC_DBSteelGrade::CSMC_DBSteelGrade(cCBS_Connection* Connection)
: CSMC_DBTableBase(Connection)
{
  m_pHeatDataProduction         = new CPD_HEAT_DATA(Connection);
  m_pSteelGradePlanned          = new CGT_GRADE(Connection);
  m_pSteelGradeAnalysisPlanned  = new CGT_GRADE_ANL(Connection);
  m_pSteelGradeAct              = new CHD_GRADE(Connection);
  m_pSteelGradeAnalysisAct      = new CHD_GRADE_ANL(Connection);
}

//##ModelId=41D9305C0004
CSMC_DBSteelGrade::~CSMC_DBSteelGrade()
{
}

bool CSMC_DBSteelGrade::updateSteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID, const std::string& STEELGRADECODE,const std::string& PLANT, const std::string& ENAME, const std::string& AIMTYPE)
{
  // update might be very complex
  // so first delet all existing entries
  if ( selectSteelGradeAnalysis(HEATID, TREATID, STEELGRADECODE,PLANT, ENAME, AIMTYPE) )
  {
    if ( deleteRows() )
    {
      commit();
    }
  }

  // now copy all data from source 
  // copySteelGradeAnalysis already commits successful transactions
  return copySteelGradeAnalysis(HEATID, TREATID, PLANT, ENAME, AIMTYPE);
}

bool CSMC_DBSteelGrade::updateSteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  // update might be very complex
  // so first delet all existing entries
  if ( selectSteelGrade(HEATID, TREATID, PLANT) )
  {
    if ( deleteRows() )
    {
      commit();
    }
  }

  // now copy all data from source 
  // copySteelGradeAnalysis already commits successful transactions
  return copySteelGrade(HEATID, TREATID, PLANT);
}

bool CSMC_DBSteelGrade::copySteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, const std::string& ENAME, const std::string& AIMTYPE)
{
  bool RetValue = false;

  // switch to HD_GRADE
  // **********************
  m_pSMC_DBData = m_pSteelGradeAnalysisAct;
  // **********************

  std::string STEELGRADECODE = CSMC_DBData::unspecString;

  // try to find steelgradecode for heat
  if ( m_pHeatDataProduction && m_pHeatDataProduction->select(HEATID,TREATID,PLANT) )
  {
    STEELGRADECODE = m_pHeatDataProduction->getSTEELGRADECODE_ACT(1);

    if (STEELGRADECODE == CSMC_DBData::unspecString)
    {
      STEELGRADECODE = m_pHeatDataProduction->getSTEELGRADECODE_PLAN(1);
    }
  }
    
  if ( STEELGRADECODE != CSMC_DBData::unspecString && 
       m_pSteelGradeAnalysisPlanned && 
       m_pSteelGradeAnalysisPlanned->select(STEELGRADECODE,PLANT,ENAME,AIMTYPE) )
  {
    for (int i = 1; i <= m_pSteelGradeAnalysisPlanned->getLastRow(); i++)
    {
      setHEATID(HEATID);
      setTREATID(TREATID);

      setColumnsFromTable(m_pSteelGradeAnalysisPlanned,i);

      RetValue = insert();
    }

    if ( RetValue )
    {
      commit();
      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = CSMC_EventLogFrame::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteInfo(sMessage,"","HD_GRADE_ANL","copy from GT_GRADE_ANL");
    }

  }

  return RetValue;
}


bool CSMC_DBSteelGrade::copySteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  bool RetValue = false;

  // switch to HD_GRADE
  // **********************
  m_pSMC_DBData = m_pSteelGradeAct;
  // **********************

  std::string STEELGRADECODE = CSMC_DBData::unspecString;

  if ( m_pHeatDataProduction && m_pHeatDataProduction->select(HEATID,TREATID,PLANT) )
  {
    STEELGRADECODE = m_pHeatDataProduction->getSTEELGRADECODE_ACT(1);

    if (STEELGRADECODE == CSMC_DBData::unspecString)
    {
      STEELGRADECODE = m_pHeatDataProduction->getSTEELGRADECODE_PLAN(1);
    }
  }

  // only one entry for STEELGRADECODE at SteelGradePlanned expected !
  if ( STEELGRADECODE != CSMC_DBData::unspecString && 
      m_pSteelGradePlanned && 
      m_pSteelGradePlanned->select(STEELGRADECODE) )
  {
    RetValue = false;

    setHEATID(HEATID);
    setTREATID(TREATID);
    setPLANT(PLANT);
    setColumnsFromTable(m_pSteelGradePlanned,1);
    
    if ( insert() )
    {
      commit();
      RetValue = true;

      CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
      sEventLogMessage sMessage = CSMC_EventLogFrame::initMessage(__FILE__,__LINE__);
      pEventLog->EL_DBWriteInfo(sMessage,"","HD_GRADE","copy from GT_GRADE");
    }
  }

  return RetValue;

}

bool CSMC_DBSteelGrade::selectSteelGradeAnalysis(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT,const std::string& STEELGRADECODE, const std::string& ENAME, const std::string& AIMTYPE)
{
  bool RetValue = false;

  // switch to HD_GRADE_ANL
  // **********************
  m_pSMC_DBData = m_pSteelGradeAnalysisAct;
  // **********************

  RetValue =  m_pSteelGradeAnalysisAct->select(HEATID, TREATID, STEELGRADECODE,PLANT, ENAME, AIMTYPE);

  if (!RetValue)
  {
    copySteelGradeAnalysis(HEATID, TREATID, PLANT, ENAME, AIMTYPE);
    RetValue = m_pSteelGradeAnalysisAct->select(HEATID, TREATID,STEELGRADECODE, PLANT, ENAME, AIMTYPE);
  }

  return RetValue;

}


//##ModelId=41D9305C0203
bool CSMC_DBSteelGrade::selectSteelGrade(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  bool RetValue = false;
  
  // switch to HD_GRADE
  // **********************
  m_pSMC_DBData = m_pSteelGradeAct;
  // **********************

  RetValue =  m_pSteelGradeAct->select(HEATID, TREATID, PLANT);

  if (!RetValue)
  {
    copySteelGrade(HEATID, TREATID, PLANT);
    RetValue =  m_pSteelGradeAct->select(HEATID, TREATID, PLANT);
  }

  return RetValue;
}

//##ModelId=44FEA5D302E3
bool CSMC_DBSteelGrade::deleteSteelGrade(const std::string& Grade)
{
  // switch to HD_GRADE
  // **********************
  m_pSMC_DBData = m_pSteelGradeAct;
  // **********************

  return m_pSteelGradeAct->deleteGrade(Grade);

}



// **********************************************************************************************************
// simple set and get methods
// **********************************************************************************************************
//##ModelId=41D9305D0146
std::string CSMC_DBSteelGrade::getSTEELGRADECODE(long Row)
{
	return getString("STEELGRADECODE", Row);

}

//##ModelId=41D9305E0007
void CSMC_DBSteelGrade::setSTEELGRADECODE(const std::string& value)
{
	setString("STEELGRADECODE", value);

}


std::string CSMC_DBSteelGrade::getPLANT(long Row)
{
	return getString("PLANT", Row);
}

void CSMC_DBSteelGrade::setPLANT(const std::string& value)
{
	setString("PLANT", value);
}


std::string CSMC_DBSteelGrade::getHEATID(long Row)
{
	return getString("HEATID", Row);
}

void CSMC_DBSteelGrade::setHEATID(const std::string& value)
{
	setString("HEATID", value);
}

std::string CSMC_DBSteelGrade::getTREATID(long Row)
{
	return getString("TREATID", Row);
}

void CSMC_DBSteelGrade::setTREATID(const std::string& value)
{
	setString("TREATID", value);
}

//##ModelId=41D9305E02D8
std::string CSMC_DBSteelGrade::getSTEELGRADECODEDESC(long Row)
{
	return getString("STEELGRADECODEDESC", Row);

}

//##ModelId=41D9305F013F
void CSMC_DBSteelGrade::setSTEELGRADECODEDESC(const std::string& value)
{
	setString("STEELGRADECODEDESC", value);

}

//##ModelId=41D93060003C
std::string CSMC_DBSteelGrade::getSTEELGRADECODEDESC_C(long Row)
{
	return getString("STEELGRADECODEDESC_C", Row);

}

//##ModelId=41D9306001E1
void CSMC_DBSteelGrade::setSTEELGRADECODEDESC_C(const std::string& value)
{
	setString("STEELGRADECODEDESC_C", value);

}

//##ModelId=41D9306003D5
double CSMC_DBSteelGrade::getLiqTemp(long Row)
{
	return getDouble("LiqTemp", Row);

}

//##ModelId=41D9306101BA
void CSMC_DBSteelGrade::setLiqTemp(double value)
{
	setDouble("LiqTemp", value);

}

//##ModelId=41D9306103A5
CDateTime CSMC_DBSteelGrade::getREVTIME(long Row)
{
	CDateTime D;
	D.fromDBString(getString("REVTIME", Row));
	return D;

}

//##ModelId=41D9306201E4
void CSMC_DBSteelGrade::setREVTIME(const CDateTime& value)
{
	setString("REVTIME", value.toDBString());

}

//##ModelId=41D9306203BA
std::string CSMC_DBSteelGrade::getHOTMETALCOMPOSITION(long Row)
{
	return getString("HOTMETALCOMPOSITION", Row);

}

//##ModelId=41D930630177
void CSMC_DBSteelGrade::setHOTMETALCOMPOSITION(const std::string& value)
{
	setString("HOTMETALCOMPOSITION", value);

}

//##ModelId=41D930630394
std::string CSMC_DBSteelGrade::getUSERCODE(long Row)
{
	return getString("USERCODE", Row);

}

//##ModelId=41D930640100
void CSMC_DBSteelGrade::setUSERCODE(const std::string& value)
{
	setString("USERCODE", value);

}


double CSMC_DBSteelGrade::getANL(long Row)
{
	return getDouble("ANL", Row);
}

void CSMC_DBSteelGrade::setANL(double value)
{
	setDouble("ANL", value);
}

string CSMC_DBSteelGrade::getENAME(long Row)
{
	return getString("ENAME", Row);
}

void CSMC_DBSteelGrade::setENAME(const std::string& value)
{
	setString("ENAME", value);
}

string CSMC_DBSteelGrade::getAIMTYPE(long Row)
{
	return getString("AIMTYPE", Row);
}

void CSMC_DBSteelGrade::setAIMTYPE(const std::string& value)
{
	setString("AIMTYPE", value);
}


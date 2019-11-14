//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CSMC_EventLogFrameController.h"
#include "CPD_PLANTSTATUS_PLANT.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::TREATMENTPOSITION("TREATMENTPOSITION");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::TYPE("TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::VARNAME("VARNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_PLANTSTATUS_PLANT::VALUE("VALUE");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_PLANTSTATUS_PLANT::CPD_PLANTSTATUS_PLANT(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_PLANTSTATUS_PLANT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_PLANTSTATUS_PLANT::CPD_PLANTSTATUS_PLANT(cCBS_Connection* Connection)
:CSMC_DBData("PD_PLANTSTATUS_PLANT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_PLANTSTATUS_PLANT::CPD_PLANTSTATUS_PLANT()
:CSMC_DBData("PD_PLANTSTATUS_PLANT")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_PLANTSTATUS_PLANT::~CPD_PLANTSTATUS_PLANT()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_PLANTSTATUS_PLANT::getPLANT(long Row)
{
  return getString(CPD_PLANTSTATUS_PLANT::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setPLANT(const std::string& value)
{
  setString(CPD_PLANTSTATUS_PLANT::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant number
long CPD_PLANTSTATUS_PLANT::getPLANTNO(long Row)
{
  return getLong(CPD_PLANTSTATUS_PLANT::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setPLANTNO(long value)
{
  setLong(CPD_PLANTSTATUS_PLANT::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Identification of treatment position to handle heats at Twin-LF (1-> car 1, 2-> car 2) and melting units with tapping area (1-> furnace, 2-> TapLadle)
long CPD_PLANTSTATUS_PLANT::getTREATMENTPOSITION(long Row)
{
  return getLong(CPD_PLANTSTATUS_PLANT::TREATMENTPOSITION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setTREATMENTPOSITION(long value)
{
  setLong(CPD_PLANTSTATUS_PLANT::TREATMENTPOSITION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specifies data type of value. 1=long, 2=double,3=string
long CPD_PLANTSTATUS_PLANT::getTYPE(long Row)
{
  return getLong(CPD_PLANTSTATUS_PLANT::TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setTYPE(long value)
{
  setLong(CPD_PLANTSTATUS_PLANT::TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPD_PLANTSTATUS_PLANT::getVARNAME(long Row)
{
  return getString(CPD_PLANTSTATUS_PLANT::VARNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setVARNAME(const std::string& value)
{
  setString(CPD_PLANTSTATUS_PLANT::VARNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPD_PLANTSTATUS_PLANT::getVALUE(long Row)
{
  return getString(CPD_PLANTSTATUS_PLANT::VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_PLANTSTATUS_PLANT::setVALUE(const std::string& value)
{
  setString(CPD_PLANTSTATUS_PLANT::VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_PLANTSTATUS_PLANT::select(const std::string& PLANT, long PLANTNO, long TREATMENTPOSITION, long TYPE, const std::string& VARNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_PLANTSTATUS_PLANT::PLANT,PLANT);
  addWhereClause(CPD_PLANTSTATUS_PLANT::PLANTNO,PLANTNO);
  addWhereClause(CPD_PLANTSTATUS_PLANT::TREATMENTPOSITION,TREATMENTPOSITION);
  addWhereClause(CPD_PLANTSTATUS_PLANT::TYPE,TYPE);
  addWhereClause(CPD_PLANTSTATUS_PLANT::VARNAME,VARNAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_PLANTSTATUS_PLANT::resetPlantStatus(const std::string& PLANT, long PLANTNO, long TREATMENTPOSITION, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true; 

  if ( select(PLANT, PLANTNO, TREATMENTPOSITION, CSMC_DBData::unspecLong, CSMC_DBData::unspecString) )
  {
    setVALUE(CSMC_DBData::unspecString);

    result = update();

    if (!result)
      Error = getLastError();

    if (Commit)
    {
      if (result)
        commit();
      else
        rollback();
    }
  }

  return result;
}

bool CPD_PLANTSTATUS_PLANT::switchTreatmentPosition(const std::string& PLANT,long PLANTNO, long FromTreatPos, long ToTreatPos , bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true;

  result = deleteRows(PLANT, PLANTNO, FromTreatPos, ToTreatPos, Commit, Error);

  if ( result && select(PLANT, PLANTNO, FromTreatPos, CSMC_DBData::unspecLong,  CSMC_DBData::unspecString) )
  {
    for ( long i = 1; i <= getLastRow(); ++i )
    {
      setColumnsFromTable(this, i);

      setTREATMENTPOSITION(ToTreatPos);

      result = result && copy();
    } // for ( long i = 1; i <= getLastRow(); ++i )

    if (!result)
      Error = getLastError();
  }
  else
  {
    CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBReadWarning(sMessage,"PLANT - PLANTNO - TREATMENTPOSITION","PD_PLANTSTATUS_PLANT","NO_DATA_FOUND");
  }

  if (Commit)
  {
    if (result)
      commit();
    else
      rollback();
  }

  return result;
}

bool CPD_PLANTSTATUS_PLANT::updateStatus(const std::string& PLANT, long PLANTNO, long TREATMENTPOSITION, long TYPE, const std::string& VARNAME, const std::string& VALUE, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = false;

  if ( select(PLANT, PLANTNO, TREATMENTPOSITION, TYPE, VARNAME) )
  {
    setVALUE(VALUE);

    result = update();
  }
  else
  {
    setPLANT(PLANT);
    setPLANTNO(PLANTNO);
    setTREATMENTPOSITION(TREATMENTPOSITION);
    setTYPE(TYPE);
    setVARNAME(VARNAME);

    setVALUE(VALUE);

    result = insert();
  }


  if (!result)
    Error = getLastError();

  if (Commit)
  {
    if (result)
      commit();
    else
      rollback();
  }
  return result;
}


bool CPD_PLANTSTATUS_PLANT::deleteRows(const std::string& PLANT, long PLANTNO, long FromTreatPos, long ToTreatPos, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true;

  std::vector<std::string> VarName;

  if ( result && select(PLANT, PLANTNO, FromTreatPos, CSMC_DBData::unspecLong,  CSMC_DBData::unspecString) )
  {
    for ( long i = 1; i <= getLastRow(); ++i )
    {
      VarName.push_back(getVARNAME(i));
    }
  }

  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_PLANTSTATUS_PLANT::PLANT,PLANT);
  addWhereClause(CPD_PLANTSTATUS_PLANT::PLANTNO,PLANTNO);
  addWhereClause(CPD_PLANTSTATUS_PLANT::TREATMENTPOSITION,ToTreatPos);
  addWhereClause(CPD_PLANTSTATUS_PLANT::VARNAME,VarName,"IN");
  m_Statement += getWhereStatement() + ";";

  result = CSMC_DBData::deleteRows();

  if (Commit)
  {
    if (result)
      commit();
    else
      rollback();
  }

  return result;
}


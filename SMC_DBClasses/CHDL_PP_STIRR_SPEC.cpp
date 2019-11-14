//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGTL_PP_STIRR_SPEC.h"
#include "CHDL_PP_STIRR_SPEC.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::INTENSITY("INTENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::STIRRGASTYPE("STIRRGASTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDL_PP_STIRR_SPEC::DURATION("DURATION");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_STIRR_SPEC::CHDL_PP_STIRR_SPEC(cCBS_StdConnection* Connection)
:CSMC_DBData("HDL_PP_STIRR_SPEC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_STIRR_SPEC::CHDL_PP_STIRR_SPEC(cCBS_Connection* Connection)
:CSMC_DBData("HDL_PP_STIRR_SPEC",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_STIRR_SPEC::CHDL_PP_STIRR_SPEC()
:CSMC_DBData("HDL_PP_STIRR_SPEC")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDL_PP_STIRR_SPEC::~CHDL_PP_STIRR_SPEC()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_STIRR_SPEC::getHEATID(long Row)
{
  return getString(CHDL_PP_STIRR_SPEC::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setHEATID(const std::string& value)
{
  setString(CHDL_PP_STIRR_SPEC::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_STIRR_SPEC::getTREATID(long Row)
{
  return getString(CHDL_PP_STIRR_SPEC::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setTREATID(const std::string& value)
{
  setString(CHDL_PP_STIRR_SPEC::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_STIRR_SPEC::getPLANT(long Row)
{
  return getString(CHDL_PP_STIRR_SPEC::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setPLANT(const std::string& value)
{
  setString(CHDL_PP_STIRR_SPEC::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_STIRR_SPEC::getPRACNO(long Row)
{
  return getLong(CHDL_PP_STIRR_SPEC::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setPRACNO(long value)
{
  setLong(CHDL_PP_STIRR_SPEC::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_STIRR_SPEC::getPRACPHASE(long Row)
{
  return getString(CHDL_PP_STIRR_SPEC::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setPRACPHASE(const std::string& value)
{
  setString(CHDL_PP_STIRR_SPEC::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_STIRR_SPEC::getINTENSITY(long Row)
{
  return getLong(CHDL_PP_STIRR_SPEC::INTENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setINTENSITY(long value)
{
  setLong(CHDL_PP_STIRR_SPEC::INTENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDL_PP_STIRR_SPEC::getSTIRRGASTYPE(long Row)
{
  return getString(CHDL_PP_STIRR_SPEC::STIRRGASTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setSTIRRGASTYPE(const std::string& value)
{
  setString(CHDL_PP_STIRR_SPEC::STIRRGASTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDL_PP_STIRR_SPEC::getDURATION(long Row)
{
  return getLong(CHDL_PP_STIRR_SPEC::DURATION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDL_PP_STIRR_SPEC::setDURATION(long value)
{
  setLong(CHDL_PP_STIRR_SPEC::DURATION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDL_PP_STIRR_SPEC::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, const std::string& PRACPHASE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDL_PP_STIRR_SPEC::HEATID,HEATID);
  addWhereClause(CHDL_PP_STIRR_SPEC::TREATID,TREATID);
  addWhereClause(CHDL_PP_STIRR_SPEC::PLANT,PLANT);
  addWhereClause(CHDL_PP_STIRR_SPEC::PRACNO,PRACNO);
  addWhereClause(CHDL_PP_STIRR_SPEC::PRACPHASE,PRACPHASE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDL_PP_STIRR_SPEC::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(HEATID, TREATID, PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

  // preparing setting for source table
  CGTL_PP_STIRR_SPEC GTL_PP_STIRR_SPEC(m_pCBS_StdConnection);
  if ( GTL_PP_STIRR_SPEC.select(PLANT, PLANTNO, PRACNO, CSMC_DBData::unspecString) )
  {
    GTL_PP_STIRR_SPEC.cleanWhereStatement();
    GTL_PP_STIRR_SPEC.addWhereClause(CGTL_PP_STIRR_SPEC::PLANTNO,PLANTNO);
    GTL_PP_STIRR_SPEC.addWhereClause(CGTL_PP_STIRR_SPEC::PRACNO,PRACNO);
  }
  else
  {
    //copy with general plant number
    GTL_PP_STIRR_SPEC.cleanWhereStatement();
    GTL_PP_STIRR_SPEC.addWhereClause(CGTL_PP_STIRR_SPEC::PLANTNO,(long)0);
    GTL_PP_STIRR_SPEC.addWhereClause(CGTL_PP_STIRR_SPEC::PRACNO,PRACNO);
  }

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GTL_PP_STIRR_SPEC);

	if (!result)
		Error = getLastError();

	if(Commit)
  {
		if (result)
			this->commit();
		else
			rollback();
  }

	return result;
}

bool CHDL_PP_STIRR_SPEC::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDL_PP_STIRR_SPEC::HEATID,HEATID);
	addWhereClause(CHDL_PP_STIRR_SPEC::TREATID,TREATID);
	addWhereClause(CHDL_PP_STIRR_SPEC::PLANT,PLANT);
   
  std::string sWhereStatement = getWhereStatement();
  //to avoid the exception like 'Select HEATID from PP_HEAT AND ROWNUM = 1 '
  if(sWhereStatement.length() > 0 ) 
  {
    // do not use ROWNUM in "addWhereClause", ROWNUM is not a table column and where statement will be used for deletion at "deleteRows"
    m_Statement += sWhereStatement + " AND ROWNUM = 1 ;";
  }
  else
  {
    return false;
  }

	return CSMC_DBData::select();
}


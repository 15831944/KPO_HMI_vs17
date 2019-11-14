//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CHDE_PP_EL_PARAM.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::TREATMODENO("TREATMODENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::LIQ_ADD_AMOUNT("LIQ_ADD_AMOUNT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::PRACPHASE("PRACPHASE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::REMEGY("REMEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::BEGINEGYWALLTEMPCTRL("BEGINEGYWALLTEMPCTRL");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::MELTDOWNRATEBSK("MELTDOWNRATEBSK");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::MAXEGYWITHOUTBSKDATA("MAXEGYWITHOUTBSKDATA");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::MAXEGYWITHBSKDATA("MAXEGYWITHBSKDATA");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::AIMTEMP("AIMTEMP");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHDE_PP_EL_PARAM::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_EL_PARAM::CHDE_PP_EL_PARAM(cCBS_StdConnection* Connection)
:CSMC_DBData("HDE_PP_EL_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_EL_PARAM::CHDE_PP_EL_PARAM(cCBS_Connection* Connection)
:CSMC_DBData("HDE_PP_EL_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_EL_PARAM::CHDE_PP_EL_PARAM()
:CSMC_DBData("HDE_PP_EL_PARAM")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHDE_PP_EL_PARAM::~CHDE_PP_EL_PARAM()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_EL_PARAM::getHEATID(long Row)
{
  return getString(CHDE_PP_EL_PARAM::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setHEATID(const std::string& value)
{
  setString(CHDE_PP_EL_PARAM::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_EL_PARAM::getTREATID(long Row)
{
  return getString(CHDE_PP_EL_PARAM::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setTREATID(const std::string& value)
{
  setString(CHDE_PP_EL_PARAM::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_EL_PARAM::getPLANT(long Row)
{
  return getString(CHDE_PP_EL_PARAM::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setPLANT(const std::string& value)
{
  setString(CHDE_PP_EL_PARAM::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getPRACNO(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setPRACNO(long value)
{
  setLong(CHDE_PP_EL_PARAM::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getTREATMODENO(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::TREATMODENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setTREATMODENO(long value)
{
  setLong(CHDE_PP_EL_PARAM::TREATMODENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getLIQ_ADD_AMOUNT(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::LIQ_ADD_AMOUNT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setLIQ_ADD_AMOUNT(long value)
{
  setLong(CHDE_PP_EL_PARAM::LIQ_ADD_AMOUNT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CHDE_PP_EL_PARAM::getPRACPHASE(long Row)
{
  return getString(CHDE_PP_EL_PARAM::PRACPHASE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setPRACPHASE(const std::string& value)
{
  setString(CHDE_PP_EL_PARAM::PRACPHASE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getREMEGY(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::REMEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setREMEGY(long value)
{
  setLong(CHDE_PP_EL_PARAM::REMEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getBEGINEGYWALLTEMPCTRL(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::BEGINEGYWALLTEMPCTRL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setBEGINEGYWALLTEMPCTRL(long value)
{
  setLong(CHDE_PP_EL_PARAM::BEGINEGYWALLTEMPCTRL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_EL_PARAM::getMELTDOWNRATEBSK(long Row)
{
  return getDouble(CHDE_PP_EL_PARAM::MELTDOWNRATEBSK, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setMELTDOWNRATEBSK(double value)
{
  setDouble(CHDE_PP_EL_PARAM::MELTDOWNRATEBSK, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getMAXEGYWITHOUTBSKDATA(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::MAXEGYWITHOUTBSKDATA, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setMAXEGYWITHOUTBSKDATA(long value)
{
  setLong(CHDE_PP_EL_PARAM::MAXEGYWITHOUTBSKDATA, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getMAXEGYWITHBSKDATA(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::MAXEGYWITHBSKDATA, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setMAXEGYWITHBSKDATA(long value)
{
  setLong(CHDE_PP_EL_PARAM::MAXEGYWITHBSKDATA, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CHDE_PP_EL_PARAM::getAIMTEMP(long Row)
{
  return getDouble(CHDE_PP_EL_PARAM::AIMTEMP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setAIMTEMP(double value)
{
  setDouble(CHDE_PP_EL_PARAM::AIMTEMP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHDE_PP_EL_PARAM::getDISPLAY_ORDER(long Row)
{
  return getLong(CHDE_PP_EL_PARAM::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHDE_PP_EL_PARAM::setDISPLAY_ORDER(long value)
{
  setLong(CHDE_PP_EL_PARAM::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHDE_PP_EL_PARAM::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PRACPHASE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHDE_PP_EL_PARAM::HEATID,HEATID);
  addWhereClause(CHDE_PP_EL_PARAM::TREATID,TREATID);
  addWhereClause(CHDE_PP_EL_PARAM::PLANT,PLANT);
  addWhereClause(CHDE_PP_EL_PARAM::PRACNO,PRACNO);
  addWhereClause(CHDE_PP_EL_PARAM::TREATMODENO,TREATMODENO);
  addWhereClause(CHDE_PP_EL_PARAM::LIQ_ADD_AMOUNT,LIQ_ADD_AMOUNT);
  addWhereClause(CHDE_PP_EL_PARAM::PRACPHASE,PRACPHASE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHDE_PP_EL_PARAM::copy(const std::string& HeatId, 
                         const std::string& TreatId, 
                         const std::string& Plant, 
                         long PlantNo,
                         long pPracno, 
                         bool Commit, 
                         cCBS_ODBC_DBError &Error)
{
	bool result = true;
	std::stringstream sql;
	//some data found -> delete them
	if (exists(HeatId, TreatId, Plant,pPracno))
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

	sql << "insert into hde_pp_el_param"
    << "(heatid,"
    << " treatid,"
    << " plant,"
    << " pracno,"
    << " TREATMODENO,"
    << " liq_add_amount,"
    << " pracphase,"
    << " remegy,"
    << " beginegywalltempctrl,"
    << " MELTDOWNRATEBSK,"
    << " MAXEGYWITHOUTBSKDATA,"
    << " MAXEGYWITHBSKDATA,"
    << " AIMTEMP)"
    << "(select  '" << HeatId << "',"
    << "        '"  << TreatId <<"',"
    << "        '"  << Plant <<"',"
    << "        pracno,"
    << "        TREATMODENO,"
    << "        liq_add_amount,"
    << "        pracphase,"
    << "        remegy,"
    << "        beginegywalltempctrl,"
    << "        MELTDOWNRATEBSK,"
    << "        MAXEGYWITHOUTBSKDATA,"
    << "        MAXEGYWITHBSKDATA,"
    << "        AIMTEMP"
    << "   from gte_pp_el_param"
    << "  where plantno = " << PlantNo
    << "   and PRACNO = " << pPracno
    << ")";
	result = result && executeSQL(sql.str());
	if (!result)
		Error = getLastError();

	if(Commit)
  {
		if (result)
			commit();
		else
			rollback();
  }

	return result;
}

bool CHDE_PP_EL_PARAM::exists(const std::string& HeatId, 
                        const std::string& TreatId, 
                        const std::string& Plant,
                        long pPracno
                        )
{
	cleanWhereStatement();

  m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHDE_PP_EL_PARAM::HEATID,HeatId);
	addWhereClause(CHDE_PP_EL_PARAM::TREATID,TreatId);
	addWhereClause(CHDE_PP_EL_PARAM::PLANT,Plant);
  addWhereClause(CHDE_PP_EL_PARAM::PRACNO,pPracno);

  // do not use ROWNUM in "addWhereClause", ROWNUM is not a table column and where statement will be used for deletion at "deleteRows"
  m_Statement += getWhereStatement() + " AND ROWNUM = 1 ;";

  return CSMC_DBData::select();
}


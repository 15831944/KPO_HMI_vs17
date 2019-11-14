//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPDE_HEAT_DATA_BURN.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::BURNERNAME("BURNERNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::STARTTIME("STARTTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::ENDTIME("ENDTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::O2_FLOW("O2_FLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::O2_CONS("O2_CONS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::GAS_FLOW("GAS_FLOW");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPDE_HEAT_DATA_BURN::GAS_CONS("GAS_CONS");

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_HEAT_DATA_BURN::CPDE_HEAT_DATA_BURN(cCBS_StdConnection* Connection)
:CSMC_DBData("PDE_HEAT_DATA_BURN",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_HEAT_DATA_BURN::CPDE_HEAT_DATA_BURN(cCBS_Connection* Connection)
:CSMC_DBData("PDE_HEAT_DATA_BURN",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_HEAT_DATA_BURN::CPDE_HEAT_DATA_BURN()
:CSMC_DBData("PDE_HEAT_DATA_BURN")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPDE_HEAT_DATA_BURN::~CPDE_HEAT_DATA_BURN()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_HEAT_DATA_BURN::getHEATID(long Row)
{
  return getString(CPDE_HEAT_DATA_BURN::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setHEATID(const std::string& value)
{
  setString(CPDE_HEAT_DATA_BURN::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_HEAT_DATA_BURN::getTREATID(long Row)
{
  return getString(CPDE_HEAT_DATA_BURN::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setTREATID(const std::string& value)
{
  setString(CPDE_HEAT_DATA_BURN::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_HEAT_DATA_BURN::getPLANT(long Row)
{
  return getString(CPDE_HEAT_DATA_BURN::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setPLANT(const std::string& value)
{
  setString(CPDE_HEAT_DATA_BURN::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPDE_HEAT_DATA_BURN::getBURNERNAME(long Row)
{
  return getString(CPDE_HEAT_DATA_BURN::BURNERNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setBURNERNAME(const std::string& value)
{
  setString(CPDE_HEAT_DATA_BURN::BURNERNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CPDE_HEAT_DATA_BURN::getSTARTTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDE_HEAT_DATA_BURN::STARTTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setSTARTTIME(const CDateTime& value)
{
 setString(CPDE_HEAT_DATA_BURN::STARTTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CPDE_HEAT_DATA_BURN::getENDTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPDE_HEAT_DATA_BURN::ENDTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setENDTIME(const CDateTime& value)
{
 setString(CPDE_HEAT_DATA_BURN::ENDTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_HEAT_DATA_BURN::getO2_FLOW(long Row)
{
  return getDouble(CPDE_HEAT_DATA_BURN::O2_FLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setO2_FLOW(double value)
{
  setDouble(CPDE_HEAT_DATA_BURN::O2_FLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_HEAT_DATA_BURN::getO2_CONS(long Row)
{
  return getDouble(CPDE_HEAT_DATA_BURN::O2_CONS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setO2_CONS(double value)
{
  setDouble(CPDE_HEAT_DATA_BURN::O2_CONS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_HEAT_DATA_BURN::getGAS_FLOW(long Row)
{
  return getDouble(CPDE_HEAT_DATA_BURN::GAS_FLOW, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setGAS_FLOW(double value)
{
  setDouble(CPDE_HEAT_DATA_BURN::GAS_FLOW, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
double CPDE_HEAT_DATA_BURN::getGAS_CONS(long Row)
{
  return getDouble(CPDE_HEAT_DATA_BURN::GAS_CONS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPDE_HEAT_DATA_BURN::setGAS_CONS(double value)
{
  setDouble(CPDE_HEAT_DATA_BURN::GAS_CONS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPDE_HEAT_DATA_BURN::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& BURNERNAME, const CDateTime& STARTTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDE_HEAT_DATA_BURN::HEATID,HEATID);
  addWhereClause(CPDE_HEAT_DATA_BURN::TREATID,TREATID);
  addWhereClause(CPDE_HEAT_DATA_BURN::PLANT,PLANT);
  addWhereClause(CPDE_HEAT_DATA_BURN::BURNERNAME,BURNERNAME);
  addWhereClause(CPDE_HEAT_DATA_BURN::STARTTIME,STARTTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPDE_HEAT_DATA_BURN::selectActual(const string& HEATID, const string& TREATID, const string& PLANT, const string& BURNERNAME)
{
	cleanWhereStatement();

	m_Statement = "Select * from " + m_TableName;

	addWhereClause(CPDE_HEAT_DATA_BURN::HEATID,HEATID);
	addWhereClause(CPDE_HEAT_DATA_BURN::TREATID,TREATID);
	addWhereClause(CPDE_HEAT_DATA_BURN::PLANT,PLANT);
	addWhereClause(CPDE_HEAT_DATA_BURN::BURNERNAME,BURNERNAME);

  std::string MaxClause = CPDE_HEAT_DATA_BURN::STARTTIME + " = (select max(" + CPDE_HEAT_DATA_BURN::STARTTIME + ") from " + m_TableName + getWhereStatement() +")";
  addWhereClause(MaxClause);

  m_Statement += getWhereStatement() + ";";

	return CSMC_DBData::select();

}

bool CPDE_HEAT_DATA_BURN::selectBurnerConsDataByHeat(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
  cleanWhereStatement();

  std::stringstream sql;

  /*sql<< "select t.heatid,"
    << "       t.treatid,"
    << "       t.plant,"
    << "       t.burnername,"
    << "       max(t.o2_cons) as o2_cons,"
    << "       max(t.gas_cons) as gas_cons"
    << "  from l2smc_eaf.pde_heat_data_burn t"
    << " where t.heatid = '"  << HEATID << "'"
    << "   and t.treatid = '" << TREATID << "'"
    << "   and t.plant = '"   << PLANT << "'"
    << "   group by t.heatid, t.treatid, t.plant, t.burnername";
		*/


	//as per JSW
  sql<< "select t.heatid,"
    << "       t.treatid,"
    << "       t.plant,"
    << "       max(t.o2_cons) as o2_cons,"
    << "       max(t.gas_cons) as gas_cons"
    << "  from l2smc_eaf.pde_heat_data_burn t"
    << " where t.heatid = '"  << HEATID << "'"
    << "   and t.treatid = '" << TREATID << "'"
    << "   and t.plant = '"   << PLANT << "'"
    << "   group by t.heatid, t.treatid, t.plant";

    m_Statement = sql.str();

  bool result = CSMC_DBData::select();

  return result;
}

bool CPDE_HEAT_DATA_BURN::selectNotStopBurner(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT,const std::string& BURNERNAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPDE_HEAT_DATA_BURN::HEATID,HEATID);
  addWhereClause(CPDE_HEAT_DATA_BURN::TREATID,TREATID);
  addWhereClause(CPDE_HEAT_DATA_BURN::PLANT,PLANT);
  addWhereClause(CPDE_HEAT_DATA_BURN::BURNERNAME,BURNERNAME);
  addWhereClause(CPDE_HEAT_DATA_BURN::ENDTIME + " is NULL");

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}



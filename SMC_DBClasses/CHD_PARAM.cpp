//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_PARAM.h"
#include "CGC_PLANTGROUP.h"
#include "CHD_PARAM.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::UNITGROUPNO("UNITGROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PNAME("PNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::TYPE("TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::UNIT("UNIT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::VALUE("VALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::INST_ACTV("INST_ACTV");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::DIALOG_PARAM("DIALOG_PARAM");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::CONV("CONV");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::MIN_VALUE("MIN_VALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::MAX_VALUE("MAX_VALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::CREATIONDATE("CREATIONDATE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PARAMDESCR("PARAMDESCR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PARAMDESCR_C("PARAMDESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM::PARAMGROUP("PARAMGROUP");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM::CHD_PARAM(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM::CHD_PARAM(cCBS_Connection* Connection)
:CSMC_DBData("HD_PARAM",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM::CHD_PARAM()
:CSMC_DBData("HD_PARAM")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM::~CHD_PARAM()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_PARAM::getHEATID(long Row)
{
  return getString(CHD_PARAM::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setHEATID(const std::string& value)
{
  setString(CHD_PARAM::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_PARAM::getTREATID(long Row)
{
  return getString(CHD_PARAM::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setTREATID(const std::string& value)
{
  setString(CHD_PARAM::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_PARAM::getPLANT(long Row)
{
  return getString(CHD_PARAM::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPLANT(const std::string& value)
{
  setString(CHD_PARAM::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unit group number, see GC_PLANT_GROUP
long CHD_PARAM::getUNITGROUPNO(long Row)
{
  return getLong(CHD_PARAM::UNITGROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setUNITGROUPNO(long value)
{
  setLong(CHD_PARAM::UNITGROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Parameter name
std::string CHD_PARAM::getPNAME(long Row)
{
  return getString(CHD_PARAM::PNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPNAME(const std::string& value)
{
  setString(CHD_PARAM::PNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Production Practice Number
long CHD_PARAM::getPRACNO(long Row)
{
  return getLong(CHD_PARAM::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPRACNO(long value)
{
  setLong(CHD_PARAM::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Type indicator (1-9)
long CHD_PARAM::getTYPE(long Row)
{
  return getLong(CHD_PARAM::TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setTYPE(long value)
{
  setLong(CHD_PARAM::TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Engineering unit
std::string CHD_PARAM::getUNIT(long Row)
{
  return getString(CHD_PARAM::UNIT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setUNIT(const std::string& value)
{
  setString(CHD_PARAM::UNIT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value
std::string CHD_PARAM::getVALUE(long Row)
{
  return getString(CHD_PARAM::VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setVALUE(const std::string& value)
{
  setString(CHD_PARAM::VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Immediately active flag
long CHD_PARAM::getINST_ACTV(long Row)
{
  return getLong(CHD_PARAM::INST_ACTV, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setINST_ACTV(long value)
{
  setLong(CHD_PARAM::INST_ACTV, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Can be modified via the dialogue system
long CHD_PARAM::getDIALOG_PARAM(long Row)
{
  return getLong(CHD_PARAM::DIALOG_PARAM, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setDIALOG_PARAM(long value)
{
  setLong(CHD_PARAM::DIALOG_PARAM, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Conversion factor
double CHD_PARAM::getCONV(long Row)
{
  return getDouble(CHD_PARAM::CONV, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setCONV(double value)
{
  setDouble(CHD_PARAM::CONV, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Minimum value
double CHD_PARAM::getMIN_VALUE(long Row)
{
  return getDouble(CHD_PARAM::MIN_VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setMIN_VALUE(double value)
{
  setDouble(CHD_PARAM::MIN_VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Maximum value
double CHD_PARAM::getMAX_VALUE(long Row)
{
  return getDouble(CHD_PARAM::MAX_VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setMAX_VALUE(double value)
{
  setDouble(CHD_PARAM::MAX_VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
CDateTime CHD_PARAM::getCREATIONDATE(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_PARAM::CREATIONDATE, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setCREATIONDATE(const CDateTime& value)
{
 setString(CHD_PARAM::CREATIONDATE, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description of Parameter
std::string CHD_PARAM::getPARAMDESCR(long Row)
{
  return getString(CHD_PARAM::PARAMDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPARAMDESCR(const std::string& value)
{
  setString(CHD_PARAM::PARAMDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Parameter Description Customer
std::string CHD_PARAM::getPARAMDESCR_C(long Row)
{
  return getString(CHD_PARAM::PARAMDESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPARAMDESCR_C(const std::string& value)
{
  setString(CHD_PARAM::PARAMDESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Parameter group
std::string CHD_PARAM::getPARAMGROUP(long Row)
{
  return getString(CHD_PARAM::PARAMGROUP, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM::setPARAMGROUP(const std::string& value)
{
  setString(CHD_PARAM::PARAMGROUP, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_PARAM::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long UNITGROUPNO, const std::string& PNAME, long PRACNO, long TYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_PARAM::HEATID,HEATID);
  addWhereClause(CHD_PARAM::TREATID,TREATID);
  addWhereClause(CHD_PARAM::PLANT,PLANT);
  addWhereClause(CHD_PARAM::UNITGROUPNO,UNITGROUPNO);
  addWhereClause(CHD_PARAM::PNAME,PNAME);
  addWhereClause(CHD_PARAM::PRACNO,PRACNO);
  addWhereClause(CHD_PARAM::TYPE,TYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_PARAM::selectByPlant(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE)
{
  bool RetValue = false;  

  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_PARAM::HEATID,HEATID);
  addWhereClause(CHD_PARAM::TREATID,TREATID);
  addWhereClause(CHD_PARAM::PLANT,PLANT);
  addWhereClause(CHD_PARAM::PNAME,PNAME);
  addWhereClause(CHD_PARAM::PRACNO,PRACNO);
  addWhereClause(CHD_PARAM::TYPE,TYPE);

  // find unitgroup numbers for PLANT and PLANTNO
  std::vector<long> UnitGroupList = getUnitGroupList(PLANT,PLANTNO);
  addWhereClause(CHD_PARAM::UNITGROUPNO,UnitGroupList,"IN");

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CHD_PARAM::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error)
{
  CGC_PLANTGROUP GC_PLANTGROUP(m_pCBS_StdConnection);

  std::vector<long> UnitGroupList = GC_PLANTGROUP.getUnitGroupList(PLANT,PLANTNO);

  return copy(UnitGroupList, HEATID, TREATID, PLANT, PLANTNO, PRACNO, Commit, Error);
}

bool CHD_PARAM::copy(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(pUnitGroup, HEATID, TREATID,PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteData(pUnitGroup, HEATID, TREATID, PLANT, Commit, Error);		
	}

  // preparing setting for source table
  std::vector<long> PRACNOGroup;
  PRACNOGroup.push_back(0);
  PRACNOGroup.push_back(PRACNO);

  CGT_PARAM GT_PARAM(m_pCBS_StdConnection);
  GT_PARAM.addWhereClause(CGT_PARAM::UNITGROUPNO,pUnitGroup, "IN");
  GT_PARAM.addWhereClause(CGT_PARAM::PRACNO,PRACNOGroup, "IN");

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GT_PARAM);

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

std::string CHD_PARAM::ArrayToString(std::vector<long> &pUnitGroup)
{
	string result = "";

	//create the condition
	std::stringstream mUnitNoStream;	
	for (long i = 0; i < (long)pUnitGroup.size(); i++)
		mUnitNoStream << pUnitGroup[i] << ",";

	result = mUnitNoStream.str(); 

	if (!result.empty())
		result = result.substr(0, result.length()-1); //delete the last coma ','
	
	return result;
}

bool CHD_PARAM::deleteData(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
	cleanWhereStatement();

	addWhereClause(CHD_PARAM::HEATID,HEATID);
	addWhereClause(CHD_PARAM::TREATID,TREATID);
	addWhereClause(CHD_PARAM::PLANT,PLANT);
	addWhereClause(CHD_PARAM::UNITGROUPNO,pUnitGroup, "IN");

  bool result = CSMC_DBData::deleteRows();

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

bool CHD_PARAM::exists(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_PARAM::HEATID,HEATID);
	addWhereClause(CHD_PARAM::TREATID,TREATID);
	addWhereClause(CHD_PARAM::PLANT,PLANT);
	addWhereClause(CHD_PARAM::UNITGROUPNO,pUnitGroup, "IN");
   
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

std::vector<long> CHD_PARAM::getUnitGroupList(const std::string& Plant,long PlantNo)
{
  CGC_PLANTGROUP GC_PLANTGROUP(m_pCBS_StdConnection);

  return GC_PLANTGROUP.getUnitGroupList(Plant,PlantNo);
}



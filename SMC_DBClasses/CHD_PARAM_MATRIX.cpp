//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_PARAM_MATRIX.h"
#include "CHD_PARAM_MATRIX.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::UNITGROUPNO("UNITGROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::PNAME("PNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::TYPE("TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::PRACNO("PRACNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::KEY1("KEY1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::KEY2("KEY2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_PARAM_MATRIX::VALUE("VALUE");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM_MATRIX::CHD_PARAM_MATRIX(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_PARAM_MATRIX",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM_MATRIX::CHD_PARAM_MATRIX(cCBS_Connection* Connection)
:CSMC_DBData("HD_PARAM_MATRIX",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM_MATRIX::CHD_PARAM_MATRIX()
:CSMC_DBData("HD_PARAM_MATRIX")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_PARAM_MATRIX::~CHD_PARAM_MATRIX()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_PARAM_MATRIX::getHEATID(long Row)
{
  return getString(CHD_PARAM_MATRIX::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setHEATID(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_PARAM_MATRIX::getTREATID(long Row)
{
  return getString(CHD_PARAM_MATRIX::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setTREATID(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_PARAM_MATRIX::getPLANT(long Row)
{
  return getString(CHD_PARAM_MATRIX::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setPLANT(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unit group number, see GC_PLANT_GROUP
long CHD_PARAM_MATRIX::getUNITGROUPNO(long Row)
{
  return getLong(CHD_PARAM_MATRIX::UNITGROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setUNITGROUPNO(long value)
{
  setLong(CHD_PARAM_MATRIX::UNITGROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Parameter name
std::string CHD_PARAM_MATRIX::getPNAME(long Row)
{
  return getString(CHD_PARAM_MATRIX::PNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setPNAME(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::PNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Type indicator (1-9)
long CHD_PARAM_MATRIX::getTYPE(long Row)
{
  return getLong(CHD_PARAM_MATRIX::TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setTYPE(long value)
{
  setLong(CHD_PARAM_MATRIX::TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Production Practice Number
long CHD_PARAM_MATRIX::getPRACNO(long Row)
{
  return getLong(CHD_PARAM_MATRIX::PRACNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setPRACNO(long value)
{
  setLong(CHD_PARAM_MATRIX::PRACNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##First key
std::string CHD_PARAM_MATRIX::getKEY1(long Row)
{
  return getString(CHD_PARAM_MATRIX::KEY1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setKEY1(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::KEY1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Second key, not used for single, keyed parameter
std::string CHD_PARAM_MATRIX::getKEY2(long Row)
{
  return getString(CHD_PARAM_MATRIX::KEY2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setKEY2(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::KEY2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value
std::string CHD_PARAM_MATRIX::getVALUE(long Row)
{
  return getString(CHD_PARAM_MATRIX::VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_PARAM_MATRIX::setVALUE(const std::string& value)
{
  setString(CHD_PARAM_MATRIX::VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_PARAM_MATRIX::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long UNITGROUPNO, const std::string& PNAME, long TYPE, long PRACNO, const std::string& KEY1, const std::string& KEY2)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_PARAM_MATRIX::HEATID,HEATID);
  addWhereClause(CHD_PARAM_MATRIX::TREATID,TREATID);
  addWhereClause(CHD_PARAM_MATRIX::PLANT,PLANT);
  addWhereClause(CHD_PARAM_MATRIX::UNITGROUPNO,UNITGROUPNO);
  addWhereClause(CHD_PARAM_MATRIX::PNAME,PNAME);
  addWhereClause(CHD_PARAM_MATRIX::TYPE,TYPE);
  addWhereClause(CHD_PARAM_MATRIX::PRACNO,PRACNO);
  addWhereClause(CHD_PARAM_MATRIX::KEY1,KEY1);
  addWhereClause(CHD_PARAM_MATRIX::KEY2,KEY2);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_PARAM_MATRIX::copy(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(pUnitGroup, HEATID, TREATID, PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteData(pUnitGroup, HEATID, TREATID, PLANT, Commit, Error);
	}

  // preparing setting for source table
  std::vector<long> PRACNOGroup;
  PRACNOGroup.push_back(0);
  PRACNOGroup.push_back(PRACNO);

  CGT_PARAM_MATRIX GT_PARAM_MATRIX(m_pCBS_StdConnection);
  GT_PARAM_MATRIX.addWhereClause(CGT_PARAM_MATRIX::UNITGROUPNO,pUnitGroup, "IN");
  GT_PARAM_MATRIX.addWhereClause(CGT_PARAM_MATRIX::PRACNO,PRACNOGroup, "IN");

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT  (PLANT);

  result = result && copyByInsert(&GT_PARAM_MATRIX);

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

std::string CHD_PARAM_MATRIX::ArrayToString(std::vector<long> &pUnitGroup)
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

bool CHD_PARAM_MATRIX::deleteData(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
	cleanWhereStatement();

	addWhereClause(CHD_PARAM_MATRIX::HEATID,HEATID);
	addWhereClause(CHD_PARAM_MATRIX::TREATID,TREATID);
	addWhereClause(CHD_PARAM_MATRIX::PLANT,PLANT);
	addWhereClause(CHD_PARAM_MATRIX::UNITGROUPNO,pUnitGroup, "IN");

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

bool CHD_PARAM_MATRIX::exists(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_PARAM_MATRIX::HEATID,HEATID);
	addWhereClause(CHD_PARAM_MATRIX::TREATID,TREATID);
	addWhereClause(CHD_PARAM_MATRIX::PLANT,PLANT);
	addWhereClause(CHD_PARAM_MATRIX::UNITGROUPNO,pUnitGroup, "IN");
   
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



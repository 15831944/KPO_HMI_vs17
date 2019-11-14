//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_PLANTGROUP.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP::UNITGROUPNO("UNITGROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANTGROUP::PLANTNO("PLANTNO");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP::CGC_PLANTGROUP(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_PLANTGROUP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP::CGC_PLANTGROUP(cCBS_Connection* Connection)
:CSMC_DBData("GC_PLANTGROUP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP::CGC_PLANTGROUP()
:CSMC_DBData("GC_PLANTGROUP")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANTGROUP::~CGC_PLANTGROUP()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unit group number, see GC_PLANT_GROUP
long CGC_PLANTGROUP::getUNITGROUPNO(long Row)
{
  return getLong(CGC_PLANTGROUP::UNITGROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP::setUNITGROUPNO(long value)
{
  setLong(CGC_PLANTGROUP::UNITGROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_PLANTGROUP::getPLANT(long Row)
{
  return getString(CGC_PLANTGROUP::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP::setPLANT(const std::string& value)
{
  setString(CGC_PLANTGROUP::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant number
long CGC_PLANTGROUP::getPLANTNO(long Row)
{
  return getLong(CGC_PLANTGROUP::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANTGROUP::setPLANTNO(long value)
{
  setLong(CGC_PLANTGROUP::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_PLANTGROUP::select(long UNITGROUPNO, const std::string& PLANT, long PLANTNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PLANTGROUP::UNITGROUPNO,UNITGROUPNO);
  addWhereClause(CGC_PLANTGROUP::PLANT,PLANT);
  addWhereClause(CGC_PLANTGROUP::PLANTNO,PLANTNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGC_PLANTGROUP::selectByPlant(const std::string& PLANT, long PLANTNO)
{
	cleanWhereStatement();

	m_Statement = "Select * from " + m_TableName;

	addWhereClause(CGC_PLANTGROUP::PLANT,PLANT);
	addWhereClause(CGC_PLANTGROUP::PLANTNO,PLANTNO);

	m_Statement += getWhereStatement() + ";";

	return CSMC_DBData::select();
}

bool CGC_PLANTGROUP::selectOrdered(long UNITGROUPNO, const std::string& PLANT, long PLANTNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PLANTGROUP::UNITGROUPNO,UNITGROUPNO);
  addWhereClause(CGC_PLANTGROUP::PLANT,PLANT);
  addWhereClause(CGC_PLANTGROUP::PLANTNO,PLANTNO);

  m_Statement += getWhereStatement() + " ORDER BY UNITGROUPNO DESC ;";

  return CSMC_DBData::select();
}

std::vector<long> CGC_PLANTGROUP::getUnitGroupList(const std::string& PLANT, long PLANTNO)
{
  std::vector<long> UnitGroupList;

  if ( selectOrdered(CSMC_DBData::unspecLong, PLANT, PLANTNO) )
  {
    long LastRow = getLastRow(); 

    for ( long i = 1; i <= LastRow ; ++i)
    {
      UnitGroupList.push_back(getUNITGROUPNO(i));
    }
  }

  return UnitGroupList;
}


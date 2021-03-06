//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_EQUIP_COUNTER.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_COUNTER::EQUIP_TYPE("EQUIP_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_COUNTER::COUNTER_TYPE("COUNTER_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_EQUIP_COUNTER::COUNTER_LIMIT("COUNTER_LIMIT");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_COUNTER::CGC_EQUIP_COUNTER(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_COUNTER::CGC_EQUIP_COUNTER(cCBS_Connection* Connection)
:CSMC_DBData("GC_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_COUNTER::CGC_EQUIP_COUNTER()
:CSMC_DBData("GC_EQUIP_COUNTER")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_EQUIP_COUNTER::~CGC_EQUIP_COUNTER()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment type 
std::string CGC_EQUIP_COUNTER::getEQUIP_TYPE(long Row)
{
  return getString(CGC_EQUIP_COUNTER::EQUIP_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_COUNTER::setEQUIP_TYPE(const std::string& value)
{
  setString(CGC_EQUIP_COUNTER::EQUIP_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Counter type used for equipment tracking
std::string CGC_EQUIP_COUNTER::getCOUNTER_TYPE(long Row)
{
  return getString(CGC_EQUIP_COUNTER::COUNTER_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_COUNTER::setCOUNTER_TYPE(const std::string& value)
{
  setString(CGC_EQUIP_COUNTER::COUNTER_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value limit for this counter type
double CGC_EQUIP_COUNTER::getCOUNTER_LIMIT(long Row)
{
  return getDouble(CGC_EQUIP_COUNTER::COUNTER_LIMIT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_EQUIP_COUNTER::setCOUNTER_LIMIT(double value)
{
  setDouble(CGC_EQUIP_COUNTER::COUNTER_LIMIT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_EQUIP_COUNTER::select(const std::string& EQUIP_TYPE, const std::string& COUNTER_TYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_EQUIP_COUNTER::EQUIP_TYPE,EQUIP_TYPE);
  addWhereClause(CGC_EQUIP_COUNTER::COUNTER_TYPE,COUNTER_TYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
//sankar
bool CGC_EQUIP_COUNTER::InsertData(const std::string &EQUIP_TYPE, const std::string &COUNTER_TYPE, double COUNTER_LIMIT, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = true;

  setEQUIP_TYPE         (EQUIP_TYPE);
  setCOUNTER_TYPE       (COUNTER_TYPE);
  setCOUNTER_LIMIT      (COUNTER_LIMIT);

  RetValue = RetValue && insert();

  if (!RetValue)
    Error = getLastError();

  if (Commit)
  {
    if (RetValue)
      commit();
    else
      rollback();
  }

  return RetValue;
}



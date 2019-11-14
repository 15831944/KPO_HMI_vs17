//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_EQUIP_COUNTER.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_EQUIP_COUNTER::EQUIP_ID("EQUIP_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_EQUIP_COUNTER::EQUIP_TYPE("EQUIP_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_EQUIP_COUNTER::COUNTER_TYPE("COUNTER_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_EQUIP_COUNTER::COUNTER_VALUE("COUNTER_VALUE");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_EQUIP_COUNTER::CPD_EQUIP_COUNTER(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_EQUIP_COUNTER::CPD_EQUIP_COUNTER(cCBS_Connection* Connection)
:CSMC_DBData("PD_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_EQUIP_COUNTER::CPD_EQUIP_COUNTER()
:CSMC_DBData("PD_EQUIP_COUNTER")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_EQUIP_COUNTER::~CPD_EQUIP_COUNTER()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment identification 
long CPD_EQUIP_COUNTER::getEQUIP_ID(long Row)
{
  return getLong(CPD_EQUIP_COUNTER::EQUIP_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_EQUIP_COUNTER::setEQUIP_ID(long value)
{
  setLong(CPD_EQUIP_COUNTER::EQUIP_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment type 
std::string CPD_EQUIP_COUNTER::getEQUIP_TYPE(long Row)
{
  return getString(CPD_EQUIP_COUNTER::EQUIP_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_EQUIP_COUNTER::setEQUIP_TYPE(const std::string& value)
{
  setString(CPD_EQUIP_COUNTER::EQUIP_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Counter type used for equipment tracking
std::string CPD_EQUIP_COUNTER::getCOUNTER_TYPE(long Row)
{
  return getString(CPD_EQUIP_COUNTER::COUNTER_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_EQUIP_COUNTER::setCOUNTER_TYPE(const std::string& value)
{
  setString(CPD_EQUIP_COUNTER::COUNTER_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value for this counter
double CPD_EQUIP_COUNTER::getCOUNTER_VALUE(long Row)
{
  return getDouble(CPD_EQUIP_COUNTER::COUNTER_VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_EQUIP_COUNTER::setCOUNTER_VALUE(double value)
{
  setDouble(CPD_EQUIP_COUNTER::COUNTER_VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_EQUIP_COUNTER::select(long EQUIP_ID, const std::string& EQUIP_TYPE, const std::string& COUNTER_TYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_EQUIP_COUNTER::EQUIP_ID,EQUIP_ID);
  addWhereClause(CPD_EQUIP_COUNTER::EQUIP_TYPE,EQUIP_TYPE);
  addWhereClause(CPD_EQUIP_COUNTER::COUNTER_TYPE,COUNTER_TYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_EQUIP_COUNTER::updateOrInsert(long EQUIP_ID,const std::string &EQUIP_TYPE, const std::string &COUNTER_TYPE, long COUNTER_VALUE, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = true;

  
  if ( select(EQUIP_ID, EQUIP_TYPE, COUNTER_TYPE) )
  {
    setEQUIP_ID            (EQUIP_ID);
    setEQUIP_TYPE          (EQUIP_TYPE);
    setCOUNTER_TYPE        (COUNTER_TYPE);
    setCOUNTER_VALUE       (COUNTER_VALUE);

    RetValue = RetValue && update();

  }
  else
  {
    setEQUIP_ID            (EQUIP_ID);
    setEQUIP_TYPE          (EQUIP_TYPE);
    setCOUNTER_TYPE        (COUNTER_TYPE);
    setCOUNTER_VALUE       (COUNTER_VALUE);

    RetValue = RetValue && insert();
  }

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


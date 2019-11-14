//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CHD_EQUIP_COUNTER.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::EQUIP_ID("EQUIP_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::EQUIP_TYPE("EQUIP_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::COUNTER_TYPE("COUNTER_TYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_EQUIP_COUNTER::COUNTER_VALUE("COUNTER_VALUE");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_EQUIP_COUNTER::CHD_EQUIP_COUNTER(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_EQUIP_COUNTER::CHD_EQUIP_COUNTER(cCBS_Connection* Connection)
:CSMC_DBData("HD_EQUIP_COUNTER",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_EQUIP_COUNTER::CHD_EQUIP_COUNTER()
:CSMC_DBData("HD_EQUIP_COUNTER")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_EQUIP_COUNTER::~CHD_EQUIP_COUNTER()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_EQUIP_COUNTER::getHEATID(long Row)
{
  return getString(CHD_EQUIP_COUNTER::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setHEATID(const std::string& value)
{
  setString(CHD_EQUIP_COUNTER::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_EQUIP_COUNTER::getTREATID(long Row)
{
  return getString(CHD_EQUIP_COUNTER::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setTREATID(const std::string& value)
{
  setString(CHD_EQUIP_COUNTER::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_EQUIP_COUNTER::getPLANT(long Row)
{
  return getString(CHD_EQUIP_COUNTER::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setPLANT(const std::string& value)
{
  setString(CHD_EQUIP_COUNTER::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment Id
long CHD_EQUIP_COUNTER::getEQUIP_ID(long Row)
{
  return getLong(CHD_EQUIP_COUNTER::EQUIP_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setEQUIP_ID(long value)
{
  setLong(CHD_EQUIP_COUNTER::EQUIP_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equipment type 
std::string CHD_EQUIP_COUNTER::getEQUIP_TYPE(long Row)
{
  return getString(CHD_EQUIP_COUNTER::EQUIP_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setEQUIP_TYPE(const std::string& value)
{
  setString(CHD_EQUIP_COUNTER::EQUIP_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Counter type used for equipment tracking
std::string CHD_EQUIP_COUNTER::getCOUNTER_TYPE(long Row)
{
  return getString(CHD_EQUIP_COUNTER::COUNTER_TYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setCOUNTER_TYPE(const std::string& value)
{
  setString(CHD_EQUIP_COUNTER::COUNTER_TYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value for this counter
double CHD_EQUIP_COUNTER::getCOUNTER_VALUE(long Row)
{
  return getDouble(CHD_EQUIP_COUNTER::COUNTER_VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_EQUIP_COUNTER::setCOUNTER_VALUE(double value)
{
  setDouble(CHD_EQUIP_COUNTER::COUNTER_VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_EQUIP_COUNTER::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long EQUIP_ID, const std::string& EQUIP_TYPE, const std::string& COUNTER_TYPE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_EQUIP_COUNTER::HEATID,HEATID);
  addWhereClause(CHD_EQUIP_COUNTER::TREATID,TREATID);
  addWhereClause(CHD_EQUIP_COUNTER::PLANT,PLANT);
  addWhereClause(CHD_EQUIP_COUNTER::EQUIP_ID,EQUIP_ID);
  addWhereClause(CHD_EQUIP_COUNTER::EQUIP_TYPE,EQUIP_TYPE);
  addWhereClause(CHD_EQUIP_COUNTER::COUNTER_TYPE,COUNTER_TYPE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 
bool CHD_EQUIP_COUNTER::updateOrInsert(const std::string &HEATID, const std::string &TREATID, const std::string &PLANT, long EQUIP_ID, const std::string& EQUIP_TYPE,const std::string& COUNTER_TYPE,double VALUE, bool Commit,cCBS_ODBC_DBError &Error)
{
  bool RetValue = true;

  if ( select(HEATID, TREATID, PLANT, EQUIP_ID,EQUIP_TYPE,COUNTER_TYPE) )
  {
    setHEATID           (HEATID);
    setTREATID          (TREATID);
    setPLANT            (PLANT);
    setEQUIP_ID         (EQUIP_ID);
    setEQUIP_TYPE       (EQUIP_TYPE);
    setCOUNTER_TYPE     (COUNTER_TYPE);
    setCOUNTER_VALUE    (VALUE);

    RetValue = RetValue && update();
  }
  else
  {
    setHEATID           (HEATID);
    setTREATID          (TREATID);
    setPLANT            (PLANT);
    setEQUIP_ID         (EQUIP_ID);
    setEQUIP_TYPE       (EQUIP_TYPE);
    setCOUNTER_TYPE     (COUNTER_TYPE);
    setCOUNTER_VALUE    (VALUE);

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


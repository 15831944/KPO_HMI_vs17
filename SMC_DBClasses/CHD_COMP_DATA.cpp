//## Copyright (C) 2012 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_COMP_DATA.h"
#include "CHD_COMP_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::DATECHANGE("DATECHANGE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::COMPCODE("COMPCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_COMP_DATA::STATUS("STATUS");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_COMP_DATA::CHD_COMP_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_COMP_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_COMP_DATA::CHD_COMP_DATA(cCBS_Connection* Connection)
:CSMC_DBData("HD_COMP_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_COMP_DATA::CHD_COMP_DATA()
:CSMC_DBData("HD_COMP_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_COMP_DATA::~CHD_COMP_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_COMP_DATA::getHEATID(long Row)
{
  return getString(CHD_COMP_DATA::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setHEATID(const std::string& value)
{
  setString(CHD_COMP_DATA::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_COMP_DATA::getTREATID(long Row)
{
  return getString(CHD_COMP_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setTREATID(const std::string& value)
{
  setString(CHD_COMP_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_COMP_DATA::getPLANT(long Row)
{
  return getString(CHD_COMP_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setPLANT(const std::string& value)
{
  setString(CHD_COMP_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Timestamp indication of the change
CDateTime CHD_COMP_DATA::getDATECHANGE(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_COMP_DATA::DATECHANGE, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setDATECHANGE(const CDateTime& value)
{
 setString(CHD_COMP_DATA::DATECHANGE, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Computer mode
std::string CHD_COMP_DATA::getCOMPCODE(long Row)
{
  return getString(CHD_COMP_DATA::COMPCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setCOMPCODE(const std::string& value)
{
  setString(CHD_COMP_DATA::COMPCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CHD_COMP_DATA::getSTATUS(long Row)
{
  return getLong(CHD_COMP_DATA::STATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_COMP_DATA::setSTATUS(long value)
{
  setLong(CHD_COMP_DATA::STATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_COMP_DATA::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& DATECHANGE, const std::string& COMPCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_COMP_DATA::HEATID,HEATID);
  addWhereClause(CHD_COMP_DATA::TREATID,TREATID);
  addWhereClause(CHD_COMP_DATA::PLANT,PLANT);
  addWhereClause(CHD_COMP_DATA::DATECHANGE,DATECHANGE);
  addWhereClause(CHD_COMP_DATA::COMPCODE,COMPCODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_COMP_DATA::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool result = true;

  //the heat ID, treat ID and PLANT must be set
  if ( CSMC_DBData::unspecString == HEATID
    || CSMC_DBData::unspecString == TREATID
    || CSMC_DBData::unspecString == PLANT
     )
  {
    setLastError("HEAT_INFORMATION_NOT_SET",-1,"");
    Error = getLastError();
    log ("CHD_COMP_DATA::copy heat information not set!",1);
    return false;
  }

  //some data found -> delete them
  if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecDate, CSMC_DBData::unspecString) )
  {
    result = deleteRows();

    if (!result)
    {
      Error = getLastError();
      return result;
    }
  }//if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecDate, CSMC_DBData::unspecString) )

  // preparing setting for source table
  CPD_COMP_DATA PD_COMP_DATA(m_pCBS_StdConnection);

  PD_COMP_DATA.addWhereClause(CPD_COMP_DATA::HEATID  ,HEATID);
  PD_COMP_DATA.addWhereClause(CPD_COMP_DATA::TREATID ,TREATID);
  PD_COMP_DATA.addWhereClause(CPD_COMP_DATA::PLANT   ,PLANT);

  result = result && copyByInsert(&PD_COMP_DATA);

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



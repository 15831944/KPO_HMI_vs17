//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CIntfData.h"
#include "CPD_COMP_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::DATECHANGE("DATECHANGE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::COMPCODE("COMPCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_COMP_DATA::STATUS("STATUS");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COMP_DATA::CPD_COMP_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_COMP_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COMP_DATA::CPD_COMP_DATA(cCBS_Connection* Connection)
:CSMC_DBData("PD_COMP_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COMP_DATA::CPD_COMP_DATA()
:CSMC_DBData("PD_COMP_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_COMP_DATA::~CPD_COMP_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_COMP_DATA::getHEATID(long Row)
{
  return getString(CPD_COMP_DATA::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setHEATID(const std::string& value)
{
  setString(CPD_COMP_DATA::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_COMP_DATA::getTREATID(long Row)
{
  return getString(CPD_COMP_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setTREATID(const std::string& value)
{
  setString(CPD_COMP_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_COMP_DATA::getPLANT(long Row)
{
  return getString(CPD_COMP_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setPLANT(const std::string& value)
{
  setString(CPD_COMP_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Timestamp indication of the change
CDateTime CPD_COMP_DATA::getDATECHANGE(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_COMP_DATA::DATECHANGE, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setDATECHANGE(const CDateTime& value)
{
 setString(CPD_COMP_DATA::DATECHANGE, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Computer mode
std::string CPD_COMP_DATA::getCOMPCODE(long Row)
{
  return getString(CPD_COMP_DATA::COMPCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setCOMPCODE(const std::string& value)
{
  setString(CPD_COMP_DATA::COMPCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CPD_COMP_DATA::getSTATUS(long Row)
{
  return getLong(CPD_COMP_DATA::STATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_COMP_DATA::setSTATUS(long value)
{
  setLong(CPD_COMP_DATA::STATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_COMP_DATA::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& DATECHANGE, const std::string& COMPCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_COMP_DATA::HEATID,HEATID);
  addWhereClause(CPD_COMP_DATA::TREATID,TREATID);
  addWhereClause(CPD_COMP_DATA::PLANT,PLANT);
  addWhereClause(CPD_COMP_DATA::DATECHANGE,DATECHANGE);
  addWhereClause(CPD_COMP_DATA::COMPCODE,COMPCODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_COMP_DATA::selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& DATECHANGE, const std::string& COMPCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_COMP_DATA::HEATID,HEATID);
  addWhereClause(CPD_COMP_DATA::TREATID,TREATID);
  addWhereClause(CPD_COMP_DATA::PLANT,PLANT);
  addWhereClause(CPD_COMP_DATA::DATECHANGE,DATECHANGE);
  addWhereClause(CPD_COMP_DATA::COMPCODE,COMPCODE);

  m_Statement += getWhereStatement() + " order by DATECHANGE DESC;";

  return CSMC_DBData::select();
}

long CPD_COMP_DATA::getActStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& COMPCODE)
{
  long RetValue = CSMC_DBData::unspecLong;

  if ( selectOrdered(HEATID, TREATID, PLANT, CSMC_DBData::unspecDate, COMPCODE) )
  {
    RetValue = getSTATUS(1);
  }

  return RetValue;
}

bool CPD_COMP_DATA::writeStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& COMPCODE, long STATUS)
{
  bool          RetValue   = false;
  CDateTime     now;

  try
  {

    if ( select(HEATID, TREATID, PLANT, CSMC_DBData::unspecDate, COMPCODE) )
    {
      setDATECHANGE(now);
      setSTATUS(STATUS);
      RetValue = update();
    }
    else
    {
      setHEATID(HEATID);
      setTREATID(TREATID);
      setPLANT(PLANT);
      setCOMPCODE(COMPCODE);

      setDATECHANGE(now);
      setSTATUS(STATUS);
      RetValue = insert();
    }

    if (RetValue)
    {
      commit();
    }
    else
    {
      rollback();
    }
  }
  catch(...)
  {
    rollback();
    RetValue = false;
  }
  return RetValue;
}

bool CPD_COMP_DATA::writeStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, seqComputerModes& SeqComputerModes)
{
  bool RetValue = false;

  try
  {
    for (long i = 0; i < CIntfData::getLength(SeqComputerModes); i++) 
    {
      sComputerMode Mode;
      CIntfData::getAt(Mode, SeqComputerModes, i);

      writeStatus(HEATID, TREATID, PLANT, (std::string)Mode.Device, Mode.Status);
    }

    RetValue = true;

  }
  catch(...)
  {
    RetValue = false;
    rollback(); //something wrong, rollback transaction.
  }

  return RetValue;
}



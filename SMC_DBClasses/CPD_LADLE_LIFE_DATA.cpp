//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CDataConversion.h"
#include "CGC_LADLE_DEF.h"
#include "CPD_LADLE_LIFE_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::LADLENO("LADLENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::LADLETYPE("LADLETYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::LADLEPARTCODE("LADLEPARTCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::DATEOFPARTCHG("DATEOFPARTCHG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::LIFE("LIFE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::PARTTYPE("PARTTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::PARTSIZE("PARTSIZE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_LADLE_LIFE_DATA::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_LADLE_LIFE_DATA::CPD_LADLE_LIFE_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_LADLE_LIFE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_LADLE_LIFE_DATA::CPD_LADLE_LIFE_DATA(cCBS_Connection* Connection)
:CSMC_DBData("PD_LADLE_LIFE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_LADLE_LIFE_DATA::CPD_LADLE_LIFE_DATA()
:CSMC_DBData("PD_LADLE_LIFE_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_LADLE_LIFE_DATA::~CPD_LADLE_LIFE_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique ladle number
long CPD_LADLE_LIFE_DATA::getLADLENO(long Row)
{
  return getLong(CPD_LADLE_LIFE_DATA::LADLENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setLADLENO(long value)
{
  setLong(CPD_LADLE_LIFE_DATA::LADLENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##e.g. Hot Metal -> H, Teeming -> T
std::string CPD_LADLE_LIFE_DATA::getLADLETYPE(long Row)
{
  return getString(CPD_LADLE_LIFE_DATA::LADLETYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setLADLETYPE(const std::string& value)
{
  setString(CPD_LADLE_LIFE_DATA::LADLETYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Ladle part code
std::string CPD_LADLE_LIFE_DATA::getLADLEPARTCODE(long Row)
{
  return getString(CPD_LADLE_LIFE_DATA::LADLEPARTCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setLADLEPARTCODE(const std::string& value)
{
  setString(CPD_LADLE_LIFE_DATA::LADLEPARTCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Timestamp indication of the part change
CDateTime CPD_LADLE_LIFE_DATA::getDATEOFPARTCHG(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_LADLE_LIFE_DATA::DATEOFPARTCHG, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setDATEOFPARTCHG(const CDateTime& value)
{
 setString(CPD_LADLE_LIFE_DATA::DATEOFPARTCHG, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##No of heats for this part
long CPD_LADLE_LIFE_DATA::getLIFE(long Row)
{
  return getLong(CPD_LADLE_LIFE_DATA::LIFE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setLIFE(long value)
{
  setLong(CPD_LADLE_LIFE_DATA::LIFE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specific Type of Part - may be material, age or whatever
std::string CPD_LADLE_LIFE_DATA::getPARTTYPE(long Row)
{
  return getString(CPD_LADLE_LIFE_DATA::PARTTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setPARTTYPE(const std::string& value)
{
  setString(CPD_LADLE_LIFE_DATA::PARTTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specific Size of Part may 1, 2, 3, or [cm] or whatever
long CPD_LADLE_LIFE_DATA::getPARTSIZE(long Row)
{
  return getLong(CPD_LADLE_LIFE_DATA::PARTSIZE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setPARTSIZE(long value)
{
  setLong(CPD_LADLE_LIFE_DATA::PARTSIZE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CPD_LADLE_LIFE_DATA::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_LADLE_LIFE_DATA::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_LADLE_LIFE_DATA::setREVTIME(const CDateTime& value)
{
 setString(CPD_LADLE_LIFE_DATA::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_LADLE_LIFE_DATA::select(long LADLENO, const std::string& LADLETYPE, const std::string& LADLEPARTCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_LADLE_LIFE_DATA::LADLENO,LADLENO);
  addWhereClause(CPD_LADLE_LIFE_DATA::LADLETYPE,LADLETYPE);
  addWhereClause(CPD_LADLE_LIFE_DATA::LADLEPARTCODE,LADLEPARTCODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

long CPD_LADLE_LIFE_DATA::getLife(long LADLENO, const std::string& LADLETYPE, const std::string& LADLEPARTCODE)
{
  long Life = CSMC_DBData::unspecLong;

  if ( select(LADLENO, LADLETYPE, LADLEPARTCODE) )
  {
    Life = getLIFE(1);
  }

  return Life;
}

bool CPD_LADLE_LIFE_DATA::incrLife(long LADLENO, const std::string& LADLETYPE, std::vector<std::string>& LADLEPARTCODES, bool Commit)
{
  bool RetValue = true;

  std::vector<std::string>::iterator it;

  for ( it = LADLEPARTCODES.begin() ; it != LADLEPARTCODES.end() ; ++it)
  {
    std::string PartCode = (*it);

    if ( PartCode.empty() || PartCode== CSMC_DBData::unspecString )
    {
      continue;
    }

    RetValue = RetValue && incrLife(LADLENO, LADLETYPE, PartCode, Commit);
  }


  return RetValue;
}

bool CPD_LADLE_LIFE_DATA::incrLife(long LADLENO, const std::string& LADLETYPE, const std::string& LADLEPARTCODE, bool Commit)
{
  bool RetValue = true;

  setREVTIME       ( CDateTime() );

  if ( select(LADLENO, LADLETYPE, LADLEPARTCODE) )
  {
    long LIFE = CDataConversion::SetInvalidToDefault(getLIFE(1), 0, CSMC_DBData::unspecLong);

    setLIFE          ( LIFE + 1 );
   
    setDATEOFPARTCHG ( CDateTime() );

    RetValue = update();
  }
  else
  {
    CGC_LADLE_DEF             GC_LADLE_DEF            (m_pCBS_StdConnection);

    if ( GC_LADLE_DEF.isValidLadle(LADLENO, LADLETYPE) )
    {
      setLADLENO(LADLENO);
      setLADLETYPE(LADLETYPE);
      setLADLEPARTCODE(LADLEPARTCODE);

      setLIFE( 1 );

      RetValue = insert();
    }
  }

  if ( Commit )
  {
    if ( RetValue )
    {
      commit();
    }
    else
    {
      rollback();
    }
  }

  return RetValue;
}

//sankar
bool CPD_LADLE_LIFE_DATA::setLifeData(long LADLENO, const std::string& LADLETYPE, const std::string& LADLEPARTCODE, long life, bool Commit)
{
  bool RetValue = true;

  setREVTIME       ( CDateTime() );

  if ( select(LADLENO, LADLETYPE, LADLEPARTCODE) )
  {
    setLIFE          ( life );
   
    RetValue = update();
  }
  else
  {
    CGC_LADLE_DEF             GC_LADLE_DEF            (m_pCBS_StdConnection);

    if ( GC_LADLE_DEF.isValidLadle(LADLENO, LADLETYPE) )
    {
      setLADLENO(LADLENO);
      setLADLETYPE(LADLETYPE);
      setLADLEPARTCODE(LADLEPARTCODE);

      setLIFE( life );

      RetValue = insert();
    }
  }

  if ( Commit )
  {
    if ( RetValue )
    {
      commit();
    }
    else
    {
      rollback();
    }
  }

  return RetValue;
}



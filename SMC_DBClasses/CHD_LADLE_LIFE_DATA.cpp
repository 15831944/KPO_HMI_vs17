//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CSMC_EventLogFrameController.h"

#include "CGC_Ladle_Def_Container.h"
#include "CPD_HEAT_DATA.h"
#include "CPD_LADLE_LIFE_DATA.h"
#include "CHD_LADLE_LIFE_DATA.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::LADLENO("LADLENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::LADLETYPE("LADLETYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::LADLEPARTCODE("LADLEPARTCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::DATEOFPARTCHG("DATEOFPARTCHG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::LIFE("LIFE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::PARTTYPE("PARTTYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::PARTSIZE("PARTSIZE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_LADLE_LIFE_DATA::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_LADLE_LIFE_DATA::CHD_LADLE_LIFE_DATA(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_LADLE_LIFE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_LADLE_LIFE_DATA::CHD_LADLE_LIFE_DATA(cCBS_Connection* Connection)
:CSMC_DBData("HD_LADLE_LIFE_DATA",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_LADLE_LIFE_DATA::CHD_LADLE_LIFE_DATA()
:CSMC_DBData("HD_LADLE_LIFE_DATA")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_LADLE_LIFE_DATA::~CHD_LADLE_LIFE_DATA()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CHD_LADLE_LIFE_DATA::getHEATID(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setHEATID(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_LADLE_LIFE_DATA::getTREATID(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setTREATID(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_LADLE_LIFE_DATA::getPLANT(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setPLANT(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique ladle number
long CHD_LADLE_LIFE_DATA::getLADLENO(long Row)
{
  return getLong(CHD_LADLE_LIFE_DATA::LADLENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setLADLENO(long value)
{
  setLong(CHD_LADLE_LIFE_DATA::LADLENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##e.g. Hot Metal -> H, Teeming -> T
std::string CHD_LADLE_LIFE_DATA::getLADLETYPE(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::LADLETYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setLADLETYPE(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::LADLETYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Ladle part code
std::string CHD_LADLE_LIFE_DATA::getLADLEPARTCODE(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::LADLEPARTCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setLADLEPARTCODE(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::LADLEPARTCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Timestamp indication of the part change
CDateTime CHD_LADLE_LIFE_DATA::getDATEOFPARTCHG(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_LADLE_LIFE_DATA::DATEOFPARTCHG, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setDATEOFPARTCHG(const CDateTime& value)
{
 setString(CHD_LADLE_LIFE_DATA::DATEOFPARTCHG, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##No of heats for this part
long CHD_LADLE_LIFE_DATA::getLIFE(long Row)
{
  return getLong(CHD_LADLE_LIFE_DATA::LIFE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setLIFE(long value)
{
  setLong(CHD_LADLE_LIFE_DATA::LIFE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specific Type of Part - may be material, age or whatever
std::string CHD_LADLE_LIFE_DATA::getPARTTYPE(long Row)
{
  return getString(CHD_LADLE_LIFE_DATA::PARTTYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setPARTTYPE(const std::string& value)
{
  setString(CHD_LADLE_LIFE_DATA::PARTTYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Specific Size of Part may 1, 2, 3, or [cm] or whatever
long CHD_LADLE_LIFE_DATA::getPARTSIZE(long Row)
{
  return getLong(CHD_LADLE_LIFE_DATA::PARTSIZE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setPARTSIZE(long value)
{
  setLong(CHD_LADLE_LIFE_DATA::PARTSIZE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CHD_LADLE_LIFE_DATA::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_LADLE_LIFE_DATA::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_LADLE_LIFE_DATA::setREVTIME(const CDateTime& value)
{
 setString(CHD_LADLE_LIFE_DATA::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_LADLE_LIFE_DATA::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long LADLENO, const std::string& LADLETYPE, const std::string& LADLEPARTCODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_LADLE_LIFE_DATA::HEATID,HEATID);
  addWhereClause(CHD_LADLE_LIFE_DATA::TREATID,TREATID);
  addWhereClause(CHD_LADLE_LIFE_DATA::PLANT,PLANT);
  addWhereClause(CHD_LADLE_LIFE_DATA::LADLENO,LADLENO);
  addWhereClause(CHD_LADLE_LIFE_DATA::LADLETYPE,LADLETYPE);
  addWhereClause(CHD_LADLE_LIFE_DATA::LADLEPARTCODE,LADLEPARTCODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_LADLE_LIFE_DATA::selectByREVTIME(const CDateTime& REVTIME, const std::string& Operator)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_LADLE_LIFE_DATA::REVTIME, REVTIME, Operator );

  m_Statement += getWhereStatement() + " order by REVTIME desc;";

  return CSMC_DBData::select();
}

bool CHD_LADLE_LIFE_DATA::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, bool Commit, cCBS_ODBC_DBError &Error)
{
	//bool result = !exists(HEATID,TREATID);
	bool result = !exists(HEATID,TREATID,PLANT);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows();
		if (!result)
			setLastError(std::string("ERROR_DELETE_DATA"), 0, getActStatement());
	}

  CPD_HEAT_DATA           PD_HEAT_DATA(m_pCBS_StdConnection);
  CGC_Ladle_Def_Container GC_Ladle_Def_Container(m_pCBS_StdConnection);

  if ( PD_HEAT_DATA.select(HEATID, TREATID, PLANT ) )
  {
    std::string LADLETYPE = PD_HEAT_DATA.getLADLETYPE(1);
    long LADLENO          = PD_HEAT_DATA.getLADLENO(1);

    if ( GC_Ladle_Def_Container.isValidLadle(LADLENO, LADLETYPE) )
    {
      // preparing setting for source table
      CPD_LADLE_LIFE_DATA PD_LADLE_LIFE_DATA(m_pCBS_StdConnection);
      PD_LADLE_LIFE_DATA.addWhereClause(CPD_LADLE_LIFE_DATA::LADLENO,LADLENO);
      PD_LADLE_LIFE_DATA.addWhereClause(CPD_LADLE_LIFE_DATA::LADLETYPE,LADLETYPE);

      // preparing setting for aim table
      setHEATID (HEATID);
      setTREATID(TREATID);

      setPLANT(PLANT);

      result = result && copyByInsert(&PD_LADLE_LIFE_DATA);
    }
  }

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

//bool CHD_LADLE_LIFE_DATA::exists(const std::string& HEATID, const std::string& TREATID)
bool CHD_LADLE_LIFE_DATA::exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT)
{
	cleanWhereStatement();

	m_Statement = "Select HEATID from " + m_TableName;

	addWhereClause(CHD_LADLE_LIFE_DATA::HEATID,HEATID);
	addWhereClause(CHD_LADLE_LIFE_DATA::TREATID,TREATID);
	addWhereClause(CHD_LADLE_LIFE_DATA::PLANT,PLANT);
   
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



//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_HEAT_STATUS.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::HEATSTATUSNO("HEATSTATUSNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::HEATSTATUS("HEATSTATUS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::HEATSTATUSDESCR("HEATSTATUSDESCR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::HEATSTATNO_L3("HEATSTATNO_L3");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_HEAT_STATUS::HEATSTATNO_CCS("HEATSTATNO_CCS");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_HEAT_STATUS::CGC_HEAT_STATUS(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_HEAT_STATUS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_HEAT_STATUS::CGC_HEAT_STATUS(cCBS_Connection* Connection)
:CSMC_DBData("GC_HEAT_STATUS",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_HEAT_STATUS::CGC_HEAT_STATUS()
:CSMC_DBData("GC_HEAT_STATUS")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_HEAT_STATUS::~CGC_HEAT_STATUS()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Heat Status as defined in the Requirement Book Naming standard specification.
long CGC_HEAT_STATUS::getHEATSTATUSNO(long Row)
{
  return getLong(CGC_HEAT_STATUS::HEATSTATUSNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setHEATSTATUSNO(long value)
{
  setLong(CGC_HEAT_STATUS::HEATSTATUSNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_HEAT_STATUS::getPLANT(long Row)
{
  return getString(CGC_HEAT_STATUS::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setPLANT(const std::string& value)
{
  setString(CGC_HEAT_STATUS::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Heat status name, used for generation of definition in header files (one word only)
std::string CGC_HEAT_STATUS::getHEATSTATUS(long Row)
{
  return getString(CGC_HEAT_STATUS::HEATSTATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setHEATSTATUS(const std::string& value)
{
  setString(CGC_HEAT_STATUS::HEATSTATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description of Heat Status
std::string CGC_HEAT_STATUS::getHEATSTATUSDESCR(long Row)
{
  return getString(CGC_HEAT_STATUS::HEATSTATUSDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setHEATSTATUSDESCR(const std::string& value)
{
  setString(CGC_HEAT_STATUS::HEATSTATUSDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGC_HEAT_STATUS::getHEATSTATNO_L3(long Row)
{
  return getLong(CGC_HEAT_STATUS::HEATSTATNO_L3, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setHEATSTATNO_L3(long value)
{
  setLong(CGC_HEAT_STATUS::HEATSTATNO_L3, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGC_HEAT_STATUS::getHEATSTATNO_CCS(long Row)
{
  return getLong(CGC_HEAT_STATUS::HEATSTATNO_CCS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_HEAT_STATUS::setHEATSTATNO_CCS(long value)
{
  setLong(CGC_HEAT_STATUS::HEATSTATNO_CCS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_HEAT_STATUS::select(long HEATSTATUSNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_HEAT_STATUS::HEATSTATUSNO,HEATSTATUSNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGC_HEAT_STATUS::select(const std::string &PLANT, const std::string &HEATSTATUS)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_HEAT_STATUS::PLANT, PLANT);
  addWhereClause(CGC_HEAT_STATUS::HEATSTATUS, HEATSTATUS);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();  
}

std::string CGC_HEAT_STATUS::getHeatStatus(long HEATSTATUSNO)
{
  std::string HeatStatus = CSMC_DBData::unspecString;
	
  if( select(HEATSTATUSNO))  
  {
    HeatStatus = getHEATSTATUS(1);
  }

	return HeatStatus;
}

long CGC_HEAT_STATUS::getHeatStatusNo(const std::string &PLANT, const std::string &HEATSTATUS)
{
  long returnValue = -1;
	
	cleanWhereStatement();
	m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_HEAT_STATUS::PLANT, PLANT);
  addWhereClause(CGC_HEAT_STATUS::HEATSTATUS, HEATSTATUS);

  m_Statement += getWhereStatement() + ";";

  if(CSMC_DBData::select())  
  {
    returnValue = getHEATSTATUSNO(1);
  }

	return returnValue;
}


long CGC_HEAT_STATUS::getHeatStatusNo(const std::string &PLANT, long HEATSTATUSNO_L3,long HEATSTATUSNO_CCS)
{
  long returnValue = -1;
	
	cleanWhereStatement();
	m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_HEAT_STATUS::PLANT, PLANT);
  addWhereClause(CGC_HEAT_STATUS::HEATSTATNO_L3, HEATSTATUSNO_L3);
  addWhereClause(CGC_HEAT_STATUS::HEATSTATNO_CCS, HEATSTATUSNO_CCS);

  m_Statement += getWhereStatement() + ";";

  if(CSMC_DBData::select())  
  {
    returnValue = getHEATSTATUSNO(1);
  }

	return returnValue;
}


std::vector<long> CGC_HEAT_STATUS::getPlantRelatedStates(const std::string& PLANT)
{
  std::vector<long> PlantRelatedStates;

  if ( select(PLANT, CSMC_DBData::unspecString) )
  {
    for ( long i = 1; i <= getLastRow(); ++i )
    {
      PlantRelatedStates.push_back(getHEATSTATUSNO(i));
    }
  }

  return PlantRelatedStates;
}



//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_ACTION_DEF.h"
#include "DEF_GC_ACTION_DEF.h"
#include "CPD_ACTION.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ACTIONNO("ACTIONNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::REVTIME("REVTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::DURSINCEHEATANNOUNCEMENT("DURSINCEHEATANNOUNCEMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::O2_MOMENT("O2_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::N2_MOMENT("N2_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::AR_MOMENT("AR_MOMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ELECEGY("ELECEGY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ACTIONNAME("ACTIONNAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ACTIONUNIT("ACTIONUNIT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ACTIONVALUE("ACTIONVALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CPD_ACTION::ACTIONSTATUS("ACTIONSTATUS");

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_ACTION::CPD_ACTION(cCBS_StdConnection* Connection)
:CSMC_DBData("PD_ACTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_ACTION::CPD_ACTION(cCBS_Connection* Connection)
:CSMC_DBData("PD_ACTION",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_ACTION::CPD_ACTION()
:CSMC_DBData("PD_ACTION")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CPD_ACTION::~CPD_ACTION()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Internal heat identifier
std::string CPD_ACTION::getHEATID(long Row)
{
  return getString(CPD_ACTION::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setHEATID(const std::string& value)
{
  setString(CPD_ACTION::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CPD_ACTION::getTREATID(long Row)
{
  return getString(CPD_ACTION::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setTREATID(const std::string& value)
{
  setString(CPD_ACTION::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CPD_ACTION::getPLANT(long Row)
{
  return getString(CPD_ACTION::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setPLANT(const std::string& value)
{
  setString(CPD_ACTION::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique action number
long CPD_ACTION::getACTIONNO(long Row)
{
  return getLong(CPD_ACTION::ACTIONNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setACTIONNO(long value)
{
  setLong(CPD_ACTION::ACTIONNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CPD_ACTION::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CPD_ACTION::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setREVTIME(const CDateTime& value)
{
 setString(CPD_ACTION::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since heat announcement
double CPD_ACTION::getDURSINCEHEATANNOUNCEMENT(long Row)
{
  return getDouble(CPD_ACTION::DURSINCEHEATANNOUNCEMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setDURSINCEHEATANNOUNCEMENT(double value)
{
  setDouble(CPD_ACTION::DURSINCEHEATANNOUNCEMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Metallurgical Nm3 since start of heat
double CPD_ACTION::getO2_MOMENT(long Row)
{
  return getDouble(CPD_ACTION::O2_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setO2_MOMENT(double value)
{
  setDouble(CPD_ACTION::O2_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Metallurgical Nm3 since start of heat
double CPD_ACTION::getN2_MOMENT(long Row)
{
  return getDouble(CPD_ACTION::N2_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setN2_MOMENT(double value)
{
  setDouble(CPD_ACTION::N2_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Argon consumption
double CPD_ACTION::getAR_MOMENT(long Row)
{
  return getDouble(CPD_ACTION::AR_MOMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setAR_MOMENT(double value)
{
  setDouble(CPD_ACTION::AR_MOMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since start of heat
double CPD_ACTION::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CPD_ACTION::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CPD_ACTION::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Total electric energy consumption when action occurs in case of electric heating, kWh
double CPD_ACTION::getELECEGY(long Row)
{
  return getDouble(CPD_ACTION::ELECEGY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setELECEGY(double value)
{
  setDouble(CPD_ACTION::ELECEGY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Action name
std::string CPD_ACTION::getACTIONNAME(long Row)
{
  return getString(CPD_ACTION::ACTIONNAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setACTIONNAME(const std::string& value)
{
  setString(CPD_ACTION::ACTIONNAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPD_ACTION::getACTIONUNIT(long Row)
{
  return getString(CPD_ACTION::ACTIONUNIT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setACTIONUNIT(const std::string& value)
{
  setString(CPD_ACTION::ACTIONUNIT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CPD_ACTION::getACTIONVALUE(long Row)
{
  return getString(CPD_ACTION::ACTIONVALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setACTIONVALUE(const std::string& value)
{
  setString(CPD_ACTION::ACTIONVALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##0=Not Finished, 1=Finished
long CPD_ACTION::getACTIONSTATUS(long Row)
{
  return getLong(CPD_ACTION::ACTIONSTATUS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CPD_ACTION::setACTIONSTATUS(long value)
{
  setLong(CPD_ACTION::ACTIONSTATUS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CPD_ACTION::select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO, const CDateTime& REVTIME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);
  addWhereClause(CPD_ACTION::REVTIME,REVTIME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CPD_ACTION::selectByActionNo(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement += getWhereStatement() + " order by revtime ;";


  return CSMC_DBData::select();
}

bool CPD_ACTION::CalcAndStoreDuration(const string& HEATID, const string& TREATID, const string& PLANT, long ACTIONNO,bool pCommit)
{
	bool retVal = true;

	//get the two last record from action number 1102 and 1103 and fill duration number
	double  dbBegin = 0;
	GetLastPowerEventTime(  HEATID,TREATID,PLANT,1102,dbBegin );
	double  dbEnd   = 0;
	GetLastPowerEventTime(  HEATID,TREATID,PLANT,1103,dbEnd  );

	double  dbDuration = dbEnd - dbBegin;

	std::stringstream sDuration;
	sDuration << dbDuration;
	CDateTime now;

	if( select(HEATID,TREATID,PLANT,ACTIONNO,CSMC_DBData::unspecDate ) )
	{
		double dbLastDuration = getDURSINCEHEATANNOUNCEMENT(1);
	  setREVTIME(now);
	  setACTIONNAME(m_Row.ACTIONNAME);
	  setACTIONUNIT(m_Row.ACTIONUNIT);
	  //setACTIONVALUE(m_Row.ACTIONVALUE);
	  setACTIONVALUE( sDuration.str() );
	  setACTIONSTATUS(m_Row.ACTIONSTATUS);
	  setDURSINCESTARTOFHEAT( m_Row.DURSINCESTARTOFHEAT );
	  setO2_MOMENT(m_Row.O2_MOMENT);
	  setN2_MOMENT(m_Row.N2_MOMENT);
	  setAR_MOMENT(m_Row.AR_MOMENT);
	  setELECEGY(m_Row.ELECEGY);   

	  //Add two duration
	  setDURSINCEHEATANNOUNCEMENT( dbLastDuration +  dbDuration );
	  retVal = update();
	}else{
	  //insert a new row
	  setHEATID(  HEATID );
	  setTREATID( TREATID);
	  setPLANT(   PLANT);
	  setACTIONNO(ACTIONNO);

	  setREVTIME(now);
	  setACTIONNAME(m_Row.ACTIONNAME);
	  setACTIONUNIT(m_Row.ACTIONUNIT);
	  //setACTIONVALUE(m_Row.ACTIONVALUE);	  
	  setACTIONVALUE( sDuration.str() );
	  setACTIONSTATUS(m_Row.ACTIONSTATUS);
	  setDURSINCESTARTOFHEAT( m_Row.DURSINCESTARTOFHEAT );
	  setO2_MOMENT(m_Row.O2_MOMENT);
	  setN2_MOMENT(m_Row.N2_MOMENT);
	  setAR_MOMENT(m_Row.AR_MOMENT);
	  setELECEGY(m_Row.ELECEGY);   
	  setDURSINCEHEATANNOUNCEMENT( dbDuration );
	  retVal = insert();
	}

	if (pCommit)
	{
	if (retVal)
		commit();
	else
		rollback();
	}

	return retVal;
}

void CPD_ACTION::doOnConstruct()
{
  CGC_ACTION_DEF GC_ACTION_DEF( m_pCBS_StdConnection );

  if ( GC_ACTION_DEF.select(CSMC_DBData::unspecLong) )
  {
    for ( long i = 1; i<= GC_ACTION_DEF.getLastRow(); ++i )
    { 
      long actionNo = GC_ACTION_DEF.getACTIONNO(i);
      std::string actionName = GC_ACTION_DEF.getACTIONNAME(i);

      m_DefinedActions.insert(make_pair(actionNo,actionName));
    }
  }
}

double CPD_ACTION::getAccumulatedDuration( const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO_START, long ACTIONNO_END )
{
  double Duration = CSMC_DBData::unspecDouble;

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO_START);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO_END);
  addWhereClause(CPD_ACTION::REVTIME,REVTIME);

  m_Statement += getWhereStatement() + " ORDER BY REVTIME ;";

  // duration as addition of duration between ACTION_START and ACTION_END sequence
  if( CSMC_DBData::select() )
  {
    Duration = 0.;

    CDateTime REVTIME_START(CSMC_DBData::unspecDate);
    CDateTime REVTIME_END(CSMC_DBData::unspecDate);

    for ( long i = 1; i<= getLastRow(); ++i )
    { 
      // find start for ACTIONNO_START
      if ( REVTIME_START  == CSMC_DBData::unspecDate &&
           getACTIONNO(i) == ACTIONNO_START )
      {
        REVTIME_START = getREVTIME(i);
      }
      // if started, find end for ACTIONNO_END
      else if ( REVTIME_START  != CSMC_DBData::unspecDate &&
                getACTIONNO(i) == ACTIONNO_END )
      {
        REVTIME_END = getREVTIME(i);

        // now we may have to valid REVTIMEs to compare
        if ( REVTIME_END != CSMC_DBData::unspecDate )
        {
          CDeltaTime DiffTime = CDateTime::subTimes(REVTIME_END, REVTIME_START);

          Duration += DiffTime.asSeconds() / 60;

          // prepare for next ACTION_START and ACTION_END sequence
          REVTIME_START  = CSMC_DBData::unspecDate;
        } // if ( REVTIME_END != CSMC_DBData::unspecDate )
      } // if ( REVTIME_START  == CSMC_DBData::unspecDate &&
    } // for ( long i = 1; i<= getLastRow(); ++i )
  } // if( CSMC_DBData::select() )

  return Duration;
}

std::string CPD_ACTION::getActionDefName(long ACTIONNO)
{
  std::string RetVal ;
  std::map<long,string>::iterator it = m_DefinedActions.find(ACTIONNO);

  if ( it != m_DefinedActions.end() )
  {
    RetVal = (std::string)it->second ;
  }

  return RetVal;
}

double CPD_ACTION::GetFirstEventDurationSinceStart(  const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO )
{
  double DurationSinceStart = CSMC_DBData::unspecDouble;

  cleanWhereStatement();

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement = "Select min(DURSINCESTARTOFHEAT) as DURSINCESTARTOFHEAT from " + m_TableName;  
  m_Statement += getWhereStatement() + ";";


  if( CSMC_DBData::select() )
  {
    DurationSinceStart = getDURSINCESTARTOFHEAT(1);
  }

  return DurationSinceStart;
}

CDateTime CPD_ACTION::GetFirstEventRevTime( const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO )
{
  CDateTime EventTime = CSMC_DBData::unspecDate;
  cleanWhereStatement();

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement = "Select min(REVTIME) as REVTIME from " + m_TableName;  
  m_Statement += getWhereStatement() + ";";

  if( CSMC_DBData::select() )
  {
    EventTime = getREVTIME(1);
  }

  return EventTime;
}

double CPD_ACTION::GetLastEventDurationSinceStart(  const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO )
{
  double DurationSinceStart = CSMC_DBData::unspecDouble;

  cleanWhereStatement();

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement = "Select max(DURSINCESTARTOFHEAT) as DURSINCESTARTOFHEAT from " + m_TableName;  
  m_Statement += getWhereStatement() + ";";


  if( CSMC_DBData::select() )
  {
    DurationSinceStart = getDURSINCESTARTOFHEAT(1);
  }

  return DurationSinceStart;
}

CDateTime CPD_ACTION::GetLastEventRevTime( const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO )
{
  CDateTime EventTime = CSMC_DBData::unspecDate;
  cleanWhereStatement();

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement = "Select max(REVTIME) as REVTIME from " + m_TableName;  
  m_Statement += getWhereStatement() + ";";

  if( CSMC_DBData::select() )
  {
    EventTime = getREVTIME(1);
  }

  return EventTime;
}

bool CPD_ACTION::GetLastPowerEventTime(  const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO,double& dbDurationSinceHeatStart )
{
  cleanWhereStatement();

  addWhereClause(CPD_ACTION::HEATID,HEATID);
  addWhereClause(CPD_ACTION::TREATID,TREATID);
  addWhereClause(CPD_ACTION::PLANT,PLANT);
  addWhereClause(CPD_ACTION::ACTIONNO,ACTIONNO);

  m_Statement = "Select * from " + m_TableName + getWhereStatement();  
  m_Statement += " and DURSINCESTARTOFHEAT = ( SELECT max( DURSINCESTARTOFHEAT ) FROM ";
  m_Statement += m_TableName + getWhereStatement() + ");";

  bool bFlag = CSMC_DBData::select();
  if( bFlag )
  {
    dbDurationSinceHeatStart =  getDURSINCESTARTOFHEAT( 1);
  }
  return  bFlag;
}

bool CPD_ACTION::isActionDefined(long ACTIONNO)
{
  bool RetVal = false;
  std::map<long,std::string>::iterator it = m_DefinedActions.find(ACTIONNO);

  if ( it != m_DefinedActions.end() )
  {
    RetVal = true;
  }

  return RetVal;
}

void CPD_ACTION::resetData()
{
  m_Row.HEATID.clear();
  m_Row.TREATID.clear();
  m_Row.PLANT.clear();
  m_Row.ACTIONNO = CSMC_DBData::unspecLong;
  m_Row.ACTIONNAME.clear();
  m_Row.ACTIONUNIT.clear();
  m_Row.ACTIONVALUE.clear();
  m_Row.ACTIONSTATUS = CSMC_DBData::unspecLong;
  m_Row.DURSINCEHEATANNOUNCEMENT = CSMC_DBData::unspecDouble;
  m_Row.DURSINCESTARTOFHEAT = CSMC_DBData::unspecDouble;
  m_Row.O2_MOMENT = CSMC_DBData::unspecDouble;
  m_Row.N2_MOMENT = CSMC_DBData::unspecDouble;
  m_Row.AR_MOMENT = CSMC_DBData::unspecDouble;
  m_Row.ELECEGY = CSMC_DBData::unspecDouble;
}

bool CPD_ACTION::UpdateOrInsertAction(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO, std::string ACTIONUNIT, std::string  ACTIONVALUE, long ACTIONSTATUS, sMetTimeStamp MetTimeStamp, bool UniqueAction, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = true;

  // When action is unique it must be updated otherwise insert action
  if ( UniqueAction && select(HEATID, TREATID, PLANT, ACTIONNO, CSMC_DBData::unspecDate) )
  {
    setREVTIME(CDateTime());

    setO2_MOMENT(MetTimeStamp.O2_Moment);
    setAR_MOMENT(MetTimeStamp.Ar_Moment);
    setN2_MOMENT(MetTimeStamp.N2_Moment);

    setDURSINCEHEATANNOUNCEMENT (MetTimeStamp.DurSinceHeatAnnouncement);
    setDURSINCESTARTOFHEAT      (MetTimeStamp.DurSinceStartOfHeat);
    setELECEGY                  (MetTimeStamp.Elec_Moment);

    RetValue = RetValue && update();
  }
  else
  {
    // the structure m_Row must be set before the 'write' call !!!
    setHEATID(HEATID);
    setTREATID(TREATID);
    setPLANT(PLANT);
    setACTIONNO(ACTIONNO);
    setREVTIME(CDateTime());

    if( isActionDefined(ACTIONNO) )
    {
      setACTIONNAME(getActionDefName(ACTIONNO));
    }

    if ( !ACTIONUNIT.empty() )
      setACTIONUNIT(ACTIONUNIT);

    if ( !ACTIONVALUE.empty() )
      setACTIONVALUE(ACTIONVALUE);

    if ( ACTIONSTATUS != CSMC_DBData::unspecLong )
      setACTIONSTATUS(ACTIONSTATUS);

    setO2_MOMENT(MetTimeStamp.O2_Moment);
    setAR_MOMENT(MetTimeStamp.Ar_Moment);
    setN2_MOMENT(MetTimeStamp.N2_Moment);

    setDURSINCEHEATANNOUNCEMENT (MetTimeStamp.DurSinceHeatAnnouncement);
    setDURSINCESTARTOFHEAT      (MetTimeStamp.DurSinceStartOfHeat);
    setELECEGY                  (MetTimeStamp.Elec_Moment);

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

bool CPD_ACTION::write(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO, bool Commit)
{
  bool retVal;
  CDateTime now;

  // the structure m_Row must be set before the 'write' call !!!
  setHEATID(HEATID);
  setTREATID(TREATID);
  setPLANT(PLANT);
  setACTIONNO(ACTIONNO);
  setREVTIME(now);

  if (m_Row.ACTIONNAME.empty())
    setACTIONNAME(getActionDefName(ACTIONNO));
  else
    setACTIONNAME(m_Row.ACTIONNAME);
  
  if (!m_Row.ACTIONUNIT.empty())
    setACTIONUNIT(m_Row.ACTIONUNIT);
  
  if (!m_Row.ACTIONVALUE.empty())
      setACTIONVALUE(m_Row.ACTIONVALUE);

  if (m_Row.ACTIONSTATUS != CSMC_DBData::unspecLong)
      setACTIONSTATUS(m_Row.ACTIONSTATUS);

  if (m_Row.DURSINCEHEATANNOUNCEMENT != CSMC_DBData::unspecDouble)
    setDURSINCEHEATANNOUNCEMENT(m_Row.DURSINCEHEATANNOUNCEMENT);

  if (m_Row.DURSINCESTARTOFHEAT != CSMC_DBData::unspecDouble)
    setDURSINCESTARTOFHEAT(m_Row.DURSINCESTARTOFHEAT);

  if (m_Row.O2_MOMENT != CSMC_DBData::unspecDouble)
    setO2_MOMENT(m_Row.O2_MOMENT);
  
  if (m_Row.N2_MOMENT != CSMC_DBData::unspecDouble)
    setN2_MOMENT(m_Row.N2_MOMENT);

  if (m_Row.AR_MOMENT != CSMC_DBData::unspecDouble)
    setAR_MOMENT(m_Row.AR_MOMENT);

  if (m_Row.ELECEGY != CSMC_DBData::unspecDouble)
    setELECEGY(m_Row.ELECEGY);

  retVal = insert();

  if (Commit)
  {
    if (retVal)
      commit();
    else
      rollback();
  }
  return retVal;
}

bool CPD_ACTION::write(ActionRow PD_ACTIONROW , bool Commit)
{
  bool retVal;
  CDateTime now;
  setHEATID(PD_ACTIONROW.HEATID);
  setTREATID(PD_ACTIONROW.TREATID);
  setPLANT(PD_ACTIONROW.PLANT);
  setACTIONNO(PD_ACTIONROW.ACTIONNO);
  setREVTIME(now);
  setACTIONNAME(getActionDefName(PD_ACTIONROW.ACTIONNO));
  if(!PD_ACTIONROW.ACTIONUNIT.empty())
    setACTIONUNIT(PD_ACTIONROW.ACTIONUNIT);
  if(!PD_ACTIONROW.ACTIONVALUE.empty())
    setACTIONVALUE(PD_ACTIONROW.ACTIONVALUE);
  if(PD_ACTIONROW.ACTIONSTATUS >0)
    setACTIONSTATUS(PD_ACTIONROW.ACTIONSTATUS);
  if(PD_ACTIONROW.DURSINCEHEATANNOUNCEMENT >0)
    setDURSINCEHEATANNOUNCEMENT(PD_ACTIONROW.DURSINCEHEATANNOUNCEMENT);
  if(PD_ACTIONROW.DURSINCESTARTOFHEAT >0)
    setDURSINCESTARTOFHEAT(PD_ACTIONROW.DURSINCESTARTOFHEAT);
  if(PD_ACTIONROW.O2_MOMENT>0)
    setO2_MOMENT(PD_ACTIONROW.O2_MOMENT);
  if(PD_ACTIONROW.N2_MOMENT >0 )
    setN2_MOMENT(PD_ACTIONROW.N2_MOMENT);
  if(PD_ACTIONROW.AR_MOMENT >0)
    setAR_MOMENT(PD_ACTIONROW.AR_MOMENT);
  if(PD_ACTIONROW.ELECEGY >0)
    setELECEGY(PD_ACTIONROW.ELECEGY);   
  retVal = insert();

  if ( retVal )
  {
    commit();
  }
  else
  {
    rollback();
  }

  return retVal;
}



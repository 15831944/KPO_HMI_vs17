//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CPD_SAMPLE.h"
#include "CHD_SAMPLE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLE_COUNTER("SAMPLE_COUNTER");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::HEATID("HEATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::HM_ID("HM_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::TREATID("TREATID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::PRODORDERID("PRODORDERID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLENO("SAMPLENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::MEASTYPENO("MEASTYPENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::GROUPNO("GROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLETIME("SAMPLETIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::RECTIME("RECTIME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::RECTIMELAB("RECTIMELAB");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLEMODE("SAMPLEMODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLELOC("SAMPLELOC");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::LADLENO("LADLENO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::LADLETYPE("LADLETYPE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::DURSINCEHEATANNOUNCEMENT("DURSINCEHEATANNOUNCEMENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::DURSINCESTARTOFHEAT("DURSINCESTARTOFHEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLEUSABLE("SAMPLEUSABLE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::ORIGIN("ORIGIN");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::USERCODE("USERCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::SAMPLEID_CUST("SAMPLEID_CUST");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CHD_SAMPLE::REVTIME("REVTIME");

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_SAMPLE::CHD_SAMPLE(cCBS_StdConnection* Connection)
:CSMC_DBData("HD_SAMPLE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_SAMPLE::CHD_SAMPLE(cCBS_Connection* Connection)
:CSMC_DBData("HD_SAMPLE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_SAMPLE::CHD_SAMPLE()
:CSMC_DBData("HD_SAMPLE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CHD_SAMPLE::~CHD_SAMPLE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##SAMPLE_COUNTER is the primary key
long CHD_SAMPLE::getSAMPLE_COUNTER(long Row)
{
  return getLong(CHD_SAMPLE::SAMPLE_COUNTER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLE_COUNTER(long value)
{
  setLong(CHD_SAMPLE::SAMPLE_COUNTER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Heat identifier, gives the possibility to select all samples for this heat.
std::string CHD_SAMPLE::getHEATID(long Row)
{
  return getString(CHD_SAMPLE::HEATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setHEATID(const std::string& value)
{
  setString(CHD_SAMPLE::HEATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Hot metal identifier, gives the possibility to select all samples for this hot metal.
std::string CHD_SAMPLE::getHM_ID(long Row)
{
  return getString(CHD_SAMPLE::HM_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setHM_ID(const std::string& value)
{
  setString(CHD_SAMPLE::HM_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Treatment identifier
std::string CHD_SAMPLE::getTREATID(long Row)
{
  return getString(CHD_SAMPLE::TREATID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setTREATID(const std::string& value)
{
  setString(CHD_SAMPLE::TREATID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CHD_SAMPLE::getPLANT(long Row)
{
  return getString(CHD_SAMPLE::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setPLANT(const std::string& value)
{
  setString(CHD_SAMPLE::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant number
long CHD_SAMPLE::getPLANTNO(long Row)
{
  return getLong(CHD_SAMPLE::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setPLANTNO(long value)
{
  setLong(CHD_SAMPLE::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Production oder identification
std::string CHD_SAMPLE::getPRODORDERID(long Row)
{
  return getString(CHD_SAMPLE::PRODORDERID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setPRODORDERID(const std::string& value)
{
  setString(CHD_SAMPLE::PRODORDERID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sample No, Definition see Requirment Book Naming standard specification
long CHD_SAMPLE::getSAMPLENO(long Row)
{
  return getLong(CHD_SAMPLE::SAMPLENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLENO(long value)
{
  setLong(CHD_SAMPLE::SAMPLENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Identifies the type of measurement
long CHD_SAMPLE::getMEASTYPENO(long Row)
{
  return getLong(CHD_SAMPLE::MEASTYPENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setMEASTYPENO(long value)
{
  setLong(CHD_SAMPLE::MEASTYPENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Grouping of measurements makes sense in the following situations:, 1. Two measurements has been taken together, e.g. with a sub lance and special devices. The results arrives the system at different times. Grouping these measurements together gives the possibility to indicate the coherence of these measurements, e.g., for statistical evaluations as introduced at BOF, 2. Assume the situation that two hot metal ladles are assigned to a heat. Then we have an entry for the PRODORDERID in the PD_SAMPLE and if the heat already exists also an entry with the HEATID. In case one ladle was de-assigned from the heat we have to delete the corresponding entries for HEATID and PRODORDERID from the table, but the entries for the other ladle must remain. Using this GROUPNO by entering the HOTMETAL_COUNTER allows the deletion of the data only for the de-assigned ladle.
long CHD_SAMPLE::getGROUPNO(long Row)
{
  return getLong(CHD_SAMPLE::GROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setGROUPNO(long value)
{
  setLong(CHD_SAMPLE::GROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sample taken time
CDateTime CHD_SAMPLE::getSAMPLETIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_SAMPLE::SAMPLETIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLETIME(const CDateTime& value)
{
 setString(CHD_SAMPLE::SAMPLETIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sample taken receive time (telegram received)
CDateTime CHD_SAMPLE::getRECTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_SAMPLE::RECTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setRECTIME(const CDateTime& value)
{
 setString(CHD_SAMPLE::RECTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sample analysis receive time (telegram received)
CDateTime CHD_SAMPLE::getRECTIMELAB(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_SAMPLE::RECTIMELAB, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setRECTIMELAB(const CDateTime& value)
{
 setString(CHD_SAMPLE::RECTIMELAB, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Manually, automatic
long CHD_SAMPLE::getSAMPLEMODE(long Row)
{
  return getLong(CHD_SAMPLE::SAMPLEMODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLEMODE(long value)
{
  setLong(CHD_SAMPLE::SAMPLEMODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Sample location
std::string CHD_SAMPLE::getSAMPLELOC(long Row)
{
  return getString(CHD_SAMPLE::SAMPLELOC, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLELOC(const std::string& value)
{
  setString(CHD_SAMPLE::SAMPLELOC, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique ladle number
long CHD_SAMPLE::getLADLENO(long Row)
{
  return getLong(CHD_SAMPLE::LADLENO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setLADLENO(long value)
{
  setLong(CHD_SAMPLE::LADLENO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##e.g. Hot Metal -> H, Teeming -> T
std::string CHD_SAMPLE::getLADLETYPE(long Row)
{
  return getString(CHD_SAMPLE::LADLETYPE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setLADLETYPE(const std::string& value)
{
  setString(CHD_SAMPLE::LADLETYPE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since heat announcement
double CHD_SAMPLE::getDURSINCEHEATANNOUNCEMENT(long Row)
{
  return getDouble(CHD_SAMPLE::DURSINCEHEATANNOUNCEMENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setDURSINCEHEATANNOUNCEMENT(double value)
{
  setDouble(CHD_SAMPLE::DURSINCEHEATANNOUNCEMENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Duration since start of heat
double CHD_SAMPLE::getDURSINCESTARTOFHEAT(long Row)
{
  return getDouble(CHD_SAMPLE::DURSINCESTARTOFHEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setDURSINCESTARTOFHEAT(double value)
{
  setDouble(CHD_SAMPLE::DURSINCESTARTOFHEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##0: not usable, 1: usable with sample taken detected, 2: usable without sample taken detected
long CHD_SAMPLE::getSAMPLEUSABLE(long Row)
{
  return getLong(CHD_SAMPLE::SAMPLEUSABLE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLEUSABLE(long value)
{
  setLong(CHD_SAMPLE::SAMPLEUSABLE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Measured -> 1, Calculated -> 2, Manual entered -> 3
long CHD_SAMPLE::getORIGIN(long Row)
{
  return getLong(CHD_SAMPLE::ORIGIN, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setORIGIN(long value)
{
  setLong(CHD_SAMPLE::ORIGIN, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##User who entered data
std::string CHD_SAMPLE::getUSERCODE(long Row)
{
  return getString(CHD_SAMPLE::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setUSERCODE(const std::string& value)
{
  setString(CHD_SAMPLE::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Customer specific representation of the sample. It is only used for display and reporting and will not used for interpretation of details.
std::string CHD_SAMPLE::getSAMPLEID_CUST(long Row)
{
  return getString(CHD_SAMPLE::SAMPLEID_CUST, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setSAMPLEID_CUST(const std::string& value)
{
  setString(CHD_SAMPLE::SAMPLEID_CUST, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Date and time of last revision
CDateTime CHD_SAMPLE::getREVTIME(long Row)
{
  CDateTime D;
  D.fromDBString(getString(CHD_SAMPLE::REVTIME, Row));
  return D;
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CHD_SAMPLE::setREVTIME(const CDateTime& value)
{
 setString(CHD_SAMPLE::REVTIME, value.toDBString());
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CHD_SAMPLE::select(long SAMPLE_COUNTER)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CHD_SAMPLE::SAMPLE_COUNTER,SAMPLE_COUNTER);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CHD_SAMPLE::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long SAMPLE_COUNTER, bool Commit, cCBS_ODBC_DBError &Error)
{
	bool result = !exists(SAMPLE_COUNTER);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows(SAMPLE_COUNTER, Commit, Error);
	}

  // preparing setting for source table
  CPD_SAMPLE PD_SAMPLE(m_pCBS_StdConnection);
  PD_SAMPLE.addWhereClause(CPD_SAMPLE::SAMPLE_COUNTER,SAMPLE_COUNTER);

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT(PLANT);
  setPLANTNO(PLANTNO);

  result = result && copyByInsert(&PD_SAMPLE);

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

bool CHD_SAMPLE::copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, std::vector<long> &SampleCounterList, bool Commit, cCBS_ODBC_DBError &Error)
{
  if(SampleCounterList.size() < 1)
    return true;

	bool result = !exists(SampleCounterList);
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows(SampleCounterList, Commit, Error);
	}

  // preparing setting for source table
  CPD_SAMPLE PD_SAMPLE(m_pCBS_StdConnection);
  PD_SAMPLE.addWhereClause(CPD_SAMPLE::SAMPLE_COUNTER,SampleCounterList, "IN");

  // preparing setting for aim table
  setHEATID (HEATID);
  setTREATID(TREATID);
  setPLANT(PLANT);
  setPLANTNO(PLANTNO);

  result = result && copyByInsert(&PD_SAMPLE);

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

std::string CHD_SAMPLE::ArrayToString(std::vector<long> &pArray)
{
  std::stringstream mStream;	
	for (unsigned int i = 0; i < pArray.size(); i++)
		mStream << pArray[i] << ",";

	string result = mStream.str(); 
	if (!result.empty())
		result = result.substr(0, result.length()-1); //delete the last coma ','
	return result;
}

bool CHD_SAMPLE::deleteByRecTime(CDateTime& OlderThan)
{
  bool RetValue = false;

  cleanWhereStatement();

  if (OlderThan != CSMC_DBData::unspecDate)
  {
    addWhereClause(CHD_SAMPLE::RECTIME, OlderThan,"<=");

    m_Statement = "Select * from " + m_TableName;
    m_Statement += getWhereStatement() + ";";

    if (CSMC_DBData::select())
    {
      long NoRows = getLastRow();
      log("INFO: Try to delete entries in HD_SAMPLE older than " + OlderThan.toDBString(),3);

      m_Statement = "Delete " + m_TableName;
      m_Statement += getWhereStatement() + ";";

      std::stringstream Message;
      if (CSMC_DBData::deleteRows())
      {
        Message << "INFO: Deleted '" << NoRows << "' rows";
        log(Message.str(),3);
        RetValue = true;
      }
      else
      {
        Message << "ERROR: Delete rows in HD_SAMPLE older than " << OlderThan.toDBString();
        log(Message.str(),1);
      }
    }
    else
      log("INFO: Clean up HD_SAMPLE not necessary. No rows older than " + OlderThan.toDBString(),3);
  }
  else
    log("ERROR: CHD_SAMPLE::deleteByRecTime not possible: unspecified date!",1);

  return RetValue;
}

bool CHD_SAMPLE::deleteRows(long SAMPLE_COUNTER, bool Commit, cCBS_ODBC_DBError &Error)
{
	cleanWhereStatement();

	addWhereClause(CHD_SAMPLE::SAMPLE_COUNTER,SAMPLE_COUNTER);

  bool result = CSMC_DBData::deleteRows();

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

bool CHD_SAMPLE::deleteRows(std::vector<long> &SampleCounterList, bool Commit, cCBS_ODBC_DBError &Error)
{
	cleanWhereStatement();

	addWhereClause(CHD_SAMPLE::SAMPLE_COUNTER, SampleCounterList, "IN");

  bool result = CSMC_DBData::deleteRows();

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

bool CHD_SAMPLE::exists(long SAMPLE_COUNTER)
{
	cleanWhereStatement();

	m_Statement = "Select SAMPLE_COUNTER from " + m_TableName;

	addWhereClause(CHD_SAMPLE::SAMPLE_COUNTER,SAMPLE_COUNTER);
   
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

bool CHD_SAMPLE::exists(std::vector<long> &SampleCounterList)
{
  if(SampleCounterList.size() < 1)
    return false;

	cleanWhereStatement();

	m_Statement = "Select SAMPLE_COUNTER from " + m_TableName;

  addWhereClause(CHD_SAMPLE::SAMPLE_COUNTER,SampleCounterList,"IN");
   
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

bool CHD_SAMPLE::OnTempMeasurement(const string& pHMId, const string& pTreatId, const string& pPlant, long pPlantNo, long pSampleCount, bool pCommit, cCBS_ODBC_DBError &pError)
{
	bool result = !exists(pSampleCount);
	std::stringstream sql;
	//some data found -> delete them
	if (!result)
	{
		result = deleteRows(pSampleCount, pCommit, pError);
	}

	sql << "insert into HD_SAMPLE"
		<< "  (SAMPLE_COUNTER, PLANT, PLANTNO, HM_ID, TREATID, PRODORDERID, LADLENO,"
		<< "  LADLETYPE, SAMPLENO, MEASTYPENO, SAMPLETIME, RECTIME, RECTIMELAB,"
		<< "  SAMPLEMODE, SAMPLELOC, DURSINCEHEATANNOUNCEMENT, DURSINCESTARTOFHEAT,"
		<< "  SAMPLEUSABLE, ORIGIN, USERCODE,SAMPLEID_CUST,REVTIME)"
		<< " (select SAMPLE_COUNTER, '" << pPlant << "', " << pPlantNo << ","
		<< "  '" << pHMId << "', '" << pTreatId << "', PRODORDERID, LADLENO,"
		<< "  LADLETYPE, SAMPLENO, MEASTYPENO, SAMPLETIME, RECTIME, RECTIMELAB,"
		<< "  SAMPLEMODE, SAMPLELOC, DURSINCEHEATANNOUNCEMENT, DURSINCESTARTOFHEAT,"
		<< "  SAMPLEUSABLE, ORIGIN, USERCODE,SAMPLEID_CUST,REVTIME"
		<< " from PD_SAMPLE"
		<< " where SAMPLE_COUNTER = " << pSampleCount << ")";

	result = result && executeSQL(sql.str());
	if (!result)
		pError = getLastError();

	if(pCommit)
	{
		if (result)
			this->commit();
		else
			rollback();
	}

	return result;
}


//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "cCBS_StdEventLogFrameController.h"
#include "CSMC_EventLogFrameController.h"
#include "CGC_PLANTGROUP.h"
#include "CGT_MAT_PURP.h"
#include "CGT_PURP.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_PURP::UNITGROUPNO("UNITGROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_PURP::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT_PURP::PURP_CODE("PURP_CODE");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_PURP::CGT_MAT_PURP(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_MAT_PURP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_PURP::CGT_MAT_PURP(cCBS_Connection* Connection)
:CSMC_DBData("GT_MAT_PURP",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_PURP::CGT_MAT_PURP()
:CSMC_DBData("GT_MAT_PURP")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT_PURP::~CGT_MAT_PURP()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unit group number, see GC_PLANT_GROUP
long CGT_MAT_PURP::getUNITGROUPNO(long Row)
{
  return getLong(CGT_MAT_PURP::UNITGROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_PURP::setUNITGROUPNO(long value)
{
  setLong(CGT_MAT_PURP::UNITGROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code
std::string CGT_MAT_PURP::getMAT_CODE(long Row)
{
  return getString(CGT_MAT_PURP::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_PURP::setMAT_CODE(const std::string& value)
{
  setString(CGT_MAT_PURP::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Purpose code
std::string CGT_MAT_PURP::getPURP_CODE(long Row)
{
  return getString(CGT_MAT_PURP::PURP_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT_PURP::setPURP_CODE(const std::string& value)
{
  setString(CGT_MAT_PURP::PURP_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_MAT_PURP::select(long UNITGROUPNO, const std::string& MAT_CODE, const std::string& PURP_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_MAT_PURP::UNITGROUPNO,UNITGROUPNO);
  addWhereClause(CGT_MAT_PURP::MAT_CODE,MAT_CODE);
  addWhereClause(CGT_MAT_PURP::PURP_CODE,PURP_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGT_MAT_PURP::selectAllMaterialsBySpecPurpose(const std::string& PURP_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select DISTINCT(MAT_CODE) from " + m_TableName;

  addWhereClause(CGT_MAT_PURP::PURP_CODE,PURP_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CGT_MAT_PURP::selectByPlant(const std::string& PLANT, long PLANTNO, const std::string& MAT_CODE, const std::string& PURP_CODE)
{
  bool RetValue = false;

  CGT_PURP GT_PURP(m_pCBS_StdConnection);

  // find unitgroup numbers
  std::vector<long> UnitGroupList = getUnitGroupList(PLANT,PLANTNO);
  std::vector<long>::iterator it;

  for (it = UnitGroupList.begin(); it != UnitGroupList.end(); ++it)
  {
    // check, if purpose is defined for current unitgroupno
    if (GT_PURP.select(*it, PURP_CODE))
    {
      // check, if there are any materials defined
      if (select(*it, MAT_CODE, PURP_CODE))
      {
        RetValue = true;
        break;
      }
      // if purpose is empty, write an event log
      else
      {
        CSMC_EventLogFrame *pEventLog = CSMC_EventLogFrameController::getInstance()->getpEventLog();
        sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
        pEventLog->EL_EmptyPurpose(sMessage, PURP_CODE.c_str(), *it);      
      }
    }
  }


  return RetValue;
}

bool CGT_MAT_PURP::deleteRow(const std::string& PLANT, long PLANTNO, const std::string& Mat_Code, const std::string& Purp_Code)
{
  bool RetValue = false;

  std::vector<long> UnitGroupList = getUnitGroupList(PLANT, PLANTNO);
  std::vector<long>::iterator it = UnitGroupList.begin();

  if ( it != UnitGroupList.end() )
  {
    long UNITGROUPNO = (*it);

    RetValue = deleteRow(UNITGROUPNO, Mat_Code, Purp_Code);
  }

  return RetValue;
}

bool CGT_MAT_PURP::deleteRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code)
{
  bool RetValue = false;

  try
  {
    cleanWhereStatement();

    if (!Mat_Code.empty())  addWhereClause(CGT_MAT_PURP::MAT_CODE,Mat_Code);
    if (!Purp_Code.empty()) addWhereClause(CGT_MAT_PURP::PURP_CODE,Purp_Code);
    
    if ( UNITGROUPNO != CSMC_DBData::unspecLong )
    {
      addWhereClause(CGT_MAT_PURP::UNITGROUPNO,UNITGROUPNO);
    }

    RetValue = CSMC_DBData::deleteRows();
  }
  catch(...)
  {
    rollback(); //something wrong, rollback transaction.
  }

  return RetValue;
}

bool CGT_MAT_PURP::deleteRows(long UNITGROUPNO, std::vector<std::string> Exclude_Mat_Codes, const std::string& Purp_Code)
{
  bool RetValue = false;

  try
  {
    cleanWhereStatement();

    if (!Exclude_Mat_Codes.empty() && !Purp_Code.empty() && UNITGROUPNO != CSMC_DBData::unspecLong )
    {
      addWhereClause(CGT_MAT_PURP::MAT_CODE,Exclude_Mat_Codes,"NOT IN");

      addWhereClause(CGT_MAT_PURP::PURP_CODE,Purp_Code);

      addWhereClause(CGT_MAT_PURP::UNITGROUPNO,UNITGROUPNO);

      RetValue = CSMC_DBData::deleteRows();
    }   
  }
  catch(...)
  {
    rollback(); //something wrong, rollback transaction.
  }

  return RetValue;
}

std::string CGT_MAT_PURP::getRelatedMatCode(long UNITGROUPNO, const std::string& PURP_CODE)
{
  cleanWhereStatement();
  std::string MatCode;

  m_Statement = "select * from " + m_TableName;

  addWhereClause(CGT_MAT_PURP::PURP_CODE, PURP_CODE);

  if ( UNITGROUPNO != CSMC_DBData::unspecLong )
  {
    addWhereClause(CGT_MAT_PURP::UNITGROUPNO,UNITGROUPNO);
  }

  m_Statement += getWhereStatement();
  m_Statement += " ; ";
  CSMC_DBData::select();

  if (CSMC_DBData::getLastRow() == 1)
    MatCode = getMAT_CODE(1);
  else
  {
    if (CSMC_DBData::getLastRow() > 1)
      log("ERROR: purpose code and unit no are not unique!",1);

    MatCode = CSMC_DBData::unspecString;
  }
  return MatCode;
}

std::vector<std::string> CGT_MAT_PURP::getRelatedMatCodes(const std::string& PLANT, long PLANTNO, const std::string& PURP_CODE)
{
  std::vector<std::string> MatCodeList;

  if ( selectByPlant(PLANT, PLANTNO, CSMC_DBData::unspecString, PURP_CODE) )
  {
    for ( long i = 1 ; i <= getLastRow(); ++i )
    {
      MatCodeList.push_back(getMAT_CODE(i));
    }
  }

  return MatCodeList;
}

std::vector<long> CGT_MAT_PURP::getUnitGroupList(const std::string& Plant, long PlantNo)
{
  CGC_PLANTGROUP GC_PLANTGROUP(m_pCBS_StdConnection);

  return GC_PLANTGROUP.getUnitGroupList(Plant,PlantNo);
}

// to be backward compatible
bool CGT_MAT_PURP::insertRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code)
{
  bool Commit = false;
  cCBS_ODBC_DBError Error;

  return insertRow(UNITGROUPNO, Mat_Code, Purp_Code, Commit, Error);
}

bool CGT_MAT_PURP::insertRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = false;

  if ( UNITGROUPNO != CSMC_DBData::unspecLong )
  {
    setMAT_CODE(Mat_Code);
    setPURP_CODE(Purp_Code);
    setUNITGROUPNO(UNITGROUPNO);

    RetValue = insert();

	  if (!RetValue)
		  Error = getLastError();

	  if (Commit)
	  {
		  if (RetValue)
			  commit();
		  else
			  rollback();
	  }
  }

  return RetValue;
}

bool CGT_MAT_PURP::insertRow(const std::string& PLANT, long PLANTNO, const std::string& Mat_Code, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = false;

  CGC_PLANTGROUP GC_PLANTGROUP(m_pCBS_StdConnection);

  // returns " ORDER BY UNITGROUPNO DESC ;"
  if ( GC_PLANTGROUP.selectOrdered(CSMC_DBData::unspecLong, PLANT, PLANTNO) )
  {
    long UNITGROUPNO = GC_PLANTGROUP.getUNITGROUPNO(1);

    RetValue = insertRow(UNITGROUPNO, Mat_Code, Purp_Code, Commit, Error);
  }

  return RetValue;
}

bool CGT_MAT_PURP::insertRows(const std::string& PLANT, long PLANTNO, std::vector<std::string> Mat_Codes, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = false;

  if ( Mat_Codes.size() == 0 )
  {
    // empty Mat_Codes container may not force return value == false
    RetValue = true;

    cCBS_StdEventLogFrame *pEventLog = cCBS_StdEventLogFrameController::getInstance()->getpEventLog();
    sEventLogMessage sMessage = cCBS_StdEventLog::initMessage(__FILE__,__LINE__);
    pEventLog->EL_DBWriteInfo(sMessage,"", m_TableName.c_str(), "no material data received" );
  }
  else
  {
    CGC_PLANTGROUP GC_PLANTGROUP(m_pCBS_StdConnection);

    // returns " ORDER BY UNITGROUPNO DESC ;"
    if ( GC_PLANTGROUP.selectOrdered(CSMC_DBData::unspecLong, PLANT, PLANTNO) )
    {
      long UNITGROUPNO = GC_PLANTGROUP.getUNITGROUPNO(1);

      std::vector<std::string>::iterator it;

      for ( it = Mat_Codes.begin(); it != Mat_Codes.end(); ++it)
      {
        std::string Mat_Code = (*it);

        setMAT_CODE(Mat_Code);
        setPURP_CODE(Purp_Code);
        setUNITGROUPNO(UNITGROUPNO);

        RetValue = insert();

        if ( !RetValue)
        {
          break;
        }
      }
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
  }

  return RetValue;
}


bool CGT_MAT_PURP::insertOrReplace(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code)
{
  bool RetValue = false;

  if ( select ( UNITGROUPNO, Mat_Code, Purp_Code ) )
  {
    deleteRow(UNITGROUPNO, Mat_Code, Purp_Code);
  }

  RetValue = insertRow(UNITGROUPNO, Mat_Code, Purp_Code);

  return RetValue;
}

bool CGT_MAT_PURP::deleteOnExist(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code)
{
  bool RetValue = false;

  if ( select ( UNITGROUPNO, Mat_Code, Purp_Code ) )
  {
    RetValue = deleteRow(UNITGROUPNO, Mat_Code, Purp_Code);
  }

  return RetValue;
}

//SRKO
bool CGT_MAT_PURP::mergePurposeCodes(const std::string& PLANT, long PLANTNO, const std::string& From_Purp_Code_1, const std::string& From_Purp_Code_2, const std::string& To_Purp_Code)
{
	bool RetValue = false;
	bool Commit = false;
  cCBS_ODBC_DBError Error;
	std::string Mat_Code=CSMC_DBData::unspecString;
	
	RetValue = deleteRow(PLANT, PLANTNO, Mat_Code, To_Purp_Code); 

	std::vector<std::string> MatCodeList;

	MatCodeList=getRelatedMatCodes(PLANT, PLANTNO, From_Purp_Code_1);
	RetValue=RetValue && insertRows(PLANT, PLANTNO, MatCodeList, To_Purp_Code, Commit, Error);

	MatCodeList=getRelatedMatCodes(PLANT, PLANTNO, From_Purp_Code_2);
	RetValue=RetValue && insertRows(PLANT, PLANTNO, MatCodeList, To_Purp_Code, Commit, Error);

	return RetValue;
}
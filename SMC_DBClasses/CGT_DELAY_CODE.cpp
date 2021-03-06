//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_DELAY_CODE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::DELAY_CODE("DELAY_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::GROUPNO("GROUPNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::DELAYDESCR("DELAYDESCR");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::USERCODE("USERCODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_DELAY_CODE::DEFAULT_DURATION("DEFAULT_DURATION");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_DELAY_CODE::CGT_DELAY_CODE(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_DELAY_CODE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_DELAY_CODE::CGT_DELAY_CODE(cCBS_Connection* Connection)
:CSMC_DBData("GT_DELAY_CODE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_DELAY_CODE::CGT_DELAY_CODE()
:CSMC_DBData("GT_DELAY_CODE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_DELAY_CODE::~CGT_DELAY_CODE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGT_DELAY_CODE::getPLANT(long Row)
{
  return getString(CGT_DELAY_CODE::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setPLANT(const std::string& value)
{
  setString(CGT_DELAY_CODE::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Delay code
std::string CGT_DELAY_CODE::getDELAY_CODE(long Row)
{
  return getString(CGT_DELAY_CODE::DELAY_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setDELAY_CODE(const std::string& value)
{
  setString(CGT_DELAY_CODE::DELAY_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
long CGT_DELAY_CODE::getGROUPNO(long Row)
{
  return getLong(CGT_DELAY_CODE::GROUPNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setGROUPNO(long value)
{
  setLong(CGT_DELAY_CODE::GROUPNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Delay Description
std::string CGT_DELAY_CODE::getDELAYDESCR(long Row)
{
  return getString(CGT_DELAY_CODE::DELAYDESCR, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setDELAYDESCR(const std::string& value)
{
  setString(CGT_DELAY_CODE::DELAYDESCR, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##User who entered the delay
std::string CGT_DELAY_CODE::getUSERCODE(long Row)
{
  return getString(CGT_DELAY_CODE::USERCODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setUSERCODE(const std::string& value)
{
  setString(CGT_DELAY_CODE::USERCODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Delay default duration
long CGT_DELAY_CODE::getDEFAULT_DURATION(long Row)
{
  return getLong(CGT_DELAY_CODE::DEFAULT_DURATION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_DELAY_CODE::setDEFAULT_DURATION(long value)
{
  setLong(CGT_DELAY_CODE::DEFAULT_DURATION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_DELAY_CODE::select(const std::string& PLANT, const std::string& DELAY_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_DELAY_CODE::PLANT,PLANT);
  addWhereClause(CGT_DELAY_CODE::DELAY_CODE,DELAY_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGT_DELAY_CODE::deleteRow(const std::string& PLANT, const std::string& DELAY_CODE)
{

  cleanWhereStatement();
  
  addWhereClause(CGT_DELAY_CODE::PLANT,PLANT);
  addWhereClause(CGT_DELAY_CODE::DELAY_CODE,DELAY_CODE);

  return CSMC_DBData::deleteRows();
}

bool CGT_DELAY_CODE::updateInsertDelay(const std::string& PLANT, const std::string& DELAY_CODE, long GROUPNO, const std::string& DELAYDESCR, const std::string& DELAYDESCR_CUST, const std::string& USERCODE, long DEFAULT_DURATION, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = false;

  setGROUPNO(GROUPNO);

  setDELAYDESCR(DELAYDESCR);

  setUSERCODE(USERCODE);

  setDEFAULT_DURATION(DEFAULT_DURATION);

  if ( select(PLANT, DELAY_CODE) )
  {
    RetValue = update();
  }
  else
  {
    setPLANT(PLANT);
    setDELAY_CODE(DELAY_CODE);

    RetValue = insert();
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



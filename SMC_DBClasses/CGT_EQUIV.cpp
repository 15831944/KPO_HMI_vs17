//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_EQUIV_ENTRY.h"
#include "CIntfData.h"
#include "CGT_EQUIV.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_EQUIV::EQ_NAME("EQ_NAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_EQUIV::DESCRIPTION("DESCRIPTION");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_EQUIV::OFFSET("OFFSET");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_EQUIV::CGT_EQUIV(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_EQUIV",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_EQUIV::CGT_EQUIV(cCBS_Connection* Connection)
:CSMC_DBData("GT_EQUIV",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_EQUIV::CGT_EQUIV()
:CSMC_DBData("GT_EQUIV")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_EQUIV::~CGT_EQUIV()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Equivalence name
std::string CGT_EQUIV::getEQ_NAME(long Row)
{
  return getString(CGT_EQUIV::EQ_NAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_EQUIV::setEQ_NAME(const std::string& value)
{
  setString(CGT_EQUIV::EQ_NAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGT_EQUIV::getDESCRIPTION(long Row)
{
  return getString(CGT_EQUIV::DESCRIPTION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_EQUIV::setDESCRIPTION(const std::string& value)
{
  setString(CGT_EQUIV::DESCRIPTION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Offset in formula
double CGT_EQUIV::getOFFSET(long Row)
{
  return getDouble(CGT_EQUIV::OFFSET, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_EQUIV::setOFFSET(double value)
{
  setDouble(CGT_EQUIV::OFFSET, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_EQUIV::select(const std::string& EQ_NAME)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_EQUIV::EQ_NAME,EQ_NAME);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

void CGT_EQUIV::doOnConstruct()
{
  if (m_pCBS_StdConnection)
  {
    m_pGT_EQUIV_ENTRY          = new CGT_EQUIV_ENTRY(m_pCBS_StdConnection);
  }
}

void CGT_EQUIV::doOnDestruct()
{
  if (m_pGT_EQUIV_ENTRY)                { delete m_pGT_EQUIV_ENTRY; } 
}

std::map<std::string,double> CGT_EQUIV::getDenominator(const std::string& EQ_NAME)
{
  std::map<std::string,double> EquivList;

  if ( m_pGT_EQUIV_ENTRY && m_pGT_EQUIV_ENTRY->select(EQ_NAME,2,CSMC_DBData::unspecString) )
  {
    for( long i = 1 ; i <= m_pGT_EQUIV_ENTRY->getLastRow(); ++i )
    {
      EquivList.insert( std::pair<std::string,double> (m_pGT_EQUIV_ENTRY->getENAME(i), m_pGT_EQUIV_ENTRY->getFACTOR(i) ));
    }
  }

  return EquivList;
}

double CGT_EQUIV::getEquivValue(const std::string& EQ_NAME, seqAnalysis SeqAnalysis)
{
  double RetValue   = CSMC_DBData::unspecDouble;
  bool doCalculate  = true;

  // for better handling fill internal map here to use "find" method
  std::map<std::string,double> AnalysisList;
  std::map<std::string,double>::iterator itAnalysisList;

  for( long i = 0 ; i < CIntfData::getLength(SeqAnalysis); ++i )
  { 
    sAnalysis Analysis;
    CIntfData::getAt(Analysis,SeqAnalysis,i);
    AnalysisList.insert(std::pair<std::string,double>(std::string(Analysis.Element) , Analysis.Concentration ) );
  }

  if ( select ( EQ_NAME ) )
  {
    double Numerator    = CSMC_DBData::unspecDouble;
    double Denominator  = CSMC_DBData::unspecDouble;

    // take offset
    double Offset       = getOFFSET(1);
    if ( Offset == CSMC_DBData::unspecDouble )
    {
      Offset = 0.0;
    }

    // calculating Numerator value
    std::map<std::string,double> NumeratorList = getNumerator(EQ_NAME);
    std::map<std::string,double>::iterator itNumerator;
    for( itNumerator = NumeratorList.begin(); itNumerator != NumeratorList.end(); ++itNumerator )
    {
      std::string ENAME = itNumerator->first;
      double FACTOR     = itNumerator->second;

      // use map to detect ENAME from equivalence in Analysis
      itAnalysisList    = AnalysisList.find(ENAME);
      if ( itAnalysisList != AnalysisList.end() )
      {
        Numerator += itAnalysisList->second * FACTOR;
      }
      else
      {
        doCalculate    = false;
        break;
      }
    }

    // calculating Denominator value
    std::map<std::string,double> DenominatorList = getDenominator(EQ_NAME);
    std::map<std::string,double>::iterator itDenominator;
    for( itDenominator = DenominatorList.begin(); itDenominator != DenominatorList.end(); ++itDenominator )
    {
      std::string ENAME = itDenominator->first;
      double FACTOR     = itDenominator->second;

      // use map to detect ENAME from equivalence in Analysis
      itAnalysisList    = AnalysisList.find(ENAME);
      if ( itAnalysisList != AnalysisList.end() )
      {
        Denominator += itAnalysisList->second * FACTOR;
      }
      else
      {
        doCalculate    = false;
        break;
      }
    }

    // calculate, prevent division by zero !
    // equivalences may have no Denominator !
    if ( doCalculate )
    {
      if ( Numerator == CSMC_DBData::unspecDouble )
      {
        Numerator = 1;
      }

      if ( Denominator == 0. || Denominator == CSMC_DBData::unspecDouble )
      {
        Denominator = 1;
      }

      RetValue = Offset + Numerator / Denominator ;

    }
  }

  return RetValue;
}

std::map<std::string,double> CGT_EQUIV::getNumerator(const std::string& EQ_NAME)
{
  std::map<std::string,double> EquivList;

  if ( m_pGT_EQUIV_ENTRY && m_pGT_EQUIV_ENTRY->select(EQ_NAME,1,CSMC_DBData::unspecString) )
  {
    for( long i = 1 ; i <= m_pGT_EQUIV_ENTRY->getLastRow(); ++i )
    {
      EquivList.insert( std::pair<std::string,double> (m_pGT_EQUIV_ENTRY->getENAME(i), m_pGT_EQUIV_ENTRY->getFACTOR(i) ));
    }
  }

  return EquivList;
}


std::set<std::string> CGT_EQUIV::getEQUIVList()
{
  std::set<std::string> EquivList;

  if ( select(CSMC_DBData::unspecString) )
  {
    for( long i = 1 ; i <= getLastRow(); ++i )
    {
      EquivList.insert( getEQ_NAME(i));
    }
  }

  return EquivList;
}

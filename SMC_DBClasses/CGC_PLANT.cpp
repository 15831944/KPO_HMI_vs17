//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_PLANT.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANT("PLANT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANTNO("PLANTNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::ROUTECODEID("ROUTECODEID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANTID_L2("PLANTID_L2");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANTID_L1("PLANTID_L1");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANTID_L3("PLANTID_L3");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::PLANTID_CCS("PLANTID_CCS");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_PLANT::DISPLAY_ORDER("DISPLAY_ORDER");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANT::CGC_PLANT(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_PLANT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANT::CGC_PLANT(cCBS_Connection* Connection)
:CSMC_DBData("GC_PLANT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANT::CGC_PLANT()
:CSMC_DBData("GC_PLANT")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_PLANT::~CGC_PLANT()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier
std::string CGC_PLANT::getPLANT(long Row)
{
  return getString(CGC_PLANT::PLANT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANT(const std::string& value)
{
  setString(CGC_PLANT::PLANT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant number
long CGC_PLANT::getPLANTNO(long Row)
{
  return getLong(CGC_PLANT::PLANTNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANTNO(long value)
{
  setLong(CGC_PLANT::PLANTNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
std::string CGC_PLANT::getROUTECODEID(long Row)
{
  return getString(CGC_PLANT::ROUTECODEID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setROUTECODEID(const std::string& value)
{
  setString(CGC_PLANT::ROUTECODEID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier EXT L2
std::string CGC_PLANT::getPLANTID_L2(long Row)
{
  return getString(CGC_PLANT::PLANTID_L2, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANTID_L2(const std::string& value)
{
  setString(CGC_PLANT::PLANTID_L2, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier L1
long CGC_PLANT::getPLANTID_L1(long Row)
{
  return getLong(CGC_PLANT::PLANTID_L1, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANTID_L1(long value)
{
  setLong(CGC_PLANT::PLANTID_L1, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier L3
std::string CGC_PLANT::getPLANTID_L3(long Row)
{
  return getString(CGC_PLANT::PLANTID_L3, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANTID_L3(const std::string& value)
{
  setString(CGC_PLANT::PLANTID_L3, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Plant identifier CCS
std::string CGC_PLANT::getPLANTID_CCS(long Row)
{
  return getString(CGC_PLANT::PLANTID_CCS, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setPLANTID_CCS(const std::string& value)
{
  setString(CGC_PLANT::PLANTID_CCS, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Display order for HMI
long CGC_PLANT::getDISPLAY_ORDER(long Row)
{
  return getLong(CGC_PLANT::DISPLAY_ORDER, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_PLANT::setDISPLAY_ORDER(long value)
{
  setLong(CGC_PLANT::DISPLAY_ORDER, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_PLANT::select(const std::string& PLANT, long PLANTNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_PLANT::PLANT,PLANT);
  addWhereClause(CGC_PLANT::PLANTNO,PLANTNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



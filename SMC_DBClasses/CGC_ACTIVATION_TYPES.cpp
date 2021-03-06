//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGC_ACTIVATION_TYPES.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_ACTIVATION_TYPES::ACTIVATIONNO("ACTIVATIONNO");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_ACTIVATION_TYPES::OBJECT_PARENT_NAME("OBJECT_PARENT_NAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_ACTIVATION_TYPES::OBJECT_CHILD_NAME("OBJECT_CHILD_NAME");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_ACTIVATION_TYPES::ENABLE_MODE("ENABLE_MODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGC_ACTIVATION_TYPES::ACTIVATIONDESC("ACTIVATIONDESC");

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_ACTIVATION_TYPES::CGC_ACTIVATION_TYPES(cCBS_StdConnection* Connection)
:CSMC_DBData("GC_ACTIVATION_TYPES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_ACTIVATION_TYPES::CGC_ACTIVATION_TYPES(cCBS_Connection* Connection)
:CSMC_DBData("GC_ACTIVATION_TYPES",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_ACTIVATION_TYPES::CGC_ACTIVATION_TYPES()
:CSMC_DBData("GC_ACTIVATION_TYPES")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGC_ACTIVATION_TYPES::~CGC_ACTIVATION_TYPES()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Unique activation number
long CGC_ACTIVATION_TYPES::getACTIVATIONNO(long Row)
{
  return getLong(CGC_ACTIVATION_TYPES::ACTIVATIONNO, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_ACTIVATION_TYPES::setACTIVATIONNO(long value)
{
  setLong(CGC_ACTIVATION_TYPES::ACTIVATIONNO, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Name of HMI-item: Dialog, Tab, pop-up name to which this roles are to be applied to
std::string CGC_ACTIVATION_TYPES::getOBJECT_PARENT_NAME(long Row)
{
  return getString(CGC_ACTIVATION_TYPES::OBJECT_PARENT_NAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_ACTIVATION_TYPES::setOBJECT_PARENT_NAME(const std::string& value)
{
  setString(CGC_ACTIVATION_TYPES::OBJECT_PARENT_NAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Item of defined object: e.g. OBJECT_NAME = BOFProduction, OBJECT_CHILD_NAME: HeatAnnouncement or NewHeat
std::string CGC_ACTIVATION_TYPES::getOBJECT_CHILD_NAME(long Row)
{
  return getString(CGC_ACTIVATION_TYPES::OBJECT_CHILD_NAME, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_ACTIVATION_TYPES::setOBJECT_CHILD_NAME(const std::string& value)
{
  setString(CGC_ACTIVATION_TYPES::OBJECT_CHILD_NAME, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##0 - "disable" for defined Heat Status No, 1- "enable" for defined Heat Status No, e.g. button
long CGC_ACTIVATION_TYPES::getENABLE_MODE(long Row)
{
  return getLong(CGC_ACTIVATION_TYPES::ENABLE_MODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_ACTIVATION_TYPES::setENABLE_MODE(long value)
{
  setLong(CGC_ACTIVATION_TYPES::ENABLE_MODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description of evaluated action, which has to be implemented based on Heat Status
std::string CGC_ACTIVATION_TYPES::getACTIVATIONDESC(long Row)
{
  return getString(CGC_ACTIVATION_TYPES::ACTIVATIONDESC, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGC_ACTIVATION_TYPES::setACTIVATIONDESC(const std::string& value)
{
  setString(CGC_ACTIVATION_TYPES::ACTIVATIONDESC, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGC_ACTIVATION_TYPES::select(long ACTIVATIONNO)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGC_ACTIVATION_TYPES::ACTIVATIONNO,ACTIVATIONNO);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 



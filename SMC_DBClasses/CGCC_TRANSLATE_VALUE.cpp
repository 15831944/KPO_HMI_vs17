//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGCC_TRANSLATE_VALUE.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCC_TRANSLATE_VALUE::GROUP_ID("GROUP_ID");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCC_TRANSLATE_VALUE::VALUE("VALUE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCC_TRANSLATE_VALUE::LANG("LANG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGCC_TRANSLATE_VALUE::TEXT_("TEXT");

//##DBClassCodeUtility ! DO NOT EDIT !
CGCC_TRANSLATE_VALUE::CGCC_TRANSLATE_VALUE(cCBS_StdConnection* Connection)
:CSMC_DBData("GCC_TRANSLATE_VALUE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCC_TRANSLATE_VALUE::CGCC_TRANSLATE_VALUE(cCBS_Connection* Connection)
:CSMC_DBData("GCC_TRANSLATE_VALUE",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCC_TRANSLATE_VALUE::CGCC_TRANSLATE_VALUE()
:CSMC_DBData("GCC_TRANSLATE_VALUE")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGCC_TRANSLATE_VALUE::~CGCC_TRANSLATE_VALUE()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Group of values
std::string CGCC_TRANSLATE_VALUE::getGROUP_ID(long Row)
{
  return getString(CGCC_TRANSLATE_VALUE::GROUP_ID, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCC_TRANSLATE_VALUE::setGROUP_ID(const std::string& value)
{
  setString(CGCC_TRANSLATE_VALUE::GROUP_ID, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value
std::string CGCC_TRANSLATE_VALUE::getVALUE(long Row)
{
  return getString(CGCC_TRANSLATE_VALUE::VALUE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCC_TRANSLATE_VALUE::setVALUE(const std::string& value)
{
  setString(CGCC_TRANSLATE_VALUE::VALUE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Language
std::string CGCC_TRANSLATE_VALUE::getLANG(long Row)
{
  return getString(CGCC_TRANSLATE_VALUE::LANG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCC_TRANSLATE_VALUE::setLANG(const std::string& value)
{
  setString(CGCC_TRANSLATE_VALUE::LANG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description of value
std::string CGCC_TRANSLATE_VALUE::getTEXT(long Row)
{
  return getString(CGCC_TRANSLATE_VALUE::TEXT_, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGCC_TRANSLATE_VALUE::setTEXT(const std::string& value)
{
  setString(CGCC_TRANSLATE_VALUE::TEXT_, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGCC_TRANSLATE_VALUE::select(const std::string& VALUE, const std::string& LANG)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGCC_TRANSLATE_VALUE::VALUE,VALUE);
  addWhereClause(CGCC_TRANSLATE_VALUE::LANG,LANG);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 


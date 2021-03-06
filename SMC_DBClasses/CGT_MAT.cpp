//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 


#include "CGT_MAT.h"


//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::MAT_CODE("MAT_CODE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::DESCRIPTION("DESCRIPTION");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::CHARGE_PRIORITY("CHARGE_PRIORITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::PRICE("PRICE");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::DENSITY("DENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::BULK_DENSITY("BULK_DENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::WIRE_DENSITY("WIRE_DENSITY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::ENTHALPY("ENTHALPY");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::SPEC_HEAT("SPEC_HEAT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::HOMOG("HOMOG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::DISTRIB_STEEL_SLAG("DISTRIB_STEEL_SLAG");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::FEED_SPEED("FEED_SPEED");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::FEED_TEMP_FACT("FEED_TEMP_FACT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::DESCR_C("DESCR_C");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::MG_EQUIVALENT("MG_EQUIVALENT");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::MULTIPLE_ADDITION("MULTIPLE_ADDITION");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::AVAIL("AVAIL");
//##DBClassCodeUtility ! DO NOT EDIT !
const std::string CGT_MAT::MINWEIGHT("MINWEIGHT");

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT::CGT_MAT(cCBS_StdConnection* Connection)
:CSMC_DBData("GT_MAT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT::CGT_MAT(cCBS_Connection* Connection)
:CSMC_DBData("GT_MAT",Connection)
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT::CGT_MAT()
:CSMC_DBData("GT_MAT")
{
  //please implement virtual method, to initialize your members  
  doOnConstruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
CGT_MAT::~CGT_MAT()
{
  //please implement virtual method, to destruct your members
  doOnDestruct(); 
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Material code
std::string CGT_MAT::getMAT_CODE(long Row)
{
  return getString(CGT_MAT::MAT_CODE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setMAT_CODE(const std::string& value)
{
  setString(CGT_MAT::MAT_CODE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description, length to be defined
std::string CGT_MAT::getDESCRIPTION(long Row)
{
  return getString(CGT_MAT::DESCRIPTION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setDESCRIPTION(const std::string& value)
{
  setString(CGT_MAT::DESCRIPTION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##A lower value indicates a greater priority
long CGT_MAT::getCHARGE_PRIORITY(long Row)
{
  return getLong(CGT_MAT::CHARGE_PRIORITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setCHARGE_PRIORITY(long value)
{
  setLong(CGT_MAT::CHARGE_PRIORITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Price
double CGT_MAT::getPRICE(long Row)
{
  return getDouble(CGT_MAT::PRICE, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setPRICE(double value)
{
  setDouble(CGT_MAT::PRICE, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng.Unit : kg/m3, Density
long CGT_MAT::getDENSITY(long Row)
{
  return getLong(CGT_MAT::DENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setDENSITY(long value)
{
  setLong(CGT_MAT::DENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Used for normal materials (kg/m3)
long CGT_MAT::getBULK_DENSITY(long Row)
{
  return getLong(CGT_MAT::BULK_DENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setBULK_DENSITY(long value)
{
  setLong(CGT_MAT::BULK_DENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Used for wire materials (kg/m)
double CGT_MAT::getWIRE_DENSITY(long Row)
{
  return getDouble(CGT_MAT::WIRE_DENSITY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setWIRE_DENSITY(double value)
{
  setDouble(CGT_MAT::WIRE_DENSITY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng.Unit : kWh/kg, Enthalpy at 1600 Ã‚Â°C
double CGT_MAT::getENTHALPY(long Row)
{
  return getDouble(CGT_MAT::ENTHALPY, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setENTHALPY(double value)
{
  setDouble(CGT_MAT::ENTHALPY, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng.Unit : kWh/(kg*K), pecific heat
double CGT_MAT::getSPEC_HEAT(long Row)
{
  return getDouble(CGT_MAT::SPEC_HEAT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setSPEC_HEAT(double value)
{
  setDouble(CGT_MAT::SPEC_HEAT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Homogenisation factor
long CGT_MAT::getHOMOG(long Row)
{
  return getLong(CGT_MAT::HOMOG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setHOMOG(long value)
{
  setLong(CGT_MAT::HOMOG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng.Unit : %, Percent of material that will go into the steel
double CGT_MAT::getDISTRIB_STEEL_SLAG(long Row)
{
  return getDouble(CGT_MAT::DISTRIB_STEEL_SLAG, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setDISTRIB_STEEL_SLAG(double value)
{
  setDouble(CGT_MAT::DISTRIB_STEEL_SLAG, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Eng.Unit : m/min, Feeding Speed for wire feeder
double CGT_MAT::getFEED_SPEED(long Row)
{
  return getDouble(CGT_MAT::FEED_SPEED, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setFEED_SPEED(double value)
{
  setDouble(CGT_MAT::FEED_SPEED, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Temperature coefficient for feeding speed
double CGT_MAT::getFEED_TEMP_FACT(long Row)
{
  return getDouble(CGT_MAT::FEED_TEMP_FACT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setFEED_TEMP_FACT(double value)
{
  setDouble(CGT_MAT::FEED_TEMP_FACT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Description Customer
std::string CGT_MAT::getDESCR_C(long Row)
{
  return getString(CGT_MAT::DESCR_C, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setDESCR_C(const std::string& value)
{
  setString(CGT_MAT::DESCR_C, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Value needed for HMD only. For the model to see, how Mg can be replaced.
long CGT_MAT::getMG_EQUIVALENT(long Row)
{
  return getLong(CGT_MAT::MG_EQUIVALENT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setMG_EQUIVALENT(long value)
{
  setLong(CGT_MAT::MG_EQUIVALENT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Flag if multiple addition is allowed or not. (1= allowed, 0= not allowed)
long CGT_MAT::getMULTIPLE_ADDITION(long Row)
{
  return getLong(CGT_MAT::MULTIPLE_ADDITION, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setMULTIPLE_ADDITION(long value)
{
  setLong(CGT_MAT::MULTIPLE_ADDITION, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##Indicates the genreal availability in the plant. 0,1. Availabilities in the individual bin systems are controlled by purpose codes.
long CGT_MAT::getAVAIL(long Row)
{
  return getLong(CGT_MAT::AVAIL, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setAVAIL(long value)
{
  setLong(CGT_MAT::AVAIL, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
//##This MINWEIGHT indicates that the material should not be considered for a charging instruction if the model calculates less than this weight. See also MINWEIGTH in PD_MAT_AVAIL with is based on Level 1 information and indicates the minimum chargeable weight due to physical restrictions of the bin/weighing system. The maximum of these weigths is to be used.
double CGT_MAT::getMINWEIGHT(long Row)
{
  return getDouble(CGT_MAT::MINWEIGHT, Row);
}

//##DBClassCodeUtility ! DO NOT EDIT !
void CGT_MAT::setMINWEIGHT(double value)
{
  setDouble(CGT_MAT::MINWEIGHT, value);
}

//##DBClassCodeUtility ! DO NOT EDIT !
bool CGT_MAT::select(const std::string& MAT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_MAT::MAT_CODE,MAT_CODE);
  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

//## ------------------------------------END-GENERATED-CODE---------------------- 

//## ------------------------------------YOUR-CODE------------------------------- 

bool CGT_MAT::selectAvailable(const std::string& MAT_CODE)
{
  cleanWhereStatement();

  m_Statement = "Select * from " + m_TableName;

  addWhereClause(CGT_MAT::MAT_CODE,MAT_CODE);
  addWhereClause(CGT_MAT::AVAIL, (long)1);

  m_Statement += getWhereStatement() + ";";

  return CSMC_DBData::select();
}

bool CGT_MAT::deleteRow(const std::string& MAT_CODE)
{
  cleanWhereStatement();

  addWhereClause(CGT_MAT::MAT_CODE,MAT_CODE);

  return CSMC_DBData::deleteRows();
}

std::string CGT_MAT::getMatDescrforMatCode(const std::string MAT_CODE)
{
  std::string RetValue = CSMC_DBData::unspecString;

  if( select(MAT_CODE))
  {
    RetValue = getDESCRIPTION(1);
  }

  return RetValue;
}

double CGT_MAT::getMinWeightOfMatCode(const std::string& MAT_CODE)
{
  double RetValue = CSMC_DBData::unspecDouble;

  if ( select(MAT_CODE) )
  {
    RetValue = getMINWEIGHT(1);
  }

  return RetValue;
}

bool CGT_MAT::updateInsertMat(const std::string &MAT_CODE, const std::string &DESCRIPTION, long CHARGE_PRIORITY, double PRICE, 
                              long DENSITY, long BULK_DENSITY, double WIRE_DENSITY, double ENTHALPY, double SPEC_HEAT, 
                              long HOMOG, double DISTRIB_STEEL_SLAG, 
                              double FEED_SPEED, double FEED_TEMP_FACT, const std::string& DESCR_C, long MG_EQUIVALENT, 
                              long MULTIPLE_ADDITION, long AVAIL, double MINWEIGHT, bool Commit, cCBS_ODBC_DBError &Error)
{
  bool RetValue = false;

  setDESCRIPTION(DESCRIPTION);

  setCHARGE_PRIORITY(CHARGE_PRIORITY);

  setPRICE(PRICE);

  setDENSITY(DENSITY);

  setBULK_DENSITY(BULK_DENSITY);

  setWIRE_DENSITY(WIRE_DENSITY);

  setENTHALPY(ENTHALPY);

  setSPEC_HEAT(SPEC_HEAT);

  setHOMOG(HOMOG);

  setDISTRIB_STEEL_SLAG(DISTRIB_STEEL_SLAG);

  setFEED_SPEED(FEED_SPEED);

  setFEED_TEMP_FACT(FEED_TEMP_FACT);

  setDESCR_C(DESCR_C);

  setMG_EQUIVALENT(MG_EQUIVALENT);

  setMULTIPLE_ADDITION(MULTIPLE_ADDITION);

  setAVAIL(AVAIL);

  setMINWEIGHT(MINWEIGHT);

  if ( select(MAT_CODE) )
  {
    RetValue = update();
  }
  else
  {
    setMAT_CODE(MAT_CODE);

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



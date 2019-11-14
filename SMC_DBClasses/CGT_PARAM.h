//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGT_PARAM_INCLUDED
#define _INC_CGT_PARAM_INCLUDED

#include "CSMC_DBData.h"

class CGT_PARAM
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string UNITGROUPNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string UNIT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string VALUE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INST_ACTV;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DIALOG_PARAM;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONV;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MIN_VALUE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAX_VALUE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CREATIONDATE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PARAMDESCR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PARAMDESCR_C;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PARAMGROUP;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_PARAM(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_PARAM(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_PARAM();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGT_PARAM();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unit group number, see GC_PLANT_GROUP
  long getUNITGROUPNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUNITGROUPNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Parameter name
  std::string getPNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Production Practice Number
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Type indicator 1-9
  long getTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTYPE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Engineering unit
  std::string getUNIT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUNIT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Value, used for unkeyed parameters only, see also
  std::string getVALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVALUE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Immediately active flag
  long getINST_ACTV(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINST_ACTV(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Can be modified via the dialogue system
  long getDIALOG_PARAM(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDIALOG_PARAM(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Conversion factor
  double getCONV(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONV(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Minimum value
  double getMIN_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMIN_VALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Maximum value
  double getMAX_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAX_VALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getCREATIONDATE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCREATIONDATE(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Description of Parameter
  std::string getPARAMDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPARAMDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Parameter Description Customer
  std::string getPARAMDESCR_C(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPARAMDESCR_C(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Parameter group
  std::string getPARAMGROUP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPARAMGROUP(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long UNITGROUPNO, const std::string& PNAME, long PRACNO, long TYPE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByPlant(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE);

  bool selectOrderByUnitGroupNo(const std::string& PNAME, long PRACNO, long TYPE);

  std::vector<long> getUnitGroupList(const std::string& Plant,long PlantNo);

  bool getValue(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE, std::string& Value);

  bool getKeyedValue(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE, const std::string& KEY1, const std::string& KEY2, std::string& Value);

  bool getKeyedValueList(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE, const std::string& KEY1, const std::string& KEY2, std::set<std::string>& ValueList);

  bool setHeatCustSeqParam(long PlantNo, long pValue, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateValue (const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE, const std::string &Value);

  // check plausibility for numeric parameter types MIN <= value <= MAX
  bool checkMinMaxRange(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE, const std::string &Value);

  bool isParam(const std::string& PLANT, long PLANTNO, const std::string& PNAME, long PRACNO, long TYPE);


};

#endif /* _INC_CGT_PARAM_INCLUDED */

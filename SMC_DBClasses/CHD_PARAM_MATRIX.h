//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHD_PARAM_MATRIX_INCLUDED
#define _INC_CHD_PARAM_MATRIX_INCLUDED

#include <vector>
#include "CSMC_DBData.h"

class CHD_PARAM_MATRIX
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HEATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string UNITGROUPNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string KEY1;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string KEY2;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string VALUE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_PARAM_MATRIX(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_PARAM_MATRIX(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_PARAM_MATRIX();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHD_PARAM_MATRIX();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Internal heat identifier
  std::string getHEATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHEATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Treatment identifier
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Plant identifier
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

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
  //##Type indicator (1-9)
  long getTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTYPE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Production Practice Number
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##First key
  std::string getKEY1(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setKEY1(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Second key, not used for single, keyed parameter
  std::string getKEY2(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setKEY2(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Value
  std::string getVALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVALUE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long UNITGROUPNO, const std::string& PNAME, long TYPE, long PRACNO, const std::string& KEY1, const std::string& KEY2);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error);

  std::string ArrayToString(std::vector<long> &pUnitGroup);

  bool deleteData(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(std::vector<long> &pUnitGroup, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHD_PARAM_MATRIX_INCLUDED */

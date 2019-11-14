//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHD_GRADE_EQUIV_INCLUDED
#define _INC_CHD_GRADE_EQUIV_INCLUDED

#include "CSMC_DBData.h"

class CGT_GRADE_EQUIV;

class CHD_GRADE_EQUIV
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
  static const std::string STEELGRADECODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string EQ_NAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DEF_ORDER;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_GRADE_EQUIV(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_GRADE_EQUIV(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_GRADE_EQUIV();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHD_GRADE_EQUIV();

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
  //##Steel grade code
  std::string getSTEELGRADECODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTEELGRADECODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Equivalence name
  std::string getEQ_NAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setEQ_NAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Display order for HMI
  long getDEF_ORDER(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDEF_ORDER(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& STEELGRADECODE, const std::string& EQ_NAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(const std::string& STEELGRADECODE, const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHD_GRADE_EQUIV_INCLUDED */

//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHDH_GRADE_INCLUDED
#define _INC_CHDH_GRADE_INCLUDED

#include "CSMC_DBData.h"

class CHDH_GRADE
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HM_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STEELGRADECODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LIQTEMP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string USERCODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_GRADE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_GRADE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_GRADE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHDH_GRADE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getHM_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHM_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getSTEELGRADECODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTEELGRADECODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getLIQTEMP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLIQTEMP(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getUSERCODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUSERCODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copyHDHGrade(const string &pSteelGrade, const string& pHeatId, const string& pTreatId, const string& pPlant, bool pCommit);

};

#endif /* _INC_CHDH_GRADE_INCLUDED */

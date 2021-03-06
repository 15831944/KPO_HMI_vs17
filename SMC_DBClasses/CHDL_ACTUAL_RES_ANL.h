//## Copyright (C) 2012 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHDL_ACTUAL_RES_ANL_INCLUDED
#define _INC_CHDL_ACTUAL_RES_ANL_INCLUDED

#include "CSMC_DBData.h"

class CHDL_ACTUAL_RES_ANL
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
  static const std::string REVTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ENAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ANL;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_ACTUAL_RES_ANL(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_ACTUAL_RES_ANL(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_ACTUAL_RES_ANL();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHDL_ACTUAL_RES_ANL();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getHEATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHEATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getENAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setENAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getANL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setANL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& REVTIME, const std::string& ENAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHDL_ACTUAL_RES_ANL_INCLUDED */

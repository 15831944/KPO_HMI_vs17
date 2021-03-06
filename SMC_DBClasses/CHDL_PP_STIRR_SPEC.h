//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHDL_PP_STIRR_SPEC_INCLUDED
#define _INC_CHDL_PP_STIRR_SPEC_INCLUDED

#include "CSMC_DBData.h"

class CGTL_PP_STIRR_SPEC;

class CHDL_PP_STIRR_SPEC
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
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACPHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INTENSITY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRRGASTYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURATION;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_PP_STIRR_SPEC(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_PP_STIRR_SPEC(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_PP_STIRR_SPEC();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHDL_PP_STIRR_SPEC();

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
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPRACPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getINTENSITY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINTENSITY(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getSTIRRGASTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRRGASTYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getDURATION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURATION(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PRACNO, const std::string& PRACPHASE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long PRACNO, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHDL_PP_STIRR_SPEC_INCLUDED */

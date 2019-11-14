//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGTE_PP_BURNER_INCLUDED
#define _INC_CGTE_PP_BURNER_INCLUDED

#include "CSMC_DBData.h"

class CGTE_PP_BURNER
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATMODENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LIQ_ADD_AMOUNT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string BURNERNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCR_E;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCR_C;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string USERCODE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_BURNER(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_BURNER(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_BURNER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGTE_PP_BURNER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getTREATMODENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATMODENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getLIQ_ADD_AMOUNT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLIQ_ADD_AMOUNT(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getBURNERNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setBURNERNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDESCR_E(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCR_E(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDESCR_C(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCR_C(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getUSERCODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUSERCODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& BURNERNAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGTE_PP_BURNER_INCLUDED */

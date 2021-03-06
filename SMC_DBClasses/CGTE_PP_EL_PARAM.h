//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGTE_PP_EL_PARAM_INCLUDED
#define _INC_CGTE_PP_EL_PARAM_INCLUDED

#include "CSMC_DBData.h"

class CGTE_PP_EL_PARAM
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
  static const std::string PRACPHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REMEGY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string BEGINEGYWALLTEMPCTRL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MELTDOWNRATEBSK;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAXEGYWITHOUTBSKDATA;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAXEGYWITHBSKDATA;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string AIMTEMP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DISPLAY_ORDER;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_EL_PARAM(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_EL_PARAM(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTE_PP_EL_PARAM();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGTE_PP_EL_PARAM();

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
  std::string getPRACPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getREMEGY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREMEGY(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getBEGINEGYWALLTEMPCTRL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setBEGINEGYWALLTEMPCTRL(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getMELTDOWNRATEBSK(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMELTDOWNRATEBSK(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getMAXEGYWITHOUTBSKDATA(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAXEGYWITHOUTBSKDATA(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getMAXEGYWITHBSKDATA(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAXEGYWITHBSKDATA(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getAIMTEMP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setAIMTEMP(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getDISPLAY_ORDER(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDISPLAY_ORDER(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, long PLANTNO, long PRACNO, long TREATMODENO, long LIQ_ADD_AMOUNT, const std::string& PRACPHASE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGTE_PP_EL_PARAM_INCLUDED */

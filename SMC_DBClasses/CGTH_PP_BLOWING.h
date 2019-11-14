//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGTH_PP_BLOWING_INCLUDED
#define _INC_CGTH_PP_BLOWING_INCLUDED

#include "CSMC_DBData.h"

class CGTH_PP_BLOWING
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCR_E;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCR_C;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string USERCODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_STD_REL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_FIX_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_FIX_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_MIN_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_MIN_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_LIME_MIN_MG;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_STD_REL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_FIX_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_FIX_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_MIN_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_MIN_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CO_CARB_MIN_MG;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_STD_REL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_FIX_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_FIX_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_MIN_LIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_MIN_CARBIDE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ECO_MIN_MG;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTH_PP_BLOWING(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTH_PP_BLOWING(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTH_PP_BLOWING();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGTH_PP_BLOWING();

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

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
  double getCO_LIME_STD_REL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_STD_REL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_LIME_FIX_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_FIX_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_LIME_FIX_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_FIX_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_LIME_MIN_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_MIN_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_LIME_MIN_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_MIN_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_LIME_MIN_MG(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_LIME_MIN_MG(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_STD_REL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_STD_REL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_FIX_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_FIX_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_FIX_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_FIX_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_MIN_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_MIN_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_MIN_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_MIN_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getCO_CARB_MIN_MG(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCO_CARB_MIN_MG(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_STD_REL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_STD_REL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_FIX_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_FIX_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_FIX_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_FIX_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_MIN_LIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_MIN_LIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_MIN_CARBIDE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_MIN_CARBIDE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getECO_MIN_MG(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setECO_MIN_MG(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long PLANTNO, long PRACNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGTH_PP_BLOWING_INCLUDED */

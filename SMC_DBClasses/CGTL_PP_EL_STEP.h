//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGTL_PP_EL_STEP_INCLUDED
#define _INC_CGTL_PP_EL_STEP_INCLUDED

#include "CSMC_DBData.h"

class CGTL_PP_EL_STEP
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIVITYNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACPHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STEPNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURATION;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DELTA_TEMP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string VOLTTAP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string IMPCURVE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTL_PP_EL_STEP(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTL_PP_EL_STEP(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGTL_PP_EL_STEP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGTL_PP_EL_STEP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPRACNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getACTIVITYNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIVITYNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPRACPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTEPNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTEPNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getDURATION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURATION(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getDELTA_TEMP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDELTA_TEMP(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getVOLTTAP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVOLTTAP(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getIMPCURVE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setIMPCURVE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long PLANTNO, long PRACNO, const std::string& ACTIVITYNAME, const std::string& PRACPHASE, long STEPNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGTL_PP_EL_STEP_INCLUDED */

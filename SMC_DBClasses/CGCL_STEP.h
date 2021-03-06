//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGCL_STEP_INCLUDED
#define _INC_CGCL_STEP_INCLUDED

#include "CSMC_DBData.h"

class CGCL_STEP
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STEPNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STEPDESCR;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCL_STEP(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCL_STEP(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCL_STEP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGCL_STEP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTEPNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTEPNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getSTEPDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTEPDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long STEPNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGCL_STEP_INCLUDED */

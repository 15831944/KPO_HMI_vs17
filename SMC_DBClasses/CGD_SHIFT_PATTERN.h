//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGD_SHIFT_PATTERN_INCLUDED
#define _INC_CGD_SHIFT_PATTERN_INCLUDED

#include "CSMC_DBData.h"

class CGD_SHIFT_PATTERN
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PATTERN_NO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SHIFT_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SHIFT_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DAY_IN_PATTERN;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CREW_ID;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_SHIFT_PATTERN(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_SHIFT_PATTERN(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_SHIFT_PATTERN();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGD_SHIFT_PATTERN();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identification of pattern 
  long getPATTERN_NO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPATTERN_NO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Type of shift from GC_SHIFT_CAT
  long getSHIFT_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSHIFT_TYPE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Shift code of GC_SHIFT_CAT
  std::string getSHIFT_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSHIFT_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Day within this pattern
  long getDAY_IN_PATTERN(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDAY_IN_PATTERN(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Crew Id from GC_CREW_CAT
  std::string getCREW_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCREW_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long PATTERN_NO, long SHIFT_TYPE, const std::string& SHIFT_ID, long DAY_IN_PATTERN);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGD_SHIFT_PATTERN_INCLUDED */

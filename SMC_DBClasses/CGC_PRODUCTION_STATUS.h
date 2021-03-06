//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.0 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_PRODUCTION_STATUS_INCLUDED
#define _INC_CGC_PRODUCTION_STATUS_INCLUDED

#include "CSMC_DBData.h"

class CGC_PRODUCTION_STATUS
: public CSMC_DBData

{

public:

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_PRODUCTION_STATUS(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_PRODUCTION_STATUS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTATUS_NO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUS_NO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getSTATUS_DESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUS_DESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long STATUS_NO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_PRODUCTION_STATUS_INCLUDED */

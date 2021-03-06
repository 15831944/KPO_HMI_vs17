//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_MEASUREMENT_TYPE_INCLUDED
#define _INC_CGC_MEASUREMENT_TYPE_INCLUDED

#include "CSMC_DBData.h"

class CGC_MEASUREMENT_TYPE
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MEASTYPENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MEASTYPENAME;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_TYPE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_TYPE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_MEASUREMENT_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identifies the type of measurement
  long getMEASTYPENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMEASTYPENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identifies the name of measurement
  std::string getMEASTYPENAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMEASTYPENAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long MEASTYPENO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_MEASUREMENT_TYPE_INCLUDED */

//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_MEASUREMENT_NAME_INCLUDED
#define _INC_CGC_MEASUREMENT_NAME_INCLUDED

#include "CSMC_DBData.h"

class CGC_MEASUREMENT_NAME
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MEASNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SCOPENO;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_NAME(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_NAME(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_MEASUREMENT_NAME();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_MEASUREMENT_NAME();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Measured Element/compound names for analysis, or names like TEMP, EMF or other measuremens
  std::string getMEASNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMEASNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Type specifier
  long getSCOPENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSCOPENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& MEASNAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool isOfElement(const std::string &MEASNAME, long SCOPENO);

};

#endif /* _INC_CGC_MEASUREMENT_NAME_INCLUDED */

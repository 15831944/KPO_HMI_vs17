//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_LADLE_TYPE_INCLUDED
#define _INC_CGC_LADLE_TYPE_INCLUDED

#include "CSMC_DBData.h"

class CGC_LADLE_TYPE
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLETYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLETYPEDESCR;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_LADLE_TYPE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_LADLE_TYPE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_LADLE_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_LADLE_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##e.g. Hot Metal -> H, Teeming -> T
  std::string getLADLETYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLETYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getLADLETYPEDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLETYPEDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& LADLETYPE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool isValidType(const std::string& LADLETYPE);

};

#endif /* _INC_CGC_LADLE_TYPE_INCLUDED */
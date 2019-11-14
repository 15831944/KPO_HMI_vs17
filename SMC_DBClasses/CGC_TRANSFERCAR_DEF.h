//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_TRANSFERCAR_DEF_INCLUDED
#define _INC_CGC_TRANSFERCAR_DEF_INCLUDED

#include "CSMC_DBData.h"

class CGC_TRANSFERCAR_DEF
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CARNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCR;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_TRANSFERCAR_DEF(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_TRANSFERCAR_DEF(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_TRANSFERCAR_DEF();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_TRANSFERCAR_DEF();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Transfer car number
  long getCARNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCARNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Meaningful name, if numbering is insiufficient, e.g. North, South
  std::string getDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long CARNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_TRANSFERCAR_DEF_INCLUDED */

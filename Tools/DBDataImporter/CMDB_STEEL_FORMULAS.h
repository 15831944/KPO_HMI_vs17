//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.5.8 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMDB_STEEL_FORMULAS_INCLUDED
#define _INC_CMDB_STEEL_FORMULAS_INCLUDED

#include "CSMC_DBData.h"

class CMDB_STEEL_FORMULAS
: public CSMC_DBData
{

public:

  //##DBClassCodeUtility ! DO NOT EDIT !
  CMDB_STEEL_FORMULAS(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CMDB_STEEL_FORMULAS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getFORMULA_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFORMULA_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDESCRIPTION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCRIPTION(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getOFFSET(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setOFFSET(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getLINEAR_FORMULA_FLG(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLINEAR_FORMULA_FLG(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getNUMERATOR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setNUMERATOR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDENOMINATOR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDENOMINATOR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& FORMULA_ID);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CMDB_STEEL_FORMULAS_INCLUDED */

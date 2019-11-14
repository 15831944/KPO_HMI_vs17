//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.5.8 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CAUX_VALUES_INCLUDED
#define _INC_CAUX_VALUES_INCLUDED

#include "CSMC_DBData.h"

class CAUX_VALUES
: public CSMC_DBData
{

public:

  //##DBClassCodeUtility ! DO NOT EDIT !
  CAUX_VALUES(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CAUX_VALUES();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getVARIABLE_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVARIABLE_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getVALUE_SEQ(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVALUE_SEQ(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDESCRIPTION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCRIPTION(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getINTEGER_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINTEGER_VALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getCHAR_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCHAR_VALUE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDouble_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDouble_VALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getINFO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINFO(const std::string& value);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  std::string getElementName(long ElementCode);

  std::string getComponentName(long ElementCode);

};

#endif /* _INC_CAUX_VALUES_INCLUDED */
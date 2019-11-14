//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_SCRAP_CONTAINER_STATUS_INCLUDED
#define _INC_CGC_SCRAP_CONTAINER_STATUS_INCLUDED

#include "CSMC_DBData.h"

class CGC_SCRAP_CONTAINER_STATUS
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUSNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUSSHORT;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_SCRAP_CONTAINER_STATUS(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_SCRAP_CONTAINER_STATUS(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_SCRAP_CONTAINER_STATUS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_SCRAP_CONTAINER_STATUS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTATUSNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUSNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Physical status: Available, Maintenance
  std::string getSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUS(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##A, M
  std::string getSTATUSSHORT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUSSHORT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long STATUSNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_SCRAP_CONTAINER_STATUS_INCLUDED */

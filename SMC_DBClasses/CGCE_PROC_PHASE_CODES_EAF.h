//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGCE_PROC_PHASE_CODES_EAF_INCLUDED
#define _INC_CGCE_PROC_PHASE_CODES_EAF_INCLUDED

#include "CSMC_DBData.h"

class CGCE_PROC_PHASE_CODES_EAF
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PROCPHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PROCPHASENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PROCPHASEDESCR;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_PROC_PHASE_CODES_EAF(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_PROC_PHASE_CODES_EAF(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_PROC_PHASE_CODES_EAF();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGCE_PROC_PHASE_CODES_EAF();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPROCPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPROCPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPROCPHASENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPROCPHASENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPROCPHASEDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPROCPHASEDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PROCPHASE, long PROCPHASENO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGCE_PROC_PHASE_CODES_EAF_INCLUDED */

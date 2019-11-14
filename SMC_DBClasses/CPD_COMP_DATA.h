//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPD_COMP_DATA_INCLUDED
#define _INC_CPD_COMP_DATA_INCLUDED

#include "CSMC_DBData.h"

class CPD_COMP_DATA
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HEATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DATECHANGE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COMPCODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUS;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_COMP_DATA(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_COMP_DATA(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_COMP_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPD_COMP_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Internal heat identifier
  std::string getHEATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHEATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Treatment identifier
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Plant identifier
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Timestamp indication of the change
  CDateTime getDATECHANGE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDATECHANGE(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Computer mode
  std::string getCOMPCODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOMPCODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& DATECHANGE, const std::string& COMPCODE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& DATECHANGE, const std::string& COMPCODE);

  long getActStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& COMPCODE);

  bool writeStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const std::string& COMPCODE, long STATUS);

  bool writeStatus(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, seqComputerModes& SeqComputerModes);

};

#endif /* _INC_CPD_COMP_DATA_INCLUDED */

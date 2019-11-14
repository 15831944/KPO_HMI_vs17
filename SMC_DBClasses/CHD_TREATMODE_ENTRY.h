//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHD_TREATMODE_ENTRY_INCLUDED
#define _INC_CHD_TREATMODE_ENTRY_INCLUDED

#include "CSMC_DBData.h"

class CHD_TREATMODE_ENTRY
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
  static const std::string TREATMODENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATMENTPHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATMENTPHASENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATMENTPHASEORDER;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRACPHASE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TREATMODE_ENTRY(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TREATMODE_ENTRY(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TREATMODE_ENTRY();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHD_TREATMODE_ENTRY();

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
  //##Treatment mode number
  long getTREATMODENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATMODENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Phases are e.g. Basket, LiqAdd for EAF
  std::string getTREATMENTPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATMENTPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Counter for equal phases, e.g Basket number 1, Basket number 2
  long getTREATMENTPHASENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATMENTPHASENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Display order in the HMI
  long getTREATMENTPHASEORDER(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATMENTPHASEORDER(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Practice phase name
  std::string getPRACPHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRACPHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long TREATMODENO, const std::string& TREATMENTPHASE, long TREATMENTPHASENO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectOrdered(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long TREATMODENO);

  bool copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO, long TREATMODENO, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long TREATMODENO);

};

#endif /* _INC_CHD_TREATMODE_ENTRY_INCLUDED */

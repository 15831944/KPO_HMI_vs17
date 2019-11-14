//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHD_TAPCH_DATA_INCLUDED
#define _INC_CHD_TAPCH_DATA_INCLUDED

#include "CSMC_DBData.h"

class CHD_TAPCH_DATA
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
  static const std::string STARTTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ENDTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string VOLTTAP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string IMPCURVE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURATION;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ELEC_EGY_TAP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ELEC_EGYTOT;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TAPCH_DATA(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TAPCH_DATA(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_TAPCH_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHD_TAPCH_DATA();

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
  //##Start time of either changed tap or imp-curve
  CDateTime getSTARTTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTARTTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##end time of either changed tap or imp-curve before to another tap or imp-curve
  CDateTime getENDTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setENDTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getVOLTTAP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVOLTTAP(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getIMPCURVE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setIMPCURVE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Duration the voltage step was active
  double getDURATION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURATION(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Total electric energy consumption within this voltage tap, kWh
  double getELEC_EGY_TAP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setELEC_EGY_TAP(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Total electric energy consumption in case of electric heating, kWh
  double getELEC_EGYTOT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setELEC_EGYTOT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& STARTTIME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHD_TAPCH_DATA_INCLUDED */

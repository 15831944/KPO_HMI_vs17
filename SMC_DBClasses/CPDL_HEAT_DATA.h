//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPDL_HEAT_DATA_INCLUDED
#define _INC_CPDL_HEAT_DATA_INCLUDED

#include "CSMC_DBData.h"

class CPDL_HEAT_DATA
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
  static const std::string CARNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLE_ARRTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLE_DEPARTTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string FIRST_POWER_ON;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LAST_POWER_OFF;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ELEC_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SPECEGY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string POWER_ON_DUR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LASTTRAFOTAP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_START;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_END;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_AR_DUR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_N2_DUR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_AR_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_N2_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_START_EMRGNCY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_END_EMRGNCY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_AR_CONS_EMRGNCY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_N2_CONS_EMRGNCY;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_SPEC_AR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_SPEC_N2;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SOFTSTIRR_DUR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CLEANLINESS_START;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CLEANLINESS_END;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string FURNACE_ROOFAGE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ADD_AL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SLAG_FORMER;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ALLOY_MAT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string BIN_MATERIAL;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDL_HEAT_DATA(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDL_HEAT_DATA(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDL_HEAT_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPDL_HEAT_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getHEATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHEATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCARNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCARNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getLADLE_ARRTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLE_ARRTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getLADLE_DEPARTTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLE_DEPARTTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getFIRST_POWER_ON(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFIRST_POWER_ON(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getLAST_POWER_OFF(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLAST_POWER_OFF(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getELEC_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setELEC_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSPECEGY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSPECEGY(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getPOWER_ON_DUR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPOWER_ON_DUR(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getLASTTRAFOTAP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLASTTRAFOTAP(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getSTIRR_START(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_START(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getSTIRR_END(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_END(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_AR_DUR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_AR_DUR(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_N2_DUR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_N2_DUR(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_AR_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_AR_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_N2_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_N2_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getSTIRR_START_EMRGNCY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_START_EMRGNCY(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getSTIRR_END_EMRGNCY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_END_EMRGNCY(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_AR_CONS_EMRGNCY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_AR_CONS_EMRGNCY(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_N2_CONS_EMRGNCY(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_N2_CONS_EMRGNCY(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_SPEC_AR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_SPEC_AR(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_SPEC_N2(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_SPEC_N2(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSOFTSTIRR_DUR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSOFTSTIRR_DUR(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getCLEANLINESS_START(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCLEANLINESS_START(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getCLEANLINESS_END(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCLEANLINESS_END(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getFURNACE_ROOFAGE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFURNACE_ROOFAGE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getADD_AL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setADD_AL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSLAG_FORMER(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSLAG_FORMER(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getALLOY_MAT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setALLOY_MAT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getBIN_MATERIAL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setBIN_MATERIAL(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool doAnnouncement(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long CARNO, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

  CDateTime getLastFinishedTimeByPlant(const std::string &PLANT,const long PLANTNO, const long CARNO);

  bool UpdateAlloyWeight(const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, const double ALLOY_MAT ,bool Commit, cCBS_ODBC_DBError &Error);

  bool UpdateBinWeight(const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, const double dbBinWeight ,bool Commit, cCBS_ODBC_DBError &Error);

  bool UpdateElecConsTotal(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const double dbElecConsTotal, const double specEgy, bool Commit, cCBS_ODBC_DBError &Error);

  bool UpdateSlagFormer(const std::string& HEATID, const std::string& TREATID,const std::string& PLANT, const double dbSlagFormer ,bool Commit, cCBS_ODBC_DBError &Error);

};

#endif /* _INC_CPDL_HEAT_DATA_INCLUDED */

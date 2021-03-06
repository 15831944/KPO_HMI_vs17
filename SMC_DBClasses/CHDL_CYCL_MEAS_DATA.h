//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHDL_CYCL_MEAS_DATA_INCLUDED
#define _INC_CHDL_CYCL_MEAS_DATA_INCLUDED

#include "CSMC_DBData.h"

class CHDL_CYCL_MEAS_DATA
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
  static const std::string REVTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCEHEATANNOUNCE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCESTARTOFHEAT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ELEC_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CURACTIYITY_L1;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COMPMODE_ELEC;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COMPMODE_MAT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COMPMODE_STIRR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string VOLTTAP;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string IMPCURVE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ELECTRODEPOS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string FURNACEBRAKERSTATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TAPCHANGERSTATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string POWERSTATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ROOFPOS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string GANTRYPOS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HOIST_AVAIL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRRGASTYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_N2_FLOW;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_AR_FLOW;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_N2_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_AR_CONS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STIRR_INT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIVITYNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CURPHASE_L1;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TEMP_ACT;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_CYCL_MEAS_DATA(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_CYCL_MEAS_DATA(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDL_CYCL_MEAS_DATA();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHDL_CYCL_MEAS_DATA();

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
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDURSINCEHEATANNOUNCE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCEHEATANNOUNCE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDURSINCESTARTOFHEAT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCESTARTOFHEAT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getELEC_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setELEC_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getCURACTIYITY_L1(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCURACTIYITY_L1(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCOMPMODE_ELEC(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOMPMODE_ELEC(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCOMPMODE_MAT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOMPMODE_MAT(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCOMPMODE_STIRR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOMPMODE_STIRR(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getVOLTTAP(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setVOLTTAP(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getIMPCURVE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setIMPCURVE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getELECTRODEPOS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setELECTRODEPOS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getFURNACEBRAKERSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFURNACEBRAKERSTATUS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getTAPCHANGERSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTAPCHANGERSTATUS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPOWERSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPOWERSTATUS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getROOFPOS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setROOFPOS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getGANTRYPOS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setGANTRYPOS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getHOIST_AVAIL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHOIST_AVAIL(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getSTIRRGASTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRRGASTYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_N2_FLOW(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_N2_FLOW(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_AR_FLOW(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_AR_FLOW(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_N2_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_N2_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSTIRR_AR_CONS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_AR_CONS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getSTIRR_INT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTIRR_INT(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getACTIVITYNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIVITYNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCURPHASE_L1(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCURPHASE_L1(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getTEMP_ACT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTEMP_ACT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, const CDateTime& REVTIME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CHDL_CYCL_MEAS_DATA_INCLUDED */

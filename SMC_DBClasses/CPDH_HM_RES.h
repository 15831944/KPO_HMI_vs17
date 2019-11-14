//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPDH_HM_RES_INCLUDED
#define _INC_CPDH_HM_RES_INCLUDED

#include "CSMC_DBData.h"

class CPDH_HM_RES
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HM_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREAT_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string UPDATENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCEHEATANNOUNCEMENT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HM_MASS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SLAG_MASS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TEMP_ACT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TEMP_END;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CUR_PHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string GAS_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COMP_AVAIL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SULPHUR_PPM_AIM;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SULPHUR_DELTA_PPM;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SULPHUR_DELTA_KG;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DEPART_TIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string FINAL_SLAG_WEIGHT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DUR_START_PHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DUR_CO_PHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DUR_END_PHASE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAT_COST_START;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAT_COST_END;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_HM_RES(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_HM_RES(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_HM_RES();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPDH_HM_RES();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getHM_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHM_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getTREATID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getTREAT_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREAT_TYPE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getUPDATENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUPDATENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDURSINCEHEATANNOUNCEMENT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCEHEATANNOUNCEMENT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getHM_MASS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHM_MASS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSLAG_MASS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSLAG_MASS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getTEMP_ACT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTEMP_ACT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getTEMP_END(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTEMP_END(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getCUR_PHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCUR_PHASE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getGAS_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setGAS_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getCOMP_AVAIL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOMP_AVAIL(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSULPHUR_PPM_AIM(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSULPHUR_PPM_AIM(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSULPHUR_DELTA_PPM(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSULPHUR_DELTA_PPM(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getSULPHUR_DELTA_KG(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSULPHUR_DELTA_KG(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getDEPART_TIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDEPART_TIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getFINAL_SLAG_WEIGHT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFINAL_SLAG_WEIGHT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDUR_START_PHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDUR_START_PHASE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDUR_CO_PHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDUR_CO_PHASE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDUR_END_PHASE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDUR_END_PHASE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getMAT_COST_START(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAT_COST_START(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getMAT_COST_END(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAT_COST_END(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long TREAT_TYPE, const CDateTime& REVTIME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

 bool update_HeatAnnounce(const string &pHM_ID);
 bool selectActual(const string& HEATID, const string& TREATID, const string& PLANT, long TREAT_TYPE);
 bool CPDH_HM_RES::writeResults(const string& HM_ID, const string& TreatID, const string& PlantID, long Treat_Type, const CDateTime& Now,double d1, double SlagAmount,double TemperatureAfter,long ComputerMode,double CODur);
 bool update_CompModes(const string& HM_ID, const string& TreatID, long pCompMode);


};

#endif /* _INC_CPDH_HM_RES_INCLUDED */

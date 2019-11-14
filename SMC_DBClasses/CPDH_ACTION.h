//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPDH_ACTION_INCLUDED
#define _INC_CPDH_ACTION_INCLUDED

#include "CSMC_DBData.h"

class CPDH_ACTION
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
  static const std::string ACTIONNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCEHEATANNOUNCEMENT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCESTARTOFHEAT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIONNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIONUNIT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIONVALUE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ACTIONSTATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REVTIME;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_ACTION(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_ACTION(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPDH_ACTION();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPDH_ACTION();

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
  long getACTIONNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIONNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDURSINCEHEATANNOUNCEMENT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCEHEATANNOUNCEMENT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  double getDURSINCESTARTOFHEAT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCESTARTOFHEAT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getACTIONNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIONNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getACTIONUNIT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIONUNIT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getACTIONVALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIONVALUE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getACTIONSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setACTIONSTATUS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CDateTime getREVTIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREVTIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long ACTIONNO);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool doAnnouncement(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT);

  bool doCancelHeat(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT);

  bool doHeatDeparture(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT,long pDurSinceHeatStart,long pDurSinceHeatAnnounce);
  bool doHeatStart(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT,long pDurSinceHeatStart,long pDurSinceHeatAnnounce);
  bool doHeatEnd(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT,long pDurSinceHeatStart,long pDurSinceHeatAnnounce);
  bool insert_Deslagging(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long pDeslagStat,const std::string& pActionname,long pActionNo);
  bool select_L3Data(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT);
  bool select_HMStatus(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT);

};

#endif /* _INC_CPDH_ACTION_INCLUDED */
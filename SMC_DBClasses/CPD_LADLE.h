//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPD_LADLE_INCLUDED
#define _INC_CPD_LADLE_INCLUDED

#include "CSMC_DBData.h"

class CPD_LADLE
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLETYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TAREWEIGHT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SCULLMASS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string THERMALSTATUS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESLAGGED;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DURSINCELASTUSE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LAST_TREATMENT_STATION;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLE_CIRCULATION_TIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LAST_FILL_TIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LAST_EMPTY_TIME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STATUSNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LADLEPOSID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRETREAT_CNT_ACT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PRETREAT_CNT_PREV;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HOTMETAL_CNT_ACT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HOTMETAL_CNT_PREV;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string FREEBOARD;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_LADLE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_LADLE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_LADLE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPD_LADLE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unique ladle number
  long getLADLENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##e.g. Hot Metal -> H, Teeming -> T
  std::string getLADLETYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLETYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Eng. Unit : kg, Tare weight of the ladle
  double getTAREWEIGHT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTAREWEIGHT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Eng. Unit : kg, Mass of ladle scull
  double getSCULLMASS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSCULLMASS(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##H=Hot, M=Medium, C=Cold
  std::string getTHERMALSTATUS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTHERMALSTATUS(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##1 = Deslagged, 0 = Not deslagged, -1 = Not known
  long getDESLAGGED(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESLAGGED(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Set in melting units and is calculated with tapping end (teeming/pre-metal ladles) or, with filling end (hot metal ladles). This duration shows the time the ladle was empty (cooling down time).
  double getDURSINCELASTUSE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDURSINCELASTUSE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Route Plant id of Last treatment station
  std::string getLAST_TREATMENT_STATION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLAST_TREATMENT_STATION(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##This duration corresponds to the LAST_FILL_TIME and gives the duration from previous tapping to current tapping of the ladle.
  double getLADLE_CIRCULATION_TIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLE_CIRCULATION_TIME(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Last time filling time with hot metal in case of HM ladle., Tapping end time in case of teeming or pre-metal ladles.
  CDateTime getLAST_FILL_TIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLAST_FILL_TIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Discharge end time in case of liquid addition or pouring end time from Caster in case of teeming.
  CDateTime getLAST_EMPTY_TIME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLAST_EMPTY_TIME(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Defined in GC_LADLE_STATUS
  long getSTATUSNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTATUSNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Valid ladle position as defined in GC_LADLE_POS
  long getLADLEPOSID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLADLEPOSID(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Treatment data for the actual treatment in the ladle
  long getPRETREAT_CNT_ACT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRETREAT_CNT_ACT(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Treatment data for the previous treatment in the ladle
  long getPRETREAT_CNT_PREV(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPRETREAT_CNT_PREV(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unique counter
  long getHOTMETAL_CNT_ACT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHOTMETAL_CNT_ACT(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unique counter
  long getHOTMETAL_CNT_PREV(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHOTMETAL_CNT_PREV(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Actual freeboard of the ladle
  long getFREEBOARD(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setFREEBOARD(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long LADLENO, const std::string& LADLETYPE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectbySpecifiedColumn(const std::string& ColumnName, long Value);

  bool doAnnouncement(long LADLENO, const std::string& LADLETYPE, std::string LadleState, double SteelMass, double SlagMass, long PretreatCounter, bool Commit, cCBS_ODBC_DBError &Error);

  bool doDeparture(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long &LadleNo, std::string &LadleType, long LadleLocation, bool Commit, cCBS_ODBC_DBError &Error);

  bool doTappingEnd(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long &LadleNo, std::string &LadleType, long LadleLocation, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(long LADLENO, const std::string& LADLETYPE);

  bool exists(long PRETREAT_CNT);

  std::string getThermalStatus(long LADLENO, const std::string& LADLETYPE, cCBS_ODBC_DBError &Error);

  bool switchHotMetalCounter(long LADLENO, const std::string& LADLETYPE, long HOTMETAL_CNT_ACT , bool Commit, cCBS_ODBC_DBError &Error);

  bool switchPretreatmentCounter(long LADLENO, const std::string& LADLETYPE, long PRETREAT_CNT_ACT , bool Commit, cCBS_ODBC_DBError &Error);

  bool updateHotMetalCounter(long LADLENO, const string& LADLETYPE, long HOTMETAL_CNT_ACT, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateLocation(long LADLENO, const std::string& LADLETYPE, long Location, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateStatusNo(long LADLENO, const std::string& LADLETYPE, long StatusNo, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateTermalStatus(long LADLENO, const std::string& LADLETYPE, const std::string &THERMALSTATUS, bool Commit, cCBS_ODBC_DBError &Error);

  bool updateTimes(long LADLENO, const std::string& LADLETYPE, const CDateTime& NewFillTime, bool Commit, cCBS_ODBC_DBError &Error);

};

#endif /* _INC_CPD_LADLE_INCLUDED */

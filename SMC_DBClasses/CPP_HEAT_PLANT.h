//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPP_HEAT_PLANT_INCLUDED
#define _INC_CPP_HEAT_PLANT_INCLUDED

#include <vector>
#include "CSMC_DBData.h"

class CPP_HEAT_PLANT
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
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string HEATID_CUST_PLAN;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATID_CUST_PLAN;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATSTART_PLAN;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string TREATEND_PLAN;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPP_HEAT_PLANT(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPP_HEAT_PLANT(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPP_HEAT_PLANT();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPP_HEAT_PLANT();

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
  //##Plant number
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Generated, if not fixed by L3
  std::string getHEATID_CUST_PLAN(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHEATID_CUST_PLAN(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Treatment planned by L3
  std::string getTREATID_CUST_PLAN(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATID_CUST_PLAN(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Planned start time at unit
  CDateTime getTREATSTART_PLAN(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATSTART_PLAN(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Planed end time at unit
  CDateTime getTREATEND_PLAN(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setTREATEND_PLAN(const CDateTime& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByCustData(const std::string& HEATID_CUST_PLAN, const std::string& TREATID_CUST_PLAN, const std::string& PLANT, bool ASC = true);

  bool selectByCustHeatAndPlanningState(const std::string& HEATID_CUST_PLAN, const std::string& TREATID_CUST_PLAN, long PLANNED);

  bool selectByHeatData(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool ASC = true);

  bool selectByHeatPlantData(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, long PLANTNO);

  bool selectByPlanningState(const std::string& PLANT, long PLANTNO, long PLANNED);

  bool selectByPlanningState(const std::string& PLANT, long PLANTNO, long PLANNED, bool OrderByHeatIdCustPlan);

  bool selectByPlanningStateAndPreset(const std::string& PLANT, long PLANTNO, long PLANNED, long PRESET_HEATID);

  bool selectByPlanningStateAndPreset(const std::string& PLANT, long PLANTNO, long PLANNED, long PRESET_HEATID, bool OrderByHeatIdCustPlan);

  bool selectByPlantData(const std::string& PLANT, long PLANTNO);

  bool selectCanFillBasketOrderSerils(const std::string& BeginHeat,const std::string &Plant );

  bool selectNextHeatsForPlant(const std::string& PLANT, long PLANTNO);

  bool selectOrderedByMaxTreatID(const std::string& HEATID, const std::string& PLANT);

  bool selectOrderedByMaxTreatIDCustPlan(const std::string& HEATID_CUST_PLAN, const std::string& PLANT);

  bool selectOrderedByPlannedTreatmentStart(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT, bool asc);

  bool selectOrderedByPlantData(const std::string& PLANT, long PLANTNO, bool asc);

  bool deleteOneRow( std::string& HEATID_CUST_PLAN, std::string& TREATID_CUST_PLAN, const std::string& PLANT);

  bool deleteRow(const std::string &HEATID, const std::string &TREATID, const std::string &PLANT, bool Commit, cCBS_ODBC_DBError &Error);

  bool deleteRowsbyHeatID(const std::string& HEATID );

  bool deleteRowsbyPlant(const std::string& HEATID,const std::string &PLANT );

  bool doCancelHeat(const std::string& HeatId, const std::string& TreatId, const std::string& Plant, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(const std::string& HEATID, const std::string& TREATID, const std::string& PLANT);

  bool exists(const std::string& HEATID_CUST_PLAN);

  std::string getLastCustHeatInProduction(const std::string& PLANT, long PLANTNO);

  bool isCustHeatInProduction(const std::string& HEATID_CUST_PLAN, const std::string& TREATID_CUST_PLAN, const std::string& PLANT);

  bool isCustHeatPlanned(const std::string& HEATID_CUST_PLAN, const std::string& TREATID_CUST_PLAN);

  bool resetCustHeatId(std::vector<long> &SeqParam, const std::string & Year, std::vector<std::string> &PlantList, long ReturnHeatNo,bool Commit, cCBS_ODBC_DBError &Error);

  bool updateInsertPP(const std::string &HEATID, std::string &TREATID, const std::string &PLANT, const long PLANTNO, const std::string &HEATID_CUST_PLAN, const std::string &TREATID_CUST_PLAN, const CDateTime &TREATSTART_PLAN, const CDateTime &TREATEND_PLAN, bool Commit, cCBS_ODBC_DBError &Error);

};

#endif /* _INC_CPP_HEAT_PLANT_INCLUDED */

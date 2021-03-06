//## Copyright (C) 2013 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHDH_EQUIP_COUNTER_INCLUDED
#define _INC_CHDH_EQUIP_COUNTER_INCLUDED

#include "CSMC_DBData.h"

class CHDH_EQUIP_COUNTER
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
  static const std::string EQUIP_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string EQUIP_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COUNTER_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string COUNTER_VALUE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_EQUIP_COUNTER(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_EQUIP_COUNTER(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHDH_EQUIP_COUNTER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHDH_EQUIP_COUNTER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Internal heat identifier
  std::string getHM_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setHM_ID(const std::string& value);

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
  //##Equipment Id
  long getEQUIP_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setEQUIP_ID(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Equipment type 
  std::string getEQUIP_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setEQUIP_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Counter type used for equipment tracking
  std::string getCOUNTER_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOUNTER_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Value for this counter
  double getCOUNTER_VALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCOUNTER_VALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& HM_ID, const std::string& TREATID, const std::string& PLANT, long EQUIP_ID, const std::string& EQUIP_TYPE, const std::string& COUNTER_TYPE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 
	bool updateOrInsert(const std::string &HM_ID, const std::string &TREATID, const std::string &PLANT, long EQUIP_ID, const std::string& EQUIP_TYPE,const std::string& COUNTER_TYPE,double VALUE, bool Commit,cCBS_ODBC_DBError &Error);
};

#endif /* _INC_CHDH_EQUIP_COUNTER_INCLUDED */

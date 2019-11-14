//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGD_EQUIP_TYPE_INCLUDED
#define _INC_CGD_EQUIP_TYPE_INCLUDED

#include "CSMC_DBData.h"

class CGD_EQUIP_TYPE
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string EQUIP_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INTERNAL_EQUIP_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DESCRIPTION;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INCIDENTAL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string REPLACEABLE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_TYPE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_TYPE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGD_EQUIP_TYPE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##External equipment type e.g. segment1, burner1, a customer specific name for terms defined in the table GD_INTERNAL_EQUIP_TYPE
  std::string getEQUIP_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setEQUIP_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Internal equipment type, ie. the corresponding type used in Tracking for a heat or slab location. E.g.: mould, segment. Normally it is less specific then EQUIP_TYPE. Null values indicate that this equipment is not heat location of its own right.
  std::string getINTERNAL_EQUIP_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINTERNAL_EQUIP_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Description of equipment type
  std::string getDESCRIPTION(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDESCRIPTION(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##This equipment type is part of incidentals (can be exchanged on the fly and has no customer specific id)
  long getINCIDENTAL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINCIDENTAL(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##eq. can be replaced in the course of normal operation or maintanance
  long getREPLACEABLE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setREPLACEABLE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& EQUIP_TYPE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 
	bool InsertData(const std::string &EQUIP_TYPE, const std::string &INTERNAL_EQUIP_TYPE, const std::string &DESCRIPTION, long INCIDENTAL, long REPLACEABLE,bool Commit, cCBS_ODBC_DBError &Error);
};

#endif /* _INC_CGD_EQUIP_TYPE_INCLUDED */
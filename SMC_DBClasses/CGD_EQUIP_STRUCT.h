//## Copyright (C) 2011 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGD_EQUIP_STRUCT_INCLUDED
#define _INC_CGD_EQUIP_STRUCT_INCLUDED

#include "CSMC_DBData.h"

class CGD_EQUIP_STRUCT
: public CSMC_DBData

{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STRUCT_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string EQUIP_TYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STRUCT_SUB_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string ORDER_IN_LEVEL;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PARENT_ID;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STRUCT_NAME;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_STRUCT(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_STRUCT(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGD_EQUIP_STRUCT();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGD_EQUIP_STRUCT();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Identification of structure element
  long getSTRUCT_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTRUCT_ID(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Equipment type of structure element
  std::string getEQUIP_TYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setEQUIP_TYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Sub Id of structure element
  std::string getSTRUCT_SUB_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTRUCT_SUB_ID(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Order of structure element related to hierarchy level
  long getORDER_IN_LEVEL(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setORDER_IN_LEVEL(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Parent id of structure element
  long getPARENT_ID(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPARENT_ID(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Name of this equipment in tree
  std::string getSTRUCT_NAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTRUCT_NAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long STRUCT_ID);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  // selects all data on same level 
  bool selectByEquipType(const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID);

  // selects all data and its complete child tree starting from EQUIP_TYPE and STRUCT_SUB_ID
  bool selectStructTreeByEquipType(const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID);

  // returns vector of struct_ids under a parental struct id
  // e.g. returns struct id of Electode 2 of Plant EAF 1 where
  // EQUIP_TYPE_PARENT = EAF, STRUCT_SUB_ID_PARENT = 1, EQUIP_TYPE = "Electrodes", STRUCT_SUB_ID = 2
  std::vector<long> getStructIdListOfParentId(const std::string& EQUIP_TYPE_PARENT, const std::string& STRUCT_SUB_ID_PARENT, const std::string& EQUIP_TYPE, const std::string& STRUCT_SUB_ID);

	//sankar
	bool InsertData(long STRUCT_ID,const std::string &EQUIP_TYPE, const std::string &STRUCT_SUB_ID, long ORDER_IN_LEVEL,long PARENT_ID,const std::string &STRUCT_NAME, bool Commit, cCBS_ODBC_DBError &Error);
	long GetMaxSTRUCT_ID();
};

#endif /* _INC_CGD_EQUIP_STRUCT_INCLUDED */

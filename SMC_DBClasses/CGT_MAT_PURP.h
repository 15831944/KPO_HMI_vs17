//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGT_MAT_PURP_INCLUDED
#define _INC_CGT_MAT_PURP_INCLUDED

#include "CSMC_DBData.h"

class CGT_MAT_PURP
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string UNITGROUPNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAT_CODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PURP_CODE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_MAT_PURP(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_MAT_PURP(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGT_MAT_PURP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGT_MAT_PURP();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unit group number, see GC_PLANT_GROUP
  long getUNITGROUPNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setUNITGROUPNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Material code
  std::string getMAT_CODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAT_CODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Purpose code
  std::string getPURP_CODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPURP_CODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long UNITGROUPNO, const std::string& MAT_CODE, const std::string& PURP_CODE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectAllMaterialsBySpecPurpose(const std::string& PURP_CODE);

  bool selectByPlant(const std::string& PLANT, long PLANTNO, const std::string& MAT_CODE, const std::string& PURP_CODE);

  bool deleteRow(const std::string& PLANT, long PLANTNO, const std::string& Mat_Code, const std::string& Purp_Code);

  bool deleteRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code);

  bool deleteRows(long UNITGROUPNO, std::vector<std::string> Exclude_Mat_Codes, const std::string& Purp_Code);

  std::string getRelatedMatCode(long UNITGROUPNO, const std::string& PURP_CODE);

  std::vector<std::string> getRelatedMatCodes(const std::string& PLANT, long PLANTNO, const std::string& PURP_CODE);

  std::vector<long> getUnitGroupList(const std::string& Plant, long PlantNo);

  // to be backward compatible
  bool insertRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code);

  bool insertRow(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error);

  bool insertRow(const std::string& PLANT, long PLANTNO, const std::string& Mat_Code, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error);

  bool insertRows(const std::string& PLANT, long PLANTNO, std::vector<std::string> Mat_Codes, const std::string& Purp_Code, bool Commit, cCBS_ODBC_DBError &Error);

  bool insertOrReplace(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code);

  bool deleteOnExist(long UNITGROUPNO, const std::string& Mat_Code, const std::string& Purp_Code);

	bool mergePurposeCodes(const std::string& PLANT, long PLANTNO, const std::string& From_Purp_Code_1, const std::string& From_Purp_Code_2, const std::string& To_Purp_Code); //SRKO

};

#endif /* _INC_CGT_MAT_PURP_INCLUDED */

//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPD_SCRAP_CONTAINER_ENTRY_INCLUDED
#define _INC_CPD_SCRAP_CONTAINER_ENTRY_INCLUDED

#include "CSMC_DBData.h"

class CPD_SCRAP_CONTAINER_ENTRY
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string CONTAINERTYPE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MATCHARGESEQ;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAT_CODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MATWEIGHT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MATWEIGHT_CHARGED;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ENTRY(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ENTRY(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_SCRAP_CONTAINER_ENTRY();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPD_SCRAP_CONTAINER_ENTRY();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Unique identification number
  long getCONTAINERNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##basket or chute
  std::string getCONTAINERTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setCONTAINERTYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Charging sequence for the materials in the container
  long getMATCHARGESEQ(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMATCHARGESEQ(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getMAT_CODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAT_CODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Actual weight
  double getMATWEIGHT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMATWEIGHT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##If material is charged the attribute is filled with copy of .MATWEIGHT., MATWEIGHT is set to 0. In case of wrong assignment of ContainerID,, the previous materials can be restored in container by copy from MATWEIGHT_CHARGED to MATWEIGHT., MATWEIGHT_CHARGED must be cleared during new assignement.
  double getMATWEIGHT_CHARGED(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMATWEIGHT_CHARGED(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long CONTAINERNO, const std::string& CONTAINERTYPE, long MATCHARGESEQ);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByMatCode(long CONTAINERNO, const std::string& CONTAINERTYPE, const std::string& MAT_CODE);

  bool deleteRow(long CONTAINERNO, const std::string& CONTAINERTYPE, long MATCHARGESEQ);

  bool updateOnDischarge(long CONTAINERNO, const std::string& CONTAINERTYPE);

};

#endif /* _INC_CPD_SCRAP_CONTAINER_ENTRY_INCLUDED */

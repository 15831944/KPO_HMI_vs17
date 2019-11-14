//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGCE_BURNER_INCLUDED
#define _INC_CGCE_BURNER_INCLUDED

#include "cCBS_ResultSet.h"
#include "CSMC_DBData.h"

class CGCE_BURNER
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string BURNERNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string BURNERDESCR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string L1_BURNERNO;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_BURNER(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_BURNER(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_BURNER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGCE_BURNER();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getBURNERNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setBURNERNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getBURNERDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setBURNERDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getL1_BURNERNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setL1_BURNERNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, long PLANTNO, const std::string& BURNERNAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByL1BurnerNo(const std::string& PLANT, long PLANTNO, long L1_BURNERNO);

  std::vector<std::string> getBurnerList(const std::string& PLANT, long PLANTNO);

  std::string getBurnerNameByPlant(const std::string& PLANT, long PLANTNO, long L1_BURNERNO);

  long getBurnerNoByPlant(const std::string& PLANT, long PLANTNO, const std::string& BURNERNAME);

};

#endif /* _INC_CGCE_BURNER_INCLUDED */

//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHD_SAMPLE_ENTRY_INCLUDED
#define _INC_CHD_SAMPLE_ENTRY_INCLUDED

#include <vector>
#include "CSMC_DBData.h"

class CHD_SAMPLE_ENTRY
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SAMPLE_COUNTER;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MEASNAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MEASVALUE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_SAMPLE_ENTRY(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_SAMPLE_ENTRY(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CHD_SAMPLE_ENTRY();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CHD_SAMPLE_ENTRY();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##SAMPLE_COUNTER is the primary key
  long getSAMPLE_COUNTER(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSAMPLE_COUNTER(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Measured Element/compound concentration in case of analysis, otherwise the type name
  std::string getMEASNAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMEASNAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Measured value
  double getMEASVALUE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMEASVALUE(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long SAMPLE_COUNTER, const std::string& MEASNAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool copy(long pSampleCount, bool Commit, cCBS_ODBC_DBError &Error);

  bool copy(std::vector<long> &SampleCounterList, bool Commit, cCBS_ODBC_DBError &Error);

  std::string ArrayToString(std::vector<long> &pArray);

  bool deleteRows(long pSampleCount, bool Commit, cCBS_ODBC_DBError &Error);

  bool deleteRows(std::vector<long> &SampleCounterList, bool Commit, cCBS_ODBC_DBError &Error);

  bool exists(long SAMPLE_COUNTER);

  bool exists(std::vector<long> &SampleCounterList);

};

#endif /* _INC_CHD_SAMPLE_ENTRY_INCLUDED */

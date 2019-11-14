//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPD_MAT_AVAIL_INCLUDED
#define _INC_CPD_MAT_AVAIL_INCLUDED

#include "CSMC_DBData.h"

class CPD_MAT_AVAIL
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string SOURCE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LOCATIONNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MAT_CODE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string AVAILWGT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string MINWEIGHT;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_MAT_AVAIL(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_MAT_AVAIL(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CPD_MAT_AVAIL();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CPD_MAT_AVAIL();

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
  std::string getSOURCE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSOURCE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##LOCATION identifies the material location within the SOURCE:, bunker number if SOURCE = Bin,, strand number if SOURCE= Wire, etc.
  long getLOCATIONNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLOCATIONNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Material code
  std::string getMAT_CODE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMAT_CODE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Available material weight of each material code (per source and per location)
  double getAVAILWGT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setAVAILWGT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Minimum charge weight according to Level 1 Information. Iindicates the minimum chargeable weight due to physical restrictions of the bin/weighing system. See also MINWEIGHT in GT_MAT. The maximum of these weigths is to be used.
  double getMINWEIGHT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setMINWEIGHT(double value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATIONNO, const std::string& MAT_CODE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 
  bool selectAvailableLocation(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATIONNO, const std::string& MAT_CODE);

  bool deleteRow(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATION_NO, const std::string& MAT_CODE);

  bool exists( const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATION_NO, const std::string& MAT_CODE );

  double getMinWeightOfMatCode(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATIONNO, const std::string& MAT_CODE);

  bool updateOrInsertRow(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATION_NO, const std::string& MAT_CODE, double AVAILWGT);

  bool updateOrInsertRowForMinWeight(const std::string& PLANT, long PLANTNO, const std::string& SOURCE, long LOCATION_NO, const std::string& MAT_CODE, double AVAILWGT, double MINWEIGHT);

};

#endif /* _INC_CPD_MAT_AVAIL_INCLUDED */

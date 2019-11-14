//## Copyright (C) 2010 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGCE_INJECTION_INCLUDED
#define _INC_CGCE_INJECTION_INCLUDED

#include "CSMC_DBData.h"

class CGCE_INJECTION
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANT;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string PLANTNO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DEVICENAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string DEVICEDESCR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string L1_DEVICENO;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INJTYPE;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_INJECTION(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_INJECTION(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGCE_INJECTION();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGCE_INJECTION();

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getPLANT(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANT(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getPLANTNO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setPLANTNO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDEVICENAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDEVICENAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getDEVICEDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setDEVICEDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  long getL1_DEVICENO(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setL1_DEVICENO(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  std::string getINJTYPE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINJTYPE(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& PLANT, long PLANTNO, const std::string& DEVICENAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

  bool selectByL1InjectorNo(const std::string& PLANT, long PLANTNO, long L1_DEVICENO, const std::string& INJTYPE);

  std::string getDeviceNameByL1InjectorNo(const std::string& PLANT, long PLANTNO, long L1_DEVICENO, const std::string& INJTYPE);

  std::map < std::string, long > &  getDeviceNameList(const std::string& PLANT,long PlantNo, const std::string& INJTYPE);

  std::map < std::string, std::string > &  getInjTypeList(const std::string& PLANT, long PLANTNO);

  long getL1DeviceNo(const std::string& PLANT,long PLANTNO, const std::string& DEVICENAME);

  std::map < long, std::string> & getL1DeviceNoList(const std::string& PLANT,long PlantNo, const std::string& INJTYPE);

};

#endif /* _INC_CGCE_INJECTION_INCLUDED */

//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_ACTIVATION_CHILD_OBJECTS_INCLUDED
#define _INC_CGC_ACTIVATION_CHILD_OBJECTS_INCLUDED

#include "CSMC_DBData.h"

class CGC_ACTIVATION_CHILD_OBJECTS
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string OBJECT_CHILD_NAME;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string OBJECT_CHILD_DESC;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_ACTIVATION_CHILD_OBJECTS(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_ACTIVATION_CHILD_OBJECTS(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_ACTIVATION_CHILD_OBJECTS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_ACTIVATION_CHILD_OBJECTS();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Item of defined object: e.g. OBJECT_NAME = BOFProduction, OBJECT_CHILD_NAME: HeatAnnouncement or NewHeat
  std::string getOBJECT_CHILD_NAME(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setOBJECT_CHILD_NAME(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Option: Description of child object
  std::string getOBJECT_CHILD_DESC(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setOBJECT_CHILD_DESC(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(const std::string& OBJECT_CHILD_NAME);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_ACTIVATION_CHILD_OBJECTS_INCLUDED */

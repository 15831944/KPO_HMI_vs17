//## Copyright (C) 2009 SMS Siemag AG, Germany 
//## Version generated by DBClassCodeUtility BETA 0.6.3 
//## ALL METHODS MARKED AS - //##DBClassCodeUtility - WILL BE OVERWRITTEN, IF DB CLASS RE-GENERATED 
//## MANUALLY IMPLEMENTED METHODS MUST BE LOCATED BELOW THE MARK - "YOUR-CODE" - 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CGC_GRAPH_LINESTYLE_INCLUDED
#define _INC_CGC_GRAPH_LINESTYLE_INCLUDED

#include "CSMC_DBData.h"

class CGC_GRAPH_LINESTYLE
: public CSMC_DBData
{

public:
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LINESTYLE;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string LINEDESCR;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string WIDTH;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string STAIRS;
  //##DBClassCodeUtility ! DO NOT EDIT !
  static const std::string INVERTED;

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_GRAPH_LINESTYLE(cCBS_StdConnection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_GRAPH_LINESTYLE(cCBS_Connection* Connection);

  //##DBClassCodeUtility ! DO NOT EDIT !
  CGC_GRAPH_LINESTYLE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  ~CGC_GRAPH_LINESTYLE();

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Line style identification
  long getLINESTYLE(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLINESTYLE(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Line style description
  std::string getLINEDESCR(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setLINEDESCR(const std::string& value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Line widht in points, -1 for no line displayed
  long getWIDTH(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setWIDTH(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Flag for show stairs on line (0 - linear dot to dot, 1 - rectangular left up
  long getSTAIRS(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setSTAIRS(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  //##Flag for show inverted stairs (0 - rectangular left up, 1 - rectangular right up )
  long getINVERTED(long Row);

  //##DBClassCodeUtility ! DO NOT EDIT !
  void setINVERTED(long value);

  //##DBClassCodeUtility ! DO NOT EDIT !
  bool select(long LINESTYLE);

  //## ----------------------------------END-GENERATED-CODE--------------------- 

  //## ----------------------------------YOUR-CODE------------------------------ 

};

#endif /* _INC_CGC_GRAPH_LINESTYLE_INCLUDED */

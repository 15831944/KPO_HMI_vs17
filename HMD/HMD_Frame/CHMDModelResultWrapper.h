// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMDModelResultWrapper_4118CC3401F4_INCLUDED
#define _INC_CHMDModelResultWrapper_4118CC3401F4_INCLUDED

#include "CHMDModelTask.h"
#include "CHMDModelWrapper.h"

#include "CEventMessage.h"
#include "cCBS_Connection.h"
#include "cCBS_DBExc.h"
#include "CHD_RESTRI_ENTRY.h"
#include "CGT_PARAM.h"
#include "CHD_PARAM.h"
//#include "CGTA_MI_P_MAIN_BLOW.h"
//#include "CGTA_MI_P_DYN_DECARB.h"
//#include "CGTA_MI_P_POST_DECARB.h"
#include "CGC_Phase.h"
#include "CGC_Restri_Def.h"
#include "CGC_Recipe_Source.h"
#include "CPP_HEAT_PLANT.h"
#include "CHD_GRADE_ANL.h"
//#include "CPD_BIN.h"
#include "CPD_LADLE.h"
//#include "CPD_LADLE_DATA.h"
//#include "CPD_LADLE_ANL.h"
#include "CPD_HEAT_DATA_PRODPRAC.h"
//#include "CPD_HEATDATA.h"
#include "CPDH_HM_DATA.h" //or CHDH_HM_DATA??? Kubbe


//#include "CPD_HEATDATA_LIQADD.h"
//#include "CPD_HEATDATA_LIQADD_ANL.h"
//#include "CPD_HOTHEEL.h"
//#include "CPD_HOTHEEL_ANL_ENTRY.h"
//#include "CPDA_CHUTE_HEAT.h"
//#include "CPDA_CHUTE_ENTRY_HEAT.h"
//#include "CGC_COMBI_RECIPES_SOURCE.h"
#include "CChem_Elem_Container.h"


class CIntfHMD;
class CHMDModelTask;

//##ModelId=4118CC3401F4
class CHMDModelResultWrapper : public CHMDModelWrapper
{

public:
  //##ModelId=4124B120022C
  CHMDModelResultWrapper();

  //##ModelId=4124B121004D
  virtual ~CHMDModelResultWrapper(); 

  //##ModelId=4118CDE2024D
  bool doModelResult(CEventMessage &Event);

  //##ModelId=4135CB690333
  bool doResultCodeAndMessage(CEventMessage &Event);

  //##ModelId=4119D83500CF
  bool doModelActualSetpoints(CEventMessage &Event);

  //##ModelId=4135CB6601ED
  bool doMatRecipeSetpoints(CEventMessage &Event);
};

#endif /* _INC_CHMDModelResultWrapper_4118CC3401F4_INCLUDED */

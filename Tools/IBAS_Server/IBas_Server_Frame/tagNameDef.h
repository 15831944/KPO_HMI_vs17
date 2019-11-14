#ifndef _TagNameDef_h_
#define _TagNameDef_h_

#include "..\ExtInterfaceLib\basTagNameDef.h"

//#include "l2events.h"

#include "..\ApplicationLib\cApp_tagName.h"
#include "..\ApplicationLib\cApp_Event.h"
#include <string>

namespace L2TAG
{
  static cApp_Event Ev_NewMoldTaperValue( EV_COPT_NEWMOULDTAPERVALUE, EV_COPT_NEWMOULDTAPERVALUE_2 );
  static cApp_Event Ev_NewMarkingSetpoint( EV_MST_NEW_MARKING_SETPOINT, EV_MST_NEW_MARKING_SETPOINT_2 );
};


#endif 

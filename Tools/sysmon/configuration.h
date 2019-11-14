//---------------------------------------------------------------------------- 
// 
//                           S M S  D e m a g  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : Caster Computer 
// filename      : configuration.h 
// author        : Waldheim	
// department    : EAM1
// creation date : 09-16-2003 
// description   : project wide general configurations as far as hard-wired
// 
//---------------------------------------------------------------------------- 
// 
// change notes: 
// 
// version  dd-mm-yyyy author       remarks 
// 1.0      09-09-2003 Waldheim     original edit 
// 1.1      28-09-2005 Hautzer      init for daylight saving time
// 
//---------------------------------------------------------------------------- 

#ifndef _configuration_h_
#define _configuration_h_

#include "cCBS_Corba.h"
                       
static cCBS_Corba corbaMode ( cCBS_Corba::CATCH_CORBA_SYSTEM_EXCEPTIONS | 
                              cCBS_Corba::RETHROW_CORBA_SYSTEM_AS_CBS_EXCEPTION |
								              cCBS_Corba::USE_CORBA_NAME_SERVICE |
								              cCBS_Corba::AUTO_REBIND );

#endif 
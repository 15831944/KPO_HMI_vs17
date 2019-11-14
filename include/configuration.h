//---------------------------------------------------------------------------- 
// 
//                           S M S  D e m a g  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : Meltshop Computer 
// filename      : configuration.h 
// author        : Terhorst	
// department    : EAM4
// creation date : 07-11-2011 
// description   : project wide general configurations as far as hard-wired
// 
//---------------------------------------------------------------------------- 



#ifndef _configuration_h_
#define _configuration_h_

#include "cCBS_DB.h"
#include "cCBS_Corba.h"
#include "cApp_DSTMode.h"

#ifndef _SMC_
#define _SMC_

#include "cCBS_DB.h"
#include "cCBS_Corba.h"

static cCBS_Corba corbaMode ( cCBS_Corba::CATCH_CORBA_SYSTEM_EXCEPTIONS | 
                              cCBS_Corba::RETHROW_CORBA_SYSTEM_AS_CBS_EXCEPTION |
								              cCBS_Corba::USE_CORBA_NAME_SERVICE |
								              cCBS_Corba::AUTO_REBIND );

static cCBS_DB dbMode( cCBS_DB::CREATE_CBS_DB_EXCEPTION | 
  cCBS_DB::ODBC_DRIVER |
  cCBS_DB::AUTO_RECONNECT ); 
  
static cApp_DSTMode dstMode (cApp_DSTMode::DAYLIGHT_SAVING_TIME_DISABLED);


#endif 
#endif
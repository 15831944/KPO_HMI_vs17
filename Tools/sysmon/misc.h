// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : TrackingLib
//  filename      : 
//  originator    : Josef Curda
//  department    : PIKE Electronic
//  creation date : 12-May-2004
//  description   : 
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy author  remarks
//  1.0      DD-MMM-YYYY         First Version
// 
// ----------------------------------------------------------------------------

#ifndef __MISC_H
#define __MISC_H

#define _CLOG9
#include "CBS_Utilities/CBS_Clog.h"
#include "CBS_StdAPI/cCBS_StdTestLog_Proxy.h"

//Extern channels for logging
extern cCBS_StdTestLog_Proxy* g_log;

//Severity levels
#define DBG_RUN
#define DBG_INFO
#define DBG_MSG
#define DBG_SUCC
#define DBG_ERR

//Macro for debug messages
#define LOG_(severity, msg) CLOG##severity( << ##msg << std::endl );
#define ERR_(msg) CLOG1( << ##msg << std::endl );
//#define MLOG_ ::m_log->logfNl

//Return codes
#define RC_OK		0
#define RC_ERROR	-1

#endif

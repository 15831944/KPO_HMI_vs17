//---------------------------------------------------------------------------- 
// 
//                           S M S  S I E M A G  A G 
// 
//                            All Rights Reserved 
// 
// 
// project       : Email Server 
// filename      : cEmailServer_EventHandlerTask.h
// author        :Sankar Sarkar
// department    : EAM4
// creation date : 06-JUL-2010 
// description   : header file for cEmailServer_EventHandlerTask.cpp; description see there.
// 
//---------------------------------------------------------------------------- 

#ifndef _INC_cEmailServerEventHdlTask_INCLUDED
#define _INC_cEmailServerEventHdlTask_INCLUDED


#include "cCBS_StdEventHdlTask.h"
#include <CBS_Utilities/cCBS_ConfigBase.h>
#include <gcroot.h>
//#include "emails_cParam.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
//using namespace SMSSiemag::XPact::HMI::XPactCore::Utils::SQLOracle;
//using namespace SMSSiemag::XPact::HMI::XPactCore::Utils::SQL;
using namespace SMSSiemag::XPact::HMI::XPactCore::Utils;
using namespace SMSSiemag::XPact::HMI::XPactCore::Utils;
#pragma warning (default: 4311 4312 4267)


class cEmailServerEventHdlTask : public cCBS_StdEventHdlTask
{
public:
  cEmailServerEventHdlTask ( const char * channelName, const char * serviceName);	
  virtual ~cEmailServerEventHdlTask(void);   
  cCBS_ConfigBase * getCfb() { return m_cfb ; }; 
protected:
  virtual void ownStartUp();
  virtual void ownRunDown();
  virtual void handleEvent(const FRIESEvent& Event);
  virtual String^ GetEmailBody(String^ PlantName, String^ PlantNo);
  static std::string ConvertString(String^ s);
	static String^ ConvertString(const char* s);

  
private:
	cCBS_ConfigBase *m_cfb;
	static cEmailServerEventHdlTask * m_comp;	
    std::string m_IniFile; 
	//cCBS_Driver* m_DBDriver;
  //EMAILS::cParam::EmailParameter  * m_emailParam
};


#endif // _INC_cEmailServerEventHdlTask_INCLUDED

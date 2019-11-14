// Copyright (C) 2005 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTraceLogCleaner_Task_4253CDEE012D_INCLUDED
#define _INC_CTraceLogCleaner_Task_4253CDEE012D_INCLUDED


#include <string>

#include "cCBS_StdFrame_Task.h"
#include "CTraceLogCleaner_Controller.h"

class CTraceLogCleaner_Task 
: public cCBS_StdFrame_Task
{
public:

  static CTraceLogCleaner_Task* getInstance();

	virtual ~CTraceLogCleaner_Task();

   virtual void log(const std::string& Message, long Level = 1);

   std::vector<std::string> getSubDirs(const std::string& PathName);

protected:

	static CTraceLogCleaner_Task* m_Instance;

	CTraceLogCleaner_Task();

	//Virtual initialization method. Creates the task POA 
	//with the policies created by the createPolicies method 
	//and activates the task servant on this POA. Called by 
	//the activate method. Returns true on success.
	virtual bool initialize();

  std::vector<CTraceLogCleaner_Controller*> m_TraceLogCleaner_ControllerList;

};

#endif /* _INC_CTraceLogCleaner_Task_4253CDEE012D_INCLUDED */

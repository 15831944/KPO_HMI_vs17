// Copyright (C) 2009 SMS Demag AG Germany

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CProcess_Monitor_Check_Task_INCLUDED
#define _INC_CProcess_Monitor_Check_Task_INCLUDED

#include <string>
#include <iostream>
#include <set>
#include "cCBS_StdFrame_Task.h"
#include "cCBS_Thread.h"

class CProcess_Monitor_Check_Task 
  : public cCBS_StdFrame_Task, cCBS_Thread
{
private:
  static CProcess_Monitor_Check_Task* m_pInstance;

  // scan interval from ini file. default 20 sec
  long m_iScanInterval;

  //void log(const std::string& _message, long _level);
	
public:
	CProcess_Monitor_Check_Task();

	virtual ~CProcess_Monitor_Check_Task();

	virtual void getOwnStateDetails(CORBA::String_out details);

  static CProcess_Monitor_Check_Task* getInstance();

protected:
  // start control thread
  virtual void ownStartUp();

  // stop control thread
	virtual void ownRunDown();

  // go over all plants and try to get running state of the 
  // components registered for plant.
  // if component is not running or is not reachable
  // sendEvent function of CProcess_Monitor_Task is called.
	virtual void performWorkingStep();

private:
  std::map <std::string, bool> AvailabilityForPlant;
};
//-------------------------------------------------------------------------------------------------
#endif /* _INC_CProcess_Monitor_Check_Task_INCLUDED */

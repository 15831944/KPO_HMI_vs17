// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CHMD_MODEL_TASK_4110E43C02F8_INCLUDED
#define _INC_CHMD_MODEL_TASK_4110E43C02F8_INCLUDED

#include "iDM_Interface_s.hh"
#include "cCorbaProxyAdapter.h"
#include "CModelTask.h"
#include "cCBS_StdDB_Task.h"
#include "cCBS_DBExc.h"
#include "cCBS_DBExcODBC.h"

#include "CDateTime.h"
#include "CProxyManager.h"

class CHMDModelResultWrapper;
class CHMDModelWrapper;

class CEventMessage;

//##ModelId=4110E43C02F8
class CHMDModelTask
: public CModelTask
{
private:

  CHMDModelResultWrapper* m_pHMDModelResultWrapper;

  //##ModelId=4124B2550204
  static CHMDModelTask* Instance;

public:

  virtual bool callModelResultWrapper(const std::string& Type ,CEventMessage& Event);

  //##ModelId=4124B26E0215
  static CHMDModelTask* getInstance();

  //##ModelId=411120B001EC
  virtual ~CHMDModelTask();

protected:
  //##ModelId=411120B8025D
  CHMDModelTask( );
  

  //Virtual task start up method. Called by the 
  //runtimeStartUp method after starting up the subtasks. 
  //The default implementation sets only the state of the 
  //task to Running. Note that the work state is not set.
  //
  //This method may be redefined if the task represents for 
  //example a thread or a process. In this case, the method 
  //redefinition would start thread execution.
  //##ModelId=4110E48B0136
  virtual void ownStartUp();

  //Virtual task run down method. Called by the runDown 
  //method before stopping the subtasks. The default 
  //implementation sets only the state of the task to 
  //NotRunning. Note that the work state is not set.
  //
  //This method may be redefined if the task represents for 
  //example a thread or a process. In this case, the method 
  //redefinition would stop thread execution.
  //##ModelId=4110E48D014F
  virtual void ownRunDown();

  //Virtual initialization method. Creates the task POA 
  //with the policies created by the createPolicies method 
  //and activates the task servant on this POA. Called by 
  //the activate method. Returns true on success.
  //##ModelId=4110E49900E7
  virtual bool initialize();

};

#endif /* _INC_CHMD_MODEL_TASK_4110E43C02F8_INCLUDED */

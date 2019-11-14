// Copyright (C) 1999 - 2004 SMS Demag AG

#include "cCBS_StdFrame_Task.h"
#include "cCBS_StdFrame_TaskController.h"


//##ModelId=48A549AD01A2
cCBS_StdFrame_TaskController::~cCBS_StdFrame_TaskController()
{
	if ( m_pTask )
  {
    m_pTask->uncontrol();
  }
}

//call with LifeTime in msecs
//##ModelId=48A549AE00E5
cCBS_StdFrame_TaskController::cCBS_StdFrame_TaskController( cCBS_StdFrame_Task* pTask)
: m_pTask(pTask)
{
	if ( m_pTask )
  {
    m_pTask->control();
  }
}



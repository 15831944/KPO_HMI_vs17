// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCBS_STDFRAME_TASKCONTROLLER_48A5496F0068_INCLUDED
#define _INC_CCBS_STDFRAME_TASKCONTROLLER_48A5496F0068_INCLUDED

class cCBS_StdFrame_Task;

//class calls "control" and "uncontrol" method of respective 
//task during construction / destruiction. The task will 
//forward this call to respective controller thread.
//##ModelId=48A5496F0068
class cCBS_StdFrame_TaskController 
{
public:
	//##ModelId=48A549AD01A2
	virtual ~cCBS_StdFrame_TaskController();

	//call with LifeTime in msecs
	//##ModelId=48A549AE00E5
	cCBS_StdFrame_TaskController( cCBS_StdFrame_Task* pTask    );

private:
	//##ModelId=48A5593A0298
	cCBS_StdFrame_Task* m_pTask;

};

#endif /* _INC_CCBS_STDFRAME_TASKCONTROLLER_48A5496F0068_INCLUDED */

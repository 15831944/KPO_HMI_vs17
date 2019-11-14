// // ----------------------------------------------------------------------------
// // 
// //                            S M S  D e m a g  A G
// // 
// //                             All Rights Reserved
// // 
// // 
// //  project       : Shougang 
// //  filename      : 
// //  originator    : 
// //  department    : 
// //  creation date : 
// //  description   : 
// // 
// // ----------------------------------------------------------------------------
// // 
// //  change notes:
// // 
// //  version  dd-mmm-yyyy author  remarks
// //  0.1      06-JUN-2001 	 First Version
// // 
// // ----------------------------------------------------------------------------
// // 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_cSysMon_SERVER_43145F01013D_INCLUDED
#define _INC_cSysMon_SERVER_43145F01013D_INCLUDED

#include <CBS_General.h>
#include <CBS_Tasks.h>
#include <CBS_StdAPI.h>

class cSysMon_Comp;

//##ModelId=43145F01013D
class cSysMon_Server 
: public cCBS_StdServer
{
protected:
	//##ModelId=4314B52B032E
	cSysMon_Comp* m_pComponent;

public:
	//##ModelId=4314666D0384
	virtual ~cSysMon_Server();

	//##ModelId=4314666E0139
	cSysMon_Server(int argc, const char* argv[]);

	//Abstract method. Should create the tasks that are part 
	//of this server.
	//##ModelId=4314668A02DC
	virtual void createTasks();

};

#endif /* _INC_cSysMon_SERVER_43145F01013D_INCLUDED */

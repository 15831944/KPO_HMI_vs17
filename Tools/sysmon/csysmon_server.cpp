// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : SysMon 
//  filename      : cSysMon_Server.cpp
//  originator    : Bjoern Knops
//  department    : EAM1
//  creation date : 
//  description   : 
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy author  remarks
//  0.1                  knop    First Version
// 
// ----------------------------------------------------------------------------
//

#include "cSysMon_Server.h"
#include "cSysMon_Comp.h"
// compile test log levels up to #9 
#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"




//##ModelId=4314666D0384
cSysMon_Server::~cSysMon_Server()
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=4314666E0139
cSysMon_Server::cSysMon_Server(int argc, const char* argv[])
: cCBS_StdServer(argc, argv),
  m_pComponent(NULL)
{
	// ToDo: Add your specialized code here and/or call the base class
}

//##ModelId=4314668A02DC
void cSysMon_Server::createTasks()
{
	// ToDo: Add your specialized code here
	try
  {
    m_pComponent = new cSysMon_Comp();

    m_pComponent->activate(s_componentPOA, getComponentName());  // POA: portable object adapter

  }
  catch (cCBS_Exception& e)
  {
    CLOG1(<< string("createTasks(): Error when creating SysMon_Component): ") << e);
  }
}


//-------------------------------------------------------------------------------------------------
//
//                           S M S  Siemag  A G
//
//                            All Rights Reserved
//
//
// project       : Email Server
// filename      : cEmailServer_Server.cpp
// originator    : Dominik Terhorst
// department    : SMS Siemag AG
// creation date : 06-JUL-2010 
// description   : CBS Server for Email Server
//
//-------------------------------------------------------------------------------------------------

// compile test log levels op to #9
#define _CLOG9

#include "cEmailServer_Comp.h"
#include "cEmailServer_Server.h"
#include "CBS_Clog.h"

//-------------------------------------------------------------------------------------------------
// cEmailServer_Server()
//-------------------------------------------------------------------------------------------------
cEmailServer_Server::cEmailServer_Server(int argc, const char* argv[]) : cCBS_StdServer(argc, argv),
m_pComponent(NULL)
{
  CLOG5(<< "Constructor: finished!" << std::endl);
}
//-------------------------------------------------------------------------------------------------
// ~cEmailServer_Server()
//-------------------------------------------------------------------------------------------------
cEmailServer_Server::~cEmailServer_Server()
{
  if(m_pComponent)
  {
    cEmailServer_Comp::release();
    m_pComponent = NULL;
  }
}
//-------------------------------------------------------------------------------------------------
// createTasks()
//-------------------------------------------------------------------------------------------------
void cEmailServer_Server::createTasks()
{
  m_pComponent = cEmailServer_Comp::getComponent();
  CLOG5(<< "createTasks(): trigger activation of component.." << std::endl);
  m_pComponent->activate(s_componentPOA, getComponentName());
}

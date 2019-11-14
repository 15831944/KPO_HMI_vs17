// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : StraGang
//  filename      : 
//  originator    : 
//  department    : 
//  creation date : 03.03.2005 10:49
//  description   : Server for IBAS
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy 	author  	remarks
//  0.1      03.03.2005 10:49 	Uli Bellgardt   First Version
// 
// ----------------------------------------------------------------------------
// 
#pragma warning (disable:4503)

#include "cIBAS_Component.h"
#include "cIBAS_Server.h"



cIBAS_Server::~cIBAS_Server()
{
	if (m_pComponent)
	{
		delete m_pComponent;
	}
}


cIBAS_Server::cIBAS_Server( int          argc, 
                            const char** argv, 
  	 		                    const char*  compName,
										        const char*  serverName)
:   cCBS_StdServer( argc, argv)
  , m_pComponent(0)
{
  m_pComponent = new cIBAS_Component(this);
}


void cIBAS_Server::createTasks()
{
  if (m_pComponent)
  {
    m_pComponent->activate(s_componentPOA, getComponentName());
  }

}


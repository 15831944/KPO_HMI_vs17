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

#ifndef INC_CIBAS_Server_INCLUDED
#define INC_CIBAS_Server_INCLUDED


#include "CBS_StdAPI\cCBS_StdServer.h"

class cIBAS_Component;

class cIBAS_Server : 
public cCBS_StdServer
  
{
public:

  virtual ~cIBAS_Server();

	cIBAS_Server(int argc, const char** argv, 
		                const char* compName ="IBAS_Component",
										const char* serverName = NULL  );

	virtual void createTasks();

protected:
	cIBAS_Component* m_pComponent;

};

#endif // INC_CIBAS_Server_INCLUDED

// ------------------------------------------------------------------------------------------------
//
//                            S M S  D e m a g  A G
//
//                             All Rights Reserved
//
//
//  project       : Email Server
//  filename      : main.cpp
//  originator    : Sankar Sarkar
//  department    : SMS Siemag AG
//  creation date : 05-JUL-2010
//  description   : Main class. Reads ini file and starts CBS server.
//
// ------------------------------------------------------------------------------------------------

// compile test log levels op to #9
#define _CLOG9

#include <CBS_General.h>
#include <CBS_Tasks.h>
#include "CBS_Clog.h"
#include "cEmailServer_Server.h"

#ifdef _EVENTLOG_
#include "CBS_EventLog\errorlog.h"
#endif




// ------------------------------------------------------------------------------------------------
// main()
// ------------------------------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
	try
	{
		cEmailServer_Server server(argc, argv);  

		server.get_StdTestLog();
		server.createTasks();        
		std::cout << "\nNow waiting for you to start up component from TaskViewer.." << std::endl;

    server.run(); 

	}
	catch(CORBA::Exception& e)
	{
		CLOG2( << "CORBA::Exception: " << e << std::endl);
	}
	catch(cCBS_Exception &exc)
	{
		CLOG2( << "CBSException: " << std::endl << exc << std::endl);
	}
	catch(...)  // TODO: check this unknown exception stuff here
	{
		CLOG1( << "Unknown Exception in main!!!" << std::endl);
	}
	return(0);
}



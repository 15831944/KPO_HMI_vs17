// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : Shougang
//  filename      : IntrfImpl.cpp
//  originator    : Josef Curda
//  department    : PIKE Electronic
//  creation date : 2-Jul-2004
//  description   : Implementation of CORBA interface functions
// 
// ----------------------------------------------------------------------------
// 
//  change notes:
// 
//  version  dd-mmm-yyyy author  remarks
//  1.0      02-jul-2004         First Version
// 
// ----------------------------------------------------------------------------


#include <iostream>

#include "IntrfImpl.h"
#include <CBS_Threads/cCBS_AccessSync.h>



#define CORBA_OK		1
#define CORBA_ERROR	0


IntrfImpl::IntrfImpl() 
{
}


void IntrfImpl::getLastResponses(SMON::seq_SMON_LastResponses_out SMON_LastResponses) {
  TLastResponseTimeMap::iterator ii;
	
	SMON_LastResponses = new SMON::seq_SMON_LastResponses();
	long j = 0;

	cCBS_AccessSync accessSync(&m_LastResponseMutex);
	SMON_LastResponses->length(lastResponseMap.size());

	for (ii = lastResponseMap.begin(); ii != lastResponseMap.end(); ii++) 
	{

		(*SMON_LastResponses)[j].intName  = CORBA::string_dup( ((string) (*ii).first).c_str() );       

      std::string tmp2 = ((*ii).first);
      std::string tmp = ((*ii).second).LastResponse;
      (*SMON_LastResponses)[j].lastTime = CORBA::string_dup( ((*ii).second).LastResponse.c_str() );
      (*SMON_LastResponses)[j].status = ((*ii).second).Status;
		j++;
	}
}


//##ModelId=41A39E010261
void IntrfImpl::setLastResponse(const char* system, std::string lastTime) 
{	
	cCBS_AccessSync accessSync(&m_LastResponseMutex);

	//LOG_(4, "-------------------------------------------------------------------");
	
	try
	{
		lastResponseMap[system].LastResponse = lastTime;
	}
	catch(...)
	{
		//LOG_(1, "Exception when setting LastResponse for system " << system);
	}


	
}

void IntrfImpl::setStatus(const char* system, bool status)
{
	cCBS_AccessSync accessSync(&m_LastResponseMutex);

	//LOG_(4, "-------------------------------------------------------------------");
	
	try
	{
		lastResponseMap[system].Status = status;
	}
	catch(...)
	{
		//LOG_(1, "Exception when setting Status for system " << system);
	}
}



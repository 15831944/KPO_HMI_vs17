// ----------------------------------------------------------------------------
// 
//                            S M S  D e m a g  A G
// 
//                             All Rights Reserved
// 
// 
//  project       : Shougang
//  filename      : IntrfImpl.h
//  originator    : Josef Curda
//  department    : PIKE Electronic
//  creation date : 2-Jul-2005
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


#ifndef _INTRFIMPL_H
#define _INTRFIMPL_H


#include <map>
#include <string>
#include <CBS_General.h>
#include <CBS_Tasks.h>
#include <CBS_StdAPI/cCBS_StdComponent.h>
#include <CBS_Threads/cCBS_Mutex.h>
#include "LastResponse.h"


using namespace std;

struct sResponseEntry
{
	std::string LastResponse;
  bool   Status;
};

typedef std::map<string, sResponseEntry> TLastResponseTimeMap;


class IntrfImpl : public POA_SMON::SMONIntrf,
				public PortableServer::RefCountServantBase
{
	public:
		IntrfImpl();		// constructor

		virtual void getLastResponses(SMON::seq_SMON_LastResponses_out SMON_LastResponses) ;
    void setLastResponse(const char* system, std::string lastTime);
		void setStatus(const char* system, bool status);

	private:
		cCBS_Mutex m_LastResponseMutex;
		
		TLastResponseTimeMap lastResponseMap;

}; 


#endif

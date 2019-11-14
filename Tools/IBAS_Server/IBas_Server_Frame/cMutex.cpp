#include "cmutex.h"
#include "cCBS_AccessSync.h"

// the static data member
cCBS_Mutex cMutex::m_Mutex;

// utilize cCBS_AccessSync with cCBS_Mutex.
// m_Mutex lives forever, 
// m_accessSync lives as long as cMutex.
////////////////////////////////////////////////////////////////
cMutex::cMutex(void)
: m_accessSync(&m_Mutex)
{
}

cMutex::~cMutex(void)
{
}


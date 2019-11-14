#include "CProgressInfoByFileLogRead.h"

//-----------------------------------------------
CProgressInfoByFileLogRead::CProgressInfoByFileLogRead()
{
  lineSize=0;
  ready = false;
  InitializeCriticalSection(&sec);
}
//-----------------------------------------------
CProgressInfoByFileLogRead::~CProgressInfoByFileLogRead(void)
{
  DeleteCriticalSection(&sec);
}

//-----------------------------------------------
void CProgressInfoByFileLogRead::setData(long size)
{
  // Request ownership of the critical section.
  EnterCriticalSection(&sec);  
  lineSize+=size;
  // Release ownership of the critical section.
  LeaveCriticalSection(&sec);
}
//-----------------------------------------------
void CProgressInfoByFileLogRead::resetData()
{
  // Request ownership of the critical section.
  EnterCriticalSection(&sec);  
  
  lineSize=0;
  ready = false;
  
  // Release ownership of the critical section.
  LeaveCriticalSection(&sec);
}

//-----------------------------------------------
long CProgressInfoByFileLogRead::getData()
{
  //// Request ownership of the critical section.
  EnterCriticalSection(&sec); 

  long temp = lineSize;
  lineSize = 0;
  
  // Release ownership of the critical section.
  LeaveCriticalSection(&sec);
  return temp;
}

CProgressInfoByFileLogRead* CProgressInfoByFileLogRead::getProgressInfoByFileLogRead()
{
  if(ProgressInfoByFileLogRead == 0)
    ProgressInfoByFileLogRead = new CProgressInfoByFileLogRead();
  
  return ProgressInfoByFileLogRead; 
}
//-----------------------------------------------
 void CProgressInfoByFileLogRead::setStatusReady(bool st)
 {
  ready = st;
 }
//-----------------------------------------------
bool CProgressInfoByFileLogRead::getStatusReady(void)
{
  return ready;
}
//-----------------------------------------------
CProgressInfoByFileLogRead* CProgressInfoByFileLogRead::ProgressInfoByFileLogRead = 0; 
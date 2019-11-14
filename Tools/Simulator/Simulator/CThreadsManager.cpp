#include "StdAfx.h"
#include "CThreadsManager.h"
#using <mscorlib.dll>

using namespace System;

//----------------------------------------------------
CThreadsManager::~CThreadsManager(void)
{
}
//----------------------------------------------------
CThreadsManager::CThreadsManager(CloseAppDelTyp^ eventTyp)
{
  CloseAppDelEvent = eventTyp;
}
//----------------------------------------------------
CThreadsManager^ CThreadsManager::getThreadsManager()
{
  if (ThreadsManager==nullptr)
  {
    return nullptr;
  }
  return ThreadsManager; 
}
//----------------------------------------------------
CThreadsManager^ CThreadsManager::getThreadsManager(CloseAppDelTyp^ eventTyp)
{
  if (ThreadsManager==nullptr)
  {
    ThreadsManager = gcnew CThreadsManager(eventTyp);
  }
  return ThreadsManager; 
}
//----------------------------------------------------
void CThreadsManager::CallCloseByForm1()
{
  if (CloseAppDelEvent)
    CloseAppDelEvent->Invoke();
}
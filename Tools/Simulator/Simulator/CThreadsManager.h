//#pragma once
// Copyright 2009 SMS - Demag AG

#ifndef _CThreadsManager_H_
#define _CThreadsManager_H_

using namespace System;
//-------------------------------------------
// Name:  CThreadsManager.h
// Descr: Diese Klasse ruft in Form1.h die Close Methode auf.
//        Die Klasse ist singleton.
// Date:  27.02.2009
// Autor: Emeljanov Alexander 
//-------------------------------------------

public ref class CThreadsManager
{
public:
  delegate void CloseAppDelTyp();
public:
  ~CThreadsManager(void);
  static CThreadsManager^ getThreadsManager();
  static CThreadsManager^ getThreadsManager(CloseAppDelTyp^ eventTyp);
  void CallCloseByForm1();
protected:
  CThreadsManager(CloseAppDelTyp^ eventTyp);

private:
  static CThreadsManager^ ThreadsManager; 
  CloseAppDelTyp^ CloseAppDelEvent;
};
#endif
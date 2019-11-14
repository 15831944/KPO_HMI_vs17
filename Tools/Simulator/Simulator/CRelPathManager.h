//#pragma once
// Copyright 2008 SMS - Demag AG

#ifndef _CRelPathManager_H_
#define _CRelPathManager_H_

using namespace System;
//-------------------------------------------
// Name:  CRelPathManager.h
// Descr: Mit dieser Klasse werden alle relative Pfade (z.B.
//        für Interfacekonfigurationsfile) verwaltet. 
// Date:  17.03.2008
// Autor: Emeljanov Alexander 
//-------------------------------------------

public ref class CRelPathManager
{
public:
  ~CRelPathManager(void);
  String^ getPathToSave(String^ globalPath);
  String^ getPathToOpen(String^ relativPath); 
  static CRelPathManager^ getRelPathManager(String^ path);
  static CRelPathManager^ getRelPathManager();
protected:
  CRelPathManager(String^ path);

private:
  //System::Management::ManagementPath^ relPath;
  String^ BasicFolder;
  static CRelPathManager^ RelPathManager;  
};
#endif
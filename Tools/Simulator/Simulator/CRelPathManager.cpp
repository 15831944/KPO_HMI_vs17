#include "StdAfx.h"
#include "CRelPathManager.h"
#using <mscorlib.dll>

using namespace System;

//----------------------------------------------------
CRelPathManager::CRelPathManager(String^ path)
{
  BasicFolder=path;
}
//----------------------------------------------------
CRelPathManager::~CRelPathManager(void)
{
}
//----------------------------------------------------
CRelPathManager^ CRelPathManager::getRelPathManager()
{
 if (RelPathManager!=nullptr)
   return RelPathManager;
 else
	 return nullptr;
}
//----------------------------------------------------
CRelPathManager^ CRelPathManager::getRelPathManager(String^ path)
{
  if (RelPathManager==nullptr)
  {
   RelPathManager = gcnew CRelPathManager(path);
  }
  return RelPathManager; 
}
//----------------------------------------------------
String^ CRelPathManager::getPathToSave(String^ globalPath)
{
  String^ fileName;
  //prueft,ob Dateiname mit Dateierweiterung am Ende des Pfades ist.
  if (globalPath->LastIndexOf(".")>0)
  {
    //Findet von hinten den Backslash und gibt Index zurueck
    int temp=globalPath->LastIndexOf("\\");
    fileName = globalPath->Substring(temp);
    globalPath = String::Concat(globalPath->Remove(temp,globalPath->Length-temp));
  }
  
  int lenght1 = BasicFolder->Length;
  int lenght2 = globalPath->Length;

  if (lenght2>=lenght1)
  {
    String^ test1 = globalPath->Substring(0,lenght1);
    if (String::Compare(globalPath->Substring(0,lenght1),BasicFolder,true)==0)
    {
      String^ test2 = String::Concat(globalPath->Substring(lenght1),fileName); 
      if (lenght2==lenght1) 
        return String::Concat(globalPath->Substring(lenght1),fileName); 
      else
      {
        String^ Test4 = globalPath->Substring(lenght1,1);
        if (String::Compare(globalPath->Substring(lenght1,1),"\\")==0)
          return String::Concat(globalPath->Substring(lenght1),fileName); 
        else
          return String::Concat(globalPath,fileName); 
      }
    }
    else
    {
      String^ test3 = String::Concat(globalPath,fileName); 
      return String::Concat(globalPath,fileName); 
    }
  }
  else
  {
    return String::Concat(globalPath,fileName); 
  }

  /* String^ tempPath = safe_cast<String^>(BasicFolder->Clone());
  String^ tempGlobalPath = safe_cast<String^>(globalPath->Clone());
  String^ ret = 0;
  bool ok = true;
  int index1,index2;  
  int counter = 1;

  while (ok)
  {
    index1 = tempPath->IndexOf("\\");
    index2 = tempGlobalPath->IndexOf("\\");
    
    if (index1>=0 && index2>=0)
    {
      String^ temp1 = tempGlobalPath->Substring(0,index2+1); 
      String^ temp2 = tempPath->Substring(0,index1+1);

      //Wenn's bis zum 1-ten Slash gleich ist.
      if (String::Compare(temp1,temp2,true) == 0)
      {
        ret=String::Concat(ret,temp1);
        
        tempGlobalPath=String::Concat(tempGlobalPath->Remove(0,index2+1));
        tempPath=String::Concat(tempPath->Remove(0,index1+1));
        
        counter++;
      }
      else
      {
        ok = false;
      }
    }
    else
    {
      if (counter == 1)
        return globalPath;
      else
        ok = false;
    }
  }
  return tempGlobalPath;*/
}
//---------------------------------------------------
String^ CRelPathManager::getPathToOpen(String^ relativPath)
{
  if (relativPath->IndexOf(":")==-1)
  {
    if (relativPath->StartsWith("\\"))
      return String::Concat(BasicFolder,relativPath);
    else
      return String::Concat(BasicFolder,"\\",relativPath);
  }
  else if (relativPath->Equals("") || relativPath->Equals(""))
    return BasicFolder;
  else
  {
    return relativPath; 
  }
  /*if (relativPath->IndexOf(":")==-1)
  {
    String^ fileName = 0;
    String^ tempPath = safe_cast<String^>(BasicFolder->Clone());
    bool ok = true;
    String^ ret = 0;   
    //ob mit Dateinname inclusiv
    int a = relativPath->LastIndexOf(".");
    //prueft,ob Dateiname mit Dateierweiterung am Ende des Pfades ist.
    if (relativPath->LastIndexOf(".")>0)
    {
      //Findet von hinten den Backslash und gibt Index zurueck
      int temp=relativPath->LastIndexOf("\\");
      //Wenn keinen Backshlash gefunden wurde, dann handelt es sich um Dateiname
      if (temp==-1)  
      {
        fileName = relativPath;
        ok = false;
      }
      else
      {
        fileName = relativPath->Substring(temp,relativPath->Length-temp-1);
        relativPath = String::Concat(relativPath->Remove(temp,relativPath->Length-temp));
      }
    }
    if (ok)
    {
      //BasicSting und relative Pfad von hinten vergleichen
      bool ok_ = true;
      int index1,index2;
      while (ok_)
      {
        index1=tempPath->LastIndexOf("\\");
        index2=relativPath->LastIndexOf("\\");
       
        if (String::Compare(tempPath->Substring(index1-1),relativPath->Substring(index2-1),true)==0)
        {
          relativPath->Length;
        }
        else
        {
        }
      }
      ret->String::Concat(tempPath->Substring(tempPath->Length-relativPath->Length,relativPath->Length),
                   relativPath,fileName);         
    }
    return String::Concat(fileName);
  }
  else
    return relativPath; */
}
// Copyright 2006 SMS - Demag AG

//--------------------------------------------------
#include "stdafx.h"
#include "CAppSetting.h"
#include "CStdConverter.h"
#include "CRelPathManager.h"
//--------------------------------------------------
CAppSetting::CAppSetting()
{
}
//--------------------------------------------------
CAppSetting^ CAppSetting::getApp()
{
  if(AppSetting == nullptr)
  {
    AppSetting = gcnew CAppSetting();
    String^ path = System::Windows::Forms::Application::StartupPath;
    String^ exeFile = System::Windows::Forms::Application::ExecutablePath;
    int pos = exeFile->LastIndexOf("\\");
    exeFile=exeFile->Substring(pos+1,exeFile->Length-pos-1);
    pos = exeFile->LastIndexOf(".");
    exeFile = String::Concat(exeFile->Substring(0,pos),".ini");
    path = System::String::Concat(path,"\\",exeFile);
    AppSetting->IniName = path;

    int index = path->IndexOf(exeFile);
    RelPath = CRelPathManager::getRelPathManager(path->Substring(0,index-1));
    
    //RelPath->getPathToSave("v:\\smck\\l2S1\\Debug\\bin\\fff\\aaa.txt");
    //relpath->getPathToOpen("v:\\smc\\l2S1\\Debug\\bin\\aaa.txt");
  }
  return AppSetting;
}
//--------------------------------------------------
bool CAppSetting::checkIniFile()
{
  return System::IO::File::Exists(IniName);
}
//--------------------------------------------------
String^ CAppSetting::getIniFileName()
{
  int pos;
    String^ ret = nullptr;

  pos = IniName->LastIndexOf("\\");
  ret = IniName->Substring(pos+1,IniName->Length-pos-1);
  return ret;
}
//--------------------------------------------------
bool CAppSetting::checkInterConfigFile(String^ name)
{
  String^ path = nullptr;
  std::string inipathstr("");
  std::string interNameStr("");
  std::string pathstr("");
  CStdConverter::StringToStdStr(IniName,inipathstr);
  CStdConverter::StringToStdStr(name,interNameStr);
  pathstr = CIniFile::GetValue(interNameStr,"InterConfig",inipathstr);
  path = RelPath->getPathToOpen(CStdConverter::StdStrToString(pathstr));
  return System::IO::File::Exists(path);
}
//--------------------------------------------------
void CAppSetting::createIniFile()
{
  std::string inipathstr("");
  CStdConverter::StringToStdStr(IniName,inipathstr);
  CIniFile::Create(inipathstr);
  CIniFile::AddSection("Interfaces",inipathstr);
  CIniFile::AddSection("InterConfig",inipathstr);
  CIniFile::AddSection("Directory",inipathstr);
  CIniFile::AddSection("LogFiles",inipathstr);
  CIniFile::AddSection("LastActiveInterface",inipathstr);
  CIniFile::SetValue("Analyzer","","Directory",inipathstr);
  CIniFile::SetValue("Connection","","Directory",inipathstr);
  CIniFile::SetValue("Cyclic","","Directory",inipathstr);
  CIniFile::SetValue("Interface","","Directory",inipathstr);
  CIniFile::SetValue("LogFile","","Directory",inipathstr);
  CIniFile::SetValue("Szenarium","","Directory",inipathstr);
  CIniFile::SetValue("LastActiveInterface","","LastActiveInterface",inipathstr);
  CIniFile::SetValue("MaxCount","10","LogFiles",inipathstr);
  CIniFile::SetValue("MaxSize","20","LogFiles",inipathstr);
  CIniFile::SetValue("Ok","1","LogFiles",inipathstr);
  CIniFile::SetValue("Warning","1","LogFiles",inipathstr);
  CIniFile::SetValue("Error","1","LogFiles",inipathstr);
  CIniFile::SetValue("Info","1","LogFiles",inipathstr);
  CIniFile::SetValue("NodesInTlgViewCollapsed","-1","TlgView",inipathstr);
  CIniFile::SetValue("HeaderTlg", "", "TlgType",inipathstr);

}
//--------------------------------------------------
void CAppSetting::addInterface(String^ path)
{
  std::string inipathstr("");
  CStdConverter::StringToStdStr(IniName,inipathstr);
  String^ interName=nullptr;
  std::string pathStr("");
  std::string interNameStr("");
  int pos;
    
  CStdConverter::StringToStdStr(RelPath->getPathToSave(path),pathStr);
  pos=path->LastIndexOf("\\");
  interName = path->Substring(pos+1,path->Length-pos-1);
  pos=interName->LastIndexOf(".");
  interName=interName->Substring(0,pos);
  CStdConverter::StringToStdStr(interName,interNameStr);
  CIniFile::SetValue(interNameStr,pathStr,"Interfaces",inipathstr);
}
//--------------------------------------------------
void CAppSetting::addInterDefaultConfigFile(String^ path,String^ interName)
{
  std::string inipathstr("");
  std::string interNameStr("");
  std::string pathstr("");
  
  if (path->IndexOf("icnf")==-1)
    path = String::Concat(path,"\\",interName,".icnf");

  CStdConverter::StringToStdStr(interName,interNameStr);
  CStdConverter::StringToStdStr(IniName,inipathstr);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(path),pathstr);
  
  CIniFile::SetValue(interNameStr,pathstr,"InterConfig",inipathstr);
}
//--------------------------------------------------
void CAppSetting::addInterfaceConfigFile(String^ path,String^ interName)
{
  std::string inipathstr("");
  std::string interNameStr("");
  std::string pathstr("");

  CStdConverter::StringToStdStr(interName,interNameStr);
  CStdConverter::StringToStdStr(IniName,inipathstr);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(path),pathstr);
  
  CIniFile::SetValue(interNameStr,pathstr,"InterConfig",inipathstr);
}
//--------------------------------------------------
array <String^>^ CAppSetting::getInterfacePath()
{
  array <String^>^ ret = nullptr;
  std::vector<CIniFile::Record> vec;
  std::string ini("");
  int count,i;
  std::string valstr("");
  CStdConverter::StringToStdStr(IniName,ini);

  vec = CIniFile::GetSection("Interfaces",ini);
  count = vec.size();
  ret = gcnew array <String^>(count);
  for(i=0;i<count;i++)
  { 
    valstr=vec[i].Value;
    ret[i] = RelPath->getPathToOpen(CStdConverter::StdStrToString(valstr));
  }
  return ret;
}
//--------------------------------------------------
String^ CAppSetting::getAnalyzerDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("Analyzer","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret = RelPath->getPathToOpen(ret);
  return ret;
}
//--------------------------------------------------  
void CAppSetting::setAnalyzerDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("Analyzer",dirstr,"Directory",ini);
}
//--------------------------------------------------
void CAppSetting::setCyclicDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("Cyclic",dirstr,"Directory",ini);
}
//--------------------------------------------------
String^ CAppSetting::getCyclicDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("Cyclic","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret = RelPath->getPathToOpen(ret);
  return ret;
} 
//--------------------------------------------------
String^ CAppSetting::getLogFileDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("LogFile","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret = RelPath->getPathToOpen(ret);
  return ret;
}
//--------------------------------------------------
void CAppSetting::setLogFileDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("LogFile",dirstr,"Directory",ini);
}
//--------------------------------------------------
String^ CAppSetting::getSzenDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("Szenarium","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret = RelPath->getPathToOpen(ret);
  return ret;
}
//--------------------------------------------------
void CAppSetting::setSzenDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("Szenarium",dirstr,"Directory",ini);
}
//-------------------------------------------------
String^ CAppSetting::getConnDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("Connection","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret= RelPath->getPathToOpen(ret);
  return ret; 
}
//-------------------------------------------------
void CAppSetting::setConnDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("Connection",dirstr,"Directory",ini);
}
//-------------------------------------------------
String^ CAppSetting::getInterDirectory()
{
  String^ ret = nullptr;
  std::string path("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  path=CIniFile::GetValue("Interface","Directory",ini);
  ret = CStdConverter::StdStrToString(path);
  ret = RelPath->getPathToOpen(ret);
  return ret;
}
//-------------------------------------------------
void CAppSetting::setInterDirectory(String^ directory)
{
  std::string dirstr("");
  std::string ini("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(RelPath->getPathToSave(directory),dirstr);
  CIniFile::SetValue("Interface",dirstr,"Directory",ini);
}
//--------------------------------------------------
String^ CAppSetting::getWorkingDirectory()
{
  return System::Windows::Forms::Application::StartupPath;
}
//--------------------------------------------------
String^ CAppSetting::getInterConfigFilePath(String^ inter)
{
  std::string interstr("");
  std::string ini("");
  std::string val("");

  CStdConverter::StringToStdStr(IniName,ini);
  CStdConverter::StringToStdStr(inter,interstr);
  val = CIniFile::GetValue(interstr,"InterConfig",ini);
  return RelPath->getPathToOpen(CStdConverter::StdStrToString(val));
}
//--------------------------------------------------
void CAppSetting::removeInterface(String^ inter)
{
  std::string interStr("");
  std::string ini("");
  CStdConverter::StringToStdStr(inter,interStr);
  CStdConverter::StringToStdStr(IniName,ini);
	
	//Die Konf - Datei soll nicht geloescht werden!!! 
  //String^ confPath = RelPath->getPathToOpen(getInterConfigFilePath(inter));
  // System::IO::File::Delete(confPath);
  
	CIniFile::DeleteRecord(interStr,"Interfaces",ini);
  CIniFile::DeleteRecord(interStr,"InterConfig",ini);
}
//-----------------------------------------------
void CAppSetting::setLastActivInterfaceName(String^ inter)
{
  std::string interStr("");
  std::string ini("");
  CStdConverter::StringToStdStr(inter,interStr);
  CStdConverter::StringToStdStr(IniName,ini);

  CIniFile::SetValue("LastActiveInterface",interStr,"LastActiveInterface",ini);

}
//-----------------------------------------------
String^ CAppSetting::getLastActivInterfaceName()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  return CStdConverter::StdStrToString(CIniFile::GetValue("LastActiveInterface",
                                        "LastActiveInterface",ini));
}
//-----------------------------------------------
void CAppSetting::setMessageTypsInLogFiles(array <String^>^ messTyps)
{
  std::string tmp("");
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  CStdConverter::StringToStdStr(messTyps[0],tmp);
  CIniFile::SetValue("Info",tmp,"LogFiles",ini);
  CStdConverter::StringToStdStr(messTyps[1],tmp);
  CIniFile::SetValue("Warning",tmp,"LogFiles",ini);
  CStdConverter::StringToStdStr(messTyps[2],tmp);
  CIniFile::SetValue("Error",tmp,"LogFiles",ini);
}
//-----------------------------------------------
array <String^>^ CAppSetting::getMessageTypsInLogFiles()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);
  array <String^>^ ret = gcnew array <String^>(3);
  //Initialisieren
  ret[0] = "";
  ret[1] = "";
  ret[2] = "";
  //Auslesen
  ret[0] = CStdConverter::StdStrToString(CIniFile::GetValue("Info","LogFiles",ini));
  ret[1] = CStdConverter::StdStrToString(CIniFile::GetValue("Warning","LogFiles",ini));
  ret[2] = CStdConverter::StdStrToString(CIniFile::GetValue("Error","LogFiles",ini));
  return ret;
}
//-----------------------------------------------
void CAppSetting::setMaxSizeOfLogFiles(String^ size)
{
  std::string stdSize("");
  std::string ini("");
  CStdConverter::StringToStdStr(size,stdSize);
  CStdConverter::StringToStdStr(IniName,ini);
  
  CIniFile::SetValue("MaxSize",stdSize,"LogFiles",ini);
}
//-----------------------------------------------
String^ CAppSetting::getMaxSizeOfLogFiles()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  return CStdConverter::StdStrToString(CIniFile::GetValue("MaxSize",
                                        "LogFiles",ini));
}
//-----------------------------------------------
void CAppSetting::setMaxCountOfLogFiles(String^ count)
{
  std::string stdCount("");
  std::string ini("");
  CStdConverter::StringToStdStr(count,stdCount);
  CStdConverter::StringToStdStr(IniName,ini);
  
  CIniFile::SetValue("MaxCount",stdCount,"LogFiles",ini);
}
//-----------------------------------------------
String^ CAppSetting::getMaxCountOfLogFiles()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  return CStdConverter::StdStrToString(CIniFile::GetValue("MaxCount",
                                        "LogFiles",ini));
}
//-----------------------------------------------
void CAppSetting::setNodesInTlgViewCollapsed(String^ value)
{
  std::string stdVal("");
  std::string ini("");
  CStdConverter::StringToStdStr(value,stdVal);
  CStdConverter::StringToStdStr(IniName,ini);
  
  CIniFile::SetValue("NodesInTlgViewCollapsed",stdVal,"TlgView",ini);
}
//-----------------------------------------------
String^ CAppSetting::getNodesInTlgViewCollapsed()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  return CStdConverter::StdStrToString(CIniFile::GetValue("NodesInTlgViewCollapsed",
                                        "TlgView",ini));
}
//-----------------------------------------------
array <String^>^ CAppSetting::getCorbaInterfaces(String^ context)
{
  array <String^>^ ret = nullptr;
  std::vector<CIniFile::Record> vec;
  std::string ini("");
  int count,i;
  std::string valstr("");
  std::string stdcontext("");
  CStdConverter::StringToStdStr(context,stdcontext);
  CStdConverter::StringToStdStr(IniName,ini);

  vec = CIniFile::GetSection(stdcontext,ini);
  count = vec.size();
  
  if (count == 0)
    return nullptr;

  ret = gcnew array <String^>(count);
  for(i=0;i<count;i++)
  { 
    valstr=vec[i].Value;
    ret[i] = CStdConverter::StdStrToString(valstr);
  }
  return ret;

}
//-----------------------------------------------
array <String^>^ CAppSetting::getCorbaContext()
{
  array <String^>^ ret = nullptr;
  std::vector<CIniFile::Record> vec;
  std::string ini("");
  int count,i;
  std::string valstr("");
  CStdConverter::StringToStdStr(IniName,ini);

  vec = CIniFile::GetSection("Corba_Context",ini);
  count = vec.size();
  
  if (count == 0)
    return nullptr;

  ret = gcnew array <String^>(count);
  for(i=0;i<count;i++)
  { 
    valstr=vec[i].Value;
    ret[i] = CStdConverter::StdStrToString(valstr);
  }
  return ret;
}
//-----------------------------------------------
bool CAppSetting::useDynamicAdaptation()
{
  return false;
}

//-----------------------------------------------
String^ CAppSetting::getHeaderTlg()
{
  std::string ini("");
  CStdConverter::StringToStdStr(IniName,ini);

  //return CStdConverter::StdStrToString(CIniFile::GetValue("HeaderTlg", "TlgType",ini));
  String^ HeaderTlg = CStdConverter::StdStrToString(CIniFile::GetValue("HeaderTlg", "TlgType",ini));

  if ( HeaderTlg == "" )
  {
    HeaderTlg = "Head";
  }

  return HeaderTlg;
}

#include "stdafx.h"
#include "CCorbaIdlWrapper.h"
#include "CAppSetting.h"

//---------------------------------------------------------
void CCorbaIdlWrapper::ReadIniFile()
{
  CAppSetting^ Sett = CAppSetting::getApp();
  
  this->CorbaContext = Sett->getCorbaContext();

  if (CorbaContext == nullptr)
  {
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                      "No corba context in simulator.ini defined.",
                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    return;
  }

  Collections::ArrayList^ tmpList = gcnew Collections::ArrayList();
  array <String^>^ tmp;
  String^ LastContext;
  for (int i=0;i<CorbaContext->Length;i++)
  {
    //if (CorbaContext[i]->LastIndexOf("/") < 0)
      LastContext = CorbaContext[i];
    //else
    //  LastContext = CorbaContext[i]->Substring(CorbaContext[i]->LastIndexOf("/")+1);

    tmp = Sett->getCorbaInterfaces(LastContext);
    if (tmp!=nullptr)
    {
      for (int j=0;j<tmp->Length;j++)
      {
        if (ContextTable->Contains(tmp[j]))
          LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                        "Name of corba interface <" + tmp[j] + "> is not unique.",
                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        else
        {
          this->ContextTable->Add(tmp[j],CorbaContext[i]);
          tmpList->Add(tmp[j]);
        }
      }
    }
  }

  if (tmpList->Count == 0)
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                        "No corba interfaces in simulator.ini defined.",
                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  else
  {
    this->CorbaInterfaces = gcnew array<String^>(tmpList->Count);
    for (int i=0;i<tmpList->Count;i++)
      this->CorbaInterfaces[i]=(String^)tmpList[i];
  }
}

//---------------------------------------------------------
array<String^>^ CCorbaIdlWrapper::getInterfaceNames()
{
  return this->CorbaInterfaces;
}
//------------------------------------------------------------
array <String^>^ CCorbaIdlWrapper::getContext()
{
  return this->CorbaContext;
}

/*
  Unterschied, neue Syntax :) :

  Zeiger für verwaltete Klasse: ^ und Objekt erzeugen mit gcnew
  Zeiger für nicht verwaltete Klasse: * und Objekt erzeugen mit new

  //Ein neues Array (verwaltet) mit String wird so erzeugt.
  //array<String^>^ ret = gcnew array<String^>(count bzw. Anzahl von Elementen);
*/

/*
Alle unten stehende Methoden müssen richtig implementiert werden.
(connect,getKeys,getNames,getValue,getDataType)
Solange Übergabeparameter und Rückgabewerte nicht geändert werden, so muss auch nicht die Klasse 
CCorbaViewerForm modifiziert werden.
*/
//---------------------------------------------------------
bool CCorbaIdlWrapper::connect(String^ name)
{
  if (name == nullptr)
  {
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                        "Pointer of parameter <name> is null",
                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    return false;
  }

  /*
    Interface-Name wird in Form <Tracking_LF_1.context> übergeben
    Die restliche Kontextangabe ohne Slash am Ende befindet sich in ContextTable, als Key wird der Parameter name verwendet.
  */

  //String^ context = ((String^)this->ContextTable[name]);
  //String^ connString = context + "/" + name;
  
  //Testzweck***************
  if (name->Equals("xxx"))
    return false;
  //************************

  return true;
}
//---------------------------------------------------------
array<String^>^ CCorbaIdlWrapper::getKeys(String^ InterfaceName)
{
  if (InterfaceName == nullptr)
  {
    LogWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,
                            "Pointer of parameter <InterfaceName> is null",
                            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    return nullptr;
  }
  
  //Testzweck***************
  array<String^>^ ret = {"1","2","3","4","5"};
  return ret;
  //************************
}
//---------------------------------------------------------
array<String^>^ CCorbaIdlWrapper::getNames(String^ InterfaceName,String^ KeyName)
{
  //Testzweck***************
  array<String^>^ ret = {"1","2","3","4","5"};
  return ret;
  //************************
}
//---------------------------------------------------------
System::Text::StringBuilder^ CCorbaIdlWrapper::getValue(String^ InterfaceName,String^ key,String^ name)
{
  //Da Stingangabe groß sein kann, wird StringBuilder verwendet. 
  System::Text::StringBuilder^ ret = gcnew System::Text::StringBuilder();
  
  //Testzweck***************
  //System::IO::StreamReader^ sr = System::IO::File::OpenText("CorbaSeq.txt");
  String^ line = "This is a prototype feature and is in development phase";
  //while ((line = sr->ReadLine()) != nullptr)
    ret->AppendLine(line);
  //************************
  return ret;
}
//-----------------------------------------------------------
String^ CCorbaIdlWrapper::getDataType(String^ InterfaceName,String^ key,String^ name)
{
  //Testzweck***************
  return "none";
  //Testzweck***************
}
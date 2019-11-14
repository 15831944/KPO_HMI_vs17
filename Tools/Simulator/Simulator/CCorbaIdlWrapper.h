#ifndef _CCorbaIdlWrapper_H_
#define _CCorbaIdlWrapper_H_

#include "CLogWriterWrapper.h"

using namespace System;
/*
  Diese Klasse ist eine Wrapperklasse. 
  Sie stellt die Schnittstellen bereit, welche ausschlißlich im verwalteten Code verwenden werden.
  Diese werden benötigt, um Daten aus Corba - System aufzurufen und in der grapischer Oberfläche 
  darzustellen. Die Änderung von diesen Schnittstellen und deren Parameter erordert Modifikation
  des Quellcode in der Klasse <CCorbaViewerForm>.
  Zusätzlich werden in dieser Klasse die Parameter wie <Corba_Context> und <Corba_Interfaces> aus
  der Simulator.ini gelesen. In der Klasse sind Corba - Instanzen enthalten.
*/
public ref class CCorbaIdlWrapper
{
  public: CCorbaIdlWrapper()
        {
          LogWriter = CLogWriterWrapper::getLogWriterWrapper();
          CorbaContext = nullptr;
          CorbaInterfaces = nullptr;
          ContextTable = gcnew Collections::Hashtable();
          ReadIniFile();
        }

  public: array<String^>^ getInterfaceNames();
        array <String^>^ getContext();
        /*
        Fünf folgende Methoden müssen implementiert werden, sobald Corba - Anbindung existiert.
        Momentan werden Default - Werte zur Testzwecken verwendet.
        */
        //Diese Methode stellt die Verbinung der angegebenen Interface her.
        //Richtige Connection-String wird in dieser Methode erzeugt.
        bool connect(String^ name);
        array<String^>^ getKeys(String^ InterfaceName);
        array<String^>^ getNames(String^ InterfaceName,String^ KeyName);
        System::Text::StringBuilder^ getValue(String^ InterfaceName,String^ key,String^ name);
        String^ getDataType(String^ InterfaceName,String^ key,String^ name);
        
  private:             
        //Als Blockname wird immer tieferste Context aus kompletem Contextpfad entnommen.
        //Der Eintrag in .ini Datei sieht beispielsweise wie folgt aus:
        //[Tracking_LF_1.context]
        //Interface1=DM_LF_1DataInterface.CORBA_Object
        //Interface2=DM_LF_1ProductManagementInterface.CORBA_Object
        //Interface3=DM_LF_1PlantManagementInterface.CORBA_Object
        array<String^>^ CorbaInterfaces;
        //Diese Methode liest die Einträge aus der Simulator.ini
        void ReadIniFile();
        CLogWriterWrapper^ LogWriter;
        //Der Eintrag in .ini Datei sieht beispielsweise wie folgt aus:
        //[Corba_Context]
        //Context=Tracking_LF_1POA.context/Tracking_LF_1.context
        array <String^>^ CorbaContext;
        //In der HashTabelle wird jeder Interface die Kontextangabe zugeordnet.
        Collections::Hashtable^ ContextTable;
};
#endif
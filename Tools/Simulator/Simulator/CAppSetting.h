// Copyright 2006 SMS - Demag AG

#ifndef _CAppSetting_H_
#define _CAppSetting_H_

//-------------------------------------------------------------
#include "IniFile.h" 
#include "CRelPathManager.h"
//--------------------------------------------------------------
using namespace System;
//-------------------------------------------------------------
//-------------------------------------------
// Name:  CAppSeting.h
// Descr: Mit dieser Klasse wird die Initialisierungsdatei bearbeitet.
//        Es wird einziges Objekt von dieser Klasse erzeugt(Singelton)
//        Um IniFile zu bearbeiten benutzt diese Klasse "Free Ware CIniFile"
//        (www.sourceforge.net)
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CAppSetting
{
  public:
    //! gibt true wenn dynamische adaption erwünscht ist zurück.
    bool useDynamicAdaptation();
    //! gib das Objekt der Klasse CAppSeting zurueck
    static CAppSetting^ getApp();
    //! prueft,ob Initialisierungsdatei existiert
    bool checkIniFile();
    //! prueft, ob Konfigurationsdatei fuer die 
    //  Schnittstelle existiert
    bool checkInterConfigFile(String^ name);
    //! erzeigt eine Initialisierungsdatei
    void createIniFile();
    //! fuegt den Pfad von einer Schnittstellenzpesifikationsdate
    //  in Initialsisierungsdatei zu
    void addInterface(String^ path);
    //! fuegt den Pfad zu einer Schnittstellenkonfigurationsdatei 
    //  in Initialisierungsdatei zu
    void addInterfaceConfigFile(String^ path,String^ interName);
    //! fuegt den Pfad zu einer Schnittstellenkonfigurationsdatei 
    //  in Initialisierungsdatei zu
    void addInterDefaultConfigFile(String^ path,String^ interName);
    //!
    array <String^>^ getInterfacePath();
    //! gibt den Pfad zum Verzeichniss mit Telegramm - Log - Files
    String^ getLogFileDirectory();
    //!  setzt den Pfad zum Verzeichniss mit Telegramm - Log - Files
    void setLogFileDirectory(String^ directory);
    //! gibt den Pfad zum Verzeichniss mit Szenariumdateien
    String^ getSzenDirectory();
    //!  setzt den Pfad zum Verzeichniss mit Szenariumdateien
    void setSzenDirectory(String^ directory);
    //! gibt den Pfad zum Verzeichniss mit Schnittstellenspezifikationsdateien
    String^ getInterDirectory();
    //! setzt den Pfad zum Verzeichniss mit Schnittstellenspezifikationsdateien
    void setInterDirectory(String^ directory);
    //! gibt den Pfad zum Verzeichniss mit LogFiles zu Analysieren
    String^ getAnalyzerDirectory();
    //! setzt den Pfad zum Verzeichniss mit LogFiles zu Analysieren
    void setAnalyzerDirectory(String^ directory);
    //! gibt den Pfad zum Verzeichniss mit Connectionskofigurationsdateien
    String^ getConnDirectory();
    //! setzt den Pfad zum Verzeichniss mit CyclicTelegrammskofigurationsdateien
    void setCyclicDirectory(String^ directory);
    //! gibt den Pfad zum Verzeichniss mit Connectionskofigurationsdateien
    String^ getCyclicDirectory();
    //! setzt den Pfad zum Verzeichniss mit CCyclicTelegrammskofigurationsdateien
    void setConnDirectory(String^ directory);
    //! gibt den Name der Initialisierungsdatei
    String^ getIniFileName();
    //! gibt den Pfad zu dem Verzeichniss, wo Ausfuehrbare Datei liegt.
    String^ getWorkingDirectory();
    //! gibt den Pfad zu Schnittstellenkonfigurationsdatei einer Schnittstelle
    String^ getInterConfigFilePath(String^ inter);
    //! entfernt Info ueber eine Schnittstelle aus Inizialisierungsdatei
    void removeInterface(String^ inter);
    //! schreibt Namen der zuletztbenutzen Schnittstelle in die Inizialisierungsdatei   
    void setLastActivInterfaceName(String^ inter);
    //! gibt Namen der zuletzbenutzten Schnittstelle
    String^ getLastActivInterfaceName();
    //!
    void setMessageTypsInLogFiles(array <String^>^ messTyps);
    //!
    array <String^>^ getMessageTypsInLogFiles();
    //!
    void setMaxSizeOfLogFiles(String^ size);
    //!
    String^ getMaxSizeOfLogFiles();
    //!
    void setMaxCountOfLogFiles(String^ count);
    //!
    String^ getMaxCountOfLogFiles();
    //!
    void setNodesInTlgViewCollapsed(String^ value);
    //!
    String^ getNodesInTlgViewCollapsed();
    //!
    array <String^>^ getCorbaInterfaces(String^ context);
    //!
    array <String^>^ getCorbaContext();
    //! Der Pfad zu Inizialisierungsdatei
    String^ IniName;

    // der Header aus dem Interface
    String^ getHeaderTlg();

  protected:
    CAppSetting();

  private:
    //! Durch das Attribute wird auf das Objekt(Singelton) der Klasse CAppSetting zugegriffen 
    static CAppSetting^ AppSetting=nullptr;
    static CRelPathManager^ RelPath = nullptr;
};

#endif
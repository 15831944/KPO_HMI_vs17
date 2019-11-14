// Copyright 2006 SMS - Demag AG

#ifndef _CItemBaseContainerWrapper_H_
#define _CItemBaseContainerWrapper_H_

#include "CItemWrapper.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

//-------------------------------------------
// Name:  CTlgBaseContainerWrapper.h
// Descr: Eine abstrakte Klasse, die ein Container fuer
//        Telegramme darstellt
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------

public ref class CItemBaseContainerWrapper
{
  public:
    CItemBaseContainerWrapper();
    virtual ~CItemBaseContainerWrapper();
    //! gibt eine Referenz aufs Telegramm aus dem Telegrammcontainer zurueck
    //  Parametern:
    //  id -  Position des Telegramms im Container.
    virtual CItemWrapper^ getTlg(int id) = 0;
    //! gibt eine Referenz aufs Telegramm aus dem Telegrammcontainer zurueck
    //  Parametern:
    //  tlgName - Name des Telegramms im Container.
    virtual CItemWrapper^ getTlg(String^ tlgName)=0;
    //! gibt eine Copie des Telegramms aus dem Telegrammcontainer zurueck
    //  Parametern:
    //  tlg - enthaelt zurueck gegebenes Telegramm
    //  id -  Position des Telegramms im Container.
    virtual void getClonedTlg(CItemWrapper^ tlg,int id) = 0;
    //! gibt eine Copie des Telegramms aus dem Telegrammcontainer zurueck
    //  Parametern:
    //  tlg - enthaelt zurueck gegebenes Telegramm
    //  tlgName -  Name des Telegramms im Container.
    virtual void getClonedTlg(CItemWrapper^ tlg,String^ tlgName)=0;
    //! fuellt Container mit Telegrammen aus einer Datei
    // CTlgInterfaceWrapper - Schnittstellenspezifikationdatei
    // CTlgLogFileReaderWrapper - Telegramm - Log - File
    virtual int loadFromFile(String^ path,bool const&abort)=0;
    //! //! gibt eine Kopie des Telegramms aus dem virtuelle Telegrammcontainer zurueck
    //  Parametern:
    //  tlg - enthaelt zurueck gegebene Telegramm
    //  id -  Position des Telegramms in Container.
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,int id) = 0;
    //!
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName)=0;
    //! gibt Description des Telegramms zurueck
    //  CTlgInterfaceWrapper - Description des Telegramm
    //  CTlgLogFileReaderWrapper - Telegrammzeit aus Telegramm - Log - File
    //  CTlgContainerWrapper - Zeit des Telegramms
    virtual String^ getVirtualTlgDescr(int id)=0;
    //!
    virtual String^ getTlgTimeAsString(int id)=0;
    //!
    virtual int getTlgCount()=0;
    //--------------------------------------------
    // virtuelle Methode
    //--------------------------------------------
    //!
    virtual void reset(); 
    //!
    virtual void clearContainer();
    //!
    virtual double getTlgTime(int id);
    //!
    virtual double getVirtualTlgTime(int id);
    //-----------------------------------------------
    //   nicht virtuelle Methode
    //-----------------------------------------------
    //!
    int getVirtualTlgCount();
    //!
    String^ getPathFile();
    //!
    void setSelectedItem(int item);
    //!
    int getSelectedItem();
    //!
    bool setFilterByRegExp(array <String^>^ reg);
    //!
    void setFilterByPositions(List<int>^ pos);
    //!
    void setFilterByTelName(ArrayList^ nameListe);
    void setFilterByInterfaceName(String^ inter);
    void removeFromVirtuallContainer(int pos);
    int findTelegramm(int pos,String^ tlgName);
    int findTelegramm(int pos,String^ tlgName,String^ elemName,String^ rel,String^ val);
    //void addSortCondition(String^ tel,String^ elem,String^ subElem);
    void addSortCondition(String^ tel,String^ elemPath);
    void sortContainer();
    String^ getErrorMessage();
		//!
    value struct SortConditionTyp
    {
      String^ TlgName;
      //String^ ElemName;
      //String^ SubElemName;
      String^ ElemNamePath;
    };
    String^ getFilterRegExpAsString();
    array <String^>^ getFilterRegExpAsStringArray();
    //-----------------------------------------------
  protected:
    //!
    ArrayList^ SortConditonArray;
    //!
    String^ ErrorMessage;
    //!
    String^ Path;
    //!
    ArrayList^ VirtuallContainer;
    //!
    int SelectedItem;
    //!
    array <System::Text::RegularExpressions::Regex^>^ regExpArray;

    String^ regToNetReg(String^ reg);
    String^ treatmentOfStar(String^ reg);
    String^ treatmentOfQuestionMark(String^ reg);
    int getPosInContainer(String^ val,ArrayList^ list,int unten,int oben,String^ ElemName);
};


#endif
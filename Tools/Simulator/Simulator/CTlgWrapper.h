// Copyright 2006 SMS - Demag AG

#ifndef _CTlgWrapper_H_
#define _CTlgWrapper_H_

//------------------------------------------
#include "CTlg.h"
#include "CTlgElem.h"
#include "CTimeWrapper.h"
#include "CExpWrapper.h"
#include "CItemWrapper.h"
#include "CTlgElem.h"

using namespace System;
//-------------------------------------------
// Name:  CTlgWrapper.h
// Descr: Diese Klasse dient als "verwalteter" Wrapper 
//        fuer die Klasse CTlg
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CTlgWrapper : public CItemWrapper
{
  public:
    CTlgWrapper();
    ~CTlgWrapper();

    //! gibt die Referenz aufs Tlg
    virtual CTlg* getTlg() override;
    //! ersetzt CTlg
    virtual bool updateTlg(CItemWrapper^ w_tlg) override;
    //!
    virtual array <String^>^ getElemAsStringArray(int i,int* elemFlag) override;
    //!
    virtual array <String^>^ getElemProtoTypInfo(int i,int* elemFlag) override;
    //! gebt Applicationstyp eines Telegrammelements zurueck
    //! Rueckgabewert:
    //  1 - Rekords
    //  2 - Array
    //  0 - fuer andere Applicationstypen
    virtual int getElemTyp(int id) override;
    //! gibt die Anzahl der Telegrammelemente zurueck
    virtual int getTlgElemCount() override;
    //! wechselt das referenzierte Objekt der Klasse CTlg
    virtual void setTlg(CTlg* tlg) override;
    //! gibt den Wert des Telegrammelemets als String^ zurueck
    virtual String^ getElemValue(int id) override;
    //! gibt die Anzahl der Subelementen in einem Telegrammelemente zurueck 
    virtual int getSubElemCount(int id) override;
    //! gibt die Eigenschaften des Subelements eines Telegrammelemente zurueck
    virtual void getSubElementDescr(int elemId,int subId,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max) override;
    //! gibt die Laenge eines Subelement eines Telegrammelements zurueck
    virtual int getSubElemLen(int elemId,int subId) override;
    //! gibt den Name eines Subelement eines Telegrammelements zurueck
    virtual String^ getSubElemName(int elemId,int subId) override;
    //! gibt den Wert des Subelements eines Telegrammelements zurueck 
    virtual String^ getSubElemValue(int elemId,int subId) override;
    virtual String^ getSubElemValue(String^ elemId,String^ subElemId) override;
    //! gibt den Name des Telegramms zurueck
    virtual String^ getName() override;
    //! gibt die Laenge des Telegramm ohne Header zuruck
    virtual int getTlgBodyLen() override;
    //! gibt die Laenge des Telegrammheaders zurueck
    virtual int getTlgHeaderLen() override;
    //! gibt die Laenge des Telegramms zurueck
    virtual int getTlgLen() override;
    //! gibt eine Kopie des Objekt der Klasse CTlgWrapper zurueck
    virtual CItemWrapper^ clone() override;
    //! kodiert das Telegramm in Byte - Stream
    virtual int getSerializeTlg(char* buffer,int length) override;
    //! gibt die Telegrammelemente as Folge von ascii - Zeichen zurueck
    virtual String^ getSerialiseTlgAsString(String^ del) override;
    //!
    virtual CTlgElem* getElem(int id) override;
    //! gibt den Name eines Telegrammelements zurueck
    virtual String^ getElemName(int id) override;
    ////! gibt den eines TelegrammElement(SubElement) bezueglich Angabe der Tiefebene zurueck
    //virtual String^ getElemName(int level,int id);
    //! gibt Description des Telegramms zurueck
    virtual String^ getTlgDescr() override;
    //! gibt die Richtung des Telegramms(Senden,Empfangen) als String^ zurueck
    virtual String^ getTlgDirection() override;
    //! gibt Description eines Telegrammelements zurueck
    virtual String^ getElemDescr(int id) override;
    //! gibt Eigenschaften eines Telegrammelements zurueck
    virtual void getElementDescr(int id,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max) override;
    //! gibt die Laenge eines Telegrammelements zurueck
    virtual int getElemLen(int id) override;
    //! fuellt das Telegramm mit Daten
    virtual String^ fillTlg(String^ line) override;
    //! erzeigt eine kopie vom gekapselten Objekt der Klasse CTlg
    //  und gibt diese zurueck
    virtual CTlg* getClonedTlg() override;
    //! gibt den Name der Schnittstelle zurueck
    virtual String^ getInterfece() override;
    //! gibt die Position eines Telegrammelements in Telegramm zurueck
    virtual int getElemIndex(String^ elem) override;
    //! gibt die Position eines Subelements in komplexes Telegrammelement zurueck
    virtual int getSubElemIndex(String^ elem,String^ subElem) override;
    //! gibt Applicationstyp eines Telegrammelements als String^ zurueck
    virtual String^ getElemTypAsString(int id) override;
    //! gibt Applicationstyp eines Subelements des Telegrammelements als String^ zurueck
    virtual String^ getSubElemTypAsString(int elem,int subelem) override;
    //! gibt den Speicher von gekappseltem Objekt der Klasse CTlg frei
    virtual void clearWrapperTlg() override;
    //! gibt den Zeiger auf Subelement zurueck
    virtual CTlgElem* getTlgElem(String^ elemPathName) override;
    //! dekodiert Byte - Stream in das Telegramm
    virtual int decodeTlg(char* bytes,int count) override;
    //! vergleicht den Wert eines Telegrammelements mit val
    virtual int compareElem(String^ elemName,String^ subElemName,String^ val) override;
    virtual int getTlgTransBytesCount() override;
    virtual int getTlgBodyTransBytesCount() override;
    virtual int getSubElemTransBytesCount(int index) override;
    virtual int getElemNummber(int elem,int subElem) override;
    virtual bool CTlgWrapper::getTlgEmpty() override; 
    virtual Collections::ArrayList^ createNumberElemList() override;
    //String^ getSerializeTlgAsByteSteam();
  protected:
    //! Referenziert ein Objekt der Klasse CTlg
    CTlg* Tlg;
    void createNumberElemListRekursiv(Collections::ArrayList^ ret,CTlgElem* elem);
};

#endif
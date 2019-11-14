#ifndef _CItemWrapper_H_
#define _CItemWrapper_H_

#pragma warning( disable : 4570 )

#include "CTlg.h"
#include "CTlgElemWrapper.h"
#include "CTlgElem.h"

using namespace System;


public ref class CItemWrapper
{
public:
  CItemWrapper(void);
  virtual ~CItemWrapper(void);
	//! gibt die Referenz aufs Tlg
  virtual CTlg* getTlg() = 0;
  //! ersetzt CTlg
  virtual bool updateTlg(CItemWrapper^ w_tlg) = 0;
  //!
  virtual array <String^>^ getElemAsStringArray(int i,int* elemFlag)  = 0;
  //!
  virtual array <String^>^  getElemProtoTypInfo(int i,int* elemFlag) = 0;
	//! gebt Applicationstyp eines Telegrammelements zurueck
  //! Rueckgabewert:
  //  1 - Rekords
  //  2 - Array
  //  0 - fuer andere Applicationstypen
  virtual int getElemTyp(int id) = 0;
  //! gibt die Anzahl der Telegrammelemente zurueck
  virtual int getTlgElemCount() = 0;
  //! wechselt das referenzierte Objekt der Klasse CTlg
  virtual void setTlg(CTlg* tlg) = 0;
  //! gibt den Wert des Telegrammelemets als String^ zurueck
  virtual String^ getElemValue(int id) = 0;
  //! gibt die Anzahl der Subelementen in einem Telegrammelemente zurueck 
  virtual int getSubElemCount(int id) = 0;
  //! gibt die Eigenschaften des Subelements eines Telegrammelemente zurueck
  virtual void getSubElementDescr(int elemId,int subId,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max) = 0;
  //! gibt die Laenge eines Subelement eines Telegrammelements zurueck
  virtual int getSubElemLen(int elemId,int subId) = 0;
  //! gibt den Name eines Subelement eines Telegrammelements zurueck
  virtual String^ getSubElemName(int elemId,int subId) = 0;
  //! gibt den Wert des Subelements eines Telegrammelements zurueck 
  virtual String^ getSubElemValue(int elemId,int subId) = 0;
  virtual String^ getSubElemValue(String^ elemId,String^ subElemId) = 0;
  //! gibt den Name des Telegramms zurueck
  virtual String^ getName() = 0;
  //! gibt die Laenge des Telegramm ohne Header zuruck
  virtual int getTlgBodyLen() = 0;
  //! gibt die Laenge des Telegrammheaders zurueck
  virtual int getTlgHeaderLen() = 0;
  //! gibt die Laenge des Telegramms zurueck
  virtual int getTlgLen() = 0;
  //! gibt eine Kopie des Objekt der Klasse CTlgWrapper zurueck
  virtual CItemWrapper^ clone() = 0;
  //! kodiert das Telegramm in Byte - Stream
  virtual int getSerializeTlg(char* buffer,int length) = 0;
  //! gibt die Telegrammelemente as Folge von ascii - Zeichen zurueck
  virtual String^ getSerialiseTlgAsString(String^ del) = 0;
  ////! gibt den eines TelegrammElement(SubElement) bezueglich Angabe der Tiefebene zurueck
  //virtual String^ getElemName(int level,int id) = 0;
  //! gibt den Name eines Telegrammelements zurueck
  virtual String^ getElemName(int id) = 0;
  //!
  virtual CTlgElem* getElem(int id) = 0;
  //! gibt Description des Telegramms zurueck
  virtual String^ getTlgDescr() = 0;
  //! gibt die Richtung des Telegramms(Senden,Empfangen) als String^ zurueck
  virtual String^ getTlgDirection() = 0;
  //! gibt Description eines Telegrammelements zurueck
  virtual String^ getElemDescr(int id) = 0;
  //! gibt Eigenschaften eines Telegrammelements zurueck
  virtual void getElementDescr(int id,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max) = 0;
  //! gibt die Laenge eines Telegrammelements zurueck
  virtual int getElemLen(int id) = 0;
  //! fuellt das Telegramm mit Daten
  virtual String^ fillTlg(String^ line) = 0;
  //! erzeigt eine kopie vom gekapselten Objekt der Klasse CTlg
  //  und gibt diese zurueck
  virtual CTlg* getClonedTlg() = 0;
  //! gibt den Name der Schnittstelle zurueck
  virtual String^ getInterfece() = 0;
  //! gibt die Position eines Telegrammelements in Telegramm zurueck
  virtual int getElemIndex(String^ elem) = 0;
  //! gibt die Position eines Subelements in komplexes Telegrammelement zurueck
  virtual int getSubElemIndex(String^ elem,String^ subElem) = 0;
  //! gibt Applicationstyp eines Telegrammelements als String^ zurueck
  virtual String^ getElemTypAsString(int id) = 0;
  //! gibt Applicationstyp eines Subelements des Telegrammelements als String^ zurueck
  virtual String^ getSubElemTypAsString(int elem,int subelem) = 0;
  //! gibt den Speicher von gekappseltem Objekt der Klasse CTlg frei
  virtual void clearWrapperTlg() = 0;
  //! dekodiert Byte - Stream in das Telegramm
  virtual int decodeTlg(char* bytes,int count) = 0;
  //! gibt aus, ob Tgl - Objekt mit Werten gefuelt ist oder nicht
  virtual bool getTlgEmpty() = 0;
  //! gibt den Zeiger auf Subelement zurueck
  virtual CTlgElem* getTlgElem(String^ elemPathName) = 0;
  //! vergleicht den Wert eines Telegrammelements mit val
  virtual int compareElem(String^ elemName,String^ subElemName,String^ val) = 0;
  virtual int getTlgTransBytesCount() = 0;
  virtual int getTlgBodyTransBytesCount() = 0;
  virtual int getSubElemTransBytesCount(int index) = 0;
  virtual int getElemNummber(int elem,int subElem) = 0;
  virtual Collections::ArrayList^ createNumberElemList() = 0;
	//******************
};
#endif

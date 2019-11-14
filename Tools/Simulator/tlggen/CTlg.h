// Copyright 2006 SMS - Demag AG

#ifndef _CTlg_H_
#define _CTlg_H_

#pragma warning( disable : 4290 )

#include "CTokenParser.h"
#include <vector>
#include <string>

class CTlgElem;
class CExpInvalidTlg;
class CExpConvertError;
class CLogWriter;
//-------------------------------------------
// Name:  CTlg.h
// Descr: Mit dieser Klasse wird die Aufbaustruktur eines
//        Telegramms dargestellt.
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
//##ModelId=4404D3B201F4
class CTlg 
{
  public:
    CTlg(const std::string& name,int len,const std::string& direction,int descr);
    CTlg(const CTlg& Obj);
    ~CTlg();
    //! gibt der Name des Telegramms zurueck
    const std::string& getTlgName();
    //! git die kompllete Laenge des Telegramms zurueck 
    long getTlgLen();
    //! gibt die Laenge des Telegramms ohne Telegrammheader(aus Scnittstellenspezifikation)
    // zurueck.
    long getTlgBodyLen();
    //! gibt die Laenge des Telegrammsheader zurueck.
    long getTlgHeaderLen();
    //! 
    int getTransBytesCount() const;
    //!
    int getTranspBodyBytesCount();
    //!
    int getTranspHeaderBytesCount();
    //! Erzeugt eine Kopie von Telegramm
    CTlg* clone() const;
    //! Erzeugt eine Kopie von Telegrammelement
    CTlgElem* cloneElem(int id) const;
    //! Gibt den Zeiger auf Telegrammelement aus ElemListe zurueck
    CTlgElem* getFlatElem(const std::string& id) const;
    CTlgElem* getFlatElem(int id) const;
    //! fuegt ein neues Element in dem Telegramm hinzu
    void addElem(CTlgElem* elem);
    //! fuellt das Telegramm mit Daten
    bool load(const std::string& line) throw(CExpInvalidTlg,CExpConvertError);
    //! kodiert das Telegramm in Byte - Stream
    int serializeTlg(char* buffer,int len);
    //! dekodiert den Byte - Stream und fuellt Telegramm mit Daten
    int decodeTlg(char* bytes,int count);
    //! vergleicht den Wert eines Telegrammelements mit val
    //! Rueckgabewert:
    //! 1 - Wert > val
    //! -1 - Wert < val
    //! 0 - Wert = val;
    //! -2 Fehler
    int compareElement(const std::string& elemName,const std::string& subElemName,const std::string& val);
    void setDescription(const std::string& descr);
    const std::string& getDescription() const;
    const std::string& getDirection() const;
    long getDescrIndex() const;
    int getElemCount() const;
    void setEmpty(bool flag);
    bool getEmpty() const;
    void setInterfaceName(const std::string& name);
    const std::string& getInterfaceName() const;
    void getTlgAsString(std::string& tel,const std::string& del);
    int getElemOffset(const std::string& id) const;
  private:
    //! Container fuer Telegrammelemente
    std::vector<CTlgElem*> ElemListe;
    //! Die Nummer von Objekt der Klasse CTlgDescription in
    // der Registratur
    int DescrIndex;
    //! Dieses Attribut wird gesetzt, wenn das Telegramm
    // mit Daten gefuellt wird
    bool EmptyFlag;
    //! Schreiben in die Log Datei
    CLogWriter* LogWriter;
    void loadSubElement(CTlgElem* elem,CTokenParser* Parser);
    void freeTlgDescription();
};
#endif

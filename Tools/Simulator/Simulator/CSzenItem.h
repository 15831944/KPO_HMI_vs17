// Copyright 2006 SMS - Demag AG

#ifndef _CSzenItem_H_
#define _CSzenItem_H_

#include "CTlgWrapper.h"

using namespace System;

//======================================================================
//  NAME  : CSzenItem.h
//  DESCR : Diese Klasse repräsentiert ein Element eines Szenarium und 
//          kapselt intern ein Telegramm
//  DATE  :
//  AUTOR : Emeljanov Anatolij
//======================================================================
public ref class CSzenItem
{
  public:
    //! Mit diesem Konstruktor wird ein Objekt von CSzenItem 
    //erzeugt. Mit den uebergebene Paremeter werden Telegramm
    //und Zeit initialisiert.
    CSzenItem(CItemWrapper^ tlg,double time);
    ~CSzenItem();
    //Set- Methoden 
    void setDelay(double delay);
    void setItem(CItemWrapper^ tlg);
    void setSendStatus(bool stat);
    void setTime(double time);
    void setBreakPoint(bool flag);
    void setChangeTime(double changeTime);
    void acceptChangeTime(bool flag,double rel);
    void acceptChangeTime(bool flag,double rel,double t0,double d0);
    
    //Get - Methode
    double getDelay();
    String^ getItemName();
    double getTime();
    CItemWrapper^ getTlgWrapper();
    bool getSendStatus();
    String^ getItemAsString();
    String^ getInterface();
    bool getBreakPoint();
    bool getChangeTimeStatus();
    void setChangeTimeStatus(bool status);
    double getChangeTime();
    //! Mit dieser Methode wird Telegramm in Byie - Stream kodiert
    int getSerializeTlg(char* buffer,int length);
    //! Gibt Elemente des Telegramm als Folge der ASCII - Zeichen zurueck
    String^ SerializeTlgAsString();
      //String^ SerializeTlgAsByteStream();
    //! loescht Telegramm 
    void clearItem();
    //! Erzeugt ein Kopie von Objekt der Klasse CSzenItem 
    CSzenItem^ clone();
    int getTlgLen();
    int getTlgTransBytesCount();
    void setIsCyclic(bool cyclic);
    bool getIsCyclic();
    void setBarredDelay (double val);
    double getBarredDelay();
  private:
    //! Kapselt ein Telgramm
    CItemWrapper^ Tlg;
    //! Zeitverzoegerung des Telegramm
    double TimeDelay;
    //! Zeit des Telegramms
    double Time;
    //! noch nicht uebernommene Zeit
    double ChangeTime;
    //! Sendestatus des Telegramms
    bool SendStatus;
    //! Haltepunkt fuer Telegramm
    bool BreakPoint;
    //! Flag, wird gesetzt, wenn die neue Zeit noch nicht uebernommen wurde
    bool ChangeFlag;
    //! IsCyclci, wird gesetz, wenn es um ein zyklische Tlg handelt.
    bool IsCyclic;
    //! Bei dieser Zeitverzoegerung wird die Zeit des ausgeschlossenen Tlgs abgezogen.
    double TimeBarredDelay;
};
#endif
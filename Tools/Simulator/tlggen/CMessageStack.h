// Copyright 2006 SMS - Demag AG

#ifndef _CMessageStack_H_
#define _CMessageStack_H_

#include <string>
#include <vector>
#include <windows.h>
//--------------------------------------------
// Name:  CMessageStack.h
// Descr: Mit diesem Klasse werden Fehler- und Informationsmeldungen,
//        die waehrend der Bearbeitung der Telegrammdaten entstehen, gesammelt  
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
class CMessageStack
{
  public:
	  //! gibt das Objekt der Klasse zurueck
    static CMessageStack* getMessageStack();
    ~CMessageStack();
	  //! fuegt neues Message zum Container hinzu
    void addMessage(const std::string& mess,int type);
	  //! loescht alle Message aus dem Container
    void clearMessage();
	  //! gibt aktuelle Message zurueck
    bool getActMessage(std::string& mess,int* type);
    /*   CRITICAL_SECTION sec;*/
  protected:
    CMessageStack();
  private:
		//! Zeiger auf Objekt der Klasse
    static CMessageStack* MessageStack;
		//! Container mit Message
    std::vector<std::string> MessStack;
		//! Container mit Typ der Message(Error,Warnung,Info)
    std::vector<int> MessType;
		//! Nummer des Aktuellen Message
    int ActMess;
    bool getActMessage_(std::string& mess,int* type);
};
#endif

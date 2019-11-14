// Copyright 2006 SMS - Demag AG

#ifndef _CTlgContainer_H_
#define _CTlgContainer_H_

#include<string>
#include<map>
#include <vector>
#include "CLogWriter.h"
#include "CFormatConverter.h"

class CTlg;

//----------------------------------------------------
// NAME : CTlgContainer.h
// DESCR: Mit der Klasse wird Container mit Telegramme verwaltet
//        Die Klasse ist als Template - Klasse implementiert. 
//        Abhaengig von parameterisiertem Schlussel werden Telegramme
//        nach entsprechende Datentyp sortiert.
// DATE:
// AUTOR: Emeljanov Anatolij
//----------------------------------------------------
template<class T>
class CTlgContainer   
{
  public:
    virtual ~CTlgContainer();
    CTlgContainer();
		//! fuegt eint Telegramm zum Container hinzu, nachdem alle Telegramme hinzugefuegt sind,
    //! BuildIndex() - Methode aufrufen!
    void addTlg(const T& key ,CTlg* tlg);
	  //! fuegt zum Container Telegramme von anderen Container hinzu
	  void addContainer(CTlgContainer<T>& con);
	  //! gibt die Anzahl der Telegramme im Container zurueck
    int getTlgCount()const;
	  //! gibt den Zeiger auf ein Telegramm vom Container zurueck.
    CTlg* getFlatTlg(int id);
	  //!
		CTlg* getFlatTlg(const T& id);
		//! gibt den Scluessel von einem Telegramm zurueck
		T getKeyTlg(int id);
		//!
		void freeTlg(bool DeleteTlgObjects);
    //!
		std::multimap<T,CTlg*>* getCon();
		//! 
    void BuildIndex();

  private:
    //! Vectror - Container mit Telegrammen, ermoeglicht schnellen indexbasierten Zugriff,
		std::vector <CTlg*> TlgVectrorContainer;
		//! Container mit Telegrammen
    std::multimap<T,CTlg*>* TlgContainer;
    //! Schreiben in die Log Datei
    CLogWriter* LogWriter;
};
//---------------------------------------------------------------------
template<class T>
CTlgContainer<T>::CTlgContainer()
{
  LogWriter = CLogWriter::getLogWriter();
  //TlgVectrorContainer = new std::vector <CTlg*>();
	TlgContainer = new std::multimap<T,CTlg*>();
  freeTlg(true); 
}
//---------------------------------------------------------------------
template<class T>
CTlgContainer<T>::~CTlgContainer()
{
  delete TlgContainer;
}
//---------------------------------------------------------------------
template<class T>
void CTlgContainer<T>::addTlg(const T& key,CTlg* tlg)
{
  TlgContainer->insert(std::pair<T,CTlg*>(key,tlg));
}
//---------------------------------------------------------------------
template<class T>
void CTlgContainer<T>::addContainer(CTlgContainer<T>& con)
{
  CTlg* tlg=0;
	T key;
  std::multimap<T,CTlg*>::iterator iter;
  for(iter=con.getCon()->begin();iter != con.getCon()->end();++iter)
  {
    key = iter->first;
    tlg = iter->second;
    this->addTlg(key,tlg);
  }
  std::string mess = "New container with telegrams added.";
  LogWriter->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
	//Index neu bilden
	BuildIndex();
}
//---------------------------------------------------------------------
template<class T>
int CTlgContainer<T>::getTlgCount()const
{
	return (int)TlgContainer->size();
}
//---------------------------------------------------------------------
template<class T>
CTlg* CTlgContainer<T>::getFlatTlg(const T& id)
{
	CTlg* tlg=0;
	std::multimap<T,CTlg*>::iterator iter = TlgContainer->find(id);
	if(iter != TlgContainer->end())
		tlg = iter->second;

	return tlg;
}
//---------------------------------------------------------------------
template<class T>
CTlg* CTlgContainer<T>::getFlatTlg(int id)
{
	if (((size_t)id <= TlgVectrorContainer.size()) && (id > 0))
		return TlgVectrorContainer[id-1];
	else
		LogWriter->WriteMessage(CLogWriter::Error,
                            "tlg with id <" + CFormatConverter::IntToString(id) + "> not exist",
                            __FILE__,__FUNCTION__,__LINE__);
  return 0;
}
//---------------------------------------------------------------------
template<class T>
T CTlgContainer<T>::getKeyTlg(int id)
{
	T ret=0;
	if(((size_t)id <= TlgContainer->size()) && (id > 0))
  {
		std::multimap<T,CTlg*>::iterator iter = TlgContainer->begin();
    std::advance(iter,id-1);
		ret = iter->first;
	}
  else
    LogWriter->WriteMessage(CLogWriter::Error,
                            "tlg with id <" + CFormatConverter::IntToString(id) + "> not exist",
                            __FILE__,__FUNCTION__,__LINE__);
  return ret;
}

//---------------------------------------------------------------------
template<class T>
std::multimap<T,CTlg*>* CTlgContainer<T>::getCon()
{
  return TlgContainer;
}
//---------------------------------------------------------------------
template<class T>
void CTlgContainer<T>::freeTlg(bool DeleteTlgObjects)
{
  if (DeleteTlgObjects)
  {
    std::multimap<T,CTlg*>::iterator iter;
    for(iter=TlgContainer->begin();iter != TlgContainer->end();++iter)
    {
      delete iter->second;
    }
    std::string mess = "All telegram objects removed.";
    LogWriter->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  TlgContainer->clear();
	TlgVectrorContainer.clear();
}
//---------------------------------------------------------------------
template<class T>
void CTlgContainer<T>::BuildIndex()
{
	TlgVectrorContainer.clear();
	std::multimap<T,CTlg*>::iterator iter;
	for(iter=TlgContainer->begin();iter != TlgContainer->end();++iter)
		TlgVectrorContainer.insert(TlgVectrorContainer.end(),iter->second);
  std::string mess = "Verctor - list of telegram (re)buildet.";
  LogWriter->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);
}
//---------------------------------------------------------------------
#endif

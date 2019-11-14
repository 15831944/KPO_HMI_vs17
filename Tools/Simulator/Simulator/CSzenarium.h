//	Copyright 2006 SMS - Demag AG

#ifndef _CSzenarium_H_
#define _CSzenarium_H_

//---------------------------------------------
#include "CSzenItem.h"
#include "CTlgWrapper.h"
#include "CTimeWrapper.h"
#include "CTlgContainerWrapper.h"
#include "CInterBaseManager.h"
#include "CInterConfigWrapper.h"
#include "CItemWrapper.h"

//---------------------------------------------
using namespace System::Collections;
//---------------------------------------------

//---------------------------------------------
//======================================================================
//	NAME  : CSzenItem.h
//	DESCR : Ein Objekt dieser Klasse stellt ein Szenarium dar. Diese Klsse
//			    beinhaltet ein Container für Objekten der Klasse CSzenItem
//	DATE  :
//	AUTOR : Emeljanov Anatolij
//======================================================================
public ref class CSzenarium
{
    public: delegate void MessageScenSafeProgressDelTyp(int count);
    public: delegate void MessageScenarioDelTyp(String^ mess);
    public: delegate void UpdateRemoveCyclicTlgInScenarioDelTyp(int count);
    public:
      CSzenarium();
      ~CSzenarium();
			//! Fuegt ein Element zum Szenarium zu. Entsprechend dem Wert
			//des Parameters time wird das neue Telegramm im Container einsortiert
		  int addToSzenarium(CItemWrapper^ tlg,double time);
			//! Mit dieser Methode wird ein neues Telegramm im Container auf den 
			//Platz, der durch Parameter index festgelegt ist, eingefuegt
			void addToSzenarium(CItemWrapper^ tlg,int index);
      //! fuegt item zum Szenarium hinzu
      int addToSzenarium(CSzenItem^ item);
			//! Mit dieser Methode wird ein Element, dessen Position im Container 
			//durch den Parameter index festgelegt ist, aus dem Container entfernt.
			void remouteAt(int index);
			//! Mit dieser Methode wird durch den Parameter index festgelegtes
			//Element des Szenariums geaendert.
			void updateItem(int index,CItemWrapper^ tlg);
			//! Mit dieser Methode wird durch den Parameter index festgelegtes
			//Element die  neue Verzoegerungszeit gesetzt und die neue Zeit 
			//berechnet. Anschliessend wird dieses Element neu einsortiert.
			int updateItem(int index,double delay);
			//! Mit dieser Funktion werden Kopien des Szenariumselements erzeugt.
			// index - legt das Element fest
			// count - Anzahl der Kopien
			void duplicateItem(int index,int count);
			//! Mit dieser Funktion werden zwei Elementen des Szenariums 
			//umgetauscht.
      void swapItems(int index1,int index2);
      //! Liest Szenatio Datei stueckweise aus.      
      bool readScenarioFromFileInPart(System::IO::StreamReader^ sr,ArrayList^ protoSet,
                                      int TlgCount,double &t0,String^ name, double rel,String^ path
                                      ,double &d0_par,int haveTime);
			void setDelayRel(double rel);
			double getDelayRel();
			//! Berechnet die Verzoegerungszeiten fuer Elemente des Szenarium abhaengig
			//von den Werte der Attributen DelayRel und Time 
      void calcDelay();
			//! Setzt das Attribut DelayRel mit del und ruft die Methode calcDelay() auf
      void calcDelay(double rel);
			//! Die Methode setzt einfache Verzoegerungszeiten fuer Elemente des Szenariums
			//del - Zeitabstand zwischen zwei aufeinander folgende Telegramme
			void setSimpleDelay(double del);
			//! Verschiebt Verzoegerungszeiten der Elemente des Szenarium
			// offset - Um diesen Wert werden Verzoegerungszeiten verschoben.
			void moveDelay(double offset);
			//! Entfernt alle Elemente aus dem Szenarium
      void clearSzenarium();
      int getSzenItemCount();
      CSzenItem^ getSzenItem(int pos);
      int getSerializeTlg(int id,char* buffer,int length);
      void setName(String^ name);
      String^ getName();
			String^ getSzenItemAsString(int id);
      CItemBaseContainerWrapper^ getSzenariumContainer();
      void setFocusedItem(int index);
      int getFocusedItem();
      void setSzenChangeModus(bool flag);
      bool getSzenChangeModus();
			void setPath(String^ szenPfad);
			String^ getPath();
      void setSendSzenItem(int index);
      int getSendSzenItem();
      void removeAllInterTlgFromSzenarium(String^ inter);
			void acceptChangeTime();
      void readScenarioFromFile(String^ path,ArrayList^ protoSet);
      void setMessScenDel(MessageScenarioDelTyp^ del);
      void setMessageScenSafeProgressDel (MessageScenSafeProgressDelTyp^ del);
      void setUpdateRemoveCyclicTlgInScenarioDel (UpdateRemoveCyclicTlgInScenarioDelTyp^ del);
      CInterBaseManager^ getProtoInterface(String^ interName,ArrayList^ liste);
      void saveSzenarium(String^ path);
      CItemWrapper^ findItemFromSzenarium(String^ name);
      void setAllSameItemToCyclic(CItemWrapper^ item,bool mod);
      void removeAllCyclicTlg();
      bool TlgsFromInterInSzenario(String^ interName);
    private:
      //! Diese Tabelle enthalt die Anzahl der Telegramme im Szenario zu jeder Schnittstelle
      Hashtable^ InterCounterTable;
      //! HashMap, enthaelt Namen aller zyklischen Tlgs im Szenario,
      //! Key in HashMap wird als String aus dem Interfacename und aus 
      //! dem TlgName zusammengesetzt.
      Hashtable^ CyclicTable;
      //! Container fuer Objekte der Klasse CSzenItem
      ArrayList^ ItemArray;
			//! Dieser Container enthaelt die Nummern der 
			//Elemente von ItemArray in richtige Zeitreihenfolge
			ArrayList^ IndexArray;
			//! Name des Szenariums
      String^ Name;
			//! Pfad zur Szenariumdatei, mit der das Szenarium 
			//initialisiert ist. Wenn das Szenarium ohne eine
			//Szenariumdatei erstellt wurde,wird Path gleich NULL
			String^ Path;
			//! Relation zwischen Verzoegerung und reale Zeit.
			//Wenn DelayRel gleich 1 ist, wird die Telegramme in 
			//realle Zeit verscickt.
      double DelayRel;
			//! Die Nummer das ausgewaehlte Element des Szenarium 
      int FocusedItem;
      int SendItem;
			//! Dieses Attribut witd gesetzt, wenn Datenzustand des Szenarium
			//geaendert wurde.
      bool ChangeSzenFlag;

      MessageScenarioDelTyp^ MessageScenarioDel;
      MessageScenSafeProgressDelTyp^ MessageScenSafeProgressDel;
      UpdateRemoveCyclicTlgInScenarioDelTyp^ UpdateRemoveCyclicTlgInScenarioDel;

			int getIndex(double time,int unten,int oben);
			void addIndex(int index,int value);
      void indexCorection(int val);
      void CompareConfigIdWithFileId (CItemWrapper^ item,CInterConfigWrapper^ interConfig);
      void AddToInterCounterTable(String^ interName);
};
#endif

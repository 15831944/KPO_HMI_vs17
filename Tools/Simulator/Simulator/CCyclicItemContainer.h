
#ifndef _CCyclicItemContainer_H_
#define _CCyclicItemContainer_H_

#include "CCyclicItemContainer.h"
#include "CCyclicElemTable.h"
#include "CItemWrapper.h"
#include "CSzenarium.h"
#include "CInterConnectionListe.h"

using namespace System;

public ref class CCyclicItemContainer
{
public: delegate void WriteMessageDelTyp (String^ mess,int typ);
  public:
    ~CCyclicItemContainer();
    static CCyclicItemContainer^ getCyclicItemContainer();
    void addItemToContainer (String^ interName, CItemWrapper^ item, bool isProtoItem);
    void addItemToContainer (String^ interName, CItemWrapper^ item,CCyclicElemTable^ elemTable, bool isProtoItem);
    void setWriteMessageDelTyp(WriteMessageDelTyp^ typ);
    CCyclicElemTable^ getElemTable(String^ interName,CItemWrapper^ item);
    CCyclicElemTable^ getElemTable(String^ interName,String^ itemName);
    void iterReset();
    String^ getNextInterface();
    CCyclicElemTable^ getNextItem(String^ interName);
    int getInterfaceCount();
    CItemWrapper^ getLastAddedItem();
    bool isItemInContainer(CItemWrapper^ item);
    void addSzenariumPointer(CSzenarium^ szen);
    void removeSzenariumPointer();
    bool removeItem(CItemWrapper^ item);
    void Send(CInterConnectionListe^ SendInterConnectionListe);
    void StopAll();
    int getCountOfInterface();
    bool IsSending();
    bool TlgsFromInterInCyclicCon(String^ interName);
  protected:
    CCyclicItemContainer();

  private:
    Collections::Hashtable^ ThreadTable;
    CSzenarium^ Szenarium;
    Collections::Hashtable^ InterfaceTable;
    static CCyclicItemContainer^ cyclicItemContainer=nullptr;
    System::Collections::IEnumerator^ iterator;
    String^ lastInterName;
    System::Collections::IEnumerator^ iteratorOfItem;
    CItemWrapper^ lastAddedItem;
    WriteMessageDelTyp^ writeMessage;

    void SendCyclicItem(System::Object^ obj);
    ArrayList^ findAllNumericElem (CItemWrapper^ item);
    void findAllNmericSubElem (CTlgElemWrapper^ elem, ArrayList^ liste);
    bool setIdFromConfiguration(CItemWrapper^ item);
    bool LoadFormInterConf (CItemWrapper^ item);
};
#endif
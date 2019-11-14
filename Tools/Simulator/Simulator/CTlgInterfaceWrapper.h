// Copyright 2006 SMS - Demag AG

#ifndef _CTlgInterfaceWrapper_H_
#define _CTlgInterfaceWrapper_H_
//------------------------------------------------------
//------------------------------------------------------
#include "CTlgProtoTypSet.h"
#include "CItemBaseContainerWrapper.h"
#include "CTlgWrapper.h"
#include "CExpWrapper.h"
#include "CExpUnknownTlg.h"
#include "CXmlTlgProtoTypeReader.h"
//-------------------------------------------------------
using namespace System;
//using namespace System::Collections;
//-------------------------------------------------------
//-------------------------------------------
// Name:  CTlgInterfaceWrapper.h
// Descr: Wrapper fuer die Klasse CTlgPrototypSet
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
 public ref class CTlgInterfaceWrapper : public CItemBaseContainerWrapper
{
  public:
    CTlgInterfaceWrapper();
    virtual ~CTlgInterfaceWrapper();
    virtual CItemWrapper^ getTlg(int id) override;
    virtual CItemWrapper^ getTlg(String^ tlgName) override;
    virtual void getClonedTlg(CItemWrapper^ tlg,int id) override;
    virtual void getClonedTlg(CItemWrapper^ tlg,String^ tlgName) override;
    virtual String^ getTlgTimeAsString(int id) override;
    virtual int getTlgCount() override;
    virtual int loadFromFile(String^ path,bool const&abort) override;
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,int id) override;
    virtual void getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName) override;
    // emal
    virtual int findTelegramm(int pos,String^ tlgName);
    virtual int findTelegramm(int pos,String^ tlgName,String^ elemName,String^ rel,String^ val);
    String^ getInterfaceName();
    String^ getInterfaceDescr();
    String^ getInterfaceVersion();
    CTlgProtoTypSet* getTlgProtoTypSet();
    CItemWrapper^ makeTlg(String^ name);
    void getFlatTlg(CItemWrapper^ tlgWr,String^ name);
    int getOffsetElem(String^ tlg,String^ elem);
    void removeInter();
    virtual String^ getVirtualTlgDescr(int id) override;
  private:
    CTlgProtoTypSet* TlgProtoTypSet;
};

#endif
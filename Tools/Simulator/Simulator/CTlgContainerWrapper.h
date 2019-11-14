// Copyright 2006 SMS - Demag AG
#ifndef _CTlgContainerWrapper_H_
#define _CTlgContainerWrapper_H_

//-----------------------------------------------------------
#include "CItemBaseContainerWrapper.h"
//-----------------------------------------------------------
using namespace System::Collections;
//-----------------------------------------------------------
//-------------------------------------------
// Name:  CTlgContainerWrapper.h
// Descr: Diese Klasse ist ein Container für
//        Telegramme. Der Schluessel ist Zeit 
// Date:
// Autor: Emeljanov Anatolij 
//--------------------------------------------
public ref class CTlgContainerWrapper : public CItemBaseContainerWrapper
{
public:
  CTlgContainerWrapper();
  virtual ~CTlgContainerWrapper();
  virtual CItemWrapper^ getTlg(int id) override;
  virtual CItemWrapper^ getTlg(String^ tlgName) override;
  //! return a copy of tlg in wrapper
  virtual void getClonedTlg(CItemWrapper^ tlg,int id) override;
  virtual void getClonedTlg(CItemWrapper^ tlg,String^ tlgName) override;
  virtual String^ getTlgTimeAsString(int id) override;
  virtual int getTlgCount() override;
  virtual int loadFromFile(String^ path,const bool &abort) override;
  virtual void getClonedVirtualTlg(CItemWrapper^ tlg,int id) override;
  virtual void getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName) override;
  virtual void clearContainer() override;
  void addTlgToContainer(CItemWrapper^ tlgWr);
  virtual String^ getVirtualTlgDescr(int id) override;
	value struct ConElementTyp
  {
      CItemWrapper^ Tlg;
      System::DateTime TimeTlg;
  };
private:
  ArrayList^ Container;
};

#endif
 
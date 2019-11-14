// Copyright 2006 SMS - Demag AG
//-------------------------------------------
// Name:  CCyclicElemTable.h
// Date:  21.11.08
// Autor: Emeljanov Alexander 
//--------------------------------------------
#ifndef _CCyclicElemTable_H_
#define  _CCyclicElemTable_H_

//#include "CItemWrapper.h"
#include "CCyclicElemStatus.h"
#include "CTlgElemWrapper.h"
#include "CItemWrapper.h"

using namespace System;

//using namespace simulator;

public ref class CCyclicElemTable
{
  public:
     CCyclicElemTable(CItemWrapper^ item);
     ~CCyclicElemTable();
     void updateElem(CTlgElemWrapper^ elem,CCyclicElemStatus^ status);
     void updateElem(String^ elem,CCyclicElemStatus^ status);
     bool updateElemStatus(CTlgElemWrapper^ elem,CCyclicElemStatus::changeTyp typ,
                           double max,double min,double variabelValue);
     void setTimeInterval(int time);
     CCyclicElemStatus^ getElemStatus(CTlgElemWrapper^ elem);
     CCyclicElemStatus^ getElemStatus(String^ name);
     int getElemCount();
     int getTimeInterval();
     Collections::ICollection^ getTableKeys();
     CItemWrapper^ getItem();
     String^ getItemName();
     String^ getInterfaceName();
  private:
    void FillElemTable();
    void FillElemTable(CTlgElemWrapper^ elem);
    System::Collections::Hashtable^ elemTable;
    int timeInterval;
    CItemWrapper^ Item;
};


#endif
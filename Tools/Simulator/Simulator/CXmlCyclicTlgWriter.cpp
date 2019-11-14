#include "StdAfx.h"
#include "CXmlCyclicTlgWriter.h"
#include "CFormatConverterWrapper.h"
#include "CItemWrapper.h"
#include "CCyclicElemTable.h"
#include "CCyclicElemStatus.h"
#include "CCyclicItemContainer.h"

using namespace System;
//----------------------------------------------------
CXmlCyclicTlgWriter::CXmlCyclicTlgWriter(void)
{
}
//----------------------------------------------------
CXmlCyclicTlgWriter::~CXmlCyclicTlgWriter(void)
{
}
//----------------------------------------------------
void CXmlCyclicTlgWriter::writeCyclicItems(String^ path)
{
  CCyclicItemContainer^ itemCon = CCyclicItemContainer::getCyclicItemContainer();
  
  Collections::ArrayList^ interList = gcnew Collections::ArrayList();
  CItemWrapper^ item = nullptr;
  CCyclicElemTable^ elemTable = nullptr;

  Writer = gcnew XmlTextWriter(path,nullptr);
  Writer->Formatting = Formatting::Indented;
  //root
  Writer->WriteStartDocument();
  Writer->WriteStartElement("CyclicTelegram");
  Writer->WriteAttributeString("date",DateTime::Now.ToString());
  
  //Liste mit allen Interfases durchlaufen
  String^ interName = nullptr;
  itemCon->iterReset();
  bool ok = true;
  while (ok)
  {
    interName = itemCon->getNextInterface();
    if (interName)
      interList->Add(interName);
    else
      ok = false;
  }

  //Liste mit allen Items durchlaufen
  for (int i=0;i<interList->Count;i++)
  {
    ok = true;
    interName = safe_cast <String^> (interList[i]);
    while (ok)
    {
      elemTable = itemCon->getNextItem(interName);
      if (elemTable)
      {
        writeItem(elemTable->getItem(),elemTable);
      }
      else
      {
        ok = false;
      }
    }
  }

  Writer->WriteEndElement();
  Writer->Flush();
  Writer->Close();
}
//----------------------------------------------------
void CXmlCyclicTlgWriter::writeItem(CItemWrapper^ item,CCyclicElemTable^ elemTable)
{
  Writer->WriteStartElement("item");
  Writer->WriteAttributeString("name",item->getName());
  Writer->WriteAttributeString("interface",item->getInterfece());
  Writer->WriteAttributeString("interval",CFormatConverterWrapper::IntToString(elemTable->getTimeInterval()));
  Writer->WriteAttributeString("body",item->getSerialiseTlgAsString("|"));
  ////Body Inhalt
  //Writer->WriteStartElement("body");
  //Writer->WriteAttributeString("statement",item->getSerialiseTlgAsString("|"));
  //Writer->WriteEndElement();
  
  //Liste mit Items Namen
  Collections::ArrayList^ elements = gcnew Collections::ArrayList();
  //Liste fuellen
  System::Collections::ICollection^ i_col = elemTable->getTableKeys();
  System::Collections::IEnumerator^ iterator = i_col->GetEnumerator();
  String^ tempName = nullptr;
  iterator->Reset();
  for (int i=0;i<i_col->Count;i++)
  {
    iterator->MoveNext();
    tempName=safe_cast <String^>(iterator->Current);
    elements->Add(tempName);
  }
  //XML Datei 
  CCyclicElemStatus^ elemStatus = nullptr;
  String^ elemName = nullptr;

  for (int i=0;i<elemTable->getElemCount();i++)
  {
    elemName = safe_cast <String^>(elements[i]);
    elemStatus = safe_cast <CCyclicElemStatus^>(elemTable->getElemStatus(elemName));

    Writer->WriteStartElement("element");
    //
    Writer->WriteAttributeString("name",elemName);
    Writer->WriteStartElement("config ");
    Writer->WriteAttributeString("variabelTyp",CFormatConverterWrapper::IntToString((int)elemStatus->getVariabelTyp()));;
    Writer->WriteAttributeString("variabelValue",CFormatConverterWrapper::DoubleToString(elemStatus->getVariabelValue()));
    Writer->WriteAttributeString("minValue",CFormatConverterWrapper::DoubleToString(elemStatus->getMinValue()));
    Writer->WriteAttributeString("maxValue",CFormatConverterWrapper::DoubleToString(elemStatus->getMaxValue()));
    Writer->WriteEndElement();
    //
    Writer->WriteEndElement();
  }
  Writer->WriteEndElement();
}
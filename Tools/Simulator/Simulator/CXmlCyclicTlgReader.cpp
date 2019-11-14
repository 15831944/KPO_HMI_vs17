#include "stdafx.h"
#include "CXmlCyclicTlgReader.h"
#include "CFormatConverterWrapper.h"
#include "CSzenarium.h"
#include "CItemWrapper.h"
#include "CCyclicElemTable.h"
#include "CCyclicItemContainer.h"
#include "CLogWriterWrapper.h"

//------------------------------------------
CXmlCyclicTlgReader::CXmlCyclicTlgReader()
{
  MessageXmlCyclicReaderDel = nullptr;
}
//------------------------------------------
CXmlCyclicTlgReader::~CXmlCyclicTlgReader()
{
}
//------------------------------------------
void CXmlCyclicTlgReader::setMessageXmlCyclicReaderDelTyp(MessageXmlCyclicReaderDelTyp^ typ)
{
  MessageXmlCyclicReaderDel = typ;
}
//------------------------------------------
void CXmlCyclicTlgReader::readCyclicItems(String^ path,List<CTlgInterfaceWrapper^>^ interCon)
{
  CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
  String^ mess = nullptr; 
  //Alle InterfaceWrapper in Map ablegen
  CTlgInterfaceWrapper^ interWrapper = nullptr;
  Collections::Hashtable^ InterMap = gcnew Collections::Hashtable(); 
  for (int i=0;i<interCon->Count;i++)
  {
    interWrapper = safe_cast <CTlgInterfaceWrapper^> (interCon[i]);
    if (interWrapper)
      InterMap->Add(interWrapper->getInterfaceName(),interWrapper);
  }
  
  //Ueberpruefen, ob die XML-Datei existiert
  IO::FileInfo^ checkFIle = gcnew IO::FileInfo(path);
  if (checkFIle->Exists)
  {
    CCyclicItemContainer^ itemCon = CCyclicItemContainer::getCyclicItemContainer();
    CItemWrapper^ item=nullptr;
    CCyclicElemTable^ elemTable=nullptr;
    int interval = 0;
    Object^ TempObj=nullptr;
    String^ body = nullptr;
    String^ error = nullptr;
    String^ itemName = nullptr;
    int pos;
    
    Reader = gcnew XmlTextReader(path);
    //Root
    while(Reader->Read())
    {
      if (Reader->NodeType == XmlNodeType::Element)   
      {
        if((Reader->Name)->Equals("CyclicTelegram"))
        { 
          //Item
          while((Reader->NodeType == XmlNodeType::Element && Reader->Name->Equals("item")) || Reader->Read())
          {
            //Element Name of Item
            if (Reader->NodeType == XmlNodeType::Element && Reader->Name->Equals("item"))
            {
              item = nullptr;
              TempObj = nullptr;
              pos = 0;
              interWrapper = nullptr;
              TempObj = InterMap[Reader[1]];
              itemName = Reader[1];
              if (TempObj) //Interface Gefunden
              {
                interWrapper = safe_cast <CTlgInterfaceWrapper^> (TempObj);
                interWrapper->reset();
                pos = interWrapper->findTelegramm(1,Reader[0]);
                if (pos>0)
                {
                  item = gcnew CTlgWrapper();
                  interWrapper->getClonedTlg(item,pos);
                }
                if (item) //Telegramm gefunden
                {
                  //Interval
                  interval = CFormatConverterWrapper::StringToInt(Reader[2]);
                  //Body Statement
                  body = Reader[3];
                  //Telegramm mit Werten fuellen
                  error=item->fillTlg(body);
                  if (!error)
                  {
                    //Elemente
                    elemTable=readItemAllElem(item);
                    if (elemTable) //Wenn alle num. Elemente ausgelesen
                    {
                      elemTable->setTimeInterval(interval);
                      //Telegramm zu CyclicCon hinzufuegen
                      itemCon->addItemToContainer(item->getInterfece(),item,elemTable,false);
                    }
                  }
                  else
                  {
                    //Ausgabe error
                    if (MessageXmlCyclicReaderDel)
                    {
                      mess = String::Concat("Telegram <",Reader[0],"> not created.");
                      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                      MessageXmlCyclicReaderDel->Invoke(mess,2);
                      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,error,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                      MessageXmlCyclicReaderDel->Invoke(error,2);
                    }
                    interWrapper->reset();
                    Reader->Read();
                  }
                }
                else //Telegramm nicht gefunden
                {
                  //FehlerMeldung Ausgabe
                  mess = String::Concat("Telegram <",Reader[0],"> not found.");
                  logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                  if (MessageXmlCyclicReaderDel)
                    MessageXmlCyclicReaderDel->Invoke(mess,2);
                  Reader->Read();
                }
              }
              else //Interface nicht gefunden
              {
                //FehlerMeldung Ausgabe
                mess = String::Concat("Telegram <",itemName,"> not created, because interface <",Reader[1],"> is not loaded.");
                logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
                if (MessageXmlCyclicReaderDel)
                  MessageXmlCyclicReaderDel->Invoke(mess,2);
                Reader->Read();
              }  
            }
          //End While Item
          }
        }
      }
    }//End While
    Reader->Close();
  }
}
//------------------------------------------
CCyclicElemTable^ CXmlCyclicTlgReader::readItemAllElem(CItemWrapper^ item)
{
  bool flag_elem = true;
  bool flag_variabel = true;
  String^ elemName = nullptr;
  double minValue=0;
  double maxValue=0;
  String^ endValueUseStr = nullptr;
  int typ=0;
  double value=0;
  CCyclicElemTable^ elemTable = gcnew CCyclicElemTable(item);
  while (flag_elem && Reader->Read())
  {
    if (Reader->NodeType == XmlNodeType::Element && Reader->Name->Equals("element"))
    {
      elemName = Reader[0];
      flag_variabel=true;
      //Element Status
      while(Reader->Read() && flag_variabel)
      {
        if (Reader->NodeType == XmlNodeType::Element && Reader->Name->Equals("config"))
        { 
          typ = CFormatConverterWrapper::StringToInt(Reader[0]);
          value = CFormatConverterWrapper::StringToDouble(Reader[1]); 
          minValue = CFormatConverterWrapper::StringToDouble(Reader[2]);
          maxValue = CFormatConverterWrapper::StringToDouble(Reader[3]);
          //Adding to table
          elemTable->updateElem(elemName,gcnew CCyclicElemStatus(typ,value,minValue,maxValue));
          flag_variabel = false;
        }//End Element Status
      }//End while variabel 
    }//End if element
    else if (Reader->NodeType == XmlNodeType::Element && Reader->Name->Equals("item")) 
    {
      flag_elem = false;
      Reader->MoveToElement();
      /*Reader->ResetState(*/
    }
  }//End while
  return elemTable;
}
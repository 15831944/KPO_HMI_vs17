#include "stdafx.h"
#include "CXmlSzenReader.h"
#include "CFormatConverterWrapper.h"

//------------------------------------------
CXmlSzenReader::CXmlSzenReader():
Reader(nullptr),Szen(nullptr)
{
}
//------------------------------------------
CXmlSzenReader::~CXmlSzenReader()
{
}
//------------------------------------------
CSzenarium^ CXmlSzenReader::loadSzenarium(String^ path,ArrayList^ protoInterSet)
{
  
  PrototypTlgSet = protoInterSet;
  Reader = gcnew XmlTextReader(path);
  //!!!TlgFactory=fac;
  while(Reader->Read())
  {
       switch(Reader->NodeType)
       {

           case XmlNodeType::Element:
              if((Reader->Name)->Equals("Szenarium"))
                 createSzen();
             break;
           default:
             break;
     }
  }

  return Szen;
}
//------------------------------------------
void CXmlSzenReader::createSzen()
{
  bool endSzen=false;
  bool flag=true;
  String^ value=nullptr;

  Szen = gcnew CSzenarium();

  while((!endSzen) && (flag))
  {
    value="Unknow";
    if(Reader->HasAttributes)
    {
      value = Reader[0];
    }
    Szen->setName(value);
    flag=Reader->Read();
    if((Reader->NodeType == XmlNodeType::EndElement) && ((Reader->Name)->Equals("Szenarium")))
    {
      endSzen = true;
    }
    else
    {
      if((Reader->NodeType == XmlNodeType::Element) && ((Reader->Name)->Equals("telegram")))
      {
        addTelegram();
      }
    }

  }
  
}
//-------------------------------------------------
void CXmlSzenReader::addTelegram()
{
    bool endTlg;
    bool flag=true;
    String^ name=nullptr;
    String^ body=nullptr;
    String^ status=nullptr;
    String^ delay=nullptr;
    String^ value=nullptr;
    String^ tlgId=nullptr;
    CItemWrapper^ TlgWr=nullptr;
    CSzenItem^ item;
	
    if(Reader->HasAttributes)
    {
      name = Reader[0];
    }
    if(name != nullptr)
    {
        endTlg = false;
        while((!endTlg) && (flag))
        {
          flag=Reader->Read();
          if((Reader->NodeType == XmlNodeType::EndElement) && ((Reader->Name)->Equals("telegram")))
          {
            endTlg = true;
          }
          else
          {
               if((Reader->NodeType == XmlNodeType::Element))
               {
                 value = Reader->Name;
               }
               if((Reader->NodeType == XmlNodeType::Text))
               {
                 if(value->Equals("body"))
                   body = Reader->Value;
                if(value->Equals("statu"))
                   status = Reader->Value;
                if(value->Equals("delay"))
                   delay = Reader->Value;
               }

          }
        }
        tlgId = getTlgId(body);
        if(tlgId != nullptr)
        {
            CItemWrapper^ TlgWr=nullptr;
            TlgWr = createTlg(tlgId);
            TlgWr->fillTlg(body);
        
			int index;
			index = Szen->getSzenItemCount();
			//?item=Szen->addToSzenarium(TlgWr);
			Szen->addToSzenarium(TlgWr,index);
			item = Szen->getSzenItem(index+1);
			item->setDelay(CFormatConverterWrapper::StringToDouble(delay));
			//item->setDelay(System::Convert::ToDouble(delay));
          if(status->Equals("Off"))
            item->setSendStatus(false);
          else
            item->setSendStatus(true);
        }
    }
}
//--------------------------------------------------
String^ CXmlSzenReader::getTlgId(String^ line)
{
  String^ ret=nullptr;
  int pos;

  pos=line->IndexOf("|");
  if(pos != -1)
    ret = line->Substring(0,pos);

   return ret;
}
//--------------------------------------------------
CItemWrapper^ CXmlSzenReader::createTlg(String^ name)
{
    CItemWrapper^ wr=nullptr;
    CInterBaseManager^ interMan = nullptr;
    int count = PrototypTlgSet->Count;
    int i=0;

    while((i<count) && (wr == nullptr))
    {
        try
        {
            interMan = safe_cast<CInterBaseManager^>(PrototypTlgSet[i]);
            wr=interMan->makeTlg(name);
        }
        catch(...)
        {
            wr=nullptr;
            i++;
        }
    }


    return wr;
}
//--------------------------------------------------

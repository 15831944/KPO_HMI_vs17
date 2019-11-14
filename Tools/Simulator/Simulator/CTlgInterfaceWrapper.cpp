// Copyright 2006 SMS - Demag AG
//---------------------------------------------------------------
#include "stdafx.h"
#include "CTlgInterfaceWrapper.h"
#include "CLogWriterWrapper.h"
#include "CStdConverter.h"
//--------------------------------------------------------------
#include <string>
//---------------------------------------------------------
CTlgInterfaceWrapper::CTlgInterfaceWrapper():
CItemBaseContainerWrapper()
{
  TlgProtoTypSet=nullptr;
}
//---------------------------------------------------------
CTlgInterfaceWrapper::~CTlgInterfaceWrapper()
{
  if(TlgProtoTypSet)
    delete TlgProtoTypSet;
}
//---------------------------------------------------------
void CTlgInterfaceWrapper::getClonedTlg(CItemWrapper^ tlg,int id)
{
  //tlg->setTlg(TlgProtoTypSet->makeFlatTlg(id));
  tlg->setTlg(TlgProtoTypSet->makeTlg(id));
}
//---------------------------------------------------------
void CTlgInterfaceWrapper::getClonedTlg(CItemWrapper^ tlg,String^ tlgName)
{

}
CItemWrapper^ CTlgInterfaceWrapper::getTlg(int id)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                      "This methode is not implement in this cla",
                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return nullptr;
}
//---------------------------------------------------------
CItemWrapper^ CTlgInterfaceWrapper::getTlg(String^ tlgName)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                      "This methode is not implement in this cla",
                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return nullptr;
}
//---------------------------------------------------------
int CTlgInterfaceWrapper::getTlgCount()
{
  return TlgProtoTypSet->getTlgCount();
}
//---------------------------------------------------------
int CTlgInterfaceWrapper::loadFromFile(String^ path,bool const&abort)
{
  int ret = 0;
  std::string pathstr("");
  Path=path;
  CStdConverter::StringToStdStr(path,pathstr);
  CXmlTlgProtoTypeReader* reader = new CXmlTlgProtoTypeReader();
  TlgProtoTypSet=reader->readXmlProtoInterface(pathstr);
    if(TlgProtoTypSet == nullptr)
    {
        ret = 1;
        ErrorMessage = CStdConverter::StdStrToString(reader->getErrorMessage());
    }
    else
    {
        reset();
    }
    delete reader;    
  return ret;
}
//---------------------------------------------------------
//---------------------------------------------------------
String^ CTlgInterfaceWrapper::getInterfaceName()
{
  return  CStdConverter::StdStrToString(TlgProtoTypSet->getName());
}
//---------------------------------------------------------
String^  CTlgInterfaceWrapper::getInterfaceDescr()
{
  return  CStdConverter::StdStrToString(TlgProtoTypSet->getComment());
}

//---------------------------------------------------------
String^  CTlgInterfaceWrapper::getInterfaceVersion()
{
  return  CStdConverter::StdStrToString(TlgProtoTypSet->getVersion());
}

//---------------------------------------------------------
CTlgProtoTypSet*  CTlgInterfaceWrapper::getTlgProtoTypSet()
{
  return this->TlgProtoTypSet;
}
//---------------------------------------------------------
CItemWrapper^ CTlgInterfaceWrapper::makeTlg(String^ name)
{
  CItemWrapper^ tlgWr = nullptr;
  std::string namestr("");
  CTlg* tlg = nullptr;

  CStdConverter::StringToStdStr(name,namestr);
  try
  {
    tlg=TlgProtoTypSet->makeTlg(namestr);
    tlgWr = gcnew CTlgWrapper();
    tlgWr->setTlg(tlg);
  }
  catch(CExpUnknownTlg& e)
  {
    #if defined __CONSOLE__
      String^ Mes;
      String^ tmp = CStdConverter::StdStrToString(e.getTlg().c_str());
      Mes->Concat("ExpUnknownTlg",tmp);
      Console::WriteLine(Mes);
    #endif
    
    String^ mess = String::Concat("Unknown Telegram: ",name);
    throw gcnew CExpWrapper(mess,CExpWrapper::ErrorTyp::tUnknowTlg);
  }

  return tlgWr;
}
//---------------------------------------------------------
void CTlgInterfaceWrapper::getFlatTlg(CItemWrapper^ tlgWr,String^ name)
{
  try
  {
    std::string namestr(""); 
    CStdConverter::StringToStdStr(name,namestr);
    tlgWr->setTlg(TlgProtoTypSet->makeFlatTlg(namestr));
  }
  catch(CExpUnknownTlg& e)
  {
    #if defined __CONSOLE__
      String^ Mes;
      String^ tmp = CStdConverter::StdStrToString(e.getTlg().c_str());
      Mes->Concat("ExpUnknownTlg",tmp);
      Console::WriteLine(Mes);
    #endif
    
    //String^ mess = String::Concat("Unknown Telegram: ",name);
    //throw gcnew CExpWrapper(mess,CExpWrapper::ErrorTyp::tUnknowTlg);
  }
}
//---------------------------------------------------------
int CTlgInterfaceWrapper::getOffsetElem(String^ tlg,String^ elem)
{
  int ret = -1;
  std::string tlgname("");
  std::string elemname("");

  CStdConverter::StringToStdStr(tlg,tlgname);
  CStdConverter::StringToStdStr(elem,elemname);

  ret=TlgProtoTypSet->makeFlatTlg(tlgname)->getElemOffset(elemname);

  return ret;
}

 //--------------------------------------------------------
 void CTlgInterfaceWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,int id)
 {
   int index = System::Convert::ToInt32(VirtuallContainer[id-1]);
   tlg->setTlg(TlgProtoTypSet->makeFlatTlg(index+1));
 }
//---------------------------------------------------------
void CTlgInterfaceWrapper::getClonedVirtualTlg(CItemWrapper^ tlg,String^ tlgName)
{
}
//---------------------------------------------------------
String^ CTlgInterfaceWrapper::getTlgTimeAsString(int id)
{
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                      "This methode is not implement in this cla",
                                                      __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return nullptr;
}
 //--------------------------------------------------------
void CTlgInterfaceWrapper::removeInter()
{
  delete TlgProtoTypSet;
    TlgProtoTypSet=nullptr;
}
 //--------------------------------------------------------
// emal
int CTlgInterfaceWrapper::findTelegramm(int pos,String^ tlgName)
{
  int count;
  int ret=0;
  int i;
  bool flag;
  count=this->TlgProtoTypSet->getTlgCount();
  if (pos<count)
  {
    CItemWrapper^ wr = gcnew CTlgWrapper();
		flag=false;
		i=pos;
		while((i<=count) && (!flag))
		{
      this->getClonedTlg(wr,i);
      //this->getClonedVirtualTlg(wr,i);
			if(wr->getName()->Equals(tlgName))
			{
				flag=true;
				ret=i;
			}
			else
			{
				i++;
			}
		}
  }
  return ret;
}
//---------------------------------------------------------
int CTlgInterfaceWrapper::findTelegramm(int pos,String^ tlgName,String^ elemName,String^ rel,String^ val)
{
  return 0;
}
//---------------------------------------------------------
String^ CTlgInterfaceWrapper::getVirtualTlgDescr(int id)
{
  String^ ret=nullptr;
  CItemWrapper^ wr=gcnew CTlgWrapper();
  getClonedVirtualTlg(wr,id);
  ret=wr->getTlgDescr();
  return ret;
}
//---------------------------------------------------------
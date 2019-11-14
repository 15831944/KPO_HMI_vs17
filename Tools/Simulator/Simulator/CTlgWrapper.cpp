// Copyright 2006 SMS - Demag AG

//-----------------------------------------------------
#include "stdafx.h"
#include "CTlgWrapper.h"
#include "CStdConverter.h"
#include "CBaseExp.h"
#include "CExpInvalidTlg.h"
#include "CElemDescription.h"
#include "CExpConvertError.h"
#include "CExpTlgLenError.h"
#include "CExpLimitError.h"
#include "CTlgElem.h"
#include "CTlgElemWrapper.h"
//-----------------------------------------------------
using namespace System::Runtime::InteropServices;
//-----------------------------------------------------
CTlgWrapper::CTlgWrapper():
Tlg(nullptr)
{
}
//-------------------------------------------------
CTlgWrapper::~CTlgWrapper()
{
 
}
//-------------------------------------------------
Collections::ArrayList^ CTlgWrapper::createNumberElemList()
{
  Collections::ArrayList^ ret = gcnew Collections::ArrayList();
  CTlgElem* elem = nullptr;
  for (int i=1;i<=getTlgElemCount();i++)
  {
    elem = getElem(i);
    createNumberElemListRekursiv(ret,elem);
  }
  return ret;
}
//--------------------------------------------------
void CTlgWrapper::createNumberElemListRekursiv(Collections::ArrayList^ ret,CTlgElem* elem)
{
  int elemCount = elem->getSubElemCount();
  if (elemCount > 0)
  {
    for (int i=1;i<=elem->getSubElemCount();i++)
    {
      //Rekursiv Aufuruf
      createNumberElemListRekursiv(ret,elem->getSubElem(i));
    } 
  }
  else
  {
    CElemDescription::ElementType elemTyp = elem->getElemType();
    //Wenn, es eine Number - Element ist.
    if ((elemTyp == CElemDescription::tDouble) || (elemTyp == CElemDescription::tFloat)
      || (elemTyp == CElemDescription::tInteger) || (elemTyp == CElemDescription::tShortInteger))
    {
      CTlgElemWrapper^ tmp = gcnew CTlgElemWrapper();
      tmp->setTlgElem(elem);
      ret->Add(tmp);
    }
  }
}
//--------------------------------------------------
int CTlgWrapper::getTlgElemCount()
{
  if(Tlg != 0)
    return Tlg->getElemCount();
  else
    return -1;
}
//--------------------------------------------------
int CTlgWrapper::getElemTyp(int id)
{
  CElemDescription::ElementType type = CElemDescription::tUnknow;
  const CTlgElem* elem;

  if(Tlg != 0)
  {
    elem=Tlg->getFlatElem(id);
    type=elem->getElemType();
    if(type == CElemDescription::tArray)
    {
      return 2;
    }
    if(type == CElemDescription::tRecord)
    {
      return 1;
    }
  }

  return 0;
}
//--------------------------------------------------
String^ CTlgWrapper::getElemTypAsString(int id)
{
  String^ ret = nullptr;
  CElemDescription::ElementType type = CElemDescription::tUnknow;
  const CTlgElem* elem;

  if(Tlg != 0)
  {
    elem=Tlg->getFlatElem(id);
    type=elem->getElemType();

    if(type == CElemDescription::tArray)
    {
      ret = "Array";
    }
    if(type == CElemDescription::tRecord)
    {
      ret = "Record";
    }
    if(type == CElemDescription::tDouble)
    {
      ret = "Double";
    }
    if(type == CElemDescription::tInteger)
    {
      ret = "Integer";
    }
    if(type == CElemDescription::tString)
    {
      ret = "String";
    }
  }
  return ret;
}
//--------------------------------------------------
CTlgElem* CTlgWrapper::getTlgElem(String^ elemPathName)
{
  int index = elemPathName->IndexOf("\\");
  String^ elemName = nullptr;
  
  //Wenn es ein Element aus der 1.te Ebene ist
  if (index == -1)
  {
    elemName = elemPathName;

    //Root Elemente durchlaufen
    int i = 1;
    while (i<=getTlgElemCount())
    {
      if (elemPathName->Equals(getElemName(i)))
      {
        return getElem(i);
      }
      i++;
    }
  }
  else
  {
    elemName = elemPathName->Substring(0,index);
    elemPathName = elemPathName->Remove(0,index+1);
    //String^ testtest = elemPathName->Remove(0,index+1);

    int i = 1;
    CTlgElem* tlgElem = nullptr;
    CTlgElem* ret = nullptr;
    
    CTlgElemWrapper^ temp = gcnew CTlgElemWrapper(); 

    while (i<=getTlgElemCount())
    {
      tlgElem = getElem(i);
      temp->setTlgElem(tlgElem);
      
      if (elemName->Equals(temp->getElemName()))
      {
        ret = temp->getSubElem(elemPathName);   
        
        if (ret)
        {
          return ret;
        }
        else
        {
          return 0;
        }
      }
      i++;
    } 
  }
  return 0;
}
//--------------------------------------------------
array <String^>^ CTlgWrapper::getElemAsStringArray(int i,int* elemFlag)
{
  array <String^>^ ret;
  std::string stdstr("");
  const CTlgElem* elem=nullptr;
  const CTlgElem* subElem=nullptr;
  //CTlgElem::Type elemType;
  int count=0;

  
  //  elem=Tlg->getTlgElem(i);
  // count = elem->getSubElemCount();
  //  elemType = elem->getType();
  //  if(elemType == CTlgElem::Type::tArray)
  //{
    ret = gcnew array <String^>(count+2);
    (*elemFlag)=2;
  // }
  //  else
  // {
  //    if(elemType == CTlgElem::Type::tRecords)
  //  {
  //     ret = new String^[3*count+2];
  //   (*elemFlag)=1;
  //}
  // else
  //{
  //   ret = new String^[count+3];
  // (*elemFlag)=0;
  //}
  //}
  //  stdstr=elem->getName();
  ret[0] = Marshal::PtrToStringAnsi(System::IntPtr((void*)stdstr.c_str()));
  ret[1] = "Description";  
  switch(*elemFlag)
  {
      case 0:
      //elem->getAsString(stdstr);
        ret[2] = Marshal::PtrToStringAnsi(System::IntPtr((void*)stdstr.c_str()));
        break;
      case 1:
        for(int i=1;i<=count;i++)
        {
          subElem=elem->getSubElem(i);
          //stdstr=subElem->getName();
          ret[(i-1)*3 + 2] = Marshal::PtrToStringAnsi(System::IntPtr((void*)stdstr.c_str()));
          ret[(i-1)*3 + 3 ] = "Description";
          //subElem->getAsString(stdstr);
          ret[(i-1)*3 + 4] = Marshal::PtrToStringAnsi(System::IntPtr((void*)stdstr.c_str()));
        }
        break;
      case 2:
        for(int i=1;i<=count;i++)
        {
          subElem=elem->getSubElem(i);
          //subElem->getAsString(stdstr);
          ret[i+1]=Marshal::PtrToStringAnsi(System::IntPtr((void*)stdstr.c_str()));
        }
        break;
  }
  return ret;
}
//--------------------------------------------------
void CTlgWrapper::setTlg(CTlg* tlg)
{
  this->Tlg=tlg;
}
//--------------------------------------------------
String^ CTlgWrapper::getName()
{
  String^ val=nullptr;
  std::string name("");
  
  if(Tlg != 0)
  {
    name=Tlg->getTlgName();
  }

  return CStdConverter::StdStrToString(name);
}
//--------------------------------------------------
int CTlgWrapper::getTlgBodyLen()
{
  if(Tlg != 0)
  {
    return Tlg->getTlgBodyLen();
  }
  else
  {
    return 0;
  }
}
//--------------------------------------------------
int CTlgWrapper::getTlgHeaderLen()
{
  if(Tlg != 0)
  {
    return Tlg->getTlgHeaderLen();
  }
  else
  {
    return 0;
  }
}
 //-------------------------------------------------
int CTlgWrapper::getTlgLen()
{
  if(Tlg != 0)
  {
    return Tlg->getTlgLen();
  }
  else
  {
    return 0;
  }
}
//--------------------------------------------------
CItemWrapper^ CTlgWrapper::clone() 
{
  CTlg* tlg=nullptr;
  CItemWrapper^ wr=gcnew CTlgWrapper();

  if(Tlg != 0)
  {
    tlg = Tlg->clone();
    wr->setTlg(tlg);
  }

  return wr;
}
//--------------------------------------------------
int CTlgWrapper::getSerializeTlg(char* buffer,int length)
{
  int count=0;

  if(Tlg != 0)
  {
    count = Tlg->serializeTlg(buffer,length);
  }

  return count;
}
//--------------------------------------------------
/*String^ CTlgWrapper::getSerializeTlgAsByteSteam()
{
    String^ ret = 0;
    std::string retstr("");
    Tlg->getTlgAsByteStream(retstr);
    ret = CStdConverter::StdStrToString(retstr);
    return 0;
}*/
//--------------------------------------------------
String^ CTlgWrapper::getSerialiseTlgAsString(String^ del)
{
  String^ ret=nullptr;
  std::string retstr("");
  std::string str("");
  CStdConverter::StringToStdStr(del,str);

  if(Tlg != 0)
  {
    Tlg->getTlgAsString(retstr,str);
    ret = CStdConverter::StdStrToString(retstr);
  }

  return ret;
}
//--------------------------------------------------
String^ CTlgWrapper::getElemName(int id)
{
  String^ ret=nullptr;
  std::string name("");

  if(Tlg != 0)
  {
    name=Tlg->getFlatElem(id)->getNameElem();
    ret=CStdConverter::StdStrToString(name);
  }

  return ret;
}
//--------------------------------------------------
//String^ CTlgWrapper::getElemName(int level,int id)
//{
//  String^ ret = 0;
//  std::string val("");
//  CTlgElem* elem=0;
//  CTlgElem* elemTemp=0;
//  
//  for (int i=1;i<=level;i++)
//  {
//
//  }
//  return ret;
//}
//--------------------------------------------------
String^ CTlgWrapper::getElemValue(int id)
{
  String^ ret = nullptr;
  const CTlgElem* elem=nullptr;
  std::string val("");  

  if(Tlg != 0)
  {
    if(!Tlg->getEmpty())
    {
      elem=Tlg->getFlatElem(id);
      elem->getValue(val);
      ret=CStdConverter::StdStrToString(val);
    }
  }

  return ret;
}
//--------------------------------------------------
String^ CTlgWrapper::getSubElemValue(int elemId,int subId)
{
  String^ ret=nullptr;
  std::string val("");

  if(Tlg != 0)
  {
    if(!Tlg->getEmpty())
    {
      CTlgElem* elem = Tlg->getFlatElem(elemId)->getSubElem(subId);
      elem->getValue(val);
      ret=CStdConverter::StdStrToString(val);
    }
  }

  return ret;
 }
//-------------------------------------------------
String^ CTlgWrapper::getSubElemValue(String^ elemId,String^ subElemId)
{
  String^ ret=nullptr;
  std::string elemIdStr;
  std::string subElemIdStr;
  std::string val;

  if((Tlg) && (!Tlg->getEmpty()))
  {
    CStdConverter::StringToStdStr(elemId,elemIdStr);
    CStdConverter::StringToStdStr(subElemId,subElemIdStr);
    Tlg->getFlatElem(elemIdStr)->getSubElem(subElemIdStr)->getValue(val);
    ret=CStdConverter::StdStrToString(val);
  }
  return ret;
}
//-------------------------------------------------
int CTlgWrapper::getSubElemCount(int id)
{
  if(Tlg != 0)
  {
    return Tlg->getFlatElem(id)->getSubElemCount();
  }
  else
  {
    return 0;
  }
}
 //-------------------------------------------------
void CTlgWrapper::getSubElementDescr(int elemId,int subId,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max)
{
  std::string elemDescrStr("");
  std::string TranspTypStr("");
  std::string UnitStr("");
  std::string FactorStr("");
  std::string MinStr("");
  std::string MaxStr("");
  const CTlgElem* elem=nullptr;

  if(Tlg != 0)
  {
    elem = Tlg->getFlatElem(elemId)->getSubElem(subId);
    elemDescrStr=elem->getComment();
    TranspTypStr=elem->getTranspTyp();
    elem->getElemInfo(UnitStr,FactorStr,MinStr,MaxStr);
    elemDescr=CStdConverter::StdStrToString(elemDescrStr);
    TranspTyp=CStdConverter::StdStrToString(TranspTypStr);
    Unit=CStdConverter::StdStrToString(UnitStr);
    Factor=CStdConverter::StdStrToString(FactorStr);
    Min=CStdConverter::StdStrToString(MinStr);
    Max=CStdConverter::StdStrToString(MaxStr);
  }
 }
//--------------------------------------------------
int CTlgWrapper::getSubElemLen(int elemId,int subId)
{
  if(Tlg != 0)
  {
    return Tlg->getFlatElem(elemId)->getSubElem(subId)->getLen();
  }
  else
  {
    return 0;
  }

}
 //-------------------------------------------------
String^ CTlgWrapper::getSubElemName(int elemId,int subId)
{
  std::string name("");
  const CTlgElem* elem;

  if(Tlg != 0)
  {
    elem=Tlg->getFlatElem(elemId);
    name=elem->getSubElem(subId)->getNameElem();
  }

  return CStdConverter::StdStrToString(name);
}
//--------------------------------------------------
String^ CTlgWrapper::getTlgDescr()
{
  if(Tlg != 0)
  {
    return CStdConverter::StdStrToString(Tlg->getDescription());
  }
  else
  {
    return nullptr;
  }
}
//--------------------------------------------------
void CTlgWrapper::getElementDescr(int id,String^& elemDescr,String^& TranspTyp,String^& Unit,String^& Factor,String^& Min,String^& Max)
{
  std::string elemDescrStr("");
  std::string TranspTypStr("");
  std::string UnitStr("");
  std::string FactorStr("");
  std::string MinStr("");
  std::string MaxStr("");
  CTlgElem* elem=nullptr;

  if(Tlg != 0)
  {
    elem=Tlg->getFlatElem(id);
    elemDescrStr=elem->getComment();
    TranspTypStr=elem->getTranspTyp();
    elem->getElemInfo(UnitStr,FactorStr,MinStr,MaxStr);
    elemDescr=CStdConverter::StdStrToString(elemDescrStr);
    TranspTyp=CStdConverter::StdStrToString(TranspTypStr);
    Unit=CStdConverter::StdStrToString(UnitStr);
    Factor=CStdConverter::StdStrToString(FactorStr);
    Min=CStdConverter::StdStrToString(MinStr);
    Max=CStdConverter::StdStrToString(MaxStr);
  }
}
//--------------------------------------------------
int CTlgWrapper::getElemLen(int id)
{
  if(Tlg != 0)
  {
    return Tlg->getFlatElem(id)->getLen();
  }
  else
  {
    return 0;
  }
}
//--------------------------------------------------
String^ CTlgWrapper::fillTlg(String^ line)
{
  String^ ret = nullptr;
  std::string linestr("");
  CStdConverter::StringToStdStr(line,linestr);
  try
  {
    Tlg->load(linestr);
  }
  catch(CExpInvalidTlg& e)
  {
    ret = String::Concat("Telegram: ",CStdConverter::StdStrToString(e.getTlg())," is ",
      CStdConverter::StdStrToString(e.getError()));      
    delete Tlg;
    Tlg=0;
    
  }
  catch(CExpConvertError& e)
  {
    if(e.getType() == "String")
    {
      ret = String::Concat("Value: <",CStdConverter::StdStrToString(e.getValue()),"< of ",CStdConverter::StdStrToString(e.getElem())," is to large");
    }
    else
    {
      ret = String::Concat("Value <",CStdConverter::StdStrToString(e.getValue()),"> of ",CStdConverter::StdStrToString(e.getElem())," is not ",
          CStdConverter::StdStrToString(e.getType()));
    }
    delete Tlg;
    Tlg=0;
  }
  catch(CExpTlgLenError& e)
  {
    String^ tlg = CStdConverter::StdStrToString(e.getTlg());
    String^ elem = CStdConverter::StdStrToString(e.getElem());
    String^ val = CStdConverter::StdStrToString(e.getValue());

    ret=String::Concat("Length of Telegram is wrong (tel: ",tlg, " elem: ",elem);
    ret=String::Concat(ret,"=",val,")");
      
    delete Tlg;
    Tlg=0;
  }
  catch(...)
  {
    delete Tlg;
    Tlg=0;
        ret = "Telegram is wrong";
  }
  return ret;
}
//--------------------------------------------------
 CTlg* CTlgWrapper::getClonedTlg()
 {
   return Tlg->clone();
 }
//--------------------------------------------------
array <String^>^ CTlgWrapper::getElemProtoTypInfo(int i,int* elemFlag)
{
  array <String^>^ ret;
  CTlgElem* elem;
  int count = 0;
  CElemDescription::ElementType type = CElemDescription::tUnknow;

  if(Tlg != 0)
  {
    elem=Tlg->getFlatElem(i);
    type = elem->getElemType();
  }

  if((type == CElemDescription::tDouble) || (type == CElemDescription::tInteger) || 
      (type == CElemDescription::tString))
  {
      (*elemFlag) = 1;
      ret = gcnew array <String^>(1);
  }
  else
  {
    if(type == CElemDescription::tArray)
    {
      (*elemFlag) = 2;
      ret = gcnew array <String^>(2);
    }
    else
    {
      if(type == CElemDescription::tRecord)
      {
        (*elemFlag) = 3;
      }
      else
      {
        (*elemFlag) = 0;
      }
    }
  }

  switch(*elemFlag)
  {
    case 1:
        ret[0] = CStdConverter::StdStrToString(elem->getNameElem());
        break;
    case 2:
        ret[0] = CStdConverter::StdStrToString(elem->getNameElem());
        ret[1] = System::Convert::ToString(elem->getSubElemCount());
        break;
    case 3:
        count = elem->getSubElemCount();
        ret = gcnew array <String^>(count+1);
        ret[0] = CStdConverter::StdStrToString(elem->getNameElem());
        for(int i=1;i<=count;i++)
            ret[i] = CStdConverter::StdStrToString(elem->getSubElem(i)->getNameElem());
        break;
  }

  return ret;
}
//--------------------------------------------------
String^ CTlgWrapper::getTlgDirection()
{
  if(Tlg != 0)
  {
    return CStdConverter::StdStrToString(Tlg->getDirection());
  }
  else
  {
    return nullptr;
  }
}
//--------------------------------------------------
String^ CTlgWrapper::getElemDescr(int id)
{
  String^ ret = nullptr;
  std::string val("");

  if(Tlg != 0)
  {
    val=Tlg->getFlatElem(id)->getComment();
    ret = CStdConverter::StdStrToString(val);
  }

  return ret;
}
//--------------------------------------------------
String^ CTlgWrapper::getInterfece()
{
  if(Tlg != 0)
  {
    return CStdConverter::StdStrToString(Tlg->getInterfaceName());
  }
  else
  {
    return nullptr;
  }
}
//--------------------------------------------------
int CTlgWrapper::getElemIndex(String^ elem)
{
  int ret = -1;
  bool flag;
  int count,i;
  std::string namestr("");
  String^ name = nullptr;

  if(Tlg != 0)
  {
    count = Tlg->getElemCount();
    flag=false;
    i=0;
    while((!flag) && (i<count))
    {
      namestr = Tlg->getFlatElem(i+1)->getNameElem();
      name = CStdConverter::StdStrToString(namestr);
      if(name->Equals(elem))
      {
        flag = true;
        ret=i+1;
      }
      else
      {
        i++;
      }
    }
  }

  return ret;
}
//--------------------------------------------------
int CTlgWrapper::getSubElemIndex(String^ elem,String^ subElem)
{
  int ret = 0;
  String^ subElemName=nullptr;
  bool flag = false;
  int i=0;
  int elemIndex = getElemIndex(elem);
  int count = getSubElemCount(elemIndex);
  while((!flag) && (i<count))
  {
    subElemName=getSubElemName(elemIndex,i+1);
    if(subElemName->Equals(subElem))
    {
      ret=i+1;
      flag=true;
    }
    else
    {
      i++;
    }
  }
  return ret;
}
//--------------------------------------------------
String^ CTlgWrapper::getSubElemTypAsString(int elem,int subelem)
{
  String^ ret = nullptr;

  if(Tlg != 0)
  {
    CElemDescription::ElementType elemTyp = Tlg->getFlatElem(elem)->getSubElem(subelem)->getElemType();
    if(elemTyp == CElemDescription::tArray)
      ret = "Array";
    if(elemTyp == CElemDescription::tDouble)
      ret = "Double";
    if(elemTyp == CElemDescription::tInteger)
      ret = "Integer";
    if(elemTyp == CElemDescription::tRecord)
      ret = "Record";
    if(elemTyp == CElemDescription::tSegment)
      ret = "Segment";
    if(elemTyp == CElemDescription::tString)
      ret = "String";
  }
  return ret;
}
//--------------------------------------------------
void CTlgWrapper::clearWrapperTlg()
{
  delete Tlg;
  Tlg=0;
}
//--------------------------------------------------
int CTlgWrapper::decodeTlg(char* bytes,int count)
{
  int ret=-1;
  try
  {
    ret=Tlg->decodeTlg(bytes,count);
  }
  catch(CExpUnknownTranspTyp& e)
  {
    String^ tlgStr = CStdConverter::StdStrToString(e.getTlg());
    String^ elemStr = CStdConverter::StdStrToString(e.getElem());
    String^ transStr = CStdConverter::StdStrToString(e.getTranspTyp());
    String^ mess = String::Concat("Transporttyp ",transStr," for ",elemStr);
    mess = String::Concat(mess," is no  define(Tlg: ",tlgStr," Elem: ",elemStr," )");
    throw gcnew CExpWrapper(mess,CExpWrapper::ErrorTyp::tUnknownTranspTyp);
  }
  catch(CExpConvertError& e)
  {
    String^ tlgStr = CStdConverter::StdStrToString(e.getTlg());
    String^ elemStr = CStdConverter::StdStrToString(e.getElem());
    String^ typeStr = CStdConverter::StdStrToString(e.getType());
    String^ valStr = CStdConverter::StdStrToString(e.getValue());
    String^ mess = nullptr;
    mess = String::Concat(mess,"Error by convert  ",valStr, " to ");
    mess = String::Concat(mess,typeStr," (Tel: ",tlgStr," Elem: ");
    mess = String::Concat(mess,elemStr,")");
    throw gcnew CExpWrapper(mess,CExpWrapper::ErrorTyp::tDecodeElem);
  }
  catch(...)
  {
    throw gcnew CExpWrapper("Unknown error",CExpWrapper::ErrorTyp::tUnknow);
  }
  return ret;
}
//--------------------------------------------------
int CTlgWrapper::compareElem(String^ elemName,String^ subElemName,String^ val)
{
  int ret=-1;
  std::string elemNameStr("");
  std::string subElemNameStr("");
  std::string valStr("");

  CStdConverter::StringToStdStr(elemName,elemNameStr);
  CStdConverter::StringToStdStr(subElemName,subElemNameStr);
  CStdConverter::StringToStdStr(val,valStr);
  
  if(Tlg != 0)
  {
    ret=Tlg->compareElement(elemNameStr,subElemNameStr,valStr);
  }
  return ret;
}
//--------------------------------------------------
int CTlgWrapper::getTlgTransBytesCount()
{
  int ret=-1;

  if(Tlg)
  {
    ret = Tlg->getTransBytesCount();
  }

  return ret;
}
//--------------------------------------------------
int CTlgWrapper::getTlgBodyTransBytesCount()
{
  int ret=-1;
  if(Tlg)
  {
    ret=Tlg->getTranspBodyBytesCount();
  }

  return ret;
}
//--------------------------------------------------
int CTlgWrapper::getSubElemTransBytesCount(int index)
{
  int ret=-1;

  if(Tlg != 0)
  {
    CTlgElem* elem = Tlg->getFlatElem(index);
    
    if (elem)
    {
      ret=elem->getTransBytesCount();
    }
  }

  return ret;
}
//-------------------------------------------------
int CTlgWrapper::getElemNummber(int elem,int subElem)
{
  int ret = 0;
  int i;
  int subElemCount;
  for(i=1;i<elem;i++)
  {
    subElemCount = getSubElemCount(i);
    if(subElemCount == 0)
    {
      ret++;
    }
    else
    {
      ret=ret+subElemCount;
    }
  }
  if(subElem == 0)
    ret = ret+1;
  else
    ret = ret+subElem;
  return ret;
}
//-------------------------------------------------
bool CTlgWrapper::updateTlg(CItemWrapper^ tlg)
{
  return true;
}
//-------------------------------------------------
CTlg* CTlgWrapper::getTlg()
{
  return Tlg;
}
//-------------------------------------------------
CTlgElem* CTlgWrapper::getElem(int id)
{
  if(Tlg != 0)
  {
    return Tlg->getFlatElem(id);
  }
  else
  {
    return nullptr;
  }
}
//-------------------------------------------------
bool CTlgWrapper::getTlgEmpty() 
{
  if(Tlg != 0)
  {
    return Tlg->getEmpty();
  }
  else
  {
    return true;
  }
}
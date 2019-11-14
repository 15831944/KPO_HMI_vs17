// Copyright 2006 SMS - Demag AG

//--------------------------------------------------
#include "CTlgElem.h"
#include "CTlg.h"
#include "CTlgDescription.h"
#include "CExpInvalidTlg.h"
#include "CExpConvertError.h"
#include "CExpTlgLenError.h"
#include "CInterConfig.h"
#include "CMessageStack.h"
#include "CLogWriter.h"
#include "CFormatConverter.h"
//---------------------------------------------------
CTlg::CTlg(const std::string& name,int len,const std::string& direction,int descr)
{
  this->DescrIndex = descr;
  CTlgDescription* descrTlg = CTlgDescription::getTlgDescriptionInztanz(DescrIndex);
  descrTlg->setNameTlg(name);
  descrTlg->setLenTlg(len);
  descrTlg->setDirection(direction);
  CTlgDescription::reserveTlgDescription(DescrIndex);
  EmptyFlag = true;
  LogWriter = CLogWriter::getLogWriter();
}
//---------------------------------------------------
CTlg::CTlg(const CTlg& Obj)
{
  int count,i;
  CTlgElem* elem = 0;

  this->DescrIndex = Obj.getDescrIndex();
  CTlgDescription::reserveTlgDescription(DescrIndex);
  count = Obj.getElemCount();
  this->EmptyFlag = Obj.getEmpty();
  for(i=1;i<=count;i++)
  {
    elem = Obj.cloneElem(i);
    ElemListe.push_back(elem);
  }
  LogWriter = CLogWriter::getLogWriter();
}
//---------------------------------------------------
CTlg::~CTlg()
{
  freeTlgDescription();
}
//---------------------------------------------------
CTlg* CTlg::clone() const
{
  return new CTlg(*this);
}
//---------------------------------------------------
CTlgElem* CTlg::cloneElem(int id)const
{
  CTlgElem* elem = 0;
  size_t key = size_t(id);
  if((key <= ElemListe.size()) && (key > 0))
    elem = ElemListe[id-1]->clone();
  else
  {
    std::string name = CTlgDescription::getTlgDescriptionInztanz(this->DescrIndex)->getNameTlg();
    LogWriter->WriteMessage(CLogWriter::Error,
                            "element in tlg <" + name + "> with id <" + 
                            CFormatConverter::IntToString(id) + "> not exist",
                            __FILE__,__FUNCTION__,__LINE__);
  }

  return elem;
}
//---------------------------------------------------
CTlgElem* CTlg::getFlatElem(int id) const
{
  CTlgElem* elem = 0;
  if((id <= int(ElemListe.size())) && (id > 0))
    elem = ElemListe[id-1];
  else
  {
    std::string name = CTlgDescription::getTlgDescriptionInztanz(this->DescrIndex)->getNameTlg();
    LogWriter->WriteMessage(CLogWriter::Error,
                            "element in tlg <" + name + "> with id <" + 
                            CFormatConverter::IntToString(id) + "> not exist",
                            __FILE__,__FUNCTION__,__LINE__);
  }

  return elem;
}
//---------------------------------------------------
CTlgElem* CTlg::getFlatElem(const std::string& id) const
{
  int count,i;
  CTlgElem* elem = 0;
  bool flag;

  count=int(ElemListe.size());
  flag=false;
  i=0;
  while((!flag) && (i<count))
  {
    if(ElemListe[i]->getNameElem() == id)
    {
      flag = true;
      elem = ElemListe[i];
    }
    else
    {
      i++;
    }
  }
  if (elem == 0)
  {
    std::string name = CTlgDescription::getTlgDescriptionInztanz(this->DescrIndex)->getNameTlg();
    LogWriter->WriteMessage(CLogWriter::Error,
                            "element in tlg <" + name + "> with id <" + id + "> not exist",
                            __FILE__,__FUNCTION__,__LINE__);
  }
  return elem;
}
//---------------------------------------------------
const std::string& CTlg::getTlgName()
{
  return CTlgDescription::getTlgDescriptionInztanz(this->DescrIndex)->getNameTlg();
}
//----------------------------------------------------
long CTlg::getTlgLen() 
{
  long ret=0;
  int test;
  int i;
  int count = getElemCount();
  for(i=1;i<=count;i++)
  {
    test = getFlatElem(i)->getLen();
    ret = ret + getFlatElem(i)->getLen();
  }
  return ret;
}
//----------------------------------------------------
long CTlg::getTlgBodyLen()
{
  return getTlgLen()-getTlgHeaderLen();
}
//-----------------------------------------------------
long CTlg::getTlgHeaderLen()
{
  long ret=0;
//  if(getTlgName() != "Head")
//    ret=getFlatElem("Header")->getLen();

  ret=getFlatElem("Header")->getLen();

  return ret;
}
//----------------------------------------------------
int CTlg::getTransBytesCount() const
{
  int ret = 0;
  int i,count;

  count = getElemCount();
  for(i=1;i<=count;i++)
  {
    ret = ret + getFlatElem(i)->getTransBytesCount();
  }

  return ret;
}
//----------------------------------------------------
int CTlg::getTranspBodyBytesCount() 
{
  return getTransBytesCount()-getTranspHeaderBytesCount();
}
//----------------------------------------------------
int CTlg::getTranspHeaderBytesCount()
{
  int ret=0;
  //if(getTlgName() != "Head")
  //  ret=getFlatElem("Header")->getTransBytesCount();

  ret=getFlatElem("Header")->getTransBytesCount();

  return ret;
}
//-----------------------------------------------------
void CTlg::setDescription(const std::string& descr)
{
  CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->setDescrTlg(descr);
}
//----------------------------------------------------
const std::string& CTlg::getDescription() const
{
  return CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getDescrTlg();
}
//----------------------------------------------------
const std::string& CTlg::getDirection() const
{
  return CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getDirection();
}
//----------------------------------------------------
long CTlg::getDescrIndex() const
{
  return this->DescrIndex;
}
//----------------------------------------------------
int CTlg::getElemCount() const
{
  return int(ElemListe.size());
}
//----------------------------------------------------
void CTlg::addElem(CTlgElem* elem)
{
  ElemListe.push_back(elem);
}
//----------------------------------------------------
bool CTlg::load(const std::string& line)
{
  bool ret = true;
  int count,i; 
  CTlgElem* elem = 0;
  std::string parserline("");
  std::string interName("");
  CInterConfig* interConf=0;
  char del;
  interConf = CInterConfig::getInterConfig(getInterfaceName());
  del=interConf->getLogDelimeter(); //Separator zwischen Elemente
  //Wenn line sich mit del endet, fuege " " zum Ende von line zu 
  count = int(line.find_last_of(del));
  
  if(count != std::string::npos)
  {
    parserline = line.substr(0,count);
    std::string str(" ");
    int length=int(parserline.size());
    int pos=int(parserline.find_last_of(del));
    if(length == pos+1)
    {
      parserline.append(str.c_str());
    }
  }
  else
  {
    parserline = line;
  }

  EmptyFlag = false;
  
  //parse des lines in Strings fuer Telegrammelemente
  CTokenParser* Parser = new CTokenParser();
  Parser->setDelimeter(del);
  Parser->parsen(parserline);

  //fuellen des Telegramms mit Werten
  count = getElemCount();
  for(i=1;i<=count;i++)
  {
      elem=getFlatElem(i);
      loadSubElement(elem,Parser);
  }

  //Wenn Parser nicht leer ist, line enthaelt mehr Elemente 
  if(!Parser->isEmpty())
  {
    delete Parser;
    std::string name = CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getNameTlg();
    throw CExpInvalidTlg(name,getTlgName(),"to large");
  }
  delete Parser;
  
  //Behandeln von Telegrammlaenge, abhaengig von Benutzereinstellung
  int tlgLen = 0;
  std::string elemLenName("");
  CInterConfig::LenTlgIdTyp lenTyp = interConf->getTreatLenIdMode();
  elemLenName=interConf->getElemLenName();
  if(lenTyp == CInterConfig::Total)
  {
    std::string elemVal("");
    //int lenTot = this->getTlgBodyLen() + this->getTlgHeaderLen();
    int lenTot = this->getTransBytesCount();
    
    elem = this->getFlatElem("Header");

    if (elem)
    {
      elem = this->getFlatElem("Header")->getSubElem(elemLenName);     
    }
    else
    {
      elem = this->getFlatElem(elemLenName);     
    }


    if (elem)
      elem->getValue(elemVal);
    else
      return false;

    tlgLen=CFormatConverter::StringToInt(elemVal);
    if(lenTot != tlgLen)
    {
      throw CExpTlgLenError(lenTyp,elemVal,getTlgName(),elem->getNameElem());
    }
  }
  if(lenTyp == CInterConfig::Body)
  {
    std::string elemVal("");
    int lenBod = this->getTranspBodyBytesCount();
    elem=this->getFlatElem("Header")->getSubElem(elemLenName);
    if (elem)
      elem->getValue(elemVal);
    else
      return false;
    tlgLen=CFormatConverter::StringToInt(elemVal);
    if(lenBod != tlgLen)
    {
      throw CExpTlgLenError(lenTyp,elemVal,getTlgName(),elem->getNameElem());
    }
  }

  return true;
}
//----------------------------------------------------
void CTlg::loadSubElement(CTlgElem* elem,CTokenParser* Parser)
{
  int sub_count,i;
  CInterConfig* interConf=CInterConfig::getInterConfig(getInterfaceName());
  CMessageStack* messStack = CMessageStack::getMessageStack();
  sub_count = elem->getSubElemCount();
  if(sub_count > 0)
  {
    for(i=1;i<=sub_count;i++)
    {
      loadSubElement(elem->getSubElem(i),Parser);
    }
  }
  else
  {
    if(!Parser->isEmpty())
    {
      std::string val("");
      Parser->getNextToken(val);
      if((!val.empty()) && (val.compare(" ")!=0))
      {
        elem->setValue(val,interConf);
      }
      else
      {
        elem->setDefaultValue();
      }
    }
    else
    {
      std::string name = CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getNameTlg();
      throw CExpInvalidTlg(name,getTlgName(),"to short");
    }
  }
}
//----------------------------------------------------
void CTlg::setEmpty(bool flag)
{
  this->EmptyFlag = flag;
}
//----------------------------------------------------
bool CTlg::getEmpty() const
{
  return this->EmptyFlag;
}
//----------------------------------------------------
int CTlg::serializeTlg(char* buffer,int len)
{
  int ret = -1;
  int tlgLen = this->getTransBytesCount();
  int elemCount,elemLen;
  CTlgElem* elem=0;
  int byteLen;
  int pos,i;
  char* elemBuff=0;
  // try
  //{
  elemBuff = new char[tlgLen*sizeof(char)];

  if(tlgLen <= len)
  {
    CInterConfig* interConfig = CInterConfig::getInterConfig(getInterfaceName());
    elemCount = getElemCount();
    pos=0;
    for(i=1;i<=elemCount;i++)
    {
      elem=getFlatElem(i);
      elemLen=elem->getTransBytesCount();
      byteLen=elem->serialize(&elemBuff[pos],elemLen,interConfig);
      pos=pos+byteLen;
    }
    ret = pos;
    for(i=0;i<pos;i++)
      buffer[i]=elemBuff[i];
  }
  else
  {
    //error
  }

  delete [] elemBuff;
    //}
   /* catch(CExpUnknownTranspTyp& e)
    {
        e.setTlg(getTlgName());
        if(elemBuff)
            delete [] elemBuff;
        throw e;
    }
    catch(...)
    {
        if(elemBuff)
            delete [] elemBuff;
    }*/

  return ret;
}
//----------------------------------------------------
void CTlg::setInterfaceName(const std::string& name)
{
  CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->setInterfaceName(name);
}
//----------------------------------------------------
const std::string& CTlg::getInterfaceName() const
{
  return CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getInterfaceName();
}
//----------------------------------------------------
void CTlg::getTlgAsString(std::string& tel,const std::string& del)
{
  int count,i;
  std::string elembuff("");

  tel.clear();
  count=getElemCount();
  for(i=1;i<=count;i++)
  {
    getFlatElem(i)->getElemAsString(elembuff,del);
    tel.append(elembuff);
    tel.append(del);
  }
}
//----------------------------------------------------
int CTlg::getElemOffset(const std::string& id) const
{
  int ret = 0;
  int count;
  int i;
  bool flag;

  count=int(ElemListe.size());
  flag=false;
  i=0;
  while((!flag) && (i<count))
  {
    if(ElemListe[i]->getNameElem() == id)
    {
      flag = true;
    }
    else
    {
      ret = ret + ElemListe[i]->getLen();
      i++;
    }
  }
  if(!flag)
    ret = -1;
  return ret;
}
//----------------------------------------------------
int CTlg::decodeTlg(char* bytes,int count)
{
  int ret = 0;
  int elemCount,i,j;
  int elemLen = 0;
  int pos;
  char* buffer=0;
  CTlgElem* elem=0;
  try
  {
    if(count == getTransBytesCount())
    {
      CInterConfig* interConfig = CInterConfig::getInterConfig(getInterfaceName());
      elemCount = getElemCount();
      pos=0;
      for(i=1;i<=elemCount;i++)
      {
        elem = getFlatElem(i);
        elemLen=elem->getTransBytesCount();
        buffer = new char[sizeof(char)*elemLen];
        for(j=0;j<elemLen;j++)
          buffer[j]=bytes[pos+j];
        elem->decodeElem(buffer,elemLen,interConfig);
        pos=pos+elemLen;
        delete [] buffer;
      }
      EmptyFlag = false;
    }
    else
    {
      ret = -1;
    }
  }
  catch(CExpUnknownTranspTyp& e)
  {
    if(buffer)
      delete [] buffer;
    e.setTlg(CTlgDescription::getTlgDescriptionInztanz(DescrIndex)->getNameTlg());
    throw(e);
  }
  catch(CExpConvertError& e)
  {
    if(buffer)
      delete [] buffer;
    e.setTlg(getTlgName());
    throw e;
  }
  catch(...)
  {
    if(buffer)
      delete [] buffer;
  }

  return ret;
}
//----------------------------------------------------
void CTlg::freeTlgDescription()
{
  int count,i;
  CTlgDescription::releaseTlgDescription(DescrIndex);
  count = (int)ElemListe.size();
  for(i=0;i<count;i++)
  {
    delete ElemListe[i];
  }
  ElemListe.clear();
}
//----------------------------------------------------
int CTlg::compareElement(const std::string& elemName,const std::string& subElemName,const std::string& val)
{
  int ret = -1;
  CTlgElem* elem=0;
  elem=getFlatElem(elemName);
  if(elem)
    ret=elem->compare(val,subElemName);
  return ret;
}
//----------------------------------------------------

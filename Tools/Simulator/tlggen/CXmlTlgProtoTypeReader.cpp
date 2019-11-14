// Copyright 2006 SMS - Demag AG

//-----------------------------------------------
#include "CXmlTlgProtoTypeReader.h"
#include "CTlgBuilder.h"
#include "CTlgProtoTypSet.h"
#include "CFormatConverter.h"
#include "CExpConvertError.h"
#include "CExpUnknownElemTyp.h"
#include "CExpUnknowTranspTyp.h"
#include "CTlg.h"
#include "CInterConfig.h"
#include "TinyXml.h"
#include <assert.h>
#include "CLogWriter.h"
//------------------------------------------------
CXmlTlgProtoTypeReader::CXmlTlgProtoTypeReader():
XmlDoc(0), ErrorMessage(""), TlgProtoTypSet(0)
{
}
//------------------------------------------------
CXmlTlgProtoTypeReader::~CXmlTlgProtoTypeReader()
{
  
}
//------------------------------------------------
CTlgProtoTypSet * CXmlTlgProtoTypeReader::readXmlProtoInterface(const std::string& path)
{
  bool flag;
  int test = 0;
  CTlgProtoTypSet* TlgProtoTypSet = 0;
  TiXmlHandle* xmlHandle=0;
  try
  {
    XmlDoc = new TiXmlDocument(path.c_str());
    flag = XmlDoc->LoadFile();
    if(flag)
    {
      TlgProtoTypSet = new CTlgProtoTypSet();
      readInterfaceDescr(TlgProtoTypSet);
      readAllTelegrams(TlgProtoTypSet);
    }
    else
    {
      ErrorMessage += "File couldn't be read";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
    }
    delete XmlDoc;
  }
  catch(CExpConvertError& e)
  {
    delete TlgProtoTypSet;
    TlgProtoTypSet = 0;
    ErrorMessage += e.getValue() + "is not " + e.getType();
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
  }
  catch(CExpUnknownElemTyp& e)
  {
    delete TlgProtoTypSet;
    TlgProtoTypSet = 0;
    ErrorMessage = "Elementtyp " + e.getType() + " is uknown(tlg: " + e.getTlg()+" elem: " + e.getElem() +")";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
  }
  catch(CExpUnknownTranspTyp& e)
  {
    delete TlgProtoTypSet;
    TlgProtoTypSet = 0;
    ErrorMessage = "Transporttyp " + e.getTranspTyp() + " is uknown(tlg: " + e.getTlg()+" elem: " + e.getElem() +")";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
  }
  catch(...)
  {
    delete TlgProtoTypSet;
    TlgProtoTypSet = 0;
    ErrorMessage = "Unknown Error";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
  }
  return TlgProtoTypSet;
}
//------------------------------------------------
int CXmlTlgProtoTypeReader::readInterfaceDescr(CTlgProtoTypSet* inter)
{
  std::string modstr("module");
  std::string namestr("");
  std::string descrstr("");
  std::string verstr("");
  std::string padding("");
  std::string paddingStr("");
  std::string transpType("");
  
  CInterConfig* TransportRules = 0;

  TiXmlElement* root = XmlDoc->RootElement(); 
  if(root)
  {
    const char* mod = root->Value();
    if(modstr != mod)
    {
      std::string mess = "root string is not similar with <" + modstr + ">";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
    }
    else
    {
      const char* name = root->Attribute("name");
      const char* ver = root->Attribute("ver");
      namestr.assign(name);
      verstr.assign(ver);

      readComment(root,descrstr);
      inter->setComment(descrstr);
      readEncodingRules(root,transpType,padding,paddingStr);
      
      inter->setName(namestr);
      inter->setVersion(verstr);

      TransportRules = CInterConfig::getInterConfig(namestr);
      if(padding == "left")
        TransportRules->setPaddingDirection(CInterConfig::Left);
      else
        TransportRules->setPaddingDirection(CInterConfig::Right);

      if(!paddingStr.empty())
        TransportRules->setPaddingString(paddingStr);
      TransportRules->setSwapping(false);
    }
  }
  return 0;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readComment(TiXmlElement* elem,std::string& comment)
{
  bool ret = false;

  TiXmlElement* element = elem->FirstChildElement("comment");
  if(element)
  {
    TiXmlNode* elemText = element->FirstChild();
    if(elemText)
    {
      const char* decr=elemText->Value();
      comment.assign(decr);
    }  
    ret = true;
  }
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readEncodingRules(TiXmlElement* elem,std::string& traspType,std::string& padding,std::string& paddingStr)
{
   bool ret = false;
   TiXmlElement* element = elem->FirstChildElement("encodingRules");
   if(element)
   {
     const char* trans = element->Attribute("transType");
     const char* padd = element->Attribute("padding");
     const char* paddStr = element->Attribute("paddingStr");
     traspType.assign(trans);
     padding.assign(padd);
     paddingStr.assign(paddStr);
     ret = true;
   }
   return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readAllTelegrams(CTlgProtoTypSet* inter)
{
  bool ret = false;
 // bool flag = true;
  int i=0;
  TiXmlElement* tel = 0;
  TiXmlHandle docHandle(XmlDoc);
  //---test
  while((tel = docHandle.FirstChild("module").Child("telegram",i).Element()) != 0)
  {
    readOneTelegram(inter,tel);
    i++;
  }
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readOneTelegram(CTlgProtoTypSet* inter,TiXmlElement* elem)
{
  bool ret = true;
  CTlg* tlg=0;
  std::string namestr("");
  std::string lenstr("");
  std::string dirstr("");
  std::string comment("");
  long lenTlg=0;
  int i;
  TiXmlElement* tlgElem=0;
  std::string mess("");
  
  const char* name = elem->Attribute("name");
  const char* len = elem->Attribute("len");
  const char* dir = elem->Attribute("direction");

  namestr.assign(name);
  lenstr.assign(len);
  dirstr.assign(dir);
  lenTlg = CFormatConverter::StringToLong(len);
  TlgBuilder.makeTlg(namestr,lenTlg,dirstr);
  readComment(elem,comment);
  TlgBuilder.setTlgDescr(comment); 
  TlgBuilder.setTlgInterName(inter->getName());
  
  TiXmlHandle docHandle(elem);
  i=0;
  while((tlgElem = docHandle.FirstChild("record").Child("element",i).Element()) != 0)
  {
    //---test
    readElement(tlgElem);
    i++;
  }
  tlg = TlgBuilder.getTlg();
  inter->addTlgPrototyp(tlg);
  //Message in die Log -Datei schreiben
  mess = inter->getName() + "->" + name + " " + comment;
  CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Info,mess,__FILE__,__FUNCTION__,__LINE__);

  return true;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readElement(TiXmlElement* elem)
{
  bool ret = true;
  bool flag;
  std::string namestr("");
  std::string lenstr("");
  std::string countstr("");
  std::string comment("");
  long lenElem=0;
  long countElem=0;
  bool isRecord;

  std::string leer_zeichen("_");

  std::string appType("");
  std::string transpType("");
  std::string unit("");
  std::string factor("");
  std::string minstr("");
  std::string maxstr("");
  std::string numFmt("");

  const char* name = elem->Attribute("name");
  const char* len = elem->Attribute("len");
  const char* count = elem->Attribute("count");

  bool convertLength = true;
  try
  {
    namestr.assign(name);
    lenstr.assign(len);
    countstr.assign(count);
    lenElem   = CFormatConverter::StringToLong(lenstr);
    convertLength = false;
    countElem = CFormatConverter::StringToLong(countstr);
    readComment(elem,comment);
	  isRecord = isRecords(elem);
	
	  if(isRecord && (countElem == 1)) //eins Recordselement
	  {
		  TlgBuilder.makeRecords(namestr);
      TlgBuilder.setElemComment(comment);
      flag = readUserDefinedTyp(elem);
      TlgBuilder.endRecordsElement();
	  }
	  else if(isRecord && (countElem  > 1)) //array aus Recordselementts
	  {
		  TlgBuilder.makeArrayElement(name,countElem);
		  TlgBuilder.setElemComment(comment);
    
      for(int i=0;i<countElem;i++)
		  {
        TlgBuilder.makeRecords(name+leer_zeichen+CFormatConverter::IntToString(i+1));
			  
			  if ( !readUserDefinedTyp(elem) )
        {
          readRecord(elem);
        }
			  TlgBuilder.endRecordsElement();
		  }
		  //lenElem = CFormatConverter::StringToLong(lenstr);

		  //TlgBuilder.setArrayAttribute(appType,transpType,lenElem);
		  TlgBuilder.endArray();
	  }
	  else if(!isRecord && (countElem == 1)) // simple Elements
	  {
		  flag = readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr,numFmt);
		  if(flag)
		  {
			  lenElem = CFormatConverter::StringToLong(lenstr);
			  TlgBuilder.makeSimpleElement(namestr,appType,lenElem);
			  TlgBuilder.setElemComment(comment);
			  TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr,numFmt);
			  TlgBuilder.endSimpleElement();
		  }
		  else
		  {
			  assert(false);
        std::string mess = "<" + namestr + "> is not simple element";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
		  }
	  }
	  else if(!isRecord && (countElem > 1))//array aus Simplelements
	  {
		  flag = readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr,numFmt);
		  if(flag)
		  {
			  TlgBuilder.makeArrayElement(name,countElem);
			  TlgBuilder.setElemComment(comment);
			  lenElem = CFormatConverter::StringToLong(lenstr);
			  for(int i=0;i<countElem;i++)
			  {
          TlgBuilder.makeSimpleElement(name+leer_zeichen+CFormatConverter::IntToString(i+1),appType,lenElem);
          //TlgBuilder.makeSimpleElement(name,appType,lenElem);
          /*TlgBuilder.makeSimpleElement(" ",appType,lenElem);*/
				  TlgBuilder.setElemComment(comment);
				  TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr,numFmt);
				  TlgBuilder.endSimpleElement();
			  }
			  //TlgBuilder.setArrayAttribute(appType,transpType,lenElem);
			  TlgBuilder.endArray();
		  }
		  else
		  {
			  assert(false);
        std::string mess = "<" + namestr + "> is not array with simple element";
        CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
		  }
	  }
	  else
	  {
		  //Andere Konstruktionen eines Elements sind unmöglich 
		  //(Xml Beschreibung ist fehlerhaft)
		  std::string mess =  "xml specification of this element <" + namestr + "> is wrong";
      CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
      assert(false);
	  }

    /*if(countElem > 1) //array
    {
      TlgBuilder.makeArrayElement(name,countElem);
      TlgBuilder.setElemComment(comment);
      if(isSimple(elem))
      {
        readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr);
        lenElem = CFormatConverter::StringToLong(lenstr);
        TlgBuilder.setArrayAttribute(appType,transpType,lenElem);
      }
      else
      {
        TlgBuilder.makeRecords("");
        //TlgBuilder.setElemComment(comment);
        flag = readUserDefinedTyp(elem);
        TlgBuilder.endRecordsElement();
      }
      TlgBuilder.endArray();
    }
    else
    {
      flag = readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr);
      if(flag) //simple
      {
        lenElem = CFormatConverter::StringToLong(lenstr);
        TlgBuilder.makeSimpleElement(namestr,appType,lenElem);
        TlgBuilder.setElemComment(comment);
        TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr);
        TlgBuilder.endSimpleElement();
      }
      else //records
      {
        TlgBuilder.makeRecords(namestr);
        TlgBuilder.setElemComment(comment);
        flag = readUserDefinedTyp(elem);
        TlgBuilder.endRecordsElement();
      }
    }*/
  }
  catch (CExpConvertError& e)
  {
    ErrorMessage = "Telegram: " + TlgBuilder.getTlg()->getTlgName();;
    ErrorMessage += " Element: " + namestr;
    if (convertLength)
      ErrorMessage += " Length: '" + lenstr +"'";
    else
      ErrorMessage += " Count: '" + countstr +"'";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,ErrorMessage,__FILE__,__FUNCTION__,__LINE__);
    throw e;
  }
  return ret;
}

//------------------------------------------------
bool CXmlTlgProtoTypeReader::readPrimitive(TiXmlElement* elem,std::string& appType,std::string& transpType,std::string& len,
                       std::string& unit,std::string& factor,std::string& min,std::string& max,std::string& numFmt)
{
  bool ret = false;
  const char* val = 0;
  TiXmlElement* primitive=0;
  primitive=elem->FirstChildElement("primitive");

  TiXmlElement* encodingRules=0;
  encodingRules=primitive->FirstChildElement("encodingRules");

  if(primitive)
  {
    // primitive
    val=primitive->Attribute("appType");
    appType.assign(val);
    val=primitive->Attribute("transType");
    transpType.assign(val);
    val=primitive->Attribute("len");
    len.assign(val);
    val=primitive->Attribute("unit");
    unit.assign(val);
    val=primitive->Attribute("factor");
    factor.assign(val);
    val=primitive->Attribute("min");
    min.assign(val);
    val=primitive->Attribute("max");
    max.assign(val);

    // encodingRules
    if (encodingRules)
    {
      val=encodingRules->Attribute("numFmt");
      numFmt.assign(val);
    }
    
    ret = true;
    //---add element to tlg
  }
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readUserDefinedTyp(TiXmlElement* elem)
{
  bool ret = false;
  TiXmlElement* def=0;
  std::string typestr("");

  def=elem->FirstChildElement("userDefined");
  if(def)
  {
    const char* type = def->Attribute("name");
    typestr.assign(type);
    if(!typestr.empty())
    {
      if(readUserDefinedType(typestr))
        ret=true;
    }
  }
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::readUserDefinedType(std::string& name)
{
  bool ret = false;
  TiXmlElement* tel = 0;
  TiXmlElement* tlgElem=0;
  std::string comment("");
  std::string lenstr("");
  long lenElem;

  std::string namestr("");
  std::string appType("");
  std::string transpType("");
  std::string unit("");
  std::string factor("");
  std::string minstr("");
  std::string maxstr("");
  std::string numFmt("");

  tel = findType(name);
  if(tel)
  {
    const char* len = tel->Attribute("len");
    lenstr.assign(len);
    lenElem = CFormatConverter::StringToLong(lenstr);

    readComment(tel,comment);
    TlgBuilder.setElemComment(comment);

    TiXmlHandle docHandle(tel);
    int i=0;
    if(docHandle.FirstChild("element").Child("record",0).Element())
    {
      while((tlgElem = docHandle.FirstChild("element").FirstChild("record").Child("element",i).Element()) != 0)
	    {
		    //const char* name = tlgElem->Attribute("name");
		    //namestr.assign(name);
		    //readPrimitive(tlgElem,appType,transpType,lenstr,unit,factor,minstr,maxstr);
		    //lenElem = CFormatConverter::StringToLong(lenstr);
        //TlgBuilder.makeSimpleElement(namestr,appType,lenElem);
        //TlgBuilder.setElemComment(comment);
        //TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr);
        //TlgBuilder.endSimpleElement();
		    readElement(tlgElem);
		    i++;
	    }
    }
    else
    {
		  /*assert(false);*/
      while((tlgElem = docHandle.Child("element",i).Element()) != 0)
      {
        const char* name = tlgElem->Attribute("name");
        namestr.assign(name);
        readPrimitive(tlgElem,appType,transpType,lenstr,unit,factor,minstr,maxstr,numFmt);
        lenElem = CFormatConverter::StringToLong(lenstr);
        TlgBuilder.makeSimpleElement(namestr,appType,lenElem);
        TlgBuilder.setElemComment(comment);
        TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr,numFmt);
        TlgBuilder.endSimpleElement();
        i++;
      }
    }
    ret = true;
  }
  return ret;
}

bool CXmlTlgProtoTypeReader::readRecord(TiXmlElement* elem)
{
  bool ret = false;
  TiXmlElement* tlgElem=0;
  std::string comment("");
  std::string lenstr("");
  long lenElem;

  std::string namestr("");
  std::string appType("");
  std::string transpType("");
  std::string unit("");
  std::string factor("");
  std::string minstr("");
  std::string maxstr("");
  std::string numFmt("");

  const char* len = elem->Attribute("len");
  lenstr.assign(len);
  lenElem = CFormatConverter::StringToLong(lenstr);

  readComment(elem,comment);
  TlgBuilder.setElemComment(comment);

  TiXmlHandle docHandle(elem);
  int i=0;
  if(docHandle.Child("record",0).Element())
  {
    while((tlgElem = docHandle.FirstChild("record").Child("element",i).Element()) != 0)
    {
	    readElement(tlgElem);
	    i++;
    }
  }
  else
  {
	  /*assert(false);*/
    while((tlgElem = docHandle.Child("element",i).Element()) != 0)
    {
      readElement(tlgElem);
      i++;
    }
  }
  ret = true;

  return ret;
}

//------------------------------------------------
TiXmlElement* CXmlTlgProtoTypeReader::findType(std::string& name)
{
  TiXmlElement* ret = 0;
  bool flag;
  int i;
  TiXmlHandle docHandle(XmlDoc);

  i=0;
  flag = false;
  while((!flag) && ((ret = docHandle.FirstChild("module").Child("type",i).Element()) != 0))
  {
    if(ret)
    {
      if(name == ret->Attribute("name"))
      {
        flag = true;
      }
      else
      {
        i++;
      }
    }
  }
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::isRecords(TiXmlElement* elem)
{
  bool ret = false;
  if(elem->FirstChild("userDefined"))
    ret = true;
  if(elem->FirstChild("record"))
    ret = true;
  return ret;
}
//------------------------------------------------
bool CXmlTlgProtoTypeReader::isSimple(TiXmlElement* elem)
{
  bool ret = false;
  if(elem->FirstChild("primitive"))
    ret = true;
  return ret;
}
//------------------------------------------------
const std::string&  CXmlTlgProtoTypeReader::getErrorMessage() const
{
  return this->ErrorMessage;
}
//------------------------------------------------
//------------------------------------------------
/*bool CXmlTlgProtoTypeReader::readElementRekursiv(TiXmlElement* elem)
{
  bool ret = true;
  bool flag;
  std::string namestr("");
  std::string lenstr("");
  std::string countstr("");
  std::string comment("");
  long lenElem=0;
  long countElem=0;

  std::string appType("");
  std::string transpType("");
  std::string unit("");
  std::string factor("");
  std::string minstr("");
  std::string maxstr("");

  const char* name = elem->Attribute("name");
  const char* len = elem->Attribute("len");
  const char* count = elem->Attribute("count");

  bool convertLength = true;
  try
  {
    namestr.assign(name);
    lenstr.assign(len);
    countstr.assign(count);
    lenElem   = CFormatConverter::StringToLong(lenstr);
    convertLength = false;
    countElem = CFormatConverter::StringToLong(countstr);
    readComment(elem,comment);
    //*************************************************
    if(countElem > 1)
    {
      TlgBuilder.makeArrayElement(name,countElem);
      TlgBuilder.setElemComment(comment);
      
      if(isSimple(elem))
      {
        readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr);
        lenElem = CFormatConverter::StringToLong(lenstr);
        TlgBuilder.setArrayAttribute(appType,transpType,lenElem);
      }
      else
      {
        
        //TlgBuilder.makeRecords("");
        ////TlgBuilder.setElemComment(comment);
        //flag = readUserDefinedTyp(elem);
        //TlgBuilder.endRecordsElement();
      }
      TlgBuilder.endArray();
    }
    else
    {
      flag = readPrimitive(elem,appType,transpType,lenstr,unit,factor,minstr,maxstr);
      if(flag) //simple
      {
        lenElem = CFormatConverter::StringToLong(lenstr);
        TlgBuilder.makeSimpleElement(namestr,appType,lenElem);
        TlgBuilder.setElemComment(comment);
        TlgBuilder.setElemInfo(transpType,unit,factor,minstr,maxstr);
        TlgBuilder.endSimpleElement();
      }
      else //records
      {
        TlgBuilder.makeRecords(namestr);
        TlgBuilder.setElemComment(comment);
        flag = readUserDefinedTyp(elem);
        TlgBuilder.endRecordsElement();
      }
    }
  }
  catch (CExpConvertError& e)
  {
    ErrorMessage = "Telegram: " + TlgBuilder.getTlg()->getTlgName();;
    ErrorMessage += " Element: " + namestr;
    if (convertLength)
      ErrorMessage += " Length: '" + lenstr +"'";
    else
      ErrorMessage += " Count: '" + countstr +"'";
    throw e;
  }
  return ret;
}*/
// Copyright 2006 SMS - Demag AG

#include "CTlgElemString.h"
#include "CLogWriter.h"

#pragma warning( disable : 4996 )
//--------------------------------------------------------------------------------
CTlgElemString::CTlgElemString(const CElemDescription::TransportType transp,const int len,
							                 const std::string& val,const std::string& name):
CTlgElem(transp,len,name)
{
	this->Value = val;
}
//---------------------------------------------------------------------------------
CTlgElemString::CTlgElemString(int index):
CTlgElem(index)
{
  this->setDefaultValue();
}
//---------------------------------------------------------------------------------
CTlgElemString::CTlgElemString(const CTlgElemString& Obj)
{
	std::string val("");
	Obj.getValue(val);
	this->Value = val;
  this->DescrIndex = Obj.getDescrIndex();
	CElemDescription::reserveElemDescription(DescrIndex);
}
//---------------------------------------------------------------------------------
CTlgElemString::~CTlgElemString()
{
}
//---------------------------------------------------------------------------------
CTlgElem* CTlgElemString::clone() const
{
  return new CTlgElemString(*this);
}
//---------------------------------------------------------------------------------
void CTlgElemString::getValue(std::string& value) const
{
  if (this->Value.empty())
  {
    value = " ";
  }
  else
  {
    value = this->Value;
  }
}
//---------------------------------------------------------------------
int CTlgElemString::serialize(char* buffer,int len,CInterConfig* interConfig)
{
  int ret=-1; // Rueckgabewert im Fehlerfall
	CElemDescription::TransportType trans = getElemTranspTyp();
  switch (trans)
  {
    case CElemDescription::ascii:
      ret=serializeAsASCII(buffer,len,interConfig);
      break;
    case CElemDescription::binary:
      ret=serializeAsBinary(buffer,len,interConfig); 
      break;
    case CElemDescription::binaryL3D:
      ret=serializeAsBinaryL3D(buffer,len,interConfig);
      break;
    case CElemDescription::binaryCCSD:
      ret=serializeAsBinaryCCSD(buffer,len,interConfig);
      break;
		case CElemDescription::binaryRD:
			ret=serializeAsBinaryRD(buffer,len,interConfig);
			break;
    case CElemDescription::binaryRS:
      ret=serializeAsBinaryRS(buffer,len,interConfig);
      break;
    default:
      //Fehler: ubekannte Kodierungstyp
      throw CExpUnknownTranspTyp("","",getNameElem());
      break;
  }	
	return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::serializeAsBinaryL3D(char* buffer,int len,CInterConfig* interConfig)
{
  int ret=-1;
  char* p_ch;
  std::string valStr("");
  long valLong;
  int transBytesCount;
  transBytesCount=getTransBytesCount();
  if(transBytesCount == len)
  {
    //Jahr
    valStr=Value.substr(0,4);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=buffer;
    longToByteStream(p_ch,valLong,interConfig);
    //Monat
    valStr=Value.substr(5,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Tag
    valStr=Value.substr(8,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Stunde
    valStr=Value.substr(11,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Minute
    valStr=Value.substr(14,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Sekunde
    valStr=Value.substr(17,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
  }
  p_ch=p_ch+4;
  longToByteStream(p_ch,0,interConfig);
  ret=transBytesCount;
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::serializeAsBinaryCCSD(char* buffer,int len,CInterConfig* interConfig)
{
  int ret=-1;
  char* p_ch;
  std::string valStr("");
  long valLong;
  int transBytesCount;
  transBytesCount=getTransBytesCount();
  if(transBytesCount == len)
  {
    //Jahr
    valStr=Value.substr(0,4);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=buffer;
    longToByteStream(p_ch,valLong,interConfig);
    //Monat
    valStr=Value.substr(5,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Tag
    valStr=Value.substr(8,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Stunde
    valStr=Value.substr(11,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Minute
    valStr=Value.substr(14,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Sekunde
    valStr=Value.substr(17,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
  }
  p_ch=p_ch+4;
  longToByteStream(p_ch,0,interConfig);
  ret=transBytesCount;
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::serializeAsBinaryRD(char* buffer,int len,CInterConfig* interConfig)
{
	int ret=-1;
  char* p_ch;
  std::string valStr("");
  long valLong;
  int transBytesCount;
  transBytesCount=getTransBytesCount();
  if(transBytesCount == len)
  {
    //Jahr
    valStr=Value.substr(0,4);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=buffer;
    longToByteStream(p_ch,valLong,interConfig);
    //Monat
    valStr=Value.substr(5,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Tag
    valStr=Value.substr(8,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Stunde
    valStr=Value.substr(11,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Minute
    valStr=Value.substr(14,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
    //Sekunde
    valStr=Value.substr(17,2);
    valLong=CFormatConverter::StringToLong(valStr);
    p_ch=p_ch+4;
    longToByteStream(p_ch,valLong,interConfig);
  }
  ret=transBytesCount;
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::serializeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	std::string valStr = Value;
	int lenElem = getLen(); 
	int lenVal = int(valStr.size());
	int ret = -1;

  std::string numFmt;
    
  this->getNumFmt(numFmt);

	//ergaenzen des Wert um fehlende Anzahl der Bytes
	if(lenElem > lenVal)
	{

	  char paddChar = interConfig->getPaddingString(); //Fuellzeichen
	  
    CInterConfig::PaddingTyp dir = interConfig->getPaddingDirection();

	  if(dir == CInterConfig::Left)
	  {
		  valStr.insert(0,(lenElem-lenVal),paddChar);
	  }
	  else
	  {
		  valStr.append((lenElem-lenVal),paddChar);
	  }
	}

  else if (lenElem < lenVal)
  {
    std::string mess = "Error on serialization, content > size of element : " + this->getNameElem();
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }

	//kopieren den Wert in buffer
	if(lenElem == valStr.length())
	{
		valStr.copy(buffer,lenElem);
      ret=lenElem;
	}

  return ret;
}
//----------------------------------------------------------------------
int CTlgElemString::serializeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
  int elemLen;
	int i,pos,factor;
  const char* buff_char;
  bool swapping;

	elemLen = getLen();
  buff_char = Value.c_str();
  swapping = interConfig->getSwapping();
  //Einstellung der Bytereihenfolge fuer Kodirung
	if(!swapping)
	{
		pos = 0;
		factor = 1;
	}
	else
	{
		pos = elemLen-1;
		factor = -1;
	}
  // Kodierung des Wertes in Byte - Stream (Ergebniss in buffer)
	for(i=0;i<elemLen;i++)
	{
		//buff_char = val & maske;
		buffer[pos+factor*i] = buff_char[i];
		//val = val >> 8;
	}
	return elemLen;
}
//---------------------------------------------------------------------
int CTlgElemString::serializeAsBinaryRS(char* buffer,int len,CInterConfig* interConfig)
{
  int ret = -1;
  long elemLen = (long)Value.size();
  int elemLen1 = getLen();
  int elemByteLen = getTransBytesCount();

  if(len == elemByteLen)
  {
    serializeAsASCII(buffer+4,elemLen1,interConfig);
    longToByteStream(buffer,long(elemLen),interConfig);
    ret = elemByteLen;
  }

  return ret;
}
//---------------------------------------------------------------------
void CTlgElemString::getElemAsString(std::string& elem,const std::string& del)
{
  elem=Value;
}
//---------------------------------------------------------------------
void CTlgElemString::setValue(const std::string& val,CInterConfig* interConf)
{
	int len = CElemDescription::getDescriptionInztanz(DescrIndex)->getElemLen();

	if(len < int(val.length()))
	{
    CExpConvertError error(val,"overflow, valid length of this string is " + CFormatConverter::IntToString(len)+ " characters");
    error.setElem(this->getNameElem());
		throw error;
	}
	else
	{
		this->Value = val;
	}
}
//---------------------------------------------------------------------
void CTlgElemString::setDefaultValue()
{
	Value = " ";
}
//---------------------------------------------------------------------
int CTlgElemString::decodeElem(char* bytes,int count,CInterConfig* interConfig)
{
	std::string val("");
	//int elemLen = getLen();
  int elemLen = getTransBytesCount();
	CElemDescription::TransportType trans = getElemTranspTyp();
  try
  {
    switch(trans)
    {
      case CElemDescription::ascii:
        decodeAsASCII(bytes,elemLen,interConfig);
        break;
      case CElemDescription::binary:
        decodeAsBinary(bytes,elemLen,interConfig);
        break;
      case CElemDescription::binaryL3D:
        decodeAsBinaryL3D(bytes,elemLen,interConfig);
        break;
      case CElemDescription::binaryCCSD:
        decodeAsBinaryCCSD(bytes,elemLen,interConfig);
        break;
		  case CElemDescription::binaryRD:
		    decodeAsBinaryRD(bytes,elemLen,interConfig);
		    break;
      case CElemDescription::binaryRS:
        decodeAsBinaryRS(bytes,elemLen,interConfig);
        break;
      default:
        //Fehler: ubekannte Kodierungstyp
        std::string transStr=CElemDescription::getDescriptionInztanz(DescrIndex)->getTransTypAsString();
        throw CExpUnknownTranspTyp(transStr,"",getNameElem());
        break;
    }
  }
  catch(CExpConvertError& e)
  {
    e.setElem(getNameElem());
    throw e;
  }
	return elemLen;
}
//---------------------------------------------------------------------
int CTlgElemString::decodeAsASCII(char* bytes,int count,CInterConfig* interConfig)
{
  int ret = -1;
  std::string val("");
  val.append(bytes,count);
	removeFillChar(val,interConfig);
	Value=val;
  ret=(int)val.size();
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::decodeAsBinary(char* bytes,int count,CInterConfig* interConfig)
{
  int ret = -1;
  std::string val("");
  val.append(bytes,count);
	removeFillChar(val,interConfig);
	Value=val;
  ret=(int)val.size();
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::decodeAsBinaryL3D(char* bytes,int count,CInterConfig* interConfig)
{
  int ret = -1;
  int longSize;
  long longVal;
  std::string strVal("");
  int countBytes,i;
  char* p_ch;

  countBytes=7;
  p_ch=bytes;
  longSize=sizeof(long);
  if(count == countBytes*longSize)
  {
    Value.clear();
    for(i=0;i<countBytes-1;i++)
    {
      longVal=byteStreamToLong(p_ch,interConfig);
      strVal=CFormatConverter::IntToString(longVal);
      Value.append(strVal);
      if(i != countBytes-2)
      {
        Value.append("-");
      }
      p_ch=p_ch+4;
    }
  }
  else
  {
    //fehler
  }
  ret = countBytes*longSize;
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::decodeAsBinaryCCSD(char* bytes,int count,CInterConfig* interConfig)
{
  int ret = -1;
  int longSize;
  long longVal;
  std::string strVal("");
  int countBytes,i;
  char* p_ch;

  countBytes=7;
  p_ch=bytes;
  longSize=sizeof(long);
  if(count == countBytes*longSize)
  {
    Value.clear();
    for(i=0;i<countBytes-1;i++)
    {
      longVal=byteStreamToLong(p_ch,interConfig);
      strVal=CFormatConverter::IntToString(longVal);
      Value.append(strVal);
      if(i != countBytes-2)
      {
        Value.append("-");
      }
      p_ch=p_ch+4;
    }
  }
  else
  {
    //fehler
    std::string mess ("Error (count != countBytes*longSize)");
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  ret=countBytes*longSize;
  return ret;
}
//-----------------------------------------------------------------------------
int CTlgElemString::decodeAsBinaryRD(char* bytes,int count,CInterConfig* interConfig)
{
	int ret = -1;
  int longSize;
  long longVal;
  std::string strVal("");
  int countBytes,i;
  char* p_ch;

  countBytes=6;
  p_ch=bytes;
  longSize=sizeof(long);
  if(count == countBytes*longSize)
  {
    Value.clear();
    for(i=0;i<countBytes;i++)
    {
      longVal=byteStreamToLong(p_ch,interConfig);
      strVal=CFormatConverter::IntToString(longVal);
      Value.append(strVal);
      if(i != countBytes)
      {
        Value.append("-");
      }
      p_ch=p_ch+4;
    }
  }
  else
  {
    std::string mess ("Error (count != countBytes*longSize)");
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  ret = countBytes*longSize;
  return ret;
}
//-----------------------------------------------------------------------------
int CTlgElemString::decodeAsBinaryRS(char* bytes,int count,CInterConfig* interConfig)
{
  int ret = -1;
  ret=decodeAsASCII(bytes+4,count-4,interConfig);
  return ret;
}
//-----------------------------------------------------------------------------
int CTlgElemString::compare(const std::string& val,const std::string& subElemName)
{
  int ret = -2;
  if(Value > val)
  {
    ret=1;
  }
  else
  {
    if(Value < val)
    {
      ret=-1;
    }
    else
    {
      ret=0;
    }
  }
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemString::getTransBytesCount() const
{
	int ret;
	CElemDescription::TransportType trans = CElemDescription::getDescriptionInztanz(DescrIndex)->getTranspTypeElem();
	switch(trans)
	{
		case CElemDescription::binaryCCSD:
			ret = 28;
			break;
		case CElemDescription::binaryL3D:
			ret = 28;
			break;
		case CElemDescription::binaryRD:
      if(getElemType() == CElemDescription::tInteger)
        ret=0;
      else
      ret = 24;
			break;
    case CElemDescription::binaryRS:
      ret = CElemDescription::getDescriptionInztanz(DescrIndex)->getElemLen()+sizeof(long);
      break;
		default:
			ret = CElemDescription::getDescriptionInztanz(DescrIndex)->getElemLen();
	}
	return ret;
}
//---------------------------------------------------------------------

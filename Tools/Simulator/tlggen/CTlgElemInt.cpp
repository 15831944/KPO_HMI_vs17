// Copyright SMS - Demag AG

#include "CTlgElemInt.h"
#include "CLogWriter.h"

#pragma warning( disable : 4996 )

//-----------------------------------------------------------------------
CTlgElemInt::CTlgElemInt(const CElemDescription::TransportType transp,
						 const int len,int val,const std::string& name):
CTlgElem(transp,len,name)
{
	this->Value = val;
}
//-----------------------------------------------------------------------
CTlgElemInt::CTlgElemInt(const CTlgElemInt& Obj)
{
	std::string val("");
	Obj.getValue(val);
	this->Value =CFormatConverter::StringToInt(val);
  this->DescrIndex = Obj.getDescrIndex();
	CElemDescription::reserveElemDescription(DescrIndex);
}
//-----------------------------------------------------------------------
CTlgElemInt::CTlgElemInt(int index):
CTlgElem(index)
{
  this->setDefaultValue();
}
//-----------------------------------------------------------------------
CTlgElemInt:: ~CTlgElemInt()
{
}

//-----------------------------------------------------------------------
CTlgElem* CTlgElemInt::clone() const
{
  return new CTlgElemInt(*this);
}
//------------------------------------------------------------------------
void CTlgElemInt::getValue(std::string& value)const
{
  //if (this->Value == -1)
  //{
  //  value="";
  //}
  //else
  {
    value=CFormatConverter::IntToString(this->Value);
  } 
}
//--------------------------------------------------------------------
int CTlgElemInt::serialize(char* buffer,int len,CInterConfig* interConfig)
{
	int ret=-1; // Rueckgabewert im Fehlerfall
	CElemDescription::TransportType trans = getElemTranspTyp();
	switch(trans)
	{
		case CElemDescription::binary:
			ret=serializeAsBinary(buffer,len,interConfig);
			break;
		case CElemDescription::ascii:
			ret=serializeAsASCII(buffer,len,interConfig);
			break;
    case CElemDescription::binaryRD:
      ret=0; //Das Elememt wird nicht berucksichtigt
      break;
		default:
      std::string transStr=CElemDescription::getDescriptionInztanz(DescrIndex)->getTransTypAsString();
			throw CExpUnknownTranspTyp(transStr,"",getNameElem());
	}
	return ret;
}
//---------------------------------------------------------------------
int CTlgElemInt::serializeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
  int ret = -1;
	std::string valStr = CFormatConverter::IntToString(Value);
	int lenElem = getLen();
	int lenVal = int(valStr.size());

  std::string numFmt;
    
  this->getNumFmt(numFmt);


  //ergaenzen des Wert um fehlende Anzahl der Bytes
	if(lenElem > lenVal)
	{
    if ( !numFmt.empty() )
    {
      valStr = getFormattedElemValue(valStr,numFmt);
    }
    else
    {
	    char paddChar = interConfig->getPaddingString();

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
//---------------------------------------------------------------------
int CTlgElemInt::serializeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
	int elemLen;
	int i,pos,factor;
	int val;
  char maske = -1;
  char buff_char;
  bool swapping;

	elemLen = getLen();
	val = Value;
  swapping = interConfig->getSwapping();
  //Einstellung der Bytereihenfolge fuer Kodierung
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
		buff_char = val & maske;
		buffer[pos+factor*i] = buff_char;
    if(i != elemLen-1)
      val = val >> 8;
	}
	return elemLen;
}
//---------------------------------------------------------------------
void CTlgElemInt::getElemAsString(std::string& elem,const std::string& del)
{
  //if (this->Value == -1)
  //{
  //   elem=""; 
  //}
  //else
  {
    elem = CFormatConverter::IntToString(Value);

  	if ( getLen() > int(elem.size()) )
    {
      std::string numFmt;
      
      this->getNumFmt(numFmt);

      if ( !numFmt.empty() )
      {
        elem = getFormattedElemValue(elem,numFmt);
      }
    }
  }
}
//---------------------------------------------------------------------
void CTlgElemInt::setValue(const std::string& val,CInterConfig* interConf)
{
	CInterConfig::LimitValueTyp limTyp;
	CElemDescription* elemDescr=0;
	int len;
	elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	len=elemDescr->getElemLen();
	int valInt=0;
	try
	{ //Konvertieren val nach integer abhaengig von Laenge des Elements;
      valInt = CFormatConverter::StringToInt(val,len);
		//if(len == 4)
			//valInt = CFormatConverter::StringToInt(val);
		//else
			//valInt = CFormatConverter::StringToShortInt(val);
	}
	catch(CExpConvertError& e)
	{
		e.setElem(this->getNameElem());
		throw ;
	}
	limTyp=interConf->getLimitTreatment();
  // Behandeln Grenzwerten, wenn Einstelung in CInterConfig 
  // nicht Accsept ist.
	if(!(limTyp == CInterConfig::Accept))
	{
		std::string min_("");
		std::string max_("");
		int limInt=0;
		min_=elemDescr->getMinElem();
		max_=elemDescr->getMaxElem();
		if(!min_.empty())
		{
			limInt=CFormatConverter::StringToInt(min_);
			if(limInt > valInt)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valInt;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=limInt;
					throw CExpLimitError(CInterConfig::SetToMinMax,min_,max_,val,"",this->getNameElem());
					//mess to min
				}
				if(limTyp == CInterConfig::Error)
				{
					throw CExpLimitError(CInterConfig::Error,min_,max_,val,"",this->getNameElem());
					//error
				}
			}
		}
		if(!max_.empty())
		{
			limInt=CFormatConverter::StringToInt(max_);
			if(limInt < valInt)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valInt;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=limInt;
					throw CExpLimitError(CInterConfig::SetToMinMax,min_,max_,val,"",this->getNameElem());
					//mess to max
				}
				if(limTyp == CInterConfig::Error)
				{
					throw CExpLimitError(CInterConfig::Error,min_,max_,val,"",this->getNameElem());
					//error
				}
			}
		}
		Value=valInt;
	}
	else
	{
		Value=valInt;
	}
	Value=valInt;
}
//---------------------------------------------------------------------
void CTlgElemInt::setDefaultValue()
{
	Value = -1;
}
//---------------------------------------------------------------------
int CTlgElemInt::decodeElem(char* bytes,int count,CInterConfig* interConfig)
{
	int ret = -1; // Rueckgabewert im Fehlerfall
	CElemDescription::TransportType trans = getElemTranspTyp();
  try
  {
    switch(trans)
    {
	    case CElemDescription::ascii:
		    ret=decodeAsASCII(bytes,count,interConfig);
		    break;
	    case CElemDescription::binary:
		    ret=decodeAsBinary(bytes,count,interConfig);
		    break;
      case CElemDescription::binaryRD:
        setDefaultValue();
        ret=0;
        break;
	    default:
		    //Fehler: ubekannte Kodierungstyp
        std::string transStr=CElemDescription::getDescriptionInztanz(DescrIndex)->getTransTypAsString();
        throw CExpUnknownTranspTyp(transStr,"",getNameElem());
    }
  }
  catch(CExpConvertError& e)
  {
    e.setElem(getNameElem());
    throw e;
  }
	return ret;
}
//---------------------------------------------------------------------
int CTlgElemInt::decodeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	int ret=-1;
	std::string val("");
	int elemLen = getLen();
	val.append(buffer,elemLen);
	removeFillChar(val,interConfig);
	Value=CFormatConverter::StringToInt(val,elemLen);
	return elemLen;
}
//-----------------------------------------------------------------------
int CTlgElemInt::decodeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
	int ret = -1;
	bool swapping;
	int elemLen;
	char* bytes=0;
	int pos,fac;
	int i;
  //	int maske;
	int* val;

	elemLen=getLen();
	if(len == elemLen)
	{
		bytes = new char[sizeof(char)*sizeof(int)];
		for(i=0;i< sizeof(int);i++)
			bytes[i]=0;
		swapping = interConfig->getSwapping();
		if(swapping)
		{
      if (len == 2)
      {
        for (int i=0; i<len-1; ++i) 
        {
          std::swap(buffer[i], buffer[i+1]);
          i += 1;
        }
        int n = 0;
        for (int i=0; i<len; ++i)
        {
          unsigned char x = buffer[i];
          n += (x << i*8);
        }
        val = &n;
      }
      else
      {
			  pos = sizeof(int)-1;
			  fac = -1;
		    for(i=0;i<len;i++)
			    bytes[i]=buffer[pos+i*fac];

  		  val=(int*)bytes;
      }
		}
		else
		{
			pos = 0;
			fac = 1;
		  for(i=0;i<len;i++)
			  bytes[i]=buffer[pos+i*fac];

  		val=(int*)bytes;
		}
		Value = *val;
		delete bytes;
		ret=len;
		//if(elemLen<4)
		//{
		//	maske=2;
		//	maske=maske << (8*elemLen-1);
		//	maske--;
		//	if(((*val) && maske) != (*val))
		//		ret=-1;
		//}
	}
	return ret;
}
//---------------------------------------------------------------------
int CTlgElemInt::compare(const std::string& val,const std::string& subElemName)
{
  int ret = -2;
  int valInt;
  try
  {
    valInt=CFormatConverter::StringToInt(val);
    if(Value == valInt)
    {
      ret=0;
    }
    else if(Value < valInt)
    {
        ret=-1;
    }
    else
    {
      ret=1;
    }
  }
  catch(...)
  {
    std::string mess("unknown error by string values compare");
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemInt::getTransBytesCount() const
{
	int ret;
	CElemDescription::TransportType trans = getElemTranspTyp();
	switch(trans)
	{
		case CElemDescription::binaryRD:
			ret=0;
			break;
		default:
			ret=getLen();
			break;
	}
	return ret;
}
//---------------------------------------------------------------------
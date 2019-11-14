// Copyright 2006 SMS - Demag AG

//----------------------------------------------------------------------
#include "CTlgElemFloat.h"
#include "CLogWriter.h"

#pragma warning( disable : 4996 )

//----------------------------------------------------------------------
CTlgElemFloat::CTlgElemFloat(const CElemDescription::TransportType transp,const int len,
							 const float val,const std::string& name):
CTlgElem(transp,len,name)
{
	Value = val;
}
//---------------------------------------------------------------------
CTlgElemFloat::CTlgElemFloat(int index):
CTlgElem(index)
{
  this->setDefaultValue();
}
//---------------------------------------------------------------------
CTlgElemFloat::CTlgElemFloat(const CTlgElemFloat& Obj)
{
	std::string val("");
	Obj.getValue(val);
	this->Value = CFormatConverter::StringToFloat(val);
  this->DescrIndex = Obj.getDescrIndex();
	CElemDescription::reserveElemDescription(DescrIndex);
}
//---------------------------------------------------------------------
CTlgElemFloat::~CTlgElemFloat()
{
}
//----------------------------------------------------------------------
CTlgElem* CTlgElemFloat::clone() const
{
	return new CTlgElemFloat(*this);
}
//------------------------------------------------------------------------
void CTlgElemFloat::getValue(std::string& value) const
{
  //if (this->Value == -1.0)
  //{
  //  value="";
  //}
  //else
  //{
  value=CFormatConverter::FloatToString(this->Value);
  //} 
}
//-------------------------------------------------------------------------
void CTlgElemFloat::setValue(const std::string& val,CInterConfig* interConf)
{
	CInterConfig::LimitValueTyp limTyp;
	CElemDescription* elemDescr=0;
	float valFloat;
	elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);

	//Konvertierung nach float - Wert
	try
	{
		valFloat = CFormatConverter::StringToFloat(val);
	}
	catch(CExpConvertError& e)
	{
		e.setElem(this->getNameElem());
		throw;
	}
	//behandeln der Grenzwerte
	limTyp=interConf->getLimitTreatment();
	if(!(limTyp == CInterConfig::Accept))
	{
		std::string min_("");
		std::string max_("");
		float limFloat=0;
		min_=elemDescr->getMinElem();
		max_=elemDescr->getMaxElem();
		if(!min_.empty())
		{
			limFloat=CFormatConverter::StringToFloat(min_);
			if(limFloat > valFloat)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valFloat;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=valFloat;
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
			limFloat=CFormatConverter::StringToFloat(max_);
			if(limFloat < valFloat)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valFloat;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=limFloat;
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
		Value=valFloat;
	}
	else
	{
		Value=valFloat;
	}
	Value=valFloat;
}
//--------------------------------------------------------------------------
void CTlgElemFloat::setDefaultValue()
{
	Value = -1.0;
}
//--------------------------------------------------------------------------
int CTlgElemFloat::serialize(char* buffer,int len,CInterConfig* interConfig)
{
	int ret=-1;
	CElemDescription::TransportType trans = getElemTranspTyp();

	switch(trans)
	{
		case CElemDescription::ascii:
			ret=serializeAsASCII(buffer,len,interConfig);
			break;
		case CElemDescription::binary:
			ret=serializeAsBinary(buffer,len,interConfig);
			break;
		default:
			throw CExpUnknownTranspTyp("","",getNameElem());
			//fehler
	}
	//if((trans == CElemDescription::TransportType::binary))
	//{
		//ret=serializeAsBinary(buffer,len,interConfig);
	//}
	//else
	//{
	//if(trans == CElemDescription::TransportType::ascii)
	//{
		//ret=serializeAsASCII(buffer,len,interConfig);
	//}
	//else
	//{
		//Fehler: ubekannte Kodierungstyp
          //throw CExpUnknownTranspTyp("","",getNameElem());
	//}
	//}
	return ret;
}
//--------------------------------------------------------------------------
int CTlgElemFloat::serializeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	std::string valStr = CFormatConverter::FloatToString(Value);
	int lenElem = getLen(); 
	int lenVal = int(valStr.size());
	int ret = -1;

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
//----------------------------------------------------------------------------
int CTlgElemFloat::serializeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
	float val = Value;
	char* p_val = (char*)&val;
	int i,pos,factor;
	int lenFloat = sizeof(float);
  bool swapping = interConfig->getSwapping();

	//Einstellung der Bytereihenfolge fuer Kodierung
	if(!swapping)
	{
		pos = 0;
		factor = 1;
	}
	else
	{
		pos = len-1;
		factor = -1;
	}
	//Kopieren den Wert binaer in buffer
	for(i=0;i<lenFloat;i++)
	{
		buffer[pos+factor*i] = (*p_val);
		p_val++;
	}
	return lenFloat;
}
//--------------------------------------------------------------------------
void CTlgElemFloat::getElemAsString(std::string& elem,const std::string& del)
{
  //if (this->Value == -1)
  //{
  //   elem=""; 
  //}
  //else
  //{
    elem = CFormatConverter::FloatToString(Value);

  	if ( getLen() > int(elem.size()) )
    {
      std::string numFmt;
      
      this->getNumFmt(numFmt);

      if ( !numFmt.empty() )
      {
        elem = getFormattedElemValue(elem,numFmt);
      }
    }

  //  } 
}
//----------------------------------------------------------------------------
int CTlgElemFloat::decodeElem(char* bytes,int count,CInterConfig* interConfig)
{
	int ret = -1;
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
//----------------------------------------------------------------------------
int CTlgElemFloat::decodeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	std::string val("");
	int elemLen = getLen();
	
	val.append(buffer,elemLen);
	removeFillChar(val,interConfig);
	Value=CFormatConverter::StringToFloat(val);
	return elemLen;
}
//----------------------------------------------------------------------------
int CTlgElemFloat::decodeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
	int ret = -1;
	bool swapping;
	int elemLen;
	int i,pos;
	int fac;
	char* bytes;
	float* val=0;;
	elemLen=getLen();
	if(elemLen == len)
	{
		bytes=new char[len*sizeof(char)];
		swapping=interConfig->getSwapping();
		if(swapping)
		{
			pos=len-1;
			fac=-1;
		}
		else
		{
			pos=0;
			fac=1;
		}
		for(i=0;i<len;i++)
			bytes[i]=buffer[pos+i*fac];

		val=(float*)bytes;
		Value = *val;
		delete bytes;
		ret=len;
	}
  else
  {
    std::string mess("elemLen != len (parameter)");
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
	return ret;
}
//----------------------------------------------------------------------------
int CTlgElemFloat::compare(const std::string& val,const std::string& subElemName)
{
  int ret = -2;
  float valFloat;
  try
  {
    valFloat=CFormatConverter::StringToFloat(val);
    if(Value == valFloat)
    {
      ret=0;
    }
    else if(Value < valFloat)
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
    std::string mess("unknow error by float values compare");
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  return ret;
}
//----------------------------------------------------------------------------
int CTlgElemFloat::getTransBytesCount() const
{
	return getLen();
}
//----------------------------------------------------------------------------

// Copyright 2006 SMS - Demag AG

#include "CTlgElemDoubl.h"
#include "CLogWriter.h"

#pragma warning( disable : 4996 )

//---------------------------------------------------------------------
CTlgElemDoubl::CTlgElemDoubl(const CElemDescription::TransportType transp,const int len,
							 const double val ,const std::string& name):
CTlgElem(transp,len,name)
{
	this->Value = val;
}
//----------------------------------------------------------------------
CTlgElemDoubl::CTlgElemDoubl(int index):
CTlgElem(index)
{
  this->setDefaultValue();
}
//----------------------------------------------------------------------
CTlgElemDoubl::CTlgElemDoubl(const CTlgElemDoubl& Obj)
{
	std::string val("");
	Obj.getValue(val);
	this->Value = CFormatConverter::StringToDouble(val);
  this->DescrIndex = Obj.getDescrIndex();
	CElemDescription::reserveElemDescription(DescrIndex);
}
//----------------------------------------------------------------------
CTlgElemDoubl:: ~CTlgElemDoubl()
{
}
//----------------------------------------------------------------------
CTlgElem* CTlgElemDoubl::clone() const
{   
  return new CTlgElemDoubl(*this);
}
//----------------------------------------------------------------------
int CTlgElemDoubl::serialize(char* buffer,int len,CInterConfig* interConfig)
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
	}
	//if((trans == CElemDescription::TransportType::binary))
	//{
	//  ret=serializeAsBinary(buffer,len,interConfig);
	//}
	//else
	//{
	//  if(trans == CElemDescription::TransportType::ascii)
	//{
	//  ret=serializeAsASCII(buffer,len,interConfig);
  //}
	//else
	//{
	//  //Fehler: ubekannte Kodierungstyp
  //  throw CExpUnknownTranspTyp("","",getNameElem());
	// }
	//}
	return ret;
}
//----------------------------------------------------------------------
int CTlgElemDoubl::serializeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	std::string valStr = CFormatConverter::DoublToString(Value);
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
	if(len == (int)valStr.length())
	{
		valStr.copy(buffer,lenElem);
		ret=len;
	}

	return ret;
}
//----------------------------------------------------------------------
int CTlgElemDoubl::serializeAsBinary(char* buffer,int len,CInterConfig* interConfig)
{
	double val = Value;
	char* p_val = (char*)&val;
	int i,pos,factor;
	int lenDoubl=sizeof(double);
  bool swapping = interConfig->getSwapping();
	//Einstellung der Bytereihenfolge fuer Kodierung
	if(!swapping)
	{
		pos = 0;
		factor = 1;
	}
	else
	{
		pos = lenDoubl-1;
		factor = -1;
	}
	//Kopieren den Wert binaer in buffer
	for(i=0;i<lenDoubl;i++)
	{
		buffer[pos+factor*i] = (*p_val);
		p_val++;
	}
	return lenDoubl;
}
//----------------------------------------------------------------------
void CTlgElemDoubl::getElemAsString(std::string& elem,const std::string& del)
{
  //if (this->Value == -1)
  //{
  //   elem=""; 
  //}
  //else
  //{
  elem = CFormatConverter::DoublToString(Value);

	if ( getLen() > int(elem.size()) )
  {
    std::string numFmt;
    
    this->getNumFmt(numFmt);

    if ( !numFmt.empty() )
    {
      elem = getFormattedElemValue(elem,numFmt);
    }
  }

  //}  
}
//-----------------------------------------------------------------------
void CTlgElemDoubl::getValue(std::string& value) const
{
  //if (this->Value == -1.0)
  //{
  //  value="";
  //}
  //else
  //{
  value=CFormatConverter::DoublToString(this->Value);
  //} 
}
//--------------------------------------------------------------------
void CTlgElemDoubl::setValue(const std::string& val,CInterConfig* interConf)
{
	CInterConfig::LimitValueTyp limTyp;
	CElemDescription* elemDescr=0;
	int len;
	elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	len=elemDescr->getElemLen();
	double valDoubl=0.0;
	try
	{
		valDoubl = CFormatConverter::StringToDouble(val);
	}
	catch(CExpConvertError& e)
	{
		e.setElem(this->getNameElem());
		throw;
	}
	limTyp=interConf->getLimitTreatment();
	if(!(limTyp == CInterConfig::Accept))
	{
		std::string min_("");
		std::string max_("");
		int limDoubl=0;
		min_=elemDescr->getMinElem();
		max_=elemDescr->getMaxElem();
		if(!min_.empty())
		{
			limDoubl=CFormatConverter::StringToInt(min_);
			if(limDoubl > valDoubl)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valDoubl;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=limDoubl;
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
			limDoubl=CFormatConverter::StringToInt(max_);
			if(limDoubl < valDoubl)
			{
				if(limTyp == CInterConfig::Warning)
				{
					Value=valDoubl;
					throw CExpLimitError(CInterConfig::Warning,min_,max_,val,"",this->getNameElem());
					//warnig
				}
				if(limTyp == CInterConfig::SetToMinMax)
				{
					Value=limDoubl;
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
		Value=valDoubl;
	}
	else
	{
		Value=valDoubl;
	}
}
//--------------------------------------------------------------------
void CTlgElemDoubl::setDefaultValue()
{
	Value = -1.0;
}
//--------------------------------------------------------------------
int CTlgElemDoubl::decodeElem(char* bytes,int count,CInterConfig* interConfig)
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
//--------------------------------------------------------------------
int CTlgElemDoubl::decodeAsASCII(char* buffer,int len,CInterConfig* interConfig)
{
	std::string val("");
	int elemLen = getLen();
	
	val.append(buffer,elemLen);
	removeFillChar(val,interConfig);
	Value=CFormatConverter::StringToDouble(val);
	return elemLen;
}
//----------------------------------------------------------------------
int CTlgElemDoubl::decodeAsBinary(char* bytes,int len,CInterConfig* interConfig)
{
	int ret = -1;
	char* buffer=0;
	int lenElem;
	bool swapping;
	int pos,i,fac;
	double* val=0;

	lenElem=getLen();
	if(lenElem == len)
	{
		buffer=new char[len*sizeof(char)];
		swapping=interConfig->getSwapping();
		if(swapping)
		{
			pos=len-1;
			fac = -1;
		}
		else
		{
			pos=0;
			fac=1;
		}
		for(i=0;i<len;i++)
			buffer[i]=bytes[pos+i*fac];
		
		val=(double*)buffer;
		Value = *val;
		delete buffer;
	}
	else
	{
		ret=-1;
	}

	return ret;
}
//--------------------------------------------------------------------
int CTlgElemDoubl::compare(const std::string& val,const std::string& subElemName)
{
  int ret = -2;
  double valDoubl;
  try
  {
    valDoubl=CFormatConverter::StringToDouble(val);
    if(Value == valDoubl)
    {
      ret=0;
    }
    else if(Value < valDoubl)
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
    std::string mess = "Unknown error by double values compare";
    CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);
  }
  return ret;
}
//--------------------------------------------------------------------
int CTlgElemDoubl::getTransBytesCount() const
{
	return getLen();
}
//--------------------------------------------------------------------
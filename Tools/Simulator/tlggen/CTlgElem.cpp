// Copyright 2006 SMS - Demag AG

#include "CElemDescription.h"
#include "CTlgElem.h"
#include "CLogWriter.h"
//----------------------------------------------------------------------
CTlgElem::CTlgElem()
{
}
//----------------------------------------------------------------------
CTlgElem::CTlgElem(const CElemDescription::TransportType transp,
					 const int len,const std::string& name)
{
	int index=0;
	CElemDescription* descr=0;
	index = CElemDescription::createDescription();
	this->DescrIndex = index;
	CElemDescription::reserveElemDescription(index);
	descr = CElemDescription::getDescriptionInztanz(index);
	descr->setTtranspTypeElem(transp);
	descr->setElemLen(len);
	descr->setNameElem(name);
}
//---------------------------------------------------------------------
CTlgElem::CTlgElem(const std::string& name,const long count,const CElemDescription::ElementType elemTyp)
{
	int index=0;
	CElemDescription* descr=0;
	index = CElemDescription::createDescription();
  this->DescrIndex = index;
	CElemDescription::reserveElemDescription(index);
	descr = CElemDescription::getDescriptionInztanz(index);
	descr->setNameElem(name);
	descr->setElemType(CElemDescription::tArray);
	descr->setElemCount(count);
}
//---------------------------------------------------------------------
CTlgElem::CTlgElem(int index):
DescrIndex(index)
{
	CElemDescription::reserveElemDescription(index);
}
//---------------------------------------------------------------------
CTlgElem::~CTlgElem()
{
  freeElemDescription();
}
//---------------------------------------------------------------------
const std::string &  CTlgElem::getNameElem() const
{
	return CElemDescription::getDescriptionInztanz(DescrIndex)->getNameElem();
}
//----------------------------------------------------------------------
void CTlgElem::setComment(const std::string& comment)
{
	CElemDescription::getDescriptionInztanz(DescrIndex)->setElemDescr(comment);
}
//----------------------------------------------------------------------
const std::string& CTlgElem::getComment() const
{
	return CElemDescription::getDescriptionInztanz(DescrIndex)->getElemDescr();
}
//----------------------------------------------------------------------
int CTlgElem::getLen() const
{
	return CElemDescription::getDescriptionInztanz(DescrIndex)->getElemLen();
}
//----------------------------------------------------------------------
int CTlgElem::getTransBytesCount() const
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
//----------------------------------------------------------------------
void CTlgElem::setElemInfo(const std::string& unit,const std::string& factor,const std::string& min,const std::string& max,const std::string& numFmt)
{
	CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	elemDescr->setUnitElem(unit);
	elemDescr->setFactorElem(factor);
	elemDescr->setMinElem(min);
	elemDescr->setMaxElem(max);
  elemDescr->setNumFmtElem(numFmt);
}
//-----------------------------------------------------------------------
void CTlgElem::getMinMax(std::string& min,std::string& max)
{
	CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	min=elemDescr->getMinElem();
	max= elemDescr->getMaxElem();
}
//-----------------------------------------------------------------------
void CTlgElem::getNumFmt(std::string& numFmt)
{
	CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
  numFmt = elemDescr->getNumFmtElem();
}

std::string CTlgElem::getFormattedElemValue(const std::string& ElemValue, const std::string& numFmt)
{
  std::string FormattedElemValue;
  // possible formats
  // 999999   -> as integer number with max of 6 digits
  // 999999.9 -> as float number with max of 6 digits and 1 decimal
  // 000000   -> as integer number with max of 6 digits with left padding "0"
  // 000000.0 -> as float number with max of 6 digits and 1 decimal and with left padding "0"

  // find single parts of ElemValue and numFmt
  std::string::size_type ElemDecPos = ElemValue.find_first_of(".");
  std::string ElemValueNum = ElemValue;
  std::string ElemValueDec;
  std::string ElemValuePre;

  // we found a decimal delimiter, so divide ElemValue into ElemValueNum and ElemValueDec part
  if ( ElemDecPos != std::string::npos )
  {
    ElemValueNum = ElemValue.substr(0,ElemDecPos);
    ElemValueDec = ElemValue.substr(ElemDecPos,ElemValue.length());
  }

  if ( ElemValueNum.find_first_of("-") != std::string::npos )
  {
    ElemValuePre = "-";
    ElemValueNum = ElemValueNum.substr(1,ElemValueNum.length());
  }

  // we found a decimal delimiter in format, so divide numFmt into numFmtNum and numFmtDec part
  std::string::size_type numDecPos = numFmt.find_first_of(".");
  std::string numFmtNum = numFmt;
  std::string numFmtDec;

  if ( numDecPos != std::string::npos )
  {
    numFmtNum = numFmt.substr(0,numDecPos);
    numFmtDec = numFmt.substr(numDecPos,numFmt.length());
  }

  std::string::size_type FillDec  = numFmtDec.length() - ElemValueDec.length();
  std::string::size_type FillNum  = numFmtNum.length() - ElemValueNum.length() - ElemValuePre.length();

  if ( ElemValuePre.empty() )
  {
    FillNum  = numFmtNum.length() - ElemValueNum.length();
  }

  if ( FillNum >= 0 ) // Value fits into format but needs to be padded
  {
    // we will transport as "0"-padded string with leading "-"
    if ( numFmt.find_first_of("0") != std::string::npos )
    {
      FormattedElemValue = ElemValuePre;
      FormattedElemValue.append(FillNum,'0');
      FormattedElemValue.append(ElemValueNum);

      // add decimals
      if ( numDecPos != std::string::npos )
      {
        FormattedElemValue.append(".");
        FormattedElemValue.append(ElemValueDec);
      }

      // truncate to format lenght

      FormattedElemValue = FormattedElemValue.substr(0,numFmt.length());

    }
    else
    {
      // we will transport as it is
    }
  }
  else
  {
    FormattedElemValue = numFmt;
  }

  return FormattedElemValue;

}


//-----------------------------------------------------------------------
void CTlgElem::getElemInfo(std::string& unit,std::string& factor,std::string& min,std::string& max) const
{
	CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	unit = elemDescr->getUnitElem();
	factor = elemDescr->getFactorElem();
	min = elemDescr->getMinElem();
	max = elemDescr->getMaxElem();
}
//------------------------------------------------------------------------
std::string CTlgElem::getTranspTyp() const
{
  std::string ret("");
  CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
  CElemDescription::TransportType trans = elemDescr->getTranspTypeElem();
  if(trans == CElemDescription::ascii)
    ret.assign("ascii");
  if(trans == CElemDescription::binary)
    ret.assign("binary");
  if(trans == CElemDescription::binaryL3D)
    ret.assign("binaryL3D");
  if(trans == CElemDescription::binaryCCSD)
    ret.assign("binaryCCSD");
  if(trans == CElemDescription::binaryRD)
	  ret.assign("binaryRD");
  if(trans == CElemDescription::binaryRS)
    ret.assign("binaryRS");
  if(trans == CElemDescription::unknow)
    ret.assign("unknow");

  return ret;
}
//------------------------------------------------------------------------
CElemDescription::TransportType CTlgElem::getElemTranspTyp() const
{
	CElemDescription* elemDescr = CElemDescription::getDescriptionInztanz(DescrIndex);
	return elemDescr->getTranspTypeElem();
}
//------------------------------------------------------------------------
void CTlgElem::setElemType(const CElemDescription::ElementType& elemType)
{
	CElemDescription::getDescriptionInztanz(DescrIndex)->setElemType(elemType);
}
//------------------------------------------------------------------------
CElemDescription::ElementType CTlgElem::getElemType() const
{
	return CElemDescription::getDescriptionInztanz(DescrIndex)->getElemType();
}
//------------------------------------------------------------------------
int CTlgElem::getDescrIndex() const
{
  return DescrIndex;
}
//------------------------------------------------------------------------
void CTlgElem::removeFillChar(std::string& val,CInterConfig* interConfig)
{
	char fill = interConfig->getPaddingString();
	if(fill == 0)
		fill=' ';
	CInterConfig::PaddingTyp dir = interConfig->getPaddingDirection();
	if(dir == CInterConfig::Left)
	{
		while((val.size() > 0) && (val[0] == fill))
			val.erase(0,1);
	}
	else
	{
		int length = int(val.size());
		while((length > 0) && (val[length-1] == fill))
		{
			val.erase(length-1,1);
			length--;
		}
	}
}
//------------------------------------------------------------------------
void CTlgElem::addSubElem(CTlgElem* elem)
{
}
//------------------------------------------------------------------------
CTlgElem* CTlgElem::getSubElem(int id) const
{
 /* std::string mess = "This methode is not implement in this class";
  CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);*/
  return 0;
}
//------------------------------------------------------------------------
CTlgElem* CTlgElem::getSubElem(const std::string& id) const
{
 /* std::string mess = "This methode is not implement in this class";
  CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);*/
  return 0;
}
//------------------------------------------------------------------------
int CTlgElem::getSubElemCount() const
{
 /* std::string mess = "This methode is not implement in this class";
  CLogWriter::getLogWriter()->WriteMessage(CLogWriter::Error,mess,__FILE__,__FUNCTION__,__LINE__);*/
  return 0;
}
//------------------------------------------------------------------------
void CTlgElem::freeElemDescription()
{
  CElemDescription::releaseElemDescription(DescrIndex);
}
//------------------------------------------------------------------------
void CTlgElem::longToByteStream(char* buffer,long val,CInterConfig* interConfig)
{
	int i,pos,factor;
  char maske = -1;
  char buff_char;
  bool swapping;

  swapping = interConfig->getSwapping();
  //Einstellung der Bytereihenfolge fuer Kodierung
	if(!swapping)
	{
		pos = 0;
		factor = 1;
	}
	else
	{
		pos = 3;
		factor = -1;
	}
  // Kodierung des Wertes in Byte - Stream (Ergebniss in buffer)
	for(i=0;i<4;i++)
	{
		buff_char = val & maske;
		buffer[pos+factor*i] = buff_char;
		val = val >> 8;
	}
}
//------------------------------------------------------------------------
long CTlgElem::byteStreamToLong(char* buffer,CInterConfig* interConfig)
{
  long ret=0;
  bool swapping;
  char* p_ch=0;
  int sizeOfLong;
  int i;
  long* p_long=0;

  sizeOfLong=sizeof(long);
  swapping = interConfig->getSwapping();
  p_ch = new char[sizeOfLong*sizeof(char)];
  for(i=0;i<sizeOfLong;i++)
    p_ch[i]=buffer[i];

  if(swapping)
    swapBytes(p_ch,sizeOfLong);

  p_long = (long*)p_ch;
  ret = (*p_long);

  delete p_ch;

  return ret;
}
//------------------------------------------------------------------------
void CTlgElem::swapBytes(char* bytes,int count)
{
  char c;
  for(int i=0;i<count/2;i++)
  {
    c=bytes[i];
    bytes[i]=bytes[count-i-1];
    bytes[count-i-1]=c;
  }
}
//------------------------------------------------------------------------
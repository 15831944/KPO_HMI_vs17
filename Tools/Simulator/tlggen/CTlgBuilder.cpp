// Copyright 2006 SMS - Demag AG

//--------------------------------------------------------------
#include "CTlgBuilder.h"
#include "CTlgElemString.h"
#include "CTlgElemDoubl.h"
#include "CTlgElemInt.h"
#include "CTlgElemFloat.h"
#include "CTlgElemSegment.h"
#include "CTlgDescription.h"
#include "CExpUnknownElemTyp.h"
#include "CExpUnknowTranspTyp.h"
#include <assert.h>
//-------------------------------------------------------------
//---------------------------------------------------------------
CTlgBuilder::CTlgBuilder():
Tlg(0)/*TlgElem(0),RecordElem(0),ArrayElem(0)*/
{
}
//---------------------------------------------------------------
CTlgBuilder::~CTlgBuilder()
{
}
//---------------------------------------------------------------
void CTlgBuilder::makeTlg(const std::string& name,const long len,const std::string& dir)
{
	int index;
	index=CTlgDescription::createTlgDescription();
	Tlg = new CTlg(name,len,dir,index);
	ElemVect.clear();
	//TlgElem = 0;
	//RecordElem = 0;
	//ArrayElem = 0;
}
//---------------------------------------------------------------
CTlg* CTlgBuilder::getTlg()
{
	//TlgElem = 0;
	//RecordElem = 0;
	//ArrayElem = 0;
	//Elem = NULL;
	//ContextElem = NULL;
	assert(ElemVect.size() == 0);
	return Tlg;
}
//---------------------------------------------------------------
void CTlgBuilder::makeArrayElement(const std::string& name,long count)
{
	//ArrayElem = new CTlgElemSegment(name,CElemDescription::ElementType::tArray,count);
	CTlgElem* elem = new CTlgElemSegment(name,CElemDescription::tArray,count);
	ElemVect.push_back(elem);
}
//------------------------------------------------------------------
void CTlgBuilder::endArray()
{
	int countElem = ElemVect.size();
	CTlgElem* elem = ElemVect[countElem-1];
	CElemDescription* descr = CElemDescription::getDescriptionInztanz(elem->getDescrIndex());
	int count = elem->getSubElemCount();
	int len=0;
	for(int i=1;i<=count;i++)
		len = len + elem->getSubElem(i)->getLen();
	descr->setElemLen(len);

	if(countElem >= 2)
		ElemVect[countElem - 2]->addSubElem(elem);
	else
		Tlg->addElem(elem);
	ElemVect.pop_back();
	//TlgElem=0;
	//RecordElem=0;
	//ArrayElem=0;
}
//-----------------------------------------------------------------
 void CTlgBuilder::setTlgDescr(const std::string& DescrStr)
 {
   Tlg->setDescription(DescrStr);
 }
//-----------------------------------------------------------------
void CTlgBuilder::setElemComment(const std::string& comment)
{
	ElemVect[ElemVect.size() - 1]->setComment(comment);
	//if(TlgElem)
	//{
	//	TlgElem->setComment(comment);
	//}
	//else
	//{
    //if(RecordElem)
	//	{
	//	  RecordElem->setComment(comment);
	//	}
	//	else
	//	{
	//	  if(ArrayElem)
	//	  {
	//		  ArrayElem->setComment(comment);
	//	  }
	//	}
	//}


}
//-----------------------------------------------------------------
/*void CTlgBuilder::setArrayAttribute(const std::string& elemType,const std::string& transpType,long elemLen)
{
	CElemDescription::ElementType type = stringToElemType(elemType,elemLen);
	CElemDescription::TransportType transp = stringToTranspType(transpType);
	CTlgElem* actElem = 0;
	
	if( (type != CElemDescription::ElementType::tUnknow) && (transp != CElemDescription::TransportType::unknow))
	{
		CTlgElem* elem = 0;
    int count = CElemDescription::getDescriptionInztanz(ArrayElem->getDescrIndex())->getElemCount();
		int index = CElemDescription::createDescription();
		CElemDescription* descr = CElemDescription::getDescriptionInztanz(index);
		descr->setElemCount(0);
		descr->setElemLen(elemLen);
		descr->setElemType(type);
		descr->setTtranspTypeElem(transp);
		for(int i=0;i<count;i++)
		{
      elem = createElement(type,index,elemLen);
      ArrayElem->addSubElem(elem);
		}
	}
	else
 	{ 
		if(type == CElemDescription::ElementType::tUnknow)
      throw CExpUnknownElemTyp(elemType,Tlg->getTlgName(),getActElemName());
    if(transp == CElemDescription::TransportType::unknow)
      throw CExpUnknownElemTyp(transpType,Tlg->getTlgName(),getActElemName());
	}
}*/
//-----------------------------------------------------------------
void CTlgBuilder::makeSimpleElement(const std::string& name,const std::string& elemType,long elemLen)
{
  CElemDescription::ElementType type = stringToElemType(elemType,elemLen);
  if(type != CElemDescription::tUnknow)
  {
	  CTlgElem* elem = NULL;
	  int index = CElemDescription::createDescription();
	  CElemDescription* descr = CElemDescription::getDescriptionInztanz(index);
	  descr->setNameElem(name);
	  descr->setElemType(type);
	  descr->setElemLen(elemLen);
	  elem = createElement(type,index,elemLen);
	  ElemVect.push_back(elem);
	  //TlgElem = createElement(type,index,elemLen);
  }
  else
  {
    if(type == CElemDescription::tUnknow)
      throw CExpUnknownElemTyp(elemType,Tlg->getTlgName(),getActElemName());
  }
}
//-----------------------------------------------------------------
void CTlgBuilder::endSimpleElement()
{
	int count = ElemVect.size();
	assert(count>0);
	if(count == 1)
	{
		Tlg->addElem(ElemVect[0]);
	}
	else
	{
		assert((ElemVect[count-2]->getElemType() != CElemDescription::tRecord) ||
			(ElemVect[count-2]->getElemType() != CElemDescription::tArray));

		ElemVect[count-2]->addSubElem(ElemVect[count-1]);
	}
	ElemVect.pop_back();
  //if(RecordElem)
  //{
   // RecordElem->addSubElem(TlgElem);
  //}
  //else
  //{
	//if(ArrayElem)
	//{
	//	ArrayElem->addSubElem(TlgElem);
	//}
	//else
	//{
	//	Tlg->addElem(TlgElem);
	//}
  //}
  //TlgElem=0;
}
//-----------------------------------------------------------------
void CTlgBuilder::makeRecords(const std::string& name)
{
	ElemVect.push_back(new CTlgElemSegment(name,CElemDescription::tRecord));
}
//-----------------------------------------------------------------
void CTlgBuilder::endRecordsElement()
{

  /*CElemDescription* descr = CElemDescription::getDescriptionInztanz(RecordElem->getDescrIndex());
  int count = RecordElem->getSubElemCount();
  int len=0;
  for(int i=1;i<=count;i++)
		len = len + RecordElem->getSubElem(i)->getLen();
	descr->setElemLen(len);
	if(ArrayElem)
	{
		int count = 0;
		count = CElemDescription::getDescriptionInztanz(ArrayElem->getDescrIndex())->getElemCount();
		for(int i=0;i<count;i++)
		{
			ArrayElem->addSubElem(RecordElem->clone());
		}
	}
	else
	{
		Tlg->addElem(RecordElem);
	}
  RecordElem = 0;*/

	int countElem = ElemVect.size();
	CElemDescription* descr = CElemDescription::getDescriptionInztanz(ElemVect[countElem-1]->getDescrIndex());
	int count = ElemVect[countElem-1]->getSubElemCount();
	int len=0;
	for(int i=1;i<=count;i++)
		len = len + ElemVect[countElem-1]->getSubElem(i)->getLen();
	descr->setElemLen(len);

	if(countElem>=2)
	{
		ElemVect[countElem-2]->addSubElem(ElemVect[countElem-1]);
	}
	else
	{
		Tlg->addElem(ElemVect[countElem-1]);
	}
	ElemVect.pop_back();
	
}
//-----------------------------------------------------------------
void CTlgBuilder::setElemInfo(const std::string& transp,const std::string& unit,const std::string& factor,
            const std::string& min,const std::string& max,const std::string& numFmt)
{
  /*int index = TlgElem->getDescrIndex();
  CElemDescription* descr = CElemDescription::getDescriptionInztanz(index);
  CElemDescription::TransportType transpType = stringToTranspType(transp);
  if(transpType == CElemDescription::TransportType::unknow)
    throw CExpUnknownElemTyp(transp,Tlg->getTlgName(),getActElemName());
  descr->setTtranspTypeElem(transpType);
  descr->setUnitElem(unit);
  descr->setFactorElem(factor);
  descr->setMinElem(min);
  descr->setMaxElem(max);*/

	int countElem = ElemVect.size();
	int index = ElemVect[countElem - 1]->getDescrIndex();
	CElemDescription* descr = CElemDescription::getDescriptionInztanz(index);
	CElemDescription::TransportType transpType = stringToTranspType(transp);
	if(transpType == CElemDescription::unknow)
		throw CExpUnknownElemTyp(transp,Tlg->getTlgName(),getActElemName());
	descr->setTtranspTypeElem(transpType);
	descr->setUnitElem(unit);
	descr->setFactorElem(factor);
	descr->setMinElem(min);
	descr->setMaxElem(max);
  descr->setNumFmtElem(numFmt);
}
//-----------------------------------------------------------------
CTlgElem* CTlgBuilder::createElement(CElemDescription::ElementType type,int index,int len)
{
  CTlgElem* ret = 0;
  if(type == CElemDescription::tInteger)
	ret = new CTlgElemInt(index);

	if(type == CElemDescription::tDouble)
	{
		if(len == 8)
			ret = new CTlgElemDoubl(index);
		else
			ret = new CTlgElemFloat(index);
	}

	if(type == CElemDescription::tString)
		ret = new CTlgElemString(index);

	if(type == CElemDescription::tRecord)
		ret = new CTlgElemSegment(index);
    return ret;
}
//-----------------------------------------------------------------
CElemDescription::ElementType CTlgBuilder::stringToElemType(const std::string& str,int len)
{
	CElemDescription::ElementType ret = CElemDescription::tUnknow;

  if(str == "integer")
	{
		//if(len == 4)
		ret = CElemDescription::tInteger;
		//if(len == 2)
		//	ret = CElemDescription::ElementType::tShowInteger;
	}
	if(str == "number")
	{
		//if(len == 8)
		ret = CElemDescription::tDouble;
		//if(len == 4)
		//	ret == CElemDescription::ElementType::tFloat;
	}
	if(str == "string")
		ret = CElemDescription::tString;

	return ret;
}
//-----------------------------------------------------------------
CElemDescription::TransportType CTlgBuilder::stringToTranspType(const std::string& str)
{
	CElemDescription::TransportType ret = CElemDescription::unknow;

	if(str == "binary")
		ret = CElemDescription::binary;
	if(str == "ascii")
		ret = CElemDescription::ascii;
  if(str == "binaryL3D")
      ret = CElemDescription::binaryL3D;
  if(str == "binaryCCSD")
      ret = CElemDescription::binaryCCSD;
	if(str == "binaryRD")
		ret = CElemDescription::binaryRD;
  if(str == "binaryRS")
      ret = CElemDescription::binaryRS;
    
	return ret;
}
//-----------------------------------------------------------------
std::string CTlgBuilder::getActElemName()
{
  std::string ret("");

  ret = ElemVect[ElemVect.size()-1]->getNameElem();
  /*if(ArrayElem)
  {
    ret=ArrayElem->getNameElem();
  }
  else
  {
    if(RecordElem)
    {
      ret=RecordElem->getNameElem();
    }
      else
      {
        if(TlgElem)
        {
          ret=TlgElem->getNameElem();
        }
      }
  }*/
  return ret;
}
//-----------------------------------------------------------------
void CTlgBuilder::setTlgInterName(const std::string& name)
{
	Tlg->setInterfaceName(name);
}
//-----------------------------------------------------------------